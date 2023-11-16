//  Copyright (c) 2023 Agora.io. All rights reserved.

#if AGORA_UESDK_ENABLE_VIDEO

#include "AgoraCppPlugin/Include/DataManager.h"

namespace agora {
	namespace rtc {
		namespace ue {

			DataManager::DataManager()
			{
				Cache = createCacheManager();
			}

			DataManager* DataManager::getInstance()
			{
				static DataManager Inst;
				return &Inst;
			}

			ICacheManager* DataManager::getCacheManager()
			{
				return Cache;
			}

		}
	}
}

#endif