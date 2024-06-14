// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinMultipleChannelsWidget.h"


void UJoinMultipleChannelsWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	InitData();

	ShowUserGuide();

	JoinChannel1();

	JoinChannel2();
}


void UJoinMultipleChannelsWidget::CheckPermission()
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

void UJoinMultipleChannelsWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName1 = CHANNEL_NAME;
	ChannelName2 = CHANNEL_NAME + "2";

	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UJoinMultipleChannelsWidget::InitData()
{
	FString MachineCode = UBFL_UtilityTool::GenSimpleUIDPart_MachineCode();
	FString FuncCode = UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType::CAMERA);
	FString BaseUID = MachineCode + FuncCode;

	UIDChannel1 = FCString::Atoi(*(BaseUID + "1"));
	UIDChannel2 = FCString::Atoi(*(BaseUID + "2"));

	UBFL_Logger::Print(FString::Printf(TEXT(" >>>> UID Generation <<< ")), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID1:  %d"), UIDChannel1), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID2:  %d"), UIDChannel2), LogMsgViewPtr);
}

void UJoinMultipleChannelsWidget::ShowUserGuide()
{
	FString Guide = ""
		"Case: [JoinMultiChannels]\n"
		"1. You will join 2 channels: [YourChannelName] with UID [UIDChannel1] and [YourChannelName2] with UID [UIDChannel2].\n"
		"2. By default, [YourChannelName] would be CLIENT_ROLE_AUDIENCE and [YourChannelName2] would be CLIENT_ROLE_BROADCASTER.\n"
		"3. There can only be 1 CLIENT_ROLE_BROADCASTER for 1 channel at a time.If you need multiple broadcasters, that should be handled on the server side.\n"
		"4. If someone joins the channel with the same CHANNEL_NAME and the same UID, it will kick off the previous user for now.\n"
		"5. You can switch the broadcaster by clicking buttons. Note: You need to stop publishing first.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UJoinMultipleChannelsWidget::JoinChannel1()
{
	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->enableVideo();

	agora::rtc::ChannelMediaOptions ChannelMediaOptions;
	ChannelMediaOptions.autoSubscribeAudio = true;
	ChannelMediaOptions.autoSubscribeVideo = true;

	ChannelMediaOptions.publishCameraTrack = true;

	ChannelMediaOptions.enableAudioRecordingOrPlayout = true;
	ChannelMediaOptions.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_AUDIENCE;

	agora::rtc::RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName1);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UIDChannel1;

	int ret = AgoraUERtcEngine::Get()->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, ChannelMediaOptions, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ChannelName=%s ret %d"), *FString(FUNCTION_MACRO), *ChannelName1, ret), LogMsgViewPtr);
}


void UJoinMultipleChannelsWidget::JoinChannel2()
{
	agora::rtc::ChannelMediaOptions ChannelMediaOptions;
	ChannelMediaOptions.autoSubscribeAudio = true;
	ChannelMediaOptions.autoSubscribeVideo = true;

	ChannelMediaOptions.publishCameraTrack = true;

	ChannelMediaOptions.enableAudioRecordingOrPlayout = true;
	ChannelMediaOptions.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	agora::rtc::RtcConnection connection;
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName2);
	connection.channelId = StdStrChannelName.c_str();
	connection.localUid = UIDChannel2;

	int ret = AgoraUERtcEngine::Get()->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, ChannelMediaOptions, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ChannelName=%s ret %d"), *FString(FUNCTION_MACRO), *ChannelName2, ret), LogMsgViewPtr);
}

void UJoinMultipleChannelsWidget::OnBtnPublishChannel1()
{
	// Notice, here the order is important.
	// You need to unpublish and free your camera first.
	// Otherwise, the camera will be occupied by the first channel.

	agora::rtc::ChannelMediaOptions Options2;
	Options2.publishCameraTrack = false;
	Options2.publishMicrophoneTrack = false;
	Options2.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_AUDIENCE;

	agora::rtc::RtcConnection Connection2;
	std::string StdStrChannelName2 = TCHAR_TO_UTF8(*ChannelName2);
	Connection2.channelId = StdStrChannelName2.c_str();
	Connection2.localUid = UIDChannel2;

	int ret2 = AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(Options2, Connection2);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ChannelName=%s ret %d"), *FString(FUNCTION_MACRO), *ChannelName2, ret2), LogMsgViewPtr);


	agora::rtc::ChannelMediaOptions Options1;
	Options1.publishCameraTrack = true;
	Options1.publishMicrophoneTrack = true;
	Options1.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	agora::rtc::RtcConnection Connection1;
	std::string StdStrChannelName1 = TCHAR_TO_UTF8(*ChannelName1);
	Connection1.channelId = StdStrChannelName1.c_str();
	Connection1.localUid = UIDChannel1;

	int ret1 = AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(Options1, Connection1);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ChannelName=%s ret %d"), *FString(FUNCTION_MACRO), *ChannelName1, ret1), LogMsgViewPtr);
}

void UJoinMultipleChannelsWidget::OnBtnPublishChannel2()
{
	// Unpublish First
	agora::rtc::ChannelMediaOptions Options1;
	Options1.publishCameraTrack = false;
	Options1.publishMicrophoneTrack = false;
	Options1.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_AUDIENCE;

	agora::rtc::RtcConnection Connection1;
	std::string StdStrChannelName1 = TCHAR_TO_UTF8(*ChannelName1);
	Connection1.channelId = StdStrChannelName1.c_str();
	Connection1.localUid = UIDChannel1;

	int ret1 = AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(Options1, Connection1);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ChannelName=%s ret %d"), *FString(FUNCTION_MACRO), *ChannelName1, ret1), LogMsgViewPtr);


	agora::rtc::ChannelMediaOptions Options2;
	Options2.publishCameraTrack = true;
	Options2.publishMicrophoneTrack = true;
	Options2.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	agora::rtc::RtcConnection Connection2;
	std::string StdStrChannelName2 = TCHAR_TO_UTF8(*ChannelName2);
	Connection2.channelId = StdStrChannelName2.c_str();
	Connection2.localUid = UIDChannel2;

	int ret2 = AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(Options2, Connection2);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ChannelName=%s ret %d"), *FString(FUNCTION_MACRO), *ChannelName2, ret2), LogMsgViewPtr);

}


void UJoinMultipleChannelsWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}



void UJoinMultipleChannelsWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}



void UJoinMultipleChannelsWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


#pragma region UI Utility

int UJoinMultipleChannelsWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UJoinMultipleChannelsWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

void UJoinMultipleChannelsWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

			WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UJoinMultipleChannelsWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

			WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UJoinMultipleChannelsWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s localuid = %d remote uid=%u"), *FString(FUNCTION_MACRO), connection.localUid, remoteUid), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid == WidgetPtr->GetUID1())
				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName1());

			else if (connection.localUid == WidgetPtr->GetUID2())
				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName2());
		});
}

void UJoinMultipleChannelsWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s localuid = %d remote uid=%u"), *FString(FUNCTION_MACRO), connection.localUid, remoteUid), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid == WidgetPtr->GetUID1())
				WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName1());

			else if (connection.localUid == WidgetPtr->GetUID2())
				WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName2());
		});
}

#pragma endregion


