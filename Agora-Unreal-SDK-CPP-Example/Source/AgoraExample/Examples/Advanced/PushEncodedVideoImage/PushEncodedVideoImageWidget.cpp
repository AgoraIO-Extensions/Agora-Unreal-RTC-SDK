// Copyright(c) 2024 Agora.io. All rights reserved.


#include "PushEncodedVideoImageWidget.h"

void UPushEncodedVideoImageWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	InitData();

	ShowUserGuide();

	JoinChannel();

	JoinChannel2();
}

void UPushEncodedVideoImageWidget::CheckPermission()
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

void UPushEncodedVideoImageWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

	AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	AgoraUERtcEngine::Get()->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);
	VideoObserver = MakeShareable(new FUserIVideoEncodedFrameObserver(this));
	int ret = MediaEngine->registerVideoEncodedFrameObserver(VideoObserver.Get());
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UPushEncodedVideoImageWidget::InitData()
{
	FString MachineCode = UBFL_UtilityTool::GenSimpleUIDPart_MachineCode();
	FString FuncCode = UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType::CAMERA);
	FString BaseUID = MachineCode + FuncCode;

	UID1 = FCString::Atoi(*(BaseUID + "1"));
	UID2 = FCString::Atoi(*(BaseUID + "2"));

	UBFL_Logger::Print(FString::Printf(TEXT(" >>>> UID Generation <<< ")), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID1:  %d"), UID1), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID2:  %d"), UID2), LogMsgViewPtr);
}

void UPushEncodedVideoImageWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [PushEncodedVideoImage]\n"
		"1. In this example, we send 1 H.264 frame's data to demo the usage of API PushEncodedVideoImage.\n"
		"2. We join channel twice: UID1 receives the encoded image, and UID2 handles the encoded image pushing job.\n"
		"3. It will launch a timer to send data continuously.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UPushEncodedVideoImageWidget::JoinChannel()
{
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	AgoraUERtcEngine::Get()->enableVideo();

	ChannelMediaOptions option;
	option.autoSubscribeVideo = true;
	option.autoSubscribeAudio = true;
	option.publishCameraTrack = true;
	option.publishMicrophoneTrack = true;
	option.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	option.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;


	RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UID1;

	int ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, option, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UPushEncodedVideoImageWidget::JoinChannel2()
{
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	AgoraUERtcEngine::Get()->enableVideo();


	SenderOptions SenderOptions;
	SenderOptions.codecType = VIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC;
	MediaEngine->setExternalVideoSource(true, true, agora::media::EXTERNAL_VIDEO_SOURCE_TYPE::ENCODED_VIDEO_FRAME, SenderOptions);


	/*
		If a client wants to add multiple connections to the same channel,
		then auto-subscribing to audio and video in just one connection is enough, [autoSubscribeAudio/autoSubscribeVideo]
		and set subscriptions to false for other connections.
	*/

	ChannelMediaOptions option;
	option.autoSubscribeVideo = false;
	option.autoSubscribeAudio = false;
	option.publishCustomAudioTrack = false;
	option.publishCameraTrack = false;
	option.publishCustomVideoTrack = false;
	option.publishEncodedVideoTrack = true;
	option.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	option.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UID2;

	int ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, option, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UPushEncodedVideoImageWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UPushEncodedVideoImageWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}

void UPushEncodedVideoImageWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

void UPushEncodedVideoImageWidget::StartPushEncodeVideoImage()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UPushEncodedVideoImageWidget::UpdateForPushEncodeVideoImage, 0.1f, true, 0.f);
}

void UPushEncodedVideoImageWidget::StopPushEncodeVideoImage()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
}

