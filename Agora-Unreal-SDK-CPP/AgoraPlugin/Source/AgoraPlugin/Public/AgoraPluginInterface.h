#pragma once

#include "../Private/AgoraCppPlugin/Include/AgoraHeaderBase.h"

namespace agora
{
	namespace rtc
	{
		namespace ue
		{
            AGORAPLUGIN_API agora::rtc::IRtcEngine* AGORA_CALL createAgoraRtcEngine();
        }
    }
}