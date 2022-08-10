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

	auto ret = RtcEngineProxy->startPrimaryCameraCapture(ConfigPrimary);
	agora::rtc::ChannelMediaOptions options;
#if !(PLATFORM_ANDROID || PLATFORM_IOS)
	options.autoSubscribeAudio = true;
	options.autoSubscribeVideo = true;
	options.publishCameraTrack = true;
	options.publishScreenTrack = false;
	options.enableAudioRecordingOrPlayout = true;
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
#endif
	RtcEngineProxy->joinChannel(Token.c_str(),ChannelName.c_str(), Uid1, options);
}

void USendMultiCameraStreamWidget::MainCameraLeaveChannel()
{
	RtcEngineProxy->stopPrimaryCameraCapture();

	auto ret = RtcEngineProxy->leaveChannel();
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

	UE_LOG(LogTemp, Warning, TEXT("SecondCameraLeaveChannel returns: %d"), ret);
}

#pragma region RtcEngineCallBack
void USendMultiCameraStreamWidget::onUserOffline(const RtcConnection& connection, uid_t remoteUid, USER_OFFLINE_REASON_TYPE reason)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnUserJoined uid: %d, reason: %d"), remoteUid,(int)reason));

	if (remoteUid != Uid1 && remoteUid != Uid2)
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserJoined  uid: %u"), remoteUid);
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = remoteUid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	}
}


void USendMultiCameraStreamWidget::onError(int err, const char* msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnError err: %d, msg: %s"), err,msg));
}

void USendMultiCameraStreamWidget::onJoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	bIsChannelJoined = true;

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnJoinChannelSuccess uid: %d, elapsed: %d"), connection.localUid, elapsed));

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
}

void USendMultiCameraStreamWidget::onRejoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnRejoinChannelSuccess")));
}

void USendMultiCameraStreamWidget::onLeaveChannel(const RtcConnection& connection, const RtcStats& stats)
{
	bIsChannelJoined = false;

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnLeaveChannel")));

	if (connection.localUid == Uid1)
	{
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = Uid1;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
		RtcEngineProxy->setupLocalVideo(videoCanvas);
	}

	if (connection.localUid == Uid2)
	{
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = Uid2;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
		RtcEngineProxy->setupLocalVideo(videoCanvas);
	}
}

void USendMultiCameraStreamWidget::onClientRoleChanged(const RtcConnection& connection, CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("OnClientRoleChanged")));
}

void USendMultiCameraStreamWidget::onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed)
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
}
#pragma endregion RtcEngineCallBack
void USendMultiCameraStreamWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}

