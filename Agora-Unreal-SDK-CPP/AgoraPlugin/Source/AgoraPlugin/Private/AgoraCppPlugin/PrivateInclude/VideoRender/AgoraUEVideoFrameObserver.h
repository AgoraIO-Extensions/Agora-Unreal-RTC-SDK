#pragma once
#if AGORA_UESDK_ENABLE_VIDEO
#include "AgoraHeaderBase.h"

namespace agora {
	namespace rtc {
		namespace ue {


			class AgoraUEVideoFrameObserver : public media::IVideoFrameObserver {

			public:

				AgoraUEVideoFrameObserver(media::IVideoFrameObserver* observer);

				virtual ~AgoraUEVideoFrameObserver() override;

#pragma region Overrride Agora Native Methods
				virtual bool onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, VideoFrame& videoFrame)  override;

				virtual bool onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, VideoFrame& videoFrame) override;

				virtual bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId) override;

				virtual bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame) override;

				virtual bool onTranscodedVideoFrame(VideoFrame& videoFrame) override;

				virtual VIDEO_FRAME_PROCESS_MODE getVideoFrameProcessMode() override;

				virtual agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference()  override;

				virtual bool getRotationApplied() override;

				virtual bool getMirrorApplied() override;

				virtual uint32_t getObservedFramePosition() override;

				virtual bool isExternal() override;
#pragma endregion Agora Native Methods

			
			private:
				media::IVideoFrameObserver* _NativeAgoraVideoObserver = nullptr;
			};
		}
	}
}

#endif