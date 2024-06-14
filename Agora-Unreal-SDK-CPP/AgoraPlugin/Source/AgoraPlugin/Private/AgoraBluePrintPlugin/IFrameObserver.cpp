//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/IFrameObserver.h"

bool UIAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
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

			FAudioFrame frame;
			frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
			frame.samplesPerChannel = audioFrame.samplesPerChannel;
			frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
			frame.channels = audioFrame.channels;
			frame.samplesPerSec = audioFrame.samplesPerSec;

			int ByteSize = audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels;
			frame.buffer.AddZeroed(ByteSize);
			FMemory::Memcpy(frame.buffer.GetData(), audioFrame.buffer, ByteSize);

			frame.renderTimeMs = audioFrame.renderTimeMs;
			frame.avsync_type = audioFrame.avsync_type;
			OnPlaybackAudioFrameBeforeMixing.Broadcast(FString(channelId), uid, frame);
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

			FAudioSpectrumData audioSpectrumData;
			float* audioData = new float[data.dataLength];
			FMemory::Memcpy(audioData, data.audioSpectrumData, data.dataLength);
			for (int i = 0; i < data.dataLength; i++)
			{
				audioSpectrumData.audioSpectrumData.Add(audioData[i]);
			}
			delete[] audioData;
			audioSpectrumData.dataLength = data.dataLength;
			OnLocalAudioSpectrum.Broadcast(audioSpectrumData);
		});
	return true;
}
bool UIAudioSpectrumObserver::onRemoteAudioSpectrum(const agora::media::UserAudioSpectrumInfo* spectrums, unsigned int spectrumNumber)
{
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

			FUserAudioSpectrumInfo userAudioSpectrumInfo;
			userAudioSpectrumInfo.uid = spectrums->uid;
			agora::media::UserAudioSpectrumInfo* audioSpectrumInfo = new agora::media::UserAudioSpectrumInfo[spectrumNumber];
			FMemory::Memcpy(audioSpectrumInfo, spectrums, spectrumNumber);
			TArray<FUserAudioSpectrumInfo> userAudioInfos;
			for (unsigned int i = 0; i < spectrumNumber; i++)
			{
				FUserAudioSpectrumInfo userAudioInfo;
				userAudioInfo.uid = audioSpectrumInfo->uid;

				agora::media::AudioSpectrumData data = audioSpectrumInfo->spectrumData;
				FAudioSpectrumData audioSpectrumData;
				float* audioData = new float[data.dataLength];
				FMemory::Memcpy(audioData, data.audioSpectrumData, data.dataLength);
				for (int j = 0; j < data.dataLength; j++)
				{
					audioSpectrumData.audioSpectrumData.Add(audioData[j]);
				}
				delete[] audioData;
				audioSpectrumData.dataLength = data.dataLength;
				userAudioInfo.spectrumData = audioSpectrumData;
				userAudioInfos.Add(userAudioInfo);
			}
			delete[] audioSpectrumInfo;
			OnRemoteAudioSpectrum.Broadcast(userAudioInfos, spectrumNumber);
		});
	return true;
}


