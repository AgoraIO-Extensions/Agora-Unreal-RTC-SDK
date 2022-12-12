// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinMultipleChannelWidget.h"


void UJoinMultipleChannelWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
#if PLATFORM_IOS
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::White, FString::Printf(TEXT("Not Support in this platform!")));
	return;
#endif

	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	PrepareScreenCapture();

	SetUpUIEvent();

	InitUI();

	int ret = RtcEngineProxy->setParameters("{\"che.video.local.camera_index\":1024}");
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setParameters che.video.local.camera_index ======%d"), ret);

	ret = RtcEngineProxy->setParameters("{\"rtc.video.degradation_preference\":100}");
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setParameters rtc.video.degradation_preference ======%d"), ret);

	ret = RtcEngineProxy->setParameters("{\"che.video.h264.hwenc\":1}");
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setParameters che.video.h264.hwenc ======%d"), ret);
}

void UJoinMultipleChannelWidget::SetUpUIEvent()
{
	JoinBtn->OnClicked.AddDynamic(this, &UJoinMultipleChannelWidget::JoinChannelClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UJoinMultipleChannelWidget::LeaveChannelClick);
	ConfirmBtn->OnClicked.AddDynamic(this, &UJoinMultipleChannelWidget::ScreenShareClick);
}

void UJoinMultipleChannelWidget::CheckAndroidPermission()
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

void  UJoinMultipleChannelWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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


void UJoinMultipleChannelWidget::StartScreenShare(int width, int height, int bitRate, int frameRate)
{
#if PLATFORM_IOS
	//iPhone not support screen capture       
#elif PLATFORM_ANDROID
	ScreenCaptureParameters2 parameters2;
	parameters2.captureAudio = true;
	parameters2.captureVideo = true;
	auto ret = RtcEngineProxy->startScreenCapture(parameters2);
	UE_LOG(LogTemp, Warning, TEXT("StartScreenShrareClick JoinChannel ====== %d"), ret);
#else
	RtcEngineProxy->stopScreenCapture();
	agora::rtc::ScreenCaptureParameters capParam;
	VideoDimensions dimensions(width,height);
	capParam.dimensions = dimensions;
	capParam.bitrate = bitRate;
	capParam.frameRate = frameRate;
	capParam.enableHighLight = false;
	capParam.windowFocus = false;
	capParam.captureMouseCursor =false;
	UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget StartScreenShrare width: %d height : %d,bitRate %d,frameRate %d"), width,height,bitRate,frameRate);
	const agora::rtc::Rectangle regionRect;
#if PLATFORM_WINDOWS
	SIZE size;
	size.cx = 100;
	size.cy = 100;
#else
	agora::rtc::SIZE size;
	size.width = 100;
	size.height = 100;
#endif
	if (infos == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetScreenDisplay is null"));
		return;
	}
	agora::rtc::ScreenCaptureSourceInfo info = infos->getSourceInfo(SelectDisplayId);
	if (info.type == agora::rtc::ScreenCaptureSourceType_Screen)
	{
		RtcEngineProxy->startScreenCaptureByDisplayId((uint64)(info.sourceId), regionRect, capParam);
	}
	else if (info.type == agora::rtc::ScreenCaptureSourceType_Window)
	{
		RtcEngineProxy->startScreenCaptureByWindowId(info.sourceId, regionRect, capParam);
	}
#endif
#if PLATFORM_WINDOWS||PLATFORM_MAC
	RtcEngineProxy->setScreenCaptureScenario(SCREEN_SCENARIO_GAMING);
#endif
	ScreenShareJoinChannel();
}

