#include "Include/DataManager.h"

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
