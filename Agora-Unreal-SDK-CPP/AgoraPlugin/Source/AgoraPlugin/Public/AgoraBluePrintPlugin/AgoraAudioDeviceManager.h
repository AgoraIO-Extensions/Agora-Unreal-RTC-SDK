//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "AgoraAudioDeviceManager.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioDeviceCollection : public UObject
{
	GENERATED_BODY()

private:
	agora::rtc::IAudioDeviceCollection* AudioDeviceCollection;

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetDevice(int index, FString& deviceName, FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int SetDevice(FString deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetDefaultDevice(FString& deviceName, FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int SetApplicationVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int GetApplicationVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int SetApplicationMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	int IsApplicationMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceCollection")
	void Release();
	void SetAudioDeviceCollection(agora::rtc::IAudioDeviceCollection* audioDeviceCollection);

};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioDeviceManager : public UObject
{
	GENERATED_BODY()
private:
	UIAudioDeviceCollection* playbackDevice;
	UIAudioDeviceCollection* recordDevice;
public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	UIAudioDeviceCollection* EnumeratePlaybackDevices();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	UIAudioDeviceCollection* EnumerateRecordingDevices();
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetPlaybackDevice(FString deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDevice(FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDeviceInfo(FString& deviceId, FString& deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetPlaybackDeviceVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDeviceVolume(int& volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetRecordingDevice(FString deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDevice(FString& deviceId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDeviceInfo(FString& deviceId, FString& deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetRecordingDeviceVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDeviceVolume(int& volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetPlaybackDeviceMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetPlaybackDeviceMute(bool& mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int SetRecordingDeviceMute(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int GetRecordingDeviceMute(bool& mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAudioDeviceManager")
	int StartPlaybackDeviceTest(FString testAudioFilePath);
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
	void Release();
	void SetAudioDeviceManager(agora::rtc::IAudioDeviceManager* audioDeviceManager);
private:
	agora::rtc::IAudioDeviceManager* AudioDeviceManager;
};