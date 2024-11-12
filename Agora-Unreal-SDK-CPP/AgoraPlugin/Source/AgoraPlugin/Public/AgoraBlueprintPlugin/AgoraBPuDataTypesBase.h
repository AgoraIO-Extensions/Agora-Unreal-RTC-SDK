// Copyright(c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "AgoraHeaderBase.h"
#include "UtilityAgoraBPuLogger.h"
#include "UtilityUABTEnumConvertMacro.h"
#include "AgoraBPuDataTypesBase.generated.h"


#pragma region Enum - IMediaPlayerSourceObserver

/**
 * @brief Player error code
 *
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_PLAYER_REASON : uint8 {
	/** No error.
	 */
	PLAYER_REASON_NONE = 0,
	/** The parameter is invalid.
	 */
	PLAYER_REASON_INVALID_ARGUMENTS,
	/** Internel error.
	 */
	PLAYER_REASON_INTERNAL,
	/** No resource.
	 */
	PLAYER_REASON_NO_RESOURCE,
	/** Invalid media source.
	 */
	PLAYER_REASON_INVALID_MEDIA_SOURCE,
	/** The type of the media stream is unknown.
	 */
	PLAYER_REASON_UNKNOWN_STREAM_TYPE,
	/** The object is not initialized.
	 */
	PLAYER_REASON_OBJ_NOT_INITIALIZED,
	/** The codec is not supported.
	 */
	PLAYER_REASON_CODEC_NOT_SUPPORTED,
	/** Invalid renderer.
	 */
	PLAYER_REASON_VIDEO_RENDER_FAILED,
	/** An error occurs in the internal state of the player.
	 */
	PLAYER_REASON_INVALID_STATE,
	/** The URL of the media file cannot be found.
	 */
	PLAYER_REASON_URL_NOT_FOUND,
	/** Invalid connection between the player and the Agora server.
	 */
	PLAYER_REASON_INVALID_CONNECTION_STATE,
	/** The playback buffer is insufficient.
	 */
	PLAYER_REASON_SRC_BUFFER_UNDERFLOW,
	/** The audio mixing file playback is interrupted.
	 */
	PLAYER_REASON_INTERRUPTED,
	/** The SDK does not support this function.
	 */
	PLAYER_REASON_NOT_SUPPORTED,
	/** The token has expired.
	 */
	PLAYER_REASON_TOKEN_EXPIRED,
	/** The ip has expired.
	 */
	PLAYER_REASON_IP_EXPIRED,
	/** An unknown error occurs.
	 */
	PLAYER_REASON_UNKNOWN,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_18_ENTRIES(EUABT_MEDIA_PLAYER_REASON, agora::media::base::MEDIA_PLAYER_REASON,
	PLAYER_REASON_NONE,
	PLAYER_REASON_INVALID_ARGUMENTS,
	PLAYER_REASON_INTERNAL,
	PLAYER_REASON_NO_RESOURCE,
	PLAYER_REASON_INVALID_MEDIA_SOURCE,
	PLAYER_REASON_UNKNOWN_STREAM_TYPE,
	PLAYER_REASON_OBJ_NOT_INITIALIZED,
	PLAYER_REASON_CODEC_NOT_SUPPORTED,
	PLAYER_REASON_VIDEO_RENDER_FAILED,
	PLAYER_REASON_INVALID_STATE,
	PLAYER_REASON_URL_NOT_FOUND,
	PLAYER_REASON_INVALID_CONNECTION_STATE,
	PLAYER_REASON_SRC_BUFFER_UNDERFLOW,
	PLAYER_REASON_INTERRUPTED,
	PLAYER_REASON_NOT_SUPPORTED,
	PLAYER_REASON_TOKEN_EXPIRED,
	PLAYER_REASON_IP_EXPIRED,
	PLAYER_REASON_UNKNOWN
)


/**
 * @brief The playback event.
 *
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_PLAYER_EVENT : uint8 {
	/** The player begins to seek to the new playback position.
	 */
	PLAYER_EVENT_SEEK_BEGIN = 0,
	/** The seek operation completes.
	 */
	PLAYER_EVENT_SEEK_COMPLETE = 1,
	/** An error occurs during the seek operation.
	 */
	PLAYER_EVENT_SEEK_ERROR = 2,
	/** The player changes the audio track for playback.
	 */
	PLAYER_EVENT_AUDIO_TRACK_CHANGED = 5,
	/** player buffer low
	 */
	PLAYER_EVENT_BUFFER_LOW = 6,
	/** player buffer recover
   */
	PLAYER_EVENT_BUFFER_RECOVER = 7,
	/** The video or audio is interrupted
	 */
	PLAYER_EVENT_FREEZE_START = 8,
	/** Interrupt at the end of the video or audio
	 */
	PLAYER_EVENT_FREEZE_STOP = 9,
	/** switch source begin
	*/
	PLAYER_EVENT_SWITCH_BEGIN = 10,
	/** switch source complete
	*/
	PLAYER_EVENT_SWITCH_COMPLETE = 11,
	/** switch source error
	*/
	PLAYER_EVENT_SWITCH_ERROR = 12,
	/** An application can render the video to less than a second
	 */
	PLAYER_EVENT_FIRST_DISPLAYED = 13,
	/** cache resources exceed the maximum file count
	 */
	PLAYER_EVENT_REACH_CACHE_FILE_MAX_COUNT = 14,
	/** cache resources exceed the maximum file size
	 */
	PLAYER_EVENT_REACH_CACHE_FILE_MAX_SIZE = 15,
	/** Triggered when a retry is required to open the media
	 */
	PLAYER_EVENT_TRY_OPEN_START = 16,
	/** Triggered when the retry to open the media is successful
	 */
	PLAYER_EVENT_TRY_OPEN_SUCCEED = 17,
	/** Triggered when retrying to open media fails
	 */
	PLAYER_EVENT_TRY_OPEN_FAILED = 18,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_17_ENTRIES(
	EUABT_MEDIA_PLAYER_EVENT, agora::media::base::MEDIA_PLAYER_EVENT,
	PLAYER_EVENT_SEEK_BEGIN,
	PLAYER_EVENT_SEEK_COMPLETE,
	PLAYER_EVENT_SEEK_ERROR,
	PLAYER_EVENT_AUDIO_TRACK_CHANGED,
	PLAYER_EVENT_BUFFER_LOW,
	PLAYER_EVENT_BUFFER_RECOVER,
	PLAYER_EVENT_FREEZE_START,
	PLAYER_EVENT_FREEZE_STOP,
	PLAYER_EVENT_SWITCH_BEGIN,
	PLAYER_EVENT_SWITCH_COMPLETE,
	PLAYER_EVENT_SWITCH_ERROR,
	PLAYER_EVENT_FIRST_DISPLAYED,
	PLAYER_EVENT_REACH_CACHE_FILE_MAX_COUNT,
	PLAYER_EVENT_REACH_CACHE_FILE_MAX_SIZE,
	PLAYER_EVENT_TRY_OPEN_START,
	PLAYER_EVENT_TRY_OPEN_SUCCEED,
	PLAYER_EVENT_TRY_OPEN_FAILED)



/**
* @brief The play preload another source event.
*
*/
UENUM(BlueprintType)
enum class EUABT_PLAYER_PRELOAD_EVENT :uint8 {
	/** preload source begin
	*/
	PLAYER_PRELOAD_EVENT_BEGIN = 0,
	/** preload source complete
	*/
	PLAYER_PRELOAD_EVENT_COMPLETE = 1,
	/** preload source error
	*/
	PLAYER_PRELOAD_EVENT_ERROR = 2,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_PLAYER_PRELOAD_EVENT, agora::media::base::PLAYER_PRELOAD_EVENT,
	PLAYER_PRELOAD_EVENT_BEGIN,
	PLAYER_PRELOAD_EVENT_COMPLETE,
	PLAYER_PRELOAD_EVENT_ERROR
)


/** Audio dual-mono output mode
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_DUAL_MONO_MODE : uint8 {
	/**< ChanLOut=ChanLin, ChanRout=ChanRin */
	AUDIO_DUAL_MONO_STEREO = 0,
	/**< ChanLOut=ChanRout=ChanLin */
	AUDIO_DUAL_MONO_L = 1,
	/**< ChanLOut=ChanRout=ChanRin */
	AUDIO_DUAL_MONO_R = 2,
	/**< ChanLout=ChanRout=(ChanLin+ChanRin)/2 */
	AUDIO_DUAL_MONO_MIX = 3
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_AUDIO_DUAL_MONO_MODE, agora::media::base::AUDIO_DUAL_MONO_MODE,
	AUDIO_DUAL_MONO_STEREO,
	AUDIO_DUAL_MONO_L,
	AUDIO_DUAL_MONO_R,
	AUDIO_DUAL_MONO_MIX
)


/**
 * @brief The type of the media stream.
 *
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_STREAM_TYPE : uint8 {
	/** The type is unknown.
	 */
	STREAM_TYPE_UNKNOWN = 0,
	/** The video stream.
	 */
	STREAM_TYPE_VIDEO = 1,
	/** The audio stream.
	 */
	STREAM_TYPE_AUDIO = 2,
	/** The subtitle stream.
	 */
	STREAM_TYPE_SUBTITLE = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_MEDIA_STREAM_TYPE, agora::media::base::MEDIA_STREAM_TYPE,
	STREAM_TYPE_UNKNOWN,
	STREAM_TYPE_VIDEO,
	STREAM_TYPE_AUDIO,
	STREAM_TYPE_SUBTITLE
)

#pragma endregion Enum - IMediaPlayerSourceObserver




#pragma region Enum - NoChange

/**
 * Video source types definition.
 **/
UENUM(BlueprintType)
enum class EUABT_VIDEO_SOURCE_TYPE : uint8 {
	/** Video captured by the camera.
	 */
	VIDEO_SOURCE_CAMERA_PRIMARY = 0,
	
	// VIDEO_SOURCE_CAMERA = VIDEO_SOURCE_CAMERA_PRIMARY,
	VIDEO_SOURCE_CAMERA,
	/** Video captured by the secondary camera.
	 */
	VIDEO_SOURCE_CAMERA_SECONDARY,
	/** Video for screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_PRIMARY,

	//VIDEO_SOURCE_SCREEN = VIDEO_SOURCE_SCREEN_PRIMARY,
	VIDEO_SOURCE_SCREEN,

	/** Video for secondary screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_SECONDARY,
	/** Not define.
	 */
	VIDEO_SOURCE_CUSTOM,
	/** Video for media player sharing.
	 */
	VIDEO_SOURCE_MEDIA_PLAYER,
	/** Video for png image.
	 */
	VIDEO_SOURCE_RTC_IMAGE_PNG,
	/** Video for png image.
	 */
	VIDEO_SOURCE_RTC_IMAGE_JPEG,
	/** Video for png image.
	 */
	VIDEO_SOURCE_RTC_IMAGE_GIF,
	/** Remote video received from network.
	 */
	VIDEO_SOURCE_REMOTE,
	/** Video for transcoded.
	 */
	VIDEO_SOURCE_TRANSCODED,

	/** Video captured by the third camera.
	 */
	VIDEO_SOURCE_CAMERA_THIRD,
	/** Video captured by the fourth camera.
	 */
	VIDEO_SOURCE_CAMERA_FOURTH,
	/** Video for third screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_THIRD,
	/** Video for fourth screen sharing.
	 */
	VIDEO_SOURCE_SCREEN_FOURTH,
	/** Video for voice drive.
	 */
	VIDEO_SOURCE_SPEECH_DRIVEN,

	VIDEO_SOURCE_UNKNOWN
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_19_ENTRIES_WITH_2_IDENTICAL_ONES(
	VIDEO_SOURCE_CAMERA, VIDEO_SOURCE_SCREEN, EUABT_VIDEO_SOURCE_TYPE, agora::rtc::VIDEO_SOURCE_TYPE,

	VIDEO_SOURCE_CAMERA_PRIMARY,
	VIDEO_SOURCE_CAMERA_SECONDARY,
	VIDEO_SOURCE_SCREEN_PRIMARY,
	VIDEO_SOURCE_SCREEN_SECONDARY,
	VIDEO_SOURCE_CUSTOM,
	VIDEO_SOURCE_MEDIA_PLAYER,
	VIDEO_SOURCE_RTC_IMAGE_PNG,
	VIDEO_SOURCE_RTC_IMAGE_JPEG,
	VIDEO_SOURCE_RTC_IMAGE_GIF,
	VIDEO_SOURCE_REMOTE,
	VIDEO_SOURCE_TRANSCODED,
	VIDEO_SOURCE_CAMERA_THIRD,
	VIDEO_SOURCE_CAMERA_FOURTH,
	VIDEO_SOURCE_SCREEN_THIRD,
	VIDEO_SOURCE_SCREEN_FOURTH,
	VIDEO_SOURCE_SPEECH_DRIVEN,
	VIDEO_SOURCE_UNKNOWN
)


/**
 * Thread priority type.
 */
UENUM(BlueprintType)
enum class EUABT_THREAD_PRIORITY_TYPE : uint8 {
	/**
	 * 0: Lowest priority.
	 */
	LOWEST = 0,
	/**
	 * 1: Low priority.
	 */
	LOW = 1,
	/**
	 * 2: Normal priority.
	 */
	NORMAL = 2,
	/**
	 * 3: High priority.
	 */
	HIGH = 3,
	/**
	 * 4. Highest priority.
	 */
	HIGHEST = 4,
	/**
	 * 5. Critical priority.
	 */
	CRITICAL = 5,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_THREAD_PRIORITY_TYPE, agora::rtc::THREAD_PRIORITY_TYPE,
	LOWEST,
	LOW,
	NORMAL,
	HIGH,
	HIGHEST,
	CRITICAL)


UENUM(BlueprintType)
enum class EUABT_PROXY_TYPE : uint8 {
	/** 0: Do not use the cloud proxy.
	 */
	NONE_PROXY_TYPE = 0,
	/** 1: The cloud proxy for the UDP protocol.
	 */
	UDP_PROXY_TYPE = 1,
	/** 2: The cloud proxy for the TCP (encrypted) protocol.
	 */
	TCP_PROXY_TYPE = 2,
	/** 3: The local proxy.
	 */
	LOCAL_PROXY_TYPE = 3,
	/** 4: auto fallback to tcp cloud proxy
	 */
	TCP_PROXY_AUTO_FALLBACK_TYPE = 4,
	/** 5: The http proxy.
	 */
	HTTP_PROXY_TYPE = 5,
	/** 6: The https proxy.
	 */
	HTTPS_PROXY_TYPE = 6,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_7_ENTRIES(EUABT_PROXY_TYPE, agora::rtc::PROXY_TYPE,
	NONE_PROXY_TYPE,
	UDP_PROXY_TYPE,
	TCP_PROXY_TYPE,
	LOCAL_PROXY_TYPE,
	TCP_PROXY_AUTO_FALLBACK_TYPE,
	HTTP_PROXY_TYPE,
	HTTPS_PROXY_TYPE)



/**
 * Video stream types.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_STREAM_TYPE : uint8 {
	/**
	 * 0: The high-quality video stream, which has the highest resolution and bitrate.
	 */
	VIDEO_STREAM_HIGH = 0,
	/**
	 * 1: The low-quality video stream, which has the lowest resolution and bitrate.
	 */
	VIDEO_STREAM_LOW = 1,
	/**
	 * 4: The video stream of layer_1, which has a lower resolution and bitrate than VIDEO_STREAM_HIGH.
	 */
	VIDEO_STREAM_LAYER_1 = 4,
	/**
	 * 5: The video stream of layer_2, which has a lower resolution and bitrate than VIDEO_STREAM_LAYER_1.
	 */
	VIDEO_STREAM_LAYER_2 = 5,
	/**
	 * 6: The video stream of layer_3, which has a lower resolution and bitrate than VIDEO_STREAM_LAYER_2.
	 */
	VIDEO_STREAM_LAYER_3 = 6,
	/**
	 * 7: The video stream of layer_4, which has a lower resolution and bitrate than VIDEO_STREAM_LAYER_3.
	 */
	VIDEO_STREAM_LAYER_4 = 7,
	/**
	 * 8: The video stream of layer_5, which has a lower resolution and bitrate than VIDEO_STREAM_LAYER_4.
	 */
	VIDEO_STREAM_LAYER_5 = 8,
	/**
	 * 9: The video stream of layer_6, which has a lower resolution and bitrate than VIDEO_STREAM_LAYER_5.
	 */
	VIDEO_STREAM_LAYER_6 = 9,

};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_8_ENTRIES(EUABT_VIDEO_STREAM_TYPE, agora::rtc::VIDEO_STREAM_TYPE,
	VIDEO_STREAM_HIGH,
	VIDEO_STREAM_LOW,
	VIDEO_STREAM_LAYER_1,
	VIDEO_STREAM_LAYER_2,
	VIDEO_STREAM_LAYER_3,
	VIDEO_STREAM_LAYER_4,
	VIDEO_STREAM_LAYER_5,
	VIDEO_STREAM_LAYER_6
)

/**
 * The downscale level of the remote video stream . The higher the downscale level, the more the
 * video downscales.
 */
UENUM(BlueprintType)
enum  class EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL : uint8 {
	/**
	 * No downscale.
	 */
	REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE = 0,
	/**
	 * Downscale level 1.
	 */
	REMOTE_VIDEO_DOWNSCALE_LEVEL_1,
	/**
	 * Downscale level 2.
	 */
	REMOTE_VIDEO_DOWNSCALE_LEVEL_2,
	/**
	 * Downscale level 3.
	 */
	REMOTE_VIDEO_DOWNSCALE_LEVEL_3,
	/**
	 * Downscale level 4.
	 */
	REMOTE_VIDEO_DOWNSCALE_LEVEL_4,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_REMOTE_VIDEO_DOWNSCALE_LEVEL, agora::rtc::REMOTE_VIDEO_DOWNSCALE_LEVEL,
	REMOTE_VIDEO_DOWNSCALE_LEVEL_NONE,
	REMOTE_VIDEO_DOWNSCALE_LEVEL_1,
	REMOTE_VIDEO_DOWNSCALE_LEVEL_2,
	REMOTE_VIDEO_DOWNSCALE_LEVEL_3,
	REMOTE_VIDEO_DOWNSCALE_LEVEL_4
)

/** Local video state types.
 */
UENUM(BlueprintType)
enum class EUABT_LOCAL_VIDEO_STREAM_STATE :uint8 {
	/**
	 * 0: The local video is in the initial state.
	 */
	LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,
	/**
	 * 1: The local video capturing device starts successfully. The SDK also reports this state when
	 * you call `startScreenCaptureByWindowId` to share a maximized window.
	 */
	LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,
	/**
	 * 2: The first video frame is successfully encoded.
	 */
	LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,
	/**
	 * 3: Fails to start the local video.
	 */
	LOCAL_VIDEO_STREAM_STATE_FAILED = 3
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_LOCAL_VIDEO_STREAM_STATE, agora::rtc::LOCAL_VIDEO_STREAM_STATE,
	LOCAL_VIDEO_STREAM_STATE_STOPPED,
	LOCAL_VIDEO_STREAM_STATE_CAPTURING,
	LOCAL_VIDEO_STREAM_STATE_ENCODING,
	LOCAL_VIDEO_STREAM_STATE_FAILED
)

/**
 * The state of the remote video.
 */
UENUM(BlueprintType)
enum class EUABT_REMOTE_VIDEO_STATE : uint8 {
	/**
	 * 0: The remote video is in the default state. The SDK reports this state in the case of
	 * `REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3)`, `REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5)`,
	 * `REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7)`, or `REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK
	 * (8)`.
	 */
	REMOTE_VIDEO_STATE_STOPPED = 0,
	/**
	 * 1: The first remote video packet is received.
	 */
	REMOTE_VIDEO_STATE_STARTING = 1,
	/**
	 * 2: The remote video stream is decoded and plays normally. The SDK reports this state in the
	 * case of `REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2)`,
	 * `REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4)`, `REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6)`,
	 * or `REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9)`.
	 */
	REMOTE_VIDEO_STATE_DECODING = 2,
	/** 3: The remote video is frozen, probably due to
	 * #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1).
	 */
	REMOTE_VIDEO_STATE_FROZEN = 3,
	/** 4: The remote video fails to start. The SDK reports this state in the case of
	 * `REMOTE_VIDEO_STATE_REASON_INTERNAL (0)`.
	 */
	REMOTE_VIDEO_STATE_FAILED = 4,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_REMOTE_VIDEO_STATE, agora::rtc::REMOTE_VIDEO_STATE,
	REMOTE_VIDEO_STATE_STOPPED,
	REMOTE_VIDEO_STATE_STARTING,
	REMOTE_VIDEO_STATE_DECODING,
	REMOTE_VIDEO_STATE_FROZEN,
	REMOTE_VIDEO_STATE_FAILED
)

/**
 * The reason for the remote video state change.
 */
UENUM(BlueprintType)
enum class EUABT_REMOTE_VIDEO_STATE_REASON :uint8 {
	/**
	 * 0: The SDK reports this reason when the video state changes.
	 */
	REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,
	/**
	 * 1: Network congestion.
	 */
	REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,
	/**
	 * 2: Network recovery.
	 */
	REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,
	/**
	 * 3: The local user stops receiving the remote video stream or disables the video module.
	 */
	REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,
	/**
	 * 4: The local user resumes receiving the remote video stream or enables the video module.
	 */
	REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,
	/**
	 * 5: The remote user stops sending the video stream or disables the video module.
	 */
	REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,
	/**
	 * 6: The remote user resumes sending the video stream or enables the video module.
	 */
	REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,
	/**
	 * 7: The remote user leaves the channel.
	 */
	REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,
	/** 8: The remote audio-and-video stream falls back to the audio-only stream
	 * due to poor network conditions.
	 */
	REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,
	/** 9: The remote audio-only stream switches back to the audio-and-video
	 * stream after the network conditions improve.
	 */
	REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9,
	/** (Internal use only) 10: The remote video stream type change to low stream type
	 */
	REMOTE_VIDEO_STATE_REASON_VIDEO_STREAM_TYPE_CHANGE_TO_LOW = 10,
	/** (Internal use only)  11: The remote video stream type change to high stream type
	 */
	REMOTE_VIDEO_STATE_REASON_VIDEO_STREAM_TYPE_CHANGE_TO_HIGH = 11,
	/** (iOS only) 12: The app of the remote user is in background.
	 */
	REMOTE_VIDEO_STATE_REASON_SDK_IN_BACKGROUND = 12,

