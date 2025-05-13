import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  'agora::media::IMediaEngine.pushVideoFrame': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuMediaEngine::PushVideoFrame(TArray<FUABT_ExternalVideoFrame> & frame, int64 videoTrackId)
    {
        // Need to be optimized
        int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);
  
      //   // Convert UEBP to CppType
      //   base::ExternalVideoFrame* Raw_frame = nullptr; UABT::New_CustomRawDataArray<base::ExternalVideoFrame, FUABT_ExternalVideoFrame>(Raw_frame,frame, 1);
  
      //   unsigned int Raw_videoTrackId = videoTrackId;
  
      //   // Call Native Method
        
      //   auto ret = _NativePtr->pushVideoFrame(Raw_frame, Raw_videoTrackId);
  
      //   // Free Data if neeeded
      //   UABT::Free_CustomRawDataArray<base::ExternalVideoFrame, FUABT_ExternalVideoFrame>(Raw_frame, 1);
  
      //   int ReturnVal = ret;
      //   FinalReturnResult =  ReturnVal;
  
        // Need to be optimized
        return FinalReturnResult;
    }
          `,
  },

  'agora::media::IMediaEngine.pushEncodedVideoImage': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuMediaEngine::PushEncodedVideoImage(const FString & imageBuffer, int64 length, const FUABT_EncodedVideoFrameInfo & videoEncodedFrameInfo, int64 videoTrackId)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

    // [Error] - ImageBuffer
    //   // Convert UEBP to CppType
    //   std::string Raw_imageBuffer = TCHAR_TO_UTF8(*imageBuffer);
    //   size_t Raw_length = length;
    //   agora::rtc::EncodedVideoFrameInfo Raw_videoEncodedFrameInfo = videoEncodedFrameInfo.CreateRawData();

    //   unsigned int Raw_videoTrackId = videoTrackId;

    //   // Call Native Method
      
    //   auto ret = _NativePtr->pushEncodedVideoImage(Raw_imageBuffer.c_str(), Raw_length, Raw_videoEncodedFrameInfo, Raw_videoTrackId);

    //   // Free Data if neeeded
    
    //   videoEncodedFrameInfo.FreeRawData(Raw_videoEncodedFrameInfo);

    //   int ReturnVal = ret;
    //   FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },
};
