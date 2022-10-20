// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "AgoraConfig.h"
#include "LevelSwitchItem.h"
#include "MainAgoraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UMainAgoraUserWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()
public:

	TArray<FString> LevelArray;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTileView* LevelTileView = nullptr;

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

private:
	void InitLevelArray();
};
