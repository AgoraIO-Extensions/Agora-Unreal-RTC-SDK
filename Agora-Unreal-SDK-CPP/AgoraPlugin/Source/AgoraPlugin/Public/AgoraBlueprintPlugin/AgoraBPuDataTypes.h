// Copyright(c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "UtilityUEEnumAgoraConvertMacro.h"
#include "UtilityUABTTypeHelper.h"
#include "UtilityAgoraBPuLogger.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"

#include "AgoraBPuDataTypesBase.h"

#include "AgoraBPuDataTypes.generated.h"

using UABT = agora::rtc::ue::UABT;

using UABTEnum = agora::rtc::ue::UABTEnum;

#pragma region Custom Defined

UENUM()
enum class EAgoraBPuEventHandlerType : uint8
{
	None UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	EventHandler = 1,
	EventHandlerEx = 2
};

#pragma endregion Custom Defined


#pragma region EventHandler


USTRUCT(BlueprintType)
struct FUABT_LastmileProbeOneWayResult {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult")
	int64 packetLossRate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult")
	int64 jitter = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult")
	int64 availableBandwidth = 0;

	FUABT_LastmileProbeOneWayResult(){}
	FUABT_LastmileProbeOneWayResult(const agora::rtc::LastmileProbeOneWayResult & AgoraData){
		packetLossRate = AgoraData.packetLossRate;
		jitter = AgoraData.jitter;
		availableBandwidth = AgoraData.availableBandwidth;
	}

	agora::rtc::LastmileProbeOneWayResult CreateAgoraData() const {
		agora::rtc::LastmileProbeOneWayResult AgoraData;
		AgoraData.packetLossRate = packetLossRate;
		AgoraData.jitter = jitter;
		AgoraData.availableBandwidth = availableBandwidth;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LastmileProbeOneWayResult & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_AudioVolumeInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	int64 volume = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	int64 vad = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	float voicePitch = 0;

	FUABT_AudioVolumeInfo(){}
	FUABT_AudioVolumeInfo(const agora::rtc::AudioVolumeInfo & AgoraData){
		uid = AgoraData.uid;
		volume = AgoraData.volume;
		vad = AgoraData.vad;
		voicePitch = AgoraData.voicePitch;
	}

	agora::rtc::AudioVolumeInfo CreateAgoraData() const {
		agora::rtc::AudioVolumeInfo AgoraData;
		AgoraData.uid = uid;
		AgoraData.volume = volume;
		AgoraData.vad = vad;
		AgoraData.voicePitch = voicePitch;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AudioVolumeInfo & AgoraData) const {

	}


};


USTRUCT(BlueprintType)
struct FUABT_LastmileProbeResult {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	EUABT_LASTMILE_PROBE_RESULT_STATE state = EUABT_LASTMILE_PROBE_RESULT_STATE::LASTMILE_PROBE_RESULT_UNAVAILABLE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	FUABT_LastmileProbeOneWayResult uplinkReport = FUABT_LastmileProbeOneWayResult();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	FUABT_LastmileProbeOneWayResult downlinkReport = FUABT_LastmileProbeOneWayResult();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	int64 rtt = 0;

	FUABT_LastmileProbeResult(){}
	FUABT_LastmileProbeResult(const agora::rtc::LastmileProbeResult & AgoraData){
		state = static_cast<EUABT_LASTMILE_PROBE_RESULT_STATE>(AgoraData.state);
		uplinkReport = FUABT_LastmileProbeOneWayResult(AgoraData.uplinkReport);
		downlinkReport = FUABT_LastmileProbeOneWayResult(AgoraData.downlinkReport);
		rtt = AgoraData.rtt;
	}

	agora::rtc::LastmileProbeResult CreateAgoraData() const {
		agora::rtc::LastmileProbeResult AgoraData;
		AgoraData.state = static_cast<agora::rtc::LASTMILE_PROBE_RESULT_STATE>(state);
		AgoraData.uplinkReport = uplinkReport.CreateAgoraData();
		AgoraData.downlinkReport = downlinkReport.CreateAgoraData();
		AgoraData.rtt = rtt;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LastmileProbeResult & AgoraData) const {
		uplinkReport.FreeAgoraData(AgoraData.uplinkReport);
		downlinkReport.FreeAgoraData(AgoraData.downlinkReport);
	}
};




USTRUCT(BlueprintType)
struct FUABT_RtcStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 duration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 txBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 rxBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 txAudioBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 txVideoBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 rxAudioBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 rxVideoBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxAudioKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txAudioKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxVideoKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txVideoKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 lastmileDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 userCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	FString cpuAppUsage = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	FString cpuTotalUsage = "0";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 gatewayRtt = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	FString memoryAppUsageRatio = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	FString memoryTotalUsageRatio = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 memoryAppUsageInKbytes = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 connectTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstAudioPacketDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoPacketDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFramePacketDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 packetsBeforeFirstKeyFramePacket = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstAudioPacketDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoPacketDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFramePacketDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFrameDecodedDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFrameRenderedDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txPacketLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxPacketLossRate = 0;



	FUABT_RtcStats(){}
	FUABT_RtcStats(const agora::rtc::RtcStats & AgoraData){
		duration = AgoraData.duration;
		txBytes = AgoraData.txBytes;
		rxBytes = AgoraData.rxBytes;
		txAudioBytes = AgoraData.txAudioBytes;
		txVideoBytes = AgoraData.txVideoBytes;
		rxAudioBytes = AgoraData.rxAudioBytes;
		rxVideoBytes = AgoraData.rxVideoBytes;
		txKBitRate = AgoraData.txKBitRate;
		rxKBitRate = AgoraData.rxKBitRate;
		rxAudioKBitRate = AgoraData.rxAudioKBitRate;
		txAudioKBitRate = AgoraData.txAudioKBitRate;
		rxVideoKBitRate = AgoraData.rxVideoKBitRate;
		txVideoKBitRate = AgoraData.txVideoKBitRate;
		lastmileDelay = AgoraData.lastmileDelay;
		userCount = AgoraData.userCount;

		this->cpuAppUsage = UABT::FromDouble(AgoraData.cpuAppUsage);
		this->cpuTotalUsage = UABT::FromDouble(AgoraData.cpuTotalUsage);

		gatewayRtt = AgoraData.gatewayRtt;
		
		this->memoryAppUsageRatio = UABT::FromDouble(AgoraData.memoryAppUsageRatio);
		this->memoryTotalUsageRatio = UABT::FromDouble(AgoraData.memoryTotalUsageRatio);
		
		memoryAppUsageInKbytes = AgoraData.memoryAppUsageInKbytes;
		connectTimeMs = AgoraData.connectTimeMs;
		firstAudioPacketDuration = AgoraData.firstAudioPacketDuration;
		firstVideoPacketDuration = AgoraData.firstVideoPacketDuration;
		firstVideoKeyFramePacketDuration = AgoraData.firstVideoKeyFramePacketDuration;
		packetsBeforeFirstKeyFramePacket = AgoraData.packetsBeforeFirstKeyFramePacket;
		firstAudioPacketDurationAfterUnmute = AgoraData.firstAudioPacketDurationAfterUnmute;
		firstVideoPacketDurationAfterUnmute = AgoraData.firstVideoPacketDurationAfterUnmute;
		firstVideoKeyFramePacketDurationAfterUnmute = AgoraData.firstVideoKeyFramePacketDurationAfterUnmute;
		firstVideoKeyFrameDecodedDurationAfterUnmute = AgoraData.firstVideoKeyFrameDecodedDurationAfterUnmute;
		firstVideoKeyFrameRenderedDurationAfterUnmute = AgoraData.firstVideoKeyFrameRenderedDurationAfterUnmute;
		txPacketLossRate = AgoraData.txPacketLossRate;
		rxPacketLossRate = AgoraData.rxPacketLossRate;
	}


	agora::rtc::RtcStats CreateAgoraData(){
	
		agora::rtc::RtcStats AgoraData;
		AgoraData.duration = duration;
		AgoraData.txBytes = txBytes;
		AgoraData.rxBytes = rxBytes;
		AgoraData.txAudioBytes = txAudioBytes;
		AgoraData.txVideoBytes = txVideoBytes;
		AgoraData.rxAudioBytes = rxAudioBytes;
		AgoraData.rxVideoBytes = rxVideoBytes;
		AgoraData.txKBitRate = txKBitRate;
		AgoraData.rxKBitRate = rxKBitRate;
		AgoraData.rxAudioKBitRate = rxAudioKBitRate;
		AgoraData.txAudioKBitRate = txAudioKBitRate;
		AgoraData.rxVideoKBitRate = rxVideoKBitRate;
		AgoraData.txVideoKBitRate = txVideoKBitRate;
		AgoraData.lastmileDelay = lastmileDelay;
		AgoraData.userCount = userCount;

		AgoraData.cpuAppUsage = UABT::ToDouble(this->cpuAppUsage);
		AgoraData.cpuTotalUsage = UABT::ToDouble(this->cpuTotalUsage);

		AgoraData.gatewayRtt = gatewayRtt;

		AgoraData.memoryAppUsageRatio = UABT::ToDouble(this->memoryAppUsageRatio);
		AgoraData.memoryTotalUsageRatio = UABT::ToDouble(this->memoryTotalUsageRatio);

		AgoraData.memoryAppUsageInKbytes = memoryAppUsageInKbytes;
		AgoraData.connectTimeMs = connectTimeMs;
		AgoraData.firstAudioPacketDuration = firstAudioPacketDuration;
		AgoraData.firstVideoPacketDuration = firstVideoPacketDuration;
		AgoraData.firstVideoKeyFramePacketDuration = firstVideoKeyFramePacketDuration;
		AgoraData.packetsBeforeFirstKeyFramePacket = packetsBeforeFirstKeyFramePacket;
		AgoraData.firstAudioPacketDurationAfterUnmute = firstAudioPacketDurationAfterUnmute;
		AgoraData.firstVideoPacketDurationAfterUnmute = firstVideoPacketDurationAfterUnmute;
		AgoraData.firstVideoKeyFramePacketDurationAfterUnmute = firstVideoKeyFramePacketDurationAfterUnmute;
		AgoraData.firstVideoKeyFrameDecodedDurationAfterUnmute = firstVideoKeyFrameDecodedDurationAfterUnmute;
		AgoraData.firstVideoKeyFrameRenderedDurationAfterUnmute = firstVideoKeyFrameRenderedDurationAfterUnmute;
		AgoraData.txPacketLossRate = txPacketLossRate;
		AgoraData.rxPacketLossRate = rxPacketLossRate;

		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::RtcStats & AgoraData) const {
	}
};



USTRUCT(BlueprintType)
struct FUABT_UplinkNetworkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UplinkNetworkInfo")
	int video_encoder_target_bitrate_bps = 0;

	FUABT_UplinkNetworkInfo(){}
	FUABT_UplinkNetworkInfo(const agora::rtc::UplinkNetworkInfo & AgoraData){
		video_encoder_target_bitrate_bps = AgoraData.video_encoder_target_bitrate_bps;
	}

	agora::rtc::UplinkNetworkInfo CreateAgoraData() const {
		agora::rtc::UplinkNetworkInfo AgoraData;
		AgoraData.video_encoder_target_bitrate_bps = video_encoder_target_bitrate_bps;
		return AgoraData;
	}
	void FreeAgoraData(agora::rtc::UplinkNetworkInfo & AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_PeerDownlinkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	FString userId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	EUABT_VIDEO_STREAM_TYPE stream_type = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL current_downscale_level = EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL::REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	int expected_bitrate_bps = 0;

	FUABT_PeerDownlinkInfo(){}
	FUABT_PeerDownlinkInfo(const agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo & AgoraData){
		userId = UTF8_TO_TCHAR(AgoraData.userId);
		stream_type = static_cast<EUABT_VIDEO_STREAM_TYPE>(AgoraData.stream_type);
		current_downscale_level = static_cast<EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL>(AgoraData.current_downscale_level);
		expected_bitrate_bps = AgoraData.expected_bitrate_bps;
	}

	agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo CreateAgoraData() const {
		agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo AgoraData;
		AgoraData.userId = UABT::New_CharPtr(this->userId);
		AgoraData.stream_type = static_cast<agora::rtc::VIDEO_STREAM_TYPE>(stream_type);
		AgoraData.current_downscale_level = static_cast<agora::rtc::REMOTE_VIDEO_DOWNSCALE_LEVEL>(current_downscale_level);
		AgoraData.expected_bitrate_bps = expected_bitrate_bps;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.userId);
	}
};


USTRUCT(BlueprintType)
struct FUABT_DownlinkNetworkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int lastmile_buffer_delay_time_ms = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int bandwidth_estimation_bps = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int total_downscale_level_count = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	TArray<FUABT_PeerDownlinkInfo> peer_downlink_info;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int total_received_video_count = -1;

	FUABT_DownlinkNetworkInfo(){}
	FUABT_DownlinkNetworkInfo(const agora::rtc::DownlinkNetworkInfo & AgoraData){
		lastmile_buffer_delay_time_ms = AgoraData.lastmile_buffer_delay_time_ms;
		bandwidth_estimation_bps = AgoraData.bandwidth_estimation_bps;
		total_downscale_level_count = AgoraData.total_downscale_level_count;
		for (int i = 0; i < total_received_video_count; ++i) {
			peer_downlink_info.Add(FUABT_PeerDownlinkInfo(AgoraData.peer_downlink_info[i]));
		}
		total_received_video_count = AgoraData.total_received_video_count;
	}

	agora::rtc::DownlinkNetworkInfo CreateAgoraData() const {
		agora::rtc::DownlinkNetworkInfo AgoraData;
		AgoraData.lastmile_buffer_delay_time_ms = lastmile_buffer_delay_time_ms;
		AgoraData.bandwidth_estimation_bps = bandwidth_estimation_bps;
		AgoraData.total_downscale_level_count = total_downscale_level_count;
		AgoraData.total_received_video_count = total_received_video_count;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.peer_downlink_info, agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo, total_received_video_count, this->peer_downlink_info)
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::DownlinkNetworkInfo & AgoraData) const {
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.peer_downlink_info, total_received_video_count, FUABT_PeerDownlinkInfo)
	}
};


