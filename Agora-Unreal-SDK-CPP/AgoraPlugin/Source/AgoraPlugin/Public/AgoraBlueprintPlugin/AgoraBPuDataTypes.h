// Copyright(c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "UtilityUABTTypeHelper.h"
#include "UtilityAgoraBPuLogger.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"

#include "AgoraBPuDataTypesBase.h"

#include "AgoraBPuDataTypes.generated.h"

using namespace agora::rtc::ue;

#pragma region Custom Defined

UENUM()
enum class EAgoraBPuEventHandlerType : uint8
{
	None = 0 UMETA(Hidden, DisplayName = "AGORA NULL VALUE"),
	EventHandler = 1,
	EventHandlerEx = 2
};

#pragma endregion Custom Defined



#pragma region Optional Value
USTRUCT(BlueprintType)
struct FUABT_Opt_bool {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EAgoraOptional Value = EAgoraOptional::AGORA_NULL_VALUE;

	FUABT_Opt_bool() {}
	FUABT_Opt_bool(const agora::Optional<bool> AgoraOptVal) {
		if (AgoraOptVal.has_value() == true) {
			Value = AgoraOptVal.value()? EAgoraOptional::AGORA_TRUE_VALUE : EAgoraOptional::AGORA_FALSE_VALUE;
		}
		else {
			Value = EAgoraOptional::AGORA_NULL_VALUE;
		}
	}

	agora::Optional<bool> CreateRawOptData() const {
		if (Value == EAgoraOptional::AGORA_TRUE_VALUE) {
			return true;
		}
		else if (Value == EAgoraOptional::AGORA_FALSE_VALUE) {
			return false;
		}
		return agora::nullopt;
	}

	static void FreeRawOptData(agora::Optional<bool>& AgoraData) {

	}
};




USTRUCT(BlueprintType)
struct FUABT_Opt_VIDEO_STREAM_TYPE {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_STREAM_TYPE Value = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;

	FUABT_Opt_VIDEO_STREAM_TYPE() {}
	FUABT_Opt_VIDEO_STREAM_TYPE(const agora::Optional<agora::rtc::VIDEO_STREAM_TYPE> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABTEnum::WrapWithUE(AgoraOptVal.value());
		}
	}


	agora::Optional<agora::rtc::VIDEO_STREAM_TYPE> CreateRawOptData() const {
		if (SetValue == true) {
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::rtc::VIDEO_STREAM_TYPE>();
	}

	static void FreeRawOptData(agora::Optional<agora::rtc::VIDEO_STREAM_TYPE>& AgoraData) {
	}
};


USTRUCT(BlueprintType)
struct FUABT_Opt_CAMERA_DIRECTION {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CAMERA_DIRECTION Value = EUABT_CAMERA_DIRECTION::CAMERA_FRONT;

	FUABT_Opt_CAMERA_DIRECTION() {}
	FUABT_Opt_CAMERA_DIRECTION(const agora::Optional<agora::rtc::CAMERA_DIRECTION> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABTEnum::WrapWithUE(AgoraOptVal.value());
		}
	}

	agora::Optional<agora::rtc::CAMERA_DIRECTION> CreateRawOptData() const {
		if (SetValue == true) {
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::rtc::CAMERA_DIRECTION>();
	}

	static void FreeRawOptData(agora::Optional<agora::rtc::CAMERA_DIRECTION>& AgoraData) {
	}
};



USTRUCT(BlueprintType)
struct FUABT_Opt_CAMERA_FOCAL_LENGTH_TYPE {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CAMERA_FOCAL_LENGTH_TYPE Value = EUABT_CAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

	FUABT_Opt_CAMERA_FOCAL_LENGTH_TYPE() {}
	FUABT_Opt_CAMERA_FOCAL_LENGTH_TYPE(const agora::Optional<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABTEnum::WrapWithUE(AgoraOptVal.value());
		}
	}

	agora::Optional<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE> CreateRawOptData() const {
		if (SetValue == true) {
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE>();
	}

	static void FreeRawOptData(agora::Optional<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE>& AgoraData) {
	}

};

USTRUCT(BlueprintType)
struct FUABT_Opt_double {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString Value = "";

	FUABT_Opt_double() {}
	FUABT_Opt_double(const agora::Optional<double> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABT::FromDouble(AgoraOptVal.value());
		}
		else {
			Value = AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_OPTIONAL_VALUE_NOT_SET];
		}
	}

	agora::Optional<double> CreateRawOptData() const {
		if (SetValue == true) {
			return UABT::ToDouble(Value);
		}
		return agora::Optional<double>();
	}

	static void FreeRawOptData(agora::Optional<double>& AgoraData) {
	}
};



USTRUCT(BlueprintType)
struct FUABT_Opt_int {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Value = 0;

	FUABT_Opt_int() {}
	FUABT_Opt_int(const agora::Optional<int> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = AgoraOptVal.value();
		}
		else {
			Value = 0;
		}
	}

	agora::Optional<int> CreateRawOptData() const {
		if (SetValue == true) {
			return Value;
		}
		return agora::Optional<int>();
	}

	static void FreeRawOptData(agora::Optional<int>& AgoraData) {
	}
};



USTRUCT(BlueprintType)
struct FUABT_Opt_ConstCharPtr {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString Value = "";

	FUABT_Opt_ConstCharPtr() {}
	FUABT_Opt_ConstCharPtr(const agora::Optional<const char*> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UTF8_TO_TCHAR(AgoraOptVal.value());
		}
		else{
			Value = AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_OPTIONAL_VALUE_NOT_SET];
		}
	}
	agora::Optional<const char*> CreateRawOptData() const {
		if (SetValue == true) {
			return UABT::New_CharPtr(Value);
		}
		return agora::Optional<const char*>();
	}

	static void FreeRawOptData(agora::Optional<const char*> & AgoraData) {
		if (AgoraData.has_value() == true) {
			const char* Ptr = AgoraData.value();
			UABT::Free_CharPtr(Ptr);
			AgoraData = nullptr;
		}
	}
};



USTRUCT(BlueprintType)
struct FUABT_Opt_CLIENT_ROLE_TYPE {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CLIENT_ROLE_TYPE Value = EUABT_CLIENT_ROLE_TYPE::CLIENT_ROLE_AUDIENCE;

	FUABT_Opt_CLIENT_ROLE_TYPE() {}
	FUABT_Opt_CLIENT_ROLE_TYPE(const agora::Optional<agora::rtc::CLIENT_ROLE_TYPE> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABTEnum::WrapWithUE(AgoraOptVal.value());
		}
	}

	agora::Optional<agora::rtc::CLIENT_ROLE_TYPE> CreateRawOptData() const {
		if (SetValue == true) {
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::rtc::CLIENT_ROLE_TYPE>();
	}

	static void FreeRawOptData(agora::Optional<agora::rtc::CLIENT_ROLE_TYPE>& AgoraData) {
	}
};




USTRUCT(BlueprintType)
struct FUABT_Opt_AUDIENCE_LATENCY_LEVEL_TYPE {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIENCE_LATENCY_LEVEL_TYPE Value = EUABT_AUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_LOW_LATENCY;

	FUABT_Opt_AUDIENCE_LATENCY_LEVEL_TYPE() {}
	FUABT_Opt_AUDIENCE_LATENCY_LEVEL_TYPE(const agora::Optional<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABTEnum::WrapWithUE(AgoraOptVal.value());
		}
	}

	agora::Optional<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE> CreateRawOptData() const {
		if (SetValue == true) {
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>();
	}


	static void FreeRawOptData(agora::Optional<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>& AgoraData) {
	}
};



USTRUCT(BlueprintType)
struct FUABT_Opt_CHANNEL_PROFILE_TYPE {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CHANNEL_PROFILE_TYPE Value = EUABT_CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	FUABT_Opt_CHANNEL_PROFILE_TYPE() {}
	FUABT_Opt_CHANNEL_PROFILE_TYPE(const agora::Optional<agora::CHANNEL_PROFILE_TYPE> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = UABTEnum::WrapWithUE(AgoraOptVal.value());
		}
	}

	agora::Optional<agora::CHANNEL_PROFILE_TYPE> CreateRawOptData() const {
		if (SetValue == true) {
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::CHANNEL_PROFILE_TYPE>();
	}

	static void FreeRawOptData(agora::Optional<agora::CHANNEL_PROFILE_TYPE>& AgoraData) {
	}

};



USTRUCT(BlueprintType)
struct FUABT_Opt_video_track_id_t {
	
	GENERATED_BODY()

public:
	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 Value = 0;

	FUABT_Opt_video_track_id_t() {}
	FUABT_Opt_video_track_id_t(const agora::Optional<agora::rtc::video_track_id_t> AgoraOptVal) {
		SetValue = AgoraOptVal.has_value();
		if (SetValue == true) {
			Value = AgoraOptVal.value();
		}
	}

	agora::Optional<agora::rtc::video_track_id_t> CreateRawOptData() const {
		if (SetValue == true) {
			return UABT::ToVTID(Value);
		}
		return agora::Optional<agora::rtc::video_track_id_t>();
	}

	static void FreeRawOptData(agora::Optional<agora::rtc::video_track_id_t>& AgoraData) {

	}
};


USTRUCT(BlueprintType)
struct FUABT_Opt_THREAD_PRIORITY_TYPE {
	
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)

	bool SetValue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_THREAD_PRIORITY_TYPE Value = EUABT_THREAD_PRIORITY_TYPE::NORMAL;

	FUABT_Opt_THREAD_PRIORITY_TYPE(){}
	FUABT_Opt_THREAD_PRIORITY_TYPE(const agora::Optional<agora::rtc::THREAD_PRIORITY_TYPE> AgoraOptVal){
	
		SetValue = AgoraOptVal.has_value();

		Value= UABTEnum::WrapWithUE(AgoraOptVal.value());
	}
	agora::Optional<agora::rtc::THREAD_PRIORITY_TYPE> CreateRawOptData() const {
		if (SetValue == true){
			return UABTEnum::ToRawValue(Value);
		}
		return agora::Optional<agora::rtc::THREAD_PRIORITY_TYPE>();
	}

	static void FreeRawOptData(agora::Optional<agora::rtc::THREAD_PRIORITY_TYPE>& AgoraData) {
	}
};

#pragma endregion Optional Value











#pragma region EventHandler


USTRUCT(BlueprintType)
struct FUABT_LastmileProbeOneWayResult {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 packetLossRate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 jitter = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 availableBandwidth = 0;

	FUABT_LastmileProbeOneWayResult(){}
	FUABT_LastmileProbeOneWayResult(const agora::rtc::LastmileProbeOneWayResult & AgoraData){
		packetLossRate = AgoraData.packetLossRate;
		jitter = AgoraData.jitter;
		availableBandwidth = AgoraData.availableBandwidth;
	}

	agora::rtc::LastmileProbeOneWayResult CreateRawData() const {
		agora::rtc::LastmileProbeOneWayResult AgoraData;
		AgoraData.packetLossRate = packetLossRate;
		AgoraData.jitter = jitter;
		AgoraData.availableBandwidth = availableBandwidth;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LastmileProbeOneWayResult & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_AudioVolumeInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 volume = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 vad = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float voicePitch = 0;

	FUABT_AudioVolumeInfo(){}
	FUABT_AudioVolumeInfo(const agora::rtc::AudioVolumeInfo & AgoraData){
		uid = AgoraData.uid;
		volume = AgoraData.volume;
		vad = AgoraData.vad;
		voicePitch = AgoraData.voicePitch;
	}

	agora::rtc::AudioVolumeInfo CreateRawData() const {
		agora::rtc::AudioVolumeInfo AgoraData;
		AgoraData.uid = uid;
		AgoraData.volume = volume;
		AgoraData.vad = vad;
		AgoraData.voicePitch = voicePitch;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::AudioVolumeInfo & AgoraData) const {

	}


};


USTRUCT(BlueprintType)
struct FUABT_LastmileProbeResult {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_LASTMILE_PROBE_RESULT_STATE state = EUABT_LASTMILE_PROBE_RESULT_STATE::LASTMILE_PROBE_RESULT_UNAVAILABLE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_LastmileProbeOneWayResult uplinkReport = FUABT_LastmileProbeOneWayResult();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_LastmileProbeOneWayResult downlinkReport = FUABT_LastmileProbeOneWayResult();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 rtt = 0;

	FUABT_LastmileProbeResult(){}
	FUABT_LastmileProbeResult(const agora::rtc::LastmileProbeResult & AgoraData){
		state = UABTEnum::WrapWithUE(AgoraData.state);
		uplinkReport = FUABT_LastmileProbeOneWayResult(AgoraData.uplinkReport);
		downlinkReport = FUABT_LastmileProbeOneWayResult(AgoraData.downlinkReport);
		rtt = AgoraData.rtt;
	}

	agora::rtc::LastmileProbeResult CreateRawData() const {
		agora::rtc::LastmileProbeResult AgoraData;
		AgoraData.state = UABTEnum::ToRawValue(state);
		AgoraData.uplinkReport = uplinkReport.CreateRawData();
		AgoraData.downlinkReport = downlinkReport.CreateRawData();
		AgoraData.rtt = rtt;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LastmileProbeResult & AgoraData) const {
		uplinkReport.FreeRawData(AgoraData.uplinkReport);
		downlinkReport.FreeRawData(AgoraData.downlinkReport);
	}
};




USTRUCT(BlueprintType)
struct FUABT_RtcStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 duration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 txBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 rxBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 txAudioBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 txVideoBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 rxAudioBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 rxVideoBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 txKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 rxKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 rxAudioKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 txAudioKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 rxVideoKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 txVideoKBitRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 lastmileDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 userCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString cpuAppUsage = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString cpuTotalUsage = "0";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 gatewayRtt = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString memoryAppUsageRatio = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString memoryTotalUsageRatio = "0";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 memoryAppUsageInKbytes = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 connectTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstAudioPacketDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstVideoPacketDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstVideoKeyFramePacketDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 packetsBeforeFirstKeyFramePacket = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstAudioPacketDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstVideoPacketDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstVideoKeyFramePacketDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstVideoKeyFrameDecodedDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 firstVideoKeyFrameRenderedDurationAfterUnmute = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 txPacketLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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


	agora::rtc::RtcStats CreateRawData(){
	
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

	void FreeRawData(agora::rtc::RtcStats & AgoraData) const {
	}
};



USTRUCT(BlueprintType)
struct FUABT_UplinkNetworkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int video_encoder_target_bitrate_bps = 0;

