#pragma once
#include "AgoraHeaderBase.h"
#include <memory>

namespace agora {
namespace rtc {
namespace ue {

using namespace media;
using VideoFrame = media::IVideoFrameObserver::VideoFrame;

typedef struct VideoFrameIdentity {

    VIDEO_SOURCE_TYPE Type;
    unsigned int Id;
    const char* Channel;

    bool operator <(const VideoFrameIdentity& other) const
    {
        if (Type < other.Type)
        {
            return true;
        }
        else if (Type == other.Type)
        {
            if (Id < other.Id)
            {
                return true;
            }
            else if (Id == other.Id)
            {
                if (strcmp(Channel, other.Channel) != 0)
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
	virtual void enableVideoFrameObserver(const VideoFrameIdentity *Identity) = 0;
	virtual void disableVideoFrameObserver(const VideoFrameIdentity *Identity) = 0;
	virtual int pushVideo(const VideoFrameIdentity *Identity, VideoFrame* Frame) = 0;
	virtual int popVideo(const VideoFrameIdentity *Identity, VideoFrame*& Frame) = 0;
	virtual void clear(const VideoFrameIdentity *Identity) = 0;
	virtual void clearAll() = 0;
};

ICacheManager* createCacheManager();

}
}
}
