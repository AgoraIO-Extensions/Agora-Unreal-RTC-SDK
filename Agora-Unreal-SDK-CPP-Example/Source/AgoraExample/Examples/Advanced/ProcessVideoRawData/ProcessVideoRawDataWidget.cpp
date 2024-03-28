// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessVideoRawDataWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Texture2D.h"

void UProcessVideoRawDataWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

}

void UProcessVideoRawDataWidget::CheckPermission()
{
#if PLATFORM_ANDROID
	FString TargetPlatformName = UGameplayStatics::GetPlatformName();
	if (TargetPlatformName == "Android")
	{
		TArray<FString> AndroidPermission;
#if !AGORA_UESDK_AUDIO_ONLY || (!(PLATFORM_ANDROID || PLATFORM_IOS))
		AndroidPermission.Add(FString("android.permission.CAMERA"));
#endif
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UProcessVideoRawDataWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngineEx();

	int SDKBuild = 0;
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);


	RtcEngineProxy->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);
	UserVideoFrameObserver = MakeShared<FUserVideoFrameObserver>(this);
	MediaEngine->registerVideoFrameObserver(UserVideoFrameObserver.Get());
}

void UProcessVideoRawDataWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [ProcessVideoRawData]\n"
		"1. You can retrieve your raw video data (in this case, the data would be video frames captured by your webcam) and handle it yourself.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UProcessVideoRawDataWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UProcessVideoRawDataWidget::OnBtnJoinChannelClicked()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	MakeVideoViewForRawData();
}


void UProcessVideoRawDataWidget::OnBtnLeaveChannelClicked()
{
	int ret = RtcEngineProxy->leaveChannel();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	ReleaseVideoViewForRawData();
}


void UProcessVideoRawDataWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}



void UProcessVideoRawDataWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		ReleaseVideoViewForRawData();

		if (MediaEngine != nullptr)
		{
			MediaEngine->registerVideoFrameObserver(nullptr);
		}

		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		agora::rtc::ue::releaseAgoraRtcEngine();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

void UProcessVideoRawDataWidget::RenderRawData(agora::media::base::VideoFrame& videoFrame)
{
	TWeakObjectPtr<UProcessVideoRawDataWidget> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

	int Width = videoFrame.width;
	int Height = videoFrame.height;
	uint8* rawdata = new uint8[Width * Height * 4];
	memcpy(rawdata, videoFrame.yBuffer, Width * Height * 4);


#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			TWeakObjectPtr<UDraggableVideoViewWidget> VideoRenderViewWeakPtr(VideoRenderView);
			if (!VideoRenderViewWeakPtr.IsValid())
				return;

			if (RenderTexture == nullptr || !RenderTexture->IsValidLowLevel() || RenderTexture->GetSizeX() != Width || RenderTexture->GetSizeY() != Height)
				RenderTexture = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);

			uint8* raw = (uint8*)RenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			memcpy(raw, rawdata, Width * Height * 4);
			delete[] rawdata;
			RenderTexture->PlatformData->Mips[0].BulkData.Unlock();

#ifdef UpdateResource
#undef UpdateResource

			// For PLATFORM Windows
			RenderTexture->UpdateResource();

#define UpdateResource UpdateResourceW

#else
			RenderTexture->UpdateResource();
#endif
			RenderBrush.SetResourceObject(RenderTexture);
			RenderBrush.SetImageSize(FVector2D(Width, Height));

			VideoRenderViewWeakPtr->View->SetBrush(RenderBrush);

			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoRenderViewWeakPtr.Get());
			CanvasPanelSlot->SetSize(FVector2D(Width, Height));

		});
}


void UProcessVideoRawDataWidget::MakeVideoViewForRawData()
{
	ReleaseVideoViewForRawData();

	UWorld* world = GEngine->GameViewport->GetWorld();
	VideoRenderView = CreateWidget<UDraggableVideoViewWidget>(world, DraggableVideoViewTemplate);

	FText ShowedText = FText::FromString(FString("RawDataRenderView"));
	VideoRenderView->Text->SetText(ShowedText);

	UPanelSlot* PanelSlot = CanvasPanel_VideoView->AddChild(VideoRenderView);
	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoRenderView);
}

void UProcessVideoRawDataWidget::ReleaseVideoViewForRawData()
{
	if (VideoRenderView != nullptr)
	{
		VideoRenderView->RemoveFromParent();
		VideoRenderView = nullptr;
	}
}


#pragma region UI Utility

int UProcessVideoRawDataWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	/*
		For local view:
			please reference the callback function Ex.[onCaptureVideoFrame]

		For remote view:
			please reference the callback function [onRenderVideoFrame]

		channelId will be set in [setupLocalVideo] / [setupRemoteVideo]
	*/

	int ret = -ERROR_NULLPTR;

	if (RtcEngineProxy == nullptr)
		return ret;

	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);
		ret = RtcEngineProxy->setupLocalVideo(videoCanvas);
	}
	else
	{

		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);

		if (channelId == "") {
			ret = RtcEngineProxy->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	}

	return ret;
}

int UProcessVideoRawDataWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	int ret = -ERROR_NULLPTR;

	if (RtcEngineProxy == nullptr)
		return ret;

	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		ret = RtcEngineProxy->setupLocalVideo(videoCanvas);
	}
	else
	{
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		if (channelId == "") {
			ret = RtcEngineProxy->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	}
	return ret;
}

#pragma endregion


#pragma region AgoraCallback - IRtcEngineEventHandlerEx

void UProcessVideoRawDataWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UProcessVideoRawDataWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UProcessVideoRawDataWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UProcessVideoRawDataWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

#pragma endregion

#pragma region AgoraCallback - IVideoFrameObserver

bool UProcessVideoRawDataWidget::FUserVideoFrameObserver::onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
{
	if (!IsWidgetValid())
		return false;

	WidgetPtr->RenderRawData(videoFrame);

	return true;
}

bool UProcessVideoRawDataWidget::FUserVideoFrameObserver::onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
{
	return false;
}

bool UProcessVideoRawDataWidget::FUserVideoFrameObserver::onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId)
{
	return false;
}

bool UProcessVideoRawDataWidget::FUserVideoFrameObserver::onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame)
{
	return false;
}

bool UProcessVideoRawDataWidget::FUserVideoFrameObserver::onTranscodedVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	return false;
}


agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE UProcessVideoRawDataWidget::FUserVideoFrameObserver::getVideoFrameProcessMode()
{
	return agora::media::IVideoFrameObserver::PROCESS_MODE_READ_ONLY;
}

agora::media::base::VIDEO_PIXEL_FORMAT UProcessVideoRawDataWidget::FUserVideoFrameObserver::getVideoFormatPreference()
{
	return agora::media::base::VIDEO_PIXEL_RGBA;
}

#pragma endregion


