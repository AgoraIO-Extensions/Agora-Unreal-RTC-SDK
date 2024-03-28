//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/IVideoDeviceManager.h"

int UIVideoDeviceCollection::GetCount()
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceCollection != nullptr)
	{
		ret = VideoDeviceCollection->getCount();
	}
	return ret;
}
int UIVideoDeviceCollection::SetDevice(FString& deviceIdUTF8)
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceCollection != nullptr)
	{
		std::string STDdeviceIdUTF8 = TCHAR_TO_UTF8(*deviceIdUTF8);
		ret = VideoDeviceCollection->setDevice(STDdeviceIdUTF8.c_str());
	}
	return ret;
}
int UIVideoDeviceCollection::GetDevice(int index, FString& deviceNameUTF8, FString& deviceIdUTF8)
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		ret = VideoDeviceCollection->getDevice(index, tempDeviceName, tempDeviceId);

		deviceNameUTF8 = UTF8_TO_TCHAR(tempDeviceName);

		deviceIdUTF8 = UTF8_TO_TCHAR(tempDeviceId);
	}
	return ret;
}
void UIVideoDeviceCollection::Release()
{
	if (VideoDeviceCollection != nullptr)
	{
		VideoDeviceCollection->release();
	}
}
void UIVideoDeviceCollection::SetVideoDeviceCollection(agora::rtc::IVideoDeviceCollection* videoDeviceCollection)
{
	this->VideoDeviceCollection = videoDeviceCollection;
}
UIVideoDeviceCollection* UIVideoDeviceManager::EnumerateVideoDevices()
{
	if (VideoDeviceManager != nullptr)
	{
		if (deviceDevice == nullptr)
		{
			deviceDevice = NewObject<UIVideoDeviceCollection>();
		}

		deviceDevice->SetVideoDeviceCollection(VideoDeviceManager->enumerateVideoDevices());

		return deviceDevice;
	}
	return nullptr;
}
int UIVideoDeviceManager::SetDevice(FString deviceIdUTF8)
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceManager != nullptr)
	{
		std::string STDdeviceIdUTF8 = TCHAR_TO_UTF8(*deviceIdUTF8);
		ret = VideoDeviceManager->setDevice(STDdeviceIdUTF8.c_str());
	}
	return ret;
}
int UIVideoDeviceManager::GetDevice(FString& deviceIdUTF8)
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceManager != nullptr)
	{
		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		ret = VideoDeviceManager->getDevice(tempDeviceId);

		deviceIdUTF8 = UTF8_TO_TCHAR(tempDeviceId);
	}
	return ret;
}
int UIVideoDeviceManager::NumberOfCapabilities(FString deviceIdUTF8)
{
	int ret = -ERROR_NULLPTR;
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (VideoDeviceManager != nullptr)
	{
		std::string STDdeviceIdUTF8 = TCHAR_TO_UTF8(*deviceIdUTF8);
		ret = VideoDeviceManager->numberOfCapabilities(STDdeviceIdUTF8.c_str());
	}
#endif
	return ret;
}
int UIVideoDeviceManager::GetCapability(FString deviceIdUTF8, int deviceCapabilityNumber, FVideoFormat& capability)
{
	int ret = -ERROR_NULLPTR;
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

	if (VideoDeviceManager != nullptr)
	{
		agora::rtc::VideoFormat videoFormat = capability.CreateAgoraData();
		std::string STDdeviceIdUTF8 = TCHAR_TO_UTF8(*deviceIdUTF8);

		ret = VideoDeviceManager->getCapability(STDdeviceIdUTF8.c_str(), deviceCapabilityNumber, videoFormat);

		capability.FreeAgoraData(videoFormat);
	}
#endif
	return ret;
}
int UIVideoDeviceManager::StartDeviceTest(int64 hwnd)
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceManager != nullptr)
	{
		ret = VideoDeviceManager->startDeviceTest((agora::view_t)hwnd);
	}
	return ret;
}
int UIVideoDeviceManager::StopDeviceTest()
{
	int ret = -ERROR_NULLPTR;
	if (VideoDeviceManager != nullptr)
	{
		ret = VideoDeviceManager->stopDeviceTest();
	}
	return ret;
}
void UIVideoDeviceManager::Release()
{
	deviceDevice = nullptr;
	if (VideoDeviceManager != nullptr)
	{
		VideoDeviceManager->release();
	}
}
void UIVideoDeviceManager::SetVideoDeviceManager(agora::rtc::IVideoDeviceManager* videoDeviceManager)
{
	this->VideoDeviceManager = videoDeviceManager;
}

agora::rtc::IVideoDeviceManager* UIVideoDeviceManager::GetVideoDeviceManager()
{
	return VideoDeviceManager;
}

