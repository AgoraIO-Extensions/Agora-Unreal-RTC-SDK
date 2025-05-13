module.exports = [
  {
    source: 'agora::rtc::IRtcEngineEx',
    target: 'agora::rtc::IRtcEngine',
    deleteSource: true,
    isFilterOverloadFunctions: false,
  },
  {
    source: 'agora::media::IAudioFrameObserverBase',
    target: 'agora::media::IAudioFrameObserver',
    deleteSource: false,
    isFilterOverloadFunctions: false,
  },
];
