#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "Async/Async.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "URtcEngineProxyCompatibility.generated.h"

class UIRtcEngineEventHandler;
class UIRtcEngineEventHandlerEx;
UENUM(BlueprintType)
enum class AGORAOPTIONAL : uint8 {
	AGORA_NULL_VALUE = 0,
	AGORA_TRUE_VALUE = 1,
	AGORA_FALSE_VALUE = 2,
};

UENUM(BlueprintType)
enum class EINTERFACE_ID_TYPE : uint8 {
	AGORA_IID_NULL = 0,
	AGORA_IID_AUDIO_DEVICE_MANAGER = 1,
	AGORA_IID_VIDEO_DEVICE_MANAGER = 2,
	AGORA_IID_PARAMETER_ENGINE = 3,
	AGORA_IID_MEDIA_ENGINE = 4,
	AGORA_IID_AUDIO_ENGINE = 5,
	AGORA_IID_VIDEO_ENGINE = 6,
	AGORA_IID_RTC_CONNECTION = 7,
	AGORA_IID_SIGNALING_ENGINE = 8,
	AGORA_IID_MEDIA_ENGINE_REGULATOR = 9,
	AGORA_IID_CLOUD_SPATIAL_AUDIO = 10,
	AGORA_IID_LOCAL_SPATIAL_AUDIO = 11,
	AGORA_IID_STATE_SYNC = 13,
	AGORA_IID_METACHAT_SERVICE = 14,
	AGORA_IID_MUSIC_CONTENT_CENTER = 15,
	AGORA_IID_H265_TRANSCODER = 16,
};
UENUM(BlueprintType)
enum class ECOMPRESSION_PREFERENCE : uint8 {

	PREFER_LOW_LATENCY = 0,

	PREFER_QUALITY = 1,
};


UENUM(BlueprintType)
enum class EENUMCUSTOM_ENCODING_PREFERENCE:uint8{

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
	EENUMCUSTOM_ENCODING_PREFERENCE ValueWrapper;

	// default
	FENUMWRAP_ENCODING_PREFERENCE():ValueWrapper(EENUMCUSTOM_ENCODING_PREFERENCE::PREFER_AUTO){}
	

	FENUMWRAP_ENCODING_PREFERENCE(EENUMCUSTOM_ENCODING_PREFERENCE Val):ValueWrapper(Val){}
	void operator = (EENUMCUSTOM_ENCODING_PREFERENCE InValue) {
		ValueWrapper = InValue;
	}

	int GetRawValue() const {
		return ((int)ValueWrapper - 1);
	}
};


USTRUCT(BlueprintType)
struct FAdvanceOptions {

	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	FENUMWRAP_ENCODING_PREFERENCE encodingPreference = EENUMCUSTOM_ENCODING_PREFERENCE::PREFER_AUTO;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
	ECOMPRESSION_PREFERENCE compressionPreference;
};

USTRUCT(BlueprintType)
struct FRtcImage
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	FString url;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int x;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int y;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	int zOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage")
	float alpha;
};


UENUM(BlueprintType)
enum ELOG_LEVEL {
	LOG_LEVEL_NONE = 0x0000,
	LOG_LEVEL_INFO = 0x0001,
	LOG_LEVEL_WARN = 0x0002,
	LOG_LEVEL_ERROR = 0x0004,
	LOG_LEVEL_FATAL = 0x0008,
	LOG_LEVEL_API_CALL = 0x0010,
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
enum EAUDIO_SAMPLE_RATE_TYPE {

	AUDIO_SAMPLE_NULL = 0,

	AUDIO_SAMPLE_RATE_32000 = 1,

	AUDIO_SAMPLE_RATE_44100 = 2,

	AUDIO_SAMPLE_RATE_48000 = 3,
};



UENUM(BlueprintType)
enum class ECLIENT_ROLE_TYPE : uint8 {
	CLIENT_ROLE_NULL = 0,
	CLIENT_ROLE_BROADCASTER = 1,
	CLIENT_ROLE_AUDIENCE = 2,
};

UENUM(BlueprintType)
enum class EVIDEO_SOURCE_TYPE : uint8 {
	VIDEO_SOURCE_CAMERA_PRIMARY = 0,
	VIDEO_SOURCE_CAMERA = VIDEO_SOURCE_CAMERA_PRIMARY,
	VIDEO_SOURCE_CAMERA_SECONDARY = 1,
	VIDEO_SOURCE_SCREEN_PRIMARY = 2,
	VIDEO_SOURCE_SCREEN = VIDEO_SOURCE_SCREEN_PRIMARY,
	VIDEO_SOURCE_SCREEN_SECONDARY = 3,
	VIDEO_SOURCE_CUSTOM = 4,
	VIDEO_SOURCE_MEDIA_PLAYER = 5,
	VIDEO_SOURCE_RTC_IMAGE_PNG = 6,
	VIDEO_SOURCE_RTC_IMAGE_JPEG = 7,
	VIDEO_SOURCE_RTC_IMAGE_GIF = 8,
	VIDEO_SOURCE_REMOTE = 9,
	VIDEO_SOURCE_TRANSCODED = 10,
	VIDEO_SOURCE_CAMERA_THIRD = 11,
	VIDEO_SOURCE_CAMERA_FOURTH = 12,
	VIDEO_SOURCE_SCREEN_THIRD = 13,
	VIDEO_SOURCE_SCREEN_FOURTH = 14,
	VIDEO_SOURCE_UNKNOWN = 100,
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
enum class EVIDEO_STREAM_TYPE : uint8 {
	VIDEO_STREAM_HIGH = 0,
	VIDEO_STREAM_LOW = 1,
};

UENUM(BlueprintType)
enum class EAUDIO_RECORDING_QUALITY_TYPE : uint8 {
	AUDIO_RECORDING_QUALITY_LOW = 0,
	AUDIO_RECORDING_QUALITY_MEDIUM = 1,
	AUDIO_RECORDING_QUALITY_HIGH = 2,
	AUDIO_RECORDING_QUALITY_ULTRA_HIGH = 3,
};

UENUM(BlueprintType)
enum class EAUDIO_MIXING_DUAL_MONO_MODE : uint8 {
	AUDIO_MIXING_DUAL_MONO_AUTO = 0,
	AUDIO_MIXING_DUAL_MONO_L = 1,
	AUDIO_MIXING_DUAL_MONO_R = 2,
	AUDIO_MIXING_DUAL_MONO_MIX = 3,
};

UENUM(BlueprintType)
enum EVOICE_BEAUTIFIER_PRESET {
	VOICE_BEAUTIFIER_OFF = 0x00000000,
	CHAT_BEAUTIFIER_MAGNETIC = 0x01010100,
	CHAT_BEAUTIFIER_FRESH = 0x01010200,
	CHAT_BEAUTIFIER_VITALITY = 0x01010300,
	SINGING_BEAUTIFIER = 0x01020100,
	TIMBRE_TRANSFORMATION_VIGOROUS = 0x01030100,
	TIMBRE_TRANSFORMATION_DEEP = 0x01030200,
	TIMBRE_TRANSFORMATION_MELLOW = 0x01030300,
	TIMBRE_TRANSFORMATION_FALSETTO = 0x01030400,
	TIMBRE_TRANSFORMATION_FULL = 0x01030500,
	TIMBRE_TRANSFORMATION_CLEAR = 0x01030600,
	TIMBRE_TRANSFORMATION_RESOUNDING = 0x01030700,
	TIMBRE_TRANSFORMATION_RINGING = 0x01030800,
	ULTRA_HIGH_QUALITY_VOICE = 0x01040100,
};

UENUM(BlueprintType)
enum class EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET:uint8{
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
	EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET ValueWrapper;

	// default
	FENUMWRAP_VOICE_BEAUTIFIER_PRESET():ValueWrapper(EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::VOICE_BEAUTIFIER_OFF){}
	

	FENUMWRAP_VOICE_BEAUTIFIER_PRESET(EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET Val):ValueWrapper(Val){}
	void operator = (EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET InValue) {
		ValueWrapper = InValue;
	}

	agora::rtc::VOICE_BEAUTIFIER_PRESET GetRawValue() const {
		switch(ValueWrapper)
		{
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::VOICE_BEAUTIFIER_OFF:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::VOICE_BEAUTIFIER_OFF;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::CHAT_BEAUTIFIER_MAGNETIC:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::CHAT_BEAUTIFIER_MAGNETIC;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::CHAT_BEAUTIFIER_FRESH:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::CHAT_BEAUTIFIER_FRESH;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::CHAT_BEAUTIFIER_VITALITY:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::CHAT_BEAUTIFIER_VITALITY;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::SINGING_BEAUTIFIER:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::SINGING_BEAUTIFIER;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_VIGOROUS:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_VIGOROUS;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_DEEP:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_DEEP;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_MELLOW:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_MELLOW;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_FALSETTO:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_FALSETTO;

		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_FULL:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_FULL;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_CLEAR:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_CLEAR;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_RESOUNDING:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_RESOUNDING;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_RINGING:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::TIMBRE_TRANSFORMATION_RINGING;
		case EENUMCUSTOM_VOICE_BEAUTIFIER_PRESET::ULTRA_HIGH_QUALITY_VOICE:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::ULTRA_HIGH_QUALITY_VOICE;

		default:
			return agora::rtc::VOICE_BEAUTIFIER_PRESET::VOICE_BEAUTIFIER_OFF;
		}
	}
};


//
//UENUM(BlueprintType)
//enum EAUDIO_EFFECT_PRESET {
//	AUDIO_EFFECT_OFF = 0x00000000,
//	ROOM_ACOUSTICS_KTV = 0x02010100,
//	ROOM_ACOUSTICS_VOCAL_CONCERT = 0x02010200,
//	ROOM_ACOUSTICS_STUDIO = 0x02010300,
//	ROOM_ACOUSTICS_PHONOGRAPH = 0x02010400,
//	ROOM_ACOUSTICS_VIRTUAL_STEREO = 0x02010500,
//	ROOM_ACOUSTICS_SPACIAL = 0x02010600,
//	ROOM_ACOUSTICS_ETHEREAL = 0x02010700,
//	ROOM_ACOUSTICS_3D_VOICE = 0x02010800,
//	ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND = 0x02010900,
//	VOICE_CHANGER_EFFECT_UNCLE = 0x02020100,
//	VOICE_CHANGER_EFFECT_OLDMAN = 0x02020200,
//	VOICE_CHANGER_EFFECT_BOY = 0x02020300,
//	VOICE_CHANGER_EFFECT_SISTER = 0x02020400,
//	VOICE_CHANGER_EFFECT_GIRL = 0x02020500,
//	VOICE_CHANGER_EFFECT_PIGKING = 0x02020600,
//	VOICE_CHANGER_EFFECT_HULK = 0x02020700,
//	STYLE_TRANSFORMATION_RNB = 0x02030100,
//	STYLE_TRANSFORMATION_POPULAR = 0x02030200,
//	PITCH_CORRECTION = 0x02040100,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_EFFECT_PRESET : uint8 {
	AUDIO_EFFECT_OFF = 0,
	ROOM_ACOUSTICS_KTV = 1,
	ROOM_ACOUSTICS_VOCAL_CONCERT = 2,
	ROOM_ACOUSTICS_STUDIO = 3,
	ROOM_ACOUSTICS_PHONOGRAPH = 4,
	ROOM_ACOUSTICS_VIRTUAL_STEREO = 5,
	ROOM_ACOUSTICS_SPACIAL = 6,
	ROOM_ACOUSTICS_ETHEREAL = 7,
	ROOM_ACOUSTICS_3D_VOICE = 8,
	ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND = 9,
	VOICE_CHANGER_EFFECT_UNCLE = 10,
	VOICE_CHANGER_EFFECT_OLDMAN = 11,
	VOICE_CHANGER_EFFECT_BOY = 12,
	VOICE_CHANGER_EFFECT_SISTER = 13,
	VOICE_CHANGER_EFFECT_GIRL = 14,
	VOICE_CHANGER_EFFECT_PIGKING = 15,
	VOICE_CHANGER_EFFECT_HULK = 16,
	STYLE_TRANSFORMATION_RNB = 17,
	STYLE_TRANSFORMATION_POPULAR = 18,
	PITCH_CORRECTION = 19
};

USTRUCT(BlueprintType)
struct FENUMWRAP_AUDIO_EFFECT_PRESET {
	GENERATED_BODY()

public:
	// require to call [GetRawValue] method to get the raw value
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AUDIO_EFFECT_PRESET")
		EENUMCUSTOM_AUDIO_EFFECT_PRESET ValueWrapper;

