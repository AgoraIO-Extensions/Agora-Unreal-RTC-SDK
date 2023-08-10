// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundWaveProcedural.h"
#include "AgoraPluginInterface.h"
#include "Misc/ScopeLock.h" 
#include "AgoraSoundWaveProcedural.generated.h"

/**
 * 
 */
UCLASS()
class UAgoraSoundWaveProcedural : public USoundWaveProcedural
{
	GENERATED_BODY()
	
public:
    UAgoraSoundWaveProcedural(const FObjectInitializer& ObjectInitializer):USoundWaveProcedural(ObjectInitializer){}

    virtual int32 OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples) override;

    virtual Audio::EAudioMixerStreamDataFormat::Type GetGeneratedPCMDataFormat() const override;

    void AddToFrames(agora::media::IAudioFrameObserverBase::AudioFrame& frames);
    
    void Init(TArray<uint8>& InData);

    void BeginDestroy() override;

private:

    TArray<agora::media::IAudioFrameObserverBase::AudioFrame> AudioFrames;

    int lastpos = 0;

    FCriticalSection CriticalSectionOfAudioFrames;
};
