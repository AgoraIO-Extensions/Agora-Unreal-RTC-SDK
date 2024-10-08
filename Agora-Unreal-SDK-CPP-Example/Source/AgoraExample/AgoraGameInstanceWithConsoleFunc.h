// Copyright(c) 2024 Agora.io. All rights reserved.

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
};
