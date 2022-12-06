	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "Components/EditableTextBox.h"
#include "ScreenShareWidget.generated.h"
using namespace agora::rtc;
using namespace agora;


/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UScreenShareWidget : public UBaseAgoraUserWidget ,public  agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LocalVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ScreenShareBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LeaveBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ComboBoxDisplayId = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ScenarioComboBox = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	//UComboBoxString* ProfileComboBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* FPSComboBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* WidthTextBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* HeightTextBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* BitRateTextBox = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnLeaveButtonClick();

	UFUNCTION(BlueprintCallable)
	void StartScreenShare(int width, int height, int bitRate, int frameRate);
	
	UFUNCTION(BlueprintCallable)
	void OnScreenShareClick();

	UFUNCTION(BlueprintCallable)
	void SelectValueCallBack(FString SelectedItem, ESelectInfo::Type SelectionType);

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void GetScreenDisplayId();

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString AppId;

	FString Token;

	FString ChannelName;

	TMap<FString, CHANNEL_PROFILE_TYPE> AgoraChannelProfileEnumMap;

	TMap<FString, AUDIO_SCENARIO_TYPE> AgoraAudioScenarioEnumMap;

	int SelectDisplayId;

	VideoDimensions videoDimensions;

	void InitUI();

	void JoinChannel();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void UpdateChannelMediaOptions();

	void SetUpUIEvent();

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;

	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

	FSlateBrush EmptyBrush;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	agora::rtc::IScreenCaptureSourceList* infos;
#endif
protected:

	void NativeDestruct() override;

	void CheckAndroidPermission();
};


