import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  //TBD(WinterPu)
  // Custom Header Error
  'agora::rtc::ILocalSpatialAudioEngine.initialize': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
    UFUNCTION(BlueprintCallable,Category = "Agora|ILocalSpatialAudioEngine")
    int Initialize();
    `,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuLocalSpatialAudioEngine::Initialize()
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

    //   // Convert UEBP to CppType

    //   // Call Native Method
      
    //   auto ret = _NativePtr->initialize();

    //   // Free Data if neeeded

    //   int ReturnVal = ret;
    //   FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },
};
