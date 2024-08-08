//  Copyright (c) 2024 Agora.io. All rights reserved.

#include "AgoraBPuDeviceManager.h"
#include "AgoraHeaderBase.h"
#include "UtilityAgoraBPuLogger.h"


UAgoraBPuVideoDeviceManager* UAgoraBPuVideoDeviceManager::Instance = nullptr;

UAgoraBPuAudioDeviceManager* UAgoraBPuAudioDeviceManager::Instance = nullptr;


UAgoraBPuVideoDeviceManager* UAgoraBPuVideoDeviceManager::GetAgoraVideoDeviceManager()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UAgoraBPuVideoDeviceManager>();
		Instance->AddToRoot();
		AgoraUERtcEngine::Get()->queryInterface(agora::rtc::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&Instance->VideoDeviceManager);

		if (Instance->VideoDeviceManager == nullptr) {

			UAgoraBPuLogger::PrintError("VideoDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

			Instance->VideoDeviceCollection = nullptr;
		}
		else{
		
			Instance->VideoDeviceCollection = NewObject<UVideoDeviceCollection>();
		
		}
	}
	return Instance;
}

void UAgoraBPuVideoDeviceManager::Release()
{
	if (Instance)
	{
		if(Instance->VideoDeviceCollection){
			Instance->VideoDeviceCollection->Release();
			Instance->VideoDeviceCollection = nullptr;
		}
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}


UVideoDeviceCollection* UAgoraBPuVideoDeviceManager::EnumerateVideoDevices()
{
	if (VideoDeviceManager == nullptr) {

		UAgoraBPuLogger::PrintError("VideoDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	if (VideoDeviceCollection != nullptr) {
		VideoDeviceCollection->Release();
	}

	agora::rtc::IVideoDeviceCollection* VideoCollection = VideoDeviceManager->enumerateVideoDevices();
	if (VideoCollection == nullptr) {

		UAgoraBPuLogger::PrintError("VideoCollection is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	VideoDeviceCollection->Init(VideoCollection);

	return VideoDeviceCollection;
}

UAgoraBPuAudioDeviceManager* UAgoraBPuAudioDeviceManager::GetAgoraAudioDeviceManager()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UAgoraBPuAudioDeviceManager>();
		Instance->AddToRoot();
		AgoraUERtcEngine::Get()->queryInterface(agora::rtc::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&Instance->AudioDeviceManager);

		if(Instance->AudioDeviceManager == nullptr){
		
			UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		}


		Instance->PlaybackDeviceCollection = NewObject<UAudioDeviceCollection>();

		Instance->RecordDeviceCollection = NewObject<UAudioDeviceCollection>();
	}
	return Instance;
}

void UAgoraBPuAudioDeviceManager::Release()
{
	if (Instance)
	{
		if (Instance->PlaybackDeviceCollection) {
			Instance->PlaybackDeviceCollection->Release();
			Instance->PlaybackDeviceCollection = nullptr;
		}

		if (Instance->RecordDeviceCollection) {
			Instance->RecordDeviceCollection->Release();
			Instance->RecordDeviceCollection = nullptr;
		}

		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}

UAudioDeviceCollection* UAgoraBPuAudioDeviceManager::EnumeratePlaybackDevices()
{
	if (AudioDeviceManager == nullptr) {
		UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);
		return nullptr;
	}

	if(PlaybackDeviceCollection != nullptr){
		PlaybackDeviceCollection->Release();
	}


	agora::rtc::IAudioDeviceCollection* AudioCollection = AudioDeviceManager->enumeratePlaybackDevices();
	if (AudioCollection == nullptr) {

		UAgoraBPuLogger::PrintError("AudioCollection is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	PlaybackDeviceCollection->Init(AudioCollection);

	return PlaybackDeviceCollection;
}

UAudioDeviceCollection* UAgoraBPuAudioDeviceManager::EnumerateRecordingDevices()
{
	if (AudioDeviceManager == nullptr) {

		UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	if (RecordDeviceCollection != nullptr) {
		RecordDeviceCollection->Release();
	}



	agora::rtc::IAudioDeviceCollection* AudioCollection = AudioDeviceManager->enumerateRecordingDevices();
	if (AudioCollection == nullptr) {

		UAgoraBPuLogger::PrintError("AudioCollection is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	RecordDeviceCollection->Init(AudioCollection);

	return RecordDeviceCollection;
}

void UVideoDeviceCollection::Init(agora::rtc::IVideoDeviceCollection* VideoCollectionPtr)
{
	VideoDeviceCollection = VideoCollectionPtr;
}

int UVideoDeviceCollection::GetCount()
{
	if (VideoDeviceCollection != nullptr)
	{
		
		return VideoDeviceCollection->getCount();

	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UVideoDeviceCollection::SetDevice(const FString& deviceId)
{
	if (VideoDeviceCollection != nullptr)
	{
		std::string DeviceIdStr = TCHAR_TO_UTF8(*deviceId);
		return VideoDeviceCollection->setDevice(DeviceIdStr.c_str());
	
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UVideoDeviceCollection::GetDevice(int index, FString& deviceName, FString& deviceId)
{
	if (VideoDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = VideoDeviceCollection->getDevice(index, tempDeviceName, tempDeviceId);

		std::string StdStrDeviceName = tempDeviceName;
		std::string StdStrDeviceId = tempDeviceId;

		deviceName = StdStrDeviceName.c_str();
		deviceId = StdStrDeviceId.c_str();

		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

void UVideoDeviceCollection::Release()
{
	if (VideoDeviceCollection != nullptr)
	{
		return VideoDeviceCollection->release();
	}
}

void UAudioDeviceCollection::Init(agora::rtc::IAudioDeviceCollection* AudioCollectionPtr)
{
	AudioDeviceCollection = AudioCollectionPtr;
}

int UAudioDeviceCollection::GetCount()
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->getCount();
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::GetDevice(int index, FString& deviceName, FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceCollection->getDevice(index, tempDeviceName, tempDeviceId);


		deviceName = UTF8_TO_TCHAR(tempDeviceName);
		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::SetDevice(const FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		std::string DeviceIdStr = TCHAR_TO_UTF8(*deviceId);
		return AudioDeviceCollection->setDevice(DeviceIdStr.c_str());
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::GetDefaultDevice(FString& deviceName, FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceCollection->getDefaultDevice(tempDeviceName, tempDeviceId);

		deviceName = UTF8_TO_TCHAR(tempDeviceName);
		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::SetApplicationVolume(int volume)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->setApplicationVolume(volume);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::GetApplicationVolume(int & volume)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->getApplicationVolume(volume);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::SetApplicationMute(bool mute)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->setApplicationMute(mute);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::IsApplicationMute(bool mute)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->isApplicationMute(mute);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

void UAudioDeviceCollection::Release()
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->release();
	}
}
