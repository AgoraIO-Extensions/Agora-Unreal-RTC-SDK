// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//UI
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DraggableVideoViewWidget.generated.h"

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UDraggableVideoViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* View = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text = nullptr;

};