void UJoinMultipleChannelWidget::PrepareScreenCapture()
{
#if PLATFORM_WINDOWS || PLATFORM_MAC
#if PLATFORM_WINDOWS
	SIZE size;
	size.cx = 100;
	size.cy = 100;
#endif
#if PLATFORM_MAC
	agora::rtc::SIZE size;
	size.width = 100;
	size.height = 100;
#endif

	infos = RtcEngineProxy->getScreenCaptureSources(size, size, true);

	if (infos == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetScreenDisplay is null"));
		return;
	}

	for (size_t i = 0; i < infos->getCount(); i++) {
		agora::rtc::ScreenCaptureSourceInfo info = infos->getSourceInfo(i);
		FString Displayid(UTF8_TO_TCHAR(info.sourceName));
		ComboBoxDisplayId->AddOption(Displayid);
	}

	ComboBoxDisplayId->OnSelectionChanged.AddDynamic(this, &UJoinMultipleChannelWidget::SelectValueCallBack);

	if (infos != nullptr && infos->getCount() > 0)
	{
		ComboBoxDisplayId->SetSelectedIndex(0);
		SelectDisplayId = 0;
	}
#endif
}
void UJoinMultipleChannelWidget::LeaveChannelClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget OnJoinButtonClick ======"));

	RtcEngineProxy->leaveChannel();
	for (int i = 0; i < NotUseArray.Num(); i++)
	{
		NotUseArray[i].image->SetBrush(EmptyBrush);
	}
	for (int i = 0; i < UsedArray.Num(); i++)
	{
		UsedArray[i].image->SetBrush(EmptyBrush);
	}
	LocalVideo->SetBrush(EmptyBrush);
	NotUseArray.Empty();
	UsedArray.Empty();
	InitUI();
}

void UJoinMultipleChannelWidget::JoinChannelClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget OnJoinButtonClick ======"));

	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();

	RtcConnection rtcConnection;
	rtcConnection.channelId = ChannelName.c_str();
	rtcConnection.localUid = Uid1;
	agora::rtc::ChannelMediaOptions options;

	options.autoSubscribeAudio = true;
	options.autoSubscribeVideo = true;
	options.publishCameraTrack = true;
	options.publishMicrophoneTrack = true;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	options.publishScreenTrack = false;
#elif PLATFORM_ANDROID
	options.publishScreenCaptureAudio = false;
	options.publishScreenCaptureVideo = false;
#endif
	options.enableAudioRecordingOrPlayout = true;
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->joinChannelEx(Token.c_str(), rtcConnection, options, nullptr);
}

void UJoinMultipleChannelWidget::ScreenShareClick()
{
	int ret = RtcEngineProxy->setChannelProfile(AgoraChannelProfileEnumMap[ProfileComboBox->GetSelectedOption()]);
	UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget setChannelProfile ret: %d ChannelProfile : %s"), ret, *ProfileComboBox->GetSelectedOption());

	ret = RtcEngineProxy->setAudioScenario(AgoraAudioScenarioEnumMap[ScenarioComboBox->GetSelectedOption()]);
	UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget setAudioScenario ret: %d AudioScenario : %s"), ret, *ScenarioComboBox->GetSelectedOption());

	StartScreenShare(FCString::Atoi(*WidthTextBox->GetText().ToString()), FCString::Atoi(*HeightTextBox->GetText().ToString()), FCString::Atoi(*BitRateTextBox->GetText().ToString()), FCString::Atoi(*FPSComboBox->GetSelectedOption()));
}

void UJoinMultipleChannelWidget::SelectValueCallBack(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	UE_LOG(LogTemp, Warning, TEXT("Screen Callpture"));
	if (ComboBoxDisplayId != nullptr)
	{
		SelectDisplayId = ComboBoxDisplayId->FindOptionIndex(SelectedItem);
	}
}


void UJoinMultipleChannelWidget::ScreenShareJoinChannel()
{
	UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget JoinChannel ======"));
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();

	agora::rtc::ChannelMediaOptions options;
	options.autoSubscribeAudio = false;
	options.autoSubscribeVideo = false;
	options.publishMicrophoneTrack = false;
	options.publishCameraTrack = false;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	options.publishScreenTrack = true;
#elif PLATFORM_ANDROID
	options.publishScreenCaptureAudio = true;
	options.publishScreenCaptureVideo = true;
#endif
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	RtcConnection rtcConnection;
	rtcConnection.channelId = ChannelName.c_str();
	rtcConnection.localUid = Uid2;

	((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->joinChannelEx(Token.c_str(), rtcConnection, options, nullptr);
}

void UJoinMultipleChannelWidget::onJoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}
		if (connection.localUid == Uid1)
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess Video"));
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = LocalVideo;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}

void UJoinMultipleChannelWidget::onLeaveChannel(const RtcConnection& connection, const RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}
		if (connection.localUid == Uid1)
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess Video"));
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}

