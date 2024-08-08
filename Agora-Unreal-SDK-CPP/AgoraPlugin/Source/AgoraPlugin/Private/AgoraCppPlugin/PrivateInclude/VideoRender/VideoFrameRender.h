#pragma once

#if AGORA_UESDK_ENABLE_VIDEO

#include "DataTypes.h"

class UTexture2D;
class UImage;
class UTextureRenderTarget2D;
class VideoFrameDataManager;
class VideoFrame;

namespace agora {
	namespace rtc {
		namespace ue {

			class VideoFrameRender {
				
			public:
				VideoFrameRender();
				virtual ~VideoFrameRender();

				void Init(const VideoFrameId & FrameId);
				void Clear();
				void OnTick();
				
				void SetRenderImage(UImage* Image);

			private:
				void InitTexture2D(int Width,int Height);
				void CopyToTexture2D(VideoFrame* _VideoFrame);

				void UpdateImage();

				// CPU
				UTexture2D* RenderTexture = nullptr;


				
				// Base On Texture
				UImage* RenderImage = nullptr;


				// Another RenderTarget
				// GPU
				// UTextureRenderTarget2D* RenderTarget;


				VideoFrameId _VideoFrameId;
			};
		}
	}
}

#endif