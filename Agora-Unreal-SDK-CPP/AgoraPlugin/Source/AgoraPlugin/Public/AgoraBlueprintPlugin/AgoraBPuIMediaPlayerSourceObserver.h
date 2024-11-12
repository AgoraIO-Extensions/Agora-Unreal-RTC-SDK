//  Copyright (c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "AgoraBPuDataTypes.h"
#include "AgoraBPuIMediaPlayerSourceObserver.generated.h"

#pragma region Data Types

USTRUCT(BlueprintType)
struct FUABT_SrcInfo {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int bitrateInKbps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString name = "";

	FUABT_SrcInfo(){}
	FUABT_SrcInfo(const agora::media::base::SrcInfo& srcInfo) {
		bitrateInKbps = srcInfo.bitrateInKbps;
		name = UTF8_TO_TCHAR(srcInfo.name);
	}

	agora::media::base::SrcInfo CreateRawData() const {
		agora::media::base::SrcInfo srcInfo;
		srcInfo.bitrateInKbps = bitrateInKbps;
		srcInfo.name = UABT::New_CharPtr(name);
		return srcInfo;
	}

	void FreeRawData(agora::media::base::SrcInfo& srcInfo) const {
		UABT::Free_CharPtr(srcInfo.name);
	}

};

USTRUCT(BlueprintType)
struct FUABT_CacheStatistics {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 fileSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 cacheSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 downloadSize = 0;
	
	FUABT_CacheStatistics(){}
	FUABT_CacheStatistics(const agora::media::base::CacheStatistics& cacheStatistics) {
		fileSize = cacheStatistics.fileSize;
		cacheSize = cacheStatistics.cacheSize;
		downloadSize = cacheStatistics.downloadSize;
	}

	agora::media::base::CacheStatistics CreateRawData() const {
		agora::media::base::CacheStatistics cacheStatistics;
		cacheStatistics.fileSize = fileSize;
		cacheStatistics.cacheSize = cacheSize;
		cacheStatistics.downloadSize = downloadSize;
		return cacheStatistics;
	}
	void FreeRawData(agora::media::base::CacheStatistics & AgoraData) const {
		
	}
};

USTRUCT(BlueprintType)
struct FUABT_PlayerPlaybackStats {
	
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoFps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoBitrateInKbps =0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioBitrateInKbps =0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int totalBitrateInKbps =0;

	FUABT_PlayerPlaybackStats(){}
	FUABT_PlayerPlaybackStats(const agora::media::base::PlayerPlaybackStats& AgoraData) {
		videoFps = AgoraData.videoFps;
		videoBitrateInKbps = AgoraData.videoBitrateInKbps;
		audioBitrateInKbps = AgoraData.audioBitrateInKbps;
		totalBitrateInKbps = AgoraData.totalBitrateInKbps;
	}

	agora::media::base::PlayerPlaybackStats CreateRawData() const {
		agora::media::base::PlayerPlaybackStats AgoraData;
		AgoraData.videoFps = videoFps;
		AgoraData.videoBitrateInKbps = videoBitrateInKbps;
		AgoraData.audioBitrateInKbps = audioBitrateInKbps;
		AgoraData.totalBitrateInKbps = totalBitrateInKbps;
		return AgoraData;
	}

	void FreeRawData(agora::media::base::PlayerPlaybackStats & AgoraData) const {
		
	}
};


USTRUCT(BlueprintType)
struct FUABT_PlayerUpdatedInfo {
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString internalPlayerUuid = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString deviceId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioBitsPerSample = 0;



	FUABT_PlayerUpdatedInfo(){}
	FUABT_PlayerUpdatedInfo(const agora::media::base::PlayerUpdatedInfo& playerUpdatedInfo) {
		
		internalPlayerUuid = UTF8_TO_TCHAR(playerUpdatedInfo.internalPlayerUuid);
		deviceId = UTF8_TO_TCHAR(playerUpdatedInfo.deviceId);
		videoHeight = playerUpdatedInfo.videoHeight;
		videoWidth = playerUpdatedInfo.videoWidth;
		audioSampleRate = playerUpdatedInfo.audioSampleRate;
		audioChannels = playerUpdatedInfo.audioChannels;
		audioBitsPerSample = playerUpdatedInfo.audioBitsPerSample;
	}

	agora::media::base::PlayerUpdatedInfo CreateRawData() const {
		agora::media::base::PlayerUpdatedInfo AgoraData;

		AgoraData.internalPlayerUuid = UABT::New_CharPtr(this->internalPlayerUuid);
		AgoraData.deviceId = UABT::New_CharPtr(this->deviceId);
		AgoraData.videoHeight = videoHeight;
		AgoraData.videoWidth = videoWidth;
		AgoraData.audioSampleRate = audioSampleRate;
		AgoraData.audioChannels = audioChannels;
		AgoraData.audioBitsPerSample = audioBitsPerSample;

		return AgoraData;
	}

