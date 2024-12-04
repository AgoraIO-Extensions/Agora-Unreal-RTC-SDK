//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "AgoraPluginInterface.h"
#include "IAgoraMediaPlayer.h" // because UE has a IMediaPlayer class
#include "AgoraBPuDataTypes.h"
#include "AgoraBPuIMediaPlayerSourceObserver.h"
#include "UObject/StrongObjectPtr.h"

#include "AgoraBPuMediaPlayer.generated.h"


#pragma region  Data Types

USTRUCT(BlueprintType)
struct FUABT_AgoraMediaSource
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	FString url = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	FString uri = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	int64 startPos = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	bool autoPlay = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	bool enableCache = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	bool enableMultiAudioTrack = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	FUABT_Opt_bool isAgoraSource;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	FUABT_Opt_bool isLiveSource;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaSource")
	//UIMediaPlayerCustomDataProvider* provider = nullptr;

	FUABT_AgoraMediaSource(){}
	FUABT_AgoraMediaSource(const agora::media::base::MediaSource & AgoraData){
		url = UTF8_TO_TCHAR(AgoraData.url);
		uri = UTF8_TO_TCHAR(AgoraData.uri);
		startPos = AgoraData.startPos;
		autoPlay = AgoraData.autoPlay;
		enableCache = AgoraData.enableCache;
		enableMultiAudioTrack = AgoraData.enableMultiAudioTrack;
		this->isAgoraSource = AgoraData.isAgoraSource;
		this->isLiveSource = AgoraData.isLiveSource;
		// provider = AgoraData.provider; not supported
	}

	agora::media::base::MediaSource CreateRawData() const {
		agora::media::base::MediaSource AgoraData;
		
		AgoraData.url = UABT::New_CharPtr(url);
		AgoraData.uri = UABT::New_CharPtr(uri);
		AgoraData.startPos = startPos;
		AgoraData.autoPlay = autoPlay;
		AgoraData.enableCache = enableCache;
		AgoraData.enableMultiAudioTrack = enableMultiAudioTrack;
		AgoraData.isAgoraSource = isAgoraSource.CreateRawOptData();
		AgoraData.isLiveSource = isLiveSource.CreateRawOptData();
		// not supported
		return AgoraData;
	}

	void FreeRawData(agora::media::base::MediaSource& AgoraData) const{
		UABT::Free_CharPtr(AgoraData.url);
		UABT::Free_CharPtr(AgoraData.uri);

		FUABT_Opt_bool::FreeRawOptData(AgoraData.isAgoraSource);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.isLiveSource);
	}

};


USTRUCT(BlueprintType)
struct FUABT_PlayerStreamInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int streamIndex = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	EUABT_MEDIA_STREAM_TYPE streamType = EUABT_MEDIA_STREAM_TYPE::STREAM_TYPE_UNKNOWN;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	FString codecName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	FString language = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int videoRotation = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int audioSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int audioChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int audioBitsPerSample = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PlayerStreamInfo")
	int duration = 0;

	FUABT_PlayerStreamInfo(){}
	FUABT_PlayerStreamInfo(const agora::media::base::PlayerStreamInfo & AgoraData){
		streamIndex = AgoraData.streamIndex;
		streamType = (EUABT_MEDIA_STREAM_TYPE)AgoraData.streamType;
		codecName = UTF8_TO_TCHAR(AgoraData.codecName);
		language = UTF8_TO_TCHAR(AgoraData.language);
		videoFrameRate = AgoraData.videoFrameRate;
		videoBitRate = AgoraData.videoBitRate;
		videoWidth = AgoraData.videoWidth;
		videoHeight = AgoraData.videoHeight;
		videoRotation = AgoraData.videoRotation;
		audioSampleRate = AgoraData.audioSampleRate;
		audioChannels = AgoraData.audioChannels;
		audioBitsPerSample = AgoraData.audioBitsPerSample;
		duration = AgoraData.duration;
	}

	agora::media::base::PlayerStreamInfo CreateRawData() const {
		agora::media::base::PlayerStreamInfo AgoraData;
		AgoraData.streamIndex = streamIndex;
		AgoraData.streamType = (agora::media::base::MEDIA_STREAM_TYPE)streamType;
		UABT::SetCharArrayPtr(AgoraData.codecName, codecName,agora::media::base::kMaxCharBufferLength);
		UABT::SetCharArrayPtr(AgoraData.language, language, agora::media::base::kMaxCharBufferLength);
		AgoraData.videoFrameRate = videoFrameRate;
		AgoraData.videoBitRate = videoBitRate;
		AgoraData.videoWidth = videoWidth;
		AgoraData.videoHeight = videoHeight;
		AgoraData.videoRotation = videoRotation;
		AgoraData.audioSampleRate = audioSampleRate;
		AgoraData.audioChannels = audioChannels;
		AgoraData.audioBitsPerSample = audioBitsPerSample;
		AgoraData.duration = duration;
		return AgoraData;
	}

	void FreeRawData(agora::media::base::PlayerStreamInfo & AgoraData) const {
	
	}
};


