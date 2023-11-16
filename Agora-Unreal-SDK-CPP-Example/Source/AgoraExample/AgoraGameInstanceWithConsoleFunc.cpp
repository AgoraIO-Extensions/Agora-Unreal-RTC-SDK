// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraGameInstanceWithConsoleFunc.h"

void UAgoraGameInstanceWithConsoleFunc::SetRtcEngineParam(FString Param)
{
	agora::rtc::IRtcEngine* RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	
	int ret = RtcEngineProxy->setParameters(TCHAR_TO_UTF8(*Param));

	UE_LOG(LogTemp, Warning, TEXT("--- Cmd:%s exec:%d"), *FString(FUNCTION_MACRO), (int32)ret);
}
