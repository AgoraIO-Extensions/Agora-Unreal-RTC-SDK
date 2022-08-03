#include "Include/MediaEngineProxy.h"
#include "Include/AgoraHeaderBase.h"
#include "Include/RtcEngineProxy.h"
#include "Include/VideoObserverInternal.h"
#include "CoreMinimal.h"


namespace agora
{
namespace rtc
{
namespace ue
{

MediaEngineProxy::MediaEngineProxy(IRtcEngine* engine)
{
	if (!_agoraMediaEngine) {
		engine->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
			(void**)&_agoraMediaEngine);
	}

	_videoObserver = new VideoObserverInternal(nullptr, DataManager::getInstance()->getCacheManager());
	_agoraMediaEngine->registerVideoFrameObserver(_videoObserver);
}

MediaEngineProxy::~MediaEngineProxy()
{
	if (_agoraMediaEngine)
	{
		_agoraMediaEngine->release();
		_agoraMediaEngine = nullptr;
	}

	if (_videoObserver) {
		delete(_videoObserver);
	}
}

void MediaEngineProxy::registerVideoFrameObserver(media::IVideoFrameObserver* observer)
{
	_videoObserver->registerVideoFrameObserver(observer);
}

}
}
}
