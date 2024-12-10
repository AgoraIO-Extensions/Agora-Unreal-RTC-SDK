// Copyright(c) 2024 Agora.io. All rights reserved.

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


	UFUNCTION(BlueprintPure)
	static FString GetAgoraSaveDataSlotName();
};
