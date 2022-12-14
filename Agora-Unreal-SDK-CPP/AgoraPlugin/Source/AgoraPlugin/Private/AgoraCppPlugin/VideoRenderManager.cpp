#include "AgoraCppPlugin/Include/VideoRenderManager.h"

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
                //std::lock_guard<std::mutex> lock(VideoRenderMutex);
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
                VideoFrameIdentity VideoFrameId(SourceType,Uid,ChannelId);
                //std::lock_guard<std::mutex> lock(VideoRenderMutex);
                auto it = VideoRenderMap.find(VideoFrameId);
                if (it == VideoRenderMap.end()) {
                    TSharedPtr<VideoRender> videoRender = MakeShareable(new VideoRender(DataManager::getInstance()->getCacheManager()));
                    VideoRenderMap[VideoFrameId] = videoRender;
                    videoRender->enableVideoFrameIdentity(RenderImage, VideoFrameId);
                }
                else {
                    it->second->enableVideoFrameIdentity(RenderImage, VideoFrameId);
                }
            }

            void VideoRenderManager::releaseVideoRender(unsigned int Uid, const char* ChannelId, VIDEO_SOURCE_TYPE SourceType)
            {
                VideoFrameIdentity VideoFrameId(SourceType, Uid, ChannelId);
                //std::lock_guard<std::mutex> lock(VideoRenderMutex);
                auto it = VideoRenderMap.find(VideoFrameId);
                if (it != VideoRenderMap.end()) {
                    VideoRenderMap[VideoFrameId].Reset();
                    VideoRenderMap.erase(it);
                }
            }

            void VideoRenderManager::releaseAllVideoRender()
            {
                //std::lock_guard<std::mutex> lock(VideoRenderMutex);
                VideoRenderMap.clear();
            }

            TStatId VideoRenderManager::GetStatId() const
            {
                return TStatId();
            }
        }
    }
}