	void FreeRawData(agora::media::base::PlayerUpdatedInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.internalPlayerUuid);
		UABT::Free_CharPtr(AgoraData.deviceId);
	}
};


#pragma endregion Data Types


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSourceStateChanged, EUABT_MEDIA_PLAYER_STATE, state, EUABT_MEDIA_PLAYER_REASON, ec);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPositionChanged, int64, position_ms, int64, timestampMs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerEvent, EUABT_MEDIA_PLAYER_EVENT, eventCode, int64, elapsedTime, const FString &, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaDataSource,const FString &,Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayBufferUpdated, int64, playCachedBuffer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPreloadEvent, const FString&, src, EUABT_PLAYER_PRELOAD_EVENT, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgoraCDNTokenWillExpire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSrcInfoChanged, const FUABT_SrcInfo&, from, const FUABT_SrcInfo&, to);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoUpdated, const FUABT_PlayerUpdatedInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioVolumeIndicationSource, int, volume);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCacheStats, const FUABT_CacheStatistics &, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPlaybackStats, const FUABT_PlayerPlaybackStats&, stats);




class IMediaPlayerSourceObserverClassWrapper : public agora::rtc::IMediaPlayerSourceObserver {};

/**
 *
 */
UCLASS(BlueprintType)
class AGORAPLUGIN_API UAgoraBPuIMediaPlayerSourceObserver : public UObject, public IMediaPlayerSourceObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayerSourceStateChanged OnPlayerSourceStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPositionChanged OnPositionChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayerEvent OnPlayerEvent;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMetaDataSource OnMetaData;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayBufferUpdated OnPlayBufferUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPreloadEvent OnPreloadEvent;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnCompleted OnCompleted;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAgoraCDNTokenWillExpire OnAgoraCDNTokenWillExpire;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayerSrcInfoChanged OnPlayerSrcInfoChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayerInfoUpdated OnPlayerInfoUpdated;
	
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayerCacheStats OnPlayerCacheStats;
	
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlayerPlaybackStats OnPlayerPlaybackStats;
	
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioVolumeIndicationSource OnAudioVolumeIndication;

	void onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_REASON ec) override;

	void onPositionChanged(int64_t positionMs,int64_t timestampMs) override;

	void onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message) override;

	void onMetaData(const void* data, int length) override;

	void onPlayBufferUpdated(int64_t playCachedBuffer) override;

	void onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event) override;

	void onCompleted() override;

	void onAgoraCDNTokenWillExpire() override;

	void onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to) override;

	void onPlayerInfoUpdated(const agora::media::base::PlayerUpdatedInfo& info) override;


	void onPlayerCacheStats(const agora::media::base::CacheStatistics& stats) override;

	void onPlayerPlaybackStats(const agora::media::base::PlayerPlaybackStats& stats) override;

	void onAudioVolumeIndication(int volume) override;



		// You could add multiple executors to the target handler
	UFUNCTION(BlueprintCallable, Category = "Agora|Event")
	void AddBlueprintCallbackExecutor(UAgoraBPuIMediaPlayerSourceObserverCBExecutor* Executor);

	UFUNCTION(BlueprintCallable, Category = "Agora|Event")
	void RemoveAllBlueprintCallbackExecutors();



};


// this is a blueprint callback executor which you could add to the target handler
UCLASS(Blueprintable,Meta = (ShowWorldContextPin))
class AGORAPLUGIN_API UAgoraBPuIMediaPlayerSourceObserverCBExecutor : public UObject {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerSourceStateChanged(EUABT_MEDIA_PLAYER_STATE state, EUABT_MEDIA_PLAYER_REASON ec);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPositionChanged(int64 position_ms, int64 timestampMs);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerEvent(EUABT_MEDIA_PLAYER_EVENT eventCode, int64 elapsedTime, const FString& message);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnMetaData(const FString& Data);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayBufferUpdated(int64 playCachedBuffer);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPreloadEvent(const FString& src, EUABT_PLAYER_PRELOAD_EVENT event);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnCompleted();

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAgoraCDNTokenWillExpire();

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerSrcInfoChanged(const FUABT_SrcInfo& from, const FUABT_SrcInfo& to);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerInfoUpdated(const FUABT_PlayerUpdatedInfo& info);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerCacheStats(const FUABT_CacheStatistics& stats);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerPlaybackStats(const FUABT_PlayerPlaybackStats& stats);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioVolumeIndication(int volume);

};
