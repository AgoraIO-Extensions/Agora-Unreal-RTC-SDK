// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#include "Kismet/GameplayStatics.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "DeviceManagerUserWidget.generated.h"

using namespace agora::rtc;
using namespace agora::util;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UDeviceManagerUserWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CallBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UFUNCTION(BlueprintCallable)
	void CallDeviceManagerApi();

	UFUNCTION(BlueprintCallable)
	void BackHomeClick();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

private:

	AutoPtr<IAudioDeviceManager> AudioDeviceManager;

	AutoPtr<IVideoDeviceManager> VideoDeviceManager;

	IAudioDeviceCollection* AudioRecordingDeviceInfos;

	IAudioDeviceCollection* AudioPlaybackDeviceInfos;

	IVideoDeviceCollection* VideoDeviceInfos;

	FString AppId;

	FString Token;

	FString ChannelName;

	IRtcEngine* RtcEngineProxy;

	const int DEVICE_INDEX = 0;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	void GetAudioRecordingDevice();

	void GetAudioPlaybackDevice();

	void GetVideoDeviceManager();

	void SetCurrentDevice();

	void SetCurrentDeviceVolume();

protected:

	void NativeDestruct() override;

};
