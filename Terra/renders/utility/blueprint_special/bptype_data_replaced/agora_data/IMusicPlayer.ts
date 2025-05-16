import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  'agora::rtc::IMusicPlayer.openWithSongCode': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
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