#pragma endregion  Data Types


/**
 * 
 */
UCLASS()
class AGORAPLUGIN_API UAgoraBPuMediaPlayer : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Agora|IAgoraMediaPlayer")
	static UAgoraBPuMediaPlayer* GetAgoraMediaPlayer();

	UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaPlayer")
	void Release();

	UFUNCTION(BlueprintPure, Category = "Agora|IRtcEngine")
	UAgoraBPuIMediaPlayerSourceObserver* GetMediaPlayerSourceObserver();



#pragma region API
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetMediaPlayerId();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Open(const FString & url, int64 startPos);
	
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int OpenWithCustomSource(int64 startPos, UIMediaPlayerCustomDataProvider* provider);

	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int OpenWithMediaSource(const FUABT_AgoraMediaSource& source);
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
	int GetStreamInfo(int64 index, FUABT_PlayerStreamInfo& info);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetLoopCount(int loopCount);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetPlaybackSpeed(int speed);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SelectAudioTrack(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SelectMultiAudioTrack(int playoutTrackIndex, int publishTrackIndex);

	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetPlayerOptionWithInt(const FString & key, int value);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetPlayerOptionWithString(const FString & key, const FString & value);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int TakeScreenshot(const FString& filename);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SelectInternalSubtitle(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetExternalSubtitle(const FString& url);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	EUABT_MEDIA_PLAYER_STATE GetState();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int Mute(bool muted);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetMute(bool & muted);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int AdjustPlayoutVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetPlayoutVolume(int & volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int AdjustPublishSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetPublishSignalVolume(int & volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetView(int64 view);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetRenderMode(EUABT_RENDER_MODE_TYPE renderMode);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int RegisterPlayerSourceObserver(UIMediaPlayerSourceObserver* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int UnregisterPlayerSourceObserver(UIMediaPlayerSourceObserver* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int RegisterAudioFrameObserver(UIAudioPcmFrameSink* observer, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode = EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_ONLY);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int UnregisterAudioFrameObserver(UIAudioPcmFrameSink* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int RegisterVideoFrameObserver(UIVideoFrameObserver* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int UnregisterVideoFrameObserver(UIVideoFrameObserver* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int RegisterMediaPlayerAudioSpectrumObserver(UIAudioSpectrumObserver* observer, int intervalInMS);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	//int UnregisterMediaPlayerAudioSpectrumObserver(UIAudioSpectrumObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetAudioDualMonoMode(EUABT_AUDIO_DUAL_MONO_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	FString GetPlayerSdkVersion();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	FString GetPlaySrc();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int OpenWithAgoraCDNSrc(const FString& src, int64 startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetAgoraCDNLineCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SwitchAgoraCDNLineByIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int GetCurrentAgoraCDNIndex();
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int EnableAutoSwitchAgoraCDN(bool enable);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int RenewAgoraCDNSrcToken(const FString & token, int64 ts);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SwitchAgoraCDNSrc(const FString& src, bool syncPts = false);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SwitchSrc(const FString& src, bool syncPts = true);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int PreloadSrc(const FString& src, int64 startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int PlayPreloadedSrc(const FString& src);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int UnloadSrc(const FString& src);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetSpatialAudioParams(const FUABT_SpatialAudioParams& params);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaPlayer")
	int SetSoundPositionParams(float pan, float gain);

#pragma endregion API



private:

	static UAgoraBPuMediaPlayer* Instance;

	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer;
	
	TStrongObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> UserMediaPlayerSourceObserver = nullptr;
};
