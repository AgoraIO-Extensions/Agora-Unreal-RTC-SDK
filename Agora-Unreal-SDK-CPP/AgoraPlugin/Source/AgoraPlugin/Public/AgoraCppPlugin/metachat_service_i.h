//
//  Agora Rtc Engine SDK
//
//  Copyright (c) 2022 Agora.io. All rights reserved.
//
#pragma once

#include "meta_chat/IAgoraMetachat.h"

namespace agora {
namespace rtc {
namespace metachat {

class IMetachatSceneInternal: public IMetachatScene {
public:
  virtual int addEventHandler(IMetachatSceneEventHandler* eventHandler,
                      void (*deleter)(IMetachatSceneEventHandler*)) = 0;
};

}
}
}
