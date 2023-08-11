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

	//~MediaEngineProxy();

	int registerVideoFrameObserver(IVideoFrameObserver* observer) override;


	int registerAudioFrameObserver(IAudioFrameObserver* observer) override;


	int registerVideoEncodedFrameObserver(IVideoEncodedFrameObserver* observer) override;


	virtual int pushAudioFrame(IAudioFrameObserver::AudioFrame* frame, rtc::track_id_t trackId = 0) override;


	int pushCaptureAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int pushReverseAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int pullAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int setExternalVideoSource(bool enabled, bool useTexture, EXTERNAL_VIDEO_SOURCE_TYPE sourceType = VIDEO_FRAME, rtc::SenderOptions encodedVideoOption = rtc::SenderOptions()) override;


	virtual int setExternalAudioSource(bool enabled, int sampleRate, int channels, bool localPlayback = false, bool publish = true) override;


	virtual rtc::track_id_t createCustomAudioTrack(rtc::AUDIO_TRACK_TYPE trackType, const rtc::AudioTrackConfig& config) override;


	virtual int destroyCustomAudioTrack(rtc::track_id_t trackId) override;


	int setExternalAudioSink(bool enabled, int sampleRate, int channels) override;


	int enableCustomAudioLocalPlayback(rtc::track_id_t trackId, bool enabled) override;


	int pushVideoFrame(agora::media::base::ExternalVideoFrame* frame, unsigned int videoTrackId = 0) override;


	int pushEncodedVideoImage(const uint8_t* imageBuffer, size_t length, const agora::rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo, unsigned int videoTrackId = 0) override;


	void release() override;

private:
	VideoObserverInternal* VideoObserver;
	IMediaEngine* AgoraMediaEngine = nullptr;
};

}
}
}
