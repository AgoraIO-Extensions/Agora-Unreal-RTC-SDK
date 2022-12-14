#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
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
	AGORA_IID_MEDIA_RECORDER = 12,
	AGORA_IID_STATE_SYNC = 13,
	AGORA_IID_METACHAT_SERVICE = 14,
	AGORA_IID_MUSIC_CONTENT_CENTER = 15,
};
UENUM(BlueprintType)
enum class ECOMPRESSION_PREFERENCE : uint8 {

	PREFER_LOW_LATENCY = 0,

	PREFER_QUALITY = 1,
};

UENUM(BlueprintType)
enum class EENCODING_PREFERENCE : uint8 {

	PREFER_AUTO = 0,

	PREFER_SOFTWARE = 1,

	PREFER_HARDWARE = 2,
};

USTRUCT(BlueprintType)
struct FAdvanceOptions {

	GENERATED_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvanceOptions")
		EENCODING_PREFERENCE encodingPreference = EENCODING_PREFERENCE::PREFER_AUTO;
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
enum EAUDIO_EFFECT_PRESET {
	AUDIO_EFFECT_OFF = 0x00000000,
	ROOM_ACOUSTICS_KTV = 0x02010100,
	ROOM_ACOUSTICS_VOCAL_CONCERT = 0x02010200,
	ROOM_ACOUSTICS_STUDIO = 0x02010300,
	ROOM_ACOUSTICS_PHONOGRAPH = 0x02010400,
	ROOM_ACOUSTICS_VIRTUAL_STEREO = 0x02010500,
	ROOM_ACOUSTICS_SPACIAL = 0x02010600,
	ROOM_ACOUSTICS_ETHEREAL = 0x02010700,
	ROOM_ACOUSTICS_3D_VOICE = 0x02010800,
	ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND = 0x02010900,
	VOICE_CHANGER_EFFECT_UNCLE = 0x02020100,
	VOICE_CHANGER_EFFECT_OLDMAN = 0x02020200,
	VOICE_CHANGER_EFFECT_BOY = 0x02020300,
	VOICE_CHANGER_EFFECT_SISTER = 0x02020400,
	VOICE_CHANGER_EFFECT_GIRL = 0x02020500,
	VOICE_CHANGER_EFFECT_PIGKING = 0x02020600,
	VOICE_CHANGER_EFFECT_HULK = 0x02020700,
	STYLE_TRANSFORMATION_RNB = 0x02030100,
	STYLE_TRANSFORMATION_POPULAR = 0x02030200,
	PITCH_CORRECTION = 0x02040100,
};

UENUM(BlueprintType)
enum EVOICE_CONVERSION_PRESET {
	VOICE_CONVERSION_OFF = 0x00000000,
	VOICE_CHANGER_NEUTRAL = 0x03010100,
	VOICE_CHANGER_SWEET = 0x03010200,
	VOICE_CHANGER_SOLID = 0x03010300,
	VOICE_CHANGER_BASS = 0x03010400,
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
};

UENUM(BlueprintType)
enum class EVIDEO_MIRROR_MODE_TYPE : uint8 {
	VIDEO_MIRROR_MODE_AUTO = 0,
	VIDEO_MIRROR_MODE_ENABLED = 1,
	VIDEO_MIRROR_MODE_DISABLED = 2,
};

UENUM(BlueprintType)
enum ESIMULCAST_STREAM_MODE {
	AUTO_SIMULCAST_STREAM = -1,
	DISABLE_SIMULCAST_STREM = 0,
	ENABLE_SIMULCAST_STREAM = 1,
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
enum EVIDEO_ORIENTATION {
	VIDEO_ORIENTATION_0 = 0,
	VIDEO_ORIENTATION_90 = 90,
	VIDEO_ORIENTATION_180 = 180,
	VIDEO_ORIENTATION_270 = 270,
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

UENUM(BlueprintType)
enum EAREA_CODE {

	AREA_CODE_NULL = 0,

	AREA_CODE_CN = 0x00000001,

	AREA_CODE_NA = 0x00000002,

	AREA_CODE_EU = 0x00000004,

	AREA_CODE_AS = 0x00000008,

	AREA_CODE_JP = 0x00000010,

	AREA_CODE_IN = 0x00000020,

