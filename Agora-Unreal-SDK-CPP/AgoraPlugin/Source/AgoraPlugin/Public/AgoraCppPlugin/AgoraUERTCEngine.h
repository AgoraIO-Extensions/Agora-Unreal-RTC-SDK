//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

// AgoraHeaderBase should be included first.

#include "AgoraHeaderBase.h"
#include <mutex>
#include "Templates/SharedPointer.h"


namespace agora {
	namespace rtc {
		namespace ue {

			// there would be some naming conflicts:
			// Ex. Unreal has already define Rectangle as a function
			class VideoFrameRenderManager;
			class AgoraUEVideoFrameObserver;



			// This is a ue singleton wrapper for Agora Rtc Engine.
			class AGORAPLUGIN_API AgoraUERtcEngine : public agora::rtc::IRtcEngineEx {

			public:
				AgoraUERtcEngine();
				~AgoraUERtcEngine();

				static AgoraUERtcEngine* Get();
				static agora::rtc::IRtcEngine* NativeRtcEnginePtr();
				static FString GetSDKVersion();
				static void EnableIOSAudioSession(bool bEnable);
				static void Release(bool sync = false);
				static AgoraAppType RtcEngineAppType;

			protected:
				//static variables
				static AgoraUERtcEngine* Instance;
				static std::mutex MutexLock;

				// member variables
				agora::rtc::IRtcEngine* RtcEngine;
				agora::util::AutoPtr<agora::media::IMediaEngine> MediaEngine;

#if AGORA_UESDK_ENABLE_VIDEO
				TSharedPtr<VideoFrameRenderManager> _VideoFrameRenderManager;
				TSharedPtr< AgoraUEVideoFrameObserver>_VideoObserver;
#endif

			private:
				void CreateEngine();
				void DestroyEngine(bool sync = false);


			public:

#pragma region Agora API Wrapper
				virtual int initialize(const agora::rtc::RtcEngineContext& context) override;

				// Use Unreal Rendering
				virtual int setupRemoteVideo(const agora::rtc::VideoCanvas& canvas) override;
				virtual int setupLocalVideo(const agora::rtc::VideoCanvas& canvas) override;
				virtual int setupRemoteVideoEx(const agora::rtc::VideoCanvas& canvas, const agora::rtc::RtcConnection& connection) override;

				// Set Parameter

				// Audio Dump

				// WITH_AGORA_CALLBACKS

#pragma endregion Agora API Wrapper



#pragma region Other Native APIs
				virtual int queryInterface(rtc::INTERFACE_ID_TYPE iid, void** inter) override;
				virtual const char* getVersion(int* build) override;
				virtual const char* getErrorDescription(int code) override;
				virtual int queryCodecCapability(CodecCapInfo* codecInfo, int& size) override;
				virtual int queryDeviceScore() override;
				virtual int preloadChannel(const char* token, const char* channelId, uid_t uid) override;
				virtual int preloadChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount) override;
				virtual int updatePreloadChannelToken(const char* token) override;


