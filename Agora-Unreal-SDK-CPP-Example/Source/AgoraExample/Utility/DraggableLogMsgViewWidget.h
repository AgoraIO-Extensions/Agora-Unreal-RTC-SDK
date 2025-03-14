// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DraggableLogMsgViewWidget.generated.h"

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UDraggableLogMsgViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	inline bool IsWidgetValid() const { return !bIsDestruct; }

	void NativeConstruct() override;
	void NativeDestruct() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Txt_LogMsg = nullptr;

protected:
	bool bIsDestruct = true;
};