USTRUCT(BlueprintType)
struct FUABT_LocalAudioStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int numChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int sentSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int sentBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int internalCodec = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int txPacketLossRate = 0; // unsigned short 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int audioDeviceDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int audioPlayoutDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int earMonitorDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int aecEstimatedDelay = 0;

	FUABT_LocalAudioStats(){}
	FUABT_LocalAudioStats(const agora::rtc::LocalAudioStats & AgoraData){
		numChannels = AgoraData.numChannels;
		sentSampleRate = AgoraData.sentSampleRate;
		sentBitrate = AgoraData.sentBitrate;
		internalCodec = AgoraData.internalCodec;
		txPacketLossRate = AgoraData.txPacketLossRate;
		audioDeviceDelay = AgoraData.audioDeviceDelay;
		audioPlayoutDelay = AgoraData.audioPlayoutDelay;
		earMonitorDelay = AgoraData.earMonitorDelay;
		aecEstimatedDelay = AgoraData.aecEstimatedDelay;
	}

	agora::rtc::LocalAudioStats CreateAgoraData() const {
		agora::rtc::LocalAudioStats AgoraData;
		AgoraData.numChannels = numChannels;
		AgoraData.sentSampleRate = sentSampleRate;
		AgoraData.sentBitrate = sentBitrate;
		AgoraData.internalCodec = internalCodec;
		AgoraData.txPacketLossRate = txPacketLossRate;
		AgoraData.audioDeviceDelay = audioDeviceDelay;
		AgoraData.audioPlayoutDelay = audioPlayoutDelay;
		AgoraData.earMonitorDelay = earMonitorDelay;
		AgoraData.aecEstimatedDelay = aecEstimatedDelay;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LocalAudioStats & AgoraData) const {

	}
};



USTRUCT(BlueprintType)
struct FUABT_RemoteAudioStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int quality = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int networkTransportDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int jitterBufferDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int audioLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int numChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int receivedSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int receivedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int totalFrozenTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int frozenRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int mosValue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int64 frozenRateByCustomPlcCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int64 plcCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int totalActiveTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int publishDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int qoeQuality = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int qualityChangedReason = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int64 rxAudioBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int e2eDelay = 0;

	FUABT_RemoteAudioStats(){}
	FUABT_RemoteAudioStats(const agora::rtc::RemoteAudioStats & AgoraData){
		uid = AgoraData.uid;
		quality = AgoraData.quality;
		networkTransportDelay = AgoraData.networkTransportDelay;
		jitterBufferDelay = AgoraData.jitterBufferDelay;
		audioLossRate = AgoraData.audioLossRate;
		numChannels = AgoraData.numChannels;
		receivedSampleRate = AgoraData.receivedSampleRate;
		receivedBitrate = AgoraData.receivedBitrate;
		totalFrozenTime = AgoraData.totalFrozenTime;
		frozenRate = AgoraData.frozenRate;
		mosValue = AgoraData.mosValue;
		frozenRateByCustomPlcCount = AgoraData.frozenRateByCustomPlcCount;
		plcCount = AgoraData.plcCount;
		totalActiveTime = AgoraData.totalActiveTime;
		publishDuration = AgoraData.publishDuration;
		qoeQuality = AgoraData.qoeQuality;
		qualityChangedReason = AgoraData.qualityChangedReason;
		rxAudioBytes = AgoraData.rxAudioBytes;
		e2eDelay = AgoraData.e2eDelay;
	}

	agora::rtc::RemoteAudioStats CreateAgoraData() const {
		agora::rtc::RemoteAudioStats AgoraData;
		AgoraData.uid = uid;
		AgoraData.quality = quality;
		AgoraData.networkTransportDelay = networkTransportDelay;
		AgoraData.jitterBufferDelay = jitterBufferDelay;
		AgoraData.audioLossRate = audioLossRate;
		AgoraData.numChannels = numChannels;
		AgoraData.receivedSampleRate = receivedSampleRate;
		AgoraData.receivedBitrate = receivedBitrate;
		AgoraData.totalFrozenTime = totalFrozenTime;
		AgoraData.frozenRate = frozenRate;
		AgoraData.mosValue = mosValue;
		AgoraData.frozenRateByCustomPlcCount = frozenRateByCustomPlcCount;
		AgoraData.plcCount = plcCount;
		AgoraData.totalActiveTime = totalActiveTime;
		AgoraData.publishDuration = publishDuration;
		AgoraData.qoeQuality = qoeQuality;
		AgoraData.qualityChangedReason = qualityChangedReason;
		AgoraData.rxAudioBytes = rxAudioBytes;
		AgoraData.e2eDelay = e2eDelay;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::RemoteAudioStats & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_LocalVideoStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int sentBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int sentFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int captureFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int captureFrameWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int captureFrameHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int regulatedCaptureFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int regulatedCaptureFrameWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int regulatedCaptureFrameHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encoderOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int rendererOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int targetBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int targetFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	EUABT_QUALITY_ADAPT_INDICATION qualityAdaptIndication = EUABT_QUALITY_ADAPT_INDICATION::ADAPT_NONE;
	int encodedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int txPacketLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE  captureBrightnessLevel = EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	bool dualStreamEnabled = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int hwEncoderAccelerating = 0;


	FUABT_LocalVideoStats(){}
	FUABT_LocalVideoStats(const agora::rtc::LocalVideoStats & AgoraData){
		uid = AgoraData.uid;
		sentBitrate = AgoraData.sentBitrate;
		sentFrameRate = AgoraData.sentFrameRate;
		captureFrameRate = AgoraData.captureFrameRate;
		captureFrameWidth = AgoraData.captureFrameWidth;
		captureFrameHeight = AgoraData.captureFrameHeight;
		regulatedCaptureFrameRate = AgoraData.regulatedCaptureFrameRate;
		regulatedCaptureFrameWidth = AgoraData.regulatedCaptureFrameWidth;
		regulatedCaptureFrameHeight = AgoraData.regulatedCaptureFrameHeight;
		encoderOutputFrameRate = AgoraData.encoderOutputFrameRate;
		encodedFrameWidth = AgoraData.encodedFrameWidth;
		encodedFrameHeight = AgoraData.encodedFrameHeight;
		rendererOutputFrameRate = AgoraData.rendererOutputFrameRate;
		targetBitrate = AgoraData.targetBitrate;
		targetFrameRate = AgoraData.targetFrameRate;
		qualityAdaptIndication = static_cast<EUABT_QUALITY_ADAPT_INDICATION>(AgoraData.qualityAdaptIndication);
		encodedBitrate = AgoraData.encodedBitrate;
		encodedFrameCount = AgoraData.encodedFrameCount;
		codecType = static_cast<EUABT_VIDEO_CODEC_TYPE>(AgoraData.codecType);
		txPacketLossRate = AgoraData.txPacketLossRate;
		captureBrightnessLevel = EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE(AgoraData.captureBrightnessLevel);
		dualStreamEnabled = AgoraData.dualStreamEnabled;
		hwEncoderAccelerating = AgoraData.hwEncoderAccelerating;
	}

	agora::rtc::LocalVideoStats CreateAgoraData() const {
		agora::rtc::LocalVideoStats AgoraData;
		AgoraData.uid = uid;
		AgoraData.sentBitrate = sentBitrate;
		AgoraData.sentFrameRate = sentFrameRate;
		AgoraData.captureFrameRate = captureFrameRate;
		AgoraData.captureFrameWidth = captureFrameWidth;
		AgoraData.captureFrameHeight = captureFrameHeight;
		AgoraData.regulatedCaptureFrameRate = regulatedCaptureFrameRate;
		AgoraData.regulatedCaptureFrameWidth = regulatedCaptureFrameWidth;
		AgoraData.regulatedCaptureFrameHeight = regulatedCaptureFrameHeight;
		AgoraData.encoderOutputFrameRate = encoderOutputFrameRate;
		AgoraData.encodedFrameWidth = encodedFrameWidth;
		AgoraData.encodedFrameHeight = encodedFrameHeight;
		AgoraData.rendererOutputFrameRate = rendererOutputFrameRate;
		AgoraData.targetBitrate = targetBitrate;
		AgoraData.targetFrameRate = targetFrameRate;
		AgoraData.qualityAdaptIndication = static_cast<agora::rtc::QUALITY_ADAPT_INDICATION>(qualityAdaptIndication);
		AgoraData.encodedBitrate = encodedBitrate;
		AgoraData.encodedFrameCount = encodedFrameCount;
		AgoraData.codecType = static_cast<agora::rtc::VIDEO_CODEC_TYPE>(codecType);
		AgoraData.txPacketLossRate = txPacketLossRate;
		AgoraData.captureBrightnessLevel = UABTEnum::ToRawValue(captureBrightnessLevel);
		AgoraData.dualStreamEnabled = dualStreamEnabled;
		AgoraData.hwEncoderAccelerating = hwEncoderAccelerating;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LocalVideoStats & AgoraData) const
	{

	}
};



USTRUCT(BlueprintType)
struct FUABT_RemoteVideoStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int delay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int e2eDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int receivedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int decoderOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int rendererOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int frameLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int packetLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	EUABT_VIDEO_STREAM_TYPE rxStreamType = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int totalFrozenTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int frozenRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int avSyncTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int totalActiveTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int publishDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int mosValue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int64 rxVideoBytes = 0;


	FUABT_RemoteVideoStats(){}
	FUABT_RemoteVideoStats(const agora::rtc::RemoteVideoStats & AgoraData){
		uid = AgoraData.uid;
		delay = AgoraData.delay;
		e2eDelay = AgoraData.e2eDelay;
		width = AgoraData.width;
		height = AgoraData.height;
		receivedBitrate = AgoraData.receivedBitrate;
		decoderOutputFrameRate = AgoraData.decoderOutputFrameRate;
		rendererOutputFrameRate = AgoraData.rendererOutputFrameRate;
		frameLossRate = AgoraData.frameLossRate;
		packetLossRate = AgoraData.packetLossRate;
		rxStreamType = static_cast<EUABT_VIDEO_STREAM_TYPE>(AgoraData.rxStreamType);
		totalFrozenTime = AgoraData.totalFrozenTime;
		frozenRate = AgoraData.frozenRate;
		avSyncTimeMs = AgoraData.avSyncTimeMs;
		totalActiveTime = AgoraData.totalActiveTime;
		publishDuration = AgoraData.publishDuration;
		mosValue = AgoraData.mosValue;
		rxVideoBytes = AgoraData.rxVideoBytes;
	}

	agora::rtc::RemoteVideoStats CreateAgoraData() const {
		agora::rtc::RemoteVideoStats AgoraData;
		AgoraData.uid = uid;
		AgoraData.delay = delay;
		AgoraData.e2eDelay = e2eDelay;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.receivedBitrate = receivedBitrate;
		AgoraData.decoderOutputFrameRate = decoderOutputFrameRate;
		AgoraData.rendererOutputFrameRate = rendererOutputFrameRate;
		AgoraData.frameLossRate = frameLossRate;
		AgoraData.packetLossRate = packetLossRate;
		AgoraData.rxStreamType = static_cast<agora::rtc::VIDEO_STREAM_TYPE>(rxStreamType);
		AgoraData.totalFrozenTime = totalFrozenTime;
		AgoraData.frozenRate = frozenRate;
		AgoraData.avSyncTimeMs = avSyncTimeMs;
		AgoraData.totalActiveTime = totalActiveTime;
		AgoraData.publishDuration = publishDuration;
		AgoraData.mosValue = mosValue;
		AgoraData.rxVideoBytes = rxVideoBytes;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::RemoteVideoStats & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_WlAccStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 e2eDelayPercent = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 frozenRatioPercent = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 lossRatePercent = 0;

	FUABT_WlAccStats(){}
	FUABT_WlAccStats(const agora::rtc::WlAccStats & AgoraData){
		e2eDelayPercent = AgoraData.e2eDelayPercent;
		frozenRatioPercent = AgoraData.frozenRatioPercent;
		lossRatePercent = AgoraData.lossRatePercent;
	}

	agora::rtc::WlAccStats CreateAgoraData() const {
		agora::rtc::WlAccStats AgoraData;
		AgoraData.e2eDelayPercent = e2eDelayPercent;
		AgoraData.frozenRatioPercent = frozenRatioPercent;
		AgoraData.lossRatePercent = lossRatePercent;
		return AgoraData;
	}
};


USTRUCT(BlueprintType)
struct FUABT_UserInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString userAccount = "";

	FUABT_UserInfo(){}
	FUABT_UserInfo(const agora::rtc::UserInfo & AgoraData){
		uid = AgoraData.uid;
		userAccount = UTF8_TO_TCHAR(AgoraData.userAccount);
	}

	agora::rtc::UserInfo CreateAgoraData() const {
		agora::rtc::UserInfo AgoraData;
		AgoraData.uid = uid;
		SET_UABT_FSTRING_TO_CHAR_ARRAY(AgoraData.userAccount,this->userAccount,agora::rtc::MAX_USER_ACCOUNT_LENGTH)
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::UserInfo & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_VideoRenderingTracingInfo {

	GENERATED_BODY()

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int elapsedTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int start2JoinChannel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int join2JoinSuccess = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int joinSuccess2RemoteJoined = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int remoteJoined2SetView = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int remoteJoined2UnmuteVideo = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int remoteJoined2PacketReceived = 0;

	FUABT_VideoRenderingTracingInfo() {}
	FUABT_VideoRenderingTracingInfo(const agora::rtc::VideoRenderingTracingInfo& AgoraData) {
		elapsedTime = AgoraData.elapsedTime;
		start2JoinChannel = AgoraData.start2JoinChannel;
		join2JoinSuccess = AgoraData.join2JoinSuccess;
		joinSuccess2RemoteJoined = AgoraData.joinSuccess2RemoteJoined;
		remoteJoined2SetView = AgoraData.remoteJoined2SetView;
		remoteJoined2UnmuteVideo = AgoraData.remoteJoined2UnmuteVideo;
		remoteJoined2PacketReceived = AgoraData.remoteJoined2PacketReceived;
	}

	agora::rtc::VideoRenderingTracingInfo CreateAgoraData() const {
		agora::rtc::VideoRenderingTracingInfo AgoraData;
		AgoraData.elapsedTime = elapsedTime;
		AgoraData.start2JoinChannel = start2JoinChannel;
		AgoraData.join2JoinSuccess = join2JoinSuccess;
		AgoraData.joinSuccess2RemoteJoined = joinSuccess2RemoteJoined;
		AgoraData.remoteJoined2SetView = remoteJoined2SetView;
		AgoraData.remoteJoined2UnmuteVideo = remoteJoined2UnmuteVideo;
		AgoraData.remoteJoined2PacketReceived = remoteJoined2PacketReceived;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoRenderingTracingInfo& AgoraData) const {
		// no need to free
	}
};



USTRUCT(BlueprintType)
struct FUABT_TranscodingVideoStream {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	EUABT_VIDEO_SOURCE_TYPE sourceType = EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int64 remoteUserUid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	FString imageUrl = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int mediaPlayerId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int zOrder = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	float alpha = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	bool mirror = false;

	FUABT_TranscodingVideoStream(){}
	FUABT_TranscodingVideoStream(const agora::rtc::TranscodingVideoStream & AgoraData){
		sourceType = UABT::ToUEEnum<agora::rtc::VIDEO_SOURCE_TYPE, EUABT_VIDEO_SOURCE_TYPE>(AgoraData.sourceType);
		//static_cast<EUABT_VIDEO_SOURCE_TYPE>(AgoraData.sourceType);
		remoteUserUid = AgoraData.remoteUserUid;
		imageUrl = UTF8_TO_TCHAR(AgoraData.imageUrl);
		mediaPlayerId = AgoraData.mediaPlayerId;
		x = AgoraData.x;
		y = AgoraData.y;
		width = AgoraData.width;
		height = AgoraData.height;
		zOrder = AgoraData.zOrder;
		alpha = AgoraData.alpha;
		mirror = AgoraData.mirror;
	}

	agora::rtc::TranscodingVideoStream CreateAgoraData() const{
		
		agora::rtc::TranscodingVideoStream AgoraData;
		AgoraData.sourceType = static_cast<agora::rtc::VIDEO_SOURCE_TYPE>(sourceType);
		AgoraData.remoteUserUid = remoteUserUid;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.imageUrl,this->imageUrl)
		AgoraData.mediaPlayerId = mediaPlayerId;
		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.zOrder = zOrder;
		AgoraData.alpha = alpha;
		AgoraData.mirror = mirror;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::TranscodingVideoStream & AgoraData) const{
		UABT::Free_CharPtr(AgoraData.imageUrl);
	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoLayout
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	FString channelId = "";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	int64 uid = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	FString strUid = "";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	int64 x = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	int64 y = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	int64 width = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	int64 height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoLayout")
	int64 videoState = 0;

	FUABT_VideoLayout(){}
	FUABT_VideoLayout(const agora::VideoLayout & AgoraData){
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		uid = AgoraData.uid;
		strUid = UTF8_TO_TCHAR(AgoraData.strUid);
		x = AgoraData.x;
		y = AgoraData.y;
		width = AgoraData.width;
		height = AgoraData.height;
		videoState = AgoraData.videoState;
	}

	agora::VideoLayout CreateAgoraData() const {
		agora::VideoLayout AgoraData;
		AgoraData.channelId = UABT::New_CharPtr(channelId);
		AgoraData.uid = uid;
		AgoraData.strUid = UABT::New_CharPtr(strUid);
		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.videoState = videoState;
		return AgoraData;
	}

	void FreeAgoraData(agora::VideoLayout & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelId);
		UABT::Free_CharPtr(AgoraData.strUid);
	}
};


