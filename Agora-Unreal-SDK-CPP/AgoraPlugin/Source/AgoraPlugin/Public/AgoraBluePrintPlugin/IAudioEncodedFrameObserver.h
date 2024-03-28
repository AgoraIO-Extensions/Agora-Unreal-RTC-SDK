//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/include/AgoraHeaderBase.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "IAudioEncodedFrameObserver.generated.h"

USTRUCT(BlueprintType)
struct FPacket {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Packet")
	TArray<uint8> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Packet")
	int64 size = 0;

	FPacket(){}
	FPacket(const agora::rtc::IPacketObserver::Packet &packet) {
		size = packet.size;
		for (int i = 0; i < size; i++) {
			buffer.Add(packet.buffer[i]);
		}
	}

	agora::rtc::IPacketObserver::Packet CreateAgoraData() const {

		agora::rtc::IPacketObserver::Packet packet;
		packet.size = size;
		unsigned char* tempptr = new unsigned char[size];
		FMemory::Memcpy(tempptr, buffer.GetData(), size);
		packet.buffer = tempptr;
		return packet;
	
	}

	void FreeAgoraData(agora::rtc::IPacketObserver::Packet& AgoraData) const{
		if(AgoraData.buffer){
			delete[] AgoraData.buffer;
			AgoraData.buffer = nullptr;
		}
	}

};

UENUM(BlueprintType)
enum class EAUDIO_CODEC_TYPE : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	AUDIO_CODEC_OPUS = 1,

	AUDIO_CODEC_PCMA = 3,

	AUDIO_CODEC_PCMU = 4,

	AUDIO_CODEC_G722 = 5,

	AUDIO_CODEC_AACLC = 8,

	AUDIO_CODEC_HEAAC = 9,

	AUDIO_CODEC_JC1 = 10,

	AUDIO_CODEC_HEAAC2 = 11,

	AUDIO_CODEC_LPCNET = 12,
};


USTRUCT(BlueprintType)
struct FEncodedAudioFrameAdvancedSettings {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameAdvancedSettings")
	bool speech = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameAdvancedSettings")
	bool sendEvenIfEmpty = true;

	FEncodedAudioFrameAdvancedSettings(){}
	FEncodedAudioFrameAdvancedSettings(const agora::rtc::EncodedAudioFrameAdvancedSettings & AgoraData){
		speech = AgoraData.speech;
		sendEvenIfEmpty = AgoraData.sendEvenIfEmpty;
	}

	agora::rtc::EncodedAudioFrameAdvancedSettings CreateAgoraData() const {
		agora::rtc::EncodedAudioFrameAdvancedSettings AgoraData;
		AgoraData.speech = speech;
		AgoraData.sendEvenIfEmpty = sendEvenIfEmpty;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::EncodedAudioFrameAdvancedSettings& AgoraData) const {
		//Nothing to free
	}
};


USTRUCT(BlueprintType)
struct FEncodedAudioFrameInfo {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	EAUDIO_CODEC_TYPE codec = EAUDIO_CODEC_TYPE::AUDIO_CODEC_AACLC;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int sampleRateHz = 44100;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int samplesPerChannel = 441;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int numberOfChannels = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	FEncodedAudioFrameAdvancedSettings advancedSettings = FEncodedAudioFrameAdvancedSettings();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int64 captureTimeMs = 0;

	FEncodedAudioFrameInfo(){}
	FEncodedAudioFrameInfo(const agora::rtc::EncodedAudioFrameInfo & AgoraData){
		codec = static_cast<EAUDIO_CODEC_TYPE>(AgoraData.codec);
		sampleRateHz = AgoraData.sampleRateHz;
		samplesPerChannel = AgoraData.samplesPerChannel;
		numberOfChannels = AgoraData.numberOfChannels;
		advancedSettings = FEncodedAudioFrameAdvancedSettings(AgoraData.advancedSettings);
		captureTimeMs = AgoraData.captureTimeMs;
	}

	agora::rtc::EncodedAudioFrameInfo CreateAgoraData() const {
		agora::rtc::EncodedAudioFrameInfo AgoraData;
		AgoraData.codec = static_cast<agora::rtc::AUDIO_CODEC_TYPE>(codec);
		AgoraData.sampleRateHz = sampleRateHz;
		AgoraData.samplesPerChannel = samplesPerChannel;
		AgoraData.numberOfChannels = numberOfChannels;
		AgoraData.advancedSettings = advancedSettings.CreateAgoraData();
		AgoraData.captureTimeMs = captureTimeMs;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::EncodedAudioFrameInfo& AgoraData) const {
		advancedSettings.FreeAgoraData(AgoraData.advancedSettings);
	}
};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendAudioPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendVideoPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceiveAudioPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceiveVideoPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRecordAudioEncodedFrame, const TArray<int>, frameBuffer, int, length, const FEncodedAudioFrameInfo&, audioEncodedFrameInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlaybackAudioEncodedFrame, const TArray<int>, frameBuffer, int, length, const FEncodedAudioFrameInfo&, audioEncodedFrameInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMixedAudioEncodedFrame, const TArray<int>, frameBuffer, int, length, const FEncodedAudioFrameInfo&, audioEncodedFrameInfo);


class IPacketObserverClassWrapper : public agora::rtc::IPacketObserver {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIPacketObserver : public UObject, public IPacketObserverClassWrapper
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSendAudioPacket OnSendAudioPacket;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSendVideoPacket OnSendVideoPacket;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnReceiveAudioPacket OnReceiveAudioPacket;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnReceiveVideoPacket OnReceiveVideoPacket;

	bool onSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet) override;

	bool onSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet) override;

	bool onReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet) override;

	bool onReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet) override;

};


class IAudioEncodedFrameObserverClassWrapper : public agora::rtc::IAudioEncodedFrameObserver {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioEncodedFrameObserver : public UObject, public IAudioEncodedFrameObserverClassWrapper
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecordAudioEncodedFrame OnRecordAudioEncoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlaybackAudioEncodedFrame OnPlaybackAudioEncoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMixedAudioEncodedFrame OnMixedAudioEncoded;

	void onRecordAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo) override;

	void onPlaybackAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo) override;

	void onMixedAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo) override;

};

