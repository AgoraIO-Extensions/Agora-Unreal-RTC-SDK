// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioMixingWidget.h"
#include "Misc/Paths.h"

void UAudioMixingWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	JoinChannel();
}

void UAudioMixingWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	int SDKBuild = 0;
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UAudioMixingWidget::ShowUserGuide()
{
	FString Guide = ""
		"Case: [AudioMixing]\n"
		"1. If you don't enter a URL below, you will use the local file. Alternatively, you can enter an audio file URL into the editable text.\n"
		"2. <LocalOnly>: If checked, only the local user can hear the audio mixing.\n"
		"3. <Loop>: If checked, enable infinite playback loops.\n"
		"4. For the version 4.2.1 audio-only SDK, it will utilize the system's simple player, which may come with certain limitations. Therefore, it is recommended to use a url of a wav file instead.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UAudioMixingWidget::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UAudioMixingWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UAudioMixingWidget::OnStartMixingClicked()
{
	FString Path = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Audio"), TEXT("Agora.io-Interactions.wav"));

	if (CB_URL->CheckedState == ECheckBoxState::Checked && ET_URL->GetText().ToString() == "")
	{
		UBFL_Logger::Print(FString::Printf(TEXT("%s URL Is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	if (CB_URL->CheckedState == ECheckBoxState::Checked) {

		Path = ET_URL->GetText().ToString();
	}
	else {

		if (FPaths::FileExists(Path)) {
			UBFL_Logger::Print(FString::Printf(TEXT("%s File Exists Path=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
		else {
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s File Doesn't Exist Path=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
#if PLATFORM_ANDROID || PLATFORM_IOS
		UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.wav");
		ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
		UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
		UBFL_UtilityTool::CreateMediaFileWithSource(Path, ValSavedFilePath);
		Path = ValSavedFilePath;
#endif
	}

	int ParamLoop = CB_Loop->CheckedState == ECheckBoxState::Checked ? -1 : 1;
	int ret = RtcEngineProxy->startAudioMixing(TCHAR_TO_UTF8(*Path), CB_LocalOnly->CheckedState == ECheckBoxState::Checked, ParamLoop);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioMixingWidget::OnStopMixingClicked()
{
	int ret = RtcEngineProxy->stopAudioMixing();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioMixingWidget::OnStartEffectClicked()
{
	FString Path = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Audio"), TEXT("Agora.io-Interactions.wav"));

	if (CB_URL->CheckedState == ECheckBoxState::Checked && ET_URL->GetText().ToString() == "")
	{
		UBFL_Logger::Print(FString::Printf(TEXT("%s URL Is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	if (CB_URL->CheckedState == ECheckBoxState::Checked) {

		Path = ET_URL->GetText().ToString();
	}
	else {

		if (FPaths::FileExists(Path)) {
			UBFL_Logger::Print(FString::Printf(TEXT("%s File Exists Path=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
		else {
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s File Doesn't Exist Path=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
#if PLATFORM_ANDROID || PLATFORM_IOS
		UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.wav");
		ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
		UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
		UBFL_UtilityTool::CreateMediaFileWithSource(Path, ValSavedFilePath);
		Path = ValSavedFilePath;
#endif

	}
	int ParamLoop = CB_Loop->CheckedState == ECheckBoxState::Checked ? -1 : 1;
	int ret = RtcEngineProxy->playEffect(1, TCHAR_TO_UTF8(*Path), ParamLoop, 0.5, 1, 80, CB_LocalOnly->CheckedState != ECheckBoxState::Checked, 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UAudioMixingWidget::OnStopEffectClicked()
{
	int ret = RtcEngineProxy->stopAllEffects();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UAudioMixingWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}

void UAudioMixingWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region  AgoraCallback - IRtcEngineEventHandlerEx


void UAudioMixingWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

void UAudioMixingWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

void UAudioMixingWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());
		});
}

void UAudioMixingWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());
		});
}


#pragma endregion

