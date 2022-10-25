// Fill out your copyright notice in the Description page of Project Settings.


#include "EncryptionSampleWidget.h"

void UEncryptionSampleWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetEncryption();

	SetUpUIEvent();
}


void UEncryptionSampleWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) {

	RtcEngineContext RtcEngineContext;
	std::string APP_IDStr(TCHAR_TO_ANSI(*APP_ID));
	AppID = APP_IDStr;
	std::string TOKENStr(TCHAR_TO_ANSI(*TOKEN));
	Token = TOKENStr;
	std::string CHANNEL_NAMEStr(TCHAR_TO_ANSI(*CHANNEL_NAME));
	ChannelName = CHANNEL_NAMEStr;

	RtcEngineContext.appId = AppID.c_str();
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);
}

void UEncryptionSampleWidget::SetUpUIEvent() {

	JoinBtn->OnClicked.AddDynamic(this, &UEncryptionSampleWidget::OnJoinButtonClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UEncryptionSampleWidget::OnLeaveButtonClick);
}


void UEncryptionSampleWidget::OnJoinButtonClick() {

	UE_LOG(LogTemp, Warning, TEXT("UEncryptionSampleWidget OnJoinButtonClick ======"));
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

}



void UEncryptionSampleWidget::CheckAndroidPermission()
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

void UEncryptionSampleWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UEncryptionSampleWidget OnLeaveButtonClick ======"));

	RtcEngineProxy->leaveChannel();
}

#pragma region RtcEngineCallBack
void UEncryptionSampleWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess"));
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = localVideo;
		videoCanvas.uid = 0;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
		RtcEngineProxy->setupLocalVideo(videoCanvas);
	});
}

void UEncryptionSampleWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UEncryptionSampleWidget::onUserJoined  uid: %u"), uid);
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = remoteVideo;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = ChannelName.c_str();

		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	});
}

void UEncryptionSampleWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UEncryptionSampleWidget::onUserOffline  uid: %u"), uid);
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = ChannelName.c_str();

		if (RtcEngineProxy != nullptr)
		{
			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
		remoteVideo->SetBrush(EmptyBrush);
	});
}

void UEncryptionSampleWidget::SetEncryption()
{
	char deviceName[32] = "EncryptionKdfSaltInBase64String";

	EncryptionConfig config;
	config.encryptionMode = EncrytionMode;
	config.encryptionKey = secret;
	FMemory::Memcpy(config.encryptionKdfSalt, deviceName, 32);
	int ret = RtcEngineProxy->enableEncryption(true, config);

	UE_LOG(LogTemp, Warning, TEXT("UEncryptionSampleWidget::SetEncryption %d"), ret);
}


void UEncryptionSampleWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UEncryptionSampleWidget::onLeaveChannel"));
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = 0;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
		if (RtcEngineProxy != nullptr)
		{
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
		localVideo->SetBrush(EmptyBrush);
		remoteVideo->SetBrush(EmptyBrush);
	});
}
#pragma endregion RtcEngineCallBack


void UEncryptionSampleWidget::SetRemoteView(UImage* remoteview, uid_t uid)
{
	VideoCanvas videoCanvas;
	videoCanvas.view = remoteview;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

	RtcConnection connection;
	connection.channelId = ChannelName.c_str();

	((IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
}


void UEncryptionSampleWidget::NativeDestruct() {

	Super::NativeDestruct();

	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}

}