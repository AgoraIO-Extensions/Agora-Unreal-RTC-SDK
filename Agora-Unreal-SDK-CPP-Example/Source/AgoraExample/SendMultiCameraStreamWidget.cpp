// Fill out your copyright notice in the Description page of Project Settings.


#include "SendMultiCameraStreamWidget.h"


void USendMultiCameraStreamWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	GetVideoDeviceManager();

	SetUpUIEvent();
}


void USendMultiCameraStreamWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::White, FString::Printf(TEXT("Not Support in this platform!")));
	return;
#endif
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

	VideoDeviceManager.queryInterface(RtcEngineProxy, AGORA_IID_VIDEO_DEVICE_MANAGER);
}


void USendMultiCameraStreamWidget::SetUpUIEvent()
{
	MainCameraJoin->OnClicked.AddDynamic(this, &USendMultiCameraStreamWidget::MainCameraJoinChannel);
	MainCameraLeave->OnClicked.AddDynamic(this, &USendMultiCameraStreamWidget::MainCameraLeaveChannel);
	SecondCameraJoin->OnClicked.AddDynamic(this, &USendMultiCameraStreamWidget::SecondCameraJoinChannel);
	SecondCameraLeave->OnClicked.AddDynamic(this, &USendMultiCameraStreamWidget::SecondCameraLeaveChannel);
}

void USendMultiCameraStreamWidget::CheckAndroidPermission()
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

void USendMultiCameraStreamWidget::GetVideoDeviceManager()
{
	if (!VideoDeviceManager)
	{
		return;
	}
	VideoDeviceInfos = VideoDeviceManager->enumerateVideoDevices();

	if (VideoDeviceInfos != nullptr && VideoDeviceInfos->getCount() > 0)
	{
#if !(PLATFORM_ANDROID || PLATFORM_IOS)

		char deviceName[MAX_DEVICE_ID_LENGTH];
		char deviceId[MAX_DEVICE_ID_LENGTH];

		VideoDeviceInfos->getDevice(0, deviceName, deviceId);

		FMemory::Memcpy(ConfigPrimary.deviceId, deviceId, MAX_DEVICE_ID_LENGTH);
#endif
		
	}

	if (VideoDeviceInfos != nullptr && VideoDeviceInfos->getCount() > 1)
	{
#if !(PLATFORM_ANDROID || PLATFORM_IOS)
		char deviceName[MAX_DEVICE_ID_LENGTH];
		char deviceId[MAX_DEVICE_ID_LENGTH];

		VideoDeviceInfos->getDevice(1, deviceName, deviceId);

		FMemory::Memcpy(ConfigSecond.deviceId, deviceId, MAX_DEVICE_ID_LENGTH);
#endif
	}

}


void USendMultiCameraStreamWidget::MainCameraJoinChannel()
{
	RtcEngineProxy->startPreview();
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

	agora::rtc::RtcConnection connection;
	connection.channelId = ChannelName.c_str();
	connection.localUid = Uid1;


	auto ret = RtcEngineProxy->startPrimaryCameraCapture(ConfigPrimary);

	UE_LOG(LogTemp, Warning, TEXT("MainCameraJoinChannel returns: %d"), ret);
	agora::rtc::ChannelMediaOptions options;
#if PLATFORM_MAC || PLATFORM_WINDOWS
	options.autoSubscribeAudio = true;
	options.autoSubscribeVideo = true;
	options.publishCameraTrack = true;
	options.publishScreenTrack = false;
	options.enableAudioRecordingOrPlayout = true;
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
#endif
	ret =  ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->joinChannelEx(Token.c_str(), connection, options, nullptr);

	UE_LOG(LogTemp, Warning, TEXT("MainCameraJoinChannel joinChannelEx returns: %d"), ret);
}

