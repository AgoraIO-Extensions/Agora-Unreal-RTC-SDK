// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomRenderAudioWidget.h"

void UCustomRenderAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	JoinChannel();

	InitConfig();

	if (Runnable == nullptr)
	{
		Runnable = new FAgoraRenderRunnable(MediaEngine, AgoraSoundWaveProcedural);
		FRunnableThread* RunnableThread = FRunnableThread::Create(Runnable, TEXT("Agora"));
	}
}


void UCustomRenderAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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
}

void UCustomRenderAudioWidget::InitConfig()
{
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
void UCustomRenderAudioWidget::CheckAndroidPermission()
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

void UCustomRenderAudioWidget::JoinChannel() {
	UE_LOG(LogTemp, Warning, TEXT("UCustomRenderAudioWidget JoinChannel"));
	RtcEngineProxy->enableAudio();
	int ret = MediaEngine->setExternalAudioSink(true, SAMPLE_RATE, CHANNEL);
	UE_LOG(LogTemp, Warning, TEXT("UCustomRenderAudioWidget SetExternalAudioSink %d"), ret);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);
}


#pragma region RtcEngineCallBack
void UCustomRenderAudioWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UCustomRenderAudioWidget::JoinChannelSuccess uid: %u"), uid));
	});
}

void UCustomRenderAudioWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UCustomRenderAudioWidget::onUserJoined uid: %u"), uid));
	});
}
#pragma endregion RtcEngineCallBack



void UCustomRenderAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (Runnable != nullptr)
	{
		Runnable->Exit();
		Runnable = nullptr;
	}
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}


#pragma region AgoraThread

FAgoraRenderRunnable::FAgoraRenderRunnable(agora::media::IMediaEngine* MediaEngine, UAgoraSoundWaveProcedural* AgoraSoundWaveProcedural)
{
	sendByte = nullptr;

	this->MediaEngine = MediaEngine;
	this->AgoraSoundWaveProcedural = AgoraSoundWaveProcedural;
}

FAgoraRenderRunnable::~FAgoraRenderRunnable()
{

}

uint32 FAgoraRenderRunnable::Run()
{
	auto tic = getTimeStamp();
	bStopThread = false;

	agora::media::IAudioFrameObserverBase::AudioFrame externalAudioFrame;
	externalAudioFrame.bytesPerSample = agora::rtc::BYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE;
	externalAudioFrame.type = agora::media::IAudioFrameObserver::FRAME_TYPE_PCM16;
	externalAudioFrame.samplesPerChannel = SAMPLE_RATE / PUSH_FREQ_PER_SEC;
	externalAudioFrame.samplesPerSec = SAMPLE_RATE;
	externalAudioFrame.channels = CHANNEL;
	externalAudioFrame.buffer = FMemory::Malloc(SAMPLE_RATE / PUSH_FREQ_PER_SEC * agora::rtc::BYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE * CHANNEL);
	externalAudioFrame.renderTimeMs = 10;
	externalAudioFrame.avsync_type = 0;
	while (!bStopThread)
	{
		if (MediaEngine == nullptr)
		{
			break;
		}
		auto toc = getTimeStamp();
		if ((toc - tic) >= 10)
		{
			//UE_LOG(LogTemp, Warning, TEXT("UCustomCaptureAudioWidget TimeStamp ====== %d"), toc - tic);
			tic = getTimeStamp();
			auto ret = MediaEngine->pullAudioFrame(&externalAudioFrame);
			//UE_LOG(LogTemp, Warning, TEXT("UCustomRenderAudioWidget pullAudioFrame ====== %d"), ret);
			if (ret == 0)
			{
				AgoraSoundWaveProcedural->AddToFrames(externalAudioFrame);
			}
		}
		FPlatformProcess::Sleep(0.001f);
	}
	FMemory::Free(externalAudioFrame.buffer);
	return 0;
}

void FAgoraRenderRunnable::Stop()
{
	sendByte = nullptr;

	bStopThread = true;
}

void FAgoraRenderRunnable::Exit()
{
	sendByte = nullptr;

	bStopThread = true;
}

std::time_t FAgoraRenderRunnable::getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	std::time_t timestamp = tp.time_since_epoch().count();
	return timestamp;
}
#pragma endregion