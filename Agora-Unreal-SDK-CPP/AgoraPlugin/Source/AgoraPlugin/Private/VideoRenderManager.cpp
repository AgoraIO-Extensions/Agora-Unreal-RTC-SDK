#include "Include/VideoRenderManager.h"

namespace agora {
    namespace rtc {
        namespace ue {

            VideoRenderManager::VideoRenderManager()
            {
               
            }

            VideoRenderManager::~VideoRenderManager()
            {
                releaseAllVideoRender();
            }

            void VideoRenderManager::Tick(float DeltaTime)
            {
                for (videoRenderIter = videoRenderMap_.begin(); videoRenderIter != videoRenderMap_.end(); videoRenderIter++)
                {
                    if (videoRenderIter->second!=nullptr)
                    {
                        videoRenderIter->second->onTick();
                    }
                }
            }

            void VideoRenderManager::setRenderImage(UImage* renderImage, unsigned int uid, const char* channelId, VIDEO_SOURCE_TYPE type)
            {
                VideoFrameIdentity videoFrameId;
                videoFrameId.channel = channelId;
                videoFrameId.id = uid;
                videoFrameId.type = type;

                std::lock_guard<std::mutex> lock(videoRenderMutex_);
                auto it = videoRenderMap_.find(videoFrameId);
                if (it == videoRenderMap_.end()) {
                    std::shared_ptr<VideoRender> videoRender = std::make_shared<VideoRender>(DataManager::getInstance()->getCacheManager());
                    videoRenderMap_[videoFrameId] = videoRender;
                    videoRender->enableVideoFrameIdentity(renderImage, videoFrameId);
                }
                else {
                    it->second->enableVideoFrameIdentity(renderImage, videoFrameId);
                }
            }

            void VideoRenderManager::releaseVideoRender(unsigned int uid, const char* channelId, VIDEO_SOURCE_TYPE type)
            {
                VideoFrameIdentity videoFrameId;
                videoFrameId.channel = channelId;
                videoFrameId.id = uid;
                videoFrameId.type = type;
                std::lock_guard<std::mutex> lock(videoRenderMutex_);
                auto it = videoRenderMap_.find(videoFrameId);
                if (it != videoRenderMap_.end()) {
                    videoRenderMap_[videoFrameId].reset();
                    videoRenderMap_.erase(it);
                }
            }

            void VideoRenderManager::releaseAllVideoRender()
            {
                std::lock_guard<std::mutex> lock(videoRenderMutex_);
                videoRenderMap_.clear();
            }

            TStatId VideoRenderManager::GetStatId() const
            {
                return TStatId();
            }
        }
    }
}