// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/IFrameObserver.h"

bool UIAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FAudioFrame frame;
		frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
		frame.samplesPerChannel = audioFrame.samplesPerChannel;
		frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
		frame.channels = audioFrame.channels;
		frame.samplesPerSec = audioFrame.samplesPerSec;
		frame.buffer = (int64)audioFrame.buffer;
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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


bool UIVideoFrameObserver::onCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnCaptureVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onPreEncodeVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnPreEncodeVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onSecondaryCameraCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnSecondaryCameraCaptureVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onSecondaryPreEncodeCameraVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnSecondaryPreEncodeCameraVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onScreenCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnScreenCaptureVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onPreEncodeScreenVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnPreEncodeScreenVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
bool UIVideoFrameObserver::onSecondaryScreenCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnSecondaryScreenCaptureVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onSecondaryPreEncodeScreenVideoFrame(agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
		OnSecondaryPreEncodeScreenVideoFrame.Broadcast(frame);
	});
	return true;
}
bool UIVideoFrameObserver::onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetVideoFrameProcessMode.Broadcast();
	});
	return PROCESS_MODE_READ_ONLY;
}
agora::media::base::VIDEO_PIXEL_FORMAT UIVideoFrameObserver::getVideoFormatPreference()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetVideoFormatPreference.Broadcast();
	});
	return agora::media::base::VIDEO_PIXEL_RGBA;
}


bool UIAudioFrameObserver::onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FAudioFrame frame;
		frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
		frame.samplesPerChannel = audioFrame.samplesPerChannel;
		frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
		frame.channels = audioFrame.channels;
		frame.samplesPerSec = audioFrame.samplesPerSec;
		frame.buffer = (int64)audioFrame.buffer;
		frame.renderTimeMs = audioFrame.renderTimeMs;
		frame.avsync_type = audioFrame.avsync_type;
		OnRecordAudioFrame.Broadcast(FString(channelId), frame);
	});
	return true;
}
bool UIAudioFrameObserver::onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FAudioFrame frame;
		frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
		frame.samplesPerChannel = audioFrame.samplesPerChannel;
		frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
		frame.channels = audioFrame.channels;
		frame.samplesPerSec = audioFrame.samplesPerSec;
		frame.buffer = (int64)audioFrame.buffer;
		frame.renderTimeMs = audioFrame.renderTimeMs;
		frame.avsync_type = audioFrame.avsync_type;
		OnPlaybackAudioFrame.Broadcast(FString(channelId), frame);
	});
	return true;
}
bool UIAudioFrameObserver::onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FAudioFrame frame;
		frame.type = (EAUDIO_FRAME_TYPE)audioFrame.type;
		frame.samplesPerChannel = audioFrame.samplesPerChannel;
		frame.bytesPerSample = (EBYTES_PER_SAMPLE)audioFrame.bytesPerSample;
		frame.channels = audioFrame.channels;
		frame.samplesPerSec = audioFrame.samplesPerSec;
		frame.buffer = (int64)audioFrame.buffer;
		frame.renderTimeMs = audioFrame.renderTimeMs;
		frame.avsync_type = audioFrame.avsync_type;
		OnMixedAudioFrame.Broadcast(FString(channelId), frame);
	});
	return true;
}

int UIAudioFrameObserver::getObservedAudioFramePosition()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetObservedAudioFramePosition.Broadcast();
	});
	return 0;
}
agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getPlaybackAudioParams()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetPlaybackAudioParams.Broadcast();
	}); 

	agora::media::IAudioFrameObserverBase::AudioParams params;

	return params;
}
agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getRecordAudioParams()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetRecordAudioParams.Broadcast();
	});

	agora::media::IAudioFrameObserverBase::AudioParams params;

	return params;
}
agora::media::IAudioFrameObserverBase::AudioParams UIAudioFrameObserver::getMixedAudioParams()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetMixedAudioParams.Broadcast();
	});

	agora::media::IAudioFrameObserverBase::AudioParams params;

	return params;
}

bool UIVideoFrameObserver::getRotationApplied()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetRotationApplied.Broadcast();
	});
	return true;
}
bool UIVideoFrameObserver::getMirrorApplied()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetMirrorApplied.Broadcast();
	});
	return false;
}
uint32_t UIVideoFrameObserver::getObservedFramePosition()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GetObservedFramePosition.Broadcast();
	});
	return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;
}
bool UIVideoFrameObserver::isExternal()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		IsExternal.Broadcast();
	});
	return true;
}
