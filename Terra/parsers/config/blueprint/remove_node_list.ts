module.exports = [
  'IAgoraParameter.h',
  'AgoraOptional.h',
  'AgoraRefPtr.h',
  'agora::util::AutoPtr',
  'agora::util::CopyableAutoPtr',
  'agora::util::IString',
  'agora::util::IIterator',
  'agora::util::IContainer',
  'agora::util::AOutputIterator',
  'agora::util::AList',
  'agora::base::IParameterEngine',
  'agora::media::base::IVideoFrameObserver',
  'agora::media::base::IAudioFrameObserver',
  'agora::media::base::IMediaPlayerCustomDataProvider',
  'agora::UserInfo',
  'agora::RefCountInterface',
  'RefCountInterface',
  'agora::base::IEngineBase',
  'agora::base::AParameter',
  'agora::rtc::IMediaPlayerCustomDataProvider',
  'agora::rtc::IMediaPlayerSource',
  'agora::base::LicenseCallback',
  'agora::media::ISnapshotCallback',
  'agora::commons::ILogWriter',
  'agora::rtc::IMediaStreamingSource',
  'agora::rtc::IMediaStreamingSourceObserver',
  'agora::rtc::IAudioDeviceCollection',
  'agora::rtc::IVideoDeviceCollection',
  'agora::rtc::AAudioDeviceManager',
  'agora::rtc::AVideoDeviceManager',
  'agora::rtc::IRtcEngineParameter',
  'agora::base::IAgoraParameter',
  'agora::rtc::IRhythmPlayer',
  'agora::rtc::LocalSpatialAudioConfig',
  'agora::media::base::MAX_METADATA_SIZE_TYPE',
  'agora::media::base::VIDEO_SOURCE_TYPE',
  'agora::rtc::EncodedVideoTrackOptions.SetFrom',
  'agora::rtc::ChannelMediaOptions.SetAll',
  'agora::rtc::DirectCdnStreamingMediaOptions.SetAll',
  'agora::rtc::EncryptionConfig:getEncryptionString',
  'agora::rtc::IRtcEngineEventHandler.eventHandlerType',
  'agora::rtc::IRtcEngineEventHandlerEx.eventHandlerType',
  'agora::rtc::IMediaPlayer.initialize',
  'agora::rtc::IMediaPlayer.openWithCustomSource',
  'agora::media::IVideoFrameObserver.isExternal',
  'agora::rtc::RtcEngineContext.context',
  'agora::rtc::RtcEngineContext.eventHandler',
  'agora::media::base::ExternalVideoFrame.eglContext',
  'agora::media::base::ExternalVideoFrame.d3d11_texture_2d',
  'agora::media::base::VideoFrame.sharedContext',
  'agora::media::base::VideoFrame.d3d11Texture2d',
  'agora::media::base::MediaSource.provider',
  'agora::rtc::MusicContentCenterConfiguration.eventHandler',
  'agora::rtc::IRtcEngineEx.joinChannelEx.eventHandler',
  'agora::rtc::IRtcEngine.joinChannelWithUserAccountEx.eventHandler',
  'agora::rtc::IRtcEngine.createDataStream.streamId',
  'agora::rtc::IRtcEngineEx.createDataStreamEx.streamId',
  'agora::rtc::IRtcEngine.getVersion.build',
  'agora::rtc::IRtcEngine.takeSnapshot.callback',
  'agora::rtc::ICloudSpatialAudioEngine.getTeammates.uids',
  'agora::rtc::ICloudSpatialAudioEngine.getTeammates.userCount',
  'agora::rtc::ILocalSpatialAudioEngine.initialize.config',
  // remove
  // 'agora::rtc::IScreenCaptureSourceList',

  'agora::media::IAudioFrameObserverBase',

  // register observers
  'agora::rtc::IH265Transcoder.registerTranscoderObserver',
  'agora::rtc::IH265Transcoder.unregisterTranscoderObserver',
  'agora::media::IMediaEngine.registerAudioFrameObserver',
  'agora::media::IMediaEngine.registerVideoFrameObserver',
  'agora::media::IMediaEngine.registerVideoEncodedFrameObserver',
  'agora::media::IMediaEngine.registerFaceInfoObserver',
  'agora::media::IMediaEngine.addVideoFrameRenderer',
  'agora::media::IMediaEngine.removeVideoFrameRenderer',
  'agora::media::IMediaEngine.unregisterAudioFrameObserver',
  'agora::media::IMediaEngine.unregisterVideoFrameObserver',
  'agora::media::IMediaEngine.unregisterVideoEncodedFrameObserver',
  'agora::media::IMediaEngine.unregisterFaceInfoObserver',
  'agora::rtc::IMediaRecorder.setMediaRecorderObserver',

  // some type error
  'agora::media::IMediaEngine.pushAudioFrame',
  'agora::media::IMediaEngine.pullAudioFrame',
  'agora::media::IMediaEngine.setExternalRemoteEglContext',
  'agora::rtc::IRtcEngine.queryInterface',

  // TBD(WinterPu)
  // override conflicts
  'agora::rtc::IMediaPlayer.setPlayerOption',

  // TBD(WinterPu) void
  'agora::rtc::IMediaPlayerSourceObserver.onMetaData',

  'agora::rtc::IMediaPlayer.registerPlayerSourceObserver',
  'agora::rtc::IMediaPlayer.unregisterPlayerSourceObserver',
  'agora::rtc::IMediaPlayer.registerAudioFrameObserver',
  'agora::rtc::IMediaPlayer.unregisterAudioFrameObserver',
  'agora::rtc::IMediaPlayer.registerVideoFrameObserver',
  'agora::rtc::IMediaPlayer.unregisterVideoFrameObserver',
  'agora::rtc::IMediaPlayer.registerMediaPlayerAudioSpectrumObserver',
  'agora::rtc::IMediaPlayer.unregisterMediaPlayerAudioSpectrumObserver',

  'agora::rtc::IMusicContentCenter.registerEventHandler',
  'agora::rtc::IMusicContentCenter.unregisterEventHandler',

  'agora::rtc::IRtcEngine.registerAudioEncodedFrameObserver',
  'agora::rtc::IRtcEngine.registerAudioSpectrumObserver',
  'agora::rtc::IRtcEngine.unregisterAudioEncodedFrameObserver',
  'agora::rtc::IRtcEngine.unregisterAudioSpectrumObserver',
  'agora::rtc::IRtcEngine.registerEventHandler',
  'agora::rtc::IRtcEngine.unregisterEventHandler',
  'agora::rtc::IRtcEngine.registerPacketObserver',
  'agora::rtc::IRtcEngine.registerMediaMetadataObserver',
  'agora::rtc::IRtcEngine.unregisterMediaMetadataObserver',

  //custom header
  'agora::rtc::IRtcEngine.getVideoDeviceManager',
  'agora::rtc::IRtcEngine.getAudioDeviceManager',
  'agora::rtc::IRtcEngine.getMusicContentCenter',
  'agora::rtc::IRtcEngine.getMediaEngine',
  'agora::rtc::IRtcEngine.getLocalSpatialAudioEngine',
  'agora::rtc::IRtcEngine.getH265Transcoder',

  // TBD(WinterPu)
  // special type
  // agora_refptr<MusicChartCollection>
  'agora::rtc::IMusicContentCenterEventHandler',
  'agora::rtc::IMusicContentCenterEventHandler.onMusicChartsResult',
  'agora::rtc::IMusicContentCenter.createMusicPlayer',
  'agora::rtc::IMusicContentCenter.destroyMusicPlayer',

  'agora::rtc::IRtcEngine.createMediaPlayer',
  'agora::rtc::IRtcEngine.destroyMediaPlayer',
  'agora::rtc::IRtcEngine.createMediaRecorder',
  'agora::rtc::IRtcEngine.destroyMediaRecorder',
  'agora::rtc::IRtcEngine.uploadLogFile',
  // EUABT_ empty
  'agora::rtc::IRtcEngine.writeLog',
  // void type
  'agora::rtc::IRtcEngine.setExternalMediaProjection',

  // FString agora::util::AString
  'agora::rtc::IMusicContentCenter',
  'agora::rtc::IRtcEngine.getCallId',
  'agora::rtc::IRtcEngineEx.getCallIdEx',

  // Pointer
  'agora::rtc::IRtcEngine.startDirectCdnStreaming',
  'agora::rtc::IRtcEngine.getNativeHandle',

  // EventHandler Has Return Value
  'agora::media::IVideoFrameObserver',

  // TBD(WinterPu)
  // Observer
  // 'agora::rtc::IMediaPlayerSourceObserver',
  'agora::rtc::IMediaPlayerVideoFrameObserver',
  'agora::rtc::IAudioEncodedFrameObserver',
  'agora::rtc::IPacketObserver',
  'agora::media::IAudioPcmFrameSink',
  'agora::rtc::IMediaPlayerVideoFrameObserver',

  // TBD(WinterPu)
  // no default constructor: so currently FUABT_ generation failed
  'agora::rtc::MixedAudioFrame',
  'agora::rtc::IRtcEngine.setMixedAudioFrameParameters',

  // TBD(WinterPu)
  // for inheritance problem:
  // cannot inherit from the abstract class
  // IAudioFrameObserver : public IAudioFrameObserverBase
  'agora::media::IAudioFrameObserver',
  'agora::rtc::IMediaPlayerSourceObserver',

  // TBD(WinterPu)
  // return type has ::ext:: problem
  /*
    auto ret = _NativePtr->getPlaybackDefaultDevice();
    // Free Data if neeeded
    TArray<FUABT_AudioDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::ext::AudioDeviceInfo, FUABT_AudioDeviceInfo>(ReturnVal, ret, 1);
*/

  'agora::rtc::IAudioDeviceManager.getPlaybackDefaultDevice',
  'agora::rtc::IAudioDeviceManager.getRecordingDefaultDevice',

  //TBD(WinterPu)
  // observer -> CBExecutor has return value
  // DECLARE_DYNAMIC_MULTICAST_DELEGATE_XXX cannot has return value
  'agora::media::IAudioSpectrumObserver',
  'agora::media::IVideoEncodedFrameObserver',
  'agora::media::IFaceInfoObserver',
  'agora::rtc::IMetadataObserver',
];
