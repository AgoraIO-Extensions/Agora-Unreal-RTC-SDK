#pragma once

#if AGORA_UESDK_ENABLE_VIDEO

#include "CoreMinimal.h"
#include "Tickable.h"
#include "DataTypes.h"

class UImage;

namespace agora {
	namespace rtc {
		namespace ue {

			class VideoFrameRenderManager : public FTickableGameObject
			{
			public:
				VideoFrameRenderManager() {}
				virtual ~VideoFrameRenderManager(){}
			
				void AddOneRender(UImage* RenderImage, VIDEO_SOURCE_TYPE SourceType,const char* ChannelId, uid_t Uid);

				void ReleaseOneRender(VIDEO_SOURCE_TYPE SourceType,const char* ChannelId, uid_t Uid);

				void ReleaseAll();

				virtual void Tick(float DeltaTime) override;

		
				virtual bool IsTickable() const override { return true; }

				virtual bool IsTickableWhenPaused() const override { return true; }

				virtual TStatId GetStatId() const override { return TStatId();}

			private:
				TMap<VideoFrameId, TSharedPtr<class VideoFrameRender>> DataMapVideoRenders;
			};
		}
	}
}

#endif