	// default
	FENUMWRAP_AUDIO_EFFECT_PRESET():ValueWrapper(EENUMCUSTOM_AUDIO_EFFECT_PRESET::AUDIO_EFFECT_OFF){}

	FENUMWRAP_AUDIO_EFFECT_PRESET(EENUMCUSTOM_AUDIO_EFFECT_PRESET Val):ValueWrapper(Val){}
	void operator = (EENUMCUSTOM_AUDIO_EFFECT_PRESET InValue) {
		ValueWrapper = InValue;
	}

	agora::rtc::AUDIO_EFFECT_PRESET GetRawValue() const {
		switch (ValueWrapper)
		{
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::AUDIO_EFFECT_OFF:
			return agora::rtc::AUDIO_EFFECT_PRESET::AUDIO_EFFECT_OFF;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_KTV:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_KTV;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_VOCAL_CONCERT:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_VOCAL_CONCERT;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_STUDIO:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_STUDIO;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_PHONOGRAPH:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_PHONOGRAPH;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_VIRTUAL_STEREO:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_VIRTUAL_STEREO;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_SPACIAL:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_SPACIAL;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_ETHEREAL:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_ETHEREAL;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_3D_VOICE:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_3D_VOICE;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND:
			return agora::rtc::AUDIO_EFFECT_PRESET::ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_UNCLE:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_UNCLE;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_OLDMAN:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_OLDMAN;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_BOY:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_BOY;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_SISTER:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_SISTER;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_GIRL:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_GIRL;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_PIGKING:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_PIGKING;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_HULK:
			return agora::rtc::AUDIO_EFFECT_PRESET::VOICE_CHANGER_EFFECT_HULK;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::STYLE_TRANSFORMATION_RNB:
			return agora::rtc::AUDIO_EFFECT_PRESET::STYLE_TRANSFORMATION_RNB;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::STYLE_TRANSFORMATION_POPULAR:
			return agora::rtc::AUDIO_EFFECT_PRESET::STYLE_TRANSFORMATION_POPULAR;
		case EENUMCUSTOM_AUDIO_EFFECT_PRESET::PITCH_CORRECTION:
			return agora::rtc::AUDIO_EFFECT_PRESET::PITCH_CORRECTION;
		default:
			return agora::rtc::AUDIO_EFFECT_PRESET::AUDIO_EFFECT_OFF;
		}
	}
};

//UENUM(BlueprintType)
//enum EVOICE_CONVERSION_PRESET {
//
//	VOICE_CONVERSION_OFF = 0x00000000,
//	VOICE_CHANGER_NEUTRAL = 0x03010100,
//	VOICE_CHANGER_SWEET = 0x03010200,
//	VOICE_CHANGER_SOLID = 0x03010300,
//	VOICE_CHANGER_BASS = 0x03010400,
//	VOICE_CHANGER_CARTOON = 0x03010500,
//	VOICE_CHANGER_CHILDLIKE = 0x03010600,
//	VOICE_CHANGER_PHONE_OPERATOR = 0x03010700,
//	VOICE_CHANGER_MONSTER = 0x03010800,
//	VOICE_CHANGER_TRANSFORMERS = 0x03010900,
//	VOICE_CHANGER_GROOT = 0x03010A00,
//	VOICE_CHANGER_DARTH_VADER = 0x03010B00,
//	VOICE_CHANGER_IRON_LADY = 0x03010C00,
//	VOICE_CHANGER_SHIN_CHAN = 0x03010D00,
//	VOICE_CHANGER_GIRLISH_MAN = 0x03010E00,
//	VOICE_CHANGER_CHIPMUNK = 0x03010F00,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_VOICE_CONVERSION_PRESET:uint8 {

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
		EENUMCUSTOM_VOICE_CONVERSION_PRESET ValueWrapper;

    // default 
    FENUMWRAP_VOICE_CONVERSION_PRESET():ValueWrapper(EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CONVERSION_OFF){}

