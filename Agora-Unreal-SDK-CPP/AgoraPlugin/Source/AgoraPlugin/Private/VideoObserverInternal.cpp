#include "Include/VideoObserverInternal.h"

namespace agora {
namespace rtc {
namespace ue {

VideoObserverInternal::VideoObserverInternal(media::IVideoFrameObserver* observer, ICacheManager* cache) 
{
    AacheManager = cache;
    UserObserver = observer;
  
}

VideoObserverInternal::~VideoObserverInternal()
{

}

bool VideoObserverInternal::onCaptureVideoFrame(VideoFrame& videoFrame)
{
    VideoFrameIdentity config{VIDEO_SOURCE_CAMERA_PRIMARY, 0, ""};
    setVideoFrame(&config, &videoFrame);
    if (UserObserver != nullptr) UserObserver->onCaptureVideoFrame(videoFrame);
    return true; 
}

bool VideoObserverInternal::onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)
{
    VideoFrameIdentity config{VIDEO_SOURCE_REMOTE, remoteUid, channelId };
    setVideoFrame(&config, &videoFrame);
    if (UserObserver != nullptr) UserObserver->onRenderVideoFrame(channelId, remoteUid, videoFrame);
    return true; 
}

bool VideoObserverInternal::onPreEncodeVideoFrame(VideoFrame& videoFrame)
{
    return true; 
}

bool VideoObserverInternal::onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame)
{
    VideoFrameIdentity config{VIDEO_SOURCE_CAMERA_SECONDARY, 0, ""};
    setVideoFrame(&config, &videoFrame);
    return true; 
}

bool VideoObserverInternal::onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame)
{
    return true;
}

bool VideoObserverInternal::onScreenCaptureVideoFrame(VideoFrame& videoFrame)
{
    VideoFrameIdentity config{VIDEO_SOURCE_SCREEN_PRIMARY, 0, ""};
    setVideoFrame(&config, &videoFrame);
    return true; 
}

bool VideoObserverInternal::onPreEncodeScreenVideoFrame(VideoFrame& videoFrame)
{
    return true;
}

bool VideoObserverInternal::onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId)
{
    unsigned int MediaplayId = (unsigned int)mediaPlayerId;

    VideoFrameIdentity config{VIDEO_SOURCE_MEDIA_PLAYER,MediaplayId, ""};
    setVideoFrame(&config, &videoFrame);
    return true; 
}

bool VideoObserverInternal::onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame)
{
    VideoFrameIdentity config{VIDEO_SOURCE_SCREEN_SECONDARY, 0, ""};
    setVideoFrame(&config, &videoFrame);
    return true; 
}

bool VideoObserverInternal::onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame)
{
    return true;
}

bool VideoObserverInternal::onTranscodedVideoFrame(VideoFrame& videoFrame)
{
    VideoFrameIdentity config{VIDEO_SOURCE_TRANSCODED, 0, ""};
    
    setVideoFrame(&config, &videoFrame);
    return true; 
}

agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE VideoObserverInternal::getVideoFrameProcessMode()
{
    return PROCESS_MODE_READ_ONLY;
}

agora::media::base::VIDEO_PIXEL_FORMAT VideoObserverInternal::getVideoFormatPreference()
{
    return agora::media::base::VIDEO_PIXEL_RGBA;
}

bool VideoObserverInternal::getRotationApplied()
{
    return true;
}

bool VideoObserverInternal::getMirrorApplied()
{
    return false;
}

uint32_t VideoObserverInternal::getObservedFramePosition()
{
    return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;
}

bool VideoObserverInternal::isExternal()
{
    return true;
}

void VideoObserverInternal::setVideoFrame(VideoFrameIdentity *identity, VideoFrame* frame)
{
    if (AacheManager) {
        AacheManager->pushVideo(identity, frame);
    }
}

void VideoObserverInternal::registerVideoFrameObserver(media::IVideoFrameObserver* observer)
{
    UserObserver = observer;
}


} //namespace ue
} // namespace rtc
} //namespace agora
