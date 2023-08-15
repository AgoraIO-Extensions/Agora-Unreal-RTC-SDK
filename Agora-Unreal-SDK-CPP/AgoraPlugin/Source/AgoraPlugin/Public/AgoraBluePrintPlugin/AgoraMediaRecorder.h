// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "URtcEngineProxyCompatibility.h"
#include "AgoraBluePrintPlugin/IMediaRecorderObserver.h"
#include "AgoraMediaRecorder.generated.h"
UENUM(BlueprintType)
enum class EMediaRecorderContainerFormat : uint8 {

	FORMAT_NULL = 0,
	FORMAT_MP4 = 1,
};

UENUM(BlueprintType)
enum class EMediaRecorderStreamType : uint8 {

	STREAM_TYPE_NULL = 0,

	STREAM_TYPE_AUDIO = 0x01,

	STREAM_TYPE_VIDEO = 0x02,

	STREAM_TYPE_BOTH = STREAM_TYPE_AUDIO | STREAM_TYPE_VIDEO,
};

USTRUCT(BlueprintType)
struct FMediaRecorderConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	FString storagePath;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	EMediaRecorderContainerFormat containerFormat = EMediaRecorderContainerFormat::FORMAT_MP4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	EMediaRecorderStreamType streamType = EMediaRecorderStreamType::STREAM_TYPE_BOTH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	int maxDurationMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|MediaRecorderConfiguration")
	int recorderInfoUpdateInterval;
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
	agora::rtc::IMediaRecorder* GetMediaRecorder() { return MediaRecorder;}
private:
	agora::rtc::IMediaRecorder* MediaRecorder;
};

