// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/IAudioEncodedFrameObserver.h"


bool UIPacketObserver::onSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	FPacket pack;
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			OnSendAudioPacket.Broadcast(pack);
		});
	unsigned char* tempdata = new unsigned char[pack.size];
	for (int i = 0; i < pack.size; i++)
	{
		tempdata[i] = pack.buffer[i];
	}
	FMemory::Memcpy((void*)packet.buffer, tempdata, pack.size);
	delete[] tempdata;
	packet.size = pack.size;

	return true;
}
bool UIPacketObserver::onSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	FPacket pack;
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			OnSendVideoPacket.Broadcast(pack);
		});
	unsigned char* tempdata = new unsigned char[pack.size];
	for (int i = 0; i < pack.size; i++)
	{
		tempdata[i] = pack.buffer[i];
	}
	FMemory::Memcpy((void*)packet.buffer, tempdata, pack.size);
	delete[] tempdata;
	packet.size = pack.size;
	return true;
}
bool UIPacketObserver::onReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FPacket pack;
			unsigned char* tempdata = new unsigned char[packet.size];
			FMemory::Memcpy((void*)tempdata, packet.buffer, packet.size);
			TArray<int64> callBackdata;
			for (unsigned int i = 0; i < packet.size; i++)
			{
				callBackdata.Add(tempdata[i]);
			}
			delete[] tempdata;
			pack.buffer = callBackdata;
			pack.size = packet.size;
			OnReceiveAudioPacket.Broadcast(pack);
		});
	return true;
}
bool UIPacketObserver::onReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FPacket pack;
			unsigned char* tempdata = new unsigned char[packet.size];
			FMemory::Memcpy((void*)tempdata, packet.buffer, packet.size);
			TArray<int64> callBackdata;
			for (unsigned int i = 0; i < packet.size; i++)
			{
				callBackdata.Add(tempdata[i]);
			}
			delete[] tempdata;
			pack.buffer = callBackdata;
			pack.size = packet.size;
			OnReceiveVideoPacket.Broadcast(pack);
		});
	return true;
}

void UIAudioEncodedFrameObserver::onRecordAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FEncodedAudioFrameInfo encodedAudioFrameInfo;
			encodedAudioFrameInfo.codec = (EAUDIO_CODEC_TYPE)audioEncodedFrameInfo.codec;
			encodedAudioFrameInfo.sampleRateHz = audioEncodedFrameInfo.sampleRateHz;
			encodedAudioFrameInfo.samplesPerChannel = audioEncodedFrameInfo.samplesPerChannel;
			encodedAudioFrameInfo.numberOfChannels = audioEncodedFrameInfo.numberOfChannels;
			FEncodedAudioFrameAdvancedSettings advancedSettings;
			advancedSettings.sendEvenIfEmpty = audioEncodedFrameInfo.advancedSettings.sendEvenIfEmpty;
			advancedSettings.speech = audioEncodedFrameInfo.advancedSettings.speech;
			encodedAudioFrameInfo.advancedSettings = advancedSettings;
			encodedAudioFrameInfo.captureTimeMs = audioEncodedFrameInfo.captureTimeMs;
			unsigned char* tempdata = new unsigned char[length];
			FMemory::Memcpy(tempdata, frameBuffer, length);
			TArray<int64> buffer;
			for (int i = 0; i < length; i++)
			{
				buffer.Add(tempdata[i]);
			}
			delete[] tempdata;
			OnRecordAudioEncoded.Broadcast(buffer, length, encodedAudioFrameInfo);
		});
}

void UIAudioEncodedFrameObserver::onPlaybackAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FEncodedAudioFrameInfo encodedAudioFrameInfo;
			encodedAudioFrameInfo.codec = (EAUDIO_CODEC_TYPE)audioEncodedFrameInfo.codec;
			encodedAudioFrameInfo.sampleRateHz = audioEncodedFrameInfo.sampleRateHz;
			encodedAudioFrameInfo.samplesPerChannel = audioEncodedFrameInfo.samplesPerChannel;
			encodedAudioFrameInfo.numberOfChannels = audioEncodedFrameInfo.numberOfChannels;
			FEncodedAudioFrameAdvancedSettings advancedSettings;
			advancedSettings.sendEvenIfEmpty = audioEncodedFrameInfo.advancedSettings.sendEvenIfEmpty;
			advancedSettings.speech = audioEncodedFrameInfo.advancedSettings.speech;
			encodedAudioFrameInfo.advancedSettings = advancedSettings;
			encodedAudioFrameInfo.captureTimeMs = audioEncodedFrameInfo.captureTimeMs;
			unsigned char* tempdata = new unsigned char[length];
			FMemory::Memcpy(tempdata, frameBuffer, length);
			TArray<int64> buffer;
			for (int i = 0; i < length; i++)
			{
				buffer.Add(tempdata[i]);
			}
			delete[] tempdata;
			OnPlaybackAudioEncoded.Broadcast(buffer, length, encodedAudioFrameInfo);
		});
}


void UIAudioEncodedFrameObserver::onMixedAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FEncodedAudioFrameInfo encodedAudioFrameInfo;
			encodedAudioFrameInfo.codec = (EAUDIO_CODEC_TYPE)audioEncodedFrameInfo.codec;
			encodedAudioFrameInfo.sampleRateHz = audioEncodedFrameInfo.sampleRateHz;
			encodedAudioFrameInfo.samplesPerChannel = audioEncodedFrameInfo.samplesPerChannel;
			encodedAudioFrameInfo.numberOfChannels = audioEncodedFrameInfo.numberOfChannels;
			FEncodedAudioFrameAdvancedSettings advancedSettings;
			advancedSettings.sendEvenIfEmpty = audioEncodedFrameInfo.advancedSettings.sendEvenIfEmpty;
			advancedSettings.speech = audioEncodedFrameInfo.advancedSettings.speech;
			encodedAudioFrameInfo.advancedSettings = advancedSettings;
			encodedAudioFrameInfo.captureTimeMs = audioEncodedFrameInfo.captureTimeMs;
			unsigned char* tempdata = new unsigned char[length];
			FMemory::Memcpy(tempdata, frameBuffer, length);
			TArray<int64> buffer;
			for (int i = 0; i < length; i++)
			{
				buffer.Add(tempdata[i]);
			}
			delete[] tempdata;
			OnMixedAudioEncoded.Broadcast(buffer, length, encodedAudioFrameInfo);
		});
}
