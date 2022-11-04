// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraSoundWaveProcedural.h"

UAgoraSoundWaveProcedural::UAgoraSoundWaveProcedural(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

int32 UAgoraSoundWaveProcedural::OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples)
{
	agora::media::IAudioFrameObserverBase::AudioFrame frame;

	if (AudioFrames.Num() > 0)
	{
		frame = AudioFrames[0];
	}
	else
	{
		OutAudio.Reset();

		OutAudio.AddZeroed(NumSamples * sizeof(int16_t));

		return NumSamples;
	}

	OutAudio.Reset();

	OutAudio.AddZeroed(frame.bytesPerSample * frame.samplesPerChannel * frame.channels);

	int16_t* OutAudioBuffer = (int16_t*)OutAudio.GetData();

	FMemory::Memcpy(OutAudioBuffer, frame.buffer, frame.bytesPerSample * frame.samplesPerChannel * frame.channels);

	FMemory::Free(AudioFrames[0].buffer);

	AudioFrames.RemoveAt(0, 1, true);

	return frame.samplesPerChannel * frame.channels;
}

Audio::EAudioMixerStreamDataFormat::Type UAgoraSoundWaveProcedural::GetGeneratedPCMDataFormat() const
{
	return Super::GetGeneratedPCMDataFormat();
}


void UAgoraSoundWaveProcedural::AddToFrames(agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{
	agora::media::IAudioFrameObserverBase::AudioFrame frame;
	frame.type = audioFrame.type;
	frame.samplesPerChannel = audioFrame.samplesPerChannel;
	frame.bytesPerSample = audioFrame.bytesPerSample;
	frame.channels = audioFrame.channels;
	frame.samplesPerSec = audioFrame.samplesPerSec; 
	frame.renderTimeMs = audioFrame.renderTimeMs;
	frame.avsync_type = audioFrame.avsync_type;
	frame.buffer = FMemory::Malloc(audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels);
	FMemory::Memcpy(frame.buffer, audioFrame.buffer, audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels);
	AudioFrames.Add(frame);
}

void UAgoraSoundWaveProcedural::BeginDestroy()
{
	Super::BeginDestroy();
	for (int i = 0; i < AudioFrames.Num(); i++)
	{
		FMemory::Free(AudioFrames[i].buffer);
	}
}
