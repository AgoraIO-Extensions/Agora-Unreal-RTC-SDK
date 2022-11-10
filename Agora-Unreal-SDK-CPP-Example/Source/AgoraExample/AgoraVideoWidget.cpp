// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraVideoWidget.h"

void UAgoraVideoWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID,TOKEN,CHANNEL_NAME);

	SetUpUIEvent();

	InitUI();
	
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
	ConfirmBtn->OnClicked.AddDynamic(this, &UAgoraVideoWidget::OnConfirmButtonClick);
}

void UAgoraVideoWidget::OnConfirmButtonClick() {

	int ret = RtcEngineProxy->setChannelProfile(AgoraChannelProfileEnumMap[ProfileComboBox->GetSelectedOption()]);
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setChannelProfile ret: %d ChannelProfile : %s"), ret,*ProfileComboBox->GetSelectedOption());

	ret =RtcEngineProxy->setAudioScenario(AgoraAudioScenarioEnumMap[ScenarioComboBox->GetSelectedOption()]);
	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget setAudioScenario ret: %d AudioScenario : %s"), ret,*ScenarioComboBox->GetSelectedOption());

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

void UAgoraVideoWidget::OnJoinButtonClick() {

	UE_LOG(LogTemp, Warning, TEXT("UVideoWidget OnJoinButtonClick ======"));
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

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

	RtcEngineProxy->leaveChannel();
	for (int i = 0; i < NotUseArray.Num(); i++)
	{
		NotUseArray[i].image->SetBrush(EmptyBrush);
	}
	for (int i = 0; i < UsedArray.Num(); i++)
	{
		UsedArray[i].image->SetBrush(EmptyBrush);
	}
	localVideo->SetBrush(EmptyBrush);
	NotUseArray.Empty();
	UsedArray.Empty();
	InitUI();
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
		UserImageData ImageData= GetUImageNoData(uid);

		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = ImageData.image;
		videoCanvas.uid = uid;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

		agora::rtc::RtcConnection connection;
		connection.channelId = ChannelName.c_str();

		((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
	});
}

void UAgoraVideoWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
		connection.channelId = ChannelName.c_str();

		if (RtcEngineProxy != nullptr)
		{
			((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	});
}

void UAgoraVideoWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoWidget::onLeaveChannel"));
		agora::rtc::VideoCanvas videoCanvas;
		videoCanvas.view = nullptr;
		videoCanvas.uid = 0;
		videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
		if (RtcEngineProxy != nullptr)
		{
			RtcEngineProxy->setupLocalVideo(videoCanvas);
		}
	});
}
#pragma endregion RtcEngineCallBack


UserImageData UAgoraVideoWidget::GetUImageNoData(agora::rtc::uid_t uid)
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

UserImageData UAgoraVideoWidget::RemoveUImageData(agora::rtc::uid_t uid)
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

void UAgoraVideoWidget::InitUI()
{
	NotUseArray.Empty();

	NotUseArray.Add(UserImageData(remoteVideoUser1, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser2, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser3, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser4, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser5, 0));
	NotUseArray.Add(UserImageData(remoteVideoUser6, 0));

	UsedArray.Empty();

	ProfileComboBox->AddOption("Broadcaster");
	ProfileComboBox->AddOption("Audience");

	ProfileComboBox->SetSelectedOption(FString("Broadcaster"));

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

	AgoraChannelProfileEnumMap.Add(FString("Broadcaster"),CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING);
	AgoraChannelProfileEnumMap.Add(FString("Audience"), CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);

	AgoraAudioScenarioEnumMap.Add(FString("DEFAULT"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	AgoraAudioScenarioEnumMap.Add(FString("GAME_STREAMING"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING);
	AgoraAudioScenarioEnumMap.Add(FString("CHATROOM"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHATROOM);
	AgoraAudioScenarioEnumMap.Add(FString("CHORUS"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHORUS);
	AgoraAudioScenarioEnumMap.Add(FString("MEETING"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_MEETING);
	AgoraAudioScenarioEnumMap.Add(FString("NUM"), AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_NUM);
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