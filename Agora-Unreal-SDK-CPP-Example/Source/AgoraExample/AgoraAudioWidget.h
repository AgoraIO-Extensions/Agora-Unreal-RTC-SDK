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
#include "AgoraAudioWidget.generated.h"

class RtcEngineEventHandler : public agora::rtc::IRtcEngineEventHandler
{
public:
	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
};

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UAgoraAudioWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LeaveBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* VolumeIndicationBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	void CheckAndroidPermission();

	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnLeaveButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnVolumeIndicationClick();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void NativeDestruct() override;


private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString AppId;

	FString Token;

	FString ChannelName;

	void SetButtonClickAble(bool enable);

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	RtcEngineEventHandler* rtcEventHandler;
};


