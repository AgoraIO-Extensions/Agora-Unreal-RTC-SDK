// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_VideoViewManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UImage* UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(int64 uid, UCanvasPanel* CanvasPanel, TMap<int64, UDraggableVideoViewWidget*>& VideoViewMap, UImage* VideoView, TSubclassOf<UUserWidget> Template, bool bAutoSize /* = false */)
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

		// set the whole UDraggableVideoViewWidget widget size
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget);
		CanvasPanelSlot->SetSize(FVector2D(640, 360));

		// make the image auto-sized, the same as its brush size
		UCanvasPanelSlot* ViewCanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget->View);
		ViewCanvasPanelSlot->SetAutoSize(bAutoSize);

		return  VideoViewWidget->View;
	}
}


UImage* UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(const FVideoViewIdentity& Key, UCanvasPanel* CanvasPanel, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap, TSubclassOf<UUserWidget> Template, bool bAutoSize /* = false */)
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
		if (Key.uid == 0) {
			FText ShowedText = FText::FromString(FString("LocalView"));
			VideoViewWidget->Text->SetText(ShowedText);
		}
		else {
			FText ShowedText = FText::FromString(FString("RemoteView"));
			VideoViewWidget->Text->SetText(ShowedText);
		}

		VideoViewMap.Add(Key, VideoViewWidget);
		UPanelSlot* PanelSlot = CanvasPanel->AddChild(VideoViewWidget);

		// set the whole UDraggableVideoViewWidget widget size
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget);
		CanvasPanelSlot->SetSize(FVector2D(640, 360));

		// make the image auto-sized, the same as its brush size
		UCanvasPanelSlot* ViewCanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget->View);
		ViewCanvasPanelSlot->SetAutoSize(bAutoSize);
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

void UBFL_VideoViewManager::RotateTheVideoView(const FVideoViewIdentity& Key, int rotation, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap)
{
	if (VideoViewMap.Contains(Key))
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewMap[Key]);
		UImage* TargetImage = VideoViewMap[Key]->View;
		TargetImage->SetRenderTransformAngle(rotation);
	}
}

void UBFL_VideoViewManager::ResizeTheRotationAppliedImage(const FVideoViewIdentity& Key, int Width, int Height, int rotation, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap)
{
	// Because [getRotationApplied] in [VideoObserverInternal.h] is set to True, we just change the size.
	if (VideoViewMap.Contains(Key))
	{
		/*
			Rotate Matrix:
			| cos(¦È)  -sin(¦È) |
			| sin(¦È)   cos(¦È) |

			For Each Points: (x,y) -> (x',y')

			x' = x * cos(¦È) - y * sin(¦È)
			y' = x * sin(¦È) + y * cos(¦È)
		*/

		/*
			RotatedWidth = max(x'1, x'2, x'3, x'4) - min(x'1, x'2, x'3, x'4)
			RotatedHeight = max(y'1, y'2, y'3, y'4) - min(y'1, y'2, y'3, y'4)

			RotatedWidth = max((Width * cos(¦È) - Height * sin(¦È)), (Width * cos(¦È)), 0) - min((0), (0), (Width * cos(¦È) - Height * sin(¦È)))
			RotatedHeight = max((Width * sin(¦È) + Height * cos(¦È)), (Height * cos(¦È)), 0) - min((0), (0), (Width * sin(¦È) + Height * cos(¦È)))
			RotatedWidth = Width * cos(¦È) - Height * sin(¦È)
			RotatedHeight = Width * sin(¦È) + Height * cos(¦È)
		*/

		float Radians = FMath::DegreesToRadians(rotation);
		float CosTheta = FMath::Abs(FMath::Cos(Radians));
		float SinTheta = FMath::Abs(FMath::Sin(Radians));

		int32 RotatedWidth = FMath::RoundToInt(Width * CosTheta + Height * SinTheta);
		int32 RotatedHeight = FMath::RoundToInt(Width * SinTheta + Height * CosTheta);

		ChangeSizeForOneVideoView(Key, RotatedWidth, RotatedHeight, VideoViewMap);
	}
}

void UBFL_VideoViewManager::OnDropInner(const FGeometry& InGeometry, const FPointerEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UWidgetDropOP* WidgetDropOp = Cast<UWidgetDropOP>(InOperation);
	FVector2D Position = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D FinalPosition = Position - WidgetDropOp->DragOffset;
	WidgetDropOp->WidgetReference->SetRenderTranslation(FinalPosition);
}