				virtual int joinChannel(const char* token, const char* channelId, const char* info, uid_t uid) override;
				virtual int joinChannel(const char* token, const char* channelId, uid_t uid, const ChannelMediaOptions& options) override;
				virtual int updateChannelMediaOptions(const ChannelMediaOptions& options) override;
				virtual int leaveChannel() override;
				virtual int leaveChannel(const LeaveChannelOptions& options) override;
				virtual int renewToken(const char* token) override;
				virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) override;
				virtual int setClientRole(CLIENT_ROLE_TYPE role) override;
				virtual int setClientRole(CLIENT_ROLE_TYPE role, const ClientRoleOptions& options) override;
				virtual int startEchoTest(const EchoTestConfiguration& config) override;
				virtual int stopEchoTest() override;
#if defined(__APPLE__) && TARGET_OS_IOS
				virtual int enableMultiCamera(bool enabled, const CameraCapturerConfiguration& config) override;
#endif
				virtual int enableVideo() override;
				virtual int disableVideo() override;
				virtual int startPreview() override;
				virtual int startPreview(VIDEO_SOURCE_TYPE sourceType) override;
				virtual int stopPreview() override;
				virtual int stopPreview(VIDEO_SOURCE_TYPE sourceType) override;
				virtual int startLastmileProbeTest(const LastmileProbeConfig& config) override;
				virtual int stopLastmileProbeTest() override;
				virtual int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config) override;
				virtual int setBeautyEffectOptions(bool enabled, const BeautyOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setFaceShapeBeautyOptions(bool enabled, const FaceShapeBeautyOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setFaceShapeAreaOptions(const FaceShapeAreaOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int getFaceShapeBeautyOptions(FaceShapeBeautyOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int getFaceShapeAreaOptions(agora::rtc::FaceShapeAreaOptions::FACE_SHAPE_AREA shapeArea, FaceShapeAreaOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setLowlightEnhanceOptions(bool enabled, const LowlightEnhanceOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setVideoDenoiserOptions(bool enabled, const VideoDenoiserOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setColorEnhanceOptions(bool enabled, const ColorEnhanceOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int enableVirtualBackground(bool enabled, VirtualBackgroundSource backgroundSource, SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setVideoScenario(VIDEO_APPLICATION_SCENARIO_TYPE scenarioType) override;
				virtual int setVideoQoEPreference(VIDEO_QOE_PREFERENCE_TYPE qoePreference) override;
				virtual int enableAudio() override;
				virtual int disableAudio() override;
				virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) __deprecated override;
				virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile) override;
				virtual int setAudioScenario(AUDIO_SCENARIO_TYPE scenario) override;
				virtual int enableLocalAudio(bool enabled) override;
				virtual int muteLocalAudioStream(bool mute) override;
				virtual int muteAllRemoteAudioStreams(bool mute) override;
				virtual int muteRemoteAudioStream(uid_t uid, bool mute) override;
				virtual int muteLocalVideoStream(bool mute) override;
				virtual int enableLocalVideo(bool enabled) override;
				virtual int muteAllRemoteVideoStreams(bool mute) override;
				virtual int setRemoteDefaultVideoStreamType(VIDEO_STREAM_TYPE streamType) override;
				virtual int muteRemoteVideoStream(uid_t uid, bool mute) override;
				virtual int setRemoteVideoStreamType(uid_t uid, VIDEO_STREAM_TYPE streamType) override;
				virtual int setRemoteVideoSubscriptionOptions(uid_t uid, const VideoSubscriptionOptions& options) override;
				virtual int setSubscribeAudioBlocklist(uid_t* uidList, int uidNumber) override;
				virtual int setSubscribeAudioAllowlist(uid_t* uidList, int uidNumber) override;
				virtual int setSubscribeVideoBlocklist(uid_t* uidList, int uidNumber) override;
				virtual int setSubscribeVideoAllowlist(uid_t* uidList, int uidNumber) override;
				virtual int enableAudioVolumeIndication(int interval, int smooth, bool reportVad) override;
				virtual int startAudioRecording(const char* filePath, AUDIO_RECORDING_QUALITY_TYPE quality) override;
				virtual int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality) override;
				virtual int startAudioRecording(const AudioRecordingConfiguration& config) override;
				virtual int registerAudioEncodedFrameObserver(const AudioEncodedFrameObserverConfig& config, IAudioEncodedFrameObserver* observer) override;
				virtual int stopAudioRecording() override;
				virtual agora_refptr<IMediaPlayer> createMediaPlayer() override;
				virtual int destroyMediaPlayer(agora_refptr<IMediaPlayer> media_player) override;
				virtual agora_refptr<IMediaRecorder> createMediaRecorder(const RecorderStreamInfo& info) override;
				virtual int destroyMediaRecorder(agora_refptr<IMediaRecorder> mediaRecorder) override;
				virtual int startAudioMixing(const char* filePath, bool loopback, int cycle) override;
				virtual int startAudioMixing(const char* filePath, bool loopback, int cycle, int startPos) override;
				virtual int stopAudioMixing() override;
				virtual int pauseAudioMixing() override;
				virtual int resumeAudioMixing() override;
				virtual int selectAudioTrack(int index) override;
				virtual int getAudioTrackCount() override;
				virtual int adjustAudioMixingVolume(int volume) override;
				virtual int adjustAudioMixingPublishVolume(int volume) override;
				virtual int getAudioMixingPublishVolume() override;
				virtual int adjustAudioMixingPlayoutVolume(int volume) override;
				virtual int getAudioMixingPlayoutVolume() override;
				virtual int getAudioMixingDuration() override;
				virtual int getAudioMixingCurrentPosition() override;
				virtual int setAudioMixingPosition(int pos) override;
				virtual int setAudioMixingDualMonoMode(media::AUDIO_MIXING_DUAL_MONO_MODE mode) override;
				virtual int setAudioMixingPitch(int pitch) override;
				virtual int setAudioMixingPlaybackSpeed(int speed) override;

				virtual int getEffectsVolume() override;
				virtual int setEffectsVolume(int volume) override;
				virtual int preloadEffect(int soundId, const char* filePath, int startPos = 0) override;
				virtual int playEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish = false, int startPos = 0) override;
				virtual int playAllEffects(int loopCount, double pitch, double pan, int gain, bool publish = false) override;
				virtual int getVolumeOfEffect(int soundId) override;
				virtual int setVolumeOfEffect(int soundId, int volume) override;
				virtual int pauseEffect(int soundId) override;
				virtual int pauseAllEffects() override;
				virtual int resumeEffect(int soundId) override;
				virtual int resumeAllEffects() override;
				virtual int stopEffect(int soundId) override;
				virtual int stopAllEffects() override;
				virtual int unloadEffect(int soundId) override;
				virtual int unloadAllEffects() override;
				virtual int getEffectDuration(const char* filePath) override;
				virtual int setEffectPosition(int soundId, int pos) override;
				virtual int getEffectCurrentPosition(int soundId) override;
				virtual int enableSoundPositionIndication(bool enabled) override;
				virtual int setRemoteVoicePosition(uid_t uid, double pan, double gain) override;
				virtual int enableSpatialAudio(bool enabled) override;
				virtual int setRemoteUserSpatialAudioParams(uid_t uid, const agora::SpatialAudioParams& params) override;
				virtual int setVoiceBeautifierPreset(VOICE_BEAUTIFIER_PRESET preset) override;
				virtual int setAudioEffectPreset(AUDIO_EFFECT_PRESET preset) override;
				virtual int setVoiceConversionPreset(VOICE_CONVERSION_PRESET preset) override;
				virtual int setAudioEffectParameters(AUDIO_EFFECT_PRESET preset, int param1, int param2) override;
				virtual int setVoiceBeautifierParameters(VOICE_BEAUTIFIER_PRESET preset, int param1, int param2) override;
				virtual int setVoiceConversionParameters(VOICE_CONVERSION_PRESET preset, int param1, int param2) override;
				virtual int setLocalVoicePitch(double pitch) override;
				virtual int setLocalVoiceFormant(double formantRatio) override;
				virtual int setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) override;
				virtual int setLocalVoiceReverb(AUDIO_REVERB_TYPE reverbKey, int value) override;
				virtual int setHeadphoneEQPreset(HEADPHONE_EQUALIZER_PRESET preset) override;
				virtual int setHeadphoneEQParameters(int lowGain, int highGain) override;
				virtual int enableVoiceAITuner(bool enabled, VOICE_AI_TUNER_TYPE type) override;
				virtual int setLogFile(const char* filePath) override;
				virtual int setLogFilter(unsigned int filter) override;
				virtual int setLogLevel(commons::LOG_LEVEL level) override;
				virtual int setLogFileSize(unsigned int fileSizeInKBytes) override;
				virtual int uploadLogFile(agora::util::AString& requestId) override;
				virtual int writeLog(commons::LOG_LEVEL level, const char* fmt, ...) override;
				virtual int setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) override;
				virtual int setRemoteRenderMode(uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) override;
				virtual int setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode) __deprecated override;
				virtual int setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode) __deprecated override;
				virtual int enableDualStreamMode(bool enabled) __deprecated override;
				virtual int enableDualStreamMode(bool enabled, const SimulcastStreamConfig& streamConfig) __deprecated override;
				virtual int setDualStreamMode(SIMULCAST_STREAM_MODE mode) override;
				virtual int setSimulcastConfig(const SimulcastConfig& simulcastConfig) override;
				virtual int setDualStreamMode(SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig) override;
				virtual int enableCustomAudioLocalPlayback(track_id_t trackId, bool enabled) override;
				virtual int setRecordingAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) override;
				virtual int setPlaybackAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) override;
				virtual int setMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall) override;
				virtual int setEarMonitoringAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) override;
				virtual int setPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel) override;
				virtual int enableAudioSpectrumMonitor(int intervalInMS = 100) override;
				virtual int disableAudioSpectrumMonitor() override;
				virtual int registerAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) override;
				virtual int unregisterAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) override;
				virtual int adjustRecordingSignalVolume(int volume) override;
				virtual int muteRecordingSignal(bool mute) override;
				virtual int adjustPlaybackSignalVolume(int volume) override;
				virtual int adjustUserPlaybackSignalVolume(uid_t uid, int volume) override;
				virtual int setLocalPublishFallbackOption(STREAM_FALLBACK_OPTIONS option) override;
				virtual int setRemoteSubscribeFallbackOption(STREAM_FALLBACK_OPTIONS option) override;
				virtual int setHighPriorityUserList(uid_t* uidList, int uidNum, STREAM_FALLBACK_OPTIONS option) override;
				virtual int enableExtension(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, bool enable = true) override;
				virtual int setExtensionProperty(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, const char* key, const char* value)override;
				virtual int getExtensionProperty(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, const char* key, char* value, int buf_len)override;
				virtual int enableLoopbackRecording(bool enabled, const char* deviceName = NULL) override;
				virtual int adjustLoopbackSignalVolume(int volume) override;
				virtual int getLoopbackRecordingVolume() override;
				virtual int enableInEarMonitoring(bool enabled, int includeAudioFilters) override;
				virtual int setInEarMonitoringVolume(int volume) override;
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
				virtual int loadExtensionProvider(const char* path, bool unload_after_use = false) override;