	/** 13: The remote video stream is not supported by the decoder
	 */
	REMOTE_VIDEO_STATE_REASON_CODEC_NOT_SUPPORT = 13,

};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_14_ENTRIES(EUABT_REMOTE_VIDEO_STATE_REASON, agora::rtc::REMOTE_VIDEO_STATE_REASON,
	REMOTE_VIDEO_STATE_REASON_INTERNAL,
	REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION,
	REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY,
	REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED,
	REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED,
	REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED,
	REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED,
	REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE,
	REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK,
	REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY,
	REMOTE_VIDEO_STATE_REASON_VIDEO_STREAM_TYPE_CHANGE_TO_LOW,
	REMOTE_VIDEO_STATE_REASON_VIDEO_STREAM_TYPE_CHANGE_TO_HIGH,
	REMOTE_VIDEO_STATE_REASON_SDK_IN_BACKGROUND,
	REMOTE_VIDEO_STATE_REASON_CODEC_NOT_SUPPORT
)

/**
 * Local video state error codes.
 */
UENUM(BlueprintType)
enum class EUABT_LOCAL_VIDEO_STREAM_REASON : uint8 {
	/**
	 * 0: The local video is normal.
	 */
	LOCAL_VIDEO_STREAM_REASON_OK = 0,
	/**
	 * 1: No specified reason for the local video failure.
	 */
	LOCAL_VIDEO_STREAM_REASON_FAILURE = 1,
	/**
	 * 2: No permission to use the local video capturing device. Remind the user to grant permission
	 * and rejoin the channel.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_NO_PERMISSION = 2,
	/**
	 * 3: The local video capturing device is in use. Remind the user to check whether another
	 * application occupies the camera.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_BUSY = 3,
	/**
	 * 4: The local video capture fails. Remind the user to check whether the video capture device
	 * is working properly or the camera is occupied by another application, and then to rejoin the
	 * channel.
	 */
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_FAILURE = 4,
	/**
	 * 5: The local video encoder is not supported.
	 */
	LOCAL_VIDEO_STREAM_REASON_CODEC_NOT_SUPPORT = 5,
	/**
	 * 6: (iOS only) The app is in the background. Remind the user that video capture cannot be
	 * performed normally when the app is in the background.
	 */
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_INBACKGROUND = 6,
	/**
	 * 7: (iOS only) The current application window is running in Slide Over, Split View, or Picture
	 * in Picture mode, and another app is occupying the camera. Remind the user that the application
	 * cannot capture video properly when the app is running in Slide Over, Split View, or Picture in
	 * Picture mode and another app is occupying the camera.
	 */
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_MULTIPLE_FOREGROUND_APPS = 7,
	/**
	 * 8: Fails to find a local video capture device. Remind the user to check whether the camera is
	 * connected to the device properly or the camera is working properly, and then to rejoin the
	 * channel.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_NOT_FOUND = 8,
	/**
	 *  9: (macOS and Windows only) The video capture device currently in use is disconnected (such as being
	 * unplugged).
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_DISCONNECTED = 9,
	/**
	 * 10: (macOS and Windows only) The SDK cannot find the video device in the video device list.
	 * Check whether the ID of the video device is valid.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_INVALID_ID = 10,
	/**
	 * 14: (Android only) Video capture was interrupted, possibly due to the camera being occupied
	 * or some policy reasons such as background termination.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_INTERRUPT = 14,
	/**
	 * 15: (Android only) The device may need to be shut down and restarted to restore camera
	 * function, or there may be a persistent hardware problem.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_FATAL_ERROR = 15,
	/**
	 * 101: The current video capture device is unavailable due to excessive system pressure.
	 */
	LOCAL_VIDEO_STREAM_REASON_DEVICE_SYSTEM_PRESSURE = 101,
	/**
	 * 11: (macOS only) The shared window is minimized when you call `startScreenCaptureByWindowId`
	 * to share a window. The SDK cannot share a minimized window. You can cancel the minimization
	 * of this window at the application layer, for example by maximizing this window.
	 */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_MINIMIZED = 11,
	/**
	 * 12: (macOS and Windows only) The error code indicates that a window shared by the window ID
	 * has been closed or a full-screen window shared by the window ID has exited full-screen mode.
	 * After exiting full-screen mode, remote users cannot see the shared window. To prevent remote
	 * users from seeing a black screen, Agora recommends that you immediately stop screen sharing.
	 *
	 * Common scenarios for reporting this error code:
	 * - When the local user closes the shared window, the SDK reports this error code.
	 * - The local user shows some slides in full-screen mode first, and then shares the windows of
	 * the slides. After the user exits full-screen mode, the SDK reports this error code.
	 * - The local user watches a web video or reads a web document in full-screen mode first, and
	 * then shares the window of the web video or document. After the user exits full-screen mode,
	 * the SDK reports this error code.
	 */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_CLOSED = 12,
	/** 13: The local screen capture window is occluded. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_OCCLUDED = 13,
	/** 20: The local screen capture window is not supported. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_NOT_SUPPORTED = 20,
	/** 21: The screen capture fails. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_FAILURE = 21,
	/** 22: No permision to capture screen. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_NO_PERMISSION = 22,
	/**
	 * 24: (Windows Only) An unexpected error (possibly due to window block failure) occurs during the
	 * screen sharing process, resulting in performance degradation. However, the screen sharing
	 * process itself is functioning normally.
	 */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_AUTO_FALLBACK = 24,
	/** 25: (Windows only) The local screen capture window is currently hidden and not visible on the
	   desktop. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_HIDDEN = 25,
	/** 26: (Windows only) The local screen capture window is recovered from its hidden state. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_RECOVER_FROM_HIDDEN = 26,
	/** 27: (Windows and macOS only) The window is recovered from miniminzed */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_RECOVER_FROM_MINIMIZED = 27,
	/**
	 * 28: The screen capture paused.
	 *
	 * Common scenarios for reporting this error code:
	 * - When the desktop switch to the secure desktop such as UAC dialog or the Winlogon desktop on
	 * Windows platform, the SDK reports this error code.
	 */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_PAUSED = 28,
	/** 29: The screen capture is resumed. */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_RESUMED = 29,
	/** 30: The shared display has been disconnected */
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_DISPLAY_DISCONNECTED = 30,

};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_27_ENTRIES(EUABT_LOCAL_VIDEO_STREAM_REASON, agora::rtc::LOCAL_VIDEO_STREAM_REASON,
	LOCAL_VIDEO_STREAM_REASON_OK,
	LOCAL_VIDEO_STREAM_REASON_FAILURE,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_NO_PERMISSION,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_BUSY,
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_FAILURE,
	LOCAL_VIDEO_STREAM_REASON_CODEC_NOT_SUPPORT,
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_INBACKGROUND,
	LOCAL_VIDEO_STREAM_REASON_CAPTURE_MULTIPLE_FOREGROUND_APPS,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_NOT_FOUND,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_DISCONNECTED,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_INVALID_ID,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_INTERRUPT,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_FATAL_ERROR,
	LOCAL_VIDEO_STREAM_REASON_DEVICE_SYSTEM_PRESSURE,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_MINIMIZED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_CLOSED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_OCCLUDED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_NOT_SUPPORTED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_FAILURE,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_NO_PERMISSION,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_AUTO_FALLBACK,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_HIDDEN,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_RECOVER_FROM_HIDDEN,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_WINDOW_RECOVER_FROM_MINIMIZED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_PAUSED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_RESUMED,
	LOCAL_VIDEO_STREAM_REASON_SCREEN_CAPTURE_DISPLAY_DISCONNECTED)




/**
 * Quality change of the local video in terms of target frame rate and target bit rate since last
 * count.
 */
UENUM(BlueprintType)
enum class EUABT_QUALITY_ADAPT_INDICATION : uint8 {
	/**
	 * 0: The quality of the local video stays the same.
	 */
	ADAPT_NONE = 0,
	/**
	 * 1: The quality improves because the network bandwidth increases.
	 */
	ADAPT_UP_BANDWIDTH = 1,
	/**
	 * 2: The quality worsens because the network bandwidth decreases.
	 */
	ADAPT_DOWN_BANDWIDTH = 2,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_QUALITY_ADAPT_INDICATION, agora::rtc::QUALITY_ADAPT_INDICATION,
	ADAPT_NONE,
	ADAPT_UP_BANDWIDTH,
	ADAPT_DOWN_BANDWIDTH
)


/**
 * The video codec types.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_CODEC_TYPE : uint8 {
	/**
	 * 0: (Default) SDK will automatically adjust the codec type according to country and region or real-time network state and other relevant data information.
	 * Also if network state is changed, SDK may change codec automatically to get the best QOE.
	 * We recommend use this option.
	 */
	VIDEO_CODEC_NONE = 0,
	/**
	 * 1: Standard VP8.
	 */
	VIDEO_CODEC_VP8 = 1,
	/**
	 * 2: Standard H.264.
	 */
	VIDEO_CODEC_H264 = 2,
	/**
	 * 3: Standard H.265.
	 */
	VIDEO_CODEC_H265 = 3,
	/**
	 * 6: Generic. This type is used for transmitting raw video data, such as encrypted video frames.
	 * The SDK returns this type of video frames in callbacks, and you need to decode and render the
	 * frames yourself.
	 */
	VIDEO_CODEC_GENERIC = 6,
	/**
	 * 7: Generic H264.
	 * @deprecated This codec type is deprecated.
	 */
	VIDEO_CODEC_GENERIC_H264 = 7,
	/**
	 * 12: AV1.
	 * @technical preview
	 */
	VIDEO_CODEC_AV1 = 12,
	/**
	 * 13: VP9.
	 */
	VIDEO_CODEC_VP9 = 13,
	/**
	 * 20: Generic JPEG. This type consumes minimum computing resources and applies to IoT devices.
	 */
	VIDEO_CODEC_GENERIC_JPEG = 20,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_9_ENTRIES(EUABT_VIDEO_CODEC_TYPE, agora::rtc::VIDEO_CODEC_TYPE,
	VIDEO_CODEC_NONE,
	VIDEO_CODEC_VP8,
	VIDEO_CODEC_H264,
	VIDEO_CODEC_H265,
	VIDEO_CODEC_GENERIC,
	VIDEO_CODEC_GENERIC_H264,
	VIDEO_CODEC_AV1,
	VIDEO_CODEC_VP9,
	VIDEO_CODEC_GENERIC_JPEG
)

/**
 * Local audio states.
 */
UENUM(BlueprintType)
enum class EUABT_LOCAL_AUDIO_STREAM_STATE : uint8 {
	/**
	 * 0: The local audio is in the initial state.
	 */
	LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,
	/**
	 * 1: The capturing device starts successfully.
	 */
	LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,
	/**
	 * 2: The first audio frame encodes successfully.
	 */
	LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,
	/**
	 * 3: The local audio fails to start.
	 */
	LOCAL_AUDIO_STREAM_STATE_FAILED = 3
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_LOCAL_AUDIO_STREAM_STATE, agora::rtc::LOCAL_AUDIO_STREAM_STATE,
	LOCAL_AUDIO_STREAM_STATE_STOPPED,
	LOCAL_AUDIO_STREAM_STATE_RECORDING,
	LOCAL_AUDIO_STREAM_STATE_ENCODING,
	LOCAL_AUDIO_STREAM_STATE_FAILED
)

/**
 * Local audio state error codes.
 */
UENUM(BlueprintType)
enum class EUABT_LOCAL_AUDIO_STREAM_REASON : uint8 {
	/**
	 * 0: The local audio is normal.
	 */
	LOCAL_AUDIO_STREAM_REASON_OK = 0,
	/**
	 * 1: No specified reason for the local audio failure. Remind your users to try to rejoin the
	 * channel.
	 */
	LOCAL_AUDIO_STREAM_REASON_FAILURE = 1,
	/**
	 * 2: No permission to use the local audio device. Remind your users to grant permission.
	 */
	LOCAL_AUDIO_STREAM_REASON_DEVICE_NO_PERMISSION = 2,
	/**
	 * 3: (Android and iOS only) The local audio capture device is used. Remind your users to check
	 * whether another application occupies the microphone. Local audio capture automatically resume
	 * after the microphone is idle for about five seconds. You can also try to rejoin the channel
	 * after the microphone is idle.
	 */
	LOCAL_AUDIO_STREAM_REASON_DEVICE_BUSY = 3,
	/**
	 * 4: The local audio capture failed.
	 */
	LOCAL_AUDIO_STREAM_REASON_RECORD_FAILURE = 4,
	/**
	 * 5: The local audio encoding failed.
	 */
	LOCAL_AUDIO_STREAM_REASON_ENCODE_FAILURE = 5,
	/** 6: The SDK cannot find the local audio recording device.
	 */
	LOCAL_AUDIO_STREAM_REASON_NO_RECORDING_DEVICE = 6,
	/** 7: The SDK cannot find the local audio playback device.
	 */
	LOCAL_AUDIO_STREAM_REASON_NO_PLAYOUT_DEVICE = 7,
	/**
	 * 8: The local audio capturing is interrupted by the system call.
	 */
	LOCAL_AUDIO_STREAM_REASON_INTERRUPTED = 8,
	/** 9: An invalid audio capture device ID.
	 */
	LOCAL_AUDIO_STREAM_REASON_RECORD_INVALID_ID = 9,
	/** 10: An invalid audio playback device ID.
	 */
	LOCAL_AUDIO_STREAM_REASON_PLAYOUT_INVALID_ID = 10,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_11_ENTRIES(EUABT_LOCAL_AUDIO_STREAM_REASON, agora::rtc::LOCAL_AUDIO_STREAM_REASON,
	LOCAL_AUDIO_STREAM_REASON_OK,
	LOCAL_AUDIO_STREAM_REASON_FAILURE,
	LOCAL_AUDIO_STREAM_REASON_DEVICE_NO_PERMISSION,
	LOCAL_AUDIO_STREAM_REASON_DEVICE_BUSY,
	LOCAL_AUDIO_STREAM_REASON_RECORD_FAILURE,
	LOCAL_AUDIO_STREAM_REASON_ENCODE_FAILURE,
	LOCAL_AUDIO_STREAM_REASON_NO_RECORDING_DEVICE,
	LOCAL_AUDIO_STREAM_REASON_NO_PLAYOUT_DEVICE,
	LOCAL_AUDIO_STREAM_REASON_INTERRUPTED,
	LOCAL_AUDIO_STREAM_REASON_RECORD_INVALID_ID,
	LOCAL_AUDIO_STREAM_REASON_PLAYOUT_INVALID_ID
)


/**
 * Remote audio states.
 */
UENUM(BlueprintType)
enum class EUABT_REMOTE_AUDIO_STATE : uint8 {
	/**
	 * 0: The remote audio is in the default state. The SDK reports this state in the case of
	 * `REMOTE_AUDIO_REASON_LOCAL_MUTED(3)`, `REMOTE_AUDIO_REASON_REMOTE_MUTED(5)`, or
	 * `REMOTE_AUDIO_REASON_REMOTE_OFFLINE(7)`.
	 */
	REMOTE_AUDIO_STATE_STOPPED =
	0,  // Default state, audio is started or remote user disabled/muted audio stream
	/**
	 * 1: The first remote audio packet is received.
	 */
	REMOTE_AUDIO_STATE_STARTING = 1,  // The first audio frame packet has been received
	/**
	 * 2: The remote audio stream is decoded and plays normally. The SDK reports this state in the
	 * case of `REMOTE_AUDIO_REASON_NETWORK_RECOVERY(2)`, `REMOTE_AUDIO_REASON_LOCAL_UNMUTED(4)`, or
	 * `REMOTE_AUDIO_REASON_REMOTE_UNMUTED(6)`.
	 */
	REMOTE_AUDIO_STATE_DECODING =
	2,  // The first remote audio frame has been decoded or fronzen state ends
	/**
	 * 3: The remote audio is frozen. The SDK reports this state in the case of
	 * `REMOTE_AUDIO_REASON_NETWORK_CONGESTION(1)`.
	 */
	REMOTE_AUDIO_STATE_FROZEN = 3,  // Remote audio is frozen, probably due to network issue
	/**
	 * 4: The remote audio fails to start. The SDK reports this state in the case of
	 * `REMOTE_AUDIO_REASON_INTERNAL(0)`.
	 */
	REMOTE_AUDIO_STATE_FAILED = 4,  // Remote audio play failed
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_REMOTE_AUDIO_STATE, agora::rtc::REMOTE_AUDIO_STATE,
	REMOTE_AUDIO_STATE_STOPPED,
	REMOTE_AUDIO_STATE_STARTING,
	REMOTE_AUDIO_STATE_DECODING,
	REMOTE_AUDIO_STATE_FROZEN,
	REMOTE_AUDIO_STATE_FAILED
)

/**
 * Reasons for the remote audio state change.
 */
UENUM(BlueprintType)
enum class EUABT_REMOTE_AUDIO_STATE_REASON : uint8 {
	/**
	 * 0: The SDK reports this reason when the video state changes.
	 */
	REMOTE_AUDIO_REASON_INTERNAL = 0,
	/**
	 * 1: Network congestion.
	 */
	REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
	/**
	 * 2: Network recovery.
	 */
	REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
	/**
	 * 3: The local user stops receiving the remote audio stream or
	 * disables the audio module.
	 */
	REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
	/**
	 * 4: The local user resumes receiving the remote audio stream or
	 * enables the audio module.
	 */
	REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
	/**
	 * 5: The remote user stops sending the audio stream or disables the
	 * audio module.
	 */
	REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
	/**
	 * 6: The remote user resumes sending the audio stream or enables the
	 * audio module.
	 */
	REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
	/**
	 * 7: The remote user leaves the channel.
	 */
	REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
	/**
	 * 8: The local user does not receive any audio packet from remote user.
	 */
	REMOTE_AUDIO_REASON_NO_PACKET_RECEIVE = 8,
	/**
	 * 9: The local user receives remote audio packet but fails to play.
	 */
	REMOTE_AUDIO_REASON_LOCAL_PLAY_FAILED = 9,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_10_ENTRIES(EUABT_REMOTE_AUDIO_STATE_REASON, agora::rtc::REMOTE_AUDIO_STATE_REASON,
	REMOTE_AUDIO_REASON_INTERNAL,
	REMOTE_AUDIO_REASON_NETWORK_CONGESTION,
	REMOTE_AUDIO_REASON_NETWORK_RECOVERY,
	REMOTE_AUDIO_REASON_LOCAL_MUTED,
	REMOTE_AUDIO_REASON_LOCAL_UNMUTED,
	REMOTE_AUDIO_REASON_REMOTE_MUTED,
	REMOTE_AUDIO_REASON_REMOTE_UNMUTED,
	REMOTE_AUDIO_REASON_REMOTE_OFFLINE,
	REMOTE_AUDIO_REASON_NO_PACKET_RECEIVE,
	REMOTE_AUDIO_REASON_LOCAL_PLAY_FAILED
)


/**
 * States of the Media Push.
 */
UENUM(BlueprintType)
enum class EUABT_RTMP_STREAM_PUBLISH_STATE : uint8 {
  /**
   * 0: The Media Push has not started or has ended. This state is also triggered after you remove a
   * RTMP or RTMPS stream from the CDN by calling `removePublishStreamUrl`.
   */
  RTMP_STREAM_PUBLISH_STATE_IDLE = 0,
  /**
   * 1: The SDK is connecting to Agora's streaming server and the CDN server. This state is
   * triggered after you call the `addPublishStreamUrl` method.
   */
  RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,
  /**
   * 2: The RTMP or RTMPS streaming publishes. The SDK successfully publishes the RTMP or RTMPS
   * streaming and returns this state.
   */
  RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,
  /**
   * 3: The RTMP or RTMPS streaming is recovering. When exceptions occur to the CDN, or the
   * streaming is interrupted, the SDK tries to resume RTMP or RTMPS streaming and returns this
   * state.
   * - If the SDK successfully resumes the streaming, #RTMP_STREAM_PUBLISH_STATE_RUNNING (2)
   * returns.
   * - If the streaming does not resume within 60 seconds or server errors occur,
   * #RTMP_STREAM_PUBLISH_STATE_FAILURE (4) returns. You can also reconnect to the server by calling
   * the `removePublishStreamUrl` and `addPublishStreamUrl` methods.
   */
  RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,
  /**
   * 4: The RTMP or RTMPS streaming fails. See the `errCode` parameter for the detailed error
   * information. You can also call the `addPublishStreamUrl` method to publish the RTMP or RTMPS
   * streaming again.
   */
  RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,
  /**
   * 5: The SDK is disconnecting to Agora's streaming server and the CDN server. This state is
   * triggered after you call the `removePublishStreamUrl` method.
   */
  RTMP_STREAM_PUBLISH_STATE_DISCONNECTING = 5,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_RTMP_STREAM_PUBLISH_STATE, agora::rtc::RTMP_STREAM_PUBLISH_STATE,
	RTMP_STREAM_PUBLISH_STATE_IDLE,
	RTMP_STREAM_PUBLISH_STATE_CONNECTING,
	RTMP_STREAM_PUBLISH_STATE_RUNNING,
	RTMP_STREAM_PUBLISH_STATE_RECOVERING,
	RTMP_STREAM_PUBLISH_STATE_FAILURE,
	RTMP_STREAM_PUBLISH_STATE_DISCONNECTING
)



/**
 * Error codes of the RTMP or RTMPS streaming.
 */
UENUM(BlueprintType)
enum class EUABT_RTMP_STREAM_PUBLISH_REASON : uint8 {
  /**
   * 0: The RTMP or RTMPS streaming publishes successfully.
   */
  RTMP_STREAM_PUBLISH_REASON_OK = 0,
  /**
   * 1: Invalid argument used. If, for example, you do not call the `setLiveTranscoding` method to
   * configure the LiveTranscoding parameters before calling the addPublishStreamUrl method, the SDK
   * returns this error. Check whether you set the parameters in the `setLiveTranscoding` method
   * properly.
   */
  RTMP_STREAM_PUBLISH_REASON_INVALID_ARGUMENT = 1,
  /**
   * 2: The RTMP or RTMPS streaming is encrypted and cannot be published.
   */
  RTMP_STREAM_PUBLISH_REASON_ENCRYPTED_STREAM_NOT_ALLOWED = 2,
  /**
   * 3: Timeout for the RTMP or RTMPS streaming. Call the `addPublishStreamUrl` method to publish
   * the streaming again.
   */
  RTMP_STREAM_PUBLISH_REASON_CONNECTION_TIMEOUT = 3,
  /**
   * 4: An error occurs in Agora's streaming server. Call the `addPublishStreamUrl` method to
   * publish the streaming again.
   */
  RTMP_STREAM_PUBLISH_REASON_INTERNAL_SERVER_ERROR = 4,
  /**
   * 5: An error occurs in the CDN server.
   */
  RTMP_STREAM_PUBLISH_REASON_RTMP_SERVER_ERROR = 5,
  /**
   * 6: The RTMP or RTMPS streaming publishes too frequently.
   */
  RTMP_STREAM_PUBLISH_REASON_TOO_OFTEN = 6,
  /**
   * 7: The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones.
   */
  RTMP_STREAM_PUBLISH_REASON_REACH_LIMIT = 7,
  /**
   * 8: The host manipulates other hosts' URLs. Check your app logic.
   */
  RTMP_STREAM_PUBLISH_REASON_NOT_AUTHORIZED = 8,
  /**
   * 9: Agora's server fails to find the RTMP or RTMPS streaming.
   */
  RTMP_STREAM_PUBLISH_REASON_STREAM_NOT_FOUND = 9,
  /**
   * 10: The format of the RTMP or RTMPS streaming URL is not supported. Check whether the URL
   * format is correct.
   */
  RTMP_STREAM_PUBLISH_REASON_FORMAT_NOT_SUPPORTED = 10,
  /**
   * 11: The user role is not host, so the user cannot use the CDN live streaming function. Check
   * your application code logic.
   */
  RTMP_STREAM_PUBLISH_REASON_NOT_BROADCASTER =
      11,  // Note: match to ERR_PUBLISH_STREAM_NOT_BROADCASTER in AgoraBase.h
  /**
   * 13: The `updateRtmpTranscoding` or `setLiveTranscoding` method is called to update the
   * transcoding configuration in a scenario where there is streaming without transcoding. Check
   * your application code logic.
   */
  RTMP_STREAM_PUBLISH_REASON_TRANSCODING_NO_MIX_STREAM =
      13,  // Note: match to ERR_PUBLISH_STREAM_TRANSCODING_NO_MIX_STREAM in AgoraBase.h
  /**
   * 14: Errors occurred in the host's network.
   */
  RTMP_STREAM_PUBLISH_REASON_NET_DOWN = 14,  // Note: match to ERR_NET_DOWN in AgoraBase.h
  /**
   * 15: Your App ID does not have permission to use the CDN live streaming function.
   */
  RTMP_STREAM_PUBLISH_REASON_INVALID_APPID =
      15,  // Note: match to ERR_PUBLISH_STREAM_APPID_INVALID in AgoraBase.h
  /** invalid privilege. */
  RTMP_STREAM_PUBLISH_REASON_INVALID_PRIVILEGE = 16,
  /**
   * 100: The streaming has been stopped normally. After you call `removePublishStreamUrl` to stop
   * streaming, the SDK returns this value.
   */
  RTMP_STREAM_UNPUBLISH_REASON_OK = 100,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_17_ENTRIES(EUABT_RTMP_STREAM_PUBLISH_REASON, agora::rtc::RTMP_STREAM_PUBLISH_REASON,
	RTMP_STREAM_PUBLISH_REASON_OK,
	RTMP_STREAM_PUBLISH_REASON_INVALID_ARGUMENT,
	RTMP_STREAM_PUBLISH_REASON_ENCRYPTED_STREAM_NOT_ALLOWED,
	RTMP_STREAM_PUBLISH_REASON_CONNECTION_TIMEOUT,
	RTMP_STREAM_PUBLISH_REASON_INTERNAL_SERVER_ERROR,
	RTMP_STREAM_PUBLISH_REASON_RTMP_SERVER_ERROR,
	RTMP_STREAM_PUBLISH_REASON_TOO_OFTEN,
	RTMP_STREAM_PUBLISH_REASON_REACH_LIMIT,
	RTMP_STREAM_PUBLISH_REASON_NOT_AUTHORIZED,
	RTMP_STREAM_PUBLISH_REASON_STREAM_NOT_FOUND,
	RTMP_STREAM_PUBLISH_REASON_FORMAT_NOT_SUPPORTED,
	RTMP_STREAM_PUBLISH_REASON_NOT_BROADCASTER,
	RTMP_STREAM_PUBLISH_REASON_TRANSCODING_NO_MIX_STREAM,
	RTMP_STREAM_PUBLISH_REASON_NET_DOWN,
	RTMP_STREAM_PUBLISH_REASON_INVALID_APPID,
	RTMP_STREAM_PUBLISH_REASON_INVALID_PRIVILEGE,
	RTMP_STREAM_UNPUBLISH_REASON_OK
)



/**
 * Reasons causing the change of the connection state.
 */
UENUM(BlueprintType)
enum class EUABT_CONNECTION_CHANGED_REASON_TYPE : uint8 {
  /**
   * 0: The SDK is connecting to the server.
   */
  CONNECTION_CHANGED_CONNECTING = 0,
  /**
   * 1: The SDK has joined the channel successfully.
   */
  CONNECTION_CHANGED_JOIN_SUCCESS = 1,
  /**
   * 2: The connection between the SDK and the server is interrupted.
   */
  CONNECTION_CHANGED_INTERRUPTED = 2,
  /**
   * 3: The connection between the SDK and the server is banned by the server. This error occurs
   * when the user is kicked out of the channel by the server.
   */
  CONNECTION_CHANGED_BANNED_BY_SERVER = 3,
  /**
   * 4: The SDK fails to join the channel. When the SDK fails to join the channel for more than 20
   * minutes, this error occurs and the SDK stops reconnecting to the channel.
   */
  CONNECTION_CHANGED_JOIN_FAILED = 4,
  /**
   * 5: The SDK has left the channel.
   */
  CONNECTION_CHANGED_LEAVE_CHANNEL = 5,
  /**
   * 6: The connection fails because the App ID is not valid.
   */
  CONNECTION_CHANGED_INVALID_APP_ID = 6,
  /**
   * 7: The connection fails because the channel name is not valid. Please rejoin the channel with a
   * valid channel name.
   */
  CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,
  /**
   * 8: The connection fails because the token is not valid. Typical reasons include:
   * - The App Certificate for the project is enabled in Agora Console, but you do not use a token
   * when joining the channel. If you enable the App Certificate, you must use a token to join the
   * channel.
   * - The `uid` specified when calling `joinChannel` to join the channel is inconsistent with the
   * `uid` passed in when generating the token.
   */
  CONNECTION_CHANGED_INVALID_TOKEN = 8,
  /**
   * 9: The connection fails because the token has expired.
   */
  CONNECTION_CHANGED_TOKEN_EXPIRED = 9,
  /**
   * 10: The connection is rejected by the server. Typical reasons include:
   * - The user is already in the channel and still calls a method, for example, `joinChannel`, to
   * join the channel. Stop calling this method to clear this error.
   * - The user tries to join the channel when conducting a pre-call test. The user needs to call
   * the channel after the call test ends.
   */
  CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,
  /**
   * 11: The connection changes to reconnecting because the SDK has set a proxy server.
   */
  CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,
  /**
   * 12: The connection state changed because the token is renewed.
   */
  CONNECTION_CHANGED_RENEW_TOKEN = 12,
  /**
   * 13: The IP address of the client has changed, possibly because the network type, IP address, or
   * port has been changed.
   */
  CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,
  /**
   * 14: Timeout for the keep-alive of the connection between the SDK and the Agora edge server. The
   * connection state changes to CONNECTION_STATE_RECONNECTING.
   */
  CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,
  /**
   * 15: The SDK has rejoined the channel successfully.
   */
  CONNECTION_CHANGED_REJOIN_SUCCESS = 15,
  /**
   * 16: The connection between the SDK and the server is lost.
   */
  CONNECTION_CHANGED_LOST = 16,
  /**
   * 17: The change of connection state is caused by echo test.
   */
  CONNECTION_CHANGED_ECHO_TEST = 17,
  /**
   * 18: The local IP Address is changed by user.
   */
  CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED_BY_USER = 18,
  /**
   * 19: The connection is failed due to join the same channel on another device with the same uid.
   */
  CONNECTION_CHANGED_SAME_UID_LOGIN = 19,
  /**
   * 20: The connection is failed due to too many broadcasters in the channel.
   */
  CONNECTION_CHANGED_TOO_MANY_BROADCASTERS = 20,