	FUABT_UplinkNetworkInfo(){}
	FUABT_UplinkNetworkInfo(const agora::rtc::UplinkNetworkInfo & AgoraData){
		video_encoder_target_bitrate_bps = AgoraData.video_encoder_target_bitrate_bps;
	}

	agora::rtc::UplinkNetworkInfo CreateRawData() const {
		agora::rtc::UplinkNetworkInfo AgoraData;
		AgoraData.video_encoder_target_bitrate_bps = video_encoder_target_bitrate_bps;
		return AgoraData;
	}
	void FreeRawData(agora::rtc::UplinkNetworkInfo & AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_PeerDownlinkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString userId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_STREAM_TYPE stream_type = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL current_downscale_level = EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL::REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int expected_bitrate_bps = 0;

	FUABT_PeerDownlinkInfo(){}
	FUABT_PeerDownlinkInfo(const agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo & AgoraData){
		userId = UTF8_TO_TCHAR(AgoraData.userId);
		stream_type = UABTEnum::WrapWithUE(AgoraData.stream_type);
		current_downscale_level = UABTEnum::WrapWithUE(AgoraData.current_downscale_level);
		expected_bitrate_bps = AgoraData.expected_bitrate_bps;
	}

	agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo CreateRawData() const {
		agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo AgoraData;
		AgoraData.userId = UABT::New_CharPtr(this->userId);
		AgoraData.stream_type = UABTEnum::ToRawValue(stream_type);
		AgoraData.current_downscale_level = UABTEnum::ToRawValue(current_downscale_level);
		AgoraData.expected_bitrate_bps = expected_bitrate_bps;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.userId);
	}
};


USTRUCT(BlueprintType)
struct FUABT_DownlinkNetworkInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int lastmile_buffer_delay_time_ms = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int bandwidth_estimation_bps = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int total_downscale_level_count = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_PeerDownlinkInfo> peer_downlink_info;

	FUABT_DownlinkNetworkInfo(){}
	FUABT_DownlinkNetworkInfo(const agora::rtc::DownlinkNetworkInfo & AgoraData){
		lastmile_buffer_delay_time_ms = AgoraData.lastmile_buffer_delay_time_ms;
		bandwidth_estimation_bps = AgoraData.bandwidth_estimation_bps;
		total_downscale_level_count = AgoraData.total_downscale_level_count;
		for (int i = 0; i < AgoraData.total_received_video_count; ++i) {
			peer_downlink_info.Add(FUABT_PeerDownlinkInfo(AgoraData.peer_downlink_info[i]));
		}
	}

	agora::rtc::DownlinkNetworkInfo CreateRawData() const {
		agora::rtc::DownlinkNetworkInfo AgoraData;
		AgoraData.lastmile_buffer_delay_time_ms = lastmile_buffer_delay_time_ms;
		AgoraData.bandwidth_estimation_bps = bandwidth_estimation_bps;
		AgoraData.total_downscale_level_count = total_downscale_level_count;
		AgoraData.total_received_video_count = this->peer_downlink_info.Num();
		AgoraData.peer_downlink_info = UABT::New_RawDataArray<agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo,FUABT_PeerDownlinkInfo>(this->peer_downlink_info);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::DownlinkNetworkInfo & AgoraData) const {
		UABT::Free_RawDataArray<agora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo, FUABT_PeerDownlinkInfo>(AgoraData.peer_downlink_info, AgoraData.total_received_video_count);
	}
};


USTRUCT(BlueprintType)
struct FUABT_LocalAudioStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int numChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int sentSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int sentBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int internalCodec = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int txPacketLossRate = 0; // unsigned short 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioDeviceDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioPlayoutDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int earMonitorDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::LocalAudioStats CreateRawData() const {
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

	void FreeRawData(agora::rtc::LocalAudioStats & AgoraData) const {

	}
};



USTRUCT(BlueprintType)
struct FUABT_RemoteAudioStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int quality = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int networkTransportDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int jitterBufferDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int numChannels = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int receivedSampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int receivedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int totalFrozenTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int frozenRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int mosValue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 frozenRateByCustomPlcCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 plcCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int totalActiveTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int publishDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int qoeQuality = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int qualityChangedReason = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 rxAudioBytes = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::RemoteAudioStats CreateRawData() const {
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

	void FreeRawData(agora::rtc::RemoteAudioStats & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_LocalVideoStats
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int sentBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int sentFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int captureFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int captureFrameWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int captureFrameHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int regulatedCaptureFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int regulatedCaptureFrameWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int regulatedCaptureFrameHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int encoderOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int encodedFrameWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int encodedFrameHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int rendererOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int targetBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int targetFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_QUALITY_ADAPT_INDICATION qualityAdaptIndication = EUABT_QUALITY_ADAPT_INDICATION::ADAPT_NONE;
	int encodedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int encodedFrameCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int txPacketLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE  captureBrightnessLevel = EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool dualStreamEnabled = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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
		qualityAdaptIndication = UABTEnum::WrapWithUE(AgoraData.qualityAdaptIndication);
		encodedBitrate = AgoraData.encodedBitrate;
		encodedFrameCount = AgoraData.encodedFrameCount;
		codecType = UABTEnum::WrapWithUE(AgoraData.codecType);
		txPacketLossRate = AgoraData.txPacketLossRate;
		captureBrightnessLevel = UABTEnum::WrapWithUE(AgoraData.captureBrightnessLevel);
		dualStreamEnabled = AgoraData.dualStreamEnabled;
		hwEncoderAccelerating = AgoraData.hwEncoderAccelerating;
	}

	agora::rtc::LocalVideoStats CreateRawData() const {
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
		AgoraData.qualityAdaptIndication = UABTEnum::ToRawValue(qualityAdaptIndication);
		AgoraData.encodedBitrate = encodedBitrate;
		AgoraData.encodedFrameCount = encodedFrameCount;
		AgoraData.codecType = UABTEnum::ToRawValue(codecType);
		AgoraData.txPacketLossRate = txPacketLossRate;
		AgoraData.captureBrightnessLevel = UABTEnum::ToRawValue(captureBrightnessLevel);
		AgoraData.dualStreamEnabled = dualStreamEnabled;
		AgoraData.hwEncoderAccelerating = hwEncoderAccelerating;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LocalVideoStats & AgoraData) const
	{

	}
};



