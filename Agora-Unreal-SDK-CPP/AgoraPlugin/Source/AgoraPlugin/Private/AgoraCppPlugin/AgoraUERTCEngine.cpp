//  Copyright (c) 2024 Agora.io. All rights reserved.



#include "AgoraUERTCEngine.h"

#if AGORA_UESDK_ENABLE_VIDEO
#include "VideoFrameRenderManager.h"
#include "AgoraUEVideoFrameObserver.h"
using namespace agora::rtc::ue;
#endif

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJni.h"
#endif


#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#endif


#include <vector>


namespace agora {
	namespace rtc {
		namespace ue {

#pragma region Basics


			AgoraUERtcEngine* AgoraUERtcEngine::Instance = nullptr;
			std::mutex AgoraUERtcEngine::MutexLock;

			AgoraAppType AgoraUERtcEngine::RtcEngineAppType = AgoraAppType::kAppTypeUnreal;

			AgoraUERtcEngine* AgoraUERtcEngine::Get()
			{
				if (Instance == nullptr) {
					std::unique_lock<std::mutex> lock(MutexLock);
					if (Instance == nullptr) {
						Instance = new AgoraUERtcEngine();
						Instance->CreateEngine();
					}
				}

				return Instance;
			}


			agora::rtc::IRtcEngine* AgoraUERtcEngine::NativeRtcEnginePtr()
			{
				if (Instance != nullptr) {
					return Instance->RtcEngine;
				}
				
				return nullptr;
			}

			FString AgoraUERtcEngine::GetSDKVersion()
			{
				FString UEVersion = FString::Printf(TEXT("UE %d.%d.%d"), (ENGINE_MAJOR_VERSION), (ENGINE_MINOR_VERSION), (ENGINE_PATCH_VERSION));

				int SDKBuild = 0;
				const char* SDKVersionInfo = Get()->getVersion(&SDKBuild);
				FString SDKInfo = FString::Printf(TEXT("Agora SDK Version: %s Build: %d  UnrealVersion: %s"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild, *UEVersion);
				return SDKInfo;
			}


			void AgoraUERtcEngine::EnableIOSAudioSession(bool bEnable)
			{
#if PLATFORM_IOS
				[[IOSAppDelegate GetDelegate]SetFeature:EAudioFeature::Playback Active : bEnable];
				[[IOSAppDelegate GetDelegate]SetFeature:EAudioFeature::Record Active : bEnable];
				[[IOSAppDelegate GetDelegate]SetFeature:EAudioFeature::BackgroundAudio Active : bEnable];
#endif
			}

			void AgoraUERtcEngine::Release(bool sync /*= false*/)
			{
				if (Instance != nullptr) {
					std::unique_lock<std::mutex> lock(MutexLock);
					if (Instance != nullptr) {
						Instance->DestroyEngine(sync);
						delete Instance;
						Instance = nullptr;
					}
				}

			}

			void AgoraUERtcEngine::CreateEngine()
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

					//static jmethodID LoadAndroidScreenCaptureSo = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "LoadAndroidScreenCaptureSo", "()V", false);
					//if (LoadAndroidScreenCaptureSo != NULL)
					//{
					//	FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, LoadAndroidScreenCaptureSo);
					//}
				}
#endif		

				RtcEngine = ::createAgoraRtcEngine();

#if AGORA_UESDK_ENABLE_VIDEO
				_VideoFrameRenderManager = MakeShareable(new VideoFrameRenderManager());
#endif
			}


			void AgoraUERtcEngine::DestroyEngine(bool sync /*= false*/)
			{
				if (RtcEngine) {
					//RtcEngine->release(sync);
					agora::rtc::IRtcEngine::release(sync);
					RtcEngine = nullptr;
#if AGORA_UESDK_ENABLE_VIDEO
					_VideoFrameRenderManager = nullptr;
					_VideoObserver = nullptr;
#endif
				}
			}


			AgoraUERtcEngine::AgoraUERtcEngine() {}
			AgoraUERtcEngine::~AgoraUERtcEngine() {}


#pragma endregion Basics


#pragma region Agora API Wrapper


			int AgoraUERtcEngine::initialize(const agora::rtc::RtcEngineContext& context)
			{
				if (RtcEngine == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Agora RTC Engine initialize Failed, Engine Pointer is nullptr"));
					return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
				}

				int ret = RtcEngine->initialize(context);

				UE_LOG(LogTemp, Warning, TEXT("Agora RTC Engine initialize %d"), ret);
				if (ret == 0)
				{

					FString ParamType = FString::Printf(TEXT("{\"rtc.set_app_type\": %d}"), (int)RtcEngineAppType);
					agora::base::AParameter apm(RtcEngine);
					apm->setParameters(TCHAR_TO_UTF8(*ParamType));

#if AGORA_UESDK_ENABLE_VIDEO

#if PLATFORM_ANDROID

					// The following parameter is the same as "{\"rtc.enable_camera_capture_yuv\":\"true\"}"
					// These 2 parameters are used to capture YUV data directly.
					// Otherwise, the inconsistent rotation applied to video frame can lead to flickering in the displayed image.

					apm->setParameters("{\"che.video.android_camera_output_type\":0}");

#pragma region Load Android So

					int retSo = AgoraUERtcEngine::Get()->loadExtensionProvider("agora_screen_capture_extension");

					UE_LOG(LogTemp, Warning, TEXT("Initialize loadExtensionProvider [agora_screen_capture_extension] ret %d"), retSo);

#pragma endregion Load Android So

#endif
					// Our client can also use addVideoFrameRenderer to listen to VideoFrameObserver

					RtcEngine->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);
					_VideoObserver = MakeShareable(new AgoraUEVideoFrameObserver(nullptr));
					int retOb = MediaEngine->addVideoFrameRenderer(_VideoObserver.Get());
					UE_LOG(LogTemp, Warning, TEXT("Agora RTC Engine addVideoFrameRenderer %d"), retOb);
#endif



#if PLATFORM_IOS
					EnableIOSAudioSession(true);
#endif

				}
				return ret;
			}

