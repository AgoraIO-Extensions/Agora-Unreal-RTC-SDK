#if AGORA_UESDK_ENABLE_VIDEO

#include "AgoraCppPlugin/Include/VideoRender.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "AgoraCppPlugin/Include/RtcEngineProxy.h"
#include "AgoraCppPlugin/Include/VideoObserverInternal.h"
namespace agora {
	namespace rtc {
		namespace ue {
			VideoRender::VideoRender(ICacheManager* CacheManager) :RenderFrameId(VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA, 0, "")
			{
				RenderTexture = nullptr;
				RenderVideoFrame = nullptr;
				RenderImage = nullptr;
				VideoCacheManager = CacheManager;
				bEnableUpdatePreview = false;
				ArgbPixSize = 4;
			}

			VideoRender::~VideoRender()
			{
				UE_LOG(LogTemp, Warning, TEXT("~VideoRender"));
				VideoCacheManager->clear(&RenderFrameId);
				RenderVideoFrame = nullptr;
				RenderImage = nullptr;
			}

			void VideoRender::onTick()
			{
				if (RenderImage == nullptr || bEnableUpdatePreview) {
					return;
				}
				int re = getVideoFrame(&RenderFrameId, RenderVideoFrame);
				if (re != ERROR_OK) {
					return;
				}
				if (!RenderVideoFrame) {
					return;
				}
				if (RenderTexture == nullptr || !RenderTexture->IsValidLowLevel() || RenderTexture->GetSizeX() != RenderVideoFrame->width || RenderTexture->GetSizeY() != RenderVideoFrame->height) {

					RenderTexture = UTexture2D::CreateTransient(RenderVideoFrame->width, RenderVideoFrame->height, PF_R8G8B8A8);
				}
				else
				{
					UTexture2D* tex = (UTexture2D*)RenderTexture;

					uint8* raw = (uint8*)tex->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					memcpy(raw, RenderVideoFrame->yBuffer, RenderVideoFrame->height * RenderVideoFrame->width * 4);
					tex->PlatformData->Mips[0].BulkData.Unlock();
					tex->UpdateResource();
					RenderBrush.SetResourceObject(tex);
					if (RenderImage != nullptr) {
						RenderImage->SetBrush(RenderBrush);
					}
				}
				//_texture->UpdateTextureRegions(0, 1, _region.get(), videoFrame_->yStride, (uint32)argbPixSize, static_cast<uint8_t*>(videoFrame_->yBuffer));
			}

			void VideoRender::enableVideoFrameIdentity(UImage* Image, VideoFrameIdentity VideoFrameId)
			{
				this->RenderImage = Image;
				RenderFrameId = VideoFrameId;
				VideoCacheManager->enableVideoFrameObserver(&RenderFrameId);
				bEnableUpdatePreview = false;
			}

			int VideoRender::getVideoFrame(const VideoFrameIdentity* Identity, VideoFrame*& Frame)
			{
				int ret = VideoCacheManager->popVideo(Identity, Frame);
				if (ret != 0) {
					return ret;
				}
				return ERROR_OK;
			}
		}
	}
}

#endif