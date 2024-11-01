//  Copyright (c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "AgoraBPuDataTypes.h"
#include "AgoraBPuIMediaPlayerSourceObserver.generated.h"

#pragma region Data Types

UENUM(BlueprintType)
enum class EENUMCUSTOM_MEDIA_PLAYER_REASON : uint8 {
	PLAYER_REASON_NONE = 0,

	PLAYER_REASON_INVALID_ARGUMENTS = 1,

	PLAYER_REASON_INTERNAL = 2,


	PLAYER_REASON_NO_RESOURCE = 3,

	PLAYER_REASON_INVALID_MEDIA_SOURCE = 4,

	PLAYER_REASON_UNKNOWN_STREAM_TYPE = 5,

	PLAYER_REASON_OBJ_NOT_INITIALIZED = 6,

	PLAYER_REASON_CODEC_NOT_SUPPORTED = 7,

	PLAYER_REASON_VIDEO_RENDER_FAILED = 8,

	PLAYER_REASON_INVALID_STATE = 9,

	PLAYER_REASON_URL_NOT_FOUND = 10,

	PLAYER_REASON_INVALID_CONNECTION_STATE = 11,

	PLAYER_REASON_SRC_BUFFER_UNDERFLOW = 12,

	PLAYER_REASON_INTERRUPTED = 13,

	PLAYER_REASON_NOT_SUPPORTED = 14,

	PLAYER_REASON_TOKEN_EXPIRED = 15,

	PLAYER_REASON_IP_EXPIRED = 16,

	PLAYER_REASON_UNKNOWN = 17,

};

USTRUCT(BlueprintType)
struct FENUMWRAP_MEDIA_PLAYER_REASON {

	GENERATED_BODY()

public:

	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_MEDIA_PLAYER_REASON")
	EENUMCUSTOM_MEDIA_PLAYER_REASON ValueWrapper = EENUMCUSTOM_MEDIA_PLAYER_REASON::PLAYER_REASON_NONE;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_18_ENTRIES(FENUMWRAP_MEDIA_PLAYER_REASON, agora::media::base::MEDIA_PLAYER_REASON,EENUMCUSTOM_MEDIA_PLAYER_REASON, 
		PLAYER_REASON_NONE, 
		PLAYER_REASON_INVALID_ARGUMENTS, 
		PLAYER_REASON_INTERNAL, 
		PLAYER_REASON_NO_RESOURCE, 
		PLAYER_REASON_INVALID_MEDIA_SOURCE, 
		PLAYER_REASON_UNKNOWN_STREAM_TYPE, 
		PLAYER_REASON_OBJ_NOT_INITIALIZED, 
		PLAYER_REASON_CODEC_NOT_SUPPORTED, 
		PLAYER_REASON_VIDEO_RENDER_FAILED, 
		PLAYER_REASON_INVALID_STATE, 
		PLAYER_REASON_URL_NOT_FOUND, 
		PLAYER_REASON_INVALID_CONNECTION_STATE, 
		PLAYER_REASON_SRC_BUFFER_UNDERFLOW, 
		PLAYER_REASON_INTERRUPTED, 
		PLAYER_REASON_NOT_SUPPORTED, 
		PLAYER_REASON_TOKEN_EXPIRED, 
		PLAYER_REASON_IP_EXPIRED, 
		PLAYER_REASON_UNKNOWN);
};

UENUM(BlueprintType)
enum EMEDIA_PLAYER_EVENT {

	PLAYER_EVENT_SEEK_BEGIN = 0,

	PLAYER_EVENT_SEEK_COMPLETE = 1,

	PLAYER_EVENT_SEEK_ERROR = 2,

	PLAYER_EVENT_AUDIO_TRACK_CHANGED = 5,

	PLAYER_EVENT_BUFFER_LOW = 6,

	PLAYER_EVENT_BUFFER_RECOVER = 7,

	PLAYER_EVENT_FREEZE_START = 8,

	PLAYER_EVENT_FREEZE_STOP = 9,

	PLAYER_EVENT_SWITCH_BEGIN = 10,

	PLAYER_EVENT_SWITCH_COMPLETE = 11,

	PLAYER_EVENT_SWITCH_ERROR = 12,

	PLAYER_EVENT_FIRST_DISPLAYED = 13,

	PLAYER_EVENT_REACH_CACHE_FILE_MAX_COUNT = 14,

	PLAYER_EVENT_REACH_CACHE_FILE_MAX_SIZE = 15,

	PLAYER_EVENT_TRY_OPEN_START = 16,

	PLAYER_EVENT_TRY_OPEN_SUCCEED = 17,

	PLAYER_EVENT_TRY_OPEN_FAILED = 18,
};


UENUM(BlueprintType)
enum class EPLAYER_PRELOAD_EVENT :uint8 {

	PLAYER_PRELOAD_EVENT_BEGIN = 0,

	PLAYER_PRELOAD_EVENT_COMPLETE = 1,

	PLAYER_PRELOAD_EVENT_ERROR = 2,
};


USTRUCT(BlueprintType)
struct FSrcInfo {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SrcInfo")
	int bitrateInKbps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SrcInfo")
	FString name = "";

	FSrcInfo(){}
	FSrcInfo(const agora::media::base::SrcInfo& srcInfo) {
		bitrateInKbps = srcInfo.bitrateInKbps;
		name = UTF8_TO_TCHAR(srcInfo.name);
	}

	agora::media::base::SrcInfo CreateAgoraData() const {
		agora::media::base::SrcInfo srcInfo;
		srcInfo.bitrateInKbps = bitrateInKbps;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(srcInfo.name,name)
		return srcInfo;
	}

	void FreeAgoraData(agora::media::base::SrcInfo& srcInfo) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(srcInfo.name)
	}

};

