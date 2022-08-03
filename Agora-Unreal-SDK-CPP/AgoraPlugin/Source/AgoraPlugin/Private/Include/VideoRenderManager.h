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

                void setRenderImage(UImage* renderImage, unsigned int uid, const char* channelId, VIDEO_SOURCE_TYPE type);

                void releaseVideoRender(unsigned int uid, const char* channelId, VIDEO_SOURCE_TYPE type);

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
                std::mutex videoRenderMutex_;

                std::map<VideoFrameIdentity, std::shared_ptr<VideoRender>> videoRenderMap_;

                std::map<VideoFrameIdentity, std::shared_ptr<VideoRender>>::iterator videoRenderIter;
            };

        }
    }
}