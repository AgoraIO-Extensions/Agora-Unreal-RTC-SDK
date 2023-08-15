// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameWork/PlayerController.h"
#include <string>
#include "BaseAgoraUserWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UBaseAgoraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);


protected:
	void NativeConstruct() override;

};
