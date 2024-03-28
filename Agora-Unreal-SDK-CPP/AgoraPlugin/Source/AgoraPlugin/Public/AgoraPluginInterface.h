//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "../Private/AgoraCppPlugin/include/AgoraHeaderBase.h"

namespace agora
{
	namespace rtc
	{
		namespace ue
		{
			AGORAPLUGIN_API agora::rtc::IRtcEngine* AGORA_CALL createAgoraRtcEngine();
			AGORAPLUGIN_API agora::rtc::IRtcEngineEx* AGORA_CALL createAgoraRtcEngineEx();

			// could release AgoraRtcEngine or AgoraRtcEngineEx
			AGORAPLUGIN_API void AGORA_CALL releaseAgoraRtcEngine(bool sync = false);
		}
	}
}