USTRUCT(BlueprintType)
struct FUABT_RemoteVideoStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int delay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int e2eDelay = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int receivedBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int decoderOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int rendererOutputFrameRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int frameLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int packetLossRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_STREAM_TYPE rxStreamType = EUABT_VIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int totalFrozenTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int frozenRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int avSyncTimeMs = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int totalActiveTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int publishDuration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int mosValue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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
		rxStreamType = UABTEnum::WrapWithUE(AgoraData.rxStreamType);
		totalFrozenTime = AgoraData.totalFrozenTime;
		frozenRate = AgoraData.frozenRate;
		avSyncTimeMs = AgoraData.avSyncTimeMs;
		totalActiveTime = AgoraData.totalActiveTime;
		publishDuration = AgoraData.publishDuration;
		mosValue = AgoraData.mosValue;
		rxVideoBytes = AgoraData.rxVideoBytes;
	}

	agora::rtc::RemoteVideoStats CreateRawData() const {
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
		AgoraData.rxStreamType = UABTEnum::ToRawValue(rxStreamType);
		AgoraData.totalFrozenTime = totalFrozenTime;
		AgoraData.frozenRate = frozenRate;
		AgoraData.avSyncTimeMs = avSyncTimeMs;
		AgoraData.totalActiveTime = totalActiveTime;
		AgoraData.publishDuration = publishDuration;
		AgoraData.mosValue = mosValue;
		AgoraData.rxVideoBytes = rxVideoBytes;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::RemoteVideoStats & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_WlAccStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 e2eDelayPercent = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 frozenRatioPercent = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 lossRatePercent = 0;

	FUABT_WlAccStats(){}
	FUABT_WlAccStats(const agora::rtc::WlAccStats & AgoraData){
		e2eDelayPercent = AgoraData.e2eDelayPercent;
		frozenRatioPercent = AgoraData.frozenRatioPercent;
		lossRatePercent = AgoraData.lossRatePercent;
	}

	agora::rtc::WlAccStats CreateRawData() const {
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString userAccount = "";

	FUABT_UserInfo(){}
	FUABT_UserInfo(const agora::rtc::UserInfo & AgoraData){
		uid = AgoraData.uid;
		userAccount = UTF8_TO_TCHAR(AgoraData.userAccount);
	}

	agora::rtc::UserInfo CreateRawData() const {
		agora::rtc::UserInfo AgoraData;
		AgoraData.uid = uid;
		UABT::SetCharArrayPtr(AgoraData.userAccount, this->userAccount, agora::rtc::MAX_USER_ACCOUNT_LENGTH);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::UserInfo & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_VideoRenderingTracingInfo {

	GENERATED_BODY()

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int elapsedTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int start2JoinChannel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int join2JoinSuccess = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int joinSuccess2RemoteJoined = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int remoteJoined2SetView = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int remoteJoined2UnmuteVideo = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::VideoRenderingTracingInfo CreateRawData() const {
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

	void FreeRawData(agora::rtc::VideoRenderingTracingInfo& AgoraData) const {
		// no need to free
	}
};



USTRUCT(BlueprintType)
struct FUABT_TranscodingVideoStream {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_SOURCE_TYPE sourceType = EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 remoteUserUid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString imageUrl = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int mediaPlayerId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int zOrder = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float alpha = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool mirror = false;

	FUABT_TranscodingVideoStream(){}
	FUABT_TranscodingVideoStream(const agora::rtc::TranscodingVideoStream & AgoraData){
		sourceType = UABTEnum::WrapWithUE(AgoraData.sourceType);

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

	agora::rtc::TranscodingVideoStream CreateRawData() const{
		
		agora::rtc::TranscodingVideoStream AgoraData;
		AgoraData.sourceType = UABTEnum::ToRawValue(sourceType);
		AgoraData.remoteUserUid = remoteUserUid;
		AgoraData.imageUrl = UABT::New_CharPtr(this->imageUrl);
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

	void FreeRawData(agora::rtc::TranscodingVideoStream & AgoraData) const{
		UABT::Free_CharPtr(AgoraData.imageUrl);
	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoLayout
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString channelId = "";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString strUid = "";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 x = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 y = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 width = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::VideoLayout CreateRawData() const {
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

	void FreeRawData(agora::VideoLayout & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelId);
		UABT::Free_CharPtr(AgoraData.strUid);
	}
};


USTRUCT(BlueprintType)
struct FUABT_AgoraMetadata
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 size = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 timeStampMs = 0;

	FUABT_AgoraMetadata(){}
	FUABT_AgoraMetadata(const agora::rtc::IMetadataObserver::Metadata & AgoraData){
		uid = AgoraData.uid;
		size = AgoraData.size;
		buffer = UTF8_TO_TCHAR(AgoraData.buffer);
		timeStampMs = AgoraData.timeStampMs;
	}

	agora::rtc::IMetadataObserver::Metadata CreateRawData() const {
		agora::rtc::IMetadataObserver::Metadata AgoraData;
		AgoraData.uid = uid;
		AgoraData.size = size;
		AgoraData.buffer = UABT::New_UnsignedCharPtr(this->buffer);
		AgoraData.timeStampMs = timeStampMs;
		return AgoraData;
	}
	void FreeRawData (agora::rtc::IMetadataObserver::Metadata& AgoraData){
		UABT::Free_UnsignedCharPtr(AgoraData.buffer);
	}
};


USTRUCT(BlueprintType)
struct FUABT_DirectCdnStreamingStats {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int fps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioBitrate = 0;

	FUABT_DirectCdnStreamingStats(){}
	FUABT_DirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats & AgoraData){
		videoWidth = AgoraData.videoWidth;
		videoHeight = AgoraData.videoHeight;
		fps = AgoraData.fps;
		videoBitrate = AgoraData.videoBitrate;
		audioBitrate = AgoraData.audioBitrate;
	}

	agora::rtc::DirectCdnStreamingStats CreateRawData() const {
		agora::rtc::DirectCdnStreamingStats AgoraData;
		AgoraData.videoWidth = videoWidth;
		AgoraData.videoHeight = videoHeight;
		AgoraData.fps = fps;
		AgoraData.videoBitrate = videoBitrate;
		AgoraData.audioBitrate = audioBitrate;
		return AgoraData;
	}
	void FreeRawData(agora::rtc::DirectCdnStreamingStats & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_ExtensionContext {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isValid = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString providerName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString extensionName = "";

	FUABT_ExtensionContext(){}
	FUABT_ExtensionContext(const agora::rtc::ExtensionContext& AgoraData){
		isValid = AgoraData.isValid;
		uid = AgoraData.uid;
		providerName = UTF8_TO_TCHAR(AgoraData.providerName);
		extensionName = UTF8_TO_TCHAR(AgoraData.extensionName);
	}

	agora::rtc::ExtensionContext CreateRawData() const {
		agora::rtc::ExtensionContext AgoraData;
		AgoraData.isValid = isValid;
		AgoraData.uid = uid;
		AgoraData.providerName = UABT::New_CharPtr(providerName);
		AgoraData.extensionName = UABT::New_CharPtr(extensionName);
		return AgoraData;
	}
	void FreeRawData(agora::rtc::ExtensionContext& AgoraData) const {
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_ENCRYPTION_MODE encryptionMode = EUABT_ENCRYPTION_MODE::AES_128_GCM2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString encryptionKey = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString encryptionKdfSalt = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool datastreamEncryptionEnabled = false;

	FUABT_EncryptionConfig(){}
	FUABT_EncryptionConfig(const agora::rtc::EncryptionConfig & AgoraData){
		encryptionMode = UABTEnum::WrapWithUE(AgoraData.encryptionMode);
		encryptionKey = UTF8_TO_TCHAR(AgoraData.encryptionKey);

		char valencryptionKdfSalt[32] = {0};
		int AgoraCount = 32;
		for (int i = 0; i < AgoraCount; i++) {

			encryptionKdfSalt[i] = AgoraData.encryptionKdfSalt[i];
		}
		encryptionKdfSalt = valencryptionKdfSalt;

		datastreamEncryptionEnabled = AgoraData.datastreamEncryptionEnabled;
	}

	agora::rtc::EncryptionConfig CreateRawData() const {
		agora::rtc::EncryptionConfig AgoraData;
		AgoraData.encryptionMode = UABTEnum::ToRawValue(encryptionMode);
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

	void FreeRawData(agora::rtc::EncryptionConfig & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.encryptionKey);
	}
};

#pragma endregion Rtc Engine


USTRUCT(BlueprintType)
struct FUABT_ClientRoleOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel = EUABT_AUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY;

	FUABT_ClientRoleOptions() {}

	FUABT_ClientRoleOptions(const agora::rtc::ClientRoleOptions& AgoraData) {
		audienceLatencyLevel = UABTEnum::WrapWithUE(AgoraData.audienceLatencyLevel);
	}

	agora::rtc::ClientRoleOptions CreateRawData() const {
		agora::rtc::ClientRoleOptions AgoraData;
		AgoraData.audienceLatencyLevel = UABTEnum::ToRawValue(audienceLatencyLevel);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ClientRoleOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_SenderOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_TCcMode ccMode = EUABT_TCcMode::CC_ENABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int targetBitrate = 6500;


	agora::rtc::SenderOptions CreateRawData() const {
		agora::rtc::SenderOptions AgoraData;
		AgoraData.ccMode = (agora::rtc::TCcMode)ccMode;
		AgoraData.codecType = (agora::rtc::VIDEO_CODEC_TYPE)codecType;
		AgoraData.targetBitrate = targetBitrate;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::SenderOptions& AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_Rectangle
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 0;

	FUABT_Rectangle(){}
	FUABT_Rectangle(const agora::rtc::Rectangle & AgoraData){
		x = AgoraData.x;
		y = AgoraData.y;
		width = AgoraData.width;
		height = AgoraData.height;
	}

	agora::rtc::Rectangle CreateRawData() const {
		agora::rtc::Rectangle AgoraData;
		AgoraData.x = x;
		AgoraData.y = y;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::Rectangle& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoCanvas
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 subviewUid = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UImage* view = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 backgroundColor = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_RENDER_MODE_TYPE renderMode = EUABT_RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode = EUABT_VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_VIEW_SETUP_MODE setupMode = EUABT_VIDEO_VIEW_SETUP_MODE::VIDEO_VIEW_SETUP_REPLACE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_SOURCE_TYPE sourceType = EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int mediaPlayerId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Rectangle cropArea;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool enableAlphaMask = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_MODULE_POSITION position = EUABT_VIDEO_MODULE_POSITION::POSITION_POST_CAPTURER;


	FUABT_VideoCanvas(){}
	FUABT_VideoCanvas(const agora::rtc::VideoCanvas & AgoraData){
		view = nullptr; // [not support]
		uid = AgoraData.uid;
		subviewUid = AgoraData.subviewUid;
		backgroundColor = AgoraData.backgroundColor;
		renderMode = UABTEnum::WrapWithUE(AgoraData.renderMode);
		mirrorMode = UABTEnum::WrapWithUE(AgoraData.mirrorMode);
		setupMode = UABTEnum::WrapWithUE(AgoraData.setupMode);
		sourceType = UABTEnum::WrapWithUE(AgoraData.sourceType);
		mediaPlayerId = AgoraData.mediaPlayerId;
		cropArea = FUABT_Rectangle(AgoraData.cropArea);
		enableAlphaMask = AgoraData.enableAlphaMask;
		position = UABTEnum::WrapWithUE(AgoraData.position);
	}

	agora::rtc::VideoCanvas CreateRawData() const {
		agora::rtc::VideoCanvas AgoraData;
		AgoraData.view = (agora::view_t) view;
		AgoraData.uid = uid;
		AgoraData.subviewUid = subviewUid;
		AgoraData.backgroundColor = backgroundColor;
		AgoraData.renderMode = UABTEnum::ToRawValue(renderMode);
		AgoraData.mirrorMode = UABTEnum::ToRawValue(mirrorMode);
		AgoraData.setupMode = UABTEnum::ToRawValue(setupMode);
		AgoraData.sourceType = UABTEnum::ToRawValue(sourceType);
		AgoraData.mediaPlayerId = AgoraData.mediaPlayerId;
		AgoraData.cropArea = cropArea.CreateRawData();
		AgoraData.enableAlphaMask = enableAlphaMask;
		AgoraData.position = UABTEnum::ToRawValue(position);

		return AgoraData;
	}

	void FreeRawData(agora::rtc::VideoCanvas& AgoraData) const {
		cropArea.FreeRawData(AgoraData.cropArea);
	}
};


USTRUCT(BlueprintType)
struct FUABT_LogConfig {

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString filePath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 fileSizeInKB = 2048;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_LOG_LEVEL level = EUABT_LOG_LEVEL::LOG_LEVEL_INFO;

	FUABT_LogConfig() {}
	FUABT_LogConfig(const agora::commons::LogConfig& AgoraData) {
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		fileSizeInKB = AgoraData.fileSizeInKB;
		level = UABTEnum::WrapWithUE(AgoraData.level);
	}

	agora::commons::LogConfig CreateRawData() const {
		agora::commons::LogConfig AgoraData;

		AgoraData.filePath = UABT::New_CharPtr(filePath);
		AgoraData.fileSizeInKB = UABT::ToUInt32(fileSizeInKB);
		AgoraData.level = UABTEnum::ToRawValue(level);
		return AgoraData;
	}

	void FreeRawData(agora::commons::LogConfig& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.filePath);
	}
};


USTRUCT(BlueprintType)
struct FUABT_RtcEngineContext
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EAgoraBPuEventHandlerType EventHandlerCreationType = EAgoraBPuEventHandlerType::EventHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString appId = "";

	//UIRtcEngineEventHandler* eventHandler = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//int64 context = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CHANNEL_PROFILE_TYPE channelProfile = EUABT_CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString license = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIO_SCENARIO_TYPE audioScenario = EUABT_AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT;
	

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AREA_CODE areaCode = EUABT_AREA_CODE::AREA_CODE_GLOB;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_LogConfig logConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_THREAD_PRIORITY_TYPE threadPriority;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool useExternalEglContext = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool domainLimit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool autoRegisterAgoraExtensions = true;


	FUABT_RtcEngineContext() {}

	FUABT_RtcEngineContext(const agora::rtc::RtcEngineContext& AgoraData) {
		appId = UTF8_TO_TCHAR(AgoraData.appId);
		channelProfile = UABTEnum::WrapWithUE(AgoraData.channelProfile);
		license = UTF8_TO_TCHAR(AgoraData.license);
		audioScenario = UABTEnum::WrapWithUE(AgoraData.audioScenario);
		areaCode = UABTEnum::WrapWithUE(static_cast<agora::rtc::AREA_CODE>(AgoraData.areaCode));
		logConfig = AgoraData.logConfig;
		threadPriority = AgoraData.threadPriority;
		useExternalEglContext = AgoraData.useExternalEglContext;
		domainLimit = AgoraData.domainLimit;
		autoRegisterAgoraExtensions = AgoraData.autoRegisterAgoraExtensions;
	}

	agora::rtc::RtcEngineContext CreateRawData() const {

		agora::rtc::RtcEngineContext AgoraData;

		//AgoraData.eventHandler = UABTEnum::ToRawValue(eventHandler);

		AgoraData.appId = UABT::New_CharPtr(this->appId);
		AgoraData.appId = UABT::New_CharPtr(appId);

		//AgoraData.context = nullptr; // not supported

		AgoraData.channelProfile = (agora::CHANNEL_PROFILE_TYPE)channelProfile;
		
		AgoraData.license = UABT::New_CharPtr(this->license);

		AgoraData.audioScenario = (agora::rtc::AUDIO_SCENARIO_TYPE)audioScenario;

		AgoraData.areaCode = (unsigned int) UABTEnum::ToRawValue(areaCode);

		AgoraData.logConfig = logConfig.CreateRawData();


		AgoraData.threadPriority = threadPriority.CreateRawOptData();

		AgoraData.useExternalEglContext = useExternalEglContext;

		AgoraData.domainLimit = domainLimit;

		AgoraData.autoRegisterAgoraExtensions = autoRegisterAgoraExtensions;
		
		return AgoraData;
	}


	void FreeRawData(agora::rtc::RtcEngineContext& AgoraData) const {

		UABT::Free_CharPtr(AgoraData.appId);
		UABT::Free_CharPtr(AgoraData.license);
		logConfig.FreeRawData(AgoraData.logConfig);
	}
};

USTRUCT(BlueprintType)
struct FUABT_RtcConnection
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 localUid = 0;

	FUABT_RtcConnection(){}
	FUABT_RtcConnection(const agora::rtc::RtcConnection & AgoraData){
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		localUid = AgoraData.localUid;
	}

	agora::rtc::RtcConnection CreateRawData() const {
		agora::rtc::RtcConnection AgoraData;
		AgoraData.channelId = UABT::New_CharPtr(channelId);
		AgoraData.localUid = localUid;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::RtcConnection & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelId);
	}
	
};






#pragma region Rtc Engine 2


USTRUCT(BlueprintType)
struct FUABT_CodecCapLevels {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_CAPABILITY_LEVEL hwDecodingLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_CAPABILITY_LEVEL swDecodingLevel;
	
	FUABT_CodecCapLevels() {}
	FUABT_CodecCapLevels(const agora::rtc::CodecCapLevels& AgoraData) {
		hwDecodingLevel = UABTEnum::WrapWithUE(AgoraData.hwDecodingLevel);
		swDecodingLevel = UABTEnum::WrapWithUE(AgoraData.swDecodingLevel);
	}

	agora::rtc::CodecCapLevels CreateRawData() const {
		agora::rtc::CodecCapLevels AgoraData;
		AgoraData.hwDecodingLevel = UABTEnum::ToRawValue(hwDecodingLevel);
		AgoraData.swDecodingLevel = UABTEnum::ToRawValue(swDecodingLevel);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::CodecCapLevels& AgoraData) const {
		// no need to free
	}
};

USTRUCT(BlueprintType)
struct FUABT_CodecCapInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int codecCapMask = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_CodecCapLevels codecLevels;

	FUABT_CodecCapInfo(){}
	FUABT_CodecCapInfo(const agora::rtc::CodecCapInfo & AgoraData){
		codecType = UABTEnum::WrapWithUE(AgoraData.codecType);
		codecCapMask = AgoraData.codecCapMask;
		codecLevels = AgoraData.codecLevels;
	}

	agora::rtc::CodecCapInfo CreateRawData() const {
		agora::rtc::CodecCapInfo AgoraData;
		AgoraData.codecType = UABTEnum::ToRawValue(codecType);
		AgoraData.codecCapMask = codecCapMask;
		AgoraData.codecLevels = codecLevels.CreateRawData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::CodecCapInfo& AgoraData) const {
		codecLevels.FreeRawData(AgoraData.codecLevels);
	}
};



USTRUCT(BlueprintType)
struct FUABT_ChannelMediaOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishCameraTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishSecondaryCameraTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishThirdCameraTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishFourthCameraTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishMicrophoneTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishScreenCaptureVideo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishScreenCaptureAudio;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishScreenTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishSecondaryScreenTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishThirdScreenTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishFourthScreenTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishCustomAudioTrack;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_int publishCustomAudioTrackId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishCustomVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishEncodedVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishMediaPlayerAudioTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishMediaPlayerVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishTranscodedVideoTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishMixedAudioTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishLipSyncTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EAgoraOptional autoSubscribeAudio = EAgoraOptional::AGORA_TRUE_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EAgoraOptional autoSubscribeVideo = EAgoraOptional::AGORA_TRUE_VALUE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool enableAudioRecordingOrPlayout;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_int publishMediaPlayerId;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool clientRoleType_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CLIENT_ROLE_TYPE clientRoleType = EUABT_CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_AUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_VIDEO_STREAM_TYPE defaultVideoStreamType;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool channelProfile_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CHANNEL_PROFILE_TYPE channelProfile = EUABT_CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_int audioDelayMs;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_int mediaPlayerAudioDelayMs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_ConstCharPtr token;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool enableBuiltInMediaEncryption;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool publishRhythmPlayerTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool isInteractiveAudience;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_video_track_id_t customVideoTrackId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool isAudioFilterable;


	FUABT_ChannelMediaOptions(){}

	FUABT_ChannelMediaOptions(const agora::rtc::ChannelMediaOptions & AgoraData){
		
		this->publishCameraTrack = AgoraData.publishCameraTrack;
		this->publishSecondaryCameraTrack = AgoraData.publishSecondaryCameraTrack;
		this->publishThirdCameraTrack = AgoraData.publishThirdCameraTrack;
		this->publishFourthCameraTrack = AgoraData.publishFourthCameraTrack;
		this->publishMicrophoneTrack = AgoraData.publishMicrophoneTrack;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
		
		this->publishScreenCaptureVideo = AgoraData.publishScreenCaptureVideo;
		this->publishScreenCaptureAudio = AgoraData.publishScreenCaptureAudio;
#else
		this->publishScreenTrack = AgoraData.publishScreenTrack;
		this->publishSecondaryScreenTrack = AgoraData.publishSecondaryScreenTrack;
		this->publishThirdScreenTrack = AgoraData.publishThirdScreenTrack;
		this->publishFourthScreenTrack = AgoraData.publishFourthScreenTrack;

#endif

		this->publishCustomAudioTrack = AgoraData.publishCustomAudioTrack;

		this->publishCustomAudioTrackId = AgoraData.publishCustomAudioTrackId;

		this->publishCustomVideoTrack = AgoraData.publishCustomVideoTrack;

		this->audienceLatencyLevel = AgoraData.audienceLatencyLevel;
		
		this->publishEncodedVideoTrack = AgoraData.publishEncodedVideoTrack;

		this->publishMediaPlayerAudioTrack = AgoraData.publishMediaPlayerAudioTrack;

		this->publishMediaPlayerVideoTrack = AgoraData.publishMediaPlayerVideoTrack;
		this->publishTranscodedVideoTrack = AgoraData.publishTranscodedVideoTrack;
		this->publishMixedAudioTrack = AgoraData.publishMixedAudioTrack;
		this->publishLipSyncTrack = AgoraData.publishLipSyncTrack;


		SET_UEBP_OPTIONAL_VAL_BOOL(this->autoSubscribeAudio, AgoraData.autoSubscribeAudio)
		SET_UEBP_OPTIONAL_VAL_BOOL(this->autoSubscribeVideo, AgoraData.autoSubscribeVideo)


		this->enableAudioRecordingOrPlayout = AgoraData.enableAudioRecordingOrPlayout;
		this->publishMediaPlayerId = AgoraData.publishMediaPlayerId;

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->clientRoleType,AgoraData.clientRoleType, UABTEnum::WrapWithUE(AgoraData.clientRoleType.value()))
			
		this->audienceLatencyLevel = AgoraData.audienceLatencyLevel;

		this->defaultVideoStreamType = AgoraData.defaultVideoStreamType;

		SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(this->channelProfile, AgoraData.channelProfile, UABTEnum::WrapWithUE(AgoraData.channelProfile.value()))


		this->audioDelayMs = AgoraData.audioDelayMs;

		this->mediaPlayerAudioDelayMs = AgoraData.mediaPlayerAudioDelayMs;
		
		this->token = AgoraData.token;
			
		this->enableBuiltInMediaEncryption = AgoraData.enableBuiltInMediaEncryption;

		this->publishRhythmPlayerTrack = AgoraData.publishRhythmPlayerTrack;

		this->isInteractiveAudience = AgoraData.isInteractiveAudience;

		this->customVideoTrackId = AgoraData.customVideoTrackId;

		this->isAudioFilterable = AgoraData.isAudioFilterable;
	}

	agora::rtc::ChannelMediaOptions CreateRawData() const{
		agora::rtc::ChannelMediaOptions AgoraData;
		AgoraData.publishCameraTrack = this->publishCameraTrack.CreateRawOptData();

		AgoraData.publishSecondaryCameraTrack = this->publishSecondaryCameraTrack.CreateRawOptData();
		AgoraData.publishThirdCameraTrack = this->publishThirdCameraTrack.CreateRawOptData();
		AgoraData.publishFourthCameraTrack = this->publishFourthCameraTrack.CreateRawOptData();
		AgoraData.publishMicrophoneTrack = this->publishMicrophoneTrack.CreateRawOptData();

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)

		AgoraData.publishScreenCaptureVideo = this->publishScreenCaptureVideo.CreateRawOptData();
		AgoraData.publishScreenCaptureAudio = this->publishScreenCaptureAudio.CreateRawOptData();
#else
		
		AgoraData.publishScreenTrack = this->publishScreenTrack.CreateRawOptData();
		AgoraData.publishSecondaryScreenTrack = this->publishSecondaryScreenTrack.CreateRawOptData();
		AgoraData.publishThirdScreenTrack = this->publishThirdScreenTrack.CreateRawOptData();
		AgoraData.publishFourthScreenTrack = this->publishFourthScreenTrack.CreateRawOptData();
#endif

		AgoraData.publishCustomAudioTrack = this->publishCustomAudioTrack.CreateRawOptData();

		AgoraData.publishCustomAudioTrackId = this->publishCustomAudioTrackId.CreateRawOptData();

		AgoraData.publishCustomVideoTrack = this->publishCustomVideoTrack.CreateRawOptData();
		AgoraData.publishEncodedVideoTrack = this->publishEncodedVideoTrack.CreateRawOptData();
		AgoraData.publishMediaPlayerAudioTrack = this->publishMediaPlayerAudioTrack.CreateRawOptData();
		AgoraData.publishMediaPlayerVideoTrack = this->publishMediaPlayerVideoTrack.CreateRawOptData();
		AgoraData.publishTranscodedVideoTrack = this->publishTranscodedVideoTrack.CreateRawOptData();
		AgoraData.publishMixedAudioTrack = this->publishMixedAudioTrack.CreateRawOptData();
		AgoraData.publishLipSyncTrack = this->publishLipSyncTrack.CreateRawOptData();

		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.autoSubscribeAudio, this->autoSubscribeAudio)
		SET_AGORA_OPTIONAL_VAL_BOOL(AgoraData.autoSubscribeVideo, this->autoSubscribeVideo)

		AgoraData.enableAudioRecordingOrPlayout = this->enableAudioRecordingOrPlayout.CreateRawOptData();
		AgoraData.publishMediaPlayerId = this->publishMediaPlayerId.CreateRawOptData();

		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.clientRoleType, this->clientRoleType, UABTEnum::ToRawValue(this->clientRoleType))

		AgoraData.audienceLatencyLevel = this->audienceLatencyLevel.CreateRawOptData();

		AgoraData.defaultVideoStreamType = this->defaultVideoStreamType.CreateRawOptData();

		SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(AgoraData.channelProfile, this->channelProfile, UABTEnum::ToRawValue(this->channelProfile))

		AgoraData.audioDelayMs = this->audioDelayMs.CreateRawOptData();
		
		AgoraData.mediaPlayerAudioDelayMs = this->mediaPlayerAudioDelayMs.CreateRawOptData();
		AgoraData.token = this->token.CreateRawOptData();

		AgoraData.enableBuiltInMediaEncryption = this->enableBuiltInMediaEncryption.CreateRawOptData();
		AgoraData.publishRhythmPlayerTrack = this->publishRhythmPlayerTrack.CreateRawOptData();
		AgoraData.isInteractiveAudience = this->isInteractiveAudience.CreateRawOptData();
		AgoraData.customVideoTrackId = this->customVideoTrackId.CreateRawOptData();
		AgoraData.isAudioFilterable = this->isAudioFilterable.CreateRawOptData();

		return AgoraData;
	}

	void FreeRawData(agora::rtc::ChannelMediaOptions& AgoraData) const {
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishCameraTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishSecondaryCameraTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishThirdCameraTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishFourthCameraTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishMicrophoneTrack);
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishScreenCaptureVideo);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishScreenCaptureAudio);
#else
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishScreenTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishSecondaryScreenTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishThirdScreenTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishFourthScreenTrack);
#endif
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishCustomAudioTrack);

		FUABT_Opt_int::FreeRawOptData(AgoraData.publishCustomAudioTrackId);

		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishCustomVideoTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishEncodedVideoTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishMediaPlayerAudioTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishMediaPlayerVideoTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishTranscodedVideoTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishMixedAudioTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishLipSyncTrack);

		// AgoraData.autoSubscribeAudio 
		// AgoraData.autoSubscribeVideo

		FUABT_Opt_bool::FreeRawOptData(AgoraData.enableAudioRecordingOrPlayout);
		FUABT_Opt_int::FreeRawOptData(AgoraData.publishMediaPlayerId);


		// AgoraData.clientRoleType

		FUABT_Opt_AUDIENCE_LATENCY_LEVEL_TYPE::FreeRawOptData(AgoraData.audienceLatencyLevel);

		FUABT_Opt_VIDEO_STREAM_TYPE::FreeRawOptData(AgoraData.defaultVideoStreamType);

		// AgoraData.channelProfile

		FUABT_Opt_int::FreeRawOptData(AgoraData.audioDelayMs);
		FUABT_Opt_int::FreeRawOptData(AgoraData.mediaPlayerAudioDelayMs);
	
		FUABT_Opt_ConstCharPtr::FreeRawOptData(AgoraData.token);

		FUABT_Opt_bool::FreeRawOptData(AgoraData.enableBuiltInMediaEncryption);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.publishRhythmPlayerTrack);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.isInteractiveAudience);
		FUABT_Opt_video_track_id_t::FreeRawOptData(AgoraData.customVideoTrackId);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.isAudioFilterable);


	}
};