#endif
				virtual int setExtensionProviderProperty(const char* provider, const char* key, const char* value) override;
				virtual int registerExtension(const char* provider, const char* extension, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE) override;
				virtual int enableExtension(const char* provider, const char* extension, bool enable = true, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE) override;
				virtual int setExtensionProperty(
					const char* provider, const char* extension,
					const char* key, const char* value, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE)override;
				virtual int getExtensionProperty(
					const char* provider, const char* extension,
					const char* key, char* value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE) override;
				virtual int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config) override;
				virtual video_track_id_t createCustomVideoTrack() override;
				virtual video_track_id_t createCustomEncodedVideoTrack(const SenderOptions& sender_option) override;
				virtual int destroyCustomVideoTrack(video_track_id_t video_track_id) override;
				virtual int destroyCustomEncodedVideoTrack(video_track_id_t video_track_id) override;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
				virtual int switchCamera() override;
				virtual bool isCameraZoomSupported() override;
				virtual bool isCameraFaceDetectSupported() override;
				virtual bool isCameraTorchSupported() override;
				virtual bool isCameraFocusSupported() override;

				virtual bool isCameraAutoFocusFaceModeSupported() override;
				virtual int setCameraZoomFactor(float factor) override;
				virtual int enableFaceDetection(bool enabled) override;
				virtual float getCameraMaxZoomFactor() override;
				virtual int setCameraFocusPositionInPreview(float positionX, float positionY) override;
				virtual int setCameraTorchOn(bool isOn) override;
				virtual int setCameraAutoFocusFaceModeEnabled(bool enabled) override;
				virtual bool isCameraExposurePositionSupported() override;
				virtual int setCameraExposurePosition(float positionXinView, float positionYinView) override;
				virtual bool isCameraExposureSupported() override;
				virtual int setCameraExposureFactor(float factor) override;


