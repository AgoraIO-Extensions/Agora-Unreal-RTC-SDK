#include "AgoraCppPlugin/Include/MediaEngineProxy.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "AgoraCppPlugin/Include/RtcEngineProxy.h"
#include "AgoraCppPlugin/Include/VideoObserverInternal.h"
#include "CoreMinimal.h"


namespace agora
{
namespace rtc
{
namespace ue
{

MediaEngineProxy::MediaEngineProxy(IRtcEngine* Engine)
{
	if (AgoraMediaEngine == nullptr) {
		Engine->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
			(void**)&AgoraMediaEngine);
	}

	VideoObserver = new VideoObserverInternal(nullptr, DataManager::getInstance()->getCacheManager());
	AgoraMediaEngine->registerVideoFrameObserver(VideoObserver);
}


int MediaEngineProxy::registerVideoFrameObserver(media::IVideoFrameObserver* Observer)
{
	if (VideoObserver != nullptr)
	{
		VideoObserver->registerVideoFrameObserver(Observer);
	}
	return 0;
}


int MediaEngineProxy::registerAudioFrameObserver(IAudioFrameObserver* observer)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->registerAudioFrameObserver(observer);
	}
	return -ERROR_NULLPTR;
}

int MediaEngineProxy::registerVideoEncodedFrameObserver(IVideoEncodedFrameObserver* observer)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->registerVideoEncodedFrameObserver(observer);
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::pushAudioFrame(IAudioFrameObserver::AudioFrame* frame, rtc::track_id_t trackId /*= 0*/)
{
	if (VideoObserver != nullptr)
	{
		return AgoraMediaEngine->pushAudioFrame(frame, trackId);
	}

	return -ERROR_NULLPTR;
}

int MediaEngineProxy::pushCaptureAudioFrame(IAudioFrameObserver::AudioFrame* frame)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->pushCaptureAudioFrame(frame);
	}
	return -ERROR_NULLPTR;
}



int MediaEngineProxy::pushReverseAudioFrame(IAudioFrameObserver::AudioFrame* frame)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->pushReverseAudioFrame(frame);
	}
	return -ERROR_NULLPTR;
}



int MediaEngineProxy::pullAudioFrame(IAudioFrameObserver::AudioFrame* frame)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->pullAudioFrame(frame);
	}
	return -ERROR_NULLPTR;
}




int MediaEngineProxy::setExternalVideoSource(bool enabled, bool useTexture, EXTERNAL_VIDEO_SOURCE_TYPE sourceType /*= VIDEO_FRAME*/, rtc::SenderOptions encodedVideoOption /*= rtc::SenderOptions()*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->setExternalVideoSource(enabled,useTexture,sourceType,encodedVideoOption);
	}
	return -ERROR_NULLPTR;
}

int MediaEngineProxy::setExternalAudioSource(bool enabled, int sampleRate, int channels, bool localPlayback /*= false*/, bool publish /*= true*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->setExternalAudioSource(enabled, sampleRate, channels, localPlayback, publish);
	}
	return -ERROR_NULLPTR;
}


agora::rtc::track_id_t MediaEngineProxy::createCustomAudioTrack(rtc::AUDIO_TRACK_TYPE trackType, const rtc::AudioTrackConfig& config)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->createCustomAudioTrack(trackType, config);
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::destroyCustomAudioTrack(rtc::track_id_t trackId)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->destroyCustomAudioTrack(trackId);
	}
	return -ERROR_NULLPTR;
}

int MediaEngineProxy::setExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->setExternalAudioSink(enabled, sampleRate, channels);
	}
	return -ERROR_NULLPTR;
}

int MediaEngineProxy::enableCustomAudioLocalPlayback(rtc::track_id_t trackId, bool enabled)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->enableCustomAudioLocalPlayback(trackId, enabled);
	}
	return -ERROR_NULLPTR;
}

int MediaEngineProxy::pushVideoFrame(agora::media::base::ExternalVideoFrame* frame, unsigned int videoTrackId /*= 0*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->pushVideoFrame(frame,videoTrackId);
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::pushEncodedVideoImage(const uint8_t* imageBuffer, size_t length, const agora::rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo, unsigned int videoTrackId /*= 0*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		return AgoraMediaEngine->pushEncodedVideoImage(imageBuffer,length,videoEncodedFrameInfo,videoTrackId);
	}
	return -ERROR_NULLPTR;
}


void MediaEngineProxy::release()
{
	if (AgoraMediaEngine != nullptr)
	{
		AgoraMediaEngine->release();
	}
	if (VideoObserver!=nullptr) 
	{
		delete(VideoObserver);
	}
}

}
}
}
