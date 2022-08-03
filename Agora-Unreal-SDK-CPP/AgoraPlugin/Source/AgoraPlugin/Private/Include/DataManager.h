#pragma once
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
	ICacheManager* cache_;
};

}
}
}
