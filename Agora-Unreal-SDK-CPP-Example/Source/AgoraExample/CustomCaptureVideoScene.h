// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "../Private/Misc/MediaTextureResource.h"
#include <iostream>
#include <string.h>
#include <chrono> 
#include "Components/Button.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "Kismet/GameplayStatics.h"
#include "Engine/SceneCapture2D.h"
#include "Camera/CameraActor.h"
#include <mutex>
#include "CustomCaptureVideoScene.generated.h"
using namespace agora::rtc;
using namespace agora;


/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UCustomCaptureVideoScene : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBackHomeButtonClick();

	IRtcEngine* RtcEngineProxy;

	agora::media::base::ExternalVideoFrame* externalVideoFrame;

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;


	void OnBackBufferReady_RenderThread(SWindow& window, const FTexture2DRHIRef& ref);

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	FDelegateHandle eventId;

protected:

	void NativeDestruct();

	void CheckAndroidPermission();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetExternalVideoSource();

	void JoinChannel();

	std::time_t getTimeStamp();

	agora::media::IMediaEngine* MediaEngineManager;

	void NativeConstruct() override;

};