USTRUCT(BlueprintType)
struct FUABT_LeaveChannelOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool stopAudioMixing = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool stopAllEffect = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool stopMicrophoneRecording = true;

	
	FUABT_LeaveChannelOptions() {}

	FUABT_LeaveChannelOptions(const agora::rtc::LeaveChannelOptions& AgoraData) {
		this->stopAudioMixing = AgoraData.stopAudioMixing;
		this->stopAllEffect = AgoraData.stopAllEffect;
		this->stopMicrophoneRecording = AgoraData.stopMicrophoneRecording;
	}

	agora::rtc::LeaveChannelOptions CreateRawData() const {
		agora::rtc::LeaveChannelOptions AgoraData;
		AgoraData.stopAudioMixing = this->stopAudioMixing;
		AgoraData.stopAllEffect = this->stopAllEffect;
		AgoraData.stopMicrophoneRecording = this->stopMicrophoneRecording;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LeaveChannelOptions& AgoraData) const {

	}

};



USTRUCT(BlueprintType)
struct FUABT_EchoTestConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UImage* view = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool enableAudio = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool enableVideo = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString token = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::EchoTestConfiguration CreateRawData() const{
		agora::rtc::EchoTestConfiguration AgoraData;
		//AgoraData.view = view;
		AgoraData.enableAudio = enableAudio;
		AgoraData.enableVideo = enableVideo;

		AgoraData.token = UABT::New_CharPtr(this->token);
		AgoraData.channelId = UABT::New_CharPtr(this->channelId);

		AgoraData.intervalInSeconds = intervalInSeconds;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::EchoTestConfiguration& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.token);
		UABT::Free_CharPtr(AgoraData.channelId);
	}

};


USTRUCT(BlueprintType)
struct FUABT_VideoFormat {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int fps = 15;

	FUABT_VideoFormat(){}
	FUABT_VideoFormat(const agora::rtc::VideoFormat & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
		fps = AgoraData.fps;
	}

	agora::rtc::VideoFormat CreateRawData() const {
		agora::rtc::VideoFormat AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.fps = fps;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::VideoFormat& AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_CameraCapturerConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CAMERA_DIRECTION cameraDirection = EUABT_CAMERA_DIRECTION::CAMERA_FRONT;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CAMERA_FOCAL_LENGTH_TYPE cameraFocalLengthType = EUABT_CAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_ConstCharPtr deviceId;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_ConstCharPtr cameraId;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoFormat format = FUABT_VideoFormat();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool followEncodeDimensionRatio;


	FUABT_CameraCapturerConfiguration(){}
	FUABT_CameraCapturerConfiguration(const agora::rtc::CameraCapturerConfiguration & AgoraData){
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
		cameraDirection = UABTEnum::WrapWithUE(AgoraData.cameraDirection.value());
		cameraFocalLengthType = UABTEnum::WrapWithUE(AgoraData.cameraFocalLengthType.value());
#else

		this->deviceId = AgoraData.deviceId;
#endif

#if defined(__ANDROID__)
		cameraId = AgoraData.cameraId;
#endif

		format = FUABT_VideoFormat(AgoraData.format);
		followEncodeDimensionRatio = AgoraData.followEncodeDimensionRatio;
	}

	agora::rtc::CameraCapturerConfiguration CreateRawData() const {
		agora::rtc::CameraCapturerConfiguration AgoraData;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
		AgoraData.cameraDirection = UABTEnum::ToRawValue(cameraDirection);
		AgoraData.cameraFocalLengthType = UABTEnum::ToRawValue(cameraFocalLengthType);
#else

		AgoraData.deviceId = deviceId.CreateRawOptData();
#endif

#if defined(__ANDROID__)
		AgoraData.cameraId = cameraId.CreateRawOptData();
#endif

		AgoraData.format = format.CreateRawData();

		AgoraData.followEncodeDimensionRatio = this->followEncodeDimensionRatio.CreateRawOptData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::CameraCapturerConfiguration& AgoraData) const {
		format.FreeRawData(AgoraData.format);


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)

#else
		FUABT_Opt_ConstCharPtr::FreeRawOptData(AgoraData.deviceId);
#endif

#if defined(__ANDROID__)
		FUABT_Opt_ConstCharPtr::FreeRawOptData(AgoraData.cameraId);

#endif
			
		FUABT_Opt_bool::FreeRawOptData(AgoraData.followEncodeDimensionRatio);
	}
};



USTRUCT(BlueprintType)
struct FUABT_LastmileProbeConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool probeUplink = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool probeDownlink = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int expectedUplinkBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int expectedDownlinkBitrate = 0;

	FUABT_LastmileProbeConfig(){}
	FUABT_LastmileProbeConfig(const agora::rtc::LastmileProbeConfig & AgoraData){
		probeUplink = AgoraData.probeUplink;
		probeDownlink = AgoraData.probeDownlink;
		expectedUplinkBitrate = AgoraData.expectedUplinkBitrate;
		expectedDownlinkBitrate = AgoraData.expectedDownlinkBitrate;
	}

	agora::rtc::LastmileProbeConfig CreateRawData() const{
		agora::rtc::LastmileProbeConfig AgoraData;
		AgoraData.probeUplink = probeUplink;
		AgoraData.probeDownlink = probeDownlink;
		AgoraData.expectedUplinkBitrate = expectedUplinkBitrate;
		AgoraData.expectedDownlinkBitrate = expectedDownlinkBitrate;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LastmileProbeConfig& AgoraData) const {

	}
};



USTRUCT(BlueprintType)
struct FUABT_VideoDimensions {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 480;

	FUABT_VideoDimensions(){}
	FUABT_VideoDimensions(const agora::rtc::VideoDimensions & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
	}

	agora::rtc::VideoDimensions CreateRawData() const{
		agora::rtc::VideoDimensions AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::VideoDimensions& AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_AdvanceOptions {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_ENCODING_PREFERENCE encodingPreference = EUABT_ENCODING_PREFERENCE::PREFER_AUTO;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_COMPRESSION_PREFERENCE compressionPreference = EUABT_COMPRESSION_PREFERENCE::PREFER_QUALITY;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool encodeAlpha = false;


	FUABT_AdvanceOptions() {}

	FUABT_AdvanceOptions(const agora::rtc::AdvanceOptions & AgoraData){
		encodingPreference = UABTEnum::WrapWithUE(AgoraData.encodingPreference);
		compressionPreference = UABTEnum::WrapWithUE(AgoraData.compressionPreference);
		encodeAlpha = AgoraData.encodeAlpha;
	}

	agora::rtc::AdvanceOptions CreateRawData() const{
		agora::rtc::AdvanceOptions AgoraData;
		AgoraData.encodingPreference = UABTEnum::ToRawValue(encodingPreference);
		AgoraData.compressionPreference = UABTEnum::ToRawValue(compressionPreference);
		AgoraData.encodeAlpha = encodeAlpha;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::AdvanceOptions& AgoraData) const {
		// no need to free
	}
};

USTRUCT(BlueprintType)
struct FUABT_VideoEncoderConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_TYPE codecType = EUABT_VIDEO_CODEC_TYPE::VIDEO_CODEC_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int frameRate = 15;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int bitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int minBitrate = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_ORIENTATION_MODE orientationMode = EUABT_ORIENTATION_MODE::ORIENTATION_MODE_ADAPTIVE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_DEGRADATION_PREFERENCE degradationPreference = EUABT_DEGRADATION_PREFERENCE::MAINTAIN_QUALITY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode = EUABT_VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_DISABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_AdvanceOptions advanceOptions = FUABT_AdvanceOptions();

	FUABT_VideoEncoderConfiguration(){}
	FUABT_VideoEncoderConfiguration(const agora::rtc::VideoEncoderConfiguration & AgoraData){
		codecType = UABTEnum::WrapWithUE(AgoraData.codecType);
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		minBitrate = AgoraData.minBitrate;
		orientationMode = UABTEnum::WrapWithUE(AgoraData.orientationMode);
		degradationPreference = UABTEnum::WrapWithUE(AgoraData.degradationPreference);
		mirrorMode = UABTEnum::WrapWithUE(AgoraData.mirrorMode);
		advanceOptions = FUABT_AdvanceOptions(AgoraData.advanceOptions);
	}

	agora::rtc::VideoEncoderConfiguration CreateRawData() const {
		agora::rtc::VideoEncoderConfiguration AgoraData;
		AgoraData.codecType = UABTEnum::ToRawValue(codecType);
		AgoraData.dimensions = dimensions.CreateRawData();
		AgoraData.frameRate = frameRate;
		AgoraData.bitrate = bitrate;
		AgoraData.minBitrate = minBitrate;
		AgoraData.orientationMode = UABTEnum::ToRawValue(orientationMode);
		AgoraData.degradationPreference = UABTEnum::ToRawValue(degradationPreference);
		AgoraData.mirrorMode = UABTEnum::ToRawValue(mirrorMode);
		AgoraData.advanceOptions = advanceOptions.CreateRawData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::VideoEncoderConfiguration& AgoraData) const {
		dimensions.FreeRawData(AgoraData.dimensions);
		advanceOptions.FreeRawData(AgoraData.advanceOptions);
	}
};


USTRUCT(BlueprintType)
struct FUABT_BeautyOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_LIGHTENING_CONTRAST_LEVEL lighteningContrastLevel = EUABT_LIGHTENING_CONTRAST_LEVEL::LIGHTENING_CONTRAST_NORMAL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float lighteningLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float smoothnessLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float rednessLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float sharpnessLevel = 0;

