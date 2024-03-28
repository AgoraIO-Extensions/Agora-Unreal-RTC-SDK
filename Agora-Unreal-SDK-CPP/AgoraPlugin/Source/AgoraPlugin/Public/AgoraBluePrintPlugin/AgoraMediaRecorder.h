//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "URtcEngineProxyCompatibility.h"
#include "AgoraBluePrintPlugin/IMediaRecorderObserver.h"
#include "AgoraMediaRecorder.generated.h"
UENUM(BlueprintType)
enum class EMediaRecorderContainerFormat : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	FORMAT_MP4 = 1,
};

UENUM(BlueprintType)
enum class EMediaRecorderStreamType : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	STREAM_TYPE_AUDIO = 0x01,

	STREAM_TYPE_VIDEO = 0x02,

	STREAM_TYPE_BOTH = STREAM_TYPE_AUDIO | STREAM_TYPE_VIDEO,
};

USTRUCT(BlueprintType)
struct FMediaRecorderConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	FString storagePath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	EMediaRecorderContainerFormat containerFormat = EMediaRecorderContainerFormat::FORMAT_MP4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	EMediaRecorderStreamType streamType = EMediaRecorderStreamType::STREAM_TYPE_BOTH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	int maxDurationMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	int recorderInfoUpdateInterval = 0;

	FMediaRecorderConfiguration() {}
	FMediaRecorderConfiguration(const agora::media::MediaRecorderConfiguration & AgoraData){
		
		storagePath = UTF8_TO_TCHAR(AgoraData.storagePath);
		containerFormat = static_cast<EMediaRecorderContainerFormat>(AgoraData.containerFormat);
		streamType = static_cast<EMediaRecorderStreamType>(AgoraData.streamType);
		maxDurationMs = AgoraData.maxDurationMs;
		recorderInfoUpdateInterval = AgoraData.recorderInfoUpdateInterval;

	}

	agora::media::MediaRecorderConfiguration CreateAgoraData() const{
		
		agora::media::MediaRecorderConfiguration AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.storagePath, storagePath)
		AgoraData.containerFormat = static_cast<agora::media::MediaRecorderContainerFormat>(containerFormat);
		AgoraData.streamType = static_cast<agora::media::MediaRecorderStreamType>(streamType);
		AgoraData.maxDurationMs = maxDurationMs;
		AgoraData.recorderInfoUpdateInterval = recorderInfoUpdateInterval;
		return AgoraData;
	}

	void FreeAgoraData(agora::media::MediaRecorderConfiguration &AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.storagePath)
	}
};
/**
 *
 */
UCLASS(Blueprintable)
class AGORAPLUGIN_API UIMediaRecorder : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaRecorder")
	int SetMediaRecorderObserver(UIMediaRecorderObserver* callback);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaRecorder")
	int StartRecording(FMediaRecorderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IMediaRecorder")
	int StopRecording();
	void SetMediaRecorder(agora::rtc::IMediaRecorder* mediaRecorder);
	agora::rtc::IMediaRecorder* GetMediaRecorder() { return MediaRecorder; }
private:
	agora::rtc::IMediaRecorder* MediaRecorder;
};

