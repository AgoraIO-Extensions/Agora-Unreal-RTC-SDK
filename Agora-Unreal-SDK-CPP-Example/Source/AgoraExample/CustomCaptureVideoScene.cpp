// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCaptureVideoScene.h"

void UCustomCaptureVideoScene::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetExternalVideoSource();

	JoinChannel();
}

void UCustomCaptureVideoScene::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UCustomCaptureVideoScene::CheckAndroidPermission()
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


void UCustomCaptureVideoScene::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;
	std::string APP_IDStr(TCHAR_TO_ANSI(*APP_ID));
	AppID = APP_IDStr;
	std::string TOKENStr(TCHAR_TO_ANSI(*TOKEN));
	Token = TOKENStr;
	std::string CHANNEL_NAMEStr(TCHAR_TO_ANSI(*CHANNEL_NAME));
	ChannelName = CHANNEL_NAMEStr;

	RtcEngineContext.appId = AppID.c_str();
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);
}

void UCustomCaptureVideoScene::SetExternalVideoSource()
{
	int ret = RtcEngineProxy->queryInterface(INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE,(void**)&MediaEngineProxy);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("MediaEngine init is %d"),ret));

	if (MediaEngineProxy != nullptr)
	{
		agora::rtc::SenderOptions sendoptions;

		MediaEngineProxy->setExternalVideoSource(true,false, agora::media::EXTERNAL_VIDEO_SOURCE_TYPE::VIDEO_FRAME, sendoptions);
	}
}

void UCustomCaptureVideoScene::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
}
