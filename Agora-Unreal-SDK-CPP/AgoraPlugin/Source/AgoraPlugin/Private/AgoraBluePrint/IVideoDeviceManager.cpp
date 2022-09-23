// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrint/IVideoDeviceManager.h"

int UIVideoDeviceCollection::GetCount()
{
	if (VideoDeviceCollection != nullptr)
	{
		return VideoDeviceCollection->getCount();
	}
	return -ERROR_NULLPTR;
}
int UIVideoDeviceCollection::SetDevice(FString& deviceIdUTF8)
{
	if (VideoDeviceCollection != nullptr)
	{
		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		sprintf(tempDeviceId,"%s", TCHAR_TO_UTF8(*deviceIdUTF8));

		int ret = VideoDeviceCollection->setDevice(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIVideoDeviceCollection::GetDevice(int index, FString& deviceNameUTF8, FString& deviceIdUTF8)
{
	if (VideoDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = VideoDeviceCollection->getDevice(index, tempDeviceName, tempDeviceId);

		deviceNameUTF8 = UTF8_TO_TCHAR(tempDeviceName);

		deviceIdUTF8 = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
void UIVideoDeviceCollection::Release()
{
	if (VideoDeviceCollection != nullptr)
	{
		return VideoDeviceCollection->release();
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
	if (VideoDeviceManager != nullptr)
	{
		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		sprintf(tempDeviceId, "%s", TCHAR_TO_UTF8(*deviceIdUTF8));

		int ret = VideoDeviceManager->setDevice(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIVideoDeviceManager::GetDevice(FString& deviceIdUTF8)
{
	if (VideoDeviceManager != nullptr)
	{
		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = VideoDeviceManager->getDevice(tempDeviceId);

		deviceIdUTF8 = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}
	return -ERROR_NULLPTR;
}
int UIVideoDeviceManager::NumberOfCapabilities(FString deviceIdUTF8)
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (VideoDeviceManager != nullptr)
	{
		return VideoDeviceManager->numberOfCapabilities(TCHAR_TO_ANSI(*deviceIdUTF8));
	}
#endif
	return -ERROR_NULLPTR;
}
int UIVideoDeviceManager::GetCapability(FString deviceIdUTF8, int deviceCapabilityNumber, FVideoFormat& capability)
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::VideoFormat videoFormat;
	videoFormat.width = capability.width;
	videoFormat.height = capability.height;
	videoFormat.fps = capability.fps;
	if (VideoDeviceManager != nullptr)
	{
		return VideoDeviceManager->getCapability(TCHAR_TO_ANSI(*deviceIdUTF8), deviceCapabilityNumber, videoFormat);
	}
#endif
	return -ERROR_NULLPTR;
}
int UIVideoDeviceManager::StartDeviceTest(int64 hwnd)
{
	if (VideoDeviceManager != nullptr)
	{
		return VideoDeviceManager->startDeviceTest((agora::view_t)hwnd);
	}
	return -ERROR_NULLPTR;
}
int UIVideoDeviceManager::StopDeviceTest()
{
	if (VideoDeviceManager != nullptr)
	{
		return VideoDeviceManager->stopDeviceTest();
	}
	return -ERROR_NULLPTR;
}
void UIVideoDeviceManager::Release()
{
	deviceDevice = nullptr;
	if (VideoDeviceManager != nullptr)
	{
		return VideoDeviceManager->release();
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