	FUABT_BeautyOptions(){}
	FUABT_BeautyOptions(const agora::rtc::BeautyOptions & AgoraData){
		lighteningContrastLevel = UABTEnum::WrapWithUE(AgoraData.lighteningContrastLevel);
		lighteningLevel = AgoraData.lighteningLevel;
		smoothnessLevel = AgoraData.smoothnessLevel;
		rednessLevel = AgoraData.rednessLevel;
		sharpnessLevel = AgoraData.sharpnessLevel;
	}

	agora::rtc::BeautyOptions CreateRawData() const {
		agora::rtc::BeautyOptions AgoraData;
		AgoraData.lighteningContrastLevel = UABTEnum::ToRawValue(lighteningContrastLevel);
		AgoraData.lighteningLevel = lighteningLevel;
		AgoraData.smoothnessLevel = smoothnessLevel;
		AgoraData.rednessLevel = rednessLevel;
		AgoraData.sharpnessLevel = sharpnessLevel;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::BeautyOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_LowlightEnhanceOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_LOW_LIGHT_ENHANCE_MODE mode = EUABT_LOW_LIGHT_ENHANCE_MODE::LOW_LIGHT_ENHANCE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_LOW_LIGHT_ENHANCE_LEVEL level = EUABT_LOW_LIGHT_ENHANCE_LEVEL::LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY;

	FUABT_LowlightEnhanceOptions(){}
	FUABT_LowlightEnhanceOptions(const agora::rtc::LowlightEnhanceOptions & AgoraData){
		mode = UABTEnum::WrapWithUE(AgoraData.mode);
		level = UABTEnum::WrapWithUE(AgoraData.level);
	}
	agora::rtc::LowlightEnhanceOptions CreateRawData() const {
		agora::rtc::LowlightEnhanceOptions AgoraData;
		AgoraData.mode = UABTEnum::ToRawValue(mode);
		AgoraData.level = UABTEnum::ToRawValue(level);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LowlightEnhanceOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoDenoiserOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_DENOISER_MODE mode = EUABT_VIDEO_DENOISER_MODE::VIDEO_DENOISER_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_DENOISER_LEVEL  level = EUABT_VIDEO_DENOISER_LEVEL ::VIDEO_DENOISER_LEVEL_HIGH_QUALITY;

	FUABT_VideoDenoiserOptions(){}
	FUABT_VideoDenoiserOptions(const agora::rtc::VideoDenoiserOptions & AgoraData){
		mode = UABTEnum::WrapWithUE(AgoraData.mode);
		level = UABTEnum::WrapWithUE(AgoraData.level);
	}

	agora::rtc::VideoDenoiserOptions CreateRawData() const {
		agora::rtc::VideoDenoiserOptions AgoraData;
		AgoraData.mode = UABTEnum::ToRawValue(mode);
		AgoraData.level = UABTEnum::ToRawValue(level);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::VideoDenoiserOptions& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_ColorEnhanceOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float strengthLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float skinProtectLevel = 0;

	FUABT_ColorEnhanceOptions(){}
	FUABT_ColorEnhanceOptions(const agora::rtc::ColorEnhanceOptions & AgoraData){
		strengthLevel = AgoraData.strengthLevel;
		skinProtectLevel = AgoraData.skinProtectLevel;
	}

	agora::rtc::ColorEnhanceOptions CreateRawData() const {
		agora::rtc::ColorEnhanceOptions AgoraData;
		AgoraData.strengthLevel = strengthLevel;
		AgoraData.skinProtectLevel = skinProtectLevel;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ColorEnhanceOptions& AgoraData) const {

	}

};

USTRUCT(BlueprintType)
struct FUABT_VirtualBackgroundSource
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_BACKGROUND_SOURCE_TYPE background_source_type = EUABT_BACKGROUND_SOURCE_TYPE::BACKGROUND_COLOR;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 color = 0xffffff;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString source = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_BACKGROUND_BLUR_DEGREE blur_degree = EUABT_BACKGROUND_BLUR_DEGREE::BLUR_DEGREE_HIGH;

	FUABT_VirtualBackgroundSource(){}
	FUABT_VirtualBackgroundSource(const agora::rtc::VirtualBackgroundSource & AgoraData){
		background_source_type = UABTEnum::WrapWithUE(AgoraData.background_source_type);
		color = AgoraData.color;
		source = AgoraData.source;
		blur_degree = UABTEnum::WrapWithUE(AgoraData.blur_degree);
	}

	agora::rtc::VirtualBackgroundSource CreateRawData() const {
		agora::rtc::VirtualBackgroundSource AgoraData;
		AgoraData.background_source_type = UABTEnum::ToRawValue(background_source_type);
		AgoraData.color = color;
		AgoraData.source = UABT::New_CharPtr(this->source);
		AgoraData.blur_degree = UABTEnum::ToRawValue(blur_degree);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::VirtualBackgroundSource& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.source);
	}
};

USTRUCT(BlueprintType)
struct FUABT_SegmentationProperty
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_SEG_MODEL_TYPE modelType = EUABT_SEG_MODEL_TYPE::SEG_MODEL_AI;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float greenCapacity = 0.5;

	FUABT_SegmentationProperty(){}
	FUABT_SegmentationProperty(const agora::rtc::SegmentationProperty & AgoraData){
		modelType = UABTEnum::WrapWithUE(AgoraData.modelType);
		greenCapacity = AgoraData.greenCapacity;
	}

	agora::rtc::SegmentationProperty CreateRawData() const {
		agora::rtc::SegmentationProperty AgoraData;
		AgoraData.modelType = UABTEnum::ToRawValue(modelType);
		AgoraData.greenCapacity = greenCapacity;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::SegmentationProperty& AgoraData) const {

	}
};


USTRUCT(BlueprintType)
struct FUABT_VideoSubscriptionOptions
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_VIDEO_STREAM_TYPE type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool encodedFrameOnly;

	FUABT_VideoSubscriptionOptions(){}
	FUABT_VideoSubscriptionOptions(const agora::rtc::VideoSubscriptionOptions & AgoraData){
		this->type = AgoraData.type;
		this->encodedFrameOnly = AgoraData.encodedFrameOnly;
	}

	agora::rtc::VideoSubscriptionOptions CreateRawData() const {
		agora::rtc::VideoSubscriptionOptions AgoraData;
		AgoraData.type = this->type.CreateRawOptData();

		AgoraData.encodedFrameOnly = this->encodedFrameOnly.CreateRawOptData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::VideoSubscriptionOptions& AgoraData) const {
		FUABT_Opt_VIDEO_STREAM_TYPE::FreeRawOptData(AgoraData.type);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.encodedFrameOnly);

	}
};

USTRUCT(BlueprintType)
struct FUABT_AudioRecordingConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString filePath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool encode = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int sampleRate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIO_FILE_RECORDING_TYPE fileRecordingType = EUABT_AUDIO_FILE_RECORDING_TYPE::AUDIO_FILE_RECORDING_MIXED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIO_RECORDING_QUALITY_TYPE quality = EUABT_AUDIO_RECORDING_QUALITY_TYPE::AUDIO_RECORDING_QUALITY_LOW;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int recordingChannel = 0;

	FUABT_AudioRecordingConfiguration(){}
	FUABT_AudioRecordingConfiguration(const agora::rtc::AudioRecordingConfiguration & AgoraData){
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		encode = AgoraData.encode;
		sampleRate = AgoraData.sampleRate;
		fileRecordingType = UABTEnum::WrapWithUE(AgoraData.fileRecordingType);
		quality = UABTEnum::WrapWithUE(AgoraData.quality);
		recordingChannel = AgoraData.recordingChannel;
	}

	agora::rtc::AudioRecordingConfiguration CreateRawData() const {
		agora::rtc::AudioRecordingConfiguration AgoraData;
		AgoraData.filePath = UABT::New_CharPtr(this->filePath);
		AgoraData.encode = encode;
		AgoraData.sampleRate = sampleRate;
		AgoraData.fileRecordingType = UABTEnum::ToRawValue(fileRecordingType);
		AgoraData.quality = UABTEnum::ToRawValue(quality);
		AgoraData.recordingChannel = recordingChannel;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::AudioRecordingConfiguration& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.filePath);
	}
};


USTRUCT(BlueprintType)
struct FUABT_SpatialAudioParams
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_double speaker_azimuth;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_double speaker_elevation;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_double speaker_distance;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_int speaker_orientation;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool enable_blur;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool enable_air_absorb;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_double speaker_attenuation;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_bool enable_doppler;

	FUABT_SpatialAudioParams(){}
	FUABT_SpatialAudioParams(const agora::SpatialAudioParams & AgoraData){
		this->speaker_azimuth = AgoraData.speaker_azimuth;
		this->speaker_elevation = AgoraData.speaker_elevation;
		this->speaker_distance = AgoraData.speaker_distance;
		this->speaker_orientation = AgoraData.speaker_orientation;
		this->enable_blur = AgoraData.enable_blur;
		this->enable_air_absorb = AgoraData.enable_air_absorb;
		this->speaker_attenuation = AgoraData.speaker_attenuation;
		this->enable_doppler = AgoraData.enable_doppler;
	}

	agora::SpatialAudioParams CreateRawData() const {
		agora::SpatialAudioParams AgoraData;
		AgoraData.speaker_azimuth = this->speaker_azimuth.CreateRawOptData();
		AgoraData.speaker_elevation = this->speaker_elevation.CreateRawOptData();
		AgoraData.speaker_distance = this->speaker_distance.CreateRawOptData();
		AgoraData.speaker_orientation = this->speaker_orientation.CreateRawOptData();
		AgoraData.enable_blur = this->enable_blur.CreateRawOptData();
		AgoraData.enable_air_absorb = this->enable_air_absorb.CreateRawOptData();
		AgoraData.speaker_attenuation = this->speaker_attenuation.CreateRawOptData();
		AgoraData.enable_doppler = this->enable_doppler.CreateRawOptData();
		return AgoraData;
	}

	void FreeRawData(agora::SpatialAudioParams& AgoraData) const {
		FUABT_Opt_double::FreeRawOptData(AgoraData.speaker_azimuth);
		FUABT_Opt_double::FreeRawOptData(AgoraData.speaker_elevation);
		FUABT_Opt_double::FreeRawOptData(AgoraData.speaker_distance);
		FUABT_Opt_int::FreeRawOptData(AgoraData.speaker_orientation);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.enable_blur);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.enable_air_absorb);
		FUABT_Opt_double::FreeRawOptData(AgoraData.speaker_attenuation);
		FUABT_Opt_bool::FreeRawOptData(AgoraData.enable_doppler);
	}
};


USTRUCT(BlueprintType)
struct FUABT_SimulcastStreamConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int kBitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int framerate = 0;

	FUABT_SimulcastStreamConfig(){}
	FUABT_SimulcastStreamConfig(const agora::rtc::SimulcastStreamConfig & AgoraData){
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		kBitrate = AgoraData.kBitrate;
		framerate = AgoraData.framerate;
	}

	agora::rtc::SimulcastStreamConfig CreateRawData() const {
		agora::rtc::SimulcastStreamConfig AgoraData;
		AgoraData.dimensions = dimensions.CreateRawData();
		AgoraData.kBitrate = kBitrate;
		AgoraData.framerate = framerate;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::SimulcastStreamConfig& AgoraData) const {
		dimensions.FreeRawData(AgoraData.dimensions);
	}
};



USTRUCT(BlueprintType)
struct FUABT_ExtensionInfo {

	GENERATED_BODY();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_MEDIA_SOURCE_TYPE mediaSourceType = EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 remoteUid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString channelId = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 localUid = 0;

	FUABT_ExtensionInfo() {}

	FUABT_ExtensionInfo(const agora::rtc::ExtensionInfo& AgoraData) {
		mediaSourceType = UABTEnum::WrapWithUE(AgoraData.mediaSourceType);
		remoteUid = AgoraData.remoteUid;
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		localUid = AgoraData.localUid;
	}

