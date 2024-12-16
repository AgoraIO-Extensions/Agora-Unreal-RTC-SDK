//
//  Agora Media SDK
//
//  Created by Sting Feng in 2015-05.
//  Copyright (c) 2015 Agora IO. All rights reserved.
//
#pragma once

#include <functional>
#include <string>
#include <vector>
#include <array>

#include "AgoraBase.h"
#include "IAgoraRtcEngineEx.h"
#include "NGIAgoraAudioDeviceManager.h"
#include "NGIAgoraExtensionProvider.h"
#include "NGIAgoraRtcConnection.h"
#include "time_utils.h"

#include <api/aosl_ref.h>

#if defined(_WIN32)
extern HINSTANCE GetCurrentModuleInstance();
#elif defined(__ANDROID__) || defined(__linux__)
#include <dlfcn.h>
#endif  // _WIN32

namespace agora {
namespace commons {
namespace cjson {
class JsonWrapper;
}  // namespace cjson

}  // namespace commons

namespace base {
class IParameterEngine {
 public:
  virtual int setParametersInternal(const char* parameters, int priority) = 0;
  virtual int getParameters(const char* key, commons::cjson::JsonWrapper& result) = 0;
  virtual ~IParameterEngine() {}
};
}  // namespace base

namespace media {
class IMediaRecorderObserverEx {
 public:
  /**
   * Occurs when the recording state changes.
   *
   * @since v4.0.0
   *
   * When the local audio and video recording state changes, the SDK triggers this callback to report the current
   * recording state and the reason for the change.
   *
   * @param state The current recording state. See \ref agora::media::RecorderState "RecorderState".
   * @param reason The reason for the state change. See \ref agora::media::RecorderReasonCode "RecorderReasonCode".
   */
  virtual void onRecorderStateChanged(RecorderState state, RecorderReasonCode reason) = 0;
  /**
   * Occurs when the recording information is updated.
   *
   * @since v4.0.0
   *
   * After you successfully register this callback and enable the local audio and video recording, the SDK periodically triggers
   * the `onRecorderInfoUpdated` callback based on the set value of `recorderInfoUpdateInterval`. This callback reports the
   * filename, duration, and size of the current recording file.
   *
   * @param info Information for the recording file. See RecorderInfo.
   *
   */
  virtual void onRecorderInfoUpdated(const RecorderInfo& info) = 0;

  virtual ~IMediaRecorderObserverEx() {}
};
}

namespace rtc {
class IMediaPlayerEx;

enum INTERFACE_ID_EX_TYPE {
  AGORA_IID_RTC_ENGINE_EX = 0xacbd,
};

enum SCREEN_SHARING_MODE { SCREEN_SHARING_NORMAL = 0, SCREEN_SHARING_MOVIE = 1 };

#ifdef INTERNAL_ENGINE_STATUS
struct InternalEngineStatus {
  int recfreq;
  int playoutfreq;
  int audio_send_frame_rate;
  int audio_send_packet_rate;
  int audio_recv_packet_rate;
  int nearin_signal_level;
  int nearout_signal_level;
  int farin_signal_level;
};
#endif  // INTERNAL_ENGINE_STATUS

enum class RecordingEventType : unsigned {
  RECORDING_EVENT_UNKNOWN,
  RECORDING_EVENT_START,
  RECORDING_EVENT_JOIN = RECORDING_EVENT_START,
  RECORDING_EVENT_LEAVE,

