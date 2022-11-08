// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include <iostream>
#include <string.h>
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "SendMultiCameraStreamWidget.generated.h"
using namespace agora::rtc;

using namespace agora;

using namespace agora::util;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API USendMultiCameraStreamWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandlerEx
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PrimaryVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SecondVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MainCameraJoin = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* MainCameraLeave = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* SecondCameraJoin = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* SecondCameraLeave = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	UFUNCTION(BlueprintCallable)
	void MainCameraJoinChannel();
	UFUNCTION(BlueprintCallable)
	void MainCameraLeaveChannel();
	UFUNCTION(BlueprintCallable)
	void SecondCameraJoinChannel();
	UFUNCTION(BlueprintCallable)
	void SecondCameraLeaveChannel();

	unsigned int Uid1 = 123;

	unsigned int Uid2 = 456;

	void onUserOffline(const RtcConnection& connection, uid_t remoteUid, USER_OFFLINE_REASON_TYPE reason) override;

	void onError(int err, const char* msg) override;

	void onJoinChannelSuccess(const RtcConnection& connection, int elapsed) override;

	void onRejoinChannelSuccess(const RtcConnection& connection, int elapsed) override;

	void onLeaveChannel(const RtcConnection& connection, const RtcStats& stats) override;

	void onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed) override;

protected:
	void NativeDestruct() override;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void GetVideoDeviceManager();

	void SetUpUIEvent();

	void CheckAndroidPermission();
private:
	agora::rtc::IRtcEngine* RtcEngineProxy;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	AutoPtr<IVideoDeviceManager> VideoDeviceManager;

	IVideoDeviceCollection* VideoDeviceInfos;

	CameraCapturerConfiguration ConfigPrimary;

	CameraCapturerConfiguration ConfigSecond;

	bool bIsChannelJoined = false;

	FSlateBrush EmptyBrush;
};