	agora::rtc::ExtensionInfo CreateRawData() const {
		agora::rtc::ExtensionInfo AgoraData;
		AgoraData.mediaSourceType = UABTEnum::ToRawValue(mediaSourceType);
		AgoraData.remoteUid = UABT::ToUID(remoteUid);

		char* ChannelIdCharPtr = new char[channelId.Len() + 1];
		FMemory::Memcpy(ChannelIdCharPtr, TCHAR_TO_UTF8(*channelId), channelId.Len());
		ChannelIdCharPtr[channelId.Len()] = '\0';
		
		AgoraData.channelId = ChannelIdCharPtr;
		AgoraData.localUid = UABT::ToUID(localUid);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ExtensionInfo& AgoraData) const {
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UImage* Image = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<uint8> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 length = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::ThumbImageBuffer CreateRawData() const {
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

	void FreeRawData(agora::rtc::ThumbImageBuffer & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.buffer);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureSourceInfo {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_ScreenCaptureSourceType type = EUABT_ScreenCaptureSourceType();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 sourceId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString sourceName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_ThumbImageBuffer thumbImage = FUABT_ThumbImageBuffer();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_ThumbImageBuffer iconImage = FUABT_ThumbImageBuffer();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString processPath = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString sourceTitle = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool primaryMonitor = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isOccluded = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Rectangle position = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool minimizeWindow = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::ScreenCaptureSourceInfo CreateRawData() const {
		agora::rtc::ScreenCaptureSourceInfo AgoraData;
		AgoraData.type = UABTEnum::ToRawValue(type);
		AgoraData.sourceId = sourceId;
		AgoraData.sourceName = UABT::New_CharPtr(sourceName);
		AgoraData.thumbImage = thumbImage.CreateRawData();
		AgoraData.iconImage = iconImage.CreateRawData();
		AgoraData.processPath = UABT::New_CharPtr(processPath);
		AgoraData.sourceTitle = UABT::New_CharPtr(sourceTitle);
		AgoraData.primaryMonitor = primaryMonitor;
		AgoraData.isOccluded = isOccluded;
		AgoraData.position = position.CreateRawData();
#if defined(_WIN32)
		AgoraData.minimizeWindow = minimizeWindow;
		AgoraData.sourceDisplayId = sourceDisplayId;
#endif
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ScreenCaptureSourceInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.sourceName);
		thumbImage.FreeRawData(AgoraData.thumbImage);
		thumbImage.FreeRawData(AgoraData.iconImage);
		UABT::Free_CharPtr(AgoraData.processPath);
		UABT::Free_CharPtr(AgoraData.sourceTitle);
		position.FreeRawData(AgoraData.position);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_SIZE {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 0;

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	FUABT_SIZE(){}
	FUABT_SIZE(const agora::rtc::SIZE & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
	}

	agora::rtc::SIZE CreateRawData() const {
		agora::rtc::SIZE AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		return AgoraData;
	}
	
	void FreeRawData(agora::rtc::SIZE & AgoraData) const {

	}
#endif
};



USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureParameters
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int frameRate = 5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int bitrate = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool captureMouseCursor = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool windowFocus = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 excludeWindowList = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int excludeWindowCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int highLightWidth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int highLightColor = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::ScreenCaptureParameters CreateRawData() const {
		agora::rtc::ScreenCaptureParameters AgoraData;
		AgoraData.dimensions = dimensions.CreateRawData();
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

	void FreeRawData(agora::rtc::ScreenCaptureParameters& AgoraData) const {
		dimensions.FreeRawData(AgoraData.dimensions);
	}
};

USTRUCT(BlueprintType)
struct FUABT_ScreenAudioParameters {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int sampleRate = 16000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int channels = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int captureSignalVolume = 100;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FUABT_ScreenAudioParameters(){}
	FUABT_ScreenAudioParameters(const agora::rtc::ScreenAudioParameters & AgoraData){
		sampleRate = AgoraData.sampleRate;
		channels = AgoraData.channels;
		captureSignalVolume = AgoraData.captureSignalVolume;
	}

	agora::rtc::ScreenAudioParameters CreateRawData() const {
		agora::rtc::ScreenAudioParameters AgoraData;
		AgoraData.sampleRate = sampleRate;
		AgoraData.channels = channels;
		AgoraData.captureSignalVolume = captureSignalVolume;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ScreenAudioParameters& AgoraData) const {

	}
#endif
};

USTRUCT(BlueprintType)
struct FUABT_ScreenVideoParameters {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoDimensions dimensions = FUABT_VideoDimensions();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int frameRate = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int bitrate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CONTENT_HINT contentHint = EUABT_VIDEO_CONTENT_HINT::CONTENT_HINT_MOTION;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FUABT_ScreenVideoParameters(){}
	FUABT_ScreenVideoParameters(const agora::rtc::ScreenVideoParameters & AgoraData){
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		frameRate = AgoraData.frameRate;
		bitrate = AgoraData.bitrate;
		contentHint = UABTEnum::WrapWithUE(AgoraData.contentHint);
	}

	agora::rtc::ScreenVideoParameters CreateRawData() const {
		agora::rtc::ScreenVideoParameters AgoraData;
		AgoraData.dimensions = dimensions.CreateRawData();
		AgoraData.frameRate = frameRate;
		AgoraData.bitrate = bitrate;
		AgoraData.contentHint = UABTEnum::ToRawValue(contentHint);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ScreenVideoParameters& AgoraData) const {
		dimensions.FreeRawData(AgoraData.dimensions);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureParameters2
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool captureAudio = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_ScreenAudioParameters audioParams = FUABT_ScreenAudioParameters();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool captureVideo = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_ScreenVideoParameters videoParams = FUABT_ScreenVideoParameters();

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	FUABT_ScreenCaptureParameters2(){}
	FUABT_ScreenCaptureParameters2(const agora::rtc::ScreenCaptureParameters2 & AgoraData){
		captureAudio = AgoraData.captureAudio;
		audioParams = FUABT_ScreenAudioParameters(AgoraData.audioParams);
		captureVideo = AgoraData.captureVideo;
		videoParams = FUABT_ScreenVideoParameters(AgoraData.videoParams);
	}

	agora::rtc::ScreenCaptureParameters2 CreateRawData() const {
		agora::rtc::ScreenCaptureParameters2 AgoraData;
		AgoraData.captureAudio = captureAudio;
		AgoraData.audioParams = audioParams.CreateRawData();
		AgoraData.captureVideo = captureVideo;
		AgoraData.videoParams = videoParams.CreateRawData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ScreenCaptureParameters2& AgoraData) const {
		audioParams.FreeRawData(AgoraData.audioParams);
		videoParams.FreeRawData(AgoraData.videoParams);
	}
#endif
};


USTRUCT(BlueprintType)
struct FUABT_ScreenCaptureConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isCaptureWindow = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int displayId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Rectangle screenRect = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 windowId = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_ScreenCaptureParameters params = FUABT_ScreenCaptureParameters();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::ScreenCaptureConfiguration CreateRawData() const {
		agora::rtc::ScreenCaptureConfiguration AgoraData;
		AgoraData.isCaptureWindow = isCaptureWindow;
		AgoraData.displayId = displayId;
		AgoraData.screenRect = screenRect.CreateRawData();
		//AgoraData.windowId = windowId;
		AgoraData.params = params.CreateRawData();
		AgoraData.regionRect = regionRect.CreateRawData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ScreenCaptureConfiguration & AgoraData) const {
		screenRect.FreeRawData(AgoraData.screenRect);
		params.FreeRawData(AgoraData.params);
		regionRect.FreeRawData(AgoraData.regionRect);
	}
};

#pragma endregion Screen Share



#pragma region Rtc Engine 3

USTRUCT(BlueprintType)
struct FUABT_FocalLengthInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int cameraDirection = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CAMERA_FOCAL_LENGTH_TYPE focalLengthType = EUABT_CAMERA_FOCAL_LENGTH_TYPE::CAMERA_FOCAL_LENGTH_DEFAULT;

	FUABT_FocalLengthInfo(){}
	FUABT_FocalLengthInfo(const agora::rtc::FocalLengthInfo & AgoraData){
		cameraDirection = AgoraData.cameraDirection;
		focalLengthType = UABTEnum::WrapWithUE(AgoraData.focalLengthType);
	}

	agora::rtc::FocalLengthInfo CreateRawData() const {
		agora::rtc::FocalLengthInfo AgoraData;
		AgoraData.cameraDirection = cameraDirection;
		AgoraData.focalLengthType = UABTEnum::ToRawValue(focalLengthType);
		return AgoraData;
	}

	void FreeRawData(agora::rtc::FocalLengthInfo& AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_TranscodingUser {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int zOrder = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float alpha = 1.0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::TranscodingUser CreateRawData() const {
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

	void FreeRawData(agora::rtc::TranscodingUser& AgoraData) const {

	}

};

USTRUCT(BlueprintType)
struct FUABT_RtcImage
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString url = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int x = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int y = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int zOrder = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::rtc::RtcImage CreateRawData() const {
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

	void FreeRawData(agora::rtc::RtcImage& AgoraData) const {
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString featureName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool opened = false;

	FUABT_LiveStreamAdvancedFeature(){}
	FUABT_LiveStreamAdvancedFeature(const agora::rtc::LiveStreamAdvancedFeature & AgoraData){
		featureName = UTF8_TO_TCHAR(AgoraData.featureName);
		opened = AgoraData.opened;
	}

	agora::rtc::LiveStreamAdvancedFeature CreateRawData() const {
		agora::rtc::LiveStreamAdvancedFeature AgoraData;
		AgoraData.featureName = UABT::New_CharPtr(this->featureName);
		AgoraData.opened = opened;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LiveStreamAdvancedFeature& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.featureName);
	}
};



USTRUCT(BlueprintType)
struct FUABT_LiveTranscoding
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int width = 360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int height = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoBitrate = 400;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoFramerate = 15;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool lowLatency = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int videoGop = 30;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_PROFILE_TYPE videoCodecProfile = EUABT_VIDEO_CODEC_PROFILE_TYPE::VIDEO_CODEC_PROFILE_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 backgroundColor = 0x000000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_CODEC_TYPE_FOR_STREAM videoCodecType = EUABT_VIDEO_CODEC_TYPE_FOR_STREAM::VIDEO_CODEC_H264_FOR_STREAM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_TranscodingUser> transcodingUsers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString transcodingExtraInfo = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString metadata = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray <FUABT_RtcImage> watermark;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_RtcImage> backgroundImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIO_SAMPLE_RATE_TYPE audioSampleRate = EUABT_AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioBitrate = 48;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int audioChannels = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIO_CODEC_PROFILE_TYPE audioCodecProfile = EUABT_AUDIO_CODEC_PROFILE_TYPE::AUDIO_CODEC_PROFILE_LC_AAC;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_LiveStreamAdvancedFeature> advancedFeatures;

	FUABT_LiveTranscoding(){}
	FUABT_LiveTranscoding(const agora::rtc::LiveTranscoding & AgoraData){
		width = AgoraData.width;
		height = AgoraData.height;
		videoBitrate = AgoraData.videoBitrate;
		videoFramerate = AgoraData.videoFramerate;
		lowLatency = AgoraData.lowLatency;
		videoGop = AgoraData.videoGop;
		videoCodecProfile = UABTEnum::WrapWithUE(AgoraData.videoCodecProfile);
		backgroundColor = AgoraData.backgroundColor;
		videoCodecType = UABTEnum::WrapWithUE(AgoraData.videoCodecType);

		for(unsigned int i = 0; i< AgoraData.userCount; i++){
			transcodingUsers.Add(FUABT_TranscodingUser((AgoraData.transcodingUsers[i])));
		}
	
		transcodingExtraInfo = UTF8_TO_TCHAR(AgoraData.transcodingExtraInfo);
		metadata = UTF8_TO_TCHAR(AgoraData.metadata);

		for(unsigned int i =0; i< AgoraData.watermarkCount;i++)
		{
			watermark.Add(FUABT_RtcImage(AgoraData.watermark[i]));
		}

		for(unsigned int i =0; i< AgoraData.backgroundImageCount;i++){
			backgroundImage.Add(FUABT_RtcImage(AgoraData.watermark[i]));
		}
		audioSampleRate = UABTEnum::WrapWithUE(AgoraData.audioSampleRate);
		audioBitrate = AgoraData.audioBitrate;
		audioChannels = AgoraData.audioChannels;
		audioCodecProfile = UABTEnum::WrapWithUE(AgoraData.audioCodecProfile);

		for(unsigned int i = 0; i< AgoraData.advancedFeatureCount; i++){
			advancedFeatures.Add(FUABT_LiveStreamAdvancedFeature(AgoraData.advancedFeatures[i]));
		}
	}

	agora::rtc::LiveTranscoding CreateRawData() const {
		agora::rtc::LiveTranscoding AgoraData;
		AgoraData.width = width;
		AgoraData.height = height;
		AgoraData.videoBitrate = videoBitrate;
		AgoraData.videoFramerate = videoFramerate;
		AgoraData.lowLatency = lowLatency;
		AgoraData.videoGop = videoGop;
		AgoraData.videoCodecProfile = UABTEnum::ToRawValue(videoCodecProfile);
		AgoraData.backgroundColor = static_cast<unsigned int>(backgroundColor);
		AgoraData.videoCodecType = UABTEnum::ToRawValue(videoCodecType);
		
		AgoraData.transcodingUsers = UABT::New_RawDataArray<agora::rtc::TranscodingUser,FUABT_TranscodingUser>(this->transcodingUsers);

		AgoraData.transcodingExtraInfo = UABT::New_CharPtr(this->transcodingExtraInfo);
		AgoraData.metadata = UABT::New_CharPtr(this->metadata);

		AgoraData.watermark = UABT::New_RawDataArray<agora::rtc::RtcImage, FUABT_RtcImage>(this->watermark);
		

		AgoraData.backgroundImage = UABT::New_RawDataArray<agora::rtc::RtcImage, FUABT_RtcImage>(this->backgroundImage);

		AgoraData.audioSampleRate = UABTEnum::ToRawValue(audioSampleRate);
		AgoraData.audioBitrate = audioBitrate;
		AgoraData.audioChannels = audioChannels;

		AgoraData.advancedFeatureCount = this->advancedFeatures.Num();
		AgoraData.advancedFeatures = UABT::New_RawDataArray<agora::rtc::LiveStreamAdvancedFeature, FUABT_LiveStreamAdvancedFeature>(this->advancedFeatures);

		return AgoraData;
	}

	void FreeRawData(agora::rtc::LiveTranscoding & AgoraData) const{
		
			UABT::Free_RawDataArray<agora::rtc::TranscodingUser,FUABT_TranscodingUser>(AgoraData.transcodingUsers, AgoraData.userCount);

		
		UABT::Free_CharPtr(AgoraData.transcodingExtraInfo);

		UABT::Free_RawDataArray<agora::rtc::RtcImage, FUABT_RtcImage>(AgoraData.watermark, AgoraData.watermarkCount);


		UABT::Free_RawDataArray<agora::rtc::RtcImage, FUABT_RtcImage>(AgoraData.backgroundImage, AgoraData.backgroundImageCount);

		UABT::Free_RawDataArray<agora::rtc::LiveStreamAdvancedFeature, FUABT_LiveStreamAdvancedFeature>(AgoraData.advancedFeatures, AgoraData.advancedFeatureCount);
	
	}
		
};




USTRUCT(BlueprintType)
struct FUABT_LocalTranscoderConfiguration
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_TranscodingVideoStream> videoInputStreams;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoEncoderConfiguration videoOutputConfiguration = FUABT_VideoEncoderConfiguration();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool syncWithPrimaryCamera = true;

	FUABT_LocalTranscoderConfiguration(){}
	FUABT_LocalTranscoderConfiguration(const agora::rtc::LocalTranscoderConfiguration & AgoraData){
		for(unsigned int i = 0; i< AgoraData.streamCount; i++){
			videoInputStreams.Add(FUABT_TranscodingVideoStream(AgoraData.videoInputStreams[i]));
		}
		videoOutputConfiguration = FUABT_VideoEncoderConfiguration(AgoraData.videoOutputConfiguration);
		syncWithPrimaryCamera = AgoraData.syncWithPrimaryCamera;
	}

	agora::rtc::LocalTranscoderConfiguration CreateRawData() const {
		agora::rtc::LocalTranscoderConfiguration AgoraData;
		AgoraData.streamCount = this->videoInputStreams.Num();
		UABT::New_RawDataArray<agora::rtc::TranscodingVideoStream,FUABT_TranscodingVideoStream>(this->videoInputStreams);

		AgoraData.videoOutputConfiguration = videoOutputConfiguration.CreateRawData();
		AgoraData.syncWithPrimaryCamera = syncWithPrimaryCamera;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LocalTranscoderConfiguration & AgoraData) const {
		UABT::Free_RawDataArray<agora::rtc::TranscodingVideoStream, FUABT_TranscodingVideoStream>(AgoraData.videoInputStreams, AgoraData.streamCount);
		videoOutputConfiguration.FreeRawData(AgoraData.videoOutputConfiguration);
	}
};


USTRUCT(BlueprintType)
struct FUABT_DataStreamConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool syncWithAudio = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ordered = false;

	FUABT_DataStreamConfig(){}
	FUABT_DataStreamConfig(const agora::rtc::DataStreamConfig & AgoraData){
		syncWithAudio = AgoraData.syncWithAudio;
		ordered = AgoraData.ordered;
	}

	agora::rtc::DataStreamConfig CreateRawData() const {
		agora::rtc::DataStreamConfig AgoraData;
		AgoraData.syncWithAudio = syncWithAudio;
		AgoraData.ordered = ordered;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::DataStreamConfig & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_WatermarkRatio {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float xRatio = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float yRatio = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float widthRatio = 0;

	FUABT_WatermarkRatio(){}
	FUABT_WatermarkRatio(const agora::rtc::WatermarkRatio & AgoraData){
		xRatio = AgoraData.xRatio;
		yRatio = AgoraData.yRatio;
		widthRatio = AgoraData.widthRatio;
	}

	agora::rtc::WatermarkRatio CreateRawData() const {
		agora::rtc::WatermarkRatio AgoraData;
		AgoraData.xRatio = xRatio;
		AgoraData.yRatio = yRatio;
		AgoraData.widthRatio = widthRatio;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::WatermarkRatio & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_WatermarkOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool visibleInPreview = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Rectangle positionInLandscapeMode = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Rectangle positionInPortraitMode = FUABT_Rectangle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_WatermarkRatio watermarkRatio = FUABT_WatermarkRatio();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_WATERMARK_FIT_MODE mode = EUABT_WATERMARK_FIT_MODE::FIT_MODE_COVER_POSITION;

	FUABT_WatermarkOptions(){}
	FUABT_WatermarkOptions(const agora::rtc::WatermarkOptions & AgoraData){
		visibleInPreview = AgoraData.visibleInPreview;
		positionInLandscapeMode = FUABT_Rectangle(AgoraData.positionInLandscapeMode);
		positionInPortraitMode = FUABT_Rectangle(AgoraData.positionInPortraitMode);
		watermarkRatio = FUABT_WatermarkRatio(AgoraData.watermarkRatio);
		mode = UABTEnum::WrapWithUE(AgoraData.mode);
	}

	agora::rtc::WatermarkOptions CreateRawData() const {
		agora::rtc::WatermarkOptions AgoraData;
		AgoraData.visibleInPreview = visibleInPreview;
		AgoraData.positionInLandscapeMode = positionInLandscapeMode.CreateRawData();
		AgoraData.positionInPortraitMode = positionInPortraitMode.CreateRawData();
		AgoraData.watermarkRatio = watermarkRatio.CreateRawData();
		AgoraData.mode = UABTEnum::ToRawValue(mode);
		return AgoraData;
	}
	void FreeRawData(agora::rtc::WatermarkOptions & AgoraData) const {
		positionInLandscapeMode.FreeRawData(AgoraData.positionInLandscapeMode);
		positionInPortraitMode.FreeRawData(AgoraData.positionInPortraitMode);
		watermarkRatio.FreeRawData(AgoraData.watermarkRatio);
	}
	
};


USTRUCT(BlueprintType)
struct FUABT_AgoraRhythmPlayerConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int beatsPerMeasure = 4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int beatsPerMinute = 60;

	FUABT_AgoraRhythmPlayerConfig(){}
	FUABT_AgoraRhythmPlayerConfig(const agora::rtc::AgoraRhythmPlayerConfig & AgoraData){
		beatsPerMeasure = AgoraData.beatsPerMeasure;
		beatsPerMinute = AgoraData.beatsPerMinute;
	}

	agora::rtc::AgoraRhythmPlayerConfig CreateRawData() const {
		agora::rtc::AgoraRhythmPlayerConfig AgoraData;
		AgoraData.beatsPerMeasure = beatsPerMeasure;
		AgoraData.beatsPerMinute = beatsPerMinute;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::AgoraRhythmPlayerConfig & AgoraData) const {

	}

};


USTRUCT(BlueprintType)
struct FUABT_ContentInspectModule {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_CONTENT_INSPECT_TYPE type = EUABT_CONTENT_INSPECT_TYPE::CONTENT_INSPECT_INVALID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 interval = 0;

	FUABT_ContentInspectModule(){}
	FUABT_ContentInspectModule(const agora::media::ContentInspectModule & AgoraData){
		type = UABTEnum::WrapWithUE(AgoraData.type);
		interval = AgoraData.interval;
	}

	agora::media::ContentInspectModule CreateRawData() const {
		agora::media::ContentInspectModule AgoraData;
		AgoraData.type = UABTEnum::ToRawValue(type);
		AgoraData.interval = interval;
		return AgoraData;
	}
	void FreeRawData(agora::media::ContentInspectModule & AgoraData) const {

	}
};

USTRUCT(BlueprintType)
struct FUABT_ContentInspectConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString extraInfo = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString serverConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_ContentInspectModule> modules;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	agora::media::ContentInspectConfig CreateRawData() const {
		agora::media::ContentInspectConfig AgoraData;
		AgoraData.extraInfo = UABT::New_CharPtr(this->extraInfo);
		AgoraData.serverConfig = UABT::New_CharPtr(this->serverConfig);
		AgoraData.moduleCount = moduleCount;
		for(int i = 0;i < moduleCount; i++){
			AgoraData.modules[i] = modules[i].CreateRawData();
		}
		return AgoraData;
	}

	void FreeRawData(agora::media::ContentInspectConfig & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.extraInfo);
		UABT::Free_CharPtr(AgoraData.serverConfig);
		for (int i = 0; i < moduleCount; i++) {
			FUABT_ContentInspectModule ReleaseOperator;
			ReleaseOperator.FreeRawData(AgoraData.modules[i]);
		}
	}

};

USTRUCT(BlueprintType)
struct FUABT_LogUploadServerInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString serverDomain = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString serverPath = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int serverPort = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool serverHttps = true;

	FUABT_LogUploadServerInfo() {}
	FUABT_LogUploadServerInfo(const agora::rtc::LogUploadServerInfo& AgoraData) {
		serverDomain = UTF8_TO_TCHAR(AgoraData.serverDomain);
		serverPath = UTF8_TO_TCHAR(AgoraData.serverPath);
		serverPort = AgoraData.serverPort;
		serverHttps = AgoraData.serverHttps;
	}

	agora::rtc::LogUploadServerInfo CreateRawData() const {
		agora::rtc::LogUploadServerInfo AgoraData;
		AgoraData.serverDomain = UABT::New_CharPtr(serverDomain);
		AgoraData.serverPath = UABT::New_CharPtr(serverPath);
		
		AgoraData.serverPort = serverPort;
		AgoraData.serverHttps = serverHttps;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LogUploadServerInfo& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.serverDomain);
		UABT::Free_CharPtr(AgoraData.serverPath);
	}
};


USTRUCT(BlueprintType)
struct FUABT_AdvancedConfigInfo {