  /**
   * 21: The connection is failed due to license validation failure.
   */
  CONNECTION_CHANGED_LICENSE_VALIDATION_FAILURE = 21,
  /*
   * 22: The connection is failed due to certification verify failure.
   */
  CONNECTION_CHANGED_CERTIFICATION_VERYFY_FAILURE = 22,
  /**
   * 23: The connection is failed due to the lack of granting permission to the stream channel.
   */
  CONNECTION_CHANGED_STREAM_CHANNEL_NOT_AVAILABLE = 23,
  /**
   * 24: The connection is failed due to join channel with an inconsistent appid.
   */
  CONNECTION_CHANGED_INCONSISTENT_APPID = 24,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_25_ENTRIES(EUABT_CONNECTION_CHANGED_REASON_TYPE, agora::rtc::CONNECTION_CHANGED_REASON_TYPE,
	CONNECTION_CHANGED_CONNECTING,
	CONNECTION_CHANGED_JOIN_SUCCESS,
	CONNECTION_CHANGED_INTERRUPTED,
	CONNECTION_CHANGED_BANNED_BY_SERVER,
	CONNECTION_CHANGED_JOIN_FAILED,
	CONNECTION_CHANGED_LEAVE_CHANNEL,
	CONNECTION_CHANGED_INVALID_APP_ID,
	CONNECTION_CHANGED_INVALID_CHANNEL_NAME,
	CONNECTION_CHANGED_INVALID_TOKEN,
	CONNECTION_CHANGED_TOKEN_EXPIRED,
	CONNECTION_CHANGED_REJECTED_BY_SERVER,
	CONNECTION_CHANGED_SETTING_PROXY_SERVER,
	CONNECTION_CHANGED_RENEW_TOKEN,
	CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED,
	CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT,
	CONNECTION_CHANGED_REJOIN_SUCCESS,
	CONNECTION_CHANGED_LOST,
	CONNECTION_CHANGED_ECHO_TEST,
	CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED_BY_USER,
	CONNECTION_CHANGED_SAME_UID_LOGIN,
	CONNECTION_CHANGED_TOO_MANY_BROADCASTERS,
	CONNECTION_CHANGED_LICENSE_VALIDATION_FAILURE,
	CONNECTION_CHANGED_CERTIFICATION_VERYFY_FAILURE,
	CONNECTION_CHANGED_STREAM_CHANNEL_NOT_AVAILABLE,
	CONNECTION_CHANGED_INCONSISTENT_APPID
)


/**
 * The reason of notifying the user of a message.
 */
UENUM(BlueprintType)
enum class EUABT_WLACC_MESSAGE_REASON : uint8 {
  /**
   * WIFI signal is weak.
   */
  WLACC_MESSAGE_REASON_WEAK_SIGNAL = 0,
  /**
   * Channel congestion.
   */
  WLACC_MESSAGE_REASON_CHANNEL_CONGESTION = 1,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_WLACC_MESSAGE_REASON, agora::rtc::WLACC_MESSAGE_REASON,
	WLACC_MESSAGE_REASON_WEAK_SIGNAL,
	WLACC_MESSAGE_REASON_CHANNEL_CONGESTION
)


/**
 * Suggest an action for the user.
 */
UENUM(BlueprintType)
enum class EUABT_WLACC_SUGGEST_ACTION : uint8 {
  /**
   * Please get close to AP.
   */
  WLACC_SUGGEST_ACTION_CLOSE_TO_WIFI = 0,
  /**
   * The user is advised to connect to the prompted SSID.
   */
  WLACC_SUGGEST_ACTION_CONNECT_SSID = 1,
  /**
   * The user is advised to check whether the AP supports 5G band and enable 5G band (the aciton
   * link is attached), or purchases an AP that supports 5G. AP does not support 5G band.
   */
  WLACC_SUGGEST_ACTION_CHECK_5G = 2,
  /**
   * The user is advised to change the SSID of the 2.4G or 5G band (the aciton link is attached).
   * The SSID of the 2.4G band AP is the same as that of the 5G band.
   */
  WLACC_SUGGEST_ACTION_MODIFY_SSID = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_WLACC_SUGGEST_ACTION, agora::rtc::WLACC_SUGGEST_ACTION,
	WLACC_SUGGEST_ACTION_CLOSE_TO_WIFI,
	WLACC_SUGGEST_ACTION_CONNECT_SSID,
	WLACC_SUGGEST_ACTION_CHECK_5G,
	WLACC_SUGGEST_ACTION_MODIFY_SSID
)


/** Encryption error type.
 */
UENUM(BlueprintType)
enum class EUABT_ENCRYPTION_ERROR_TYPE : uint8 {
  /**
   * 0: Internal reason.
   */
  ENCRYPTION_ERROR_INTERNAL_FAILURE = 0,
  /**
   * 1: MediaStream decryption errors. Ensure that the receiver and the sender use the same
   * encryption mode and key.
   */
  ENCRYPTION_ERROR_DECRYPTION_FAILURE = 1,
  /**
   * 2: MediaStream encryption errors.
   */
  ENCRYPTION_ERROR_ENCRYPTION_FAILURE = 2,
  /**
   * 3: DataStream decryption errors. Ensure that the receiver and the sender use the same
   * encryption mode and key.
   */
  ENCRYPTION_ERROR_DATASTREAM_DECRYPTION_FAILURE = 3,
  /**
   * 4: DataStream encryption errors.
   */
  ENCRYPTION_ERROR_DATASTREAM_ENCRYPTION_FAILURE = 4,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_ENCRYPTION_ERROR_TYPE, agora::rtc::ENCRYPTION_ERROR_TYPE,
	ENCRYPTION_ERROR_INTERNAL_FAILURE,
	ENCRYPTION_ERROR_DECRYPTION_FAILURE,
	ENCRYPTION_ERROR_ENCRYPTION_FAILURE,
	ENCRYPTION_ERROR_DATASTREAM_DECRYPTION_FAILURE,
	ENCRYPTION_ERROR_DATASTREAM_ENCRYPTION_FAILURE
)


/** The type of the device permission.
 */
UENUM(BlueprintType)
enum class EUABT_PERMISSION_TYPE : uint8 {
  /**
   * 0: Permission for the audio capture device.
   */
  RECORD_AUDIO = 0,
  /**
   * 1: Permission for the camera.
   */
  CAMERA = 1,

  SCREEN_CAPTURE = 2,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_PERMISSION_TYPE, agora::rtc::PERMISSION_TYPE,
	RECORD_AUDIO,
	CAMERA,
	SCREEN_CAPTURE
)


/**
 * The tracing event of media rendering.
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_TRACE_EVENT : uint8 {
  /**
   * 0: The media frame has been rendered.
   */
  MEDIA_TRACE_EVENT_VIDEO_RENDERED = 0,
  /**
   * 1: The media frame has been decoded.
   */
  MEDIA_TRACE_EVENT_VIDEO_DECODED,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_MEDIA_TRACE_EVENT, agora::rtc::MEDIA_TRACE_EVENT,
	MEDIA_TRACE_EVENT_VIDEO_RENDERED,
	MEDIA_TRACE_EVENT_VIDEO_DECODED
)


UENUM(BlueprintType)
enum class EUABT_UPLOAD_ERROR_REASON : uint8 {
  UPLOAD_SUCCESS = 0,
  UPLOAD_NET_ERROR = 1,
  UPLOAD_SERVER_ERROR = 2,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_UPLOAD_ERROR_REASON, agora::rtc::UPLOAD_ERROR_REASON,
	UPLOAD_SUCCESS,
	UPLOAD_NET_ERROR,
	UPLOAD_SERVER_ERROR
)

/**
 * The subscribing state.
 */
UENUM(BlueprintType)
enum class EUABT_STREAM_SUBSCRIBE_STATE : uint8 {
  /**
   * 0: The initial subscribing state after joining the channel.
   */
  SUB_STATE_IDLE = 0,
  /**
   * 1: Fails to subscribe to the remote stream. Possible reasons:
   * - The remote user:
   *   - Calls `muteLocalAudioStream(true)` or `muteLocalVideoStream(true)` to stop sending local
   * media stream.
   *   - Calls `disableAudio` or `disableVideo `to disable the local audio or video module.
   *   - Calls `enableLocalAudio(false)` or `enableLocalVideo(false)` to disable the local audio or
   * video capture.
   *   - The role of the remote user is audience.
   * - The local user calls the following methods to stop receiving remote streams:
   *   - Calls `muteRemoteAudioStream(true)`, `muteAllRemoteAudioStreams(true)` to stop receiving the remote audio streams.
   *   - Calls `muteRemoteVideoStream(true)`, `muteAllRemoteVideoStreams(true)` to stop receiving the remote video streams.
   */
  SUB_STATE_NO_SUBSCRIBED = 1,
  /**
   * 2: Subscribing.
   */
  SUB_STATE_SUBSCRIBING = 2,
  /**
   * 3: Subscribes to and receives the remote stream successfully.
   */
  SUB_STATE_SUBSCRIBED = 3
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_STREAM_SUBSCRIBE_STATE, agora::rtc::STREAM_SUBSCRIBE_STATE,
	SUB_STATE_IDLE,
	SUB_STATE_NO_SUBSCRIBED,
	SUB_STATE_SUBSCRIBING,
	SUB_STATE_SUBSCRIBED
)


/**
 * The publishing state.
 */
UENUM(BlueprintType)
enum class EUABT_STREAM_PUBLISH_STATE : uint8 {
  /**
   * 0: The initial publishing state after joining the channel.
   */
  PUB_STATE_IDLE = 0,
  /**
   * 1: Fails to publish the local stream. Possible reasons:
   * - The local user calls `muteLocalAudioStream(true)` or `muteLocalVideoStream(true)` to stop
   * sending the local media stream.
   * - The local user calls `disableAudio` or `disableVideo` to disable the local audio or video
   * module.
   * - The local user calls `enableLocalAudio(false)` or `enableLocalVideo(false)` to disable the
   * local audio or video capture.
   * - The role of the local user is audience.
   */
  PUB_STATE_NO_PUBLISHED = 1,
  /**
   * 2: Publishing.
   */
  PUB_STATE_PUBLISHING = 2,
  /**
   * 3: Publishes successfully.
   */
  PUB_STATE_PUBLISHED = 3
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_STREAM_PUBLISH_STATE, agora::rtc::STREAM_PUBLISH_STATE,
	PUB_STATE_IDLE,
	PUB_STATE_NO_PUBLISHED,
	PUB_STATE_PUBLISHING,
	PUB_STATE_PUBLISHED
)


// The connection state of media streaming
// GENERATED_JAVA_ENUM_PACKAGE: io.agora.streaming
UENUM(BlueprintType)
enum class EUABT_DIRECT_CDN_STREAMING_STATE : uint8 {

