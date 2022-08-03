#pragma once
#include <mutex>
#include <memory>
#include <map>
#include <queue>
#include "AgoraHeaderBase.h"
#include "Containers/CircularQueue.h"
#include "ICacheManager.h"

#define MAX_CACHE_SIZE 1;

namespace agora {
namespace rtc {
namespace ue {

using namespace media;
using VideoFrame = media::IVideoFrameObserver::VideoFrame;

struct FramesInfo
{
	VideoFrame* swipFrame;
	VideoFrame* currentFrame;
	bool isFresh=false;
};

typedef std::map<VideoFrameIdentity, bool> MapStatus;
typedef std::map<VideoFrameIdentity, FramesInfo* > VideoFrameMap;

class CacheManagerImpl : public ICacheManager
{
public:
	virtual void enableVideoFrameObserver(const VideoFrameIdentity *identity) override;
	virtual void disableVideoFrameObserver(const VideoFrameIdentity *identity) override;
	virtual int pushVideo(const VideoFrameIdentity *identity, VideoFrame* frame) override;
	virtual int popVideo(const VideoFrameIdentity *identity, VideoFrame*& frame) override;
	virtual void clear(const VideoFrameIdentity *identity) override;
	virtual void clearAll() override;
	void swap(VideoFrame*& swipFrame, VideoFrame*& currentFrame);
private:
	std::recursive_mutex mutex_;
	MapStatus mapStatus_;
	VideoFrameMap data_map_;
};

}
}
}

