// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_VideoViewManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UImage* UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(int64 uid, UCanvasPanel* CanvasPanel,TMap<int64, UDraggableVideoViewWidget*> & VideoViewMap, UImage* VideoView, TSubclassOf<UUserWidget> Template)
{
	if (VideoViewMap.Contains(uid))
	{
		return VideoViewMap[uid]->View;
	}
	else
	{	
		UWorld* world = GEngine->GameViewport->GetWorld();
		//TSubclassOf<UDraggableVideoViewWidget> VideoViewClass = UDraggableVideoViewWidget::StaticClass();
		UDraggableVideoViewWidget* VideoViewWidget = CreateWidget<UDraggableVideoViewWidget>(world, Template);
		VideoViewMap.Add(uid, VideoViewWidget);
		UPanelSlot* PanelSlot = CanvasPanel->AddChild(VideoViewWidget);
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget);
		CanvasPanelSlot->SetSize(FVector2D(640,360));
		return  VideoViewWidget->View;
	}
}


UImage* UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(const FVideoViewIdentity& Key, UCanvasPanel* CanvasPanel, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap, TSubclassOf<UUserWidget> Template)
{
	if (VideoViewMap.Contains(Key))
	{
		return VideoViewMap[Key]->View;
	}
	else
	{
		UWorld* world = GEngine->GameViewport->GetWorld();
		//TSubclassOf<UDraggableVideoViewWidget> VideoViewClass = UDraggableVideoViewWidget::StaticClass();
		UDraggableVideoViewWidget* VideoViewWidget = CreateWidget<UDraggableVideoViewWidget>(world, Template);
		ensure(VideoViewWidget != nullptr);
		if(Key.uid == 0){
			FText ShowedText = FText::FromString(FString("LocalView"));
			VideoViewWidget->Text->SetText(ShowedText);
		}
		else{
			FText ShowedText = FText::FromString(FString("RemoteView"));
			VideoViewWidget->Text->SetText(ShowedText);
		}

		VideoViewMap.Add(Key, VideoViewWidget);
		UPanelSlot* PanelSlot = CanvasPanel->AddChild(VideoViewWidget);
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget);
		CanvasPanelSlot->SetSize(FVector2D(640, 360));
		return  VideoViewWidget->View;
	}
}

void UBFL_VideoViewManager::ReleaseOneVideoView(int64 uid, TMap<int64, UDraggableVideoViewWidget*>& VideoViewMap)
{
	if (VideoViewMap.Contains(uid))
	{
		VideoViewMap[uid]->RemoveFromParent();
		VideoViewMap.Remove(uid);
	}
}

void UBFL_VideoViewManager::ReleaseOneVideoView(const FVideoViewIdentity& Key, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap)
{
	if (VideoViewMap.Contains(Key))
	{
		VideoViewMap[Key]->RemoveFromParent();
		VideoViewMap.Remove(Key);
	}
}

void UBFL_VideoViewManager::ReleaseAllVideoView(TMap<int64, UDraggableVideoViewWidget*>& VideoViewMap)
{
	for (auto& VideoView : VideoViewMap)
	{
		VideoView.Value->RemoveFromParent();
	}
	VideoViewMap.Empty();
}

void UBFL_VideoViewManager::ReleaseAllVideoView(TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap)
{
	for (auto& VideoView : VideoViewMap)
	{
		VideoView.Value->RemoveFromParent();
	}
	VideoViewMap.Empty();
}

void UBFL_VideoViewManager::ChangeSizeForOneVideoView(const FVideoViewIdentity& Key, int Width, int Height, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap)
{
	if (VideoViewMap.Contains(Key))
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewMap[Key]);
		CanvasPanelSlot->SetSize(FVector2D(Width, Height));
		//VideoViewMap[Key]->View->SetBrushSize(FVector2D(Width, Height));
	}
}

void UBFL_VideoViewManager::OnDropInner(const FGeometry& InGeometry, const FPointerEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UWidgetDropOP* WidgetDropOp = Cast<UWidgetDropOP>(InOperation);
	FVector2D Position = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D FinalPosition = Position - WidgetDropOp->DragOffset;
	WidgetDropOp->WidgetReference->SetRenderTranslation(FinalPosition);
}

