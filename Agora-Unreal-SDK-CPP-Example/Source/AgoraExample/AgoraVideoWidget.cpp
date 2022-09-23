// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraVideoWidget.h"

void UAgoraVideoWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID,TOKEN,CHANNEL_NAME);

	SetUpUIEvent();

	//SetResolution(640,480);
}

void UAgoraVideoWidget::SetResolution(int width ,int height)
{
	VideoEncoderConfiguration videoEncoderConfiguration;
	VideoDimensions videoDimensions(width, height);
	videoEncoderConfiguration.dimensions = videoDimensions;
	videoEncoderConfiguration.codecType = VIDEO_CODEC_TYPE::VIDEO_CODEC_H264;
	videoEncoderConfiguration.bitrate = 0;
	videoEncoderConfiguration.minBitrate = 1;
	videoEncoderConfiguration.orientationMode = ORIENTATION_MODE::ORIENTATION_MODE_ADAPTIVE;
	videoEncoderConfiguration.degradationPreference = DEGRADATION_PREFERENCE::MAINTAIN_FRAMERATE;
	videoEncoderConfiguration.mirrorMode = VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO;

	RtcEngineProxy->setVideoEncoderConfiguration(videoEncoderConfiguration);
}


void UAgoraVideoWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) {

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

void UAgoraVideoWidget::SetUpUIEvent() {

	JoinBtn->OnClicked.AddDynamic(this, &UAgoraVideoWidget::OnJoinButtonClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UAgoraVideoWidget::OnLeaveButtonClick);
	PreviousBtn->SetIsEnabled(false);
	NextBtn->SetIsEnabled(false);
	PreviousBtn->OnClicked.AddDynamic(this, &UAgoraVideoWidget::OnPreviousButtonClick);
	NextBtn->OnClicked.AddDynamic(this, &UAgoraVideoWidget::OnNextButtonClick);
	BackHomeBtn->OnClicked.AddDynamic(this, &UAgoraVideoWidget::BackHomeClick);
}


void UAgoraVideoWidget::OnJoinButtonClick() {

	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnJoinButtonClick ======"));
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

}

void UAgoraVideoWidget::OnPreviousButtonClick()
{
	if (RemoteUserIdArray.Num() == 1 || CurrentRemoteIndex == 0)
	{
		return;
	}
	SetRemoteView(nullptr, RemoteUserIdArray[CurrentRemoteIndex]);
	CurrentRemoteIndex--;
	SetRemoteView(remoteVideo, RemoteUserIdArray[CurrentRemoteIndex]);
	NextBtn->SetIsEnabled(true);
}

void UAgoraVideoWidget::OnNextButtonClick()
{
	if (RemoteUserIdArray.Num() == 1 || CurrentRemoteIndex == RemoteUserIdArray.Num() - 1)
	{
		return;
	}
	SetRemoteView(nullptr, RemoteUserIdArray[CurrentRemoteIndex]);
	CurrentRemoteIndex++;
	SetRemoteView(remoteVideo, RemoteUserIdArray[CurrentRemoteIndex]);
	PreviousBtn->SetIsEnabled(true);
}

void UAgoraVideoWidget::BackHomeClick()
{
	UClass* AgoraWidgetClass = LoadClass<UBaseAgoraUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/API-Example/Advance/MainWidgetManager.MainWidgetManager_C'"));

	UBaseAgoraUserWidget* AgoraWidget = CreateWidget<UBaseAgoraUserWidget>(GetWorld(), AgoraWidgetClass);

	AgoraWidget->AddToViewport();

	AgoraWidget->InitAgoraWidget(FString(AppID.c_str()), FString(Token.c_str()), FString(ChannelName.c_str()));

	this->RemoveFromViewport();
}

void UAgoraVideoWidget::CheckAndroidPermission()
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

void UAgoraVideoWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnLeaveButtonClick ======"));

	for (int i = 0; i < RemoteUserIdArray.Num(); i++)
	{
		VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = RemoteUserIdArray[i];
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		RtcConnection connection;
		connection.channelId = ChannelName.c_str();
		((IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	}
	RemoteUserIdArray.Empty();

	RtcEngineProxy->leaveChannel();
}

#pragma region RtcEngineCallBack
void UAgoraVideoWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
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

void UAgoraVideoWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserJoined  uid: %u"), uid);
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = remoteVideo;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = ChannelName.c_str();

		if (RemoteUserIdArray.Num()>0)
		{
			SetRemoteView(nullptr, RemoteUserIdArray[CurrentRemoteIndex]);

		}
		RemoteUserIdArray.Add(uid);
		SetRemoteView(remoteVideo, uid);
		CurrentRemoteIndex = RemoteUserIdArray.Num() - 1;

		NextBtn->SetIsEnabled(RemoteUserIdArray.Num() != 1);
		PreviousBtn->SetIsEnabled(RemoteUserIdArray.Num() != 1);

		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	});
}

void UAgoraVideoWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserOffline  uid: %u"), uid);
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

		if (RemoteUserIdArray.Num() != 0)
		{
			SetRemoteView(nullptr, RemoteUserIdArray[CurrentRemoteIndex]);
			CurrentRemoteIndex = 0;
			SetRemoteView(remoteVideo, RemoteUserIdArray[CurrentRemoteIndex]);
		}

		RemoteUserIdArray.Remove(uid);
		remoteVideo->SetBrush(EmptyBrush);
	});
}

void UAgoraVideoWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onLeaveChannel  uid"));
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


void UAgoraVideoWidget::SetRemoteView(UImage* remoteview, uid_t uid)
{
	VideoCanvas videoCanvas;
	videoCanvas.view = remoteview;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

	RtcConnection connection;
	connection.channelId = ChannelName.c_str();

	((IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
}


void UAgoraVideoWidget::NativeDestruct() {

	Super::NativeDestruct();

	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}

}