  DIRECT_CDN_STREAMING_STATE_IDLE = 0,

  DIRECT_CDN_STREAMING_STATE_RUNNING = 1,

  DIRECT_CDN_STREAMING_STATE_STOPPED = 2,

  DIRECT_CDN_STREAMING_STATE_FAILED = 3,

  DIRECT_CDN_STREAMING_STATE_RECOVERING = 4,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_DIRECT_CDN_STREAMING_STATE, agora::rtc::DIRECT_CDN_STREAMING_STATE,
	DIRECT_CDN_STREAMING_STATE_IDLE,
	DIRECT_CDN_STREAMING_STATE_RUNNING,
	DIRECT_CDN_STREAMING_STATE_STOPPED,
	DIRECT_CDN_STREAMING_STATE_FAILED,
	DIRECT_CDN_STREAMING_STATE_RECOVERING
)


// The reason codes for media streaming
// GENERATED_JAVA_ENUM_PACKAGE: io.agora.streaming
UENUM(BlueprintType)
enum class EUABT_DIRECT_CDN_STREAMING_REASON : uint8 {
  // No error occurs.
  DIRECT_CDN_STREAMING_REASON_OK = 0,
  // A general error occurs (no specified reason).
  DIRECT_CDN_STREAMING_REASON_FAILED = 1,
  // Audio publication error.
  DIRECT_CDN_STREAMING_REASON_AUDIO_PUBLICATION = 2,
  // Video publication error.
  DIRECT_CDN_STREAMING_REASON_VIDEO_PUBLICATION = 3,

  DIRECT_CDN_STREAMING_REASON_NET_CONNECT = 4,
  // Already exist stream name.
  DIRECT_CDN_STREAMING_REASON_BAD_NAME = 5,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_DIRECT_CDN_STREAMING_REASON, agora::rtc::DIRECT_CDN_STREAMING_REASON,
	DIRECT_CDN_STREAMING_REASON_OK,
	DIRECT_CDN_STREAMING_REASON_FAILED,
	DIRECT_CDN_STREAMING_REASON_AUDIO_PUBLICATION,
	DIRECT_CDN_STREAMING_REASON_VIDEO_PUBLICATION,
	DIRECT_CDN_STREAMING_REASON_NET_CONNECT,
	DIRECT_CDN_STREAMING_REASON_BAD_NAME
)


/**
 * Reasons for a user being offline.
 */
UENUM(BlueprintType)
enum class EUABT_USER_OFFLINE_REASON_TYPE : uint8 {
  /**
   * 0: The user leaves the current channel.
   */
  USER_OFFLINE_QUIT = 0,
  /**
   * 1: The SDK times out and the user drops offline because no data packet was received within a
   * certain period of time. If a user quits the call and the message is not passed to the SDK (due
   * to an unreliable channel), the SDK assumes that the user drops offline.
   */
  USER_OFFLINE_DROPPED = 1,
  /**
   * 2: The user switches the client role from the host to the audience.
   */
  USER_OFFLINE_BECOME_AUDIENCE = 2,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_USER_OFFLINE_REASON_TYPE, agora::rtc::USER_OFFLINE_REASON_TYPE,
	USER_OFFLINE_QUIT,
	USER_OFFLINE_DROPPED,
	USER_OFFLINE_BECOME_AUDIENCE
)


/**
 * @brief The playback state.
 *
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_PLAYER_STATE : uint8 {
  /** Default state.
   */
  PLAYER_STATE_IDLE = 0,
  /** Opening the media file.
   */
  PLAYER_STATE_OPENING,
  /** The media file is opened successfully.
   */
  PLAYER_STATE_OPEN_COMPLETED,
  /** Playing the media file.
   */
  PLAYER_STATE_PLAYING,
  /** The playback is paused.
   */
  PLAYER_STATE_PAUSED,
  /** The playback is completed.
   */
  PLAYER_STATE_PLAYBACK_COMPLETED,
  /** All loops are completed.
   */
  PLAYER_STATE_PLAYBACK_ALL_LOOPS_COMPLETED,
  /** The playback is stopped.
   */
  PLAYER_STATE_STOPPED,
  /** Player pausing (internal)
   */
  PLAYER_STATE_PAUSING_INTERNAL = 50,
  /** Player stopping (internal)
   */
  PLAYER_STATE_STOPPING_INTERNAL,
  /** Player seeking state (internal)
   */
  PLAYER_STATE_SEEKING_INTERNAL,
  /** Player getting state (internal)
   */
  PLAYER_STATE_GETTING_INTERNAL,
  /** None state for state machine (internal)
   */
  PLAYER_STATE_NONE_INTERNAL,
  /** Do nothing state for state machine (internal)
   */
  PLAYER_STATE_DO_NOTHING_INTERNAL,
  /** Player set track state (internal)
   */
  PLAYER_STATE_SET_TRACK_INTERNAL,
  /** The playback fails.
   */
  PLAYER_STATE_FAILED = 100,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_16_ENTRIES(EUABT_MEDIA_PLAYER_STATE, agora::media::base::MEDIA_PLAYER_STATE,
	PLAYER_STATE_IDLE,

	PLAYER_STATE_OPENING,
	PLAYER_STATE_OPEN_COMPLETED,
	PLAYER_STATE_PLAYING,
	PLAYER_STATE_PAUSED,
	PLAYER_STATE_PLAYBACK_COMPLETED,

	PLAYER_STATE_PLAYBACK_ALL_LOOPS_COMPLETED,
	PLAYER_STATE_STOPPED,
	PLAYER_STATE_PAUSING_INTERNAL,
	PLAYER_STATE_STOPPING_INTERNAL,
	PLAYER_STATE_SEEKING_INTERNAL,

	PLAYER_STATE_GETTING_INTERNAL,
	PLAYER_STATE_NONE_INTERNAL,
	PLAYER_STATE_DO_NOTHING_INTERNAL,
	PLAYER_STATE_SET_TRACK_INTERNAL,
	PLAYER_STATE_FAILED
)




/**
 * The channel profile.
 */
UENUM(BlueprintType)
enum class EUABT_CHANNEL_PROFILE_TYPE : uint8 {
  /**
   * 0: Communication.
   *
   * This profile prioritizes smoothness and applies to the one-to-one scenario.
   */
  CHANNEL_PROFILE_COMMUNICATION = 0,
  /**
   * 1: (Default) Live Broadcast.
   *
   * This profile prioritizes supporting a large audience in a live broadcast channel.
   */
  CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
  /**
   * 2: Gaming.
   * @deprecated This profile is deprecated.
   */
  CHANNEL_PROFILE_GAME  = 2,
  /**
   * 3: Cloud Gaming.
   *
   * @deprecated This profile is deprecated.
   */
  CHANNEL_PROFILE_CLOUD_GAMING  = 3,

  /**
   * 4: Communication 1v1.
   * @deprecated This profile is deprecated.
   */
  CHANNEL_PROFILE_COMMUNICATION_1v1  = 4,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_CHANNEL_PROFILE_TYPE, agora::CHANNEL_PROFILE_TYPE,
	CHANNEL_PROFILE_COMMUNICATION,
	CHANNEL_PROFILE_LIVE_BROADCASTING,
	CHANNEL_PROFILE_GAME,
	CHANNEL_PROFILE_CLOUD_GAMING,
	CHANNEL_PROFILE_COMMUNICATION_1v1
)


/**
 * The external video source type.
 */
UENUM(BlueprintType)
enum class EUABT_EXTERNAL_VIDEO_SOURCE_TYPE : uint8 {
  /**
   * 0: non-encoded video frame.
   */
  VIDEO_FRAME = 0,
  /**
   * 1: encoded video frame.
   */
  ENCODED_VIDEO_FRAME,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_EXTERNAL_VIDEO_SOURCE_TYPE, agora::media::EXTERNAL_VIDEO_SOURCE_TYPE,
	VIDEO_FRAME,
	ENCODED_VIDEO_FRAME
)


/**
 * The CC (Congestion Control) mode options.
 */
UENUM(BlueprintType)
enum class EUABT_TCcMode :uint8 {
  /**
   * Enable CC mode.
   */
  CC_ENABLED,
  /**
   * Disable CC mode.
   */
  CC_DISABLED,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_TCcMode, agora::rtc::TCcMode,
	CC_ENABLED,
	CC_DISABLED
)


/**
 * Video mirror mode types.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_MIRROR_MODE_TYPE : uint8 {
  /**
   * 0: The mirror mode determined by the SDK.
   */
  VIDEO_MIRROR_MODE_AUTO = 0,
  /**
   * 1: Enable the mirror mode.
   */
  VIDEO_MIRROR_MODE_ENABLED = 1,
  /**
   * 2: Disable the mirror mode.
   */
  VIDEO_MIRROR_MODE_DISABLED = 2,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_VIDEO_MIRROR_MODE_TYPE, agora::rtc::VIDEO_MIRROR_MODE_TYPE,
	VIDEO_MIRROR_MODE_AUTO,
	VIDEO_MIRROR_MODE_ENABLED,
	VIDEO_MIRROR_MODE_DISABLED
)


/**
 * The mode of setting up video views.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_VIEW_SETUP_MODE : uint8 {
  /**
   * 0: replace one view
   */
  VIDEO_VIEW_SETUP_REPLACE = 0,
  /**
   * 1: add one view
   */
  VIDEO_VIEW_SETUP_ADD = 1,
  /**
   * 2: remove one view
   */
  VIDEO_VIEW_SETUP_REMOVE = 2,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_VIDEO_VIEW_SETUP_MODE, agora::rtc::VIDEO_VIEW_SETUP_MODE,
	VIDEO_VIEW_SETUP_REPLACE,
	VIDEO_VIEW_SETUP_ADD,
	VIDEO_VIEW_SETUP_REMOVE
)


/**
 * Audio profile types.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_PROFILE_TYPE : uint8 {
  /**
   * 0: The default audio profile.
   * - For the Communication profile:
   *   - Windows: A sample rate of 16 kHz, audio encoding, mono, and a bitrate of up to 16 Kbps.
   *   - Android/macOS/iOS: A sample rate of 32 kHz, audio encoding, mono, and a bitrate of up to 18
   * Kbps. of up to 16 Kbps.
   * - For the Live-broadcast profile: A sample rate of 48 kHz, music encoding, mono, and a bitrate
   * of up to 64 Kbps.
   */
  AUDIO_PROFILE_DEFAULT = 0,
  /**
   * 1: A sample rate of 32 kHz, audio encoding, mono, and a bitrate of up to 18 Kbps.
   */
  AUDIO_PROFILE_SPEECH_STANDARD = 1,
  /**
   * 2: A sample rate of 48 kHz, music encoding, mono, and a bitrate of up to 64 Kbps.
   */
  AUDIO_PROFILE_MUSIC_STANDARD = 2,
  /**
   * 3: A sample rate of 48 kHz, music encoding, stereo, and a bitrate of up to 80 Kbps.
   *
   * To implement stereo audio, you also need to call `setAdvancedAudioOptions` and set
   * `audioProcessingChannels` to `AUDIO_PROCESSING_STEREO` in `AdvancedAudioOptions`.
   */
  AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3,
  /**
   * 4: A sample rate of 48 kHz, music encoding, mono, and a bitrate of up to 96 Kbps.
   */
  AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4,
  /**
   * 5: A sample rate of 48 kHz, music encoding, stereo, and a bitrate of up to 128 Kbps.
   *
   * To implement stereo audio, you also need to call `setAdvancedAudioOptions` and set
   * `audioProcessingChannels` to `AUDIO_PROCESSING_STEREO` in `AdvancedAudioOptions`.
   */
  AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5,
  /**
   * 6: A sample rate of 16 kHz, audio encoding, mono, and Acoustic Echo Cancellation (AES) enabled.
   */
  AUDIO_PROFILE_IOT = 6,
  AUDIO_PROFILE_NUM = 7
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_8_ENTRIES(EUABT_AUDIO_PROFILE_TYPE, agora::rtc::AUDIO_PROFILE_TYPE,
	AUDIO_PROFILE_DEFAULT,
	AUDIO_PROFILE_SPEECH_STANDARD,
	AUDIO_PROFILE_MUSIC_STANDARD,
	AUDIO_PROFILE_MUSIC_STANDARD_STEREO,
	AUDIO_PROFILE_MUSIC_HIGH_QUALITY,
	AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO,
	AUDIO_PROFILE_IOT,
	AUDIO_PROFILE_NUM
)



/**
 * The audio scenario.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_SCENARIO_TYPE : uint8 {
  /**
   * 0: Automatic scenario, where the SDK chooses the appropriate audio quality according to the
   * user role and audio route.
   */
  AUDIO_SCENARIO_DEFAULT = 0,
  /**
   * 3: (Recommended) The live gaming scenario, which needs to enable gaming
   * audio effects in the speaker. Choose this scenario to achieve high-fidelity
   * music playback.
   */
  AUDIO_SCENARIO_GAME_STREAMING = 3,
  /**
   * 5: The chatroom scenario, which needs to keep recording when setClientRole to audience.
   * Normally, app developer can also use mute api to achieve the same result,
   * and we implement this 'non-orthogonal' behavior only to make API backward compatible.
   */
  AUDIO_SCENARIO_CHATROOM = 5,
  /**
   * 7: Real-time chorus scenario, where users have good network conditions and require ultra-low
   * latency.
   */
  AUDIO_SCENARIO_CHORUS = 7,
  /**
   * 8: Meeting
   */
  AUDIO_SCENARIO_MEETING = 8,
  /**
   * 9: The number of enumerations.
   */
  AUDIO_SCENARIO_NUM = 9,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_AUDIO_SCENARIO_TYPE, agora::rtc::AUDIO_SCENARIO_TYPE,
	AUDIO_SCENARIO_DEFAULT,
	AUDIO_SCENARIO_GAME_STREAMING,
	AUDIO_SCENARIO_CHATROOM,
	AUDIO_SCENARIO_CHORUS,
	AUDIO_SCENARIO_MEETING,
	AUDIO_SCENARIO_NUM
)


/**
 * Supported logging severities of SDK
 */
UENUM(BlueprintType)
enum class EUABT_LOG_LEVEL : uint8 {
  LOG_LEVEL_NONE = 0x0000,
  LOG_LEVEL_INFO = 0x0001,
  LOG_LEVEL_WARN = 0x0002,
  LOG_LEVEL_ERROR = 0x0004,
  LOG_LEVEL_FATAL = 0x0008,
  LOG_LEVEL_API_CALL = 0x0010,
  LOG_LEVEL_DEBUG = 0x0020,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_7_ENTRIES(EUABT_LOG_LEVEL, agora::commons::LOG_LEVEL,
	LOG_LEVEL_NONE,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_FATAL,
	LOG_LEVEL_API_CALL,
	LOG_LEVEL_DEBUG
)


/**
 * The camera direction.
 */
UENUM(BlueprintType)
enum class EUABT_CAMERA_DIRECTION :uint8 {
  /** The rear camera. */
  CAMERA_REAR = 0,
  /** The front camera. */
  CAMERA_FRONT = 1,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_CAMERA_DIRECTION, agora::rtc::CAMERA_DIRECTION,
	CAMERA_REAR,
	CAMERA_FRONT
)



/**
 * Camera focal length type.
 */
UENUM(BlueprintType)
enum class EUABT_CAMERA_FOCAL_LENGTH_TYPE :uint8 {
	/**
	 * By default, there are no wide-angle and ultra-wide-angle properties.
	 */
	CAMERA_FOCAL_LENGTH_DEFAULT = 0,
	/**
	 * Lens with focal length from 24mm to 35mm.
	 */
	CAMERA_FOCAL_LENGTH_WIDE_ANGLE = 1,
	/**
	 * Lens with focal length of less than 24mm.
	 */
	CAMERA_FOCAL_LENGTH_ULTRA_WIDE = 2,
	/**
	 * Telephoto lens.
	 */
	CAMERA_FOCAL_LENGTH_TELEPHOTO = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_CAMERA_FOCAL_LENGTH_TYPE, agora::rtc::CAMERA_FOCAL_LENGTH_TYPE,
	CAMERA_FOCAL_LENGTH_DEFAULT,
	CAMERA_FOCAL_LENGTH_WIDE_ANGLE,
	CAMERA_FOCAL_LENGTH_ULTRA_WIDE,
	CAMERA_FOCAL_LENGTH_TELEPHOTO
)




/**
 * Video output orientation modes.
 */
UENUM(BlueprintType)
enum class EUABT_ORIENTATION_MODE : uint8 {
  /**
   * 0: The output video always follows the orientation of the captured video. The receiver takes
   * the rotational information passed on from the video encoder. This mode applies to scenarios
   * where video orientation can be adjusted on the receiver:
   * - If the captured video is in landscape mode, the output video is in landscape mode.
   * - If the captured video is in portrait mode, the output video is in portrait mode.
   */
  ORIENTATION_MODE_ADAPTIVE = 0,
  /**
   * 1: Landscape mode. In this mode, the SDK always outputs videos in landscape (horizontal) mode.
   * If the captured video is in portrait mode, the video encoder crops it to fit the output.
   * Applies to situations where the receiving end cannot process the rotational information. For
   * example, CDN live streaming.
   */
  ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
  /**
   * 2: Portrait mode. In this mode, the SDK always outputs video in portrait (portrait) mode. If
   * the captured video is in landscape mode, the video encoder crops it to fit the output. Applies
   * to situations where the receiving end cannot process the rotational information. For example,
   * CDN live streaming.
   */
  ORIENTATION_MODE_FIXED_PORTRAIT = 2,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_ORIENTATION_MODE, agora::rtc::ORIENTATION_MODE,
	ORIENTATION_MODE_ADAPTIVE,
	ORIENTATION_MODE_FIXED_LANDSCAPE,
	ORIENTATION_MODE_FIXED_PORTRAIT)




