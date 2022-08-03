#include "Include/RtcEngineProxy.h"
#include "AgoraPluginInterface.h"

namespace agora
{
	namespace rtc
	{
		namespace ue
		{
			agora::rtc::IRtcEngine* createAgoraRtcEngine()
			{
				return new RtcEngineProxy();
			}

			RtcEngineProxy::RtcEngineProxy()
			{
#if PLATFORM_ANDROID
				if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
				{
					static jmethodID LoadLibrary = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "LoadLibrary", "()V", false);
					FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadLibrary);
				}
#endif
				_rtcEngine = ::createAgoraRtcEngine();
				_videoRenderMgr = std::make_unique<VideoRenderManager>();
			}

			void RtcEngineProxy::registerVideoFrameObserver(media::IVideoFrameObserver* observer)
			{
				if (_mediaEngineProxy != nullptr)
				{
					 _mediaEngineProxy->registerVideoFrameObserver(observer);
				}
			}

			void RtcEngineProxy::release(bool sync) {

				if (_rtcEngine != nullptr)
				{
					_mediaEngineProxy->registerVideoFrameObserver(nullptr);
					_rtcEngine->release(sync);
					_rtcEngine = nullptr;
				}
			}

			int RtcEngineProxy::initialize(const RtcEngineContext& context)
			{
				int ret = _rtcEngine->initialize(context);

				UE_LOG(LogTemp, Warning, TEXT("RtcEngineProxy initialize %d"), ret);
				AppType appType = kAppTypeUnreal;
				char parameters[512] = "";
				sprintf(parameters, "{\"rtc.set_app_type\": %d}", appType);
				agora::base::AParameter apm(_rtcEngine);
				apm->setParameters(parameters);

				if (_rtcEngine != nullptr && ret == 0)
				{
					_mediaEngineProxy = std::make_unique<MediaEngineProxy>(_rtcEngine);
				}
				return 0;
			}

