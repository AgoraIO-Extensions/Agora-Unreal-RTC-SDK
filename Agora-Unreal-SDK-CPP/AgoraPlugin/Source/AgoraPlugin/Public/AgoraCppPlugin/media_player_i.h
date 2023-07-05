//
//  Agora SDK
//
//  Copyright (c) 2020 Agora.io. All rights reserved.
//
#pragma once  // NOLINT(build/header_guard)

#include <atomic>

#include "IAgoraMediaPlayer.h"

namespace agora {
namespace rtc {

class IMediaPlayerEx: public IMediaPlayer {
public:
  
  virtual void release() = 0;

  static agora::agora_refptr<agora::rtc::IMediaPlayer> Create(
      media::base::MEDIA_PLAYER_SOURCE_TYPE type =
          media::base::MEDIA_PLAYER_SOURCE_TYPE::MEDIA_PLAYER_SOURCE_DEFAULT);

  virtual agora_refptr<ILocalAudioTrack> getLocalAudioTrack() = 0;

  virtual agora_refptr<ILocalVideoTrack> getLocalVideoTrack() = 0;

  virtual int waitForOpenCompleted(int ms) = 0;
  
  virtual int stopAsync() = 0;
  
  virtual int enableMusicMode(bool enable) = 0;
};

class IMediaPlayerCacheManagerEx: public IMediaPlayerCacheManager{
  public:
   static void SetRtcEngineInitialized(bool is_initialized);

  protected:
   static std::atomic_bool is_rtc_engine_initialized_;
};

} //namespace rtc
} // namespace agora
