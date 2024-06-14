//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "URtcEngineProxyCompatibility.h"
#include "AgoraCppPlugin/IAgoraRtcEngine.h"
#include "IVideoDeviceManager.generated.h"

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIVideoDeviceCollection : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	int GetCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	int SetDevice(FString& deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	int GetDevice(int index, FString& deviceNameUTF8, FString& deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	void Release();
	void SetVideoDeviceCollection(agora::rtc::IVideoDeviceCollection* videoDeviceCollection);
private:
	agora::rtc::IVideoDeviceCollection* VideoDeviceCollection;
};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIVideoDeviceManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	UIVideoDeviceCollection* EnumerateVideoDevices();
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int SetDevice(FString deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int GetDevice(FString& deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int NumberOfCapabilities(FString deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int GetCapability(FString deviceIdUTF8, int deviceCapabilityNumber, FVideoFormat& capability);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int StartDeviceTest(int64 hwnd);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int StopDeviceTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	void Release();
	void SetVideoDeviceManager(agora::rtc::IVideoDeviceManager* videoDeviceManager);
	agora::rtc::IVideoDeviceManager* GetVideoDeviceManager();
private:
	agora::rtc::IVideoDeviceManager* VideoDeviceManager;
	UIVideoDeviceCollection* deviceDevice;
};
