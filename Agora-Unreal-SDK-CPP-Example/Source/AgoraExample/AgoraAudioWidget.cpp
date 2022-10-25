// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraAudioWidget.h"


void UAgoraAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();
}


void UAgoraAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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
}

void UAgoraAudioWidget::SetUpUIEvent()
{
	JoinBtn->OnClicked.AddDynamic(this, &UAgoraAudioWidget::OnJoinButtonClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UAgoraAudioWidget::OnLeaveButtonClick);
	VolumeIndicationBtn->OnClicked.AddDynamic(this, &UAgoraAudioWidget::OnVolumeIndicationClick);
}

void UAgoraAudioWidget::CheckAndroidPermission()
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

void UAgoraAudioWidget::OnJoinButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UAgoraAudioWidget OnJoinButtonClick ======"));

	SetButtonClickAble(false);

	RtcEngineProxy->enableAudio();
	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

	
}

void UAgoraAudioWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UAgoraAudioWidget OnLeaveButtonClick ======"));
	SetButtonClickAble(true);
	RtcEngineProxy->leaveChannel();
}


void UAgoraAudioWidget::OnVolumeIndicationClick()
{
	if (RtcEngineProxy!=nullptr)
	{
		RtcEngineProxy->enableAudioVolumeIndication(200,3,false);
	}
}

#pragma region RtcEngineCallBack
void UAgoraAudioWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UAgoraAudioWidget::JoinChannelSuccess uid: %u"), uid));
	});
}

void UAgoraAudioWidget::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		for (unsigned int i = 0; i < speakerNumber; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("onAudioVolumeIndication uid:%lld,vad:%d,voicepatch:%d,volume %d,totalvolume:%d"), speakers[i].uid, speakers[i].vad, speakers[i].voicePitch, speakers[i].volume, totalVolume));
		}
	});
}

void UAgoraAudioWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UAgoraAudioWidget::onUserJoined uid: %u"), uid));
	});

}
#pragma endregion RtcEngineCallBack

void UAgoraAudioWidget::SetButtonClickAble(bool enable) {
	JoinBtn->SetIsEnabled(enable);
	LeaveBtn->SetIsEnabled(!enable);
}

void UAgoraAudioWidget::NativeDestruct() {
	Super::NativeDestruct();

	if (RtcEngineProxy!=nullptr)
	{
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}