void USendMultiCameraStreamWidget::MainCameraLeaveChannel()
{
	RtcEngineProxy->stopPrimaryCameraCapture();

	agora::rtc::RtcConnection connection;
	connection.channelId = ChannelName.c_str();
	connection.localUid = Uid1;

	auto ret = ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->leaveChannelEx(connection);

	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = 0;
	videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	RtcEngineProxy->setupLocalVideo(videoCanvas);

	UE_LOG(LogTemp, Warning, TEXT("MainCameraLeaveChannel returns: %d ,ChannelName %s ,Uid %d"), ret, *FString(ChannelName.c_str()), Uid1);
	PrimaryVideo->Brush = EmptyBrush;
}


void USendMultiCameraStreamWidget::SecondCameraJoinChannel()
{
	auto ret = RtcEngineProxy->startSecondaryCameraCapture(ConfigSecond);

	agora::rtc::RtcConnection connection;
	connection.channelId = ChannelName.c_str();
	connection.localUid = Uid2;
	agora::rtc::ChannelMediaOptions options;
#if !(PLATFORM_ANDROID || PLATFORM_IOS)
	options.autoSubscribeAudio = false;
	options.autoSubscribeVideo = false;
	options.publishCustomAudioTrack = false;
	options.publishCameraTrack = false;
	options.publishSecondaryCameraTrack = true;
	options.enableAudioRecordingOrPlayout = false;
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
#endif
	((agora::rtc::IRtcEngineEx*)RtcEngineProxy) ->joinChannelEx(Token.c_str(), connection , options,nullptr);
}

void USendMultiCameraStreamWidget::SecondCameraLeaveChannel()
{
	agora::rtc::RtcConnection connection;
	connection.channelId = ChannelName.c_str();
	connection.localUid = Uid2;
	RtcEngineProxy->stopSecondaryCameraCapture();
	auto ret = ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->leaveChannelEx(connection);

	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = 0;
	videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_SECONDARY;
	RtcEngineProxy->setupLocalVideo(videoCanvas);

	SecondVideo->Brush = EmptyBrush;
	UE_LOG(LogTemp, Warning, TEXT("SecondCameraLeaveChannel returns: %d ,ChannelName %s ,Uid %d"), ret, *FString(ChannelName.c_str()) ,Uid2);
}

#pragma region RtcEngineCallBack
void USendMultiCameraStreamWidget::onUserOffline(const RtcConnection& connection, uid_t remoteUid, USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnUserJoined uid: %d, reason: %d"), (int64)remoteUid,(int)reason));

		if (remoteUid != Uid1 && remoteUid != Uid2)
		{
			UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserOffline  uid: %u"), remoteUid);
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = remoteUid;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	});
}


void USendMultiCameraStreamWidget::onError(int err, const char* msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnError err: %d, msg: %s"), err,msg));
}

void USendMultiCameraStreamWidget::onJoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnJoinChannelSuccess uid: %d,ChannelName: %s, elapsed: %d"), connection.localUid, *FString(connection.channelId),elapsed));

		if (connection.localUid == Uid1)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = PrimaryVideo;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}

		if (connection.localUid == Uid2)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = SecondVideo;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_SECONDARY;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}

void USendMultiCameraStreamWidget::onRejoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnRejoinChannelSuccess")));
}

void USendMultiCameraStreamWidget::onLeaveChannel(const RtcConnection& connection, const RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnLeaveChannel")));

		if (connection.localUid == Uid1)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = Uid1;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
			PrimaryVideo->Brush = EmptyBrush;
		}

		if (connection.localUid == Uid2)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = Uid2;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}


void USendMultiCameraStreamWidget::onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnUserJoined uid: %d elapsed: %d"), connection.channelId, elapsed));

		if (remoteUid != Uid1 && remoteUid != Uid2)
		{
			UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserJoined  uid: %u"), remoteUid);
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = remoteVideo;
			videoCanvas.uid = remoteUid;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	});
}
#pragma endregion RtcEngineCallBack
void USendMultiCameraStreamWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RtcEngineProxy != nullptr)
	{
		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}