USTRUCT(BlueprintType)
struct FUABT_AgoraMetadata
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	int64 size = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	FString buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	int64 timeStampMs = 0;

	FUABT_AgoraMetadata(){}
	FUABT_AgoraMetadata(const agora::rtc::IMetadataObserver::Metadata & AgoraData){
		uid = AgoraData.uid;
		size = AgoraData.size;
		buffer = UTF8_TO_TCHAR(AgoraData.buffer);
		timeStampMs = AgoraData.timeStampMs;
	}

	agora::rtc::IMetadataObserver::Metadata CreateAgoraData() const {
		agora::rtc::IMetadataObserver::Metadata AgoraData;
		AgoraData.uid = uid;
		AgoraData.size = size;
		SET_UABT_FSTRING_TO_UNSIGNED_CHAR___MEMALLOC(AgoraData.buffer, this->buffer)
		//AgoraData.buffer = UABT::New_UnsignedCharPtr(this->buffer);
		AgoraData.timeStampMs = timeStampMs;
		return AgoraData;
	}
	void FreeAgoraData (agora::rtc::IMetadataObserver::Metadata& AgoraData){
		SET_UABT_FSTRING_TO_UNSIGNED_CHAR___MEMFREE(AgoraData.buffer)
		//UABT::Free_UnsignedCharPtr(AgoraData.buffer);
	}
};


USTRUCT(BlueprintType)
struct FUABT_DirectCdnStreamingStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int videoWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int videoHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int fps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int videoBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int audioBitrate = 0;

	FUABT_DirectCdnStreamingStats(){}
	FUABT_DirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats & AgoraData){
		videoWidth = AgoraData.videoWidth;
		videoHeight = AgoraData.videoHeight;
		fps = AgoraData.fps;
		videoBitrate = AgoraData.videoBitrate;
		audioBitrate = AgoraData.audioBitrate;
	}

	agora::rtc::DirectCdnStreamingStats CreateAgoraData() const {
		agora::rtc::DirectCdnStreamingStats AgoraData;
		AgoraData.videoWidth = videoWidth;
		AgoraData.videoHeight = videoHeight;
		AgoraData.fps = fps;
		AgoraData.videoBitrate = videoBitrate;
		AgoraData.audioBitrate = audioBitrate;
		return AgoraData;
	}
	void FreeAgoraData(agora::rtc::DirectCdnStreamingStats & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_ExtensionContext {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	bool isValid = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	FString providerName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	FString extensionName = "";

	FUABT_ExtensionContext(){}
	FUABT_ExtensionContext(const agora::rtc::ExtensionContext& AgoraData){
		isValid = AgoraData.isValid;
		uid = AgoraData.uid;
		providerName = UTF8_TO_TCHAR(AgoraData.providerName);
		extensionName = UTF8_TO_TCHAR(AgoraData.extensionName);
	}

	agora::rtc::ExtensionContext CreateAgoraData() const {
		agora::rtc::ExtensionContext AgoraData;
		AgoraData.isValid = isValid;
		AgoraData.uid = uid;
		AgoraData.providerName = UABT::New_CharPtr(providerName);
		AgoraData.extensionName = UABT::New_CharPtr(extensionName);
		return AgoraData;
	}
	void FreeAgoraData(agora::rtc::ExtensionContext& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.providerName);
		UABT::Free_CharPtr(AgoraData.extensionName);
	}
};


#pragma endregion EventHandler


#pragma region Rtc Engine


USTRUCT(BlueprintType)
struct FUABT_EncryptionConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	EUABT_ENCRYPTION_MODE encryptionMode = EUABT_ENCRYPTION_MODE::AES_128_GCM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	FString encryptionKey = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	FString encryptionKdfSalt = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	bool datastreamEncryptionEnabled = false;

	FUABT_EncryptionConfig(){}
	FUABT_EncryptionConfig(const agora::rtc::EncryptionConfig & AgoraData){
		encryptionMode = static_cast<EUABT_ENCRYPTION_MODE>(AgoraData.encryptionMode);
		encryptionKey = UTF8_TO_TCHAR(AgoraData.encryptionKey);

		char valencryptionKdfSalt[32] = {0};
		int AgoraCount = 32;
		for (int i = 0; i < AgoraCount; i++) {

			encryptionKdfSalt[i] = AgoraData.encryptionKdfSalt[i];
		}
		encryptionKdfSalt = valencryptionKdfSalt;

		datastreamEncryptionEnabled = AgoraData.datastreamEncryptionEnabled;
	}

	agora::rtc::EncryptionConfig CreateAgoraData() const {
		agora::rtc::EncryptionConfig AgoraData;
		AgoraData.encryptionMode = static_cast<agora::rtc::ENCRYPTION_MODE>(encryptionMode);
		AgoraData.encryptionKey = UABT::New_CharPtr(this->encryptionKey);
		std::string StdencryptionKdfSalt = TCHAR_TO_UTF8(*encryptionKdfSalt);
		int AgoraCount = 32;
		for (int i = 0; i < AgoraCount; i++) {
			if(i >= StdencryptionKdfSalt.size()){
				break;
			}
			AgoraData.encryptionKdfSalt[i] = StdencryptionKdfSalt[i];
		}

		AgoraData.datastreamEncryptionEnabled = datastreamEncryptionEnabled;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::EncryptionConfig & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.encryptionKey);
	}
};

#pragma endregion Rtc Engine


USTRUCT(BlueprintType)
struct FUABT_ClientRoleOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ClientRoleOptions")
	EUABT_AUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel = EUABT_AUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY;

	FUABT_ClientRoleOptions() {}

	FUABT_ClientRoleOptions(const agora::rtc::ClientRoleOptions& AgoraData) {
		audienceLatencyLevel = static_cast<EUABT_AUDIENCE_LATENCY_LEVEL_TYPE>(AgoraData.audienceLatencyLevel);
	}

	agora::rtc::ClientRoleOptions CreateAgoraData() const {
		agora::rtc::ClientRoleOptions AgoraData;
		AgoraData.audienceLatencyLevel = static_cast<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>(audienceLatencyLevel);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ClientRoleOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_SenderOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	EUABT_TCcMode ccMode = EUABT_TCcMode::CC_ENABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	int targetBitrate = 6500;


	agora::rtc::SenderOptions CreateAgoraData() const {
		agora::rtc::SenderOptions AgoraData;
		AgoraData.ccMode = (agora::rtc::TCcMode)ccMode;
		AgoraData.codecType = (agora::rtc::VIDEO_CODEC_TYPE)codecType;
		AgoraData.targetBitrate = targetBitrate;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::SenderOptions& AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_Rectangle
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int height = 0;

	FUABT_Rectangle(){}
	FUABT_Rectangle(const agora::rtc::Rectangle & AgoraData){
		x = AgoraData.x;
		y = AgoraData.y;
		width = AgoraData.width;
		height = AgoraData.height;
	}

	agora::rtc::Rectangle CreateAgoraData() const {
		agora::rtc::Rectangle AgoraData;
		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::Rectangle& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoCanvas
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int64 subviewUid = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	UImage* view = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int64 backgroundColor = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EUABT_RENDER_MODE_TYPE renderMode = EUABT_RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode = EUABT_VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EUABT_VIDEO_VIEW_SETUP_MODE setupMode = EUABT_VIDEO_VIEW_SETUP_MODE::VIDEO_VIEW_SETUP_REPLACE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EUABT_VIDEO_SOURCE_TYPE sourceType = EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int mediaPlayerId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	FUABT_Rectangle cropArea;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	bool enableAlphaMask = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EUABT_VIDEO_MODULE_POSITION position = EUABT_VIDEO_MODULE_POSITION::POSITION_POST_CAPTURER;


	FUABT_VideoCanvas(){}
	FUABT_VideoCanvas(const agora::rtc::VideoCanvas & AgoraData){
		view = nullptr; // [not support]
		uid = AgoraData.uid;
		subviewUid = AgoraData.subviewUid;
		backgroundColor = AgoraData.backgroundColor;
		renderMode = static_cast<EUABT_RENDER_MODE_TYPE>(AgoraData.renderMode);
		mirrorMode = static_cast<EUABT_VIDEO_MIRROR_MODE_TYPE>(AgoraData.mirrorMode);
		setupMode = static_cast<EUABT_VIDEO_VIEW_SETUP_MODE>(AgoraData.setupMode);
		sourceType = static_cast<EUABT_VIDEO_SOURCE_TYPE>(AgoraData.sourceType);
		mediaPlayerId = AgoraData.mediaPlayerId;
		cropArea = FUABT_Rectangle(AgoraData.cropArea);
		enableAlphaMask = AgoraData.enableAlphaMask;
		position = static_cast<EUABT_VIDEO_MODULE_POSITION>(AgoraData.position);
	}

	agora::rtc::VideoCanvas CreateAgoraData() const {
		agora::rtc::VideoCanvas AgoraData;
		AgoraData.view = (agora::view_t) view;
		AgoraData.uid = uid;
		AgoraData.subviewUid = subviewUid;
		AgoraData.backgroundColor = backgroundColor;
		AgoraData.renderMode = static_cast<agora::media::base::RENDER_MODE_TYPE>(renderMode);
		AgoraData.mirrorMode = static_cast<agora::rtc::VIDEO_MIRROR_MODE_TYPE>(mirrorMode);
		AgoraData.setupMode = static_cast<agora::rtc::VIDEO_VIEW_SETUP_MODE>(setupMode);
		AgoraData.sourceType = static_cast<agora::rtc::VIDEO_SOURCE_TYPE>(sourceType);
		AgoraData.mediaPlayerId = AgoraData.mediaPlayerId;
		AgoraData.cropArea = cropArea.CreateAgoraData();
		AgoraData.enableAlphaMask = enableAlphaMask;
		AgoraData.position = static_cast<agora::media::base::VIDEO_MODULE_POSITION>(position);

		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoCanvas& AgoraData) const {
		cropArea.FreeAgoraData(AgoraData.cropArea);
	}
};


USTRUCT(BlueprintType)
struct FUABT_LogConfig {

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	FString filePath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	int64 fileSizeInKB = 2048;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	EUABT_LOG_LEVEL level = EUABT_LOG_LEVEL::LOG_LEVEL_INFO;

	FUABT_LogConfig() {}
	FUABT_LogConfig(const agora::commons::LogConfig& AgoraData) {
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		fileSizeInKB = AgoraData.fileSizeInKB;
		level = (EUABT_LOG_LEVEL)AgoraData.level;
	}

	agora::commons::LogConfig CreateAgoraData() const {
		agora::commons::LogConfig AgoraData;

		AgoraData.filePath = UABT::New_CharPtr(filePath);
		AgoraData.fileSizeInKB = UABT::ToUInt32(fileSizeInKB);
		AgoraData.level = (agora::commons::LOG_LEVEL)level;
		return AgoraData;
	}

	void FreeAgoraData(agora::commons::LogConfig& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.filePath);
	}
};


USTRUCT(BlueprintType)
struct FUABT_RtcEngineContext
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EAgoraBPuEventHandlerType EventHandlerCreationType = EAgoraBPuEventHandlerType::EventHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString appId = "";

	//UIRtcEngineEventHandler* eventHandler = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	//int64 context = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EUABT_CHANNEL_PROFILE_TYPE channelProfile = EUABT_CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString license = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EUABT_AUDIO_SCENARIO_TYPE audioScenario = EUABT_AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT;
	

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EUABT_AREA_CODE areaCode = EUABT_AREA_CODE::AREA_CODE_GLOB;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FUABT_LogConfig logConfig;


	//// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool threadPriority_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EUABT_THREAD_PRIORITY_TYPE threadPriority = EUABT_THREAD_PRIORITY_TYPE::NORMAL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool useExternalEglContext = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool domainLimit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool autoRegisterAgoraExtensions = true;


	FUABT_RtcEngineContext() {}

	agora::rtc::RtcEngineContext CreateAgoraData() const {

		agora::rtc::RtcEngineContext AgoraData;

		//AgoraData.eventHandler = static_cast<agora::rtc::IRtcEngineEventHandler*>(eventHandler);

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.appId, this->appId)
		AgoraData.appId = UABT::New_CharPtr(appId);

		//AgoraData.context = nullptr; // not supported

		AgoraData.channelProfile = (agora::CHANNEL_PROFILE_TYPE)channelProfile;
		
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.license, this->license)

		AgoraData.audioScenario = (agora::rtc::AUDIO_SCENARIO_TYPE)audioScenario;

		AgoraData.areaCode = (unsigned int) UABTEnum::ToRawValue(areaCode);

		AgoraData.logConfig = logConfig.CreateAgoraData();

		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.threadPriority, this->threadPriority, static_cast<agora::rtc::THREAD_PRIORITY_TYPE>(this->threadPriority))

		AgoraData.useExternalEglContext = useExternalEglContext;

		AgoraData.domainLimit = domainLimit;

		AgoraData.autoRegisterAgoraExtensions = autoRegisterAgoraExtensions;
		
		return AgoraData;
	}


	void FreeAgoraData(agora::rtc::RtcEngineContext& AgoraData) const {

		UABT::Free_CharPtr(AgoraData.appId);
		UABT::Free_CharPtr(AgoraData.license);
		logConfig.FreeAgoraData(AgoraData.logConfig);
	}
};

