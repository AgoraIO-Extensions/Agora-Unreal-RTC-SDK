// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceChangerWidget.h"


void UVoiceChangerWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	JoinChannel();
}


void UVoiceChangerWidget::CheckPermission()
{

}

void UVoiceChangerWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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


	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [VoiceChanger]\n"
		"1. Apply audio/voice effects during your phone call.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UVoiceChangerWidget::JoinChannel()
{
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_BROADCASTER);
	AgoraUERtcEngine::Get()->enableAudio();
	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

#pragma region  UI VoiceBeautifier

void UVoiceChangerWidget::OnBtn_ChatBeautifierClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setVoiceBeautifierPreset(CHAT_BEAUTIFIER_MAGNETIC);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_SingingBeautifierClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setVoiceBeautifierPreset(SINGING_BEAUTIFIER);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_TimbreTransformationClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setVoiceBeautifierPreset(TIMBRE_TRANSFORMATION_VIGOROUS);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_TurnOffVoiceBeautifierClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setVoiceBeautifierPreset(VOICE_BEAUTIFIER_OFF);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

#pragma endregion


#pragma region UI AudioEffect

void UVoiceChangerWidget::OnBtn_StyleTransformationClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setAudioEffectPreset(STYLE_TRANSFORMATION_POPULAR);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_RoomAcoustuicsClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setAudioEffectPreset(ROOM_ACOUSTICS_KTV);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_PitchClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setAudioEffectPreset(PITCH_CORRECTION);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_TurnOffAudioEffectClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setAudioEffectPreset(AUDIO_EFFECT_OFF);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

#pragma endregion


#pragma region UI VoiceConversion

void UVoiceChangerWidget::OnBtn_VoiceChangerClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setVoiceConversionPreset(VOICE_CHANGER_NEUTRAL);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UVoiceChangerWidget::OnBtn_TurnOffVoiceChangerClicked()
{
	AgoraUERtcEngine::Get()->setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY, AUDIO_SCENARIO_GAME_STREAMING);
	int ret = AgoraUERtcEngine::Get()->setVoiceConversionPreset(VOICE_CONVERSION_OFF);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

#pragma endregion


#pragma region UI CustomVocalEffects

void UVoiceChangerWidget::OnBtn_CustomVocalEffectsClicked()
{
	int ret = AgoraUERtcEngine::Get()->setLocalVoicePitch(0.5);
	UBFL_Logger::Print(FString::Printf(TEXT("%s SetLocalVoicePitch ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	ret = AgoraUERtcEngine::Get()->setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_31, -15);
	UBFL_Logger::Print(FString::Printf(TEXT("%s SetLocalVoiceEqualization ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	ret = AgoraUERtcEngine::Get()->setLocalVoiceReverb(AUDIO_REVERB_DRY_LEVEL, 10);
	UBFL_Logger::Print(FString::Printf(TEXT("%s SetLocalVoiceReverb AUDIO_REVERB_DRY_LEVEL  ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	ret = AgoraUERtcEngine::Get()->setLocalVoiceReverb(AUDIO_REVERB_WET_LEVEL, 7);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	UE_LOG(LogTemp, Warning, TEXT("%s SetLocalVoiceReverb AUDIO_REVERB_WET_LEVEL  %d"), *FString(__FUNCTION__), ret);

	ret = AgoraUERtcEngine::Get()->setLocalVoiceReverb(AUDIO_REVERB_ROOM_SIZE, 6);
	UBFL_Logger::Print(FString::Printf(TEXT("%s SetLocalVoiceReverb AUDIO_REVERB_ROOM_SIZE ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	ret = AgoraUERtcEngine::Get()->setLocalVoiceReverb(AUDIO_REVERB_WET_DELAY, 124);
	UBFL_Logger::Print(FString::Printf(TEXT("%s SetLocalVoiceReverb AUDIO_REVERB_WET_DELAY ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	ret = AgoraUERtcEngine::Get()->setLocalVoiceReverb(AUDIO_REVERB_STRENGTH, 78);
	UBFL_Logger::Print(FString::Printf(TEXT("%s SetLocalVoiceReverb AUDIO_REVERB_STRENGTH  ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

#pragma endregion



void UVoiceChangerWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UVoiceChangerWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}

void UVoiceChangerWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region AgoraCallback - IRtcEngineEventHandlerEx


void UVoiceChangerWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

void UVoiceChangerWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

void UVoiceChangerWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

		});
}

void UVoiceChangerWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

		});
}

#pragma endregion