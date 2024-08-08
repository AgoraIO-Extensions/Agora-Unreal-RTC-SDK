#if AGORA_UESDK_ENABLE_VIDEO

#include "AgoraUEVideoFrameObserver.h"
#include "DataTypes.h"
#include "VideoFrameDataManager.h"

namespace agora {
	namespace rtc {
		namespace ue {

			AgoraUEVideoFrameObserver::AgoraUEVideoFrameObserver(media::IVideoFrameObserver* observer)
			{
				_NativeAgoraVideoObserver = observer;
			}

			AgoraUEVideoFrameObserver::~AgoraUEVideoFrameObserver()
			{
				_NativeAgoraVideoObserver = nullptr;
			}

#pragma region Overrride Agora Native Methods

			bool AgoraUEVideoFrameObserver::onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, VideoFrame& videoFrame)
			{
				VideoFrameDataManager::Get()->PushVideoFrame({ sourceType, 0, "" }, &videoFrame);

				// trigger native observer if it has been set
				if(_NativeAgoraVideoObserver != nullptr){
					_NativeAgoraVideoObserver->onCaptureVideoFrame(sourceType,videoFrame);
				}

				return true;
			}

			bool AgoraUEVideoFrameObserver::onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, VideoFrame& videoFrame)
			{
				VideoFrameDataManager::Get()->PushVideoFrame({ sourceType, 0, "" }, &videoFrame);

				// trigger native observer if it has been set
				if (_NativeAgoraVideoObserver != nullptr) {
					_NativeAgoraVideoObserver->onPreEncodeVideoFrame(sourceType, videoFrame);
				}

				return true;
			}

			bool AgoraUEVideoFrameObserver::onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId)
			{
				VideoFrameDataManager::Get()->PushVideoFrame({ VIDEO_SOURCE_MEDIA_PLAYER,static_cast<uid_t>(mediaPlayerId),""}, &videoFrame);

				// trigger native observer if it has been set
				if (_NativeAgoraVideoObserver != nullptr) {
					_NativeAgoraVideoObserver->onMediaPlayerVideoFrame(videoFrame, mediaPlayerId);
				}

				return true;
			}

			bool AgoraUEVideoFrameObserver::onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)
			{
				VideoFrameDataManager::Get()->PushVideoFrame({ VIDEO_SOURCE_REMOTE,remoteUid,channelId}, &videoFrame);

				// trigger native observer if it has been set
				if (_NativeAgoraVideoObserver != nullptr) {
					_NativeAgoraVideoObserver->onRenderVideoFrame(channelId, remoteUid, videoFrame);
				}

				return true;
			}

			bool AgoraUEVideoFrameObserver::onTranscodedVideoFrame(VideoFrame& videoFrame)
			{
				VideoFrameDataManager::Get()->PushVideoFrame({ VIDEO_SOURCE_TRANSCODED,0,""}, &videoFrame);

				// trigger native observer if it has been set
				if (_NativeAgoraVideoObserver != nullptr) {
					_NativeAgoraVideoObserver->onTranscodedVideoFrame(videoFrame);
				}

				return true;
			}

			agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE AgoraUEVideoFrameObserver::getVideoFrameProcessMode()
			{
				return PROCESS_MODE_READ_ONLY;
			}

			agora::media::base::VIDEO_PIXEL_FORMAT AgoraUEVideoFrameObserver::getVideoFormatPreference()
			{
				return agora::media::base::VIDEO_PIXEL_RGBA;
			}

			bool AgoraUEVideoFrameObserver::getRotationApplied()
			{
				return true;
			}

			bool AgoraUEVideoFrameObserver::getMirrorApplied()
			{
				return false;
			}

			uint32_t AgoraUEVideoFrameObserver::getObservedFramePosition()
			{
				return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;
			}

			bool AgoraUEVideoFrameObserver::isExternal()
			{
				return true;
			}

#pragma endregion Overrride Agora Native Methods

		}
	}
}

#endif