    FENUMWRAP_VOICE_CONVERSION_PRESET(EENUMCUSTOM_VOICE_CONVERSION_PRESET Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_VOICE_CONVERSION_PRESET InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::VOICE_CONVERSION_PRESET GetRawValue() const {
        switch (ValueWrapper) 
        {
        case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CONVERSION_OFF:
            return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CONVERSION_OFF; 
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_NEUTRAL:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_NEUTRAL;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_SWEET:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_SWEET;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_SOLID:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_SOLID;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_BASS:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_BASS;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_CARTOON:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_CARTOON;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_CHILDLIKE:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_CHILDLIKE;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_PHONE_OPERATOR:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_PHONE_OPERATOR;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_MONSTER:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_MONSTER;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_TRANSFORMERS:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_TRANSFORMERS;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_GROOT:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_GROOT;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_IRON_LADY:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_IRON_LADY;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_SHIN_CHAN:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_SHIN_CHAN;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_GIRLISH_MAN:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_GIRLISH_MAN;
		case EENUMCUSTOM_VOICE_CONVERSION_PRESET::VOICE_CHANGER_CHIPMUNK:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CHANGER_CHIPMUNK;
		default:
			return agora::rtc::VOICE_CONVERSION_PRESET::VOICE_CONVERSION_OFF;
		}  
    }
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

UENUM(BlueprintType)
enum class ERENDER_MODE_TYPE : uint8 {
	RENDER_NULL = 0,
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

//UENUM(BlueprintType)
//enum ESIMULCAST_STREAM_MODE {
//	AUTO_SIMULCAST_STREAM = -1,
//	DISABLE_SIMULCAST_STREM = 0,
//	ENABLE_SIMULCAST_STREAM = 1,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_SIMULCAST_STREAM_MODE: uint8 {
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
		EENUMCUSTOM_SIMULCAST_STREAM_MODE ValueWrapper;

    // default 
	FENUMWRAP_SIMULCAST_STREAM_MODE():ValueWrapper(EENUMCUSTOM_SIMULCAST_STREAM_MODE::AUTO_SIMULCAST_STREAM){}

	FENUMWRAP_SIMULCAST_STREAM_MODE(EENUMCUSTOM_SIMULCAST_STREAM_MODE Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_SIMULCAST_STREAM_MODE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::SIMULCAST_STREAM_MODE GetRawValue() const {
        switch (ValueWrapper) 
        {
        case EENUMCUSTOM_SIMULCAST_STREAM_MODE::AUTO_SIMULCAST_STREAM:
            return agora::rtc::SIMULCAST_STREAM_MODE::AUTO_SIMULCAST_STREAM;
		case EENUMCUSTOM_SIMULCAST_STREAM_MODE::DISABLE_SIMULCAST_STREAM:
			return agora::rtc::SIMULCAST_STREAM_MODE::DISABLE_SIMULCAST_STREAM;
		case EENUMCUSTOM_SIMULCAST_STREAM_MODE::ENABLE_SIMULCAST_STREAM:
			return agora::rtc::SIMULCAST_STREAM_MODE::ENABLE_SIMULCAST_STREAM;
		default:
			return agora::rtc::SIMULCAST_STREAM_MODE::AUTO_SIMULCAST_STREAM;
        }  
    }
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
UENUM(BlueprintType)
enum class ELICENSE_ERROR_TYPE : uint8 {

	LICENSE_ERR_NULL = 0,

	LICENSE_ERR_INVALID = 1,

	LICENSE_ERR_EXPIRE = 2,

	LICENSE_ERR_MINUTES_EXCEED = 3,

	LICENSE_ERR_LIMITED_PERIOD = 4,

	LICENSE_ERR_DIFF_DEVICES = 5,

	LICENSE_ERR_INTERNAL = 99,
};



UENUM(BlueprintType)
enum class EAUDIO_SESSION_OPERATION_RESTRICTION : uint8 {
	AUDIO_SESSION_OPERATION_RESTRICTION_NONE = 0,
	AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY = 1,
	AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION = 1 << 1,
	AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION = 1 << 2,
	AUDIO_SESSION_OPERATION_RESTRICTION_ALL = 1 << 7,
};

UENUM(BlueprintType)
enum class EVIDEO_CONTENT_HINT : uint8 {
	CONTENT_HINT_NONE,
	CONTENT_HINT_MOTION,
	CONTENT_HINT_DETAILS,
};

UENUM(BlueprintType)
enum class ESCREEN_SCENARIO_TYPE : uint8 {
	SCREEN_SCENARIO_NULL = 0,
	SCREEN_SCENARIO_DOCUMENT = 1,
	SCREEN_SCENARIO_GAMING = 2,
	SCREEN_SCENARIO_VIDEO = 3,
	SCREEN_SCENARIO_RDC = 4,
};

UENUM(BlueprintType)
enum class EVIDEO_APPLICATION_SCENARIO_TYPE : uint8 {
	APPLICATION_SCENARIO_GENERAL = 0,
	APPLICATION_SCENARIO_VIDEO = 1,
};

//UENUM(BlueprintType)
//enum EVIDEO_ORIENTATION {
//	VIDEO_ORIENTATION_0 = 0,
//	VIDEO_ORIENTATION_90 = 90,
//	VIDEO_ORIENTATION_180 = 180,
//	VIDEO_ORIENTATION_270 = 270,
//};

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
		EENUMCUSTOM_VIDEO_ORIENTATION ValueWrapper;

	// default
	FENUMWRAP_VIDEO_ORIENTATION():ValueWrapper(EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_0){}
	

	FENUMWRAP_VIDEO_ORIENTATION(EENUMCUSTOM_VIDEO_ORIENTATION Val):ValueWrapper(Val){}
	void operator = (EENUMCUSTOM_VIDEO_ORIENTATION InValue) {
		ValueWrapper = InValue;
	}

	agora::rtc::VIDEO_ORIENTATION GetRawValue() const {
		switch(ValueWrapper)
		{
		case EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_0:
			return agora::rtc::VIDEO_ORIENTATION::VIDEO_ORIENTATION_0;
		case EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_90:
			return agora::rtc::VIDEO_ORIENTATION::VIDEO_ORIENTATION_90;
		case EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_180:
			return agora::rtc::VIDEO_ORIENTATION::VIDEO_ORIENTATION_180;
		case EENUMCUSTOM_VIDEO_ORIENTATION::VIDEO_ORIENTATION_270:
			return agora::rtc::VIDEO_ORIENTATION::VIDEO_ORIENTATION_270;
		default:
			return agora::rtc::VIDEO_ORIENTATION::VIDEO_ORIENTATION_0;
		}
	}
};


UENUM(BlueprintType)
enum class ECONNECTION_STATE_TYPE : uint8 {
	CONNECTION_NULL = 0,
	CONNECTION_STATE_DISCONNECTED = 1,
	CONNECTION_STATE_CONNECTING = 2,
	CONNECTION_STATE_CONNECTED = 3,
	CONNECTION_STATE_RECONNECTING = 4,
	CONNECTION_STATE_FAILED = 5,
};

UENUM(BlueprintType)
enum class EPRIORITY_TYPE : uint8 {
	PRIORITY_NULL = 0,
	PRIORITY_HIGH = 50,
	PRIORITY_NORMAL = 100,
};

UENUM(BlueprintType)
enum class ECLOUD_PROXY_TYPE : uint8 {
	NONE_PROXY = 0,
	UDP_PROXY = 1,
	TCP_PROXY = 2,
};
UENUM(BlueprintType)
enum class EAUDIENCE_LATENCY_LEVEL_TYPE : uint8 {
	AUDIENCE_NULL = 0,
	AUDIENCE_LATENCY_LEVEL_LOW_LATENCY = 1,
	AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY = 2,
};
USTRUCT(BlueprintType)
struct FLogUploadServerInfo {

	GENERATED_BODY()

	FString serverDomain;

	FString serverPath;

	int serverPort = 0;

	bool serverHttps =true;
};
USTRUCT(BlueprintType)
struct FAdvancedConfigInfo {

	GENERATED_BODY()
	FLogUploadServerInfo logUploadServer;
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
enum class ELOW_LIGHT_ENHANCE_MODE : uint8 {

	LOW_LIGHT_ENHANCE_AUTO = 0,

	LOW_LIGHT_ENHANCE_MANUAL = 1,
};

UENUM(BlueprintType)
enum class ELOW_LIGHT_ENHANCE_LEVEL : uint8 {

	LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY = 0,

	LOW_LIGHT_ENHANCE_LEVEL_FAST = 1,
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
enum class EMEDIA_TRACE_EVENT : uint8 {

	MEDIA_TRACE_EVENT_VIDEO_RENDERED = 0,

	MEDIA_TRACE_EVENT_VIDEO_DECODED = 1,
};

USTRUCT(BlueprintType)
struct FVideoRenderingTracingInfo {

	GENERATED_BODY()

UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int elapsedTime;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int start2JoinChannel;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int join2JoinSuccess;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int joinSuccess2RemoteJoined;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int remoteJoined2SetView;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int remoteJoined2UnmuteVideo;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoRenderingTracingInfo")
	int remoteJoined2PacketReceived;
};



USTRUCT(BlueprintType)
struct FLogConfig {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	FString filePath;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	int64 fileSizeInKB =1024;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LogConfig")
	TEnumAsByte<ELOG_LEVEL>	level = ELOG_LEVEL::LOG_LEVEL_INFO;
};

USTRUCT(BlueprintType)
struct FRecorderStreamInfo {

	GENERATED_BODY()

UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RecorderStreamInfo")
	FString channelId;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RecorderStreamInfo")
	int64 uid;
	
};



//UENUM(BlueprintType)
//enum EAREA_CODE {
//
//	AREA_CODE_NULL = 0,
//
//	AREA_CODE_CN = 0x00000001,
//
//	AREA_CODE_NA = 0x00000002,
//
//	AREA_CODE_EU = 0x00000004,
//
//	AREA_CODE_AS = 0x00000008,
//
//	AREA_CODE_JP = 0x00000010,
//
//	AREA_CODE_IN = 0x00000020,
//
//	AREA_CODE_GLOB = (0xFFFFFFFF),
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_AREA_CODE : uint8 {

	AREA_CODE_NULL = 0,

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
		EENUMCUSTOM_AREA_CODE ValueWrapper;

    // default 
    FENUMWRAP_AREA_CODE():ValueWrapper(EENUMCUSTOM_AREA_CODE::AREA_CODE_GLOB){}

    FENUMWRAP_AREA_CODE(EENUMCUSTOM_AREA_CODE Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_AREA_CODE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::AREA_CODE GetRawValue() const {
        switch (ValueWrapper) 
        {
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_CN:
			return agora::rtc::AREA_CODE::AREA_CODE_CN;
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_NA:
			return agora::rtc::AREA_CODE::AREA_CODE_NA;
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_EU:
			return agora::rtc::AREA_CODE::AREA_CODE_EU;
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_AS:
			return agora::rtc::AREA_CODE::AREA_CODE_AS;
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_JP:
			return agora::rtc::AREA_CODE::AREA_CODE_JP;
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_IN:
			return agora::rtc::AREA_CODE::AREA_CODE_IN;
		case EENUMCUSTOM_AREA_CODE::AREA_CODE_GLOB:
			return agora::rtc::AREA_CODE::AREA_CODE_GLOB;
		default:
			return	agora::rtc::AREA_CODE::AREA_CODE_GLOB;
        }
    }    
};


USTRUCT(BlueprintType)
struct FRtcEngineContext
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString appId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	UIRtcEngineEventHandler* eventHandler;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	int64 context;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString license;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	ECHANNEL_PROFILE_TYPE channelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EAUDIO_SCENARIO_TYPE audioScenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool threadPriority_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	ETHREAD_PRIORITY_TYPE threadPriority;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FLogConfig logConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FENUMWRAP_AREA_CODE areaCode = EENUMCUSTOM_AREA_CODE::AREA_CODE_GLOB;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool useExternalEglContext;
};


USTRUCT(BlueprintType)
struct FRtcEngineContextEx
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString appId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	UIRtcEngineEventHandlerEx* eventHandler;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	int64 context;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FString license;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	ECHANNEL_PROFILE_TYPE channelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	EAUDIO_SCENARIO_TYPE audioScenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool threadPriority_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	ETHREAD_PRIORITY_TYPE threadPriority;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FLogConfig logConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FENUMWRAP_AREA_CODE areaCode = EENUMCUSTOM_AREA_CODE::AREA_CODE_GLOB;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	bool useExternalEglContext;
};



USTRUCT(BlueprintType)
struct FExtensionInfo {

	GENERATED_BODY();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	EMEDIA_SOURCE_TYPE mediaSourceType = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	int64 remoteUid = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	FString channelId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ExtensionInfo")
	int64 localUid = 0;
};


USTRUCT(BlueprintType)
struct FChannelMediaOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCameraTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishSecondaryCameraTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishMicrophoneTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishScreenCaptureVideo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishScreenCaptureAudio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishScreenTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishSecondaryScreenTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCustomAudioTrack;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool publishCustomAudioTrackId_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int publishCustomAudioTrackId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCustomVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishEncodedVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishMediaPlayerAudioTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishMediaPlayerVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishTranscodedVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL autoSubscribeAudio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL autoSubscribeVideo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL enableAudioRecordingOrPlayout;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool publishMediaPlayerId_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int publishMediaPlayerId;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool clientRoleType_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	ECLIENT_ROLE_TYPE clientRoleType = ECLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool audienceLatencyLevel_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool defaultVideoStreamType_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EVIDEO_STREAM_TYPE defaultVideoStreamType;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool channelProfile_SetValue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	ECHANNEL_PROFILE_TYPE channelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool audioDelayMs_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int audioDelayMs;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool mediaPlayerAudioDelayMs_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int mediaPlayerAudioDelayMs;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool token_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	FString token;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL enableBuiltInMediaEncryption;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishRhythmPlayerTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL isInteractiveAudience;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool customVideoTrackId_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int64 customVideoTrackId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL isAudioFilterable;
};

// Set ChannelMediaOptions Using FAgora_ChannelMediaOptions
#define SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(Agora_ChannelMediaOptions,UE_FAgora_ChannelMediaOptions)\
{\
		if (UE_FAgora_ChannelMediaOptions.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishScreenCaptureVideo = UE_FAgora_ChannelMediaOptions.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishScreenCaptureAudio = UE_FAgora_ChannelMediaOptions.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		SET_AGORA_DATA_CHANNELMEDIAOPTIONS_INNER_COMMON(Agora_ChannelMediaOptions,UE_FAgora_ChannelMediaOptions); \
}

#define SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(Agora_ChannelMediaOptions,UE_FAgora_ChannelMediaOptions) \
{\
		if (UE_FAgora_ChannelMediaOptions.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishScreenTrack = UE_FAgora_ChannelMediaOptions.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishSecondaryScreenTrack = UE_FAgora_ChannelMediaOptions.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		SET_AGORA_DATA_CHANNELMEDIAOPTIONS_INNER_COMMON(Agora_ChannelMediaOptions,UE_FAgora_ChannelMediaOptions); \
}


#define SET_AGORA_DATA_CHANNELMEDIAOPTIONS_INNER_COMMON(Agora_ChannelMediaOptions,UE_FAgora_ChannelMediaOptions)\
{\
		if (UE_FAgora_ChannelMediaOptions.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishCameraTrack = UE_FAgora_ChannelMediaOptions.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)\
		{ \
			Agora_ChannelMediaOptions.publishSecondaryCameraTrack = UE_FAgora_ChannelMediaOptions.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishMicrophoneTrack = UE_FAgora_ChannelMediaOptions.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishCustomAudioTrack = UE_FAgora_ChannelMediaOptions.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishCustomVideoTrack = UE_FAgora_ChannelMediaOptions.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishEncodedVideoTrack = UE_FAgora_ChannelMediaOptions.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishMediaPlayerAudioTrack = UE_FAgora_ChannelMediaOptions.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishMediaPlayerVideoTrack = UE_FAgora_ChannelMediaOptions.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishTranscodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishTranscodedVideoTrack = UE_FAgora_ChannelMediaOptions.publishTranscodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.autoSubscribeAudio = UE_FAgora_ChannelMediaOptions.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.autoSubscribeVideo = UE_FAgora_ChannelMediaOptions.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.enableAudioRecordingOrPlayout = UE_FAgora_ChannelMediaOptions.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishMediaPlayerId_SetValue) \
		{ \
			Agora_ChannelMediaOptions.publishMediaPlayerId = UE_FAgora_ChannelMediaOptions.publishMediaPlayerId; \
		} \
		if (UE_FAgora_ChannelMediaOptions.clientRoleType_SetValue) \
		{ \
			Agora_ChannelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)UE_FAgora_ChannelMediaOptions.clientRoleType; \
		} \
		if (UE_FAgora_ChannelMediaOptions.audienceLatencyLevel_SetValue) \
		{ \
			Agora_ChannelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)UE_FAgora_ChannelMediaOptions.audienceLatencyLevel; \
		} \
		if (UE_FAgora_ChannelMediaOptions.defaultVideoStreamType_SetValue) \
		{ \
			Agora_ChannelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)UE_FAgora_ChannelMediaOptions.defaultVideoStreamType; \
		} \
		if (UE_FAgora_ChannelMediaOptions.channelProfile_SetValue) \
		{ \
			Agora_ChannelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)UE_FAgora_ChannelMediaOptions.channelProfile; \
		} \
		if (UE_FAgora_ChannelMediaOptions.audioDelayMs_SetValue) \
		{ \
			Agora_ChannelMediaOptions.audioDelayMs = UE_FAgora_ChannelMediaOptions.audioDelayMs; \
		} \
		if (UE_FAgora_ChannelMediaOptions.mediaPlayerAudioDelayMs_SetValue) \
		{ \
			Agora_ChannelMediaOptions.mediaPlayerAudioDelayMs = UE_FAgora_ChannelMediaOptions.mediaPlayerAudioDelayMs; \
		} \
		if (UE_FAgora_ChannelMediaOptions.token_SetValue) \
		{ \
			std::string Token = TCHAR_TO_UTF8(*UE_FAgora_ChannelMediaOptions.token); \
 \
			Agora_ChannelMediaOptions.token = Token.c_str(); \
		} \
		if (UE_FAgora_ChannelMediaOptions.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.enableBuiltInMediaEncryption = UE_FAgora_ChannelMediaOptions.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.publishRhythmPlayerTrack = UE_FAgora_ChannelMediaOptions.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.isInteractiveAudience = UE_FAgora_ChannelMediaOptions.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
		if (UE_FAgora_ChannelMediaOptions.customVideoTrackId_SetValue) \
		{ \
			Agora_ChannelMediaOptions.customVideoTrackId = UE_FAgora_ChannelMediaOptions.customVideoTrackId; \
		} \
		if (UE_FAgora_ChannelMediaOptions.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE) \
		{ \
			Agora_ChannelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE; \
		} \
}




USTRUCT(BlueprintType)
struct FLeaveChannelOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	AGORAOPTIONAL stopAudioMixing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	AGORAOPTIONAL stopAllEffect;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LeaveChannelOptions")
	AGORAOPTIONAL stopMicrophoneRecording;
};

#define SET_AGORA_DATA_LEAVECHANNELOPTIONS(Agora_LeaveChannelOptions,UE_FAgora_LeaveChannelOptions)\
{\
	if (UE_FAgora_LeaveChannelOptions.stopAudioMixing != AGORAOPTIONAL::AGORA_NULL_VALUE)          \
	{   \
		Agora_LeaveChannelOptions.stopAudioMixing = UE_FAgora_LeaveChannelOptions.stopAudioMixing == AGORAOPTIONAL::AGORA_TRUE_VALUE;        \
	}   \
	if (UE_FAgora_LeaveChannelOptions.stopAllEffect != AGORAOPTIONAL::AGORA_NULL_VALUE)        \
	{   \
		Agora_LeaveChannelOptions.stopAllEffect = UE_FAgora_LeaveChannelOptions.stopAllEffect == AGORAOPTIONAL::AGORA_TRUE_VALUE;        \
	}   \
	if (UE_FAgora_LeaveChannelOptions.stopMicrophoneRecording != AGORAOPTIONAL::AGORA_NULL_VALUE)             \
	{   \
		Agora_LeaveChannelOptions.stopMicrophoneRecording = UE_FAgora_LeaveChannelOptions.stopMicrophoneRecording == AGORAOPTIONAL::AGORA_TRUE_VALUE;            \
	}  \
}



USTRUCT(BlueprintType)
struct FClientRoleOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ClientRoleOptions")
	EAUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel = EAUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY;
};

USTRUCT(BlueprintType)
struct FEchoTestConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	UImage* view;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	bool enableAudio = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	bool enableVideo = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	FString token;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	FString channelId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	int intervalInSeconds = 2;
};


UENUM(BlueprintType)
enum class EVIDEO_TRANSCODER_ERROR : uint8 {
	VT_ERR_OK = 0,
	VT_ERR_VIDEO_SOURCE_NOT_READY = 1,
	VT_ERR_INVALID_VIDEO_SOURCE_TYPE = 2,
	VT_ERR_INVALID_IMAGE_PATH = 3,
	VT_ERR_UNSUPPORT_IMAGE_FORMAT = 4,
	VT_ERR_INVALID_LAYOUT = 5,
	VT_ERR_INTERNAL = 20

};

