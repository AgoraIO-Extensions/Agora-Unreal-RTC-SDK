
#pragma once

#include "CoreMinimal.h"
#include "SlateOptMacros.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include <memory>
#include "AgoraHeaderBase.h"
#include "CacheManagerImpl.h"
/**
 *
 */
namespace agora {
namespace rtc {
namespace ue {
    
using VideoFrame = media::IVideoFrameObserver::VideoFrame;

class VideoObserverInternal : public media::IVideoFrameObserver
{
public:

    VideoObserverInternal(media::IVideoFrameObserver* observer, ICacheManager* cache);

    virtual ~VideoObserverInternal() override;

    virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onScreenCaptureVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onPreEncodeScreenVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId) override;

    virtual bool onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame) override;

    virtual bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame) override;

    virtual bool onTranscodedVideoFrame(VideoFrame& videoFrame) override;

    virtual VIDEO_FRAME_PROCESS_MODE getVideoFrameProcessMode() override;

    virtual agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference()  override;

    virtual bool getRotationApplied() override;
    
    virtual uint32_t getObservedFramePosition() override;

    virtual bool isExternal() override;

    void registerVideoFrameObserver(media::IVideoFrameObserver* observer);
private:

    void setVideoFrame(VideoFrameIdentity *identity, VideoFrame* frame);

public:
    ICacheManager* AacheManager;
    media::IVideoFrameObserver* UserObserver;
};

}
}
}

