// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "AgoraPluginInterface.h"
#include "Kismet/GameplayStatics.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include <iostream>
#include <string.h>
#include "AgoraPluginInterface.h"
#include "RtmpStreamWithTranscodingWidget.generated.h"
using namespace agora::rtc;
using namespace agora;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API URtmpStreamWithTranscodingWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* localVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StartBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* UpdateBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StopBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* RtmpTextBox = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnUpdateButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnStartButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnStopButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnBackHomeButtonClick();

	void JoinChannel();

	void CheckAndroidPermission();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

protected:

	void NativeDestruct() override;

private:

	IRtcEngine* RtcEngineProxy;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	FSlateBrush EmptyBrush;

	unsigned int Uid = 0;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();



	void SetRemoteView(UImage* remoteview, agora::rtc::uid_t uid);

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

	void onTranscodingUpdated() override;

	void onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR_TYPE errCode) override;
};
