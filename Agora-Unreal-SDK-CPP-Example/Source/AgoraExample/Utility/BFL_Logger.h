// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// UI
#include "DraggableLogMsgViewWidget.h"
#include "Components/CanvasPanel.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_Logger.generated.h"


#if defined(_MSC_VER)
//#define FUNCTION_MACRO __FUNCSIG__ // °üº¬Ç©Ãû
#define FUNCTION_MACRO __FUNCTION__
#else
#define FUNCTION_MACRO __PRETTY_FUNCTION__
#endif


/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UBFL_Logger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool bDisablePrintToConsole;
	static bool bDisablePrintToLogMsgView;
	static bool bDisablePrintOnScreen;
	static FString ConsolePreix;
	static FString ConsoleLogTitle;

public:
	static UDraggableLogMsgViewWidget* CreateLogView(UCanvasPanel* ParentCanvasPanel, TSubclassOf<UUserWidget> Template);
	static void ReleaseLogView(UDraggableLogMsgViewWidget* LogMsgViewWidgetPtr);
	static void InitLogMsgView(UDraggableLogMsgViewWidget* Widget);


	static void Print(FString LogMsg, UDraggableLogMsgViewWidget* Widget = nullptr, bool bToConsole = true, bool bToLogMsgView = true, bool bOnScreen = false);
	static void PrintWarn(FString LogMsg, UDraggableLogMsgViewWidget* Widget = nullptr, bool bToConsole = true, bool bToLogMsgView = true, bool bOnScreen = false);
	static void PrintError(FString LogMsg, UDraggableLogMsgViewWidget* Widget = nullptr, bool bToConsole = true, bool bToLogMsgView = true, bool bOnScreen = false);


	static void DisplayUserGuide(FString UserGuide, UDraggableLogMsgViewWidget* Widget = nullptr, bool bToConsole = true, bool bToLogMsgView = true, bool bOnScreen = false);

	UFUNCTION(Blueprintcallable)
	static FString GetAgoraConsoleLogTitleStr() { return ConsoleLogTitle; }
};
