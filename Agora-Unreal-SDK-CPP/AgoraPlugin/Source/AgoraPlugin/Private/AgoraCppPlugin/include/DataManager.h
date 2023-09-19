#pragma once
#if AGORA_UESDK_ENABLE_VIDEO

#include "ICacheManager.h"

namespace agora {
	namespace rtc {
		namespace ue {

			class DataManager
			{
				DataManager();
			public:
				static DataManager* getInstance();
				ICacheManager* getCacheManager();

			public:
				ICacheManager* Cache;
			};

		}
	}
}

#endif