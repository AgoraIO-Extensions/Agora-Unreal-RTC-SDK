// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_UtilityTool.h"

bool UBFL_UtilityTool::IsAgoraAudioOnlySDK()
{
#if AGORA_UESDK_AUDIO_ONLY
	return true;
#else
	return false;
#endif

}
