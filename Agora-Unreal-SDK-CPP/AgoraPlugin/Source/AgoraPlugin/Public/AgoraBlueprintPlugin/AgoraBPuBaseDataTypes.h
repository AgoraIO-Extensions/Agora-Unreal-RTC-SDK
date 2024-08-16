// Copyright(c) 2024 Agora.io.All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "UtilityUEEnumAgoraConvertMacro.h"
#include "UtilityUABTTypeHelper.h"
#include "UtilityAgoraBPuLogger.h"
#include "Components/Image.h"
#include "AgoraBPuBaseDataTypes.generated.h"

using UABT = agora::rtc::ue::UABT;


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

UENUM(BlueprintType)
enum class EVIDEO_SOURCE_TYPE : uint8 {
	/** Video captured by the camera.
	 */
	VIDEO_SOURCE_CAMERA_PRIMARY = 0,
	VIDEO_SOURCE_CAMERA = VIDEO_SOURCE_CAMERA_PRIMARY,
	/** Video captured by the secondary camera.
	 */
	VIDEO_SOURCE_CAMERA_SECONDARY = 1,
	/** Video for screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_PRIMARY = 2,
	VIDEO_SOURCE_SCREEN = VIDEO_SOURCE_SCREEN_PRIMARY,
	/** Video for secondary screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_SECONDARY = 3,
	/** Not define.
	 */
	VIDEO_SOURCE_CUSTOM = 4,
	/** Video for media player sharing.
	 */
	VIDEO_SOURCE_MEDIA_PLAYER = 5,
	/** Video for png image.
	 */
	VIDEO_SOURCE_RTC_IMAGE_PNG = 6,
	/** Video for png image.
	 */
	VIDEO_SOURCE_RTC_IMAGE_JPEG = 7,
	/** Video for png image.
	 */
	VIDEO_SOURCE_RTC_IMAGE_GIF = 8,
	/** Remote video received from network.
	 */
	VIDEO_SOURCE_REMOTE = 9,
	/** Video for transcoded.
	 */
	VIDEO_SOURCE_TRANSCODED = 10,

	/** Video captured by the third camera.
	 */
	VIDEO_SOURCE_CAMERA_THIRD = 11,
	/** Video captured by the fourth camera.
	 */
	VIDEO_SOURCE_CAMERA_FOURTH = 12,
	/** Video for third screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_THIRD = 13,
	/** Video for fourth screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_FOURTH = 14,
	/** Video for voice drive.
	*/
	VIDEO_SOURCE_SPEECH_DRIVEN = 15,

	VIDEO_SOURCE_UNKNOWN = 100
};


UENUM(BlueprintType)
enum class ETHREAD_PRIORITY_TYPE : uint8 {

	LOWEST = 0,

	LOW = 1,

	NORMAL = 2,

	HIGH = 3,

	HIGHEST = 4,

	CRITICAL = 5,
};


UENUM(BlueprintType)
enum class EPROXY_TYPE : uint8 {

	NONE_PROXY_TYPE = 0,

	UDP_PROXY_TYPE = 1,

	TCP_PROXY_TYPE = 2,

	LOCAL_PROXY_TYPE = 3,

	TCP_PROXY_AUTO_FALLBACK_TYPE = 4,

	HTTP_PROXY_TYPE = 5,

	HTTPS_PROXY_TYPE = 6,
};


UENUM(BlueprintType)
enum class ELASTMILE_PROBE_RESULT_STATE :uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	LASTMILE_PROBE_RESULT_COMPLETE = 1,

	LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE = 2,

	LASTMILE_PROBE_RESULT_UNAVAILABLE = 3
};



USTRUCT(BlueprintType)
struct FLastmileProbeOneWayResult {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult")
	int64 packetLossRate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult")
	int64 jitter = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult")
	int64 availableBandwidth = 0;

	FLastmileProbeOneWayResult(){}
	FLastmileProbeOneWayResult(const agora::rtc::LastmileProbeOneWayResult & AgoraData){
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
struct FAudioVolumeInfo {

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

	FAudioVolumeInfo(){}
	FAudioVolumeInfo(const agora::rtc::AudioVolumeInfo & AgoraData){
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
struct FLastmileProbeResult {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	ELASTMILE_PROBE_RESULT_STATE state = ELASTMILE_PROBE_RESULT_STATE::LASTMILE_PROBE_RESULT_UNAVAILABLE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	FLastmileProbeOneWayResult uplinkReport = FLastmileProbeOneWayResult();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	FLastmileProbeOneWayResult downlinkReport = FLastmileProbeOneWayResult();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult")
	int64 rtt = 0;

	FLastmileProbeResult(){}
	FLastmileProbeResult(const agora::rtc::LastmileProbeResult & AgoraData){
		state = static_cast<ELASTMILE_PROBE_RESULT_STATE>(AgoraData.state);
		uplinkReport = FLastmileProbeOneWayResult(AgoraData.uplinkReport);
		downlinkReport = FLastmileProbeOneWayResult(AgoraData.downlinkReport);
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
struct FRtcStats
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



	FRtcStats(){}
	FRtcStats(const agora::rtc::RtcStats & AgoraData){
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

		SET_UABT_DOUBLE_TO_FSTRING(this->cpuAppUsage, AgoraData.cpuAppUsage);
		SET_UABT_DOUBLE_TO_FSTRING(this->cpuTotalUsage, AgoraData.cpuTotalUsage);

		gatewayRtt = AgoraData.gatewayRtt;
		
		SET_UABT_DOUBLE_TO_FSTRING(this->memoryAppUsageRatio, AgoraData.memoryAppUsageRatio);
		SET_UABT_DOUBLE_TO_FSTRING(this->memoryTotalUsageRatio, AgoraData.memoryTotalUsageRatio);
		
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

		SET_UABT_FSTRING_TO_DOUBLE(AgoraData.cpuAppUsage, this->cpuAppUsage);
		SET_UABT_FSTRING_TO_DOUBLE(AgoraData.cpuTotalUsage, this->cpuTotalUsage);

		AgoraData.gatewayRtt = gatewayRtt;

		SET_UABT_FSTRING_TO_DOUBLE(AgoraData.memoryAppUsageRatio, this->memoryAppUsageRatio);
		SET_UABT_FSTRING_TO_DOUBLE(AgoraData.memoryTotalUsageRatio, this->memoryTotalUsageRatio);

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
struct FUplinkNetworkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UplinkNetworkInfo")
	int video_encoder_target_bitrate_bps = 0;

	FUplinkNetworkInfo(){}
	FUplinkNetworkInfo(const agora::rtc::UplinkNetworkInfo & AgoraData){
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


UENUM(BlueprintType)
enum class EREMOTE_VIDEO_DOWNSCALE_LEVEL : uint8 {

	REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_1,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_2,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_3,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_4,
};



UENUM(BlueprintType)
enum class EVIDEO_STREAM_TYPE : uint8 {
	VIDEO_STREAM_HIGH = 0,
	VIDEO_STREAM_LOW = 1,
};



USTRUCT(BlueprintType)
struct FPeerDownlinkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	FString userId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	EVIDEO_STREAM_TYPE stream_type = EVIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	EREMOTE_VIDEO_DOWNSCALE_LEVEL current_downscale_level = EREMOTE_VIDEO_DOWNSCALE_LEVEL::REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|PeerDownlinkInfo")
	int expected_bitrate_bps = 0;

	FPeerDownlinkInfo(){}
	FPeerDownlinkInfo(const agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo & AgoraData){
		userId = UTF8_TO_TCHAR(AgoraData.userId);
		stream_type = static_cast<EVIDEO_STREAM_TYPE>(AgoraData.stream_type);
		current_downscale_level = static_cast<EREMOTE_VIDEO_DOWNSCALE_LEVEL>(AgoraData.current_downscale_level);
		expected_bitrate_bps = AgoraData.expected_bitrate_bps;
	}

	agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo CreateAgoraData() const {
		agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.userId,this->userId)
		AgoraData.stream_type = static_cast<agora::rtc::VIDEO_STREAM_TYPE>(stream_type);
		AgoraData.current_downscale_level = static_cast<agora::rtc::REMOTE_VIDEO_DOWNSCALE_LEVEL>(current_downscale_level);
		AgoraData.expected_bitrate_bps = expected_bitrate_bps;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo & AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.userId)
	}
};


USTRUCT(BlueprintType)
struct FDownlinkNetworkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int lastmile_buffer_delay_time_ms = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int bandwidth_estimation_bps = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int total_downscale_level_count = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	TArray<FPeerDownlinkInfo> peer_downlink_info;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int total_received_video_count = -1;

	FDownlinkNetworkInfo(){}
	FDownlinkNetworkInfo(const agora::rtc::DownlinkNetworkInfo & AgoraData){
		lastmile_buffer_delay_time_ms = AgoraData.lastmile_buffer_delay_time_ms;
		bandwidth_estimation_bps = AgoraData.bandwidth_estimation_bps;
		total_downscale_level_count = AgoraData.total_downscale_level_count;
		for (int i = 0; i < total_received_video_count; ++i) {
			peer_downlink_info.Add(FPeerDownlinkInfo(AgoraData.peer_downlink_info[i]));
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
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.peer_downlink_info, total_received_video_count, FPeerDownlinkInfo)
	}
};



UENUM(BlueprintType)
enum class ELOCAL_VIDEO_STREAM_STATE : uint8 {

	LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,

	LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,

	LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,

	LOCAL_VIDEO_STREAM_STATE_FAILED = 3
};

UENUM(BlueprintType)
enum class ELOCAL_VIDEO_STREAM_REASON : uint8 {
	LOCAL_VIDEO_STREAM_REASON_OK = 0,
	LOCAL_VIDEO_STREAM_REASON_FAILURE = 1,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_NO_PERMISSION = 2,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_BUSY = 3,
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_FAILURE = 4,
	LOCAL_VIDEO_STREAM_REASON_CODEC_NOT_SUPPORT = 5,
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_INBACKGROUND = 6,
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_MULTIPLE_FOREGROUND_APPS = 7,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_NOT_FOUND = 8,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_DISCONNECTED = 9,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_INVALID_ID = 10,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_INTERRUPT = 14,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_FATAL_ERROR = 15,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_SYSTEM_PRESSURE = 101,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_MINIMIZED = 11,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_CLOSED = 12,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_OCCLUDED = 13,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_NOT_SUPPORTED = 20,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_FAILURE = 21,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_NO_PERMISSION = 22,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_AUTO_FALLBACK = 24,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_HIDDEN = 25,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_RECOVER_FROM_HIDDEN = 26,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_RECOVER_FROM_MINIMIZED = 27,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_PAUSED = 28,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_RESUMED = 29
};




UENUM(BlueprintType)
enum class EREMOTE_VIDEO_STATE : uint8 {

	REMOTE_VIDEO_STATE_STOPPED = 0,

	REMOTE_VIDEO_STATE_STARTING = 1,

	REMOTE_VIDEO_STATE_DECODING = 2,

	REMOTE_VIDEO_STATE_FROZEN = 3,

	REMOTE_VIDEO_STATE_FAILED = 4,
};

UENUM(BlueprintType)
enum class EREMOTE_VIDEO_STATE_REASON : uint8 {

	REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,

	REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,

	REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,

	REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,

	REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,

	REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,

	REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,

	REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,

	REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,

	REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9,

	REMOTE_VIDEO_STATE_REASON_VIDEO_STREAM_TYPE_CHANGE_TO_LOW = 10,

	REMOTE_VIDEO_STATE_REASON_VIDEO_STREAM_TYPE_CHANGE_TO_HIGH = 11,

	REMOTE_VIDEO_STATE_REASON_SDK_IN_BACKGROUND = 12,

	REMOTE_VIDEO_STATE_REASON_CODEC_NOT_SUPPORT = 13,
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_REMOTE_USER_STATE : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	USER_STATE_MUTE_AUDIO,
	USER_STATE_MUTE_VIDEO,
	USER_STATE_ENABLE_VIDEO,
	USER_STATE_ENABLE_LOCAL_VIDEO,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_REMOTE_USER_STATE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EENUMWRAP_REMOTE_USER_STATE")
	EENUMCUSTOM_REMOTE_USER_STATE ValueWrapper = EENUMCUSTOM_REMOTE_USER_STATE::USER_STATE_MUTE_AUDIO;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_4_ENTRIES(FENUMWRAP_REMOTE_USER_STATE, agora::rtc::REMOTE_USER_STATE, EENUMCUSTOM_REMOTE_USER_STATE,
			USER_STATE_MUTE_AUDIO,
			USER_STATE_MUTE_VIDEO,
			USER_STATE_ENABLE_VIDEO,
			USER_STATE_ENABLE_LOCAL_VIDEO)
};


USTRUCT(BlueprintType)
struct FLocalAudioStats
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

	FLocalAudioStats(){}
	FLocalAudioStats(const agora::rtc::LocalAudioStats & AgoraData){
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
struct FRemoteAudioStats
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

	FRemoteAudioStats(){}
	FRemoteAudioStats(const agora::rtc::RemoteAudioStats & AgoraData){
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


UENUM(BlueprintType)
enum class EQUALITY_ADAPT_INDICATION : uint8 {

	ADAPT_NONE = 0,

	ADAPT_UP_BANDWIDTH = 1,

	ADAPT_DOWN_BANDWIDTH = 2,
};

UENUM(BlueprintType)
enum class EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE : uint8 {

	CAPTURE_BRIGHTNESS_LEVEL_INVALID = 0,

	CAPTURE_BRIGHTNESS_LEVEL_NORMAL = 1,

	CAPTURE_BRIGHTNESS_LEVEL_BRIGHT = 2,

	CAPTURE_BRIGHTNESS_LEVEL_DARK = 3,
};



USTRUCT(BlueprintType)
struct FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE")
	EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE ValueWrapper = EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_4_ENTRIES(FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE, agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE, EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE,
	CAPTURE_BRIGHTNESS_LEVEL_INVALID, 
	CAPTURE_BRIGHTNESS_LEVEL_NORMAL, 
	CAPTURE_BRIGHTNESS_LEVEL_BRIGHT, 
	CAPTURE_BRIGHTNESS_LEVEL_DARK)
};

UENUM(BlueprintType)
enum class EVIDEO_CODEC_TYPE : uint8 {

	VIDEO_CODEC_NONE = 0,

	VIDEO_CODEC_VP8 = 1,

	VIDEO_CODEC_H264 = 2,

	VIDEO_CODEC_H265 = 3,

	VIDEO_CODEC_GENERIC = 6,

	VIDEO_CODEC_GENERIC_H264 = 7,

	VIDEO_CODEC_AV1 = 12,

	VIDEO_CODEC_VP9 = 13,

	VIDEO_CODEC_GENERIC_JPEG = 20,
};

USTRUCT(BlueprintType)
struct FLocalVideoStats
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
	EQUALITY_ADAPT_INDICATION qualityAdaptIndication = EQUALITY_ADAPT_INDICATION::ADAPT_NONE;
	int encodedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	EVIDEO_CODEC_TYPE codecType = EVIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int txPacketLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE  captureBrightnessLevel = EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	bool dualStreamEnabled = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int hwEncoderAccelerating = 0;


	FLocalVideoStats(){}
	FLocalVideoStats(const agora::rtc::LocalVideoStats & AgoraData){
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
		qualityAdaptIndication = static_cast<EQUALITY_ADAPT_INDICATION>(AgoraData.qualityAdaptIndication);
		encodedBitrate = AgoraData.encodedBitrate;
		encodedFrameCount = AgoraData.encodedFrameCount;
		codecType = static_cast<EVIDEO_CODEC_TYPE>(AgoraData.codecType);
		txPacketLossRate = AgoraData.txPacketLossRate;
		captureBrightnessLevel = FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE(AgoraData.captureBrightnessLevel);
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
		AgoraData.captureBrightnessLevel = captureBrightnessLevel.GetRawValue();
		AgoraData.dualStreamEnabled = dualStreamEnabled;
		AgoraData.hwEncoderAccelerating = hwEncoderAccelerating;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::LocalVideoStats & AgoraData) const
	{

	}
};



USTRUCT(BlueprintType)
struct FRemoteVideoStats {

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
	EVIDEO_STREAM_TYPE rxStreamType = EVIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
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


	FRemoteVideoStats(){}
	FRemoteVideoStats(const agora::rtc::RemoteVideoStats & AgoraData){
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
		rxStreamType = static_cast<EVIDEO_STREAM_TYPE>(AgoraData.rxStreamType);
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


UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	AUDIO_MIXING_STATE_PLAYING = 1,

	AUDIO_MIXING_STATE_PAUSED = 2,

	AUDIO_MIXING_STATE_STOPPED = 3,

	AUDIO_MIXING_STATE_FAILED = 4,
};


USTRUCT(BlueprintType)
struct FENUMWRAP_AUDIO_MIXING_STATE_TYPE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value   
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AUDIO_MIXING_STATE_TYPE")
	EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_4_ENTRIES(FENUMWRAP_AUDIO_MIXING_STATE_TYPE, agora::rtc::AUDIO_MIXING_STATE_TYPE, EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE,
		AUDIO_MIXING_STATE_PLAYING,
		AUDIO_MIXING_STATE_PAUSED,
		AUDIO_MIXING_STATE_STOPPED,
		AUDIO_MIXING_STATE_FAILED)
};

UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE : uint8 {

	AUDIO_MIXING_REASON_OK = 0,

	AUDIO_MIXING_REASON_CAN_NOT_OPEN = 1,

	AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 2,

	AUDIO_MIXING_REASON_INTERRUPTED_EOF = 3,

	AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 4,

	AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 5,

	AUDIO_MIXING_REASON_STOPPED_BY_USER = 6,

};

USTRUCT(BlueprintType)
struct FENUMWRAP_AUDIO_MIXING_REASON_TYPE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AUDIO_MIXING_REASON_TYPE")
	EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_7_ENTRIES(FENUMWRAP_AUDIO_MIXING_REASON_TYPE, agora::rtc::AUDIO_MIXING_REASON_TYPE, EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE,
		AUDIO_MIXING_REASON_OK,
		AUDIO_MIXING_REASON_CAN_NOT_OPEN,
		AUDIO_MIXING_REASON_TOO_FREQUENT_CALL,
		AUDIO_MIXING_REASON_INTERRUPTED_EOF,
		AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED,
		AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED,
		AUDIO_MIXING_REASON_STOPPED_BY_USER)
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	RHYTHM_PLAYER_STATE_IDLE = 1,

	RHYTHM_PLAYER_STATE_OPENING,

	RHYTHM_PLAYER_STATE_DECODING,

	RHYTHM_PLAYER_STATE_PLAYING,

	RHYTHM_PLAYER_STATE_FAILED,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE")
	EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_5_ENTRIES(FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE, agora::rtc::RHYTHM_PLAYER_STATE_TYPE, EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE,
		RHYTHM_PLAYER_STATE_IDLE,
		RHYTHM_PLAYER_STATE_OPENING,
		RHYTHM_PLAYER_STATE_DECODING,
		RHYTHM_PLAYER_STATE_PLAYING,
		RHYTHM_PLAYER_STATE_FAILED)
};

UENUM(BlueprintType)
enum class EENUMCUSTOM_RHYTHM_PLAYER_REASON :uint8 {

	RHYTHM_PLAYER_REASON_OK = 0,

	RHYTHM_PLAYER_REASON_FAILED = 1,

	RHYTHM_PLAYER_REASON_CAN_NOT_OPEN,

	RHYTHM_PLAYER_REASON_CAN_NOT_PLAY,

	RHYTHM_PLAYER_REASON_FILE_OVER_DURATION_LIMIT,
};


USTRUCT(BlueprintType)
struct FENUMWRAP_RHYTHM_PLAYER_REASON
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_RHYTHM_PLAYER_ERROR_TYPE")
	EENUMCUSTOM_RHYTHM_PLAYER_REASON ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_REASON::RHYTHM_PLAYER_REASON_OK;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_5_ENTRIES(FENUMWRAP_RHYTHM_PLAYER_REASON, agora::rtc::RHYTHM_PLAYER_REASON, EENUMCUSTOM_RHYTHM_PLAYER_REASON,
		RHYTHM_PLAYER_REASON_OK,
		RHYTHM_PLAYER_REASON_FAILED,
		RHYTHM_PLAYER_REASON_CAN_NOT_OPEN,
		RHYTHM_PLAYER_REASON_CAN_NOT_PLAY,
		RHYTHM_PLAYER_REASON_FILE_OVER_DURATION_LIMIT)
};


UENUM(BlueprintType)
enum class ELICENSE_ERROR_TYPE : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	LICENSE_ERR_INVALID = 1,

	LICENSE_ERR_EXPIRE = 2,

	LICENSE_ERR_MINUTES_EXCEED = 3,

	LICENSE_ERR_LIMITED_PERIOD = 4,

	LICENSE_ERR_DIFF_DEVICES = 5,

	LICENSE_ERR_INTERNAL = 99,
};



UENUM(BlueprintType)
enum class ELOCAL_AUDIO_STREAM_STATE : uint8 {

	LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,

	LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,

	LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,

	LOCAL_AUDIO_STREAM_STATE_FAILED = 3
};

UENUM(BlueprintType)
enum class ELOCAL_AUDIO_STREAM_REASON : uint8 {

	LOCAL_AUDIO_STREAM_REASON_OK = 0,
	LOCAL_AUDIO_STREAM_REASON_FAILURE = 1,
	LOCAL_AUDIO_STREAM_REASON_DEVICE_NO_PERMISSION = 2,
	LOCAL_AUDIO_STREAM_REASON_DEVICE_BUSY = 3,
	LOCAL_AUDIO_STREAM_REASON_RECORD_FAILURE = 4,
	LOCAL_AUDIO_STREAM_REASON_ENCODE_FAILURE = 5,
	LOCAL_AUDIO_STREAM_REASON_NO_RECORDING_DEVICE = 6,
	LOCAL_AUDIO_STREAM_REASON_NO_PLAYOUT_DEVICE = 7,
	LOCAL_AUDIO_STREAM_REASON_INTERRUPTED = 8,
	LOCAL_AUDIO_STREAM_REASON_RECORD_INVALID_ID = 9,
	LOCAL_AUDIO_STREAM_REASON_PLAYOUT_INVALID_ID = 10,
};


UENUM(BlueprintType)
enum class EREMOTE_AUDIO_STATE : uint8
{

	REMOTE_AUDIO_STATE_STOPPED = 0,

	REMOTE_AUDIO_STATE_STARTING = 1,

	REMOTE_AUDIO_STATE_DECODING = 2,

	REMOTE_AUDIO_STATE_FROZEN = 3,

	REMOTE_AUDIO_STATE_FAILED = 4,
};

UENUM(BlueprintType)
enum class EREMOTE_AUDIO_STATE_REASON : uint8
{
	REMOTE_AUDIO_REASON_INTERNAL = 0,

	REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,

	REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,

	REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,

	REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,

	REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,

	REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,

	REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,

	REMOTE_AUDIO_REASON_NO_PACKET_RECEIVE = 8,
	
	REMOTE_AUDIO_REASON_LOCAL_PLAY_FAILED = 9,

};


UENUM(BlueprintType)
enum class ECONTENT_INSPECT_RESULT : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	CONTENT_INSPECT_NEUTRAL = 1,
	CONTENT_INSPECT_SEXY = 2,
	CONTENT_INSPECT_PORN = 3,
};

UENUM(BlueprintType)
enum class ECLIENT_ROLE_CHANGE_FAILED_REASON : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	CLIENT_ROLE_CHANGE_FAILED_TOO_MANY_BROADCASTERS = 1,

	CLIENT_ROLE_CHANGE_FAILED_NOT_AUTHORIZED = 2,

	CLIENT_ROLE_CHANGE_FAILED_REQUEST_TIME_OUT = 3,

	CLIENT_ROLE_CHANGE_FAILED_CONNECTION_FAILED = 4,
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_MEDIA_DEVICE_TYPE : uint8 {

	UNKNOWN_AUDIO_DEVICE = 0,

	AUDIO_PLAYOUT_DEVICE = 1,

	AUDIO_RECORDING_DEVICE = 2,

	VIDEO_RENDER_DEVICE = 3,

	VIDEO_CAPTURE_DEVICE = 4,

	AUDIO_APPLICATION_PLAYOUT_DEVICE = 5,

	AUDIO_VIRTUAL_PLAYOUT_DEVICE = 6,

	AUDIO_VIRTUAL_RECORDING_DEVICE = 7,
};



USTRUCT(BlueprintType)
struct FENUMWRAP_MEDIA_DEVICE_TYPE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_MEDIA_DEVICE_TYPE")
	EENUMCUSTOM_MEDIA_DEVICE_TYPE ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE;



	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_8_ENTRIES(FENUMWRAP_MEDIA_DEVICE_TYPE, agora::rtc::MEDIA_DEVICE_TYPE, EENUMCUSTOM_MEDIA_DEVICE_TYPE,
		UNKNOWN_AUDIO_DEVICE,
		AUDIO_PLAYOUT_DEVICE,
		AUDIO_RECORDING_DEVICE,
		VIDEO_RENDER_DEVICE,
		VIDEO_CAPTURE_DEVICE,
		AUDIO_APPLICATION_PLAYOUT_DEVICE,
		AUDIO_VIRTUAL_PLAYOUT_DEVICE,
		AUDIO_VIRTUAL_RECORDING_DEVICE)

	
};



UENUM(BlueprintType)
enum class ERTMP_STREAM_PUBLISH_STATE : uint8 {

	RTMP_STREAM_PUBLISH_STATE_IDLE = 0,

	RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,

	RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,

	RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,

	RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,

	RTMP_STREAM_PUBLISH_STATE_DISCONNECTING = 5,
};

UENUM(BlueprintType)
enum class ERTMP_STREAM_PUBLISH_REASON : uint8 {

	RTMP_STREAM_PUBLISH_REASON_OK = 0,

	RTMP_STREAM_PUBLISH_REASON_INVALID_ARGUMENT = 1,

	RTMP_STREAM_PUBLISH_REASON_ENCRYPTED_STREAM_NOT_ALLOWED = 2,

	RTMP_STREAM_PUBLISH_REASON_CONNECTION_TIMEOUT = 3,

	RTMP_STREAM_PUBLISH_REASON_INTERNAL_SERVER_ERROR = 4,

	RTMP_STREAM_PUBLISH_REASON_RTMP_SERVER_ERROR = 5,

	RTMP_STREAM_PUBLISH_REASON_TOO_OFTEN = 6,

	RTMP_STREAM_PUBLISH_REASON_REACH_LIMIT = 7,

	RTMP_STREAM_PUBLISH_REASON_NOT_AUTHORIZED = 8,

	RTMP_STREAM_PUBLISH_REASON_STREAM_NOT_FOUND = 9,

	RTMP_STREAM_PUBLISH_REASON_FORMAT_NOT_SUPPORTED = 10,

	RTMP_STREAM_PUBLISH_REASON_NOT_BROADCASTER = 11,

	RTMP_STREAM_PUBLISH_REASON_TRANSCODING_NO_MIX_STREAM = 13,

	RTMP_STREAM_PUBLISH_REASON_NET_DOWN = 14,

	RTMP_STREAM_PUBLISH_REASON_INVALID_APPID = 15,

	RTMP_STREAM_PUBLISH_REASON_INVALID_PRIVILEGE = 16,

	RTMP_STREAM_UNPUBLISH_REASON_OK = 100,
};


UENUM(BlueprintType)
enum class ERTMP_STREAMING_EVENT : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	RTMP_STREAMING_EVENT_FAILED_LOAD_IMAGE = 1,

	RTMP_STREAMING_EVENT_URL_ALREADY_IN_USE = 2,

	RTMP_STREAMING_EVENT_ADVANCED_FEATURE_NOT_SUPPORT = 3,

	RTMP_STREAMING_EVENT_REQUEST_TOO_OFTEN = 4,
};