USTRUCT(BlueprintType)
struct FLastmileProbeConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	bool probeUplink;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	bool probeDownlink;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	int expectedUplinkBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	int expectedDownlinkBitrate;
};

USTRUCT(BlueprintType)
struct FVideoDimensions {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	int width = 640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig")
	int height = 480;
};

USTRUCT(BlueprintType)
struct FCodecCapInfo {

	GENERATED_BODY()	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	EVIDEO_CODEC_TYPE codecType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CodecCapInfo")
	int codecCapMask;
};

USTRUCT(BlueprintType)
struct FVideoEncoderConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	EVIDEO_CODEC_TYPE codecType = EVIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	FVideoDimensions dimensions;
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
	ECOMPRESSION_PREFERENCE compressionPreference = ECOMPRESSION_PREFERENCE::PREFER_LOW_LATENCY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration")
	FAdvanceOptions advanceOptions;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	ELIGHTENING_CONTRAST_LEVEL lighteningContrastLevel = ELIGHTENING_CONTRAST_LEVEL::LIGHTENING_CONTRAST_NORMAL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float lighteningLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float smoothnessLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float rednessLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions")
	float sharpnessLevel;
};

USTRUCT(BlueprintType)
struct FLowlightEnhanceOptions
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LowlightEnhanceOptions")
	ELOW_LIGHT_ENHANCE_MODE mode =ELOW_LIGHT_ENHANCE_MODE::LOW_LIGHT_ENHANCE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LowlightEnhanceOptions")
	ELOW_LIGHT_ENHANCE_LEVEL level=ELOW_LIGHT_ENHANCE_LEVEL::LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDenoiserOptions")
	EVIDEO_DENOISER_MODE mode = EVIDEO_DENOISER_MODE::VIDEO_DENOISER_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDenoiserOptions")
	EVIDEO_DENOISER_LEVEL level = EVIDEO_DENOISER_LEVEL::VIDEO_DENOISER_LEVEL_HIGH_QUALITY;
};


USTRUCT(BlueprintType)
struct FColorEnhanceOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ColorEnhanceOptions")
	float strengthLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ColorEnhanceOptions")
	float skinProtectLevel;
};


UENUM(BlueprintType)
enum class EBACKGROUND_SOURCE_TYPE :uint8 {

	BACKGROUND_NULL = 0,

	BACKGROUND_COLOR = 1,

	BACKGROUND_IMG = 2,

	BACKGROUND_BLUR = 3,

	BACKGROUND_VIDEO = 4,
};

UENUM(BlueprintType)
enum class EBACKGROUND_BLUR_DEGREE :uint8 {

	BLUR_NULL = 0,

	BLUR_DEGREE_LOW = 1,

	BLUR_DEGREE_MEDIUM = 2,

	BLUR_DEGREE_HIGH = 3,
};


USTRUCT(BlueprintType)
struct FVirtualBackgroundSource
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	EBACKGROUND_SOURCE_TYPE background_source_type = EBACKGROUND_SOURCE_TYPE::BACKGROUND_COLOR;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	int64 color = 0xffffff;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	FString source;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VirtualBackgroundSource")
	EBACKGROUND_BLUR_DEGREE blur_degree = EBACKGROUND_BLUR_DEGREE::BLUR_DEGREE_HIGH;
};
UENUM(BlueprintType)
enum class ESEG_MODEL_TYPE : uint8 {

	SEG_MODEL_NULL,
	SEG_MODEL_AI = 1,
	SEG_MODEL_GREEN = 2
};

USTRUCT(BlueprintType)
struct FSegmentationProperty
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SegmentationProperty")
	ESEG_MODEL_TYPE modelType =ESEG_MODEL_TYPE::SEG_MODEL_AI;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SegmentationProperty")
	float greenCapacity = 0.5;
};

UENUM(BlueprintType)
enum class EVIDEO_VIEW_SETUP_MODE : uint8 {

	VIDEO_VIEW_SETUP_REPLACE = 0,

	VIDEO_VIEW_SETUP_ADD = 1,

	VIDEO_VIEW_SETUP_REMOVE = 2,
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
	ETCcMode ccMode =ETCcMode::CC_ENABLED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	EVIDEO_CODEC_TYPE codecType =EVIDEO_CODEC_TYPE::VIDEO_CODEC_GENERIC_H264;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SenderOptions")
	int targetBitrate = 6500;
};


USTRUCT(BlueprintType)
struct FRectangle
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int x;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int y;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle")
	int height;
};

USTRUCT(BlueprintType)
struct FVideoCanvas
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	UImage* view;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	ERENDER_MODE_TYPE renderMode = ERENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_MIRROR_MODE_TYPE mirrorMode =EVIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	bool isScreenView = false;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	//void priv;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	int64 priv_size;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	FRectangle cropArea;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas")
	EVIDEO_VIEW_SETUP_MODE setupMode = EVIDEO_VIEW_SETUP_MODE::VIDEO_VIEW_SETUP_REPLACE;
};

USTRUCT(BlueprintType)
struct FVideoSubscriptionOptions
{
	GENERATED_BODY()
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	bool type_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	EVIDEO_STREAM_TYPE type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	AGORAOPTIONAL encodedFrameOnly;
};

#define SET_AGORA_DATA_VIDEOSUBSCRIPTIONOPTIONS(Agora_VideoSubscriptionOptions,UE_FVideoSubscriptionOptions)    \
{ \
	if (UE_FVideoSubscriptionOptions.type_SetValue)    \
	{    \
		Agora_VideoSubscriptionOptions.type = (agora::rtc::VIDEO_STREAM_TYPE)UE_FVideoSubscriptionOptions.type;    \
	}    \
	\
	if (UE_FVideoSubscriptionOptions.encodedFrameOnly != AGORAOPTIONAL::AGORA_NULL_VALUE)    \
	{    \
		Agora_VideoSubscriptionOptions.encodedFrameOnly = UE_FVideoSubscriptionOptions.encodedFrameOnly == AGORAOPTIONAL::AGORA_TRUE_VALUE;    \
	}    \
}

UENUM(BlueprintType)
enum class EAUDIO_FILE_RECORDING_TYPE :uint8 {

	AUDIO_FILE_NULL = 0,

	AUDIO_FILE_RECORDING_MIC = 1,

	AUDIO_FILE_RECORDING_PLAYBACK = 2,

	AUDIO_FILE_RECORDING_MIXED = 3,
};


USTRUCT(BlueprintType)
struct FAudioRecordingConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	FString filePath;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	bool encode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	int sampleRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	EAUDIO_FILE_RECORDING_TYPE fileRecordingType = EAUDIO_FILE_RECORDING_TYPE::AUDIO_FILE_RECORDING_MIXED;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	EAUDIO_RECORDING_QUALITY_TYPE quality = EAUDIO_RECORDING_QUALITY_TYPE::AUDIO_RECORDING_QUALITY_LOW;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioRecordingConfiguration")
	int recordingChannel;
};

UENUM(BlueprintType)
enum class EAUDIO_ENCODED_FRAME_OBSERVER_POSITION :uint8 {

	AUDIO_ENCODED_FRAME_NULL = 0,

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_RECORD = 1,

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_PLAYBACK = 2,

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_MIXED = 3,
};

//UENUM(BlueprintType)
//enum EENUMCUSTOM_AUDIO_ENCODING_TYPE {
//
//	AUDIO_ENCODING_TYPE_AAC_16000_LOW = 0x010101,
//	AUDIO_ENCODING_TYPE_AAC_16000_MEDIUM = 0x010102,
//	AUDIO_ENCODING_TYPE_AAC_32000_LOW = 0x010201,
//	AUDIO_ENCODING_TYPE_AAC_32000_MEDIUM = 0x010202,
//	AUDIO_ENCODING_TYPE_AAC_32000_HIGH = 0x010203,
//	AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM = 0x010302,
//	AUDIO_ENCODING_TYPE_AAC_48000_HIGH = 0x010303,
//	AUDIO_ENCODING_TYPE_OPUS_16000_LOW = 0x020101,
//	AUDIO_ENCODING_TYPE_OPUS_16000_MEDIUM = 0x020102,
//	AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM = 0x020302,
//	AUDIO_ENCODING_TYPE_OPUS_48000_HIGH = 0x020303,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_ENCODING_TYPE : uint8 {

	AUDIO_ENCODING_TYPE_NULL = 0,
	AUDIO_ENCODING_TYPE_AAC_16000_LOW = 1,
	AUDIO_ENCODING_TYPE_AAC_16000_MEDIUM = 2,
	AUDIO_ENCODING_TYPE_AAC_32000_LOW = 3,
	AUDIO_ENCODING_TYPE_AAC_32000_MEDIUM = 4,
	AUDIO_ENCODING_TYPE_AAC_32000_HIGH = 5,
	AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM = 6,
	AUDIO_ENCODING_TYPE_AAC_48000_HIGH = 7,
	AUDIO_ENCODING_TYPE_OPUS_16000_LOW = 8,
	AUDIO_ENCODING_TYPE_OPUS_16000_MEDIUM = 9,
	AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM = 10,
	AUDIO_ENCODING_TYPE_OPUS_48000_HIGH = 11,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_AUDIO_ENCODING_TYPE 
{
    GENERATED_BODY()

public:
    // require to call [GetRawValue] method to get the raw value
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_AUDIO_ENCODING_TYPE")
		EENUMCUSTOM_AUDIO_ENCODING_TYPE ValueWrapper;

    // default
    FENUMWRAP_AUDIO_ENCODING_TYPE():ValueWrapper(EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM){}

    FENUMWRAP_AUDIO_ENCODING_TYPE(EENUMCUSTOM_AUDIO_ENCODING_TYPE Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_AUDIO_ENCODING_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::AUDIO_ENCODING_TYPE GetRawValue() const {
        switch (ValueWrapper) 
        {
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_16000_LOW:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_16000_LOW;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_16000_MEDIUM:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_16000_MEDIUM;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_LOW:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_LOW;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_MEDIUM:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_MEDIUM;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_HIGH:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_HIGH;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_HIGH:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_HIGH;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_16000_LOW:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_16000_LOW;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_16000_MEDIUM:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_16000_MEDIUM;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM;
		case EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_HIGH:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_HIGH;
		default:
			return agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM;
        }
    }    
};

USTRUCT(BlueprintType)
struct FAudioEncodedFrameObserverConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioEncodedFrameObserverConfig")
	EAUDIO_ENCODED_FRAME_OBSERVER_POSITION postionType = EAUDIO_ENCODED_FRAME_OBSERVER_POSITION::AUDIO_ENCODED_FRAME_OBSERVER_POSITION_PLAYBACK;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioEncodedFrameObserverConfig")
	FENUMWRAP_AUDIO_ENCODING_TYPE encodingType = EENUMCUSTOM_AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM;
};

USTRUCT(BlueprintType)
struct FSpatialAudioParams
{
	GENERATED_BODY()

	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_azimuth_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_azimuth;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_elevation_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_elevation;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_distance_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_distance;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_orientation_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	int speaker_orientation;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_blur_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_blur;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_air_absorb_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_air_absorb;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool speaker_attenuation_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_attenuation;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_doppler_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_doppler;
};

#define SET_AGORA_DATA_SPATIALAUDIOPARAMS(Agora_SpatialAudioParams,UE_FSpatialAudioParams)        \
{\
	if (UE_FSpatialAudioParams.speaker_azimuth_SetValue)  \
	{     \
	    Agora_SpatialAudioParams.speaker_azimuth = UE_FSpatialAudioParams.speaker_azimuth;    \
	}    \
	\
	if (UE_FSpatialAudioParams.speaker_elevation_SetValue) \
	{     \
	    Agora_SpatialAudioParams.speaker_elevation = UE_FSpatialAudioParams.speaker_elevation;    \
	}    \
	\
	if (UE_FSpatialAudioParams.speaker_distance_SetValue) \
	{     \
	    Agora_SpatialAudioParams.speaker_distance = UE_FSpatialAudioParams.speaker_distance;    \
	}    \
	\
	if (UE_FSpatialAudioParams.speaker_orientation_SetValue)  \
	{     \
	    Agora_SpatialAudioParams.speaker_orientation = UE_FSpatialAudioParams.speaker_orientation;    \
	}    \
	\
	if (UE_FSpatialAudioParams.enable_blur_SetValue)  \
	{     \
	    Agora_SpatialAudioParams.enable_blur = UE_FSpatialAudioParams.enable_blur;    \
	}    \
	\
	if (UE_FSpatialAudioParams.enable_air_absorb_SetValue) \
	{     \
	    Agora_SpatialAudioParams.enable_air_absorb = UE_FSpatialAudioParams.enable_air_absorb;    \
	}    \
	\
	if (UE_FSpatialAudioParams.speaker_attenuation_SetValue)  \
	{     \
	    Agora_SpatialAudioParams.speaker_attenuation = UE_FSpatialAudioParams.speaker_attenuation;    \
	}    \
	\
	if (UE_FSpatialAudioParams.enable_doppler_SetValue)   \
	{     \
	    Agora_SpatialAudioParams.enable_doppler = UE_FSpatialAudioParams.enable_doppler;    \
	}	\
}