USTRUCT(BlueprintType)
struct FCacheStatistics {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CacheStatistics")
	int64 fileSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CacheStatistics")
	int64 cacheSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CacheStatistics")
	int64 downloadSize = 0;
	
	FCacheStatistics(){}
	FCacheStatistics(const agora::media::base::CacheStatistics& cacheStatistics) {
		fileSize = cacheStatistics.fileSize;
		cacheSize = cacheStatistics.cacheSize;
		downloadSize = cacheStatistics.downloadSize;
	}

	agora::media::base::CacheStatistics CreateAgoraData() const {
		agora::media::base::CacheStatistics cacheStatistics;
		cacheStatistics.fileSize = fileSize;
		cacheStatistics.cacheSize = cacheSize;
		cacheStatistics.downloadSize = downloadSize;
		return cacheStatistics;
	}
	void FreeAgoraData(agora::media::base::CacheStatistics & AgoraData) const {
		
	}
};

USTRUCT(BlueprintType)
struct FPlayerPlaybackStats {
	
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPlayerPlaybackStats")
	int videoFps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPlayerPlaybackStats")
	int videoBitrateInKbps =0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPlayerPlaybackStats")
	int audioBitrateInKbps =0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPlayerPlaybackStats")
	int totalBitrateInKbps =0;

	FPlayerPlaybackStats(){}
	FPlayerPlaybackStats(const agora::media::base::PlayerPlaybackStats& AgoraData) {
		videoFps = AgoraData.videoFps;
		videoBitrateInKbps = AgoraData.videoBitrateInKbps;
		audioBitrateInKbps = AgoraData.audioBitrateInKbps;
		totalBitrateInKbps = AgoraData.totalBitrateInKbps;
	}

	agora::media::base::PlayerPlaybackStats CreateAgoraData() const {
		agora::media::base::PlayerPlaybackStats AgoraData;
		AgoraData.videoFps = videoFps;
		AgoraData.videoBitrateInKbps = videoBitrateInKbps;
		AgoraData.audioBitrateInKbps = audioBitrateInKbps;
		AgoraData.totalBitrateInKbps = totalBitrateInKbps;
		return AgoraData;
	}

	void FreeAgoraData(agora::media::base::PlayerPlaybackStats & AgoraData) const {
		
	}
};


USTRUCT(BlueprintType)
struct FPlayerUpdatedInfo {
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	FString internalPlayerUuid = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	FString deviceId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	int videoHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	int videoWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	int audioSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	int audioChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	int audioBitsPerSample = 0;



	FPlayerUpdatedInfo(){}
	FPlayerUpdatedInfo(const agora::media::base::PlayerUpdatedInfo& playerUpdatedInfo) {
		
		internalPlayerUuid = UTF8_TO_TCHAR(playerUpdatedInfo.internalPlayerUuid);
		deviceId = UTF8_TO_TCHAR(playerUpdatedInfo.deviceId);
		videoHeight = playerUpdatedInfo.videoHeight;
		videoWidth = playerUpdatedInfo.videoWidth;
		audioSampleRate = playerUpdatedInfo.audioSampleRate;
		audioChannels = playerUpdatedInfo.audioChannels;
		audioBitsPerSample = playerUpdatedInfo.audioBitsPerSample;
	}

	agora::media::base::PlayerUpdatedInfo CreateAgoraData() const {
		agora::media::base::PlayerUpdatedInfo AgoraData;

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.internalPlayerUuid,this->internalPlayerUuid)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.deviceId,this->deviceId)
		AgoraData.videoHeight = videoHeight;
		AgoraData.videoWidth = videoWidth;
		AgoraData.audioSampleRate = audioSampleRate;
		AgoraData.audioChannels = audioChannels;
		AgoraData.audioBitsPerSample = audioBitsPerSample;

		return AgoraData;
	}

	void FreeAgoraData(agora::media::base::PlayerUpdatedInfo & AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.internalPlayerUuid)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.deviceId)
	}
};


#pragma endregion Data Types


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSourceStateChanged, EUABT_MEDIA_PLAYER_STATE, state, FENUMWRAP_MEDIA_PLAYER_REASON, ec);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPositionChanged, int64, position_ms, int64, timestampMs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerEvent, EMEDIA_PLAYER_EVENT, eventCode, int64, elapsedTime, const FString &, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaDataSource,const FString &,Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayBufferUpdated, int64, playCachedBuffer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPreloadEvent, const FString&, src, EPLAYER_PRELOAD_EVENT, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgoraCDNTokenWillExpire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSrcInfoChanged, const FSrcInfo&, from, const FSrcInfo&, to);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoUpdated, const FPlayerUpdatedInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioVolumeIndicationSource, int, volume);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCacheStats, const FCacheStatistics &, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPlaybackStats, const FPlayerPlaybackStats&, stats);




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
	void OnPlayerSourceStateChanged(EUABT_MEDIA_PLAYER_STATE state, FENUMWRAP_MEDIA_PLAYER_REASON ec);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPositionChanged(int64 position_ms, int64 timestampMs);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerEvent(EMEDIA_PLAYER_EVENT eventCode, int64 elapsedTime, const FString& message);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnMetaData(const FString& Data);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayBufferUpdated(int64 playCachedBuffer);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPreloadEvent(const FString& src, EPLAYER_PRELOAD_EVENT event);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnCompleted();

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAgoraCDNTokenWillExpire();

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerSrcInfoChanged(const FSrcInfo& from, const FSrcInfo& to);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerInfoUpdated(const FPlayerUpdatedInfo& info);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerCacheStats(const FCacheStatistics& stats);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPlayerPlaybackStats(const FPlayerPlaybackStats& stats);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioVolumeIndication(int volume);

};
