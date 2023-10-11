// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "../Config/AgoraConfig.h"
#include "LevelSwitchItem.h"
#include "MainAgoraUserWidget.generated.h"


#pragma region CustomTileView
// To change the scroll bar thickness of the tile view.

UCLASS()
class AGORAEXAMPLE_API UCustomTileView : public UTileView
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
class AGORAEXAMPLE_API SCustomListView : public STileView<ItemType>
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



/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UMainAgoraUserWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()
public:

	TArray<FString> LevelArray;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCustomTileView* LevelTileView = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* AppidBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* TokenBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* ChannelBox;

	FString APP_ID; 

	FString TOKEN;

	FString CHANNEL_NAME;

protected:
	void NativeConstruct() override;

	void NativeDestruct() override;

private:
	void InitLevelArray();
};