USTRUCT(BlueprintType)
struct FSimulcastStreamConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	FVideoDimensions dimensions;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	int bitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SimulcastStreamConfig")
	int framerate;
};
USTRUCT(BlueprintType)
struct FAudioTrackConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioTrackConfig")
	bool enableLocalPlayback = true;
};

UENUM(BlueprintType)
enum class ECAMERA_DIRECTION :uint8 {

	CAMERA_REAR = 0,

	CAMERA_FRONT = 1,
};

USTRUCT(BlueprintType)
struct FVideoFormat {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int width=640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int height=360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoFormat")
	int fps=15;
};

USTRUCT(BlueprintType)
struct FCameraCapturerConfiguration
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	ECAMERA_DIRECTION cameraDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	FString deviceId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	FVideoFormat format;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration")
	bool followEncodeDimensionRatio = true;
};

USTRUCT(BlueprintType)
struct FScreenCaptureParameters
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	FVideoDimensions dimensions;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int frameRate=5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int bitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	bool captureMouseCursor=true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	bool windowFocus=false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int64 excludeWindowList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int excludeWindowCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int highLightWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	int highLightColor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters")
	bool enableHighLight=false;
};


USTRUCT(BlueprintType)
struct FDeviceInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DeviceInfo")
	bool isLowLatencyAudioSupported;
};

USTRUCT(BlueprintType)
struct FScreenAudioParameters {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenAudioParameters")
	int sampleRate = 16000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenAudioParameters")
	int channels = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenAudioParameters")
	int captureSignalVolume = 100;

};


USTRUCT(BlueprintType)
struct FScreenVideoParameters {

	GENERATED_BODY()

	FVideoDimensions dimensions;

	int frameRate = 15;

	int bitrate;

	EVIDEO_CONTENT_HINT contentHint = EVIDEO_CONTENT_HINT::CONTENT_HINT_MOTION;

};

USTRUCT(BlueprintType)
struct FScreenCaptureParameters2
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	bool captureAudio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	FScreenAudioParameters audioParams;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	bool captureVideo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters2")
	FScreenVideoParameters videoParams;
};

USTRUCT(BlueprintType)
struct FTranscodingUser {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int x;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int y;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int zOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	float alpha = 1.0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser")
	int audioChannel;

};

USTRUCT(BlueprintType)
struct FLiveStreamAdvancedFeature {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveStreamAdvancedFeature")
	FString featureName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveStreamAdvancedFeature")
	bool opened;
};

UENUM(BlueprintType)
enum class EVIDEO_CODEC_PROFILE_TYPE : uint8 {

	VIDEO_CODEC_PROFILE_NULL = 0,

	VIDEO_CODEC_PROFILE_BASELINE = 66,

	VIDEO_CODEC_PROFILE_MAIN = 77,

	VIDEO_CODEC_PROFILE_HIGH = 100,
};

UENUM(BlueprintType)
enum class EVIDEO_CODEC_TYPE_FOR_STREAM : uint8 {

	VIDEO_CODEC_NULL = 0,

	VIDEO_CODEC_H264_FOR_STREAM = 1,

	VIDEO_CODEC_H265_FOR_STREAM = 2,
};

UENUM(BlueprintType)
enum class EAUDIO_CODEC_PROFILE_TYPE : uint8 {

	AUDIO_CODEC_PROFILE_LC_AAC = 0,

	AUDIO_CODEC_PROFILE_HE_AAC = 1,

	AUDIO_CODEC_PROFILE_HE_AAC_V2 = 2,
};



USTRUCT(BlueprintType)
struct FLiveTranscoding
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int width=360;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int height=640;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int videoBitrate=400;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int videoFramerate=15;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	bool lowLatency=false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int videoGop=30;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EVIDEO_CODEC_PROFILE_TYPE videoCodecProfile = EVIDEO_CODEC_PROFILE_TYPE::VIDEO_CODEC_PROFILE_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int64 backgroundColor = 0x000000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EVIDEO_CODEC_TYPE_FOR_STREAM videoCodecType =EVIDEO_CODEC_TYPE_FOR_STREAM::VIDEO_CODEC_H264_FOR_STREAM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int userCount=0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FTranscodingUser> transcodingUsers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	FString transcodingExtraInfo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	FString metadata;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray <FRtcImage> watermark;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int watermarkCount=0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FRtcImage> backgroundImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int backgroundImageCount=0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TEnumAsByte<EAUDIO_SAMPLE_RATE_TYPE> audioSampleRate = EAUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int audioBitrate=48;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int audioChannels=1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	EAUDIO_CODEC_PROFILE_TYPE audioCodecProfile =EAUDIO_CODEC_PROFILE_TYPE::AUDIO_CODEC_PROFILE_LC_AAC;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	TArray<FLiveStreamAdvancedFeature> advancedFeatures;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding")
	int advancedFeatureCount = 0;
};

USTRUCT(BlueprintType)
struct FTranscodingVideoStream {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	EMEDIA_SOURCE_TYPE sourceType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int64 remoteUserUid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	FString imageUrl;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int x;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int y;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	int zOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	float alpha;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingVideoStream")
	bool mirror;
};

USTRUCT(BlueprintType)
struct FLocalTranscoderConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	int streamCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	TArray<FTranscodingVideoStream> VideoInputStreams;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	FVideoEncoderConfiguration videoOutputConfiguration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalTranscoderConfiguration")
	bool syncWithPrimaryCamera=true;
};


USTRUCT(BlueprintType)
struct FScreenCaptureConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	bool isCaptureWindow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	int displayId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FRectangle screenRect;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	int64 windowId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FScreenCaptureParameters params;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureConfiguration")
	FRectangle regionRect;
};

UENUM(BlueprintType)
enum class ENCRYPTION_MODE :uint8 {

	AES_NULL = 0,

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	ENCRYPTION_MODE encryptionMode = ENCRYPTION_MODE::AES_128_GCM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	FString encryptionKey;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EncryptionConfig")
	FString encryptionKdfSalt;
};

USTRUCT(BlueprintType)
struct FDataStreamConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DataStreamConfig")
	bool syncWithAudio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DataStreamConfig")
	bool ordered;
};



USTRUCT(BlueprintType)
struct FWatermarkRatio {

	GENERATED_BODY()

	float xRatio;

	float yRatio;

	float widthRatio;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	bool visibleInPreview;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FRectangle positionInLandscapeMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FRectangle positionInPortraitMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	FWatermarkRatio watermarkRatio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions")
	EWATERMARK_FIT_MODE mode = EWATERMARK_FIT_MODE::FIT_MODE_COVER_POSITION;
};




USTRUCT(BlueprintType)
struct FInjectStreamConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int videoGop;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int videoFramerate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int videoBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	TEnumAsByte<EAUDIO_SAMPLE_RATE_TYPE> audioSampleRate = EAUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int audioBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig")
	int audioChannels;
};

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo")
	FString userAccount;
};

USTRUCT(BlueprintType)
struct FChannelMediaInfo {

	GENERATED_BODY()

	FString channelName;

	FString token;

	int64 uid;

};

USTRUCT(BlueprintType)
struct FChannelMediaRelayConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	FChannelMediaInfo srcInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	TArray<FChannelMediaInfo> destInfos;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration")
	int destCount;
};

USTRUCT(BlueprintType)
struct FDirectCdnStreamingMediaOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL publishCameraTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL publishMicrophoneTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL publishCustomAudioTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL publishCustomVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL publishMediaPlayerAudioTrack;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	bool publishMediaPlayerId_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	int publishMediaPlayerId;
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	bool customVideoTrackId_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	int64 customVideoTrackId;
};

#define SET_AGORA_DATA_DIRECTCDNSTREAMINGMEDIAOPTIONS(Agora_DirectCdnStreamingMediaOptions,UE_FDirectCdnStreamingMediaOptions)\
{\
	if (UE_FDirectCdnStreamingMediaOptions.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.publishCameraTrack = UE_FDirectCdnStreamingMediaOptions.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;         \
	}         \
	if (UE_FDirectCdnStreamingMediaOptions.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.publishMicrophoneTrack = UE_FDirectCdnStreamingMediaOptions.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;         \
	}         \
	if (UE_FDirectCdnStreamingMediaOptions.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.publishCustomAudioTrack = UE_FDirectCdnStreamingMediaOptions.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;         \
	}         \
	if (UE_FDirectCdnStreamingMediaOptions.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.publishCustomVideoTrack = UE_FDirectCdnStreamingMediaOptions.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;         \
	}         \
	if (UE_FDirectCdnStreamingMediaOptions.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.publishMediaPlayerAudioTrack = UE_FDirectCdnStreamingMediaOptions.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;         \
	}         \
	if (UE_FDirectCdnStreamingMediaOptions.publishMediaPlayerId_SetValue)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.publishMediaPlayerId = UE_FDirectCdnStreamingMediaOptions.publishMediaPlayerId;         \
	}         \
	if (UE_FDirectCdnStreamingMediaOptions.customVideoTrackId_SetValue)         \
	{         \
		Agora_DirectCdnStreamingMediaOptions.customVideoTrackId = UE_FDirectCdnStreamingMediaOptions.customVideoTrackId;         \
	}         \
}


USTRUCT(BlueprintType)
struct FAgoraRhythmPlayerConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraRhythmPlayerConfig")
	int beatsPerMeasure = 4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraRhythmPlayerConfig")
	int beatsPerMinute = 60;
};
UENUM(BlueprintType)
enum ECONTENT_INSPECT_TYPE {

	CONTENT_INSPECT_INVALID = 0,

	CONTENT_INSPECT_MODERATION = 1,

	CONTENT_INSPECT_SUPERVISION = 2
};

USTRUCT(BlueprintType)
struct FContentInspectModule {

	GENERATED_BODY()

	ECONTENT_INSPECT_TYPE type = ECONTENT_INSPECT_TYPE::CONTENT_INSPECT_INVALID;

	int64 interval = 0;
};

USTRUCT(BlueprintType)
struct FContentInspectConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	FString extraInfo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	TArray<FContentInspectModule> modules;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ContentInspectConfig")
	int moduleCount;
};

UENUM(BlueprintType)
enum class ELOCAL_PROXY_MODE :uint8 {

	ConnectivityFirst = 0,

	LocalOnly = 1,
};

USTRUCT(BlueprintType)
struct FLocalAccessPointConfiguration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	FString ipList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	int ipListSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	FString domainList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	int domainListSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	FString verifyDomainName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAccessPointConfiguration")
	ELOCAL_PROXY_MODE mode = ELOCAL_PROXY_MODE::ConnectivityFirst;
};

USTRUCT(BlueprintType)
struct FAdvancedAudioOptions
{
	GENERATED_BODY()
	// If the box is unchecked, the value of the corresponding variable (named without _SetValue)  will be ignored.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	bool audioProcessingChannels_SetValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	int audioProcessingChannels;
};

#define SET_AGORA_DATA_ADVANCEDAUDIOOPTIONS(Agora_AdvancedAudioOptions,UE_FAdvancedAudioOptions)\
{\
	if (UE_FAdvancedAudioOptions.audioProcessingChannels_SetValue) \
	{ \
		Agora_AdvancedAudioOptions.audioProcessingChannels = UE_FAdvancedAudioOptions.audioProcessingChannels; \
	} \
}

USTRUCT(BlueprintType)
struct FImageTrackOptions
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ImageTrackOptions")
	FString imageUrl;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ImageTrackOptions")
	int fps = 1;
};

USTRUCT(BlueprintType)
struct FRtcConnection
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcConnection")
	FString channelId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcConnection")
	int64 localUid;
};
UENUM(BlueprintType)
enum class ELASTMILE_PROBE_RESULT_STATE :uint8 {

	LASTMILE_PROBE_RESULT_NULL = 0,

