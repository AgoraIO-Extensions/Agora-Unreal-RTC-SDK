// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "WidgetDropOP.generated.h"

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UWidgetDropOP : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag Related", meta = (ExposeOnSpawn = "true"))
	UUserWidget* WidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag Related", meta = (ExposeOnSpawn = "true"))
	FVector2D DragOffset;
};
