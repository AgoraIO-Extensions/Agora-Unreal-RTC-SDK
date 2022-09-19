// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"
#include "Components/Image.h"
#include <iostream>
#include <string.h>
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
	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* localVideo = nullptr;

	IRtcEngine* RtcEngineProxy;

	agora::media::IMediaEngine* MediaEngineProxy;

	agora::util::AutoPtr<agora::media::IMediaEngine> MediaEngineManager;

protected:
	void NativeConstruct() override;

	void CheckAndroidPermission();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetExternalVideoSource();
private:
	void JoinChannel();
};
