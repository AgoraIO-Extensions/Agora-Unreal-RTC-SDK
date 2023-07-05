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

/** connection state of sync service
 */
enum SYNC_CONNECTION_STATE_TYPE {
  /* The SDK is disconnected from the state sync server. */
  SYNC_CONNECTION_STATE_DISCONNECTED = 1,
  /* The SDK is connecting to the state sync server. */
  SYNC_CONNECTION_STATE_CONNECTING,
  /* The SDK is connected to the state sync server. */
  SYNC_CONNECTION_STATE_CONNECTED,
  /* The SDK is reconnecting to the state sync server. */
  SYNC_CONNECTION_STATE_RECONNECTING,
  /* The SDK is reconnected to the state sync server. */
  SYNC_CONNECTION_STATE_ABORTED
};

/** reason of connection state change of sync service
 */
enum SYNC_CONNECTION_CHANGED_REASON_TYPE {
  /* The connection state is changed. */
  SYNC_CONNECTION_CHANGED_DEFAULT = 0,
};

struct RoomStateItem {
  const char *key;
  const char *value;
  int64_t revision;
  RoomStateItem() : key(NULL), value(NULL), revision(-1) {}
};

struct RoomLockInfo {
  const char *ownerId;
  const char *key;
  const char *value;
  int64_t revision;
  int64_t updateTime;
  int64_t timeToLive;
};

struct UserStateItem {
  const char *key;
  const char *value;
};

class IStateSyncEventHandler {
public:
  virtual void onConnectionStateChanged(SYNC_CONNECTION_STATE_TYPE state, SYNC_CONNECTION_CHANGED_REASON_TYPE reason) {}
  virtual void onRequestToken() {}

  virtual void onJoinRoomSuccess(const char *roomName) {}
  virtual void onJoinRoomFailed(const char *roomName, int errorCode) {}
  virtual void onLeaveRoom(const char *roomName, int errorCode) {}
  virtual void onRemoteUserJoinedRoom(const char *roomName, const char *userId) {}
  virtual void onRemoteUserLeftRoom(const char *roomName, const char *userId) {}
  virtual void onGetRoomUsers(const char *roomName, const char *users[], int userCount, int errorCode) {}

  virtual void onRecvRoomMessage(const char *roomName, const char *userId, const uint8_t *msg, int len) {}
  virtual void onLockResult(const char *roomName, const char *lockName, int errorCode) {}
  virtual void onLockExpired(const char *roomName, const char *lockName) {}
  virtual void onUnlockResult(const char *roomName, const char *lockName, int errorCode) {}
  virtual void onRecvRoomState(const char *roomName, const RoomStateItem roomStateItems[], int count) {}
  virtual void onRecvUserState(const char *userId, const UserStateItem userStateItems[], int count) {}
};

struct StateSyncConfig {
  const char *appId;
  const char *token;
  const char *userId;
  IStateSyncEventHandler *eventHandler;
};

class IStateSync {
protected:
  virtual ~IStateSync() {}
public:
  virtual int release() = 0;

  virtual int initialize(const StateSyncConfig &cfg) = 0;
  virtual int uninitialize() = 0;

  virtual int addEventHandler(IStateSyncEventHandler *eventHandler) = 0;
  virtual int removeEventHandler(IStateSyncEventHandler *eventHandler) = 0;

  virtual int sendPeerMessage(const char *userId, const uint8_t *msg, int len) = 0;

  virtual int joinRoom(const char *roomName) = 0;
  virtual int leaveRoom(const char *roomName) = 0;
  virtual int renewToken(const char *token) = 0;

  virtual int getRoomUsers(const char *roomName) = 0;

  virtual int sendRoomMessage(const char *roomName, const uint8_t *msg, int len) = 0;

  virtual int tryLock(const char *roomName, const char *lockName) = 0;
  virtual int unlock(const char *roomName, const char *lockName) = 0;
  virtual int getLocks(const char *roomName, const RoomLockInfo **locks, int *locksCount) = 0;

  virtual int setRoomState(const char *roomName, const RoomStateItem items[], int count) = 0;
  virtual int deleteRoomState(const char *roomName, const char *keys[], int count) = 0;
  virtual int getRoomStates(const char *roomName) = 0;
  virtual int clearRoomStates(const char *roomName) = 0;

  virtual int subscribeUserState(const char *userId) = 0;
  virtual int setUserState(const UserStateItem items[], int count) = 0;
  virtual int deleteUserState(const char *keys[], int count) = 0;
  virtual int unsubscribeUserState(const char *userId) = 0;
};

}
}
