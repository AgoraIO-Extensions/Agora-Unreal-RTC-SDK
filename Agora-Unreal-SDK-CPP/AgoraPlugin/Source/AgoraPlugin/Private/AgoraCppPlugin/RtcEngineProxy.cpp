#include "AgoraCppPlugin/Include/RtcEngineProxy.h"
#include "AgoraPluginInterface.h"

namespace agora
{
	namespace rtc
	{
		namespace ue
		{
			RtcEngineProxy* RtcEngineProxy::Instance = nullptr;
			std::mutex RtcEngineProxy::MutexLock;

			agora::rtc::IRtcEngine* createAgoraRtcEngine()
			{
				return RtcEngineProxy::GetInstance();
			}

			RtcEngineProxy* RtcEngineProxy::GetInstance()
			{
				if(Instance == nullptr){
					std::unique_lock<std::mutex> lock(MutexLock);
					if (Instance == nullptr) {
						Instance = new RtcEngineProxy();
						Instance->InitInstance();
					}
				}
		
				return Instance;
			}


			void RtcEngineProxy::ReleaseInstance()
			{
				if (Instance != nullptr) {
					std::unique_lock<std::mutex> lock(MutexLock);
					if (Instance != nullptr) {
						Instance->UnInitInstance();
						delete Instance;
						Instance = nullptr;
					}
				}
			}


			void RtcEngineProxy::InitInstance()
			{
#if PLATFORM_ANDROID
				if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
				{
					static jmethodID LoadLibrary = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "LoadLibrary", "()V", false);
					FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadLibrary);
					if (LoadLibrary != NULL)
					{
						FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadLibrary);
					}

					static jmethodID LoadAndroidScreenCaptureSo = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "LoadAndroidScreenCaptureSo", "()V", false);
					if (LoadAndroidScreenCaptureSo != NULL)
					{
						FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadAndroidScreenCaptureSo);
					}
				}
#endif
				RtcEngine = ::createAgoraRtcEngine();
				VideoRenderMgr = MakeShareable(new VideoRenderManager());	
			}


			void RtcEngineProxy::UnInitInstance(bool sync /*= false*/)
			{
				RtcEngine->release(sync);
				RtcEngine = nullptr;
			}

			RtcEngineProxy::RtcEngineProxy(){}
			RtcEngineProxy::~RtcEngineProxy(){}

			void RtcEngineProxy::release(bool sync) {
				if (Instance != nullptr)
				{
					RtcEngineProxy::ReleaseInstance();
				}
			}

			int RtcEngineProxy::initialize(agora::rtc::RtcEngineContext const& context) {
				int ret = RtcEngine->initialize(context);

				UE_LOG(LogTemp, Warning, TEXT("RtcEngineProxy initialize %d"), ret);
				if (RtcEngine != nullptr && ret == 0)
				{
					AppType appType = kAppTypeUnreal;
					char parametersType[512] = "";
					sprintf(parametersType, "{\"rtc.set_app_type\": %d}", appType);
					agora::base::AParameter apm(RtcEngine);
					apm->setParameters(parametersType);
#if PLATFORM_ANDROID
					char parametersDataOutput[512] = "";
					sprintf(parametersDataOutput, "{\"che.video.android_camera_output_type\":0}");
					apm->setParameters(parametersDataOutput);
#endif
					MediaProxy = MakeShareable(new MediaEngineProxy(RtcEngine));
					return ret;
				}
				else if(RtcEngine != nullptr && ret != 0)
				{
					return ret;
				}
				return -ERROR_NULLPTR;
			}
			int RtcEngineProxy::queryInterface(agora::rtc::INTERFACE_ID_TYPE iid, void** inter) {
				if (RtcEngine != nullptr) {
					if (iid == INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE)
					{
						*inter = (void*)(MediaProxy.Get());
						if (*inter == nullptr)
						{
							return -ERROR_NULLPTR;
						}
						return 0;
					}
					return RtcEngine->queryInterface(iid, inter);
				}
				return -ERROR_NULLPTR;
			}

#if defined(__APPLE__) && TARGET_OS_IOS
			int RtcEngineProxy::enableMultiCamera(bool enabled, const CameraCapturerConfiguration& config)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableMultiCamera(enabled, config);
				}
				return -ERROR_NULLPTR;
			}
