import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  // [Error]: return type val deference problem
  'agora::rtc::MusicChartCollection.get': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
    doReplceImpl: true,
    impl: `
      FUABT_MusicChartInfo UAgoraBPuMusicChartCollection::Get(int index)
  {
      // Need to be optimized
      FUABT_MusicChartInfo FinalReturnResult ;

      // Convert UEBP to CppType
      int Raw_index = index;

      // Call Native Method
      
      auto ret = _NativePtr->get(Raw_index);

      // Free Data if neeeded
      


      FUABT_MusicChartInfo ReturnVal = *ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;
  }
    `,
  },

  'agora::rtc::MusicCollection.getMusic': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
    doReplceImpl: true,
    impl: `
  FUABT_Music UAgoraBPuMusicCollection::GetMusic(int index)
  {
      // Need to be optimized
      FUABT_Music FinalReturnResult ;




      // Convert UEBP to CppType
      int32_t Raw_index = index;

      // Call Native Method
      
      auto ret = _NativePtr->getMusic(Raw_index);

      // Free Data if neeeded
      


      FUABT_Music ReturnVal = *ret;
      FinalReturnResult =  ReturnVal;




      // Need to be optimized
      return FinalReturnResult;

  }
      `,
  },
};
