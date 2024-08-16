// Copyright(c) 2024 Agora.io. All rights reserved.


#include "BFL_UtilityTool.h"

bool UBFL_UtilityTool::IsAgoraAudioOnlySDK()
{
#if AGORA_UESDK_AUDIO_ONLY
	return true;
#else
	return false;
#endif

}
