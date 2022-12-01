// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraIMediaPlayerSourceObserver.h"

void UIMediaPlayerSourceObserver::onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_ERROR ec)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnPlayerSourceStateChanged.Broadcast((EMEDIA_PLAYER_STATE)state, (EMEDIA_PLAYER_ERROR)ec);
	});
}
void UIMediaPlayerSourceObserver::onPositionChanged(int64_t position_ms)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnPositionChanged.Broadcast(position_ms);
	});
}
void UIMediaPlayerSourceObserver::onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnPlayerEvent.Broadcast((EMEDIA_PLAYER_EVENT)eventCode, elapsedTime, FString(message));
	});
}
void UIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnMetaData.Broadcast((int64)data, length);
	});
}
void UIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnPlayBufferUpdated.Broadcast(playCachedBuffer);
	});
}
void UIMediaPlayerSourceObserver::onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnPreloadEvent.Broadcast(FString(src), (EPLAYER_PRELOAD_EVENT)event);
	});
}
void UIMediaPlayerSourceObserver::onCompleted()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnCompleted.Broadcast();
	});
}
void UIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnAgoraCDNTokenWillExpire.Broadcast();
	});
}
void UIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FPlayerUpdatedInfo playerUpdatedInfo;
		if (playerUpdatedInfo.playerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
		{
			playerUpdatedInfo.playerId = FString(*info.playerId);
		}
		if (playerUpdatedInfo.deviceIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
		{
			playerUpdatedInfo.deviceId = FString(*info.deviceId);
		}
		if (playerUpdatedInfo.cacheStatisticsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnAudioVolumeIndication.Broadcast(volume);
	});
}


int UIMediaPlayerCustomDataProvider::onReadData(unsigned char* buffer, int bufferSize)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
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
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnSeek.Broadcast(offset,whence);
	});
	return offset;
}
