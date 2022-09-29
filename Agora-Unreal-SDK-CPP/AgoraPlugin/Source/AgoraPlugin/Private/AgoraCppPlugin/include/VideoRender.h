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
                VideoRender(ICacheManager* CacheManager);
                ~VideoRender();

                void onTick();
                void enableVideoFrameIdentity(UImage* RenderImage, VideoFrameIdentity VideoFrameId);

            private:
                int getVideoFrame(const VideoFrameIdentity* Identity, VideoFrame*& Frame);

            private:
                ICacheManager* VideoCacheManager;
                UTexture2D* RenderTexture;
                FSlateBrush RenderBrush;
                UImage* RenderImage;
                VideoFrame* RenderVideoFrame;
                VideoFrameIdentity RenderFrameId;
                bool bEnableUpdatePreview;
                int ArgbPixSize;
            };
        }
    }
}
