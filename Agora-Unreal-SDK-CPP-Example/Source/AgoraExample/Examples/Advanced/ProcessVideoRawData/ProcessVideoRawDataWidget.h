// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "SlateOptMacros.h"
#include <iostream>
#include <string.h>
#include <memory>
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif
#include "ProcessVideoRawDataWidget.generated.h"
using namespace agora::rtc;
using namespace agora;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UProcessVideoRawDataWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler , public media::IVideoFrameObserver
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnLeaveButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnBackHomeButtonClick();

	void CheckAndroidPermission();

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

protected:

	void NativeDestruct() override;

private:

	IRtcEngine* RtcEngineProxy;

	agora::media::IMediaEngine* MediaEngine;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	FSlateBrush EmptyBrush;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

	virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onScreenCaptureVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onPreEncodeScreenVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId) override;
	virtual bool onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame) override;
	virtual bool onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame) override;
	virtual agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE getVideoFrameProcessMode() override;
	virtual agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference() override;
	virtual bool getRotationApplied() override;
	virtual bool getMirrorApplied() override;
	virtual uint32_t getObservedFramePosition() override;
	virtual bool isExternal() override;
	virtual bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame) override;
	virtual bool onTranscodedVideoFrame(VideoFrame& videoFrame) override;

	UTexture2D* LocalRenderTexture;
	FSlateBrush LocalRenderBrush;

	UTexture2D* RemoteRenderTexture;
	FSlateBrush RemoteRenderBrush;
};



