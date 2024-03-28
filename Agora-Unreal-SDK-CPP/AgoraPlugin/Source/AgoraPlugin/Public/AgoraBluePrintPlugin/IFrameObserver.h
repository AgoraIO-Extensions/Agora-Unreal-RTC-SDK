//  Copyright (c) 2023 Agora.io. All rights reserved.	

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/include/AgoraHeaderBase.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "IFrameObserver.generated.h"


UENUM(BlueprintType)
enum class EBYTES_PER_SAMPLE :uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	TWO_BYTES_PER_SAMPLE = 2,
};

USTRUCT(BlueprintType)
struct FAudioPcmFrame {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int64 capture_timestamp = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int64 samples_per_channel_ = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int sample_rate_hz_ = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	int64 num_channels_ = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	EBYTES_PER_SAMPLE bytes_per_sample = EBYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioPcmFrame")
	/*3840 * sizeof(int16_t)*/
	TArray<int32> data_;

	FAudioPcmFrame(){}
	FAudioPcmFrame(const agora::media::base::AudioPcmFrame & AgoraData){
		
		capture_timestamp = AgoraData.capture_timestamp;
		samples_per_channel_ = AgoraData.samples_per_channel_;
		sample_rate_hz_ = AgoraData.sample_rate_hz_;
		num_channels_ = AgoraData.num_channels_;
		bytes_per_sample = (EBYTES_PER_SAMPLE)AgoraData.bytes_per_sample;
		for(int i =0; i< 3840;i++){
			data_.Add(AgoraData.data_[i]);
		}
	}

	agora::media::base::AudioPcmFrame CreateAgoraData() const {
		
		agora::media::base::AudioPcmFrame AgoraData;
		AgoraData.capture_timestamp = capture_timestamp;
		AgoraData.samples_per_channel_ = samples_per_channel_;
		AgoraData.sample_rate_hz_ = sample_rate_hz_;
		AgoraData.num_channels_ = num_channels_;
		AgoraData.bytes_per_sample = (agora::rtc::BYTES_PER_SAMPLE)bytes_per_sample;
		for(int i =0; i< 3840;i++){
			AgoraData.data_[i] = data_[i];
		}
		return AgoraData;
	
	}
	
	void FreeAgoraData(agora::media::base::AudioPcmFrame & AgoraData) const {
	
	}
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

	VIDEO_TEXTURE_ID3D11TEXTURE2D = 17,
	
	VIDEO_PIXEL_I010 = 18,

};

USTRUCT(BlueprintType)
struct FVideoFrame {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	EVIDEO_PIXEL_FORMAT type = EVIDEO_PIXEL_FORMAT::VIDEO_PIXEL_DEFAULT;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int yStride = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int uStride = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int vStride = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<uint8> yBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<uint8> uBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<uint8> vBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int rotation = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int64 renderTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int avsync_type = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<uint8> metadata_buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int metadata_size = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int64 sharedContext = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int textureId = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int64 d3d11Texture2d = 0;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<float> matrix;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	TArray<uint8> alphaBuffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	int64 pixelBuffer = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFrame")
	UIVideoFrameMetaInfo* metaInfo = nullptr;


	FVideoFrame() {}
	FVideoFrame(const agora::media::base::VideoFrame& AgoraData) {

		type = static_cast<EVIDEO_PIXEL_FORMAT>(AgoraData.type);
		width = AgoraData.width;
		height = AgoraData.height;
		yStride = AgoraData.yStride;
		uStride = AgoraData.uStride;
		vStride = AgoraData.vStride;
		for (int i = 0; i < AgoraData.yStride; i++) {
			yBuffer.Add(AgoraData.yBuffer[i]);
		}
		for (int i = 0; i < AgoraData.uStride; i++) {
			uBuffer.Add(AgoraData.uBuffer[i]);
		}
		for (int i = 0; i < AgoraData.vStride; i++) {
			vBuffer.Add(AgoraData.vBuffer[i]);
		}
		rotation = AgoraData.rotation;
		renderTimeMs = AgoraData.renderTimeMs;
		avsync_type = AgoraData.avsync_type;
		metadata_size = AgoraData.metadata_size;
		for (int i = 0; i < AgoraData.metadata_size; i++) {
			metadata_buffer.Add(AgoraData.metadata_buffer[i]);
		}
		// sharedContext = AgoraData.sharedContext; not supported
		textureId = AgoraData.textureId;

		// d3d11Texture2d = AgoraData.d3d11Texture2d; not supported

		for (int i = 0; i < 16; i++) {
			matrix.Add(AgoraData.matrix[i]);
		}
		int Size = AgoraData.width * AgoraData.height;
		for (int i = 0; i < Size; i++) {
			alphaBuffer.Add(AgoraData.alphaBuffer[i]);
		}
		// pixelBuffer = AgoraData.pixelBuffer; not supported

		// metaInfo = AgoraData.metaInfo; not supported
	}

