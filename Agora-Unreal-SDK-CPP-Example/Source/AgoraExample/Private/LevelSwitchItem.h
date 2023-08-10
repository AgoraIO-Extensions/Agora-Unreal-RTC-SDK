// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelSwitchItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ULevelSwitchItem : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	FString LevelName;
};