  RECORDING_EVENT_END = RECORDING_EVENT_LEAVE,
};

enum RecordingEventKeyIndex {
  // Join event
  RECORDING_JOIN_EVT_START = 1,
  RECORDING_JOIN_EVT_MIXMODE = RECORDING_JOIN_EVT_START,
  RECORDING_JOIN_EVT_MIXEDVIDEOAUDIOMODE = 2,
  RECORDING_JOIN_EVT_MIXHIGH = 3,
  RECORDING_JOIN_EVT_MIXLOW = 4,
  RECORDING_JOIN_EVT_MIXFPS = 5,
  RECORDING_JOIN_EVT_MIXKBPS = 6,
  RECORDING_JOIN_EVT_MINUDPPORT = 7,
  RECORDING_JOIN_EVT_MAXUDPPORT = 8,
  RECORDING_JOIN_EVT_DECODEAUDIOTYPE = 9,
  RECORDING_JOIN_EVT_DECODEVIDEOTYPE = 10,
  RECORDING_JOIN_EVT_LIVEMODE = 11,
  RECORDING_JOIN_EVT_IDLE = 12,
  RECORDING_JOIN_EVT_AUDIOONLY = 13,
  RECORDING_JOIN_EVT_VIDEOONLY = 14,  // NEW INSERT
  RECORDING_JOIN_EVT_SYSLOGFACILITY = 15,
  RECORDING_JOIN_EVT_STREAMTYPE = 16,
  RECORDING_JOIN_EVT_TRIGGERMODE = 17,
  RECORDING_JOIN_EVT_LANGUAGE = 18,
  RECORDING_JOIN_EVT_RESERVE1 = 19,

  // add new recording join event here ...

  MAX_RECORDING_JOIN_EVT_RESERVE15 = RECORDING_JOIN_EVT_RESERVE1 + 14,
  RECORDING_JOIN_EVT_MAX = MAX_RECORDING_JOIN_EVT_RESERVE15,

  // Leave event
  RECORDING_LEAVE_EVT_START = 101,
  RECORDING_LEAVE_EVT_LEAVEPATHCODE = RECORDING_LEAVE_EVT_START,
  RECORDING_LEAVE_EVT_RESERVE1,

  // add new recording leave event here ...

  RECORDING_LEAVE_EVT_RESERVE5 = RECORDING_LEAVE_EVT_RESERVE1 + 4,
  RECORDING_LEAVE_EVT_MAX = RECORDING_LEAVE_EVT_RESERVE5,
};

/**
 * The development type of app
 */
enum APP_TYPE {
  APP_TYPE_INVALID_VALUE = -1,
  APP_TYPE_NATIVE = 0,
  APP_TYPE_COCOS = 1,
  APP_TYPE_UNITY = 2,
  APP_TYPE_ELECTRON = 3,
  APP_TYPE_FLUTTER = 4,
  APP_TYPE_UNREAL = 5,
  APP_TYPE_XAMARIN = 6,
  APP_TYPE_APICLOUD = 7,
  APP_TYPE_REACT_NATIVE = 8,
  APP_TYPE_PYTHON = 9,
  APP_TYPE_COCOS_CREATOR = 10,
  APP_TYPE_RUST = 11,
  APP_TYPE_C_SHARP = 12,
  APP_TYPE_CEF = 13,
  APP_TYPE_UNI_APP = 14,
};

enum class RTC_EVENT {
  NATIVE_LOG = 100,
  ERROR_EVENT = 101,
  WARNING_EVENT = 102,
  MEDIA_ENGINE_LOAD_SUCCESS = 1002,
  MEDIA_ENGINE_START_CAMERA_SUCCESS = 1005,
  MEDIA_ENGINE_START_CALL_SUCCESS = 1006,
  VIDEO_STOPPED = 1007,
  TRANSPORT_QUALITY = 1101,
  AUDIO_QUALITY = 1102,
  TRANSPORT_SERVER_INSTANCE = 1103,
  MEDIA_ENGINE_EVENT = 1104,
  AUDIO_DEVICE_STATE_CHANGED = 1105,
  VIDEO_DEVICE_STATE_CHANGED = 1107,
  REQUEST_TOKEN = 1108,
  CLIENT_ROLE_CHANGED = 1109,
  PUBLISH_URL = 1110,
  UNPUBLISH_URL = 1111,
  LIVE_TRANSCODING = 1112,
  JOIN_PUBLISHER_REQUEST = 1113,
  JOIN_PUBILSHER_RESPONSE = 1114,
  REMOVE_PUBLISHER_REQUEST = 1115,
  STREAM_INJECTED_STATUS = 1116,
  PRIVILEGE_WILL_EXPIRE = 1117,
  LOCAL_VIDEO_STATE_CHANGED = 1118,
  RTMP_STREAMING_STATE = 1119,
  PUBLISH_STREAM_STATE = 1120,
  CLIENT_ROLE_CHANGE_FAILED = 1121,
  PUBLISH_STREAM_EVENT = 1122,

