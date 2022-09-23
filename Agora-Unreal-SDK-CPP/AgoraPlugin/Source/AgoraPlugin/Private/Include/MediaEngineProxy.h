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

	~MediaEngineProxy();

	int registerVideoFrameObserver(IVideoFrameObserver* observer) override;


	int registerAudioFrameObserver(IAudioFrameObserver* observer) override;


	int registerVideoEncodedFrameObserver(IVideoEncodedFrameObserver* observer) override;


	int pushAudioFrame(MEDIA_SOURCE_TYPE type, IAudioFrameObserver::AudioFrame* frame, bool wrap = false, int sourceId = 0) override;


	int pushCaptureAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int pushReverseAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int pushDirectAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int pullAudioFrame(IAudioFrameObserver::AudioFrame* frame) override;


	int setExternalVideoSource(bool enabled, bool useTexture, EXTERNAL_VIDEO_SOURCE_TYPE sourceType = VIDEO_FRAME, rtc::SenderOptions encodedVideoOption = rtc::SenderOptions()) override;


	int setExternalAudioSource(bool enabled, int sampleRate, int channels, int sourceNumber = 1, bool localPlayback = false, bool publish = true) override;


	int setExternalAudioSink(bool enabled, int sampleRate, int channels) override;


	int enableCustomAudioLocalPlayback(int sourceId, bool enabled) override;


	int setDirectExternalAudioSource(bool enable, bool localPlayback = false) override;


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