USTRUCT(BlueprintType)
struct FUABT_RtcConnection
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcConnection")
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcConnection")
	int64 localUid = 0;

	FUABT_RtcConnection(){}
	FUABT_RtcConnection(const agora::rtc::RtcConnection & AgoraData){
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		localUid = AgoraData.localUid;
	}

	agora::rtc::RtcConnection CreateAgoraData() const {
		agora::rtc::RtcConnection AgoraData;
		AgoraData.channelId = UABT::New_CharPtr(channelId);
		AgoraData.localUid = localUid;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::RtcConnection & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelId);
	}
	
};






#pragma region Rtc Engine 2


USTRUCT(BlueprintType)
struct FUABT_CodecCapLevels {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_CodecCapLevels")
	EUABT_VIDEO_CODEC_CAPABILITY_LEVEL hwDecodingLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_CodecCapLevels")
	EUABT_VIDEO_CODEC_CAPABILITY_LEVEL swDecodingLevel;
	
	FUABT_CodecCapLevels() {}
	FUABT_CodecCapLevels(const agora::rtc::CodecCapLevels& AgoraData) {
		hwDecodingLevel = UABTEnum::WrapWithUE(AgoraData.hwDecodingLevel);
		swDecodingLevel = UABTEnum::WrapWithUE(AgoraData.swDecodingLevel);
	}

	agora::rtc::CodecCapLevels CreateAgoraData() const {
		agora::rtc::CodecCapLevels AgoraData;
		AgoraData.hwDecodingLevel = UABTEnum::ToRawValue(hwDecodingLevel);
		AgoraData.swDecodingLevel = UABTEnum::ToRawValue(swDecodingLevel);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::CodecCapLevels& AgoraData) const {
		// no need to free
	}
};

USTRUCT(BlueprintType)
struct FUABT_CodecCapInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	int codecCapMask = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	FUABT_CodecCapLevels codecLevels;

	FUABT_CodecCapInfo(){}
	FUABT_CodecCapInfo(const agora::rtc::CodecCapInfo & AgoraData){
		codecType = static_cast<EUABT_VIDEO_CODEC_TYPE>(AgoraData.codecType);
		codecCapMask = AgoraData.codecCapMask;
		codecLevels = AgoraData.codecLevels;
	}

	agora::rtc::CodecCapInfo CreateAgoraData() const {
		agora::rtc::CodecCapInfo AgoraData;
		AgoraData.codecType = static_cast<agora::rtc::VIDEO_CODEC_TYPE>(codecType);
		AgoraData.codecCapMask = codecCapMask;
		AgoraData.codecLevels = codecLevels.CreateAgoraData();
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::CodecCapInfo& AgoraData) const {
		codecLevels.FreeAgoraData(AgoraData.codecLevels);
	}
};



USTRUCT(BlueprintType)
struct FUABT_ChannelMediaOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishCameraTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishSecondaryCameraTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishThirdCameraTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishFourthCameraTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishMicrophoneTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishScreenCaptureVideo = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishScreenCaptureAudio = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishScreenTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishSecondaryScreenTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishThirdScreenTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishFourthScreenTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishCustomAudioTrack = EAgoraOptional::AGORA_NULL_VALUE;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool publishCustomAudioTrackId_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int publishCustomAudioTrackId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishCustomVideoTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishEncodedVideoTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishMediaPlayerAudioTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishMediaPlayerVideoTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishTranscodedVideoTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishMixedAudioTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishLipSyncTrack = EAgoraOptional::AGORA_NULL_VALUE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional autoSubscribeAudio = EAgoraOptional::AGORA_TRUE_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional autoSubscribeVideo = EAgoraOptional::AGORA_TRUE_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional enableAudioRecordingOrPlayout = EAgoraOptional::AGORA_NULL_VALUE;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool publishMediaPlayerId_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int publishMediaPlayerId = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool clientRoleType_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EUABT_CLIENT_ROLE_TYPE clientRoleType = EUABT_CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool audienceLatencyLevel_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EUABT_AUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel = EUABT_AUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_LOW_LATENCY;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool defaultVideoStreamType_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EUABT_VIDEO_STREAM_TYPE defaultVideoStreamType = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool channelProfile_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EUABT_CHANNEL_PROFILE_TYPE channelProfile = EUABT_CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool audioDelayMs_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int audioDelayMs = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool mediaPlayerAudioDelayMs_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int mediaPlayerAudioDelayMs = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool token_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	FString token = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional enableBuiltInMediaEncryption = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional publishRhythmPlayerTrack = EAgoraOptional::AGORA_NULL_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional isInteractiveAudience = EAgoraOptional::AGORA_NULL_VALUE;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool customVideoTrackId_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int64 customVideoTrackId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional isAudioFilterable = EAgoraOptional::AGORA_NULL_VALUE;


	FUABT_ChannelMediaOptions(){}

	FUABT_ChannelMediaOptions(const agora::rtc::ChannelMediaOptions & AgoraData){
		
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishCameraTrack, AgoraData.publishCameraTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishSecondaryCameraTrack, AgoraData.publishSecondaryCameraTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishThirdCameraTrack, AgoraData.publishThirdCameraTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishFourthCameraTrack, AgoraData.publishFourthCameraTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishMicrophoneTrack, AgoraData.publishMicrophoneTrack)

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishScreenCaptureVideo, AgoraData.publishScreenCaptureVideo)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishScreenCaptureAudio, AgoraData.publishScreenCaptureAudio)
#else
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishScreenTrack, AgoraData.publishScreenTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishSecondaryScreenTrack, AgoraData.publishSecondaryScreenTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishThirdScreenTrack, AgoraData.publishThirdScreenTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishFourthScreenTrack, AgoraData.publishFourthScreenTrack)

#endif
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishCustomAudioTrack, AgoraData.publishCustomAudioTrack)
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->publishCustomAudioTrackId, AgoraData.publishCustomAudioTrackId)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishCustomVideoTrack, AgoraData.publishCustomVideoTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishEncodedVideoTrack, AgoraData.publishEncodedVideoTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishMediaPlayerAudioTrack, AgoraData.publishMediaPlayerAudioTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishMediaPlayerVideoTrack, AgoraData.publishMediaPlayerVideoTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishTranscodedVideoTrack, AgoraData.publishTranscodedVideoTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishMixedAudioTrack, AgoraData.publishMixedAudioTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishLipSyncTrack, AgoraData.publishLipSyncTrack)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->autoSubscribeAudio, AgoraData.autoSubscribeAudio)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->autoSubscribeVideo, AgoraData.autoSubscribeVideo)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->enableAudioRecordingOrPlayout, AgoraData.enableAudioRecordingOrPlayout)
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->publishMediaPlayerId, AgoraData.publishMediaPlayerId)

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->clientRoleType,AgoraData.clientRoleType,static_cast<EUABT_CLIENT_ROLE_TYPE>(AgoraData.clientRoleType.value()))
			
		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->audienceLatencyLevel, AgoraData.audienceLatencyLevel, static_cast<EUABT_AUDIENCE_LATENCY_LEVEL_TYPE>(AgoraData.audienceLatencyLevel.value()))

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->defaultVideoStreamType, AgoraData.defaultVideoStreamType, static_cast<EUABT_VIDEO_STREAM_TYPE>(AgoraData.defaultVideoStreamType.value()))

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->channelProfile, AgoraData.channelProfile, static_cast<EUABT_CHANNEL_PROFILE_TYPE>(AgoraData.channelProfile.value()))

		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->audioDelayMs, AgoraData.audioDelayMs)

		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->mediaPlayerAudioDelayMs, AgoraData.mediaPlayerAudioDelayMs)
		
		SET_UEBP_OPTIONAL_VAL_FString(this->token,AgoraData.token)
			
		SET_UEBP_OPTIONAL_VAL_BOOL(this->enableBuiltInMediaEncryption, AgoraData.enableBuiltInMediaEncryption)

		SET_UEBP_OPTIONAL_VAL_BOOL(this->publishRhythmPlayerTrack, AgoraData.publishRhythmPlayerTrack)

		SET_UEBP_OPTIONAL_VAL_BOOL(this->isInteractiveAudience, AgoraData.isInteractiveAudience)

		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->customVideoTrackId, AgoraData.customVideoTrackId)

		SET_UEBP_OPTIONAL_VAL_BOOL(this->isAudioFilterable, AgoraData.isAudioFilterable)
	}

	agora::rtc::ChannelMediaOptions CreateAgoraData() const{
		agora::rtc::ChannelMediaOptions AgoraData;
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishCameraTrack, this->publishCameraTrack)

		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishSecondaryCameraTrack, this->publishSecondaryCameraTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishThirdCameraTrack, this->publishThirdCameraTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishFourthCameraTrack, this->publishFourthCameraTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishMicrophoneTrack, this->publishMicrophoneTrack)

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)

		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishScreenCaptureVideo, this->publishScreenCaptureVideo)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishScreenCaptureAudio, this->publishScreenCaptureAudio)
#else
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishScreenTrack, this->publishScreenTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishSecondaryScreenTrack, this->publishSecondaryScreenTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishThirdScreenTrack, this->publishThirdScreenTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishFourthScreenTrack, this->publishFourthScreenTrack)
#endif

		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishCustomAudioTrack, this->publishCustomAudioTrack)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.publishCustomAudioTrackId, this->publishCustomAudioTrackId)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishCustomVideoTrack, this->publishCustomVideoTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishEncodedVideoTrack, this->publishEncodedVideoTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishMediaPlayerAudioTrack, this->publishMediaPlayerAudioTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishMediaPlayerVideoTrack, this->publishMediaPlayerVideoTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishTranscodedVideoTrack, this->publishTranscodedVideoTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishMixedAudioTrack, this->publishMixedAudioTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishLipSyncTrack, this->publishLipSyncTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.autoSubscribeAudio, this->autoSubscribeAudio)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.autoSubscribeVideo, this->autoSubscribeVideo)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.enableAudioRecordingOrPlayout, this->enableAudioRecordingOrPlayout)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.publishMediaPlayerId, this->publishMediaPlayerId)
		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.clientRoleType, this->clientRoleType,static_cast<agora::rtc::CLIENT_ROLE_TYPE>(this->clientRoleType))
		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.audienceLatencyLevel, this->audienceLatencyLevel, static_cast<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>(this->audienceLatencyLevel))
		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.defaultVideoStreamType, this->defaultVideoStreamType, static_cast<agora::rtc::VIDEO_STREAM_TYPE>(this->defaultVideoStreamType))
		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.channelProfile, this->channelProfile, static_cast<agora::CHANNEL_PROFILE_TYPE>(this->channelProfile))
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.audioDelayMs, this->audioDelayMs)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.mediaPlayerAudioDelayMs, this->mediaPlayerAudioDelayMs)
		SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOALLOC(AgoraData.token, this->token)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.enableBuiltInMediaEncryption, this->enableBuiltInMediaEncryption)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.publishRhythmPlayerTrack, this->publishRhythmPlayerTrack)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.isInteractiveAudience, this->isInteractiveAudience)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.customVideoTrackId, this->customVideoTrackId)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.isAudioFilterable, this->isAudioFilterable)

		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ChannelMediaOptions& AgoraData) const {
		SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOFREE(AgoraData.token)
	}
};



USTRUCT(BlueprintType)
struct FUABT_LeaveChannelOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	bool stopAudioMixing = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	bool stopAllEffect = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	bool stopMicrophoneRecording = true;

	
	FUABT_LeaveChannelOptions() {}

	FUABT_LeaveChannelOptions(const agora::rtc::LeaveChannelOptions& AgoraData) {
		this->stopAudioMixing = AgoraData.stopAudioMixing;
		this->stopAllEffect = AgoraData.stopAllEffect;
		this->stopMicrophoneRecording = AgoraData.stopMicrophoneRecording;
	}

	agora::rtc::LeaveChannelOptions CreateAgoraData() const {
		agora::rtc::LeaveChannelOptions AgoraData;
		AgoraData.stopAudioMixing = this->stopAudioMixing;
		AgoraData.stopAllEffect = this->stopAllEffect;
		AgoraData.stopMicrophoneRecording = this->stopMicrophoneRecording;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LeaveChannelOptions& AgoraData) const {

	}

};



USTRUCT(BlueprintType)
struct FUABT_EchoTestConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	UImage* view = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	bool enableAudio = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	bool enableVideo = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	FString token = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	int intervalInSeconds = 2;

	
	FUABT_EchoTestConfiguration() {}

	FUABT_EchoTestConfiguration(const agora::rtc::EchoTestConfiguration& AgoraData) {
		view = nullptr; // [not support]
		enableAudio = AgoraData.enableAudio;
		enableVideo = AgoraData.enableVideo;
		token = AgoraData.token;
		channelId = AgoraData.channelId;
		intervalInSeconds = AgoraData.intervalInSeconds;
	}

	agora::rtc::EchoTestConfiguration CreateAgoraData() const{
		agora::rtc::EchoTestConfiguration AgoraData;
		//AgoraData.view = view;
		AgoraData.enableAudio = enableAudio;
		AgoraData.enableVideo = enableVideo;

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.token,this->token)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.channelId, this->channelId)

		AgoraData.intervalInSeconds = intervalInSeconds;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::EchoTestConfiguration& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.token);
		UABT::Free_CharPtr(AgoraData.channelId);
	}

};


USTRUCT(BlueprintType)
struct FUABT_VideoFormat {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int height = 360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int fps = 15;

	FUABT_VideoFormat(){}
	FUABT_VideoFormat(const agora::rtc::VideoFormat & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
		fps = AgoraData.fps;
	}

