// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrint/AgoraIMediaPlayerSourceObserver.h"

void AIMediaPlayerSourceObserver::onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_ERROR ec)
{
	OnPlayerSourceStateChanged.Broadcast((EMEDIA_PLAYER_STATE)state, (EMEDIA_PLAYER_ERROR)ec);
}
void AIMediaPlayerSourceObserver::onPositionChanged(int64_t position_ms)
{
	OnPositionChanged.Broadcast(position_ms);
}
void AIMediaPlayerSourceObserver::onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{
	OnPlayerEvent.Broadcast((EMEDIA_PLAYER_EVENT)eventCode, elapsedTime, FString(message));
}
void AIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{
	OnMetaData.Broadcast((int64)data, length);
}
void AIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{
	OnPlayBufferUpdated.Broadcast(playCachedBuffer);
}
void AIMediaPlayerSourceObserver::onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event)
{
	OnPreloadEvent.Broadcast(FString(src), (EPLAYER_PRELOAD_EVENT)event);
}
void AIMediaPlayerSourceObserver::onCompleted()
{
	OnCompleted.Broadcast();
}
void AIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{
	OnAgoraCDNTokenWillExpire.Broadcast();
}
void AIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to)
{
	FSrcInfo fromInfo;
	fromInfo.bitrateInKbps = from.bitrateInKbps;
	fromInfo.name = FString(from.name);
	FSrcInfo toInfo;
	toInfo.bitrateInKbps = to.bitrateInKbps;
	toInfo.name = FString(to.name);
	OnPlayerSrcInfoChanged.Broadcast(fromInfo, toInfo);
}
void AIMediaPlayerSourceObserver::onPlayerInfoUpdated(const agora::media::base::PlayerUpdatedInfo& info)
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
}
void AIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{
	OnAudioVolumeIndication.Broadcast(volume);
}

void AIMediaPlayerSourceObserver::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = false;
}

int AIMediaPlayerCustomDataProvider::onReadData(unsigned char* buffer, int bufferSize)
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

	return bufferSize;
}

int64_t AIMediaPlayerCustomDataProvider::onSeek(int64_t offset, int whence)
{
	OnSeek.Broadcast(offset,whence);

	return offset;
}