  /** The contrast level.
   */
UENUM(BlueprintType)
enum class EUABT_LIGHTENING_CONTRAST_LEVEL : uint8 {
    /** Low contrast level. */
    LIGHTENING_CONTRAST_LOW = 0,
    /** (Default) Normal contrast level. */
    LIGHTENING_CONTRAST_NORMAL = 1,
    /** High contrast level. */
    LIGHTENING_CONTRAST_HIGH = 2,
  };


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_LIGHTENING_CONTRAST_LEVEL, agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL,
	LIGHTENING_CONTRAST_LOW,
	LIGHTENING_CONTRAST_NORMAL,
	LIGHTENING_CONTRAST_HIGH
)


/**
 * The type of media device.
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_SOURCE_TYPE : uint8 {
  /**
   * 0: The audio playback device.
   */
  AUDIO_PLAYOUT_SOURCE = 0,
  /**
   * 1: Microphone.
   */
  AUDIO_RECORDING_SOURCE = 1,
  /**
   * 2: Video captured by primary camera.
   */
  PRIMARY_CAMERA_SOURCE = 2,
  /**
   * 3: Video captured by secondary camera.
   */
  SECONDARY_CAMERA_SOURCE = 3,
  /**
   * 4: Video captured by primary screen capturer.
   */
  PRIMARY_SCREEN_SOURCE = 4,
  /**
   * 5: Video captured by secondary screen capturer.
   */
  SECONDARY_SCREEN_SOURCE = 5,
  /**
   * 6: Video captured by custom video source.
   */
  CUSTOM_VIDEO_SOURCE = 6,
  /**
   * 7: Video for media player sharing.
   */
  MEDIA_PLAYER_SOURCE = 7,
  /**
   * 8: Video for png image.
   */
  RTC_IMAGE_PNG_SOURCE = 8,
  /**
   * 9: Video for jpeg image.
   */
  RTC_IMAGE_JPEG_SOURCE = 9,
  /**
   * 10: Video for gif image.
   */
  RTC_IMAGE_GIF_SOURCE = 10,
  /**
   * 11: Remote video received from network.
   */
  REMOTE_VIDEO_SOURCE = 11,
  /**
   * 12: Video for transcoded.
   */
  TRANSCODED_VIDEO_SOURCE = 12,
  /**
   * 13: Video for voice drive.
   */
  SPEECH_DRIVEN_VIDEO_SOURCE = 13,
  /**
   * 100: Internal Usage only.
   */
  UNKNOWN_MEDIA_SOURCE = 100
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_15_ENTRIES(EUABT_MEDIA_SOURCE_TYPE, agora::media::MEDIA_SOURCE_TYPE,
	AUDIO_PLAYOUT_SOURCE,
	AUDIO_RECORDING_SOURCE,
	PRIMARY_CAMERA_SOURCE,
	SECONDARY_CAMERA_SOURCE,
	PRIMARY_SCREEN_SOURCE,
	SECONDARY_SCREEN_SOURCE,
	CUSTOM_VIDEO_SOURCE,
	MEDIA_PLAYER_SOURCE,
	RTC_IMAGE_PNG_SOURCE,
	RTC_IMAGE_JPEG_SOURCE,
	RTC_IMAGE_GIF_SOURCE,
	REMOTE_VIDEO_SOURCE,
	TRANSCODED_VIDEO_SOURCE,
	SPEECH_DRIVEN_VIDEO_SOURCE,
	UNKNOWN_MEDIA_SOURCE
)






/**
 * The low-light enhancement mode.
 */
UENUM(BlueprintType)
enum class EUABT_LOW_LIGHT_ENHANCE_MODE : uint8 {
/** 0: (Default) Automatic mode. The SDK automatically enables or disables the low-light
	 enhancement feature according to the ambient light to compensate for the lighting level or
	prevent overexposure, as necessary. */
LOW_LIGHT_ENHANCE_AUTO = 0,
/** Manual mode. Users need to enable or disable the low-light enhancement feature manually. */
LOW_LIGHT_ENHANCE_MANUAL = 1,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_LOW_LIGHT_ENHANCE_MODE, agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_MODE,
	LOW_LIGHT_ENHANCE_AUTO,
	LOW_LIGHT_ENHANCE_MANUAL
)


/**
 * The low-light enhancement level.
 */
UENUM(BlueprintType)
enum class EUABT_LOW_LIGHT_ENHANCE_LEVEL : uint8 {
/**
 * 0: (Default) Promotes video quality during low-light enhancement. It processes the
 * brightness, details, and noise of the video image. The performance consumption is moderate,
 * the processing speed is moderate, and the overall video quality is optimal.
 */
LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY = 0,
/**
 * Promotes performance during low-light enhancement. It processes the brightness and details of
 * the video image. The processing speed is faster.
 */
LOW_LIGHT_ENHANCE_LEVEL_FAST = 1,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_LOW_LIGHT_ENHANCE_LEVEL, agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_LEVEL,
	LOW_LIGHT_ENHANCE_LEVEL_HIGH_QUALITY,
	LOW_LIGHT_ENHANCE_LEVEL_FAST
)



/** The video noise reduction mode.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_DENOISER_MODE : uint8 {
	/** 0: (Default) Automatic mode. The SDK automatically enables or disables the video noise
		 reduction feature according to the ambient light. */
	VIDEO_DENOISER_AUTO = 0,
	/** Manual mode. Users need to enable or disable the video noise reduction feature manually. */
	VIDEO_DENOISER_MANUAL = 1,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_VIDEO_DENOISER_MODE, agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_MODE,
	VIDEO_DENOISER_AUTO,
	VIDEO_DENOISER_MANUAL
)


/**
 * The video noise reduction level.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_DENOISER_LEVEL  : uint8 {
	/**
	 * 0: (Default) Promotes video quality during video noise reduction. `HIGH_QUALITY` balances
	 * performance consumption and video noise reduction quality. The performance consumption is
	 * moderate, the video noise reduction speed is moderate, and the overall video quality is
	 * optimal.
	 */
	VIDEO_DENOISER_LEVEL_HIGH_QUALITY = 0,
	/**
	 * Promotes reducing performance consumption during video noise reduction. `FAST` prioritizes
	 * reducing performance consumption over video noise reduction quality. The performance
	 * consumption is lower, and the video noise reduction speed is faster. To avoid a noticeable
	 * shadowing effect (shadows trailing behind moving objects) in the processed video, Agora
	 * recommends that you use `FAST` when the camera is fixed.
	 */
	VIDEO_DENOISER_LEVEL_FAST = 1,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_VIDEO_DENOISER_LEVEL, agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_LEVEL,
	VIDEO_DENOISER_LEVEL_HIGH_QUALITY,
	VIDEO_DENOISER_LEVEL_FAST
)



/** The type of the custom background source.
 */
UENUM(BlueprintType)
enum class EUABT_BACKGROUND_SOURCE_TYPE :uint8 {
    /**
     * 0: Enable segementation with the captured video frame without replacing the background.
     */
    BACKGROUND_NONE = 0,
    /**
     * 1: (Default) The background source is a solid color.
     */
    BACKGROUND_COLOR = 1,
    /**
     * The background source is a file in PNG or JPG format.
     */
    BACKGROUND_IMG = 2,
    /**
     * The background source is the blurred original video frame.
     * */
    BACKGROUND_BLUR = 3,
    /**
     * The background source is a file in MP4, AVI, MKV, FLV format.
     * */
    BACKGROUND_VIDEO = 4,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_BACKGROUND_SOURCE_TYPE, agora::rtc::VirtualBackgroundSource::BACKGROUND_SOURCE_TYPE,
	BACKGROUND_NONE,
	BACKGROUND_COLOR,
	BACKGROUND_IMG,
	BACKGROUND_BLUR,
	BACKGROUND_VIDEO
)



/**
 * The video application scenario type.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_APPLICATION_SCENARIO_TYPE : uint8 {
  /**
   * 0: Default Scenario.
   */
  APPLICATION_SCENARIO_GENERAL = 0,
  /**
   * 1: Meeting Scenario. This scenario is the best QoE practice of meeting application.
   */
  APPLICATION_SCENARIO_MEETING = 1,
  /**
   * 2: Video Call Scenario. This scenario is used to optimize the video experience in video application, like 1v1 video call.
   */
  APPLICATION_SCENARIO_1V1 = 2,
  /**
   * 3: Live Show Scenario. This scenario is used to optimize the video experience in video live show.
   */
  APPLICATION_SCENARIO_LIVESHOW = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_VIDEO_APPLICATION_SCENARIO_TYPE, agora::rtc::VIDEO_APPLICATION_SCENARIO_TYPE,
	APPLICATION_SCENARIO_GENERAL,
	APPLICATION_SCENARIO_MEETING,
	APPLICATION_SCENARIO_1V1,
	APPLICATION_SCENARIO_LIVESHOW
)


/**
 * Audio recording quality.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_RECORDING_QUALITY_TYPE : uint8 {
  /**
   * 0: Low quality. The sample rate is 32 kHz, and the file size is around 1.2 MB after 10 minutes
   * of recording.
   */
  AUDIO_RECORDING_QUALITY_LOW = 0,
  /**
   * 1: Medium quality. The sample rate is 32 kHz, and the file size is around 2 MB after 10 minutes
   * of recording.
   */
  AUDIO_RECORDING_QUALITY_MEDIUM = 1,
  /**
   * 2: High quality. The sample rate is 32 kHz, and the file size is around 3.75 MB after 10
   * minutes of recording.
   */
  AUDIO_RECORDING_QUALITY_HIGH = 2,
  /**
   * 3: Ultra high audio recording quality.
   */
  AUDIO_RECORDING_QUALITY_ULTRA_HIGH = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_AUDIO_RECORDING_QUALITY_TYPE, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE,
	AUDIO_RECORDING_QUALITY_LOW,
	AUDIO_RECORDING_QUALITY_MEDIUM,
	AUDIO_RECORDING_QUALITY_HIGH,
	AUDIO_RECORDING_QUALITY_ULTRA_HIGH
)



/** dual-mono music output mode
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_MIXING_DUAL_MONO_MODE : uint8 {
  /* 0: Original mode */
  AUDIO_MIXING_DUAL_MONO_AUTO = 0,
  /* 1: Left channel mode */
  AUDIO_MIXING_DUAL_MONO_L = 1,
  /* 2: Right channel mode */
  AUDIO_MIXING_DUAL_MONO_R = 2,
  /* 3: Mixed channel mode */
  AUDIO_MIXING_DUAL_MONO_MIX = 3
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_AUDIO_MIXING_DUAL_MONO_MODE, agora::media::AUDIO_MIXING_DUAL_MONO_MODE,
	AUDIO_MIXING_DUAL_MONO_AUTO,
	AUDIO_MIXING_DUAL_MONO_L,
	AUDIO_MIXING_DUAL_MONO_R,
	AUDIO_MIXING_DUAL_MONO_MIX
)


/**
 * The audio equalization band frequency.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_EQUALIZATION_BAND_FREQUENCY : uint8 {
  /**
   * 0: 31 Hz.
   */
  AUDIO_EQUALIZATION_BAND_31 = 0,
  /**
   * 1: 62 Hz.
   */
  AUDIO_EQUALIZATION_BAND_62 = 1,
  /**
   * 2: 125 Hz.
   */
  AUDIO_EQUALIZATION_BAND_125 = 2,
  /**
   * 3: 250 Hz.
   */
  AUDIO_EQUALIZATION_BAND_250 = 3,
  /**
   * 4: 500 Hz.
   */
  AUDIO_EQUALIZATION_BAND_500 = 4,
  /**
   * 5: 1 KHz.
   */
  AUDIO_EQUALIZATION_BAND_1K = 5,
  /**
   * 6: 2 KHz.
   */
  AUDIO_EQUALIZATION_BAND_2K = 6,
  /**
   * 7: 4 KHz.
   */
  AUDIO_EQUALIZATION_BAND_4K = 7,
  /**
   * 8: 8 KHz.
   */
  AUDIO_EQUALIZATION_BAND_8K = 8,
  /**
   * 9: 16 KHz.
   */
  AUDIO_EQUALIZATION_BAND_16K = 9,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_10_ENTRIES(EUABT_AUDIO_EQUALIZATION_BAND_FREQUENCY, agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY,
	AUDIO_EQUALIZATION_BAND_31,
	AUDIO_EQUALIZATION_BAND_62,
	AUDIO_EQUALIZATION_BAND_125,
	AUDIO_EQUALIZATION_BAND_250,
	AUDIO_EQUALIZATION_BAND_500,
	AUDIO_EQUALIZATION_BAND_1K,
	AUDIO_EQUALIZATION_BAND_2K,
	AUDIO_EQUALIZATION_BAND_4K,
	AUDIO_EQUALIZATION_BAND_8K,
	AUDIO_EQUALIZATION_BAND_16K
)



/**
 * The audio reverberation type.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_REVERB_TYPE : uint8 {
  /**
   * 0: (-20 to 10 dB), the level of the dry signal.
   */
  AUDIO_REVERB_DRY_LEVEL = 0,
  /**
   * 1: (-20 to 10 dB), the level of the early reflection signal (wet signal).
   */
  AUDIO_REVERB_WET_LEVEL = 1,
  /**
   * 2: (0 to 100 dB), the room size of the reflection.
   */
  AUDIO_REVERB_ROOM_SIZE = 2,
  /**
   * 3: (0 to 200 ms), the length of the initial delay of the wet signal in ms.
   */
  AUDIO_REVERB_WET_DELAY = 3,
  /**
   * 4: (0 to 100), the strength of the late reverberation.
   */
  AUDIO_REVERB_STRENGTH = 4,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_AUDIO_REVERB_TYPE, agora::rtc::AUDIO_REVERB_TYPE,
	AUDIO_REVERB_DRY_LEVEL,
	AUDIO_REVERB_WET_LEVEL,
	AUDIO_REVERB_ROOM_SIZE,
	AUDIO_REVERB_WET_DELAY,
	AUDIO_REVERB_STRENGTH
)


/**
 * The use mode of the audio data.
 */
UENUM(BlueprintType)
enum class EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE : uint8 {
  /** 0: Read-only mode: Users only read the data from `AudioFrame` without modifying anything.
   * For example, when users acquire the data with the Agora SDK, then start the media push.
   */
  RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,

  /** 2: Read and write mode: Users read the data from `AudioFrame`, modify it, and then play it.
   * For example, when users have their own audio-effect processing module and perform some voice
   * pre-processing, such as a voice change.
   */
  RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE,
	RAW_AUDIO_FRAME_OP_MODE_READ_ONLY,
	RAW_AUDIO_FRAME_OP_MODE_READ_WRITE
)



UENUM(BlueprintType)
enum class EUABT_STREAM_FALLBACK_OPTIONS : uint8 {
  /** 0: No fallback operation to a lower resolution stream when the network
     condition is poor. Fallback to Scalable Video Coding (e.g. SVC)
     is still possible, but the resolution remains in high stream.
     The stream quality cannot be guaranteed. */
  STREAM_FALLBACK_OPTION_DISABLED = 0,
  /** 1: (Default) Under poor network conditions, the receiver SDK will receive
     agora::rtc::VIDEO_STREAM_LOW. You can only set this option in
     RtcEngineParameters::setRemoteSubscribeFallbackOption. Nothing happens when
     you set this in RtcEngineParameters::setLocalPublishFallbackOption. */
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
  /** 2: Under poor network conditions, the SDK may receive agora::rtc::VIDEO_STREAM_LOW first,
     then agora::rtc::VIDEO_STREAM_LAYER_1 to agora::rtc::VIDEO_STREAM_LAYER_6 if the related layer exists.
     If the network still does not allow displaying the video, the SDK will receive audio only. */
  STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
  /** 3~8: If the receiver SDK uses RtcEngineParameters::setRemoteSubscribeFallbackOption，it will receive
     one of the streams from agora::rtc::VIDEO_STREAM_LAYER_1 to agora::rtc::VIDEO_STREAM_LAYER_6
     if the related layer exists when the network condition is poor. The lower bound of fallback depends on
     the STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_X. */
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_1 = 3,
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_2 = 4,
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_3 = 5,
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_4 = 6,
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_5 = 7,
  STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_6 = 8,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_9_ENTRIES(EUABT_STREAM_FALLBACK_OPTIONS, agora::rtc::STREAM_FALLBACK_OPTIONS,
	STREAM_FALLBACK_OPTION_DISABLED,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW,
	STREAM_FALLBACK_OPTION_AUDIO_ONLY,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_1,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_2,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_3,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_4,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_5,
	STREAM_FALLBACK_OPTION_VIDEO_STREAM_LAYER_6
)



/**
 * Video content hints.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_CONTENT_HINT : uint8 {
  /**
   * (Default) No content hint. In this case, the SDK balances smoothness with sharpness.
   */
  CONTENT_HINT_NONE,
  /**
   * Choose this option if you prefer smoothness or when
   * you are sharing motion-intensive content such as a video clip, movie, or video game.
   *
   *
   */
  CONTENT_HINT_MOTION,
  /**
   * Choose this option if you prefer sharpness or when you are
   * sharing montionless content such as a picture, PowerPoint slide, ot text.
   *
   */
  CONTENT_HINT_DETAILS
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_VIDEO_CONTENT_HINT, agora::rtc::VIDEO_CONTENT_HINT,
	CONTENT_HINT_NONE,
	CONTENT_HINT_MOTION,
	CONTENT_HINT_DETAILS
)


/**
 * The operational permission of the SDK on the audio session.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_SESSION_OPERATION_RESTRICTION : uint8 {
  /**
   * 0: No restriction; the SDK can change the audio session.
   */
  AUDIO_SESSION_OPERATION_RESTRICTION_NONE = 0,
  /**
   * 1: The SDK cannot change the audio session category.
   */
  AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY = 1,
  /**
   * 2: The SDK cannot change the audio session category, mode, or categoryOptions.
   */
  AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION = 1 << 1,
  /**
   * 4: The SDK keeps the audio session active when the user leaves the
   * channel, for example, to play an audio file in the background.
   */
  AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION = 1 << 2,
  /**
   * 128: Completely restricts the operational permission of the SDK on the
   * audio session; the SDK cannot change the audio session.
   */
  AUDIO_SESSION_OPERATION_RESTRICTION_ALL = 1 << 7,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_AUDIO_SESSION_OPERATION_RESTRICTION, agora::AUDIO_SESSION_OPERATION_RESTRICTION,
	AUDIO_SESSION_OPERATION_RESTRICTION_NONE,
	AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY,
	AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION,
	AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION,
	AUDIO_SESSION_OPERATION_RESTRICTION_ALL
)


/**
 * Self-defined audio codec profile.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_CODEC_PROFILE_TYPE : uint8 {
  /**
   * 0: LC-AAC.
   */
  AUDIO_CODEC_PROFILE_LC_AAC = 0,
  /**
   * 1: HE-AAC.
   */
  AUDIO_CODEC_PROFILE_HE_AAC = 1,
  /**
   *  2: HE-AAC v2.
   */
  AUDIO_CODEC_PROFILE_HE_AAC_V2 = 2,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_AUDIO_CODEC_PROFILE_TYPE, agora::rtc::AUDIO_CODEC_PROFILE_TYPE,
	AUDIO_CODEC_PROFILE_LC_AAC,
	AUDIO_CODEC_PROFILE_HE_AAC,
	AUDIO_CODEC_PROFILE_HE_AAC_V2
)


/**
 * The adaptation mode of the watermark.
 */
UENUM(BlueprintType)
enum class EUABT_WATERMARK_FIT_MODE : uint8 {
  /**
   * Use the `positionInLandscapeMode` and `positionInPortraitMode` values you set in
   * #WatermarkOptions. The settings in `WatermarkRatio` are invalid.
   */
  FIT_MODE_COVER_POSITION,
  /**
   * Use the value you set in `WatermarkRatio`. The settings in `positionInLandscapeMode` and
   * `positionInPortraitMode` in `WatermarkOptions` are invalid.
   */
  FIT_MODE_USE_IMAGE_RATIO
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_WATERMARK_FIT_MODE, agora::rtc::WATERMARK_FIT_MODE,
	FIT_MODE_COVER_POSITION,
	FIT_MODE_USE_IMAGE_RATIO
)


/**
 * Audio AINS mode
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_AINS_MODE : uint8 {
  /**
   * AINS mode with soft suppression level.
   */
  AINS_MODE_BALANCED = 0,
  /**
   * AINS mode with high suppression level.
   */
  AINS_MODE_AGGRESSIVE = 1,
  /**
   * AINS mode with high suppression level and ultra-low-latency
   */
  AINS_MODE_ULTRALOWLATENCY = 2
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_AUDIO_AINS_MODE, agora::rtc::AUDIO_AINS_MODE,
	AINS_MODE_BALANCED,
	AINS_MODE_AGGRESSIVE,
	AINS_MODE_ULTRALOWLATENCY
)


