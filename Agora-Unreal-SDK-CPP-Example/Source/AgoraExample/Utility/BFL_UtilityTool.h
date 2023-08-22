// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "BFL_UtilityTool.generated.h"

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UBFL_UtilityTool : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static FString ConvertToAbsolutePath(FString InRelativePath, bool bAndroidUseInternalBasePath = false);

	static void CreateMediaFileWithSource(FString SrcPath,FString DstPath);
};