bool UIVideoFrameObserver::onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
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

			FVideoFrame frame;
			frame.type = (EVIDEO_PIXEL_FORMAT)videoFrame.type;
			frame.width = videoFrame.width;
			frame.height = videoFrame.height;
			frame.yStride = videoFrame.yStride;
			frame.uStride = videoFrame.uStride;
			frame.vStride = videoFrame.vStride;
			unsigned char* y = new unsigned char[videoFrame.yStride];
			FMemory::Memcpy(y, videoFrame.yBuffer, videoFrame.yStride);
			for (int i = 0; i < videoFrame.yStride; i++)
			{
				frame.yBuffer.Add(y[i]);
			}
			delete[] y;
			unsigned char* u = new unsigned char[videoFrame.uStride];
			FMemory::Memcpy(u, videoFrame.uBuffer, videoFrame.uStride);
			for (int i = 0; i < videoFrame.uStride; i++)
			{
				frame.uBuffer.Add(u[i]);
			}
			delete[] u;
			unsigned char* v = new unsigned char[videoFrame.vStride];
			FMemory::Memcpy(v, videoFrame.vBuffer, videoFrame.vStride);
			for (int i = 0; i < videoFrame.vStride; i++)
			{
				frame.vBuffer.Add(v[i]);
			}
			delete[] v;
			frame.rotation = videoFrame.rotation;
			frame.renderTimeMs = videoFrame.renderTimeMs;
			frame.avsync_type = videoFrame.avsync_type;
			unsigned char* metadatabuffer = new unsigned char[videoFrame.metadata_size];
			FMemory::Memcpy(metadatabuffer, videoFrame.metadata_buffer, videoFrame.metadata_size);
			for (int i = 0; i < videoFrame.metadata_size; i++)
			{
				frame.metadata_buffer.Add(metadatabuffer[i]);
			}
			delete[] metadatabuffer;
			frame.metadata_size = videoFrame.metadata_size;
			//frame.sharedContext = videoFrame.sharedContext;
			frame.textureId = videoFrame.textureId;
			for (int i = 0; i < 16; i++)
			{
				frame.matrix.Add(videoFrame.matrix[i]);
			}
			OnCaptureVideoFrame.Broadcast((EVIDEO_SOURCE_TYPE)sourceType, frame);
		});
	return true;
}
bool UIVideoFrameObserver::onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame)
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

			FVideoFrame frame;
			frame.type = (EVIDEO_PIXEL_FORMAT)videoFrame.type;
			frame.width = videoFrame.width;
			frame.height = videoFrame.height;
			frame.yStride = videoFrame.yStride;
			frame.uStride = videoFrame.uStride;
			frame.vStride = videoFrame.vStride;
			unsigned char* y = new unsigned char[videoFrame.yStride];
			FMemory::Memcpy(y, videoFrame.yBuffer, videoFrame.yStride);
			for (int i = 0; i < videoFrame.yStride; i++)
			{
				frame.yBuffer.Add(y[i]);
			}
			delete[] y;
			unsigned char* u = new unsigned char[videoFrame.uStride];
			FMemory::Memcpy(u, videoFrame.uBuffer, videoFrame.uStride);
			for (int i = 0; i < videoFrame.uStride; i++)
			{
				frame.uBuffer.Add(u[i]);
			}
			delete[] u;
			unsigned char* v = new unsigned char[videoFrame.vStride];
			FMemory::Memcpy(v, videoFrame.vBuffer, videoFrame.vStride);
			for (int i = 0; i < videoFrame.vStride; i++)
			{
				frame.vBuffer.Add(v[i]);
			}
			delete[] v;
			frame.rotation = videoFrame.rotation;
			frame.renderTimeMs = videoFrame.renderTimeMs;
			frame.avsync_type = videoFrame.avsync_type;
			unsigned char* metadatabuffer = new unsigned char[videoFrame.metadata_size];
			FMemory::Memcpy(metadatabuffer, videoFrame.metadata_buffer, videoFrame.metadata_size);
			for (int i = 0; i < videoFrame.metadata_size; i++)
			{
				frame.metadata_buffer.Add(metadatabuffer[i]);
			}
			delete[] metadatabuffer;
			frame.metadata_size = videoFrame.metadata_size;
			frame.textureId = videoFrame.textureId;
			for (int i = 0; i < 16; i++)
			{
				frame.matrix.Add(videoFrame.matrix[i]);
			}
			OnPreEncodeVideoFrame.Broadcast((EVIDEO_SOURCE_TYPE)sourceType, frame);
		});
	return true;
}


