// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "AgoraConfig.h"
#include "MainAgoraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UMainAgoraUserWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinChannelVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinChannelAudio = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DeviceManager = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinMultipleChannel = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MediaPlayer = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ScreenShare = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SendMultiCameraStream = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SpatialAudio = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CustomCaptureVideo = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* AppidBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* TokenBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* ChannelBox;

	FString APP_ID; 

	FString TOKEN;

	FString CHANNEL_NAME;

protected:
	void NativeConstruct() override;

	void NativeDestruct() override;

};
