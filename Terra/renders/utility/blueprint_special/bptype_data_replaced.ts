import {
  ClazzMethodReplacedContext_,
  rc_empty_data,
} from './bptype_data_replaced/helper';

export const map_clazz_method_replaced_context: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  'agora::media::IMediaEngine.pushVideoFrame': {
    ...rc_empty_data,
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

  'agora::rtc::IRtcEngine.getScreenCaptureSources': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      UAgoraBPuScreenCaptureSourceList * UAgoraBPuRtcEngine::GetScreenCaptureSources(const FUABT_SIZE & thumbSize, const FUABT_SIZE & iconSize, const bool & includeScreen)
  {
      // Need to be optimized
      UAgoraBPuScreenCaptureSourceList * FinalReturnResult = nullptr;


// #if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

//       // Convert UEBP to CppType
//       agora::rtc::SIZE Raw_thumbSize = thumbSize.CreateRawData();

//       agora::rtc::SIZE Raw_iconSize = iconSize.CreateRawData();

//       bool Raw_includeScreen = includeScreen;

//       // Call Native Method
      
//       auto ret = AgoraUERtcEngine::Get()->getScreenCaptureSources(Raw_thumbSize, Raw_iconSize, Raw_includeScreen);

// // Free Data if neeeded
//       thumbSize.FreeRawData(Raw_thumbSize);

//       iconSize.FreeRawData(Raw_iconSize);

      


//       UAgoraBPuScreenCaptureSourceList * ReturnVal = ret;
//       FinalReturnResult =  ReturnVal;



// #endif

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IMediaPlayer.setPlayerOptionInInt': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
int UAgoraBPuMediaPlayer::SetPlayerOptionInInt(const FString & key, int value)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);




      // Convert UEBP to CppType
      std::string Raw_key = TCHAR_TO_UTF8(*key);
      int Raw_value = value;

      // Call Native Method
      
      // REPLACE_REPLACE!!!
      auto ret = _NativePtr->setPlayerOption(Raw_key.c_str(), Raw_value);

      // Free Data if neeeded
      

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
        `,
  },

  'agora::rtc::IMediaPlayer.setPlayerOptionInString': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
    int UAgoraBPuMediaPlayer::SetPlayerOptionInString(const FString & key, const FString & value)
          {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      std::string Raw_key = TCHAR_TO_UTF8(*key);
      std::string Raw_value = TCHAR_TO_UTF8(*value);

      // Call Native Method
      
      auto ret = _NativePtr->setPlayerOption(Raw_key.c_str(), Raw_value.c_str());

// Free Data if neeeded
      

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;
        
          }
                `,
  },

  'agora::rtc::IMusicPlayer.openWithSongCode': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuMusicPlayer::OpenWithSongCode(int64 songCode, int64 startPos)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);




      // Convert UEBP to CppType
      int64_t Raw_songCode = songCode;
      int64_t Raw_startPos = startPos;

      // Call Native Method
      
      auto ret = _NativePtr->open(Raw_songCode, Raw_startPos);

      // Free Data if neeeded
      

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;


      // Need to be optimized
      return FinalReturnResult;

  }
                `,
  },
};