bool UIVideoFrameObserver::onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId)
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

			FVideoFrame frame;
			frame.type = (EVIDEO_PIXEL_FORMAT)videoFrame.type;
			frame.width = videoFrame.width;
			frame.height = videoFrame.height;
			frame.yStride = videoFrame.yStride;
			frame.uStride = videoFrame.uStride;
			frame.vStride = videoFrame.vStride;
			unsigned char* y = new unsigned char[videoFrame.yStride];
			FMemory::Memcpy(y, videoFrame.yBuffer, videoFrame.yStride);
			for (int i = 0; i < videoFrame.yStride; i++)
			{
				frame.yBuffer.Add(y[i]);
			}
			delete[] y;
			unsigned char* u = new unsigned char[videoFrame.uStride];
			FMemory::Memcpy(u, videoFrame.uBuffer, videoFrame.uStride);
			for (int i = 0; i < videoFrame.uStride; i++)
			{
				frame.uBuffer.Add(u[i]);
			}
			delete[] u;
			unsigned char* v = new unsigned char[videoFrame.vStride];
			FMemory::Memcpy(v, videoFrame.vBuffer, videoFrame.vStride);
			for (int i = 0; i < videoFrame.vStride; i++)
			{
				frame.vBuffer.Add(v[i]);
			}
			delete[] v;
			frame.rotation = videoFrame.rotation;
			frame.renderTimeMs = videoFrame.renderTimeMs;
			frame.avsync_type = videoFrame.avsync_type;
			unsigned char* metadatabuffer = new unsigned char[videoFrame.metadata_size];
			FMemory::Memcpy(metadatabuffer, videoFrame.metadata_buffer, videoFrame.metadata_size);
			for (int i = 0; i < videoFrame.metadata_size; i++)
			{
				frame.metadata_buffer.Add(metadatabuffer[i]);
			}
			delete[] metadatabuffer;
			frame.metadata_size = videoFrame.metadata_size;
			//frame.sharedContext = videoFrame.sharedContext;
			frame.textureId = videoFrame.textureId;
			for (int i = 0; i < 16; i++)
			{
				frame.matrix.Add(videoFrame.matrix[i]);
			}
			OnMediaPlayerVideoFrame.Broadcast(frame, mediaPlayerId);
		});
	return true;
}

