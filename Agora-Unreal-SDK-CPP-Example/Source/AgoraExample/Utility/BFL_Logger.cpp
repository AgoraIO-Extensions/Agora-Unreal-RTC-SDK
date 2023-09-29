// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_Logger.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

bool UBFL_Logger::bDisablePrintToConsole = false;
bool UBFL_Logger::bDisablePrintToLogMsgView = false;
bool UBFL_Logger::bDisablePrintOnScreen = false;


FString UBFL_Logger::ConsolePreix = "[Agora-UE]";

FString UBFL_Logger::ConsoleLogTitle =" ======= Init Log Msg View ======= \n";

UDraggableLogMsgViewWidget* UBFL_Logger::CreateLogView(UCanvasPanel* ParentCanvasPanel, TSubclassOf<UUserWidget> Template)
{
	UWorld* world = GEngine->GameViewport->GetWorld();
	UDraggableLogMsgViewWidget* VideoViewWidget = CreateWidget<UDraggableLogMsgViewWidget>(world, Template);
	UPanelSlot* PanelSlot = ParentCanvasPanel->AddChild(VideoViewWidget);
	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(VideoViewWidget);
	CanvasPanelSlot->SetSize(FVector2D(1280, 960));
	InitLogMsgView(VideoViewWidget);
	return VideoViewWidget;
}

void UBFL_Logger::ReleaseLogView(UDraggableLogMsgViewWidget* LogMsgViewWidgetPtr)
{
	if (LogMsgViewWidgetPtr)
	{
		LogMsgViewWidgetPtr->RemoveFromParent();
		LogMsgViewWidgetPtr = nullptr;
	}
}

void UBFL_Logger::InitLogMsgView(UDraggableLogMsgViewWidget* Widget)
{
	if(Widget){
		Widget->Txt_LogMsg->SetText(FText::FromString(ConsoleLogTitle));
	}
}

void UBFL_Logger::Print(FString LogMsg, UDraggableLogMsgViewWidget* Widget /*= nullptr*/, bool bToConsole /*= true*/, bool bToLogMsgView /*= true */, bool bOnScreen /*= false*/)
{
	if (bToConsole && !bDisablePrintToConsole) {
		// Print Log To Console
		UE_LOG(LogTemp, Display, TEXT("%s %s"), *ConsolePreix, *LogMsg);
	}

	if (bToLogMsgView && Widget != nullptr && !bDisablePrintToLogMsgView) {
		if (!Widget->IsWidgetValid())
			return;
		// Print Log To LogMsgView
		FString NewLogMsg = Widget->Txt_LogMsg->GetText().ToString() + "\n" + LogMsg;
		Widget->Txt_LogMsg->SetText(FText::FromString(NewLogMsg));
	}

	if (bOnScreen && !bDisablePrintOnScreen) {
		// Print Log To LogMsgView
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, LogMsg);
	}

}

void UBFL_Logger::PrintWarn(FString LogMsg, UDraggableLogMsgViewWidget* Widget /*= nullptr*/, bool bToConsole /*= true*/, bool bToLogMsgView /*= true*/, bool bOnScreen /*= false*/)
{
	if (bToConsole && !bDisablePrintToConsole) {
		// Print Log To Console
		UE_LOG(LogTemp, Warning, TEXT("%s %s"), *ConsolePreix, *LogMsg);
	}

	if (bToLogMsgView && Widget != nullptr && !bDisablePrintToLogMsgView) {
		if (!Widget->IsWidgetValid())
			return;
		// Print Log To LogMsgView
		FString NewLogMsg = Widget->Txt_LogMsg->GetText().ToString() + "\n [Warn] " + LogMsg;
		Widget->Txt_LogMsg->SetText(FText::FromString(NewLogMsg));
	}

	if (bOnScreen && !bDisablePrintOnScreen) {
		// Print Log To LogMsgView
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, LogMsg);
	}
}

void UBFL_Logger::PrintError(FString LogMsg, UDraggableLogMsgViewWidget* Widget /*= nullptr*/, bool bToConsole /*= true*/, bool bToLogMsgView /*= true*/, bool bOnScreen /*= false*/)
{
	if (bToConsole && !bDisablePrintToConsole) {
		// Print Log To Console
		UE_LOG(LogTemp, Error, TEXT("%s %s"), *ConsolePreix, *LogMsg);
	}

	if (bToLogMsgView && Widget != nullptr && !bDisablePrintToLogMsgView) {
		if (!Widget->IsWidgetValid())
			return;
		// Print Log To LogMsgView
		FString NewLogMsg = Widget->Txt_LogMsg->GetText().ToString() + "\n [Error] " + LogMsg;
		Widget->Txt_LogMsg->SetText(FText::FromString(NewLogMsg));
	}

	if (bOnScreen && !bDisablePrintOnScreen) {
		// Print Log To LogMsgView
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, LogMsg);
	}
}

void UBFL_Logger::DisplayUserGuide(FString UserGuide, UDraggableLogMsgViewWidget* Widget /*= nullptr*/, bool bToConsole /*= true*/, bool bToLogMsgView /*= true*/, bool bOnScreen /*= false*/)
{
	FString GuideBegin ="\n"\
	"******************************************\n" \
	"======== User Guide Begin ========\n" \
	"[Notice]: All the views are draggable\n" \
	"---------------------------------------\n";

	FString GuideEnd = ""\
	"========= User Guide End ========\n"\
	"******************************************\n";

	FString ContentMsg = GuideBegin + UserGuide + GuideEnd;

	Print(ContentMsg,Widget,false, bToLogMsgView, bOnScreen);
}
