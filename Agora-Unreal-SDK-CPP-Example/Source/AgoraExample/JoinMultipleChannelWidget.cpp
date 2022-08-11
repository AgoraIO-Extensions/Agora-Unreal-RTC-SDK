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

#if PLATFORM_ANDROID
	StartScreenShrareClick();
#endif
}

void UJoinMultipleChannelWidget::SetUpUIEvent()
{
	StartScreenShrareBtn->SetVisibility(ESlateVisibility::Collapsed);
#if PLATFORM_WINDOWS || PLATFORM_MAC
	StartScreenShrareBtn->OnClicked.AddDynamic(this, &UJoinMultipleChannelWidget::StartScreenShrareClick);
	StartScreenShrareBtn->SetVisibility(ESlateVisibility::Visible);
#endif
	JoinBtn->OnClicked.AddDynamic(this, &UJoinMultipleChannelWidget::JoinChannelClick);
	BackHomeBtn->OnClicked.AddDynamic(this, &UJoinMultipleChannelWidget::BackHomeClick);
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

void UJoinMultipleChannelWidget::BackHomeClick()
{
	UClass* AgoraWidgetClass = LoadClass<UBaseAgoraUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/API-Example/Advance/MainWidgetManager.MainWidgetManager_C'"));

	UBaseAgoraUserWidget* AgoraWidget = CreateWidget<UBaseAgoraUserWidget>(GetWorld(), AgoraWidgetClass);

	AgoraWidget->AddToViewport();

	AgoraWidget->InitAgoraWidget(FString(AppID.c_str()), FString(Token.c_str()), FString(ChannelName.c_str()));

	this->RemoveFromViewport();
}

void UJoinMultipleChannelWidget::StartScreenShrareClick()
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


void UJoinMultipleChannelWidget::JoinChannelClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnJoinButtonClick ======"));

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
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget JoinChannel ======"));
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
		if (connection.localUid == Uid1)
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess Video"));
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = LocalVideo;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
		else if (connection.localUid == Uid2)
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess ScreenShare"));
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = ScreenShareVideo;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_SCREEN;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
		
	});
}

void UJoinMultipleChannelWidget::onLeaveChannel(const RtcConnection& connection, const RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (connection.localUid == Uid1)
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess Video"));
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
		else if (connection.localUid == Uid2)
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess ScreenShare"));
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = nullptr;
			videoCanvas.uid = 0;
			videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_SCREEN;
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}

void UJoinMultipleChannelWidget::onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (remoteUid != Uid1 && remoteUid != Uid2)
		{
			agora::rtc::VideoCanvas videoCanvas;
			videoCanvas.view = remoteVideo;
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
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onUserOffline  uid: %u"), remoteUid);
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

void UJoinMultipleChannelWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (RtcEngineProxy!=nullptr)
	{
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}
