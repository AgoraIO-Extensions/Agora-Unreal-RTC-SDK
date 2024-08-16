// Copyright(c) 2024 Agora.io. All rights reserved.

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
