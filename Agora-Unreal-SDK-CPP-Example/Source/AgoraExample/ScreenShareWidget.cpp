// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenShareWidget.h"
#include "Math/UnrealMathUtility.h"

void UScreenShareWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
#if PLATFORM_ANDROID || PLATFORM_IOS
#if PLATFORM_ANDROID
	CheckAndroidPermission();
#endif
	ComboBoxDisplayId->SetVisibility(ESlateVisibility::Collapsed);
#endif

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();

	InitUI();
	/*this get all windows in you devices ,you can move this to other position. 
	this code may freeze,you can move this to button click */
#if PLATFORM_WINDOWS || PLATFORM_MAC
	GetScreenDisplayId();
#endif
}

void UScreenShareWidget::SetUpUIEvent()
{
	ScreenShareBtn->OnClicked.AddDynamic(this, &UScreenShareWidget::StartScreenShrareClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UScreenShareWidget::OnLeaveButtonClick);
	ConfirmBtn->OnClicked.AddDynamic(this, &UScreenShareWidget::OnConfirmButtonClick);
}


void UScreenShareWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;
	RtcEngineContext.appId = TCHAR_TO_ANSI(*APP_ID);
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	auto ret = RtcEngineProxy->initialize(RtcEngineContext);

	UE_LOG(LogTemp, Warning, TEXT("InitAgoraEngine ====== %d"), ret);
}

void UScreenShareWidget::UpdateChannelMediaOptions()
{
	agora::rtc::ChannelMediaOptions options;
	options.autoSubscribeAudio = true;
	options.autoSubscribeVideo = true;
	options.publishCameraTrack = false;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	options.publishScreenTrack = true;
#elif PLATFORM_ANDROID || PLATFORM_IOS
	options.publishScreenCaptureAudio = true;
	options.publishScreenCaptureVideo = true;
#endif
	options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;

	RtcEngineProxy->updateChannelMediaOptions(options);
}


void UScreenShareWidget::JoinChannel() {
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget JoinChannel ======"));

	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	auto ret = RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName),"",0);
}

void UScreenShareWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnLeaveButtonClick ======"));

	RtcEngineProxy->stopScreenCapture();

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

void UScreenShareWidget::StartScreenShrareClick()
{    
#if PLATFORM_ANDROID || PLATFORM_IOS
	ScreenCaptureParameters2 parameters2;
	parameters2.captureAudio = true;
	parameters2.captureVideo = true;
	auto ret = RtcEngineProxy->startScreenCapture(parameters2);
	UE_LOG(LogTemp, Warning, TEXT("StartScreenShrareClick JoinChannel ====== %d"),ret);
#else
	RtcEngineProxy->stopScreenCapture();
	agora::rtc::ScreenCaptureParameters capParam;
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
	UpdateChannelMediaOptions();
	JoinChannel();
}



void UScreenShareWidget::GetScreenDisplayId()
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

	ComboBoxDisplayId->OnSelectionChanged.AddDynamic(this, &UScreenShareWidget::SelectValueCallBack);

	if (infos != nullptr && infos->getCount() > 0)
	{
		ComboBoxDisplayId->SetSelectedIndex(0);
		SelectDisplayId = 0;
	}
#endif
}
void UScreenShareWidget::SelectValueCallBack(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	UE_LOG(LogTemp, Warning, TEXT("Screen Callpture"));
	if (ComboBoxDisplayId != nullptr)
	{
		SelectDisplayId = ComboBoxDisplayId->FindOptionIndex(SelectedItem);
	}
}
#pragma region RtcEngineCallBack

void UScreenShareWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess"));
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = LocalVideo;
		videoCanvas.uid = 0;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_SCREEN;
		RtcEngineProxy->setupLocalVideo(videoCanvas);
	});
}

void UScreenShareWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = 0;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_SCREEN;
		if (RtcEngineProxy != nullptr)
		{
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}

void UScreenShareWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserJoined  uid: %u"), uid);
		UserImageData ImageData = GetUImageNoData(uid);

		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = ImageData.image;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = TCHAR_TO_ANSI(*ChannelName);

		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	});
}

void UScreenShareWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserOffline  uid: %u"), uid);
		UserImageData ImageData = RemoveUImageData(uid);
		ImageData.image->SetBrush(EmptyBrush);
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = TCHAR_TO_ANSI(*ChannelName);

		if (RtcEngineProxy != nullptr)
		{
			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	});
}
#pragma endregion RtcEngineCallBack
void UScreenShareWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RtcEngineProxy!=nullptr)
	{
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}


void UScreenShareWidget::OnConfirmButtonClick()
{
	int ret = RtcEngineProxy->setAudioScenario(AgoraAudioScenarioEnumMap[ScenarioComboBox->GetSelectedOption()]);
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setAudioScenario ret: %d AudioScenario : %s"), ret, *ScenarioComboBox->GetSelectedOption());

	VideoEncoderConfiguration videoEncoderConfiguration;
	videoEncoderConfiguration.frameRate = FCString::Atoi(*FPSComboBox->GetSelectedOption());
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget frameRate ======%s"), *FPSComboBox->GetSelectedOption());

	VideoDimensions videoDimensions(FCString::Atoi(*WidthTextBox->GetText().ToString()), FCString::Atoi(*HeightTextBox->GetText().ToString()));
	videoEncoderConfiguration.dimensions = videoDimensions;
	videoEncoderConfiguration.bitrate = FCString::Atoi(*BitRateTextBox->GetText().ToString());
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget Width:%d Height:%d"), FCString::Atoi(*WidthTextBox->GetText().ToString()), FCString::Atoi(*HeightTextBox->GetText().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget Bitrate %d"), FCString::Atoi(*BitRateTextBox->GetText().ToString()));

	ret = RtcEngineProxy->setVideoEncoderConfiguration(videoEncoderConfiguration);

	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setVideoEncoderConfiguration ret %d"), ret);
}

UserImageData UScreenShareWidget::GetUImageNoData(agora::rtc::uid_t uid)
{
	UserImageData data;

	if (NotUseArray.Num() == 0)
	{
		return data;
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

UserImageData UScreenShareWidget::RemoveUImageData(agora::rtc::uid_t uid)
{
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

			UsedArray[i].uid = 0;

			NotUseArray.Add(data);

			UsedArray.Remove(data);

			return data;
		}
	}
	return data;
}

void UScreenShareWidget::InitUI()
{
	NotUseArray.Empty();

	NotUseArray.Add(UserImageData(remoteVideoUser1, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser2, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser3, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser4, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser5, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser6, 0));

	UsedArray.Empty();

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

	AgoraChannelProfileEnumMap.Add(FString("Broadcaster"), CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING);
	AgoraChannelProfileEnumMap.Add(FString("Audience"), CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);

	AgoraAudioScenarioEnumMap.Add(FString("DEFAULT"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	AgoraAudioScenarioEnumMap.Add(FString("GAME_STREAMING"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING);
	AgoraAudioScenarioEnumMap.Add(FString("CHATROOM"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHATROOM);
	AgoraAudioScenarioEnumMap.Add(FString("CHORUS"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHORUS);
	AgoraAudioScenarioEnumMap.Add(FString("MEETING"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_MEETING);
	AgoraAudioScenarioEnumMap.Add(FString("NUM"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_NUM);
}


void UScreenShareWidget::CheckAndroidPermission()
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
