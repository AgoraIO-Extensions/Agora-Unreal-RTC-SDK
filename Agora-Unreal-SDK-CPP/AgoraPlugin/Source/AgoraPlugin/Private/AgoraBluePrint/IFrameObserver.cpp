// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrint/IFrameObserver.h"

bool AIAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
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
	return true;
}
bool AIAudioSpectrumObserver::onLocalAudioSpectrum(const agora::media::AudioSpectrumData& data)
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
	return true;
}
bool AIAudioSpectrumObserver::onRemoteAudioSpectrum(const agora::media::UserAudioSpectrumInfo* spectrums, unsigned int spectrumNumber)
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
	return true;
}
bool AIVideoFrameObserver::onCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onPreEncodeVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onSecondaryCameraCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onSecondaryPreEncodeCameraVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onScreenCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onPreEncodeScreenVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId)
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
	return true;
}
bool AIVideoFrameObserver::onSecondaryScreenCaptureVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onSecondaryPreEncodeScreenVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
bool AIVideoFrameObserver::onTranscodedVideoFrame(agora::media::base::VideoFrame& videoFrame)
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
	return true;
}
agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE AIVideoFrameObserver::getVideoFrameProcessMode()
{
	GetVideoFrameProcessMode.Broadcast();

	return PROCESS_MODE_READ_ONLY;
}
agora::media::base::VIDEO_PIXEL_FORMAT AIVideoFrameObserver::getVideoFormatPreference()
{
	GetVideoFormatPreference.Broadcast();

	return agora::media::base::VIDEO_PIXEL_RGBA;
}

bool AIAudioFrameObserver::onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
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

	return true;
}
bool AIAudioFrameObserver::onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
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

	return true;
}
bool AIAudioFrameObserver::onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
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

	return true;
}
bool AIAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(const char* channelId,agora::media::base::user_id_t userId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	return true;
}
int AIAudioFrameObserver::getObservedAudioFramePosition()
{
	GetObservedAudioFramePosition.Broadcast();

	return 0;
}
agora::media::IAudioFrameObserverBase::AudioParams AIAudioFrameObserver::getPlaybackAudioParams()
{
	GetPlaybackAudioParams.Broadcast();

	agora::media::IAudioFrameObserverBase::AudioParams params;

	return params;
}
agora::media::IAudioFrameObserverBase::AudioParams AIAudioFrameObserver::getRecordAudioParams()
{
	GetRecordAudioParams.Broadcast();

	agora::media::IAudioFrameObserverBase::AudioParams params;

	return params;
}
agora::media::IAudioFrameObserverBase::AudioParams AIAudioFrameObserver::getMixedAudioParams()
{
	GetMixedAudioParams.Broadcast();

	agora::media::IAudioFrameObserverBase::AudioParams params;

	return params;
}

bool AIVideoFrameObserver::getRotationApplied()
{
	GetRotationApplied.Broadcast();

	return true;
}
bool AIVideoFrameObserver::getMirrorApplied()
{
	GetMirrorApplied.Broadcast();

	return false;
}
uint32_t AIVideoFrameObserver::getObservedFramePosition()
{
	GetObservedFramePosition.Broadcast();

	return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;
}
bool AIVideoFrameObserver::isExternal()
{
	IsExternal.Broadcast();

	return true;
}