void UJoinMultipleChannelWidget::onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}
		if (remoteUid != Uid1 && remoteUid != Uid2)
		{
			UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget::onUserJoined  uid: %d"), (int64)remoteUid);
			UserImageData ImageData = GetUImageNoData(remoteUid);
			if (ImageData.image == nullptr)
			{
				return;
			}
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = ImageData.image;
			videoCanvas.uid = remoteUid;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

			agora::rtc::RtcConnection connection;
			connection.channelId = ChannelName.c_str();

			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	});
}

void UJoinMultipleChannelWidget::onUserOffline(const RtcConnection& connection, uid_t remoteUid, USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("UJoinMultipleChannelWidget::onUserOffline  uid: %d"), (int64)remoteUid);
		UserImageData ImageData = RemoveUImageData(remoteUid);
		if (ImageData.image != nullptr)
		{
			ImageData.image->SetBrush(EmptyBrush);
		}
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = remoteUid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = ChannelName.c_str();

		if (RtcEngineProxy != nullptr)
		{
			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	});
}

UserImageData UJoinMultipleChannelWidget::GetUImageNoData(agora::rtc::uid_t uid) {

	UserImageData data;

	if (NotUseArray.Num() == 0)
	{
		return data;
	}
	for (int i = 0; i < UsedArray.Num(); i++)
	{
		if (UsedArray[i].uid == uid)
		{
			return data;
		}
	}
	for (int i = 0; i < NotUseArray.Num(); i++)
	{
		if (NotUseArray[i].uid == 0)
		{
			data = NotUseArray[i];

			data.uid = uid;

			UsedArray.Add(data);

			NotUseArray.Remove(data);

			return data;
		}
	}
	return data;
}

UserImageData UJoinMultipleChannelWidget::RemoveUImageData(agora::rtc::uid_t uid) {

	UserImageData data;

	if (UsedArray.Num() == 0)
	{
		return data;
	}

	for (int i = 0; i < UsedArray.Num(); i++)
	{
		if (UsedArray[i].uid == uid)
		{
			data = UsedArray[i];

			data.uid = 0;

			NotUseArray.Add(data);

			UsedArray.Remove(data);

			return data;
		}
	}
	return data;
}

void UJoinMultipleChannelWidget::InitUI()
{
	NotUseArray.Empty();

	NotUseArray.Add(UserImageData(remoteVideoUser1, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser2, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser3, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser4, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser5, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser6, 0));

	UsedArray.Empty();

	ProfileComboBox->AddOption("BROADCASTING");
	ProfileComboBox->AddOption("COMMUNICATION");

	ProfileComboBox->SetSelectedOption(FString("BROADCASTING"));

	ScenarioComboBox->AddOption("DEFAULT");
	ScenarioComboBox->AddOption("GAME_STREAMING");
	ScenarioComboBox->AddOption("CHATROOM");
	ScenarioComboBox->AddOption("CHORUS");
	ScenarioComboBox->AddOption("MEETING");
	ScenarioComboBox->AddOption("NUM");
	ScenarioComboBox->SetSelectedOption(FString("DEFAULT"));


	FPSComboBox->AddOption("5");
	FPSComboBox->AddOption("15");
	FPSComboBox->AddOption("24");
	FPSComboBox->AddOption("30");
	FPSComboBox->AddOption("60");
	FPSComboBox->SetSelectedOption(FString("15"));

	AgoraChannelProfileEnumMap.Add(FString("BROADCASTING"), CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING);
	AgoraChannelProfileEnumMap.Add(FString("COMMUNICATION"), CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);

	AgoraAudioScenarioEnumMap.Add(FString("DEFAULT"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	AgoraAudioScenarioEnumMap.Add(FString("GAME_STREAMING"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING);
	AgoraAudioScenarioEnumMap.Add(FString("CHATROOM"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHATROOM);
	AgoraAudioScenarioEnumMap.Add(FString("CHORUS"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHORUS);
	AgoraAudioScenarioEnumMap.Add(FString("MEETING"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_MEETING);
	AgoraAudioScenarioEnumMap.Add(FString("NUM"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_NUM);

}


void UJoinMultipleChannelWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (RtcEngineProxy!=nullptr)
	{
		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->unregisterEventHandler(this);
#if !PLATFORM_IOS
		RtcEngineProxy->stopScreenCapture();
#endif
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}
