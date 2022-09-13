// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Private/Include/AgoraHeaderBase.h"
#include "AgoraBluePrint/URtcEngineProxyCompatibility.h"
#include "AgoraIMediaPlayerSourceObserver.generated.h"

UENUM(BlueprintType)
enum EMEDIA_PLAYER_ERROR {

	PLAYER_ERROR_NONE = 0,

	PLAYER_ERROR_INVALID_ARGUMENTS = -1,

	PLAYER_ERROR_INTERNAL = -2,

	PLAYER_ERROR_NO_RESOURCE = -3,

	PLAYER_ERROR_INVALID_MEDIA_SOURCE = -4,

	PLAYER_ERROR_UNKNOWN_STREAM_TYPE = -5,

	PLAYER_ERROR_OBJ_NOT_INITIALIZED = -6,

	PLAYER_ERROR_CODEC_NOT_SUPPORTED = -7,

	PLAYER_ERROR_VIDEO_RENDER_FAILED = -8,

	PLAYER_ERROR_INVALID_STATE = -9,

	PLAYER_ERROR_URL_NOT_FOUND = -10,

	PLAYER_ERROR_INVALID_CONNECTION_STATE = -11,

	PLAYER_ERROR_SRC_BUFFER_UNDERFLOW = -12,

	PLAYER_ERROR_INTERRUPTED = -13,

	PLAYER_ERROR_NOT_SUPPORTED = -14,

	PLAYER_ERROR_TOKEN_EXPIRED = -15,

	PLAYER_ERROR_IP_EXPIRED = -16,
	PLAYER_ERROR_UNKNOWN = -17,
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
enum class EPLAYER_PRELOAD_EVENT :uint8{

	PLAYER_PRELOAD_EVENT_BEGIN = 0,

	PLAYER_PRELOAD_EVENT_COMPLETE = 1,

	PLAYER_PRELOAD_EVENT_ERROR = 2,
};
USTRUCT(BlueprintType)
struct FSrcInfo {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SrcInfo")
	int bitrateInKbps;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SrcInfo")
	FString name;

};
USTRUCT(BlueprintType)
struct FCacheStatistics {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CacheStatistics")
	int64 fileSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CacheStatistics")
	int64 cacheSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CacheStatistics")
	int64 downloadSize;
};

USTRUCT(BlueprintType)
struct FPlayerUpdatedInfo {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	AGORAOPTIONAL playerIdValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	FString playerId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	AGORAOPTIONAL deviceIdValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	FString deviceId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	AGORAOPTIONAL cacheStatisticsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerUpdatedInfo")
	FCacheStatistics cacheStatistics;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSourceStateChanged, EMEDIA_PLAYER_STATE, state, EMEDIA_PLAYER_ERROR, ec);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPositionChanged, int64, position_ms);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerEvent, EMEDIA_PLAYER_EVENT, eventCode, int64, elapsedTime, const FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaDataSource, int64, data, int, length);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayBufferUpdated, int64, playCachedBuffer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPreloadEvent, const FString, src, EPLAYER_PRELOAD_EVENT, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgoraCDNTokenWillExpire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSrcInfoChanged, const FSrcInfo&, from, const FSrcInfo&, to);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoUpdated, const FPlayerUpdatedInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioVolumeIndicationSource, int, volume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReadData, TArray<int64>, buffer, int, bufferSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSeek, int64, offset, int, whence);
/**
 * 
 */
UCLASS(Blueprintable)
class AGORAPLUGIN_API AIMediaPlayerSourceObserver : public AActor, public agora::rtc::IMediaPlayerSourceObserver
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
	FOnAudioVolumeIndicationSource OnAudioVolumeIndication;

	void onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_ERROR ec) override;

	void onPositionChanged(int64_t position_ms) override;

	void onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message) override;

	void onMetaData(const void* data, int length) override;

	void onPlayBufferUpdated(int64_t playCachedBuffer) override;

	void onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event) override;

	void onCompleted() override;

	void onAgoraCDNTokenWillExpire() override;

	void onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to) override;

	void onPlayerInfoUpdated(const agora::media::base::PlayerUpdatedInfo& info) override;

	void onAudioVolumeIndication(int volume) override;

protected:
	void BeginPlay() override;
};

UCLASS(Blueprintable)
class AGORAPLUGIN_API AIMediaPlayerCustomDataProvider : public AActor, public agora::media::base::IMediaPlayerCustomDataProvider
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnReadData OnReadData;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSeek OnSeek;
	int onReadData(unsigned char* buffer, int bufferSize) override;

	int64_t onSeek(int64_t offset, int whence) override;

};