UENUM(BlueprintType)
enum class ECONNECTION_STATE_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL = 0,
	CONNECTION_STATE_DISCONNECTED = 1,
	CONNECTION_STATE_CONNECTING = 2,
	CONNECTION_STATE_CONNECTED = 3,
	CONNECTION_STATE_RECONNECTING = 4,
	CONNECTION_STATE_FAILED = 5,
};


UENUM(BlueprintType)
enum class ECONNECTION_CHANGED_REASON_TYPE : uint8
{
	CONNECTION_CHANGED_CONNECTING = 0,

	CONNECTION_CHANGED_JOIN_SUCCESS = 1,

	CONNECTION_CHANGED_INTERRUPTED = 2,

	CONNECTION_CHANGED_BANNED_BY_SERVER = 3,

	CONNECTION_CHANGED_JOIN_FAILED = 4,

	CONNECTION_CHANGED_LEAVE_CHANNEL = 5,

	CONNECTION_CHANGED_INVALID_APP_ID = 6,

	CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,

	CONNECTION_CHANGED_INVALID_TOKEN = 8,

	CONNECTION_CHANGED_TOKEN_EXPIRED = 9,

	CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,

	CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,

	CONNECTION_CHANGED_RENEW_TOKEN = 12,

	CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,

	CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,

	CONNECTION_CHANGED_REJOIN_SUCCESS = 15,

	CONNECTION_CHANGED_LOST = 16,

	CONNECTION_CHANGED_ECHO_TEST = 17,

	CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED_BY_USER = 18,

	CONNECTION_CHANGED_SAME_UID_LOGIN = 19,

	CONNECTION_CHANGED_TOO_MANY_BROADCASTERS = 20,

	CONNECTION_CHANGED_LICENSE_VERIFY_FAILED = 21,

	CONNECTION_CHANGED_CERTIFICATION_VERYFY_FAILURE = 22,

	CONNECTION_CHANGED_STREAM_CHANNEL_NOT_AVAILABLE = 23,

	CONNECTION_CHANGED_INCONSISTENT_APPID = 24

};


UENUM(BlueprintType)
enum class EWLACC_MESSAGE_REASON : uint8 {

	WLACC_MESSAGE_REASON_WEAK_SIGNAL = 0,

	WLACC_MESSAGE_REASON_CHANNEL_CONGESTION = 1,
};

UENUM(BlueprintType)
enum class EWLACC_SUGGEST_ACTION : uint8 {

	WLACC_SUGGEST_ACTION_CLOSE_TO_WIFI = 0,

	WLACC_SUGGEST_ACTION_CONNECT_SSID = 1,

	WLACC_SUGGEST_ACTION_CHECK_5G = 2,

	WLACC_SUGGEST_ACTION_MODIFY_SSID = 3,
};


USTRUCT(BlueprintType)
struct FWlAccStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 e2eDelayPercent = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 frozenRatioPercent = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 lossRatePercent = 0;

	FWlAccStats(){}
	FWlAccStats(const agora::rtc::WlAccStats & AgoraData){
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


UENUM(BlueprintType)
enum class EENUMCUSTOM_NETWORK_TYPE : uint8 {

	NETWORK_TYPE_UNKNOWN = 0,

	NETWORK_TYPE_DISCONNECTED = 1,

	NETWORK_TYPE_LAN = 2,

	NETWORK_TYPE_WIFI = 3,

	NETWORK_TYPE_MOBILE_2G = 4,

	NETWORK_TYPE_MOBILE_3G = 5,

	NETWORK_TYPE_MOBILE_4G = 6,

	NETWORK_TYPE_MOBILE_5G = 7

};


USTRUCT(BlueprintType)
struct FENUMWRAP_NETWORK_TYPE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_NETWORK_TYPE")
	EENUMCUSTOM_NETWORK_TYPE ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_UNKNOWN;
	
	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_8_ENTRIES(FENUMWRAP_NETWORK_TYPE, agora::rtc::NETWORK_TYPE, EENUMCUSTOM_NETWORK_TYPE,
		NETWORK_TYPE_UNKNOWN,
		NETWORK_TYPE_DISCONNECTED,
		NETWORK_TYPE_LAN,
		NETWORK_TYPE_WIFI,
		NETWORK_TYPE_MOBILE_2G,
		NETWORK_TYPE_MOBILE_3G,
		NETWORK_TYPE_MOBILE_4G,
		NETWORK_TYPE_MOBILE_5G)
};


UENUM(BlueprintType)
enum class EENCRYPTION_ERROR_TYPE : uint8 {
	ENCRYPTION_ERROR_INTERNAL_FAILURE = 0,
	ENCRYPTION_ERROR_DECRYPTION_FAILURE = 1,
	ENCRYPTION_ERROR_ENCRYPTION_FAILURE = 2,
	ENCRYPTION_ERROR_DATASTREAM_DECRYPTION_FAILURE = 3,
	ENCRYPTION_ERROR_DATASTREAM_ENCRYPTION_FAILURE = 4,

};


UENUM(BlueprintType)
enum class EPERMISSION_TYPE : uint8 {
	RECORD_AUDIO = 0,
	CAMERA = 1,
	SCREEN_CAPTURE = 2,
};


USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString userAccount = "";

	FUserInfo(){}
	FUserInfo(const agora::rtc::UserInfo & AgoraData){
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

UENUM(BlueprintType)
enum class EMEDIA_TRACE_EVENT : uint8 {

	MEDIA_TRACE_EVENT_VIDEO_RENDERED = 0,

	MEDIA_TRACE_EVENT_VIDEO_DECODED = 1,
};



USTRUCT(BlueprintType)
struct FVideoRenderingTracingInfo {

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

	FVideoRenderingTracingInfo() {}
	FVideoRenderingTracingInfo(const agora::rtc::VideoRenderingTracingInfo& AgoraData) {
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
struct FTranscodingVideoStream {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
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

	FTranscodingVideoStream(){}
	FTranscodingVideoStream(const agora::rtc::TranscodingVideoStream & AgoraData){
		sourceType = static_cast<EVIDEO_SOURCE_TYPE>(AgoraData.sourceType);
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.imageUrl)
	}
};


UENUM(BlueprintType)
enum class EVIDEO_TRANSCODER_ERROR : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	VT_ERR_VIDEO_SOURCE_NOT_READY = 1,
	VT_ERR_INVALID_VIDEO_SOURCE_TYPE = 2,
	VT_ERR_INVALID_IMAGE_PATH = 3,
	VT_ERR_UNSUPPORT_IMAGE_FORMAT = 4,
	VT_ERR_INVALID_LAYOUT = 5,
	VT_ERR_INTERNAL = 20

};

UENUM(BlueprintType)
enum class EUPLOAD_ERROR_REASON : uint8
{
	UPLOAD_SUCCESS = 0,
	UPLOAD_NET_ERROR = 1,
	UPLOAD_SERVER_ERROR = 2,
};

UENUM(BlueprintType)
enum class ESTREAM_SUBSCRIBE_STATE : uint8 {
	SUB_STATE_IDLE = 0,
	SUB_STATE_NO_SUBSCRIBED = 1,
	SUB_STATE_SUBSCRIBING = 2,
	SUB_STATE_SUBSCRIBED = 3
};

UENUM(BlueprintType)
enum class ESTREAM_PUBLISH_STATE : uint8 {
	PUB_STATE_IDLE = 0,
	PUB_STATE_NO_PUBLISHED = 1,
	PUB_STATE_PUBLISHING = 2,
	PUB_STATE_PUBLISHED = 3
};



USTRUCT(BlueprintType)
struct FVideoLayout
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	FString channelId = "";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	int64 uid = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	FString strUid = "";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	int64 x = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	int64 y = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	int64 width = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	int64 height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoLayout")
	int64 videoState = 0;

	FVideoLayout(){}
	FVideoLayout(const agora::VideoLayout & AgoraData){
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.channelId, channelId)
		AgoraData.uid = uid;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.strUid, strUid)
		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.videoState = videoState;
		return AgoraData;
	}

	void FreeAgoraData(agora::VideoLayout & AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.channelId)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.strUid)
	}
};


USTRUCT(BlueprintType)
struct FAgoraMetadata
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

	FAgoraMetadata(){}
	FAgoraMetadata(const agora::rtc::IMetadataObserver::Metadata & AgoraData){
		uid = AgoraData.uid;
		size = AgoraData.size;
		buffer = UTF8_TO_TCHAR(AgoraData.buffer);
		timeStampMs = AgoraData.timeStampMs;
	}

	agora::rtc::IMetadataObserver::Metadata CreateAgoraData() const {
		agora::rtc::IMetadataObserver::Metadata AgoraData;
		AgoraData.uid = uid;
		AgoraData.size = size;
		SET_UABT_FSTRING_TO_UNSIGNED_CHAR___MEMALLOC(AgoraData.buffer,this->buffer)
		AgoraData.timeStampMs = timeStampMs;
		return AgoraData;
	}
	void FreeAgoraData (agora::rtc::IMetadataObserver::Metadata& AgoraData){
		SET_UABT_FSTRING_TO_UNSIGNED_CHAR___MEMFREE(AgoraData.buffer)
	}
};


UENUM(BlueprintType)
enum class EDIRECT_CDN_STREAMING_STATE : uint8 {

	DIRECT_CDN_STREAMING_STATE_IDLE = 0,

	DIRECT_CDN_STREAMING_STATE_RUNNING = 1,

	DIRECT_CDN_STREAMING_STATE_STOPPED = 2,

	DIRECT_CDN_STREAMING_STATE_FAILED = 3,

	DIRECT_CDN_STREAMING_STATE_RECOVERING = 4,
};

UENUM(BlueprintType)
enum class EDIRECT_CDN_STREAMING_REASON : uint8 {

	DIRECT_CDN_STREAMING_REASON_OK = 0,

	DIRECT_CDN_STREAMING_REASON_FAILED = 1,

	DIRECT_CDN_STREAMING_REASON_AUDIO_PUBLICATION = 2,

	DIRECT_CDN_STREAMING_REASON_VIDEO_PUBLICATION = 3,

	DIRECT_CDN_STREAMING_REASON_NET_CONNECT = 4,

	DIRECT_CDN_STREAMING_REASON_BAD_NAME = 5,
};


USTRUCT(BlueprintType)
struct FDirectCdnStreamingStats {

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

	FDirectCdnStreamingStats(){}
	FDirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats & AgoraData){
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


UENUM(BlueprintType)
enum class EUSER_OFFLINE_REASON_TYPE : uint8 {

	USER_OFFLINE_QUIT = 0,

	USER_OFFLINE_DROPPED = 1,

	USER_OFFLINE_BECOME_AUDIENCE = 2,
};


USTRUCT(BlueprintType)
struct FExtensionContext {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	bool isValid = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	FString providerName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionContext")
	FString extensionName = "";

	FExtensionContext(){}
	FExtensionContext(const agora::rtc::ExtensionContext& AgoraData){
		isValid = AgoraData.isValid;
		uid = AgoraData.uid;
		providerName = UTF8_TO_TCHAR(AgoraData.providerName);
		extensionName = UTF8_TO_TCHAR(AgoraData.extensionName);
	}

	agora::rtc::ExtensionContext CreateAgoraData() const {
		agora::rtc::ExtensionContext AgoraData;
		AgoraData.isValid = isValid;
		AgoraData.uid = uid;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.providerName, providerName)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.extensionName, extensionName)
		return AgoraData;
	}
	void FreeAgoraData(agora::rtc::ExtensionContext& AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.providerName)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.extensionName)
	}
};


#pragma endregion EventHandler


#pragma region MediaPlayer
UENUM(BlueprintType)
enum class EMEDIA_PLAYER_STATE : uint8 {
	PLAYER_STATE_IDLE = 0,
	PLAYER_STATE_OPENING,
	PLAYER_STATE_OPEN_COMPLETED,
	PLAYER_STATE_PLAYING,
	PLAYER_STATE_PAUSED,
	PLAYER_STATE_PLAYBACK_COMPLETED,
	PLAYER_STATE_PLAYBACK_ALL_LOOPS_COMPLETED,
	PLAYER_STATE_STOPPED,
	PLAYER_STATE_PAUSING_INTERNAL = 50,
	PLAYER_STATE_STOPPING_INTERNAL,
	PLAYER_STATE_SEEKING_INTERNAL,
	PLAYER_STATE_GETTING_INTERNAL,
	PLAYER_STATE_NONE_INTERNAL,
	PLAYER_STATE_DO_NOTHING_INTERNAL,
	PLAYER_STATE_SET_TRACK_INTERNAL,
	PLAYER_STATE_FAILED = 100,
};

#pragma endregion MediaPlayer

#pragma region Rtc Engine


UENUM(BlueprintType)
enum class EENCRYPTION_MODE :uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	AES_128_XTS = 1,

	AES_128_ECB = 2,

	AES_256_XTS = 3,

	SM4_128_ECB = 4,

	AES_128_GCM = 5,

	AES_256_GCM = 6,

	AES_128_GCM2 = 7,

	AES_256_GCM2 = 8,

	MODE_END,
};

USTRUCT(BlueprintType)
struct FEncryptionConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	EENCRYPTION_MODE encryptionMode = EENCRYPTION_MODE::AES_128_GCM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	FString encryptionKey = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	FString encryptionKdfSalt = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	bool datastreamEncryptionEnabled = false;

	FEncryptionConfig(){}
	FEncryptionConfig(const agora::rtc::EncryptionConfig & AgoraData){
		encryptionMode = static_cast<EENCRYPTION_MODE>(AgoraData.encryptionMode);
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.encryptionKey,this->encryptionKey)


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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.encryptionKey)
	}
};

#pragma endregion Rtc Engine


