#pragma once
#include "AgoraHeaderBase.h"
#include "RtcEngineProxy.h"
#include "MediaEngineProxy.h"
#include "VideoObserverInternal.h"

namespace agora
{
namespace rtc
{
namespace ue
{

using namespace agora::media;

class MediaEngineProxy {

public:
	MediaEngineProxy(IRtcEngine* Engine); 

	~MediaEngineProxy();

public:
	void registerVideoFrameObserver(media::IVideoFrameObserver* Observer);

private:
	VideoObserverInternal* VideoObserver;
	IMediaEngine* AgoraMediaEngine = nullptr;
};

}
}
}
