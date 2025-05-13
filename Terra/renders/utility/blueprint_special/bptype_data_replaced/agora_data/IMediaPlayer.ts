import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  'agora::rtc::IMediaPlayer.setPlayerOptionInInt': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
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
    doReplceDecl: false,
    decl: ``,
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
};
