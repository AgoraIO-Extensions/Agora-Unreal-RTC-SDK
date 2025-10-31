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
					AgoraUERtcEngine::Get()->setAudioScenario(agora::rtc::AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING);
					int ret00 = AgoraUERtcEngine::Get()->setParameters("{\"che.audio.keep.audiosession\": true}");
					UE_LOG(LogTemp, Warning, TEXT("Agora RTC Engine Keep Audio Session ret %d"), ret00);
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

#pragma endregion Agora API Wrapper

#pragma region Other Native APIs



                int AgoraUERtcEngine::queryInterface (INTERFACE_ID_TYPE iid, void ** inter)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->queryInterface(iid, inter);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                char const* AgoraUERtcEngine::getVersion (int * build)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getVersion(build);
                        return ret;
                    }
                    return nullptr;
                }




                char const* AgoraUERtcEngine::getErrorDescription (int code)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getErrorDescription(code);
                        return ret;
                    }
                    return nullptr;
                }




                int AgoraUERtcEngine::queryCodecCapability (CodecCapInfo * codecInfo, int & size)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->queryCodecCapability(codecInfo, size);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::queryDeviceScore ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->queryDeviceScore();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::preloadChannel (const char * token, const char * channelId, uid_t uid)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->preloadChannel(token, channelId, uid);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::preloadChannelWithUserAccount (const char * token, const char * channelId, const char * userAccount)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->preloadChannelWithUserAccount(token, channelId, userAccount);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updatePreloadChannelToken (const char * token)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updatePreloadChannelToken(token);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::joinChannel (const char * token, const char * channelId, const char * info, uid_t uid)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->joinChannel(token, channelId, info, uid);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::joinChannel (const char * token, const char * channelId, uid_t uid, const ChannelMediaOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->joinChannel(token, channelId, uid, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateChannelMediaOptions (const ChannelMediaOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateChannelMediaOptions(options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::leaveChannel ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->leaveChannel();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::leaveChannel (const LeaveChannelOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->leaveChannel(options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::renewToken (const char * token)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->renewToken(token);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setChannelProfile (CHANNEL_PROFILE_TYPE profile)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setChannelProfile(profile);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setClientRole (CLIENT_ROLE_TYPE role)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setClientRole(role);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setClientRole (CLIENT_ROLE_TYPE role, const ClientRoleOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setClientRole(role, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startEchoTest (const EchoTestConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startEchoTest(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopEchoTest ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopEchoTest();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }



#if defined(__APPLE__) && TARGET_OS_IOS
                int AgoraUERtcEngine::enableMultiCamera (bool enabled, const CameraCapturerConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableMultiCamera(enabled, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif



                int AgoraUERtcEngine::enableVideo ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableVideo();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::disableVideo ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->disableVideo();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startPreview ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startPreview();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startPreview (VIDEO_SOURCE_TYPE sourceType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startPreview(sourceType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopPreview ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopPreview();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopPreview (VIDEO_SOURCE_TYPE sourceType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopPreview(sourceType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startLastmileProbeTest (const LastmileProbeConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startLastmileProbeTest(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopLastmileProbeTest ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopLastmileProbeTest();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVideoEncoderConfiguration (const VideoEncoderConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVideoEncoderConfiguration(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setBeautyEffectOptions (bool enabled, const BeautyOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setBeautyEffectOptions(enabled, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setFaceShapeBeautyOptions (bool enabled, const FaceShapeBeautyOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setFaceShapeBeautyOptions(enabled, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setFaceShapeAreaOptions (const FaceShapeAreaOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setFaceShapeAreaOptions(options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getFaceShapeBeautyOptions (FaceShapeBeautyOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getFaceShapeBeautyOptions(options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getFaceShapeAreaOptions (agora::rtc::FaceShapeAreaOptions::FACE_SHAPE_AREA shapeArea, FaceShapeAreaOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getFaceShapeAreaOptions(shapeArea, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setFilterEffectOptions (bool enabled, const FilterEffectOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setFilterEffectOptions(enabled, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLowlightEnhanceOptions (bool enabled, const LowlightEnhanceOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLowlightEnhanceOptions(enabled, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVideoDenoiserOptions (bool enabled, const VideoDenoiserOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVideoDenoiserOptions(enabled, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setColorEnhanceOptions (bool enabled, const ColorEnhanceOptions & options, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setColorEnhanceOptions(enabled, options, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableVirtualBackground (bool enabled, VirtualBackgroundSource backgroundSource, SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::PRIMARY_CAMERA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableVirtualBackground(enabled, backgroundSource, segproperty, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVideoScenario (VIDEO_APPLICATION_SCENARIO_TYPE scenarioType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVideoScenario(scenarioType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVideoQoEPreference (VIDEO_QOE_PREFERENCE_TYPE qoePreference)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVideoQoEPreference(qoePreference);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableAudio ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableAudio();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::disableAudio ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->disableAudio();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioProfile (AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioProfile(profile, scenario);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioProfile (AUDIO_PROFILE_TYPE profile)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioProfile(profile);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioScenario (AUDIO_SCENARIO_TYPE scenario)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioScenario(scenario);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableLocalAudio (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableLocalAudio(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteLocalAudioStream (bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteLocalAudioStream(mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteAllRemoteAudioStreams (bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteAllRemoteAudioStreams(mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteRemoteAudioStream (uid_t uid, bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteRemoteAudioStream(uid, mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteLocalVideoStream (bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteLocalVideoStream(mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableLocalVideo (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableLocalVideo(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteAllRemoteVideoStreams (bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteAllRemoteVideoStreams(mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteDefaultVideoStreamType (VIDEO_STREAM_TYPE streamType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteDefaultVideoStreamType(streamType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteRemoteVideoStream (uid_t uid, bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteRemoteVideoStream(uid, mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteVideoStreamType (uid_t uid, VIDEO_STREAM_TYPE streamType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteVideoStreamType(uid, streamType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteVideoSubscriptionOptions (uid_t uid, const VideoSubscriptionOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteVideoSubscriptionOptions(uid, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeAudioBlocklist (uid_t * uidList, int uidNumber)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setSubscribeAudioBlocklist(uidList, uidNumber);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeAudioAllowlist (uid_t * uidList, int uidNumber)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setSubscribeAudioAllowlist(uidList, uidNumber);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeVideoBlocklist (uid_t * uidList, int uidNumber)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setSubscribeVideoBlocklist(uidList, uidNumber);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeVideoAllowlist (uid_t * uidList, int uidNumber)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setSubscribeVideoAllowlist(uidList, uidNumber);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableAudioVolumeIndication (int interval, int smooth, bool reportVad)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableAudioVolumeIndication(interval, smooth, reportVad);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startAudioRecording (const char * filePath, AUDIO_RECORDING_QUALITY_TYPE quality)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startAudioRecording(filePath, quality);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startAudioRecording (const char * filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startAudioRecording(filePath, sampleRate, quality);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startAudioRecording (const AudioRecordingConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startAudioRecording(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::registerAudioEncodedFrameObserver (const AudioEncodedFrameObserverConfig & config, IAudioEncodedFrameObserver * observer)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerAudioEncodedFrameObserver(config, observer);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopAudioRecording ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopAudioRecording();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                agora_refptr<agora::rtc::IMediaPlayer> AgoraUERtcEngine::createMediaPlayer ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->createMediaPlayer();
                        return ret;
                    }
                    return nullptr;
                }




                int AgoraUERtcEngine::destroyMediaPlayer (agora_refptr<IMediaPlayer> media_player)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->destroyMediaPlayer(media_player);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                agora_refptr<agora::rtc::IMediaRecorder> AgoraUERtcEngine::createMediaRecorder (const RecorderStreamInfo & info)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->createMediaRecorder(info);
                        return ret;
                    }
                    return nullptr;
                }




                int AgoraUERtcEngine::destroyMediaRecorder (agora_refptr<IMediaRecorder> mediaRecorder)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->destroyMediaRecorder(mediaRecorder);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startAudioMixing (const char * filePath, bool loopback, int cycle)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startAudioMixing(filePath, loopback, cycle);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startAudioMixing (const char * filePath, bool loopback, int cycle, int startPos)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startAudioMixing(filePath, loopback, cycle, startPos);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopAudioMixing ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopAudioMixing();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::pauseAudioMixing ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->pauseAudioMixing();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::resumeAudioMixing ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->resumeAudioMixing();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::selectAudioTrack (int index)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->selectAudioTrack(index);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getAudioTrackCount ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getAudioTrackCount();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustAudioMixingVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustAudioMixingVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustAudioMixingPublishVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustAudioMixingPublishVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getAudioMixingPublishVolume ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getAudioMixingPublishVolume();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustAudioMixingPlayoutVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustAudioMixingPlayoutVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getAudioMixingPlayoutVolume ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getAudioMixingPlayoutVolume();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getAudioMixingDuration ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getAudioMixingDuration();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getAudioMixingCurrentPosition ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getAudioMixingCurrentPosition();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioMixingPosition (int pos)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioMixingPosition(pos);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioMixingDualMonoMode (media::AUDIO_MIXING_DUAL_MONO_MODE mode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioMixingDualMonoMode(mode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioMixingPitch (int pitch)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioMixingPitch(pitch);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioMixingPlaybackSpeed (int speed)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioMixingPlaybackSpeed(speed);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getEffectsVolume ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getEffectsVolume();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setEffectsVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setEffectsVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::preloadEffect (int soundId, const char * filePath, int startPos /* 0 */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->preloadEffect(soundId, filePath, startPos);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::playEffect (int soundId, const char * filePath, int loopCount, double pitch, double pan, int gain, bool publish /* false */ , int startPos /* 0 */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->playEffect(soundId, filePath, loopCount, pitch, pan, gain, publish, startPos);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::playAllEffects (int loopCount, double pitch, double pan, int gain, bool publish /* false */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->playAllEffects(loopCount, pitch, pan, gain, publish);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getVolumeOfEffect (int soundId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getVolumeOfEffect(soundId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVolumeOfEffect (int soundId, int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVolumeOfEffect(soundId, volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::pauseEffect (int soundId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->pauseEffect(soundId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::pauseAllEffects ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->pauseAllEffects();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::resumeEffect (int soundId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->resumeEffect(soundId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::resumeAllEffects ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->resumeAllEffects();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopEffect (int soundId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopEffect(soundId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopAllEffects ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopAllEffects();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::unloadEffect (int soundId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->unloadEffect(soundId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::unloadAllEffects ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->unloadAllEffects();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getEffectDuration (const char * filePath)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getEffectDuration(filePath);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setEffectPosition (int soundId, int pos)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setEffectPosition(soundId, pos);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getEffectCurrentPosition (int soundId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getEffectCurrentPosition(soundId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableSoundPositionIndication (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableSoundPositionIndication(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteVoicePosition (uid_t uid, double pan, double gain)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteVoicePosition(uid, pan, gain);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableSpatialAudio (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableSpatialAudio(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteUserSpatialAudioParams (uid_t uid, const agora::SpatialAudioParams & params)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteUserSpatialAudioParams(uid, params);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVoiceBeautifierPreset (VOICE_BEAUTIFIER_PRESET preset)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVoiceBeautifierPreset(preset);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioEffectPreset (AUDIO_EFFECT_PRESET preset)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioEffectPreset(preset);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVoiceConversionPreset (VOICE_CONVERSION_PRESET preset)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVoiceConversionPreset(preset);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAudioEffectParameters (AUDIO_EFFECT_PRESET preset, int param1, int param2)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioEffectParameters(preset, param1, param2);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVoiceBeautifierParameters (VOICE_BEAUTIFIER_PRESET preset, int param1, int param2)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVoiceBeautifierParameters(preset, param1, param2);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVoiceConversionParameters (VOICE_CONVERSION_PRESET preset, int param1, int param2)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setVoiceConversionParameters(preset, param1, param2);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalVoicePitch (double pitch)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalVoicePitch(pitch);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalVoiceFormant (double formantRatio)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalVoiceFormant(formantRatio);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalVoiceEqualization (AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalVoiceEqualization(bandFrequency, bandGain);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalVoiceReverb (AUDIO_REVERB_TYPE reverbKey, int value)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalVoiceReverb(reverbKey, value);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setHeadphoneEQPreset (HEADPHONE_EQUALIZER_PRESET preset)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setHeadphoneEQPreset(preset);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setHeadphoneEQParameters (int lowGain, int highGain)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setHeadphoneEQParameters(lowGain, highGain);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableVoiceAITuner (bool enabled, VOICE_AI_TUNER_TYPE type)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableVoiceAITuner(enabled, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLogFile (const char * filePath)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLogFile(filePath);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLogFilter (unsigned int filter)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLogFilter(filter);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLogLevel (commons::LOG_LEVEL level)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLogLevel(level);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLogFileSize (unsigned int fileSizeInKBytes)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLogFileSize(fileSizeInKBytes);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::uploadLogFile (agora::util::AString & requestId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->uploadLogFile(requestId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalRenderMode (media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalRenderMode(renderMode, mirrorMode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteRenderMode (uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteRenderMode(uid, renderMode, mirrorMode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalRenderTargetFps (VIDEO_SOURCE_TYPE sourceType, int targetFps)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalRenderTargetFps(sourceType, targetFps);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteRenderTargetFps (int targetFps)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteRenderTargetFps(targetFps);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalRenderMode (media::base::RENDER_MODE_TYPE renderMode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalRenderMode(renderMode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalVideoMirrorMode (VIDEO_MIRROR_MODE_TYPE mirrorMode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalVideoMirrorMode(mirrorMode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableDualStreamMode (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableDualStreamMode(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableDualStreamMode (bool enabled, const SimulcastStreamConfig & streamConfig)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableDualStreamMode(enabled, streamConfig);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setDualStreamMode (SIMULCAST_STREAM_MODE mode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setDualStreamMode(mode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSimulcastConfig (const SimulcastConfig & simulcastConfig)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setSimulcastConfig(simulcastConfig);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setDualStreamMode (SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig & streamConfig)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setDualStreamMode(mode, streamConfig);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableCustomAudioLocalPlayback (track_id_t trackId, bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableCustomAudioLocalPlayback(trackId, enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRecordingAudioFrameParameters (int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setPlaybackAudioFrameParameters (int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setMixedAudioFrameParameters (int sampleRate, int channel, int samplesPerCall)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setEarMonitoringAudioFrameParameters (int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setEarMonitoringAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setPlaybackAudioFrameBeforeMixingParameters (int sampleRate, int channel)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableAudioSpectrumMonitor (int intervalInMS /* 100 */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableAudioSpectrumMonitor(intervalInMS);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::disableAudioSpectrumMonitor ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->disableAudioSpectrumMonitor();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::registerAudioSpectrumObserver (agora::media::IAudioSpectrumObserver * observer)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerAudioSpectrumObserver(observer);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::unregisterAudioSpectrumObserver (agora::media::IAudioSpectrumObserver * observer)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->unregisterAudioSpectrumObserver(observer);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustRecordingSignalVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustRecordingSignalVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteRecordingSignal (bool mute)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->muteRecordingSignal(mute);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustPlaybackSignalVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustPlaybackSignalVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustUserPlaybackSignalVolume (uid_t uid, int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustUserPlaybackSignalVolume(uid, volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalPublishFallbackOption (STREAM_FALLBACK_OPTIONS option)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalPublishFallbackOption(option);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteSubscribeFallbackOption (STREAM_FALLBACK_OPTIONS option)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteSubscribeFallbackOption(option);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setHighPriorityUserList (uid_t * uidList, int uidNum, STREAM_FALLBACK_OPTIONS option)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setHighPriorityUserList(uidList, uidNum, option);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableExtension (const char * provider, const char * extension, const ExtensionInfo & extensionInfo, bool enable /* true */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableExtension(provider, extension, extensionInfo, enable);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setExtensionProperty (const char * provider, const char * extension, const ExtensionInfo & extensionInfo, const char * key, const char * value)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setExtensionProperty(provider, extension, extensionInfo, key, value);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getExtensionProperty (const char * provider, const char * extension, const ExtensionInfo & extensionInfo, const char * key, char * value, int buf_len)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getExtensionProperty(provider, extension, extensionInfo, key, value, buf_len);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableLoopbackRecording (bool enabled, const char * deviceName /* nullptr */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableLoopbackRecording(enabled, deviceName);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustLoopbackSignalVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustLoopbackSignalVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getLoopbackRecordingVolume ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getLoopbackRecordingVolume();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableInEarMonitoring (bool enabled, int includeAudioFilters)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableInEarMonitoring(enabled, includeAudioFilters);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setInEarMonitoringVolume (int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setInEarMonitoringVolume(volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }



#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
                int AgoraUERtcEngine::loadExtensionProvider (const char * path, bool unload_after_use /* false */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->loadExtensionProvider(path, unload_after_use);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif



                int AgoraUERtcEngine::setExtensionProviderProperty (const char * provider, const char * key, const char * value)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setExtensionProviderProperty(provider, key, value);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::registerExtension (const char * provider, const char * extension, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::UNKNOWN_MEDIA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerExtension(provider, extension, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableExtension (const char * provider, const char * extension, bool enable /* true */ , agora::media::MEDIA_SOURCE_TYPE type /* agora::media::UNKNOWN_MEDIA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableExtension(provider, extension, enable, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setExtensionProperty (const char * provider, const char * extension, const char * key, const char * value, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::UNKNOWN_MEDIA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setExtensionProperty(provider, extension, key, value, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getExtensionProperty (const char * provider, const char * extension, const char * key, char * value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type /* agora::media::UNKNOWN_MEDIA_SOURCE */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getExtensionProperty(provider, extension, key, value, buf_len, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setCameraCapturerConfiguration (const CameraCapturerConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraCapturerConfiguration(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                agora::rtc::video_track_id_t AgoraUERtcEngine::createCustomVideoTrack ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->createCustomVideoTrack();
                        return ret;
                    }
                    return 0;
                }




                agora::rtc::video_track_id_t AgoraUERtcEngine::createCustomEncodedVideoTrack (const SenderOptions & sender_option)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->createCustomEncodedVideoTrack(sender_option);
                        return ret;
                    }
                    return 0;
                }




                int AgoraUERtcEngine::destroyCustomVideoTrack (video_track_id_t video_track_id)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->destroyCustomVideoTrack(video_track_id);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::destroyCustomEncodedVideoTrack (video_track_id_t video_track_id)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->destroyCustomEncodedVideoTrack(video_track_id);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }



#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::switchCamera ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->switchCamera();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraZoomSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraZoomSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraFaceDetectSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraFaceDetectSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraTorchSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraTorchSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraFocusSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraFocusSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraAutoFocusFaceModeSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraAutoFocusFaceModeSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setCameraZoomFactor (float factor)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraZoomFactor(factor);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::enableFaceDetection (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableFaceDetection(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                float AgoraUERtcEngine::getCameraMaxZoomFactor ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getCameraMaxZoomFactor();
                        return ret;
                    }
                    return 0.0f;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setCameraFocusPositionInPreview (float positionX, float positionY)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraFocusPositionInPreview(positionX, positionY);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setCameraTorchOn (bool isOn)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraTorchOn(isOn);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setCameraAutoFocusFaceModeEnabled (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraAutoFocusFaceModeEnabled(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraExposurePositionSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraExposurePositionSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setCameraExposurePosition (float positionXinView, float positionYinView)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraExposurePosition(positionXinView, positionYinView);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isCameraExposureSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraExposureSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setCameraExposureFactor (float factor)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraExposureFactor(factor);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
                bool AgoraUERtcEngine::isCameraAutoExposureFaceModeSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraAutoExposureFaceModeSupported();
                        return ret;
                    }
                    return false;
                }

#endif
#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
                int AgoraUERtcEngine::setCameraAutoExposureFaceModeEnabled (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraAutoExposureFaceModeEnabled(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif
#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
                int AgoraUERtcEngine::setCameraStabilizationMode (CAMERA_STABILIZATION_MODE mode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraStabilizationMode(mode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif
#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setDefaultAudioRouteToSpeakerphone (bool defaultToSpeaker)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setEnableSpeakerphone (bool speakerOn)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setEnableSpeakerphone(speakerOn);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                bool AgoraUERtcEngine::isSpeakerphoneEnabled ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isSpeakerphoneEnabled();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setRouteInCommunicationMode (int route)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRouteInCommunicationMode(route);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__APPLE__)
                bool AgoraUERtcEngine::isCameraCenterStageSupported ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isCameraCenterStageSupported();
                        return ret;
                    }
                    return false;
                }

#endif


#if defined(__APPLE__)
                int AgoraUERtcEngine::enableCameraCenterStage (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableCameraCenterStage(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
                agora::rtc::IScreenCaptureSourceList* AgoraUERtcEngine::getScreenCaptureSources (const SIZE & thumbSize, const SIZE & iconSize, const bool includeScreen)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getScreenCaptureSources(thumbSize, iconSize, includeScreen);
                        return ret;
                    }
                    return nullptr;
                }

#endif


#if (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::setAudioSessionOperationRestriction (AUDIO_SESSION_OPERATION_RESTRICTION restriction)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAudioSessionOperationRestriction(restriction);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
                int AgoraUERtcEngine::startScreenCaptureByDisplayId (int64_t displayId, const Rectangle & regionRect, const ScreenCaptureParameters & captureParams)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startScreenCaptureByDisplayId(displayId, regionRect, captureParams);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32)
                int AgoraUERtcEngine::startScreenCaptureByScreenRect (const Rectangle & screenRect, const Rectangle & regionRect, const ScreenCaptureParameters & captureParams)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, captureParams);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__)
                int AgoraUERtcEngine::getAudioDeviceInfo (DeviceInfo & deviceInfo)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getAudioDeviceInfo(deviceInfo);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
                int AgoraUERtcEngine::startScreenCaptureByWindowId (int64_t windowId, const Rectangle & regionRect, const ScreenCaptureParameters & captureParams)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startScreenCaptureByWindowId(windowId, regionRect, captureParams);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
                int AgoraUERtcEngine::setScreenCaptureContentHint (VIDEO_CONTENT_HINT contentHint)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setScreenCaptureContentHint(contentHint);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
                int AgoraUERtcEngine::updateScreenCaptureRegion (const Rectangle & regionRect)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateScreenCaptureRegion(regionRect);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
                int AgoraUERtcEngine::updateScreenCaptureParameters (const ScreenCaptureParameters & captureParams)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateScreenCaptureParameters(captureParams);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::startScreenCapture (const ScreenCaptureParameters2 & captureParams)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startScreenCapture(captureParams);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::updateScreenCapture (const ScreenCaptureParameters2 & captureParams)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateScreenCapture(captureParams);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::queryScreenCaptureCapability ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->queryScreenCaptureCapability();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
                int AgoraUERtcEngine::queryCameraFocalLengthCapability (agora::rtc::FocalLengthInfo * focalLengthInfos, int & size)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->queryCameraFocalLengthCapability(focalLengthInfos, size);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__ANDROID__)
                int AgoraUERtcEngine::setExternalMediaProjection (void * mediaProjection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setExternalMediaProjection(mediaProjection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif
#endif


#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
                int AgoraUERtcEngine::setScreenCaptureScenario (SCREEN_SCENARIO_TYPE screenScenario)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setScreenCaptureScenario(screenScenario);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif


#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
                int AgoraUERtcEngine::stopScreenCapture ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopScreenCapture();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }

#endif



                int AgoraUERtcEngine::getCallId (agora::util::AString & callId)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getCallId(callId);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::rate (const char * callId, int rating, const char * description)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->rate(callId, rating, description);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::complain (const char * callId, const char * description)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->complain(callId, description);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startRtmpStreamWithoutTranscoding (const char * url)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startRtmpStreamWithoutTranscoding(url);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startRtmpStreamWithTranscoding (const char * url, const LiveTranscoding & transcoding)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startRtmpStreamWithTranscoding(url, transcoding);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateRtmpTranscoding (const LiveTranscoding & transcoding)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateRtmpTranscoding(transcoding);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startLocalVideoTranscoder (const LocalTranscoderConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startLocalVideoTranscoder(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateLocalTranscoderConfiguration (const LocalTranscoderConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateLocalTranscoderConfiguration(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopRtmpStream (const char * url)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopRtmpStream(url);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopLocalVideoTranscoder ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopLocalVideoTranscoder();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startLocalAudioMixer (const LocalAudioMixerConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startLocalAudioMixer(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateLocalAudioMixerConfiguration (const LocalAudioMixerConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateLocalAudioMixerConfiguration(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopLocalAudioMixer ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopLocalAudioMixer();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startCameraCapture (VIDEO_SOURCE_TYPE sourceType, const CameraCapturerConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startCameraCapture(sourceType, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopCameraCapture (VIDEO_SOURCE_TYPE sourceType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopCameraCapture(sourceType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setCameraDeviceOrientation (VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCameraDeviceOrientation(type, orientation);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setScreenCaptureOrientation (VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setScreenCaptureOrientation(type, orientation);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startScreenCapture (VIDEO_SOURCE_TYPE sourceType, const ScreenCaptureConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startScreenCapture(sourceType, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopScreenCapture (VIDEO_SOURCE_TYPE sourceType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopScreenCapture(sourceType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                agora::rtc::CONNECTION_STATE_TYPE AgoraUERtcEngine::getConnectionState ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getConnectionState();
                        return ret;
                    }
                    return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
                }




                bool AgoraUERtcEngine::registerEventHandler (IRtcEngineEventHandler * eventHandler)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerEventHandler(eventHandler);
                        return ret;
                    }
                    return false;
                }




                bool AgoraUERtcEngine::unregisterEventHandler (IRtcEngineEventHandler * eventHandler)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->unregisterEventHandler(eventHandler);
                        return ret;
                    }
                    return false;
                }




                int AgoraUERtcEngine::setRemoteUserPriority (uid_t uid, PRIORITY_TYPE userPriority)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setRemoteUserPriority(uid, userPriority);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::registerPacketObserver (IPacketObserver * observer)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerPacketObserver(observer);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableEncryption (bool enabled, const EncryptionConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableEncryption(enabled, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::createDataStream (int * streamId, bool reliable, bool ordered)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->createDataStream(streamId, reliable, ordered);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::createDataStream (int * streamId, const DataStreamConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->createDataStream(streamId, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::sendStreamMessage (int streamId, const char * data, size_t length)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->sendStreamMessage(streamId, data, length);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::addVideoWatermark (const RtcImage & watermark)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->addVideoWatermark(watermark);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::addVideoWatermark (const char * watermarkUrl, const WatermarkOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->addVideoWatermark(watermarkUrl, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::clearVideoWatermarks ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->clearVideoWatermarks();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::pauseAudio ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->pauseAudio();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::resumeAudio ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->resumeAudio();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableWebSdkInteroperability (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableWebSdkInteroperability(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::sendCustomReportMessage (const char * id, const char * category, const char * event, const char * label, int value)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->sendCustomReportMessage(id, category, event, label, value);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::registerMediaMetadataObserver (IMetadataObserver * observer, IMetadataObserver::METADATA_TYPE type)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerMediaMetadataObserver(observer, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::unregisterMediaMetadataObserver (IMetadataObserver * observer, IMetadataObserver::METADATA_TYPE type)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->unregisterMediaMetadataObserver(observer, type);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startAudioFrameDump (const char * channel_id, uid_t uid, const char * location, const char * uuid, const char * passwd, long duration_ms, bool auto_upload)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startAudioFrameDump(channel_id, uid, location, uuid, passwd, duration_ms, auto_upload);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopAudioFrameDump (const char * channel_id, uid_t uid, const char * location)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopAudioFrameDump(channel_id, uid, location);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAINSMode (bool enabled, AUDIO_AINS_MODE mode)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAINSMode(enabled, mode);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::registerLocalUserAccount (const char * appId, const char * userAccount)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->registerLocalUserAccount(appId, userAccount);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::joinChannelWithUserAccount (const char * token, const char * channelId, const char * userAccount)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->joinChannelWithUserAccount(token, channelId, userAccount);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::joinChannelWithUserAccount (const char * token, const char * channelId, const char * userAccount, const ChannelMediaOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->joinChannelWithUserAccount(token, channelId, userAccount, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::joinChannelWithUserAccountEx (const char * token, const char * channelId, const char * userAccount, const ChannelMediaOptions & options, IRtcEngineEventHandler * eventHandler)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->joinChannelWithUserAccountEx(token, channelId, userAccount, options, eventHandler);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getUserInfoByUserAccount (const char * userAccount, rtc::UserInfo * userInfo)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getUserInfoByUserAccount(userAccount, userInfo);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getUserInfoByUid (uid_t uid, rtc::UserInfo * userInfo)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getUserInfoByUid(uid, userInfo);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startOrUpdateChannelMediaRelay (const ChannelMediaRelayConfiguration & configuration)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startOrUpdateChannelMediaRelay(configuration);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopChannelMediaRelay ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopChannelMediaRelay();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::pauseAllChannelMediaRelay ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->pauseAllChannelMediaRelay();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::resumeAllChannelMediaRelay ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->resumeAllChannelMediaRelay();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setDirectCdnStreamingAudioConfiguration (AUDIO_PROFILE_TYPE profile)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setDirectCdnStreamingAudioConfiguration(profile);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setDirectCdnStreamingVideoConfiguration (const VideoEncoderConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setDirectCdnStreamingVideoConfiguration(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startDirectCdnStreaming (IDirectCdnStreamingEventHandler * eventHandler, const char * publishUrl, const DirectCdnStreamingMediaOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startDirectCdnStreaming(eventHandler, publishUrl, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopDirectCdnStreaming ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopDirectCdnStreaming();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateDirectCdnStreamingMediaOptions (const DirectCdnStreamingMediaOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->updateDirectCdnStreamingMediaOptions(options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startRhythmPlayer (const char * sound1, const char * sound2, const AgoraRhythmPlayerConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startRhythmPlayer(sound1, sound2, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopRhythmPlayer ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->stopRhythmPlayer();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::configRhythmPlayer (const AgoraRhythmPlayerConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->configRhythmPlayer(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::takeSnapshot (uid_t uid, const char * filePath)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->takeSnapshot(uid, filePath);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::takeSnapshot (uid_t uid, const media::SnapshotConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->takeSnapshot(uid, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableContentInspect (bool enabled, const media::ContentInspectConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableContentInspect(enabled, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustCustomAudioPublishVolume (track_id_t trackId, int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustCustomAudioPublishVolume(trackId, volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustCustomAudioPlayoutVolume (track_id_t trackId, int volume)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->adjustCustomAudioPlayoutVolume(trackId, volume);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setCloudProxy (CLOUD_PROXY_TYPE proxyType)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setCloudProxy(proxyType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setLocalAccessPoint (const LocalAccessPointConfiguration & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setLocalAccessPoint(config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAdvancedAudioOptions (AdvancedAudioOptions & options, int sourceType /* 0 */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAdvancedAudioOptions(options, sourceType);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setAVSyncSource (const char * channelId, uid_t uid)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setAVSyncSource(channelId, uid);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableVideoImageSource (bool enable, const ImageTrackOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableVideoImageSource(enable, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int64_t AgoraUERtcEngine::getCurrentMonotonicTimeInMs ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getCurrentMonotonicTimeInMs();
                        return ret;
                    }
                    return 0;
                }




                int AgoraUERtcEngine::enableWirelessAccelerate (bool enabled)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableWirelessAccelerate(enabled);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getNetworkType ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getNetworkType();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setParameters (const char * parameters)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->setParameters(parameters);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startMediaRenderingTracing ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->startMediaRenderingTracing();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableInstantMediaRendering ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->enableInstantMediaRendering();
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                uint64_t AgoraUERtcEngine::getNtpWallTimeInMs ()
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->getNtpWallTimeInMs();
                        return ret;
                    }
                    return 0;
                }




                bool AgoraUERtcEngine::isFeatureAvailableOnDevice (FeatureType type)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->isFeatureAvailableOnDevice(type);
                        return ret;
                    }
                    return false;
                }




                int AgoraUERtcEngine::sendAudioMetadata (const char * metadata, size_t length)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->sendAudioMetadata(metadata, length);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::queryHDRCapability (VIDEO_MODULE_TYPE videoModule, HDR_CAPABILITY & capability)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = RtcEngine->queryHDRCapability(videoModule, capability);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::joinChannelEx (const char * token, const RtcConnection & connection, const ChannelMediaOptions & options, IRtcEngineEventHandler * eventHandler)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->joinChannelEx(token, connection, options, eventHandler);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::leaveChannelEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->leaveChannelEx(connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::leaveChannelEx (const RtcConnection & connection, const LeaveChannelOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->leaveChannelEx(connection, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::leaveChannelWithUserAccountEx (const char * channelId, const char * userAccount)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->leaveChannelWithUserAccountEx(channelId, userAccount);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::leaveChannelWithUserAccountEx (const char * channelId, const char * userAccount, const LeaveChannelOptions & options)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->leaveChannelWithUserAccountEx(channelId, userAccount, options);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateChannelMediaOptionsEx (const ChannelMediaOptions & options, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->updateChannelMediaOptionsEx(options, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setVideoEncoderConfigurationEx (const VideoEncoderConfiguration & config, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setVideoEncoderConfigurationEx(config, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteRemoteAudioStreamEx (uid_t uid, bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteRemoteAudioStreamEx(uid, mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteRemoteVideoStreamEx (uid_t uid, bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteRemoteVideoStreamEx(uid, mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteVideoStreamTypeEx (uid_t uid, VIDEO_STREAM_TYPE streamType, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setRemoteVideoStreamTypeEx(uid, streamType, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteLocalAudioStreamEx (bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteLocalAudioStreamEx(mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteLocalVideoStreamEx (bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteLocalVideoStreamEx(mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteAllRemoteAudioStreamsEx (bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteAllRemoteAudioStreamsEx(mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteAllRemoteVideoStreamsEx (bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteAllRemoteVideoStreamsEx(mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeAudioBlocklistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setSubscribeAudioBlocklistEx(uidList, uidNumber, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeAudioAllowlistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setSubscribeAudioAllowlistEx(uidList, uidNumber, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeVideoBlocklistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setSubscribeVideoBlocklistEx(uidList, uidNumber, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSubscribeVideoAllowlistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setSubscribeVideoAllowlistEx(uidList, uidNumber, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteVideoSubscriptionOptionsEx (uid_t uid, const VideoSubscriptionOptions & options, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setRemoteVideoSubscriptionOptionsEx(uid, options, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteVoicePositionEx (uid_t uid, double pan, double gain, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setRemoteVoicePositionEx(uid, pan, gain, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteUserSpatialAudioParamsEx (uid_t uid, const agora::SpatialAudioParams & params, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setRemoteUserSpatialAudioParamsEx(uid, params, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setRemoteRenderModeEx (uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setRemoteRenderModeEx(uid, renderMode, mirrorMode, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableLoopbackRecordingEx (const RtcConnection & connection, bool enabled, const char * deviceName /* nullptr */ )
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->enableLoopbackRecordingEx(connection, enabled, deviceName);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustRecordingSignalVolumeEx (int volume, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->adjustRecordingSignalVolumeEx(volume, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::muteRecordingSignalEx (bool mute, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->muteRecordingSignalEx(mute, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::adjustUserPlaybackSignalVolumeEx (uid_t uid, int volume, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->adjustUserPlaybackSignalVolumeEx(uid, volume, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                agora::rtc::CONNECTION_STATE_TYPE AgoraUERtcEngine::getConnectionStateEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->getConnectionStateEx(connection);
                        return ret;
                    }
                    return agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED;
                }




                int AgoraUERtcEngine::enableEncryptionEx (const RtcConnection & connection, bool enabled, const EncryptionConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->enableEncryptionEx(connection, enabled, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::createDataStreamEx (int * streamId, bool reliable, bool ordered, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->createDataStreamEx(streamId, reliable, ordered, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::createDataStreamEx (int * streamId, const DataStreamConfig & config, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->createDataStreamEx(streamId, config, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::sendStreamMessageEx (int streamId, const char * data, size_t length, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->sendStreamMessageEx(streamId, data, length, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::addVideoWatermarkEx (const char * watermarkUrl, const WatermarkOptions & options, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->addVideoWatermarkEx(watermarkUrl, options, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::clearVideoWatermarkEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->clearVideoWatermarkEx(connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::sendCustomReportMessageEx (const char * id, const char * category, const char * event, const char * label, int value, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->sendCustomReportMessageEx(id, category, event, label, value, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableAudioVolumeIndicationEx (int interval, int smooth, bool reportVad, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->enableAudioVolumeIndicationEx(interval, smooth, reportVad, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startRtmpStreamWithoutTranscodingEx (const char * url, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->startRtmpStreamWithoutTranscodingEx(url, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startRtmpStreamWithTranscodingEx (const char * url, const LiveTranscoding & transcoding, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->startRtmpStreamWithTranscodingEx(url, transcoding, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::updateRtmpTranscodingEx (const LiveTranscoding & transcoding, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->updateRtmpTranscodingEx(transcoding, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopRtmpStreamEx (const char * url, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->stopRtmpStreamEx(url, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startOrUpdateChannelMediaRelayEx (const ChannelMediaRelayConfiguration & configuration, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->startOrUpdateChannelMediaRelayEx(configuration, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::stopChannelMediaRelayEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->stopChannelMediaRelayEx(connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::pauseAllChannelMediaRelayEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->pauseAllChannelMediaRelayEx(connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::resumeAllChannelMediaRelayEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->resumeAllChannelMediaRelayEx(connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getUserInfoByUserAccountEx (const char * userAccount, rtc::UserInfo * userInfo, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->getUserInfoByUserAccountEx(userAccount, userInfo, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getUserInfoByUidEx (uid_t uid, rtc::UserInfo * userInfo, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->getUserInfoByUidEx(uid, userInfo, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableDualStreamModeEx (bool enabled, const SimulcastStreamConfig & streamConfig, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->enableDualStreamModeEx(enabled, streamConfig, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setDualStreamModeEx (SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig & streamConfig, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setDualStreamModeEx(mode, streamConfig, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setSimulcastConfigEx (const SimulcastConfig & simulcastConfig, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setSimulcastConfigEx(simulcastConfig, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setHighPriorityUserListEx (uid_t * uidList, int uidNum, STREAM_FALLBACK_OPTIONS option, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setHighPriorityUserListEx(uidList, uidNum, option, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::takeSnapshotEx (const RtcConnection & connection, uid_t uid, const char * filePath)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->takeSnapshotEx(connection, uid, filePath);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::takeSnapshotEx (const RtcConnection & connection, uid_t uid, const media::SnapshotConfig & config)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->takeSnapshotEx(connection, uid, config);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::enableContentInspectEx (bool enabled, const media::ContentInspectConfig & config, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->enableContentInspectEx(enabled, config, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::startMediaRenderingTracingEx (const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->startMediaRenderingTracingEx(connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::setParametersEx (const RtcConnection & connection, const char * parameters)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->setParametersEx(connection, parameters);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::getCallIdEx (agora::util::AString & callId, const RtcConnection & connection)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->getCallIdEx(callId, connection);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }




                int AgoraUERtcEngine::sendAudioMetadataEx (const RtcConnection & connection, const char * metadata, size_t length)
                {
                    if (RtcEngine != nullptr) {
                        auto ret = ((IRtcEngineEx*)RtcEngine)->sendAudioMetadataEx(connection, metadata, length);
                        return ret;
                    }
                    return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
                }



#pragma endregion Other Native APIs

        }
    }
}