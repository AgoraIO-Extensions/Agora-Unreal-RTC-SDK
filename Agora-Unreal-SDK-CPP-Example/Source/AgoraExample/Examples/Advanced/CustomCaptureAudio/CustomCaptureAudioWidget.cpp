// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCaptureAudioWidget.h"


void UCustomCaptureAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetExternalAudioSource();

	JoinChannel();

	StartPushAudio();

	BackHomeBtn->OnClicked.AddDynamic(this, &UCustomCaptureAudioWidget::OnBackHomeButtonClick);
}

void UCustomCaptureAudioWidget::OnBackHomeButtonClick()
{
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
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}
void UCustomCaptureAudioWidget::SetExternalAudioSource()
{
	int ret = MediaEngine->setExternalAudioSource(true, SAMPLE_RATE, CHANNEL, 1);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UCustomCaptureAudioWidget::setExternalAudioSource ret: %d"), ret));
}


void UCustomCaptureAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

void UCustomCaptureAudioWidget::CheckAndroidPermission()
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

void UCustomCaptureAudioWidget::JoinChannel() {
	UE_LOG(LogTemp, Warning, TEXT("UCustomCaptureAudioWidget OnJoinButtonClick ======"));
	RtcEngineProxy->setAudioProfile(AUDIO_PROFILE_TYPE::AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);
}
void UCustomCaptureAudioWidget::StartPushAudio()
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Audio/Agora.io-Interactions.wav");  
	TArray<uint8> result;
	FFileHelper::LoadFileToArray(result, *LoadDir, 0);
	Runnable = new FAgoraCaptureRunnable(MediaEngine, result.GetData(), result.Num() * sizeof(uint8));
	FRunnableThread* RunnableThread = FRunnableThread::Create(Runnable, TEXT("Agora"));
}

#pragma region RtcEngineCallBack
void UCustomCaptureAudioWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UCustomCaptureAudioWidget::JoinChannelSuccess uid: %u"), uid));
	});
}

void UCustomCaptureAudioWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UCustomCaptureAudioWidget::onUserJoined uid: %u"), uid));
	});
}
#pragma endregion RtcEngineCallBack



void UCustomCaptureAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (Runnable!=nullptr)
	{
		Runnable->Exit();
		Runnable=nullptr;
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

FAgoraCaptureRunnable::FAgoraCaptureRunnable(agora::media::IMediaEngine* MediaEngine, const uint8* audioData, int dataLength)
{
	sendByte = nullptr;

	this->MediaEngine = MediaEngine;
	this->audioData = new uint8[dataLength];
	this->dataLength = dataLength;

	FMemory::Memcpy(this->audioData, audioData, dataLength * sizeof(uint8));
}

FAgoraCaptureRunnable::~FAgoraCaptureRunnable()
{

}

uint32 FAgoraCaptureRunnable::Run()
{
	auto tic = getTimeStamp();
	bStopThread = false;
	const uint8* Ptr = reinterpret_cast<const uint8*>(audioData);

	while (!bStopThread)
	{
		if (MediaEngine == nullptr)
		{
			break;
		}
		auto toc = getTimeStamp();
		if ((toc - tic) >= 10)
		{
			UE_LOG(LogTemp, Warning, TEXT("UCustomCaptureAudioWidget TimeStamp ====== %d"), toc - tic);

			if (dataLength != 0)
			{
				if (dataLength < 0)
				{
					OnCompleteDelegate.Broadcast();
					break;
				}
				if (sendByte==nullptr)
				{
					sendByte = FMemory::Malloc(SAMPLE_RATE / PUSH_FREQ_PER_SEC * agora::rtc::BYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE * CHANNEL);
				}
				FMemory::Memcpy(sendByte, Ptr, SAMPLE_RATE / PUSH_FREQ_PER_SEC * agora::rtc::BYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE * CHANNEL);
				agora::media::IAudioFrameObserverBase::AudioFrame externalAudioFrame;
				externalAudioFrame.bytesPerSample = agora::rtc::BYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE;
				externalAudioFrame.type = agora::media::IAudioFrameObserver::FRAME_TYPE_PCM16;
				externalAudioFrame.samplesPerChannel = SAMPLE_RATE / PUSH_FREQ_PER_SEC;
				externalAudioFrame.samplesPerSec = SAMPLE_RATE;
				externalAudioFrame.channels = CHANNEL;
				externalAudioFrame.buffer = (void*)sendByte;
				externalAudioFrame.renderTimeMs = 10;
				int ret = MediaEngine->pushAudioFrame(agora::media::AUDIO_PLAYOUT_SOURCE, &externalAudioFrame);
				//UE_LOG(LogTemp, Warning, TEXT("UCustomCaptureAudioWidget pushAudioFrame ====== %d"), ret);
				Ptr += SAMPLE_RATE / PUSH_FREQ_PER_SEC * 2 * CHANNEL;
				dataLength -= SAMPLE_RATE / PUSH_FREQ_PER_SEC * 2 * CHANNEL;
				tic = toc;
			}
		}
		FPlatformProcess::Sleep(0.001f);
	}

	return 0;
}

void FAgoraCaptureRunnable::Stop()
{
	sendByte = nullptr;

	bStopThread = true;

}

void FAgoraCaptureRunnable::Exit()
{
	sendByte = nullptr;

	bStopThread = true;

	FMemory::Free(sendByte);
}

std::time_t FAgoraCaptureRunnable::getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	std::time_t timestamp = tp.time_since_epoch().count();
	return timestamp;
}
#pragma endregion