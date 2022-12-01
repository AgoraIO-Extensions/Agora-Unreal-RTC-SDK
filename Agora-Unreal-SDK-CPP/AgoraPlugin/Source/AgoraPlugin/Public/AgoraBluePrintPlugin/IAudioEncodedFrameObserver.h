// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "IAudioEncodedFrameObserver.generated.h"

USTRUCT(BlueprintType)
struct FPacket {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Packet")
	TArray<int64> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Packet")
	int64 size;
};

UENUM(BlueprintType)
enum class EAUDIO_CODEC_TYPE : uint8 {

	AUDIO_CODEC_NULL = 0,

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameAdvancedSettings")
	bool speech =true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameAdvancedSettings")
	bool sendEvenIfEmpty = true;
};


USTRUCT(BlueprintType)
struct FEncodedAudioFrameInfo {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	EAUDIO_CODEC_TYPE codec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int sampleRateHz;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int samplesPerChannel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int numberOfChannels;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	FEncodedAudioFrameAdvancedSettings advancedSettings;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncodedAudioFrameInfo")
	int64 captureTimeMs;
};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendAudioPacket,const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendVideoPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceiveAudioPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceiveVideoPacket, const FPacket&, packet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRecordAudioEncodedFrame, const TArray<int64>, frameBuffer, int, length, const FEncodedAudioFrameInfo&, audioEncodedFrameInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlaybackAudioEncodedFrame, const TArray<int64>, frameBuffer, int, length, const FEncodedAudioFrameInfo&, audioEncodedFrameInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMixedAudioEncodedFrame, const TArray<int64>, frameBuffer, int, length, const FEncodedAudioFrameInfo&, audioEncodedFrameInfo);


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIPacketObserver : public UObject, public agora::rtc::IPacketObserver
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


UCLASS(Blueprintable)
class AGORAPLUGIN_API UIAudioEncodedFrameObserver : public UObject, public agora::rtc::IAudioEncodedFrameObserver
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecordAudioEncodedFrame OnRecordAudioEncoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPlaybackAudioEncodedFrame OnPlaybackAudioEncoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMixedAudioEncodedFrame OnMixedAudioEncoded;

	void OnRecordAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo) override;

	void OnPlaybackAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo) override;

	void OnMixedAudioEncodedFrame(const uint8_t* frameBuffer, int length, const agora::rtc::EncodedAudioFrameInfo& audioEncodedFrameInfo) override;

};

