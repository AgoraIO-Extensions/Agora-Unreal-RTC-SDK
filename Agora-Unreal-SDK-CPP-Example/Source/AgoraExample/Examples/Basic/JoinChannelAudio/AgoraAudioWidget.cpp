// Copyright(c) 2024 Agora.io. All rights reserved.


#include "AgoraAudioWidget.h"


void UAgoraAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitUI();

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

}


void UAgoraAudioWidget::InitUI()
{
	Txt_PlaybackSignalVolume->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Slider_PlaybackSignalVolume->GetValue()))));
	Txt_RecordingSignalVolume->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Slider_RecordingSignalVolume->GetValue()))));
}

void UAgoraAudioWidget::CheckPermission()
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


void UAgoraAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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


	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [BasicAudioScene]\n"
		"1. This is a basic audio scene.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UAgoraAudioWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandler.Get());
		AgoraUERtcEngine::Release();
		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

void UAgoraAudioWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UAgoraAudioWidget::OnBtnStartEchoTestClicked()
{
	agora::rtc::EchoTestConfiguration Config;
	Config.intervalInSeconds = 10;
	int ret = AgoraUERtcEngine::Get()->startEchoTest(Config);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnBtnStopEchoTestClicked()
{
	int ret = AgoraUERtcEngine::Get()->stopEchoTest();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnBtnJoinChannelClicked()
{
	AgoraUERtcEngine::Get()->enableAudio();
	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	AgoraUERtcEngine::Get()->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnBtnLeaveChannelClicked()
{
	int ret = AgoraUERtcEngine::Get()->leaveChannel();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnBtnStartPublishClicked()
{
	ChannelMediaOptions options;
	options.publishMicrophoneTrack = true;
	int ret = AgoraUERtcEngine::Get()->updateChannelMediaOptions(options);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnBtnStopPublishClicked()
{
	ChannelMediaOptions options;
	options.publishMicrophoneTrack = false;
	int ret = AgoraUERtcEngine::Get()->updateChannelMediaOptions(options);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnSliderPlaybackSignalVolumeValChanged(float val)
{
	Txt_PlaybackSignalVolume->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(val))));
	int ret = AgoraUERtcEngine::Get()->adjustPlaybackSignalVolume(val);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnSliderRecordingSignalVolumeValChanged(float val)
{
	Txt_RecordingSignalVolume->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(val))));
	int ret = AgoraUERtcEngine::Get()->adjustRecordingSignalVolume(val);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnBtnEnableAudioIndicationClicked()
{
	int ret = AgoraUERtcEngine::Get()->enableAudioVolumeIndication(200, 3, false);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnCBSAudioProfileSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	agora::rtc::AUDIO_PROFILE_TYPE audioProfile = AUDIO_PROFILE_DEFAULT;
	FString SelectedOption = SelectedItem;

	if (SelectedOption == "AUDIO_PROFILE_DEFAULT")
		audioProfile = AUDIO_PROFILE_DEFAULT;
	else if (SelectedOption == "AUDIO_PROFILE_SPEECH_STANDARD")
		audioProfile = AUDIO_PROFILE_SPEECH_STANDARD;
	else if (SelectedOption == "AUDIO_PROFILE_MUSIC_STANDARD")
		audioProfile = AUDIO_PROFILE_MUSIC_STANDARD;
	else if (SelectedOption == "AUDIO_PROFILE_MUSIC_STANDARD_STEREO")
		audioProfile = AUDIO_PROFILE_MUSIC_STANDARD_STEREO;
	else if (SelectedOption == "AUDIO_PROFILE_MUSIC_HIGH_QUALITY")
		audioProfile = AUDIO_PROFILE_MUSIC_HIGH_QUALITY;
	else if (SelectedOption == "AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO")
		audioProfile = AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO;
	else if (SelectedOption == "AUDIO_PROFILE_IOT")
		audioProfile = AUDIO_PROFILE_IOT;

	int ret = AgoraUERtcEngine::Get()->setAudioProfile(audioProfile);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d AudioProfile=%s"), *FString(FUNCTION_MACRO), ret, *SelectedOption), LogMsgViewPtr);
}

void UAgoraAudioWidget::OnCBSAudioSenarioSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	agora::rtc::AUDIO_SCENARIO_TYPE scenario = AUDIO_SCENARIO_DEFAULT;
	FString SelectedOption = SelectedItem;

	if (SelectedOption == "AUDIO_SCENARIO_DEFAULT")
		scenario = AUDIO_SCENARIO_DEFAULT;
	else if (SelectedOption == "AUDIO_SCENARIO_GAME_STREAMING")
		scenario = AUDIO_SCENARIO_GAME_STREAMING;
	else if (SelectedOption == "AUDIO_SCENARIO_CHATROOM")
		scenario = AUDIO_SCENARIO_CHATROOM;
	else if (SelectedOption == "AUDIO_SCENARIO_CHORUS")
		scenario = AUDIO_SCENARIO_CHORUS;
	else if (SelectedOption == "AUDIO_SCENARIO_MEETING")
		scenario = AUDIO_SCENARIO_MEETING;

	int ret = AgoraUERtcEngine::Get()->setAudioScenario(scenario);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d  AudioScenario=%s"), *FString(FUNCTION_MACRO), ret, *SelectedOption), LogMsgViewPtr);
}

void UAgoraAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}



#pragma region AgoraCallback - IRtcEngineEventHandler

void UAgoraAudioWidget::FUserRtcEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
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

void UAgoraAudioWidget::FUserRtcEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
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


void UAgoraAudioWidget::FUserRtcEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
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

void UAgoraAudioWidget::FUserRtcEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

void UAgoraAudioWidget::FUserRtcEventHandler::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
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
				UBFL_Logger::Print(FString::Printf(TEXT("%s uid:%u,vad:%u,voicepatch:%f,volume %u,totalvolume:%d"), *FString(FUNCTION_MACRO), speakers[i].uid, speakers[i].vad, speakers[i].voicePitch, speakers[i].volume, totalVolume), WidgetPtr->GetLogMsgViewPtr());
			}

		});

}


#pragma endregion
