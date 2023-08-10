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


int MediaEngineProxy::registerAudioFrameObserver(IAudioFrameObserver* observer)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->registerAudioFrameObserver(observer);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::registerVideoFrameObserver(IVideoFrameObserver* observer)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->registerVideoFrameObserver(observer);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::registerVideoEncodedFrameObserver(IVideoEncodedFrameObserver* observer)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->registerVideoEncodedFrameObserver(observer);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::pushAudioFrame(IAudioFrameObserver::AudioFrame* frame, rtc::track_id_t trackId /*= 0*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->pushAudioFrame(frame, trackId);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::pullAudioFrame(IAudioFrameObserver::AudioFrame* frame)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->pullAudioFrame(frame);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::setExternalVideoSource(bool enabled, bool useTexture, EXTERNAL_VIDEO_SOURCE_TYPE sourceType /*= VIDEO_FRAME*/, rtc::SenderOptions encodedVideoOption /*= rtc::SenderOptions()*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->setExternalVideoSource(enabled, useTexture, sourceType ,  encodedVideoOption);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::setExternalAudioSource(bool enabled, int sampleRate, int channels, bool localPlayback /*= false*/, bool publish /*= true*/) __deprecated
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->setExternalAudioSource(enabled, sampleRate, channels, localPlayback, publish);
		return ret;
	}
	return -ERROR_NULLPTR;
}


agora::rtc::track_id_t MediaEngineProxy::createCustomAudioTrack(rtc::AUDIO_TRACK_TYPE trackType, const rtc::AudioTrackConfig& config)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->createCustomAudioTrack(trackType, config);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::destroyCustomAudioTrack(rtc::track_id_t trackId)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->destroyCustomAudioTrack(trackId);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::setExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->setExternalAudioSink(enabled, sampleRate, channels);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::enableCustomAudioLocalPlayback(rtc::track_id_t trackId, bool enabled)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->enableCustomAudioLocalPlayback(trackId, enabled);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::pushVideoFrame(agora::media::base::ExternalVideoFrame* frame, unsigned int videoTrackId /*= 0*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->pushVideoFrame(frame, videoTrackId);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::pushEncodedVideoImage(const uint8_t* imageBuffer, size_t length, const agora::rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo, unsigned int videoTrackId /*= 0*/)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->pushEncodedVideoImage(imageBuffer,length, videoEncodedFrameInfo, videoTrackId);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::addVideoFrameRenderer(IVideoFrameObserver* renderer)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->addVideoFrameRenderer(renderer);
		return ret;
	}
	return -ERROR_NULLPTR;
}


int MediaEngineProxy::removeVideoFrameRenderer(IVideoFrameObserver* renderer)
{
	if (AgoraMediaEngine != nullptr)
	{
		int ret = AgoraMediaEngine->removeVideoFrameRenderer(renderer);
		return ret;
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
