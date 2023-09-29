// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenShareWhileVideoCallWidget.h"


void UScreenShareWhileVideoCallWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitUI();

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	InitData();

	ShowUserGuide();

	PrepareScreenShare();
	
	JoinChannel();
}


void UScreenShareWhileVideoCallWidget::InitUI()
{
	FString UniqueID = FString::FromInt(GetUniqueID());
	UID1_Camera = FCString::Atoi(*(UniqueID + "1"));
	UID2_Screen = FCString::Atoi(*(UniqueID + "2"));

#if PLATFORM_ANDROID || PLATFORM_IOS
	if (CBS_DisplayID)
		CBS_DisplayID->SetVisibility(ESlateVisibility::Collapsed);
#endif
}

void UScreenShareWhileVideoCallWidget::CheckPermission()
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


void UScreenShareWhileVideoCallWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(RtcEngineProxy->getVersion(&SDKBuild)), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UScreenShareWhileVideoCallWidget::InitData()
{
	FString MachineCode = UBFL_UtilityTool::GenSimpleUIDPart_MachineCode();
	FString FuncCode1 = UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType::CAMERA);
	FString FuncCode2 = UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType::SCREEN_SHARE);

	UID1_Camera = FCString::Atoi(*(MachineCode + FuncCode1 + "1"));
	UID2_Screen = FCString::Atoi(*(MachineCode + FuncCode2 + "2"));

	UBFL_Logger::Print(FString::Printf(TEXT(" >>>> UID Generation <<< ")), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID1_Camera:  %d"), UID1_Camera), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID2_Screen:  %d"), UID2_Screen), LogMsgViewPtr);
}

void UScreenShareWhileVideoCallWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [ScreenShareWhileVideoCall]\n"
		"1. Perform screen sharing and video call at the same time.\n"
		"2. For IOS, you need to check the screen share guide on Github.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UScreenShareWhileVideoCallWidget::PrepareScreenShare()
{
	CBS_DisplayID->ClearOptions();


#if PLATFORM_WINDOWS || PLATFORM_MAC
#if PLATFORM_WINDOWS
	SIZE size;
	size.cx = 360;
	size.cy = 240;
#endif
#if PLATFORM_MAC
	agora::rtc::SIZE size;
	size.width = 360;
	size.height = 240;
#endif

	infos = RtcEngineProxy->getScreenCaptureSources(size, size, true);

	if (infos == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetScreenDisplay is null"));
		return;
	}

	for (size_t i = 0; i < infos->getCount(); i++) {
		agora::rtc::ScreenCaptureSourceInfo info = infos->getSourceInfo(i);
		FString Displayid(UTF8_TO_TCHAR(info.sourceName));
		CBS_DisplayID->AddOption(Displayid);
	}

	if (infos != nullptr && infos->getCount() > 0)
	{
		CBS_DisplayID->SetSelectedIndex(0);
		SelectDisplayId = 0;
	}
#endif
}

void UScreenShareWhileVideoCallWidget::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);

	agora::rtc::ChannelMediaOptions ChannelMediaOptions;
	ChannelMediaOptions.autoSubscribeAudio = true;
	ChannelMediaOptions.autoSubscribeVideo = true;

	ChannelMediaOptions.publishCameraTrack = true;

#if PLATFORM_ANDROID || PLATFORM_IOS
	ChannelMediaOptions.publishScreenCaptureVideo = false;
	ChannelMediaOptions.publishScreenCaptureAudio = false;
#else
	ChannelMediaOptions.publishScreenTrack = false;
#endif

	ChannelMediaOptions.enableAudioRecordingOrPlayout = true;
	ChannelMediaOptions.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), UID1_Camera, ChannelMediaOptions);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}



void UScreenShareWhileVideoCallWidget::OnBtnStartScreenShare()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	ScreenCaptureParameters2 parameters2;
	parameters2.captureAudio = true;
	parameters2.captureVideo = true;
	auto ret = RtcEngineProxy->startScreenCapture(parameters2);
	UE_LOG(LogTemp, Warning, TEXT("StartScreenShrareClick JoinChannel ====== %d"), ret);
