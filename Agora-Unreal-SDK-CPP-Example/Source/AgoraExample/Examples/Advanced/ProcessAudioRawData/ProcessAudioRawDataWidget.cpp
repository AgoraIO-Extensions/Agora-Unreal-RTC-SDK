// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessAudioRawDataWidget.h"
#include "Components/AudioComponent.h"

void UProcessAudioRawDataWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitConfig();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

}


void UProcessAudioRawDataWidget::CheckPermission()
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


void UProcessAudioRawDataWidget::InitConfig()
{
	// AudioParam
	audioParams.channels = 2;
	audioParams.sample_rate = 44100;
	audioParams.mode = agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE;
	audioParams.samples_per_call = 1024;

	FirstRemoteUID = 0;

	if (AgoraSoundWaveProcedural == nullptr)
	{
		AgoraSoundWaveProcedural = NewObject<UAgoraSoundWaveProcedural>();

		AgoraSoundWaveProcedural->SetSampleRate(44100); // The Value should be CLIP_SAMPLES x PULL_FREQ_PER_SEC

		AgoraSoundWaveProcedural->NumChannels = 2;

		AgoraSoundWaveProcedural->AddToRoot();
	}
	if (AgoraSound == nullptr)
	{
		AgoraSound = UGameplayStatics::SpawnSound2D(this, AgoraSoundWaveProcedural);

		AgoraSound->Play();
	}
}


void UProcessAudioRawDataWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	RtcEngineProxy->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);
	UserAudioFrameObserver = MakeShared<FUserAudioFrameObserver>(this);
	MediaEngine->registerAudioFrameObserver(UserAudioFrameObserver.Get());
}

void UProcessAudioRawDataWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [ProcessAudioRawData]\n"
		"1. You can retrieve your raw audio data (in this case, the data would be your playback audio data) and handle it yourself.\n"
		"2. If you want to mute the original playback stream and play it independently, there are two methods:\n"
		"*  Set [adjustPlaybackSignalVolume] to 0 and Use [onPlaybackAudioFrameBeforeMixing]\n"
		"*  Please refer to the example [CustomRenderAudio]\n"
		"3. If you set [adjustPlaybackSignalVolume] to 0, the audio frames you receive from [onPlaybackAudioFrame] will also be muted."
		"4. This example only plays one remote user's audio stream; you can expand and manage it yourself."
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UProcessAudioRawDataWidget::OnBtnJoinChannelClicked()
{
	
	// Mute the playback volume of SDK (not UE).
	RtcEngineProxy->adjustPlaybackSignalVolume(0);

	RtcEngineProxy->enableAudio();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UProcessAudioRawDataWidget::OnBtnLeaveChannelClicked()
{
	int ret = RtcEngineProxy->leaveChannel();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UProcessAudioRawDataWidget::OnBtnStopUEAudioClicked()
{
	if (AgoraSound)
	{
		AgoraSound->Stop();
	}
}

void UProcessAudioRawDataWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UProcessAudioRawDataWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();
}



void UProcessAudioRawDataWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		if (MediaEngine != nullptr)
		{
			MediaEngine->registerAudioFrameObserver(nullptr);
		}
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		agora::rtc::ue::releaseAgoraRtcEngine();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

void UProcessAudioRawDataWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

		});
}

void UProcessAudioRawDataWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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
		});
}

void UProcessAudioRawDataWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

			WidgetPtr->SetFirstRemoteUID(remoteUid);

			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UProcessAudioRawDataWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

			WidgetPtr->ClearFirstRemoteUID(remoteUid);

			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

		});
}

#pragma endregion

#pragma region AgoraCallback - IAudioFrameObserver

bool UProcessAudioRawDataWidget::FUserAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, AudioFrame& audioFrame)
{
	if (!IsWidgetValid())
		return false;

	if(WidgetPtr->GetFirstRemoteUID() == uid){

		// We only record 1 remote user's audio stream. You could expand it.
		WidgetPtr->GetAgoraSoundWaveProcedural()->AddToFrames(audioFrame);
	
	}

	return true;
}

bool UProcessAudioRawDataWidget::FUserAudioFrameObserver::onRecordAudioFrame(const char* channelId, AudioFrame& audioFrame)
{
	if (!IsWidgetValid())
		return false;

	//WidgetPtr->GetAgoraSoundWaveProcedural()->AddToFrames(audioFrame);
	return true;
}

bool UProcessAudioRawDataWidget::FUserAudioFrameObserver::onPlaybackAudioFrame(const char* channelId, AudioFrame& audioFrame)
{
	if (!IsWidgetValid())
		return false;

	//WidgetPtr->GetAgoraSoundWaveProcedural()->AddToFrames(audioFrame);

	return true;
}

bool UProcessAudioRawDataWidget::FUserAudioFrameObserver::onMixedAudioFrame(const char* channelId, AudioFrame& audioFrame)
{
	return true;
}

bool UProcessAudioRawDataWidget::FUserAudioFrameObserver::onEarMonitoringAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

int UProcessAudioRawDataWidget::FUserAudioFrameObserver::getObservedAudioFramePosition()
{
	return (int)(AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_PLAYBACK |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_RECORD |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_BEFORE_MIXING |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_MIXED |
		AUDIO_FRAME_POSITION::AUDIO_FRAME_POSITION_EAR_MONITORING);
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::FUserAudioFrameObserver::getPlaybackAudioParams()
{
	if (!IsWidgetValid())
		return agora::media::IAudioFrameObserverBase::AudioParams();

	return WidgetPtr->GetAudioParams();
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::FUserAudioFrameObserver::getRecordAudioParams()
{
	if (!IsWidgetValid())
		return agora::media::IAudioFrameObserverBase::AudioParams();

	return WidgetPtr->GetAudioParams();
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::FUserAudioFrameObserver::getMixedAudioParams()
{
	if (!IsWidgetValid())
		return agora::media::IAudioFrameObserverBase::AudioParams();

	return WidgetPtr->GetAudioParams();
}

agora::media::IAudioFrameObserverBase::AudioParams UProcessAudioRawDataWidget::FUserAudioFrameObserver::getEarMonitoringAudioParams()
{
	if (!IsWidgetValid())
		return agora::media::IAudioFrameObserverBase::AudioParams();

	return WidgetPtr->GetAudioParams();
}


#pragma endregion
