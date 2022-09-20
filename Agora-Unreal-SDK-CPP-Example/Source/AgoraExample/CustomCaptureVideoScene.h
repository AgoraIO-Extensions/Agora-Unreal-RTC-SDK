// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"
#include "Components/Image.h"
#include "MediaTexture.h"
#include "Components/CanvasPanelSlot.h"
#include "../Private/Misc/MediaTextureResource.h"
#include <iostream>
#include <string.h>
#include <chrono> 
#include "Components/Button.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "CustomCaptureVideoScene.generated.h"
using namespace agora::rtc;
using namespace agora;
/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UCustomCaptureVideoScene : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* localVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void InitCamera();

	UFUNCTION(BlueprintCallable)
	void BackHomeClick();

	IRtcEngine* RtcEngineProxy;

	agora::media::base::ExternalVideoFrame* externalVideoFrame;

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeDestruct();

	void CheckAndroidPermission();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetExternalVideoSource();

	void JoinChannel();

	std::time_t getTimeStamp();

	agora::media::IMediaEngine* MediaEngineManager;
};
