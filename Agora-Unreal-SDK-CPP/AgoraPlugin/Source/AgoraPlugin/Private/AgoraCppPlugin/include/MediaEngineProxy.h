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

class MediaEngineProxy : IMediaEngine{

public:
	MediaEngineProxy(IRtcEngine* Engine); 


	int registerAudioFrameObserver(IAudioFrameObserver* observer) override;


	int registerVideoFrameObserver(IVideoFrameObserver* observer) override;


	int registerVideoEncodedFrameObserver(IVideoEncodedFrameObserver* observer) override;


	int pushAudioFrame(IAudioFrameObserver::AudioFrame* frame, rtc::track_id_t trackId = 0) override;


	int pullAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int setExternalVideoSource(bool enabled, bool useTexture, EXTERNAL_VIDEO_SOURCE_TYPE sourceType = VIDEO_FRAME, rtc::SenderOptions encodedVideoOption = rtc::SenderOptions()) override;


	int setExternalAudioSource(bool enabled, int sampleRate, int channels, bool localPlayback = false, bool publish = true) __deprecated override;


	rtc::track_id_t createCustomAudioTrack(rtc::AUDIO_TRACK_TYPE trackType, const rtc::AudioTrackConfig& config) override;


	int destroyCustomAudioTrack(rtc::track_id_t trackId) override;


	int setExternalAudioSink(bool enabled, int sampleRate, int channels) override;


	int enableCustomAudioLocalPlayback(rtc::track_id_t trackId, bool enabled) override;


	int pushVideoFrame(agora::media::base::ExternalVideoFrame* frame, unsigned int videoTrackId = 0) override;


	int pushEncodedVideoImage(const uint8_t* imageBuffer, size_t length, const agora::rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo, unsigned int videoTrackId = 0) override;


	int addVideoFrameRenderer(IVideoFrameObserver* renderer) override;


	int removeVideoFrameRenderer(IVideoFrameObserver* renderer) override;


	void release() override;
	//~MediaEngineProxy();

private:
	VideoObserverInternal* VideoObserver;
	IMediaEngine* AgoraMediaEngine = nullptr;
};

}
}
}