UENUM(BlueprintType)
enum class ECLIENT_ROLE_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	CLIENT_ROLE_BROADCASTER = 1,
	CLIENT_ROLE_AUDIENCE = 2,
};


UENUM(BlueprintType)
enum class ECHANNEL_PROFILE_TYPE : uint8 {
	CHANNEL_PROFILE_COMMUNICATION = 0,
	CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
	CHANNEL_PROFILE_GAME = 2,
	CHANNEL_PROFILE_CLOUD_GAMING = 3,
	CHANNEL_PROFILE_COMMUNICATION_1v1 = 4,
};


UENUM(BlueprintType)
enum class EAUDIENCE_LATENCY_LEVEL_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	AUDIENCE_LATENCY_LEVEL_LOW_LATENCY = 1,
	AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY = 2,
};


USTRUCT(BlueprintType)
struct FClientRoleOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ClientRoleOptions")
	EAUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel = EAUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY;

	FClientRoleOptions() {}

	FClientRoleOptions(const agora::rtc::ClientRoleOptions& AgoraData) {
		audienceLatencyLevel = static_cast<EAUDIENCE_LATENCY_LEVEL_TYPE>(AgoraData.audienceLatencyLevel);
	}

	agora::rtc::ClientRoleOptions CreateAgoraData() const {
		agora::rtc::ClientRoleOptions AgoraData;
		AgoraData.audienceLatencyLevel = static_cast<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>(audienceLatencyLevel);
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ClientRoleOptions& AgoraData) const {

	}
};



UENUM(BlueprintType)
enum class EEXTERNAL_VIDEO_SOURCE_TYPE :uint8 {
	/**
	 * 0: non-encoded video frame.
	 */
	VIDEO_FRAME = 0,
	/**
	 * 1: encoded video frame.
	 */
	ENCODED_VIDEO_FRAME,
};

UENUM(BlueprintType)
enum class ETCcMode :uint8 {

	CC_ENABLED,

	CC_DISABLED,
};


USTRUCT(BlueprintType)
struct FSenderOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	ETCcMode ccMode = ETCcMode::CC_ENABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	EVIDEO_CODEC_TYPE codecType = EVIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
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



UENUM(BlueprintType)
enum class ERENDER_MODE_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	RENDER_MODE_HIDDEN = 1,
	RENDER_MODE_FIT = 2,
	RENDER_MODE_ADAPTIVE = 3,
};

UENUM(BlueprintType)
enum class EVIDEO_MIRROR_MODE_TYPE : uint8 {
	VIDEO_MIRROR_MODE_AUTO = 0,
	VIDEO_MIRROR_MODE_ENABLED = 1,
	VIDEO_MIRROR_MODE_DISABLED = 2,
};



USTRUCT(BlueprintType)
struct FRectangle
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

	FRectangle(){}
	FRectangle(const agora::rtc::Rectangle & AgoraData){
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


UENUM(BlueprintType)
enum class EVIDEO_VIEW_SETUP_MODE : uint8 {

	VIDEO_VIEW_SETUP_REPLACE = 0,

	VIDEO_VIEW_SETUP_ADD = 1,

	VIDEO_VIEW_SETUP_REMOVE = 2,
};


UENUM(BlueprintType)
enum class EVIDEO_MODULE_POSITION :uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	POSITION_POST_CAPTURER = 1 << 0,
	POSITION_PRE_RENDERER = 1 << 1,
	POSITION_PRE_ENCODER = 1 << 2,
	POSITION_POST_CAPTURER_ORIGIN = 1 << 3,
};


USTRUCT(BlueprintType)
struct FVideoCanvas
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
	ERENDER_MODE_TYPE renderMode = ERENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_MIRROR_MODE_TYPE mirrorMode = EVIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_VIEW_SETUP_MODE setupMode = EVIDEO_VIEW_SETUP_MODE::VIDEO_VIEW_SETUP_REPLACE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int mediaPlayerId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	FRectangle cropArea;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	bool enableAlphaMask = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_MODULE_POSITION position = EVIDEO_MODULE_POSITION::POSITION_POST_CAPTURER;


	FVideoCanvas(){}
	FVideoCanvas(const agora::rtc::VideoCanvas & AgoraData){
		view = nullptr; // [not support]
		uid = AgoraData.uid;
		subviewUid = AgoraData.subviewUid;
		backgroundColor = AgoraData.backgroundColor;
		renderMode = static_cast<ERENDER_MODE_TYPE>(AgoraData.renderMode);
		mirrorMode = static_cast<EVIDEO_MIRROR_MODE_TYPE>(AgoraData.mirrorMode);
		setupMode = static_cast<EVIDEO_VIEW_SETUP_MODE>(AgoraData.setupMode);
		sourceType = static_cast<EVIDEO_SOURCE_TYPE>(AgoraData.sourceType);
		mediaPlayerId = AgoraData.mediaPlayerId;
		cropArea = FRectangle(AgoraData.cropArea);
		enableAlphaMask = AgoraData.enableAlphaMask;
		position = static_cast<EVIDEO_MODULE_POSITION>(AgoraData.position);
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


UENUM(BlueprintType)
enum class EAUDIO_PROFILE_TYPE : uint8 {
	AUDIO_PROFILE_DEFAULT = 0,
	AUDIO_PROFILE_SPEECH_STANDARD = 1,
	AUDIO_PROFILE_MUSIC_STANDARD = 2,
	AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3,
	AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4,
	AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5,
	AUDIO_PROFILE_IOT = 6,
	AUDIO_PROFILE_NUM = 7,
};

UENUM(BlueprintType)
enum class EAUDIO_SCENARIO_TYPE : uint8 {
	AUDIO_SCENARIO_DEFAULT = 0,
	AUDIO_SCENARIO_GAME_STREAMING = 3,
	AUDIO_SCENARIO_CHATROOM = 5,
	AUDIO_SCENARIO_CHORUS = 7,
	AUDIO_SCENARIO_MEETING = 8,
	AUDIO_SCENARIO_NUM = 9,
};



UENUM(BlueprintType)
enum class ELOG_LEVEL : uint8 {
	LOG_LEVEL_NONE = 0x0000,
	LOG_LEVEL_INFO = 0x0001,
	LOG_LEVEL_WARN = 0x0002,
	LOG_LEVEL_ERROR = 0x0004,
	LOG_LEVEL_FATAL = 0x0008,
	LOG_LEVEL_API_CALL = 0x0010,
	LOG_LEVEL_DEBUG = 0x0020,
};




USTRUCT(BlueprintType)
struct FLogConfig {

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	FString filePath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	int64 fileSizeInKB = 2048;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	ELOG_LEVEL level = ELOG_LEVEL::LOG_LEVEL_INFO;

	FLogConfig() {}
	FLogConfig(const agora::commons::LogConfig& AgoraData) {
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		fileSizeInKB = AgoraData.fileSizeInKB;
		level = (ELOG_LEVEL)AgoraData.level;
	}

	agora::commons::LogConfig CreateAgoraData() const {
		agora::commons::LogConfig AgoraData;

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.filePath, filePath)
		AgoraData.fileSizeInKB = UABT::ToUInt32(fileSizeInKB);
		AgoraData.level = (agora::commons::LOG_LEVEL)level;
		return AgoraData;
	}

	void FreeAgoraData(agora::commons::LogConfig& AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.filePath)
	}
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_AREA_CODE : uint8 {

	INVALID_OPT_BPGEN_NULL = 0,

	AREA_CODE_CN = 1,

	AREA_CODE_NA = 2,

	AREA_CODE_EU = 3,

	AREA_CODE_AS = 4,

	AREA_CODE_JP = 5,

	AREA_CODE_IN = 6,

	AREA_CODE_GLOB = 255,
};


USTRUCT(BlueprintType)
struct FENUMWRAP_AREA_CODE
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AREA_CODE")
	EENUMCUSTOM_AREA_CODE ValueWrapper = EENUMCUSTOM_AREA_CODE::AREA_CODE_GLOB;


	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_7_ENTRIES(FENUMWRAP_AREA_CODE, agora::rtc::AREA_CODE, EENUMCUSTOM_AREA_CODE,
		AREA_CODE_GLOB,
		AREA_CODE_CN,
		AREA_CODE_NA,
		AREA_CODE_EU,
		AREA_CODE_AS,
		AREA_CODE_JP,
		AREA_CODE_IN)

};

USTRUCT(BlueprintType)
struct FRtcEngineContext
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
	ECHANNEL_PROFILE_TYPE channelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString license = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EAUDIO_SCENARIO_TYPE audioScenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT;
	

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FENUMWRAP_AREA_CODE areaCode = EENUMCUSTOM_AREA_CODE::AREA_CODE_GLOB;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FLogConfig logConfig;


	//// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool threadPriority_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	ETHREAD_PRIORITY_TYPE threadPriority = ETHREAD_PRIORITY_TYPE::NORMAL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool useExternalEglContext = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool domainLimit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool autoRegisterAgoraExtensions = true;


	FRtcEngineContext() {}

	agora::rtc::RtcEngineContext CreateAgoraData() const {

		agora::rtc::RtcEngineContext AgoraData;

		//AgoraData.eventHandler = static_cast<agora::rtc::IRtcEngineEventHandler*>(eventHandler);

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.appId, this->appId)

		//AgoraData.context = nullptr; // not supported

		AgoraData.channelProfile = (agora::CHANNEL_PROFILE_TYPE)channelProfile;
		
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.license, this->license)

		AgoraData.audioScenario = (agora::rtc::AUDIO_SCENARIO_TYPE)audioScenario;

		AgoraData.areaCode = areaCode.GetRawValue();

		AgoraData.logConfig = logConfig.CreateAgoraData();

		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.threadPriority, this->threadPriority, static_cast<agora::rtc::THREAD_PRIORITY_TYPE>(this->threadPriority))

		AgoraData.useExternalEglContext = useExternalEglContext;

		AgoraData.domainLimit = domainLimit;

		AgoraData.autoRegisterAgoraExtensions = autoRegisterAgoraExtensions;
		
		return AgoraData;
	}


	void FreeAgoraData(agora::rtc::RtcEngineContext& AgoraData) const {

		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.appId)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.license)
		logConfig.FreeAgoraData(AgoraData.logConfig);
	}
};

USTRUCT(BlueprintType)
struct FRtcConnection
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcConnection")
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcConnection")
	int64 localUid = 0;

	FRtcConnection(){}
	FRtcConnection(const agora::rtc::RtcConnection & AgoraData){
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		localUid = AgoraData.localUid;
	}

	agora::rtc::RtcConnection CreateAgoraData() const {
		agora::rtc::RtcConnection AgoraData;
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(AgoraData.channelId, this->channelId)
		AgoraData.localUid = localUid;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::RtcConnection & AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.channelId)
	}
	
};






#pragma region Rtc Engine 2
UENUM(BlueprintType)
enum class EENUMCUSTOM_VIDEO_CODEC_CAPABILITY_LEVEL : uint8{
	CODEC_CAPABILITY_LEVEL_UNSPECIFIED,
	CODEC_CAPABILITY_LEVEL_BASIC_SUPPORT,
	CODEC_CAPABILITY_LEVEL_1080P30FPS,
	CODEC_CAPABILITY_LEVEL_1080P60FPS,
	CODEC_CAPABILITY_LEVEL_4K60FPS
};

USTRUCT(BlueprintType)
struct FENUMWRAP_VIDEO_CODEC_CAPABILITY_LEVEL
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_VIDEO_CODEC_CAPABILITY_LEVEL")
	EENUMCUSTOM_VIDEO_CODEC_CAPABILITY_LEVEL ValueWrapper = EENUMCUSTOM_VIDEO_CODEC_CAPABILITY_LEVEL::CODEC_CAPABILITY_LEVEL_UNSPECIFIED;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_5_ENTRIES(FENUMWRAP_VIDEO_CODEC_CAPABILITY_LEVEL, agora::rtc::VIDEO_CODEC_CAPABILITY_LEVEL, EENUMCUSTOM_VIDEO_CODEC_CAPABILITY_LEVEL,
		CODEC_CAPABILITY_LEVEL_UNSPECIFIED,
		CODEC_CAPABILITY_LEVEL_BASIC_SUPPORT,
		CODEC_CAPABILITY_LEVEL_1080P30FPS,
		CODEC_CAPABILITY_LEVEL_1080P60FPS,
		CODEC_CAPABILITY_LEVEL_4K60FPS)
};

USTRUCT(BlueprintType)
struct FCodecCapLevels {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FCodecCapLevels")
	FENUMWRAP_VIDEO_CODEC_CAPABILITY_LEVEL hwDecodingLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FCodecCapLevels")
	FENUMWRAP_VIDEO_CODEC_CAPABILITY_LEVEL swDecodingLevel;
	
	FCodecCapLevels() {}
	FCodecCapLevels(const agora::rtc::CodecCapLevels& AgoraData) {
		hwDecodingLevel = AgoraData.hwDecodingLevel;
		swDecodingLevel = AgoraData.swDecodingLevel;
	}

	agora::rtc::CodecCapLevels CreateAgoraData() const {
		agora::rtc::CodecCapLevels AgoraData;
		AgoraData.hwDecodingLevel = hwDecodingLevel.GetRawValue();
		AgoraData.swDecodingLevel = swDecodingLevel.GetRawValue();
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::CodecCapLevels& AgoraData) const {
		// no need to free
	}
};