	AREA_CODE_GLOB = (0xFFFFFFFF),
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	AGORAOPTIONAL threadPriorityValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	ETHREAD_PRIORITY_TYPE threadPriority;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	FLogConfig logConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcEngineContext")
	TEnumAsByte<EAREA_CODE> areaCode = EAREA_CODE::AREA_CODE_GLOB;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCustomAudioSourceId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCustomAudioTrackEnableAec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishDirectCustomAudioTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCustomAudioTrackAec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishCustomVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishEncodedVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishMediaPlayerAudioTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishMediaPlayerVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishTrancodedVideoTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL autoSubscribeAudio;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL autoSubscribeVideo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL enableAudioRecordingOrPlayout;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishMediaPlayerIdValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int publishMediaPlayerId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL clientRoleTypeValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	ECLIENT_ROLE_TYPE clientRoleType = ECLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL audienceLatencyLevelValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EAUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL defaultVideoStreamValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	EVIDEO_STREAM_TYPE defaultVideoStreamType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL channelProfileValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	ECHANNEL_PROFILE_TYPE channelProfile;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL audioDelayMsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int audioDelayMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL mediaPlayerAudioDelayMsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int mediaPlayerAudioDelayMs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL tokenValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	FString token;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL enableBuiltInMediaEncryption;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL publishRhythmPlayerTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL isInteractiveAudience;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL customVideoTrackIdValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	int64 customVideoTrackId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaOptions")
	AGORAOPTIONAL isAudioFilterable;
};

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
	int64 view;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	bool enableAudio = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	bool enableVideo = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	FString token;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|EchoTestConfiguration")
	FString channelId;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	AGORAOPTIONAL typeValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	EVIDEO_STREAM_TYPE type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoSubscriptionOptions")
	AGORAOPTIONAL encodedFrameOnly;
};
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
UENUM(BlueprintType)
enum EAUDIO_ENCODING_TYPE {
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


//UENUM(BlueprintType)
//enum EAUDIO_ENCODING_TYPE {
//	AUDIO_ENCODING_TYPE_NULL = 0x000000,
//
//	AUDIO_ENCODING_TYPE_AAC_16000_LOW = 0x010101,
//
//	AUDIO_ENCODING_TYPE_AAC_16000_MEDIUM = 0x010102,
//
//	AUDIO_ENCODING_TYPE_AAC_32000_LOW = 0x010201,
//
//	AUDIO_ENCODING_TYPE_AAC_32000_MEDIUM = 0x010202,
//
//	AUDIO_ENCODING_TYPE_AAC_32000_HIGH = 0x010203,
//
//	AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM = 0x010302,
//
//	AUDIO_ENCODING_TYPE_AAC_48000_HIGH = 0x010303,
//
//	AUDIO_ENCODING_TYPE_OPUS_16000_LOW = 0x020101,
//
//	AUDIO_ENCODING_TYPE_OPUS_16000_MEDIUM = 0x020102,
//
//	AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM = 0x020302,
//
//	AUDIO_ENCODING_TYPE_OPUS_48000_HIGH = 0x020303,
//};

USTRUCT(BlueprintType)
struct FAudioEncodedFrameObserverConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioEncodedFrameObserverConfig")
	EAUDIO_ENCODED_FRAME_OBSERVER_POSITION postionType = EAUDIO_ENCODED_FRAME_OBSERVER_POSITION::AUDIO_ENCODED_FRAME_OBSERVER_POSITION_PLAYBACK;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioEncodedFrameObserverConfig")
	TEnumAsByte<EAUDIO_ENCODING_TYPE> encodingType = EAUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM;
};

USTRUCT(BlueprintType)
struct FSpatialAudioParams
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL speaker_azimuthValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_azimuth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL speaker_elevationValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_elevation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL speaker_distanceValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_distance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL speaker_orientationValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	int speaker_orientation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL enable_blurValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_blur;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL enable_air_absorbValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_air_absorb;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL speaker_attenuationValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	float speaker_attenuation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	AGORAOPTIONAL enable_dopplerValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|SpatialAudioParams")
	bool enable_doppler;
};

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL publishMediaPlayerIdValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	int publishMediaPlayerId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	AGORAOPTIONAL customVideoTrackIdValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|DirectCdnStreamingMediaOptions")
	int64 customVideoTrackId;
};

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	AGORAOPTIONAL audioProcessingChannelsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AdvancedAudioOptions")
	int audioProcessingChannels;
};

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
enum class EQUALITY_ADAPT_INDICATION : uint8 {

	ADAPT_NONE = 0,

	ADAPT_UP_BANDWIDTH = 1,

	ADAPT_DOWN_BANDWIDTH = 2,
};
UENUM(BlueprintType)
enum ECAPTURE_BRIGHTNESS_LEVEL_TYPE {

	CAPTURE_BRIGHTNESS_LEVEL_INVALID = -1,

	CAPTURE_BRIGHTNESS_LEVEL_NORMAL = 0,

	CAPTURE_BRIGHTNESS_LEVEL_BRIGHT = 1,

	CAPTURE_BRIGHTNESS_LEVEL_DARK = 2,
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
	TEnumAsByte<ECAPTURE_BRIGHTNESS_LEVEL_TYPE>  captureBrightnessLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	bool dualStreamEnabled;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats")
	int hwEncoderAccelerating;
};