#if defined(__APPLE__)
				virtual bool isCameraAutoExposureFaceModeSupported() override;
				virtual int setCameraAutoExposureFaceModeEnabled(bool enabled) override;
				virtual int setCameraStabilizationMode(CAMERA_STABILIZATION_MODE mode) override;

#endif
				virtual int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) override;
				virtual int setEnableSpeakerphone(bool speakerOn) override;
				virtual bool isSpeakerphoneEnabled() override;
				virtual int setRouteInCommunicationMode(int route) override;

#endif
#if defined(__APPLE__)
				virtual bool isCameraCenterStageSupported() override;
				virtual int enableCameraCenterStage(bool enabled) override;
#endif


#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
				virtual IScreenCaptureSourceList* getScreenCaptureSources(const SIZE& thumbSize, const SIZE& iconSize, const bool includeScreen) override;
#endif
#if (defined(__APPLE__) && TARGET_OS_IOS)
				virtual int setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction) override;
#endif
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
				virtual int startScreenCaptureByDisplayId(uint32_t displayId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) override;
#endif
#if defined(_WIN32)
				virtual int startScreenCaptureByScreenRect(const Rectangle& screenRect, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) __deprecated override;
#endif
#if defined(__ANDROID__)
				virtual int getAudioDeviceInfo(DeviceInfo& deviceInfo) override;
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
				virtual int startScreenCaptureByWindowId(view_t windowId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) override;
				virtual int setScreenCaptureContentHint(VIDEO_CONTENT_HINT contentHint) override;
				virtual int updateScreenCaptureRegion(const Rectangle& regionRect) override;
				virtual int updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams) override;