	GENERATED_BODY()

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_LogUploadServerInfo logUploadServer = FUABT_LogUploadServerInfo();

	FUABT_AdvancedConfigInfo(){}
	FUABT_AdvancedConfigInfo(const agora::rtc::AdvancedConfigInfo& AgoraData) {
		logUploadServer = FUABT_LogUploadServerInfo(AgoraData.logUploadServer);
	}

	agora::rtc::AdvancedConfigInfo CreateRawData() const {
		agora::rtc::AdvancedConfigInfo AgoraData;
		AgoraData.logUploadServer = logUploadServer.CreateRawData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::AdvancedConfigInfo& AgoraData) const {
		logUploadServer.FreeRawData(AgoraData.logUploadServer);
	}
};

USTRUCT(BlueprintType)
struct FUABT_LocalAccessPointConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> ipList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int ipListSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> domainList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int domainListSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString verifyDomainName = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_LOCAL_PROXY_MODE mode = EUABT_LOCAL_PROXY_MODE::ConnectivityFirst;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_AdvancedConfigInfo advancedConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

		mode = UABTEnum::WrapWithUE(AgoraData.mode);

		advancedConfig = FUABT_AdvancedConfigInfo(AgoraData.advancedConfig);

		disableAut = AgoraData.disableAut;
	}

	agora::rtc::LocalAccessPointConfiguration CreateRawData() const {
		
		agora::rtc::LocalAccessPointConfiguration AgoraData;
		AgoraData.ipList = (const char**)UABT::New_CharArrayPtr(ipList);
		AgoraData.ipListSize = ipListSize;
		AgoraData.domainList = (const char**)UABT::New_CharArrayPtr(domainList);
			AgoraData.domainListSize = domainListSize;
		AgoraData.verifyDomainName = UABT::New_CharPtr(this->verifyDomainName);
			AgoraData.mode = UABTEnum::ToRawValue(mode);
		AgoraData.advancedConfig = advancedConfig.CreateRawData();
		AgoraData.disableAut = disableAut;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LocalAccessPointConfiguration & AgoraData) const {
		UABT::Free_CharArrayPtr(AgoraData.ipList, ipListSize);
		UABT::Free_CharArrayPtr(AgoraData.domainList, domainListSize);
		UABT::Free_CharPtr(AgoraData.verifyDomainName);
		advancedConfig.FreeRawData(AgoraData.advancedConfig);
	}
};

USTRUCT(BlueprintType)
struct FUABT_AdvancedAudioOptions
{
	GENERATED_BODY()

public:

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_Opt_int audioProcessingChannels;

	FUABT_AdvancedAudioOptions(){}
	FUABT_AdvancedAudioOptions(const agora::rtc::AdvancedAudioOptions & AgoraData){
	  this->audioProcessingChannels = AgoraData.audioProcessingChannels;
	}

	agora::rtc::AdvancedAudioOptions CreateRawData() const {
		agora::rtc::AdvancedAudioOptions AgoraData;
		AgoraData.audioProcessingChannels = this->audioProcessingChannels.CreateRawOptData();
		return AgoraData;
	}

	void FreeRawData(agora::rtc::AdvancedAudioOptions & AgoraData) const {
		this->audioProcessingChannels.FreeRawOptData(AgoraData.audioProcessingChannels);
	}
};


USTRUCT(BlueprintType)
struct FUABT_ImageTrackOptions
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString imageUrl = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int fps = 1;

	FUABT_ImageTrackOptions(){}
	FUABT_ImageTrackOptions(const agora::rtc::ImageTrackOptions & AgoraData){
		imageUrl = UTF8_TO_TCHAR(AgoraData.imageUrl);
		fps = AgoraData.fps;
	}

	agora::rtc::ImageTrackOptions CreateRawData() const {
		agora::rtc::ImageTrackOptions AgoraData;
		AgoraData.imageUrl = UABT::New_CharPtr(this->imageUrl);
		AgoraData.fps = fps;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ImageTrackOptions & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.imageUrl);
	}

};

USTRUCT(BlueprintType)
struct FUABT_DeviceInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isLowLatencyAudioSupported = false;

	FUABT_DeviceInfo(){}
	FUABT_DeviceInfo(const agora::rtc::DeviceInfo & AgoraData){
		isLowLatencyAudioSupported = AgoraData.isLowLatencyAudioSupported;
	}

	agora::rtc::DeviceInfo CreateRawData() const {
		agora::rtc::DeviceInfo AgoraData;
		AgoraData.isLowLatencyAudioSupported = isLowLatencyAudioSupported;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::DeviceInfo& AgoraData) const {

	}
};



USTRUCT(BlueprintType)
struct FUABT_ChannelMediaInfo {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 uid = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString channelName = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString token = "";

	FUABT_ChannelMediaInfo(){}
	FUABT_ChannelMediaInfo(const agora::rtc::ChannelMediaInfo & AgoraData){
		channelName = UTF8_TO_TCHAR(AgoraData.channelName);
		token = UTF8_TO_TCHAR(AgoraData.token);
		uid = AgoraData.uid;
	}

	agora::rtc::ChannelMediaInfo CreateRawData() const {
		agora::rtc::ChannelMediaInfo AgoraData;
		AgoraData.channelName = UABT::New_CharPtr(this->channelName);
		AgoraData.token = UABT::New_CharPtr(this->token);
		AgoraData.uid = uid;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::ChannelMediaInfo & AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelName);
		UABT::Free_CharPtr(AgoraData.token);
	}
};


