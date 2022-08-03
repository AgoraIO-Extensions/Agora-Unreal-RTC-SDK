#include "Include/CacheManagerImpl.h"
namespace agora {
namespace rtc {
namespace ue {

void CacheManagerImpl::enableVideoFrameObserver(const VideoFrameIdentity *identity)
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	auto it = mapStatus_.find(*identity);
	if (it == mapStatus_.end()) {
		mapStatus_[*identity] = true;
	}
	else {
		it->second = true;
	}

	auto videoFrameIterator = data_map_.find(*identity);
	if (videoFrameIterator == data_map_.end()) {
		auto frame = new FramesInfo();
		frame->currentFrame = new VideoFrame();
		frame->currentFrame->yBuffer = nullptr;
		frame->swipFrame = new VideoFrame();
		frame->swipFrame->yBuffer = nullptr;

		data_map_[*identity] = frame;
	}
}

void CacheManagerImpl::disableVideoFrameObserver(const VideoFrameIdentity *identity)
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	auto it = mapStatus_.find(*identity);
	if (it == mapStatus_.end()) {
		return;
	}
	else {
		it->second = false;
	}
}

int CacheManagerImpl::pushVideo(const VideoFrameIdentity *identity, VideoFrame* frame)
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	if (frame == nullptr)
	{
		return false;
	}

	auto it = mapStatus_.find(*identity);
	if (it == mapStatus_.end()) {
		return CACHE_MANAGER_NOT_ENABLE;
	}

	if (it->second == false) {
		return CACHE_MANAGER_NOT_ENABLE;
	}
	
	auto iterator = data_map_.find(*identity);

	if (iterator != data_map_.end()) {
		auto local_frames = iterator->second;

		if (!local_frames->currentFrame->yBuffer) {
			local_frames->currentFrame->yBuffer = (uint8*)malloc(frame->width * frame->height * 4);
		}

		if (local_frames->currentFrame->width != frame->width || local_frames->currentFrame->height != frame->height) {
			local_frames->currentFrame->yBuffer = (uint8*)realloc(local_frames->currentFrame->yBuffer, frame->width * frame->height * 4);
		}

		memcpy(local_frames->currentFrame->yBuffer, frame->yBuffer, frame->width * frame->height * 4);
		local_frames->currentFrame->width = frame->width;
		local_frames->currentFrame->height = frame->height;
		local_frames->currentFrame->yStride = frame->yStride;

		local_frames->isFresh = true;
	}
	return ERROR_OK;
}

int CacheManagerImpl::popVideo(const VideoFrameIdentity *identity, VideoFrame*& frame)
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	auto it = mapStatus_.find(*identity);
	if (it == mapStatus_.end()) {
		return CACHE_MANAGER_NOT_ENABLE;
	}

	if (it->second == false) {
		return CACHE_MANAGER_NOT_ENABLE;
	}

	auto iterator = data_map_.find(*identity);

	if (iterator != data_map_.end()) {
		auto local_frames = iterator->second;

		if (local_frames->currentFrame->yBuffer&& local_frames->isFresh) {

			swap(local_frames->swipFrame, local_frames->currentFrame);

			frame = local_frames->swipFrame;

			local_frames->isFresh = false;
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

void CacheManagerImpl::clear(const VideoFrameIdentity *identity)
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	auto it = data_map_.find(*identity);
	if (it == data_map_.end()) {
		mutex_.unlock();
		return;
	}
	else {
		FramesInfo* frames = it->second;
		if (frames) {
			if (frames->currentFrame->yBuffer) {
				free(frames->currentFrame->yBuffer);
				frames->currentFrame->yBuffer = nullptr;
				delete(frames->currentFrame);
				frames->currentFrame = nullptr;
			}
			if (frames->swipFrame->yBuffer) {
				free(frames->swipFrame->yBuffer);
				frames->swipFrame->yBuffer = nullptr;
				delete(frames->swipFrame);
				frames->swipFrame = nullptr;
			}
			delete frames;
			data_map_.erase(it);
		}
	}
}

void CacheManagerImpl::clearAll()
{
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	auto it = data_map_.begin();
	for (; it != data_map_.end(); it++) {
		clear(&(it->first));
	}
	data_map_.clear();
}

void CacheManagerImpl::swap(VideoFrame*& swipFrame, VideoFrame*& currentFrame)
{
	VideoFrame* temp = swipFrame;
	swipFrame = currentFrame;
	currentFrame = temp;
}

ICacheManager* createCacheManager() {
	return new CacheManagerImpl();
}

}
}
}
