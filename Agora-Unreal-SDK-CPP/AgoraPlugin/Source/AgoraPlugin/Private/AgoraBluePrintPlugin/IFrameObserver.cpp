//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/IFrameObserver.h"

bool UIAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	FString UEChannelId = UTF8_TO_TCHAR(channelId);
	FAudioFrame frame = audioFrame;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnPlaybackAudioFrameBeforeMixing.Broadcast(UEChannelId, uid, frame);
		});
	return true;
}


bool UIAudioFrameObserver::onEarMonitoringAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getEarMonitoringAudioParams()
{
	AudioParams params;

	return params;
}

bool UIAudioSpectrumObserver::onLocalAudioSpectrum(const agora::media::AudioSpectrumData& data)
{
	FAudioSpectrumData UEAudioSpectrumData = data;
	TWeakObjectPtr<UIAudioSpectrumObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnLocalAudioSpectrum.Broadcast(UEAudioSpectrumData);
		});
	return true;
}
bool UIAudioSpectrumObserver::onRemoteAudioSpectrum(const agora::media::UserAudioSpectrumInfo* spectrums, unsigned int spectrumNumber)
{
	TArray<FUserAudioSpectrumInfo> userAudioInfos;
	for (unsigned int i = 0; i < spectrumNumber; i++)
	{
		userAudioInfos.Add(spectrums[i]);
	}

	TWeakObjectPtr<UIAudioSpectrumObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteAudioSpectrum.Broadcast(userAudioInfos);
		});
	return true;
}


bool UIVideoFrameObserver::onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
{
	FVideoFrame UEVideoFrame = videoFrame;

	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;
				
			OnCaptureVideoFrame.Broadcast((EVIDEO_SOURCE_TYPE)sourceType, UEVideoFrame);
		});
	return true;
}
bool UIVideoFrameObserver::onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
{
	FVideoFrame UEVideoFrame = videoFrame;

	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

		
			OnPreEncodeVideoFrame.Broadcast((EVIDEO_SOURCE_TYPE)sourceType, UEVideoFrame);
		});
	return true;
}


bool UIVideoFrameObserver::onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId)
{
	FVideoFrame UEVideoFrame = videoFrame;

	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnMediaPlayerVideoFrame.Broadcast(UEVideoFrame, mediaPlayerId);
		});
	return true;
}

bool UIVideoFrameObserver::onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame)
{
	FVideoFrame UEVideoFrame = videoFrame;
	FString UEChannelId = UTF8_TO_TCHAR(channelId);
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRenderVideoFrame.Broadcast(UEChannelId, remoteUid, UEVideoFrame);
		});
	return true;
}
bool UIVideoFrameObserver::onTranscodedVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	FVideoFrame UEVideoFrame = videoFrame;

	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnTranscodedVideoFrame.Broadcast(UEVideoFrame);
		});
	return true;
}
agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE UIVideoFrameObserver::getVideoFrameProcessMode()
{
	
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return PROCESS_MODE_READ_ONLY;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetVideoFrameProcessMode.Broadcast();
		});
	return PROCESS_MODE_READ_ONLY;
}
agora::media::base::VIDEO_PIXEL_FORMAT UIVideoFrameObserver::getVideoFormatPreference()
{
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return agora::media::base::VIDEO_PIXEL_RGBA;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetVideoFormatPreference.Broadcast();
		});
	return agora::media::base::VIDEO_PIXEL_RGBA;
}


bool UIAudioFrameObserver::onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	FString UEChannelId = UTF8_TO_TCHAR(channelId);
	FAudioFrame UEAudioFrame = audioFrame;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRecordAudioFrame.Broadcast(UEChannelId, UEAudioFrame);
		});
	return true;
}
bool UIAudioFrameObserver::onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	FString UEChannelId = UTF8_TO_TCHAR(channelId);
	FAudioFrame UEAudioFrame = audioFrame;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnPlaybackAudioFrame.Broadcast(UEChannelId, UEAudioFrame);
		});
	return true;
}
bool UIAudioFrameObserver::onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	FString UEChannelId = UTF8_TO_TCHAR(channelId);
	FAudioFrame UEAudioFrame = audioFrame;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;


			OnMixedAudioFrame.Broadcast(UEChannelId, UEAudioFrame);
		});
	return true;
}

int UIAudioFrameObserver::getObservedAudioFramePosition()
{
	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return 0;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetObservedAudioFramePosition.Broadcast();
		});
	return 0;
}
agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getPlaybackAudioParams()
{
	agora::media::IAudioFrameObserverBase::AudioParams params;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return params;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetPlaybackAudioParams.Broadcast();
		});

	return params;
}
agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getRecordAudioParams()
{
	agora::media::IAudioFrameObserverBase::AudioParams params;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return params;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetRecordAudioParams.Broadcast();
		});

	return params;
}
agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getMixedAudioParams()
{
	agora::media::IAudioFrameObserverBase::AudioParams params;

	TWeakObjectPtr<UIAudioFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return params;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetMixedAudioParams.Broadcast();
		});

	return params;
}

bool UIVideoFrameObserver::getRotationApplied()
{
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetRotationApplied.Broadcast();
		});
	return true;
}
bool UIVideoFrameObserver::getMirrorApplied()
{
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetMirrorApplied.Broadcast();
		});
	return false;
}
uint32_t UIVideoFrameObserver::getObservedFramePosition()
{
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetObservedFramePosition.Broadcast();
		});
	return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;
}
bool UIVideoFrameObserver::isExternal()
{
	TWeakObjectPtr<UIVideoFrameObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			IsExternal.Broadcast();
		});
	return true;
}

void UIAudioPcmFrameSink::onFrame(agora::media::base::AudioPcmFrame* frame)
{
	FAudioPcmFrame UEPcmFrame = *frame;

	TWeakObjectPtr<UIAudioPcmFrameSink> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFrame.Broadcast(UEPcmFrame);
		});
}

bool UIFaceInfoObserver::onFaceInfo(const char* outFaceInfo)
{
	FString UEOutFaceInfo = UTF8_TO_TCHAR(outFaceInfo);

	TWeakObjectPtr<UIFaceInfoObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFaceInfo.Broadcast(UEOutFaceInfo);
		});

	return false;
}
