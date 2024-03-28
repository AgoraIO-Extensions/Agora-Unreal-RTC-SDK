// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomRenderAudioWidget.h"
#include <string>

void UCustomRenderAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	JoinChannel();

	InitConfig();

	if (Runnable == nullptr)
	{
		Runnable = new FAgoraRenderRunnable(MediaEngine, AgoraSoundWaveProcedural);
		FRunnableThread* RunnableThread = FRunnableThread::Create(Runnable, TEXT("AgoraUE-UserThread"));
	}
}


void UCustomRenderAudioWidget::CheckPermission()
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

void UCustomRenderAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

void UCustomRenderAudioWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [CustomRenderAudio]\n"
		"[Limitation on IOS]\n"
		"You may not be able to hear sounds. This is because UE may not consider cooperating with third-party audio systems in this case.\n"
		"UE and SDK would compete for the ADM (audio device module). Please refer to the code [IOSAppDelegate.cpp]. \n"
		"If we are not in [Playback] or [RecordActive] status, the AVAudioSessionCategory won't be set to [AVAudioSessionCategoryPlayAndRecord].\n"
		"The temporary solution you could check the comment in the [JoinChannel] method. We would provide a better solution in the future.\n"
		"1. It will pull the audio data from the remote side and then play it using your own tools (e.g., UE audio Tools).\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UCustomRenderAudioWidget::JoinChannel()
{
	RtcEngineProxy->enableAudio();


#if PLATFORM_IOS

	// UE and SDK would compete for the ADM.

	// [Tmp Solution]
	// It would disable SDK's ADM, therefore, it would disable the functionality of Recording and Playout.
	// You could get the sample effect with ChannelMediaOptions.enableAudioRecordingOrPlayout to false
	// int ret00 = RtcEngineProxy->enableLocalAudio(false);

	// [Solution]
	int ret00 = RtcEngineProxy->setParameters("{\"che.audio.keep.audiosession\": true}");
	UBFL_Logger::Print(FString::Printf(TEXT("%s setParameters ret %d"), *FString(FUNCTION_MACRO), ret00), LogMsgViewPtr);

#endif

	int ret0 = MediaEngine->setExternalAudioSink(true, SAMPLE_RATE, CHANNEL);
	UBFL_Logger::Print(FString::Printf(TEXT("%s setExternalAudioSink ret %d"), *FString(FUNCTION_MACRO), ret0), LogMsgViewPtr);

	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s joinChannel ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
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

void UCustomRenderAudioWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UCustomRenderAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}



void UCustomRenderAudioWidget::UnInitAgoraEngine()
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

void UCustomRenderAudioWidget::FUserRtcEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
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

void UCustomRenderAudioWidget::FUserRtcEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
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


void UCustomRenderAudioWidget::FUserRtcEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
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

void UCustomRenderAudioWidget::FUserRtcEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

void UCustomRenderAudioWidget::FUserRtcEventHandler::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
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

			for (unsigned int i = 0; i < speakerNumber; i++)
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s uid:%u,vad:%d,voicepatch:%d,volume %d,totalvolume:%d"), *FString(FUNCTION_MACRO), speakers[i].uid, speakers[i].vad, speakers[i].voicePitch, speakers[i].volume, totalVolume), WidgetPtr->GetLogMsgViewPtr());
			}

		});

}


#pragma endregion


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
				// [To retrieve iOS audio data]	IOS playback failed, but the data is normal. Customers can modify it by themselves
				//#if PLATFORM_IOS
				//                NSString* path = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
				//                std::string temp =std::string([path UTF8String]);
				//                std::string output = temp +std::string("/CustomAudiodata.pcm");
				//                FILE* file = fopen(output.c_str(),"ab+");
				//                fwrite(externalAudioFrame.buffer, 1, externalAudioFrame.bytesPerSample * externalAudioFrame.samplesPerChannel * externalAudioFrame.channels, file);
				//                fclose(file);
				//#endif
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