	agora::rtc::VideoFormat CreateAgoraData() const {
		agora::rtc::VideoFormat AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.fps = fps;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoFormat& AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_CameraCapturerConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	EUABT_CAMERA_DIRECTION cameraDirection = EUABT_CAMERA_DIRECTION::CAMERA_FRONT;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	EUABT_CAMERA_FOCAL_LENGTH_TYPE cameraFocalLengthType = EUABT_CAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	bool deviceId_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	FString deviceId = "";


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	bool cameraId_SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	FString cameraId = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	FUABT_VideoFormat format = FUABT_VideoFormat();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional followEncodeDimensionRatio = EAgoraOptional::AGORA_NULL_VALUE;


	FUABT_CameraCapturerConfiguration(){}
	FUABT_CameraCapturerConfiguration(const agora::rtc::CameraCapturerConfiguration & AgoraData){
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
		cameraDirection = static_cast<EUABT_CAMERA_DIRECTION>(AgoraData.cameraDirection.value());
		cameraFocalLengthType = static_cast<EUABT_CAMERA_FOCAL_LENGTH_TYPE>(AgoraData.cameraFocalLengthType.value());
#else

		SET_UEBP_OPTIONAL_VAL_FString(this->deviceId, AgoraData.deviceId);
#endif

#if defined(__ANDROID__)
		cameraId = UTF8_TO_TCHAR(AgoraData.cameraId.value());
#endif

		format = FUABT_VideoFormat(AgoraData.format);
		SET_UEBP_OPTIONAL_VAL_BOOL(	followEncodeDimensionRatio ,AgoraData.followEncodeDimensionRatio)
	}

	agora::rtc::CameraCapturerConfiguration CreateAgoraData() const {
		agora::rtc::CameraCapturerConfiguration AgoraData;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
		AgoraData.cameraDirection = static_cast<agora::rtc::CAMERA_DIRECTION>(cameraDirection);
		AgoraData.cameraFocalLengthType = static_cast<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE>(cameraFocalLengthType);
#else

		SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOALLOC(AgoraData.deviceId, this->deviceId)
#endif

#if defined(__ANDROID__)
		SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOALLOC(
				AgoraData.cameraId,this->cameraId)
			 
#endif

		AgoraData.format = format.CreateAgoraData();

		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.followEncodeDimensionRatio, this->followEncodeDimensionRatio)
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::CameraCapturerConfiguration& AgoraData) const {
		format.FreeAgoraData(AgoraData.format);


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)

#else
		SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOFREE(AgoraData.deviceId)
#endif

#if defined(__ANDROID__)
			SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOFREE(AgoraData.cameraId)

#endif

	}
};



USTRUCT(BlueprintType)
struct FUABT_LastmileProbeConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	bool probeUplink = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	bool probeDownlink = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	int expectedUplinkBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	int expectedDownlinkBitrate = 0;

	FUABT_LastmileProbeConfig(){}
	FUABT_LastmileProbeConfig(const agora::rtc::LastmileProbeConfig & AgoraData){
		probeUplink = AgoraData.probeUplink;
		probeDownlink = AgoraData.probeDownlink;
		expectedUplinkBitrate = AgoraData.expectedUplinkBitrate;
		expectedDownlinkBitrate = AgoraData.expectedDownlinkBitrate;
	}

	agora::rtc::LastmileProbeConfig CreateAgoraData() const{
		agora::rtc::LastmileProbeConfig AgoraData;
		AgoraData.probeUplink = probeUplink;
		AgoraData.probeDownlink = probeDownlink;
		AgoraData.expectedUplinkBitrate = expectedUplinkBitrate;
		AgoraData.expectedDownlinkBitrate = expectedDownlinkBitrate;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LastmileProbeConfig& AgoraData) const {

	}
};



USTRUCT(BlueprintType)
struct FUABT_VideoDimensions {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoDimensions")
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_VideoDimensions")
	int height = 480;

	FUABT_VideoDimensions(){}
	FUABT_VideoDimensions(const agora::rtc::VideoDimensions & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
	}

	agora::rtc::VideoDimensions CreateAgoraData() const{
		agora::rtc::VideoDimensions AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoDimensions& AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_AdvanceOptions {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	EUABT_ENCODING_PREFERENCE encodingPreference = EUABT_ENCODING_PREFERENCE::PREFER_AUTO;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	EUABT_COMPRESSION_PREFERENCE compressionPreference = EUABT_COMPRESSION_PREFERENCE::PREFER_QUALITY;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	bool encodeAlpha = false;


	FUABT_AdvanceOptions() {}

	FUABT_AdvanceOptions(const agora::rtc::AdvanceOptions & AgoraData){
		encodingPreference = UABTEnum::WrapWithUE(AgoraData.encodingPreference);
		compressionPreference = static_cast<EUABT_COMPRESSION_PREFERENCE>(AgoraData.compressionPreference);
		encodeAlpha = AgoraData.encodeAlpha;
	}

	agora::rtc::AdvanceOptions CreateAgoraData() const{
		agora::rtc::AdvanceOptions AgoraData;
		AgoraData.encodingPreference = UABTEnum::ToRawValue(encodingPreference);
		AgoraData.compressionPreference = UABTEnum::ToRawValue(compressionPreference);
		AgoraData.encodeAlpha = encodeAlpha;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AdvanceOptions& AgoraData) const {
		// no need to free
	}
};

USTRUCT(BlueprintType)
struct FUABT_VideoEncoderConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	int frameRate = 15;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	int bitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	int minBitrate = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EUABT_ORIENTATION_MODE orientationMode = EUABT_ORIENTATION_MODE::ORIENTATION_MODE_ADAPTIVE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EUABT_DEGRADATION_PREFERENCE degradationPreference = EUABT_DEGRADATION_PREFERENCE::MAINTAIN_QUALITY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode = EUABT_VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_DISABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	FUABT_AdvanceOptions advanceOptions = FUABT_AdvanceOptions();

	FUABT_VideoEncoderConfiguration(){}
	FUABT_VideoEncoderConfiguration(const agora::rtc::VideoEncoderConfiguration & AgoraData){
		codecType = static_cast<EUABT_VIDEO_CODEC_TYPE>(AgoraData.codecType);
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		minBitrate = AgoraData.minBitrate;
		orientationMode = static_cast<EUABT_ORIENTATION_MODE>(AgoraData.orientationMode);
		degradationPreference = static_cast<EUABT_DEGRADATION_PREFERENCE>(AgoraData.degradationPreference);
		mirrorMode = static_cast<EUABT_VIDEO_MIRROR_MODE_TYPE>(AgoraData.mirrorMode);
		advanceOptions = FUABT_AdvanceOptions(AgoraData.advanceOptions);
	}

	agora::rtc::VideoEncoderConfiguration CreateAgoraData() const {
		agora::rtc::VideoEncoderConfiguration AgoraData;
		AgoraData.codecType = static_cast<agora::rtc::VIDEO_CODEC_TYPE>(codecType);
		AgoraData.dimensions = dimensions.CreateAgoraData();
		AgoraData.frameRate = frameRate;
		AgoraData.bitrate = bitrate;
		AgoraData.minBitrate = minBitrate;
		AgoraData.orientationMode = static_cast<agora::rtc::ORIENTATION_MODE>(orientationMode);
		AgoraData.degradationPreference = static_cast<agora::rtc::DEGRADATION_PREFERENCE>(degradationPreference);
		AgoraData.mirrorMode = static_cast<agora::rtc::VIDEO_MIRROR_MODE_TYPE>(mirrorMode);
		AgoraData.advanceOptions = advanceOptions.CreateAgoraData();
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoEncoderConfiguration& AgoraData) const {
		dimensions.FreeAgoraData(AgoraData.dimensions);
		advanceOptions.FreeAgoraData(AgoraData.advanceOptions);
	}
};


USTRUCT(BlueprintType)
struct FUABT_BeautyOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	EUABT_LIGHTENING_CONTRAST_LEVEL lighteningContrastLevel = EUABT_LIGHTENING_CONTRAST_LEVEL::LIGHTENING_CONTRAST_NORMAL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float lighteningLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float smoothnessLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float rednessLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float sharpnessLevel = 0;

	FUABT_BeautyOptions(){}
	FUABT_BeautyOptions(const agora::rtc::BeautyOptions & AgoraData){
		lighteningContrastLevel = static_cast<EUABT_LIGHTENING_CONTRAST_LEVEL>(AgoraData.lighteningContrastLevel);
		lighteningLevel = AgoraData.lighteningLevel;
		smoothnessLevel = AgoraData.smoothnessLevel;
		rednessLevel = AgoraData.rednessLevel;
		sharpnessLevel = AgoraData.sharpnessLevel;
	}

	agora::rtc::BeautyOptions CreateAgoraData() const {
		agora::rtc::BeautyOptions AgoraData;
		AgoraData.lighteningContrastLevel = static_cast<agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL>(lighteningContrastLevel);
		AgoraData.lighteningLevel = lighteningLevel;
		AgoraData.smoothnessLevel = smoothnessLevel;
		AgoraData.rednessLevel = rednessLevel;
		AgoraData.sharpnessLevel = sharpnessLevel;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::BeautyOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_LowlightEnhanceOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LowlightEnhanceOptions")
	EUABT_LOW_LIGHT_ENHANCE_MODE mode = EUABT_LOW_LIGHT_ENHANCE_MODE::LOW_LIGHT_ENHANCE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LowlightEnhanceOptions")
	EUABT_LOW_LIGHT_ENHANCE_LEVEL level = EUABT_LOW_LIGHT_ENHANCE_LEVEL::LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY;

	FUABT_LowlightEnhanceOptions(){}
	FUABT_LowlightEnhanceOptions(const agora::rtc::LowlightEnhanceOptions & AgoraData){
		mode = static_cast<EUABT_LOW_LIGHT_ENHANCE_MODE>(AgoraData.mode);
		level = static_cast<EUABT_LOW_LIGHT_ENHANCE_LEVEL>(AgoraData.level);
	}
	agora::rtc::LowlightEnhanceOptions CreateAgoraData() const {
		agora::rtc::LowlightEnhanceOptions AgoraData;
		AgoraData.mode = static_cast<agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_MODE>(mode);
		AgoraData.level = static_cast<agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_LEVEL>(level);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LowlightEnhanceOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoDenoiserOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDenoiserOptions")
	EUABT_VIDEO_DENOISER_MODE mode = EUABT_VIDEO_DENOISER_MODE::VIDEO_DENOISER_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDenoiserOptions")
	EUABT_VIDEO_DENOISER_LEVEL  level = EUABT_VIDEO_DENOISER_LEVEL ::VIDEO_DENOISER_LEVEL_HIGH_QUALITY;

	FUABT_VideoDenoiserOptions(){}
	FUABT_VideoDenoiserOptions(const agora::rtc::VideoDenoiserOptions & AgoraData){
		mode = static_cast<EUABT_VIDEO_DENOISER_MODE>(AgoraData.mode);
		level = static_cast<EUABT_VIDEO_DENOISER_LEVEL >(AgoraData.level);
	}

	agora::rtc::VideoDenoiserOptions CreateAgoraData() const {
		agora::rtc::VideoDenoiserOptions AgoraData;
		AgoraData.mode = static_cast<agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_MODE>(mode);
		AgoraData.level = static_cast<agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_LEVEL>(level);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoDenoiserOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_ColorEnhanceOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ColorEnhanceOptions")
	float strengthLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ColorEnhanceOptions")
	float skinProtectLevel = 0;

	FUABT_ColorEnhanceOptions(){}
	FUABT_ColorEnhanceOptions(const agora::rtc::ColorEnhanceOptions & AgoraData){
		strengthLevel = AgoraData.strengthLevel;
		skinProtectLevel = AgoraData.skinProtectLevel;
	}

	agora::rtc::ColorEnhanceOptions CreateAgoraData() const {
		agora::rtc::ColorEnhanceOptions AgoraData;
		AgoraData.strengthLevel = strengthLevel;
		AgoraData.skinProtectLevel = skinProtectLevel;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ColorEnhanceOptions& AgoraData) const {

	}

};

USTRUCT(BlueprintType)
struct FUABT_VirtualBackgroundSource
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	EUABT_BACKGROUND_SOURCE_TYPE background_source_type = EUABT_BACKGROUND_SOURCE_TYPE::BACKGROUND_COLOR;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	int64 color = 0xffffff;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	FString source = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	EUABT_BACKGROUND_BLUR_DEGREE blur_degree = EUABT_BACKGROUND_BLUR_DEGREE::BLUR_DEGREE_HIGH;

	FUABT_VirtualBackgroundSource(){}
	FUABT_VirtualBackgroundSource(const agora::rtc::VirtualBackgroundSource & AgoraData){
		background_source_type = static_cast<EUABT_BACKGROUND_SOURCE_TYPE>(AgoraData.background_source_type);
		color = AgoraData.color;
		source = AgoraData.source;
		blur_degree = static_cast<EUABT_BACKGROUND_BLUR_DEGREE>(AgoraData.blur_degree);
	}

	agora::rtc::VirtualBackgroundSource CreateAgoraData() const {
		agora::rtc::VirtualBackgroundSource AgoraData;
		AgoraData.background_source_type = static_cast<agora::rtc::VirtualBackgroundSource::BACKGROUND_SOURCE_TYPE>(background_source_type);
		AgoraData.color = color;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.source, this->source)
		AgoraData.blur_degree = static_cast<agora::rtc::VirtualBackgroundSource::BACKGROUND_BLUR_DEGREE>(blur_degree);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VirtualBackgroundSource& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.source);
	}
};