UENUM(BlueprintType)
enum class EUABT_CONTENT_INSPECT_TYPE : uint8 {
  /**
   * (Default) content inspect type invalid
   */
  CONTENT_INSPECT_INVALID = 0,
  /**
   * @deprecated
   * Content inspect type moderation
   */
  CONTENT_INSPECT_MODERATION = 1,
  /**
   * Content inspect type supervise
   */
  CONTENT_INSPECT_SUPERVISION = 2,
  /**
   * Content inspect type image moderation
   */
  CONTENT_INSPECT_IMAGE_MODERATION = 3
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_CONTENT_INSPECT_TYPE, agora::media::CONTENT_INSPECT_TYPE,
	CONTENT_INSPECT_INVALID,
	CONTENT_INSPECT_MODERATION,
	CONTENT_INSPECT_SUPERVISION,
	CONTENT_INSPECT_IMAGE_MODERATION
)


/** The cloud proxy type.
 *
 * @since v3.3.0
 */
UENUM(BlueprintType)
enum class EUABT_CLOUD_PROXY_TYPE : uint8 {
  /** 0: Do not use the cloud proxy.
   */
  NONE_PROXY = 0,
  /** 1: The cloud proxy for the UDP protocol.
   */
  UDP_PROXY = 1,
  /// @cond
  /** 2: The cloud proxy for the TCP (encrypted) protocol.
   */
  TCP_PROXY = 2,
  /// @endcond
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_CLOUD_PROXY_TYPE, agora::rtc::CLOUD_PROXY_TYPE,
	NONE_PROXY,
	UDP_PROXY,
	TCP_PROXY
)



/** The local  proxy mode type. */
UENUM(BlueprintType)
enum class EUABT_LOCAL_PROXY_MODE : uint8 {
  /** 0: Connect local proxy with high priority, if not connected to local proxy, fallback to sdrtn.
   */
  ConnectivityFirst = 0,
  /** 1: Only connect local proxy
   */
  LocalOnly = 1,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_LOCAL_PROXY_MODE, agora::rtc::LOCAL_PROXY_MODE,
	ConnectivityFirst,
	LocalOnly
)



/** The options for SDK voice AI tuner.
 */
UENUM(BlueprintType)
enum class EUABT_VOICE_AI_TUNER_TYPE : uint8 {
  /** Uncle, deep and magnetic male voice.
   */
  VOICE_AI_TUNER_MATURE_MALE,
  /** Fresh male, refreshing and sweet male voice.
   */
  VOICE_AI_TUNER_FRESH_MALE,
  /** Big sister, deep and charming female voice.
   */
  VOICE_AI_TUNER_ELEGANT_FEMALE,
  /** Lolita, high-pitched and cute female voice.
   */
  VOICE_AI_TUNER_SWEET_FEMALE,
  /** Warm man singing, warm and melodic male voice that is suitable for male lyrical songs.
   */
  VOICE_AI_TUNER_WARM_MALE_SINGING,
  /** Gentle female singing, soft and delicate female voice that is suitable for female lyrical songs.
   */
  VOICE_AI_TUNER_GENTLE_FEMALE_SINGING,
  /** Smoky uncle singing, unique husky male voice that is suitable for rock or blues songs.
   */
  VOICE_AI_TUNER_HUSKY_MALE_SINGING,
  /** Warm big sister singing, warm and mature female voice that is suitable for emotionally powerful songs.
   */
  VOICE_AI_TUNER_WARM_ELEGANT_FEMALE_SINGING,
  /** Forceful male singing, strong and powerful male voice that is suitable for passionate songs.
   */
  VOICE_AI_TUNER_POWERFUL_MALE_SINGING,
  /** Dreamy female singing, dreamlike and soft female voice that is suitable for airy and dream-like songs.
   */
  VOICE_AI_TUNER_DREAMY_FEMALE_SINGING,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_10_ENTRIES(EUABT_VOICE_AI_TUNER_TYPE, agora::rtc::VOICE_AI_TUNER_TYPE,
	VOICE_AI_TUNER_MATURE_MALE,
	VOICE_AI_TUNER_FRESH_MALE,
	VOICE_AI_TUNER_ELEGANT_FEMALE,
	VOICE_AI_TUNER_SWEET_FEMALE,
	VOICE_AI_TUNER_WARM_MALE_SINGING,

	VOICE_AI_TUNER_GENTLE_FEMALE_SINGING,
	VOICE_AI_TUNER_HUSKY_MALE_SINGING,
	VOICE_AI_TUNER_WARM_ELEGANT_FEMALE_SINGING,
	VOICE_AI_TUNER_POWERFUL_MALE_SINGING,
	VOICE_AI_TUNER_DREAMY_FEMALE_SINGING)




#pragma endregion Enum - NoChange





#pragma region Enum Wrapper

/**
 * The remote user state information.
 */
UENUM(BlueprintType)
enum class EUABT_REMOTE_USER_STATE : uint8 {
	/**
	 * The remote user has muted the audio.
	 */
	USER_STATE_MUTE_AUDIO = 0,
	/**
	 * The remote user has muted the video.
	 */
	USER_STATE_MUTE_VIDEO = 1,
	/**
	 * The remote user has enabled the video, which includes video capturing and encoding.
	 */
	USER_STATE_ENABLE_VIDEO = 2,
	/**
	 * The remote user has enabled the local video capturing.
	 */
	USER_STATE_ENABLE_LOCAL_VIDEO = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_REMOTE_USER_STATE, agora::rtc::REMOTE_USER_STATE,
	USER_STATE_MUTE_AUDIO,
	USER_STATE_MUTE_VIDEO,
	USER_STATE_ENABLE_VIDEO,
	USER_STATE_ENABLE_LOCAL_VIDEO)


/**
 * The brightness level of the video image captured by the local camera.
 */
UENUM(BlueprintType)
enum class EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE : uint8 {
	/** -1: The SDK does not detect the brightness level of the video image.
	 * Wait a few seconds to get the brightness level from `CAPTURE_BRIGHTNESS_LEVEL_TYPE` in the next
	 * callback.
	 */
	CAPTURE_BRIGHTNESS_LEVEL_INVALID = 0,
	/** 0: The brightness level of the video image is normal.
	 */
	CAPTURE_BRIGHTNESS_LEVEL_NORMAL = 1,
	/** 1: The brightness level of the video image is too bright.
	 */
	CAPTURE_BRIGHTNESS_LEVEL_BRIGHT = 2,
	/** 2: The brightness level of the video image is too dark.
	 */
	CAPTURE_BRIGHTNESS_LEVEL_DARK = 3,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES
(EUABT_CAPTURE_BRIGHTNESS_LEVEL_TYPE, agora::rtc::CAPTURE_BRIGHTNESS_LEVEL_TYPE,
	CAPTURE_BRIGHTNESS_LEVEL_INVALID,
	CAPTURE_BRIGHTNESS_LEVEL_NORMAL,
	CAPTURE_BRIGHTNESS_LEVEL_BRIGHT,
	CAPTURE_BRIGHTNESS_LEVEL_DARK
)

/**
 The playback state of the music file.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_MIXING_STATE_TYPE : uint8 {

	/** 710: The music file is playing. */
	AUDIO_MIXING_STATE_PLAYING = 0,
	/** 711: The music file pauses playing. */
	AUDIO_MIXING_STATE_PAUSED = 1,
	/** 713: The music file stops playing. */
	AUDIO_MIXING_STATE_STOPPED = 2,
	/** 714: An error occurs during the playback of the audio mixing file.
	 */
	AUDIO_MIXING_STATE_FAILED = 3,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_AUDIO_MIXING_STATE_TYPE, agora::rtc::AUDIO_MIXING_STATE_TYPE,
	AUDIO_MIXING_STATE_PLAYING,
	AUDIO_MIXING_STATE_PAUSED,
	AUDIO_MIXING_STATE_STOPPED,
	AUDIO_MIXING_STATE_FAILED)

/**
 The reson codes of the local user's audio mixing file.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_MIXING_REASON_TYPE : uint8 {
	/** 0: The SDK can open the audio mixing file. */
	AUDIO_MIXING_REASON_OK = 0,

