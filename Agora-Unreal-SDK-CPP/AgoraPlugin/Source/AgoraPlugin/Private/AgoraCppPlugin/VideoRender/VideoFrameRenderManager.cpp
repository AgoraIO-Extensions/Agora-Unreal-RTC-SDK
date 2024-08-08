#if AGORA_UESDK_ENABLE_VIDEO

#include "VideoFrameRenderManager.h"
#include "VideoFrameRender.h"
namespace agora {
	namespace rtc {
		namespace ue {

			void VideoFrameRenderManager::AddOneRender(UImage* RenderImage, VIDEO_SOURCE_TYPE SourceType, const char* ChannelId, uid_t Uid)
			{
				VideoFrameId _VideoFrameId = { SourceType,Uid,ChannelId };

				if (DataMapVideoRenders.Contains(_VideoFrameId))
				{
					DataMapVideoRenders[_VideoFrameId]->SetRenderImage(RenderImage);
				}
				else
				{
					TSharedPtr<VideoFrameRender> _VideoFrameRender = MakeShareable(new VideoFrameRender());
					_VideoFrameRender->Init(_VideoFrameId);
					_VideoFrameRender->SetRenderImage(RenderImage);
					DataMapVideoRenders.Add(_VideoFrameId, _VideoFrameRender);
				}
			}

			void VideoFrameRenderManager::ReleaseOneRender(VIDEO_SOURCE_TYPE SourceType, const char* ChannelId, uid_t Uid)
			{
				VideoFrameId FrameId = { SourceType,Uid,ChannelId };

				if (DataMapVideoRenders.Contains(FrameId))
				{
					DataMapVideoRenders[FrameId]->Clear();
					DataMapVideoRenders.Remove(FrameId);
				}
			}

			void VideoFrameRenderManager::ReleaseAll()
			{
				for (auto& OneVideoRender : DataMapVideoRenders)
				{
					OneVideoRender.Value->Clear();
				}
				DataMapVideoRenders.Empty();
			}

			void VideoFrameRenderManager::Tick(float DeltaTime)
			{
				for (auto& OneVideoRender : DataMapVideoRenders)
				{
					OneVideoRender.Value->OnTick();
				}
			}
		}
	}
}

#endif