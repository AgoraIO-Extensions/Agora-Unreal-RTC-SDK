// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AgoraConfig.generated.h"

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UAgoraConfig : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString Channelname;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString Token;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString AppId;
};