UENUM(BlueprintType)
enum EAUDIO_MIXING_STATE_TYPE {

	AUDIO_MIXING_STATE_NULL = 0,

	AUDIO_MIXING_STATE_PLAYING = 710,

	AUDIO_MIXING_STATE_PAUSED = 711,

	AUDIO_MIXING_STATE_STOPPED = 713,

	AUDIO_MIXING_STATE_FAILED = 714,
};

UENUM(BlueprintType)
enum EAUDIO_MIXING_REASON_TYPE {

	AUDIO_MIXING_REASON_NULL = 0,

	AUDIO_MIXING_REASON_CAN_NOT_OPEN = 701,

	AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 702,

	AUDIO_MIXING_REASON_INTERRUPTED_EOF = 703,

	AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 721,

	AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 723,

	AUDIO_MIXING_REASON_STOPPED_BY_USER = 724,

	AUDIO_MIXING_REASON_OK = 0,
};

UENUM(BlueprintType)
enum ERHYTHM_PLAYER_STATE_TYPE {

	RHYTHM_PLAYER_NULL = 0,

	RHYTHM_PLAYER_STATE_IDLE = 810,

	RHYTHM_PLAYER_STATE_OPENING,

	RHYTHM_PLAYER_STATE_DECODING,

	RHYTHM_PLAYER_STATE_PLAYING,

	RHYTHM_PLAYER_STATE_FAILED,
};

UENUM(BlueprintType)
enum ERHYTHM_PLAYER_ERROR_TYPE {

	RHYTHM_PLAYER_ERROR_OK = 0,

	RHYTHM_PLAYER_ERROR_FAILED = 1,

	RHYTHM_PLAYER_ERROR_CAN_NOT_OPEN = 801,

	RHYTHM_PLAYER_ERROR_CAN_NOT_PLAY,

	RHYTHM_PLAYER_ERROR_FILE_OVER_DURATION_LIMIT,
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
UENUM(BlueprintType)
enum EMEDIA_DEVICE_TYPE {

	UNKNOWN_AUDIO_DEVICE = -1,

	AUDIO_PLAYOUT_DEVICE = 0,

	AUDIO_RECORDING_DEVICE = 1,

	VIDEO_RENDER_DEVICE = 2,

	VIDEO_CAPTURE_DEVICE = 3,

	AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
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
UENUM(BlueprintType)
enum HEADPHONE_EQUALIZER_PRESET {

	HEADPHONE_EQUALIZER_OFF = 0x00000000,

	HEADPHONE_EQUALIZER_OVEREAR = 0x04000001,

	HEADPHONE_EQUALIZER_INEAR = 0x04000002
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

UENUM(BlueprintType)
enum ENETWORK_TYPE {

	NETWORK_TYPE_UNKNOWN = -1,

	NETWORK_TYPE_DISCONNECTED = 0,

	NETWORK_TYPE_LAN = 1,

	NETWORK_TYPE_WIFI = 2,

	NETWORK_TYPE_MOBILE_2G = 3,

	NETWORK_TYPE_MOBILE_3G = 4,

	NETWORK_TYPE_MOBILE_4G = 5,
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
};


USTRUCT(BlueprintType)
struct FRemoteVideoStats {

	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int64 uid;
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
	int superResolutionType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats")
	int mosValue;
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

UENUM(BlueprintType)
enum EMETADATA_TYPE
{
	UNKNOWN_METADATA = -1,

	VIDEO_METADATA = 0,
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

UENUM(BlueprintType)
enum EScreenCaptureSourceType {
	ScreenCaptureSourceType_Unknown = -1,
	ScreenCaptureSourceType_Window = 0,
	ScreenCaptureSourceType_Screen = 1,
	ScreenCaptureSourceType_Custom = 2,
};
USTRUCT(BlueprintType)
struct FScreenCaptureSourceInfo {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	TEnumAsByte<EScreenCaptureSourceType> type = EScreenCaptureSourceType::ScreenCaptureSourceType_Unknown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	int64 sourceId;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	FString sourceName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	FThumbImageBuffer thumbImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	FThumbImageBuffer iconImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	FString processPath;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	FString sourceTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
	bool primaryMonitor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ThumbImageBuffer")
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

UENUM(BlueprintType)
enum ERecorderState {

	RECORDER_STATE_NULL = 0,

	RECORDER_STATE_ERROR = -1,

	RECORDER_STATE_START = 2,

	RECORDER_STATE_STOP = 3,
};

UENUM(BlueprintType)
enum class ERecorderErrorCode : uint8 {

	RECORDER_ERROR_NONE = 0,

	RECORDER_ERROR_WRITE_FAILED = 1,

	RECORDER_ERROR_NO_STREAM = 2,

	RECORDER_ERROR_OVER_MAX_DURATION = 3,

	RECORDER_ERROR_CONFIG_CHANGED = 4,
};

