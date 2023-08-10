// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraSoundWaveProceduralFromFile.h"

int32 UAgoraSoundWaveProceduralFromFile::OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples)
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

Audio::EAudioMixerStreamDataFormat::Type UAgoraSoundWaveProceduralFromFile::GetGeneratedPCMDataFormat() const
{
	return Audio::EAudioMixerStreamDataFormat::Int16;
}


void UAgoraSoundWaveProceduralFromFile::AddToFrames(agora::media::IAudioFrameObserverBase::AudioFrame& audioFrame)
{

	FScopeLock Lock(&CriticalSectionOfAudioFrames);

	agora::media::IAudioFrameObserverBase::AudioFrame frame;
	frame.type = audioFrame.type;
	frame.samplesPerChannel = 512;
	frame.bytesPerSample = agora::rtc::BYTES_PER_SAMPLE::TWO_BYTES_PER_SAMPLE;
	frame.channels = 2;
	frame.samplesPerSec = 44100;
	frame.renderTimeMs = audioFrame.renderTimeMs;
	frame.avsync_type = audioFrame.avsync_type;


	int ByteSize = frame.bytesPerSample * audioFrame.samplesPerChannel * audioFrame.channels;

	auto InAudioBuffer = FileData.GetData();

	frame.buffer = FMemory::Malloc(ByteSize);

	FMemory::Memcpy(frame.buffer, &InAudioBuffer[lastpos], ByteSize);

	lastpos += ByteSize;


	// Add to the array
	AudioFrames.Add(frame);
}

void UAgoraSoundWaveProceduralFromFile::Init(TArray<uint8>& InData)
{
	FileData = InData;
	lastpos = 0;
}

void UAgoraSoundWaveProceduralFromFile::Init(FString Path)
{
	FFileHelper::LoadFileToArray(FileData, *Path, 0);
}

void UAgoraSoundWaveProceduralFromFile::BeginDestroy()
{
	FScopeLock Lock(&CriticalSectionOfAudioFrames);
	Super::BeginDestroy();
	for (int i = 0; i < AudioFrames.Num(); i++)
	{
		FMemory::Free(AudioFrames[i].buffer);
	}
	AudioFrames.Empty();
}
