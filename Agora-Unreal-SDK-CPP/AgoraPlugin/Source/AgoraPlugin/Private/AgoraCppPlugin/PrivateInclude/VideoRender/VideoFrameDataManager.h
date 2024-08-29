#pragma once
#include "CoreMinimal.h"
#include "DataTypes.h"
#include "AgoraHeaderBase.h"

namespace agora {
	namespace rtc {
		namespace ue {
			using namespace media;

			class VideoFrameBuffer
			{
				
			public:
				VideoFrameBuffer();

				virtual ~VideoFrameBuffer();

				void Init();

				int Push(VideoFrame* Frame);
				int Pop(VideoFrame*& Frame);

				void Clear();
	

				inline void SetStartUpdatingStatus(bool IsStartUpdating) {
					this->IsUpdating = IsStartUpdating;
				}

			private:
				void _ClearOneBuffer(VideoFrame* BufferFrame);
				int _CopyOneFrameToBuffer(VideoFrame* SrcFrame, VideoFrame* DstFrameBuffer);
				void _Swap();

				VideoFrame* FrontBufferFrame = nullptr;
				VideoFrame* BackBufferFrame = nullptr;
				bool IsUpdating = false;
				bool HasData = false;

				//Status Statistics
				bool IsFirstPop = true;
			};

			
	

			class VideoFrameDataManager {

			public:
				static VideoFrameDataManager* Get();
				static void Release();
				static VideoFrameDataManager* VideoFrameDataManagerInstance;

				void StartUpdatingOneVideoBuffer(const VideoFrameId& FrameId);
				void StopUpdatingOneVideoBuffer(const VideoFrameId& FrameId);

				int PushVideoFrame(const VideoFrameId& FrameId, VideoFrame* Frame);
				int PopVideoFrame(const VideoFrameId& FrameId, VideoFrame*& Frame);
				void ClearAll();

			private:
				FCriticalSection _CriticalSection;
				TMap<VideoFrameId, VideoFrameBuffer*> DataMapVideoFrameBuffers;
			};
		}
	}
}