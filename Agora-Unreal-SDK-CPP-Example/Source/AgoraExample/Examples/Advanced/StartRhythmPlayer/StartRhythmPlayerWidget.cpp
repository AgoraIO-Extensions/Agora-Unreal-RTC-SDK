// Fill out your copyright notice in the Description page of Project Settings.


#include "StartRhythmPlayerWidget.h"


void UStartRhythmPlayerWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	JoinChannel();
}

void UStartRhythmPlayerWidget::CheckPermission()
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

void UStartRhythmPlayerWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

void UStartRhythmPlayerWidget::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}



void UStartRhythmPlayerWidget::OnBtnStartClicked()
{
	FString PathSound1 = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Audio"), TEXT("ding.mp3"));
	FString PathSound2 = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Audio"), TEXT("dong.mp3"));


	if (FPaths::FileExists(PathSound1) && FPaths::FileExists(PathSound2)) {
		UBFL_Logger::Print(FString::Printf(TEXT("%s File1 Exists Path=%s"), *FString(FUNCTION_MACRO), *PathSound1), LogMsgViewPtr);
		UBFL_Logger::Print(FString::Printf(TEXT("%s File2 Exists Path=%s"), *FString(FUNCTION_MACRO), *PathSound2), LogMsgViewPtr);
	}
	else {
		UBFL_Logger::PrintError(FString::Printf(TEXT("%s File1 May Not Exist Path=%s"), *FString(FUNCTION_MACRO), *PathSound1), LogMsgViewPtr);
		UBFL_Logger::PrintError(FString::Printf(TEXT("%s File2 May Not Exist Path=%s"), *FString(FUNCTION_MACRO), *PathSound2), LogMsgViewPtr);
	}


#if PLATFORM_ANDROID || PLATFORM_IOS
	
	UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *PathSound1), LogMsgViewPtr);
	FString ValSavedFilePath1 = FPaths::ProjectSavedDir() / TEXT("Ding.mp3");
	ValSavedFilePath1 = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath1, false);
	UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath1), LogMsgViewPtr);
	UBFL_UtilityTool::CreateMediaFileWithSource(PathSound1, ValSavedFilePath1);
	PathSound1 = ValSavedFilePath1;


	UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *PathSound2), LogMsgViewPtr);
	FString ValSavedFilePath2 = FPaths::ProjectSavedDir() / TEXT("Dong.mp3");
	ValSavedFilePath2 = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath2, false);
	UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath2), LogMsgViewPtr);
	UBFL_UtilityTool::CreateMediaFileWithSource(PathSound2, ValSavedFilePath2);
	PathSound2 = ValSavedFilePath2;

#endif

	AgoraRhythmPlayerConfig Config;
	Config.beatsPerMeasure = 4;
	Config.beatsPerMinute = 120;
	int ret = RtcEngineProxy->startRhythmPlayer(TCHAR_TO_UTF8(*PathSound1), TCHAR_TO_UTF8(*PathSound2), Config);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UStartRhythmPlayerWidget::OnBtnStopClicked()
{
	int ret = RtcEngineProxy->stopRhythmPlayer();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UStartRhythmPlayerWidget::OnBtnChangeConfigClicked()
{
	AgoraRhythmPlayerConfig Config;
	Config.beatsPerMeasure = 6;
	Config.beatsPerMinute = 60;
	int ret = RtcEngineProxy->configRhythmPlayer(Config);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s Beat Config is from 4 to 6 "), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UStartRhythmPlayerWidget::OnBtnPublishClicked()
{
	ChannelMediaOptions Options;
	Options.publishRhythmPlayerTrack = true;
	int ret = RtcEngineProxy->updateChannelMediaOptions(Options);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UStartRhythmPlayerWidget::OnBtnUnPublishClicked()
{
	ChannelMediaOptions Options;
	Options.publishRhythmPlayerTrack = false;
	int ret = RtcEngineProxy->updateChannelMediaOptions(Options);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}



void UStartRhythmPlayerWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UStartRhythmPlayerWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();
}



void UStartRhythmPlayerWidget::UnInitAgoraEngine()
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

int UStartRhythmPlayerWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UStartRhythmPlayerWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

void UStartRhythmPlayerWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

			//WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UStartRhythmPlayerWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

			//WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UStartRhythmPlayerWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

			//WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UStartRhythmPlayerWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

			//WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UStartRhythmPlayerWidget::FUserRtcEventHandlerEx::onRhythmPlayerStateChanged(RHYTHM_PLAYER_STATE_TYPE state, RHYTHM_PLAYER_ERROR_TYPE errorCode)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s state=%d errorcode=%d"), *FString(FUNCTION_MACRO), (int)state,(int)errorCode), WidgetPtr->GetLogMsgViewPtr());
		});
}

#pragma endregion