USTRUCT(BlueprintType)
struct FCodecCapInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	EVIDEO_CODEC_TYPE codecType = EVIDEO_CODEC_TYPE::VIDEO_CODEC_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	int codecCapMask = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	FCodecCapLevels codecLevels;

	FCodecCapInfo(){}
	FCodecCapInfo(const agora::rtc::CodecCapInfo & AgoraData){
		codecType = static_cast<EVIDEO_CODEC_TYPE>(AgoraData.codecType);
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
struct FChannelMediaOptions
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
	ECLIENT_ROLE_TYPE clientRoleType = ECLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool audienceLatencyLevel_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel = EAUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_LOW_LATENCY;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool defaultVideoStreamType_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EVIDEO_STREAM_TYPE defaultVideoStreamType = EVIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool channelProfile_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	ECHANNEL_PROFILE_TYPE channelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
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


	FChannelMediaOptions(){}

	FChannelMediaOptions(const agora::rtc::ChannelMediaOptions & AgoraData){
		
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

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->clientRoleType,AgoraData.clientRoleType,static_cast<ECLIENT_ROLE_TYPE>(AgoraData.clientRoleType.value()))
			
		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->audienceLatencyLevel, AgoraData.audienceLatencyLevel, static_cast<EAUDIENCE_LATENCY_LEVEL_TYPE>(AgoraData.audienceLatencyLevel.value()))

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->defaultVideoStreamType, AgoraData.defaultVideoStreamType, static_cast<EVIDEO_STREAM_TYPE>(AgoraData.defaultVideoStreamType.value()))

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->channelProfile, AgoraData.channelProfile, static_cast<ECHANNEL_PROFILE_TYPE>(AgoraData.channelProfile.value()))

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
struct FLeaveChannelOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	bool stopAudioMixing = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	bool stopAllEffect = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	bool stopMicrophoneRecording = true;

	
	FLeaveChannelOptions() {}

	FLeaveChannelOptions(const agora::rtc::LeaveChannelOptions& AgoraData) {
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
struct FEchoTestConfiguration
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

	
	FEchoTestConfiguration() {}

	FEchoTestConfiguration(const agora::rtc::EchoTestConfiguration& AgoraData) {
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.token)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.channelId)
	}

};


UENUM(BlueprintType)
enum class ECAMERA_DIRECTION :uint8 {

	CAMERA_REAR = 0,

	CAMERA_FRONT = 1,
};

UENUM(BlueprintType)
enum class ECAMERA_FOCAL_LENGTH_TYPE :uint8 {
	CAMERA_FOCAL_LENGTH_DEFAULT = 0,
	CAMERA_FOCAL_LENGTH_WIDE_ANGLE = 1,
	CAMERA_FOCAL_LENGTH_URLTRA_WIDE = 2,
	CAMERA_FOCAL_LENGTH_TELEPHOTO = 3,
};

USTRUCT(BlueprintType)
struct FVideoFormat {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int height = 360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int fps = 15;

