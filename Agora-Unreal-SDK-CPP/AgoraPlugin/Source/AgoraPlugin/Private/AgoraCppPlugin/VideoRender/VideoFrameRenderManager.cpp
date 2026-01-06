#if AGORA_UESDK_ENABLE_VIDEO

#include "VideoFrameRenderManager.h"
#include "VideoFrameRender.h"
#include "VideoRenderStatHelper.h"

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
				STATTimer += DeltaTime * 1000;
				for (auto& OneVideoRender : DataMapVideoRenders)
				{

					bool outRenderRet = false;
					OneVideoRender.Value->OnTick(outRenderRet);

					if(outRenderRet){
						// successfully rendered one frame
						STATTimeStamp_Cur = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();

						if(STATTimeStamp_Begin  < 0)
						{
							STATTimeStamp_Begin = STATTimeStamp_Cur;
						}
						else{
							double OneInterval = STATTimeStamp_Cur - STATTimeStamp_Begin;
							STATDATA_ArrRenderIntervals.Add(OneInterval);
							STATTimeStamp_Begin = STATTimeStamp_Cur;
						}
					}
				}
				UE_LOG(LogTemp,Warning,TEXT("StatTimer %f"), STATTimer);
				if(STATTimer < STATTimeInterval){
					// During the interval
				}
				else{
					// Over the interval, update the stats
					STAT_Update_All();
					STATTimer = 0;
					STATTimeStamp_Begin = -1;
				}
			}
		}
	}
}

#endif