// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateOptMacros.h"
#include "VideoRender.h"
#include "RtcEngineProxy.h"
#include "DataManager.h"
#include "VideoObserverInternal.h"
#include <memory>
#include <map>
#include "Tickable.h"
#include "Templates/SharedPointer.h"
/**
 *
 */
namespace agora {
    namespace rtc {
        namespace ue {

            class VideoRenderManager : public FTickableGameObject
            {
            public:
                VideoRenderManager();

                ~VideoRenderManager();

                void setRenderImage(UImage* RenderImage, unsigned int Uid, const char* ChannelId, VIDEO_SOURCE_TYPE SourceType);

                void releaseVideoRender(unsigned int Uid, const char* ChannelId, VIDEO_SOURCE_TYPE SourceType);

                void releaseAllVideoRender();

                virtual void Tick(float DeltaTime) override;

                virtual bool IsTickable() const override
                {
                    return true;
                }
                virtual bool IsTickableWhenPaused() const override
                {
                    return true;
                }

                virtual TStatId GetStatId() const override;

            private:
                //std::mutex VideoRenderMutex;

                std::map<VideoFrameIdentity, TSharedPtr<class VideoRender>> VideoRenderMap;

                std::map<VideoFrameIdentity, TSharedPtr<class VideoRender>>::iterator VideoRenderIter;
            };

        }
    }
}