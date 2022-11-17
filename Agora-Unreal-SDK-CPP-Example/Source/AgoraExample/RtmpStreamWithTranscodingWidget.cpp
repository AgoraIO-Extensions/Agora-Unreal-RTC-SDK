// Fill out your copyright notice in the Description page of Project Settings.


#include "RtmpStreamWithTranscodingWidget.h"

void URtmpStreamWithTranscodingWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();

	JoinChannel();
}




void URtmpStreamWithTranscodingWidget::OnStartButtonClick()
{
	if (this->Uid == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("your must join channel."));
		return;
	}

	LiveTranscoding liveTranscoding;

	liveTranscoding.userCount = 1;
	TranscodingUser* transcodingUsers = new TranscodingUser[1];
	transcodingUsers[0].uid = this->Uid;
	transcodingUsers[0].x = 0;
	transcodingUsers[0].y = 0;
	transcodingUsers[0].width = 360;
	transcodingUsers[0].height = 640;
	transcodingUsers[0].alpha = 1;
	transcodingUsers[0].zOrder = 1;
	transcodingUsers[0].audioChannel = 0;
	liveTranscoding.transcodingUsers = transcodingUsers;

	FString url = RtmpTextBox->GetText().ToString();;
	if (url == "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("your must input your rtmpUrl in Inspector of VideoCanvas")));
		return;
	}

	auto ret = RtcEngineProxy->startRtmpStreamWithTranscoding(TCHAR_TO_ANSI(*url), liveTranscoding);

	delete[]transcodingUsers;
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("StartRtmpStreamWithTranscoding  ret %d"), ret));
	if (ret == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("StartRtmpStreamWithTranscoding url %s"), *url));
		/*
			Verify remote
			1.install ffmpeg(brew install ffmpeg)
			2.ffplay rtmp://play.xxxxx.xxx.xxxx
			or 
			1.vlc open rtmp://play.xxxxx.xxx.xxxx
		 */
	}
}

void URtmpStreamWithTranscodingWidget::OnStopButtonClick()
{
	FString url = RtmpTextBox->GetText().ToString();
	if (url == "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("your must input your rtmpUrl in Inspector of VideoCanvas")));
		return;
	}
	int ret = RtcEngineProxy->stopRtmpStream(TCHAR_TO_ANSI(*url));
	UE_LOG(LogTemp, Warning, TEXT("StopRtmpStream %d"), ret);
}

void URtmpStreamWithTranscodingWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) {

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

void URtmpStreamWithTranscodingWidget::SetUpUIEvent() {

	StartBtn->OnClicked.AddDynamic(this, &URtmpStreamWithTranscodingWidget::OnStartButtonClick);
	UpdateBtn->OnClicked.AddDynamic(this, &URtmpStreamWithTranscodingWidget::OnUpdateButtonClick);
	StopBtn->OnClicked.AddDynamic(this, &URtmpStreamWithTranscodingWidget::OnStopButtonClick);
}


void URtmpStreamWithTranscodingWidget::JoinChannel() {

	UE_LOG(LogTemp, Warning, TEXT("URtmpStreamWithTranscodingWidget"));
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

}



void URtmpStreamWithTranscodingWidget::CheckAndroidPermission()
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

void URtmpStreamWithTranscodingWidget::OnUpdateButtonClick() {

	LiveTranscoding liveTranscoding;
	liveTranscoding.userCount = 1;
	TranscodingUser* transcodingUsers = new TranscodingUser[1];
	transcodingUsers[0].uid = this->Uid;
	transcodingUsers[0].x = 0;
	transcodingUsers[0].y = 0;
	transcodingUsers[0].width = 640;
	transcodingUsers[0].height = 960;
	transcodingUsers[0].alpha = 1;
	transcodingUsers[0].zOrder = 1;
	transcodingUsers[0].audioChannel = 0;
	liveTranscoding.transcodingUsers = transcodingUsers;

	int ret = RtcEngineProxy->updateRtmpTranscoding(liveTranscoding);

	delete[] transcodingUsers;
	UE_LOG(LogTemp, Warning, TEXT("UpdateRtmpTranscoding %d"), ret);
}

#pragma region RtcEngineCallBack
void URtmpStreamWithTranscodingWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess"));
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = localVideo;
		videoCanvas.uid = 0;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
		RtcEngineProxy->setupLocalVideo(videoCanvas);
		this->Uid = uid;
	});
}

void URtmpStreamWithTranscodingWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("URtmpStreamWithTranscodingWidget::onUserJoined  uid: %d"), (int64)uid);
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = remoteVideo;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = ChannelName.c_str();

		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	});
}

void URtmpStreamWithTranscodingWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("URtmpStreamWithTranscodingWidget::onUserOffline  uid: %d"), (int64)uid);
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



void URtmpStreamWithTranscodingWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("URtmpStreamWithTranscodingWidget::onLeaveChannel"));
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

void URtmpStreamWithTranscodingWidget::onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR_TYPE errCode)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("OnRtmpStreamingStateChanged url:%s,state:%d ,errCode:%d"), UTF8_TO_TCHAR(url), state, errCode));
	});
}

void URtmpStreamWithTranscodingWidget::onTranscodingUpdated()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("OnTranscodingUpdated")));
	});
}
#pragma endregion RtcEngineCallBack


void URtmpStreamWithTranscodingWidget::SetRemoteView(UImage* remoteview, uid_t uid)
{
	VideoCanvas videoCanvas;
	videoCanvas.view = remoteview;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

	RtcConnection connection;
	connection.channelId = ChannelName.c_str();

	((IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
}


void URtmpStreamWithTranscodingWidget::NativeDestruct() {

	Super::NativeDestruct();

	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}

}