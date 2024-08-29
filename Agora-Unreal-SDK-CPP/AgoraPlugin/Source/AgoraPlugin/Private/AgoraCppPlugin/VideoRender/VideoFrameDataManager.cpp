#if AGORA_UESDK_ENABLE_VIDEO

#include "VideoFrameDataManager.h"

namespace agora {
	namespace rtc {
		namespace ue {

#pragma region VideoFrameBuffer

			void VideoFrameBuffer::_ClearOneBuffer(VideoFrame* BufferFrame)
			{
				if (BufferFrame) {
					FMemory::Free(BufferFrame->yBuffer);
					delete BufferFrame;
					BufferFrame = nullptr;
				}
			}

			int VideoFrameBuffer::_CopyOneFrameToBuffer(VideoFrame* SrcFrame, VideoFrame* DstFrameBuffer)
			{	
				if (SrcFrame == nullptr) {
					return AGORA_UE_ERR_CODE(ERROR_RENDER_NULL_FRAME);
				}

				if(DstFrameBuffer == nullptr){
					return AGORA_UE_ERR_CODE(ERROR_RENDER_NULL_BUFFER);
				}

				// make sure DstFrameBuffer has the same size as SrcFrame
				int SrcWidth = SrcFrame->width;
				int SrcHeight = SrcFrame->height;
				int TotalBytes = SrcWidth * SrcHeight * 4;

				// Empty
				if (DstFrameBuffer->yBuffer == nullptr) {
					DstFrameBuffer->yBuffer = static_cast<uint8*>(FMemory::Malloc(TotalBytes));
				}

				int DstBufferWidth = DstFrameBuffer->width;
				int DstBufferHeight = DstFrameBuffer->height;

				// Or Different Size
				if (SrcWidth != DstBufferWidth || SrcHeight != DstBufferHeight) {

					DstFrameBuffer->yBuffer = static_cast<uint8*>(FMemory::Realloc(DstFrameBuffer->yBuffer, TotalBytes));
				}

				FMemory::Memcpy(DstFrameBuffer->yBuffer,SrcFrame->yBuffer, TotalBytes);

				DstFrameBuffer->width = SrcFrame->width;
				DstFrameBuffer->height = SrcFrame->height;
				DstFrameBuffer->yStride = SrcFrame->yStride;

				return AGORA_UE_ERR_CODE(ERROR_OK);
			}


			VideoFrameBuffer::VideoFrameBuffer()
			{
				FrontBufferFrame = nullptr;
				BackBufferFrame = nullptr;
				Init();
			}

			VideoFrameBuffer::~VideoFrameBuffer(){
				Clear();
			}

			void VideoFrameBuffer::Init()
			{
				if (FrontBufferFrame == nullptr) {
					FrontBufferFrame = new VideoFrame();
					FrontBufferFrame->yBuffer = nullptr;
				}

				if (BackBufferFrame == nullptr) {
					BackBufferFrame = new VideoFrame();
					BackBufferFrame->yBuffer = nullptr;
				}

				IsUpdating = false;
				HasData = false;
				IsFirstPop = true;
			}

			int VideoFrameBuffer::Push(VideoFrame* Frame)
			{
				if (!IsUpdating) {
					return AGORA_UE_ERR_CODE(ERROR_RENDER_BUFFER_STOP_UPDATEING);
				}

				_CopyOneFrameToBuffer(Frame, BackBufferFrame);
				HasData = true;

				return AGORA_UE_ERR_CODE(ERROR_OK);
			}

			int VideoFrameBuffer::Pop(VideoFrame*& Frame)
			{
				if (HasData) {
					_Swap();
					//_ClearOneBuffer(BackBufferFrame);
					HasData = false;
					Frame = FrontBufferFrame;

					return AGORA_UE_ERR_CODE(ERROR_OK);
				}

				return AGORA_UE_ERR_CODE(ERROR_RENDER_NO_NEW_FRAME_DATA);
			}

