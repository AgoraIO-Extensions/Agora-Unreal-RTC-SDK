#pragma once
#include "AgoraHeaderBase.h"
#include <memory>

namespace agora {
namespace rtc {
namespace ue {

using namespace media;
using VideoFrame = media::IVideoFrameObserver::VideoFrame;

typedef struct VideoFrameIdentity {

    VIDEO_SOURCE_TYPE type;
    unsigned int id;
    const char* channel;

    bool operator <(const VideoFrameIdentity& other) const
    {
        if (type < other.type)
        {
            return true;
        }
        else if (type == other.type)
        {
            if (id < other.id)
            {
                return true;
            }
            else if (id == other.id)
            {
                if (strcmp(channel, other.channel) != 0)
                {
                    return true;
                }
            }

        }
        return false;
    }
} VideoFrameIdentity;

class ICacheManager
{
public:
	virtual ~ICacheManager() {}
	virtual void enableVideoFrameObserver(const VideoFrameIdentity *identity) = 0;
	virtual void disableVideoFrameObserver(const VideoFrameIdentity *identity) = 0;
	virtual int pushVideo(const VideoFrameIdentity *identity, VideoFrame* frame) = 0;
	virtual int popVideo(const VideoFrameIdentity *identity, VideoFrame*& frame) = 0;
	virtual void clear(const VideoFrameIdentity *identity) = 0;
	virtual void clearAll() = 0;
};

ICacheManager* createCacheManager();

}
}
}
