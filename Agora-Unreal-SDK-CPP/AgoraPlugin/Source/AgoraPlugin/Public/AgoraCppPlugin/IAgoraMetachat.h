//
//  Agora Rtc Engine SDK
//
//  Copyright (c) 2022 Agora.io. All rights reserved.
//
#pragma once

#include "AgoraBase.h"
#include "AgoraMediaBase.h"

namespace agora {
namespace rtc {

typedef uint64_t SceneId;
typedef uint64_t AvatarId;

/** connection state of metachat service
 */
enum METACHAT_CONNECTION_STATE_TYPE {
  /* The SDK is disconnected from the state metachat server. */
  METACHAT_CONNECTION_STATE_DISCONNECTED = 1,
  /* The SDK is connecting to the state metachat server. */
  METACHAT_CONNECTION_STATE_CONNECTING,
  /* The SDK is connected to the state metachat server. */
  METACHAT_CONNECTION_STATE_CONNECTED,
  /* The SDK is reconnecting to the state metachat server. */
  METACHAT_CONNECTION_STATE_RECONNECTING,
  /* The SDK is reconnected to the state metachat server. */
  METACHAT_CONNECTION_STATE_ABORTED
};

/** reason of connection state change of sync service
 */
enum METACHAT_CONNECTION_CHANGED_REASON_TYPE {
  /* The connection state is changed. */
  METACHAT_CONNECTION_CHANGED_DEFAULT = 0,
};

enum METACHAT_SCENE_DOWNLOAD_STATE_TYPE {
  METACHAT_SCENE_DOWNLOAD_STATE_IDLE = 0,
  METACHAT_SCENE_DOWNLOAD_STATE_DOWNLOADING = 1,
  METACHAT_SCENE_DOWNLOAD_STATE_DOWNLOADED = 2,
  METACHAT_SCENE_DOWNLOAD_STATE_FAILED = 3
};

enum METACHAT_ERROR_TYPE {
  METACHAT_ERROR_OK = 0,
  METACHAT_ERROR_ENGINE_LOAD_FAILED,
  METACHAT_ERROR_SCENE_LOAD_FAILED,
  METACHAT_ERROR_JOIN_ROOM_FAILED,
  METACHAT_ERROR_SCENE_UNLOAD_FAILED,
};

// metachat avatar model information bound to metachat scene information
struct MetachatAvatarInfo {
  AvatarId avatarId;
  const char* avatarCode;
  const char* avatarName;
  const char* description;
  // local path of avatar model path
  const char* avatarPath;
  // local path of avatar thumbnail
  const char* thumbnailPath;
  // assets of the avatar bundle are needed to load scene
  const char* assets;
  // custom extra information
  const char* extraInfo;
  MetachatAvatarInfo() = default;
};

// metachat scene information retrieved by getScenes interface
struct MetachatSceneInfo {
  SceneId sceneId;
  const char* sceneName;
  // local path of scene thumbnail
  const char* thumbnailPath;
  // local path of scene model path
  const char* scenePath;
  const char* description;
  // config string is needed to load scene
  const char* sceneConfig;
  // assets of the scene bundle are needed to load scene
  const char* assets;
  // custom extra information
  const char* extraInfo;
  // avatar information bound to scene
  MetachatAvatarInfo *avatars;
  int32_t avatarCount;
  // version of scene
  const char* sceneVersion;
  // version of local scene
  const char* sceneLocalVersion;
  MetachatSceneInfo() = default;
};

struct MetachatUserInfo {
  const char *userId;
  const char *userName;
  const char *userIconUrl;
  MetachatUserInfo():userId(NULL), userName(NULL), userIconUrl(NULL) {}
};

struct MetachatUserPositionInfo {
  float position[3];
  float forward[3];
  float right[3];
  float up[3];
  MetachatUserPositionInfo() = default;
};

class IMetachatEventHandler {
public:
  virtual ~IMetachatEventHandler() {}

  virtual void onConnectionStateChanged(METACHAT_CONNECTION_STATE_TYPE state, METACHAT_CONNECTION_CHANGED_REASON_TYPE reason) {}
  virtual void onRequestToken() {}

  virtual void onGetScenesResult(const MetachatSceneInfo *scenes, int32_t count, int32_t errorCode) {}
  virtual void onDownloadSceneProgress(const MetachatSceneInfo &sceneInfo, int32_t progress, METACHAT_SCENE_DOWNLOAD_STATE_TYPE state) {}
};

class IMetachatSceneEventHandler {
public:
  virtual ~IMetachatSceneEventHandler() {}

  virtual void onEnterSceneResult(int errorCode) {}
  virtual void onLeaveSceneResult(int errorCode) {}

  virtual void onRecvMessageFromScene(const uint8_t *message, int32_t size) {}
  virtual void onUserPositionChanged(const char *uid, const MetachatUserPositionInfo &posInfo) {}
};

struct MetachatUserAvatarConfig {
  // avatarId is used to retrieve avatarInfo and load avatar
  const char* avatarCode;
  bool localVisible;
  bool remoteVisible;
  bool syncPosition;
  MetachatUserAvatarConfig() : avatarCode(NULL), localVisible(false), remoteVisible(false), syncPosition(false) {}
};

struct MetachatConfig {
  const char *appId;
  const char *token;
  MetachatUserInfo userInfo;
  IMetachatEventHandler *eventHandler;
  const char *localDownloadPath;
  MetachatConfig():appId(NULL), token(NULL), userInfo(), eventHandler(NULL), localDownloadPath(NULL) {}
};

class IMetachatScene {
protected:
  virtual ~IMetachatScene() {}
public:
  virtual int release() = 0;

  virtual int addEventHandler(IMetachatSceneEventHandler *eventHandler) = 0;
  virtual int removeEventHandler(IMetachatSceneEventHandler *eventHandler) = 0;

  virtual int enterScene(const MetachatSceneInfo &sceneInfo, const MetachatUserAvatarConfig &avatarConfig) = 0;
  virtual int leaveScene() = 0;

  virtual int sendMessageToScene(const uint8_t *message, int32_t size) = 0;

  virtual int setSceneParameters(const char *jsonParam) = 0;
  virtual int enableUserPositionNotification(bool enable) = 0;
  virtual int enableVideoDisplay(uint32_t displayId, bool enable) = 0;
  virtual int pushVideoFrameToDisplay(uint32_t displayId, const media::base::VideoFrame &frame) = 0;
  virtual int updateLocalAvatarConfig(const MetachatUserAvatarConfig &config) = 0;
};

class IMetachatService {
protected:
  virtual ~IMetachatService() {}
public:
  virtual int release() = 0;

  virtual int addEventHandler(IMetachatEventHandler *eventHandler) = 0;
  virtual int removeEventHandler(IMetachatEventHandler *eventHandler) = 0;

  virtual int initialize(const MetachatConfig &cfg) = 0;
  virtual int uninitialize() = 0;

  virtual int getScenes() = 0;
  virtual int isSceneDownloaded(SceneId sceneId) = 0;
  virtual int downloadScene(SceneId sceneId) = 0;
  virtual int cancelDownloadScene(SceneId sceneId) = 0;
  virtual int cleanScene(SceneId sceneId) = 0;

  virtual IMetachatScene *createScene(const char *roomName, const IMetachatSceneEventHandler *eventHandler) = 0;
};

}
}
