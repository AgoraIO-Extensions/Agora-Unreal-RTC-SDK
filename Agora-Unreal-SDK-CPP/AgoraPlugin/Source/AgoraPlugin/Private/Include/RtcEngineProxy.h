#pragma once


#include "AgoraHeaderBase.h"
#include "MediaEngineProxy.h"
#include "VideoObserverInternal.h"
#include "VideoRenderManager.h"
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJni.h"
#endif
#include <memory>

namespace agora
{
	namespace rtc
	{
		namespace ue
		{
			class MediaEngineProxy;
			class AGORAPLUGIN_API RtcEngineProxy : public IRtcEngineEx
			{
			private:

				IRtcEngine* RtcEngine;
				std::unique_ptr<MediaEngineProxy> MediaProxy;
				std::unique_ptr<VideoRenderManager> VideoRenderMgr;

			public:

				RtcEngineProxy();

				util::AutoPtr<agora::media::IMediaEngine> MediaEngine;

				virtual int queryInterface(rtc::INTERFACE_ID_TYPE iid, void** inter) override;
				virtual void release(bool sync = false) override;
				virtual int initialize(const RtcEngineContext& context) override;
				virtual const char* getVersion(int* build) override;
				virtual const char* getErrorDescription(int code) override;
				virtual int joinChannel(const char* token, const char* channelId, const char* info, uid_t uid) override;
				virtual int joinChannel(const char* token, const char* channelId, uid_t uid, const ChannelMediaOptions& options) override;
				virtual int updateChannelMediaOptions(const ChannelMediaOptions& options) override;
				virtual int leaveChannel() override;
				virtual int leaveChannel(const LeaveChannelOptions& options) override;
				virtual int renewToken(const char* token) override;
				virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) override;
				virtual int setClientRole(CLIENT_ROLE_TYPE role) override;
				virtual int setClientRole(CLIENT_ROLE_TYPE role, const ClientRoleOptions& options) override;
				virtual int startEchoTest() override;
				virtual int startEchoTest(int intervalInSeconds) override;
				virtual int startEchoTest(const EchoTestConfiguration& config) override;
				virtual int stopEchoTest() override;
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
				virtual int setLowlightEnhanceOptions(bool enabled, const LowlightEnhanceOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setVideoDenoiserOptions(bool enabled, const VideoDenoiserOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int setColorEnhanceOptions(bool enabled, const ColorEnhanceOptions& options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int enableVirtualBackground(bool enabled, VirtualBackgroundSource backgroundSource, SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE) override;
				virtual int enableRemoteSuperResolution(uid_t userId, bool enable) override;
				virtual int setupRemoteVideo(const VideoCanvas& canvas) override;
				virtual int setupLocalVideo(const VideoCanvas& canvas) override;
				virtual int enableAudio() override;
				virtual int disableAudio() override;
				virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) override;
				virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile) override;
				virtual int setAudioScenario(AUDIO_SCENARIO_TYPE scenario) override;
				virtual int enableLocalAudio(bool enabled) override;
				virtual int muteLocalAudioStream(bool mute) override;
				virtual int muteAllRemoteAudioStreams(bool mute) override;
				virtual int setDefaultMuteAllRemoteAudioStreams(bool mute) override;
				virtual int muteRemoteAudioStream(uid_t uid, bool mute) override;
				virtual int muteLocalVideoStream(bool mute) override;
				virtual int enableLocalVideo(bool enabled) override;
				virtual int muteAllRemoteVideoStreams(bool mute) override;
				virtual int setDefaultMuteAllRemoteVideoStreams(bool mute) override;
				virtual int muteRemoteVideoStream(uid_t uid, bool mute) override;
				virtual int setRemoteVideoStreamType(uid_t uid, VIDEO_STREAM_TYPE streamType) override;
				virtual int setRemoteVideoSubscriptionOptions(uid_t uid, const VideoSubscriptionOptions& options) override;
				virtual int setRemoteDefaultVideoStreamType(VIDEO_STREAM_TYPE streamType) override;
				virtual int setSubscribeAudioBlacklist(uid_t* uidList, int uidNumber) override;
				virtual int setSubscribeAudioWhitelist(uid_t* uidList, int uidNumber) override;
				virtual int setSubscribeVideoBlacklist(uid_t* uidList, int uidNumber) override;
				virtual int setSubscribeVideoWhitelist(uid_t* uidList, int uidNumber) override;
				virtual int enableAudioVolumeIndication(int interval, int smooth, bool reportVad) override;
				virtual int startAudioRecording(const char* filePath, AUDIO_RECORDING_QUALITY_TYPE quality) override;
				virtual int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality) override;
				virtual int startAudioRecording(const AudioRecordingConfiguration& config) override;
				virtual int registerAudioEncodedFrameObserver(const AudioEncodedFrameObserverConfig& config, IAudioEncodedFrameObserver* observer) override;
				virtual int stopAudioRecording() override;
				virtual agora_refptr<IMediaPlayer> createMediaPlayer() override;
				virtual int destroyMediaPlayer(agora_refptr<IMediaPlayer> media_player) override;
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
				virtual int setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) override;
				virtual int setLocalVoiceReverb(AUDIO_REVERB_TYPE reverbKey, int value) override;
				virtual int setLogFile(const char* filePath) override;
				virtual int setLogFilter(unsigned int filter) override;
				virtual int setLogLevel(commons::LOG_LEVEL level) override;
				virtual int setLogFileSize(unsigned int fileSizeInKBytes) override;
				virtual int uploadLogFile(agora::util::AString& requestId) override;
				virtual int setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) override;
				virtual int setRemoteRenderMode(uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) override;
				virtual int setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode) override;
				virtual int setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode) override;
				virtual int enableDualStreamMode(bool enabled) override;
				virtual int enableDualStreamMode(VIDEO_SOURCE_TYPE sourceType, bool enabled) override;
				virtual int enableDualStreamMode(VIDEO_SOURCE_TYPE sourceType, bool enabled, const SimulcastStreamConfig& streamConfig) override;
				virtual int setDualStreamMode(SIMULCAST_STREAM_MODE mode) override;
				virtual int setDualStreamMode(VIDEO_SOURCE_TYPE sourceType, SIMULCAST_STREAM_MODE mode) override;
				virtual int setDualStreamMode(VIDEO_SOURCE_TYPE sourceType, SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig) override;
				virtual int enableEchoCancellationExternal(bool enabled, int audioSourceDelay) override;
				virtual int enableCustomAudioLocalPlayback(int sourceId, bool enabled) override;
				virtual int startPrimaryCustomAudioTrack(const AudioTrackConfig& config) override;
				virtual int stopPrimaryCustomAudioTrack() override;
				virtual int startSecondaryCustomAudioTrack(const AudioTrackConfig& config) override;
				virtual int stopSecondaryCustomAudioTrack() override;
				virtual int setRecordingAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) override;
				virtual int setPlaybackAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) override;
				virtual int setMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall) override;
				virtual int setPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel) override;
				virtual int enableAudioSpectrumMonitor(int intervalInMS = 100) override;
				virtual int disableAudioSpectrumMonitor() override;
				virtual int registerAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) override;
				virtual int unregisterAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) override;
				virtual int adjustRecordingSignalVolume(int volume) override;
				virtual int muteRecordingSignal(bool mute) override;
				virtual int adjustPlaybackSignalVolume(int volume) override;
				virtual int adjustUserPlaybackSignalVolume(unsigned int uid, int volume) override;
				virtual int setLocalPublishFallbackOption(STREAM_FALLBACK_OPTIONS option) override;
				virtual int setRemoteSubscribeFallbackOption(STREAM_FALLBACK_OPTIONS option) override;
				virtual int enableLoopbackRecording(bool enabled, const char* deviceName = NULL) override;
				virtual int adjustLoopbackSignalVolume(int volume) override;
				virtual int getLoopbackRecordingVolume() override;
				virtual int enableInEarMonitoring(bool enabled, int includeAudioFilters) override;
				virtual int setInEarMonitoringVolume(int volume) override;
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
				virtual int loadExtensionProvider(const char* path, bool unload_after_use = false) override;
