// Copyright(c) 2024 Agora.io. All rights reserved.


#include "AgoraGameInstanceWithConsoleFunc.h"

void UAgoraGameInstanceWithConsoleFunc::SetRtcEngineParam(FString Param)
{
	int ret = AgoraUERtcEngine::Get()->setParameters(TCHAR_TO_UTF8(*Param));

	UE_LOG(LogTemp, Warning, TEXT("--- Cmd:%s exec:%d"), *FString(FUNCTION_MACRO), (int32)ret);
}
