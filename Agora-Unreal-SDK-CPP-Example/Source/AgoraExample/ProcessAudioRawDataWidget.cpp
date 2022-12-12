// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessAudioRawDataWidget.h"


void UProcessAudioRawDataWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	InitConfig();

	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();
}


void UProcessAudioRawDataWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	RtcEngineContext.appId = TCHAR_TO_ANSI(*APP_ID);
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;


	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	RtcEngineProxy->initialize(RtcEngineContext);

	RtcEngineProxy->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);

	MediaEngine->registerAudioFrameObserver(this);

	//RtcEngineProxy->setPlaybackAudioFrameParameters(SAMPLE_RATE, 1, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE, 1024);
}

void UProcessAudioRawDataWidget::InitConfig()
{
	audioParams.channels = 2;
	audioParams.sample_rate = 48000;
	audioParams.mode = agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE;
	audioParams.samples_per_call = 960;

	if (AgoraSoundWaveProcedural == nullptr)
	{
		AgoraSoundWaveProcedural = NewObject<UAgoraSoundWaveProcedural>();

		AgoraSoundWaveProcedural->SetSampleRate(SAMPLE_RATE);

		AgoraSoundWaveProcedural->NumChannels = CHANNEL;

		AgoraSoundWaveProcedural->AddToRoot();
	}
	if (AgoraSound == nullptr)
	{
		AgoraSound = UGameplayStatics::SpawnSound2D(this, AgoraSoundWaveProcedural);

		AgoraSound->Play();
	}
}

void UProcessAudioRawDataWidget::SetUpUIEvent()
{
	JoinBtn->OnClicked.AddDynamic(this, &UProcessAudioRawDataWidget::OnJoinButtonClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UProcessAudioRawDataWidget::OnLeaveButtonClick);
}


void UProcessAudioRawDataWidget::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
	FString pathfromName = UGameplayStatics::GetPlatformName();
	if (pathfromName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UProcessAudioRawDataWidget::OnJoinButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UProcessAudioRawDataWidget OnJoinButtonClick ======"));

	SetButtonClickAble(false);

	RtcEngineProxy->enableAudio();

	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

}

void UProcessAudioRawDataWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UProcessAudioRawDataWidget OnLeaveButtonClick ======"));
	SetButtonClickAble(true);
	RtcEngineProxy->leaveChannel();
}



#pragma region RtcEngineCallBack

void UProcessAudioRawDataWidget::onJoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UProcessAudioRawDataWidget::JoinChannelSuccess uid: %u"), connection.localUid));
	});
}

void UProcessAudioRawDataWidget::onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UProcessAudioRawDataWidget::onUserJoined uid: %u"), remoteUid));
	});
}


bool UProcessAudioRawDataWidget::onPlaybackAudioFrameBeforeMixing(const char* channelId, rtc::uid_t uid, AudioFrame& audioFrame)
{
	return true;
}


bool UProcessAudioRawDataWidget::onRecordAudioFrame(const char* channelId, AudioFrame& audioFrame)
{
	return true;
}


bool UProcessAudioRawDataWidget::onPlaybackAudioFrame(const char* channelId, AudioFrame& audioFrame)
{
	AgoraSoundWaveProcedural->AddToFrames(audioFrame);

	FMemory::Memset(audioFrame.buffer, 0 ,audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels);
	
	return false;
}

bool UProcessAudioRawDataWidget::onMixedAudioFrame(const char* channelId, AudioFrame& audioFrame)
{
	return true;
}

bool UProcessAudioRawDataWidget::onEarMonitoringAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::getEarMonitoringAudioParams()
{
	return this->audioParams;
}

int UProcessAudioRawDataWidget::getObservedAudioFramePosition()
{
	return (int)(AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_PLAYBACK |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_RECORD |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_BEFORE_MIXING |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_MIXED);
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::getPlaybackAudioParams()
{
	return this->audioParams;
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::getRecordAudioParams()
{
	return this->audioParams;
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::getMixedAudioParams()
{
	return this->audioParams;
}
bool agora::media::IAudioFrameObserverBase::onEarMonitoringAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

#pragma endregion RtcEngineCallBack

void UProcessAudioRawDataWidget::SetButtonClickAble(bool enable) {
	JoinBtn->SetIsEnabled(enable);
	LeaveBtn->SetIsEnabled(!enable);
}

void UProcessAudioRawDataWidget::NativeDestruct() {
	Super::NativeDestruct();

	if (RtcEngineProxy != nullptr)
	{
		if (MediaEngine!=nullptr)
		{
			MediaEngine->registerAudioFrameObserver(nullptr);
		}
		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}


