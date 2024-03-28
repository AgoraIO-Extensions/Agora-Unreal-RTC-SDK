// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialAudioWidget.h"

void USpatialAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitUI();

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	InitSpatialAudioEngine(RtcEngineProxy);
}

void USpatialAudioWidget::CheckPermission()
{
#if PLATFORM_ANDROID
	FString TargetPlatformName = UGameplayStatics::GetPlatformName();
	if (TargetPlatformName == "Android")
	{
		TArray<FString> AndroidPermission;
#if !AGORA_UESDK_AUDIO_ONLY || (!(PLATFORM_ANDROID || PLATFORM_IOS))
		AndroidPermission.Add(FString("android.permission.CAMERA"));
#endif
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}


void USpatialAudioWidget::InitUI()
{
	Txt_Distance->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), Slider_Distance->GetValue())));
}

void USpatialAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

}


void USpatialAudioWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [SpatialAudio]\n"
		"1. Play spatial audio using the audio data from the remote user. \n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void USpatialAudioWidget::InitSpatialAudioEngine(IRtcEngine* engine)
{

	if (LocalSpatialAudioEngine == nullptr)
	{
		engine->queryInterface(AGORA_IID_LOCAL_SPATIAL_AUDIO, (void**)&LocalSpatialAudioEngine);
	}

	if (LocalSpatialAudioEngine != nullptr)
	{
		LocalSpatialAudioConfig AudioConfig;

		AudioConfig.rtcEngine = engine;

		auto ret = LocalSpatialAudioEngine->initialize(AudioConfig);

		UBFL_Logger::Print(FString::Printf(TEXT("%s  LocalSpatialAudioEngine->initialize ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

		LocalSpatialAudioEngine->setAudioRecvRange(50);

		LocalSpatialAudioEngine->setDistanceUnit(1);

		float pos[3] = { 0,0,0 };
		float forward[3] = { 1,0,0 };
		float right[3] = { 0,1,0 };
		float up[3] = { 0,0,1 };

		LocalSpatialAudioEngine->updateSelfPosition(pos, forward, right, up);
	}
}

int USpatialAudioWidget::UpdateRemotePositionWithCurrentDistanceVal()
{
	float Val = Slider_Distance->GetValue();
	RemoteVoicePositionInfo ValRemotePositionInfo{ { 0.0f , Val, 0.0f },{ 0.0f ,0.0f , 0.0f } };
	int ret = LocalSpatialAudioEngine->updateRemotePosition(RemoteUID, ValRemotePositionInfo);
	return ret;
}

void USpatialAudioWidget::OnBtnJoinChannelClicked()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void USpatialAudioWidget::OnBtnLeaveChannelClicked()
{
	int ret = RtcEngineProxy->leaveChannel();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void USpatialAudioWidget::OnSliderDistanceValChanged(float val)
{
	Txt_Distance->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), val)));

	if (RemoteUID == 0)
		return;

	int ret = UpdateRemotePositionWithCurrentDistanceVal();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void USpatialAudioWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void USpatialAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();
}



void USpatialAudioWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{

		if (LocalSpatialAudioEngine != nullptr)
		{
			LocalSpatialAudioEngine->release();
			LocalSpatialAudioEngine = nullptr;
		}

		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		agora::rtc::ue::releaseAgoraRtcEngine();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


#pragma region AgoraCallback - IRtcEngineEventHandlerEx

void USpatialAudioWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

void USpatialAudioWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

void USpatialAudioWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

			WidgetPtr->SetRemoteUID(remoteUid);
			int ret = WidgetPtr->UpdateRemotePositionWithCurrentDistanceVal();
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u update position ret=%d"), *FString(FUNCTION_MACRO), remoteUid, ret), WidgetPtr->GetLogMsgViewPtr());

		});
}

void USpatialAudioWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
			WidgetPtr->SetRemoteUID(0);
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

		});
}

#pragma endregion