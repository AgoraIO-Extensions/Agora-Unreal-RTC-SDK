// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "CustomTileView.generated.h"


#pragma region CustomTileView
// To change the scroll bar thickness of the tile view.

UCLASS()
class AGORABPEXAMPLE_API UCustomTileView : public UTileView
{
	GENERATED_BODY()

	UCustomTileView(const FObjectInitializer& Initializer);

protected:
	virtual TSharedRef<STableViewBase> RebuildListWidget() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Scroll Bar Thickness"))
	FVector2D BarThickness;
};


template <typename ItemType>
class AGORABPEXAMPLE_API SCustomListView : public STileView<ItemType>
{
public:

	// It doesn't work
	//void SetScrollBarThickness(const FVector2D& Vec2)
	//{
	//	if (ScrollBar.IsValid())
	//	{
	//		ScrollBar->SetThickness(Vec2);
	//	}
	//}

	void UpdateScrollBarThickness(const FVector2D& Vec2)
	{
		if (STableViewBase::ScrollBar.IsValid())
		{
			TSharedPtr<SWidget> SBarParentWidgetPtr = STableViewBase::ScrollBar->GetParentWidget();
			auto ScrollBarBox = StaticCastSharedPtr<SBox>(SBarParentWidgetPtr);

			ScrollBarBox->SetWidthOverride(FOptionalSize(Vec2.X));
			STableViewBase::ScrollBar->SetThickness(Vec2);
		}
	}
};

#pragma endregion