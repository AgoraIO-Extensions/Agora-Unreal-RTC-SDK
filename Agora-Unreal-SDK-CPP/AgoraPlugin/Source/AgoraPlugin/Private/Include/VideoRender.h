// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateOptMacros.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "DataManager.h"
#include "Engine/Texture2D.h"
#include "VideoObserverInternal.h"
#include "VideoRenderManager.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include <memory>

namespace agora {
    namespace rtc {
        namespace ue {

            using VideoFrame = media::IVideoFrameObserver::VideoFrame;

            class VideoRender
            {
            public:
                VideoRender(ICacheManager* cacheManager);
                ~VideoRender();

                void onTick();
                void enableVideoFrameIdentity(UImage* renderImage, VideoFrameIdentity videoFrameId);

            private:
                int getVideoFrame(const VideoFrameIdentity* identity, VideoFrame*& frame);

            private:
                ICacheManager* _videoCacheManager;
                UTexture2D* _texture;
                FSlateBrush Brush;
                std::unique_ptr<FUpdateTextureRegion2D> _region;
                UImage* uImage;
                VideoFrame* videoFrame_;
                VideoFrameIdentity id;
                bool _needUpdateInfo = true;
                bool _fresh;
                const int argbPixSize = 4;
            };
        }
    }
}