	/** 701: The SDK cannot open the audio mixing file. */
	AUDIO_MIXING_REASON_CAN_NOT_OPEN = 1,
	/** 702: The SDK opens the audio mixing file too frequently. */
	AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 2,
	/** 703: The audio mixing file playback is interrupted. */
	AUDIO_MIXING_REASON_INTERRUPTED_EOF = 3,
	/** 715: The audio mixing file is played once. */
	AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 4,
	/** 716: The audio mixing file is all played out. */
	AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 5,
	/** 716: The audio mixing file stopped by user */
	AUDIO_MIXING_REASON_STOPPED_BY_USER = 6,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_7_ENTRIES(EUABT_AUDIO_MIXING_REASON_TYPE, agora::rtc::AUDIO_MIXING_REASON_TYPE,
	AUDIO_MIXING_REASON_OK,
	AUDIO_MIXING_REASON_CAN_NOT_OPEN,
	AUDIO_MIXING_REASON_TOO_FREQUENT_CALL,
	AUDIO_MIXING_REASON_INTERRUPTED_EOF,
	AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED,
	AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED,
	AUDIO_MIXING_REASON_STOPPED_BY_USER)

/**
 The states of the rhythm player.
 */
UENUM(BlueprintType)
enum class EUABT_RHYTHM_PLAYER_STATE_TYPE : uint8 {
	/** 810: The rhythm player is idle. */
	RHYTHM_PLAYER_STATE_IDLE = 0,
	/** 811: The rhythm player is opening files. */
	RHYTHM_PLAYER_STATE_OPENING,
	/** 812: Files opened successfully, the rhythm player starts decoding files. */
	RHYTHM_PLAYER_STATE_DECODING,
	/** 813: Files decoded successfully, the rhythm player starts mixing the two files and playing back them locally. */
	RHYTHM_PLAYER_STATE_PLAYING,
	/** 814: The rhythm player is starting to fail, and you need to check the error code for detailed failure reasons. */
	RHYTHM_PLAYER_STATE_FAILED,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_RHYTHM_PLAYER_STATE_TYPE, agora::rtc::RHYTHM_PLAYER_STATE_TYPE,
	RHYTHM_PLAYER_STATE_IDLE,
	RHYTHM_PLAYER_STATE_OPENING,
	RHYTHM_PLAYER_STATE_DECODING,
	RHYTHM_PLAYER_STATE_PLAYING,
	RHYTHM_PLAYER_STATE_FAILED)


/**
 The reason codes of the rhythm player.
 */
UENUM(BlueprintType)
enum class EUABT_RHYTHM_PLAYER_REASON : uint8 {
	/** 0: The rhythm player works well. */
	RHYTHM_PLAYER_REASON_OK = 0,
	/** 1: The rhythm player occurs a internal error. */
	RHYTHM_PLAYER_REASON_FAILED,
	/** 801: The rhythm player can not open the file. */
	RHYTHM_PLAYER_REASON_CAN_NOT_OPEN,
	/** 802: The rhythm player can not play the file. */
	RHYTHM_PLAYER_REASON_CAN_NOT_PLAY,
	/** 803: The file duration over the limit. The file duration limit is 1.2 seconds */
	RHYTHM_PLAYER_REASON_FILE_OVER_DURATION_LIMIT,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_RHYTHM_PLAYER_REASON, agora::rtc::RHYTHM_PLAYER_REASON,
	RHYTHM_PLAYER_REASON_OK,
	RHYTHM_PLAYER_REASON_FAILED,
	RHYTHM_PLAYER_REASON_CAN_NOT_OPEN,
	RHYTHM_PLAYER_REASON_CAN_NOT_PLAY,
	RHYTHM_PLAYER_REASON_FILE_OVER_DURATION_LIMIT)


UENUM(BlueprintType)
enum class EUABT_LICENSE_ERROR_TYPE : uint8 {
	/**
	 * 1: Invalid license
	 */
	LICENSE_ERR_INVALID = 0,
	/**
	 * 2: License expired
	 */
	LICENSE_ERR_EXPIRE,
	/**
	 * 3: Exceed license minutes limit
	 */
	LICENSE_ERR_MINUTES_EXCEED,
	/**
	 * 4: License use in limited period
	 */
	LICENSE_ERR_LIMITED_PERIOD,
	/**
	 * 5: Same license used in different devices at the same time
	 */
	LICENSE_ERR_DIFF_DEVICES,
	/**
	 * 99: SDK internal error
	 */
	LICENSE_ERR_INTERNAL,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_LICENSE_ERROR_TYPE, agora::LICENSE_ERROR_TYPE,
	LICENSE_ERR_INVALID,
	LICENSE_ERR_EXPIRE,
	LICENSE_ERR_MINUTES_EXCEED,
	LICENSE_ERR_LIMITED_PERIOD,
	LICENSE_ERR_DIFF_DEVICES,
	LICENSE_ERR_INTERNAL)



UENUM(BlueprintType)
enum class EUABT_CONTENT_INSPECT_RESULT : uint8 {
	CONTENT_INSPECT_NEUTRAL = 0,
	CONTENT_INSPECT_SEXY,
	CONTENT_INSPECT_PORN,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_CONTENT_INSPECT_RESULT, agora::media::CONTENT_INSPECT_RESULT,
	CONTENT_INSPECT_NEUTRAL,
	CONTENT_INSPECT_SEXY,
	CONTENT_INSPECT_PORN)



/**
 * The reason of changing role's failure.
 */
UENUM(BlueprintType)
enum class EUABT_CLIENT_ROLE_CHANGE_FAILED_REASON : uint8 {
	/**
	 * 1: Too many broadcasters in the channel.
	 */
	CLIENT_ROLE_CHANGE_FAILED_TOO_MANY_BROADCASTERS = 0,
	/**
	 * 2: The operation of changing role is not authorized.
	 */
	CLIENT_ROLE_CHANGE_FAILED_NOT_AUTHORIZED,
	/**
	 * 3: The operation of changing role is timeout.
	 * @deprecated This reason is deprecated.
	 */
	CLIENT_ROLE_CHANGE_FAILED_REQUEST_TIME_OUT,
	/**
	 * 4: The operation of changing role is interrupted since we lost connection with agora service.
	 * @deprecated This reason is deprecated.
	 */
	CLIENT_ROLE_CHANGE_FAILED_CONNECTION_FAILED,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_CLIENT_ROLE_CHANGE_FAILED_REASON, agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON,
	CLIENT_ROLE_CHANGE_FAILED_TOO_MANY_BROADCASTERS,
	CLIENT_ROLE_CHANGE_FAILED_NOT_AUTHORIZED,
	CLIENT_ROLE_CHANGE_FAILED_REQUEST_TIME_OUT,
	CLIENT_ROLE_CHANGE_FAILED_CONNECTION_FAILED)



/**
 * The media device types.
 */
UENUM(BlueprintType)
enum class EUABT_MEDIA_DEVICE_TYPE : uint8 {
	/**
	 * -1: Unknown device type.
	 */
	UNKNOWN_AUDIO_DEVICE = 0,
	/**
	 * 0: The audio playback device.
	 */
	AUDIO_PLAYOUT_DEVICE,
	/**
	 * 1: The audio recording device.
	 */
	AUDIO_RECORDING_DEVICE,
	/**
	 * 2: The video renderer.
	 */
	VIDEO_RENDER_DEVICE,
	/**
	 * 3: The video capturer.
	 */
	VIDEO_CAPTURE_DEVICE,
	/**
	 * 4: The audio playback device of the app.
	 */
	AUDIO_APPLICATION_PLAYOUT_DEVICE,
	/**
	 * 5: The virtual audio playback device.
	 */
	AUDIO_VIRTUAL_PLAYOUT_DEVICE,
	/**
	 * 6: The virtual audio recording device.
	 */
	AUDIO_VIRTUAL_RECORDING_DEVICE,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_8_ENTRIES(EUABT_MEDIA_DEVICE_TYPE, agora::rtc::MEDIA_DEVICE_TYPE,
	UNKNOWN_AUDIO_DEVICE,
	AUDIO_PLAYOUT_DEVICE,
	AUDIO_RECORDING_DEVICE,
	VIDEO_RENDER_DEVICE,
	VIDEO_CAPTURE_DEVICE,
	AUDIO_APPLICATION_PLAYOUT_DEVICE,
	AUDIO_VIRTUAL_PLAYOUT_DEVICE,
	AUDIO_VIRTUAL_RECORDING_DEVICE)





/** Events during the RTMP or RTMPS streaming. */
UENUM(BlueprintType)
enum class EUABT_RTMP_STREAMING_EVENT : uint8 {
	/**
	 * 1: An error occurs when you add a background image or a watermark image to the RTMP or RTMPS
	 * stream.
	 */
	RTMP_STREAMING_EVENT_FAILED_LOAD_IMAGE = 0,
	/**
	 * 2: The streaming URL is already being used for CDN live streaming. If you want to start new
	 * streaming, use a new streaming URL.
	 */
	RTMP_STREAMING_EVENT_URL_ALREADY_IN_USE,
	/**
	 * 3: The feature is not supported.
	 */
	RTMP_STREAMING_EVENT_ADVANCED_FEATURE_NOT_SUPPORT,
	/**
	 * 4: Client request too frequently.
	 */
	RTMP_STREAMING_EVENT_REQUEST_TOO_OFTEN,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_RTMP_STREAMING_EVENT, agora::rtc::RTMP_STREAMING_EVENT,
	RTMP_STREAMING_EVENT_FAILED_LOAD_IMAGE,
	RTMP_STREAMING_EVENT_URL_ALREADY_IN_USE,
	RTMP_STREAMING_EVENT_ADVANCED_FEATURE_NOT_SUPPORT,
	RTMP_STREAMING_EVENT_REQUEST_TOO_OFTEN)

/**
 * Connection state types.
 */
UENUM(BlueprintType)
enum class EUABT_CONNECTION_STATE_TYPE : uint8 {
	/**
	 * 1: The SDK is disconnected from the Agora edge server. The state indicates the SDK is in one of
	 * the following phases:
	 * - The initial state before calling the `joinChannel` method.
	 * - The app calls the `leaveChannel` method.
	 */
	CONNECTION_STATE_DISCONNECTED = 0,
	/**
	 * 2: The SDK is connecting to the Agora edge server. This state indicates that the SDK is
	 * establishing a connection with the specified channel after the app calls `joinChannel`.
	 * - If the SDK successfully joins the channel, it triggers the `onConnectionStateChanged`
	 * callback and the connection state switches to `CONNECTION_STATE_CONNECTED`.
	 * - After the connection is established, the SDK also initializes the media and triggers
	 * `onJoinChannelSuccess` when everything is ready.
	 */
	CONNECTION_STATE_CONNECTING,
	/**
	 * 3: The SDK is connected to the Agora edge server. This state also indicates that the user
	 * has joined a channel and can now publish or subscribe to a media stream in the channel.
	 * If the connection to the Agora edge server is lost because, for example, the network is down
	 * or switched, the SDK automatically tries to reconnect and triggers `onConnectionStateChanged`
	 * that indicates the connection state switches to `CONNECTION_STATE_RECONNECTING`.
	 */
	CONNECTION_STATE_CONNECTED,
	/**
	 * 4: The SDK keeps reconnecting to the Agora edge server. The SDK keeps rejoining the channel
	 * after being disconnected from a joined channel because of network issues.
	 * - If the SDK cannot rejoin the channel within 10 seconds, it triggers `onConnectionLost`,
	 * stays in the `CONNECTION_STATE_RECONNECTING` state, and keeps rejoining the channel.
	 * - If the SDK fails to rejoin the channel 20 minutes after being disconnected from the Agora
	 * edge server, the SDK triggers the `onConnectionStateChanged` callback, switches to the
	 * `CONNECTION_STATE_FAILED` state, and stops rejoining the channel.
	 */
	CONNECTION_STATE_RECONNECTING,
	/**
	 * 5: The SDK fails to connect to the Agora edge server or join the channel. This state indicates
	 * that the SDK stops trying to rejoin the channel. You must call `leaveChannel` to leave the
	 * channel.
	 * - You can call `joinChannel` to rejoin the channel.
	 * - If the SDK is banned from joining the channel by the Agora edge server through the RESTful
	 * API, the SDK triggers the `onConnectionStateChanged` callback.
	 */
	CONNECTION_STATE_FAILED,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_CONNECTION_STATE_TYPE, agora::rtc::CONNECTION_STATE_TYPE,
	CONNECTION_STATE_DISCONNECTED,
	CONNECTION_STATE_CONNECTING,
	CONNECTION_STATE_CONNECTED,
	CONNECTION_STATE_RECONNECTING,
	CONNECTION_STATE_FAILED)


/**
 * The network type.
 */
UENUM(BlueprintType)
enum class EUABT_NETWORK_TYPE : uint8 {
	/**
	 * -1: The network type is unknown.
	 */
	NETWORK_TYPE_UNKNOWN = 0,
	/**
	 * 0: The SDK disconnects from the network.
	 */
	NETWORK_TYPE_DISCONNECTED,
	/**
	 * 1: The network type is LAN.
	 */
	NETWORK_TYPE_LAN,
	/**
	 * 2: The network type is Wi-Fi (including hotspots).
	 */
	NETWORK_TYPE_WIFI,
	/**
	 * 3: The network type is mobile 2G.
	 */
	NETWORK_TYPE_MOBILE_2G,
	/**
	 * 4: The network type is mobile 3G.
	 */
	NETWORK_TYPE_MOBILE_3G,
	/**
	 * 5: The network type is mobile 4G.
	 */
	NETWORK_TYPE_MOBILE_4G,
	/**
	 * 6: The network type is mobile 5G.
	 */
	NETWORK_TYPE_MOBILE_5G,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_8_ENTRIES(EUABT_NETWORK_TYPE, agora::rtc::NETWORK_TYPE,
	NETWORK_TYPE_UNKNOWN,
	NETWORK_TYPE_DISCONNECTED,
	NETWORK_TYPE_LAN,
	NETWORK_TYPE_WIFI,
	NETWORK_TYPE_MOBILE_2G,
	NETWORK_TYPE_MOBILE_3G,
	NETWORK_TYPE_MOBILE_4G,
	NETWORK_TYPE_MOBILE_5G)


UENUM(BlueprintType)
enum class EUABT_VIDEO_TRANSCODER_ERROR : uint8 {
	/**
	 * The video track of the video source is not started.
	 */
	VT_ERR_VIDEO_SOURCE_NOT_READY = 0,
	/**
	 * The video source type is not supported.
	 */
	VT_ERR_INVALID_VIDEO_SOURCE_TYPE,
	/**
	 * The image url is not correctly of image source.
	 */
	VT_ERR_INVALID_IMAGE_PATH,
	/**
	 * The image format not the type png/jpeg/gif of image source.
	 */
	VT_ERR_UNSUPPORT_IMAGE_FORMAT,
	/**
	 * The layout is invalid such as width is zero.
	 */
	VT_ERR_INVALID_LAYOUT,
	/**
	 * Internal error.
	 */
	VT_ERR_INTERNAL
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_VIDEO_TRANSCODER_ERROR, agora::rtc::VIDEO_TRANSCODER_ERROR,
	VT_ERR_VIDEO_SOURCE_NOT_READY,
	VT_ERR_INVALID_VIDEO_SOURCE_TYPE,
	VT_ERR_INVALID_IMAGE_PATH,
	VT_ERR_UNSUPPORT_IMAGE_FORMAT,
	VT_ERR_INVALID_LAYOUT,
	VT_ERR_INTERNAL)


/**
 * The built-in encryption mode.
 *
 * Agora recommends using AES_128_GCM2 or AES_256_GCM2 encrypted mode. These two modes support the
 * use of salt for higher security.
 */
UENUM(BlueprintType)
enum class EUABT_ENCRYPTION_MODE :uint8 {
	/** 1: 128-bit AES encryption, XTS mode.
	 */
	AES_128_XTS = 0,
	/** 2: 128-bit AES encryption, ECB mode.
	 */
	AES_128_ECB,
	/** 3: 256-bit AES encryption, XTS mode.
	 */
	AES_256_XTS,
	/** 4: 128-bit SM4 encryption, ECB mode.
	 */
	SM4_128_ECB,
	/** 5: 128-bit AES encryption, GCM mode.
	 */
	AES_128_GCM,
	/** 6: 256-bit AES encryption, GCM mode.
	 */
	AES_256_GCM,
	/** 7: (Default) 128-bit AES encryption, GCM mode. This encryption mode requires the setting of
	 * salt (`encryptionKdfSalt`).
	 */
	AES_128_GCM2,
	/** 8: 256-bit AES encryption, GCM mode. This encryption mode requires the setting of salt
	 * (`encryptionKdfSalt`).
	 */
	AES_256_GCM2,
	/** Enumerator boundary.
	 */
	MODE_END,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_9_ENTRIES(EUABT_ENCRYPTION_MODE, agora::rtc::ENCRYPTION_MODE,
	AES_128_XTS,
	AES_128_ECB,
	AES_256_XTS,
	SM4_128_ECB,
	AES_128_GCM,
	AES_256_GCM,
	AES_128_GCM2,
	AES_256_GCM2,
	MODE_END)

/**
 * User role types.
 */
UENUM(BlueprintType)
enum class EUABT_CLIENT_ROLE_TYPE : uint8 {
	/**
	 * 1: Broadcaster. A broadcaster can both send and receive streams.
	 */
	CLIENT_ROLE_BROADCASTER = 0,
	/**
	 * 2: Audience. An audience member can only receive streams.
	 */
	CLIENT_ROLE_AUDIENCE,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_CLIENT_ROLE_TYPE, agora::rtc::CLIENT_ROLE_TYPE,
	CLIENT_ROLE_BROADCASTER,
	CLIENT_ROLE_AUDIENCE)


/**
 * The latency level of an audience member in interactive live streaming. This enum takes effect
 * only when the user role is set to `CLIENT_ROLE_AUDIENCE`.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIENCE_LATENCY_LEVEL_TYPE : uint8 {
	/**
	 * 1: Low latency.
	 */
	AUDIENCE_LATENCY_LEVEL_LOW_LATENCY = 0,
	/**
	 * 2: Ultra low latency.
	 */
	AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY,
};

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_AUDIENCE_LATENCY_LEVEL_TYPE, agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE,
	AUDIENCE_LATENCY_LEVEL_LOW_LATENCY,
	AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY)


/**
 * The video display mode.
 */
UENUM(BlueprintType)
enum class EUABT_RENDER_MODE_TYPE : uint8 {
	/**
	 * 1: Uniformly scale the video until it fills the visible boundaries
	 * (cropped). One dimension of the video may have clipped contents.
	 */
	RENDER_MODE_HIDDEN = 0,
	/**
	 * 2: Uniformly scale the video until one of its dimension fits the boundary
	 * (zoomed to fit). Areas that are not filled due to the disparity in the
	 * aspect ratio will be filled with black.
	 */
	RENDER_MODE_FIT,
	/**
	 * @deprecated
	 * 3: This mode is deprecated.
	 */
	RENDER_MODE_ADAPTIVE,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_RENDER_MODE_TYPE, agora::media::base::RENDER_MODE_TYPE,
	RENDER_MODE_HIDDEN,
	RENDER_MODE_FIT,
	RENDER_MODE_ADAPTIVE)


UENUM(BlueprintType)
enum class EUABT_VIDEO_MODULE_POSITION :uint8 {
	POSITION_POST_CAPTURER = 0,
	POSITION_PRE_RENDERER,
	POSITION_PRE_ENCODER,
	POSITION_POST_CAPTURER_ORIGIN,
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_VIDEO_MODULE_POSITION, agora::media::base::VIDEO_MODULE_POSITION,
	POSITION_POST_CAPTURER,
	POSITION_PRE_RENDERER,
	POSITION_PRE_ENCODER,
	POSITION_POST_CAPTURER_ORIGIN)

/** The region for connection, which is the region where the server the SDK connects to is located.
 */
UENUM(BlueprintType)
enum class EUABT_AREA_CODE : uint8 {
	/**
	 * Mainland China.
	 */
	AREA_CODE_CN = 0,
	/**
	 * North America.
	 */
	AREA_CODE_NA,
	/**
	 * Europe.
	 */
	AREA_CODE_EU,
	/**
	 * Asia, excluding Mainland China.
	 */
	AREA_CODE_AS,
	/**
	 * Japan.
	 */
	AREA_CODE_JP,
	/**
	 * India.
	 */
	AREA_CODE_IN,
	/**
	 * (Default) Global.
	 */
	AREA_CODE_GLOB
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_7_ENTRIES(EUABT_AREA_CODE, agora::rtc::AREA_CODE,
	AREA_CODE_GLOB,
	AREA_CODE_CN,
	AREA_CODE_NA,
	AREA_CODE_EU,
	AREA_CODE_AS,
	AREA_CODE_JP,
	AREA_CODE_IN)


/**
 * Video codec capability levels.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_CODEC_CAPABILITY_LEVEL : uint8{
	/** No specified level */
	CODEC_CAPABILITY_LEVEL_UNSPECIFIED = 0,
	/** Only provide basic support for the codec type */
	CODEC_CAPABILITY_LEVEL_BASIC_SUPPORT,
	/** Can process 1080p video at a rate of approximately 30 fps. */
	CODEC_CAPABILITY_LEVEL_1080P30FPS,
	/** Can process 1080p video at a rate of approximately 60 fps. */
	CODEC_CAPABILITY_LEVEL_1080P60FPS,
	/** Can process 4k video at a rate of approximately 30 fps. */
	CODEC_CAPABILITY_LEVEL_4K60FPS,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_VIDEO_CODEC_CAPABILITY_LEVEL, agora::rtc::VIDEO_CODEC_CAPABILITY_LEVEL,
	CODEC_CAPABILITY_LEVEL_UNSPECIFIED,
	CODEC_CAPABILITY_LEVEL_BASIC_SUPPORT,
	CODEC_CAPABILITY_LEVEL_1080P30FPS,
	CODEC_CAPABILITY_LEVEL_1080P60FPS,
	CODEC_CAPABILITY_LEVEL_4K60FPS)


/**
 * (For future use) Video degradation preferences under limited bandwidth.
 */
UENUM(BlueprintType)
enum class EUABT_DEGRADATION_PREFERENCE : uint8 {
	/**
	 * -1: (Default) SDK uses degradation preference according to setVideoScenario API settings, real-time network state and other relevant data information.
	 * If API setVideoScenario set video scenario to APPLICATION_SCENARIO_LIVESHOW, then MAINTAIN_BALANCED is used. If not, then MAINTAIN_RESOLUTION is used.
	 * Also if network state has changed, SDK may change this parameter between MAINTAIN_FRAMERATE��MAINTAIN_BALANCED and MAINTAIN_RESOLUTION automatically to get the best QOE.
	 * We recommend using this option.
	*/
	MAINTAIN_AUTO = 0,
	/**
	 * 0: (Deprecated) Prefers to reduce the video frame rate while maintaining video quality during
	 * video encoding under limited bandwidth. This degradation preference is suitable for scenarios
	 * where video quality is prioritized.
	 * @note In the COMMUNICATION channel profile, the resolution of the video sent may change, so
	 * remote users need to handle this issue.
	 */
	MAINTAIN_QUALITY,
	/**
	 * 1: Prefers to reduce the video quality while maintaining the video frame rate during video
	 * encoding under limited bandwidth. This degradation preference is suitable for scenarios where
	 * smoothness is prioritized and video quality is allowed to be reduced.
	 */
	MAINTAIN_FRAMERATE,
	/**
	 * 2: Reduces the video frame rate and video quality simultaneously during video encoding under
	 * limited bandwidth. MAINTAIN_BALANCED has a lower reduction than MAINTAIN_RESOLUTION and
	 * MAINTAIN_FRAMERATE, and this preference is suitable for scenarios where both smoothness and
	 * video quality are a priority.
	 */
	MAINTAIN_BALANCED,
	/**
	 * 3: Degrade framerate in order to maintain resolution.
	 */
	MAINTAIN_RESOLUTION,
	/**
	 * 4: Disable VQC adjustion.
	 */
	DISABLED,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_6_ENTRIES(EUABT_DEGRADATION_PREFERENCE, agora::rtc::DEGRADATION_PREFERENCE,
	MAINTAIN_AUTO,
	MAINTAIN_QUALITY,
	MAINTAIN_FRAMERATE,
	MAINTAIN_BALANCED,
	MAINTAIN_RESOLUTION,
	DISABLED)


/**
 * The video encoder type preference.
 */
UENUM(BlueprintType)
enum class EUABT_ENCODING_PREFERENCE : uint8 {
	/**
	 *Default .
	 */
	PREFER_AUTO = 0,
	/**
	 *  Software encoding.
	 */
	PREFER_SOFTWARE,
	/**
	 * Hardware encoding
	 */
	PREFER_HARDWARE,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_ENCODING_PREFERENCE, agora::rtc::ENCODING_PREFERENCE,
	PREFER_AUTO,
	PREFER_SOFTWARE,
	PREFER_HARDWARE)



/**
 * Video compression preference.
 */
UENUM(BlueprintType)
enum class EUABT_COMPRESSION_PREFERENCE :uint8 {
	/**
	 * (Default) SDK uses compression preference according to setVideoScenario API settings, real-time network state and other relevant data information.
	 * If API setVideoScenario set video scenario to APPLICATION_SCENARIO_LIVESHOW, then PREFER_QUALITY is used. If not, then PREFER_LOW_LATENCY is used.
	 * Also if network state has changed, SDK may change this parameter between PREFER_QUALITY and PREFER_LOW_LATENCY automatically to get the best QOE.
	 * We recommend using this option.
	*/
	PREFER_COMPRESSION_AUTO = 0,
	/**
	 * Prefer low latency, usually used in real-time communication where low latency is the number one priority.
	*/
	PREFER_LOW_LATENCY,
	/**
	 * Prefer quality in sacrifice of a degree of latency, usually around 30ms ~ 150ms, depends target fps
	*/
	PREFER_QUALITY,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_COMPRESSION_PREFERENCE, agora::rtc::COMPRESSION_PREFERENCE,
	PREFER_COMPRESSION_AUTO,
	PREFER_LOW_LATENCY,
	PREFER_QUALITY)



/** The degree of blurring applied to the background source.
 */
UENUM(BlueprintType)
enum class EUABT_BACKGROUND_BLUR_DEGREE :uint8 {
	/** 1: The degree of blurring applied to the custom background image is low. The user can almost
	   see the background clearly. */
	BLUR_DEGREE_LOW = 0,
	/** 2: The degree of blurring applied to the custom background image is medium. It is difficult
	   for the user to recognize details in the background. */
	BLUR_DEGREE_MEDIUM,
	/** 3: (Default) The degree of blurring applied to the custom background image is high. The user
	   can barely see any distinguishing features in the background. */
	BLUR_DEGREE_HIGH,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_BACKGROUND_BLUR_DEGREE, agora::rtc::VirtualBackgroundSource::BACKGROUND_BLUR_DEGREE,
	BLUR_DEGREE_LOW,
	BLUR_DEGREE_MEDIUM,
	BLUR_DEGREE_HIGH)



UENUM(BlueprintType)
enum class EUABT_SEG_MODEL_TYPE : uint8 {

	SEG_MODEL_AI = 0,
	SEG_MODEL_GREEN
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_SEG_MODEL_TYPE, agora::rtc::SegmentationProperty::SEG_MODEL_TYPE,
	SEG_MODEL_AI,
	SEG_MODEL_GREEN)


/**
 * The video QoE preference type.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_QOE_PREFERENCE_TYPE : uint8 {
	/**
	 * 1: Default QoE type, balance the delay, picture quality and fluency.
	 */
	VIDEO_QOE_PREFERENCE_BALANCE = 0,
	/**
	 * 2: lower the e2e delay.
	 */
	VIDEO_QOE_PREFERENCE_DELAY_FIRST,
	/**
	 * 3: picture quality.
	 */
	VIDEO_QOE_PREFERENCE_PICTURE_QUALITY_FIRST,
	/**
	 * 4: more fluency.
	 */
	VIDEO_QOE_PREFERENCE_FLUENCY_FIRST,

};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_VIDEO_QOE_PREFERENCE_TYPE, agora::rtc::VIDEO_QOE_PREFERENCE_TYPE,
	VIDEO_QOE_PREFERENCE_BALANCE,
	VIDEO_QOE_PREFERENCE_DELAY_FIRST,
	VIDEO_QOE_PREFERENCE_PICTURE_QUALITY_FIRST,
	VIDEO_QOE_PREFERENCE_FLUENCY_FIRST)



/**
 * Recording content. Set in `startAudioRecording`.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_FILE_RECORDING_TYPE :uint8 {
	/**
	 * 1: Only records the audio of the local user.
	 */
	AUDIO_FILE_RECORDING_MIC = 0,
	/**
	 * 2: Only records the audio of all remote users.
	 */
	AUDIO_FILE_RECORDING_PLAYBACK,
	/**
	 * 3: Records the mixed audio of the local and all remote users.
	 */
	AUDIO_FILE_RECORDING_MIXED,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_AUDIO_FILE_RECORDING_TYPE, agora::rtc::AUDIO_FILE_RECORDING_TYPE,
	AUDIO_FILE_RECORDING_MIC,
	AUDIO_FILE_RECORDING_PLAYBACK,
	AUDIO_FILE_RECORDING_MIXED)


/**
 * Audio encoded frame observer position.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_ENCODED_FRAME_OBSERVER_POSITION :uint8 {
	/**
	 * 1: Only records the audio of the local user.
	 */
	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_RECORD = 0,
	/**
	 * 2: Only records the audio of all remote users.
	 */
	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_PLAYBACK,
	/**
	 * 3: Records the mixed audio of the local and all remote users.
	 */
	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_MIXED,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_AUDIO_ENCODED_FRAME_OBSERVER_POSITION, agora::rtc::AUDIO_ENCODED_FRAME_OBSERVER_POSITION,

	AUDIO_ENCODED_FRAME_OBSERVER_POSITION_RECORD, AUDIO_ENCODED_FRAME_OBSERVER_POSITION_PLAYBACK, AUDIO_ENCODED_FRAME_OBSERVER_POSITION_MIXED)


/**
 * Preset local voice reverberation options.
 * bitmap allocation:
 * |  bit31  |    bit30 - bit24   |        bit23 - bit16        | bit15 - bit8 |  bit7 - bit0   |
 * |---------|--------------------|-----------------------------|--------------|----------------|
 * |reserved | 0x1: voice beauty  | 0x1: chat beautification    | effect types | effect settings|
 * |         |                    | 0x2: singing beautification |              |                |
 * |         |                    | 0x3: timbre transform       |              |                |
 * |         |                    | 0x4: ultra high_quality     |              |                |
 * |         |--------------------|-----------------------------|              |                |
 * |         | 0x2: audio effect  | 0x1: space construction     |              |                |
 * |         |                    | 0x2: voice changer effect   |              |                |
 * |         |                    | 0x3: style transform        |              |                |
 * |         |                    | 0x4: electronic sound       |              |                |
 * |         |                    | 0x5: magic tone             |              |                |
 * |         |--------------------|-----------------------------|              |                |
 * |         | 0x3: voice changer | 0x1: voice transform        |              |                |
 */
 /** The options for SDK preset voice beautifier effects.
  */