  OPEN_CHANNEL_SUCCESS = 13001,
  LEAVE_CHANNEL = 13006,
  NETWORK_QUALITY = 13007,
  USER_OFFLINE = 13008,
  RTC_STATS = 13010,
  USER_JOINED = 13013,
  USER_MUTE_AUDIO = 13014,
  USER_MUTE_VIDEO = 13015,
  USER_ENABLE_VIDEO = 13016,
  LASTMILE_QUALITY = 13017,
  AUDIO_EFFECT_FINISHED = 13018,
  USER_ENABLE_LOCAL_VIDEO = 13019,
  LASTMILE_PROBE_RESULT = 13020,
  UPLINK_NETWORK_INFO_UPDATE = 13021,
  DOWNLINK_NETWORK_INFO_UPDATE = 13022,
  USER_STATE_CHANGED = 13023,

  RECAP_INDICATION = 14000,
  AUDIO_VOLUME_INDICATION = 14001,
  FIRST_REMOTE_VIDEO_FRAME = 14002,
  LOCAL_VIDEO_STAT = 14003,
  REMOTE_VIDEO_STAT = 14004,
  FIRST_LOCAL_VIDEO_FRAME = 14005,
  FIRST_REMOTE_VIDEO_DECODED = 14007,
  CONNECTION_LOST = 14008,
  STREAM_MESSAGE = 14009,
  CONNECTION_INTERRUPTED = 14010,
  QUERY_RECORDING_SERVICE_STATUS = 14011,
  STREAM_MESSAGE_ERROR = 14012,
  VIDEO_SIZE_CHANGED = 14013,
  FIRST_LOCAL_AUDIO_FRAME_PUBLISHED = 14014,
  FIRST_LOCAL_VIDEO_FRAME_PUBLISHED = 14015,
  ACTIVE_SPEAKER = 14016,
  AUDIO_DEVICE_VOLUME_CHANGED = 14017,
#ifdef INTERNAL_ENGINE_STATUS
  _INTERNAL_ENGINE_STATUS = 14018,
#endif
  CONNECTION_BANNED = 14019,
  CAMERA_FOCUS_AREA_CHANGED = 14020,

  REMOTE_VIDEO_STATE_CHANGED = 14021,
  LOCAL_PUBLISH_FALLBACK_TO_AUDIO_ONLY = 14022,
  REMOTE_SUBSCRIBE_FALLBACK_TO_AUDIO_ONLY = 14023,
  USER_TRANSPORT_STAT = 14024,
  CONNECTION_STATE_CHANGED = 14028,
  CAMERA_EXPOSURE_AREA_CHANGED = 14029,
  REMOTE_AUDIO_STAT = 14030,
  NETWORK_TYPE_CHANGED = 14031,
  AUDIO_ROUTING_CHANGED = 14032,
  FIRST_REMOTE_AUDIO_DECODED = 14033,
  LOCAL_USER_REGISTERED = 14034,
  USER_INFO_UPDATED = 14035,
  REMOTE_VIDEO_STATE_CHANGED_EXT = 14036,
  CROSS_CHANNEL_STATE = 14037,
  CROSS_CHANNEL_EVENT = 14038,
  REMOTE_AUDIO_STATE_CHANGED = 14040,
  LOCAL_AUDIO_STAT = 14041,
  LOCAL_AUDIO_STATE_CHANGED = 14042,
  AUDIO_MIXING_STATE_CHANGED = 14043,
  INTRA_REQUEST_RECEIVED = 14044,
  PEER_USER_INFO_UPDATED = 14045,
  ENCRYPTION_ERROR_EVENT = 14046,
  REMOTE_VIDEO_STREAM_INFO_UPDATED = 14047,
  AUDIO_SUBSCRIBE_STATE_CHANGED = 14048,
  VIDEO_SUBSCRIBE_STATE_CHANGED = 14049,
  AUDIO_PUBLISH_STATE_CHANGED = 14050,
  VIDEO_PUBLISH_STATE_CHANGED = 14051,
  PERMISSION_ERROR_EVENT = 14052,
  FACE_DETECT_VALUE = 14053,
  RHYTHM_PLAYFR_STATE_CHANGED = 14054,
  UPLOAD_LOG_RESULT = 14055,
  FIRST_REMOTE_AUDIO_FRAME = 14058,
  PROXY_SUCCESS = 14059,
  WLACC_MESSAGE = 14060,
  WLACC_STATS = 14061,
  SNAPSHOT_TAKEN = 14062,
  CONTENT_INSPECT_RESULT = 14063,
  AUDIO_MIXING_POSITION_CHANGED = 14064,
  LICENSE_VERIFY = 14065,
  VIDEO_RENDERING_TRACING_RESULT = 14066,
  LOCAL_TRANSCODING = 14067,
  SET_RTM_FLAG_RESULT = 14068,
  VIDEO_LAYOUT_INFO = 14069,
  AUDIO_METADATA_RECEIVED = 14070,
};

struct video_transport_packet_info {
    uid_t uid;
    unsigned int frame_num;
    unsigned int sent_ts;
    unsigned int ts;
};

struct audio_transport_packet_info {
    uid_t uid;
    unsigned int ts;
    unsigned int sent_ts;
};


/**
 * The IPipStateChangedObserver class.
 */
class IPipStateChangedObserver {
public:
  virtual ~IPipStateChangedObserver() = default;

