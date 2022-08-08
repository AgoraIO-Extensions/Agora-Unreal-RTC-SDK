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
                for (VideoRenderIter = VideoRenderMap.begin(); VideoRenderIter != VideoRenderMap.end(); VideoRenderIter++)
                {
                    if (VideoRenderIter->second!=nullptr)
                    {
                        VideoRenderIter->second->onTick();
                    }
                }
            }

            void VideoRenderManager::setRenderImage(UImage* RenderImage, unsigned int Uid, const char* ChannelId, VIDEO_SOURCE_TYPE SourceType)
            {
                VideoFrameIdentity VideoFrameId;
                VideoFrameId.Channel = ChannelId;
                VideoFrameId.Id = Uid;
                VideoFrameId.Type = SourceType;

                std::lock_guard<std::mutex> lock(VideoRenderMutex);
                auto it = VideoRenderMap.find(VideoFrameId);
                if (it == VideoRenderMap.end()) {
                    std::shared_ptr<VideoRender> videoRender = std::make_shared<VideoRender>(DataManager::getInstance()->getCacheManager());
                    VideoRenderMap[VideoFrameId] = videoRender;
                    videoRender->enableVideoFrameIdentity(RenderImage, VideoFrameId);
                }
                else {
                    it->second->enableVideoFrameIdentity(RenderImage, VideoFrameId);
                }
            }

            void VideoRenderManager::releaseVideoRender(unsigned int Uid, const char* ChannelId, VIDEO_SOURCE_TYPE SourceType)
            {
                VideoFrameIdentity VideoFrameId;
                VideoFrameId.Channel = ChannelId;
                VideoFrameId.Id = Uid;
                VideoFrameId.Type = SourceType;
                std::lock_guard<std::mutex> lock(VideoRenderMutex);
                auto it = VideoRenderMap.find(VideoFrameId);
                if (it != VideoRenderMap.end()) {
                    VideoRenderMap[VideoFrameId].reset();
                    VideoRenderMap.erase(it);
                }
            }

            void VideoRenderManager::releaseAllVideoRender()
            {
                std::lock_guard<std::mutex> lock(VideoRenderMutex);
                VideoRenderMap.clear();
            }

            TStatId VideoRenderManager::GetStatId() const
            {
                return TStatId();
            }
        }
    }
}