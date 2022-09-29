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
		VideoFrame* SwipFrame;
		VideoFrame* CurrentFrame;
		bool bIsFresh = false;
	};

	typedef std::map<VideoFrameIdentity, bool> MapStatus;
	typedef std::map<VideoFrameIdentity, FramesInfo* > VideoFrameMap;

	class CacheManagerImpl : public ICacheManager
	{
	public:
		virtual void enableVideoFrameObserver(const VideoFrameIdentity* Identity) override;
		virtual void disableVideoFrameObserver(const VideoFrameIdentity* Identity) override;
		virtual int pushVideo(const VideoFrameIdentity* Identity, VideoFrame* Frame) override;
		virtual int popVideo(const VideoFrameIdentity* Identity, VideoFrame*& Frame) override;
		virtual void clear(const VideoFrameIdentity* Identity) override;
		virtual void clearAll() override;
		void swap(VideoFrame*& SwipFrame, VideoFrame*& CurrentFrame);
	private:
		std::recursive_mutex Mutex;
		MapStatus CacheMapStatus;
		VideoFrameMap DataMap;
	};

}
}
}

