// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraGameInstanceWithConsoleFunc.h"

void UAgoraGameInstanceWithConsoleFunc::SetRtcEngineParam(FString Param)
{
	agora::rtc::IRtcEngine* RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	
	int ret = RtcEngineProxy->setParameters(TCHAR_TO_UTF8(*Param));

	UE_LOG(LogTemp, Warning, TEXT("--- Cmd:%s exec:%d"), *FString(FUNCTION_MACRO), (int32)ret);
}

void UAgoraGameInstanceWithConsoleFunc::DumpAudioFrame()
{
	agora::rtc::IRtcEngine* RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	//RtcEngineProxy->setParameters("{\"che.audio.start.predump\":\"true\"}");
	int ret = RtcEngineProxy->setParameters("{\"che.audio.frame_dump\":{\"location\":\"all\",\"action\":\"start\",\"max_size_bytes\":\"120000000\",\"uuid\":\"123456789\",\"duration\":\"1200000\"}}");

	UE_LOG(LogTemp, Warning, TEXT("--- Cmd:%s exec:%d"), *FString(FUNCTION_MACRO), (int32)ret);
}
