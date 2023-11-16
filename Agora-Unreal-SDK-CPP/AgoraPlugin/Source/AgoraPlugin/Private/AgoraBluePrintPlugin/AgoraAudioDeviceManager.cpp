//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraAudioDeviceManager.h"
#include <string>

int UIAudioDeviceCollection::GetCount()
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->getCount();
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::GetDevice(int index, FString& deviceName, FString& deviceId)
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
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::SetDevice(FString deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		int ret = AudioDeviceCollection->setDevice(TCHAR_TO_UTF8(*deviceId));

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::GetDefaultDevice(FString& deviceName, FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceCollection->getDefaultDevice(tempDeviceName, tempDeviceId);

		std::string StdStrDeviceName = tempDeviceName;
		std::string StdStrDeviceId = tempDeviceId;

		deviceName = StdStrDeviceName.c_str();
		deviceId = StdStrDeviceId.c_str();

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::SetApplicationVolume(int volume)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->setApplicationVolume(volume);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::GetApplicationVolume(int volume)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->getApplicationVolume(volume);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::SetApplicationMute(bool mute)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->setApplicationMute(mute);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceCollection::IsApplicationMute(bool mute)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->isApplicationMute(mute);
	}
	return -ERROR_NULLPTR;
}
void UIAudioDeviceCollection::Release()
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->release();
	}
}
void UIAudioDeviceCollection::SetAudioDeviceCollection(agora::rtc::IAudioDeviceCollection* audioDeviceCollection)
{
	this->AudioDeviceCollection = audioDeviceCollection;
}
UIAudioDeviceCollection* UIAudioDeviceManager::EnumeratePlaybackDevices()
{
	if (AudioDeviceManager != nullptr)
	{
		if (playbackDevice == nullptr)
		{
			playbackDevice = NewObject<UIAudioDeviceCollection>();
		}

		playbackDevice->SetAudioDeviceCollection(AudioDeviceManager->enumeratePlaybackDevices());

		return playbackDevice;
	}
	return nullptr;
}
UIAudioDeviceCollection* UIAudioDeviceManager::EnumerateRecordingDevices()
{
	if (AudioDeviceManager != nullptr)
	{
		if (recordDevice == nullptr)
		{
			recordDevice = NewObject<UIAudioDeviceCollection>();
		}

		recordDevice->SetAudioDeviceCollection(AudioDeviceManager->enumerateRecordingDevices());

		return recordDevice;
	}
	return nullptr;
}
int UIAudioDeviceManager::SetPlaybackDevice(FString deviceId)
{
	if (AudioDeviceManager != nullptr)
	{
		int ret = AudioDeviceManager->setPlaybackDevice(TCHAR_TO_UTF8(*deviceId));

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetPlaybackDevice(FString& deviceId)
{
	if (AudioDeviceManager != nullptr)
	{
		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceManager->getPlaybackDevice(tempDeviceId);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetPlaybackDeviceInfo(FString& deviceId, FString& deviceName)
{
	if (AudioDeviceManager != nullptr)
	{

		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceManager->getPlaybackDeviceInfo(tempDeviceId, tempDeviceName);

		deviceName = UTF8_TO_TCHAR(tempDeviceName);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::SetPlaybackDeviceVolume(int volume)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->setPlaybackDeviceVolume(volume);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetPlaybackDeviceVolume(int& volume)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->getPlaybackDeviceVolume(&volume);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::SetRecordingDevice(FString deviceId)
{
	if (AudioDeviceManager != nullptr)
	{
		int ret = AudioDeviceManager->setRecordingDevice(TCHAR_TO_UTF8(*deviceId));

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetRecordingDevice(FString& deviceId)
{
	if (AudioDeviceManager != nullptr)
	{
		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceManager->getRecordingDevice(tempDeviceId);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetRecordingDeviceInfo(FString& deviceId, FString& deviceName)
{
	if (AudioDeviceManager != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceManager->getRecordingDeviceInfo(tempDeviceId, tempDeviceName);

		deviceName = UTF8_TO_TCHAR(tempDeviceName);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::SetRecordingDeviceVolume(int volume)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->setRecordingDeviceVolume(volume);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetRecordingDeviceVolume(int& volume)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->getRecordingDeviceVolume(&volume);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::SetPlaybackDeviceMute(bool mute)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->setPlaybackDeviceMute(mute);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetPlaybackDeviceMute(bool& mute)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->getPlaybackDeviceMute(&mute);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::SetRecordingDeviceMute(bool mute)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->setRecordingDeviceMute(mute);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::GetRecordingDeviceMute(bool& mute)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->getRecordingDeviceMute(&mute);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::StartPlaybackDeviceTest(FString testAudioFilePath)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->startPlaybackDeviceTest(TCHAR_TO_UTF8(*testAudioFilePath));
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::StopPlaybackDeviceTest()
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->stopPlaybackDeviceTest();
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::StartRecordingDeviceTest(int indicationInterval)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->startRecordingDeviceTest(indicationInterval);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::StopRecordingDeviceTest()
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->stopRecordingDeviceTest();
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::StartAudioDeviceLoopbackTest(int indicationInterval)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->startAudioDeviceLoopbackTest(indicationInterval);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::StopAudioDeviceLoopbackTest()
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->stopAudioDeviceLoopbackTest();
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::FollowSystemPlaybackDevice(bool enable)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->followSystemPlaybackDevice(enable);
	}
	return -ERROR_NULLPTR;
}
int UIAudioDeviceManager::FollowSystemRecordingDevice(bool enable)
{
	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->followSystemRecordingDevice(enable);
	}
	return -ERROR_NULLPTR;
}
void UIAudioDeviceManager::Release()
{
	playbackDevice = nullptr;
	recordDevice = nullptr;

	if (AudioDeviceManager != nullptr)
	{
		return AudioDeviceManager->release();
	}
}
void UIAudioDeviceManager::SetAudioDeviceManager(agora::rtc::IAudioDeviceManager* audioDeviceManager)
{
	this->AudioDeviceManager = audioDeviceManager;
}