			int RtcEngineProxy::queryInterface(agora::rtc::INTERFACE_ID_TYPE iid, void** inter) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->queryInterface(iid, inter);
				}
				return -ERROR_NULLPTR;
			}

			char const* RtcEngineProxy::getVersion(int* build) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getVersion(build);
				}
				return nullptr;
			}

			char const* RtcEngineProxy::getErrorDescription(int code) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getErrorDescription(code);
				}
				return nullptr;
			}

			int RtcEngineProxy::joinChannel(char const* token, char const* channelId, char const* info, agora::rtc::uid_t uid) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->joinChannel(token, channelId, info, uid);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannel(char const* token, char const* channelId, agora::rtc::uid_t uid, agora::rtc::ChannelMediaOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->joinChannel(token, channelId, uid, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaOptions(agora::rtc::ChannelMediaOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateChannelMediaOptions(options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannel() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->leaveChannel();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannel(agora::rtc::LeaveChannelOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->leaveChannel(options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::renewToken(char const* token) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->renewToken(token);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setChannelProfile(agora::CHANNEL_PROFILE_TYPE profile) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setChannelProfile(profile);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setClientRole(role);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role, agora::rtc::ClientRoleOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setClientRole(role, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startEchoTest() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startEchoTest();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startEchoTest(int intervalInSeconds) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startEchoTest(intervalInSeconds);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startEchoTest(const EchoTestConfiguration& config)
			{
				return 0;
			}

			int RtcEngineProxy::setLowlightEnhanceOptions(bool enabled, const LowlightEnhanceOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				return 0;
			}

			int RtcEngineProxy::setVideoDenoiserOptions(bool enabled, const VideoDenoiserOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				return 0;
			}

			int RtcEngineProxy::setColorEnhanceOptions(bool enabled, const ColorEnhanceOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				return 0;
			}

			int RtcEngineProxy::enableVirtualBackground(bool enabled, VirtualBackgroundSource backgroundSource, SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				return 0;
			}

			int RtcEngineProxy::stopEchoTest() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopEchoTest();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableVideo() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableVideo();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::disableVideo() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->disableVideo();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPreview() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startPreview();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPreview(agora::rtc::VIDEO_SOURCE_TYPE sourceType) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startPreview(sourceType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPreview() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopPreview();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPreview(agora::rtc::VIDEO_SOURCE_TYPE sourceType) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopPreview(sourceType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startLastmileProbeTest(agora::rtc::LastmileProbeConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startLastmileProbeTest(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopLastmileProbeTest() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopLastmileProbeTest();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoEncoderConfiguration(agora::rtc::VideoEncoderConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setVideoEncoderConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setBeautyEffectOptions(bool enabled, agora::rtc::BeautyOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setBeautyEffectOptions(enabled, options, type);
				}
				return -ERROR_NULLPTR;
			}

			/*int RtcEngineProxy::enableVirtualBackground(bool enabled, agora::rtc::VirtualBackgroundSource backgroundSource) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableVirtualBackground(enabled, backgroundSource);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::enableRemoteSuperResolution(agora::rtc::uid_t userId, bool enable) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableRemoteSuperResolution(userId, enable);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setupRemoteVideo(agora::rtc::VideoCanvas const& canvas) {
				if (_rtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						_videoRenderMgr->setRenderImage((UImage*)canvas.view, canvas.uid, "", canvas.sourceType);
					}
					else {
						_videoRenderMgr->releaseVideoRender(canvas.uid, "", canvas.sourceType);
					}
					return -ERROR_OK;
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setupLocalVideo(agora::rtc::VideoCanvas const& canvas) {
				if (_rtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						_videoRenderMgr->setRenderImage((UImage*)canvas.view, canvas.uid, "", canvas.sourceType);
					}
					else {
						_videoRenderMgr->releaseVideoRender(canvas.uid, "", canvas.sourceType);
						//_videoRenderMgr->releaseAllVideoRender();
					}
					return -ERROR_OK;
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableAudio() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableAudio();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::disableAudio() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->disableAudio();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioProfile(agora::rtc::AUDIO_PROFILE_TYPE profile, agora::rtc::AUDIO_SCENARIO_TYPE scenario) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioProfile(profile, scenario);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioProfile(agora::rtc::AUDIO_PROFILE_TYPE profile) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioProfile(profile);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::setAudioScenario(AUDIO_SCENARIO_TYPE scenario)
			{
				return 0;
			}

			int RtcEngineProxy::enableLocalAudio(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableLocalAudio(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteLocalAudioStream(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteLocalAudioStream(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteAllRemoteAudioStreams(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteAllRemoteAudioStreams(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDefaultMuteAllRemoteAudioStreams(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setDefaultMuteAllRemoteAudioStreams(mute);
				}
				return -ERROR_NULLPTR;
			}



			int RtcEngineProxy::muteRemoteAudioStream(agora::rtc::uid_t uid, bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteRemoteAudioStream(uid, mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteLocalVideoStream(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteLocalVideoStream(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLocalVideo(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableLocalVideo(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteAllRemoteVideoStreams(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteAllRemoteVideoStreams(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDefaultMuteAllRemoteVideoStreams(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setDefaultMuteAllRemoteVideoStreams(mute);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::setSubscribeAudioBlacklist(uid_t* uidList, int uidNumber)
			{
				return 0;
			}

			int RtcEngineProxy::setSubscribeAudioWhitelist(uid_t* uidList, int uidNumber)
			{
				return 0;
			}

			int RtcEngineProxy::setSubscribeVideoBlacklist(uid_t* uidList, int uidNumber)
			{
				return 0;
			}

			int RtcEngineProxy::setSubscribeVideoWhitelist(uid_t* uidList, int uidNumber)
			{
				return 0;
			}

			int RtcEngineProxy::startAudioMixing(const char* filePath, bool loopback, int cycle)
			{
				return 0;
			}

			int RtcEngineProxy::startAudioMixing(const char* filePath, bool loopback, int cycle, int startPos)
			{
				return 0;
			}

			int RtcEngineProxy::selectAudioTrack(int index)
			{
				return 0;
			}

			int RtcEngineProxy::getAudioTrackCount()
			{
				return 0;
			}

			int RtcEngineProxy::setAudioMixingDualMonoMode(media::AUDIO_MIXING_DUAL_MONO_MODE mode)
			{
				return 0;
			}

			int RtcEngineProxy::getEffectDuration(const char* filePath)
			{
				return 0;
			}

			int RtcEngineProxy::setEffectPosition(int soundId, int pos)
			{
				return 0;
			}

			int RtcEngineProxy::getEffectCurrentPosition(int soundId)
			{
				return 0;
			}

			int RtcEngineProxy::setDualStreamMode(SIMULCAST_STREAM_MODE mode)
			{
				return 0;
			}

			int RtcEngineProxy::setDualStreamMode(VIDEO_SOURCE_TYPE sourceType, SIMULCAST_STREAM_MODE mode)
			{
				return 0;
			}

			int RtcEngineProxy::setDualStreamMode(VIDEO_SOURCE_TYPE sourceType, SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig)
			{
				return 0;
			}

			int RtcEngineProxy::adjustLoopbackSignalVolume(int volume)
			{
				return 0;
			}

			agora::rtc::video_track_id_t RtcEngineProxy::createCustomVideoTrack()
			{
				return 0;
			}

			agora::rtc::video_track_id_t RtcEngineProxy::createCustomEncodedVideoTrack(const SenderOptions& sender_option)
			{
				return 0;
			}

			int RtcEngineProxy::destroyCustomVideoTrack(video_track_id_t video_track_id)
			{
				return 0;
			}

			int RtcEngineProxy::destroyCustomEncodedVideoTrack(video_track_id_t video_track_id)
			{
				return 0;
			}

			int RtcEngineProxy::enableWirelessAccelerate(bool enabled)
			{
				return 0;
			}

			int RtcEngineProxy::muteRemoteVideoStream(agora::rtc::uid_t uid, bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteRemoteVideoStream(uid, mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoStreamType(agora::rtc::uid_t uid, agora::rtc::VIDEO_STREAM_TYPE streamType) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteVideoStreamType(uid, streamType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoSubscriptionOptions(agora::rtc::uid_t uid, agora::rtc::VideoSubscriptionOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteVideoSubscriptionOptions(uid, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteDefaultVideoStreamType(agora::rtc::VIDEO_STREAM_TYPE streamType) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteDefaultVideoStreamType(streamType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableAudioVolumeIndication(int interval, int smooth, bool reportVad) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableAudioVolumeIndication(interval, smooth, reportVad);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioRecording(char const* filePath, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startAudioRecording(filePath, quality);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioRecording(char const* filePath, int sampleRate, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startAudioRecording(filePath, sampleRate, quality);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioRecording(agora::rtc::AudioRecordingConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startAudioRecording(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerAudioEncodedFrameObserver(agora::rtc::AudioEncodedFrameObserverConfig const& config, agora::rtc::IAudioEncodedFrameObserver* observer) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->registerAudioEncodedFrameObserver(config, observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAudioRecording() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopAudioRecording();
				}
				return -ERROR_NULLPTR;
			}

			agora_refptr<agora::rtc::IMediaPlayer> RtcEngineProxy::createMediaPlayer() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->createMediaPlayer();
				}
				return nullptr;
			}

			int RtcEngineProxy::destroyMediaPlayer(agora_refptr<agora::rtc::IMediaPlayer> media_player) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->destroyMediaPlayer(media_player);
				}
				return -ERROR_NULLPTR;
			}

			/*int RtcEngineProxy::startAudioMixing(char const* filePath, bool loopback, bool replace, int cycle) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startAudioMixing(filePath, loopback, replace, cycle);
				}
				return -ERROR_NULLPTR;
			}*/

			/*int RtcEngineProxy::startAudioMixing(char const* filePath, bool loopback, bool replace, int cycle, int startPos) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startAudioMixing(filePath, loopback, replace, cycle, startPos);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::stopAudioMixing() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopAudioMixing();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAudioMixing() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->pauseAudioMixing();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAudioMixing() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->resumeAudioMixing();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustAudioMixingVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustAudioMixingVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustAudioMixingPublishVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustAudioMixingPublishVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingPublishVolume() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getAudioMixingPublishVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustAudioMixingPlayoutVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustAudioMixingPlayoutVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingPlayoutVolume() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getAudioMixingPlayoutVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingDuration() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getAudioMixingDuration();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingCurrentPosition() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getAudioMixingCurrentPosition();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioMixingPosition(int pos) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioMixingPosition(pos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioMixingPitch(int pitch) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioMixingPitch(pitch);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getEffectsVolume() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getEffectsVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEffectsVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setEffectsVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::preloadEffect(int soundId, char const* filePath, int startPos) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->preloadEffect(soundId, filePath, startPos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::playEffect(int soundId, char const* filePath, int loopCount, double pitch, double pan, int gain, bool publish, int startPos) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->playEffect(soundId, filePath, loopCount, pitch, pan, gain, publish, startPos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::playAllEffects(int loopCount, double pitch, double pan, int gain, bool publish) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->playAllEffects(loopCount, pitch, pan, gain, publish);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getVolumeOfEffect(int soundId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getVolumeOfEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVolumeOfEffect(int soundId, int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setVolumeOfEffect(soundId, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseEffect(int soundId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->pauseEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAllEffects() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->pauseAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeEffect(int soundId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->resumeEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAllEffects() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->resumeAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopEffect(int soundId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAllEffects() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unloadEffect(int soundId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->unloadEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unloadAllEffects() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->unloadAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableSoundPositionIndication(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableSoundPositionIndication(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVoicePosition(agora::rtc::uid_t uid, double pan, double gain) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteVoicePosition(uid, pan, gain);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableSpatialAudio(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableSpatialAudio(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteUserSpatialAudioParams(agora::rtc::uid_t uid, agora::SpatialAudioParams const& params) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteUserSpatialAudioParams(uid, params);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceBeautifierPreset(agora::rtc::VOICE_BEAUTIFIER_PRESET preset) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setVoiceBeautifierPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioEffectPreset(agora::rtc::AUDIO_EFFECT_PRESET preset) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioEffectPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceConversionPreset(agora::rtc::VOICE_CONVERSION_PRESET preset) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setVoiceConversionPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioEffectParameters(agora::rtc::AUDIO_EFFECT_PRESET preset, int param1, int param2) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioEffectParameters(preset, param1, param2);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceBeautifierParameters(agora::rtc::VOICE_BEAUTIFIER_PRESET preset, int param1, int param2) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setVoiceBeautifierParameters(preset, param1, param2);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceConversionParameters(agora::rtc::VOICE_CONVERSION_PRESET preset, int param1, int param2) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setVoiceConversionParameters(preset, param1, param2);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVoicePitch(double pitch) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalVoicePitch(pitch);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalVoiceEqualization(bandFrequency, bandGain);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalVoiceReverb(reverbKey, value);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogFile(char const* filePath) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLogFile(filePath);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogFilter(unsigned int filter) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLogFilter(filter);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogLevel(commons::LOG_LEVEL level) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLogLevel(level);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogFileSize(unsigned int fileSizeInKBytes) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLogFileSize(fileSizeInKBytes);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::uploadLogFile(agora::util::AString& requestId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->uploadLogFile(requestId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalRenderMode(renderMode, mirrorMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteRenderMode(agora::rtc::uid_t uid, media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteRenderMode(uid, renderMode, mirrorMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalRenderMode(renderMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalVideoMirrorMode(mirrorMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamMode(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableDualStreamMode(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamMode(agora::rtc::VIDEO_SOURCE_TYPE sourceType, bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableDualStreamMode(sourceType, enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamMode(agora::rtc::VIDEO_SOURCE_TYPE sourceType, bool enabled, agora::rtc::SimulcastStreamConfig const& streamConfig) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableDualStreamMode(sourceType, enabled, streamConfig);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableEchoCancellationExternal(bool enabled, int audioSourceDelay) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableEchoCancellationExternal(enabled, audioSourceDelay);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableCustomAudioLocalPlayback(int sourceId, bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableCustomAudioLocalPlayback(sourceId, enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPrimaryCustomAudioTrack(agora::rtc::AudioTrackConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startPrimaryCustomAudioTrack(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPrimaryCustomAudioTrack() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopPrimaryCustomAudioTrack();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startSecondaryCustomAudioTrack(agora::rtc::AudioTrackConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startSecondaryCustomAudioTrack(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopSecondaryCustomAudioTrack() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopSecondaryCustomAudioTrack();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRecordingAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setPlaybackAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

		/*	int RtcEngineProxy::setEarMonitoringAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setEarMonitoringAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::setPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableAudioSpectrumMonitor(int intervalInMS) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableAudioSpectrumMonitor(intervalInMS);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::disableAudioSpectrumMonitor() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->disableAudioSpectrumMonitor();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->registerAudioSpectrumObserver(observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unregisterAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->unregisterAudioSpectrumObserver(observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustRecordingSignalVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustRecordingSignalVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRecordingSignal(bool mute) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->muteRecordingSignal(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustPlaybackSignalVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustPlaybackSignalVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustUserPlaybackSignalVolume(unsigned int uid, int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustUserPlaybackSignalVolume(uid, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalPublishFallbackOption(option);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteSubscribeFallbackOption(option);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLoopbackRecording(bool enabled, char const* deviceName) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableLoopbackRecording(enabled, deviceName);
				}
				return -ERROR_NULLPTR;
			}

			/*int RtcEngineProxy::adjustLoopbackRecordingVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustLoopbackRecordingVolume(volume);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::getLoopbackRecordingVolume() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getLoopbackRecordingVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableInEarMonitoring(bool enabled, int includeAudioFilters) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableInEarMonitoring(enabled, includeAudioFilters);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setInEarMonitoringVolume(int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setInEarMonitoringVolume(volume);
				}
				return -ERROR_NULLPTR;
			}
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
			int RtcEngineProxy::loadExtensionProvider(const char* path, bool unload_after_use) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->loadExtensionProvider(path, unload_after_use);
				}
				return -ERROR_NULLPTR;
			}
#endif
			int RtcEngineProxy::setExtensionProviderProperty(char const* provider, char const* key, char const* value) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setExtensionProviderProperty(provider, key, value);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableExtension(char const* provider, char const* extension, bool enable, agora::media::MEDIA_SOURCE_TYPE type) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableExtension(provider, extension, enable, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setExtensionProperty(char const* provider, char const* extension, char const* key, char const* value, agora::media::MEDIA_SOURCE_TYPE type) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setExtensionProperty(provider, extension, key, value, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getExtensionProperty(char const* provider, char const* extension, char const* key, char* value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getExtensionProperty(provider, extension, key, value, buf_len, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraCapturerConfiguration(agora::rtc::CameraCapturerConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraCapturerConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
			int RtcEngineProxy::switchCamera() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->switchCamera();
				}
				return -ERROR_NULLPTR;
			}

			bool RtcEngineProxy::isCameraZoomSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraZoomSupported();
				}
				return false;
			}

			bool RtcEngineProxy::isCameraFaceDetectSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraFaceDetectSupported();
				}
				return false;
			}

			bool RtcEngineProxy::isCameraTorchSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraTorchSupported();
				}
				return false;
			}

			bool RtcEngineProxy::isCameraFocusSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraFocusSupported();
				}
				return false;
			}

			bool RtcEngineProxy::isCameraAutoFocusFaceModeSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraAutoFocusFaceModeSupported();
				}
				return false;
			}

			int RtcEngineProxy::setCameraZoomFactor(float factor) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraZoomFactor(factor);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableFaceDetection(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableFaceDetection(enabled);
				}
				return -ERROR_NULLPTR;
			}

			float RtcEngineProxy::getCameraMaxZoomFactor() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getCameraMaxZoomFactor();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraFocusPositionInPreview(float positionX, float positionY) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraFocusPositionInPreview(positionX, positionY);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraTorchOn(bool isOn) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraTorchOn(isOn);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraAutoFocusFaceModeEnabled(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraAutoFocusFaceModeEnabled(enabled);
				}
				return -ERROR_NULLPTR;
			}

			bool RtcEngineProxy::isCameraExposurePositionSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraExposurePositionSupported();
				}
				return false;
			}

			int RtcEngineProxy::setCameraExposurePosition(float positionXinView, float positionYinView) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraExposurePosition(positionXinView, positionYinView);
				}
				return -ERROR_NULLPTR;
			}
#if defined(__APPLE__)
			bool RtcEngineProxy::isCameraAutoExposureFaceModeSupported() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isCameraAutoExposureFaceModeSupported();
				}
				return false;
			}

			int RtcEngineProxy::setCameraAutoExposureFaceModeEnabled(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraAutoExposureFaceModeEnabled(enabled);
				}
				return -ERROR_NULLPTR;
			}
#endif
			int RtcEngineProxy::setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEnableSpeakerphone(bool speakerOn) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setEnableSpeakerphone(speakerOn);
				}
				return -ERROR_NULLPTR;
			}

			bool RtcEngineProxy::isSpeakerphoneEnabled() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->isSpeakerphoneEnabled();
				}
				return false;
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
			agora::rtc::IScreenCaptureSourceList* RtcEngineProxy::getScreenCaptureSources(SIZE const& thumbSize, SIZE const& iconSize, bool const includeScreen) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getScreenCaptureSources(thumbSize, iconSize, includeScreen);
				}
				return nullptr;
			}
#endif
#if (defined(__APPLE__) && TARGET_OS_IOS)
			int RtcEngineProxy::setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAudioSessionOperationRestriction(restriction);
				}
				return -ERROR_NULLPTR;
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
			int RtcEngineProxy::startScreenCaptureByDisplayId(uint32_t displayId, agora::rtc::Rectangle const& regionRect, agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startScreenCaptureByDisplayId(displayId, regionRect, captureParams);
				}
				return -ERROR_NULLPTR;
			}
#endif
#if defined(_WIN32)
			int RtcEngineProxy::startScreenCaptureByScreenRect(agora::rtc::Rectangle const& screenRect, agora::rtc::Rectangle const& regionRect, agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, captureParams);
				}
				return -ERROR_NULLPTR;
			}


#endif
#if defined(__ANDROID__)
			//int RtcEngineProxy::startScreenCapture(void* mediaProjectionPermissionResultData, agora::rtc::ScreenCaptureParameters const& captureParams) {
			//	if (_rtcEngine != nullptr) {
			//		return _rtcEngine->startScreenCapture(mediaProjectionPermissionResultData, captureParams);
			//	}
			//	return -ERROR_NULLPTR;
			//}

			int RtcEngineProxy::startScreenCapture(const ScreenCaptureParameters2& captureParams)
			{
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startScreenCapture(captureParams);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateScreenCapture(const ScreenCaptureParameters2& captureParams)
			{
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateScreenCapture(captureParams);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioDeviceInfo(agora::rtc::DeviceInfo& deviceInfo) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getAudioDeviceInfo(deviceInfo);
				}
				return -ERROR_NULLPTR;
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
			int RtcEngineProxy::startScreenCaptureByWindowId(agora::view_t windowId, agora::rtc::Rectangle const& regionRect, agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startScreenCaptureByWindowId(windowId, regionRect, captureParams);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setScreenCaptureContentHint(agora::rtc::VIDEO_CONTENT_HINT contentHint) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setScreenCaptureContentHint(contentHint);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setScreenCaptureScenario(agora::rtc::SCREEN_SCENARIO_TYPE screenScenario) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setScreenCaptureScenario(screenScenario);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateScreenCaptureRegion(agora::rtc::Rectangle const& regionRect) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateScreenCaptureRegion(regionRect);
				}
				return -ERROR_NULLPTR;
			}
			int RtcEngineProxy::updateScreenCaptureParameters(agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateScreenCaptureParameters(captureParams);
				}
				return -ERROR_NULLPTR;
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)|| defined(__ANDROID__)
			int RtcEngineProxy::stopScreenCapture() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopScreenCapture();
				}
				return -ERROR_NULLPTR;
			}
#endif 
			int RtcEngineProxy::getCallId(agora::util::AString& callId) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getCallId(callId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::rate(char const* callId, int rating, char const* description) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->rate(callId, rating, description);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::complain(char const* callId, char const* description) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->complain(callId, description);
				}
				return -ERROR_NULLPTR;
			}

		/*	int RtcEngineProxy::addPublishStreamUrl(char const* url, bool transcodingEnabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->addPublishStreamUrl(url, transcodingEnabled);
				}
				return -ERROR_NULLPTR;
			}*/

		/*	int RtcEngineProxy::removePublishStreamUrl(char const* url) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->removePublishStreamUrl(url);
				}
				return -ERROR_NULLPTR;
			}*/

		/*	int RtcEngineProxy::setLiveTranscoding(agora::rtc::LiveTranscoding const& transcoding) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLiveTranscoding(transcoding);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::startRtmpStreamWithoutTranscoding(char const* url) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startRtmpStreamWithoutTranscoding(url);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startRtmpStreamWithTranscoding(char const* url, agora::rtc::LiveTranscoding const& transcoding) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startRtmpStreamWithTranscoding(url, transcoding);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateRtmpTranscoding(agora::rtc::LiveTranscoding const& transcoding) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateRtmpTranscoding(transcoding);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopRtmpStream(char const* url) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopRtmpStream(url);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startLocalVideoTranscoder(agora::rtc::LocalTranscoderConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startLocalVideoTranscoder(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateLocalTranscoderConfiguration(agora::rtc::LocalTranscoderConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateLocalTranscoderConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopLocalVideoTranscoder() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopLocalVideoTranscoder();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPrimaryCameraCapture(agora::rtc::CameraCapturerConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startPrimaryCameraCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startSecondaryCameraCapture(agora::rtc::CameraCapturerConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startSecondaryCameraCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPrimaryCameraCapture() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopPrimaryCameraCapture();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopSecondaryCameraCapture() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopSecondaryCameraCapture();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraDeviceOrientation(agora::rtc::VIDEO_SOURCE_TYPE type, agora::rtc::VIDEO_ORIENTATION orientation) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCameraDeviceOrientation(type, orientation);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setScreenCaptureOrientation(agora::rtc::VIDEO_SOURCE_TYPE type, agora::rtc::VIDEO_ORIENTATION orientation) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setScreenCaptureOrientation(type, orientation);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPrimaryScreenCapture(agora::rtc::ScreenCaptureConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startPrimaryScreenCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startSecondaryScreenCapture(agora::rtc::ScreenCaptureConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startSecondaryScreenCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPrimaryScreenCapture() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopPrimaryScreenCapture();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopSecondaryScreenCapture() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopSecondaryScreenCapture();
				}
				return -ERROR_NULLPTR;
			}

			agora::rtc::CONNECTION_STATE_TYPE RtcEngineProxy::getConnectionState() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getConnectionState();
				}
				return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
			}

			bool RtcEngineProxy::registerEventHandler(agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->registerEventHandler(eventHandler);
				}
				return false;
			}

			bool RtcEngineProxy::unregisterEventHandler(agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->unregisterEventHandler(eventHandler);
				}
				return false;
			}

			int RtcEngineProxy::setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setRemoteUserPriority(uid, userPriority);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerPacketObserver(agora::rtc::IPacketObserver* observer) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->registerPacketObserver(observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEncryptionMode(char const* encryptionMode) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setEncryptionMode(encryptionMode);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::setEncryptionSecret(char const* secret) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setEncryptionSecret(secret);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::enableEncryption(bool enabled, agora::rtc::EncryptionConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableEncryption(enabled, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStream(int* streamId, bool reliable, bool ordered) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->createDataStream(streamId, reliable, ordered);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStream(int* streamId, agora::rtc::DataStreamConfig& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->createDataStream(streamId, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendStreamMessage(int streamId, char const* data, size_t length) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->sendStreamMessage(streamId, data, length);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addVideoWatermark(agora::rtc::RtcImage const& watermark) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->addVideoWatermark(watermark);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addVideoWatermark(char const* watermarkUrl, agora::rtc::WatermarkOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->addVideoWatermark(watermarkUrl, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::clearVideoWatermark() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->clearVideoWatermark();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::clearVideoWatermarks() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->clearVideoWatermarks();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addInjectStreamUrl(char const* url, agora::rtc::InjectStreamConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->addInjectStreamUrl(url, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::removeInjectStreamUrl(char const* url) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->removeInjectStreamUrl(url);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAudio() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->pauseAudio();
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::resumeAudio() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->resumeAudio();
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::enableWebSdkInteroperability(bool enabled) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableWebSdkInteroperability(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAdvancedAudioOptions(AdvancedAudioOptions& options)
			{
				return 0;
			}

			int RtcEngineProxy::sendCustomReportMessage(char const* id, char const* category, char const* event, char const* label, int value) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->sendCustomReportMessage(id, category, event, label, value);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerMediaMetadataObserver(agora::rtc::IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->registerMediaMetadataObserver(observer, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unregisterMediaMetadataObserver(agora::rtc::IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->unregisterMediaMetadataObserver(observer, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioFrameDump(char const* channel_id, agora::rtc::uid_t user_id, char const* location, char const* uuid, char const* passwd, long duration_ms, bool auto_upload) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startAudioFrameDump(channel_id, user_id, location, uuid, passwd, duration_ms, auto_upload);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAudioFrameDump(char const* channel_id, agora::rtc::uid_t user_id, char const* location) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopAudioFrameDump(channel_id, user_id, location);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerLocalUserAccount(char const* appId, char const* userAccount) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->registerLocalUserAccount(appId, userAccount);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelWithUserAccount(char const* token, char const* channelId, char const* userAccount) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->joinChannelWithUserAccount(token, channelId, userAccount);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelWithUserAccount(char const* token, char const* channelId, char const* userAccount, agora::rtc::ChannelMediaOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->joinChannelWithUserAccount(token, channelId, userAccount, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelWithUserAccountEx(char const* token, char const* channelId, char const* userAccount, agora::rtc::ChannelMediaOptions const& options, agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->joinChannelWithUserAccountEx(token, channelId, userAccount, options, eventHandler);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUserAccount(char const* userAccount, rtc::UserInfo* userInfo) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getUserInfoByUserAccount(userAccount, userInfo);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUid(agora::rtc::uid_t uid, rtc::UserInfo* userInfo) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getUserInfoByUid(uid, userInfo);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startChannelMediaRelay(agora::rtc::ChannelMediaRelayConfiguration const& configuration) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startChannelMediaRelay(configuration);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaRelay(agora::rtc::ChannelMediaRelayConfiguration const& configuration) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateChannelMediaRelay(configuration);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopChannelMediaRelay() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopChannelMediaRelay();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAllChannelMediaRelay() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->pauseAllChannelMediaRelay();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAllChannelMediaRelay() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->resumeAllChannelMediaRelay();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDirectCdnStreamingAudioConfiguration(agora::rtc::AUDIO_PROFILE_TYPE profile) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setDirectCdnStreamingAudioConfiguration(profile);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDirectCdnStreamingVideoConfiguration(agora::rtc::VideoEncoderConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setDirectCdnStreamingVideoConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startDirectCdnStreaming(agora::rtc::IDirectCdnStreamingEventHandler* eventHandler, char const* publishUrl, agora::rtc::DirectCdnStreamingMediaOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startDirectCdnStreaming(eventHandler, publishUrl, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopDirectCdnStreaming() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopDirectCdnStreaming();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateDirectCdnStreamingMediaOptions(agora::rtc::DirectCdnStreamingMediaOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->updateDirectCdnStreamingMediaOptions(options);
				}
				return -ERROR_NULLPTR;
			}

			/*int RtcEngineProxy::pushDirectCdnStreamingCustomVideoFrame(media::base::ExternalVideoFrame* frame) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->pushDirectCdnStreamingCustomVideoFrame(frame);
				}
				return -ERROR_NULLPTR;
			}*/

			/*int RtcEngineProxy::switchChannel(char const* token, char const* channel) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->switchChannel(token, channel);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::startRhythmPlayer(char const* sound1, char const* sound2, agora::rtc::AgoraRhythmPlayerConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->startRhythmPlayer(sound1, sound2, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopRhythmPlayer() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->stopRhythmPlayer();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::configRhythmPlayer(agora::rtc::AgoraRhythmPlayerConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->configRhythmPlayer(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::takeSnapshot(agora::rtc::uid_t uid, char const* filePath) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->takeSnapshot(uid, filePath);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableContentInspect(bool enabled, media::ContentInspectConfig const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableContentInspect(enabled, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustCustomAudioPublishVolume(int32_t sourceId, int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustCustomAudioPublishVolume(sourceId, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustCustomAudioPlayoutVolume(int32_t sourceId, int volume) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->adjustCustomAudioPlayoutVolume(sourceId, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCloudProxy(agora::rtc::CLOUD_PROXY_TYPE proxyType) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setCloudProxy(proxyType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalAccessPoint(agora::rtc::LocalAccessPointConfiguration const& config) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setLocalAccessPoint(config);
				}
				return -ERROR_NULLPTR;
			}

			/*int RtcEngineProxy::enableFishCorrection(bool enabled, agora::rtc::FishCorrectionParams const& params) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableFishCorrection(enabled, params);
				}
				return -ERROR_NULLPTR;
			}*/

		/*	int RtcEngineProxy::setAdvancedAudioOptions(media::base::AdvancedAudioOptions& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAdvancedAudioOptions(options);
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::setAVSyncSource(char const* channelId, agora::rtc::uid_t uid) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->setAVSyncSource(channelId, uid);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableVideoImageSource(bool enable, agora::rtc::ImageTrackOptions const& options) {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->enableVideoImageSource(enable, options);
				}
				return -ERROR_NULLPTR;
			}

			/*int64_t RtcEngineProxy::getCurrentMonotonicTimeInMs() {
				if (_rtcEngine != nullptr) {
					return _rtcEngine->getCurrentMonotonicTimeInMs();
				}
				return -ERROR_NULLPTR;
			}*/

			int RtcEngineProxy::joinChannelEx(const char* token, const RtcConnection& connection, const ChannelMediaOptions& options, IRtcEngineEventHandler* eventHandler) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->joinChannelEx(token, connection, options, eventHandler);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannelEx(const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->leaveChannelEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaOptionsEx(const ChannelMediaOptions& options, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->updateChannelMediaOptionsEx(options, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoEncoderConfigurationEx(const VideoEncoderConfiguration& config, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setVideoEncoderConfigurationEx(config, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setupRemoteVideoEx(const VideoCanvas& canvas, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						_videoRenderMgr->setRenderImage((UImage*)canvas.view, canvas.uid, connection.channelId, canvas.sourceType);
					}
					else {
						_videoRenderMgr->releaseVideoRender(canvas.uid, connection.channelId, canvas.sourceType);
					}
					return -ERROR_OK;
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRemoteAudioStreamEx(uid_t uid, bool mute, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->muteRemoteAudioStreamEx(uid, mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRemoteVideoStreamEx(uid_t uid, bool mute, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->muteRemoteVideoStreamEx(uid, mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoStreamTypeEx(uid_t uid, VIDEO_STREAM_TYPE streamType, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setRemoteVideoStreamTypeEx(uid, streamType, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoSubscriptionOptionsEx(uid_t uid, const VideoSubscriptionOptions& options, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setRemoteVideoSubscriptionOptionsEx(uid, options, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVoicePositionEx(uid_t uid, double pan, double gain, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setRemoteVoicePositionEx(uid, pan, gain, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteUserSpatialAudioParamsEx(uid_t uid, const agora::SpatialAudioParams& params, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setRemoteUserSpatialAudioParamsEx(uid, params, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteRenderModeEx(uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setRemoteRenderModeEx(uid, renderMode, mirrorMode, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLoopbackRecordingEx(const RtcConnection& connection, bool enabled, const char* deviceName) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->enableLoopbackRecordingEx(connection, enabled, deviceName);
				}
				return -ERROR_NULLPTR;
			}

			CONNECTION_STATE_TYPE RtcEngineProxy::getConnectionStateEx(const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->getConnectionStateEx(connection);
				}
				return CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
			}

			int RtcEngineProxy::enableEncryptionEx(const RtcConnection& connection, bool enabled, const EncryptionConfig& config) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->enableEncryptionEx(connection, enabled, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStreamEx(int* streamId, bool reliable, bool ordered, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->createDataStreamEx(streamId, reliable, ordered, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStreamEx(int* streamId, DataStreamConfig& config, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->createDataStreamEx(streamId, config, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendStreamMessageEx(int streamId, const char* data, size_t length, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->sendStreamMessageEx(streamId, data, length, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addVideoWatermarkEx(const char* watermarkUrl, const WatermarkOptions& options, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->addVideoWatermarkEx(watermarkUrl, options, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::clearVideoWatermarkEx(const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->clearVideoWatermarkEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendCustomReportMessageEx(const char* id, const char* category, const char* event, const char* label, int value, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->sendCustomReportMessageEx(id, category, event, label, value, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->enableAudioVolumeIndicationEx(interval, smooth, reportVad, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUserAccountEx(const char* userAccount, rtc::UserInfo* userInfo, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->getUserInfoByUserAccountEx(userAccount, userInfo, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUidEx(uid_t uid, rtc::UserInfo* userInfo, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->getUserInfoByUidEx(uid, userInfo, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoProfileEx(int width, int height, int frameRate, int bitrate) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->setVideoProfileEx(width, height, frameRate, bitrate);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamModeEx(VIDEO_SOURCE_TYPE sourceType, bool enabled, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->enableDualStreamModeEx(sourceType, enabled, streamConfig, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeAudioBlacklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				return 0;
			}

			int RtcEngineProxy::setSubscribeAudioWhitelistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				return 0;
			}

			int RtcEngineProxy::setSubscribeVideoBlacklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				return 0;
			}

			int RtcEngineProxy::setSubscribeVideoWhitelistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				return 0;
			}

			int RtcEngineProxy::setDualStreamModeEx(VIDEO_SOURCE_TYPE sourceType, SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection)
			{
				return 0;
			}

			int RtcEngineProxy::takeSnapshotEx(const RtcConnection& connection, uid_t uid, const char* filePath)
			{
				return 0;
			}

			/*int RtcEngineProxy::addPublishStreamUrlEx(const char* url, bool transcodingEnabled, const RtcConnection& connection) {
				if (_rtcEngine != nullptr) {
					return ((IRtcEngineEx*)_rtcEngine)->addPublishStreamUrlEx(url, transcodingEnabled, connection);
				}
				return -ERROR_NULLPTR;
			}*/
		}
	}
}