  virtual void onPipStateChanged(int pipState) {
    (void)pipState;
  }
};

class IRtcAvTransportPacketInfoObserver {
public:
  virtual ~IRtcAvTransportPacketInfoObserver() = default;

  virtual void onVideoTransportPacketInfo(const video_transport_packet_info& info) = 0;
  virtual void onAudioTransportPacketInfo(const audio_transport_packet_info& info) = 0;
};

struct RtcEngineContextInternal : public RtcEngineContext {
  bool isPassThruMode;
  int maxOutputBitrateKpbs;

  // extension event observer
  agora_refptr<IMediaExtensionObserver> extensionObserverProxy;

  // 0 for AGORA_CC,
  // 1 for REMB
  // 2 for TRANSPORT_CC
  bool is_p2p_switch_enabled_;

  RtcEngineContextInternal()
    : isPassThruMode(false),
      maxOutputBitrateKpbs(30 * 1000),
      extensionObserverProxy(nullptr),
#if defined(P2P_SWITCH_DEFAULT_VALUE)
      is_p2p_switch_enabled_(P2P_SWITCH_DEFAULT_VALUE)
#else
      is_p2p_switch_enabled_(false)
#endif
  {
  }
  explicit RtcEngineContextInternal(const RtcEngineContext& ctx);
};

struct WebAgentVideoStats {
  user_id_t userId;
  int delay;
  int sentFrameRate;
  int renderedFrameRate;
  int skippedFrames;
};

class IRtcEngineEventHandlerInternal : public IRtcEngineEventHandlerEx {
 public:
  virtual const char* eventHandlerType() const { return "event_handler_internal"; }

  virtual bool onEvent(RTC_EVENT evt, const std::string* payload) {
    (void)evt;
    (void)payload;

    /* return false to indicate this event is not handled */
    return false;
  }
};

class IRtcEngineInternal : public IRtcEngineEx,
                           public agora::base::IParameterEngine {
 protected:
   virtual ~IRtcEngineInternal() {}  
 public:
  virtual aosl_ref_t ref() = 0;
  virtual int initializeEx(const RtcEngineContextInternal& context) = 0;
  virtual int setProfile(const char* profile, bool merge) = 0;
  virtual int getProfile(std::string& result) = 0;
  virtual int initializeInternal(const RtcEngineContextInternal& context) = 0;

  virtual int setAudioOptionParams(const char* params) = 0;
  virtual int getAudioOptionParams(char* params) = 0;
  virtual bool isMicrophoneOn() = 0;

  virtual int reportWebAgentVideoStats(const WebAgentVideoStats& stats) = 0;

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IOS)
  virtual int monitorDeviceChange(bool enabled) = 0;
#endif  // __APPLE__ && !TARGET_OS_IOS && TARGET_OS_MAC

  virtual int printLog(int level, const char* message) = 0;
  virtual int runOnWorkerThread(std::function<void(void)>&& f) = 0;
  virtual int reportArgusCounters(int* counterId, int* value, int count, uid_t uid) = 0;

  virtual int enableYuvDumper(bool enable) = 0;