USTRUCT(BlueprintType)
struct FUABT_SegmentationProperty
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SegmentationProperty")
	EUABT_SEG_MODEL_TYPE modelType = EUABT_SEG_MODEL_TYPE::SEG_MODEL_AI;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SegmentationProperty")
	float greenCapacity = 0.5;

	FUABT_SegmentationProperty(){}
	FUABT_SegmentationProperty(const agora::rtc::SegmentationProperty & AgoraData){
		modelType = static_cast<EUABT_SEG_MODEL_TYPE>(AgoraData.modelType);
		greenCapacity = AgoraData.greenCapacity;
	}

	agora::rtc::SegmentationProperty CreateAgoraData() const {
		agora::rtc::SegmentationProperty AgoraData;
		AgoraData.modelType = static_cast<agora::rtc::SegmentationProperty::SEG_MODEL_TYPE>(modelType);
		AgoraData.greenCapacity = greenCapacity;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::SegmentationProperty& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoSubscriptionOptions
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool type_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	EUABT_VIDEO_STREAM_TYPE type = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	EAgoraOptional encodedFrameOnly = EAgoraOptional::AGORA_NULL_VALUE;

	FUABT_VideoSubscriptionOptions(){}
	FUABT_VideoSubscriptionOptions(const agora::rtc::VideoSubscriptionOptions & AgoraData){
		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->type,AgoraData.type,static_cast<EUABT_VIDEO_STREAM_TYPE>(AgoraData.type.value()))
		SET_UEBP_OPTIONAL_VAL_BOOL(this->encodedFrameOnly,AgoraData.encodedFrameOnly)
	}

	agora::rtc::VideoSubscriptionOptions CreateAgoraData() const {
		agora::rtc::VideoSubscriptionOptions AgoraData;
		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.type,this->type,static_cast<agora::rtc::VIDEO_STREAM_TYPE>(this->type))

		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.encodedFrameOnly,this->encodedFrameOnly)
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::VideoSubscriptionOptions& AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_AudioRecordingConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	FString filePath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	bool encode = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	int sampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	EUABT_AUDIO_FILE_RECORDING_TYPE fileRecordingType = EUABT_AUDIO_FILE_RECORDING_TYPE::AUDIO_FILE_RECORDING_MIXED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	EUABT_AUDIO_RECORDING_QUALITY_TYPE quality = EUABT_AUDIO_RECORDING_QUALITY_TYPE::AUDIO_RECORDING_QUALITY_LOW;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	int recordingChannel = 0;

	FUABT_AudioRecordingConfiguration(){}
	FUABT_AudioRecordingConfiguration(const agora::rtc::AudioRecordingConfiguration & AgoraData){
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		encode = AgoraData.encode;
		sampleRate = AgoraData.sampleRate;
		fileRecordingType = static_cast<EUABT_AUDIO_FILE_RECORDING_TYPE>(AgoraData.fileRecordingType);
		quality = static_cast<EUABT_AUDIO_RECORDING_QUALITY_TYPE>(AgoraData.quality);
		recordingChannel = AgoraData.recordingChannel;
	}

	agora::rtc::AudioRecordingConfiguration CreateAgoraData() const {
		agora::rtc::AudioRecordingConfiguration AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.filePath, this->filePath)
		AgoraData.encode = encode;
		AgoraData.sampleRate = sampleRate;
		AgoraData.fileRecordingType = static_cast<agora::rtc::AUDIO_FILE_RECORDING_TYPE>(fileRecordingType);
		AgoraData.quality = static_cast<agora::rtc::AUDIO_RECORDING_QUALITY_TYPE>(quality);
		AgoraData.recordingChannel = recordingChannel;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AudioRecordingConfiguration& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.filePath);
	}
};


USTRUCT(BlueprintType)
struct FUABT_SpatialAudioParams
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_azimuth_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_azimuth = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_elevation_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_elevation = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_distance_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_distance = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_orientation_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	int speaker_orientation = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	EAgoraOptional enable_blur = EAgoraOptional::AGORA_NULL_VALUE;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	EAgoraOptional enable_air_absorb = EAgoraOptional::AGORA_NULL_VALUE;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_attenuation_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_attenuation = 0;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	EAgoraOptional enable_doppler = EAgoraOptional::AGORA_NULL_VALUE;

	FUABT_SpatialAudioParams(){}
	FUABT_SpatialAudioParams(const agora::SpatialAudioParams & AgoraData){
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->speaker_azimuth,AgoraData.speaker_azimuth)
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->speaker_elevation,AgoraData.speaker_elevation)
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->speaker_distance,AgoraData.speaker_distance)
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->speaker_orientation,AgoraData.speaker_orientation)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->enable_blur,AgoraData.enable_blur)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->enable_air_absorb,AgoraData.enable_air_absorb)
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->speaker_attenuation,AgoraData.speaker_attenuation)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->enable_doppler,AgoraData.enable_doppler)
	}

	agora::SpatialAudioParams CreateAgoraData() const {
		agora::SpatialAudioParams AgoraData;
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.speaker_azimuth,this->speaker_azimuth)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.speaker_elevation,this->speaker_elevation)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.speaker_distance,this->speaker_distance)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.speaker_orientation,this->speaker_orientation)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.enable_blur,this->enable_blur)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.enable_air_absorb,this->enable_air_absorb)
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.speaker_attenuation,this->speaker_attenuation)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.enable_doppler,this->enable_doppler)
		return AgoraData;
	}

	void FreeAgoraData(agora::SpatialAudioParams& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_SimulcastStreamConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	int kBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	int framerate = 0;

	FUABT_SimulcastStreamConfig(){}
	FUABT_SimulcastStreamConfig(const agora::rtc::SimulcastStreamConfig & AgoraData){
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		kBitrate = AgoraData.kBitrate;
		framerate = AgoraData.framerate;
	}

	agora::rtc::SimulcastStreamConfig CreateAgoraData() const {
		agora::rtc::SimulcastStreamConfig AgoraData;
		AgoraData.dimensions = dimensions.CreateAgoraData();
		AgoraData.kBitrate = kBitrate;
		AgoraData.framerate = framerate;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::SimulcastStreamConfig& AgoraData) const {
		dimensions.FreeAgoraData(AgoraData.dimensions);
	}
};



USTRUCT(BlueprintType)
struct FUABT_ExtensionInfo {

	GENERATED_BODY();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	EUABT_MEDIA_SOURCE_TYPE mediaSourceType = EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	int64 remoteUid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	int64 localUid = 0;

	FUABT_ExtensionInfo() {}

	FUABT_ExtensionInfo(const agora::rtc::ExtensionInfo& AgoraData) {
		mediaSourceType = (EUABT_MEDIA_SOURCE_TYPE)AgoraData.mediaSourceType;
		remoteUid = AgoraData.remoteUid;
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		localUid = AgoraData.localUid;
	}

	agora::rtc::ExtensionInfo CreateAgoraData() const {
		agora::rtc::ExtensionInfo AgoraData;
		AgoraData.mediaSourceType = (agora::media::MEDIA_SOURCE_TYPE)mediaSourceType;
		AgoraData.remoteUid = UABT::ToUID(remoteUid);

		char* ChannelIdCharPtr = new char[channelId.Len() + 1];
		FMemory::Memcpy(ChannelIdCharPtr, TCHAR_TO_UTF8(*channelId), channelId.Len());
		ChannelIdCharPtr[channelId.Len()] = '\0';
		
		AgoraData.channelId = ChannelIdCharPtr;
		AgoraData.localUid = UABT::ToUID(localUid);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ExtensionInfo& AgoraData) const {
		if (AgoraData.channelId) {
			delete[] AgoraData.channelId;
			AgoraData.channelId = nullptr;
		}
	}
};

#pragma endregion Rtc Engine 2



#pragma region Screen Share


USTRUCT(BlueprintType)
struct FUABT_ThumbImageBuffer {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	UImage* Image = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	TArray<uint8> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 length = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 height = 0;

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	FUABT_ThumbImageBuffer(){}
	FUABT_ThumbImageBuffer(const agora::rtc::ThumbImageBuffer & AgoraData){

		length = AgoraData.length;
		buffer.SetNumZeroed(length);
		for (int i = 0; i < length; i++) {
			this->buffer[i] = AgoraData.buffer[i];
		}
		width = AgoraData.width;
		height = AgoraData.height;


		if(Image == nullptr){
			Image = NewObject<UImage>();
		}

		UTexture2D* RenderTexture = UTexture2D::CreateTransient(width, height, PF_R8G8B8A8);

		if(RenderTexture){

#if AG_UE5_OR_LATER
			uint8* RawData = (uint8*)RenderTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(RawData, AgoraData.buffer, width * height * 4);
			RenderTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
			RenderTexture->UpdateResource();
#else
			uint8* RawData = (uint8*)RenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(RawData, AgoraData.buffer, width * height * 4);
			RenderTexture->PlatformData->Mips[0].BulkData.Unlock();
			RenderTexture->UpdateResource();
#endif

			FSlateBrush RenderBrush;
			RenderBrush.SetResourceObject(RenderTexture);
			Image->SetBrush(RenderBrush);
		}


	}

	agora::rtc::ThumbImageBuffer CreateAgoraData() const {
		agora::rtc::ThumbImageBuffer AgoraData;

		// Temp solution for now
		char* TmpChar = new char[length];
		for (int i = 0; i < length; i++) {
			TmpChar[i] = this->buffer[i];
		}

		AgoraData.buffer = TmpChar;
		AgoraData.length = length;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ThumbImageBuffer & AgoraData) const {
		SET_UABT_GENERIC_PTR___MEMFREE(AgoraData.buffer)
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureSourceInfo {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	EUABT_ScreenCaptureSourceType type = EUABT_ScreenCaptureSourceType();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	int64 sourceId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	FString sourceName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	FUABT_ThumbImageBuffer thumbImage = FUABT_ThumbImageBuffer();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	FUABT_ThumbImageBuffer iconImage = FUABT_ThumbImageBuffer();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	FString processPath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	FString sourceTitle = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	bool primaryMonitor = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	bool isOccluded = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	FUABT_Rectangle position = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	bool minimizeWindow = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_ScreenCaptureSourceInfo")
	int64 sourceDisplayId = 0;

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	FUABT_ScreenCaptureSourceInfo(){}
	FUABT_ScreenCaptureSourceInfo(const agora::rtc::ScreenCaptureSourceInfo & AgoraData){

		type = UABTEnum::WrapWithUE(AgoraData.type);

		sourceId = AgoraData.sourceId;
		sourceName = UTF8_TO_TCHAR(AgoraData.sourceName);
		thumbImage = FUABT_ThumbImageBuffer(AgoraData.thumbImage);
		iconImage = FUABT_ThumbImageBuffer(AgoraData.iconImage);
		processPath = UTF8_TO_TCHAR(AgoraData.processPath);
		sourceTitle = UTF8_TO_TCHAR(AgoraData.sourceTitle);
		primaryMonitor = AgoraData.primaryMonitor;
		isOccluded = AgoraData.isOccluded;
		position = FUABT_Rectangle(AgoraData.position);
#if defined(_WIN32)
		minimizeWindow = AgoraData.minimizeWindow;
		sourceDisplayId = AgoraData.sourceDisplayId;
#endif
	}

	agora::rtc::ScreenCaptureSourceInfo CreateAgoraData() const {
		agora::rtc::ScreenCaptureSourceInfo AgoraData;
		AgoraData.type = UABTEnum::ToRawValue(type);
		AgoraData.sourceId = sourceId;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.sourceName, sourceName)
		AgoraData.thumbImage = thumbImage.CreateAgoraData();
		AgoraData.iconImage = iconImage.CreateAgoraData();
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.processPath, processPath)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.sourceTitle, sourceTitle)
		AgoraData.primaryMonitor = primaryMonitor;
		AgoraData.isOccluded = isOccluded;
		AgoraData.position = position.CreateAgoraData();
#if defined(_WIN32)
		AgoraData.minimizeWindow = minimizeWindow;
		AgoraData.sourceDisplayId = sourceDisplayId;
#endif
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenCaptureSourceInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.sourceName);
		thumbImage.FreeAgoraData(AgoraData.thumbImage);
		thumbImage.FreeAgoraData(AgoraData.iconImage);
		UABT::Free_CharPtr(AgoraData.processPath);
		UABT::Free_CharPtr(AgoraData.sourceTitle);
		position.FreeAgoraData(AgoraData.position);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_SIZE {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SIZE")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SIZE")
	int height = 0;

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	FUABT_SIZE(){}
	FUABT_SIZE(const agora::rtc::SIZE & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
	}

	agora::rtc::SIZE CreateAgoraData() const {
		agora::rtc::SIZE AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}
	
	void FreeAgoraData(agora::rtc::SIZE & AgoraData) const {

	}
#endif
};



USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureParameters
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int frameRate = 5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int bitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	bool captureMouseCursor = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	bool windowFocus = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int64 excludeWindowList = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int excludeWindowCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int highLightWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int highLightColor = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	bool enableHighLight = false;

	FUABT_ScreenCaptureParameters(){}
	FUABT_ScreenCaptureParameters(const agora::rtc::ScreenCaptureParameters & AgoraData){
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		captureMouseCursor = AgoraData.captureMouseCursor;
		windowFocus = AgoraData.windowFocus;
		//excludeWindowList = AgoraData.excludeWindowList;
		//excludeWindowCount = AgoraData.excludeWindowCount;
		highLightWidth = AgoraData.highLightWidth;
		highLightColor = AgoraData.highLightColor;
		enableHighLight = AgoraData.enableHighLight;
	}

	agora::rtc::ScreenCaptureParameters CreateAgoraData() const {
		agora::rtc::ScreenCaptureParameters AgoraData;
		AgoraData.dimensions = dimensions.CreateAgoraData();
		AgoraData.frameRate = frameRate;
		AgoraData.bitrate = bitrate;
		AgoraData.captureMouseCursor = captureMouseCursor;
		AgoraData.windowFocus = windowFocus;
		//AgoraData.excludeWindowList = excludeWindowList;
		//AgoraData.excludeWindowCount = excludeWindowCount;
		AgoraData.highLightWidth = highLightWidth;
		AgoraData.highLightColor = highLightColor;
		AgoraData.enableHighLight = enableHighLight;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenCaptureParameters& AgoraData) const {
		dimensions.FreeAgoraData(AgoraData.dimensions);
	}
};

USTRUCT(BlueprintType)
struct FUABT_ScreenAudioParameters {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenAudioParameters")
	int sampleRate = 16000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenAudioParameters")
	int channels = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenAudioParameters")
	int captureSignalVolume = 100;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FUABT_ScreenAudioParameters(){}
	FUABT_ScreenAudioParameters(const agora::rtc::ScreenAudioParameters & AgoraData){
		sampleRate = AgoraData.sampleRate;
		channels = AgoraData.channels;
		captureSignalVolume = AgoraData.captureSignalVolume;
	}

	agora::rtc::ScreenAudioParameters CreateAgoraData() const {
		agora::rtc::ScreenAudioParameters AgoraData;
		AgoraData.sampleRate = sampleRate;
		AgoraData.channels = channels;
		AgoraData.captureSignalVolume = captureSignalVolume;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenAudioParameters& AgoraData) const {

	}
#endif
};

USTRUCT(BlueprintType)
struct FUABT_ScreenVideoParameters {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	int frameRate = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	int bitrate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	EUABT_VIDEO_CONTENT_HINT contentHint = EUABT_VIDEO_CONTENT_HINT::CONTENT_HINT_MOTION;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FUABT_ScreenVideoParameters(){}
	FUABT_ScreenVideoParameters(const agora::rtc::ScreenVideoParameters & AgoraData){
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		contentHint = static_cast<EUABT_VIDEO_CONTENT_HINT>(AgoraData.contentHint);
	}