#endif
				virtual int setExtensionProviderProperty(const char* provider, const char* key, const char* value) override;
				virtual int enableExtension(const char* provider, const char* extension, bool enable = true, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE) override;
				virtual int setExtensionProperty(const char* provider, const char* extension, const char* key, const char* value, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE) override;
				virtual int getExtensionProperty(const char* provider, const char* extension, const char* key, char* value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE) override;
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
#if defined(__APPLE__)
				virtual bool isCameraAutoExposureFaceModeSupported() override;
				virtual int setCameraAutoExposureFaceModeEnabled(bool enabled) override;
#endif
				virtual int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) override;
				virtual int setEnableSpeakerphone(bool speakerOn) override;
				virtual bool isSpeakerphoneEnabled() override;
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
				virtual int startScreenCaptureByScreenRect(const Rectangle& screenRect, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) override;
#endif
#if defined(__ANDROID__)
				virtual int getAudioDeviceInfo(DeviceInfo& deviceInfo) override;
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
				virtual int startScreenCaptureByWindowId(view_t windowId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) override;
				virtual int setScreenCaptureContentHint(VIDEO_CONTENT_HINT contentHint) override;
				virtual int setScreenCaptureScenario(SCREEN_SCENARIO_TYPE screenScenario) override;
				virtual int updateScreenCaptureRegion(const Rectangle& regionRect) override;
				virtual int updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams) override;
