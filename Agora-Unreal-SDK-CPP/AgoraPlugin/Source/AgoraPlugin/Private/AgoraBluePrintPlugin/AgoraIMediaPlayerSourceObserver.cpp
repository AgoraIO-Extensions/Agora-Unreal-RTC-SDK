//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraIMediaPlayerSourceObserver.h"

void UIMediaPlayerSourceObserver::onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_REASON ec)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerSourceStateChanged.Broadcast((EMEDIA_PLAYER_STATE)state, FENUMWRAP_MEDIA_PLAYER_REASON(ec));
		});
}
void UIMediaPlayerSourceObserver::onPositionChanged(int64_t position_ms, int64_t timestampMs)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPositionChanged.Broadcast(position_ms, timestampMs);
		});
}
void UIMediaPlayerSourceObserver::onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{
	FString UEMessage = UTF8_TO_TCHAR(message);

	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerEvent.Broadcast((EMEDIA_PLAYER_EVENT)eventCode, elapsedTime, UEMessage);
		});
}
void UIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{
	FString UEStr = UTF8_TO_TCHAR((char*)data);
	
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnMetaData.Broadcast(UEStr);
		});
}
void UIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayBufferUpdated.Broadcast(playCachedBuffer);
		});
}
void UIMediaPlayerSourceObserver::onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event)
{
	FString UEStr = UTF8_TO_TCHAR(src);
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPreloadEvent.Broadcast(UEStr, (EPLAYER_PRELOAD_EVENT)event);
		});
}
void UIMediaPlayerSourceObserver::onCompleted()
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnCompleted.Broadcast();
		});
}
void UIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnAgoraCDNTokenWillExpire.Broadcast();
		});
}
void UIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to)
{
	
	FSrcInfo UESrcInfoFrom = from;
	FSrcInfo UESrcInfoTo = to;

	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerSrcInfoChanged.Broadcast(UESrcInfoFrom, UESrcInfoTo);
		});
}
void UIMediaPlayerSourceObserver::onPlayerInfoUpdated(const agora::media::base::PlayerUpdatedInfo& info)
{
	FPlayerUpdatedInfo UEPlayerUpdatedInfo = info;

	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerInfoUpdated.Broadcast(UEPlayerUpdatedInfo);
		});
}
void UIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnAudioVolumeIndication.Broadcast(volume);
		});
}


int UIMediaPlayerCustomDataProvider::onReadData(unsigned char* buffer, int bufferSize)
{
	unsigned char* tempdata = new unsigned char[bufferSize];
	FMemory::Memcpy((void*)tempdata, buffer, bufferSize);
	TArray<int> callBackdata;
	for (int i = 0; i < bufferSize; i++)
	{
		callBackdata.Add(tempdata[i]);
	}
	delete[] tempdata;

	TWeakObjectPtr<UIMediaPlayerCustomDataProvider> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return bufferSize;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;



			OnReadData.Broadcast(callBackdata);
		});
	return bufferSize;
}

void UIMediaPlayerSourceObserver::onPlayerCacheStats(const agora::media::base::CacheStatistics& stats)
{
	FCacheStatistics UEStats = stats;
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerCacheStats.Broadcast(UEStats);
		});
}



void UIMediaPlayerSourceObserver::onPlayerPlaybackStats(const agora::media::base::PlayerPlaybackStats& stats)
{
	FPlayerPlaybackStats UEStats = stats;
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerPlaybackStats.Broadcast(UEStats);
		});
}

int64_t UIMediaPlayerCustomDataProvider::onSeek(int64_t offset, int whence)
{

	TWeakObjectPtr<UIMediaPlayerCustomDataProvider> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return offset;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnSeek.Broadcast(offset, whence);
		});
	return offset;
}
