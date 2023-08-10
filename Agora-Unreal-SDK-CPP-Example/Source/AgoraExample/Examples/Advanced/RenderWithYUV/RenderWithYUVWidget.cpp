// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderWithYUVWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Texture2D.h"
#include "ImageUtils.h"


void URenderWithYUVWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);
	
	CheckPermission();
	
	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);
	
	SetBasicConfiguration();
}

void URenderWithYUVWidget::CheckPermission()
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



void URenderWithYUVWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	RtcEngineContext.audioScenario = AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT;
	RtcEngineContext.areaCode = AREA_CODE::AREA_CODE_GLOB;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	int SDKBuild = 0;
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(RtcEngineProxy->getVersion(&SDKBuild)), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	RtcEngineProxy->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);
	UserVideoFrameObserver = MakeShared<FUserVideoFrameObserver>(this);
	MediaEngine->registerVideoFrameObserver(UserVideoFrameObserver.Get());
}


void URenderWithYUVWidget::SetBasicConfiguration()
{
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->enableAudio();
	VideoEncoderConfiguration Config;
	Config.dimensions = VideoDimensions(640,360);
	Config.frameRate = 15;
	Config.bitrate = 0;
	int ret = RtcEngineProxy->setVideoEncoderConfiguration(Config);
	RtcEngineProxy->setChannelProfile(CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING);
	RtcEngineProxy->setClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void URenderWithYUVWidget::OnBtnJoinChannelClicked()
{
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void URenderWithYUVWidget::OnBtnLeaveChannelClicked()
{
	int ret = RtcEngineProxy->leaveChannel();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void URenderWithYUVWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void URenderWithYUVWidget::MakeVideoViewForYUVV()
{
	ReleaseVideoViewForYUVV();

	UWorld* world = GEngine->GameViewport->GetWorld();
	YUVVideoRenderView = CreateWidget<UDraggableVideoViewWidget>(world, DraggableVideoViewTemplate);

	FText ShowedText = FText::FromString(FString("YUV VideoView"));
	YUVVideoRenderView->Text->SetText(ShowedText);

	UPanelSlot* PanelSlot = CanvasPanel_VideoView->AddChild(YUVVideoRenderView);
	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(YUVVideoRenderView);

	YUVVideoRenderView->View->SetBrushFromMaterial(MatYUV);
	CanvasPanelSlot->SetSize(FVector2D(640, 360));
}

void URenderWithYUVWidget::ReleaseVideoViewForYUVV()
{
	if (YUVVideoRenderView != nullptr)
	{
		YUVVideoRenderView->RemoveFromParent();
		YUVVideoRenderView = nullptr;
	}
}

void URenderWithYUVWidget::RenderRawData(agora::media::base::VideoFrame& videoFrame)
{
	TWeakObjectPtr<URenderWithYUVWidget> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

	int OriginalWidth = videoFrame.width;
	int OriginalHeight = videoFrame.height;

	int YWidth = videoFrame.yStride;
	int YHeight = videoFrame.height;
	int YSize = YWidth * YHeight/* * sizeof(int)*/;
	uint8* YRawData = new uint8[YSize];
	memcpy(YRawData, videoFrame.yBuffer, YSize);

	int UWidth = videoFrame.uStride;
	int UHeight = videoFrame.height / 2.0;
	int USize = UWidth * UHeight /* * sizeof(int)*/;
	uint8* URawData = new uint8[USize];
	memcpy(URawData, videoFrame.uBuffer, USize);

	int VWidth = videoFrame.vStride;
	int VHeight = videoFrame.height / 2.0;
	int VSize = VWidth * VHeight/* * sizeof(int)*/;
	uint8* VRawData = new uint8[VSize];
	memcpy(VRawData, videoFrame.vBuffer, VSize);


	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!SelfWeakPtr.IsValid())
				return;

			TWeakObjectPtr<UDraggableVideoViewWidget> VideoRenderViewWeakPtr(YUVVideoRenderView);
			if (!VideoRenderViewWeakPtr.IsValid())
				return;
			
			EPixelFormat Format = EPixelFormat::PF_R8;
			UTexture2D* YRenderTexture = UTexture2D::CreateTransient(YWidth, YHeight, Format);
			uint8* YRaw = (uint8*)YRenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			memcpy(YRaw, YRawData, YSize);
			delete[] YRawData;
			YRenderTexture->PlatformData->Mips[0].BulkData.Unlock();
			

			UTexture2D* URenderTexture = UTexture2D::CreateTransient(UWidth, UHeight, EPixelFormat::PF_R8);
			uint8* URaw = (uint8*)URenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			memcpy(URaw, URawData, USize);
			delete[] URawData;
			URenderTexture->PlatformData->Mips[0].BulkData.Unlock();


			UTexture2D* VRenderTexture = UTexture2D::CreateTransient(VWidth, VHeight, EPixelFormat::PF_R8);
			uint8* VRaw = (uint8*)VRenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			memcpy(VRaw, VRawData, VSize);
			delete[] VRawData;
			VRenderTexture->PlatformData->Mips[0].BulkData.Unlock();

#ifdef UpdateResource
#undef UpdateResource

			// For PLATFORM Windows
			YRenderTexture->UpdateResource();
			URenderTexture->UpdateResource();
			VRenderTexture->UpdateResource();

#define UpdateResource UpdateResourceW

#else
			YRenderTexture->UpdateResource();
			URenderTexture->UpdateResource();
			VRenderTexture->UpdateResource();
#endif

			UBFL_ShaderTest::DrawTestShaderRenderTarget(
				GetWorld(),RT_Output,YRenderTexture,URenderTexture,VRenderTexture
			);



			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoRenderViewWeakPtr.Get());
			CanvasPanelSlot->SetSize(FVector2D(OriginalWidth, OriginalHeight));

		});
}

void URenderWithYUVWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

	
}

void URenderWithYUVWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		MediaEngine->registerVideoFrameObserver(nullptr);
		MediaEngine->release();
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region UI Utility

int URenderWithYUVWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int URenderWithYUVWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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


void URenderWithYUVWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	if (!IsWidgetValid())
		return;

	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoViewForYUVV();
			//WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void URenderWithYUVWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	if (!IsWidgetValid())
		return;

	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoViewForYUVV();
			//WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void URenderWithYUVWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%d"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void URenderWithYUVWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%d"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

#pragma endregion


#pragma region AgoraCallback - IVideoFrameObserver

bool URenderWithYUVWidget::FUserVideoFrameObserver::onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
{
	if (!IsWidgetValid())
		return false;

	WidgetPtr->RenderRawData(videoFrame);

	return true;
}

bool URenderWithYUVWidget::FUserVideoFrameObserver::onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
{
	return true;
}

bool URenderWithYUVWidget::FUserVideoFrameObserver::onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId)
{
	return true;
}

bool URenderWithYUVWidget::FUserVideoFrameObserver::onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame)
{
	return true;
}

bool URenderWithYUVWidget::FUserVideoFrameObserver::onTranscodedVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	return true;
}

agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE URenderWithYUVWidget::FUserVideoFrameObserver::getVideoFrameProcessMode()
{
	return agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE::PROCESS_MODE_READ_ONLY;
}

agora::media::base::VIDEO_PIXEL_FORMAT URenderWithYUVWidget::FUserVideoFrameObserver::getVideoFormatPreference()
{
	return agora::media::base::VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_I420;
}


#pragma endregion

