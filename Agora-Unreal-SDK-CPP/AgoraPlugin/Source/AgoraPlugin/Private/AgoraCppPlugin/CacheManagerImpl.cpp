#if AGORA_UESDK_ENABLE_VIDEO

#include "AgoraCppPlugin/Include/CacheManagerImpl.h"
namespace agora {
	namespace rtc {
		namespace ue {

			void CacheManagerImpl::enableVideoFrameObserver(const VideoFrameIdentity* Identity)
			{
				std::lock_guard<std::recursive_mutex> lock(Mutex);

				// refresh the status to be true
				auto it = CacheMapStatus.find(*Identity);
				if (it == CacheMapStatus.end()) {
					CacheMapStatus[*Identity] = true;
				}
				else {
					it->second = true;
				}

				// if not found, insert a new item
				auto videoFrameIterator = DataMap.find(*Identity);
				if (videoFrameIterator == DataMap.end()) {
					auto frame = new FramesInfo();
					frame->CurrentFrame = new VideoFrame();
					frame->CurrentFrame->yBuffer = nullptr;
					frame->SwipFrame = new VideoFrame();
					frame->SwipFrame->yBuffer = nullptr;

					DataMap[*Identity] = frame;
				}
			}

			void CacheManagerImpl::disableVideoFrameObserver(const VideoFrameIdentity* Identity)
			{
				std::lock_guard<std::recursive_mutex> lock(Mutex);
				auto it = CacheMapStatus.find(*Identity);
				if (it == CacheMapStatus.end()) {
					return;
				}
				else {
					it->second = false;
				}
			}

			int CacheManagerImpl::pushVideo(const VideoFrameIdentity* Identity, VideoFrame* Frame)
			{
				std::lock_guard<std::recursive_mutex> lock(Mutex);
				if (Frame == nullptr)
				{
					return false;
				}

				auto it = CacheMapStatus.find(*Identity);
				if (it == CacheMapStatus.end()) {
					return CACHE_MANAGER_NOT_ENABLE;
				}

				if (it->second == false) {
					return CACHE_MANAGER_NOT_ENABLE;
				}

				auto iterator = DataMap.find(*Identity);

				if (iterator != DataMap.end()) {
					auto local_frames = iterator->second;

					if (!local_frames->CurrentFrame->yBuffer) {
						local_frames->CurrentFrame->yBuffer = (uint8*)malloc(Frame->width * Frame->height * 4);
					}

					if (local_frames->CurrentFrame->width != Frame->width || local_frames->CurrentFrame->height != Frame->height) {
						local_frames->CurrentFrame->yBuffer = (uint8*)realloc(local_frames->CurrentFrame->yBuffer, Frame->width * Frame->height * 4);
					}

					memcpy(local_frames->CurrentFrame->yBuffer, Frame->yBuffer, Frame->width * Frame->height * 4);
					local_frames->CurrentFrame->width = Frame->width;
					local_frames->CurrentFrame->height = Frame->height;
					local_frames->CurrentFrame->yStride = Frame->yStride;

					local_frames->bIsFresh = true;
				}
				return ERROR_OK;
			}

			int CacheManagerImpl::popVideo(const VideoFrameIdentity* Identity, VideoFrame*& Frame)
			{
				std::lock_guard<std::recursive_mutex> lock(Mutex);
				auto It = CacheMapStatus.find(*Identity);
				if (It == CacheMapStatus.end()) {
					return CACHE_MANAGER_NOT_ENABLE;
				}

				if (It->second == false) {
					return CACHE_MANAGER_NOT_ENABLE;
				}

				auto iterator = DataMap.find(*Identity);

				if (iterator != DataMap.end()) {
					auto Localframes = iterator->second;

					if (Localframes->CurrentFrame->yBuffer && Localframes->bIsFresh) {

						swap(Localframes->SwipFrame, Localframes->CurrentFrame);

						Frame = Localframes->SwipFrame;

						Localframes->bIsFresh = false;
					}
					else {
						return VIDEO_FRAME_BUFFER_EMPTY;
					}

					return ERROR_OK;
				}
				else {
					return CACHE_MANAGER_NOT_ENABLE;
				}

				return ERROR_OK;
			}

			void CacheManagerImpl::clear(const VideoFrameIdentity* Identity)
			{
				std::lock_guard<std::recursive_mutex> lock(Mutex);
				auto it = DataMap.find(*Identity);
				if (it == DataMap.end()) {
					return;
				}
				else {
					FramesInfo* frames = it->second;
					if (frames) {
						if (frames->CurrentFrame->yBuffer) {
							free(frames->CurrentFrame->yBuffer);
							frames->CurrentFrame->yBuffer = nullptr;
							delete(frames->CurrentFrame);
							frames->CurrentFrame = nullptr;
						}
						if (frames->SwipFrame->yBuffer) {
							free(frames->SwipFrame->yBuffer);
							frames->SwipFrame->yBuffer = nullptr;
							delete(frames->SwipFrame);
							frames->SwipFrame = nullptr;
						}
						delete frames;

					}
					DataMap.erase(it);
				}
			}

			void CacheManagerImpl::clearAll()
			{
				std::lock_guard<std::recursive_mutex> lock(Mutex);
				auto it = DataMap.begin();
				for (; it != DataMap.end(); it++) {
					clear(&(it->first));
				}
				DataMap.clear();
			}

			void CacheManagerImpl::swap(VideoFrame*& SwipFrame, VideoFrame*& CurrentFrame)
			{
				VideoFrame* Temp = SwipFrame;
				SwipFrame = CurrentFrame;
				CurrentFrame = Temp;
			}

			ICacheManager* createCacheManager() {
				return new CacheManagerImpl();
			}

		}
	}
}

#endif