// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceManagerUserWidget.h"


void UDeviceManagerUserWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	CallDeviceManagerApi();
}


void UDeviceManagerUserWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandler = MakeShared<FUserRtcEventHandler>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandler.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngineEx();

	int SDKBuild = 0;
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);


	RtcEngineProxy->queryInterface(AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&AudioDeviceManager);
	RtcEngineProxy->queryInterface(AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);
}

void UDeviceManagerUserWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [DeviceManager]\n"
		"1. It will show your recording and playback devices.\n"
		"2. IOS/Android is not supported, but you could see how it works on the Editor for Windows/MacOS.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UDeviceManagerUserWidget::CallDeviceManagerApi()
{
	GetAudioRecordingDevice();
	GetAudioPlaybackDevice();
	GetVideoDeviceManager();
	SetCurrentDevice();
	SetCurrentDeviceVolume();
}

void UDeviceManagerUserWidget::GetAudioRecordingDevice()
{
	AudioRecordingDeviceInfos = AudioDeviceManager->enumerateRecordingDevices();

	if (AudioRecordingDeviceInfos != nullptr)
	{
		int length = AudioRecordingDeviceInfos->getCount();

		UBFL_Logger::Print(FString::Printf(TEXT("%s AudioRecordingDeviceInfos count: %d"), *FString(FUNCTION_MACRO), length), LogMsgViewPtr);

		for (int i = 0; i < length; i++)
		{
			char deviceName[MAX_DEVICE_ID_LENGTH];
			char deviceId[MAX_DEVICE_ID_LENGTH];

			AudioRecordingDeviceInfos->getDevice(i, deviceName, deviceId);

			UBFL_Logger::Print(FString::Printf(TEXT("%s device index: %d, name: %s, id: %s"), *FString(FUNCTION_MACRO), i, UTF8_TO_TCHAR(deviceName), UTF8_TO_TCHAR(deviceId)), LogMsgViewPtr);
		}
	}
}

void UDeviceManagerUserWidget::GetAudioPlaybackDevice()
{
	AudioPlaybackDeviceInfos = AudioDeviceManager->enumeratePlaybackDevices();
	if (AudioPlaybackDeviceInfos != nullptr)
	{
		int length = AudioPlaybackDeviceInfos->getCount();
		UBFL_Logger::Print(FString::Printf(TEXT("%s AudioPlaybackDeviceInfos count: %d"), *FString(FUNCTION_MACRO), length), LogMsgViewPtr);

		for (int i = 0; i < length; i++)
		{
			char deviceName[MAX_DEVICE_ID_LENGTH];
			char deviceId[MAX_DEVICE_ID_LENGTH];

			AudioPlaybackDeviceInfos->getDevice(i, deviceName, deviceId);

			UBFL_Logger::Print(FString::Printf(TEXT("%s device index: %d, name: %s, id: %s"), *FString(FUNCTION_MACRO), i, UTF8_TO_TCHAR(deviceName), UTF8_TO_TCHAR(deviceId)), LogMsgViewPtr);
		}
	}
}

void UDeviceManagerUserWidget::GetVideoDeviceManager()
{
	int ret = RtcEngineProxy->startPreview();
	UBFL_Logger::Print(FString::Printf(TEXT("%s startPreview ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);


	VideoDeviceInfos = VideoDeviceManager->enumerateVideoDevices();

	if (VideoDeviceInfos != nullptr)
	{
		int length = VideoDeviceInfos->getCount();
		UBFL_Logger::Print(FString::Printf(TEXT("%s VideoDeviceInfos count: %d"), *FString(FUNCTION_MACRO), length), LogMsgViewPtr);

		for (int i = 0; i < length; i++)
		{
			char deviceName[MAX_DEVICE_ID_LENGTH];
			char deviceId[MAX_DEVICE_ID_LENGTH];

			VideoDeviceInfos->getDevice(i, deviceName, deviceId);

			UBFL_Logger::Print(FString::Printf(TEXT("%s device index: %d, name: %s, id: %s"), *FString(FUNCTION_MACRO), i, UTF8_TO_TCHAR(deviceName), UTF8_TO_TCHAR(deviceId)), LogMsgViewPtr);
		}
	}
}



void UDeviceManagerUserWidget::SetCurrentDevice()
{
	int DEVICE_INDEX = 0;
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

		UBFL_Logger::Print(FString::Printf(TEXT("%s setDevice ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	}

}

void UDeviceManagerUserWidget::SetCurrentDeviceVolume()
{
	AudioDeviceManager->setRecordingDeviceVolume(100);

	AudioDeviceManager->setPlaybackDeviceVolume(100);
}

void UDeviceManagerUserWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UDeviceManagerUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}


void UDeviceManagerUserWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		AudioRecordingDeviceInfos->release();
		AudioPlaybackDeviceInfos->release();
		VideoDeviceInfos->release();
		AudioDeviceManager->release();
		VideoDeviceManager->release();
		RtcEngineProxy->stopPreview();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandler.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}
