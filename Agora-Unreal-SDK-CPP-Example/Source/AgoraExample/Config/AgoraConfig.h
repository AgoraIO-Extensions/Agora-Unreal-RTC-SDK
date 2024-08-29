// Copyright(c) 2024 Agora.io. All rights reserved.

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
