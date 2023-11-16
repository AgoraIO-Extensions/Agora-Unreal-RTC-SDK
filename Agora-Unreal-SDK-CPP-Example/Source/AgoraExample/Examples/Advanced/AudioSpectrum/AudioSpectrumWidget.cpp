// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSpectrumWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UAudioSpectrumWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitUI();

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	InitAgoraMediaPlayer();

	JoinChannelWithMPK();
}

void UAudioSpectrumWidget::InitUI()
{
	ET_URL->SetText(FText::FromString(MPK_URL));
}

void UAudioSpectrumWidget::CheckPermission()
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

void UAudioSpectrumWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandler = MakeShared<FUserRtcEventHandler>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandler.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	RtcEngineContext.audioScenario = agora::rtc::AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	int SDKBuild = 0;
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UAudioSpectrumWidget::ShowUserGuide()
{
	FString Guide = ""
		"Case: [AudioSpectrum]\n"
		"1. If you don't enter a URL below, you will use the local file. Alternatively, you can enter a URL into the editable text.\n"
		"2. <Loop>: If checked, enable infinite playback loops.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);

}

void UAudioSpectrumWidget::InitAgoraMediaPlayer()
{
	MediaPlayer = RtcEngineProxy->createMediaPlayer();
	UserIMediaPlayerSourceObserver = MakeShared<FUserIMediaPlayerSourceObserver>(this);
	MediaPlayer->registerPlayerSourceObserver(UserIMediaPlayerSourceObserver.Get());
	UBFL_Logger::Print(FString::Printf(TEXT("%s PlayerID=%d"), *FString(FUNCTION_MACRO), MediaPlayer->getMediaPlayerId()), LogMsgViewPtr);

	UserAudioSpectrumObserver = MakeShared<FUserAudioSpectrumObserver>(this);
	MediaPlayer->registerMediaPlayerAudioSpectrumObserver(UserAudioSpectrumObserver.Get(), 16);
}

void UAudioSpectrumWidget::JoinChannelWithMPK()
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


void UAudioSpectrumWidget::UpdateSpectrumData(const agora::media::AudioSpectrumData& data)
{
	FScopeLock Lock(&CriticalSectionForAudioSpectrumDataRW);
	AudioSpectrumData.Empty();
	for (int i = 0; i < data.dataLength; i++) {
		AudioSpectrumData.Add(data.audioSpectrumData[i]);
	}
}

void UAudioSpectrumWidget::VisualizeSpectrumData()
{
	// Be Called In Every Frame

	FScopeLock Lock(&CriticalSectionForAudioSpectrumDataRW);
	FString StrData = "";
	// CanvasPanel_Spectrum->ClearChildren(); They will be cleared at the end of the case
	FVector2D StartPosition(50, 100);
	std::function<void(UObject*)> DeSpawnFunc = [](UObject* Object) {
		//UImage* Image = Cast<UImage>(Object);
		//if (Image) {
		//	Image->SetVisibility(ESlateVisibility::Collapsed);
		//}
		};
	FAgoraUserObjectPool::GetInstance()->ReturnAllObject(DeSpawnFunc);
	for (float Item : AudioSpectrumData) {
		//StrData += FString::Printf(TEXT("%.2f"), Item) + TEXT("");

		// process the height // Original [-300,1]
		float Height = 2 - Item;
		StartPosition.X += 150;

		std::function<UObject* ()>SpawnFunc = []() {
			return (UObject*)NewObject<UImage>();
			};

		std::function<void(UObject*)> InitObjectFunc = [](UObject* Object) {
			//UImage* Image = Cast<UImage>(Object);
			//if (Image) {
			//	Image->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			//}
			};

		UImage* Image = Cast<UImage>(FAgoraUserObjectPool::GetInstance()->GetObject(SpawnFunc, InitObjectFunc));
		if (!CanvasPanel_Spectrum->HasChild(Image))
			CanvasPanel_Spectrum->AddChild(Image);

		UCanvasPanelSlot* ImageCanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Image);
		FVector2D OriginalSize = ImageCanvasPanelSlot->GetSize(); // Currently, default would be (100,30) 

		ImageCanvasPanelSlot->SetPosition(StartPosition);
		ImageCanvasPanelSlot->SetSize(FVector2D(OriginalSize.X, Height));

	}
	//UBFL_Logger::Print(FString::Printf(TEXT("%s [Tick] Spectrum Data : %s"), *FString(FUNCTION_MACRO), *StrData), LogMsgViewPtr);
	AudioSpectrumData.Empty();
}

