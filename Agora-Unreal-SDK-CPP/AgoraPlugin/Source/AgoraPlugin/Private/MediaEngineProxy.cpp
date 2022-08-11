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

MediaEngineProxy::MediaEngineProxy(IRtcEngine* Engine)
{
	if (!AgoraMediaEngine) {
		Engine->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
			(void**)&AgoraMediaEngine);
	}

	VideoObserver = new VideoObserverInternal(nullptr, DataManager::getInstance()->getCacheManager());
	AgoraMediaEngine->registerVideoFrameObserver(VideoObserver);
}

MediaEngineProxy::~MediaEngineProxy()
{
	if (AgoraMediaEngine)
	{
		AgoraMediaEngine->release();
		AgoraMediaEngine = nullptr;
	}

	if (VideoObserver) {
		delete(VideoObserver);
	}
}

void MediaEngineProxy::registerVideoFrameObserver(media::IVideoFrameObserver* Observer)
{
	if (VideoObserver != nullptr)
	{
		VideoObserver->registerVideoFrameObserver(Observer);
	}

}

}
}
}