	agora::media::base::VideoFrame CreateAgoraData() const {

		agora::media::base::VideoFrame AgoraData;
		AgoraData.type = (agora::media::base::VIDEO_PIXEL_FORMAT)type;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.yStride = yStride;
		AgoraData.uStride = uStride;
		AgoraData.vStride = vStride;

		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(AgoraData.yBuffer,this->yBuffer)
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(AgoraData.uBuffer, this->uBuffer)
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(AgoraData.vBuffer, this->vBuffer)

		AgoraData.rotation = rotation;
		AgoraData.renderTimeMs = renderTimeMs;
		AgoraData.avsync_type = avsync_type;
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(AgoraData.metadata_buffer,this->metadata_buffer)
		AgoraData.metadata_size = metadata_size;
		// AgoraData.sharedContext = sharedContext; not supported
		AgoraData.textureId = textureId;

		// AgoraData.d3d11Texture2d = d3d11Texture2d; not supported

		for (int i = 0; i < 16; i++) {
			AgoraData.matrix[i] = matrix[i];
		}
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(AgoraData.alphaBuffer, this->alphaBuffer)
		// AgoraData.pixelBuffer = pixelBuffer; not supported

		// AgoraData.metaInfo = metaInfo; not supported
		return AgoraData;

	}

	void FreeAgoraData(agora::media::base::VideoFrame& AgoraData) const {
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(AgoraData.yBuffer)
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(AgoraData.uBuffer)
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(AgoraData.vBuffer)
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(AgoraData.metadata_buffer)
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(AgoraData.alphaBuffer)
	}
};

UENUM(BlueprintType)
enum class EAUDIO_FRAME_TYPE :uint8 {

	FRAME_TYPE_PCM16 = 0,
};

USTRUCT(BlueprintType)
struct FAudioFrame {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	EAUDIO_FRAME_TYPE type = EAUDIO_FRAME_TYPE::FRAME_TYPE_PCM16;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int samplesPerChannel = 441;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	EBYTES_PER_SAMPLE bytesPerSample = EBYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int channels = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int samplesPerSec = 44100;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	TArray<uint8> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int64 renderTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int avsync_type = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int64 presentationMs = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int audioTrackNumber = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioFrame")
	int64 rtpTimestamp = 0;


	FAudioFrame() {}
	FAudioFrame(const agora::media::IAudioFrameObserverBase::AudioFrame& AgoraData) {

		type = static_cast<EAUDIO_FRAME_TYPE>(AgoraData.type);
		samplesPerChannel = AgoraData.samplesPerChannel;
		bytesPerSample = (EBYTES_PER_SAMPLE)AgoraData.bytesPerSample;
		channels = AgoraData.channels;
		samplesPerSec = AgoraData.samplesPerSec;
		// For Now it's uint8
		for (int i = 0; i < AgoraData.samplesPerChannel; i++) {
			buffer.Add(((uint8*)(AgoraData.buffer))[i]);
		}
		renderTimeMs = AgoraData.renderTimeMs;
		avsync_type = AgoraData.avsync_type;
		presentationMs = AgoraData.presentationMs;
		audioTrackNumber = AgoraData.audioTrackNumber;
		rtpTimestamp = AgoraData.rtpTimestamp;

	}

	agora::media::IAudioFrameObserverBase::AudioFrame CreateAgoraData() const {

		agora::media::IAudioFrameObserverBase::AudioFrame AgoraData;
		AgoraData.type = (agora::media::IAudioFrameObserverBase::AUDIO_FRAME_TYPE)type;
		AgoraData.samplesPerChannel = samplesPerChannel;
		AgoraData.bytesPerSample = (agora::rtc::BYTES_PER_SAMPLE)bytesPerSample;
		AgoraData.channels = channels;
		AgoraData.samplesPerSec = samplesPerSec;
		uint8* TmpBufferPtr = (uint8*)AgoraData.buffer;
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(TmpBufferPtr, this->buffer)
		AgoraData.renderTimeMs = renderTimeMs;
		AgoraData.avsync_type = avsync_type;

		AgoraData.presentationMs = presentationMs;
		AgoraData.audioTrackNumber = audioTrackNumber;
		AgoraData.rtpTimestamp = rtpTimestamp;

		return AgoraData;

	}

	void FreeAgoraData(agora::media::IAudioFrameObserverBase::AudioFrame& AgoraData) const {
		uint8* TmpBufferPtr = (uint8*)AgoraData.buffer;
		SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(TmpBufferPtr)
		AgoraData.buffer = nullptr;
	}
};
USTRUCT(BlueprintType)
struct FAudioSpectrumData {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioSpectrumData")
	TArray<float> audioSpectrumData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioSpectrumData")
	int dataLength = 0;

