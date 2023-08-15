// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AgoraPluginInterface.h"
#include "Utility/BFL_Logger.h"
#include "AgoraGameInstanceWithConsoleFunc.generated.h"

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UAgoraGameInstanceWithConsoleFunc : public UGameInstance
{
	GENERATED_BODY()
	
	UFUNCTION(Exec)
	void SetRtcEngineParam(FString Param);

	UFUNCTION(Exec)
	void DumpAudioFrame();
};
