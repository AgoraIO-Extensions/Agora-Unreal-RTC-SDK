// Fill out your copyright notice in the Description page of Project Settings.	

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "IFrameObserver.generated.h"

UENUM(BlueprintType)
enum class EBYTES_PER_SAMPLE :uint8 {

	TWO_BYTES_PER_NULL = 0,

	TWO_BYTES_PER_SAMPLE = 2,
};

USTRUCT(BlueprintType)
struct FAudioPcmFrame {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int64 capture_timestamp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int64 samples_per_channel_;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int sample_rate_hz_;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int64 num_channels_;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	EBYTES_PER_SAMPLE bytes_per_sample = EBYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	/*3840 * sizeof(int16_t)*/
	TArray<int64> data_;
};
UENUM(BlueprintType)
enum class EVIDEO_PIXEL_FORMAT :uint8 {

	VIDEO_PIXEL_DEFAULT = 0,

	VIDEO_PIXEL_I420 = 1,

	VIDEO_PIXEL_BGRA = 2,

	VIDEO_PIXEL_NV21 = 3,

	VIDEO_PIXEL_RGBA = 4,

	VIDEO_PIXEL_NV12 = 8,

	VIDEO_TEXTURE_2D = 10,

	VIDEO_TEXTURE_OES = 11,

	VIDEO_CVPIXEL_NV12 = 12,

	VIDEO_CVPIXEL_I420 = 13,

	VIDEO_CVPIXEL_BGRA = 14,

	VIDEO_PIXEL_I422 = 16,
};

USTRUCT(BlueprintType)
struct FVideoFrame {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	EVIDEO_PIXEL_FORMAT type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int yStride;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int uStride;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int vStride;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int rotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<int64> yBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<int64> uBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<int64> vBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int64 renderTimeMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int avsync_type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<int64> metadata_buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int metadata_size;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int64 sharedContext;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int textureId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<float> matrix;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<int64> alphaBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<float> pixelBuffer;
};

UENUM(BlueprintType)
enum class EAUDIO_FRAME_TYPE :uint8 {

	FRAME_TYPE_PCM16 = 0,
};

USTRUCT(BlueprintType)
struct FAudioFrame {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	EAUDIO_FRAME_TYPE type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int samplesPerChannel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	EBYTES_PER_SAMPLE bytesPerSample;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int channels;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int samplesPerSec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int64 buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int64 renderTimeMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int avsync_type;
};
USTRUCT(BlueprintType)
struct FAudioSpectrumData {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioSpectrumData")
	TArray<float> audioSpectrumData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioSpectrumData")
	int dataLength;
};
USTRUCT(BlueprintType)
struct FUserAudioSpectrumInfo {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserAudioSpectrumInfo")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserAudioSpectrumInfo")
	FAudioSpectrumData spectrumData;
};
UENUM(BlueprintType)
enum class EVIDEO_FRAME_TYPE :uint8 {

	VIDEO_FRAME_TYPE_BLANK_FRAME = 0,

	VIDEO_FRAME_TYPE_KEY_FRAME = 3,

	VIDEO_FRAME_TYPE_DELTA_FRAME = 4,

	VIDEO_FRAME_TYPE_B_FRAME = 5,

	VIDEO_FRAME_TYPE_DROPPABLE_FRAME = 6,

	VIDEO_FRAME_TYPE_UNKNOW
};
USTRUCT(BlueprintType)
struct FEncodedVideoFrameInfo {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	EVIDEO_CODEC_TYPE codecType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int framesPerSecond;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	EVIDEO_FRAME_TYPE frameType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	FENUMWRAP_VIDEO_ORIENTATION	rotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int trackId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 captureTimeMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 decodeTimeMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	EVIDEO_STREAM_TYPE streamType;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlaybackAudioFrameBeforeMixing, const FString, channelId, int64, uid, const FAudioFrame&, audioFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalAudioSpectrum, const FAudioSpectrumData&, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteAudioSpectrum, const TArray<FUserAudioSpectrumInfo>, spectrums, int, spectrumNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCaptureVideoFrame, EVIDEO_SOURCE_TYPE, sourceType, const FVideoFrame&, videoFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPreEncodeVideoFrame, EVIDEO_SOURCE_TYPE, sourceType, const FVideoFrame&, videoFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMediaPlayerVideoFrame, const FVideoFrame&, videoFrame, int, mediaPlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRenderVideoFrame, const FString, channelId, int64, remoteUid, const FVideoFrame&, videoFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTranscodedVideoFrame, const FVideoFrame&, videoFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetVideoFrameProcessMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetVideoFormatPreference);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetRotationApplied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetMirrorApplied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetObservedFramePosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIsExternal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRecordAudioFrame, const FString, channelId, const FAudioFrame&, audioFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlaybackAudioFrame, const FString, channelId, const FAudioFrame&, audioFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMixedAudioFrame, const FString, channelId, const FAudioFrame&, audioFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetObservedAudioFramePosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetPlaybackAudioParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetRecordAudioParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetMixedAudioParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFrame, const FAudioPcmFrame&, pcmFrame);