  // this function is only for expert of video codec,
  // please do NOT call it if not knowing what's it about
  virtual int setVideoConfigParam(const char* params) = 0;

  virtual int getVideoConfigParam(char* params, size_t size) = 0;

  virtual int setExternalVideoConfigEx(const VideoEncoderConfiguration& config) = 0;
  virtual int setExternalVideoConfigEx(const VideoEncoderConfiguration& config,
                                       const RtcConnection& connection) = 0;
  
  virtual int getParametersEx(const RtcConnection& connection, const char* key, std::string& results) = 0;

  // this function is only for switching screen capture source api on windows platform
#if defined(_WIN32)
  virtual int GetScreenCaptureType() = 0;
#endif

  virtual int setLogLevelEx(unsigned int filter) = 0;

  virtual int simulateOnSetParameters(const std::string& parameters) = 0;

  virtual int setCameraDevice(const char dev_id[MAX_DEVICE_ID_LENGTH]) = 0;

  virtual aosl_ref_t getMediaPlayer(int sourceId) = 0;
  virtual int putMediaPlayer(int sourceId) = 0;
  virtual agora_refptr<IRtcConnection> getConnection(const RtcConnection& connection = {}) const = 0;

#if defined(FEATURE_ENABLE_UT_SUPPORT)
  // 0 is left channel, 1 is right channel, -1 is invalid
  virtual int soundPositionChannel(uid_t uid) = 0;
  virtual int soundPositionChannel(uid_t uid, const RtcConnection& connection) = 0;
#endif

  virtual int32_t setAppType(APP_TYPE appType) = 0;
  virtual int32_t enableVosUserInfoHidden(bool enabled) = 0;

  virtual int setMediaRecorderObserver(const char* channelId, uid_t uid, bool isLocal,
                                        media::IMediaRecorderObserverEx* observer, int sys_version = 0) = 0;
  virtual int startRecording(const char* channelId, uid_t uid, bool isLocal,
                              const media::MediaRecorderConfiguration& config) = 0;
  virtual int stopRecording(const char* channelId, uid_t uid, bool isLocal) = 0;
  virtual int releaseRecorder(const char* channelId, uid_t uid, bool isLocal) = 0;

  virtual std::string getRecentSid(const RtcConnection* connnection) = 0;

  virtual int setupAudioAttributeContext(void* audioAttr) = 0;
#if defined(__ANDROID__)
  virtual int switchCameraId(const char* cameraId) = 0;
#endif // __ANDROID__
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
  virtual int switchCameraDirection(int direction) = 0;
#endif
  static bool isEventHandler(IRtcEngineEventHandler* handler) {
    return handler && 0 == strcmp("event_handler", handler->eventHandlerType());
  }

  static bool isEventHandlerEx(IRtcEngineEventHandler* handler) {
    return handler && 0 == strcmp("event_handler_ex", handler->eventHandlerType());
  }
};

class RtcEngineLibHelper {
  typedef const char*(AGORA_CALL* PFN_GetAgoraRtcEngineVersion)(int* build);
  typedef IRtcEngine*(AGORA_CALL* PFN_CreateAgoraRtcEngine)();
  typedef void(AGORA_CALL* PFN_ShutdownAgoraRtcEngineService)();

#if defined(_WIN32)
  typedef HINSTANCE lib_handle_t;
  static HINSTANCE MyLoadLibrary(const char* dllname) {
    char path[MAX_PATH];
    GetModuleFileNameA(GetCurrentModuleInstance(), path, MAX_PATH);
    auto p = strrchr(path, '\\');
    strcpy(p + 1, dllname);  // NOLINT
    HINSTANCE hDll = LoadLibraryA(path);
    if (hDll) return hDll;

    hDll = LoadLibraryA(dllname);
    return hDll;
  }
#else
  typedef void* lib_handle_t;
#endif  // _WIN32

 public:
  RtcEngineLibHelper(const char* dllname)
      : m_firstInit(true),
        m_lib(NULL),
        m_dllName(dllname),
        m_pfnCreateAgoraRtcEngine(nullptr),
        m_pfnGetAgoraRtcEngineVersion(nullptr) {}

