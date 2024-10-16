//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "../Private/AgoraCppPlugin/include/AgoraHeaderBase.h"

#include <functional>
#include <string>
namespace agora
{
	namespace rtc
	{
		namespace ue
		{
			AGORAPLUGIN_API agora::rtc::IRtcEngine* AGORA_CALL createAgoraRtcEngine();
			AGORAPLUGIN_API agora::rtc::IRtcEngineEx* AGORA_CALL createAgoraRtcEngineEx();
		}
	}
}