#else
	RtcEngineProxy->stopScreenCapture();
	agora::rtc::ScreenCaptureParameters capParam;
	VideoDimensions dimensions(640, 360);
	capParam.dimensions = dimensions;
	capParam.bitrate = 800;
	capParam.frameRate = 15;
	capParam.enableHighLight = false;
	capParam.windowFocus = false;
	capParam.captureMouseCursor = false;
	const agora::rtc::Rectangle regionRect;
#if PLATFORM_WINDOWS
	SIZE size;
	size.cx = 360;
	size.cy = 240;
#else
	agora::rtc::SIZE size;
	size.width = 360;
	size.height = 240;
#endif
	if (infos == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetScreenDisplay is null"));
		return;
	}
	agora::rtc::ScreenCaptureSourceInfo info = infos->getSourceInfo(SelectDisplayId);
	int ret = -1;
	if (info.type == agora::rtc::ScreenCaptureSourceType_Screen)
	{
		ret = RtcEngineProxy->startScreenCaptureByDisplayId((uint64)(info.sourceId), regionRect, capParam);
	}
	else if (info.type == agora::rtc::ScreenCaptureSourceType_Window)
	{
		ret = RtcEngineProxy->startScreenCaptureByWindowId(info.sourceId, regionRect, capParam);
	}
#endif

	JoinChannel_ScreenShare();
}

void UScreenShareWhileVideoCallWidget::JoinChannel_ScreenShare()
{
	agora::rtc::ChannelMediaOptions ValChannelMediaOptions;
	ValChannelMediaOptions.publishCameraTrack = false;

#if PLATFORM_ANDROID || PLATFORM_IOS
	ValChannelMediaOptions.publishScreenCaptureVideo = true;
	ValChannelMediaOptions.publishScreenCaptureAudio = true;
#else
	ValChannelMediaOptions.publishScreenTrack = true;
#endif

	ValChannelMediaOptions.autoSubscribeAudio = false;
	ValChannelMediaOptions.autoSubscribeVideo = false;
	ValChannelMediaOptions.enableAudioRecordingOrPlayout = false;
	ValChannelMediaOptions.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	agora::rtc::RtcConnection Connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	Connection.channelId = StdStrChannelName.c_str();
	Connection.localUid = UID2_Screen;
	int ret = RtcEngineProxy->joinChannelEx(TCHAR_TO_UTF8(*Token), Connection, ValChannelMediaOptions, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UScreenShareWhileVideoCallWidget::OnBtnStopScreenShare()
{
	agora::rtc::RtcConnection Connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	Connection.channelId = StdStrChannelName.c_str();
	Connection.localUid = UID2_Screen;
	int ret = RtcEngineProxy->leaveChannelEx(Connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UScreenShareWhileVideoCallWidget::OnCBSDisplayIDSelectedValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	UE_LOG(LogTemp, Warning, TEXT("Screen Callpture"));
	if (CBS_DisplayID != nullptr)
	{
		SelectDisplayId = CBS_DisplayID->FindOptionIndex(SelectedItem);
	}
}

void UScreenShareWhileVideoCallWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UScreenShareWhileVideoCallWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

	
}


void UScreenShareWhileVideoCallWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


#pragma region UI Utility

int UScreenShareWhileVideoCallWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UScreenShareWhileVideoCallWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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


void UScreenShareWhileVideoCallWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

			if (connection.localUid == WidgetPtr->GetUID_Camera())
				WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			else if (connection.localUid == WidgetPtr->GetUID_Screen())
				WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_SCREEN_PRIMARY);
		});
}

void UScreenShareWhileVideoCallWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

			if (connection.localUid == WidgetPtr->GetUID_Camera())
				WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			else if (connection.localUid == WidgetPtr->GetUID_Screen())
				WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_SCREEN_PRIMARY);
		});
}

void UScreenShareWhileVideoCallWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

			if (remoteUid != WidgetPtr->GetUID_Camera() && remoteUid != WidgetPtr->GetUID_Screen()) {

				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
			}
		
		});
}

void UScreenShareWhileVideoCallWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

			if (remoteUid != WidgetPtr->GetUID_Camera() && remoteUid != WidgetPtr->GetUID_Screen()){
				WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
			}
			
		});
}

#pragma endregion