//void UAudioSpectrumWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	Super::NativeTick(MyGeometry, InDeltaTime);	
//
//	VisualizeSpectrumData();
//}


void UAudioSpectrumWidget::OnBtnBackToHomeClicked()
{
	std::function<void(UObject*)> DestroyOneObjectFunc = [](UObject* Object) {
		UImage* Image = Cast<UImage>(Object);
		if (Image) {
			Image->RemoveFromParent();
		}
		};
	FAgoraUserObjectPool::ReleaseInstance(DestroyOneObjectFunc);
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UAudioSpectrumWidget::OnBtnOpenClicked()
{
	const char* path = nullptr;
	std::string StdStrPath = "";
	if (CB_URL->IsChecked())
	{
		StdStrPath = TCHAR_TO_UTF8(*(ET_URL->GetText().ToString()));
		path = StdStrPath.c_str();
	}
	else
	{
		FString ValPath = FPaths::ProjectContentDir() / TEXT("Movies/MPK.mp4");


#if PLATFORM_ANDROID || PLATFORM_IOS
		UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *ValPath), LogMsgViewPtr);

		FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.mp4");
		ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
		UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
		UBFL_UtilityTool::CreateMediaFileWithSource(ValPath, ValSavedFilePath);
		ValPath = ValSavedFilePath;
#endif 
		StdStrPath = TCHAR_TO_UTF8(*ValPath);
		path = StdStrPath.c_str();
	}

	auto ret = MediaPlayer->open(path, 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UAudioSpectrumWidget::OnBtnPlayClicked()
{
	if (CB_Loop->CheckedState == ECheckBoxState::Checked) {
		MediaPlayer->setLoopCount(-1);
	}
	else
	{
		MediaPlayer->setLoopCount(0);
	}
	auto ret = MediaPlayer->play();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioSpectrumWidget::OnBtnStopClicked()
{
	auto ret = MediaPlayer->stop();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioSpectrumWidget::OnBtnPauseClicked()
{
	auto ret = MediaPlayer->pause();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioSpectrumWidget::OnBtnResumeClicked()
{
	auto ret = MediaPlayer->resume();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioSpectrumWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}


void UAudioSpectrumWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		if (MediaPlayer)
		{
			MediaPlayer->stop();
			MediaPlayer->unregisterPlayerSourceObserver(UserIMediaPlayerSourceObserver.Get());
		}

		RtcEngineProxy->destroyMediaPlayer(MediaPlayer);

		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandler.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region UI Utility

int UAudioSpectrumWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UAudioSpectrumWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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


#pragma region AgoraCallback - IRtcEngineEventHandler

void UAudioSpectrumWidget::FUserRtcEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) {

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
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			// WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);

		});
}


void UAudioSpectrumWidget::FUserRtcEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			//WidgetPtr->MakeVideoView(uid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE);
		});
}

void UAudioSpectrumWidget::FUserRtcEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			WidgetPtr->ReleaseVideoView(uid, VIDEO_SOURCE_REMOTE);
		});
}

void UAudioSpectrumWidget::FUserRtcEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}
#pragma endregion


#pragma region AgoraCallback - IMediaPlayerSourceObserver

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_ERROR ec)
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
			else if (state == media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_PLAYBACK_ALL_LOOPS_COMPLETED)
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s Play Completed! "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			}
		});
}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPositionChanged(int64_t position_ms)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onCompleted()
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info)
{

}

void UAudioSpectrumWidget::FUserIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{

}


#pragma endregion


#pragma region AgoraCallback - IAudioSpectrumObserver

bool UAudioSpectrumWidget::FUserAudioSpectrumObserver::onLocalAudioSpectrum(const agora::media::AudioSpectrumData& data)
{
	if (!IsWidgetValid())
		return false;

	WidgetPtr->UpdateSpectrumData(data);

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

			WidgetPtr->VisualizeSpectrumData();
		});

	return true;
}

bool UAudioSpectrumWidget::FUserAudioSpectrumObserver::onRemoteAudioSpectrum(const agora::media::UserAudioSpectrumInfo* spectrums, unsigned int spectrumNumber)
{

	if (!IsWidgetValid())
		return false;


	return true;
}


#pragma endregion
