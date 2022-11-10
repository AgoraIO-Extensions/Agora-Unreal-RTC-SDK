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
#include "Components/ComboBoxString.h"
#include "AgoraAudioWidget.generated.h"
using namespace agora::rtc;
using namespace agora;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UAgoraAudioWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConfirmBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ScenarioComboBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ProfileComboBox = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnLeaveButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnVolumeIndicationClick();

	UFUNCTION(BlueprintCallable)
	void OnConfirmButtonClick();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString AppId;

	FString Token;

	FString ChannelName;

	void SetButtonClickAble(bool enable);

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	TMap<FString, CHANNEL_PROFILE_TYPE> AgoraChannelProfileEnumMap;

	TMap<FString, AUDIO_SCENARIO_TYPE> AgoraAudioScenarioEnumMap;

	void NativeDestruct() override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void CheckAndroidPermission();

	void InitUI();

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

	void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;
};
