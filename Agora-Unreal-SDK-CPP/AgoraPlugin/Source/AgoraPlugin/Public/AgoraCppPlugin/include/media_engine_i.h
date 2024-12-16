//
//  Agora Media SDK
//
//  Copyright (c) 2015 Agora IO. All rights reserved.
//

#pragma once

#include "AgoraMediaBase.h"
#include "api/video/video_frame.h"
#include "IAgoraMediaEngine.h"

namespace agora {

namespace rtc {
struct RtcConnection;
}

namespace media {
namespace base {
class IVideoFrameObserverEx : public IVideoFrameObserver {
 public:
  virtual ~IVideoFrameObserverEx() {}
  void onFrame(const VideoFrame* frame) final {}
  bool isExternal() final { return false; }
  virtual void onFrame(const webrtc::VideoFrame& frame) = 0;
};
}

/**
 * The IVideoFrameObserverEx class.
 */
class IVideoFrameObserverEx : public IVideoFrameObserver {
 public:
  virtual ~IVideoFrameObserverEx() {}

  bool onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE type, VideoFrame& videoFrame) final { return false; }
  bool onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE type, VideoFrame& videoFrame) final { return false; }

  bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid,
                          VideoFrame& videoFrame) final { return false; }

  bool onTranscodedVideoFrame(VideoFrame& videoFrame) final { return false; }
  bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId) final { return false; }
  bool isExternal() final { return false; }

  virtual bool onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE type, webrtc::VideoFrame& videoFrame) { return false; }
  virtual bool onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE type, webrtc::VideoFrame& videoFrame) { return false; }

  virtual bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid,
                                  webrtc::VideoFrame& videoFrame) { return false; }

  virtual bool onTranscodedVideoFrame(webrtc::VideoFrame& videoFrame) { return false; }
  virtual bool onMediaPlayerVideoFrame(webrtc::VideoFrame& videoFrame, int mediaPlayerId) { return false; }
};

/**
 * The IMediaEngineEx class
 */
class IMediaEngineEx : public IMediaEngine {
 public:
  using IMediaEngine::registerAudioFrameObserver;
  using IMediaEngine::registerVideoFrameObserver;
  using IMediaEngine::registerVideoEncodedFrameObserver;
  using IMediaEngine::pushEncodedVideoImage;

  virtual int pushVideoFrameEx(const webrtc::VideoFrame& frame, unsigned int video_track_id = 0) = 0;

  virtual int enableDualStreamModeEx(bool enabled, const rtc::SimulcastStreamConfig& streamConfig,
                             const rtc::RtcConnection& connection) = 0;
  /**
   * Deprecated by IRtcEngine::setVideoEncoderConfiguration.
   */
  virtual int setExternalVideoConfigEx(const rtc::VideoEncoderConfiguration& config) = 0;
  virtual int setExternalVideoConfigEx(const rtc::VideoEncoderConfiguration& config, const rtc::RtcConnection& connection) = 0;

  ~IMediaEngineEx() override = default;
};

}  // namespace media
}  // namespace agora