void UPushEncodedVideoImageWidget::UpdateForPushEncodeVideoImage()
{

	UE_LOG(LogTemp, Warning, TEXT("UpdateForPushEncodeVideoImage"));
	// you can send any data, not only video image.
	agora::rtc::EncodedVideoFrameInfo ValEncodedVideoFrameInfo;
	ValEncodedVideoFrameInfo.framesPerSecond = 10;
	ValEncodedVideoFrameInfo.codecType = VIDEO_CODEC_TYPE::VIDEO_CODEC_H264;
	ValEncodedVideoFrameInfo.frameType = VIDEO_FRAME_TYPE::VIDEO_FRAME_TYPE_KEY_FRAME;
	AgoraUERtcEngine::Get()->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);

	ValEncodedVideoFrameInfo.rotation = agora::rtc::VIDEO_ORIENTATION::VIDEO_ORIENTATION_0;
	ValEncodedVideoFrameInfo.streamType = agora::rtc::VIDEO_STREAM_HIGH;

	// hard-coded
	ValEncodedVideoFrameInfo.width = 800;
	ValEncodedVideoFrameInfo.height = 600;
	ValEncodedVideoFrameInfo.captureTimeMs = AgoraUERtcEngine::Get()->getCurrentMonotonicTimeInMs();


	//UTexture2D* Texture2D = NewObject<UTexture2D>(this,TEXT("EncodedData"));
	FString Path = FPaths::ProjectContentDir() / TEXT("Image/output_frame.h264");
	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *Path))
	{
		UBFL_Logger::PrintError(FString::Printf(TEXT("%s Failed To Load File"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	int ret = MediaEngine->pushEncodedVideoImage(FileData.GetData(), FileData.Num(), ValEncodedVideoFrameInfo);
	//int ret = MediaEngine->pushEncodedVideoImage(nullptr,0, ValEncodedVideoFrameInfo);
}



#pragma region UI Utility

int UPushEncodedVideoImageWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	/*
		For local view:
			please reference the callback function Ex.[onCaptureVideoFrame]

		For remote view:
			please reference the callback function [onRenderVideoFrame]

		channelId will be set in [setupLocalVideo] / [setupRemoteVideo]
	*/

	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{

		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);

		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}

	return ret;
}

int UPushEncodedVideoImageWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}
	return ret;
}

#pragma endregion


#pragma region AgoraCallback - IRtcEngineEventHandlerEx


void UPushEncodedVideoImageWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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


			if (connection.localUid == WidgetPtr->GetUID2()) {
				UBFL_Logger::Print(FString::Printf(TEXT("%s In [UID2]"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
				WidgetPtr->StartPushEncodeVideoImage();
			}
			else {
				UBFL_Logger::Print(FString::Printf(TEXT("%s  In [UID1]"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
				//WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			}

		});
}

void UPushEncodedVideoImageWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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



			if (connection.localUid == WidgetPtr->GetUID2())
			{
				WidgetPtr->StopPushEncodeVideoImage();
			}
			else
			{
				//WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			}

		});
}

void UPushEncodedVideoImageWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

	//if (remoteUid == WidgetPtr->GetUID1() || remoteUid == WidgetPtr->GetUID2())
	//	return;

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


			if(connection.localUid == WidgetPtr->GetUID1() && remoteUid == WidgetPtr->GetUID2()){
				
				// For UID1's connection to Remote UID2

				UBFL_Logger::Print(FString::Printf(TEXT("%s In [UID1] "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
			}


		});
}

void UPushEncodedVideoImageWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

	//if (remoteUid == WidgetPtr->GetUID1() || remoteUid == WidgetPtr->GetUID2())
	//	return;

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




			if (connection.localUid == WidgetPtr->GetUID1() && remoteUid == WidgetPtr->GetUID2()) {
				
				// For UID1's connection to Remote UID2

				WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
			}

		});
}


#pragma endregion


#pragma region AgoraCallback - IVideoEncodedFrameObserver

UPushEncodedVideoImageWidget::FUserIVideoEncodedFrameObserver::FUserIVideoEncodedFrameObserver(UPushEncodedVideoImageWidget* Widget)
{
	WidgetPtr = Widget;
}

UPushEncodedVideoImageWidget::FUserIVideoEncodedFrameObserver::~FUserIVideoEncodedFrameObserver()
{

}

bool UPushEncodedVideoImageWidget::FUserIVideoEncodedFrameObserver::onEncodedVideoFrameReceived(rtc::uid_t uid, const uint8_t* imageBuffer, size_t length, const rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo)
{
	if (!IsWidgetValid())
		return false;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (IsWidgetValid())
			{
				// filter out the type only you wanted.
				if (videoEncodedFrameInfo.codecType == VIDEO_CODEC_H264)
				{
					UBFL_Logger::Print(FString::Printf(TEXT("%s  uid=%u buffer length %d"), *FString(FUNCTION_MACRO), uid, length), WidgetPtr->GetLogMsgViewPtr());
				}

			}
		});

	return true;
}

#pragma endregion



