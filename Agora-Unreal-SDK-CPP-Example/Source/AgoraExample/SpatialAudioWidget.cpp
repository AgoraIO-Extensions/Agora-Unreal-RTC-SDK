// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialAudioWidget.h"

void USpatialAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Yellow, FString::Printf(TEXT("If you want to test this case ,please add another User join")));

	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();

	InitSpatialAudioEngine(RtcEngineProxy);
}

void USpatialAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;
	RtcEngineContext.appId = TCHAR_TO_ANSI(*APP_ID);
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	Appid = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);
}


void USpatialAudioWidget::SetUpUIEvent()
{
	JoinBtn->OnClicked.AddDynamic(this, &USpatialAudioWidget::OnJoinButtonClick);
	LeftMoveBtn->OnClicked.AddDynamic(this, &USpatialAudioWidget::LeftMoveButtonClick);
	RightMoveBtn->OnClicked.AddDynamic(this, &USpatialAudioWidget::RightMoveButtonClick);
}

void USpatialAudioWidget::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	float f1[3] = { 0.0f, 0.0f, 0.0f };
	float f2[3] = { 1.0f, 0.0f, 0.0f };
	float f3[3] = { 0.0f, 1.0f, 0.0f };
	float f4[3] = { 0.0f, 0.0f, 1.0f };
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("OnJoinChannelSuccess channelName: %s, uid: %d, elapsed: %d"), UTF8_TO_TCHAR(channel), (int64)uid, elapsed));
	if (LocalSpatialAudioEngine)
	{
		LocalSpatialAudioEngine->updateSelfPosition(f1, f2, f3, f4);
	}
}

void USpatialAudioWidget::onUserJoined(uid_t uid, int elapsed)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Black, FString::Printf(TEXT("OnUserJoined uid: %d elapsed: %d"), (int64)uid, elapsed));

	RemoteUid = uid;
}


void USpatialAudioWidget::OnJoinButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("USpatialAudioWidget OnJoinButtonClick ======"));

	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);

	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

	agora::rtc::ChannelMediaOptions options;
	options.autoSubscribeAudio = false;
	options.autoSubscribeVideo = false;
	options.publishCameraTrack = false;
	options.publishMicrophoneTrack = true;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	options.publishScreenTrack = false;
#elif PLATFORM_ANDROID
	options.publishScreenCaptureAudio = false;
	options.publishScreenCaptureVideo = false;
#endif
	options.enableAudioRecordingOrPlayout = true;
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	RtcEngineProxy->updateChannelMediaOptions(options);
}

void USpatialAudioWidget::RightMoveButtonClick()
{	
	RemoteVoicePositionInfo remoteVoicePos{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };

	auto ret = LocalSpatialAudioEngine->updateRemotePosition(RemoteUid, remoteVoicePos);

	UE_LOG(LogTemp, Warning, TEXT("LocalSpatialAudioEngine->updateSelfPosition returns: %d"), ret);
}

void USpatialAudioWidget::LeftMoveButtonClick()
{
	RemoteVoicePositionInfo remoteVoicePos{ { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };

	auto ret = LocalSpatialAudioEngine->updateRemotePosition(RemoteUid, remoteVoicePos);

	UE_LOG(LogTemp, Warning, TEXT("LocalSpatialAudioEngine->updateSelfPosition returns: %d"), ret);
}


void USpatialAudioWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LocalSpatialAudioEngine = nullptr;
}

void USpatialAudioWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RtcEngineProxy)
	{
		if (LocalSpatialAudioEngine != nullptr)
		{
			LocalSpatialAudioEngine->release();
			LocalSpatialAudioEngine = nullptr;
		}
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}

void USpatialAudioWidget::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
	FString pathfromName = UGameplayStatics::GetPlatformName();
	if (pathfromName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.CAMERA"));
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
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

		UE_LOG(LogTemp, Warning, TEXT("LocalSpatialAudioEngine: Initialize %d"), ret);

		LocalSpatialAudioEngine->setAudioRecvRange(30);
	}
}
