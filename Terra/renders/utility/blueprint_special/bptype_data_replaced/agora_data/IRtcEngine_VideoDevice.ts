import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  'agora::rtc::IVideoDeviceManager.enumerateVideoDevices': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
    doReplceImpl: true,
    impl: `
  TArray<FUABT_VideoDeviceInfo> UAgoraBPuVideoDeviceManager::EnumerateVideoDevices()
  {
      // Need to be optimized
      TArray<FUABT_VideoDeviceInfo> FinalReturnResult ;

    //   // Convert UEBP to CppType

    //   // Call Native Method
      
    //   auto ret = _NativePtr->enumerateVideoDevices();

    //   // Free Data if neeeded

    //   TArray<FUABT_VideoDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::VideoDeviceInfo, FUABT_VideoDeviceInfo>(ReturnVal, ret, 1);
    //   FinalReturnResult =  ReturnVal;


      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },
};
