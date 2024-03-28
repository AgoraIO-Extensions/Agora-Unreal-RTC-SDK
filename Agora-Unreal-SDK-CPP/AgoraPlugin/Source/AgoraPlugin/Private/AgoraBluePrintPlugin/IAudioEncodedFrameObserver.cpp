//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/IAudioEncodedFrameObserver.h"


bool UIPacketObserver::onSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	FPacket pack;
#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnSendAudioPacket.Broadcast(pack);
		});

	packet = pack.CreateAgoraData();

	return true;
}
bool UIPacketObserver::onSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	FPacket pack;
#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnSendVideoPacket.Broadcast(pack);
		});

	packet = pack.CreateAgoraData();
	return true;
}
bool UIPacketObserver::onReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	FPacket UEPack = packet;
#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnReceiveAudioPacket.Broadcast(UEPack);
		});
	return true;
}
bool UIPacketObserver::onReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet)
{
	FPacket UEPack = packet;
#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnReceiveVideoPacket.Broadcast(UEPack);
		});
	return true;
}

void UIAudioEncodedFrameObserver::onRecordAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo)
{
	FEncodedAudioFrameInfo encodedAudioFrameInfo = audioEncodedFrameInfo;
	unsigned char* tempdata = new unsigned char[length];
	FMemory::Memcpy(tempdata, frameBuffer, length);
	TArray<int> buffer;
	for (int i = 0; i < length; i++)
	{
		buffer.Add(tempdata[i]);
	}
	delete[] tempdata;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnRecordAudioEncoded.Broadcast(buffer, length, encodedAudioFrameInfo);
		});
}

void UIAudioEncodedFrameObserver::onPlaybackAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo)
{
	FEncodedAudioFrameInfo encodedAudioFrameInfo = audioEncodedFrameInfo;
	unsigned char* tempdata = new unsigned char[length];
	FMemory::Memcpy(tempdata, frameBuffer, length);
	TArray<int> buffer;
	for (int i = 0; i < length; i++)
	{
		buffer.Add(tempdata[i]);
	}
	delete[] tempdata;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnPlaybackAudioEncoded.Broadcast(buffer, length, encodedAudioFrameInfo);
		});
}


void UIAudioEncodedFrameObserver::onMixedAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo)
{

	FEncodedAudioFrameInfo encodedAudioFrameInfo = audioEncodedFrameInfo;
	unsigned char* tempdata = new unsigned char[length];
	FMemory::Memcpy(tempdata, frameBuffer, length);
	TArray<int> buffer;
	for (int i = 0; i < length; i++)
	{
		buffer.Add(tempdata[i]);
	}
	delete[] tempdata;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			OnMixedAudioEncoded.Broadcast(buffer, length, encodedAudioFrameInfo);
		});
}