class IAudioFrameObserverClassWrapper : public agora::media::IAudioFrameObserver {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioFrameObserver : public UObject, public IAudioFrameObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlaybackAudioFrameBeforeMixing OnPlaybackAudioFrameBeforeMixing;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecordAudioFrame OnRecordAudioFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlaybackAudioFrame OnPlaybackAudioFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMixedAudioFrame OnMixedAudioFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetObservedAudioFramePosition GetObservedAudioFramePosition;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetPlaybackAudioParams GetPlaybackAudioParams;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetRecordAudioParams GetRecordAudioParams;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetMixedAudioParams GetMixedAudioParams;

	bool onRecordAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame) override;

	bool onPlaybackAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame) override;

	bool onMixedAudioFrame(const char* channelId, agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame) override;

	int getObservedAudioFramePosition() override;

	agora::media::IAudioFrameObserverBase::AudioParams getPlaybackAudioParams() override;

	agora::media::IAudioFrameObserverBase::AudioParams getRecordAudioParams() override;

	agora::media::IAudioFrameObserverBase::AudioParams getMixedAudioParams() override;

	bool onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, AudioFrame& audioFrame) override;

	bool onEarMonitoringAudioFrame(AudioFrame& audioFrame) override;

	AudioParams getEarMonitoringAudioParams() override;

};

class IAudioPcmFrameSinkClassWrapper : public agora::media::IAudioPcmFrameSink {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioPcmFrameSink : public UObject, public IAudioPcmFrameSinkClassWrapper
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFrame OnFrame;

	void onFrame(agora::media::base::AudioPcmFrame* frame) override;
};


class IAudioSpectrumObserverClassWrapper : public agora::media::IAudioSpectrumObserver {};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioSpectrumObserver : public UObject, public IAudioSpectrumObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalAudioSpectrum OnLocalAudioSpectrum;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioSpectrum OnRemoteAudioSpectrum;
	bool onLocalAudioSpectrum(const agora::media::AudioSpectrumData& data) override;

	bool onRemoteAudioSpectrum(const agora::media::UserAudioSpectrumInfo* spectrums, unsigned int spectrumNumber) override;

};


class IVideoFrameObserverClassWrapper : public agora::media::IVideoFrameObserver {};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIVideoFrameObserver : public UObject, public IVideoFrameObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnCaptureVideoFrame OnCaptureVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPreEncodeVideoFrame OnPreEncodeVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMediaPlayerVideoFrame OnMediaPlayerVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRenderVideoFrame OnRenderVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnTranscodedVideoFrame OnTranscodedVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetVideoFrameProcessMode GetVideoFrameProcessMode;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetVideoFormatPreference GetVideoFormatPreference;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetRotationApplied GetRotationApplied;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetMirrorApplied GetMirrorApplied;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetObservedFramePosition GetObservedFramePosition;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FIsExternal IsExternal;


	bool onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame) override;

	bool onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::media::base::VideoFrame& videoFrame) override;

	bool onMediaPlayerVideoFrame(agora::media::base::VideoFrame& videoFrame, int mediaPlayerId) override;

	bool onRenderVideoFrame(const char* channelId, agora::rtc::uid_t remoteUid, agora::media::base::VideoFrame& videoFrame) override;

	bool onTranscodedVideoFrame(agora::media::base::VideoFrame& videoFrame) override;

	agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE getVideoFrameProcessMode() override;

	agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference() override;

	bool getRotationApplied() override;

	bool getMirrorApplied() override;

	uint32_t getObservedFramePosition() override;

	bool isExternal() override;

};

