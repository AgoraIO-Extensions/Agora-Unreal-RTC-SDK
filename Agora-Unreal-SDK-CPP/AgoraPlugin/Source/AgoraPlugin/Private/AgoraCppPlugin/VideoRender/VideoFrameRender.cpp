#if AGORA_UESDK_ENABLE_VIDEO

#include "VideoFrameRender.h"

#include "AgoraHeaderBase.h"
#include "VideoFrameDataManager.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"

#include "Components/CanvasPanelSlot.h"


#include "VideoRenderStatHelper.h"


namespace agora {
	namespace rtc {
		namespace ue {

			VideoFrameRender::VideoFrameRender()
			{
			
			}

			VideoFrameRender::~VideoFrameRender()
			{
				
			}

			void VideoFrameRender::Init(const VideoFrameId& FrameId)
			{
				RenderTexture = nullptr;
				_VideoFrameId = FrameId;
				VideoFrameDataManager::Get()->StartUpdatingOneVideoBuffer(_VideoFrameId);
			}

			void VideoFrameRender::Clear()
			{
				VideoFrameDataManager::Get()->StopUpdatingOneVideoBuffer(_VideoFrameId);
			}

			void VideoFrameRender::OnTick(bool & outRenderRet)
			{
				outRenderRet = false;
				VideoFrame* RenderVideoFrame = nullptr;
				int ret = VideoFrameDataManager::Get()->PopVideoFrame(_VideoFrameId,RenderVideoFrame);
				
				if(AGORA_GET_ERR_TYPE(ret) != AGORA_UE_ERROR_CODE::ERROR_OK)
					return;

				STAT_RenderProcTime_Begin();

				if (RenderVideoFrame != nullptr) {
					CopyToTexture2D(RenderVideoFrame);

					if (RenderImage != nullptr)
					{
						UpdateImage();
					}
					INC_FLOAT_STAT_BY(STAT_OutFrameCounter,1);
				}
				
				STAT_RenderProcTime_End();
				outRenderRet = true;
			}

			void VideoFrameRender::SetRenderImage(UImage* Image)
			{
				RenderImage = Image;
			}

			void VideoFrameRender::InitTexture2D(int Width, int Height)
			{
				if (RenderTexture == nullptr || !RenderTexture->IsValidLowLevel() || RenderTexture->GetSizeX() != Width || RenderTexture->GetSizeY() != Height) {

					RenderTexture = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
				}
			}

			// Helper function to determine if we need to apply color space conversion
			bool VideoFrameRender::NeedsColorSpaceConversion(const agora::media::base::ColorSpace& colorSpace)
			{
				// Check if the color space is valid and different from default
				return colorSpace.validate() && 
					   (colorSpace.primaries != agora::media::base::ColorSpace::PRIMARYID_UNSPECIFIED ||
						colorSpace.transfer != agora::media::base::ColorSpace::TRANSFERID_UNSPECIFIED ||
						colorSpace.matrix != agora::media::base::ColorSpace::MATRIXID_UNSPECIFIED ||
						colorSpace.range != agora::media::base::ColorSpace::RANGEID_INVALID);
			}

			// Helper function to apply color range conversion
			void VideoFrameRender::ApplyColorRangeConversion(uint8* PixelData, int Width, int Height, const agora::media::base::ColorSpace& colorSpace)
			{
				// Only handle limited range to full range conversion for now
				if (colorSpace.range == agora::media::base::ColorSpace::RANGEID_LIMITED)
				{
					// Convert from limited range (16-235) to full range (0-255)
					const int TotalPixels = Width * Height;
					for (int i = 0; i < TotalPixels * 4; i += 4)
					{
						// Process RGB channels (skip Alpha)
						for (int c = 0; c < 3; c++)
						{
							int idx = i + c;
							float normalized = (PixelData[idx] - 16.0f) / (235.0f - 16.0f);
							normalized = FMath::Clamp(normalized, 0.0f, 1.0f);
							PixelData[idx] = static_cast<uint8>(normalized * 255.0f);
						}
					}
				}
			}

			void VideoFrameRender::CopyToTexture2D(VideoFrame* RenderFrame)
			{
				InitTexture2D(RenderFrame->width, RenderFrame->height);

				// Store the current color space
				CurrentColorSpace = RenderFrame->colorSpace;

				bool bNeedsConversion = NeedsColorSpaceConversion(RenderFrame->colorSpace);

#if AG_UE5_OR_LATER
				uint8* RawData = (uint8*)RenderTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(RawData, RenderFrame->yBuffer, RenderFrame->height * RenderFrame->width * 4);
				
				// Apply color space conversion if needed
				if (bNeedsConversion)
				{
					ApplyColorRangeConversion(RawData, RenderFrame->width, RenderFrame->height, RenderFrame->colorSpace);
				}

				RenderTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
				RenderTexture->UpdateResource();
#else
				uint8* RawData = (uint8*)RenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(RawData, RenderFrame->yBuffer, RenderFrame->height * RenderFrame->width * 4);

				// Apply color space conversion if needed
				if (bNeedsConversion)
				{
					ApplyColorRangeConversion(RawData, RenderFrame->width, RenderFrame->height, RenderFrame->colorSpace);
				}

				RenderTexture->PlatformData->Mips[0].BulkData.Unlock();
				RenderTexture->UpdateResource();
#endif


			}

			void VideoFrameRender::UpdateImage()
			{
				if (RenderImage != nullptr) {
					int Width = RenderTexture->GetSizeX();
					int Height = RenderTexture->GetSizeY();

					FSlateBrush RenderBrush;
					RenderBrush.SetResourceObject(RenderTexture);
					RenderBrush.SetImageSize(FVector2D(
						Width,
						Height
					));
					RenderImage->SetBrush(RenderBrush);

				}
			}

		}
	}
}

#endif