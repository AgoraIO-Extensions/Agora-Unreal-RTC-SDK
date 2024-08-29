// Copyright(c) 2024 Agora.io. All rights reserved.


#include "AgoraSoundWaveProcedural.h"

int32 UAgoraSoundWaveProcedural::OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples)
{
	FScopeLock Lock(&CriticalSectionOfAudioFrames);

	agora::media::IAudioFrameObserverBase::AudioFrame frame;

	// get one frame
	if (AudioFrames.Num() > 0)
	{
		frame = AudioFrames[0];
	}
	else
	{
		// fail to get one frame

		OutAudio.Reset();

		OutAudio.AddZeroed(NumSamples * sizeof(int16_t));

		return NumSamples;
	}


	// Copy Data to OutAudio
	int ByteSize = frame.bytesPerSample * frame.samplesPerChannel * frame.channels;

	OutAudio.Reset();

	OutAudio.AddZeroed(ByteSize);

	auto OutAudioBuffer = OutAudio.GetData();

	FMemory::Memcpy(OutAudioBuffer, frame.buffer, ByteSize);

	// Remove the frame which has been consumed
	FMemory::Free(AudioFrames[0].buffer);

	AudioFrames.RemoveAt(0, 1, true);

	return frame.samplesPerChannel * frame.channels;
}

Audio::EAudioMixerStreamDataFormat::Type UAgoraSoundWaveProcedural::GetGeneratedPCMDataFormat() const
{
	return Audio::EAudioMixerStreamDataFormat::Int16;
}


void UAgoraSoundWaveProcedural::AddToFrames(agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{

	FScopeLock Lock(&CriticalSectionOfAudioFrames);
	//Make a Copy
	agora::media::IAudioFrameObserverBase::AudioFrame frame;
	frame.type = audioFrame.type;
	frame.samplesPerChannel = audioFrame.samplesPerChannel;
	frame.bytesPerSample = audioFrame.bytesPerSample;
	frame.channels = audioFrame.channels;
	frame.samplesPerSec = audioFrame.samplesPerSec;
	frame.renderTimeMs = audioFrame.renderTimeMs;
	frame.avsync_type = audioFrame.avsync_type;
	int ByteSize = audioFrame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels;
	frame.buffer = FMemory::Malloc(ByteSize);
	FMemory::Memcpy(frame.buffer, audioFrame.buffer, ByteSize);

	AudioFrames.Add(frame);
}

void UAgoraSoundWaveProcedural::Init(TArray<uint8>& InData)
{
	lastpos = 0;
}

void UAgoraSoundWaveProcedural::BeginDestroy()
{
	FScopeLock Lock(&CriticalSectionOfAudioFrames);
	Super::BeginDestroy();
	for (int i = 0; i < AudioFrames.Num(); i++)
	{
		FMemory::Free(AudioFrames[i].buffer);
	}
	AudioFrames.Empty();
}
