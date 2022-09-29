// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "URtcEngineProxyCompatibility.h"
#include "AgoraIMediaPlayerSourceObserver.h"
#include "IFrameObserver.h"
#include "AgoraMediaPlayer.generated.h"

USTRUCT(BlueprintType)
struct FAgoraMediaSource
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	FString url;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	FString uri;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	int startPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	bool autoPlay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	bool enableCache;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	AGORAOPTIONAL isAgoraSource;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	AGORAOPTIONAL isLiveSource;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	AIMediaPlayerCustomDataProvider* provider;
};
UENUM(BlueprintType)
enum class EAUDIO_DUAL_MONO_MODE : uint8 {
	AUDIO_DUAL_MONO_STEREO = 0,
	AUDIO_DUAL_MONO_L = 1,
	AUDIO_DUAL_MONO_R = 2,
	AUDIO_DUAL_MONO_MIX = 3
};

UENUM(BlueprintType)
enum class EMEDIA_STREAM_TYPE : uint8 {

	STREAM_TYPE_UNKNOWN = 0,

	STREAM_TYPE_VIDEO = 1,

	STREAM_TYPE_AUDIO = 2,

	STREAM_TYPE_SUBTITLE = 3,
};

USTRUCT(BlueprintType)
struct FPlayerStreamInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int streamIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	EMEDIA_STREAM_TYPE streamType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	FString codecName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	FString language;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int audioSampleRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int audioChannels;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int audioBitsPerSample;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int duration;
};



/**
 * 
 */
UCLASS(Blueprintable)
class AGORAPLUGIN_API UIMediaPlayer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetMediaPlayerId();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Open(FString url, int64 startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int OpenWithCustomSource(int64 startPos, AIMediaPlayerCustomDataProvider* provider);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int OpenWithMediaSource(FAgoraMediaSource& source);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Play();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Pause();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Stop();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Resume();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Seek(int64 newPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetAudioPitch(int pitch);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetDuration(int64& duration);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetPlayPosition(int64& pos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetStreamCount(int64& count);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetStreamInfo(int64 index, FPlayerStreamInfo& info);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetLoopCount(int loopCount);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetPlaybackSpeed(int speed);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SelectAudioTrack(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetPlayerOption(FString key, FString value);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int TakeScreenshot(FString filename);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SelectInternalSubtitle(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetExternalSubtitle(FString url);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	EMEDIA_PLAYER_STATE GetState();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Mute(bool muted);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetMute(bool muted);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int AdjustPlayoutVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetPlayoutVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int AdjustPublishSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetPublishSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetView(int64 view);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetRenderMode(ERENDER_MODE_TYPE renderMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int RegisterPlayerSourceObserver(AIMediaPlayerSourceObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int UnregisterPlayerSourceObserver(AIMediaPlayerSourceObserver* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int RegisterAudioFrameObserver(UIAudioFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int RegisterAudioFrameObserver(AIAudioFrameObserver* observer, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int UnregisterAudioFrameObserver(AIAudioFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int RegisterVideoFrameObserver(AIVideoFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int UnregisterVideoFrameObserver(AIVideoFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int RegisterMediaPlayerAudioSpectrumObserver(AIAudioSpectrumObserver* observer, int intervalInMS);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int UnregisterMediaPlayerAudioSpectrumObserver(AIAudioSpectrumObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetAudioDualMonoMode(EAUDIO_DUAL_MONO_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	FString GetPlayerSdkVersion();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	FString GetPlaySrc();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int OpenWithAgoraCDNSrc(FString src, int64 startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetAgoraCDNLineCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SwitchAgoraCDNLineByIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetCurrentAgoraCDNIndex();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int EnableAutoSwitchAgoraCDN(bool enable);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int RenewAgoraCDNSrcToken(FString token, int64 ts);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SwitchAgoraCDNSrc(FString src, bool syncPts);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SwitchSrc(FString src, bool syncPts);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int PreloadSrc(FString src, int64 startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int PlayPreloadedSrc(FString src);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int UnloadSrc(FString src);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetSpatialAudioParams(FSpatialAudioParams& params);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetSoundPositionParams(float pan, float gain);
	void SetMediaPlayer(agora::agora_refptr<agora::rtc::IMediaPlayer> mediaPlayer);
	agora::agora_refptr<agora::rtc::IMediaPlayer> GetMediaPlayer();
private:
	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer;
};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIMediaPlayerCacheManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int RemoveAllCaches();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int RemoveOldCache();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int RemoveCacheByUri(FString uri);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int SetCacheDir(FString path);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int SetMaxCacheFileCount(int count);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int SetMaxCacheFileSize(int64 cacheSize);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int EnableAutoRemoveCache(bool enable);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int GetCacheDir(FString path, int length);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int GetMaxCacheFileCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int64 GetMaxCacheFileSize();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayerCacheManager")
	int GetCacheFileCount();
};

