#include "Include/DataManager.h"

namespace agora {
namespace rtc {
namespace ue {

DataManager::DataManager()
{
	cache_ = createCacheManager();
}

DataManager* DataManager::getInstance()
{
	static DataManager inst;
	return &inst;
}

ICacheManager* DataManager::getCacheManager()
{
	return cache_;
}

}
}
}
