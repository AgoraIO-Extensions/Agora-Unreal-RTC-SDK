// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_UtilityTool.generated.h"

/**
 * 
 */
UCLASS()
class AGORABPEXAMPLE_API UBFL_UtilityTool : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	UFUNCTION(Blueprintcallable)
	static bool IsAgoraAudioOnlySDK();
};