	FVideoFormat(){}
	FVideoFormat(const agora::rtc::VideoFormat & AgoraData){
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
struct FCameraCapturerConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	ECAMERA_DIRECTION cameraDirection = ECAMERA_DIRECTION::CAMERA_FRONT;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	ECAMERA_FOCAL_LENGTH_TYPE cameraFocalLengthType = ECAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

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
	FVideoFormat format = FVideoFormat();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAgoraOptional followEncodeDimensionRatio = EAgoraOptional::AGORA_NULL_VALUE;


	FCameraCapturerConfiguration(){}
	FCameraCapturerConfiguration(const agora::rtc::CameraCapturerConfiguration & AgoraData){
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
		cameraDirection = static_cast<ECAMERA_DIRECTION>(AgoraData.cameraDirection.value());
		cameraFocalLengthType = static_cast<ECAMERA_FOCAL_LENGTH_TYPE>(AgoraData.cameraFocalLengthType.value());
#else

		SET_UEBP_OPTIONAL_VAL_FString(this->deviceId, AgoraData.deviceId);
#endif

#if defined(__ANDROID__)
		cameraId = UTF8_TO_TCHAR(AgoraData.cameraId.value());
#endif

		format = FVideoFormat(AgoraData.format);
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
struct FLastmileProbeConfig
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

	FLastmileProbeConfig(){}
	FLastmileProbeConfig(const agora::rtc::LastmileProbeConfig & AgoraData){
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
struct FVideoDimensions {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoDimensions")
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FVideoDimensions")
	int height = 480;

	FVideoDimensions(){}
	FVideoDimensions(const agora::rtc::VideoDimensions & AgoraData){
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

UENUM(BlueprintType)
enum class EORIENTATION_MODE : uint8 {

	ORIENTATION_MODE_ADAPTIVE = 0,

	ORIENTATION_MODE_FIXED_LANDSCAPE = 1,

	ORIENTATION_MODE_FIXED_PORTRAIT = 2,
};

UENUM(BlueprintType)
enum class EDEGRADATION_PREFERENCE : uint8 {

	MAINTAIN_QUALITY = 0,

	MAINTAIN_FRAMERATE = 1,

	MAINTAIN_BALANCED = 2,

	MAINTAIN_RESOLUTION = 3,

	DISABLED = 100,
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_ENCODING_PREFERENCE :uint8 {

	PREFER_AUTO = 0,

	PREFER_SOFTWARE = 1,

	PREFER_HARDWARE = 2,
};


USTRUCT(BlueprintType)
struct FENUMWRAP_ENCODING_PREFERENCE {
	
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_ENCODING_PREFERENCE")
	EENUMCUSTOM_ENCODING_PREFERENCE ValueWrapper = EENUMCUSTOM_ENCODING_PREFERENCE::PREFER_AUTO;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_3_ENTRIES(FENUMWRAP_ENCODING_PREFERENCE,agora::rtc::ENCODING_PREFERENCE, EENUMCUSTOM_ENCODING_PREFERENCE,
		PREFER_AUTO, 
		PREFER_SOFTWARE, 
		PREFER_HARDWARE)
};

UENUM(BlueprintType)
enum class ECOMPRESSION_PREFERENCE : uint8 {

	PREFER_LOW_LATENCY = 0,

	PREFER_QUALITY = 1,
};

USTRUCT(BlueprintType)
struct FAdvanceOptions {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	FENUMWRAP_ENCODING_PREFERENCE encodingPreference = EENUMCUSTOM_ENCODING_PREFERENCE::PREFER_AUTO;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	ECOMPRESSION_PREFERENCE compressionPreference = ECOMPRESSION_PREFERENCE::PREFER_QUALITY;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	bool encodeAlpha = false;


	FAdvanceOptions() {}

	FAdvanceOptions(const agora::rtc::AdvanceOptions & AgoraData){
		encodingPreference = AgoraData.encodingPreference;
		compressionPreference = static_cast<ECOMPRESSION_PREFERENCE>(AgoraData.compressionPreference);
		encodeAlpha = AgoraData.encodeAlpha;
	}

	agora::rtc::AdvanceOptions CreateAgoraData() const{
		agora::rtc::AdvanceOptions AgoraData;
		AgoraData.encodingPreference = encodingPreference.GetRawValue();
		AgoraData.compressionPreference =static_cast<agora::rtc::COMPRESSION_PREFERENCE>(compressionPreference);
		AgoraData.encodeAlpha = encodeAlpha;
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::AdvanceOptions& AgoraData) const {
		// no need to free
	}
};

USTRUCT(BlueprintType)
struct FVideoEncoderConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EVIDEO_CODEC_TYPE codecType = EVIDEO_CODEC_TYPE::VIDEO_CODEC_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	FVideoDimensions dimensions = FVideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	int frameRate = 15;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	int bitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	int minBitrate = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EORIENTATION_MODE orientationMode = EORIENTATION_MODE::ORIENTATION_MODE_ADAPTIVE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EDEGRADATION_PREFERENCE degradationPreference = EDEGRADATION_PREFERENCE::MAINTAIN_QUALITY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EVIDEO_MIRROR_MODE_TYPE mirrorMode = EVIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_DISABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	FAdvanceOptions advanceOptions = FAdvanceOptions();

	FVideoEncoderConfiguration(){}
	FVideoEncoderConfiguration(const agora::rtc::VideoEncoderConfiguration & AgoraData){
		codecType = static_cast<EVIDEO_CODEC_TYPE>(AgoraData.codecType);
		dimensions = FVideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		minBitrate = AgoraData.minBitrate;
		orientationMode = static_cast<EORIENTATION_MODE>(AgoraData.orientationMode);
		degradationPreference = static_cast<EDEGRADATION_PREFERENCE>(AgoraData.degradationPreference);
		mirrorMode = static_cast<EVIDEO_MIRROR_MODE_TYPE>(AgoraData.mirrorMode);
		advanceOptions = FAdvanceOptions(AgoraData.advanceOptions);
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

UENUM(BlueprintType)
enum class ELIGHTENING_CONTRAST_LEVEL : uint8 {

	LIGHTENING_CONTRAST_LOW = 0,

	LIGHTENING_CONTRAST_NORMAL = 1,

	LIGHTENING_CONTRAST_HIGH = 2,
};

USTRUCT(BlueprintType)
struct FBeautyOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	ELIGHTENING_CONTRAST_LEVEL lighteningContrastLevel = ELIGHTENING_CONTRAST_LEVEL::LIGHTENING_CONTRAST_NORMAL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float lighteningLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float smoothnessLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float rednessLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float sharpnessLevel = 0;

	FBeautyOptions(){}
	FBeautyOptions(const agora::rtc::BeautyOptions & AgoraData){
		lighteningContrastLevel = static_cast<ELIGHTENING_CONTRAST_LEVEL>(AgoraData.lighteningContrastLevel);
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

UENUM(BlueprintType)
enum class EMEDIA_SOURCE_TYPE : uint8 {
	AUDIO_PLAYOUT_SOURCE = 0,
	AUDIO_RECORDING_SOURCE = 1,
	PRIMARY_CAMERA_SOURCE = 2,
	SECONDARY_CAMERA_SOURCE = 3,
	PRIMARY_SCREEN_SOURCE = 4,
	SECONDARY_SCREEN_SOURCE = 5,
	CUSTOM_VIDEO_SOURCE = 6,
	MEDIA_PLAYER_SOURCE = 7,
	RTC_IMAGE_PNG_SOURCE = 8,
	RTC_IMAGE_JPEG_SOURCE = 9,
	RTC_IMAGE_GIF_SOURCE = 10,
	REMOTE_VIDEO_SOURCE = 11,
	TRANSCODED_VIDEO_SOURCE = 12,
	UNKNOWN_MEDIA_SOURCE = 100,
};



UENUM(BlueprintType)
enum class ELOW_LIGHT_ENHANCE_MODE : uint8 {

	LOW_LIGHT_ENHANCE_AUTO = 0,

	LOW_LIGHT_ENHANCE_MANUAL = 1,
};

UENUM(BlueprintType)
enum class ELOW_LIGHT_ENHANCE_LEVEL : uint8 {

	LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY = 0,

	LOW_LIGHT_ENHANCE_LEVEL_FAST = 1,
};


USTRUCT(BlueprintType)
struct FLowlightEnhanceOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LowlightEnhanceOptions")
	ELOW_LIGHT_ENHANCE_MODE mode = ELOW_LIGHT_ENHANCE_MODE::LOW_LIGHT_ENHANCE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LowlightEnhanceOptions")
	ELOW_LIGHT_ENHANCE_LEVEL level = ELOW_LIGHT_ENHANCE_LEVEL::LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY;

	FLowlightEnhanceOptions(){}
	FLowlightEnhanceOptions(const agora::rtc::LowlightEnhanceOptions & AgoraData){
		mode = static_cast<ELOW_LIGHT_ENHANCE_MODE>(AgoraData.mode);
		level = static_cast<ELOW_LIGHT_ENHANCE_LEVEL>(AgoraData.level);
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



UENUM(BlueprintType)
enum class EVIDEO_DENOISER_MODE : uint8 {

	VIDEO_DENOISER_AUTO = 0,

	VIDEO_DENOISER_MANUAL = 1,
};


UENUM(BlueprintType)
enum class EVIDEO_DENOISER_LEVEL : uint8 {

	VIDEO_DENOISER_LEVEL_HIGH_QUALITY = 0,

	VIDEO_DENOISER_LEVEL_FAST = 1,

	VIDEO_DENOISER_LEVEL_STRENGTH = 2,
};

USTRUCT(BlueprintType)
struct FVideoDenoiserOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDenoiserOptions")
	EVIDEO_DENOISER_MODE mode = EVIDEO_DENOISER_MODE::VIDEO_DENOISER_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDenoiserOptions")
	EVIDEO_DENOISER_LEVEL level = EVIDEO_DENOISER_LEVEL::VIDEO_DENOISER_LEVEL_HIGH_QUALITY;

	FVideoDenoiserOptions(){}
	FVideoDenoiserOptions(const agora::rtc::VideoDenoiserOptions & AgoraData){
		mode = static_cast<EVIDEO_DENOISER_MODE>(AgoraData.mode);
		level = static_cast<EVIDEO_DENOISER_LEVEL>(AgoraData.level);
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
struct FColorEnhanceOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ColorEnhanceOptions")
	float strengthLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ColorEnhanceOptions")
	float skinProtectLevel = 0;

	FColorEnhanceOptions(){}
	FColorEnhanceOptions(const agora::rtc::ColorEnhanceOptions & AgoraData){
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


UENUM(BlueprintType)
enum class EBACKGROUND_SOURCE_TYPE :uint8 {

	BACKGROUND_NONE = 0,

	BACKGROUND_COLOR = 1,

	BACKGROUND_IMG = 2,

	BACKGROUND_BLUR = 3,
	BACKGROUND_VIDEO = 4,
};

UENUM(BlueprintType)
enum class EBACKGROUND_BLUR_DEGREE :uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	BLUR_DEGREE_LOW = 1,

	BLUR_DEGREE_MEDIUM = 2,

	BLUR_DEGREE_HIGH = 3,
};

USTRUCT(BlueprintType)
struct FVirtualBackgroundSource
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	EBACKGROUND_SOURCE_TYPE background_source_type = EBACKGROUND_SOURCE_TYPE::BACKGROUND_COLOR;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	int64 color = 0xffffff;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	FString source = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	EBACKGROUND_BLUR_DEGREE blur_degree = EBACKGROUND_BLUR_DEGREE::BLUR_DEGREE_HIGH;

	FVirtualBackgroundSource(){}
	FVirtualBackgroundSource(const agora::rtc::VirtualBackgroundSource & AgoraData){
		background_source_type = static_cast<EBACKGROUND_SOURCE_TYPE>(AgoraData.background_source_type);
		color = AgoraData.color;
		source = AgoraData.source;
		blur_degree = static_cast<EBACKGROUND_BLUR_DEGREE>(AgoraData.blur_degree);
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.source)
	}
};


UENUM(BlueprintType)
enum class ESEG_MODEL_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	SEG_MODEL_AI = 1,
	SEG_MODEL_GREEN = 2
};

USTRUCT(BlueprintType)
struct FSegmentationProperty
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SegmentationProperty")
	ESEG_MODEL_TYPE modelType = ESEG_MODEL_TYPE::SEG_MODEL_AI;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SegmentationProperty")
	float greenCapacity = 0.5;

	FSegmentationProperty(){}
	FSegmentationProperty(const agora::rtc::SegmentationProperty & AgoraData){
		modelType = static_cast<ESEG_MODEL_TYPE>(AgoraData.modelType);
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


UENUM(BlueprintType)
enum class EVIDEO_APPLICATION_SCENARIO_TYPE : uint8 {
	APPLICATION_SCENARIO_GENERAL = 0,
	APPLICATION_SCENARIO_VIDEO = 1,
};


UENUM(BlueprintType)
enum class EVIDEO_QOE_PREFERENCE_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	VIDEO_QOE_PREFERENCE_BALANCE = 1,
	VIDEO_QOE_PREFERENCE_DELAY_FIRST = 2,
	VIDEO_QOE_PREFERENCE_PICTURE_QUALITY_FIRST = 3,
	VIDEO_QOE_PREFERENCE_FLUENCY_FIRST = 4

};

USTRUCT(BlueprintType)
struct FVideoSubscriptionOptions
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool type_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	EVIDEO_STREAM_TYPE type = EVIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	EAgoraOptional encodedFrameOnly = EAgoraOptional::AGORA_NULL_VALUE;

	FVideoSubscriptionOptions(){}
	FVideoSubscriptionOptions(const agora::rtc::VideoSubscriptionOptions & AgoraData){
		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->type,AgoraData.type,static_cast<EVIDEO_STREAM_TYPE>(AgoraData.type.value()))
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


UENUM(BlueprintType)
enum class EAUDIO_FILE_RECORDING_TYPE :uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	AUDIO_FILE_RECORDING_MIC = 1,

	AUDIO_FILE_RECORDING_PLAYBACK = 2,

	AUDIO_FILE_RECORDING_MIXED = 3,
};


UENUM(BlueprintType)
enum class EAUDIO_RECORDING_QUALITY_TYPE : uint8 {
	AUDIO_RECORDING_QUALITY_LOW = 0,
	AUDIO_RECORDING_QUALITY_MEDIUM = 1,
	AUDIO_RECORDING_QUALITY_HIGH = 2,
	AUDIO_RECORDING_QUALITY_ULTRA_HIGH = 3,
};


USTRUCT(BlueprintType)
struct FAudioRecordingConfiguration
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
	EAUDIO_FILE_RECORDING_TYPE fileRecordingType = EAUDIO_FILE_RECORDING_TYPE::AUDIO_FILE_RECORDING_MIXED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	EAUDIO_RECORDING_QUALITY_TYPE quality = EAUDIO_RECORDING_QUALITY_TYPE::AUDIO_RECORDING_QUALITY_LOW;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	int recordingChannel = 0;

	FAudioRecordingConfiguration(){}
	FAudioRecordingConfiguration(const agora::rtc::AudioRecordingConfiguration & AgoraData){
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		encode = AgoraData.encode;
		sampleRate = AgoraData.sampleRate;
		fileRecordingType = static_cast<EAUDIO_FILE_RECORDING_TYPE>(AgoraData.fileRecordingType);
		quality = static_cast<EAUDIO_RECORDING_QUALITY_TYPE>(AgoraData.quality);
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.filePath)
	}
};


UENUM(BlueprintType)
enum class EAUDIO_ENCODED_FRAME_OBSERVER_POSITION :uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_RECORD = 1,

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_PLAYBACK = 2,

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_MIXED = 3,
};


UENUM(BlueprintType)
enum class EAUDIO_MIXING_DUAL_MONO_MODE : uint8 {
	AUDIO_MIXING_DUAL_MONO_AUTO = 0,
	AUDIO_MIXING_DUAL_MONO_L = 1,
	AUDIO_MIXING_DUAL_MONO_R = 2,
	AUDIO_MIXING_DUAL_MONO_MIX = 3,
};


USTRUCT(BlueprintType)
struct FSpatialAudioParams
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

	FSpatialAudioParams(){}
	FSpatialAudioParams(const agora::SpatialAudioParams & AgoraData){
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


UENUM(BlueprintType)
enum class EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET :uint8 {
	VOICE_BEAUTIFIER_OFF = 0,
	CHAT_BEAUTIFIER_MAGNETIC = 1,
	CHAT_BEAUTIFIER_FRESH = 2,
	CHAT_BEAUTIFIER_VITALITY = 3,
	SINGING_BEAUTIFIER = 4,
	TIMBRE_TRANSFORMATION_VIGOROUS = 5,
	TIMBRE_TRANSFORMATION_DEEP = 6,
	TIMBRE_TRANSFORMATION_MELLOW = 7,
	TIMBRE_TRANSFORMATION_FALSETTO = 8,
	TIMBRE_TRANSFORMATION_FULL = 9,
	TIMBRE_TRANSFORMATION_CLEAR = 10,
	TIMBRE_TRANSFORMATION_RESOUNDING = 11,
	TIMBRE_TRANSFORMATION_RINGING = 12,
	ULTRA_HIGH_QUALITY_VOICE = 13,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_VOICE_BEAUTIFIER_PRESET {
	GENERATED_BODY()


public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_VOICE_BEAUTIFIER_PRESET")
	EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET ValueWrapper = EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::VOICE_BEAUTIFIER_OFF;


	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_14_ENTRIES(FENUMWRAP_VOICE_BEAUTIFIER_PRESET, agora::rtc::VOICE_BEAUTIFIER_PRESET, EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET, 
		VOICE_BEAUTIFIER_OFF,
		CHAT_BEAUTIFIER_MAGNETIC,
		CHAT_BEAUTIFIER_FRESH ,
		CHAT_BEAUTIFIER_VITALITY ,
		SINGING_BEAUTIFIER ,
		TIMBRE_TRANSFORMATION_VIGOROUS,
		TIMBRE_TRANSFORMATION_DEEP ,
		TIMBRE_TRANSFORMATION_MELLOW,
		TIMBRE_TRANSFORMATION_FALSETTO,
		TIMBRE_TRANSFORMATION_FULL,
		TIMBRE_TRANSFORMATION_CLEAR ,
		TIMBRE_TRANSFORMATION_RESOUNDING,
		TIMBRE_TRANSFORMATION_RINGING,
		ULTRA_HIGH_QUALITY_VOICE
	)
};



UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_EFFECT_PRESET : uint8 {
	AUDIO_EFFECT_OFF,
	ROOM_ACOUSTICS_KTV,
	ROOM_ACOUSTICS_VOCAL_CONCERT,
	ROOM_ACOUSTICS_STUDIO,
	ROOM_ACOUSTICS_PHONOGRAPH,
	ROOM_ACOUSTICS_VIRTUAL_STEREO,
	ROOM_ACOUSTICS_SPACIAL,
	ROOM_ACOUSTICS_ETHEREAL,
	ROOM_ACOUSTICS_3D_VOICE,
	ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND,
	ROOM_ACOUSTICS_CHORUS,
	VOICE_CHANGER_EFFECT_UNCLE,
	VOICE_CHANGER_EFFECT_OLDMAN,
	VOICE_CHANGER_EFFECT_BOY,
	VOICE_CHANGER_EFFECT_SISTER,
	VOICE_CHANGER_EFFECT_GIRL,
	VOICE_CHANGER_EFFECT_PIGKING,
	VOICE_CHANGER_EFFECT_HULK,
	STYLE_TRANSFORMATION_RNB,
	STYLE_TRANSFORMATION_POPULAR,
	PITCH_CORRECTION
};

USTRUCT(BlueprintType)
struct FENUMWRAP_AUDIO_EFFECT_PRESET {
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AUDIO_EFFECT_PRESET")
	EENUMCUSTOM_AUDIO_EFFECT_PRESET ValueWrapper = EENUMCUSTOM_AUDIO_EFFECT_PRESET::AUDIO_EFFECT_OFF;


	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_21_ENTRIES(FENUMWRAP_AUDIO_EFFECT_PRESET, agora::rtc::AUDIO_EFFECT_PRESET, EENUMCUSTOM_AUDIO_EFFECT_PRESET,
		AUDIO_EFFECT_OFF,
		ROOM_ACOUSTICS_KTV,
		ROOM_ACOUSTICS_VOCAL_CONCERT,
		ROOM_ACOUSTICS_STUDIO,
		ROOM_ACOUSTICS_PHONOGRAPH,
		ROOM_ACOUSTICS_VIRTUAL_STEREO,
		ROOM_ACOUSTICS_SPACIAL,
		ROOM_ACOUSTICS_ETHEREAL,
		ROOM_ACOUSTICS_3D_VOICE,
		ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND,
		ROOM_ACOUSTICS_CHORUS,
		VOICE_CHANGER_EFFECT_UNCLE,
		VOICE_CHANGER_EFFECT_OLDMAN,
		VOICE_CHANGER_EFFECT_BOY,
		VOICE_CHANGER_EFFECT_SISTER,
		VOICE_CHANGER_EFFECT_GIRL,
		VOICE_CHANGER_EFFECT_PIGKING,
		VOICE_CHANGER_EFFECT_HULK,
		STYLE_TRANSFORMATION_RNB,
		STYLE_TRANSFORMATION_POPULAR,
		PITCH_CORRECTION)
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_VOICE_CONVERSION_PRESET :uint8 {

	VOICE_CONVERSION_OFF = 0,
	VOICE_CHANGER_NEUTRAL = 1,
	VOICE_CHANGER_SWEET = 2,
	VOICE_CHANGER_SOLID = 3,
	VOICE_CHANGER_BASS = 4,
	VOICE_CHANGER_CARTOON = 5,
	VOICE_CHANGER_CHILDLIKE = 6,
	VOICE_CHANGER_PHONE_OPERATOR = 7,
	VOICE_CHANGER_MONSTER = 8,
	VOICE_CHANGER_TRANSFORMERS = 9,
	VOICE_CHANGER_GROOT = 10,
	VOICE_CHANGER_DARTH_VADER = 11,
	VOICE_CHANGER_IRON_LADY = 12,
	VOICE_CHANGER_SHIN_CHAN = 13,
	VOICE_CHANGER_GIRLISH_MAN = 14,
	VOICE_CHANGER_CHIPMUNK = 15,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_VOICE_CONVERSION_PRESET
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_VOICE_CONVERSION_PRESET")
	EENUMCUSTOM_VOICE_CONVERSION_PRESET ValueWrapper = EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CONVERSION_OFF;


	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_16_ENTRIES(FENUMWRAP_VOICE_CONVERSION_PRESET, agora::rtc::VOICE_CONVERSION_PRESET, EENUMCUSTOM_VOICE_CONVERSION_PRESET,
		VOICE_CONVERSION_OFF,
		VOICE_CHANGER_NEUTRAL,
		VOICE_CHANGER_SWEET,
		VOICE_CHANGER_SOLID,
		VOICE_CHANGER_BASS,
		VOICE_CHANGER_CARTOON,
		VOICE_CHANGER_CHILDLIKE,
		VOICE_CHANGER_PHONE_OPERATOR,
		VOICE_CHANGER_MONSTER,
		VOICE_CHANGER_TRANSFORMERS,
		VOICE_CHANGER_GROOT,
		VOICE_CHANGER_DARTH_VADER,
		VOICE_CHANGER_IRON_LADY,
		VOICE_CHANGER_SHIN_CHAN,
		VOICE_CHANGER_GIRLISH_MAN,
		VOICE_CHANGER_CHIPMUNK)
};

UENUM(BlueprintType)
enum class EAUDIO_EQUALIZATION_BAND_FREQUENCY : uint8 {
	AUDIO_EQUALIZATION_BAND_31 = 0,
	AUDIO_EQUALIZATION_BAND_62 = 1,
	AUDIO_EQUALIZATION_BAND_125 = 2,
	AUDIO_EQUALIZATION_BAND_250 = 3,
	AUDIO_EQUALIZATION_BAND_500 = 4,
	AUDIO_EQUALIZATION_BAND_1K = 5,
	AUDIO_EQUALIZATION_BAND_2K = 6,
	AUDIO_EQUALIZATION_BAND_4K = 7,
	AUDIO_EQUALIZATION_BAND_8K = 8,
	AUDIO_EQUALIZATION_BAND_16K = 9,
};


UENUM(BlueprintType)
enum class EAUDIO_REVERB_TYPE : uint8 {
	AUDIO_REVERB_DRY_LEVEL = 0,
	AUDIO_REVERB_WET_LEVEL = 1,
	AUDIO_REVERB_ROOM_SIZE = 2,
	AUDIO_REVERB_WET_DELAY = 3,
	AUDIO_REVERB_STRENGTH = 4,
};

USTRUCT(BlueprintType)
struct FSimulcastStreamConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	FVideoDimensions dimensions = FVideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	int kBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	int framerate = 0;

	FSimulcastStreamConfig(){}
	FSimulcastStreamConfig(const agora::rtc::SimulcastStreamConfig & AgoraData){
		dimensions = FVideoDimensions(AgoraData.dimensions);
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



UENUM(BlueprintType)
enum class EENUMCUSTOM_SIMULCAST_STREAM_MODE : uint8 {
	AUTO_SIMULCAST_STREAM = 0,
	DISABLE_SIMULCAST_STREAM = 1,
	ENABLE_SIMULCAST_STREAM = 2,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_SIMULCAST_STREAM_MODE
{
	GENERATED_BODY()

public:

	// require to call [GetRawValue] method to get the raw value 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_SIMULCAST_STREAM_MODE")
	EENUMCUSTOM_SIMULCAST_STREAM_MODE ValueWrapper = EENUMCUSTOM_SIMULCAST_STREAM_MODE::AUTO_SIMULCAST_STREAM;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_3_ENTRIES(FENUMWRAP_SIMULCAST_STREAM_MODE, agora::rtc::SIMULCAST_STREAM_MODE, EENUMCUSTOM_SIMULCAST_STREAM_MODE,
			AUTO_SIMULCAST_STREAM,
			DISABLE_SIMULCAST_STREAM,
			ENABLE_SIMULCAST_STREAM)

};


UENUM(BlueprintType)
enum class ERAW_AUDIO_FRAME_OP_MODE_TYPE : uint8 {
	RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
	RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
};

UENUM(BlueprintType)
enum class ESTREAM_FALLBACK_OPTIONS : uint8 {
	STREAM_FALLBACK_OPTION_DISABLED = 0,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
	STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
};



USTRUCT(BlueprintType)
struct FExtensionInfo {

	GENERATED_BODY();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	EMEDIA_SOURCE_TYPE mediaSourceType = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	int64 remoteUid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	int64 localUid = 0;

	FExtensionInfo() {}

	FExtensionInfo(const agora::rtc::ExtensionInfo& AgoraData) {
		mediaSourceType = (EMEDIA_SOURCE_TYPE)AgoraData.mediaSourceType;
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


UENUM(BlueprintType)
enum class EENUMCUSTOM_CAMERA_STABILIZATION_MODE : uint8{
	CAMERA_STABILIZATION_MODE_OFF,
	CAMERA_STABILIZATION_MODE_AUTO,
	CAMERA_STABILIZATION_MODE_LEVEL_1,
	CAMERA_STABILIZATION_MODE_LEVEL_2,
	CAMERA_STABILIZATION_MODE_LEVEL_3
};

USTRUCT(BlueprintType)
struct FENUMWRAP_CAMERA_STABILIZATION_MODE {
	
	GENERATED_BODY()

public:
		// require to call [GetRawValue] method to get the raw value 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_CAMERA_STABILIZATION_MODE")
	EENUMCUSTOM_CAMERA_STABILIZATION_MODE ValueWrapper = EENUMCUSTOM_CAMERA_STABILIZATION_MODE::CAMERA_STABILIZATION_MODE_OFF;

	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_5_ENTRIES(FENUMWRAP_CAMERA_STABILIZATION_MODE, agora::rtc::CAMERA_STABILIZATION_MODE, EENUMCUSTOM_CAMERA_STABILIZATION_MODE,
		CAMERA_STABILIZATION_MODE_OFF,
		CAMERA_STABILIZATION_MODE_AUTO,
		CAMERA_STABILIZATION_MODE_LEVEL_1,
		CAMERA_STABILIZATION_MODE_LEVEL_2,
		CAMERA_STABILIZATION_MODE_LEVEL_3)

};

#pragma endregion Rtc Engine 2



#pragma region Screen Share


USTRUCT(BlueprintType)
struct FThumbImageBuffer {

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
	FThumbImageBuffer(){}
	FThumbImageBuffer(const agora::rtc::ThumbImageBuffer & AgoraData){

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


UENUM(BlueprintType)
enum class EENUMCUSTOM_ScreenCaptureSourceType : uint8 {
	ScreenCaptureSourceType_Unknown = 0,
	ScreenCaptureSourceType_Window = 1,
	ScreenCaptureSourceType_Screen = 2,
	ScreenCaptureSourceType_Custom = 3,
};


USTRUCT(BlueprintType)
struct FENUMWRAP_ScreenCaptureSourceType
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_ScreenCaptureSourceType")
	EENUMCUSTOM_ScreenCaptureSourceType ValueWrapper = EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown;

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	
	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_4_ENTRIES(FENUMWRAP_ScreenCaptureSourceType, agora::rtc::ScreenCaptureSourceType, EENUMCUSTOM_ScreenCaptureSourceType,
		ScreenCaptureSourceType_Unknown,
		ScreenCaptureSourceType_Window,
		ScreenCaptureSourceType_Screen,
		ScreenCaptureSourceType_Custom)

#endif
};


USTRUCT(BlueprintType)
struct FScreenCaptureSourceInfo {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FENUMWRAP_ScreenCaptureSourceType type = FENUMWRAP_ScreenCaptureSourceType();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	int64 sourceId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FString sourceName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FThumbImageBuffer thumbImage = FThumbImageBuffer();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FThumbImageBuffer iconImage = FThumbImageBuffer();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FString processPath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FString sourceTitle = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	bool primaryMonitor = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	bool isOccluded = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FRectangle position = FRectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	bool minimizeWindow = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	int64 sourceDisplayId = 0;

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	FScreenCaptureSourceInfo(){}
	FScreenCaptureSourceInfo(const agora::rtc::ScreenCaptureSourceInfo & AgoraData){

		type = AgoraData.type;

		sourceId = UABT::FromViewToInt(AgoraData.sourceId);
		sourceName = UTF8_TO_TCHAR(AgoraData.sourceName);
		thumbImage = FThumbImageBuffer(AgoraData.thumbImage);
		iconImage = FThumbImageBuffer(AgoraData.iconImage);
		processPath = UTF8_TO_TCHAR(AgoraData.processPath);
		sourceTitle = UTF8_TO_TCHAR(AgoraData.sourceTitle);
		primaryMonitor = AgoraData.primaryMonitor;
		isOccluded = AgoraData.isOccluded;
		position = FRectangle(AgoraData.position);
#if defined(_WIN32)
		minimizeWindow = AgoraData.minimizeWindow;
		sourceDisplayId = UABT::FromViewToInt(AgoraData.sourceDisplayId);
#endif
	}

	agora::rtc::ScreenCaptureSourceInfo CreateAgoraData() const {
		agora::rtc::ScreenCaptureSourceInfo AgoraData;
		AgoraData.type = static_cast<agora::rtc::ScreenCaptureSourceType>(type.GetRawValue());
		AgoraData.sourceId = UABT::ToView(sourceId);
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
		AgoraData.sourceDisplayId = UABT::ToView(sourceDisplayId);
#endif
		return AgoraData;
	}

	void FreeAgoraData(agora::rtc::ScreenCaptureSourceInfo & AgoraData) const {
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.sourceName)
		thumbImage.FreeAgoraData(AgoraData.thumbImage);
		thumbImage.FreeAgoraData(AgoraData.iconImage);
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.processPath)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.sourceTitle)
		position.FreeAgoraData(AgoraData.position);
	}
#endif
};


USTRUCT(BlueprintType)
struct FSIZE {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SIZE")
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SIZE")
	int height = 0;

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	FSIZE(){}
	FSIZE(const agora::rtc::SIZE & AgoraData){
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
struct FScreenCaptureParameters
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	FVideoDimensions dimensions = FVideoDimensions();
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

	FScreenCaptureParameters(){}
	FScreenCaptureParameters(const agora::rtc::ScreenCaptureParameters & AgoraData){
		dimensions = FVideoDimensions(AgoraData.dimensions);
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
struct FScreenAudioParameters {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenAudioParameters")
	int sampleRate = 16000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenAudioParameters")
	int channels = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenAudioParameters")
	int captureSignalVolume = 100;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FScreenAudioParameters(){}
	FScreenAudioParameters(const agora::rtc::ScreenAudioParameters & AgoraData){
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

UENUM(BlueprintType)
enum class EVIDEO_CONTENT_HINT : uint8 {
	CONTENT_HINT_NONE,
	CONTENT_HINT_MOTION,
	CONTENT_HINT_DETAILS,
};



USTRUCT(BlueprintType)
struct FScreenVideoParameters {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	FVideoDimensions dimensions = FVideoDimensions();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	int frameRate = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	int bitrate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenVideoParameters")
	EVIDEO_CONTENT_HINT contentHint = EVIDEO_CONTENT_HINT::CONTENT_HINT_MOTION;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FScreenVideoParameters(){}
	FScreenVideoParameters(const agora::rtc::ScreenVideoParameters & AgoraData){
		dimensions = FVideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		contentHint = static_cast<EVIDEO_CONTENT_HINT>(AgoraData.contentHint);
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
struct FScreenCaptureParameters2
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	bool captureAudio = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	FScreenAudioParameters audioParams = FScreenAudioParameters();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	bool captureVideo = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	FScreenVideoParameters videoParams = FScreenVideoParameters();

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FScreenCaptureParameters2(){}
	FScreenCaptureParameters2(const agora::rtc::ScreenCaptureParameters2 & AgoraData){
		captureAudio = AgoraData.captureAudio;
		audioParams = FScreenAudioParameters(AgoraData.audioParams);
		captureVideo = AgoraData.captureVideo;
		videoParams = FScreenVideoParameters(AgoraData.videoParams);
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
struct FScreenCaptureConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	bool isCaptureWindow = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	int displayId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FRectangle screenRect = FRectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	int64 windowId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FScreenCaptureParameters params = FScreenCaptureParameters();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FRectangle regionRect = FRectangle();

	FScreenCaptureConfiguration(){}
	FScreenCaptureConfiguration(const agora::rtc::ScreenCaptureConfiguration & AgoraData){
		isCaptureWindow = AgoraData.isCaptureWindow;
		displayId = AgoraData.displayId;
		screenRect = FRectangle(AgoraData.screenRect);
		//windowId = AgoraData.windowId;
		params = FScreenCaptureParameters(AgoraData.params);
		regionRect = FRectangle(AgoraData.regionRect);
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

UENUM(BlueprintType)
enum class EAUDIO_SESSION_OPERATION_RESTRICTION : uint8 {
	AUDIO_SESSION_OPERATION_RESTRICTION_NONE = 0,
	AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY = 1,
	AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION = 1 << 1,
	AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION = 1 << 2,
	AUDIO_SESSION_OPERATION_RESTRICTION_ALL = 1 << 7,
};


USTRUCT(BlueprintType)
struct FFocalLengthInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FFocalLengthInfo")
	int cameraDirection = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FFocalLengthInfo")
	ECAMERA_FOCAL_LENGTH_TYPE focalLengthType = ECAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

	FFocalLengthInfo(){}
	FFocalLengthInfo(const agora::rtc::FocalLengthInfo & AgoraData){
		cameraDirection = AgoraData.cameraDirection;
		focalLengthType = static_cast<ECAMERA_FOCAL_LENGTH_TYPE>(AgoraData.focalLengthType);
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


UENUM(BlueprintType)
enum class ESCREEN_SCENARIO_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL = 0,
	SCREEN_SCENARIO_DOCUMENT = 1,
	SCREEN_SCENARIO_GAMING = 2,
	SCREEN_SCENARIO_VIDEO = 3,
	SCREEN_SCENARIO_RDC = 4,
};


UENUM(BlueprintType)
enum class EVIDEO_CODEC_PROFILE_TYPE : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	VIDEO_CODEC_PROFILE_BASELINE = 66,

	VIDEO_CODEC_PROFILE_MAIN = 77,

	VIDEO_CODEC_PROFILE_HIGH = 100,
};


UENUM(BlueprintType)
enum class EVIDEO_CODEC_TYPE_FOR_STREAM : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	VIDEO_CODEC_H264_FOR_STREAM = 1,

	VIDEO_CODEC_H265_FOR_STREAM = 2,
};


USTRUCT(BlueprintType)
struct FTranscodingUser {

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

	FTranscodingUser(){}
	FTranscodingUser(const agora::rtc::TranscodingUser & AgoraData){
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
struct FRtcImage
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

	FRtcImage() {}

	FRtcImage(const agora::rtc::RtcImage& AgoraData) {
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

UENUM(BlueprintType)
enum class EAUDIO_SAMPLE_RATE_TYPE:uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),

	AUDIO_SAMPLE_RATE_32000 = 1,

	AUDIO_SAMPLE_RATE_44100 = 2,

	AUDIO_SAMPLE_RATE_48000 = 3,
};



UENUM(BlueprintType)
enum class EAUDIO_CODEC_PROFILE_TYPE : uint8 {

	AUDIO_CODEC_PROFILE_LC_AAC = 0,

	AUDIO_CODEC_PROFILE_HE_AAC = 1,

	AUDIO_CODEC_PROFILE_HE_AAC_V2 = 2,
};

USTRUCT(BlueprintType)
struct FLiveStreamAdvancedFeature {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveStreamAdvancedFeature")
	FString featureName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveStreamAdvancedFeature")
	bool opened = false;

	FLiveStreamAdvancedFeature(){}
	FLiveStreamAdvancedFeature(const agora::rtc::LiveStreamAdvancedFeature & AgoraData){
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.featureName)
	}
};



USTRUCT(BlueprintType)
struct FLiveTranscoding
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
	EVIDEO_CODEC_PROFILE_TYPE videoCodecProfile = EVIDEO_CODEC_PROFILE_TYPE::VIDEO_CODEC_PROFILE_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int64 backgroundColor = 0x000000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EVIDEO_CODEC_TYPE_FOR_STREAM videoCodecType = EVIDEO_CODEC_TYPE_FOR_STREAM::VIDEO_CODEC_H264_FOR_STREAM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int userCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FTranscodingUser> transcodingUsers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	FString transcodingExtraInfo = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	FString metadata = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray <FRtcImage> watermark;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int watermarkCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FRtcImage> backgroundImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int backgroundImageCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EAUDIO_SAMPLE_RATE_TYPE audioSampleRate = EAUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int audioBitrate = 48;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int audioChannels = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EAUDIO_CODEC_PROFILE_TYPE audioCodecProfile = EAUDIO_CODEC_PROFILE_TYPE::AUDIO_CODEC_PROFILE_LC_AAC;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FLiveStreamAdvancedFeature> advancedFeatures;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int advancedFeatureCount = 0;

	FLiveTranscoding(){}
	FLiveTranscoding(const agora::rtc::LiveTranscoding & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
		videoBitrate = AgoraData.videoBitrate;
		videoFramerate = AgoraData.videoFramerate;
		lowLatency = AgoraData.lowLatency;
		videoGop = AgoraData.videoGop;
		videoCodecProfile = static_cast<EVIDEO_CODEC_PROFILE_TYPE>(AgoraData.videoCodecProfile);
		backgroundColor = AgoraData.backgroundColor;
		videoCodecType = static_cast<EVIDEO_CODEC_TYPE_FOR_STREAM>(AgoraData.videoCodecType);
		userCount = AgoraData.userCount;
		for(int i = 0; i< userCount; i++){
			transcodingUsers.Add(FTranscodingUser((AgoraData.transcodingUsers[i])));
		}
	
		transcodingExtraInfo = UTF8_TO_TCHAR(AgoraData.transcodingExtraInfo);
		metadata = UTF8_TO_TCHAR(AgoraData.metadata);

		for(unsigned int i =0; i< AgoraData.watermarkCount;i++)
		{
			watermark.Add(FRtcImage(AgoraData.watermark[i]));
		}
		watermarkCount = AgoraData.watermarkCount;

		for(unsigned int i =0; i< AgoraData.backgroundImageCount;i++){
			backgroundImage.Add(FRtcImage(AgoraData.watermark[i]));
		}
		backgroundImageCount = AgoraData.backgroundImageCount;
		audioSampleRate = static_cast<EAUDIO_SAMPLE_RATE_TYPE>(AgoraData.audioSampleRate);
		audioBitrate = AgoraData.audioBitrate;
		audioChannels = AgoraData.audioChannels;
		audioCodecProfile = static_cast<EAUDIO_CODEC_PROFILE_TYPE>(AgoraData.audioCodecProfile);

		for(unsigned int i = 0; i< AgoraData.advancedFeatureCount; i++){
			advancedFeatures.Add(FLiveStreamAdvancedFeature(AgoraData.advancedFeatures[i]));
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

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.transcodingUsers,userCount, FTranscodingUser)
		
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.transcodingExtraInfo)

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.watermark, watermarkCount, FRtcImage)

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.backgroundImage, backgroundImageCount, FRtcImage)

		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.advancedFeatures, advancedFeatureCount, FLiveStreamAdvancedFeature)
	
	}
		
};




USTRUCT(BlueprintType)
struct FLocalTranscoderConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	int64 streamCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	TArray<FTranscodingVideoStream> videoInputStreams;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	FVideoEncoderConfiguration videoOutputConfiguration = FVideoEncoderConfiguration();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	bool syncWithPrimaryCamera = true;

	FLocalTranscoderConfiguration(){}
	FLocalTranscoderConfiguration(const agora::rtc::LocalTranscoderConfiguration & AgoraData){
		streamCount = AgoraData.streamCount;
		for(int i = 0; i< streamCount; i++){
			videoInputStreams.Add(FTranscodingVideoStream(AgoraData.videoInputStreams[i]));
		}
		videoOutputConfiguration = FVideoEncoderConfiguration(AgoraData.videoOutputConfiguration);
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
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.videoInputStreams, streamCount, FTranscodingVideoStream)
		videoOutputConfiguration.FreeAgoraData(AgoraData.videoOutputConfiguration);
	}
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_VIDEO_ORIENTATION : uint8 {
	VIDEO_ORIENTATION_0 = 0,
	VIDEO_ORIENTATION_90 = 1,
	VIDEO_ORIENTATION_180 = 2,
	VIDEO_ORIENTATION_270 = 3,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_VIDEO_ORIENTATION {
	GENERATED_BODY()


public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_VIDEO_ORIENTATION")
	EENUMCUSTOM_VIDEO_ORIENTATION ValueWrapper = EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_0;


	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_4_ENTRIES(FENUMWRAP_VIDEO_ORIENTATION, agora::rtc::VIDEO_ORIENTATION, EENUMCUSTOM_VIDEO_ORIENTATION,
			VIDEO_ORIENTATION_0,
			VIDEO_ORIENTATION_90,
			VIDEO_ORIENTATION_180,
			VIDEO_ORIENTATION_270)
};


UENUM(BlueprintType)
enum class EPRIORITY_TYPE : uint8 {
	INVALID_OPT_BPGEN_NULL = 0,
	PRIORITY_HIGH = 50,
	PRIORITY_NORMAL = 100,
};


USTRUCT(BlueprintType)
struct FDataStreamConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DataStreamConfig")
	bool syncWithAudio = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DataStreamConfig")
	bool ordered = false;

	FDataStreamConfig(){}
	FDataStreamConfig(const agora::rtc::DataStreamConfig & AgoraData){
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
struct FWatermarkRatio {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkRatio")
	float xRatio = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkRatio")
	float yRatio = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkRatio")
	float widthRatio = 0;

	FWatermarkRatio(){}
	FWatermarkRatio(const agora::rtc::WatermarkRatio & AgoraData){
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


UENUM(BlueprintType)
enum class EWATERMARK_FIT_MODE : uint8 {

	FIT_MODE_COVER_POSITION,

	FIT_MODE_USE_IMAGE_RATIO
};

USTRUCT(BlueprintType)
struct FWatermarkOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	bool visibleInPreview = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FRectangle positionInLandscapeMode = FRectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FRectangle positionInPortraitMode = FRectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FWatermarkRatio watermarkRatio = FWatermarkRatio();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	EWATERMARK_FIT_MODE mode = EWATERMARK_FIT_MODE::FIT_MODE_COVER_POSITION;

	FWatermarkOptions(){}
	FWatermarkOptions(const agora::rtc::WatermarkOptions & AgoraData){
		visibleInPreview = AgoraData.visibleInPreview;
		positionInLandscapeMode = FRectangle(AgoraData.positionInLandscapeMode);
		positionInPortraitMode = FRectangle(AgoraData.positionInPortraitMode);
		watermarkRatio = FWatermarkRatio(AgoraData.watermarkRatio);
		mode = static_cast<EWATERMARK_FIT_MODE>(AgoraData.mode);
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


UENUM(BlueprintType)
enum class EAUDIO_AINS_MODE : uint8 {
	AINS_MODE_BALANCED = 0,
	AINS_MODE_AGGRESSIVE = 1,
	AINS_MODE_ULTRALOWLATENCY = 2
};



USTRUCT(BlueprintType)
struct FAgoraRhythmPlayerConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraRhythmPlayerConfig")
	int beatsPerMeasure = 4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraRhythmPlayerConfig")
	int beatsPerMinute = 60;

	FAgoraRhythmPlayerConfig(){}
	FAgoraRhythmPlayerConfig(const agora::rtc::AgoraRhythmPlayerConfig & AgoraData){
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

UENUM(BlueprintType)
enum class ECONTENT_INSPECT_TYPE : uint8 {

	CONTENT_INSPECT_INVALID = 0,

	// deprecated
	CONTENT_INSPECT_MODERATION = 1,

	CONTENT_INSPECT_SUPERVISION = 2,
	
	CONTENT_INSPECT_IMAGE_MODERATION = 3

};

USTRUCT(BlueprintType)
struct FContentInspectModule {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectModule")
	ECONTENT_INSPECT_TYPE type = ECONTENT_INSPECT_TYPE::CONTENT_INSPECT_INVALID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectModule")
	int64 interval = 0;

	FContentInspectModule(){}
	FContentInspectModule(const agora::media::ContentInspectModule & AgoraData){
		type = static_cast<ECONTENT_INSPECT_TYPE>(AgoraData.type);
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
struct FContentInspectConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	FString extraInfo = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	FString serverConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	TArray<FContentInspectModule> modules;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	int moduleCount = 0;

	FContentInspectConfig(){}
	FContentInspectConfig(const agora::media::ContentInspectConfig & AgoraData){
		extraInfo = UTF8_TO_TCHAR(AgoraData.extraInfo);
		serverConfig = UTF8_TO_TCHAR(AgoraData.serverConfig);
		moduleCount = AgoraData.moduleCount;
		for(int i = 0; i< moduleCount; i++){
			modules.Add(FContentInspectModule(AgoraData.modules[i]));
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.extraInfo)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.serverConfig)
		for (int i = 0; i < moduleCount; i++) {
			FContentInspectModule ReleaseOperator;
			ReleaseOperator.FreeAgoraData(AgoraData.modules[i]);
		}
	}

};


UENUM(BlueprintType)
enum class ECLOUD_PROXY_TYPE : uint8 {
	NONE_PROXY = 0,
	UDP_PROXY = 1,
	TCP_PROXY = 2,
};


USTRUCT(BlueprintType)
struct FLogUploadServerInfo {

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

	FLogUploadServerInfo() {}
	FLogUploadServerInfo(const agora::rtc::LogUploadServerInfo& AgoraData) {
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.serverDomain)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.serverPath)
	}
};


USTRUCT(BlueprintType)
struct FAdvancedConfigInfo {

	GENERATED_BODY()

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedConfigInfo")
	FLogUploadServerInfo logUploadServer = FLogUploadServerInfo();

	FAdvancedConfigInfo(){}
	FAdvancedConfigInfo(const agora::rtc::AdvancedConfigInfo& AgoraData) {
		logUploadServer = FLogUploadServerInfo(AgoraData.logUploadServer);
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

UENUM(BlueprintType)
enum class ELOCAL_PROXY_MODE :uint8{
	ConnectivityFirst = 0,
	LocalOnly = 1,
};

USTRUCT(BlueprintType)
struct FLocalAccessPointConfiguration
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
	FAdvancedConfigInfo advancedConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	bool disableAut = false;

	FLocalAccessPointConfiguration(){}
	FLocalAccessPointConfiguration(const agora::rtc::LocalAccessPointConfiguration & AgoraData){
		
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

		advancedConfig = FAdvancedConfigInfo(AgoraData.advancedConfig);

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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.verifyDomainName)
		advancedConfig.FreeAgoraData(AgoraData.advancedConfig);
	}
};

USTRUCT(BlueprintType)
struct FAdvancedAudioOptions
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	bool audioProcessingChannels_SetValue = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	int audioProcessingChannels = 0;

	FAdvancedAudioOptions(){}
	FAdvancedAudioOptions(const agora::rtc::AdvancedAudioOptions & AgoraData){
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
struct FImageTrackOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ImageTrackOptions")
	FString imageUrl = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ImageTrackOptions")
	int fps = 1;

	FImageTrackOptions(){}
	FImageTrackOptions(const agora::rtc::ImageTrackOptions & AgoraData){
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.imageUrl)
	}

};


UENUM(BlueprintType)
enum class EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET : uint8 {

	HEADPHONE_EQUALIZER_OFF = 0,

	HEADPHONE_EQUALIZER_OVEREAR = 1,

	HEADPHONE_EQUALIZER_INEAR = 2
};


USTRUCT(BlueprintType)
struct FENUMWRAP_HEADPHONE_EQUALIZER_PRESET
{
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_HEADPHONE_EQUALIZER_PRESET")
	EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET ValueWrapper = EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OFF;


	AGORA_CREATE_UEENUM_CONVERT_STRUCT_INNER_3_ENTRIES(FENUMWRAP_HEADPHONE_EQUALIZER_PRESET, agora::rtc::HEADPHONE_EQUALIZER_PRESET, EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET,
		HEADPHONE_EQUALIZER_OFF,
		HEADPHONE_EQUALIZER_OVEREAR,
		HEADPHONE_EQUALIZER_INEAR)

};



UENUM(BlueprintType)
enum class EFeatureType : uint8 {

	INVALID_OPT_BPGEN_NULL UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	VIDEO_VIRTUAL_BACKGROUND = 1,
	VIDEO_BEAUTY_EFFECT = 2,

};


USTRUCT(BlueprintType)
struct FDeviceInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DeviceInfo")
	bool isLowLatencyAudioSupported = false;

	FDeviceInfo(){}
	FDeviceInfo(const agora::rtc::DeviceInfo & AgoraData){
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
struct FChannelMediaInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	int64 uid = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString channelName = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString token = "";

	FChannelMediaInfo(){}
	FChannelMediaInfo(const agora::rtc::ChannelMediaInfo & AgoraData){
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
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.channelName)
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(AgoraData.token)
	}
};


USTRUCT(BlueprintType)
struct FChannelMediaRelayConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	FChannelMediaInfo srcInfo = FChannelMediaInfo();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	TArray<FChannelMediaInfo> destInfos;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	int destCount = 0;

	FChannelMediaRelayConfiguration(){}
	FChannelMediaRelayConfiguration(const agora::rtc::ChannelMediaRelayConfiguration & AgoraData){
		srcInfo = FChannelMediaInfo(*(AgoraData.srcInfo));
		destCount = AgoraData.destCount;
		for(int i = 0; i< destCount; i++){
			destInfos.Add(FChannelMediaInfo(AgoraData.destInfos[i]));
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
		SET_UABT_UECUSTOMDATA_TO_AGORA_PTR_1_ENTRY___MEMFREE(AgoraData.srcInfo, FChannelMediaInfo)
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(AgoraData.destInfos, destCount, FChannelMediaInfo)
	}
};


UENUM(BlueprintType)
enum class EVOICE_AI_TUNER_TYPE : uint8 {
	VOICE_AI_TUNER_MATURE_MALE = 0,
	VOICE_AI_TUNER_FRESH_MALE,
	VOICE_AI_TUNER_ELEGANT_FEMALE,
	VOICE_AI_TUNER_SWEET_FEMALE,
	VOICE_AI_TUNER_WARM_MALE_SINGING,
	VOICE_AI_TUNER_GENTLE_FEMALE_SINGING,
	VOICE_AI_TUNER_HUSKY_MALE_SINGING,
	VOICE_AI_TUNER_WARM_ELEGANT_FEMALE_SINGING,
	VOICE_AI_TUNER_POWERFUL_MALE_SINGING,
	VOICE_AI_TUNER_DREAMY_FEMALE_SINGING,
};

#pragma endregion Rtc Engine 3