			void VideoFrameBuffer::Clear()
			{
				_ClearOneBuffer(FrontBufferFrame);
				_ClearOneBuffer(BackBufferFrame);
				IsUpdating = false;
				HasData = false;
				IsFirstPop = true;
			}



			void VideoFrameBuffer::_Swap()
			{
				VideoFrame* Temp = FrontBufferFrame;
				FrontBufferFrame = BackBufferFrame;
				BackBufferFrame = Temp;
			}

#pragma endregion VideoFrameBuffer
 


 #pragma region VideoFrameDataManager


			VideoFrameDataManager* VideoFrameDataManager::VideoFrameDataManagerInstance = nullptr;

			void VideoFrameDataManager::StartUpdatingOneVideoBuffer(const VideoFrameId& FrameId)
			{
				FScopeLock Lock(&_CriticalSection);
				if (DataMapVideoFrameBuffers.Contains(FrameId)) {
					DataMapVideoFrameBuffers[FrameId]->SetStartUpdatingStatus(true);
				}
				else{
					VideoFrameBuffer* Buffer = new VideoFrameBuffer();
					DataMapVideoFrameBuffers.Add(FrameId, Buffer);
					Buffer->SetStartUpdatingStatus(true);
				}
			}

			void VideoFrameDataManager::StopUpdatingOneVideoBuffer(const VideoFrameId& FrameId)
			{
				FScopeLock Lock(&_CriticalSection);
				if (DataMapVideoFrameBuffers.Contains(FrameId)) {
					DataMapVideoFrameBuffers[FrameId]->SetStartUpdatingStatus(false);
				}
			}

			agora::rtc::ue::VideoFrameDataManager* VideoFrameDataManager::Get()
			{
				if(VideoFrameDataManagerInstance == nullptr){
					VideoFrameDataManagerInstance = new VideoFrameDataManager();
				}
				return VideoFrameDataManagerInstance;
			}

			void VideoFrameDataManager::Release()
			{
				if (VideoFrameDataManagerInstance) {
					VideoFrameDataManagerInstance->ClearAll();
					delete VideoFrameDataManagerInstance;
					VideoFrameDataManagerInstance = nullptr;
				}
			}

			int VideoFrameDataManager::PushVideoFrame(const VideoFrameId& FrameId, VideoFrame* Frame)
			{
				FScopeLock Lock(&_CriticalSection);

				if(Frame == nullptr){
					return AGORA_UE_ERR_CODE(ERROR_RENDER_NULL_FRAME);
				}

				if (!DataMapVideoFrameBuffers.Contains(FrameId)){
					return AGORA_UE_ERR_CODE(ERROR_RENDER_NULL_BUFFER);
				}
			
				int ret = DataMapVideoFrameBuffers[FrameId]->Push(Frame);
				return ret;
			}

			int VideoFrameDataManager::PopVideoFrame(const VideoFrameId& FrameId, VideoFrame*& Frame)
			{
				FScopeLock Lock(&_CriticalSection);

				// Frame would be nullptr, no need to check
				//if (Frame == nullptr) {
				//	return AGORA_UE_ERR_CODE(ERROR_RENDER_NULL_FRAME);
				//}

				if (!DataMapVideoFrameBuffers.Contains(FrameId)) {
					return AGORA_UE_ERR_CODE(ERROR_RENDER_NULL_BUFFER);
				}

				int ret = DataMapVideoFrameBuffers[FrameId]->Pop(Frame);

				return ret;
			}

			void VideoFrameDataManager::ClearAll()
			{
				FScopeLock Lock(&_CriticalSection);

				for (auto& OneVideoBuffer : DataMapVideoFrameBuffers) {
					OneVideoBuffer.Value->Clear();
					delete OneVideoBuffer.Value;
				}
				DataMapVideoFrameBuffers.Empty();
			}

#pragma endregion VideoFrameDataManager


		}
	}
}

#endif