#endif
			char const* RtcEngineProxy::getVersion(int* build) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getVersion(build);
				}
				return NULL;
			}

			char const* RtcEngineProxy::getErrorDescription(int code) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getErrorDescription(code);
				}
				return NULL;
			}

			int RtcEngineProxy::joinChannel(char const* token, char const* channelId, char const* info, agora::rtc::uid_t uid) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannel(token, channelId, info, uid);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannel(char const* token, char const* channelId, agora::rtc::uid_t uid, agora::rtc::ChannelMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannel(token, channelId, uid, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaOptions(agora::rtc::ChannelMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateChannelMediaOptions(options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannel() {
				if (RtcEngine != nullptr) {
					int ret = RtcEngine->leaveChannel();
					return ret;
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannel(agora::rtc::LeaveChannelOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->leaveChannel(options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::renewToken(char const* token) {
				if (RtcEngine != nullptr) {
					return RtcEngine->renewToken(token);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setChannelProfile(agora::CHANNEL_PROFILE_TYPE profile) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setChannelProfile(profile);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setClientRole(role);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role, agora::rtc::ClientRoleOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setClientRole(role, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startEchoTest() {
				if (RtcEngine != nullptr) {
					return RtcEngine->startEchoTest();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startEchoTest(int intervalInSeconds) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startEchoTest(intervalInSeconds);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startEchoTest(agora::rtc::EchoTestConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startEchoTest(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopEchoTest() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopEchoTest();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableVideo() {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVideo();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::disableVideo() {
				if (RtcEngine != nullptr) {
					return RtcEngine->disableVideo();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPreview() {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPreview();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPreview(agora::rtc::VIDEO_SOURCE_TYPE sourceType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPreview(sourceType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPreview() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPreview();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPreview(agora::rtc::VIDEO_SOURCE_TYPE sourceType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPreview(sourceType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startLastmileProbeTest(agora::rtc::LastmileProbeConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startLastmileProbeTest(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopLastmileProbeTest() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopLastmileProbeTest();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoEncoderConfiguration(agora::rtc::VideoEncoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVideoEncoderConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setBeautyEffectOptions(bool enabled, agora::rtc::BeautyOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setBeautyEffectOptions(enabled, options, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLowlightEnhanceOptions(bool enabled, agora::rtc::LowlightEnhanceOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLowlightEnhanceOptions(enabled, options, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoDenoiserOptions(bool enabled, agora::rtc::VideoDenoiserOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVideoDenoiserOptions(enabled, options, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setColorEnhanceOptions(bool enabled, agora::rtc::ColorEnhanceOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setColorEnhanceOptions(enabled, options, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableVirtualBackground(bool enabled, agora::rtc::VirtualBackgroundSource backgroundSource, agora::rtc::SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVirtualBackground(enabled, backgroundSource, segproperty, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableRemoteSuperResolution(agora::rtc::uid_t userId, bool enable) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableRemoteSuperResolution(userId, enable);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setupRemoteVideo(agora::rtc::VideoCanvas const& canvas) {

				if (RtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						VideoRenderMgr->setRenderImage((UImage*)canvas.view, canvas.uid, "", canvas.sourceType);
					}
					else {
						VideoRenderMgr->releaseVideoRender(canvas.uid, "", canvas.sourceType);
					}
					return -ERROR_OK;
				}
				return -ERROR_NULLPTR;
			}
			int RtcEngineProxy::setupLocalVideo(agora::rtc::VideoCanvas const& canvas) {


				if (RtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						VideoRenderMgr->setRenderImage((UImage*)canvas.view, canvas.uid, "", canvas.sourceType);
					}
					else {
						VideoRenderMgr->releaseVideoRender(canvas.uid, "", canvas.sourceType);
						//_videoRenderMgr->releaseAllVideoRender();
					}
					return -ERROR_OK;
				}
				return -ERROR_NULLPTR;
			}
			int RtcEngineProxy::enableAudio() {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableAudio();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::disableAudio() {
				if (RtcEngine != nullptr) {
					return RtcEngine->disableAudio();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) 
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioProfile(profile, scenario);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioProfile(AUDIO_PROFILE_TYPE profile)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioProfile(profile);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioScenario(agora::rtc::AUDIO_SCENARIO_TYPE scenario) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioScenario(scenario);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLocalAudio(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableLocalAudio(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteLocalAudioStream(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteLocalAudioStream(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteAllRemoteAudioStreams(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteAllRemoteAudioStreams(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDefaultMuteAllRemoteAudioStreams(bool mute) 
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setDefaultMuteAllRemoteAudioStreams(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRemoteAudioStream(agora::rtc::uid_t uid, bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteRemoteAudioStream(uid, mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteLocalVideoStream(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteLocalVideoStream(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLocalVideo(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableLocalVideo(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteAllRemoteVideoStreams(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteAllRemoteVideoStreams(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDefaultMuteAllRemoteVideoStreams(bool mute) 
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setDefaultMuteAllRemoteVideoStreams(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeAudioBlocklist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeAudioBlocklist(uidList, uidNumber);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeAudioAllowlist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeAudioAllowlist(uidList, uidNumber);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeVideoBlocklist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeVideoBlocklist(uidList, uidNumber);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeVideoAllowlist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeVideoAllowlist(uidList, uidNumber);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setHeadphoneEQPreset(HEADPHONE_EQUALIZER_PRESET preset)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setHeadphoneEQPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setHeadphoneEQParameters(int lowGain, int highGain)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setHeadphoneEQParameters(lowGain, highGain);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRemoteVideoStream(agora::rtc::uid_t uid, bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteRemoteVideoStream(uid, mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoStreamType(agora::rtc::uid_t uid, agora::rtc::VIDEO_STREAM_TYPE streamType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteVideoStreamType(uid, streamType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoSubscriptionOptions(agora::rtc::uid_t uid, agora::rtc::VideoSubscriptionOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteVideoSubscriptionOptions(uid, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteDefaultVideoStreamType(agora::rtc::VIDEO_STREAM_TYPE streamType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteDefaultVideoStreamType(streamType);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::enableAudioVolumeIndication(int interval, int smooth, bool reportVad) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableAudioVolumeIndication(interval, smooth, reportVad);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioRecording(char const* filePath, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioRecording(filePath, quality);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioRecording(char const* filePath, int sampleRate, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioRecording(filePath, sampleRate, quality);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioRecording(agora::rtc::AudioRecordingConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioRecording(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerAudioEncodedFrameObserver(agora::rtc::AudioEncodedFrameObserverConfig const& config, agora::rtc::IAudioEncodedFrameObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerAudioEncodedFrameObserver(config, observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAudioRecording() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAudioRecording();
				}
				return -ERROR_NULLPTR;
			}

			agora_refptr<agora::rtc::IMediaPlayer> RtcEngineProxy::createMediaPlayer() {
				if (RtcEngine != nullptr) {
					return RtcEngine->createMediaPlayer();
				}
				return NULL;
			}

			int RtcEngineProxy::destroyMediaPlayer(agora_refptr<agora::rtc::IMediaPlayer> media_player) {
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyMediaPlayer(media_player);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioMixing(char const* filePath, bool loopback, int cycle) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioMixing(filePath, loopback, cycle);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioMixing(char const* filePath, bool loopback, int cycle, int startPos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioMixing(filePath, loopback, cycle, startPos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAudioMixing() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAudioMixing();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAudioMixing() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAudioMixing();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAudioMixing() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAudioMixing();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::selectAudioTrack(int index) {
				if (RtcEngine != nullptr) {
					return RtcEngine->selectAudioTrack(index);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioTrackCount() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioTrackCount();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustAudioMixingVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustAudioMixingVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustAudioMixingPublishVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustAudioMixingPublishVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingPublishVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingPublishVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustAudioMixingPlayoutVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustAudioMixingPlayoutVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingPlayoutVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingPlayoutVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingDuration() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingDuration();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getAudioMixingCurrentPosition() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingCurrentPosition();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioMixingPosition(int pos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingPosition(pos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioMixingDualMonoMode(media::AUDIO_MIXING_DUAL_MONO_MODE mode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingDualMonoMode(mode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioMixingPitch(int pitch) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingPitch(pitch);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getEffectsVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getEffectsVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEffectsVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setEffectsVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::preloadEffect(int soundId, char const* filePath, int startPos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->preloadEffect(soundId, filePath, startPos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::playEffect(int soundId, char const* filePath, int loopCount, double pitch, double pan, int gain, bool publish, int startPos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->playEffect(soundId, filePath, loopCount, pitch, pan, gain, publish, startPos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::playAllEffects(int loopCount, double pitch, double pan, int gain, bool publish) {
				if (RtcEngine != nullptr) {
					return RtcEngine->playAllEffects(loopCount, pitch, pan, gain, publish);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getVolumeOfEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getVolumeOfEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVolumeOfEffect(int soundId, int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVolumeOfEffect(soundId, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unloadEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unloadEffect(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unloadAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->unloadAllEffects();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getEffectDuration(char const* filePath) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getEffectDuration(filePath);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEffectPosition(int soundId, int pos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setEffectPosition(soundId, pos);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getEffectCurrentPosition(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getEffectCurrentPosition(soundId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableSoundPositionIndication(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableSoundPositionIndication(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVoicePosition(agora::rtc::uid_t uid, double pan, double gain) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteVoicePosition(uid, pan, gain);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableSpatialAudio(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableSpatialAudio(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteUserSpatialAudioParams(agora::rtc::uid_t uid, agora::SpatialAudioParams const& params) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteUserSpatialAudioParams(uid, params);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceBeautifierPreset(agora::rtc::VOICE_BEAUTIFIER_PRESET preset) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceBeautifierPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioEffectPreset(agora::rtc::AUDIO_EFFECT_PRESET preset) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioEffectPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceConversionPreset(agora::rtc::VOICE_CONVERSION_PRESET preset) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceConversionPreset(preset);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAudioEffectParameters(agora::rtc::AUDIO_EFFECT_PRESET preset, int param1, int param2) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioEffectParameters(preset, param1, param2);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceBeautifierParameters(agora::rtc::VOICE_BEAUTIFIER_PRESET preset, int param1, int param2) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceBeautifierParameters(preset, param1, param2);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVoiceConversionParameters(agora::rtc::VOICE_CONVERSION_PRESET preset, int param1, int param2) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceConversionParameters(preset, param1, param2);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVoicePitch(double pitch) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoicePitch(pitch);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoiceEqualization(bandFrequency, bandGain);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoiceReverb(reverbKey, value);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogFile(char const* filePath) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogFile(filePath);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogFilter(unsigned int filter) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogFilter(filter);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogLevel(commons::LOG_LEVEL level) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogLevel(level);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLogFileSize(unsigned int fileSizeInKBytes) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogFileSize(fileSizeInKBytes);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::uploadLogFile(agora::util::AString& requestId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->uploadLogFile(requestId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalRenderMode(renderMode, mirrorMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteRenderMode(agora::rtc::uid_t uid, media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteRenderMode(uid, renderMode, mirrorMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalRenderMode(renderMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVideoMirrorMode(mirrorMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamMode(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableDualStreamMode(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamMode(bool enabled, const SimulcastStreamConfig& streamConfig)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableDualStreamMode(enabled, streamConfig);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDualStreamMode(agora::rtc::SIMULCAST_STREAM_MODE mode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDualStreamMode(mode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDualStreamMode(SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setDualStreamMode(mode, streamConfig);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEarMonitoringAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setEarMonitoringAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerExtension(const char* provider, const char* extension, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::UNKNOWN_MEDIA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->registerExtension(provider, extension, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableEchoCancellationExternal(bool enabled, int audioSourceDelay) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableEchoCancellationExternal(enabled, audioSourceDelay);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableCustomAudioLocalPlayback(int sourceId, bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableCustomAudioLocalPlayback(sourceId, enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPrimaryCustomAudioTrack(agora::rtc::AudioTrackConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPrimaryCustomAudioTrack(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPrimaryCustomAudioTrack() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPrimaryCustomAudioTrack();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startSecondaryCustomAudioTrack(agora::rtc::AudioTrackConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startSecondaryCustomAudioTrack(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopSecondaryCustomAudioTrack() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopSecondaryCustomAudioTrack();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRecordingAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setPlaybackAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableAudioSpectrumMonitor(int intervalInMS) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableAudioSpectrumMonitor(intervalInMS);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::disableAudioSpectrumMonitor() {
				if (RtcEngine != nullptr) {
					return RtcEngine->disableAudioSpectrumMonitor();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerAudioSpectrumObserver(observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unregisterAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unregisterAudioSpectrumObserver(observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustRecordingSignalVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustRecordingSignalVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRecordingSignal(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteRecordingSignal(mute);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustPlaybackSignalVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustPlaybackSignalVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustUserPlaybackSignalVolume(unsigned int uid, int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustUserPlaybackSignalVolume(uid, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalPublishFallbackOption(option);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteSubscribeFallbackOption(option);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLoopbackRecording(bool enabled, char const* deviceName) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableLoopbackRecording(enabled, deviceName);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustLoopbackSignalVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustLoopbackSignalVolume(volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getLoopbackRecordingVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getLoopbackRecordingVolume();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableInEarMonitoring(bool enabled, int includeAudioFilters) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableInEarMonitoring(enabled, includeAudioFilters);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setInEarMonitoringVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setInEarMonitoringVolume(volume);
				}
				return -ERROR_NULLPTR;
			}
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
			int RtcEngineProxy::loadExtensionProvider(char const* path, bool unload_after_use) {
				if (RtcEngine != nullptr) {
					return RtcEngine->loadExtensionProvider(path, unload_after_use);
				}
				return -ERROR_NULLPTR;
			}
#endif
			int RtcEngineProxy::setExtensionProviderProperty(char const* provider, char const* key, char const* value) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setExtensionProviderProperty(provider, key, value);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableExtension(char const* provider, char const* extension, bool enable, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableExtension(provider, extension, enable, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableExtension(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, bool enable /*= true*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableExtension(provider, extension, extensionInfo, enable);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setExtensionProperty(char const* provider, char const* extension, char const* key, char const* value, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setExtensionProperty(provider, extension, key, value, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setExtensionProperty(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, const char* key, const char* value)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setExtensionProperty(provider, extension, extensionInfo, key, key);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getExtensionProperty(char const* provider, char const* extension, char const* key, char* value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getExtensionProperty(provider, extension, key, value, buf_len, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getExtensionProperty(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, const char* key, char* value, int buf_len)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getExtensionProperty(provider, extension, extensionInfo, key, value, buf_len);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraCapturerConfiguration(agora::rtc::CameraCapturerConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraCapturerConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			agora::rtc::video_track_id_t RtcEngineProxy::createCustomVideoTrack() {
				if (RtcEngine != nullptr) {
					return RtcEngine->createCustomVideoTrack();
				}
				return 0;
			}

			agora::rtc::video_track_id_t RtcEngineProxy::createCustomEncodedVideoTrack(agora::rtc::SenderOptions const& sender_option) {
				if (RtcEngine != nullptr) {
					return RtcEngine->createCustomEncodedVideoTrack(sender_option);
				}
				return 0;
			}

			int RtcEngineProxy::destroyCustomVideoTrack(agora::rtc::video_track_id_t video_track_id) {
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyCustomVideoTrack(video_track_id);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::destroyCustomEncodedVideoTrack(agora::rtc::video_track_id_t video_track_id) {
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyCustomEncodedVideoTrack(video_track_id);
				}
				return -ERROR_NULLPTR;
			}
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
			int RtcEngineProxy::switchCamera() {
				if (RtcEngine != nullptr) {
					return RtcEngine->switchCamera();
				}
				return -ERROR_NULLPTR;
			}

			bool RtcEngineProxy::isCameraZoomSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraZoomSupported();
				}
				return true;
			}

			bool RtcEngineProxy::isCameraFaceDetectSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraFaceDetectSupported();
				}
				return true;
			}

			bool RtcEngineProxy::isCameraTorchSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraTorchSupported();
				}
				return true;
			}

			bool RtcEngineProxy::isCameraFocusSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraFocusSupported();
				}
				return true;
			}

			bool RtcEngineProxy::isCameraAutoFocusFaceModeSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraAutoFocusFaceModeSupported();
				}
				return true;
			}

			int RtcEngineProxy::setCameraZoomFactor(float factor) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraZoomFactor(factor);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableFaceDetection(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableFaceDetection(enabled);
				}
				return -ERROR_NULLPTR;
			}

			float RtcEngineProxy::getCameraMaxZoomFactor() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getCameraMaxZoomFactor();
				}
				return 0.0;
			}

			int RtcEngineProxy::setCameraFocusPositionInPreview(float positionX, float positionY) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraFocusPositionInPreview(positionX, positionY);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraTorchOn(bool isOn) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraTorchOn(isOn);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraAutoFocusFaceModeEnabled(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraAutoFocusFaceModeEnabled(enabled);
				}
				return -ERROR_NULLPTR;
			}

			bool RtcEngineProxy::isCameraExposurePositionSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraExposurePositionSupported();
				}
				return true;
			}

			int RtcEngineProxy::setCameraExposurePosition(float positionXinView, float positionYinView) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraExposurePosition(positionXinView, positionYinView);
				}
				return -ERROR_NULLPTR;
			}
#if defined(__APPLE__)
			bool RtcEngineProxy::isCameraAutoExposureFaceModeSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraAutoExposureFaceModeSupported();
				}
				return true;
			}

			int RtcEngineProxy::setCameraAutoExposureFaceModeEnabled(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraAutoExposureFaceModeEnabled(enabled);
				}
				return -ERROR_NULLPTR;
			}
#endif
			int RtcEngineProxy::setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEnableSpeakerphone(bool speakerOn) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setEnableSpeakerphone(speakerOn);
				}
				return -ERROR_NULLPTR;
			}

			bool RtcEngineProxy::isSpeakerphoneEnabled() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isSpeakerphoneEnabled();
				}
				return true;
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
			agora::rtc::IScreenCaptureSourceList* RtcEngineProxy::getScreenCaptureSources(SIZE const& thumbSize, SIZE const& iconSize, bool const includeScreen) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getScreenCaptureSources(thumbSize, iconSize, includeScreen);
				}
				return NULL;
			}
#endif
#if (defined(__APPLE__) && TARGET_OS_IOS)
			int RtcEngineProxy::setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioSessionOperationRestriction(restriction);
				}
				return -ERROR_NULLPTR;
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
			int RtcEngineProxy::startScreenCaptureByDisplayId(uint32_t displayId, Rectangle const& regionRect, ScreenCaptureParameters const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCaptureByDisplayId(displayId, regionRect, captureParams);
				}
				return -ERROR_NULLPTR;
			}
#if defined(_WIN32)
			int RtcEngineProxy::startScreenCaptureByScreenRect(const Rectangle& screenRect, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, captureParams);
				}
				return -ERROR_NULLPTR;
			}
#endif
#endif
#if defined(__ANDROID__)
			int RtcEngineProxy::getAudioDeviceInfo(agora::rtc::DeviceInfo& deviceInfo) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioDeviceInfo(deviceInfo);
				}
				return -ERROR_NULLPTR;
			}
#endif 
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
			int RtcEngineProxy::startScreenCaptureByWindowId(agora::view_t windowId, agora::rtc::Rectangle const& regionRect, agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCaptureByWindowId(windowId, regionRect, captureParams);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setScreenCaptureContentHint(agora::rtc::VIDEO_CONTENT_HINT contentHint) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setScreenCaptureContentHint(contentHint);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setScreenCaptureScenario(agora::rtc::SCREEN_SCENARIO_TYPE screenScenario) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setScreenCaptureScenario(screenScenario);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateScreenCaptureRegion(agora::rtc::Rectangle const& regionRect) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateScreenCaptureRegion(regionRect);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateScreenCaptureParameters(agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateScreenCaptureParameters(captureParams);
				}
				return -ERROR_NULLPTR;
			}
#endif 
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
			int RtcEngineProxy::startScreenCapture(agora::rtc::ScreenCaptureParameters2 const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCapture(captureParams);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateScreenCapture(agora::rtc::ScreenCaptureParameters2 const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateScreenCapture(captureParams);
				}
				return -ERROR_NULLPTR;
			}
#endif
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
			int RtcEngineProxy::stopScreenCapture() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopScreenCapture();
				}
				return -ERROR_NULLPTR;
			}
#endif
			int RtcEngineProxy::getCallId(agora::util::AString& callId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getCallId(callId);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::rate(char const* callId, int rating, char const* description) {
				if (RtcEngine != nullptr) {
					return RtcEngine->rate(callId, rating, description);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::complain(char const* callId, char const* description) {
				if (RtcEngine != nullptr) {
					return RtcEngine->complain(callId, description);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startRtmpStreamWithoutTranscoding(char const* url) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startRtmpStreamWithoutTranscoding(url);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startRtmpStreamWithTranscoding(char const* url, agora::rtc::LiveTranscoding const& transcoding) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startRtmpStreamWithTranscoding(url, transcoding);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateRtmpTranscoding(agora::rtc::LiveTranscoding const& transcoding) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateRtmpTranscoding(transcoding);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopRtmpStream(char const* url) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopRtmpStream(url);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startLocalVideoTranscoder(agora::rtc::LocalTranscoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startLocalVideoTranscoder(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateLocalTranscoderConfiguration(agora::rtc::LocalTranscoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateLocalTranscoderConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopLocalVideoTranscoder() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopLocalVideoTranscoder();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPrimaryCameraCapture(agora::rtc::CameraCapturerConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPrimaryCameraCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startSecondaryCameraCapture(agora::rtc::CameraCapturerConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startSecondaryCameraCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPrimaryCameraCapture() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPrimaryCameraCapture();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopSecondaryCameraCapture() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopSecondaryCameraCapture();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCameraDeviceOrientation(agora::rtc::VIDEO_SOURCE_TYPE type, agora::rtc::VIDEO_ORIENTATION orientation) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraDeviceOrientation(type, orientation);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setScreenCaptureOrientation(agora::rtc::VIDEO_SOURCE_TYPE type, agora::rtc::VIDEO_ORIENTATION orientation) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setScreenCaptureOrientation(type, orientation);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startPrimaryScreenCapture(agora::rtc::ScreenCaptureConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPrimaryScreenCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startSecondaryScreenCapture(agora::rtc::ScreenCaptureConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startSecondaryScreenCapture(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopPrimaryScreenCapture() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPrimaryScreenCapture();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopSecondaryScreenCapture() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopSecondaryScreenCapture();
				}
				return -ERROR_NULLPTR;
			}

			agora::rtc::CONNECTION_STATE_TYPE RtcEngineProxy::getConnectionState() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getConnectionState();
				}
				return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
			}

			bool RtcEngineProxy::registerEventHandler(agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerEventHandler(eventHandler);
				}
				return true;
			}

			bool RtcEngineProxy::unregisterEventHandler(agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unregisterEventHandler(eventHandler);
				}
				return true;
			}

			int RtcEngineProxy::setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteUserPriority(uid, userPriority);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerPacketObserver(agora::rtc::IPacketObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerPacketObserver(observer);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEncryptionMode(char const* encryptionMode) 
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setEncryptionMode(encryptionMode);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setEncryptionSecret(char const* secret)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setEncryptionSecret(secret);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableEncryption(bool enabled, agora::rtc::EncryptionConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableEncryption(enabled, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStream(int* streamId, bool reliable, bool ordered) {
				if (RtcEngine != nullptr) {
					return RtcEngine->createDataStream(streamId, reliable, ordered);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStream(int* streamId, agora::rtc::DataStreamConfig& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->createDataStream(streamId, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendStreamMessage(int streamId, char const* data, size_t length) {
				if (RtcEngine != nullptr) {
					return RtcEngine->sendStreamMessage(streamId, data, length);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addVideoWatermark(agora::rtc::RtcImage const& watermark) {
				if (RtcEngine != nullptr) {
					return RtcEngine->addVideoWatermark(watermark);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addVideoWatermark(char const* watermarkUrl, agora::rtc::WatermarkOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->addVideoWatermark(watermarkUrl, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::clearVideoWatermarks() {
				if (RtcEngine != nullptr) {
					return RtcEngine->clearVideoWatermarks();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAudio(){
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAudio();
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::resumeAudio(){
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAudio();
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::enableWebSdkInteroperability (bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableWebSdkInteroperability(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setAdvancedAudioOptions(AdvancedAudioOptions& options, int sourceType /*= 0*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAdvancedAudioOptions(options, sourceType);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::getNetworkType()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getNetworkType();
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::setParameters(const char* parameters)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setParameters(parameters);
				}
				return -ERROR_NULLPTR;
			}

			int64_t RtcEngineProxy::getCurrentMonotonicTimeInMs()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getCurrentMonotonicTimeInMs();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendCustomReportMessage(char const* id, char const* category, char const* event, char const* label, int value) {
				if (RtcEngine != nullptr) {
					return RtcEngine->sendCustomReportMessage(id, category, event, label, value);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerMediaMetadataObserver(agora::rtc::IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerMediaMetadataObserver(observer, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::unregisterMediaMetadataObserver(agora::rtc::IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unregisterMediaMetadataObserver(observer, type);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startAudioFrameDump(char const* channel_id, agora::rtc::uid_t user_id, char const* location, char const* uuid, char const* passwd, long duration_ms, bool auto_upload) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioFrameDump(channel_id, user_id, location, uuid, passwd, duration_ms, auto_upload);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopAudioFrameDump(char const* channel_id, agora::rtc::uid_t user_id, char const* location) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAudioFrameDump(channel_id, user_id, location);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::registerLocalUserAccount(char const* appId, char const* userAccount) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerLocalUserAccount(appId, userAccount);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelWithUserAccount(char const* token, char const* channelId, char const* userAccount) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannelWithUserAccount(token, channelId, userAccount);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelWithUserAccount(char const* token, char const* channelId, char const* userAccount, agora::rtc::ChannelMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannelWithUserAccount(token, channelId, userAccount, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelWithUserAccountEx(char const* token, char const* channelId, char const* userAccount, agora::rtc::ChannelMediaOptions const& options, agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannelWithUserAccountEx(token, channelId, userAccount, options, eventHandler);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUserAccount(char const* userAccount, rtc::UserInfo* userInfo) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getUserInfoByUserAccount(userAccount, userInfo);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUid(agora::rtc::uid_t uid, rtc::UserInfo* userInfo) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getUserInfoByUid(uid, userInfo);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startChannelMediaRelay(agora::rtc::ChannelMediaRelayConfiguration const& configuration) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startChannelMediaRelay(configuration);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaRelay(agora::rtc::ChannelMediaRelayConfiguration const& configuration) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateChannelMediaRelay(configuration);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopChannelMediaRelay() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopChannelMediaRelay();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAllChannelMediaRelay() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAllChannelMediaRelay();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAllChannelMediaRelay() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAllChannelMediaRelay();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDirectCdnStreamingAudioConfiguration(agora::rtc::AUDIO_PROFILE_TYPE profile) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDirectCdnStreamingAudioConfiguration(profile);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDirectCdnStreamingVideoConfiguration(agora::rtc::VideoEncoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDirectCdnStreamingVideoConfiguration(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startDirectCdnStreaming(agora::rtc::IDirectCdnStreamingEventHandler* eventHandler, char const* publishUrl, agora::rtc::DirectCdnStreamingMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startDirectCdnStreaming(eventHandler, publishUrl, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopDirectCdnStreaming() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopDirectCdnStreaming();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateDirectCdnStreamingMediaOptions(agora::rtc::DirectCdnStreamingMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateDirectCdnStreamingMediaOptions(options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startRhythmPlayer(char const* sound1, char const* sound2, agora::rtc::AgoraRhythmPlayerConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startRhythmPlayer(sound1, sound2, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopRhythmPlayer() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopRhythmPlayer();
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::configRhythmPlayer(agora::rtc::AgoraRhythmPlayerConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->configRhythmPlayer(config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::takeSnapshot(agora::rtc::uid_t uid, char const* filePath) {
				if (RtcEngine != nullptr) {
					return RtcEngine->takeSnapshot(uid, filePath);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableContentInspect(bool enabled, media::ContentInspectConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableContentInspect(enabled, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustCustomAudioPublishVolume(int32_t sourceId, int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustCustomAudioPublishVolume(sourceId, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustCustomAudioPlayoutVolume(int32_t sourceId, int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustCustomAudioPlayoutVolume(sourceId, volume);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setCloudProxy(agora::rtc::CLOUD_PROXY_TYPE proxyType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCloudProxy(proxyType);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setLocalAccessPoint(agora::rtc::LocalAccessPointConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalAccessPoint(config);
				}
				return -ERROR_NULLPTR;
			}


			int RtcEngineProxy::setAVSyncSource(char const* channelId, agora::rtc::uid_t uid) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAVSyncSource(channelId, uid);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableVideoImageSource(bool enable, agora::rtc::ImageTrackOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVideoImageSource(enable, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::joinChannelEx(char const* token, agora::rtc::RtcConnection const& connection, agora::rtc::ChannelMediaOptions const& options, agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->joinChannelEx(token, connection, options, eventHandler);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannelEx(agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->leaveChannelEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::leaveChannelEx(const RtcConnection& connection, const LeaveChannelOptions& options)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->leaveChannelEx(connection, options);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteLocalAudioStreamEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteLocalAudioStreamEx(mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteLocalVideoStreamEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteLocalVideoStreamEx(mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteAllRemoteAudioStreamsEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteAllRemoteAudioStreamsEx(mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteAllRemoteVideoStreamsEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteAllRemoteVideoStreamsEx(mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeAudioBlocklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeAudioBlocklistEx(uidList, uidNumber, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeAudioAllowlistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeAudioAllowlistEx(uidList, uidNumber, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeVideoBlocklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeVideoBlocklistEx(uidList, uidNumber, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setSubscribeVideoAllowlistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeVideoAllowlistEx(uidList, uidNumber, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::adjustUserPlaybackSignalVolumeEx(unsigned int uid, int volume, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->adjustUserPlaybackSignalVolumeEx(uid, volume, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startRtmpStreamWithoutTranscodingEx(const char* url, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startRtmpStreamWithoutTranscodingEx(url, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startRtmpStreamWithTranscodingEx(const char* url, const LiveTranscoding& transcoding, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startRtmpStreamWithTranscodingEx(url, transcoding, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateRtmpTranscodingEx(const LiveTranscoding& transcoding, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->updateRtmpTranscodingEx(transcoding, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopRtmpStreamEx(const char* url, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->stopRtmpStreamEx(url, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::startChannelMediaRelayEx(const ChannelMediaRelayConfiguration& configuration, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startChannelMediaRelayEx(configuration, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaRelayEx(const ChannelMediaRelayConfiguration& configuration, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->updateChannelMediaRelayEx(configuration, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::stopChannelMediaRelayEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->stopChannelMediaRelayEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::pauseAllChannelMediaRelayEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->stopChannelMediaRelayEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::resumeAllChannelMediaRelayEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->resumeAllChannelMediaRelayEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableDualStreamModeEx(bool enabled, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableDualStreamModeEx(enabled, streamConfig, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setDualStreamModeEx(SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setDualStreamModeEx(mode, streamConfig, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::updateChannelMediaOptionsEx(agora::rtc::ChannelMediaOptions const& options, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->updateChannelMediaOptionsEx(options, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoEncoderConfigurationEx(agora::rtc::VideoEncoderConfiguration const& config, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setVideoEncoderConfigurationEx(config, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setupRemoteVideoEx(agora::rtc::VideoCanvas const& canvas, agora::rtc::RtcConnection const& connection) {


				if (RtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						VideoRenderMgr->setRenderImage((UImage*)canvas.view, canvas.uid, connection.channelId, canvas.sourceType);
					}
					else {
						VideoRenderMgr->releaseVideoRender(canvas.uid, connection.channelId, canvas.sourceType);
					}
					return -ERROR_OK;
				}
				return -ERROR_NULLPTR;
			}
			int RtcEngineProxy::muteRemoteAudioStreamEx(agora::rtc::uid_t uid, bool mute, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteRemoteAudioStreamEx(uid, mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::muteRemoteVideoStreamEx(agora::rtc::uid_t uid, bool mute, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteRemoteVideoStreamEx(uid, mute, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoStreamTypeEx(agora::rtc::uid_t uid, agora::rtc::VIDEO_STREAM_TYPE streamType, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteVideoStreamTypeEx(uid, streamType, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVideoSubscriptionOptionsEx(agora::rtc::uid_t uid, agora::rtc::VideoSubscriptionOptions const& options, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteVideoSubscriptionOptionsEx(uid, options, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteVoicePositionEx(agora::rtc::uid_t uid, double pan, double gain, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteVoicePositionEx(uid, pan, gain, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteUserSpatialAudioParamsEx(agora::rtc::uid_t uid, agora::SpatialAudioParams const& params, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteUserSpatialAudioParamsEx(uid, params, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setRemoteRenderModeEx(agora::rtc::uid_t uid, media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteRenderModeEx(uid, renderMode, mirrorMode, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableLoopbackRecordingEx(agora::rtc::RtcConnection const& connection, bool enabled, char const* deviceName) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableLoopbackRecordingEx(connection, enabled, deviceName);
				}
				return -ERROR_NULLPTR;
			}

			agora::rtc::CONNECTION_STATE_TYPE RtcEngineProxy::getConnectionStateEx(agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getConnectionStateEx(connection);
				}
				return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
			}

			int RtcEngineProxy::enableEncryptionEx(agora::rtc::RtcConnection const& connection, bool enabled, agora::rtc::EncryptionConfig const& config) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableEncryptionEx(connection, enabled, config);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStreamEx(int* streamId, bool reliable, bool ordered, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->createDataStreamEx(streamId, reliable, ordered, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::createDataStreamEx(int* streamId, agora::rtc::DataStreamConfig& config, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->createDataStreamEx(streamId, config, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendStreamMessageEx(int streamId, char const* data, size_t length, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->sendStreamMessageEx(streamId, data, length, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::addVideoWatermarkEx(char const* watermarkUrl, agora::rtc::WatermarkOptions const& options, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->addVideoWatermarkEx(watermarkUrl, options, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::clearVideoWatermarkEx(agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->clearVideoWatermarkEx(connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::sendCustomReportMessageEx(char const* id, char const* category, char const* event, char const* label, int value, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->sendCustomReportMessageEx(id, category, event, label, value, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableAudioVolumeIndicationEx(interval, smooth, reportVad, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUserAccountEx(char const* userAccount, rtc::UserInfo* userInfo, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getUserInfoByUserAccountEx(userAccount, userInfo, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::getUserInfoByUidEx(agora::rtc::uid_t uid, rtc::UserInfo* userInfo, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getUserInfoByUidEx(uid, userInfo, connection);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::setVideoProfileEx(int width, int height, int frameRate, int bitrate) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setVideoProfileEx(width, height, frameRate, bitrate);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::enableWirelessAccelerate(bool enabled) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableWirelessAccelerate(enabled);
				}
				return -ERROR_NULLPTR;
			}

			int RtcEngineProxy::takeSnapshotEx(agora::rtc::RtcConnection const& connection, agora::rtc::uid_t uid, char const* filePath) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->takeSnapshotEx(connection, uid, filePath);
				}
				return -ERROR_NULLPTR;
			}
		}
	}
}


