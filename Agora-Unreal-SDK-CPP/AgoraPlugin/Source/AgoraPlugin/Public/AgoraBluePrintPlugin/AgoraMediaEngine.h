//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/include/AgoraHeaderBase.h"
#include "AgoraBluePrintPlugin/IFrameObserver.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "AgoraMediaEngine.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_TRACK_TYPE :uint8 {

    AUDIO_TRACK_INVALID,

    AUDIO_TRACK_MIXABLE,

    AUDIO_TRACK_DIRECT,
};


USTRUCT(BlueprintType)
struct FENUMWRAP_AUDIO_TRACK_TYPE{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AUDIO_TRACK_TYPE")
	EENUMCUSTOM_AUDIO_TRACK_TYPE ValueWrapper = EENUMCUSTOM_AUDIO_TRACK_TYPE::AUDIO_TRACK_INVALID;
    

    AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_3_ENTRIES(
        FENUMWRAP_AUDIO_TRACK_TYPE,agora::rtc::AUDIO_TRACK_TYPE, EENUMCUSTOM_AUDIO_TRACK_TYPE, 
        AUDIO_TRACK_INVALID,
        AUDIO_TRACK_MIXABLE,
        AUDIO_TRACK_DIRECT)
};


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAgoraMediaEngine : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int RegisterAudioFrameObserver(UIAudioFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int RegisterVideoFrameObserver(UIVideoFrameObserver* observer);
	
    // Current Not Support
    // UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    // int registerVideoEncodedFrameObserver(UIVideoEncodedFrameObserver* observer);

 	UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int RegisterFaceInfoObserver(UIFaceInfoObserver* observer);

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int PushAudioFrame(const FAudioFrame & frame, int64 trackId = 0);

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int PullAudioFrame(const FAudioFrame& frame);

    // Current Not Support
    //UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    //int SetExternalVideoSource(
    //    bool enabled, bool useTexture, EEXTERNAL_VIDEO_SOURCE_TYPE sourceType = VIDEO_FRAME,
    //    const FSenderOptions & encodedVideoOption = FSenderOptions());


    // Current Not Support
    //UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    //int SetExternalAudioSource(bool enabled, int sampleRate, int channels, bool localPlayback = false, bool publish = true) __deprecated;

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int64 CreateCustomAudioTrack(FENUMWRAP_AUDIO_TRACK_TYPE trackType, const FAudioTrackConfig & config);

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int DestroyCustomAudioTrack(int64 trackId);

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int SetExternalAudioSink(bool enabled, int sampleRate, int channels);


    // Currently Not Support
    //UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    //int PushVideoFrame(FExternalVideoFrame* frame, unsigned int videoTrackId = 0);
    
     // Currently Not Support
    //UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    //int PushEncodedVideoImage(const unsigned char* imageBuffer, size_t length,
    //    const agora::rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo,
    //    unsigned int videoTrackId = 0);
    
    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int AddVideoFrameRenderer(UIVideoFrameObserver* renderer);

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    int RemoveVideoFrameRenderer(UIVideoFrameObserver* renderer);

    UFUNCTION(BlueprintCallable, Category = "Agora|IAgoraMediaEngine")
    void Release();

private:
	agora::media::IMediaEngine* MediaEngine;
};