bool UIVideoFrameObserver::onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame)
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

			FVideoFrame frame;
			frame.type = (EVIDEO_PIXEL_FORMAT)videoFrame.type;
			frame.width = videoFrame.width;
			frame.height = videoFrame.height;
			frame.yStride = videoFrame.yStride;
			frame.uStride = videoFrame.uStride;
			frame.vStride = videoFrame.vStride;
			unsigned char* y = new unsigned char[videoFrame.yStride];
			FMemory::Memcpy(y, videoFrame.yBuffer, videoFrame.yStride);
			for (int i = 0; i < videoFrame.yStride; i++)
			{
				frame.yBuffer.Add(y[i]);
			}
			delete[] y;
			unsigned char* u = new unsigned char[videoFrame.uStride];
			FMemory::Memcpy(u, videoFrame.uBuffer, videoFrame.uStride);
			for (int i = 0; i < videoFrame.uStride; i++)
			{
				frame.uBuffer.Add(u[i]);
			}
			delete[] u;
			unsigned char* v = new unsigned char[videoFrame.vStride];
			FMemory::Memcpy(v, videoFrame.vBuffer, videoFrame.vStride);
			for (int i = 0; i < videoFrame.vStride; i++)
			{
				frame.vBuffer.Add(v[i]);
			}
			delete[] v;
			frame.rotation = videoFrame.rotation;
			frame.renderTimeMs = videoFrame.renderTimeMs;
			frame.avsync_type = videoFrame.avsync_type;
			unsigned char* metadatabuffer = new unsigned char[videoFrame.metadata_size];
			FMemory::Memcpy(metadatabuffer, videoFrame.metadata_buffer, videoFrame.metadata_size);
			for (int i = 0; i < videoFrame.metadata_size; i++)
			{
				frame.metadata_buffer.Add(metadatabuffer[i]);
			}
			delete[] metadatabuffer;
			frame.metadata_size = videoFrame.metadata_size;
			//frame.sharedContext = videoFrame.sharedContext;
			frame.textureId = videoFrame.textureId;
			for (int i = 0; i < 16; i++)
			{
				frame.matrix.Add(videoFrame.matrix[i]);
			}
			OnRenderVideoFrame.Broadcast(FString(channelId), remoteUid, frame);
		});
	return true;
}
bool UIVideoFrameObserver::onTranscodedVideoFrame(agora::media::base::VideoFrame& videoFrame)
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

			FVideoFrame frame;
			frame.type = (EVIDEO_PIXEL_FORMAT)videoFrame.type;
			frame.width = videoFrame.width;
			frame.height = videoFrame.height;
			frame.yStride = videoFrame.yStride;
			frame.uStride = videoFrame.uStride;
			frame.vStride = videoFrame.vStride;
			unsigned char* y = new unsigned char[videoFrame.yStride];
			FMemory::Memcpy(y, videoFrame.yBuffer, videoFrame.yStride);
			for (int i = 0; i < videoFrame.yStride; i++)
			{
				frame.yBuffer.Add(y[i]);
			}
			delete[] y;
			unsigned char* u = new unsigned char[videoFrame.uStride];
			FMemory::Memcpy(u, videoFrame.uBuffer, videoFrame.uStride);
			for (int i = 0; i < videoFrame.uStride; i++)
			{
				frame.uBuffer.Add(u[i]);
			}
			delete[] u;
			unsigned char* v = new unsigned char[videoFrame.vStride];
			FMemory::Memcpy(v, videoFrame.vBuffer, videoFrame.vStride);
			for (int i = 0; i < videoFrame.vStride; i++)
			{
				frame.vBuffer.Add(v[i]);
			}
			delete[] v;
			frame.rotation = videoFrame.rotation;
			frame.renderTimeMs = videoFrame.renderTimeMs;
			frame.avsync_type = videoFrame.avsync_type;
			unsigned char* metadatabuffer = new unsigned char[videoFrame.metadata_size];
			FMemory::Memcpy(metadatabuffer, videoFrame.metadata_buffer, videoFrame.metadata_size);
			for (int i = 0; i < videoFrame.metadata_size; i++)
			{
				frame.metadata_buffer.Add(metadatabuffer[i]);
			}
			delete[] metadatabuffer;
			frame.metadata_size = videoFrame.metadata_size;
			//frame.sharedContext = videoFrame.sharedContext;
			frame.textureId = videoFrame.textureId;
			for (int i = 0; i < 16; i++)
			{
				frame.matrix.Add(videoFrame.matrix[i]);
			}
			OnTranscodedVideoFrame.Broadcast(frame);
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

			FAudioFrame frame;
			frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
			frame.samplesPerChannel = audioFrame.samplesPerChannel;
			frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
			frame.channels = audioFrame.channels;
			frame.samplesPerSec = audioFrame.samplesPerSec;

			int ByteSize = audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels;
			frame.buffer.AddZeroed(ByteSize);
			FMemory::Memcpy(frame.buffer.GetData(), audioFrame.buffer, ByteSize);

			frame.renderTimeMs = audioFrame.renderTimeMs;
			frame.avsync_type = audioFrame.avsync_type;
			OnRecordAudioFrame.Broadcast(FString(channelId), frame);
		});
	return true;
}
bool UIAudioFrameObserver::onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
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

			FAudioFrame frame;
			frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
			frame.samplesPerChannel = audioFrame.samplesPerChannel;
			frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
			frame.channels = audioFrame.channels;
			frame.samplesPerSec = audioFrame.samplesPerSec;

			int ByteSize = audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels;
			frame.buffer.AddZeroed(ByteSize);
			FMemory::Memcpy(frame.buffer.GetData(), audioFrame.buffer, ByteSize);

			frame.renderTimeMs = audioFrame.renderTimeMs;
			frame.avsync_type = audioFrame.avsync_type;
			OnPlaybackAudioFrame.Broadcast(FString(channelId), frame);
		});
	return true;
}
bool UIAudioFrameObserver::onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
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

			FAudioFrame frame;
			frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
			frame.samplesPerChannel = audioFrame.samplesPerChannel;
			frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
			frame.channels = audioFrame.channels;
			frame.samplesPerSec = audioFrame.samplesPerSec;

			int ByteSize = audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels;
			frame.buffer.AddZeroed(ByteSize);
			FMemory::Memcpy(frame.buffer.GetData(), audioFrame.buffer, ByteSize);

			frame.renderTimeMs = audioFrame.renderTimeMs;
			frame.avsync_type = audioFrame.avsync_type;
			OnMixedAudioFrame.Broadcast(FString(channelId), frame);
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

			FAudioPcmFrame pcmFrame;
			pcmFrame.capture_timestamp = frame->capture_timestamp;
			pcmFrame.samples_per_channel_ = frame->samples_per_channel_;
			pcmFrame.sample_rate_hz_ = frame->sample_rate_hz_;
			pcmFrame.bytes_per_sample = (EBYTES_PER_SAMPLE)((int)frame->bytes_per_sample);
			pcmFrame.num_channels_ = frame->num_channels_;
			int64 length = frame->samples_per_channel_ * frame->num_channels_;

			// kMaxDataSizeSamples
			if (length > 3840)
			{
				length = 3840;
			}
			FMemory::Memcpy(pcmFrame.data_.GetData(), frame->data_, length * (sizeof(int16_t)));
			OnFrame.Broadcast(pcmFrame);
		});
}
