// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#include "Kismet/GameplayStatics.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include <iostream>
#include <string.h>
#include "AgoraVideoWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UAgoraVideoWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* localVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LeaveBtn = nullptr;										

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* PreviousBtn = nullptr;										/* If there are multiple remote users, use this button to switch */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* NextBtn = nullptr;											/* If there are multiple remote users, use this button to switch */

	UFUNCTION(BlueprintCallable)
	void OnLeaveButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnPreviousButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnNextButtonClick();

	void CheckAndroidPermission();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;
protected:

	void NativeDestruct() override;

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	TArray<unsigned int> RemoteUserIdArray;

	unsigned int CurrentRemoteIndex = 0;

	FSlateBrush EmptyBrush;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	void SetRemoteView(UImage* remoteview, agora::rtc::uid_t uid);

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

};