#endif
#if defined(__ANDROID__)
				virtual int startScreenCapture(const ScreenCaptureParameters2& captureParams) override;
				virtual int updateScreenCapture(const ScreenCaptureParameters2& captureParams) override;
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(__ANDROID__)
				virtual int stopScreenCapture() override;
#endif
				virtual int getCallId(agora::util::AString& callId) override;
				virtual int rate(const char* callId, int rating, const char* description) override;
				virtual int complain(const char* callId, const char* description) override;
				virtual int startRtmpStreamWithoutTranscoding(const char* url) override;
				virtual int startRtmpStreamWithTranscoding(const char* url, const LiveTranscoding& transcoding) override;
				virtual int updateRtmpTranscoding(const LiveTranscoding& transcoding) override;
				virtual int stopRtmpStream(const char* url) override;
				virtual int startLocalVideoTranscoder(const LocalTranscoderConfiguration& config) override;
				virtual int updateLocalTranscoderConfiguration(const LocalTranscoderConfiguration& config) override;
				virtual int stopLocalVideoTranscoder() override;
				virtual int startPrimaryCameraCapture(const CameraCapturerConfiguration& config) override;
				virtual int startSecondaryCameraCapture(const CameraCapturerConfiguration& config) override;
				virtual int stopPrimaryCameraCapture() override;
				virtual int stopSecondaryCameraCapture() override;
				virtual int setCameraDeviceOrientation(VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation) override;
				virtual int setScreenCaptureOrientation(VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation) override;
				virtual int startPrimaryScreenCapture(const ScreenCaptureConfiguration& config) override;
				virtual int startSecondaryScreenCapture(const ScreenCaptureConfiguration& config) override;
				virtual int stopPrimaryScreenCapture() override;
				virtual int stopSecondaryScreenCapture() override;
				virtual CONNECTION_STATE_TYPE getConnectionState() override;
				virtual bool registerEventHandler(IRtcEngineEventHandler* eventHandler) override;
				virtual bool unregisterEventHandler(IRtcEngineEventHandler* eventHandler) override;
				virtual int setRemoteUserPriority(uid_t uid, PRIORITY_TYPE userPriority) override;
				virtual int registerPacketObserver(IPacketObserver* observer) override;
				virtual int setEncryptionMode(const char* encryptionMode) override;
				virtual int setEncryptionSecret(const char* secret) override;
				virtual int enableEncryption(bool enabled, const EncryptionConfig& config) override;
				virtual int createDataStream(int* streamId, bool reliable, bool ordered) override;
				virtual int createDataStream(int* streamId, DataStreamConfig& config) override;
				virtual int sendStreamMessage(int streamId, const char* data, size_t length) override;
				virtual int addVideoWatermark(const RtcImage& watermark) override;
				virtual int addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options) override;
				virtual int clearVideoWatermark() override;
				virtual int clearVideoWatermarks() override;
				virtual int addInjectStreamUrl(const char* url, const InjectStreamConfig& config) override;
				virtual int removeInjectStreamUrl(const char* url) override;
				virtual int pauseAudio()  override;
				virtual int resumeAudio() override;
				virtual int enableWebSdkInteroperability(bool enabled) override;
				virtual int sendCustomReportMessage(const char* id, const char* category, const char* event, const char* label, int value) override;
				virtual int registerMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) override;
				virtual int unregisterMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) override;
				virtual int startAudioFrameDump(const char* channel_id, uid_t user_id, const char* location, const char* uuid, const char* passwd, long duration_ms, bool auto_upload) override;
				virtual int stopAudioFrameDump(const char* channel_id, uid_t user_id, const char* location) override;
				virtual int registerLocalUserAccount(const char* appId, const char* userAccount) override;
				virtual int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount) override;
				virtual int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount, const ChannelMediaOptions& options) override;
				virtual int joinChannelWithUserAccountEx(const char* token, const char* channelId, const char* userAccount, const ChannelMediaOptions& options, IRtcEngineEventHandler* eventHandler) override;
				virtual int getUserInfoByUserAccount(const char* userAccount, rtc::UserInfo* userInfo) override;
				virtual int getUserInfoByUid(uid_t uid, rtc::UserInfo* userInfo) override;
				virtual int startChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration) override;
				virtual int updateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration) override;
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
				virtual int adjustCustomAudioPublishVolume(int32_t sourceId, int volume) override;
				virtual int adjustCustomAudioPlayoutVolume(int32_t sourceId, int volume) override;
				virtual int setCloudProxy(CLOUD_PROXY_TYPE proxyType) override;
				virtual int setLocalAccessPoint(const LocalAccessPointConfiguration& config) override;
				virtual int setAdvancedAudioOptions(AdvancedAudioOptions& options) override;
				virtual int setAVSyncSource(const char* channelId, uid_t uid) override;
				virtual int enableVideoImageSource(bool enable, const ImageTrackOptions& options) override;
				virtual int joinChannelEx(const char* token, const RtcConnection& connection, const ChannelMediaOptions& options, IRtcEngineEventHandler* eventHandler) override;
				virtual int leaveChannelEx(const RtcConnection& connection) override;
				virtual int updateChannelMediaOptionsEx(const ChannelMediaOptions& options, const RtcConnection& connection) override;
				virtual int setVideoEncoderConfigurationEx(const VideoEncoderConfiguration& config, const RtcConnection& connection) override;
				virtual int setupRemoteVideoEx(const VideoCanvas& canvas, const RtcConnection& connection) override;
				virtual int muteRemoteAudioStreamEx(uid_t uid, bool mute, const RtcConnection& connection) override;
				virtual int muteRemoteVideoStreamEx(uid_t uid, bool mute, const RtcConnection& connection) override;
				virtual int setRemoteVideoStreamTypeEx(uid_t uid, VIDEO_STREAM_TYPE streamType, const RtcConnection& connection) override;
				virtual int setSubscribeAudioBlacklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setSubscribeAudioWhitelistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setSubscribeVideoBlacklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setSubscribeVideoWhitelistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection) override;
				virtual int setRemoteVideoSubscriptionOptionsEx(uid_t uid, const VideoSubscriptionOptions& options, const RtcConnection& connection) override;
				virtual int setRemoteVoicePositionEx(uid_t uid, double pan, double gain, const RtcConnection& connection) override;
				virtual int setRemoteUserSpatialAudioParamsEx(uid_t uid, const agora::SpatialAudioParams& params, const RtcConnection& connection) override;
				virtual int setRemoteRenderModeEx(uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode, const RtcConnection& connection) override;
				virtual int enableLoopbackRecordingEx(const RtcConnection& connection, bool enabled, const char* deviceName = NULL) override;
				virtual CONNECTION_STATE_TYPE getConnectionStateEx(const RtcConnection& connection) override;
				virtual int enableEncryptionEx(const RtcConnection& connection, bool enabled, const EncryptionConfig& config) override;
				virtual int createDataStreamEx(int* streamId, bool reliable, bool ordered, const RtcConnection& connection) override;
				virtual int createDataStreamEx(int* streamId, DataStreamConfig& config, const RtcConnection& connection) override;
				virtual int sendStreamMessageEx(int streamId, const char* data, size_t length, const RtcConnection& connection) override;
				virtual int addVideoWatermarkEx(const char* watermarkUrl, const WatermarkOptions& options, const RtcConnection& connection) override;
				virtual int clearVideoWatermarkEx(const RtcConnection& connection) override;
				virtual int sendCustomReportMessageEx(const char* id, const char* category, const char* event, const char* label, int value, const RtcConnection& connection) override;
				virtual int enableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const RtcConnection& connection) override;
				virtual int getUserInfoByUserAccountEx(const char* userAccount, rtc::UserInfo* userInfo, const RtcConnection& connection) override;
				virtual int getUserInfoByUidEx(uid_t uid, rtc::UserInfo* userInfo, const RtcConnection& connection) override;
				virtual int setVideoProfileEx(int width, int height, int frameRate, int bitrate) override;
				virtual int enableDualStreamModeEx(VIDEO_SOURCE_TYPE sourceType, bool enabled, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection) override;
				virtual int setDualStreamModeEx(VIDEO_SOURCE_TYPE sourceType, SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection) override;
				virtual int enableWirelessAccelerate(bool enabled) override;
				virtual int takeSnapshotEx(const RtcConnection& connection, uid_t uid, const char* filePath) override;
				virtual void registerVideoFrameObserver(media::IVideoFrameObserver* observer);

			};
		};

		
	}
}
