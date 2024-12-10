#if AGORA_UESDK_ENABLE_VIDEO

#include "VideoFrameRender.h"

#include "AgoraHeaderBase.h"
#include "VideoFrameDataManager.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"

#include "Components/CanvasPanelSlot.h"


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

			void VideoFrameRender::OnTick()
			{
				VideoFrame* RenderVideoFrame = nullptr;
				int ret = VideoFrameDataManager::Get()->PopVideoFrame(_VideoFrameId,RenderVideoFrame);
				
				if(AGORA_GET_ERR_TYPE(ret) != AGORA_UE_ERROR_CODE::ERROR_OK)
					return;

				if (RenderVideoFrame != nullptr) {
					CopyToTexture2D(RenderVideoFrame);

					if (RenderImage != nullptr)
					{
						UpdateImage();
					}
				}
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

			void VideoFrameRender::CopyToTexture2D(VideoFrame* RenderFrame)
			{
				InitTexture2D(RenderFrame->width, RenderFrame->height);

#if AG_UE5_OR_LATER
				uint8* RawData = (uint8*)RenderTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(RawData, RenderFrame->yBuffer, RenderFrame->height * RenderFrame->width * 4);
				RenderTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
				RenderTexture->UpdateResource();
#else
				uint8* RawData = (uint8*)RenderTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(RawData, RenderFrame->yBuffer, RenderFrame->height * RenderFrame->width * 4);
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