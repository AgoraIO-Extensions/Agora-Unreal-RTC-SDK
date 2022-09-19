// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceManagerUserWidget.h"

void UDeviceManagerUserWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();
}


void UDeviceManagerUserWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) {

#if PLATFORM_ANDROID || PLATFORM_IOS
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::White, FString::Printf(TEXT("Not Support in this platform!")));
	return;
#endif
	agora::rtc::RtcEngineContext RtcEngineContext;
	RtcEngineContext.appId = TCHAR_TO_ANSI(*APP_ID);
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);

	RtcEngineProxy->queryInterface(AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&AudioDeviceManager);
	RtcEngineProxy->queryInterface(AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);
}

void UDeviceManagerUserWidget::SetUpUIEvent() {

	CallBtn->OnClicked.AddDynamic(this, &UDeviceManagerUserWidget::CallDeviceManagerApi);
	BackHomeBtn->OnClicked.AddDynamic(this, &UDeviceManagerUserWidget::BackHomeClick);
}

void UDeviceManagerUserWidget::CallDeviceManagerApi()
{
	GetAudioRecordingDevice();
	GetAudioPlaybackDevice();
	GetVideoDeviceManager();
	SetCurrentDevice();
	SetCurrentDeviceVolume();
}

void UDeviceManagerUserWidget::BackHomeClick()
{
	UClass* AgoraWidgetClass = LoadClass<UBaseAgoraUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/API-Example/Advance/MainWidgetManager.MainWidgetManager_C'"));

	UBaseAgoraUserWidget* AgoraWidget = CreateWidget<UBaseAgoraUserWidget>(GetWorld(), AgoraWidgetClass);

	AgoraWidget->AddToViewport();

	AgoraWidget->InitAgoraWidget(AppId,Token,ChannelName);

	this->RemoveFromViewport();
}

void UDeviceManagerUserWidget::GetAudioRecordingDevice()
{
	AudioRecordingDeviceInfos = AudioDeviceManager->enumerateRecordingDevices();

	if (AudioRecordingDeviceInfos!= nullptr)
	{
		int length = AudioRecordingDeviceInfos->getCount();
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::White, FString::Printf(TEXT("AudioRecordingDevice count: %d"), length));
		for (int i = 0; i < length; i++)
		{
			char deviceName[MAX_DEVICE_ID_LENGTH];
			char deviceId[MAX_DEVICE_ID_LENGTH];

			AudioRecordingDeviceInfos->getDevice(i, deviceName , deviceId);

			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::White, FString::Printf(TEXT("AudioRecordingDevice device index: %d, name: %s, id: %s"), i, UTF8_TO_TCHAR(deviceName), UTF8_TO_TCHAR(deviceId)));
		}
	}
}

void UDeviceManagerUserWidget::GetAudioPlaybackDevice()
{
	AudioPlaybackDeviceInfos = AudioDeviceManager->enumeratePlaybackDevices();
	if (AudioPlaybackDeviceInfos != nullptr)
	{
		int length = AudioPlaybackDeviceInfos->getCount();
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, FString::Printf(TEXT("AudioPlaybackDevice count: %d"), length));
		for (int i = 0; i < length; i++)
		{
			char deviceName[MAX_DEVICE_ID_LENGTH];
			char deviceId[MAX_DEVICE_ID_LENGTH];

			AudioPlaybackDeviceInfos->getDevice(i, deviceName, deviceId);

			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, FString::Printf(TEXT("AudioPlaybackDevice device index: %d, name: %s, id: %s"), i, UTF8_TO_TCHAR(deviceName), UTF8_TO_TCHAR(deviceId)));
		}
	}
}

void UDeviceManagerUserWidget::GetVideoDeviceManager()
{
	int nRet = RtcEngineProxy->startPreview();

	VideoDeviceInfos = VideoDeviceManager->enumerateVideoDevices();

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("StartPreview: nRet : %d"), nRet));

	if (VideoDeviceInfos != nullptr)
	{
		int length = VideoDeviceInfos->getCount();
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("VideoDeviceInfos count: %d"), length));
		for (int i = 0; i < length; i++)
		{
			char deviceName[MAX_DEVICE_ID_LENGTH];
			char deviceId[MAX_DEVICE_ID_LENGTH];

			VideoDeviceInfos->getDevice(i, deviceName, deviceId);

			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("VideoDeviceInfos device index: %d, name: %s, id: %s"), i, UTF8_TO_TCHAR(deviceName), UTF8_TO_TCHAR(deviceId)));
		}
	}
}

void UDeviceManagerUserWidget::SetCurrentDevice()
{
	if (AudioPlaybackDeviceInfos->getCount() > 0)
	{
		char deviceName[MAX_DEVICE_ID_LENGTH];
		char deviceId[MAX_DEVICE_ID_LENGTH];

		AudioRecordingDeviceInfos->getDevice(DEVICE_INDEX, deviceName, deviceId);

		AudioDeviceManager->setRecordingDevice(deviceId);
	}

	if (AudioPlaybackDeviceInfos->getCount() > 0)
	{
		char deviceName[MAX_DEVICE_ID_LENGTH];
		char deviceId[MAX_DEVICE_ID_LENGTH];

		AudioRecordingDeviceInfos->getDevice(DEVICE_INDEX, deviceName, deviceId);

		AudioDeviceManager->setPlaybackDevice(deviceId);

	}

	if (VideoDeviceInfos->getCount() > 0)
	{
		char deviceName[MAX_DEVICE_ID_LENGTH];
		char deviceId[MAX_DEVICE_ID_LENGTH];

		VideoDeviceInfos->getDevice(DEVICE_INDEX, deviceName, deviceId);

		int ret = VideoDeviceManager->setDevice(deviceId);

		UE_LOG(LogTemp, Warning, TEXT("SetDevice returns: %d"), ret);
	}

}

void UDeviceManagerUserWidget::SetCurrentDeviceVolume()
{
	AudioDeviceManager->setRecordingDeviceVolume(100);

	AudioDeviceManager->setPlaybackDeviceVolume(100);

}


void UDeviceManagerUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RtcEngineProxy!=nullptr)
	{
		AudioDeviceManager.reset(nullptr);
		VideoDeviceManager.reset(nullptr);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}

}