	agora::rtc::ScreenVideoParameters CreateAgoraData() const {
		agora::rtc::ScreenVideoParameters AgoraData;
		AgoraData.dimensions = dimensions.CreateAgoraData();
		AgoraData.frameRate = frameRate;
		AgoraData.bitrate = bitrate;
		AgoraData.contentHint = static_cast<agora::rtc::VIDEO_CONTENT_HINT>(contentHint);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenVideoParameters& AgoraData) const {
		dimensions.FreeAgoraData(AgoraData.dimensions);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureParameters2
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	bool captureAudio = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	FUABT_ScreenAudioParameters audioParams = FUABT_ScreenAudioParameters();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	bool captureVideo = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	FUABT_ScreenVideoParameters videoParams = FUABT_ScreenVideoParameters();

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FUABT_ScreenCaptureParameters2(){}
	FUABT_ScreenCaptureParameters2(const agora::rtc::ScreenCaptureParameters2 & AgoraData){
		captureAudio = AgoraData.captureAudio;
		audioParams = FUABT_ScreenAudioParameters(AgoraData.audioParams);
		captureVideo = AgoraData.captureVideo;
		videoParams = FUABT_ScreenVideoParameters(AgoraData.videoParams);
	}

	agora::rtc::ScreenCaptureParameters2 CreateAgoraData() const {
		agora::rtc::ScreenCaptureParameters2 AgoraData;
		AgoraData.captureAudio = captureAudio;
		AgoraData.audioParams = audioParams.CreateAgoraData();
		AgoraData.captureVideo = captureVideo;
		AgoraData.videoParams = videoParams.CreateAgoraData();
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenCaptureParameters2& AgoraData) const {
		audioParams.FreeAgoraData(AgoraData.audioParams);
		videoParams.FreeAgoraData(AgoraData.videoParams);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	bool isCaptureWindow = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	int displayId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FUABT_Rectangle screenRect = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	int64 windowId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FUABT_ScreenCaptureParameters params = FUABT_ScreenCaptureParameters();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FUABT_Rectangle regionRect = FUABT_Rectangle();

	FUABT_ScreenCaptureConfiguration(){}
	FUABT_ScreenCaptureConfiguration(const agora::rtc::ScreenCaptureConfiguration & AgoraData){
		isCaptureWindow = AgoraData.isCaptureWindow;
		displayId = AgoraData.displayId;
		screenRect = FUABT_Rectangle(AgoraData.screenRect);
		//windowId = AgoraData.windowId;
		params = FUABT_ScreenCaptureParameters(AgoraData.params);
		regionRect = FUABT_Rectangle(AgoraData.regionRect);
	}

	agora::rtc::ScreenCaptureConfiguration CreateAgoraData() const {
		agora::rtc::ScreenCaptureConfiguration AgoraData;
		AgoraData.isCaptureWindow = isCaptureWindow;
		AgoraData.displayId = displayId;
		AgoraData.screenRect = screenRect.CreateAgoraData();
		//AgoraData.windowId = windowId;
		AgoraData.params = params.CreateAgoraData();
		AgoraData.regionRect = regionRect.CreateAgoraData();
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenCaptureConfiguration & AgoraData) const {
		screenRect.FreeAgoraData(AgoraData.screenRect);
		params.FreeAgoraData(AgoraData.params);
		regionRect.FreeAgoraData(AgoraData.regionRect);
	}
};

#pragma endregion Screen Share



#pragma region Rtc Engine 3

USTRUCT(BlueprintType)
struct FUABT_FocalLengthInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_FocalLengthInfo")
	int cameraDirection = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUABT_FocalLengthInfo")
	EUABT_CAMERA_FOCAL_LENGTH_TYPE focalLengthType = EUABT_CAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

	FUABT_FocalLengthInfo(){}
	FUABT_FocalLengthInfo(const agora::rtc::FocalLengthInfo & AgoraData){
		cameraDirection = AgoraData.cameraDirection;
		focalLengthType = static_cast<EUABT_CAMERA_FOCAL_LENGTH_TYPE>(AgoraData.focalLengthType);
	}

	agora::rtc::FocalLengthInfo CreateAgoraData() const {
		agora::rtc::FocalLengthInfo AgoraData;
		AgoraData.cameraDirection = cameraDirection;
		AgoraData.focalLengthType = static_cast<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE>(focalLengthType);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::FocalLengthInfo& AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_TranscodingUser {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int zOrder = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	float alpha = 1.0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int audioChannel = 0;

	FUABT_TranscodingUser(){}
	FUABT_TranscodingUser(const agora::rtc::TranscodingUser & AgoraData){
		uid = AgoraData.uid;
		x = AgoraData.x;
		y = AgoraData.y;
		width = AgoraData.width;
		height = AgoraData.height;
		zOrder = AgoraData.zOrder;
		alpha = AgoraData.alpha;
		audioChannel = AgoraData.audioChannel;
	}

	agora::rtc::TranscodingUser CreateAgoraData() const {
		agora::rtc::TranscodingUser AgoraData;
		AgoraData.uid = uid;
		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.zOrder = zOrder;
		AgoraData.alpha = alpha;
		AgoraData.audioChannel = audioChannel;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::TranscodingUser& AgoraData) const {

	}

};

USTRUCT(BlueprintType)
struct FUABT_RtcImage
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	FString url = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int zOrder = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	float alpha = 0;

	FUABT_RtcImage() {}

	FUABT_RtcImage(const agora::rtc::RtcImage& AgoraData) {
		url = UTF8_TO_TCHAR(AgoraData.url);
		x = AgoraData.x;
		y = AgoraData.y;
		width = AgoraData.width;
		height = AgoraData.height;
		zOrder = AgoraData.zOrder;
		alpha = AgoraData.alpha;
	}

	agora::rtc::RtcImage CreateAgoraData() const {
		agora::rtc::RtcImage AgoraData;
		
		char* URLCharPtr = new char[url.Len() + 1];
		FMemory::Memcpy(URLCharPtr, TCHAR_TO_UTF8(*url), url.Len());
		URLCharPtr[url.Len()] = '\0';
		AgoraData.url = URLCharPtr;

		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.zOrder = zOrder;
		AgoraData.alpha = alpha;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::RtcImage& AgoraData) const {
		if (AgoraData.url) {
			delete[] AgoraData.url;
			AgoraData.url = nullptr;
		}
	}
};


USTRUCT(BlueprintType)
struct FUABT_LiveStreamAdvancedFeature {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveStreamAdvancedFeature")
	FString featureName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveStreamAdvancedFeature")
	bool opened = false;

	FUABT_LiveStreamAdvancedFeature(){}
	FUABT_LiveStreamAdvancedFeature(const agora::rtc::LiveStreamAdvancedFeature & AgoraData){
		featureName = UTF8_TO_TCHAR(AgoraData.featureName);
		opened = AgoraData.opened;
	}

	agora::rtc::LiveStreamAdvancedFeature CreateAgoraData() const {
		agora::rtc::LiveStreamAdvancedFeature AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.featureName, this->featureName)
		AgoraData.opened = opened;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LiveStreamAdvancedFeature& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.featureName);
	}
};



USTRUCT(BlueprintType)
struct FUABT_LiveTranscoding
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int width = 360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int height = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int videoBitrate = 400;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int videoFramerate = 15;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	bool lowLatency = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int videoGop = 30;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EUABT_VIDEO_CODEC_PROFILE_TYPE videoCodecProfile = EUABT_VIDEO_CODEC_PROFILE_TYPE::VIDEO_CODEC_PROFILE_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int64 backgroundColor = 0x000000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EUABT_VIDEO_CODEC_TYPE_FOR_STREAM videoCodecType = EUABT_VIDEO_CODEC_TYPE_FOR_STREAM::VIDEO_CODEC_H264_FOR_STREAM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int userCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FUABT_TranscodingUser> transcodingUsers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	FString transcodingExtraInfo = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	FString metadata = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray <FUABT_RtcImage> watermark;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int watermarkCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FUABT_RtcImage> backgroundImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int backgroundImageCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EUABT_AUDIO_SAMPLE_RATE_TYPE audioSampleRate = EUABT_AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int audioBitrate = 48;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int audioChannels = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EUABT_AUDIO_CODEC_PROFILE_TYPE audioCodecProfile = EUABT_AUDIO_CODEC_PROFILE_TYPE::AUDIO_CODEC_PROFILE_LC_AAC;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FUABT_LiveStreamAdvancedFeature> advancedFeatures;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int advancedFeatureCount = 0;

	FUABT_LiveTranscoding(){}
	FUABT_LiveTranscoding(const agora::rtc::LiveTranscoding & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
		videoBitrate = AgoraData.videoBitrate;
		videoFramerate = AgoraData.videoFramerate;
		lowLatency = AgoraData.lowLatency;
		videoGop = AgoraData.videoGop;
		videoCodecProfile = static_cast<EUABT_VIDEO_CODEC_PROFILE_TYPE>(AgoraData.videoCodecProfile);
		backgroundColor = AgoraData.backgroundColor;
		videoCodecType = static_cast<EUABT_VIDEO_CODEC_TYPE_FOR_STREAM>(AgoraData.videoCodecType);
		userCount = AgoraData.userCount;
		for(int i = 0; i< userCount; i++){
			transcodingUsers.Add(FUABT_TranscodingUser((AgoraData.transcodingUsers[i])));
		}
	
		transcodingExtraInfo = UTF8_TO_TCHAR(AgoraData.transcodingExtraInfo);
		metadata = UTF8_TO_TCHAR(AgoraData.metadata);

		for(unsigned int i =0; i< AgoraData.watermarkCount;i++)
		{
			watermark.Add(FUABT_RtcImage(AgoraData.watermark[i]));
		}
		watermarkCount = AgoraData.watermarkCount;

		for(unsigned int i =0; i< AgoraData.backgroundImageCount;i++){
			backgroundImage.Add(FUABT_RtcImage(AgoraData.watermark[i]));
		}
		backgroundImageCount = AgoraData.backgroundImageCount;
		audioSampleRate = static_cast<EUABT_AUDIO_SAMPLE_RATE_TYPE>(AgoraData.audioSampleRate);
		audioBitrate = AgoraData.audioBitrate;
		audioChannels = AgoraData.audioChannels;
		audioCodecProfile = static_cast<EUABT_AUDIO_CODEC_PROFILE_TYPE>(AgoraData.audioCodecProfile);

		for(unsigned int i = 0; i< AgoraData.advancedFeatureCount; i++){
			advancedFeatures.Add(FUABT_LiveStreamAdvancedFeature(AgoraData.advancedFeatures[i]));
		}
		advancedFeatureCount = AgoraData.advancedFeatureCount;
	}

	agora::rtc::LiveTranscoding CreateAgoraData() const {
		agora::rtc::LiveTranscoding AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.videoBitrate = videoBitrate;
		AgoraData.videoFramerate = videoFramerate;
		AgoraData.lowLatency = lowLatency;
		AgoraData.videoGop = videoGop;
		AgoraData.videoCodecProfile = static_cast<agora::rtc::VIDEO_CODEC_PROFILE_TYPE>(videoCodecProfile);
		AgoraData.backgroundColor = static_cast<unsigned int>(backgroundColor);
		AgoraData.videoCodecType = static_cast<agora::rtc::VIDEO_CODEC_TYPE_FOR_STREAM>(videoCodecType);
		
		AgoraData.userCount = userCount;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.transcodingUsers, agora::rtc::TranscodingUser, userCount, this->transcodingUsers)

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.transcodingExtraInfo,this->transcodingExtraInfo)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.metadata,this->metadata)

		AgoraData.watermarkCount = watermarkCount;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.watermark, agora::rtc::RtcImage, watermarkCount, this->watermark)
		
		AgoraData.backgroundImageCount = backgroundImageCount;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.backgroundImage, agora::rtc::RtcImage, backgroundImageCount, this->backgroundImage)

		AgoraData.audioSampleRate = static_cast<agora::rtc::AUDIO_SAMPLE_RATE_TYPE>(audioSampleRate);
		AgoraData.audioBitrate = audioBitrate;
		AgoraData.audioChannels = audioChannels;

		AgoraData.advancedFeatureCount = advancedFeatureCount;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.advancedFeatures,agora::rtc::LiveStreamAdvancedFeature, advancedFeatureCount,this->advancedFeatures)

		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LiveTranscoding & AgoraData) const{

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.transcodingUsers,userCount, FUABT_TranscodingUser)
		
		UABT::Free_CharPtr(AgoraData.transcodingExtraInfo);

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.watermark, watermarkCount, FUABT_RtcImage)

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.backgroundImage, backgroundImageCount, FUABT_RtcImage)

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.advancedFeatures, advancedFeatureCount, FUABT_LiveStreamAdvancedFeature)
	
	}
		
};




USTRUCT(BlueprintType)
struct FUABT_LocalTranscoderConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	int64 streamCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	TArray<FUABT_TranscodingVideoStream> videoInputStreams;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	FUABT_VideoEncoderConfiguration videoOutputConfiguration = FUABT_VideoEncoderConfiguration();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	bool syncWithPrimaryCamera = true;

	FUABT_LocalTranscoderConfiguration(){}
	FUABT_LocalTranscoderConfiguration(const agora::rtc::LocalTranscoderConfiguration & AgoraData){
		streamCount = AgoraData.streamCount;
		for(int i = 0; i< streamCount; i++){
			videoInputStreams.Add(FUABT_TranscodingVideoStream(AgoraData.videoInputStreams[i]));
		}
		videoOutputConfiguration = FUABT_VideoEncoderConfiguration(AgoraData.videoOutputConfiguration);
		syncWithPrimaryCamera = AgoraData.syncWithPrimaryCamera;
	}

	agora::rtc::LocalTranscoderConfiguration CreateAgoraData() const {
		agora::rtc::LocalTranscoderConfiguration AgoraData;
		AgoraData.streamCount = streamCount;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.videoInputStreams, agora::rtc::TranscodingVideoStream, streamCount, this->videoInputStreams)
		AgoraData.videoOutputConfiguration = videoOutputConfiguration.CreateAgoraData();
		AgoraData.syncWithPrimaryCamera = syncWithPrimaryCamera;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LocalTranscoderConfiguration & AgoraData) const {
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.videoInputStreams, streamCount, FUABT_TranscodingVideoStream)
		videoOutputConfiguration.FreeAgoraData(AgoraData.videoOutputConfiguration);
	}
};


