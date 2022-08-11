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
#include "ScreenShareWidget.generated.h"
using namespace agora::rtc;

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UScreenShareWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
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

	UFUNCTION(BlueprintCallable)
	void BackHomeClick();

	UFUNCTION(BlueprintCallable)
	void OnLeaveButtonClick();

	UFUNCTION(BlueprintCallable)
	void StartScreenShrareClick();
	
	UFUNCTION(BlueprintCallable)
	void SelectValueCallBack(FString SelectedItem, ESelectInfo::Type SelectionType);

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void GetScreenDisplayId();

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString AppId;

	FString Token;

	FString ChannelName;

	int SelectDisplayId;

	void JoinChannel();

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

	void onLeaveChannel(const agora::rtc::RtcStats& stats);

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void UpdateChannelMediaOptions();

	void SetUpUIEvent();

	FSlateBrush EmptyBrush;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	agora::rtc::IScreenCaptureSourceList* infos;
#endif
protected:

	void NativeDestruct() override;

	void CheckAndroidPermission();
};
