// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaPlayerWithCustomDataWidget.h"

void UMediaPlayerWithCustomDataWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	InitAgoraMediaPlayer();

	JoinChannelWithMPK();
}

void UMediaPlayerWithCustomDataWidget::CheckPermission()
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

void UMediaPlayerWithCustomDataWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	RtcEngineContext.audioScenario = agora::rtc::AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING;

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


void UMediaPlayerWithCustomDataWidget::ShowUserGuide()
{
	FString Guide = ""
		"Case: [MediaPlayerWithCustomData]\n"
		"1. You could use media player using the custom data you provide.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UMediaPlayerWithCustomDataWidget::InitAgoraMediaPlayer()
{
	MediaPlayer = RtcEngineProxy->createMediaPlayer();
	UserIMediaPlayerSourceObserver = MakeShared<FUserIMediaPlayerSourceObserver>(this);
	MediaPlayer->registerPlayerSourceObserver(UserIMediaPlayerSourceObserver.Get());
	UBFL_Logger::Print(FString::Printf(TEXT("%s PlayerID=%d"), *FString(FUNCTION_MACRO), MediaPlayer->getMediaPlayerId()), LogMsgViewPtr);
}

void UMediaPlayerWithCustomDataWidget::JoinChannelWithMPK()
{

	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);

	ChannelMediaOptions Options;
	Options.autoSubscribeAudio = true;
	Options.autoSubscribeVideo = true;
	Options.publishCustomAudioTrack = false;
	Options.publishCameraTrack = false;
	Options.publishMediaPlayerAudioTrack = true;
	Options.publishMediaPlayerVideoTrack = true;
	Options.publishMediaPlayerId = MediaPlayer->getMediaPlayerId();
	Options.enableAudioRecordingOrPlayout = true;
	Options.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), 0, Options);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UMediaPlayerWithCustomDataWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UMediaPlayerWithCustomDataWidget::OnBtnOpenClicked()
{
	UserIMediaPlayerCustomDataProvider = MakeShared<FUserIMediaPlayerCustomDataProvider>();
	FString Path = FPaths::ProjectContentDir() / TEXT("Movies/MPK.mp4");

#if PLATFORM_ANDROID || PLATFORM_IOS
	FString ValPath = Path;
	UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *ValPath), LogMsgViewPtr);

	FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.mp4");
	ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
	UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
	UBFL_UtilityTool::CreateMediaFileWithSource(ValPath, ValSavedFilePath);
	Path = ValSavedFilePath;
#endif

	UserIMediaPlayerCustomDataProvider->Init(Path);

	agora::media::base::MediaSource source;
	source.provider = UserIMediaPlayerCustomDataProvider.Get();
	source.autoPlay = false;

	auto ret = MediaPlayer->openWithMediaSource(source);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UMediaPlayerWithCustomDataWidget::OnBtnPlayClicked()
{
	auto ret = MediaPlayer->play();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMediaPlayerWithCustomDataWidget::OnBtnStopClicked()
{
	auto ret = MediaPlayer->stop();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMediaPlayerWithCustomDataWidget::OnBtnPauseClicked()
{
	auto ret = MediaPlayer->pause();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMediaPlayerWithCustomDataWidget::OnBtnResumeClicked()
{
	auto ret = MediaPlayer->resume();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMediaPlayerWithCustomDataWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}


void UMediaPlayerWithCustomDataWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		if (UserIMediaPlayerCustomDataProvider != nullptr)
			UserIMediaPlayerCustomDataProvider->Release();

		if (MediaPlayer)
			MediaPlayer->stop();

		RtcEngineProxy->destroyMediaPlayer(MediaPlayer);

		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		agora::rtc::ue::releaseAgoraRtcEngine();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region UI Utility

int UMediaPlayerWithCustomDataWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UMediaPlayerWithCustomDataWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

void UMediaPlayerWithCustomDataWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

			//WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UMediaPlayerWithCustomDataWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

			//WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UMediaPlayerWithCustomDataWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

void UMediaPlayerWithCustomDataWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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


#pragma region AgoraCallback - IMediaPlayerSourceObserver

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_REASON reason)
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			if (state == media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_OPEN_COMPLETED)
			{
				int id = WidgetPtr->GetMediaPlayer()->getMediaPlayerId();
				WidgetPtr->MakeVideoView(id, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER, "");
			}
			else if (state == media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_STOPPED)
			{
				int id = WidgetPtr->GetMediaPlayer()->getMediaPlayerId();
				WidgetPtr->ReleaseVideoView(id, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER, "");
			}
		});
}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPositionChanged(int64_t positionMs, int64_t timestampMs)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onCompleted()
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info)
{

}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{

}


#pragma endregion

#pragma region AgoraCallback - IMediaPlayerCustomDataProvider

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerCustomDataProvider::Init(FString Path)
{
	// Check File Exists

	DataFile = fopen(TCHAR_TO_UTF8(*Path), "rb");
	FileSize = 0;

	if (DataFile)
	{
		fseek(DataFile, 0L, SEEK_END);
		// calculating the size of the file
		FileSize = ftell(DataFile);
		fseek(DataFile, 0L, SEEK_SET);
	}
	else
	{
#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s  File Not Exist "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			});
		return;
	}

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s  File Open "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
		});
}

void UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerCustomDataProvider::Release()
{
	if (DataFile) {
		fclose(DataFile);
		FileSize = 0;
	}
#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
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
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s  File Closed "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
		});
}

int UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerCustomDataProvider::onReadData(unsigned char* buffer, int bufferSize)
{
	if (!DataFile) {
		return -1;
	}

	// Read data into buffer
	size_t ReadCount = fread(buffer, 1, bufferSize, DataFile);
	return ReadCount;
}

int64_t UMediaPlayerWithCustomDataWidget::FUserIMediaPlayerCustomDataProvider::onSeek(int64_t offset, int whence)
{
	if (!DataFile) {
		return -1;
	}

	if (whence == 0) {
		fseek(DataFile, offset, SEEK_SET);
		return offset;
	}
	else if (whence == 65536)
	{
		return FileSize;
	}
	return -1;
}

#pragma endregion



