// TBD(WinterPu)
// 1. add additional_postcontent for method
// Ex. blueprint pure function

export type ClazzAddtionalContext_ = {
  NativePtr: string;
  Inst: string;
  InitDecl: string;
  InitImpl: string;
};

// a static data member with an in-class initializer must have non-volatile const integral type or be specified as 'inline'

export const map_class_initialization: {
  [key: string]: ClazzAddtionalContext_;
} = {
  // Item: {
  //   NativePtr: ``, // In Called Function
  //   Inst: `
  //   `,
  //   InitDecl: `
  //   `,
  //   InitImpl: `
  //   `,
  // },

  // UE 425 - UPROPERTY() cannot be static
  IRtcEngine: {
    NativePtr: `AgoraUERtcEngine::Get()`,
    Inst: `
    	static UAgoraBPuRtcEngine* Instance;
        `,
    InitDecl: `
    	void InitInstance();
	    void UninitInstance();
      
      UFUNCTION(BlueprintPure, Category = "Agora|IRtcEngine")
      static UAgoraBPuRtcEngine* GetAgoraRtcEngine();
        `,
    InitImpl: `

      void UAgoraBPuRtcEngine::InitInstance()
      {
        // UserRtcEventHandler.Reset();
        // UserRtcEventHandlerEx.Reset();
        // UserScreenCaptureSourceList.Reset();
      }

      void UAgoraBPuRtcEngine::UninitInstance()
      {
        // UserRtcEventHandler.Reset();
        // UserRtcEventHandlerEx.Reset();
        // UserScreenCaptureSourceList.Reset();
      }

      UAgoraBPuRtcEngine* UAgoraBPuRtcEngine::Instance = nullptr;
      UAgoraBPuRtcEngine* UAgoraBPuRtcEngine::GetAgoraRtcEngine()
      {
        if (Instance == nullptr)
        {
          Instance = NewObject<UAgoraBPuRtcEngine>();
          Instance->AddToRoot();
          Instance->InitInstance();
        }
        return Instance;
      }
        `,
  },
  IAudioDeviceManager: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuAudioDeviceManager* InsAudioDeviceManager;
      
      agora::rtc::IAudioDeviceManager* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IAudioDeviceManager")
      static UAgoraBPuAudioDeviceManager* GetAgoraAudioDeviceManager();
      `,
    InitImpl: `
      UAgoraBPuAudioDeviceManager* UAgoraBPuAudioDeviceManager::InsAudioDeviceManager = nullptr;
      UAgoraBPuAudioDeviceManager* UAgoraBPuAudioDeviceManager::GetAgoraAudioDeviceManager(){
        if (InsAudioDeviceManager == nullptr)
        {
          InsAudioDeviceManager = NewObject<UAgoraBPuAudioDeviceManager>();
          InsAudioDeviceManager->AddToRoot();
          AgoraUERtcEngine::Get()->queryInterface(agora::rtc::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&InsAudioDeviceManager->_NativePtr);
  
          if(InsAudioDeviceManager->_NativePtr == nullptr){
          
            UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);
  
          }
  
          //InsAudioDeviceManager->PlaybackDeviceCollection = NewObject<UAudioDeviceCollection>();
  
          //InsAudioDeviceManager->RecordDeviceCollection = NewObject<UAudioDeviceCollection>();
        }
        return InsAudioDeviceManager;
      }
      `,
  },

  IVideoDeviceManager: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuVideoDeviceManager* InsVideoDeviceManager;
      
      agora::rtc::IVideoDeviceManager* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IVideoDeviceManager")
      static UAgoraBPuVideoDeviceManager* GetAgoraVideoDeviceManager();
      `,
    InitImpl: `
      UAgoraBPuVideoDeviceManager* UAgoraBPuVideoDeviceManager::InsVideoDeviceManager = nullptr;
      UAgoraBPuVideoDeviceManager* UAgoraBPuVideoDeviceManager::GetAgoraVideoDeviceManager()
      {
        if (InsVideoDeviceManager == nullptr)
        {
          InsVideoDeviceManager = NewObject<UAgoraBPuVideoDeviceManager>();
          InsVideoDeviceManager->AddToRoot();
          AgoraUERtcEngine::Get()->queryInterface(agora::rtc::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&InsVideoDeviceManager->_NativePtr);
  
          if (InsVideoDeviceManager->_NativePtr == nullptr) {
  
            UAgoraBPuLogger::PrintError("VideoDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);
  
            // InsVideoDeviceManager->VideoDeviceCollection = nullptr;
          }
          else{
          
            // InsVideoDeviceManager->VideoDeviceCollection = NewObject<UVideoDeviceCollection>();
          
          }
        }
        return InsVideoDeviceManager;
      }
  `,
  },

  IMediaPlayer: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaPlayer* InsMediaPlayer;
      
      agora::rtc::IMediaPlayer* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaPlayer")
      static UAgoraBPuMediaPlayer* GetAgoraMediaPlayer();
      `,
    InitImpl: `
      UAgoraBPuMediaPlayer* UAgoraBPuMediaPlayer::InsMediaPlayer = nullptr;
      UAgoraBPuMediaPlayer* UAgoraBPuMediaPlayer::GetAgoraMediaPlayer()
      {
        if (InsMediaPlayer == nullptr)
        {
          InsMediaPlayer = NewObject<UAgoraBPuMediaPlayer>();
          InsMediaPlayer->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaPlayer;
      }
      `,
  },
  IMediaRecorder: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaRecorder* InsMediaRecorder;
      
      agora::rtc::IMediaRecorder* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaRecorder")
      static UAgoraBPuMediaRecorder* GetAgoraMediaRecorder();
      `,
    InitImpl: `
      UAgoraBPuMediaRecorder* UAgoraBPuMediaRecorder::InsMediaRecorder = nullptr;
      UAgoraBPuMediaRecorder* UAgoraBPuMediaRecorder::GetAgoraMediaRecorder()
      {
        if (InsMediaRecorder == nullptr)
        {
          InsMediaRecorder = NewObject<UAgoraBPuMediaRecorder>();
          InsMediaRecorder->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaRecorder;
      }
      `,
  },
  IMediaStreamingSource: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaStreamingSource* InsMediaStreamingSource;
      
      agora::rtc::IMediaStreamingSource* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaStreamingSource")
      static UAgoraBPuMediaStreamingSource* GetAgoraMediaStreamingSource();
      `,
    InitImpl: `
      UAgoraBPuMediaStreamingSource* UAgoraBPuMediaStreamingSource::InsMediaStreamingSource = nullptr;
      UAgoraBPuMediaStreamingSource* UAgoraBPuMediaStreamingSource::GetAgoraMediaStreamingSource()
      {
        if (InsMediaStreamingSource == nullptr)
        {
          InsMediaStreamingSource = NewObject<UAgoraBPuMediaStreamingSource>();
          InsMediaStreamingSource->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaStreamingSource;
      }
      `,
  },
  IMediaEngine: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaEngine* InsMediaEngine;
      
      agora::media::IMediaEngine* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaEngine")
      static UAgoraBPuMediaEngine* GetAgoraMediaEngine();
      `,
    InitImpl: `
      UAgoraBPuMediaEngine* UAgoraBPuMediaEngine::InsMediaEngine = nullptr;
      UAgoraBPuMediaEngine* UAgoraBPuMediaEngine::GetAgoraMediaEngine()
      {
        if (InsMediaEngine == nullptr)
        {
          InsMediaEngine = NewObject<UAgoraBPuMediaEngine>();
          InsMediaEngine->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaEngine;
      }
      `,
  },
  IMediaPlayerSource: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaPlayerSource* InsMediaPlayerSource;
      
      agora::rtc::IMediaPlayerSource* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaPlayerSource")
      static UAgoraBPuMediaPlayerSource* GetAgoraMediaPlayerSource();
      `,
    InitImpl: `
      UAgoraBPuMediaPlayerSource* UAgoraBPuMediaPlayerSource::InsMediaPlayerSource = nullptr;
      UAgoraBPuMediaPlayerSource* UAgoraBPuMediaPlayerSource::GetAgoraMediaPlayerSource()
      {
        if (InsMediaPlayerSource == nullptr)
        {
          InsMediaPlayerSource = NewObject<UAgoraBPuMediaPlayerSource>();
          InsMediaPlayerSource->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaPlayerSource;
      }
      `,
  },
  ILocalSpatialAudioEngine: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuLocalSpatialAudioEngine* InsLocalSpatialAudioEngine;
      
      agora::rtc::ILocalSpatialAudioEngine* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|ILocalSpatialAudioEngine")
      static UAgoraBPuLocalSpatialAudioEngine* GetAgoraLocalSpatialAudioEngine();
      `,
    InitImpl: `
      UAgoraBPuLocalSpatialAudioEngine* UAgoraBPuLocalSpatialAudioEngine::InsLocalSpatialAudioEngine = nullptr;
      UAgoraBPuLocalSpatialAudioEngine* UAgoraBPuLocalSpatialAudioEngine::GetAgoraLocalSpatialAudioEngine()
      {
        if (InsLocalSpatialAudioEngine == nullptr)
        {
          InsLocalSpatialAudioEngine = NewObject<UAgoraBPuLocalSpatialAudioEngine>();
          InsLocalSpatialAudioEngine->AddToRoot();
          // TBD(WinterPu)
        }
        return InsLocalSpatialAudioEngine;
      }
      `,
  },
  MusicChartCollection: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMusicChartCollection* InsMusicChartCollection;
      
      agora::rtc::MusicChartCollection* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMusicChartCollection")
      static UAgoraBPuMusicChartCollection* GetAgoraMusicChartCollection();
      `,
    InitImpl: `
      UAgoraBPuMusicChartCollection* UAgoraBPuMusicChartCollection::InsMusicChartCollection = nullptr;
      UAgoraBPuMusicChartCollection* UAgoraBPuMusicChartCollection::GetAgoraMusicChartCollection()
      {
        if (InsMusicChartCollection == nullptr)
        {
          InsMusicChartCollection = NewObject<UAgoraBPuMusicChartCollection>();
          InsMusicChartCollection->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMusicChartCollection;
      }
      `,
  },
  IH265Transcoder: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuH265Transcoder* InsH265Transcoder;
      
      agora::rtc::IH265Transcoder* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IH265Transcoder")
      static UAgoraBPuH265Transcoder* GetAgoraH265Transcoder();
      `,
    InitImpl: `
      UAgoraBPuH265Transcoder* UAgoraBPuH265Transcoder::InsH265Transcoder = nullptr;
      UAgoraBPuH265Transcoder* UAgoraBPuH265Transcoder::GetAgoraH265Transcoder()
      {
        if (InsH265Transcoder == nullptr)
        {
          InsH265Transcoder = NewObject<UAgoraBPuH265Transcoder>();
          InsH265Transcoder->AddToRoot();
          // TBD(WinterPu)
        }
        return InsH265Transcoder;
      }
      `,
  },
  IMediaRecorderObserver: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaRecorderObserver* InsMediaRecorderObserver;
      
      agora::media::IMediaRecorderObserver* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaRecorderObserver")
      static UAgoraBPuMediaRecorderObserver* GetAgoraMediaRecorderObserver();
      `,
    InitImpl: `
      UAgoraBPuMediaRecorderObserver* UAgoraBPuMediaRecorderObserver::InsMediaRecorderObserver = nullptr;
      UAgoraBPuMediaRecorderObserver* UAgoraBPuMediaRecorderObserver::GetAgoraMediaRecorderObserver()
      {
        if (InsMediaRecorderObserver == nullptr)
        {
          InsMediaRecorderObserver = NewObject<UAgoraBPuMediaRecorderObserver>();
          InsMediaRecorderObserver->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaRecorderObserver;
      }
      `,
  },
  IMediaPlayerSourceObserver: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaPlayerSourceObserver* InsMediaPlayerSourceObserver;
      
      agora::rtc::IMediaPlayerSourceObserver* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaPlayerSourceObserver")
      static UAgoraBPuMediaPlayerSourceObserver* GetAgoraMediaPlayerSourceObserver();
      `,
    InitImpl: `
      UAgoraBPuMediaPlayerSourceObserver* UAgoraBPuMediaPlayerSourceObserver::InsMediaPlayerSourceObserver = nullptr;
      UAgoraBPuMediaPlayerSourceObserver* UAgoraBPuMediaPlayerSourceObserver::GetAgoraMediaPlayerSourceObserver()
      {
        if (InsMediaPlayerSourceObserver == nullptr)
        {
          InsMediaPlayerSourceObserver = NewObject<UAgoraBPuMediaPlayerSourceObserver>();
          InsMediaPlayerSourceObserver->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaPlayerSourceObserver;
      }
      `,
  },
  IH265TranscoderObserver: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuH265TranscoderObserver* InsH265TranscoderObserver;
      
      agora::rtc::IH265TranscoderObserver* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IH265TranscoderObserver")
      static UAgoraBPuH265TranscoderObserver* GetAgoraH265TranscoderObserver();
      `,
    InitImpl: `
      UAgoraBPuH265TranscoderObserver* UAgoraBPuH265TranscoderObserver::InsH265TranscoderObserver = nullptr;
      UAgoraBPuH265TranscoderObserver* UAgoraBPuH265TranscoderObserver::GetAgoraH265TranscoderObserver()
      {
        if (InsH265TranscoderObserver == nullptr)
        {
          InsH265TranscoderObserver = NewObject<UAgoraBPuH265TranscoderObserver>();
          InsH265TranscoderObserver->AddToRoot();
          // TBD(WinterPu)
        }
        return InsH265TranscoderObserver;
      }
      `,
  },
  IVideoFrameMetaInfo: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuVideoFrameMetaInfo* InsVideoFrameMetaInfo;
      
      agora::media::base::IVideoFrameMetaInfo* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IVideoFrameMetaInfo")
      static UAgoraBPuVideoFrameMetaInfo* GetAgoraVideoFrameMetaInfo();
      `,
    InitImpl: `
      UAgoraBPuVideoFrameMetaInfo* UAgoraBPuVideoFrameMetaInfo::InsVideoFrameMetaInfo = nullptr;
      UAgoraBPuVideoFrameMetaInfo* UAgoraBPuVideoFrameMetaInfo::GetAgoraVideoFrameMetaInfo()
      {
        if (InsVideoFrameMetaInfo == nullptr)
        {
          InsVideoFrameMetaInfo = NewObject<UAgoraBPuVideoFrameMetaInfo>();
          InsVideoFrameMetaInfo->AddToRoot();
          // TBD(WinterPu)
        }
        return InsVideoFrameMetaInfo;
      }
      `,
  },
  IMediaPlayerCacheManager: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMediaPlayerCacheManager* InsMediaPlayerCacheManager;
      
      agora::rtc::IMediaPlayerCacheManager* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMediaPlayerCacheManager")
      static UAgoraBPuMediaPlayerCacheManager* GetAgoraMediaPlayerCacheManager();
      `,
    InitImpl: `
      UAgoraBPuMediaPlayerCacheManager* UAgoraBPuMediaPlayerCacheManager::InsMediaPlayerCacheManager = nullptr;
      UAgoraBPuMediaPlayerCacheManager* UAgoraBPuMediaPlayerCacheManager::GetAgoraMediaPlayerCacheManager()
      {
        if (InsMediaPlayerCacheManager == nullptr)
        {
          InsMediaPlayerCacheManager = NewObject<UAgoraBPuMediaPlayerCacheManager>();
          InsMediaPlayerCacheManager->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMediaPlayerCacheManager;
      }
      `,
  },
  MusicCollection: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMusicCollection* InsMusicCollection;
      
      agora::rtc::MusicCollection* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMusicCollection")
      static UAgoraBPuMusicCollection* GetAgoraMusicCollection();
      `,
    InitImpl: `
      UAgoraBPuMusicCollection* UAgoraBPuMusicCollection::InsMusicCollection = nullptr;
      UAgoraBPuMusicCollection* UAgoraBPuMusicCollection::GetAgoraMusicCollection()
      {
        if (InsMusicCollection == nullptr)
        {
          InsMusicCollection = NewObject<UAgoraBPuMusicCollection>();
          InsMusicCollection->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMusicCollection;
      }
      `,
  },
  IMusicContentCenter: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuMusicContentCenter* InsMusicContentCenter;
      
      agora::rtc::IMusicContentCenter* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMusicContentCenter")
      static UAgoraBPuMusicContentCenter* GetAgoraMusicContentCenter();
      `,
    InitImpl: `
      UAgoraBPuMusicContentCenter* UAgoraBPuMusicContentCenter::InsMusicContentCenter = nullptr;
      UAgoraBPuMusicContentCenter* UAgoraBPuMusicContentCenter::GetAgoraMusicContentCenter()
      {
        if (InsMusicContentCenter == nullptr)
        {
          InsMusicContentCenter = NewObject<UAgoraBPuMusicContentCenter>();
          InsMusicContentCenter->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMusicContentCenter;
      }
      `,
  },

  IMusicPlayer: {
    NativePtr: `_NativePtr`, // In Called Function
    Inst: `
      static UAgoraBPuMusicPlayer* InsMusicPlayer;
      
      agora::rtc::IMusicPlayer* _NativePtr = nullptr;
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IMusicPlayer")
      static UAgoraBPuMusicPlayer* GetAgoraMusicPlayer();
      `,
    InitImpl: `
      UAgoraBPuMusicPlayer* UAgoraBPuMusicPlayer::InsMusicPlayer = nullptr;
      UAgoraBPuMusicPlayer* UAgoraBPuMusicPlayer::GetAgoraMusicPlayer()
      {
        if (InsMusicPlayer == nullptr)
        {
          InsMusicPlayer = NewObject<UAgoraBPuMusicPlayer>();
          InsMusicPlayer->AddToRoot();
          // TBD(WinterPu)
        }
        return InsMusicPlayer;
      }
      `,
  },
  IScreenCaptureSourceList: {
    NativePtr: `_NativePtr`,
    Inst: `
      static UAgoraBPuScreenCaptureSourceList* InsScreenCaptureSourceList;
      
      #if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

      agora::rtc::IScreenCaptureSourceList* _NativePtr = nullptr;
      
      #endif
      `,
    InitDecl: `
      UFUNCTION(BlueprintCallable,Category = "Agora|IScreenCaptureSourceList")
      static UAgoraBPuScreenCaptureSourceList* GetAgoraScreenCaptureSourceList();
      `,
    InitImpl: `
      UAgoraBPuScreenCaptureSourceList* UAgoraBPuScreenCaptureSourceList::InsScreenCaptureSourceList = nullptr;
      UAgoraBPuScreenCaptureSourceList* UAgoraBPuScreenCaptureSourceList::GetAgoraScreenCaptureSourceList()
      {
        if (InsScreenCaptureSourceList == nullptr)
        {
          InsScreenCaptureSourceList = NewObject<UAgoraBPuScreenCaptureSourceList>();
          InsScreenCaptureSourceList->AddToRoot();
          // TBD(WinterPu)
        }
        return InsScreenCaptureSourceList;
      }
      `,
  },
  // MusicChartCollection: {
  //   Inst: `
  //   UPROPERTY()
  //   static UAgoraBPuVideoDeviceManager* MusicChartCollection
  //   `,
  //   InitDecl: `
  //   UFUNCTION(BlueprintCallable,Category = "Agora|IVideoDeviceManager")
  //   static UAgoraBPuVideoDeviceManager* GetAgoraVideoDeviceManager();
  //   `,
  //   InitImpl: `

  //   `,
  // },

  // MusicCollection: {},
};

export type MacropScopeMakeup = {
  start: string;
  end: string;
};
// key : fullName
export const map_macrop_scope_makeup: { [key: string]: MacropScopeMakeup } = {
  'agora::rtc::IScreenCaptureSourceList.getCount': {
    start:
      '#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)',
    end: '#endif',
  },
  'agora::rtc::IScreenCaptureSourceList.getSourceInfo': {
    start:
      '#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)',
    end: '#endif',
  },
  'agora::rtc::IScreenCaptureSourceList.release': {
    start:
      '#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)',
    end: '#endif',
  },
};
