//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#if AGORA_UESDK_ENABLE_VIDEO

#include "CoreMinimal.h"
#include "SlateOptMacros.h"
#include "Components/Image.h"
#include "DataManager.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "VideoObserverInternal.h"
#include "VideoRenderManager.h"
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

#endif