  bool initialize() {
    if (!m_firstInit) {
      return isValid();
    }

    if (m_dllName.empty()) {
      return false;
    }

    m_firstInit = false;
#if defined(_WIN32)
    m_lib = MyLoadLibrary(m_dllName.c_str());
    if (m_lib) {
      m_pfnCreateAgoraRtcEngine =
          (PFN_CreateAgoraRtcEngine)GetProcAddress(m_lib, "createAgoraRtcEngine");
      m_pfnGetAgoraRtcEngineVersion =
          (PFN_GetAgoraRtcEngineVersion)GetProcAddress(m_lib, "getAgoraRtcEngineVersion");
    }
#elif defined(__ANDROID__) || defined(__linux__)
    m_lib = dlopen(m_dllName.c_str(), RTLD_LAZY);
    if (m_lib) {
      m_pfnCreateAgoraRtcEngine = (PFN_CreateAgoraRtcEngine)dlsym(m_lib, "createAgoraRtcEngine");
      m_pfnGetAgoraRtcEngineVersion =
          (PFN_GetAgoraRtcEngineVersion)dlsym(m_lib, "getAgoraRtcEngineVersion");
    }
#endif  // _WIN32

    return isValid();
  }

  void deinitialize() {
    if (m_lib) {
#if defined(_WIN32)
      FreeLibrary(m_lib);
#elif defined(__ANDROID__) || defined(__linux__)
      dlclose(m_lib);
#endif  // _WIN32

      m_lib = NULL;
    }

    m_pfnCreateAgoraRtcEngine = nullptr;
    m_pfnGetAgoraRtcEngineVersion = nullptr;
  }

  ~RtcEngineLibHelper() { deinitialize(); }

  bool isValid() { return m_pfnCreateAgoraRtcEngine != NULL; }

  agora::rtc::IRtcEngine* createEngine() {
    return m_pfnCreateAgoraRtcEngine ? m_pfnCreateAgoraRtcEngine() : NULL;
  }

  const char* getVersion(int* build) {
    return m_pfnGetAgoraRtcEngineVersion ? m_pfnGetAgoraRtcEngineVersion(build) : nullptr;
  }

 private:
  bool m_firstInit;
  lib_handle_t m_lib;
  std::string m_dllName;
  PFN_CreateAgoraRtcEngine m_pfnCreateAgoraRtcEngine;
  PFN_GetAgoraRtcEngineVersion m_pfnGetAgoraRtcEngineVersion;
};

// A helper function for decoding out the SEI layout

struct canvas_info {
  int width;
  int height;
  int bgcolor;
};

struct region_info {
  unsigned id;

  double x;
  double y;
  double width;
  double height;

  int alpha;  // [0, 255]

  int render_mode;  // 0, crop; 1, ZoomtoFit
  int zorder;       // [0, 100]
};

#define NUM_OF_LAYOUT_REGIONS 17

struct layout_info {
  long long ms;
  canvas_info canvas;
  // At most 9 broadcasters: 1 host, 8 guests.
  unsigned int region_count;
  region_info regions[NUM_OF_LAYOUT_REGIONS];
};

class EncryptionConfigInternal {
public:
  EncryptionConfigInternal(const EncryptionConfig& config) 
    : encryptionMode(config.encryptionMode), encryptionKey(config.encryptionKey ? config.encryptionKey : ""), datastreamEncryptionEnabled(config.datastreamEncryptionEnabled)
  {
    for(size_t i = 0; i < encryptionKdfSalt.size(); i++) {
      encryptionKdfSalt[i] = config.encryptionKdfSalt[i];
    }
  }
  void ToEncryptionConfig(EncryptionConfig& config) const {
    config.encryptionMode = encryptionMode;
    config.encryptionKey = encryptionKey.c_str();
    config.datastreamEncryptionEnabled = datastreamEncryptionEnabled;
    for(size_t i = 0; i < encryptionKdfSalt.size(); i++) {
      config.encryptionKdfSalt[i] = encryptionKdfSalt.at(i);
    }
  }
  ENCRYPTION_MODE encryptionMode;
  std::string encryptionKey;
  std::array<uint8_t, 32> encryptionKdfSalt;
  bool datastreamEncryptionEnabled;
};

AGORA_API bool AGORA_CALL decode_sei_layout(const void* data, unsigned size, layout_info* layout);

}  // namespace rtc
}  // namespace agora
