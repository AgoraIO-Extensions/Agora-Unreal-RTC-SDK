// Copyright(c) 2024 Agora.io. All rights reserved.


#include "SpatialAudioWithMPWidget.h"


void USpatialAudioWithMPWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	InitData();

	ShowUserGuide();

	InitAgoraMediaPlayer();

	InitAgoraSpatialAudioEngine();

	JoinChannel();

	//We use the mpk to simulate the voice of remote users.
	JoinChannelWithMPK();
}

void USpatialAudioWithMPWidget::CheckPermission()
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


void USpatialAudioWithMPWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	//If you use a Bluetooth headset, you need to set AUDIO_SCENARIO_TYPE to AUDIO_SCENARIO_GAME_STREAMING.
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void USpatialAudioWithMPWidget::InitData()
{
	FString MachineCode = UBFL_UtilityTool::GenSimpleUIDPart_MachineCode();
	FString FuncCode1 = UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType::CAMERA);
	FString FuncCode2 = UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType::MPK);

	UID = FCString::Atoi(*(MachineCode + FuncCode1 + "1"));
	UID_UsedInMPK = FCString::Atoi(*(MachineCode + FuncCode2 + "2"));

	UBFL_Logger::Print(FString::Printf(TEXT(" >>>> UID Generation <<< ")), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID Camera:  %d"), UID), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("UID MPK:  %d"), UID_UsedInMPK), LogMsgViewPtr);
}

void USpatialAudioWithMPWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [SpatialAudio]\n"
		"1. Play spatial audio using the audio data from your local mpk (media player kit).\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void USpatialAudioWithMPWidget::InitAgoraMediaPlayer()
{
	MediaPlayer = AgoraUERtcEngine::Get()->createMediaPlayer();
	MediaPlayerSourceObserverWarpper = MakeShared<FUserIMediaPlayerSourceObserver>(this);
	int ret = MediaPlayer->registerPlayerSourceObserver(MediaPlayerSourceObserverWarpper.Get());
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void USpatialAudioWithMPWidget::InitAgoraSpatialAudioEngine()
{
	if (LocalSpatialAudioEngine == nullptr)
	{
		AgoraUERtcEngine::Get()->queryInterface(AGORA_IID_LOCAL_SPATIAL_AUDIO, (void**)&LocalSpatialAudioEngine);
	}

	if (LocalSpatialAudioEngine != nullptr)
	{
		LocalSpatialAudioConfig AudioConfig;

		AudioConfig.rtcEngine = AgoraUERtcEngine::Get();

		auto ret = LocalSpatialAudioEngine->initialize(AudioConfig);

		UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

		LocalSpatialAudioEngine->setAudioRecvRange(30);
	}
}


void USpatialAudioWithMPWidget::JoinChannel()
{
	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->enableVideo();
	AgoraUERtcEngine::Get()->enableSpatialAudio(true);
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_BROADCASTER);

	agora::rtc::ChannelMediaOptions ChannelMediaOptions;
	ChannelMediaOptions.autoSubscribeAudio = true;
	ChannelMediaOptions.autoSubscribeVideo = true;

	ChannelMediaOptions.publishCameraTrack = true;
	ChannelMediaOptions.publishMicrophoneTrack = false;
	ChannelMediaOptions.enableAudioRecordingOrPlayout = true;
	ChannelMediaOptions.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID);
	int ret = AgoraUERtcEngine::Get()->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, ChannelMediaOptions, nullptr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void USpatialAudioWithMPWidget::JoinChannelWithMPK()
{
	int playerId = MediaPlayer->getMediaPlayerId();

	/*
		If a client wants to add multiple connections to the same channel,
		then auto-subscribing to audio and video in just one connection is enough, [autoSubscribeAudio/autoSubscribeVideo]
		and set subscriptions to false for other connections.
	*/

	agora::rtc::ChannelMediaOptions ChannelMediaOptions;
	ChannelMediaOptions.autoSubscribeAudio = false;
	ChannelMediaOptions.autoSubscribeVideo = false;
	ChannelMediaOptions.publishCameraTrack = false;
	ChannelMediaOptions.publishMediaPlayerAudioTrack = true;
	ChannelMediaOptions.publishMediaPlayerVideoTrack = true;
	ChannelMediaOptions.publishMediaPlayerId = playerId;
	ChannelMediaOptions.enableAudioRecordingOrPlayout = false;
	ChannelMediaOptions.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID_UsedInMPK);
	int ret = AgoraUERtcEngine::Get()->joinChannelEx(TCHAR_TO_UTF8(*Token), connection, ChannelMediaOptions, nullptr);
	AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(ChannelMediaOptions, connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s joinChannelEx ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void USpatialAudioWithMPWidget::OnBtnLeftClicked()
{
	RemoteVoicePositionInfo remoteVoicePos{ { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID);
	int ret = LocalSpatialAudioEngine->updateRemotePositionEx(UID_UsedInMPK, remoteVoicePos, connection);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void USpatialAudioWithMPWidget::OnBtnPlayClicked()
{
	if (MediaPlayer)
	{
		int ret = MediaPlayer->open(TCHAR_TO_UTF8(*MPL_URL), 0);
		MediaPlayer->adjustPlayoutVolume(0);
		UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	}
}

void USpatialAudioWithMPWidget::OnBtnRightClicked()
{
	RemoteVoicePositionInfo remoteVoicePos{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };

	std::string StdStrChannelName = TCHAR_TO_UTF8(*ChannelName);
	agora::rtc::RtcConnection connection(StdStrChannelName.c_str(), UID);
	int ret = LocalSpatialAudioEngine->updateRemotePositionEx(UID_UsedInMPK, remoteVoicePos, connection);

	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void USpatialAudioWithMPWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void USpatialAudioWithMPWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}

void USpatialAudioWithMPWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		if (MediaPlayer)
		{
			MediaPlayer->stop();
			MediaPlayer->unregisterPlayerSourceObserver(MediaPlayerSourceObserverWarpper.Get());
		}

		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region UI Utility


int USpatialAudioWithMPWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int USpatialAudioWithMPWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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


void USpatialAudioWithMPWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s local uid=%u"), *FString(FUNCTION_MACRO), connection.localUid), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid == WidgetPtr->GetUID_Camrea()) {
				WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			}

			float localUserPosition[3] = { 0.0f, 0.0f, 0.0f };
			float forward[3] = { 1.0f, 0.0f, 0.0f };
			float right[3] = { 0.0f, 1.0f, 0.0f };
			float up[3] = { 0.0f, 0.0f, 1.0f };

			int ret = WidgetPtr->GetLocalSpatialAudioEngine()->updateSelfPositionEx(localUserPosition, forward, right, up, connection);
			UBFL_Logger::Print(FString::Printf(TEXT("%s updateSelfPositionEx ret %d"), *FString(FUNCTION_MACRO), ret), WidgetPtr->GetLogMsgViewPtr());
		});
}

void USpatialAudioWithMPWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s local uid=%u"), *FString(FUNCTION_MACRO), connection.localUid), WidgetPtr->GetLogMsgViewPtr());

			if (connection.localUid == WidgetPtr->GetUID_Camrea()) {
				WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
			}

		});
}

void USpatialAudioWithMPWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

			if (remoteUid != WidgetPtr->GetUID_Camrea() && remoteUid != WidgetPtr->GetUID_UsedInMPK()) {
				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
			}

		});
}

void USpatialAudioWithMPWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

			if (remoteUid != WidgetPtr->GetUID_Camrea() && remoteUid != WidgetPtr->GetUID_UsedInMPK()) {
				WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
			}
		});
}

#pragma endregion


#pragma region  AgoraCallback - IMediaPlayerSourceObserver

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_REASON reason)
{
	if (state != media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_OPEN_COMPLETED)
		return;

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


			auto TmpMediaPlayer = WidgetPtr->GetMediaPlayer();

			// VIDEO_SOURCE_MEDIA_PLAYER 
			int ret = TmpMediaPlayer->play();
			UBFL_Logger::Print(FString::Printf(TEXT("%s MediaPlayer Play ret %d"), *FString(FUNCTION_MACRO), ret), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(TmpMediaPlayer->getMediaPlayerId(), agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER, WidgetPtr->GetChannelName());

		});
}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPositionChanged(int64_t positionMs, int64_t timestampMs)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onCompleted()
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info)
{

}

void USpatialAudioWithMPWidget::FUserIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{

}
#pragma endregion


