//
//  Agora SDK
//
//  Copyright (c) 2020 Agora.io. All rights reserved.
//
#pragma once  // NOLINT(build/header_guard)

#include <atomic>

#include "IAgoraMediaPlayer.h"

#include "../../api2/internal/video_node_i.h"
namespace agora {
namespace rtc {

class IMediaPlayerEx: public IMediaPlayer {
public:
  
  virtual void release() = 0;

  virtual agora_refptr<ILocalAudioTrack> getLocalAudioTrack() = 0;

  virtual agora_refptr<ILocalVideoTrack> getLocalVideoTrack() = 0;
  
  virtual int stopAsync() = 0;
  
  virtual int enableMusicMode(bool enable) = 0;

  int registerPlayerSourceObserver(IMediaPlayerSourceObserver* observer) final {
    return registerPlayerSourceObserverEx(observer, false);
  }

  virtual int registerPlayerSourceObserverEx(IMediaPlayerSourceObserver* observer, bool internal) = 0;

  virtual int setMirror(bool mirror)  = 0;

  virtual int setView(media::base::view_t view, IVideoRendererEx::ViewOption & option) = 0;
};

class IMediaPlayerCacheManagerEx: public IMediaPlayerCacheManager{
  public:
   static void SetRtcEngineInitialized(bool is_initialized);

  protected:
   static std::atomic_bool is_rtc_engine_initialized_;
};

} //namespace rtc
} // namespace agora
