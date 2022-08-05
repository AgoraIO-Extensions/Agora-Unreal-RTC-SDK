// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include <iostream>
#include <string.h>
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "JoinMultipleChannelWidget.generated.h"
using namespace agora::rtc;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UJoinMultipleChannelWidget : public UBaseAgoraUserWidget, public IRtcEngineEventHandlerEx
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ScreenShareVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LocalVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* StartScreenShrareBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinBtn = nullptr;

	UFUNCTION(BlueprintCallable)
	void StartScreenShrareClick();

	UFUNCTION(BlueprintCallable)
	void JoinChannelClick();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ComboBoxDisplayId = nullptr;

	UFUNCTION(BlueprintCallable)
	void SelectValueCallBack(FString SelectedItem, ESelectInfo::Type SelectionType);

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void onJoinChannelSuccess(const RtcConnection& connection, int elapsed) override;

	void onLeaveChannel(const RtcConnection& connection, const RtcStats& stats) override;

	void onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed) override;

	void onUserOffline(const RtcConnection& connection, uid_t remoteUid, USER_OFFLINE_REASON_TYPE reason) override;

protected:

	void NativeDestruct() override;

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	unsigned int Uid1 = 123;

	unsigned int Uid2 = 456;

	int SelectDisplayId;

	FSlateBrush EmptyBrush;
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
	agora::rtc::IScreenCaptureSourceList* ScreenShareinfos;
#endif
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void PrepareScreenCapture();

	void ScreenShareJoinChannel();

	void SetUpUIEvent();

	void CheckAndroidPermission();
};
