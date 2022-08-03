#include "Include/VideoRender.h"
#include "Include/MediaEngineProxy.h"
#include "Include/AgoraHeaderBase.h"
#include "Include/RtcEngineProxy.h"
#include "Include/VideoObserverInternal.h"
namespace agora {
	namespace rtc {
		namespace ue {
			VideoRender::VideoRender(ICacheManager* cacheManager)
			{
				_texture = nullptr;
				videoFrame_ = nullptr;
				_videoCacheManager = cacheManager;
			}

			VideoRender::~VideoRender()
			{
				UE_LOG(LogTemp, Warning, TEXT("~VideoRender"));
				_videoCacheManager->clear(&id);
				videoFrame_ = nullptr;
				if (_texture != nullptr)
				{
					_texture->ReleaseResource();
					_texture = nullptr;
				}
			}

			void VideoRender::onTick()
			{
				if (uImage == nullptr || _needUpdateInfo) {
					return;
				}
				int re = getVideoFrame(&id, videoFrame_);
				//UE_LOG(LogTemp, Warning, TEXT("isFresh is : %d"), _fresh);
				if (re != ERROR_OK) {
					return;
				}
				if (!videoFrame_ /*|| !_fresh*/) {
					return;
				}
				if (_texture == nullptr || _texture->GetSizeX() != videoFrame_->width || _texture->GetSizeY() != videoFrame_->height) {
					//_region.reset(new FUpdateTextureRegion2D(0, 0, 0, 0, (uint32)videoFrame_->width, (uint32)videoFrame_->height));
					if (_texture != nullptr)
					{
						_texture->ReleaseResource();
						_texture = nullptr;
					}
					_texture = UTexture2D::CreateTransient(videoFrame_->width, videoFrame_->height, PF_R8G8B8A8);
				}
				else
				{
					UTexture2D* tex = (UTexture2D*)_texture;

					uint8* raw = (uint8*)tex->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					memcpy(raw, videoFrame_->yBuffer, videoFrame_->height * videoFrame_->width * 4);
					tex->PlatformData->Mips[0].BulkData.Unlock();
					tex->UpdateResource();
					Brush.SetResourceObject(tex);
					if (uImage != nullptr) {
						uImage->SetBrush(Brush);
					}
				}
				//_texture->UpdateTextureRegions(0, 1, _region.get(), videoFrame_->yStride, (uint32)argbPixSize, static_cast<uint8_t*>(videoFrame_->yBuffer));
			}

			void VideoRender::enableVideoFrameIdentity(UImage* renderImage, VideoFrameIdentity videoFrameId)
			{
				this->uImage = renderImage;
				id = videoFrameId;
				_videoCacheManager->enableVideoFrameObserver(&id);
				_needUpdateInfo = false;
			}

			int VideoRender::getVideoFrame(const VideoFrameIdentity* identity, VideoFrame*& frame)
			{
				int ret = _videoCacheManager->popVideo(identity, frame);
				if (ret != 0) {
					return ret;
				}
				return ERROR_OK;
			}
		}
	}
}