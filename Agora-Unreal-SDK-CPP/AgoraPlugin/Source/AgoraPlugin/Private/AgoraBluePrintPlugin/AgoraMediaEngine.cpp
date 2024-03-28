//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraMediaEngine.h"


int UIAgoraMediaEngine::RegisterAudioFrameObserver(UIAudioFrameObserver* observer)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		return MediaEngine->registerAudioFrameObserver(observer);
	}
	return ret;
}

int UIAgoraMediaEngine::RegisterVideoFrameObserver(UIVideoFrameObserver* observer)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		return MediaEngine->registerVideoFrameObserver(observer);
	}
	return ret;
}

int UIAgoraMediaEngine::RegisterFaceInfoObserver(UIFaceInfoObserver* observer)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		ret = MediaEngine->registerFaceInfoObserver(observer);
	}
	return ret;
}

int UIAgoraMediaEngine::PushAudioFrame(const FAudioFrame& frame, int64 trackId)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		agora::media::IAudioFrameObserver::AudioFrame AgoraAudioFrame = frame.CreateAgoraData();
		agora::rtc::track_id_t AgoraTrackId = static_cast<agora::rtc::track_id_t>(trackId);
		ret = MediaEngine->pushAudioFrame(&AgoraAudioFrame, AgoraTrackId);
		frame.FreeAgoraData(AgoraAudioFrame);
	}
	return ret;
}




int UIAgoraMediaEngine::PullAudioFrame(const FAudioFrame& frame)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		agora::media::IAudioFrameObserver::AudioFrame AgoraAudioFrame = frame.CreateAgoraData();
		ret = MediaEngine->pullAudioFrame(&AgoraAudioFrame);
		frame.FreeAgoraData(AgoraAudioFrame);
	}
	return ret;
}


int64 UIAgoraMediaEngine::CreateCustomAudioTrack(FENUMWRAP_AUDIO_TRACK_TYPE trackType, const FAudioTrackConfig& config)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		agora::rtc::AudioTrackConfig AgoraConfig = config.CreateAgoraData();
		ret = MediaEngine->createCustomAudioTrack(trackType.GetRawValue(), AgoraConfig);
		config.FreeAgoraData(AgoraConfig);
	}
	return ret;
}


int UIAgoraMediaEngine::DestroyCustomAudioTrack(int64 trackId)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{
		agora::rtc::track_id_t AgoraTrackId = static_cast<agora::rtc::track_id_t>(trackId);
		ret = MediaEngine->destroyCustomAudioTrack(AgoraTrackId);
	}
	return ret;
}

int UIAgoraMediaEngine::SetExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{

		ret = MediaEngine->setExternalAudioSink(enabled, sampleRate,channels);
	}
	return ret;
}

int UIAgoraMediaEngine::AddVideoFrameRenderer(UIVideoFrameObserver* renderer)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{

		ret = MediaEngine->addVideoFrameRenderer(renderer);
	}
	return ret;
}

int UIAgoraMediaEngine::RemoveVideoFrameRenderer(UIVideoFrameObserver* renderer)
{
	int ret = -ERROR_NULLPTR;
	if (MediaEngine != nullptr)
	{

		ret = MediaEngine->removeVideoFrameRenderer(renderer);
	}
	return ret;
}

void UIAgoraMediaEngine::Release()
{
	if (MediaEngine != nullptr)
	{
		MediaEngine->release();
		MediaEngine= nullptr;
	}
}