#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
				virtual int startScreenCapture(const ScreenCaptureParameters2& captureParams) override;
				virtual int updateScreenCapture(const ScreenCaptureParameters2& captureParams) override;
				virtual int queryScreenCaptureCapability() override;
				virtual int queryCameraFocalLengthCapability(agora::rtc::FocalLengthInfo* focalLengthInfos, int& size) override;

#endif
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
				virtual int setScreenCaptureScenario(SCREEN_SCENARIO_TYPE screenScenario) override;
				virtual int stopScreenCapture() override;
#endif
				virtual int getCallId(agora::util::AString& callId) override;
				virtual int rate(const char* callId, int rating, const char* description) override;
				virtual int complain(const char* callId, const char* description) override;
				virtual int startRtmpStreamWithoutTranscoding(const char* url) override;
				virtual int startRtmpStreamWithTranscoding(const char* url, const LiveTranscoding& transcoding) override;
				virtual int updateRtmpTranscoding(const LiveTranscoding& transcoding) override;
				virtual int startLocalVideoTranscoder(const LocalTranscoderConfiguration& config) override;
				virtual int updateLocalTranscoderConfiguration(const LocalTranscoderConfiguration& config) override;

				virtual int stopRtmpStream(const char* url) override;
				virtual int stopLocalVideoTranscoder() override;
				virtual int startCameraCapture(VIDEO_SOURCE_TYPE sourceType, const CameraCapturerConfiguration& config) override;
				virtual int stopCameraCapture(VIDEO_SOURCE_TYPE sourceType) override;
				virtual int setCameraDeviceOrientation(VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation) override;
				virtual int setScreenCaptureOrientation(VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation) override;
				virtual int startScreenCapture(VIDEO_SOURCE_TYPE sourceType, const ScreenCaptureConfiguration& config) override;
				virtual int stopScreenCapture(VIDEO_SOURCE_TYPE sourceType) override;
				virtual CONNECTION_STATE_TYPE getConnectionState() override;
				virtual bool registerEventHandler(IRtcEngineEventHandler* eventHandler) override;
				virtual bool unregisterEventHandler(IRtcEngineEventHandler* eventHandler) override;
				virtual int setRemoteUserPriority(uid_t uid, PRIORITY_TYPE userPriority) override;
				virtual int registerPacketObserver(IPacketObserver* observer) override;
				virtual int enableEncryption(bool enabled, const EncryptionConfig& config) override;
				virtual int createDataStream(int* streamId, bool reliable, bool ordered) override;
				virtual int createDataStream(int* streamId, const DataStreamConfig& config) override;
				virtual int sendStreamMessage(int streamId, const char* data, size_t length) override;
				virtual int addVideoWatermark(const RtcImage& watermark) __deprecated override;
				virtual int addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options) override;
				virtual int clearVideoWatermarks() override;
				virtual int pauseAudio() __deprecated override;
				virtual int resumeAudio() __deprecated override;
				virtual int enableWebSdkInteroperability(bool enabled) __deprecated override;
				virtual int sendCustomReportMessage(const char* id, const char* category, const char* event, const char* label, int value) override;
				virtual int registerMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) override;
				virtual int unregisterMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) override;
				virtual int startAudioFrameDump(const char* channel_id, uid_t uid, const char* location, const char* uuid, const char* passwd, long duration_ms, bool auto_upload) override;

				virtual int stopAudioFrameDump(const char* channel_id, uid_t uid, const char* location) override;

				virtual int setAINSMode(bool enabled, AUDIO_AINS_MODE mode) override;
				virtual int registerLocalUserAccount(const char* appId, const char* userAccount) override;
				virtual int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount) override;
				virtual int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount, const ChannelMediaOptions& options) override;
				virtual int joinChannelWithUserAccountEx(const char* token, const char* channelId, const char* userAccount, const ChannelMediaOptions& options, IRtcEngineEventHandler* eventHandler) override;
				virtual int getUserInfoByUserAccount(const char* userAccount, rtc::UserInfo* userInfo) override;
				virtual int getUserInfoByUid(uid_t uid, rtc::UserInfo* userInfo) override;
				virtual int startOrUpdateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration) override;
				virtual int stopChannelMediaRelay() override;
				virtual int pauseAllChannelMediaRelay() override;
				virtual int resumeAllChannelMediaRelay() override;
				virtual int setDirectCdnStreamingAudioConfiguration(AUDIO_PROFILE_TYPE profile) override;
				virtual int setDirectCdnStreamingVideoConfiguration(const VideoEncoderConfiguration& config) override;
				virtual int startDirectCdnStreaming(IDirectCdnStreamingEventHandler* eventHandler, const char* publishUrl, const DirectCdnStreamingMediaOptions& options) override;
				virtual int stopDirectCdnStreaming() override;
				virtual int updateDirectCdnStreamingMediaOptions(const DirectCdnStreamingMediaOptions& options) override;
				virtual int startRhythmPlayer(const char* sound1, const char* sound2, const AgoraRhythmPlayerConfig& config) override;
				virtual int stopRhythmPlayer() override;
				virtual int configRhythmPlayer(const AgoraRhythmPlayerConfig& config) override;
				virtual int takeSnapshot(uid_t uid, const char* filePath) override;
				virtual int enableContentInspect(bool enabled, const media::ContentInspectConfig& config) override;
				virtual int adjustCustomAudioPublishVolume(track_id_t trackId, int volume) override;
				virtual int adjustCustomAudioPlayoutVolume(track_id_t trackId, int volume) override;
				virtual int setCloudProxy(CLOUD_PROXY_TYPE proxyType) override;
				virtual int setLocalAccessPoint(const LocalAccessPointConfiguration& config) override;
				virtual int setAdvancedAudioOptions(AdvancedAudioOptions& options, int sourceType = 0) override;
				virtual int setAVSyncSource(const char* channelId, uid_t uid) override;
				virtual int enableVideoImageSource(bool enable, const ImageTrackOptions& options) override;
				virtual int64_t getCurrentMonotonicTimeInMs() override;

				virtual int enableWirelessAccelerate(bool enabled) override;
				virtual int getNetworkType() override;
				virtual int setParameters(const char* parameters) override;
				virtual int startMediaRenderingTracing() override;
				virtual int enableInstantMediaRendering() override;
				virtual uint64_t getNtpWallTimeInMs() override;
				virtual bool isFeatureAvailableOnDevice(FeatureType type) override;
				virtual int sendAudioMetadata(const char* metadata, size_t length) override;

				virtual int joinChannelEx(const char* token, const RtcConnection& connection, const ChannelMediaOptions& options, IRtcEngineEventHandler* eventHandler) override;
				virtual int leaveChannelEx(const RtcConnection& connection) override;
				virtual int leaveChannelEx(const RtcConnection& connection, const LeaveChannelOptions& options) override;
				virtual int updateChannelMediaOptionsEx(const ChannelMediaOptions& options, const RtcConnection& connection) override;
				virtual int setVideoEncoderConfigurationEx(const VideoEncoderConfiguration& config, const RtcConnection& connection) override;
				virtual int muteRemoteAudioStreamEx(uid_t uid, bool mute, const RtcConnection& connection) override;
				virtual int muteRemoteVideoStreamEx(uid_t uid, bool mute, const RtcConnection& connection) override;
				virtual int setRemoteVideoStreamTypeEx(uid_t uid, VIDEO_STREAM_TYPE streamType, const RtcConnection& connection) override;
				virtual int muteLocalAudioStreamEx(bool mute, const RtcConnection& connection) override;
				virtual int muteLocalVideoStreamEx(bool mute, const RtcConnection& connection) override;
				virtual int muteAllRemoteAudioStreamsEx(bool mute, const RtcConnection& connection) override;
				virtual int muteAllRemoteVideoStreamsEx(bool mute, const RtcConnection& connection) override;
				virtual int setSubscribeAudioBlocklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setSubscribeAudioAllowlistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setSubscribeVideoBlocklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setSubscribeVideoAllowlistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setRemoteVideoSubscriptionOptionsEx(uid_t uid, const VideoSubscriptionOptions& options, const RtcConnection& connection) override;
				virtual int setRemoteVoicePositionEx(uid_t uid, double pan, double gain, const RtcConnection& connection) override;
				virtual int setRemoteUserSpatialAudioParamsEx(uid_t uid, const agora::SpatialAudioParams& params, const RtcConnection& connection) override;
				virtual int setRemoteRenderModeEx(uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode, const RtcConnection& connection) override;
				virtual int enableLoopbackRecordingEx(const RtcConnection& connection, bool enabled, const char* deviceName = NULL) override;
				virtual int adjustRecordingSignalVolumeEx(int volume, const RtcConnection& connection) override;
				virtual int muteRecordingSignalEx(bool mute, const RtcConnection& connection) override;
				virtual int adjustUserPlaybackSignalVolumeEx(uid_t uid, int volume, const RtcConnection& connection) override;
				virtual CONNECTION_STATE_TYPE getConnectionStateEx(const RtcConnection& connection) override;
				virtual int enableEncryptionEx(const RtcConnection& connection, bool enabled, const EncryptionConfig& config) override;
				virtual int createDataStreamEx(int* streamId, bool reliable, bool ordered, const RtcConnection& connection) override;
				virtual int createDataStreamEx(int* streamId, const DataStreamConfig& config, const RtcConnection& connection) override;
				virtual int sendStreamMessageEx(int streamId, const char* data, size_t length, const RtcConnection& connection) override;
				virtual int addVideoWatermarkEx(const char* watermarkUrl, const WatermarkOptions& options, const RtcConnection& connection) override;
				virtual int clearVideoWatermarkEx(const RtcConnection& connection) override;
				virtual int sendCustomReportMessageEx(const char* id, const char* category, const char* event, const char* label, int value, const RtcConnection& connection) override;
				virtual int enableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const RtcConnection& connection) override;
				virtual int startRtmpStreamWithoutTranscodingEx(const char* url, const RtcConnection& connection) override;
				virtual int startRtmpStreamWithTranscodingEx(const char* url, const LiveTranscoding& transcoding, const RtcConnection& connection) override;
				virtual int updateRtmpTranscodingEx(const LiveTranscoding& transcoding, const RtcConnection& connection) override;
				virtual int stopRtmpStreamEx(const char* url, const RtcConnection& connection) override;
				virtual int startOrUpdateChannelMediaRelayEx(const ChannelMediaRelayConfiguration& configuration, const RtcConnection& connection) override;
				virtual int stopChannelMediaRelayEx(const RtcConnection& connection) override;
				virtual int pauseAllChannelMediaRelayEx(const RtcConnection& connection) override;
				virtual int resumeAllChannelMediaRelayEx(const RtcConnection& connection) override;
				virtual int getUserInfoByUserAccountEx(const char* userAccount, rtc::UserInfo* userInfo, const RtcConnection& connection) override;
				virtual int getUserInfoByUidEx(uid_t uid, rtc::UserInfo* userInfo, const RtcConnection& connection) override;
				virtual int enableDualStreamModeEx(bool enabled, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection) override;
				virtual int setDualStreamModeEx(SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection) override;
				virtual int setSimulcastConfigEx(const SimulcastConfig& simulcastConfig,
					const RtcConnection& connection) override;
				virtual int setHighPriorityUserListEx(uid_t* uidList, int uidNum, STREAM_FALLBACK_OPTIONS option, const RtcConnection& connection) override;
				virtual int takeSnapshotEx(const RtcConnection& connection, uid_t uid, const char* filePath) override;
				virtual int enableContentInspectEx(bool enabled, const media::ContentInspectConfig& config, const RtcConnection& connection) override;

				virtual int startMediaRenderingTracingEx(const RtcConnection& connection) override;
				virtual int setParametersEx(const RtcConnection& connection, const char* parameters) override;
				virtual int getCallIdEx(agora::util::AString& callId, const RtcConnection& connection) override;
				virtual int sendAudioMetadataEx(const RtcConnection& connection, const char* metadata, size_t length) override;

#pragma endregion Other Native APIs
			};


		}
	}
}
