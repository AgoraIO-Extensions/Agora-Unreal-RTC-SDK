import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  //TBD(WinterPu)
  // Custom Header Error
  'agora::rtc::IAudioDeviceManager.enumeratePlaybackDevices': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IAudioDeviceManager")
  TArray<FUABT_AudioDeviceInfo> EnumeratePlaybackDevices();
    `,
    doReplceImpl: true,
    impl: `
  TArray<FUABT_AudioDeviceInfo> UAgoraBPuAudioDeviceManager::EnumeratePlaybackDevices()
  {
      // Need to be optimized
      TArray<FUABT_AudioDeviceInfo> FinalReturnResult ;


    //   // Convert UEBP to CppType

    //   // Call Native Method
      
    //   auto ret = _NativePtr->enumeratePlaybackDevices();

    //   // Free Data if neeeded


    //   TArray<FUABT_AudioDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::AudioDeviceInfo, FUABT_AudioDeviceInfo>(ReturnVal, ret, 1);
    //   FinalReturnResult =  ReturnVal;


      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  //TBD(WinterPu)
  // Custom Header Error
  'agora::rtc::IAudioDeviceManager.enumerateRecordingDevices': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IAudioDeviceManager")
  TArray<FUABT_AudioDeviceInfo> EnumerateRecordingDevices();
    `,
    doReplceImpl: true,
    impl: `
TArray<FUABT_AudioDeviceInfo> UAgoraBPuAudioDeviceManager::EnumerateRecordingDevices()
  {
      // Need to be optimized
      TArray<FUABT_AudioDeviceInfo> FinalReturnResult ;


    //   // Convert UEBP to CppType

    //   // Call Native Method
      
    //   auto ret = _NativePtr->enumerateRecordingDevices();

    //   // Free Data if neeeded


    //   TArray<FUABT_AudioDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::AudioDeviceInfo, FUABT_AudioDeviceInfo>(ReturnVal, ret, 1);
    //   FinalReturnResult =  ReturnVal;


      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  //TBD(WinterPu)
  // Custom Header Error
  'agora::rtc::IAudioDeviceManager.getPlaybackDeviceInfo': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IAudioDeviceManager")
  TArray<FUABT_AudioDeviceInfo> GetPlaybackDeviceInfo();
    `,
    doReplceImpl: true,
    impl: `
    TArray<FUABT_AudioDeviceInfo> UAgoraBPuAudioDeviceManager::GetPlaybackDeviceInfo()
  {
      // Need to be optimized
      TArray<FUABT_AudioDeviceInfo> FinalReturnResult ;

    //   // Convert UEBP to CppType

    //   // Call Native Method
      
    //   auto ret = _NativePtr->getPlaybackDeviceInfo();

    //   // Free Data if neeeded


    //   TArray<FUABT_AudioDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::AudioDeviceInfo, FUABT_AudioDeviceInfo>(ReturnVal, ret, 1);
    //   FinalReturnResult =  ReturnVal;




      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  //TBD(WinterPu)
  // Custom Header Error
  'agora::rtc::IAudioDeviceManager.getRecordingDeviceInfo': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IAudioDeviceManager")
  TArray<FUABT_AudioDeviceInfo> GetRecordingDeviceInfo();
    `,
    doReplceImpl: true,
    impl: `
    TArray<FUABT_AudioDeviceInfo> UAgoraBPuAudioDeviceManager::GetRecordingDeviceInfo()
  {
      // Need to be optimized
      TArray<FUABT_AudioDeviceInfo> FinalReturnResult ;


    //   // Convert UEBP to CppType

    //   // Call Native Method
      
    //   auto ret = _NativePtr->getRecordingDeviceInfo();

    //   // Free Data if neeeded


    //   TArray<FUABT_AudioDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::AudioDeviceInfo, FUABT_AudioDeviceInfo>(ReturnVal, ret, 1);
    //   FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },
};
