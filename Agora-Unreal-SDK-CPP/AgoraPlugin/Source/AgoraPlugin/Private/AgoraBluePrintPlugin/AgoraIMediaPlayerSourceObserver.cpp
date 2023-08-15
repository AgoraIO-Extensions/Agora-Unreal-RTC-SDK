// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraIMediaPlayerSourceObserver.h"

void UIMediaPlayerSourceObserver::onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_ERROR ec)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnPlayerSourceStateChanged.Broadcast((EMEDIA_PLAYER_STATE)state, FENUMWRAP_MEDIA_PLAYER_ERROR(ec));
	});
}
void UIMediaPlayerSourceObserver::onPositionChanged(int64_t position_ms)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnPositionChanged.Broadcast(position_ms);
	});
}
void UIMediaPlayerSourceObserver::onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnPlayerEvent.Broadcast((EMEDIA_PLAYER_EVENT)eventCode, elapsedTime, FString(message));
	});
}
void UIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnMetaData.Broadcast((int64)data, length);
	});
}
void UIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnPlayBufferUpdated.Broadcast(playCachedBuffer);
	});
}
void UIMediaPlayerSourceObserver::onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnPreloadEvent.Broadcast(FString(src), (EPLAYER_PRELOAD_EVENT)event);
	});
}
void UIMediaPlayerSourceObserver::onCompleted()
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAgoraCDNTokenWillExpire.Broadcast();
	});
}
void UIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FSrcInfo fromInfo;
		fromInfo.bitrateInKbps = from.bitrateInKbps;
		fromInfo.name = FString(from.name);
		FSrcInfo toInfo;
		toInfo.bitrateInKbps = to.bitrateInKbps;
		toInfo.name = FString(to.name);
		OnPlayerSrcInfoChanged.Broadcast(fromInfo, toInfo);
	});
}
void UIMediaPlayerSourceObserver::onPlayerInfoUpdated(const agora::media::base::PlayerUpdatedInfo& info)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FPlayerUpdatedInfo playerUpdatedInfo;
		playerUpdatedInfo.playerId_SetValue = info.playerId.has_value();
		playerUpdatedInfo.deviceId_SetValue = info.deviceId.has_value();
		playerUpdatedInfo.cacheStatistics_SetValue = info.cacheStatistics.has_value();
		if(info.playerId.has_value()){
			playerUpdatedInfo.playerId = FString(*info.playerId);
		}
		if (info.deviceId.has_value()) {
			playerUpdatedInfo.deviceId = FString(*info.deviceId);
		}
		if (info.deviceId.has_value())
		{
			FCacheStatistics Statistics;
			Statistics.cacheSize = info.cacheStatistics->cacheSize;
			Statistics.downloadSize = info.cacheStatistics->downloadSize;
			Statistics.fileSize = info.cacheStatistics->fileSize;
			playerUpdatedInfo.cacheStatistics = Statistics;
		}
		OnPlayerInfoUpdated.Broadcast(playerUpdatedInfo);
	});
}
void UIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{
	TWeakObjectPtr<UIMediaPlayerSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioVolumeIndication.Broadcast(volume);
	});
}


int UIMediaPlayerCustomDataProvider::onReadData(unsigned char* buffer, int bufferSize)
{
	TWeakObjectPtr<UIMediaPlayerCustomDataProvider> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return bufferSize;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		unsigned char* tempdata = new unsigned char[bufferSize];
		FMemory::Memcpy((void*)tempdata, buffer, bufferSize);
		TArray<int64> callBackdata;
		for (int i = 0; i < bufferSize; i++)
		{
			callBackdata.Add(tempdata[i]);
		}
		delete[] tempdata;

		OnReadData.Broadcast(callBackdata, bufferSize);
	});
	return bufferSize;
}

int64_t UIMediaPlayerCustomDataProvider::onSeek(int64_t offset, int whence)
{
	TWeakObjectPtr<UIMediaPlayerCustomDataProvider> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return offset;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnSeek.Broadcast(offset,whence);
	});
	return offset;
}