			/*
				Note: Remote Channel would be ignore for now.
				Because Agora doesn't to join support multiple video channels.
			*/
			int AgoraUERtcEngine::setupRemoteVideo(const agora::rtc::VideoCanvas& canvas)
			{
#if AGORA_UESDK_ENABLE_VIDEO
				if (RtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						_VideoFrameRenderManager->AddOneRender((UImage*)canvas.view, canvas.sourceType, "", canvas.uid);
					}
					else {
						_VideoFrameRenderManager->ReleaseOneRender(canvas.sourceType, "", canvas.uid);
					}
					return AGORA_UE_ERR_CODE(ERROR_OK);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
#else
				return  AGORA_UE_ERR_CODE(ERROR_VIDEO_NOT_ENABLED);
#endif
			}


			int AgoraUERtcEngine::setupLocalVideo(const agora::rtc::VideoCanvas& canvas)
			{
#if AGORA_UESDK_ENABLE_VIDEO
				if (RtcEngine != nullptr) {
					if (canvas.view != nullptr) {
						_VideoFrameRenderManager->AddOneRender((UImage*)canvas.view, canvas.sourceType, "", canvas.uid);
					}
					else {
						_VideoFrameRenderManager->ReleaseOneRender(canvas.sourceType, "", canvas.uid);
					}
					return AGORA_UE_ERR_CODE(ERROR_OK);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
#else
				return  AGORA_UE_ERR_CODE(ERROR_VIDEO_NOT_ENABLED);
#endif
			}


			int AgoraUERtcEngine::setupRemoteVideoEx(const agora::rtc::VideoCanvas& canvas, const agora::rtc::RtcConnection& connection)
			{
#if AGORA_UESDK_ENABLE_VIDEO
				if (canvas.view != nullptr) {
					_VideoFrameRenderManager->AddOneRender((UImage*)canvas.view, canvas.sourceType, connection.channelId, canvas.uid);
				}
				else {
					_VideoFrameRenderManager->ReleaseOneRender(canvas.sourceType, connection.channelId, canvas.uid);
				}
				return  AGORA_UE_ERR_CODE(ERROR_OK);

#else
				return  AGORA_UE_ERR_CODE(ERROR_VIDEO_NOT_ENABLED);
#endif
			}

#pragma endregion Agora API Wrapper



#pragma region Other Native APIs

			int AgoraUERtcEngine::queryInterface(rtc::INTERFACE_ID_TYPE iid, void** inter)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->queryInterface(iid, inter);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			char const* AgoraUERtcEngine::getVersion(int* build) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getVersion(build);
				}
				return nullptr;
			}

			char const* AgoraUERtcEngine::getErrorDescription(int code) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getErrorDescription(code);
				}
				return nullptr;
			}


			int AgoraUERtcEngine::queryCodecCapability(CodecCapInfo* codecInfo, int& size)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->queryCodecCapability(codecInfo, size);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::queryDeviceScore()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->queryDeviceScore();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::preloadChannel(const char* token, const char* channelId, uid_t uid)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->preloadChannel(token, channelId, uid);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::preloadChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->preloadChannelWithUserAccount(token, channelId, userAccount);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::updatePreloadChannelToken(const char* token)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->updatePreloadChannelToken(token);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::joinChannel(char const* token, char const* channelId, char const* info, agora::rtc::uid_t uid) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannel(token, channelId, info, uid);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::joinChannel(char const* token, char const* channelId, agora::rtc::uid_t uid, agora::rtc::ChannelMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannel(token, channelId, uid, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateChannelMediaOptions(agora::rtc::ChannelMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateChannelMediaOptions(options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::leaveChannel() {
				if (RtcEngine != nullptr) {
					int ret = RtcEngine->leaveChannel();
					return ret;
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::leaveChannel(agora::rtc::LeaveChannelOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->leaveChannel(options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::renewToken(char const* token) {
				if (RtcEngine != nullptr) {
					return RtcEngine->renewToken(token);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setChannelProfile(agora::CHANNEL_PROFILE_TYPE profile) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setChannelProfile(profile);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setClientRole(role);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role, agora::rtc::ClientRoleOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setClientRole(role, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startEchoTest(agora::rtc::EchoTestConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startEchoTest(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopEchoTest() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopEchoTest();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


#if defined(__APPLE__) && TARGET_OS_IOS
			int AgoraUERtcEngine::enableMultiCamera(bool enabled, const CameraCapturerConfiguration& config)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableMultiCamera(enabled, config);
				}
				return  AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#endif

			int AgoraUERtcEngine::enableVideo() {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVideo();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::disableVideo() {
				if (RtcEngine != nullptr) {
					return RtcEngine->disableVideo();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startPreview() {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPreview();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startPreview(agora::rtc::VIDEO_SOURCE_TYPE sourceType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startPreview(sourceType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopPreview() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPreview();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopPreview(agora::rtc::VIDEO_SOURCE_TYPE sourceType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopPreview(sourceType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startLastmileProbeTest(agora::rtc::LastmileProbeConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startLastmileProbeTest(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopLastmileProbeTest() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopLastmileProbeTest();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVideoEncoderConfiguration(agora::rtc::VideoEncoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVideoEncoderConfiguration(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setBeautyEffectOptions(bool enabled, agora::rtc::BeautyOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setBeautyEffectOptions(enabled, options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setFaceShapeBeautyOptions(bool enabled, const FaceShapeBeautyOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setFaceShapeBeautyOptions(enabled, options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setFaceShapeAreaOptions(const FaceShapeAreaOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setFaceShapeAreaOptions(options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::getFaceShapeBeautyOptions(FaceShapeBeautyOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getFaceShapeBeautyOptions(options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::getFaceShapeAreaOptions(agora::rtc::FaceShapeAreaOptions::FACE_SHAPE_AREA shapeArea, FaceShapeAreaOptions& options, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::PRIMARY_CAMERA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getFaceShapeAreaOptions(shapeArea, options,type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLowlightEnhanceOptions(bool enabled, agora::rtc::LowlightEnhanceOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLowlightEnhanceOptions(enabled, options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVideoDenoiserOptions(bool enabled, agora::rtc::VideoDenoiserOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVideoDenoiserOptions(enabled, options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setColorEnhanceOptions(bool enabled, agora::rtc::ColorEnhanceOptions const& options, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setColorEnhanceOptions(enabled, options, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableVirtualBackground(bool enabled, agora::rtc::VirtualBackgroundSource backgroundSource, agora::rtc::SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVirtualBackground(enabled, backgroundSource, segproperty, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVideoScenario(VIDEO_APPLICATION_SCENARIO_TYPE scenarioType)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setVideoScenario(scenarioType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setVideoQoEPreference(VIDEO_QOE_PREFERENCE_TYPE qoePreference)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setVideoQoEPreference(qoePreference);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableAudio() {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableAudio();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::disableAudio() {
				if (RtcEngine != nullptr) {
					return RtcEngine->disableAudio();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioProfile(profile, scenario);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioProfile(AUDIO_PROFILE_TYPE profile)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioProfile(profile);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioScenario(agora::rtc::AUDIO_SCENARIO_TYPE scenario) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioScenario(scenario);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableLocalAudio(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableLocalAudio(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteLocalAudioStream(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteLocalAudioStream(mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteAllRemoteAudioStreams(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteAllRemoteAudioStreams(mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteRemoteAudioStream(agora::rtc::uid_t uid, bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteRemoteAudioStream(uid, mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteLocalVideoStream(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteLocalVideoStream(mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableLocalVideo(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableLocalVideo(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteAllRemoteVideoStreams(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteAllRemoteVideoStreams(mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteDefaultVideoStreamType(agora::rtc::VIDEO_STREAM_TYPE streamType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteDefaultVideoStreamType(streamType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setSubscribeAudioBlocklist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeAudioBlocklist(uidList, uidNumber);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeAudioAllowlist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeAudioAllowlist(uidList, uidNumber);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeVideoBlocklist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeVideoBlocklist(uidList, uidNumber);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeVideoAllowlist(uid_t* uidList, int uidNumber)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSubscribeVideoAllowlist(uidList, uidNumber);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteRemoteVideoStream(agora::rtc::uid_t uid, bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteRemoteVideoStream(uid, mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteVideoStreamType(agora::rtc::uid_t uid, agora::rtc::VIDEO_STREAM_TYPE streamType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteVideoStreamType(uid, streamType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteVideoSubscriptionOptions(agora::rtc::uid_t uid, agora::rtc::VideoSubscriptionOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteVideoSubscriptionOptions(uid, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableAudioVolumeIndication(int interval, int smooth, bool reportVad) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableAudioVolumeIndication(interval, smooth, reportVad);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startAudioRecording(char const* filePath, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioRecording(filePath, quality);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startAudioRecording(char const* filePath, int sampleRate, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioRecording(filePath, sampleRate, quality);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startAudioRecording(agora::rtc::AudioRecordingConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioRecording(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::registerAudioEncodedFrameObserver(agora::rtc::AudioEncodedFrameObserverConfig const& config, agora::rtc::IAudioEncodedFrameObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerAudioEncodedFrameObserver(config, observer);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopAudioRecording() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAudioRecording();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			agora_refptr<agora::rtc::IMediaPlayer> AgoraUERtcEngine::createMediaPlayer() {
				if (RtcEngine != nullptr) {
					return RtcEngine->createMediaPlayer();
				}
				return NULL;
			}

			int AgoraUERtcEngine::destroyMediaPlayer(agora_refptr<agora::rtc::IMediaPlayer> media_player) {
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyMediaPlayer(media_player);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			agora::agora_refptr<agora::rtc::IMediaRecorder> AgoraUERtcEngine::createMediaRecorder(const RecorderStreamInfo& info)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->createMediaRecorder(info);
				}
				return nullptr;
			}


			int AgoraUERtcEngine::destroyMediaRecorder(agora_refptr<IMediaRecorder> mediaRecorder)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyMediaRecorder(mediaRecorder);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startAudioMixing(char const* filePath, bool loopback, int cycle) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioMixing(filePath, loopback, cycle);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startAudioMixing(char const* filePath, bool loopback, int cycle, int startPos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioMixing(filePath, loopback, cycle, startPos);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopAudioMixing() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAudioMixing();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::pauseAudioMixing() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAudioMixing();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::resumeAudioMixing() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAudioMixing();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::selectAudioTrack(int index) {
				if (RtcEngine != nullptr) {
					return RtcEngine->selectAudioTrack(index);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getAudioTrackCount() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioTrackCount();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustAudioMixingVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustAudioMixingVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustAudioMixingPublishVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustAudioMixingPublishVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getAudioMixingPublishVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingPublishVolume();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustAudioMixingPlayoutVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustAudioMixingPlayoutVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getAudioMixingPlayoutVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingPlayoutVolume();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getAudioMixingDuration() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingDuration();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getAudioMixingCurrentPosition() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioMixingCurrentPosition();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioMixingPosition(int pos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingPosition(pos);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioMixingDualMonoMode(media::AUDIO_MIXING_DUAL_MONO_MODE mode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingDualMonoMode(mode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioMixingPitch(int pitch) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingPitch(pitch);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setAudioMixingPlaybackSpeed(int speed)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioMixingPlaybackSpeed(speed);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getEffectsVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getEffectsVolume();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setEffectsVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setEffectsVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::preloadEffect(int soundId, char const* filePath, int startPos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->preloadEffect(soundId, filePath, startPos);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::playEffect(int soundId, char const* filePath, int loopCount, double pitch, double pan, int gain, bool publish, int startPos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->playEffect(soundId, filePath, loopCount, pitch, pan, gain, publish, startPos);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::playAllEffects(int loopCount, double pitch, double pan, int gain, bool publish) {
				if (RtcEngine != nullptr) {
					return RtcEngine->playAllEffects(loopCount, pitch, pan, gain, publish);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getVolumeOfEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getVolumeOfEffect(soundId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVolumeOfEffect(int soundId, int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVolumeOfEffect(soundId, volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::pauseEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseEffect(soundId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::pauseAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAllEffects();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::resumeEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeEffect(soundId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::resumeAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAllEffects();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopEffect(soundId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAllEffects();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::unloadEffect(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unloadEffect(soundId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::unloadAllEffects() {
				if (RtcEngine != nullptr) {
					return RtcEngine->unloadAllEffects();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getEffectDuration(char const* filePath) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getEffectDuration(filePath);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setEffectPosition(int soundId, int pos) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setEffectPosition(soundId, pos);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getEffectCurrentPosition(int soundId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getEffectCurrentPosition(soundId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableSoundPositionIndication(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableSoundPositionIndication(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteVoicePosition(agora::rtc::uid_t uid, double pan, double gain) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteVoicePosition(uid, pan, gain);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableSpatialAudio(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableSpatialAudio(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteUserSpatialAudioParams(agora::rtc::uid_t uid, agora::SpatialAudioParams const& params) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteUserSpatialAudioParams(uid, params);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVoiceBeautifierPreset(agora::rtc::VOICE_BEAUTIFIER_PRESET preset) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceBeautifierPreset(preset);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioEffectPreset(agora::rtc::AUDIO_EFFECT_PRESET preset) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioEffectPreset(preset);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVoiceConversionPreset(agora::rtc::VOICE_CONVERSION_PRESET preset) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceConversionPreset(preset);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAudioEffectParameters(agora::rtc::AUDIO_EFFECT_PRESET preset, int param1, int param2) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioEffectParameters(preset, param1, param2);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVoiceBeautifierParameters(agora::rtc::VOICE_BEAUTIFIER_PRESET preset, int param1, int param2) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceBeautifierParameters(preset, param1, param2);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVoiceConversionParameters(agora::rtc::VOICE_CONVERSION_PRESET preset, int param1, int param2) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setVoiceConversionParameters(preset, param1, param2);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalVoicePitch(double pitch) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoicePitch(pitch);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setLocalVoiceFormant(double formantRatio)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoiceFormant(formantRatio);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoiceEqualization(bandFrequency, bandGain);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVoiceReverb(reverbKey, value);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setHeadphoneEQPreset(HEADPHONE_EQUALIZER_PRESET preset)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setHeadphoneEQPreset(preset);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setHeadphoneEQParameters(int lowGain, int highGain)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setHeadphoneEQParameters(lowGain, highGain);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::enableVoiceAITuner(bool enabled, VOICE_AI_TUNER_TYPE type)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVoiceAITuner(enabled, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLogFile(char const* filePath) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogFile(filePath);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLogFilter(unsigned int filter) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogFilter(filter);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLogLevel(commons::LOG_LEVEL level) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogLevel(level);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLogFileSize(unsigned int fileSizeInKBytes) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLogFileSize(fileSizeInKBytes);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::uploadLogFile(agora::util::AString& requestId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->uploadLogFile(requestId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::writeLog(commons::LOG_LEVEL level, const char* fmt, ...)
			{
				if (RtcEngine != nullptr) {


					va_list args;
					va_start(args, fmt);

					// to get the length
					int length = std::vsnprintf(nullptr, 0, fmt, args);
					va_end(args);

					std::vector<char> buffer(length + 1); // +1 for null terminator
					buffer.clear();

					va_start(args, fmt);
					std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
					va_end(args);

					std::string Content = (buffer.data());

					int result = RtcEngine->writeLog(level, Content.c_str());
					return result;
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalRenderMode(renderMode, mirrorMode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteRenderMode(agora::rtc::uid_t uid, media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteRenderMode(uid, renderMode, mirrorMode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalRenderMode(media::base::RENDER_MODE_TYPE renderMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalRenderMode(renderMode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalVideoMirrorMode(mirrorMode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableDualStreamMode(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableDualStreamMode(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableDualStreamMode(bool enabled, const SimulcastStreamConfig& streamConfig)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableDualStreamMode(enabled, streamConfig);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setDualStreamMode(agora::rtc::SIMULCAST_STREAM_MODE mode) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDualStreamMode(mode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setSimulcastConfig(const SimulcastConfig& simulcastConfig)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setSimulcastConfig(simulcastConfig);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setDualStreamMode(SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setDualStreamMode(mode, streamConfig);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setEarMonitoringAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setEarMonitoringAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::registerExtension(const char* provider, const char* extension, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::UNKNOWN_MEDIA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->registerExtension(provider, extension, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::enableCustomAudioLocalPlayback(track_id_t trackId, bool enabled)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableCustomAudioLocalPlayback(trackId, enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRecordingAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setPlaybackAudioFrameParameters(int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableAudioSpectrumMonitor(int intervalInMS) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableAudioSpectrumMonitor(intervalInMS);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::disableAudioSpectrumMonitor() {
				if (RtcEngine != nullptr) {
					return RtcEngine->disableAudioSpectrumMonitor();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::registerAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerAudioSpectrumObserver(observer);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::unregisterAudioSpectrumObserver(agora::media::IAudioSpectrumObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unregisterAudioSpectrumObserver(observer);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustRecordingSignalVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustRecordingSignalVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteRecordingSignal(bool mute) {
				if (RtcEngine != nullptr) {
					return RtcEngine->muteRecordingSignal(mute);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustPlaybackSignalVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustPlaybackSignalVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustUserPlaybackSignalVolume(uid_t uid, int volume)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustUserPlaybackSignalVolume(uid, volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalPublishFallbackOption(option);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteSubscribeFallbackOption(option);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setHighPriorityUserList(uid_t* uidList, int uidNum, STREAM_FALLBACK_OPTIONS option)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setHighPriorityUserList(uidList, uidNum, option);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableLoopbackRecording(bool enabled, char const* deviceName) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableLoopbackRecording(enabled, deviceName);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustLoopbackSignalVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustLoopbackSignalVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getLoopbackRecordingVolume() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getLoopbackRecordingVolume();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableInEarMonitoring(bool enabled, int includeAudioFilters) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableInEarMonitoring(enabled, includeAudioFilters);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setInEarMonitoringVolume(int volume) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setInEarMonitoringVolume(volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
			int AgoraUERtcEngine::loadExtensionProvider(char const* path, bool unload_after_use) {
				if (RtcEngine != nullptr) {
					return RtcEngine->loadExtensionProvider(path, unload_after_use);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#endif
			int AgoraUERtcEngine::setExtensionProviderProperty(char const* provider, char const* key, char const* value) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setExtensionProviderProperty(provider, key, value);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableExtension(char const* provider, char const* extension, bool enable, agora::media::MEDIA_SOURCE_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableExtension(provider, extension, enable, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableExtension(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, bool enable /*= true*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableExtension(provider, extension, extensionInfo, enable);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}



			int AgoraUERtcEngine::setExtensionProperty(const char* provider, const char* extension, const char* key, const char* value, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::UNKNOWN_MEDIA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setExtensionProperty(provider, extension, key, value, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setExtensionProperty(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, const char* key, const char* value)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setExtensionProperty(provider, extension, extensionInfo, key, value);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getExtensionProperty(const char* provider, const char* extension, const ExtensionInfo& extensionInfo, const char* key, char* value, int buf_len)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getExtensionProperty(provider, extension, extensionInfo, key, value, buf_len);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::getExtensionProperty(const char* provider, const char* extension, const char* key, char* value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type /*= agora::media::UNKNOWN_MEDIA_SOURCE*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getExtensionProperty(provider, extension, key, value, buf_len, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setCameraCapturerConfiguration(agora::rtc::CameraCapturerConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraCapturerConfiguration(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			agora::rtc::video_track_id_t AgoraUERtcEngine::createCustomVideoTrack() {
				if (RtcEngine != nullptr) {
					return RtcEngine->createCustomVideoTrack();
				}
				return 0;
			}

			agora::rtc::video_track_id_t AgoraUERtcEngine::createCustomEncodedVideoTrack(agora::rtc::SenderOptions const& sender_option) {
				if (RtcEngine != nullptr) {
					return RtcEngine->createCustomEncodedVideoTrack(sender_option);
				}
				return 0;
			}

			int AgoraUERtcEngine::destroyCustomVideoTrack(agora::rtc::video_track_id_t video_track_id) {
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyCustomVideoTrack(video_track_id);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::destroyCustomEncodedVideoTrack(agora::rtc::video_track_id_t video_track_id) {
				if (RtcEngine != nullptr) {
					return RtcEngine->destroyCustomEncodedVideoTrack(video_track_id);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
			int AgoraUERtcEngine::switchCamera() {
				if (RtcEngine != nullptr) {
					return RtcEngine->switchCamera();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			bool AgoraUERtcEngine::isCameraZoomSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraZoomSupported();
				}
				return true;
			}

			bool AgoraUERtcEngine::isCameraFaceDetectSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraFaceDetectSupported();
				}
				return true;
			}

			bool AgoraUERtcEngine::isCameraTorchSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraTorchSupported();
				}
				return true;
			}

			bool AgoraUERtcEngine::isCameraFocusSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraFocusSupported();
				}
				return true;
			}

			bool AgoraUERtcEngine::isCameraAutoFocusFaceModeSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraAutoFocusFaceModeSupported();
				}
				return true;
			}

			int AgoraUERtcEngine::setCameraZoomFactor(float factor) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraZoomFactor(factor);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableFaceDetection(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableFaceDetection(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			float AgoraUERtcEngine::getCameraMaxZoomFactor() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getCameraMaxZoomFactor();
				}
				return 0.0;
			}

			int AgoraUERtcEngine::setCameraFocusPositionInPreview(float positionX, float positionY) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraFocusPositionInPreview(positionX, positionY);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setCameraTorchOn(bool isOn) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraTorchOn(isOn);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setCameraAutoFocusFaceModeEnabled(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraAutoFocusFaceModeEnabled(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			bool AgoraUERtcEngine::isCameraExposurePositionSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraExposurePositionSupported();
				}
				return true;
			}

			int AgoraUERtcEngine::setCameraExposurePosition(float positionXinView, float positionYinView) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraExposurePosition(positionXinView, positionYinView);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			bool AgoraUERtcEngine::isCameraExposureSupported()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraExposureSupported();
				}
				return true;
			}


			int AgoraUERtcEngine::setCameraExposureFactor(float factor)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraExposureFactor(factor);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

#if defined(__APPLE__)
			bool AgoraUERtcEngine::isCameraAutoExposureFaceModeSupported() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraAutoExposureFaceModeSupported();
				}
				return true;
			}

			int AgoraUERtcEngine::setCameraAutoExposureFaceModeEnabled(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraAutoExposureFaceModeEnabled(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setCameraStabilizationMode(CAMERA_STABILIZATION_MODE mode)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraStabilizationMode(mode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

#endif
			int AgoraUERtcEngine::setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setEnableSpeakerphone(bool speakerOn) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setEnableSpeakerphone(speakerOn);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			bool AgoraUERtcEngine::isSpeakerphoneEnabled() {
				if (RtcEngine != nullptr) {
					return RtcEngine->isSpeakerphoneEnabled();
				}
				return true;
			}

			int AgoraUERtcEngine::setRouteInCommunicationMode(int route)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setRouteInCommunicationMode(route);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}



#endif

#if defined(__APPLE__)

			bool AgoraUERtcEngine::isCameraCenterStageSupported()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->isCameraCenterStageSupported();
				}
				return true;
			}


			int AgoraUERtcEngine::enableCameraCenterStage(bool enabled)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->enableCameraCenterStage(enabled);
				}
				return  AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
			agora::rtc::IScreenCaptureSourceList* AgoraUERtcEngine::getScreenCaptureSources(SIZE const& thumbSize, SIZE const& iconSize, bool const includeScreen) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getScreenCaptureSources(thumbSize, iconSize, includeScreen);
				}
				return NULL;
			}
#endif
#if (defined(__APPLE__) && TARGET_OS_IOS)
			int AgoraUERtcEngine::setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAudioSessionOperationRestriction(restriction);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#endif
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
			int AgoraUERtcEngine::startScreenCaptureByDisplayId(uint32_t displayId, Rectangle const& regionRect, ScreenCaptureParameters const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCaptureByDisplayId(displayId, regionRect, captureParams);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#if defined(_WIN32)
			int AgoraUERtcEngine::startScreenCaptureByScreenRect(const Rectangle& screenRect, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, captureParams);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#endif
#endif
#if defined(__ANDROID__)
			int AgoraUERtcEngine::getAudioDeviceInfo(agora::rtc::DeviceInfo& deviceInfo) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getAudioDeviceInfo(deviceInfo);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#endif 
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
			int AgoraUERtcEngine::startScreenCaptureByWindowId(agora::view_t windowId, agora::rtc::Rectangle const& regionRect, agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCaptureByWindowId(windowId, regionRect, captureParams);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setScreenCaptureContentHint(agora::rtc::VIDEO_CONTENT_HINT contentHint) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setScreenCaptureContentHint(contentHint);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateScreenCaptureRegion(agora::rtc::Rectangle const& regionRect) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateScreenCaptureRegion(regionRect);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateScreenCaptureParameters(agora::rtc::ScreenCaptureParameters const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateScreenCaptureParameters(captureParams);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#endif 
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
			int AgoraUERtcEngine::startScreenCapture(agora::rtc::ScreenCaptureParameters2 const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCapture(captureParams);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateScreenCapture(agora::rtc::ScreenCaptureParameters2 const& captureParams) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateScreenCapture(captureParams);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::queryScreenCaptureCapability()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->queryScreenCaptureCapability();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}



			int AgoraUERtcEngine::queryCameraFocalLengthCapability(agora::rtc::FocalLengthInfo* focalLengthInfos, int& size)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->queryCameraFocalLengthCapability(focalLengthInfos, size);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

#endif
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)


			int AgoraUERtcEngine::setScreenCaptureScenario(SCREEN_SCENARIO_TYPE screenScenario)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setScreenCaptureScenario(screenScenario);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}



			int AgoraUERtcEngine::stopScreenCapture() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopScreenCapture();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startScreenCapture(VIDEO_SOURCE_TYPE sourceType, const ScreenCaptureConfiguration& config)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->startScreenCapture(sourceType, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopScreenCapture(VIDEO_SOURCE_TYPE sourceType)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->stopScreenCapture(sourceType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

#endif
			int AgoraUERtcEngine::getCallId(agora::util::AString& callId) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getCallId(callId);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::rate(char const* callId, int rating, char const* description) {
				if (RtcEngine != nullptr) {
					return RtcEngine->rate(callId, rating, description);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::complain(char const* callId, char const* description) {
				if (RtcEngine != nullptr) {
					return RtcEngine->complain(callId, description);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startRtmpStreamWithoutTranscoding(char const* url) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startRtmpStreamWithoutTranscoding(url);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startRtmpStreamWithTranscoding(char const* url, agora::rtc::LiveTranscoding const& transcoding) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startRtmpStreamWithTranscoding(url, transcoding);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateRtmpTranscoding(agora::rtc::LiveTranscoding const& transcoding) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateRtmpTranscoding(transcoding);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopRtmpStream(char const* url) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopRtmpStream(url);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startLocalVideoTranscoder(agora::rtc::LocalTranscoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startLocalVideoTranscoder(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateLocalTranscoderConfiguration(agora::rtc::LocalTranscoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateLocalTranscoderConfiguration(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopLocalVideoTranscoder() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopLocalVideoTranscoder();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::startCameraCapture(VIDEO_SOURCE_TYPE sourceType, const CameraCapturerConfiguration& config)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->startCameraCapture(sourceType, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::stopCameraCapture(VIDEO_SOURCE_TYPE sourceType)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->stopCameraCapture(sourceType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setCameraDeviceOrientation(agora::rtc::VIDEO_SOURCE_TYPE type, agora::rtc::VIDEO_ORIENTATION orientation) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCameraDeviceOrientation(type, orientation);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setScreenCaptureOrientation(agora::rtc::VIDEO_SOURCE_TYPE type, agora::rtc::VIDEO_ORIENTATION orientation) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setScreenCaptureOrientation(type, orientation);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			agora::rtc::CONNECTION_STATE_TYPE AgoraUERtcEngine::getConnectionState() {
				if (RtcEngine != nullptr) {
					return RtcEngine->getConnectionState();
				}
				return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
			}

			bool AgoraUERtcEngine::registerEventHandler(agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerEventHandler(eventHandler);
				}
				return true;
			}

			bool AgoraUERtcEngine::unregisterEventHandler(agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unregisterEventHandler(eventHandler);
				}
				return true;
			}

			int AgoraUERtcEngine::setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setRemoteUserPriority(uid, userPriority);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::registerPacketObserver(agora::rtc::IPacketObserver* observer) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerPacketObserver(observer);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableEncryption(bool enabled, agora::rtc::EncryptionConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableEncryption(enabled, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::createDataStream(int* streamId, bool reliable, bool ordered) {
				if (RtcEngine != nullptr) {
					return RtcEngine->createDataStream(streamId, reliable, ordered);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::createDataStream(int* streamId, const agora::rtc::DataStreamConfig& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->createDataStream(streamId, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::sendStreamMessage(int streamId, char const* data, size_t length) {
				if (RtcEngine != nullptr) {
					return RtcEngine->sendStreamMessage(streamId, data, length);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::addVideoWatermark(agora::rtc::RtcImage const& watermark) {
				if (RtcEngine != nullptr) {
					return RtcEngine->addVideoWatermark(watermark);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::addVideoWatermark(char const* watermarkUrl, agora::rtc::WatermarkOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->addVideoWatermark(watermarkUrl, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::clearVideoWatermarks() {
				if (RtcEngine != nullptr) {
					return RtcEngine->clearVideoWatermarks();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::pauseAudio() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAudio();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::resumeAudio() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAudio();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::enableWebSdkInteroperability(bool enabled) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableWebSdkInteroperability(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setAdvancedAudioOptions(AdvancedAudioOptions& options, int sourceType /*= 0*/)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAdvancedAudioOptions(options, sourceType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int64_t AgoraUERtcEngine::getCurrentMonotonicTimeInMs()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getCurrentMonotonicTimeInMs();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
			int AgoraUERtcEngine::enableWirelessAccelerate(bool enabled) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableWirelessAccelerate(enabled);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getNetworkType()
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->getNetworkType();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setParameters(const char* parameters)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setParameters(parameters);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::startMediaRenderingTracing()
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startMediaRenderingTracing();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::enableInstantMediaRendering()
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableInstantMediaRendering();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			uint64_t AgoraUERtcEngine::getNtpWallTimeInMs()
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getNtpWallTimeInMs();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			bool AgoraUERtcEngine::isFeatureAvailableOnDevice(FeatureType type)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->isFeatureAvailableOnDevice(type);
				}
				return true;
			}


			int AgoraUERtcEngine::sendAudioMetadata(const char* metadata, size_t length)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->sendAudioMetadata(metadata, length);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::sendCustomReportMessage(char const* id, char const* category, char const* event, char const* label, int value) {
				if (RtcEngine != nullptr) {
					return RtcEngine->sendCustomReportMessage(id, category, event, label, value);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::registerMediaMetadataObserver(agora::rtc::IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerMediaMetadataObserver(observer, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::unregisterMediaMetadataObserver(agora::rtc::IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type) {
				if (RtcEngine != nullptr) {
					return RtcEngine->unregisterMediaMetadataObserver(observer, type);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startAudioFrameDump(char const* channel_id, agora::rtc::uid_t user_id, char const* location, char const* uuid, char const* passwd, long duration_ms, bool auto_upload) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startAudioFrameDump(channel_id, user_id, location, uuid, passwd, duration_ms, auto_upload);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopAudioFrameDump(char const* channel_id, agora::rtc::uid_t user_id, char const* location) {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopAudioFrameDump(channel_id, user_id, location);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setAINSMode(bool enabled, AUDIO_AINS_MODE mode)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->setAINSMode(enabled, mode);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::registerLocalUserAccount(char const* appId, char const* userAccount) {
				if (RtcEngine != nullptr) {
					return RtcEngine->registerLocalUserAccount(appId, userAccount);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::joinChannelWithUserAccount(char const* token, char const* channelId, char const* userAccount) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannelWithUserAccount(token, channelId, userAccount);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::joinChannelWithUserAccount(char const* token, char const* channelId, char const* userAccount, agora::rtc::ChannelMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannelWithUserAccount(token, channelId, userAccount, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::joinChannelWithUserAccountEx(char const* token, char const* channelId, char const* userAccount, agora::rtc::ChannelMediaOptions const& options, agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return RtcEngine->joinChannelWithUserAccountEx(token, channelId, userAccount, options, eventHandler);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getUserInfoByUserAccount(char const* userAccount, rtc::UserInfo* userInfo) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getUserInfoByUserAccount(userAccount, userInfo);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getUserInfoByUid(agora::rtc::uid_t uid, rtc::UserInfo* userInfo) {
				if (RtcEngine != nullptr) {
					return RtcEngine->getUserInfoByUid(uid, userInfo);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::startOrUpdateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->startOrUpdateChannelMediaRelay(configuration);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopChannelMediaRelay() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopChannelMediaRelay();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::pauseAllChannelMediaRelay() {
				if (RtcEngine != nullptr) {
					return RtcEngine->pauseAllChannelMediaRelay();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::resumeAllChannelMediaRelay() {
				if (RtcEngine != nullptr) {
					return RtcEngine->resumeAllChannelMediaRelay();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setDirectCdnStreamingAudioConfiguration(agora::rtc::AUDIO_PROFILE_TYPE profile) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDirectCdnStreamingAudioConfiguration(profile);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setDirectCdnStreamingVideoConfiguration(agora::rtc::VideoEncoderConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setDirectCdnStreamingVideoConfiguration(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startDirectCdnStreaming(agora::rtc::IDirectCdnStreamingEventHandler* eventHandler, char const* publishUrl, agora::rtc::DirectCdnStreamingMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startDirectCdnStreaming(eventHandler, publishUrl, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopDirectCdnStreaming() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopDirectCdnStreaming();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateDirectCdnStreamingMediaOptions(agora::rtc::DirectCdnStreamingMediaOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->updateDirectCdnStreamingMediaOptions(options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startRhythmPlayer(char const* sound1, char const* sound2, agora::rtc::AgoraRhythmPlayerConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->startRhythmPlayer(sound1, sound2, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopRhythmPlayer() {
				if (RtcEngine != nullptr) {
					return RtcEngine->stopRhythmPlayer();
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::configRhythmPlayer(agora::rtc::AgoraRhythmPlayerConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->configRhythmPlayer(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::takeSnapshot(agora::rtc::uid_t uid, char const* filePath) {
				if (RtcEngine != nullptr) {
					return RtcEngine->takeSnapshot(uid, filePath);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableContentInspect(bool enabled, media::ContentInspectConfig const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableContentInspect(enabled, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustCustomAudioPublishVolume(track_id_t trackId, int volume)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustCustomAudioPublishVolume(trackId, volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::adjustCustomAudioPlayoutVolume(track_id_t trackId, int volume)
			{
				if (RtcEngine != nullptr) {
					return RtcEngine->adjustCustomAudioPlayoutVolume(trackId, volume);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setCloudProxy(agora::rtc::CLOUD_PROXY_TYPE proxyType) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setCloudProxy(proxyType);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setLocalAccessPoint(agora::rtc::LocalAccessPointConfiguration const& config) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setLocalAccessPoint(config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setAVSyncSource(char const* channelId, agora::rtc::uid_t uid) {
				if (RtcEngine != nullptr) {
					return RtcEngine->setAVSyncSource(channelId, uid);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableVideoImageSource(bool enable, agora::rtc::ImageTrackOptions const& options) {
				if (RtcEngine != nullptr) {
					return RtcEngine->enableVideoImageSource(enable, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::joinChannelEx(char const* token, agora::rtc::RtcConnection const& connection, agora::rtc::ChannelMediaOptions const& options, agora::rtc::IRtcEngineEventHandler* eventHandler) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->joinChannelEx(token, connection, options, eventHandler);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::leaveChannelEx(agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->leaveChannelEx(connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::leaveChannelEx(const RtcConnection& connection, const LeaveChannelOptions& options)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->leaveChannelEx(connection, options);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteLocalAudioStreamEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteLocalAudioStreamEx(mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteLocalVideoStreamEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteLocalVideoStreamEx(mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteAllRemoteAudioStreamsEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteAllRemoteAudioStreamsEx(mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteAllRemoteVideoStreamsEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteAllRemoteVideoStreamsEx(mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeAudioBlocklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeAudioBlocklistEx(uidList, uidNumber, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeAudioAllowlistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeAudioAllowlistEx(uidList, uidNumber, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeVideoBlocklistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeVideoBlocklistEx(uidList, uidNumber, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setSubscribeVideoAllowlistEx(uid_t* uidList, int uidNumber, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSubscribeVideoAllowlistEx(uidList, uidNumber, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::adjustUserPlaybackSignalVolumeEx(uid_t uid, int volume, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->adjustUserPlaybackSignalVolumeEx(uid, volume, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startRtmpStreamWithoutTranscodingEx(const char* url, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startRtmpStreamWithoutTranscodingEx(url, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startRtmpStreamWithTranscodingEx(const char* url, const LiveTranscoding& transcoding, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startRtmpStreamWithTranscodingEx(url, transcoding, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateRtmpTranscodingEx(const LiveTranscoding& transcoding, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->updateRtmpTranscodingEx(transcoding, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopRtmpStreamEx(const char* url, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->stopRtmpStreamEx(url, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::startOrUpdateChannelMediaRelayEx(const ChannelMediaRelayConfiguration& configuration, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startOrUpdateChannelMediaRelayEx(configuration, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::stopChannelMediaRelayEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->stopChannelMediaRelayEx(connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::pauseAllChannelMediaRelayEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->stopChannelMediaRelayEx(connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::resumeAllChannelMediaRelayEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->resumeAllChannelMediaRelayEx(connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableDualStreamModeEx(bool enabled, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableDualStreamModeEx(enabled, streamConfig, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setDualStreamModeEx(SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig& streamConfig, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setDualStreamModeEx(mode, streamConfig, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setSimulcastConfigEx(const SimulcastConfig& simulcastConfig, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setSimulcastConfigEx(simulcastConfig, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);

			}


			int AgoraUERtcEngine::setHighPriorityUserListEx(uid_t* uidList, int uidNum, STREAM_FALLBACK_OPTIONS option, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setHighPriorityUserListEx(uidList, uidNum, option, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::updateChannelMediaOptionsEx(agora::rtc::ChannelMediaOptions const& options, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->updateChannelMediaOptionsEx(options, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setVideoEncoderConfigurationEx(agora::rtc::VideoEncoderConfiguration const& config, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setVideoEncoderConfigurationEx(config, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteRemoteAudioStreamEx(agora::rtc::uid_t uid, bool mute, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteRemoteAudioStreamEx(uid, mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::muteRemoteVideoStreamEx(agora::rtc::uid_t uid, bool mute, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteRemoteVideoStreamEx(uid, mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteVideoStreamTypeEx(agora::rtc::uid_t uid, agora::rtc::VIDEO_STREAM_TYPE streamType, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteVideoStreamTypeEx(uid, streamType, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteVideoSubscriptionOptionsEx(agora::rtc::uid_t uid, agora::rtc::VideoSubscriptionOptions const& options, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteVideoSubscriptionOptionsEx(uid, options, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteVoicePositionEx(agora::rtc::uid_t uid, double pan, double gain, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteVoicePositionEx(uid, pan, gain, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteUserSpatialAudioParamsEx(agora::rtc::uid_t uid, agora::SpatialAudioParams const& params, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteUserSpatialAudioParamsEx(uid, params, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::setRemoteRenderModeEx(agora::rtc::uid_t uid, media::base::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setRemoteRenderModeEx(uid, renderMode, mirrorMode, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableLoopbackRecordingEx(agora::rtc::RtcConnection const& connection, bool enabled, char const* deviceName) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableLoopbackRecordingEx(connection, enabled, deviceName);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::adjustRecordingSignalVolumeEx(int volume, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->adjustRecordingSignalVolumeEx(volume, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::muteRecordingSignalEx(bool mute, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->muteRecordingSignalEx(mute, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			agora::rtc::CONNECTION_STATE_TYPE AgoraUERtcEngine::getConnectionStateEx(agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getConnectionStateEx(connection);
				}
				return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
			}

			int AgoraUERtcEngine::enableEncryptionEx(agora::rtc::RtcConnection const& connection, bool enabled, agora::rtc::EncryptionConfig const& config) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableEncryptionEx(connection, enabled, config);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::createDataStreamEx(int* streamId, bool reliable, bool ordered, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->createDataStreamEx(streamId, reliable, ordered, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::createDataStreamEx(int* streamId, const agora::rtc::DataStreamConfig& config, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->createDataStreamEx(streamId, config, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::sendStreamMessageEx(int streamId, char const* data, size_t length, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->sendStreamMessageEx(streamId, data, length, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::addVideoWatermarkEx(char const* watermarkUrl, agora::rtc::WatermarkOptions const& options, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->addVideoWatermarkEx(watermarkUrl, options, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::clearVideoWatermarkEx(agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->clearVideoWatermarkEx(connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::sendCustomReportMessageEx(char const* id, char const* category, char const* event, char const* label, int value, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->sendCustomReportMessageEx(id, category, event, label, value, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::enableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableAudioVolumeIndicationEx(interval, smooth, reportVad, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getUserInfoByUserAccountEx(char const* userAccount, rtc::UserInfo* userInfo, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getUserInfoByUserAccountEx(userAccount, userInfo, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::getUserInfoByUidEx(agora::rtc::uid_t uid, rtc::UserInfo* userInfo, agora::rtc::RtcConnection const& connection) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getUserInfoByUidEx(uid, userInfo, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::takeSnapshotEx(agora::rtc::RtcConnection const& connection, agora::rtc::uid_t uid, char const* filePath) {
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->takeSnapshotEx(connection, uid, filePath);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::enableContentInspectEx(bool enabled, const media::ContentInspectConfig& config, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->enableContentInspectEx(enabled, config, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}

			int AgoraUERtcEngine::startMediaRenderingTracingEx(const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->startMediaRenderingTracingEx(connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::setParametersEx(const RtcConnection& connection, const char* parameters)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->setParametersEx(connection, parameters);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::getCallIdEx(agora::util::AString& callId, const RtcConnection& connection)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->getCallIdEx(callId, connection);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}


			int AgoraUERtcEngine::sendAudioMetadataEx(const RtcConnection& connection, const char* metadata, size_t length)
			{
				if (RtcEngine != nullptr) {
					return ((IRtcEngineEx*)RtcEngine)->sendAudioMetadataEx(connection, metadata, length);
				}
				return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
			}
#pragma endregion Other Native APIs
		}
	}
}

