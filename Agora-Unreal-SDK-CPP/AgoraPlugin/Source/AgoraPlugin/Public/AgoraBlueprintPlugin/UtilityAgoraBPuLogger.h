// Copyright(c) 2024 Agora.io.All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AgoraPlugin.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AgoraHeaderBase.h"
#include "UtilityAgoraBPuLogger.generated.h"


#if defined(_MSC_VER)
#define AG_FUNCTION_MACRO __FUNCTION__
#else
#define AG_FUNCTION_MACRO __PRETTY_FUNCTION__
#endif

static TMap<AGORA_UE_ERROR_CODE,FString> AGORA_UEBP_ERR_STR =
{
	{AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED," Agora Rtc Engine may not be initialized, please check if it has been initialized. "},
	{AGORA_UE_ERROR_CODE::ERROR_NULLPTR," Agora pointer Is nullptr, please check if it has been created successfully."},
};

/**
 *
 */
UCLASS()
class AGORAPLUGIN_API UAgoraBPuLogger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static bool bDisablePrintToConsole;
	static bool bDisablePrintToLogMsgView;
	static bool bDisablePrintOnScreen;
	static FString ConsolePrefix;


	static void Print(FString LogMsg, bool bToConsole = true,bool bOnScreen = true);
	static void PrintWarn(FString LogMsg, bool bToConsole = true, bool bOnScreen = true);
	static void PrintError(FString LogMsg, bool bToConsole = true, bool bOnScreen = true);
};