	LASTMILE_PROBE_RESULT_COMPLETE = 1,

	LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE = 2,

	LASTMILE_PROBE_RESULT_UNAVAILABLE = 3
};

USTRUCT(BlueprintType)
struct FLastmileProbeOneWayResult {

	GENERATED_BODY()
	int64 packetLossRate;

	int64 jitter;

	int64 availableBandwidth;
};


USTRUCT(BlueprintType)
struct FLastmileProbeResult {

	GENERATED_BODY()

	ELASTMILE_PROBE_RESULT_STATE state = ELASTMILE_PROBE_RESULT_STATE::LASTMILE_PROBE_RESULT_UNAVAILABLE;

	FLastmileProbeOneWayResult uplinkReport;

	FLastmileProbeOneWayResult downlinkReport;

	int64 rtt = 0;
};

USTRUCT(BlueprintType)
struct FAudioVolumeInfo {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	int64 volume;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	int64 vad;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo")
	float voicePitch;

};


USTRUCT(BlueprintType)
struct FRtcStats
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 duration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 txBytes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 rxBytes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 txAudioBytes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 txVideoBytes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 rxAudioBytes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 rxVideoBytes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txKBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxKBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxAudioKBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txAudioKBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxVideoKBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txVideoKBitRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 lastmileDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int64 userCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	float cpuAppUsage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	float cpuTotalUsage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 connectTimeMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstAudioPacketDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoPacketDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFramePacketDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 packetsBeforeFirstKeyFramePacket;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstAudioPacketDurationAfterUnmute;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoPacketDurationAfterUnmute;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFramePacketDurationAfterUnmute;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFrameDecodedDurationAfterUnmute;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 firstVideoKeyFrameRenderedDurationAfterUnmute;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 txPacketLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int32 rxPacketLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int gatewayRtt;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	float memoryAppUsageRatio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	float memoryTotalUsageRatio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats")
	int memoryAppUsageInKbytes;
};

USTRUCT(BlueprintType)
struct FUplinkNetworkInfo {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FUplinkNetworkInfo")
	int video_encoder_target_bitrate_bps;
};

UENUM(BlueprintType)
enum class EREMOTE_VIDEO_DOWNSCALE_LEVEL : uint8 {

	REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_1,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_2,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_3,

	REMOTE_VIDEO_DOWNSCALE_LEVEL_4,
};

USTRUCT(BlueprintType)
struct FPeerDownlinkInfo {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPeerDownlinkInfo")
	FString uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPeerDownlinkInfo")
	EVIDEO_STREAM_TYPE stream_type = EVIDEO_STREAM_TYPE::VIDEO_STREAM_HIGH;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPeerDownlinkInfo")
	EREMOTE_VIDEO_DOWNSCALE_LEVEL current_downscale_level = EREMOTE_VIDEO_DOWNSCALE_LEVEL::REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FPeerDownlinkInfo")
	int expected_bitrate_bps;
};
USTRUCT(BlueprintType)
struct FDownlinkNetworkInfo {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int lastmile_buffer_delay_time_ms = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int bandwidth_estimation_bps = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int total_downscale_level_count = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	FPeerDownlinkInfo peer_downlink_info;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DownlinkNetworkInfo")
	int total_received_video_count = -1;
};

UENUM(BlueprintType)
enum class ELOCAL_VIDEO_STREAM_STATE : uint8 {

	LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,

	LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,

	LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,

	LOCAL_VIDEO_STREAM_STATE_FAILED = 3
};

UENUM(BlueprintType)
enum class ELOCAL_VIDEO_STREAM_ERROR : uint8 {
	LOCAL_VIDEO_STREAM_ERROR_OK = 0,
	LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1,
	LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
	LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3,
	LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4,
	LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5,
	LOCAL_VIDEO_STREAM_ERROR_CAPTURE_INBACKGROUND = 6,
	LOCAL_VIDEO_STREAM_ERROR_CAPTURE_MULTIPLE_FOREGROUND_APPS = 7,
	LOCAL_VIDEO_STREAM_ERROR_DEVICE_NOT_FOUND = 8,
	LOCAL_VIDEO_STREAM_ERROR_DEVICE_DISCONNECTED = 9,
	LOCAL_VIDEO_STREAM_ERROR_DEVICE_INVALID_ID = 10,
	LOCAL_VIDEO_STREAM_ERROR_DEVICE_SYSTEM_PRESSURE = 101,
	LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_MINIMIZED = 11,
	LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_CLOSED = 12,
	LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_OCCLUDED = 13,
	LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_NOT_SUPPORTED = 20,
	LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_FAILURE = 21,
	LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_NO_PERMISSION = 22,
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
enum class EUSER_OFFLINE_REASON_TYPE : uint8 {

	USER_OFFLINE_QUIT = 0,

	USER_OFFLINE_DROPPED = 1,

	USER_OFFLINE_BECOME_AUDIENCE = 2,
};

USTRUCT(BlueprintType)
struct FLocalAudioStats
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int numChannels;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int sentSampleRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int sentBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int internalCodec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int64 txPacketLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats")
	int audioDeviceDelay;
};

USTRUCT(BlueprintType)
struct FRemoteAudioStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int quality;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int networkTransportDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int jitterBufferDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int audioLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int numChannels;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int receivedSampleRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int receivedBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int totalFrozenTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int frozenRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int mosValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int totalActiveTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int publishDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int qoeQuality;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats")
	int qualityChangedReason;
};

UENUM(BlueprintType)
enum class EAUDIO_AINS_MODE : uint8 {
	AINS_MODE_BALANCED = 0,
	AINS_MODE_AGGRESSIVE = 1,
	AINS_MODE_ULTRALOWLATENCY = 2
};

UENUM(BlueprintType)
enum class EQUALITY_ADAPT_INDICATION : uint8 {

	ADAPT_NONE = 0,

	ADAPT_UP_BANDWIDTH = 1,

	ADAPT_DOWN_BANDWIDTH = 2,
};
//UENUM(BlueprintType)
//enum ECAPTURE_BRIGHTNESS_LEVEL_TYPE {
//
//	CAPTURE_BRIGHTNESS_LEVEL_INVALID = -1,
//
//	CAPTURE_BRIGHTNESS_LEVEL_NORMAL = 0,
//
//	CAPTURE_BRIGHTNESS_LEVEL_BRIGHT = 1,
//
//	CAPTURE_BRIGHTNESS_LEVEL_DARK = 2,
//};

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
		EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE ValueWrapper;

    // default 
    FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE():ValueWrapper(EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID){}

    FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE(EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE InValue) {
        ValueWrapper = InValue;
    }
	FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE(agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE Val){
		switch(Val){
		case  agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID:
			ValueWrapper = EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;
			break;
		case  agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_NORMAL:
			ValueWrapper = EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_NORMAL;
			break;
		case  agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_BRIGHT:
			ValueWrapper = EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_BRIGHT;
			break;
		case  agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_DARK:
			ValueWrapper = EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_DARK;
			break;
		}
	}
    agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE GetRawValue() const {
        switch (ValueWrapper) 
        {
        case EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID:
            return  agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;
        case EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_NORMAL :
            return agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_NORMAL;
        case EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_BRIGHT :
            return agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_BRIGHT;
        case EENUMCUSTOM_CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_DARK :
            return agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_DARK;
        default:
			return  agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE::CAPTURE_BRIGHTNESS_LEVEL_INVALID;
		}
    }    
};

USTRUCT(BlueprintType)
struct FLocalVideoStats
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int sentBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int sentFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int captureFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int captureFrameWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int captureFrameHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int regulatedCaptureFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int regulatedCaptureFrameWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int regulatedCaptureFrameHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encoderOutputFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int rendererOutputFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int targetBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int targetFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	EQUALITY_ADAPT_INDICATION qualityAdaptIndication;
	int encodedBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int encodedFrameCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	EVIDEO_CODEC_TYPE codecType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int64 txPacketLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	FENUMWRAP_CAPTURE_BRIGHTNESS_LEVEL_TYPE  captureBrightnessLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	bool dualStreamEnabled;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int hwEncoderAccelerating;
};


//UENUM(BlueprintType)
//enum EAUDIO_MIXING_STATE_TYPE {
//
//	AUDIO_MIXING_STATE_NULL = 0,
//
//	AUDIO_MIXING_STATE_PLAYING = 710,
//
//	AUDIO_MIXING_STATE_PAUSED = 711,
//
//	AUDIO_MIXING_STATE_STOPPED = 713,
//
//	AUDIO_MIXING_STATE_FAILED = 714,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE: uint8{

	AUDIO_MIXING_STATE_NULL = 0,

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
		EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE ValueWrapper;

    // default 
    FENUMWRAP_AUDIO_MIXING_STATE_TYPE():ValueWrapper(EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED){}

    FENUMWRAP_AUDIO_MIXING_STATE_TYPE(EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE Val):ValueWrapper(Val){}
	FENUMWRAP_AUDIO_MIXING_STATE_TYPE(agora::rtc::AUDIO_MIXING_STATE_TYPE Val){
		switch(Val){
		case agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PLAYING:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PLAYING;
			break;
		case agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PAUSED:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PAUSED;
			break;
		case agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_STOPPED:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_STOPPED;
			break;
		case agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED;
			break;
		default:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED;
			break;
		}
	}
    void operator = (EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::AUDIO_MIXING_STATE_TYPE GetRawValue() const {
        switch (ValueWrapper)  
        {  
        case EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PLAYING:
			return   agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PLAYING;
		case EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PAUSED:
			return   agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_PAUSED;
		case EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_STOPPED:
			return   agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_STOPPED;
        case EENUMCUSTOM_AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED:
			return   agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED;
		default:
			return agora::rtc::AUDIO_MIXING_STATE_TYPE::AUDIO_MIXING_STATE_FAILED;
        }  
    }    
};
//
//UENUM(BlueprintType)
//enum EAUDIO_MIXING_REASON_TYPE {
//
//	AUDIO_MIXING_REASON_OK = 0,
//
//	AUDIO_MIXING_REASON_CAN_NOT_OPEN = 701,
//
//	AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 702,
//
//	AUDIO_MIXING_REASON_INTERRUPTED_EOF = 703,
//
//	AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 721,
//
//	AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 723,
//
//	AUDIO_MIXING_REASON_STOPPED_BY_USER = 724,
//
//};

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
		EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE ValueWrapper;

    // default
    FENUMWRAP_AUDIO_MIXING_REASON_TYPE():ValueWrapper(EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK){}

    FENUMWRAP_AUDIO_MIXING_REASON_TYPE(EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE Val):ValueWrapper(Val){}
	FENUMWRAP_AUDIO_MIXING_REASON_TYPE(agora::rtc::AUDIO_MIXING_REASON_TYPE Val){
		switch (Val)
		{
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK;
			break;
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_CAN_NOT_OPEN:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_CAN_NOT_OPEN;
			break;
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_TOO_FREQUENT_CALL:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_TOO_FREQUENT_CALL;
			break;
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_INTERRUPTED_EOF:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_INTERRUPTED_EOF;
			break;
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED;
			break;
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED;
			break;
		case agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_STOPPED_BY_USER:
			ValueWrapper = EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_STOPPED_BY_USER;
			break;
		}
	}
    void operator = (EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::AUDIO_MIXING_REASON_TYPE GetRawValue() const {
        switch (ValueWrapper)
        {   
        case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK:
            return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK;
        case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_CAN_NOT_OPEN:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_CAN_NOT_OPEN;
		case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_TOO_FREQUENT_CALL:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_TOO_FREQUENT_CALL;
		case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_INTERRUPTED_EOF:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_INTERRUPTED_EOF;
		case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED;
		case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED;
		case EENUMCUSTOM_AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_STOPPED_BY_USER:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_STOPPED_BY_USER;
        default:
			return agora::rtc::AUDIO_MIXING_REASON_TYPE::AUDIO_MIXING_REASON_OK;
		}  
    }    
};



