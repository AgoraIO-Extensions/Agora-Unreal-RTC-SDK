// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Button.h"
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "SpatialAudioWidget.generated.h"
using namespace agora::rtc;
using namespace agora::util;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API USpatialAudioWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
	
public:

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;

	void onUserJoined(uid_t uid, int elapsed) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LeftMoveBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RightMoveBtn = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClick();

	UFUNCTION(BlueprintCallable)
	void LeftMoveButtonClick();

	UFUNCTION(BlueprintCallable)
	void RightMoveButtonClick();


protected:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	FString Token;

	FString ChannelName;

	uid_t RemoteUid;

	ILocalSpatialAudioEngine* LocalSpatialAudioEngine;
	
	void NativeConstruct() override;

	void NativeDestruct() override;

	void CheckAndroidPermission();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	void InitSpatialAudioEngine(IRtcEngine* engine);

};