UENUM(BlueprintType)
enum class EUABT_VOICE_BEAUTIFIER_PRESET :uint8 {
	/** Turn off voice beautifier effects and use the original voice.
	 */
	VOICE_BEAUTIFIER_OFF = 0,
	/** A more magnetic voice.
	 *
	 * @note Agora recommends using this enumerator to process a male-sounding voice; otherwise, you
	 * may experience vocal distortion.
	 */
	CHAT_BEAUTIFIER_MAGNETIC,
	/** A fresher voice.
	 *
	 * @note Agora recommends using this enumerator to process a female-sounding voice; otherwise, you
	 * may experience vocal distortion.
	 */
	CHAT_BEAUTIFIER_FRESH,
	/** A more vital voice.
	 *
	 * @note Agora recommends using this enumerator to process a female-sounding voice; otherwise, you
	 * may experience vocal distortion.
	 */
	CHAT_BEAUTIFIER_VITALITY,
	/**
	 * Singing beautifier effect.
	 * - If you call `setVoiceBeautifierPreset`(SINGING_BEAUTIFIER), you can beautify a male-sounding
	 * voice and add a reverberation effect that sounds like singing in a small room. Agora recommends
	 * not using `setVoiceBeautifierPreset`(SINGING_BEAUTIFIER) to process a female-sounding voice;
	 * otherwise, you may experience vocal distortion.
	 * - If you call `setVoiceBeautifierParameters`(SINGING_BEAUTIFIER, param1, param2), you can
	 * beautify a male- or female-sounding voice and add a reverberation effect.
	 */
	SINGING_BEAUTIFIER,
	/** A more vigorous voice.
	 */
	TIMBRE_TRANSFORMATION_VIGOROUS,
	/** A deeper voice.
	 */
	TIMBRE_TRANSFORMATION_DEEP,
	/** A mellower voice.
	 */
	TIMBRE_TRANSFORMATION_MELLOW,
	/** A falsetto voice.
	 */
	TIMBRE_TRANSFORMATION_FALSETTO,
	/** A fuller voice.
	 */
	TIMBRE_TRANSFORMATION_FULL,
	/** A clearer voice.
	 */
	TIMBRE_TRANSFORMATION_CLEAR,
	/** A more resounding voice.
	 */
	TIMBRE_TRANSFORMATION_RESOUNDING,
	/** A more ringing voice.
	 */
	TIMBRE_TRANSFORMATION_RINGING,
	/**
	 * A ultra-high quality voice, which makes the audio clearer and restores more details.
	 * - To achieve better audio effect quality, Agora recommends that you call `setAudioProfile`
	 * and set the `profile` to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or
	 * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` and `scenario` to
	 * `AUDIO_SCENARIO_HIGH_DEFINITION(6)` before calling `setVoiceBeautifierPreset`.
	 * - If you have an audio capturing device that can already restore audio details to a high
	 * degree, Agora recommends that you do not enable ultra-high quality; otherwise, the SDK may
	 * over-restore audio details, and you may not hear the anticipated voice effect.
	 */
	ULTRA_HIGH_QUALITY_VOICE
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_14_ENTRIES(EUABT_VOICE_BEAUTIFIER_PRESET, agora::rtc::VOICE_BEAUTIFIER_PRESET,
	VOICE_BEAUTIFIER_OFF,
	CHAT_BEAUTIFIER_MAGNETIC,
	CHAT_BEAUTIFIER_FRESH,
	CHAT_BEAUTIFIER_VITALITY,
	SINGING_BEAUTIFIER,
	TIMBRE_TRANSFORMATION_VIGOROUS,
	TIMBRE_TRANSFORMATION_DEEP,
	TIMBRE_TRANSFORMATION_MELLOW,
	TIMBRE_TRANSFORMATION_FALSETTO,
	TIMBRE_TRANSFORMATION_FULL,
	TIMBRE_TRANSFORMATION_CLEAR,
	TIMBRE_TRANSFORMATION_RESOUNDING,
	TIMBRE_TRANSFORMATION_RINGING,
	ULTRA_HIGH_QUALITY_VOICE)


/** Preset voice effects.
 *
 * For better voice effects, Agora recommends setting the `profile` parameter of `setAudioProfile`
 * to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO` before using
 * the following presets:
 *
 * - `ROOM_ACOUSTICS_KTV`
 * - `ROOM_ACOUSTICS_VOCAL_CONCERT`
 * - `ROOM_ACOUSTICS_STUDIO`
 * - `ROOM_ACOUSTICS_PHONOGRAPH`
 * - `ROOM_ACOUSTICS_SPACIAL`
 * - `ROOM_ACOUSTICS_ETHEREAL`
 * - `ROOM_ACOUSTICS_CHORUS`
 * - `VOICE_CHANGER_EFFECT_UNCLE`
 * - `VOICE_CHANGER_EFFECT_OLDMAN`
 * - `VOICE_CHANGER_EFFECT_BOY`
 * - `VOICE_CHANGER_EFFECT_SISTER`
 * - `VOICE_CHANGER_EFFECT_GIRL`
 * - `VOICE_CHANGER_EFFECT_PIGKING`
 * - `VOICE_CHANGER_EFFECT_HULK`
 * - `PITCH_CORRECTION`
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_EFFECT_PRESET : uint8 {
	/** Turn off voice effects, that is, use the original voice.
	 */
	AUDIO_EFFECT_OFF = 0,
	/** The voice effect typical of a KTV venue.
	 */
	ROOM_ACOUSTICS_KTV,
	/** The voice effect typical of a concert hall.
	 */
	ROOM_ACOUSTICS_VOCAL_CONCERT,
	/** The voice effect typical of a recording studio.
	 */
	ROOM_ACOUSTICS_STUDIO,
	/** The voice effect typical of a vintage phonograph.
	 */
	ROOM_ACOUSTICS_PHONOGRAPH,
	/** The virtual stereo effect, which renders monophonic audio as stereo audio.
	 *
	 * @note Before using this preset, set the `profile` parameter of `setAudioProfile`
	 * to `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`;
	 * otherwise, the preset setting is invalid.
	 */
	ROOM_ACOUSTICS_VIRTUAL_STEREO,
	/** A more spatial voice effect.
	 */
	ROOM_ACOUSTICS_SPACIAL,
	/** A more ethereal voice effect.
	 */
	ROOM_ACOUSTICS_ETHEREAL,
	/** A 3D voice effect that makes the voice appear to be moving around the user. The default cycle
	 * period of the 3D voice effect is 10 seconds. To change the cycle period, call
	 * `setAudioEffectParameters` after this method.
	 *
	 * @note
	 * - Before using this preset, set the `profile` parameter of `setAudioProfile` to
	 * `AUDIO_PROFILE_MUSIC_STANDARD_STEREO` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO`; otherwise,
	 * the preset setting is invalid.
	 * - If the 3D voice effect is enabled, users need to use stereo audio playback devices to hear
	 * the anticipated voice effect.
	 */
	ROOM_ACOUSTICS_3D_VOICE,
	/** virtual suround sound.
	 *
	 * @note
	 * - Agora recommends using this enumerator to process virtual suround sound; otherwise, you may
	 * not hear the anticipated voice effect.
	 * - To achieve better audio effect quality, Agora recommends calling \ref
	 * IRtcEngine::setAudioProfile "setAudioProfile" and setting the `profile` parameter to
	 * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
	 * setting this enumerator.
	 */
	ROOM_ACOUSTICS_VIRTUAL_SURROUND_SOUND,
	/** The voice effect for chorus.
	 *
	 * @note: To achieve better audio effect quality, Agora recommends calling \ref
	 * IRtcEngine::setAudioProfile "setAudioProfile" and setting the `profile` parameter to
	 * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
	 * setting this enumerator.
	 */
	ROOM_ACOUSTICS_CHORUS,
	/** A middle-aged man's voice.
	 *
	 * @note
	 * Agora recommends using this enumerator to process a male-sounding voice; otherwise, you may
	 * not hear the anticipated voice effect.
	 */
	VOICE_CHANGER_EFFECT_UNCLE,
	/** A senior man's voice.
	 *
	 * @note Agora recommends using this enumerator to process a male-sounding voice; otherwise, you
	 * may not hear the anticipated voice effect.
	 */
	VOICE_CHANGER_EFFECT_OLDMAN,
	/** A boy's voice.
	 *
	 * @note Agora recommends using this enumerator to process a male-sounding voice; otherwise, you
	 * may not hear the anticipated voice effect.
	 */
	VOICE_CHANGER_EFFECT_BOY,
	/** A young woman's voice.
	 *
	 * @note
	 * - Agora recommends using this enumerator to process a female-sounding voice; otherwise, you may
	 * not hear the anticipated voice effect.
	 */
	VOICE_CHANGER_EFFECT_SISTER,
	/** A girl's voice.
	 *
	 * @note Agora recommends using this enumerator to process a female-sounding voice; otherwise, you
	 * may not hear the anticipated voice effect.
	 */
	VOICE_CHANGER_EFFECT_GIRL,
	/** The voice of Pig King, a character in Journey to the West who has a voice like a growling
	 * bear.
	 */
	VOICE_CHANGER_EFFECT_PIGKING,
	/** The Hulk's voice.
	 */
	VOICE_CHANGER_EFFECT_HULK,
	/** An audio effect typical of R&B music.
	 *
	 * @note Before using this preset, set the `profile` parameter of `setAudioProfile` to
	 - `AUDIO_PROFILE_MUSIC_HIGH_QUALITY` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO`; otherwise,
	 * the preset setting is invalid.
	 */
	STYLE_TRANSFORMATION_RNB,
	/** The voice effect typical of popular music.
	 *
	 * @note Before using this preset, set the `profile` parameter of `setAudioProfile` to
	 - `AUDIO_PROFILE_MUSIC_HIGH_QUALITY` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO`; otherwise,
	 * the preset setting is invalid.
	 */
	STYLE_TRANSFORMATION_POPULAR,
	/** A pitch correction effect that corrects the user's pitch based on the pitch of the natural C
	 * major scale. After setting this voice effect, you can call `setAudioEffectParameters` to adjust
	 * the basic mode of tuning and the pitch of the main tone.
	 */
	PITCH_CORRECTION,

	/** Todo:  Electronic sound, Magic tone haven't been implemented.
	 *
	 */
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_21_ENTRIES(EUABT_AUDIO_EFFECT_PRESET, agora::rtc::AUDIO_EFFECT_PRESET,
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



/** The options for SDK preset voice conversion.
 */
UENUM(BlueprintType)
enum class EUABT_VOICE_CONVERSION_PRESET :uint8 {
	/** Turn off voice conversion and use the original voice.
	 */
	VOICE_CONVERSION_OFF = 0,
	/** A gender-neutral voice. To avoid audio distortion, ensure that you use this enumerator to
	 * process a female-sounding voice.
	 */
	VOICE_CHANGER_NEUTRAL,
	/** A sweet voice. To avoid audio distortion, ensure that you use this enumerator to process a
	 * female-sounding voice.
	 */
	VOICE_CHANGER_SWEET,
	/** A steady voice. To avoid audio distortion, ensure that you use this enumerator to process a
	 * male-sounding voice.
	 */
	VOICE_CHANGER_SOLID,
	/** A deep voice. To avoid audio distortion, ensure that you use this enumerator to process a
	 * male-sounding voice.
	 */
	VOICE_CHANGER_BASS,
	/** A voice like a cartoon character.
	 */
	VOICE_CHANGER_CARTOON,
	/** A voice like a child.
	 */
	VOICE_CHANGER_CHILDLIKE,
	/** A voice like a phone operator.
	 */
	VOICE_CHANGER_PHONE_OPERATOR,
	/** A monster voice.
	 */
	VOICE_CHANGER_MONSTER,
	/** A voice like Transformers.
	 */
	VOICE_CHANGER_TRANSFORMERS,
	/** A voice like Groot.
	 */
	VOICE_CHANGER_GROOT,
	/** A voice like Darth Vader.
	 */
	VOICE_CHANGER_DARTH_VADER,
	/** A rough female voice.
	 */
	VOICE_CHANGER_IRON_LADY,
	/** A voice like Crayon Shin-chan.
	 */
	VOICE_CHANGER_SHIN_CHAN,
	/** A voice like a castrato.
	 */
	VOICE_CHANGER_GIRLISH_MAN,
	/** A voice like chipmunk.
	 */
	VOICE_CHANGER_CHIPMUNK,

};





GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_16_ENTRIES(EUABT_VOICE_CONVERSION_PRESET, agora::rtc::VOICE_CONVERSION_PRESET,
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


/**
 * The definition of SIMULCAST_STREAM_MODE
 */
UENUM(BlueprintType)
enum class EUABT_SIMULCAST_STREAM_MODE : uint8 {
	/*
	 * disable simulcast stream until receive request for enable simulcast stream by other broadcaster
	 */
	AUTO_SIMULCAST_STREAM = 0,
	/*
	 * disable simulcast stream
	 */
	DISABLE_SIMULCAST_STREAM,
	/*
	 * always enable simulcast stream
	 */
	ENABLE_SIMULCAST_STREAM,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_SIMULCAST_STREAM_MODE, agora::rtc::SIMULCAST_STREAM_MODE,
	AUTO_SIMULCAST_STREAM,
	DISABLE_SIMULCAST_STREAM,
	ENABLE_SIMULCAST_STREAM)


UENUM(BlueprintType)
enum class EUABT_CAMERA_STABILIZATION_MODE : uint8{
	/** The camera stabilization mode is disabled.
	 */
	CAMERA_STABILIZATION_MODE_OFF = 0,
	/** device choose stabilization mode automatically.
	 */
	CAMERA_STABILIZATION_MODE_AUTO,
	/** stabilization mode level 1.
	 */
	CAMERA_STABILIZATION_MODE_LEVEL_1,
	/** stabilization mode level 2.
	 */
	CAMERA_STABILIZATION_MODE_LEVEL_2,
	/** stabilization mode level 3.
	 */
	CAMERA_STABILIZATION_MODE_LEVEL_3,
	///** The maximum level of the camera stabilization mode.
	// */
	//CAMERA_STABILIZATION_MODE_MAX_LEVEL = CAMERA_STABILIZATION_MODE_LEVEL_3,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_5_ENTRIES(EUABT_CAMERA_STABILIZATION_MODE, agora::rtc::CAMERA_STABILIZATION_MODE,
	CAMERA_STABILIZATION_MODE_OFF,
	CAMERA_STABILIZATION_MODE_AUTO,
	CAMERA_STABILIZATION_MODE_LEVEL_1,
	CAMERA_STABILIZATION_MODE_LEVEL_2,
	CAMERA_STABILIZATION_MODE_LEVEL_3)


/**
 * The type of the shared target. Set in ScreenCaptureSourceInfo.
 */
UENUM(BlueprintType)
enum class EUABT_ScreenCaptureSourceType : uint8 {
	/** -1: Unknown type. */
	ScreenCaptureSourceType_Unknown = 0,
	/** 0: The shared target is a window.*/
	ScreenCaptureSourceType_Window,
	/** 1: The shared target is a screen of a particular monitor.*/
	ScreenCaptureSourceType_Screen,
	/** 2: Reserved parameter.*/
	ScreenCaptureSourceType_Custom,
};

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_ScreenCaptureSourceType, agora::rtc::ScreenCaptureSourceType,
	ScreenCaptureSourceType_Unknown,
	ScreenCaptureSourceType_Window,
	ScreenCaptureSourceType_Screen,
	ScreenCaptureSourceType_Custom)

#endif

/**
 * The screen sharing scenario.
 */
UENUM(BlueprintType)
enum class EUABT_SCREEN_SCENARIO_TYPE : uint8 {
	/**
	 * 1: Document. This scenario prioritizes the video quality of screen sharing and reduces the
	 * latency of the shared video for the receiver. If you share documents, slides, and tables,
	 * you can set this scenario.
	 */
	SCREEN_SCENARIO_DOCUMENT = 0,
	/**
	 * 2: Game. This scenario prioritizes the smoothness of screen sharing. If you share games, you
	 * can set this scenario.
	 */
	SCREEN_SCENARIO_GAMING,
	/**
	 * 3: Video. This scenario prioritizes the smoothness of screen sharing. If you share movies or
	 * live videos, you can set this scenario.
	 */
	SCREEN_SCENARIO_VIDEO,
	/**
	 * 4: Remote control. This scenario prioritizes the video quality of screen sharing and reduces
	 * the latency of the shared video for the receiver. If you share the device desktop being
	 * remotely controlled, you can set this scenario.
	 */
	SCREEN_SCENARIO_RDC,
};




GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_SCREEN_SCENARIO_TYPE, agora::rtc::SCREEN_SCENARIO_TYPE,
	SCREEN_SCENARIO_DOCUMENT,
	SCREEN_SCENARIO_GAMING,
	SCREEN_SCENARIO_VIDEO,
	SCREEN_SCENARIO_RDC)

/**
 * Audio sample rate types.
 */
UENUM(BlueprintType)
enum class EUABT_AUDIO_SAMPLE_RATE_TYPE:uint8 {
	/**
	 * 32000: 32 KHz.
	 */
	AUDIO_SAMPLE_RATE_32000 = 0,
	/**
	 * 44100: 44.1 KHz.
	 */
	AUDIO_SAMPLE_RATE_44100,
	/**
	 * 48000: 48 KHz.
	 */
	AUDIO_SAMPLE_RATE_48000,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_AUDIO_SAMPLE_RATE_TYPE, agora::rtc::AUDIO_SAMPLE_RATE_TYPE,
	AUDIO_SAMPLE_RATE_32000,
	AUDIO_SAMPLE_RATE_44100,
	AUDIO_SAMPLE_RATE_48000)

/**
 * The codec type of the output video.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_CODEC_TYPE_FOR_STREAM : uint8 {
	/**
	 * 1: H.264.
	 */
	VIDEO_CODEC_H264_FOR_STREAM = 0,
	/**
	 * 2: H.265.
	 */
	VIDEO_CODEC_H265_FOR_STREAM,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_VIDEO_CODEC_TYPE_FOR_STREAM, agora::rtc::VIDEO_CODEC_TYPE_FOR_STREAM,
	VIDEO_CODEC_H264_FOR_STREAM,
	VIDEO_CODEC_H265_FOR_STREAM)


/**
 * Video codec profile types.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_CODEC_PROFILE_TYPE : uint8 {
	/**
	 * 66: Baseline video codec profile. Generally used in video calls on mobile phones.
	 */
	VIDEO_CODEC_PROFILE_BASELINE = 0,
	/**
	 * 77: Main video codec profile. Generally used in mainstream electronics, such as MP4 players,
	 * portable video players, PSP, and iPads.
	 */
	VIDEO_CODEC_PROFILE_MAIN,
	/**
	 * 100: High video codec profile. Generally used in high-resolution broadcasts or television.
	 */
	VIDEO_CODEC_PROFILE_HIGH,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_VIDEO_CODEC_PROFILE_TYPE, agora::rtc::VIDEO_CODEC_PROFILE_TYPE,
	VIDEO_CODEC_PROFILE_BASELINE,
	VIDEO_CODEC_PROFILE_MAIN,
	VIDEO_CODEC_PROFILE_HIGH)

/**
 * The rotation information.
 */
UENUM(BlueprintType)
enum class EUABT_VIDEO_ORIENTATION : uint8 {
	/**
	 * 0: Rotate the video by 0 degree clockwise.
	 */
	VIDEO_ORIENTATION_0 = 0,
	/**
	 * 90: Rotate the video by 90 degrees clockwise.
	 */
	VIDEO_ORIENTATION_90,
	/**
	 * 180: Rotate the video by 180 degrees clockwise.
	 */
	VIDEO_ORIENTATION_180,
	/**
	 * 270: Rotate the video by 270 degrees clockwise.
	 */
	VIDEO_ORIENTATION_270
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_4_ENTRIES(EUABT_VIDEO_ORIENTATION, agora::rtc::VIDEO_ORIENTATION,
	VIDEO_ORIENTATION_0,
	VIDEO_ORIENTATION_90,
	VIDEO_ORIENTATION_180,
	VIDEO_ORIENTATION_270)



UENUM(BlueprintType)
enum class EUABT_PRIORITY_TYPE : uint8 {
	/** 50: High priority.
	 */
	PRIORITY_HIGH = 0,
	/** 100: (Default) normal priority.
	 */
	PRIORITY_NORMAL,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_PRIORITY_TYPE, agora::rtc::PRIORITY_TYPE,
	PRIORITY_HIGH,
	PRIORITY_NORMAL)

/** The options for SDK preset headphone equalizer.
 */
UENUM(BlueprintType)
enum class EUABT_HEADPHONE_EQUALIZER_PRESET : uint8 {
	/** Turn off headphone EQ and use the original voice.
	 */
	HEADPHONE_EQUALIZER_OFF = 0,
	/** For over-ear headphones.
	 */
	HEADPHONE_EQUALIZER_OVEREAR,
	/** For in-ear headphones.
	 */
	HEADPHONE_EQUALIZER_INEAR
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(EUABT_HEADPHONE_EQUALIZER_PRESET, agora::rtc::HEADPHONE_EQUALIZER_PRESET,
	HEADPHONE_EQUALIZER_OFF,
	HEADPHONE_EQUALIZER_OVEREAR,
	HEADPHONE_EQUALIZER_INEAR)



UENUM(BlueprintType)
enum class EUABT_FeatureType : uint8 {
	VIDEO_VIRTUAL_BACKGROUND = 0,
	VIDEO_BEAUTY_EFFECT = 1,
};



GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_2_ENTRIES(EUABT_FeatureType, agora::rtc::FeatureType,
	VIDEO_VIRTUAL_BACKGROUND,
	VIDEO_BEAUTY_EFFECT)

/**
 * The status of the last-mile network tests.
 */
UENUM(BlueprintType)
enum class EUABT_LASTMILE_PROBE_RESULT_STATE :uint8 {
	/**
	 * 1: The last-mile network probe test is complete.
	 */
	LASTMILE_PROBE_RESULT_COMPLETE = 0,
	/**
	 * 2: The last-mile network probe test is incomplete because the bandwidth estimation is not
	 * available due to limited test resources.
	 */
	LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE,
	/**
	 * 3: The last-mile network probe test is not carried out, probably due to poor network
	 * conditions.
	 */
	LASTMILE_PROBE_RESULT_UNAVAILABLE
};


GEN_UABTFUNC_SIGNATURE_ENUMCONVERSION_3_ENTRIES(
	EUABT_LASTMILE_PROBE_RESULT_STATE, agora::rtc::LASTMILE_PROBE_RESULT_STATE,
		LASTMILE_PROBE_RESULT_COMPLETE,
		LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE,
		LASTMILE_PROBE_RESULT_UNAVAILABLE)

#pragma endregion Enum Wrapper

