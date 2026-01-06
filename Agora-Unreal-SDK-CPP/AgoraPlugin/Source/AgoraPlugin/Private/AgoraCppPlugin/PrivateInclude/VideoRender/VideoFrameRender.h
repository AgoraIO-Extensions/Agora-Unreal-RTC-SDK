#pragma once

#if AGORA_UESDK_ENABLE_VIDEO

#include "DataTypes.h"
#include "AgoraMediaBase.h"

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
				void OnTick(bool& outRenderRet);
				
				void SetRenderImage(UImage* Image);

			private:
				void InitTexture2D(int Width,int Height);
				void CopyToTexture2D(VideoFrame* _VideoFrame);
				
				// Helper functions for color space handling
				bool NeedsColorSpaceConversion(const agora::media::base::ColorSpace& colorSpace);
				void ApplyColorRangeConversion(uint8* PixelData, int Width, int Height, const agora::media::base::ColorSpace& colorSpace);

				void UpdateImage();

				// CPU
				UTexture2D* RenderTexture = nullptr;
				
				// Store the current color space information
				agora::media::base::ColorSpace CurrentColorSpace;
				
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