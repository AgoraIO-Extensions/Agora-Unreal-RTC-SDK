// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "Kismet/GameplayStatics.h"
#include "AudioDevice.h"
#include <mutex>
#include "Http.h"
#include "HAL/Runnable.h"
#include <chrono>
#include "CustomCaptureAudioWidget.generated.h"

using namespace agora::rtc;
using namespace agora::util;


/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UCustomCaptureAudioWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	void CheckAndroidPermission();

	void JoinChannel();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void SetExternalAudioSource();

	void NativeDestruct() override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

	void StartPushAudio();

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString AppId;

	FString Token;

	FString ChannelName;

	TArray<uint8> RecordingBuffer;

	agora::media::IMediaEngine* MediaEngine;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	int AudioDataLength;

	int SAMPLE_RATE = 48000;

	int CHANNEL = 2;

	FRunnable* Runnable;
};


#pragma region AgoraThread

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAgoraOnCompleteSignature);

class FAgoraCaptureRunnable : public FRunnable
{
public:

	FAgoraCaptureRunnable(agora::media::IMediaEngine* MediaEngine, const uint8* audioData, int dataLength);
	virtual ~FAgoraCaptureRunnable();

	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	FAgoraOnCompleteSignature OnCompleteDelegate;

protected:

	TArray<int32> ProcessedNumbers;

	bool bStopThread = false;

	agora::media::IMediaEngine* MediaEngine;

	uint8* audioData;

	int dataLength;

	int CHANNEL = 2;

	int SAMPLE_RATE = 48000;

	int PUSH_FREQ_PER_SEC = 100;

	std::time_t getTimeStamp();

	uint8* sendByte;
};

#pragma endregion



