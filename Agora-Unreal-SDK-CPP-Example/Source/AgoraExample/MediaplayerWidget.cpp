// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaplayerWidget.h"



void UMediaplayerWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID ,TOKEN ,CHANNEL_NAME);

	SetUpUIEvent();

	InitMediaPlayer();

	JoinChannelWithMPK();

	bURLOpen = true;
}

void UMediaplayerWidget::onVideoSizeChanged(VIDEO_SOURCE_TYPE sourceType, uid_t uid, int width, int height, int rotation)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("onVideoSizeChanged uid:%d ,width:%d ,height:%d"), uid, width, height));


		if (uid == 0)
		{
#if ENGINE_MAJOR_VERSION > 4
				UCanvasPanelSlot* imageSlot = dynamic_cast<UCanvasPanelSlot*>(remoteVideo->Slot.Get());
#else
				UCanvasPanelSlot* imageSlot = dynamic_cast<UCanvasPanelSlot*>(remoteVideo->Slot);
#endif
				imageSlot->SetSize(FVector2D(width, height));
		}

	});
}


void UMediaplayerWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;
	std::string APP_IDStr(TCHAR_TO_ANSI(*APP_ID));
	AppID = APP_IDStr;
	std::string TOKENStr(TCHAR_TO_ANSI(*TOKEN));
	Token = TOKENStr;
	std::string CHANNEL_NAMEStr(TCHAR_TO_ANSI(*CHANNEL_NAME));
	ChannelName = CHANNEL_NAMEStr;

	RtcEngineContext.appId = AppID.c_str();
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);
}

void UMediaplayerWidget::SetUpUIEvent() 
{
	PlayButton->OnClicked.AddDynamic(this, &UMediaplayerWidget::OnPlayButtonClick);
	StopButton->OnClicked.AddDynamic(this, &UMediaplayerWidget::OnStopButtonClick);
	PauseButton->OnClicked.AddDynamic(this, &UMediaplayerWidget::OnPauseButtonClick);
	ResumeButton->OnClicked.AddDynamic(this, &UMediaplayerWidget::OnResumeButtonClick);
	OpenButton->OnClicked.AddDynamic(this, &UMediaplayerWidget::OnOpenButtonClick);
	CheckBoxUrl->OnCheckStateChanged.AddDynamic(this, &UMediaplayerWidget::CheckBoxValueChange);
}

void UMediaplayerWidget::InitMediaPlayer()
{
	MediaPlayer = RtcEngineProxy->createMediaPlayer();
	if (MediaPlayer == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("CreateMediaPlayer failed!")));
		return;
	}
	handler = new MpkEventHandler(this);

	MediaPlayer->registerPlayerSourceObserver(handler);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("playerId id: %d"), MediaPlayer->getMediaPlayerId()));
}

void UMediaplayerWidget::JoinChannelWithMPK()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

	agora::rtc::ChannelMediaOptions options;
	options.autoSubscribeAudio = true;
	options.autoSubscribeVideo = true;
	options.publishMicrophoneTrack = false;
	options.publishCameraTrack = false;
	options.publishMediaPlayerAudioTrack = true;
	options.publishMediaPlayerVideoTrack = true;
	options.publishMediaPlayerId = MediaPlayer->getMediaPlayerId();
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	auto ret = RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), 0, options);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("RtcEngineController JoinChannel_MPK returns:  %d"), ret));
}

void UMediaplayerWidget::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
	FString pathfromName = UGameplayStatics::GetPlatformName();
	if (pathfromName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.CAMERA"));
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UMediaplayerWidget::CheckBoxValueChange(bool isOn)
{
	bURLOpen = isOn;

	UE_LOG(LogTemp, Warning, TEXT("TCheckBoxValueChange is %s"), (bURLOpen ? TEXT("true") : TEXT("false")));
}


void UMediaplayerWidget::OnPlayButtonClick()
{
	auto ret = MediaPlayer->play();
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("Play return %d"), ret));
}

void UMediaplayerWidget::OnStopButtonClick()
{
	auto ret = MediaPlayer->stop();
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("stop return %d"), ret));
}

void UMediaplayerWidget::OnPauseButtonClick()
{
	auto ret = MediaPlayer->pause();
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("Pause return %d"), ret));
}

void UMediaplayerWidget::OnResumeButtonClick()
{
	auto ret = MediaPlayer->resume();
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("Resume return %d"), ret));
}

void UMediaplayerWidget::OnOpenButtonClick()
{
	const char* path = nullptr;
	if (bURLOpen)
	{
		path = MPK_URL;
	}
	else
	{
		FString LoadDir = FPaths::ProjectContentDir() / TEXT("Movies/MPK.mp4");  //ÎÄ¼þÂ·¾¶

		path = TCHAR_TO_ANSI(*LoadDir);
	}
	auto ret = MediaPlayer->open(path, 0);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("Open return %d"), ret));
}


#pragma region MPKEventHandler

MpkEventHandler::MpkEventHandler(UMediaplayerWidget* MediaPlayer)
{
	this->MediaplayerWidget = MediaPlayer;
}

void MpkEventHandler::onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_ERROR ec)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("OnPlayerSourceStateChanged playId: %d"),MediaplayerWidget->MediaPlayer->getMediaPlayerId()));

		UE_LOG(LogTemp, Warning, TEXT("OnPlayerSourceStateChanged"));

		if (state == media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_OPEN_COMPLETED)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = MediaplayerWidget->remoteVideo;
			videoCanvas.uid = MediaplayerWidget->MediaPlayer->getMediaPlayerId();
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER;
			MediaplayerWidget->RtcEngineProxy->setupLocalVideo(videoCanvas);
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("Open Complete. Click start to play media")));
		}
		else if (state == media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_STOPPED)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = MediaplayerWidget->MediaPlayer->getMediaPlayerId();
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER;
			MediaplayerWidget->RtcEngineProxy->setupLocalVideo(videoCanvas);
			MediaplayerWidget->remoteVideo->SetBrush(MediaplayerWidget->EmptyBrush);
		}
	});
}

void MpkEventHandler::onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{

}

void MpkEventHandler::onPositionChanged(int64_t position_ms)
{
	
}

void MpkEventHandler::onMetaData(const void* data, int length)
{
	
}

void MpkEventHandler::onPlayBufferUpdated(int64_t playCachedBuffer)
{
	
}

void MpkEventHandler::onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event)
{
	
}

void MpkEventHandler::onCompleted()
{
	
}

void MpkEventHandler::onAgoraCDNTokenWillExpire()
{
	
}

void MpkEventHandler::onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to)
{
	
}

void MpkEventHandler::onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info)
{
	
}

void MpkEventHandler::onAudioVolumeIndication(int volume)
{
	
}

#pragma endregion MPKEventHandler


void UMediaplayerWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->destroyMediaPlayer(MediaPlayer);
		MediaPlayer.reset();
		if (handler != nullptr)
		{
			delete handler;
			handler = nullptr;
		}
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}
