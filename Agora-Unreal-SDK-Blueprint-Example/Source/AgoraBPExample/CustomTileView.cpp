// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTileView.h"


#pragma region CustomTileView


UCustomTileView::UCustomTileView(const FObjectInitializer& Initializer) :Super(Initializer)
{
	BarThickness = FVector2D(50, 50);
}

TSharedRef<STableViewBase> UCustomTileView::RebuildListWidget()
{
	auto TileViewRef = ConstructTileView<STileView>();
	auto CustomTileViewRef = StaticCastSharedRef<SCustomListView<UObject*>>(TileViewRef);

	CustomTileViewRef->UpdateScrollBarThickness(BarThickness);
	return CustomTileViewRef;
}


#pragma endregion