import { ClazzMethodReplacedContext_, rc_empty_data } from '../helper';

export const map_data: {
  [key: string]: ClazzMethodReplacedContext_;
} = {
  'agora::rtc::IRtcEngine.getScreenCaptureSources': {
    ...rc_empty_data,
    doReplceDecl: false,
    decl: ``,
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

  'agora::rtc::IRtcEngine.getVersion': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
    UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
    FString GetVersion();
    `,
    doReplceImpl: true,
    impl: `
      FString UAgoraBPuRtcEngine::GetVersion()
  { 
      return AgoraUERtcEngine::Get()->GetSDKVersion();
  }
    `,
  },

  // TBD(WinterPu)
  // pointer treat as Array
  'agora::rtc::IRtcEngine.leaveChannel': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int LeaveChannel(const FUABT_LeaveChannelOptions & options);
    `,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuRtcEngine::LeaveChannel(const FUABT_LeaveChannelOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);


      // Convert UEBP to CppType
      agora::rtc::LeaveChannelOptions Raw_options = options.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->leaveChannel(Raw_options);


      // Free Data if neeeded
      options.FreeRawData(Raw_options);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IRtcEngine.setClientRole': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int SetClientRole(EUABT_CLIENT_ROLE_TYPE role, const FUABT_ClientRoleOptions & options);
    `,
    doReplceImpl: true,
    impl: `
 int UAgoraBPuRtcEngine::SetClientRole(EUABT_CLIENT_ROLE_TYPE role, const FUABT_ClientRoleOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);


      // Convert UEBP to CppType
      agora::rtc::CLIENT_ROLE_TYPE Raw_role = UABTEnum::ToRawValue(role);

      agora::rtc::ClientRoleOptions Raw_options = options.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->setClientRole(Raw_role, Raw_options);

      // Free Data if neeeded
      
      options.FreeRawData(Raw_options);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
  `,
  },

  'agora::rtc::IRtcEngine.enableDualStreamMode': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int EnableDualStreamMode(bool enabled, const FUABT_SimulcastStreamConfig & streamConfig);
    `,
    doReplceImpl: true,
    impl: `
    int UAgoraBPuRtcEngine::EnableDualStreamMode(bool enabled, const FUABT_SimulcastStreamConfig & streamConfig)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      bool Raw_enabled = enabled;
      agora::rtc::SimulcastStreamConfig Raw_streamConfig = streamConfig.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->enableDualStreamMode(Raw_enabled, Raw_streamConfig);

      // Free Data if neeeded
      
      streamConfig.FreeRawData(Raw_streamConfig);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IRtcEngine.setDualStreamMode': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int SetDualStreamMode(EUABT_SIMULCAST_STREAM_MODE mode, const FUABT_SimulcastStreamConfig & streamConfig); 
    `,
    doReplceImpl: true,
    impl: `
    int UAgoraBPuRtcEngine::SetDualStreamMode(EUABT_SIMULCAST_STREAM_MODE mode, const FUABT_SimulcastStreamConfig & streamConfig)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);


      // Convert UEBP to CppType
      agora::rtc::SIMULCAST_STREAM_MODE Raw_mode = UABTEnum::ToRawValue(mode);

      agora::rtc::SimulcastStreamConfig Raw_streamConfig = streamConfig.CreateRawData();

      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->setDualStreamMode(Raw_mode, Raw_streamConfig);

      // Free Data if neeeded
      
      streamConfig.FreeRawData(Raw_streamConfig);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // TBD(WinterPu)
  // should be output
  'agora::rtc::IRtcEngine.getExtensionProperty': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int GetExtensionProperty(const FString & provider, const FString & extension, const FString & key, FString & value, int buf_len, EUABT_MEDIA_SOURCE_TYPE type);
    `,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuRtcEngine::GetExtensionProperty(const FString & provider, const FString & extension, const FString & key, FString & value, int buf_len, EUABT_MEDIA_SOURCE_TYPE type)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // // Convert UEBP to CppType
      // std::string Raw_provider = TCHAR_TO_UTF8(*provider);
      // std::string Raw_extension = TCHAR_TO_UTF8(*extension);
      // std::string Raw_key = TCHAR_TO_UTF8(*key);
      // std::string Raw_value = TCHAR_TO_UTF8(*value);
      // int Raw_buf_len = buf_len;
      // agora::media::MEDIA_SOURCE_TYPE Raw_type = UABTEnum::ToRawValue(type);


      // // Call Native Method
      
      // auto ret = AgoraUERtcEngine::Get()->getExtensionProperty(Raw_provider.c_str(), Raw_extension.c_str(), Raw_key.c_str(), Raw_value.c_str(), Raw_buf_len, Raw_type);

      // // Free Data if neeeded


      // int ReturnVal = ret;
      // FinalReturnResult =  ReturnVal;


      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // TBD(WinterPu)
  // FUABT macro scope problem

  'agora::rtc::IRtcEngine.startScreenCapture': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int StartScreenCapture(const FUABT_ScreenCaptureParameters2 & captureParams);
    `,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::StartScreenCapture(const FUABT_ScreenCaptureParameters2 & captureParams)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // // Convert UEBP to CppType
      // agora::rtc::ScreenCaptureParameters2 Raw_captureParams = captureParams.CreateRawData();


      // // Call Native Method
      
      // auto ret = AgoraUERtcEngine::Get()->startScreenCapture(Raw_captureParams);

      // // Free Data if neeeded
      // captureParams.FreeRawData(Raw_captureParams);



      // int ReturnVal = ret;
      // FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;
  }
    `,
  },

  // TBD(WinterPu)
  // remove node list removed streamId

  'agora::rtc::IRtcEngine.createDataStream': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int CreateDataStream(int streamId,const FUABT_DataStreamConfig & config);
    `,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuRtcEngine::CreateDataStream(int streamId, const FUABT_DataStreamConfig & config)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // // Convert UEBP to CppType
      // agora::rtc::DataStreamConfig Raw_config = config.CreateRawData();

      // // Call Native Method
      
      // auto ret = AgoraUERtcEngine::Get()->createDataStream(&streamId, Raw_config);

      // // Free Data if neeeded
      // config.FreeRawData(Raw_config);

      // int ReturnVal = ret;
      // FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // TBD(WinterPu)
  // pointer treat as Array
  'agora::rtc::IRtcEngine.joinChannelWithUserAccount': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int JoinChannelWithUserAccount(const FString & token, const FString & channelId, const FString & userAccount, const FUABT_ChannelMediaOptions & options);
    `,
    doReplceImpl: true,
    impl: `
    int UAgoraBPuRtcEngine::JoinChannelWithUserAccount(const FString & token, const FString & channelId, const FString & userAccount, const FUABT_ChannelMediaOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      std::string Raw_token = TCHAR_TO_UTF8(*token);
      std::string Raw_channelId = TCHAR_TO_UTF8(*channelId);
      std::string Raw_userAccount = TCHAR_TO_UTF8(*userAccount);
      agora::rtc::ChannelMediaOptions Raw_options = options.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->joinChannelWithUserAccount(Raw_token.c_str(), Raw_channelId.c_str(), Raw_userAccount.c_str(), Raw_options);

      // Free Data if neeeded
      
      options.FreeRawData(Raw_options);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // TBD(WinterPu)
  // lack eventhandler pointer
  'agora::rtc::IRtcEngine.joinChannelWithUserAccountEx': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int JoinChannelWithUserAccountEx(const FString & token, const FString & channelId, const FString & userAccount, const FUABT_ChannelMediaOptions & options);
    `,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::JoinChannelWithUserAccountEx(const FString & token, const FString & channelId, const FString & userAccount, const FUABT_ChannelMediaOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // // Convert UEBP to CppType
      // std::string Raw_token = TCHAR_TO_UTF8(*token);
      // std::string Raw_channelId = TCHAR_TO_UTF8(*channelId);
      // std::string Raw_userAccount = TCHAR_TO_UTF8(*userAccount);
      // agora::rtc::ChannelMediaOptions Raw_options = options.CreateRawData();


      // // Call Native Method
      
      // auto ret = AgoraUERtcEngine::Get()->joinChannelWithUserAccountEx(Raw_token.c_str(), Raw_channelId.c_str(), Raw_userAccount.c_str(), Raw_options);

      // // Free Data if neeeded
      
      // options.FreeRawData(Raw_options);

      // int ReturnVal = ret;
      // FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IRtcEngine.startScreenCaptureBySourceType': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
    int UAgoraBPuRtcEngine::StartScreenCaptureBySourceType(EUABT_VIDEO_SOURCE_TYPE sourceType, const FUABT_ScreenCaptureConfiguration & config)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      agora::rtc::VIDEO_SOURCE_TYPE Raw_sourceType = UABTEnum::ToRawValue(sourceType);

      agora::rtc::ScreenCaptureConfiguration Raw_config = config.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->startScreenCapture(Raw_sourceType, Raw_config);

      // Free Data if neeeded
      
      config.FreeRawData(Raw_config);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IRtcEngine.stopScreenCaptureBySourceType': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::StopScreenCaptureBySourceType(EUABT_VIDEO_SOURCE_TYPE sourceType)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      agora::rtc::VIDEO_SOURCE_TYPE Raw_sourceType = UABTEnum::ToRawValue(sourceType);


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->stopScreenCapture(Raw_sourceType);

      // Free Data if neeeded
      
      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IRtcEngine.startPreviewWithoutSourceType': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::StartPreviewWithoutSourceType()
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType

      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->startPreview();

      // Free Data if neeeded


      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }`,
  },

  // TBD(WinterPu)
  // Custom Header Changed
  'agora::rtc::IRtcEngine.sendMetaData': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::SendMetaData(const FUABT_Metadata & metadata, EUABT_VIDEO_SOURCE_TYPE source_type)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // // Convert UEBP to CppType
      // IMetadataObserver::Metadata Raw_metadata = metadata.CreateRawData();

      // agora::rtc::VIDEO_SOURCE_TYPE Raw_source_type = UABTEnum::ToRawValue(source_type);

      // // Call Native Method
      
      // auto ret = AgoraUERtcEngine::Get()->sendMetaData(Raw_metadata, Raw_source_type);

      // // Free Data if neeeded
      // metadata.FreeRawData(Raw_metadata);

      // int ReturnVal = ret;
      // FinalReturnResult =  ReturnVal;


      // Need to be optimized
      return FinalReturnResult;
  }
    `,
  },

  'agora::rtc::IRtcEngine.setMaxMetadataSize': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::SetMaxMetadataSize(int size)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // // Convert UEBP to CppType
      // int Raw_size = size;

      // // Call Native Method
      
      // auto ret = AgoraUERtcEngine::Get()->setMaxMetadataSize(Raw_size);

      // // Free Data if neeeded

      // int ReturnVal = ret;
      // FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // replace method name
  'agora::rtc::IRtcEngine.takeSnapshotWithConfig': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::TakeSnapshotWithConfig(int64 uid, const FUABT_SnapshotConfig & config)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);


      // Convert UEBP to CppType
      agora::rtc::uid_t Raw_uid = UABT::ToUID(uid);

      agora::media::SnapshotConfig Raw_config = config.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->takeSnapshot(Raw_uid, Raw_config);

      // Free Data if neeeded
      
      config.FreeRawData(Raw_config);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // TBD(WinterPu)
  // need EventHandler pointer
  'agora::rtc::IRtcEngine.joinChannelEx': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuRtcEngine::JoinChannelEx(const FString & token, const FUABT_RtcConnection & connection, const FUABT_ChannelMediaOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);


      // Convert UEBP to CppType
      std::string Raw_token = TCHAR_TO_UTF8(*token);
      agora::rtc::RtcConnection Raw_connection = connection.CreateRawData();

      agora::rtc::ChannelMediaOptions Raw_options = options.CreateRawData();

      // Call Native Method
      auto ret = AgoraUERtcEngine::Get()->joinChannelEx(Raw_token.c_str(), Raw_connection, Raw_options, nullptr);

      // Free Data if neeeded
      
      connection.FreeRawData(Raw_connection);

      options.FreeRawData(Raw_options);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // pointer treat as Array
  // const TArray<FUABT_LeaveChannelOptions> & options
  'agora::rtc::IRtcEngine.leaveChannelEx': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int LeaveChannelEx(const FUABT_RtcConnection & connection, const FUABT_LeaveChannelOptions & options);
    `,
    doReplceImpl: true,
    impl: `
  int UAgoraBPuRtcEngine::LeaveChannelEx(const FUABT_RtcConnection & connection, const FUABT_LeaveChannelOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);




      // Convert UEBP to CppType
      agora::rtc::RtcConnection Raw_connection = connection.CreateRawData();

      agora::rtc::LeaveChannelOptions Raw_options = options.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->leaveChannelEx(Raw_connection, Raw_options);

      // Free Data if neeeded
      connection.FreeRawData(Raw_connection);

      options.FreeRawData(Raw_options);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  // pointer treat as Array
  // const TArray<FUABT_LeaveChannelOptions> & options
  'agora::rtc::IRtcEngine.leaveChannelWithUserAccountEx': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int LeaveChannelWithUserAccountEx(const FString & channelId, const FString & userAccount, const FUABT_LeaveChannelOptions & options);
    `,
    doReplceImpl: true,
    impl: `
     int UAgoraBPuRtcEngine::LeaveChannelWithUserAccountEx(const FString & channelId, const FString & userAccount, const FUABT_LeaveChannelOptions & options)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);


      // Convert UEBP to CppType
      std::string Raw_channelId = TCHAR_TO_UTF8(*channelId);
      std::string Raw_userAccount = TCHAR_TO_UTF8(*userAccount);
      agora::rtc::LeaveChannelOptions Raw_options = options.CreateRawData();


      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->leaveChannelWithUserAccountEx(Raw_channelId.c_str(), Raw_userAccount.c_str(), Raw_options);

      // Free Data if neeeded
      
      options.FreeRawData(Raw_options);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  } 
    `,
  },

  'agora::rtc::IRtcEngine.createDataStreamEx': {
    ...rc_empty_data,
    doReplceDecl: true,
    declOp_IncludingComments: true,
    decl: `
  UFUNCTION(BlueprintCallable,Category = "Agora|IRtcEngine")
  int CreateDataStreamEx(int streamId, const FUABT_DataStreamConfig & config, const FUABT_RtcConnection & connection);
    `,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::CreateDataStreamEx(int streamId, const FUABT_DataStreamConfig & config, const FUABT_RtcConnection & connection)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      agora::rtc::DataStreamConfig Raw_config = config.CreateRawData();

      agora::rtc::RtcConnection Raw_connection = connection.CreateRawData();

      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->createDataStreamEx(&streamId, Raw_config, Raw_connection);

      // Free Data if neeeded
      config.FreeRawData(Raw_config);

      connection.FreeRawData(Raw_connection);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },

  'agora::rtc::IRtcEngine.takeSnapshotWithConfigEx': {
    ...rc_empty_data,
    doReplceImpl: true,
    impl: `
      int UAgoraBPuRtcEngine::TakeSnapshotWithConfigEx(const FUABT_RtcConnection & connection, int64 uid, const FUABT_SnapshotConfig & config)
  {
      // Need to be optimized
      int FinalReturnResult = AGORA_UE_ERR_CODE(ERROR_NULLPTR);

      // Convert UEBP to CppType
      agora::rtc::RtcConnection Raw_connection = connection.CreateRawData();

      agora::rtc::uid_t Raw_uid = UABT::ToUID(uid);

      agora::media::SnapshotConfig Raw_config = config.CreateRawData();

      // Call Native Method
      
      auto ret = AgoraUERtcEngine::Get()->takeSnapshotEx(Raw_connection, Raw_uid, Raw_config);

      // Free Data if neeeded
      connection.FreeRawData(Raw_connection);

      
      config.FreeRawData(Raw_config);

      int ReturnVal = ret;
      FinalReturnResult =  ReturnVal;

      // Need to be optimized
      return FinalReturnResult;

  }
    `,
  },
};
