// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
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
	UButton* DevicesManager = nullptr;

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
	UEditableTextBox* AppidBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* TokenBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* ChannelBox;

	UFUNCTION(BlueprintCallable)
	void JoinChannelVideoClick();

	UFUNCTION(BlueprintCallable)
	void JoinChannelAudioClick();

	UFUNCTION(BlueprintCallable)
	void DvicesManagerClick();

	UFUNCTION(BlueprintCallable)
	void JoinMultipleChannelClick();

	UFUNCTION(BlueprintCallable)
	void MediaPlayerClick();

	UFUNCTION(BlueprintCallable)
	void ScreenShareClick();

	UFUNCTION(BlueprintCallable)
	void SendMultiCameraStreamClick();

	UFUNCTION(BlueprintCallable)
	void SpatialAudioClick();

	FString APP_ID; 

	FString TOKEN;

	FString CHANNEL_NAME;

	void LoadWidget(FString WidgetName);

	void InitAgoraWidget(FString Id, FString Token, FString Channelname) override;

protected:
	void NativeConstruct() override;
};
