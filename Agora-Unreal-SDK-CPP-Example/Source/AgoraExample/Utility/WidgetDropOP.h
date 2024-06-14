// Fill out your copyright notice in the Description page of Project Settings.

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
