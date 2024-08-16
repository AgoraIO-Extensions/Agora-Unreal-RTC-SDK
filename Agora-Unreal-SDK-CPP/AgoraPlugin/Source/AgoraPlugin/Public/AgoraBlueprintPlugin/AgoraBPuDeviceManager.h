//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "AgoraPluginInterface.h"
#include "AgoraBPuBaseDataTypes.h"


#include "AgoraBPuDeviceManager.generated.h"

UCLASS(Blueprintable)
class AGORAPLUGIN_API UVideoDeviceCollection : public UObject
{
	GENERATED_BODY()

public:
	void Init(agora::rtc::IVideoDeviceCollection* VideoCollectionPtr);

	
	UFUNCTION(BlueprintPure, Category = "Agora|IVideoDeviceCollection")
	int GetCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	int SetDevice(const FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	int GetDevice(int index, FString& deviceName, FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceCollection")
	void Release();

private:
	agora::rtc::IVideoDeviceCollection* VideoDeviceCollection;
};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UAudioDeviceCollection : public UObject
{
	GENERATED_BODY()

public:
	void Init(agora::rtc::IAudioDeviceCollection* AudioCollectionPtr);



	UFUNCTION(BlueprintPure, Category = "Agora|IAudioDeviceCollection")
	int GetCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetDevice(int index, FString& deviceName, FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int SetDevice(const FString & deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetDefaultDevice(FString& deviceName, FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int SetApplicationVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetApplicationVolume(int & volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int SetApplicationMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int IsApplicationMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	void Release();
private:
	agora::rtc::IAudioDeviceCollection* AudioDeviceCollection;

};



UCLASS()
class AGORAPLUGIN_API UAgoraBPuVideoDeviceManager : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Agora|IVideoDeviceManager")
	static UAgoraBPuVideoDeviceManager* GetAgoraVideoDeviceManager();

	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	void Release();

	
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	UVideoDeviceCollection* EnumerateVideoDevices();


	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int SetDevice(const FString & deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int GetDevice(FString& deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int NumberOfCapabilities(const FString & deviceIdUTF8);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int GetCapability(const FString & deviceIdUTF8, int deviceCapabilityNumber, FVideoFormat& capability);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int StartDeviceTest(int64 hwnd);
	UFUNCTION(BlueprintCallable, Category = "Agora|IVideoDeviceManager")
	int StopDeviceTest();

private:

	static UAgoraBPuVideoDeviceManager* Instance;

	agora::rtc::IVideoDeviceManager* VideoDeviceManager;

	UPROPERTY()
	UVideoDeviceCollection* VideoDeviceCollection = nullptr;
};



UCLASS()
class AGORAPLUGIN_API UAgoraBPuAudioDeviceManager : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Agora|IAudioDeviceManager")
	static UAgoraBPuAudioDeviceManager* GetAgoraAudioDeviceManager();

	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	void Release();

	
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	UAudioDeviceCollection* EnumeratePlaybackDevices();

	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	UAudioDeviceCollection* EnumerateRecordingDevices();





	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetPlaybackDevice(const FString & deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDevice(FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDeviceInfo(FString& deviceId, FString& deviceName, FString& deviceTypeName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetPlaybackDeviceVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDeviceVolume(int& volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetRecordingDevice(const FString & deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDevice(FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDeviceInfo(FString& deviceId, FString& deviceName, FString& deviceTypeName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetRecordingDeviceVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDeviceVolume(int& volume);

	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetLoopbackDevice(const FString & deviceId);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetLoopbackDevice(FString & deviceId);

	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetPlaybackDeviceMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDeviceMute(bool& mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetRecordingDeviceMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDeviceMute(bool& mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StartPlaybackDeviceTest(const FString & testAudioFilePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StopPlaybackDeviceTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StartRecordingDeviceTest(int indicationInterval);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StopRecordingDeviceTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StartAudioDeviceLoopbackTest(int indicationInterval);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StopAudioDeviceLoopbackTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int FollowSystemPlaybackDevice(bool enable);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int FollowSystemRecordingDevice(bool enable);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int FollowSystemLoopbackDevice(bool enable);

private:

	static UAgoraBPuAudioDeviceManager* Instance;

	agora::rtc::IAudioDeviceManager* AudioDeviceManager;

	UPROPERTY()
	UAudioDeviceCollection* PlaybackDeviceCollection = nullptr;

	UPROPERTY()
	UAudioDeviceCollection* RecordDeviceCollection = nullptr;
};