//UENUM(BlueprintType)
//enum ERHYTHM_PLAYER_STATE_TYPE {
//
//	RHYTHM_PLAYER_NULL = 0,
//
//	RHYTHM_PLAYER_STATE_IDLE = 810,
//
//	RHYTHM_PLAYER_STATE_OPENING,
//
//	RHYTHM_PLAYER_STATE_DECODING,
//
//	RHYTHM_PLAYER_STATE_PLAYING,
//
//	RHYTHM_PLAYER_STATE_FAILED,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE : uint8 {

	RHYTHM_PLAYER_NULL = 0,

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
		EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE ValueWrapper;

    // default
    FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE():ValueWrapper(EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED){}

    FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE(EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE Val):ValueWrapper(Val){}
    
	FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE(agora::rtc::RHYTHM_PLAYER_STATE_TYPE Val){
		switch (Val)
		{
		case agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_IDLE:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_IDLE;
			break;
		case agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_OPENING:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_OPENING;
			break;
		case agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_DECODING:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_DECODING;
			break;
		case agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_PLAYING:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_PLAYING;
			break;
		case agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED;
			break;
		default:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED;
			break;
		}
	}
	void operator = (EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::RHYTHM_PLAYER_STATE_TYPE GetRawValue() const {
        switch (ValueWrapper) 
        {     
        case EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_IDLE:
            return agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_IDLE;
		case EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_OPENING:
			return agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_OPENING;
		case EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_DECODING:
			return agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_DECODING;
		case EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_PLAYING:
			return agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_PLAYING;
		case EENUMCUSTOM_RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED:
			return agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED;
		default:
			return agora::rtc::RHYTHM_PLAYER_STATE_TYPE::RHYTHM_PLAYER_STATE_FAILED;
        }
    }
};

//UENUM(BlueprintType)
//enum ERHYTHM_PLAYER_ERROR_TYPE {
//
//	RHYTHM_PLAYER_ERROR_OK = 0,
//
//	RHYTHM_PLAYER_ERROR_FAILED = 1,
//
//	RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN = 801,
//
//	RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY,
//
//	RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT,
//};


UENUM(BlueprintType)
enum class EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE :uint8 {

	RHYTHM_PLAYER_ERROR_OK = 0,

	RHYTHM_PLAYER_ERROR_FAILED = 1,

	RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN,

	RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY,

	RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_RHYTHM_PLAYER_ERROR_TYPE
{
    GENERATED_BODY()

public:
   // require to call [GetRawValue] method to get the raw value
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_RHYTHM_PLAYER_ERROR_TYPE")
		EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE ValueWrapper;

    // default 
    FENUMWRAP_RHYTHM_PLAYER_ERROR_TYPE():ValueWrapper(EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_OK){}

    FENUMWRAP_RHYTHM_PLAYER_ERROR_TYPE(EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE Val):ValueWrapper(Val){}

	FENUMWRAP_RHYTHM_PLAYER_ERROR_TYPE(agora::rtc::RHYTHM_PLAYER_ERROR_TYPE Val){
		switch (Val)
		{
		case agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_OK:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_OK;
			break;
		case agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FAILED:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FAILED;
			break;
		case agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN;
			break;
		case agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY;
			break;
		case agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT:
			ValueWrapper = EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT;
			break;
		}
	}

    void operator = (EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::RHYTHM_PLAYER_ERROR_TYPE GetRawValue() const {
        switch (ValueWrapper) 
        {
        case EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_OK:
            return agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_OK;
		case EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FAILED:
			return agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FAILED;
		case EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN:
			return agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN;
		case EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY:
			return agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY;
		case EENUMCUSTOM_RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT:
			return agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT;
        default:
			return agora::rtc::RHYTHM_PLAYER_ERROR_TYPE::RHYTHM_PLAYER_ERROR_OK;
		}
    }
};

UENUM(BlueprintType)
enum class ELOCAL_AUDIO_STREAM_STATE : uint8 {

	LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,

	LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,

	LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,

	LOCAL_AUDIO_STREAM_STATE_FAILED = 3
};

UENUM(BlueprintType)
enum class ELOCAL_AUDIO_STREAM_ERROR : uint8 {

	LOCAL_AUDIO_STREAM_ERROR_OK = 0,
	LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1,
	LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
	LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3,
	LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4,
	LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5,
	LOCAL_AUDIO_STREAM_ERROR_NO_RECORDING_DEVICE = 6,
	LOCAL_AUDIO_STREAM_ERROR_NO_PLAYOUT_DEVICE = 7,
	LOCAL_AUDIO_STREAM_ERROR_INTERRUPTED = 8,
	LOCAL_AUDIO_STREAM_ERROR_RECORD_INVALID_ID = 9,
	LOCAL_AUDIO_STREAM_ERROR_PLAYOUT_INVALID_ID = 10,
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
};
UENUM(BlueprintType)
enum class ECONTENT_INSPECT_RESULT : uint8 {
	CONTENT_INSPECT_NULL = 0,
	CONTENT_INSPECT_NEUTRAL = 1,
	CONTENT_INSPECT_SEXY = 2,
	CONTENT_INSPECT_PORN = 3,
};

UENUM(BlueprintType)
enum class ECLIENT_ROLE_CHANGE_FAILED_REASON : uint8 {

	CLIENT_ROLE_CHANGE_FAILED_TOO_MANY_NULL = 0,

	CLIENT_ROLE_CHANGE_FAILED_TOO_MANY_BROADCASTERS = 1,

	CLIENT_ROLE_CHANGE_FAILED_NOT_AUTHORIZED = 2,

	CLIENT_ROLE_CHANGE_FAILED_REQUEST_TIME_OUT = 3,

	CLIENT_ROLE_CHANGE_FAILED_CONNECTION_FAILED = 4,
};



//UENUM(BlueprintType)
//enum EMEDIA_DEVICE_TYPE {
//
//	UNKNOWN_AUDIO_DEVICE = -1,
//
//	AUDIO_PLAYOUT_DEVICE = 0,
//
//	AUDIO_RECORDING_DEVICE = 1,
//
//	VIDEO_RENDER_DEVICE = 2,
//
//	VIDEO_CAPTURE_DEVICE = 3,
//
//	AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
//
//	AUDIO_VIRTUAL_PLAYOUT_DEVICE = 5,
//
//	AUDIO_VIRTUAL_RECORDING_DEVICE = 6,
//};


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
		EENUMCUSTOM_MEDIA_DEVICE_TYPE ValueWrapper;

    // default 
    FENUMWRAP_MEDIA_DEVICE_TYPE():ValueWrapper(EENUMCUSTOM_MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE){}

    FENUMWRAP_MEDIA_DEVICE_TYPE(EENUMCUSTOM_MEDIA_DEVICE_TYPE Val):ValueWrapper(Val){}
	FENUMWRAP_MEDIA_DEVICE_TYPE(agora::rtc::MEDIA_DEVICE_TYPE  Val){
		switch (Val)
		{
		case agora::rtc::MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_PLAYOUT_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_PLAYOUT_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_RECORDING_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_RECORDING_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::VIDEO_RENDER_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::VIDEO_RENDER_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::VIDEO_CAPTURE_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::VIDEO_CAPTURE_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_APPLICATION_PLAYOUT_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_APPLICATION_PLAYOUT_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_PLAYOUT_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_PLAYOUT_DEVICE;
			break;
		case agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_RECORDING_DEVICE:
			ValueWrapper = EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_RECORDING_DEVICE;
			break;
		}
	
	}
    void operator = (EENUMCUSTOM_MEDIA_DEVICE_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::MEDIA_DEVICE_TYPE GetRawValue() const {
        switch (ValueWrapper) 
        {
        case EENUMCUSTOM_MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE:
            return agora::rtc::MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_PLAYOUT_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_PLAYOUT_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_RECORDING_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_RECORDING_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::VIDEO_RENDER_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::VIDEO_RENDER_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::VIDEO_CAPTURE_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::VIDEO_CAPTURE_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_APPLICATION_PLAYOUT_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_APPLICATION_PLAYOUT_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_PLAYOUT_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_PLAYOUT_DEVICE;
		case EENUMCUSTOM_MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_RECORDING_DEVICE:
			return agora::rtc::MEDIA_DEVICE_TYPE::AUDIO_VIRTUAL_RECORDING_DEVICE;
        default:
			return agora::rtc::MEDIA_DEVICE_TYPE::UNKNOWN_AUDIO_DEVICE;
		}
    }
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
enum class ERTMP_STREAM_PUBLISH_ERROR_TYPE : uint8 {

	RTMP_STREAM_PUBLISH_ERROR_OK = 0,

	RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = 1,

	RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = 2,

	RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = 3,

	RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = 4,

	RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = 5,

	RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = 6,

	RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = 7,

	RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = 8,

	RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = 9,

	RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = 10,

	RTMP_STREAM_PUBLISH_ERROR_NOT_BROADCASTER = 11,

	RTMP_STREAM_PUBLISH_ERROR_TRANSCODING_NO_MIX_STREAM = 13,

	RTMP_STREAM_PUBLISH_ERROR_NET_DOWN = 14,

	RTMP_STREAM_PUBLISH_ERROR_INVALID_APPID = 15,

	RTMP_STREAM_PUBLISH_ERROR_INVALID_PRIVILEGE = 16,

	RTMP_STREAM_UNPUBLISH_ERROR_OK = 100,
};

UENUM(BlueprintType)
enum class ERTMP_STREAMING_EVENT : uint8 {

	RTMP_STREAMING_EVENT_FAILED_LOAD_NULL = 0,

	RTMP_STREAMING_EVENT_FAILED_LOAD_IMAGE = 1,

	RTMP_STREAMING_EVENT_URL_ALREADY_IN_USE = 2,

	RTMP_STREAMING_EVENT_ADVANCED_FEATURE_NOT_SUPPORT = 3,

	RTMP_STREAMING_EVENT_REQUEST_TOO_OFTEN = 4,
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
};


//UENUM(BlueprintType)
//enum HEADPHONE_EQUALIZER_PRESET {
//
//	HEADPHONE_EQUALIZER_OFF = 0x00000000,
//
//	HEADPHONE_EQUALIZER_OVEREAR = 0x04000001,
//
//	HEADPHONE_EQUALIZER_INEAR = 0x04000002
//};

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
		EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET ValueWrapper;

    // default 
    FENUMWRAP_HEADPHONE_EQUALIZER_PRESET():ValueWrapper(EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OFF){}

    FENUMWRAP_HEADPHONE_EQUALIZER_PRESET(EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::HEADPHONE_EQUALIZER_PRESET GetRawValue() const {
        switch (ValueWrapper)  
        {
        case EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OFF:
            return agora::rtc::HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OFF;
		case EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OVEREAR:
			return agora::rtc::HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OVEREAR;
		case EENUMCUSTOM_HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_INEAR:
			return agora::rtc::HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_INEAR;
        default:
			return agora::rtc::HEADPHONE_EQUALIZER_PRESET::HEADPHONE_EQUALIZER_OFF;
		}
    }
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

//UENUM(BlueprintType)
//enum ENETWORK_TYPE {
//
//	NETWORK_TYPE_UNKNOWN = -1,
//
//	NETWORK_TYPE_DISCONNECTED = 0,
//
//	NETWORK_TYPE_LAN = 1,
//
//	NETWORK_TYPE_WIFI = 2,
//
//	NETWORK_TYPE_MOBILE_2G = 3,
//
//	NETWORK_TYPE_MOBILE_3G = 4,
//
//	NETWORK_TYPE_MOBILE_4G = 5,
//};


UENUM(BlueprintType)
enum class EENUMCUSTOM_NETWORK_TYPE : uint8 {

	NETWORK_TYPE_UNKNOWN = 0,

	NETWORK_TYPE_DISCONNECTED = 1,

	NETWORK_TYPE_LAN = 2,

	NETWORK_TYPE_WIFI = 3,

	NETWORK_TYPE_MOBILE_2G = 4,

	NETWORK_TYPE_MOBILE_3G = 5,

	NETWORK_TYPE_MOBILE_4G = 6,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_NETWORK_TYPE 
{
    GENERATED_BODY()

public:
    // require to call [GetRawValue] method to get the raw value
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_NETWORK_TYPE")
		EENUMCUSTOM_NETWORK_TYPE ValueWrapper;

    // default
    FENUMWRAP_NETWORK_TYPE():ValueWrapper(EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_UNKNOWN){}

    FENUMWRAP_NETWORK_TYPE(EENUMCUSTOM_NETWORK_TYPE Val):ValueWrapper(Val){}

	FENUMWRAP_NETWORK_TYPE(agora::rtc::NETWORK_TYPE Val) {
		switch (Val)
		{
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_UNKNOWN:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_UNKNOWN;
			break;
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_DISCONNECTED:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_DISCONNECTED;
			break;
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_LAN:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_LAN;
			break;
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_WIFI:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_WIFI;
			break;
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_MOBILE_2G:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_MOBILE_2G;
			break;
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_MOBILE_3G:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_MOBILE_3G;
			break;
		case agora::rtc::NETWORK_TYPE::NETWORK_TYPE_MOBILE_4G:
			ValueWrapper = EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_MOBILE_4G;
			break;
		}
	}
    void operator = (EENUMCUSTOM_NETWORK_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::NETWORK_TYPE GetRawValue() const {
        switch (ValueWrapper)  
        {
        case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_UNKNOWN:
            return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_UNKNOWN;
		case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_DISCONNECTED:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_DISCONNECTED;
		case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_LAN:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_LAN;
		case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_WIFI:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_WIFI;
		case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_MOBILE_2G:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_MOBILE_2G;
		case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_MOBILE_3G:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_MOBILE_3G;
		case EENUMCUSTOM_NETWORK_TYPE::NETWORK_TYPE_MOBILE_4G:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_MOBILE_4G;
		default:
			return  agora::rtc::NETWORK_TYPE::NETWORK_TYPE_UNKNOWN;
        }
    }
};

UENUM(BlueprintType)
enum class EENCRYPTION_ERROR_TYPE : uint8 {
	ENCRYPTION_ERROR_INTERNAL_FAILURE = 0,
	ENCRYPTION_ERROR_DECRYPTION_FAILURE = 1,
	ENCRYPTION_ERROR_ENCRYPTION_FAILURE = 2,
};

UENUM(BlueprintType)
enum class EPERMISSION_TYPE : uint8 {
	RECORD_AUDIO = 0,
	CAMERA = 1,
	SCREEN_CAPTURE = 2,
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


USTRUCT(BlueprintType)
struct FRemoteVideoStats {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int delay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int e2eDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int height;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int receivedBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int decoderOutputFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int rendererOutputFrameRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int frameLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int packetLossRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	EVIDEO_STREAM_TYPE rxStreamType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int totalFrozenTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int frozenRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int avSyncTimeMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int totalActiveTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int publishDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int mosValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int64 rxVideoBytes;
};

USTRUCT(BlueprintType)
struct FWlAccStats {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 e2eDelayPercent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 frozenRatioPercent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WlAccStats")
	int64 lossRatePercent;
};
USTRUCT(BlueprintType)
struct FAgoraMetadata
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	int64 uid;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	int64 size;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	TArray<int64> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AgoraMetadata")
	int64 timeStampMs;
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
enum class EDIRECT_CDN_STREAMING_ERROR : uint8 {

	DIRECT_CDN_STREAMING_ERROR_OK = 0,

	DIRECT_CDN_STREAMING_ERROR_FAILED = 1,

	DIRECT_CDN_STREAMING_ERROR_AUDIO_PUBLICATION = 2,

	DIRECT_CDN_STREAMING_ERROR_VIDEO_PUBLICATION = 3,

	DIRECT_CDN_STREAMING_ERROR_NET_CONNECT = 4,

	DIRECT_CDN_STREAMING_ERROR_BAD_NAME = 5,
};

USTRUCT(BlueprintType)
struct FDirectCdnStreamingStats {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int videoWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int videoHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int fps;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int videoBitrate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingStats")
	int audioBitrate;
};

//UENUM(BlueprintType)
//enum EMETADATA_TYPE
//{
//	UNKNOWN_METADATA = -1,
//
//	VIDEO_METADATA = 0,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_METADATA_TYPE : uint8
{
	UNKNOWN_METADATA = 0,

	VIDEO_METADATA = 1,
};

USTRUCT(BlueprintType)
struct FENUMWRAP_METADATA_TYPE 
{
    GENERATED_BODY()  

public:
    // require to call [GetRawValue] method to get the raw value
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_METADATA_TYPE")
    EENUMCUSTOM_METADATA_TYPE ValueWrapper;

    // default 
	FENUMWRAP_METADATA_TYPE():ValueWrapper(EENUMCUSTOM_METADATA_TYPE::UNKNOWN_METADATA){}

	FENUMWRAP_METADATA_TYPE(EENUMCUSTOM_METADATA_TYPE Val):ValueWrapper(Val){}
    void operator = (EENUMCUSTOM_METADATA_TYPE InValue) {
        ValueWrapper = InValue;
    }

    agora::rtc::IMetadataObserver::METADATA_TYPE GetRawValue() const {
        switch (ValueWrapper) 
        {
        case EENUMCUSTOM_METADATA_TYPE::UNKNOWN_METADATA:        
            return   agora::rtc::IMetadataObserver::METADATA_TYPE::UNKNOWN_METADATA;
        case EENUMCUSTOM_METADATA_TYPE::VIDEO_METADATA:      
            return   agora::rtc::IMetadataObserver::METADATA_TYPE::VIDEO_METADATA;
        default:
			return   agora::rtc::IMetadataObserver::METADATA_TYPE::UNKNOWN_METADATA;
		}
    }
};


UENUM(BlueprintType)
enum class ESTREAMING_SRC_STATE : uint8 {
	STREAMING_SRC_STATE_CLOSED = 0,
	STREAMING_SRC_STATE_OPENING = 1,
	STREAMING_SRC_STATE_IDLE = 2,
	STREAMING_SRC_STATE_PLAYING = 3,
	STREAMING_SRC_STATE_SEEKING = 4,
	STREAMING_SRC_STATE_EOF = 5,
	STREAMING_SRC_STATE_ERROR = 6,
};

UENUM(BlueprintType)
enum class ESTREAMING_SRC_ERR : uint8 {
	STREAMING_SRC_ERR_NONE = 0,
	STREAMING_SRC_ERR_UNKNOWN = 1,
	STREAMING_SRC_ERR_INVALID_PARAM = 2,
	STREAMING_SRC_ERR_BAD_STATE = 3,
	STREAMING_SRC_ERR_NO_MEM = 4,
	STREAMING_SRC_ERR_BUFFER_OVERFLOW = 5,
	STREAMING_SRC_ERR_BUFFER_UNDERFLOW = 6,
	STREAMING_SRC_ERR_NOT_FOUND = 7,
	STREAMING_SRC_ERR_TIMEOUT = 8,
	STREAMING_SRC_ERR_EXPIRED = 9,
	STREAMING_SRC_ERR_UNSUPPORTED = 10,
	STREAMING_SRC_ERR_NOT_EXIST = 11,
	STREAMING_SRC_ERR_EXIST = 12,
	STREAMING_SRC_ERR_OPEN = 13,
	STREAMING_SRC_ERR_CLOSE = 14,
	STREAMING_SRC_ERR_READ = 15,
	STREAMING_SRC_ERR_WRITE = 16,
	STREAMING_SRC_ERR_SEEK = 17,
	STREAMING_SRC_ERR_EOF = 18,
	STREAMING_SRC_ERR_CODECOPEN = 19,
	STREAMING_SRC_ERR_CODECCLOSE = 20,
	STREAMING_SRC_ERR_CODECPROC = 21,
};


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
USTRUCT(BlueprintType)
struct FThumbImageBuffer {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	TArray<int64> buffer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 length;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 height;
};


//UENUM(BlueprintType)
//enum EScreenCaptureSourceType {
//	ScreenCaptureSourceType_Unknown = -1,
//	ScreenCaptureSourceType_Window = 0,
//	ScreenCaptureSourceType_Screen = 1,
//	ScreenCaptureSourceType_Custom = 2,
//};

UENUM(BlueprintType)
enum class EENUMCUSTOM_ScreenCaptureSourceType: uint8 {
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
    EENUMCUSTOM_ScreenCaptureSourceType ValueWrapper;

    // default 
	FENUMWRAP_ScreenCaptureSourceType():ValueWrapper(EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown){}

	FENUMWRAP_ScreenCaptureSourceType(EENUMCUSTOM_ScreenCaptureSourceType Val):ValueWrapper(Val){}

	void operator = (EENUMCUSTOM_ScreenCaptureSourceType InValue) {
		ValueWrapper = InValue;
	}

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

	FENUMWRAP_ScreenCaptureSourceType(agora::rtc::ScreenCaptureSourceType Val) {
		switch (Val)
		{
		case agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown:
			ValueWrapper = EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown;
			break;
		case agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Window:
			ValueWrapper = EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Window;
			break;
		case agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Screen:
			ValueWrapper = EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Screen;
			break;
		case agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Custom:
			ValueWrapper = EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Custom;
			break;
		default:
			ValueWrapper = EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown;
		}
	}

	agora::rtc::ScreenCaptureSourceType GetRawValue() const {
		switch (ValueWrapper)
		{
		case EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown:
			return agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown;
		case EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Window:
			return agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Window;
		case EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Screen:
			return agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Screen;
		case EENUMCUSTOM_ScreenCaptureSourceType::ScreenCaptureSourceType_Custom:
			return agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Custom;
		default:
			return agora::rtc::ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown;
		}
	}

#endif
};

USTRUCT(BlueprintType)
struct FScreenCaptureSourceInfo {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FENUMWRAP_ScreenCaptureSourceType type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	int64 sourceId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FString sourceName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FThumbImageBuffer thumbImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FThumbImageBuffer iconImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FString processPath;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	FString sourceTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	bool primaryMonitor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FScreenCaptureSourceInfo")
	bool isOccluded;
};


USTRUCT(BlueprintType)
struct FSIZE {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SIZE")
	int width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SIZE")
	int height;
};

USTRUCT(BlueprintType)
struct FRecorderInfo {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RecorderInfo")
	FString fileName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RecorderInfo")
	int64 durationMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RecorderInfo")
	int64 fileSize;
};

//UENUM(BlueprintType)
//enum ERecorderState {
//
//	RECORDER_STATE_NULL = 0,
//
//	RECORDER_STATE_ERROR = -1,
//
//	RECORDER_STATE_START = 2,
//
//	RECORDER_STATE_STOP = 3,
//};


UENUM(BlueprintType)
enum class EENUMCUSTOM_RecorderState : uint8 {

	RECORDER_STATE_NULL = 0,

	RECORDER_STATE_ERROR = 1,

	RECORDER_STATE_START = 2,

	RECORDER_STATE_STOP = 3,
};

USTRUCT(BlueprintType) 
struct FENUMWRAP_RecorderState  
{
    GENERATED_BODY()  

public:
    // require to call [GetRawValue] method to get the raw value   
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FENUMWRAP_RecorderState")
    EENUMCUSTOM_RecorderState ValueWrapper;

    // default  
	FENUMWRAP_RecorderState():ValueWrapper(EENUMCUSTOM_RecorderState::RECORDER_STATE_ERROR){}

	FENUMWRAP_RecorderState(EENUMCUSTOM_RecorderState Val):ValueWrapper(Val){}

	FENUMWRAP_RecorderState(agora::media::RecorderState Val) {
		switch (Val)
		{
		case agora::media::RecorderState::RECORDER_STATE_ERROR:
			ValueWrapper = EENUMCUSTOM_RecorderState::RECORDER_STATE_ERROR;
			break;
		case agora::media::RecorderState::RECORDER_STATE_START:
			ValueWrapper = EENUMCUSTOM_RecorderState::RECORDER_STATE_START;
			break;
		case agora::media::RecorderState::RECORDER_STATE_STOP:
			ValueWrapper = EENUMCUSTOM_RecorderState::RECORDER_STATE_STOP;
			break;
		default:
			ValueWrapper = EENUMCUSTOM_RecorderState::RECORDER_STATE_ERROR;
		}
	}
    void operator = (EENUMCUSTOM_RecorderState InValue) {
        ValueWrapper = InValue;
    }

    agora::media::RecorderState GetRawValue() const {
        switch (ValueWrapper)  
        {
        case EENUMCUSTOM_RecorderState::RECORDER_STATE_ERROR:      
            return agora::media::RecorderState::RECORDER_STATE_ERROR;
        case EENUMCUSTOM_RecorderState::RECORDER_STATE_START:       
			return agora::media::RecorderState::RECORDER_STATE_START;
        case EENUMCUSTOM_RecorderState::RECORDER_STATE_STOP:       
			return agora::media::RecorderState::RECORDER_STATE_STOP;
		default:
			return agora::media::RecorderState::RECORDER_STATE_ERROR;
        }
    } 
};



UENUM(BlueprintType)
enum class ERecorderErrorCode : uint8 {

	RECORDER_ERROR_NONE = 0,

	RECORDER_ERROR_WRITE_FAILED = 1,

	RECORDER_ERROR_NO_STREAM = 2,

	RECORDER_ERROR_OVER_MAX_DURATION = 3,

	RECORDER_ERROR_CONFIG_CHANGED = 4,
};


USTRUCT(BlueprintType)
struct FSpatialAudioZone {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		int zoneSetId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		FVector position;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		FVector forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		FVector right;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		FVector up;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		float forwardLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		float rightLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		float upLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|FSpatialAudioZone")
		float audioAttenuation;
};