USTRUCT(BlueprintType)
struct FUABT_DataStreamConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DataStreamConfig")
	bool syncWithAudio = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DataStreamConfig")
	bool ordered = false;

	FUABT_DataStreamConfig(){}
	FUABT_DataStreamConfig(const agora::rtc::DataStreamConfig & AgoraData){
		syncWithAudio = AgoraData.syncWithAudio;
		ordered = AgoraData.ordered;
	}

	agora::rtc::DataStreamConfig CreateAgoraData() const {
		agora::rtc::DataStreamConfig AgoraData;
		AgoraData.syncWithAudio = syncWithAudio;
		AgoraData.ordered = ordered;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::DataStreamConfig & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_WatermarkRatio {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkRatio")
	float xRatio = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkRatio")
	float yRatio = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkRatio")
	float widthRatio = 0;

	FUABT_WatermarkRatio(){}
	FUABT_WatermarkRatio(const agora::rtc::WatermarkRatio & AgoraData){
		xRatio = AgoraData.xRatio;
		yRatio = AgoraData.yRatio;
		widthRatio = AgoraData.widthRatio;
	}

	agora::rtc::WatermarkRatio CreateAgoraData() const {
		agora::rtc::WatermarkRatio AgoraData;
		AgoraData.xRatio = xRatio;
		AgoraData.yRatio = yRatio;
		AgoraData.widthRatio = widthRatio;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::WatermarkRatio & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_WatermarkOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	bool visibleInPreview = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FUABT_Rectangle positionInLandscapeMode = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FUABT_Rectangle positionInPortraitMode = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FUABT_WatermarkRatio watermarkRatio = FUABT_WatermarkRatio();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	EUABT_WATERMARK_FIT_MODE mode = EUABT_WATERMARK_FIT_MODE::FIT_MODE_COVER_POSITION;

	FUABT_WatermarkOptions(){}
	FUABT_WatermarkOptions(const agora::rtc::WatermarkOptions & AgoraData){
		visibleInPreview = AgoraData.visibleInPreview;
		positionInLandscapeMode = FUABT_Rectangle(AgoraData.positionInLandscapeMode);
		positionInPortraitMode = FUABT_Rectangle(AgoraData.positionInPortraitMode);
		watermarkRatio = FUABT_WatermarkRatio(AgoraData.watermarkRatio);
		mode = static_cast<EUABT_WATERMARK_FIT_MODE>(AgoraData.mode);
	}

	agora::rtc::WatermarkOptions CreateAgoraData() const {
		agora::rtc::WatermarkOptions AgoraData;
		AgoraData.visibleInPreview = visibleInPreview;
		AgoraData.positionInLandscapeMode = positionInLandscapeMode.CreateAgoraData();
		AgoraData.positionInPortraitMode = positionInPortraitMode.CreateAgoraData();
		AgoraData.watermarkRatio = watermarkRatio.CreateAgoraData();
		AgoraData.mode = static_cast<agora::rtc::WATERMARK_FIT_MODE>(mode);
		return AgoraData;
	}
	void FreeAgoraData(agora::rtc::WatermarkOptions & AgoraData) const {
		positionInLandscapeMode.FreeAgoraData(AgoraData.positionInLandscapeMode);
		positionInPortraitMode.FreeAgoraData(AgoraData.positionInPortraitMode);
		watermarkRatio.FreeAgoraData(AgoraData.watermarkRatio);
	}
	
};


USTRUCT(BlueprintType)
struct FUABT_AgoraRhythmPlayerConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraRhythmPlayerConfig")
	int beatsPerMeasure = 4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraRhythmPlayerConfig")
	int beatsPerMinute = 60;

	FUABT_AgoraRhythmPlayerConfig(){}
	FUABT_AgoraRhythmPlayerConfig(const agora::rtc::AgoraRhythmPlayerConfig & AgoraData){
		beatsPerMeasure = AgoraData.beatsPerMeasure;
		beatsPerMinute = AgoraData.beatsPerMinute;
	}

	agora::rtc::AgoraRhythmPlayerConfig CreateAgoraData() const {
		agora::rtc::AgoraRhythmPlayerConfig AgoraData;
		AgoraData.beatsPerMeasure = beatsPerMeasure;
		AgoraData.beatsPerMinute = beatsPerMinute;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AgoraRhythmPlayerConfig & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_ContentInspectModule {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectModule")
	EUABT_CONTENT_INSPECT_TYPE type = EUABT_CONTENT_INSPECT_TYPE::CONTENT_INSPECT_INVALID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectModule")
	int64 interval = 0;

	FUABT_ContentInspectModule(){}
	FUABT_ContentInspectModule(const agora::media::ContentInspectModule & AgoraData){
		type = static_cast<EUABT_CONTENT_INSPECT_TYPE>(AgoraData.type);
		interval = AgoraData.interval;
	}

	agora::media::ContentInspectModule CreateAgoraData() const {
		agora::media::ContentInspectModule AgoraData;
		AgoraData.type = static_cast<agora::media::CONTENT_INSPECT_TYPE>(type);
		AgoraData.interval = interval;
		return AgoraData;
	}
	void FreeAgoraData(agora::media::ContentInspectModule & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_ContentInspectConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	FString extraInfo = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	FString serverConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	TArray<FUABT_ContentInspectModule> modules;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	int moduleCount = 0;

	FUABT_ContentInspectConfig(){}
	FUABT_ContentInspectConfig(const agora::media::ContentInspectConfig & AgoraData){
		extraInfo = UTF8_TO_TCHAR(AgoraData.extraInfo);
		serverConfig = UTF8_TO_TCHAR(AgoraData.serverConfig);
		moduleCount = AgoraData.moduleCount;
		for(int i = 0; i< moduleCount; i++){
			modules.Add(FUABT_ContentInspectModule(AgoraData.modules[i]));
		}
	}

	agora::media::ContentInspectConfig CreateAgoraData() const {
		agora::media::ContentInspectConfig AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.extraInfo,this->extraInfo)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.serverConfig, this->serverConfig)
		AgoraData.moduleCount = moduleCount;
		for(int i = 0;i < moduleCount; i++){
			AgoraData.modules[i] = modules[i].CreateAgoraData();
		}
		return AgoraData;
	}

	void FreeAgoraData(agora::media::ContentInspectConfig & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.extraInfo);
		UABT::Free_CharPtr(AgoraData.serverConfig);
		for (int i = 0; i < moduleCount; i++) {
			FUABT_ContentInspectModule ReleaseOperator;
			ReleaseOperator.FreeAgoraData(AgoraData.modules[i]);
		}
	}

};

USTRUCT(BlueprintType)
struct FUABT_LogUploadServerInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogUploadServerInfo")
	FString serverDomain = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogUploadServerInfo")
	FString serverPath = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogUploadServerInfo")
	int serverPort = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogUploadServerInfo")
	bool serverHttps = true;

	FUABT_LogUploadServerInfo() {}
	FUABT_LogUploadServerInfo(const agora::rtc::LogUploadServerInfo& AgoraData) {
		serverDomain = UTF8_TO_TCHAR(AgoraData.serverDomain);
		serverPath = UTF8_TO_TCHAR(AgoraData.serverPath);
		serverPort = AgoraData.serverPort;
		serverHttps = AgoraData.serverHttps;
	}

	agora::rtc::LogUploadServerInfo CreateAgoraData() const {
		agora::rtc::LogUploadServerInfo AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.serverDomain, serverDomain)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.serverPath, serverPath)
		
		AgoraData.serverPort = serverPort;
		AgoraData.serverHttps = serverHttps;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LogUploadServerInfo& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.serverDomain);
		UABT::Free_CharPtr(AgoraData.serverPath);
	}
};


USTRUCT(BlueprintType)
struct FUABT_AdvancedConfigInfo {

	GENERATED_BODY()

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedConfigInfo")
	FUABT_LogUploadServerInfo logUploadServer = FUABT_LogUploadServerInfo();

	FUABT_AdvancedConfigInfo(){}
	FUABT_AdvancedConfigInfo(const agora::rtc::AdvancedConfigInfo& AgoraData) {
		logUploadServer = FUABT_LogUploadServerInfo(AgoraData.logUploadServer);
	}

	agora::rtc::AdvancedConfigInfo CreateAgoraData() const {
		agora::rtc::AdvancedConfigInfo AgoraData;
		AgoraData.logUploadServer = logUploadServer.CreateAgoraData();
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AdvancedConfigInfo& AgoraData) const {
		logUploadServer.FreeAgoraData(AgoraData.logUploadServer);
	}
};

USTRUCT(BlueprintType)
struct FUABT_LocalAccessPointConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	TArray<FString> ipList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	int ipListSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	TArray<FString> domainList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	int domainListSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	FString verifyDomainName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	ELOCAL_PROXY_MODE mode = ELOCAL_PROXY_MODE::ConnectivityFirst;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	FUABT_AdvancedConfigInfo advancedConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	bool disableAut = false;

	FUABT_LocalAccessPointConfiguration(){}
	FUABT_LocalAccessPointConfiguration(const agora::rtc::LocalAccessPointConfiguration & AgoraData){
		
		for(int i = 0; i< AgoraData.ipListSize; i++){
			ipList.Add(UTF8_TO_TCHAR(AgoraData.ipList[i]));
		}

		ipListSize = AgoraData.ipListSize;

		for (int i = 0; i < AgoraData.domainListSize; i++) {
			domainList.Add(UTF8_TO_TCHAR(AgoraData.domainList[i]));
		}

		domainListSize = AgoraData.domainListSize;

		verifyDomainName = UTF8_TO_TCHAR(AgoraData.verifyDomainName);

		mode = static_cast<ELOCAL_PROXY_MODE>(AgoraData.mode);

		advancedConfig = FUABT_AdvancedConfigInfo(AgoraData.advancedConfig);

		disableAut = AgoraData.disableAut;
	}

	agora::rtc::LocalAccessPointConfiguration CreateAgoraData() const {
		
		agora::rtc::LocalAccessPointConfiguration AgoraData;
		SET_UABT_TARRARY_FSTRING_TO_CONST_AGORA_ARRAY___MEMALLOC(AgoraData.ipList, ipListSize, this->ipList)
		AgoraData.ipListSize = ipListSize;
		SET_UABT_TARRARY_FSTRING_TO_CONST_AGORA_ARRAY___MEMALLOC(AgoraData.domainList, domainListSize, this->domainList)
			AgoraData.domainListSize = domainListSize;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.verifyDomainName, this->verifyDomainName)
			AgoraData.mode = static_cast<agora::rtc::LOCAL_PROXY_MODE>(mode);
		AgoraData.advancedConfig = advancedConfig.CreateAgoraData();
		AgoraData.disableAut = disableAut;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LocalAccessPointConfiguration & AgoraData) const {
		SET_UABT_TARRARY_FSTRING_TO_AGORA_ARRAY___MEMFREE(AgoraData.ipList, ipListSize)
		SET_UABT_TARRARY_FSTRING_TO_AGORA_ARRAY___MEMFREE(AgoraData.domainList, domainListSize)
		UABT::Free_CharPtr(AgoraData.verifyDomainName);
		advancedConfig.FreeAgoraData(AgoraData.advancedConfig);
	}
};

USTRUCT(BlueprintType)
struct FUABT_AdvancedAudioOptions
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	bool audioProcessingChannels_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	int audioProcessingChannels = 0;

	FUABT_AdvancedAudioOptions(){}
	FUABT_AdvancedAudioOptions(const agora::rtc::AdvancedAudioOptions & AgoraData){
		SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(this->audioProcessingChannels, AgoraData.audioProcessingChannels)
	}

	agora::rtc::AdvancedAudioOptions CreateAgoraData() const {
		agora::rtc::AdvancedAudioOptions AgoraData;
		SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(AgoraData.audioProcessingChannels, this->audioProcessingChannels)
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AdvancedAudioOptions & AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_ImageTrackOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ImageTrackOptions")
	FString imageUrl = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ImageTrackOptions")
	int fps = 1;

	FUABT_ImageTrackOptions(){}
	FUABT_ImageTrackOptions(const agora::rtc::ImageTrackOptions & AgoraData){
		imageUrl = UTF8_TO_TCHAR(AgoraData.imageUrl);
		fps = AgoraData.fps;
	}

	agora::rtc::ImageTrackOptions CreateAgoraData() const {
		agora::rtc::ImageTrackOptions AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.imageUrl,this->imageUrl)
		AgoraData.fps = fps;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ImageTrackOptions & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.imageUrl);
	}

};

USTRUCT(BlueprintType)
struct FUABT_DeviceInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DeviceInfo")
	bool isLowLatencyAudioSupported = false;

	FUABT_DeviceInfo(){}
	FUABT_DeviceInfo(const agora::rtc::DeviceInfo & AgoraData){
		isLowLatencyAudioSupported = AgoraData.isLowLatencyAudioSupported;
	}

	agora::rtc::DeviceInfo CreateAgoraData() const {
		agora::rtc::DeviceInfo AgoraData;
		AgoraData.isLowLatencyAudioSupported = isLowLatencyAudioSupported;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::DeviceInfo& AgoraData) const {

	}
};



USTRUCT(BlueprintType)
struct FUABT_ChannelMediaInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	int64 uid = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString channelName = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString token = "";

	FUABT_ChannelMediaInfo(){}
	FUABT_ChannelMediaInfo(const agora::rtc::ChannelMediaInfo & AgoraData){
		channelName = UTF8_TO_TCHAR(AgoraData.channelName);
		token = UTF8_TO_TCHAR(AgoraData.token);
		uid = AgoraData.uid;
	}

	agora::rtc::ChannelMediaInfo CreateAgoraData() const {
		agora::rtc::ChannelMediaInfo AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.channelName,this->channelName)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.token,this->token)
		AgoraData.uid = uid;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ChannelMediaInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelName);
		UABT::Free_CharPtr(AgoraData.token);
	}
};


USTRUCT(BlueprintType)
struct FUABT_ChannelMediaRelayConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	FUABT_ChannelMediaInfo srcInfo = FUABT_ChannelMediaInfo();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	TArray<FUABT_ChannelMediaInfo> destInfos;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	int destCount = 0;

	FUABT_ChannelMediaRelayConfiguration(){}
	FUABT_ChannelMediaRelayConfiguration(const agora::rtc::ChannelMediaRelayConfiguration & AgoraData){
		srcInfo = FUABT_ChannelMediaInfo(*(AgoraData.srcInfo));
		destCount = AgoraData.destCount;
		for(int i = 0; i< destCount; i++){
			destInfos.Add(FUABT_ChannelMediaInfo(AgoraData.destInfos[i]));
		}
	}

	agora::rtc::ChannelMediaRelayConfiguration CreateAgoraData() const {
		agora::rtc::ChannelMediaRelayConfiguration AgoraData;
		
		SET_UABT_UECUSTOMDATA_TO_AGORA_PTR_1_ENTRY___MEMALLOC(AgoraData.srcInfo,agora::rtc::ChannelMediaInfo, this->srcInfo)

		AgoraData.destCount = destCount;
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(AgoraData.destInfos, agora::rtc::ChannelMediaInfo, destCount, this->destInfos)

		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ChannelMediaRelayConfiguration & AgoraData) const {
		SET_UABT_UECUSTOMDATA_TO_AGORA_PTR_1_ENTRY___MEMFREE(AgoraData.srcInfo, FUABT_ChannelMediaInfo)
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.destInfos, destCount, FUABT_ChannelMediaInfo)
	}
};

#pragma endregion Rtc Engine 3