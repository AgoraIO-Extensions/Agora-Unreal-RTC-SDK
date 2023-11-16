// Fill out your copyright notice in the Description page of Project Settings.


#include "DualCameraWidget.h"

void UDualCameraWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	InitData();

	ShowUserGuide();

	GetVideoDeviceManager();
}


void UDualCameraWidget::InitData()
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

void UDualCameraWidget::CheckPermission()
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

void UDualCameraWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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
}


void UDualCameraWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [DualCamera]\n"
		"1. Android is not fully supported at the moment, so there may be unexpected problems.\n"
		"2. iPhone is only supported on iPhone XR or newer. iOS version 13.0 or later is supported.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UDualCameraWidget::GetVideoDeviceManager()
{

#if PLATFORM_ANDROID || PLATFORM_IOS
	MainCameraConfig.cameraDirection = CAMERA_FRONT;
	SecondCameraConfig.cameraDirection = CAMERA_REAR;
#else
	// Windows || Mac

	agora::rtc::IVideoDeviceManager* VideoDeviceManager = nullptr;
	RtcEngineProxy->queryInterface(AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);
	IVideoDeviceCollection* VideoDeviceInfos = VideoDeviceManager->enumerateVideoDevices();

	if (VideoDeviceInfos->getCount() >= 1) {
		char deviceId[512] = { 0 };
		char deviceName[512] = { 0 };
		// Get camera information
		VideoDeviceInfos->getDevice(0, deviceName, deviceId);
		FMemory::Memcpy(MainCameraConfig.deviceId, deviceId, 512);
	}

	if (VideoDeviceInfos->getCount() >= 2) {
		char deviceId[512] = { 0 };
		char deviceName[512] = { 0 };
		// Get camera information
		VideoDeviceInfos->getDevice(1, deviceName, deviceId);
		FMemory::Memcpy(SecondCameraConfig.deviceId, deviceId, 512);
	}

#endif


}


void UDualCameraWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UDualCameraWidget::OnBtn_MainCameraJoinClicked()
{
	RtcEngineProxy->startPreview();
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);


	int ret = RtcEngineProxy->startCameraCapture(VIDEO_SOURCE_CAMERA_PRIMARY, MainCameraConfig);
	UBFL_Logger::Print(FString::Printf(TEXT("%s startCameraCapture ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	agora::rtc::ChannelMediaOptions options1;
	options1.publishCameraTrack = true;
	options1.autoSubscribeAudio = true;
	options1.autoSubscribeVideo = true;
#if PLATFORM_ANDROID || PLATFORM_IOS
	options1.publishScreenCaptureVideo = false;
	options1.publishScreenCaptureAudio = false;
#else
	options1.publishScreenTrack = false;
#endif
	options1.enableAudioRecordingOrPlayout = true;
	options1.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID1);
	int ret2 = RtcEngineProxy->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, options1, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s joinChannel ret %d"), *FString(FUNCTION_MACRO), ret2), LogMsgViewPtr);
}

void UDualCameraWidget::OnBtn_MainCameraLeaveClicked()
{
	RtcEngineProxy->stopCameraCapture(VIDEO_SOURCE_CAMERA_PRIMARY);
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID1);
	int ret = RtcEngineProxy->leaveChannelEx(connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s leaveChannel ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UDualCameraWidget::OnBtn_SecondCameraJoinClicked()
{
#if PLATFORM_IOS
	// iPhone is only support in iPhone XR or better. iOS version is support in 13.0 or better
	CameraCapturerConfiguration CameraCaptureConfig;
	CameraCaptureConfig.cameraDirection = CAMERA_DIRECTION::CAMERA_REAR;
	int ret0 = RtcEngineProxy->enableMultiCamera(true, CameraCaptureConfig);
	UBFL_Logger::Print(FString::Printf(TEXT("%s enableMultiCamera ret0 %d"), *FString(FUNCTION_MACRO), ret0), LogMsgViewPtr);
#endif 


	int ret = RtcEngineProxy->startCameraCapture(VIDEO_SOURCE_CAMERA_SECONDARY, SecondCameraConfig);
	UBFL_Logger::Print(FString::Printf(TEXT("%s startCameraCapture ret1 %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	agora::rtc::ChannelMediaOptions options2;
	/*
		If a client wants to add multiple connections to the same channel,
		then auto-subscribing to audio and video in just one connection is enough, [autoSubscribeAudio/autoSubscribeVideo]
		and set subscriptions to false for other connections.
	*/
	options2.autoSubscribeAudio = false;
	options2.autoSubscribeVideo = false;
	options2.publishCustomAudioTrack = false;
	options2.publishCameraTrack = false;
	options2.publishSecondaryCameraTrack = true;
	options2.enableAudioRecordingOrPlayout = false;
	options2.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID2);
	int ret2 = RtcEngineProxy->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, options2, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s joinChannelEx ret2 %d"), *FString(FUNCTION_MACRO), ret2), LogMsgViewPtr);
}

void UDualCameraWidget::OnBtn_SecondCameraLeaveClicked()
{
	RtcEngineProxy->stopCameraCapture(VIDEO_SOURCE_CAMERA_SECONDARY);
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID2);
	int ret = RtcEngineProxy->leaveChannelEx(connection);
	UE_LOG(LogTemp, Warning, TEXT(" UDualCameraWidget::OnBtn_SecondCameraLeaveClicked  ret: %u"), ret);
}

void UDualCameraWidget::OnBtn_PublishMainCameraClicked()
{
	agora::rtc::ChannelMediaOptions options1;
	options1.publishCameraTrack = true;
	options1.publishMicrophoneTrack = true;
	RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UID1;
	int ret = RtcEngineProxy->updateChannelMediaOptionsEx(options1, connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UDualCameraWidget::OnBtn_UnPublishMainCamClicked()
{
	agora::rtc::ChannelMediaOptions options1;
	options1.publishCameraTrack = false;
	options1.publishMicrophoneTrack = false;
	RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UID1;
	int ret = RtcEngineProxy->updateChannelMediaOptionsEx(options1, connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UDualCameraWidget::OnBtn_PublishSecondCamClicked()
{
	agora::rtc::ChannelMediaOptions options2;
	options2.publishSecondaryCameraTrack = true;

	RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UID2;
	int ret = RtcEngineProxy->updateChannelMediaOptionsEx(options2, connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UDualCameraWidget::OnBtn_UnPublishSecondCamClicked()
{
	agora::rtc::ChannelMediaOptions options2;
	options2.publishSecondaryCameraTrack = false;

	RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UID2;
	int ret = RtcEngineProxy->updateChannelMediaOptionsEx(options2, connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UDualCameraWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}

void UDualCameraWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->leaveChannelEx(RtcConnection(TCHAR_TO_UTF8(*ChannelName), UID2));
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region UI Utility

int UDualCameraWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UDualCameraWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

void UDualCameraWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if AGORA_CPP_VER_20_OR_LATER
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid == WidgetPtr->GetUID1())
				WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			else if (connection.localUid == WidgetPtr->GetUID2())
				WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_SECONDARY);
		});
}

void UDualCameraWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	if (!IsWidgetValid())
		return;

#if AGORA_CPP_VER_20_OR_LATER
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid == WidgetPtr->GetUID1())
				WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			else if (connection.localUid == WidgetPtr->GetUID2())
				WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_SECONDARY);
		});
}

void UDualCameraWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if AGORA_CPP_VER_20_OR_LATER
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid != WidgetPtr->GetUID1() && connection.localUid != WidgetPtr->GetUID2())
				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UDualCameraWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

#if AGORA_CPP_VER_20_OR_LATER
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid != WidgetPtr->GetUID1() && connection.localUid != WidgetPtr->GetUID2())
				WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

#pragma endregion



