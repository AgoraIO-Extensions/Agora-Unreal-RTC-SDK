// Copyright(c) 2024 Agora.io. All rights reserved.
#include "UtilityAgoraBPuLogger.h"
#include "Engine/Engine.h"

bool UAgoraBPuLogger::bDisablePrintToConsole = false;
bool UAgoraBPuLogger::bDisablePrintToLogMsgView = false;
bool UAgoraBPuLogger::bDisablePrintOnScreen = false;
FString UAgoraBPuLogger::ConsolePrefix = "[Agora UE Plugin]";

void UAgoraBPuLogger::Print(FString LogMsg, bool bToConsole /*= true*/, bool bOnScreen /*= true*/)
{
	if (bToConsole && !bDisablePrintToConsole) {
		// Print Log To Console
		UE_LOG(LogAgora, Display, TEXT("%s %s"), *ConsolePrefix, *LogMsg);
	}

	if (bOnScreen && !bDisablePrintOnScreen) {
		// Print Log To LogMsgView
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, LogMsg);
	}
}

void UAgoraBPuLogger::PrintWarn(FString LogMsg, bool bToConsole /*= true*/, bool bOnScreen /*= true*/)
{
	if (bToConsole && !bDisablePrintToConsole) {
		// Print Log To Console
		UE_LOG(LogAgora, Warning, TEXT("%s %s"), *ConsolePrefix, *LogMsg);
	}

	if (bOnScreen && !bDisablePrintOnScreen) {
		// Print Log To LogMsgView
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, LogMsg);
	}
}

void UAgoraBPuLogger::PrintError(FString LogMsg, bool bToConsole /*= true*/, bool bOnScreen /*= true*/)
{
	if (bToConsole && !bDisablePrintToConsole) {
		// Print Log To Console
		UE_LOG(LogTemp, Error, TEXT("%s %s"), *ConsolePrefix, *LogMsg);
	}

	if (bOnScreen && !bDisablePrintOnScreen) {
		// Print Log To LogMsgView
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, LogMsg);
	}
}