USTRUCT(BlueprintType)
struct FUABT_ChannelMediaRelayConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_ChannelMediaInfo srcInfo = FUABT_ChannelMediaInfo();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_ChannelMediaInfo> destInfos;

	FUABT_ChannelMediaRelayConfiguration(){}
	FUABT_ChannelMediaRelayConfiguration(const agora::rtc::ChannelMediaRelayConfiguration & AgoraData){
		srcInfo = FUABT_ChannelMediaInfo(*(AgoraData.srcInfo));
		int destCount = AgoraData.destCount;
		for(int i = 0; i< destCount; i++){
			destInfos.Add(FUABT_ChannelMediaInfo(AgoraData.destInfos[i]));
		}
	}

	agora::rtc::ChannelMediaRelayConfiguration CreateRawData() const {
		agora::rtc::ChannelMediaRelayConfiguration AgoraData;
		
		AgoraData.srcInfo = UABT::New_RawData<agora::rtc::ChannelMediaInfo, FUABT_ChannelMediaInfo>(this->srcInfo);

		AgoraData.destInfos = UABT::New_RawDataArray<agora::rtc::ChannelMediaInfo, FUABT_ChannelMediaInfo>(this->destInfos);

		AgoraData.destCount = destInfos.Num();

		return AgoraData;
	}

	void FreeRawData(agora::rtc::ChannelMediaRelayConfiguration & AgoraData) const {
		UABT::Free_RawDataArray<agora::rtc::ChannelMediaInfo, FUABT_ChannelMediaInfo>(AgoraData.srcInfo,1);
		UABT::Free_RawDataArray<agora::rtc::ChannelMediaInfo, FUABT_ChannelMediaInfo>(AgoraData.destInfos, AgoraData.destCount);
	}
};

#pragma endregion Rtc Engine 3




/** Face shape beauty options. This structure defines options for facial adjustments of different facial styles.
 *
 * @technical preview
 */
USTRUCT(BlueprintType)
struct FUABT_FaceShapeBeautyOptions {
	GENERATED_BODY()

public:
	/** The face shape style, See #FACE_SHAPE_BEAUTY_STYLE.
	  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_FACE_SHAPE_BEAUTY_STYLE shapeStyle = EUABT_FACE_SHAPE_BEAUTY_STYLE::FACE_SHAPE_BEAUTY_STYLE_FEMALE;

	/** The intensity of the pinching effect applied to the specified facial style. The value ranges from 0 (original) to 100. The default value is 0. The greater the value, the stronger the intensity applied to face pinching.
	  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int styleIntensity = 50;

	FUABT_FaceShapeBeautyOptions(){}
	FUABT_FaceShapeBeautyOptions(const agora::rtc::FaceShapeBeautyOptions& AgoraData){
		shapeStyle = UABTEnum::WrapWithUE(AgoraData.shapeStyle);
		styleIntensity = AgoraData.styleIntensity;
	}

	agora::rtc::FaceShapeBeautyOptions CreateRawData() const {
		agora::rtc::FaceShapeBeautyOptions AgoraData;
		AgoraData.shapeStyle = UABTEnum::ToRawValue(shapeStyle);
		AgoraData.styleIntensity = styleIntensity;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::FaceShapeBeautyOptions& AgoraData) const {

	}
};




/** Face shape area options. This structure defines options for facial adjustments on different facial areas.
 *
 * @technical preview
 */
USTRUCT(BlueprintType)
struct FUABT_FaceShapeAreaOptions {
	/** The specific facial area to be adjusted.
	  */
	GENERATED_BODY()

public:


	/** The specific facial area to be adjusted, See #FACE_SHAPE_AREA.
	  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_FACE_SHAPE_AREA shapeArea = EUABT_FACE_SHAPE_AREA::FACE_SHAPE_AREA_NONE;

	/** The intensity of the pinching effect applied to the specified facial area.
	 * For the following area values: #FACE_SHAPE_AREA_FOREHEAD, #FACE_SHAPE_AREA_FACELENGTH, #FACE_SHAPE_AREA_CHIN, #FACE_SHAPE_AREA_NOSELENGTH, #FACE_SHAPE_AREA_NOSEWIDTH, #FACE_SHAPE_AREA_MOUTHSCALE, the value ranges from -100 to 100.
	 * The default value is 0. The greater the absolute value, the stronger the intensity applied to the specified facial area, and negative values indicate the opposite direction.
	 * For enumeration values other than the above, the value ranges from 0 to 100. The default value is 0. The greater the value, the stronger the intensity applied to the specified facial area.
	  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int shapeIntensity = 0;

	FUABT_FaceShapeAreaOptions(){}
	FUABT_FaceShapeAreaOptions(const agora::rtc::FaceShapeAreaOptions& AgoraData) {
		shapeArea = UABTEnum::WrapWithUE(AgoraData.shapeArea);
		shapeIntensity = AgoraData.shapeIntensity;
	}
	
	agora::rtc::FaceShapeAreaOptions CreateRawData() const {
		agora::rtc::FaceShapeAreaOptions AgoraData;
		AgoraData.shapeArea = UABTEnum::ToRawValue(shapeArea);
		AgoraData.shapeIntensity = shapeIntensity;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::FaceShapeAreaOptions& AgoraData) const {

	}
};



/** Filter effect options. This structure defines options for filter effect.
 *
 * @since v4.4.1
 */
USTRUCT(BlueprintType)
struct FUABT_FilterEffectOptions {
	GENERATED_BODY()

public:
	/**
	 * The local absolute path of the custom 3D Cube path. Only cube format is supported.
	 * The cube file must strictly comply with the Cube LUT Specification; otherwise, the filter effects will not take effect.
	 *
	 * The following is an example of the Cube file format. The cube file starts with `LUT_3D_SIZE`, which indicates the cube size. In filter effects, the cube size is limited to 32.

	 * LUT_3D_SIZE 32
	 * 0.0039215689 0 0.0039215682
	 * 0.0086021447 0.0037950677 0
	 * 0.0728652592 0.0039215689 0
	 * ...
	 *
	 * The SDK provides a built-in cube named `built_in_whiten.cube` for whitening. To use this cube, specify the path to `built_in_whiten_filter`
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString path;

	/**
	 * The intensity of specified filter effect. The value ranges from 0.0 to 1.0. The default value is 0.5. The greater the value, the stronger the intensity of the filter.
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float strength = 0.5;

	FUABT_FilterEffectOptions(){}
	FUABT_FilterEffectOptions(const agora::rtc::FilterEffectOptions& AgoraData) {
		path = UTF8_TO_TCHAR(AgoraData.path);
		strength = AgoraData.strength;
	}
	
	agora::rtc::FilterEffectOptions CreateRawData() const {
		agora::rtc::FilterEffectOptions AgoraData;
		AgoraData.path = UABT::New_CharPtr(path);
		AgoraData.strength = strength;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::FilterEffectOptions& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.path);
	}
};


USTRUCT(BlueprintType)
struct FUABT_StreamLayerConfig {

	GENERATED_BODY()

public:
	/**
	 * The video frame dimension. The default value is 0.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FUABT_VideoDimensions dimensions;
	/**
	 * The capture frame rate (fps) of the local video. The default value is 0.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int framerate = 0;
	/**
	 * Whether to enable the corresponding layer of video stream. The default value is false.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool enable = false;
	
	FUABT_StreamLayerConfig() {}
	FUABT_StreamLayerConfig(const agora::rtc::SimulcastConfig::StreamLayerConfig& AgoraData) {
		dimensions = FUABT_VideoDimensions(AgoraData.dimensions);
		framerate = AgoraData.framerate;
		enable = AgoraData.enable;
	}

	agora::rtc::SimulcastConfig::StreamLayerConfig CreateRawData() const {
		agora::rtc::SimulcastConfig::StreamLayerConfig AgoraData;
		AgoraData.dimensions = dimensions.CreateRawData();
		AgoraData.framerate = framerate;
		AgoraData.enable = enable;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::SimulcastConfig::StreamLayerConfig& AgoraData) const {
		dimensions.FreeRawData(AgoraData.dimensions);
	}
};


/**
 * The configuration of the multi-layer video stream.
 */
USTRUCT(BlueprintType)
struct FUABT_SimulcastConfig {

	GENERATED_BODY()

public:
	/**
	 * The array of StreamLayerConfig, which contains STREAM_LAYER_COUNT_MAX layers of video stream at most.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_StreamLayerConfig> configs;

	FUABT_SimulcastConfig() {}
	FUABT_SimulcastConfig(const agora::rtc::SimulcastConfig& AgoraData) {
		for (int i = 0; i < agora::rtc::SimulcastConfig::STREAM_LAYER_COUNT_MAX; i++) {
			configs.Add(FUABT_StreamLayerConfig(AgoraData.configs[i]));
		}
	}

	agora::rtc::SimulcastConfig CreateRawData() const {
		agora::rtc::SimulcastConfig AgoraData;
		for (int i = 0; i < agora::rtc::SimulcastConfig::STREAM_LAYER_COUNT_MAX; i++) {
			AgoraData.configs[i] = configs[i].CreateRawData();
		}
		return AgoraData;
	}

	void FreeRawData(agora::rtc::SimulcastConfig& AgoraData) const {
		for (int i = 0; i < agora::rtc::SimulcastConfig::STREAM_LAYER_COUNT_MAX; i++) {
			FUABT_StreamLayerConfig ReleaseOperator;
			ReleaseOperator.FreeRawData(AgoraData.configs[i]);
		}
	}
};


/**
 * The audio streams for the video mixing on the local client.
 */
USTRUCT(BlueprintType)
struct FUABT_MixedAudioStream {

	GENERATED_BODY()

public:
	/**
	 * The source type of audio for the audio mixing on the local client. See #AUDIO_SOURCE_TYPE.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_AUDIO_SOURCE_TYPE sourceType = EUABT_AUDIO_SOURCE_TYPE::AUDIO_SOURCE_MICROPHONE;
	/**
	 * The ID of the remote user.
	 * @note Use this parameter only when the source type is `AUDIO_SOURCE_REMOTE`.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 remoteUserUid;
	/**
	 * The channel ID of the remote user.
	 * @note Use this parameter only when the source type is `AUDIO_SOURCE_REMOTE`.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString channelId;
	/**
	 * The track ID of the local track.
	 * @note Use this parameter only when the source type is `AUDIO_SOURCE_REMOTE`.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int64 trackId;

	FUABT_MixedAudioStream() {}
	FUABT_MixedAudioStream(const agora::rtc::MixedAudioStream& AgoraData) {
		sourceType = UABTEnum::WrapWithUE(AgoraData.sourceType);
		remoteUserUid = AgoraData.remoteUserUid;
		channelId = UTF8_TO_TCHAR(AgoraData.channelId);
		trackId = AgoraData.trackId;
	}

	agora::rtc::MixedAudioStream CreateRawData() const {
		agora::rtc::MixedAudioStream AgoraData = UABTEnum::ToRawValue(sourceType);
		AgoraData.remoteUserUid = remoteUserUid;
		AgoraData.channelId = UABT::New_CharPtr(channelId);
		AgoraData.trackId = trackId;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::MixedAudioStream& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.channelId);
	}

};

/**
 * The configuration of the audio mixing on the local client.
 */
USTRUCT(BlueprintType)
struct FUABT_LocalAudioMixerConfiguration {

	GENERATED_BODY()

public:
	/**
	 * The source of the streams to mixed;
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FUABT_MixedAudioStream> audioInputStreams;

	/**
	 * Whether to use the timestamp follow the local mic's audio frame.
	 * - true: (Default) Use the timestamp of the captured audio frame as the timestamp of the mixed audio frame.
	 * - false: Do not use the timestamp of the captured audio frame as the timestamp of the mixed audio frame. Instead, use the timestamp when the mixed audio frame is constructed.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool syncWithLocalMic;

	FUABT_LocalAudioMixerConfiguration() {}
	FUABT_LocalAudioMixerConfiguration(const agora::rtc::LocalAudioMixerConfiguration& AgoraData) {
		for (unsigned int i = 0; i < AgoraData.streamCount; i++) {
			audioInputStreams.Add(FUABT_MixedAudioStream(AgoraData.audioInputStreams[i]));
		}
		syncWithLocalMic = AgoraData.syncWithLocalMic;
	}

	agora::rtc::LocalAudioMixerConfiguration CreateRawData() const {
		agora::rtc::LocalAudioMixerConfiguration AgoraData;
		AgoraData.streamCount = audioInputStreams.Num();

		int Num = audioInputStreams.Num();

		agora::rtc::MixedAudioStream* DstArray = static_cast<agora::rtc::MixedAudioStream*>(FMemory::Malloc(Num * sizeof(agora::rtc::MixedAudioStream)));

		for (int i = 0; i < Num; ++i) {
			agora::rtc::MixedAudioStream Tmp = audioInputStreams[i].CreateRawData();
			new (&DstArray[i]) agora::rtc::MixedAudioStream(Tmp.sourceType,Tmp.remoteUserUid,Tmp.channelId,Tmp.trackId);
		}

		AgoraData.audioInputStreams = DstArray;

		AgoraData.syncWithLocalMic = syncWithLocalMic;
		return AgoraData;
	}

	void FreeRawData(agora::rtc::LocalAudioMixerConfiguration& AgoraData) const {
		UABT::Free_RawDataArray<agora::rtc::MixedAudioStream, FUABT_MixedAudioStream>(AgoraData.audioInputStreams, AgoraData.streamCount);
	}
};




/** Definition of SnapshotConfig.
 */

USTRUCT(BlueprintType)
struct FUABT_SnapshotConfig {

	GENERATED_BODY()

public:

	/**
	 * The local path (including filename extensions) of the snapshot. For example:
	 * - Windows: `C:\Users\<user_name>\AppData\Local\Agora\<process_name>\example.jpg`
	 * - iOS: `/App Sandbox/Library/Caches/example.jpg`
	 * - macOS: `~/Library/Logs/example.jpg`
	 * - Android: `/storage/emulated/0/Android/data/<package name>/files/example.jpg`
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString filePath;

	/**
	 * The position of the video observation. See VIDEO_MODULE_POSITION.
	 *
	 * Allowed values vary depending on the `uid` parameter passed in `takeSnapshot` or `takeSnapshotEx`:
	 * - uid = 0: Position 2, 4 and 8 are allowed.
	 * - uid != 0: Only position 2 is allowed.
	 *
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EUABT_VIDEO_MODULE_POSITION position = EUABT_VIDEO_MODULE_POSITION::POSITION_PRE_ENCODER;


	FUABT_SnapshotConfig() {}
	FUABT_SnapshotConfig(const agora::media::SnapshotConfig& AgoraData) {
		filePath = UTF8_TO_TCHAR(AgoraData.filePath);
		position = UABTEnum::WrapWithUE(AgoraData.position);
	}

	agora::media::SnapshotConfig CreateRawData() const {
		agora::media::SnapshotConfig AgoraData;
		AgoraData.filePath = UABT::New_CharPtr(filePath);
		AgoraData.position = UABTEnum::ToRawValue(position);
		return AgoraData;
	}

	void FreeRawData(agora::media::SnapshotConfig& AgoraData) const {
		UABT::Free_CharPtr(AgoraData.filePath);
	}

};