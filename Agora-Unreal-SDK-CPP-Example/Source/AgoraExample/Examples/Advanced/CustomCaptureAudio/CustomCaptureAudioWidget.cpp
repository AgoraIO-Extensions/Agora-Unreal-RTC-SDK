// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCaptureAudioWidget.h"
#include <chrono>

void UCustomCaptureAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	SetExternalAudioSource();

	JoinChannel();

	StartPushAudio();
}


void UCustomCaptureAudioWidget::CheckPermission()
{
#if PLATFORM_ANDROID
	FString TargetPlatformName = UGameplayStatics::GetPlatformName();
	if (TargetPlatformName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UCustomCaptureAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandler = MakeShared<FUserRtcEventHandler>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandler.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

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

	RtcEngineProxy->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);
}

void UCustomCaptureAudioWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [CustomCaptureAudio]\n"
		"1. It will push the audio data to the remote side with the custom data you provide.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UCustomCaptureAudioWidget::SetExternalAudioSource()
{
	int ret = MediaEngine->setExternalAudioSource(true, SAMPLE_RATE, CHANNEL, 1);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UCustomCaptureAudioWidget::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UCustomCaptureAudioWidget::StartPushAudio()
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Audio/Agora.io-Interactions.wav");
	TArray<uint8> AudioData;
	FFileHelper::LoadFileToArray(AudioData, *LoadDir, 0);
	Runnable = new FAgoraCaptureRunnable(MediaEngine, AudioData.GetData(), AudioData.Num() * sizeof(uint8));
	FRunnableThread* RunnableThread = FRunnableThread::Create(Runnable, TEXT("AgoraUE-UserThread"));
}

void UCustomCaptureAudioWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UCustomCaptureAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();
}



void UCustomCaptureAudioWidget::UnInitAgoraEngine()
{
	if (Runnable != nullptr)
	{
		Runnable->Exit();
		Runnable = nullptr;
	}

	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandler.Get());
		agora::rtc::ue::releaseAgoraRtcEngine();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}



#pragma region AgoraCallback - IRtcEngineEventHandler

void UCustomCaptureAudioWidget::FUserRtcEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s uid=%u"), *FString(FUNCTION_MACRO), uid), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UCustomCaptureAudioWidget::FUserRtcEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

		});

}


void UCustomCaptureAudioWidget::FUserRtcEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s uid=%u"), *FString(FUNCTION_MACRO), uid), WidgetPtr->GetLogMsgViewPtr());

		});

}

void UCustomCaptureAudioWidget::FUserRtcEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s uid=%u"), *FString(FUNCTION_MACRO), uid), WidgetPtr->GetLogMsgViewPtr());

		});
}

#pragma endregion



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
				if (sendByte == nullptr)
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
				agora::rtc::track_id_t trackId = 0;
				int ret = MediaEngine->pushAudioFrame(&externalAudioFrame, trackId);
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


