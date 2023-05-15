// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "Kismet/GameplayStatics.h"
#include "AudioDevice.h"
#include "HAL/Runnable.h"
#include <chrono>
#include <string>
#include "AgoraSoundWaveProcedural.h"
#include "CustomRenderAudioWidget.generated.h"
using namespace agora::rtc;
using namespace agora::util;

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UCustomRenderAudioWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;
	UFUNCTION(BlueprintCallable)
	void OnBackHomeButtonClick();

	class UAgoraSoundWaveProcedural* AgoraSoundWaveProcedural;

	class UAudioComponent* AgoraSound;

	void CheckAndroidPermission();

	void JoinChannel();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void NativeDestruct() override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString AppId;

	FString Token;

	FString ChannelName;

	FString timedata;

	TArray<uint8> RecordingBuffer;

	agora::media::IMediaEngine* MediaEngine;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void InitConfig();

	int AudioDataLength;

	int SAMPLE_RATE = 44100;

	int CHANNEL = 1;
	
	int PULL_FREQ_PER_SEC = 100;

	FRunnable* Runnable;
};

#pragma region AgoraThread

class FAgoraRenderRunnable : public FRunnable
{

public:

	FAgoraRenderRunnable(agora::media::IMediaEngine* MediaEngine, UAgoraSoundWaveProcedural* Soundwaveprocedural);

	virtual ~FAgoraRenderRunnable();

	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	class UAgoraSoundWaveProcedural* AgoraSoundWaveProcedural;

protected:

	TArray<int32> ProcessedNumbers;

	bool bStopThread = false;

	agora::media::IMediaEngine* MediaEngine;

	int CHANNEL = 1;

	int SAMPLE_RATE = 44100;

	int PUSH_FREQ_PER_SEC = 100;

	std::time_t getTimeStamp();

	uint8* sendByte;
};

#pragma endregion