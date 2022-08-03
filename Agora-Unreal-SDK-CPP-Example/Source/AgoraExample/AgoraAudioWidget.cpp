// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraAudioWidget.h"


void UAgoraAudioWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();
}


void UAgoraAudioWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	RtcEngineContext.appId = TCHAR_TO_ANSI(*APP_ID);
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	RtcEngineProxy->initialize(RtcEngineContext);
}

void UAgoraAudioWidget::SetUpUIEvent()
{
	JoinBtn->OnClicked.AddDynamic(this, &UAgoraAudioWidget::OnJoinButtonClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UAgoraAudioWidget::OnLeaveButtonClick);
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
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnJoinButtonClick ======"));

	CheckAndroidPermission();

	SetButtonClickAble(false);

	RtcEngineProxy->enableVideo();
	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);
}

void UAgoraAudioWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnLeaveButtonClick ======"));
	SetButtonClickAble(true);
	RtcEngineProxy->leaveChannel();
}

#pragma region RtcEngineCallBack
void UAgoraAudioWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess"));
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("onJoinChannelSuccess is videoCanvas"));
	});
}

void UAgoraAudioWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserJoined  uid: %u"), uid);
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