	FAudioSpectrumData(){}
	FAudioSpectrumData(const agora::media::AudioSpectrumData & AgoraData){
		
		dataLength = AgoraData.dataLength;
		for(int i =0; i< AgoraData.dataLength;i++){
			audioSpectrumData.Add(AgoraData.audioSpectrumData[i]);
		}
	}

	agora::media::AudioSpectrumData CreateAgoraData() const {
		
		agora::media::AudioSpectrumData AgoraData;
		AgoraData.dataLength = dataLength;
		SET_UABT_GENERIC_TARRAY_TO_AGORA_PTR___MEMALLOC(AgoraData.audioSpectrumData,this->audioSpectrumData,float ,(this->audioSpectrumData).Num() * sizeof(float))
		return AgoraData;
	
	}

	void FreeAgoraData(agora::media::AudioSpectrumData & AgoraData) const {
		SET_UABT_GENERIC_TARRAY_TO_AGORA_PTR___MEMFREE(AgoraData.audioSpectrumData)
	}
};
USTRUCT(BlueprintType)
struct FUserAudioSpectrumInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserAudioSpectrumInfo")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserAudioSpectrumInfo")
	FAudioSpectrumData spectrumData = FAudioSpectrumData();

	FUserAudioSpectrumInfo(){}
	FUserAudioSpectrumInfo(const agora::media::UserAudioSpectrumInfo & AgoraData){
		uid = AgoraData.uid;
		spectrumData = FAudioSpectrumData(AgoraData.spectrumData);
	}

	agora::media::UserAudioSpectrumInfo CreateAgoraData() const {
		agora::media::UserAudioSpectrumInfo AgoraData;
		AgoraData.uid = uid;
		AgoraData.spectrumData = spectrumData.CreateAgoraData();
		return AgoraData;
	}

	void FreeAgoraData(agora::media::UserAudioSpectrumInfo & AgoraData) const {
		spectrumData.FreeAgoraData(AgoraData.spectrumData);
	}

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

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 uid = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	EVIDEO_CODEC_TYPE codecType = EVIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int framesPerSecond = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	EVIDEO_FRAME_TYPE frameType = EVIDEO_FRAME_TYPE::VIDEO_FRAME_TYPE_BLANK_FRAME;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	FENUMWRAP_VIDEO_ORIENTATION	rotation = EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int trackId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 captureTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 decodeTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	EVIDEO_STREAM_TYPE streamType = EVIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedVideoFrameInfo")
	int64 presentationMs;


	FEncodedVideoFrameInfo(){}
	FEncodedVideoFrameInfo(const agora::rtc::EncodedVideoFrameInfo & AgoraData){
		uid = AgoraData.uid;
		codecType = static_cast<EVIDEO_CODEC_TYPE>(AgoraData.codecType);
		width = AgoraData.width;
		height = AgoraData.height;
		framesPerSecond = AgoraData.framesPerSecond;
		frameType = static_cast<EVIDEO_FRAME_TYPE>(AgoraData.frameType);
		rotation = static_cast<FENUMWRAP_VIDEO_ORIENTATION>(AgoraData.rotation);
		trackId = AgoraData.trackId;
		captureTimeMs = AgoraData.captureTimeMs;
		decodeTimeMs = AgoraData.decodeTimeMs;
		streamType = static_cast<EVIDEO_STREAM_TYPE>(AgoraData.streamType);
		presentationMs = AgoraData.presentationMs;
	}

	agora::rtc::EncodedVideoFrameInfo CreateAgoraData() const {
	
		agora::rtc::EncodedVideoFrameInfo AgoraData;
		AgoraData.uid = uid;
		AgoraData.codecType = (agora::rtc::VIDEO_CODEC_TYPE)codecType;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.framesPerSecond = framesPerSecond;
		AgoraData.frameType = (agora::rtc::VIDEO_FRAME_TYPE)frameType;
		AgoraData.rotation = rotation.GetRawValue();
		AgoraData.trackId = trackId;
		AgoraData.captureTimeMs = captureTimeMs;
		AgoraData.decodeTimeMs = decodeTimeMs;
		AgoraData.streamType = (agora::rtc::VIDEO_STREAM_TYPE)streamType;
		AgoraData.presentationMs = presentationMs;
		return AgoraData;

	}

	void FreeAgoraData(agora::rtc::EncodedVideoFrameInfo & AgoraData) const {
	}

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlaybackAudioFrameBeforeMixing, const FString, channelId, int64, uid, const FAudioFrame&, audioFrame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalAudioSpectrum, const FAudioSpectrumData&, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoteAudioSpectrum, const TArray<FUserAudioSpectrumInfo>, spectrums);
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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFaceInfo, FString, OutFaceInfo);

class IFaceInfoObserverClassWrapper : public agora::media::IFaceInfoObserver {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIFaceInfoObserver : public UObject, public IFaceInfoObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFaceInfo OnFaceInfo;

	virtual bool onFaceInfo(const char* outFaceInfo) override;
};