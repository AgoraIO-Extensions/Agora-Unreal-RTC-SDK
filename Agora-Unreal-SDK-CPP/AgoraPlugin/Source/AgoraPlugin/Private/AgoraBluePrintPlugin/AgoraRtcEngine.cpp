//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraRtcEngine.h"
#include "AgoraBluePrintPlugin/AgoraSpatialAudio.h"
#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandler.h"
#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandlerEx.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif

UObject* UAgoraRtcEngine::QueryInterface(EINTERFACE_ID_TYPE iid)
{
	if (iid == EINTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER)
	{
		agora::rtc::IVideoDeviceManager* VideoDeviceManager = nullptr;
		RtcEngineProxyClassWrapper::GetInstance()->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);

		if (videoDeviceManager != nullptr)
		{
			return videoDeviceManager;
		}

		videoDeviceManager = NewObject<UIVideoDeviceManager>();
		videoDeviceManager->SetVideoDeviceManager(VideoDeviceManager);

		return videoDeviceManager;
	}
	else if (iid == EINTERFACE_ID_TYPE::AGORA_IID_AUDIO_DEVICE_MANAGER)
	{
		agora::rtc::IAudioDeviceManager* AudioDeviceManager = nullptr;
		RtcEngineProxyClassWrapper::GetInstance()->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&AudioDeviceManager);

		if (audioDeviceManager != nullptr)
		{
			return audioDeviceManager;
		}
		audioDeviceManager = NewObject<UIAudioDeviceManager>();

		audioDeviceManager->SetAudioDeviceManager(AudioDeviceManager);

		return audioDeviceManager;
	}
	else if (iid == EINTERFACE_ID_TYPE::AGORA_IID_LOCAL_SPATIAL_AUDIO)
	{
		agora::rtc::ILocalSpatialAudioEngine* SpatialAudioEngine = nullptr;
		RtcEngineProxyClassWrapper::GetInstance()->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_LOCAL_SPATIAL_AUDIO, (void**)&SpatialAudioEngine);

		if (spatialAudioEngine != nullptr)
		{
			return spatialAudioEngine;
		}
		spatialAudioEngine = NewObject<UILocalSpatialAudioEngine>();

		spatialAudioEngine->SetLocalSpatialAudioEngine(SpatialAudioEngine);

		return spatialAudioEngine;
	}
	//else if (iid == EINTERFACE_ID_TYPE::AGORA_IID_MEDIA_RECORDER)
	//{
	//	agora::rtc::IMediaRecorder* MediaRecorder = nullptr;
	//	RtcEngineProxyClassWrapper::GetInstance()->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_MEDIA_RECORDER, (void**)&MediaRecorder);

	//	if (mediaRecorder != nullptr)
	//	{
	//		return mediaRecorder;
	//	}
	//	mediaRecorder = NewObject<UIMediaRecorder>();

	//	mediaRecorder->SetMediaRecorder(MediaRecorder);

	//	return mediaRecorder;
	//}
	return nullptr;
}
void UAgoraRtcEngine::Release(bool sync)
{
	if (videoDeviceManager != nullptr)
	{
		videoDeviceManager->Release();
		videoDeviceManager = nullptr;
	}
	if (audioDeviceManager != nullptr)
	{
		audioDeviceManager->Release();
		audioDeviceManager = nullptr;
	}
	if (spatialAudioEngine != nullptr)
	{
		spatialAudioEngine->Release();
		spatialAudioEngine = nullptr;
	}
	//if (mediaRecorder != nullptr)
	//{
	//	mediaRecorder->Release();
	//	mediaRecorder = nullptr;
	//}
	if (mediaPlayer != nullptr)
	{
		DestroyMediaPlayer(mediaPlayer);
		mediaPlayer = nullptr;
	}
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (screenCaptureSourceList != nullptr)
	{
		screenCaptureSourceList = nullptr;
	}
#endif
	return RtcEngineProxyClassWrapper::GetInstance()->release(sync);
}
int UAgoraRtcEngine::Initialize(const FRtcEngineContext& context)
{
	agora::rtc::RtcEngineContext rtcEngineContext = context.CreateAgoraData();

	if (context.eventHandler != nullptr && std::strcmp(context.eventHandler->eventHandlerType(), "event_handler") == 0)
	{
		rtcEngineContext.eventHandler = (agora::rtc::IRtcEngineEventHandler*)context.eventHandler;
	}
	else
	{
		rtcEngineContext.eventHandler = (agora::rtc::IRtcEngineEventHandlerEx*)context.eventHandler;
	}

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->initialize(rtcEngineContext);

	context.FreeAgoraData(rtcEngineContext);
	
	return ret;
}


int UAgoraRtcEngine::InitializeEx(const FRtcEngineContextEx& context)
{
	agora::rtc::RtcEngineContext rtcEngineContext = context.CreateAgoraData();

	if (context.eventHandler != nullptr && std::strcmp(context.eventHandler->eventHandlerType(), "event_handler") == 0)
	{
		rtcEngineContext.eventHandler = (agora::rtc::IRtcEngineEventHandler*)context.eventHandler;
	}
	else
	{
		rtcEngineContext.eventHandler = (agora::rtc::IRtcEngineEventHandlerEx*)context.eventHandler;
	}

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->initialize(rtcEngineContext);

	context.FreeAgoraData(rtcEngineContext);
	
	return ret;
}

FString UAgoraRtcEngine::GetVersion(int build)
{
	return RtcEngineProxyClassWrapper::GetInstance()->getVersion(&build);
}
FString UAgoraRtcEngine::GetErrorDescription(int code)
{
	return RtcEngineProxyClassWrapper::GetInstance()->getErrorDescription(code);
}

int UAgoraRtcEngine::QueryCodecCapability(TArray<FCodecCapInfo> codecInfo)
{
	int size = codecInfo.Num();

	agora::rtc::CodecCapInfo* codecList = nullptr;
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(codecList, agora::rtc::CodecCapInfo, size, codecInfo)
	
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->queryCodecCapability(codecList, size);
	
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(codecList, size, FCodecCapInfo)
	return ret;
}


int UAgoraRtcEngine::QueryDeviceScore()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->queryDeviceScore();
	return ret;
}
int UAgoraRtcEngine::PreloadChannel(const FString& token, const FString& channelId, int64 uid)
{
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->preloadChannel(Token.c_str(), ChannelId.c_str(),uid);
	return ret;
}


int UAgoraRtcEngine::PreloadChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount)
{
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->preloadChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str());
	return ret;
}


int UAgoraRtcEngine::UpdatePreloadChannelToken(const FString& token)
{
	std::string Token = TCHAR_TO_UTF8(*token);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updatePreloadChannelToken(Token.c_str());
	return ret;
}

int UAgoraRtcEngine::JoinChannel(FString token, FString channelId, int64 uid, const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();

	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannel(Token.c_str(), ChannelId.c_str(), uid, channelMediaOptions);

	options.FreeAgoraData(channelMediaOptions);
	

	agora::rtc::IAudioDeviceManager* AudioDeviceManager;
	RtcEngineProxyClassWrapper::GetInstance()->queryInterface(agora::rtc::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&AudioDeviceManager);

	return ret;
}
int UAgoraRtcEngine::UpdateChannelMediaOptions(const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateChannelMediaOptions(channelMediaOptions);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}

int UAgoraRtcEngine::LeaveChannel(const FLeaveChannelOptions& options)
{
	agora::rtc::LeaveChannelOptions AgoraLeaveChannelOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->leaveChannel(AgoraLeaveChannelOptions);
	options.FreeAgoraData(AgoraLeaveChannelOptions);
	return ret;
}

int UAgoraRtcEngine::RenewToken(FString token)
{
	std::string Token = TCHAR_TO_UTF8(*token);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->renewToken(Token.c_str());
	return ret;
}
int UAgoraRtcEngine::SetChannelProfile(ECHANNEL_PROFILE_TYPE profile)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setChannelProfile((agora::CHANNEL_PROFILE_TYPE)profile);
	return ret;
}
int UAgoraRtcEngine::SetClientRole(ECLIENT_ROLE_TYPE clientroletype, FClientRoleOptions& options)
{
	agora::rtc::ClientRoleOptions clientRoleOptions = options.CreateAgoraData();
	agora::rtc::CLIENT_ROLE_TYPE roleType = (agora::rtc::CLIENT_ROLE_TYPE)clientroletype;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setClientRole(roleType, clientRoleOptions);
	options.FreeAgoraData(clientRoleOptions);
	return ret;
}
int UAgoraRtcEngine::StartEchoTest(const FEchoTestConfiguration& config)
{
	agora::rtc::EchoTestConfiguration echoTestConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startEchoTest(echoTestConfiguration);
	config.FreeAgoraData(echoTestConfiguration);
	return ret;
}
int UAgoraRtcEngine::StopEchoTest()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopEchoTest();
	return ret;
}

int UAgoraRtcEngine::EnableMultiCamera(bool enabled, const FCameraCapturerConfiguration& config)
{
	auto ret = -1;

#if defined(__APPLE__) && TARGET_OS_IOS
	agora::rtc::CameraCapturerConfiguration RtcConfig = config.CreateAgoraData();
	ret = RtcEngineProxyClassWrapper::GetInstance()->enableMultiCamera(enabled, RtcConfig);
	config.FreeAgoraData(RtcConfig);
#endif

	return ret;
}

int UAgoraRtcEngine::EnableVideo()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableVideo();
	return ret;
}
int UAgoraRtcEngine::DisableVideo()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->disableVideo();
	return ret;
}
int UAgoraRtcEngine::StartPreview(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}
int UAgoraRtcEngine::StopPreview(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}
int UAgoraRtcEngine::StartLastmileProbeTest(const FLastmileProbeConfig& config)
{
	agora::rtc::LastmileProbeConfig lastmileProbeConfig = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startLastmileProbeTest(lastmileProbeConfig);
	config.FreeAgoraData(lastmileProbeConfig);
	return ret;
}

int UAgoraRtcEngine::StopLastmileProbeTest()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopLastmileProbeTest();
	return ret;
}

int UAgoraRtcEngine::SetVideoEncoderConfiguration(const FVideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoEncoderConfiguration(videoEncoderConfiguration);
	config.FreeAgoraData(videoEncoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::SetBeautyEffectOptions(bool enabled, const FBeautyOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::BeautyOptions beautyOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setBeautyEffectOptions(enabled, beautyOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	options.FreeAgoraData(beautyOptions);
	return ret;
}
int UAgoraRtcEngine::SetLowlightEnhanceOptions(bool enabled, const FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::LowlightEnhanceOptions lowlightEnhanceOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLowlightEnhanceOptions(enabled, lowlightEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	options.FreeAgoraData(lowlightEnhanceOptions);
	return ret;
}
int UAgoraRtcEngine::SetVideoDenoiserOptions(bool enabled, const FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VideoDenoiserOptions videoDenoiserOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoDenoiserOptions(enabled, videoDenoiserOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	options.FreeAgoraData(videoDenoiserOptions);
	return ret;
}
int UAgoraRtcEngine::SetColorEnhanceOptions(bool enabled, const FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::ColorEnhanceOptions colorEnhanceOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setColorEnhanceOptions(enabled, colorEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	options.FreeAgoraData(colorEnhanceOptions);
	return ret;
}
int UAgoraRtcEngine::EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VirtualBackgroundSource virtualBackgroundSource = backgroundSource.CreateAgoraData();
	agora::rtc::SegmentationProperty segmentationProperty = segproperty.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableVirtualBackground(enabled, virtualBackgroundSource, segmentationProperty, (agora::media::MEDIA_SOURCE_TYPE)type);
	backgroundSource.FreeAgoraData(virtualBackgroundSource);
	segproperty.FreeAgoraData(segmentationProperty);
	return ret;
}

int UAgoraRtcEngine::SetupRemoteVideo(const FVideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas = canvas.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setupRemoteVideo(videoCanvas);
	canvas.FreeAgoraData(videoCanvas);
	return ret;
}
int UAgoraRtcEngine::SetupLocalVideo(const FVideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas = canvas.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setupLocalVideo(videoCanvas);
	canvas.FreeAgoraData(videoCanvas);
	return ret;
}

int UAgoraRtcEngine::SetVideoScenario(EVIDEO_APPLICATION_SCENARIO_TYPE scenarioType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoScenario((agora::rtc::VIDEO_APPLICATION_SCENARIO_TYPE)scenarioType);
	return ret;
}


int UAgoraRtcEngine::SetVideoQoEPreference(EVIDEO_QOE_PREFERENCE_TYPE qoePreference)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoQoEPreference((agora::rtc::VIDEO_QOE_PREFERENCE_TYPE)qoePreference);
	return ret;
}

int UAgoraRtcEngine::EnableAudio()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableAudio();
	return ret;
}
int UAgoraRtcEngine::DisableAudio()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->disableAudio();
	return ret;
}

int UAgoraRtcEngine::SetAudioProfile(EAUDIO_PROFILE_TYPE profile /*= EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT*/, EAUDIO_SCENARIO_TYPE scenario /*= EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT*/)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile, (agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
	return ret;
}

int UAgoraRtcEngine::SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioScenario((agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
	return ret;
}
int UAgoraRtcEngine::EnableLocalAudio(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableLocalAudio(enabled);
	return ret;
}
int UAgoraRtcEngine::MuteLocalAudioStream(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteLocalAudioStream(mute);
	return ret;
}
int UAgoraRtcEngine::MuteAllRemoteAudioStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteAllRemoteAudioStreams(mute);
	return ret;
}
int UAgoraRtcEngine::SetDefaultMuteAllRemoteAudioStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDefaultMuteAllRemoteAudioStreams(mute);
	return ret;
}
int UAgoraRtcEngine::SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteDefaultVideoStreamType((agora::rtc::VIDEO_STREAM_TYPE)streamType);
	return ret;
}

int UAgoraRtcEngine::MuteRemoteAudioStream(int64 uid, bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRemoteAudioStream(uid, mute);
	return ret;
}
int UAgoraRtcEngine::MuteLocalVideoStream(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteLocalVideoStream(mute);
	return ret;
}
int UAgoraRtcEngine::EnableLocalVideo(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableLocalVideo(enabled);
	return ret;
}
int UAgoraRtcEngine::MuteAllRemoteVideoStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteAllRemoteVideoStreams(mute);
	return ret;
}
int UAgoraRtcEngine::SetDefaultMuteAllRemoteVideoStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDefaultMuteAllRemoteVideoStreams(mute);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteVideoStream(int64 uid, bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRemoteVideoStream(uid, mute);
	return ret;
}

int UAgoraRtcEngine::SetRemoteVideoStreamType(int64 uid, EVIDEO_STREAM_TYPE streamType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoStreamType(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptions(int64 uid, const FVideoSubscriptionOptions& options)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoSubscriptionOptions(uid, videoSubscriptionOptions);
	options.FreeAgoraData(videoSubscriptionOptions);
	return ret;
}

int UAgoraRtcEngine::EnableAudioVolumeIndication(int interval, int smooth, bool reportVad)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableAudioVolumeIndication(interval, smooth, reportVad);
	return ret;
}
int UAgoraRtcEngine::StartAudioRecording(const FAudioRecordingConfiguration& config)
{
	agora::rtc::AudioRecordingConfiguration audioRecordingConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startAudioRecording(audioRecordingConfiguration);
	config.FreeAgoraData(audioRecordingConfiguration);
	return ret;
}

int UAgoraRtcEngine::RegisterAudioEncodedFrameObserver(const FAudioEncodedFrameObserverConfig& config, UIAudioEncodedFrameObserver* observer)
{
	agora::rtc::AudioEncodedFrameObserverConfig audioEncodedFrameObserverConfig = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerAudioEncodedFrameObserver(audioEncodedFrameObserverConfig, observer);
	config.FreeAgoraData(audioEncodedFrameObserverConfig);
	return ret;
}
int UAgoraRtcEngine::StopAudioRecording()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopAudioRecording();
	return ret;
}

UIMediaPlayer* UAgoraRtcEngine::CreateMediaPlayer()
{
	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer = nullptr;

	if (mediaPlayer != nullptr)
	{
		return mediaPlayer;
	}

	mediaPlayer = NewObject<UIMediaPlayer>();

	MediaPlayer = RtcEngineProxyClassWrapper::GetInstance()->createMediaPlayer();

	mediaPlayer->SetMediaPlayer(MediaPlayer);

	return mediaPlayer;
}
int UAgoraRtcEngine::DestroyMediaPlayer(UIMediaPlayer* media_player)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->destroyMediaPlayer(media_player->GetMediaPlayer());
	return ret;
}

UIMediaRecorder* UAgoraRtcEngine::CreateMediaRecorder(FRecorderStreamInfo info)
{
	agora::rtc::RecorderStreamInfo recorderStreamInfo = info.CreateAgoraData();
	UIMediaRecorder* ptrMediaRecorder = NewObject<UIMediaRecorder>();
	ptrMediaRecorder->SetMediaRecorder(RtcEngineProxyClassWrapper::GetInstance()->createMediaRecorder(recorderStreamInfo).get());
	info.FreeAgoraData(recorderStreamInfo);
	return ptrMediaRecorder;
}


int UAgoraRtcEngine::DestroyMediaRecorder(UIMediaRecorder* ptrmediaRecorder)
{
	agora::agora_refptr<agora::rtc::IMediaRecorder> AgoraMediaRecorder = ptrmediaRecorder->GetMediaRecorder();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->destroyMediaRecorder(AgoraMediaRecorder);
	return ret;
}

int UAgoraRtcEngine::StartAudioMixing(FString filePath, bool loopback, int cycle, int startPos)
{
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startAudioMixing(FilePath.c_str(), loopback, cycle, startPos);
	return ret;
}

int UAgoraRtcEngine::StopAudioMixing()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopAudioMixing();
	return ret;
}

int UAgoraRtcEngine::PauseAudioMixing()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseAudioMixing();
	return ret;
}
int UAgoraRtcEngine::ResumeAudioMixing()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeAudioMixing();
	return ret;
}
int UAgoraRtcEngine::SelectAudioTrack(int index)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->selectAudioTrack(index);
	return ret;
}
int UAgoraRtcEngine::GetAudioTrackCount()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getAudioTrackCount();
	return ret;
}
int UAgoraRtcEngine::AdjustAudioMixingVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustAudioMixingVolume(volume);
	return ret;
}
int UAgoraRtcEngine::AdjustAudioMixingPublishVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustAudioMixingPublishVolume(volume);
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingPublishVolume()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getAudioMixingPublishVolume();
	return ret;
}
int UAgoraRtcEngine::AdjustAudioMixingPlayoutVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustAudioMixingPlayoutVolume(volume);
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingPlayoutVolume()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getAudioMixingPlayoutVolume();
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingDuration()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getAudioMixingDuration();
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingCurrentPosition()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getAudioMixingCurrentPosition();
	return ret;
}
int UAgoraRtcEngine::SetAudioMixingPosition(int pos)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioMixingPosition(pos);
	return ret;
}
int UAgoraRtcEngine::SetAudioMixingDualMonoMode(EAUDIO_MIXING_DUAL_MONO_MODE mode)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioMixingDualMonoMode((agora::media::AUDIO_MIXING_DUAL_MONO_MODE)mode);
	return ret;
}
int UAgoraRtcEngine::SetAudioMixingPitch(int pitch)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioMixingPitch(pitch);
	return ret;
}

int UAgoraRtcEngine::SetAudioMixingPlaybackSpeed(int speed)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioMixingPlaybackSpeed(speed);
	return ret;
}

int UAgoraRtcEngine::GetEffectsVolume()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getEffectsVolume();
	return ret;
}
int UAgoraRtcEngine::SetEffectsVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setEffectsVolume(volume);
	return ret;
}
int UAgoraRtcEngine::PreloadEffect(int soundId, FString filePath, int startPos)
{
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->preloadEffect(soundId, FilePath.c_str(), startPos);
	return ret;
}
int UAgoraRtcEngine::PlayEffect(int soundId, FString filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos)
{
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->playEffect(soundId, FilePath.c_str(), loopCount, pitch, pan, gain, publish, startPos);
	return ret;
}
int UAgoraRtcEngine::PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->playAllEffects(loopCount, pitch, pan, gain, publish);
	return ret;
}
int UAgoraRtcEngine::GetVolumeOfEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getVolumeOfEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::SetVolumeOfEffect(int soundId, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVolumeOfEffect(soundId, volume);
	return ret;
}
int UAgoraRtcEngine::PauseEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::PauseAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseAllEffects();
	return ret;
}
int UAgoraRtcEngine::ResumeEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::ResumeAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeAllEffects();
	return ret;
}
int UAgoraRtcEngine::StopEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::StopAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopAllEffects();
	return ret;
}
int UAgoraRtcEngine::UnloadEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->unloadEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::UnloadAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->unloadAllEffects();
	return ret;
}
int UAgoraRtcEngine::GetEffectDuration(FString filePath)
{
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getEffectDuration(FilePath.c_str());
	return ret;
}
int UAgoraRtcEngine::SetEffectPosition(int soundId, int pos)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setEffectPosition(soundId, pos);
	return ret;
}
int UAgoraRtcEngine::GetEffectCurrentPosition(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getEffectCurrentPosition(soundId);
	return ret;
}
int UAgoraRtcEngine::EnableSoundPositionIndication(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableSoundPositionIndication(enabled);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVoicePosition(int64 uid, float pan, float gain)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVoicePosition(uid, pan, gain);
	return ret;
}
int UAgoraRtcEngine::EnableSpatialAudio(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableSpatialAudio(enabled);
	return ret;
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParams(int64 uid, const FSpatialAudioParams& params)
{
	agora::SpatialAudioParams spatialAudioParams = params.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteUserSpatialAudioParams(uid, spatialAudioParams);
	params.FreeAgoraData(spatialAudioParams);
	return ret;
}
int UAgoraRtcEngine::SetVoiceBeautifierPreset(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVoiceBeautifierPreset(preset.GetRawValue());
	return ret;
}
int UAgoraRtcEngine::SetAudioEffectPreset(FENUMWRAP_AUDIO_EFFECT_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioEffectPreset(preset.GetRawValue());
	return ret;
}
int UAgoraRtcEngine::SetVoiceConversionPreset(FENUMWRAP_VOICE_CONVERSION_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVoiceConversionPreset(preset.GetRawValue());
	return ret;
}
int UAgoraRtcEngine::SetAudioEffectParameters(FENUMWRAP_AUDIO_EFFECT_PRESET preset, int param1, int param2)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAudioEffectParameters(preset.GetRawValue(), param1, param2);
	return ret;
}
int UAgoraRtcEngine::SetVoiceBeautifierParameters(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset, int param1, int param2)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVoiceBeautifierParameters(preset.GetRawValue(), param1, param2);
	return ret;
}
int UAgoraRtcEngine::SetVoiceConversionParameters(FENUMWRAP_VOICE_CONVERSION_PRESET preset, int param1, int param2)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVoiceConversionParameters(preset.GetRawValue(), param1, param2);
	return ret;
}
int UAgoraRtcEngine::SetLocalVoicePitch(float pitch)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalVoicePitch(pitch);
	return ret;
}


int UAgoraRtcEngine::SetLocalVoiceFormant(FString formantRatio)
{
	double ValFormantRatio = FCString::Atod(*formantRatio);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalVoiceFormant(ValFormantRatio);
	return ret;
}

int UAgoraRtcEngine::SetLocalVoiceEqualization(EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalVoiceEqualization((agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY)bandFrequency, bandGain);
	return ret;
}
int UAgoraRtcEngine::SetLocalVoiceReverb(EAUDIO_REVERB_TYPE reverbKey, int value)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalVoiceReverb((agora::rtc::AUDIO_REVERB_TYPE)reverbKey, value);
	return ret;
}
int UAgoraRtcEngine::SetLogFile(FString filePath)
{
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLogFile(FilePath.c_str());
	return ret;
}
int UAgoraRtcEngine::SetLogFilter(int filter)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLogFilter(filter);
	return ret;
}
int UAgoraRtcEngine::SetLogLevel(ELOG_LEVEL level)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLogLevel((agora::commons::LOG_LEVEL)level);
	return ret;
}
int UAgoraRtcEngine::SetLogFileSize(int fileSizeInKBytes)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLogFileSize(fileSizeInKBytes);
	return ret;
}
int UAgoraRtcEngine::UploadLogFile(FString& requestId)
{
	agora::util::AString _requestId;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->uploadLogFile(_requestId);
	requestId = UTF8_TO_TCHAR(_requestId->c_str());
	return ret;
}

int UAgoraRtcEngine::WriteLog(ELOG_LEVEL level, FString Content)
{
	std::string STDConent = TCHAR_TO_UTF8(*Content);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->writeLog((agora::commons::LOG_LEVEL)(level), STDConent.c_str());
	return ret;
}

int UAgoraRtcEngine::SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalRenderMode((agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
	return ret;
}
int UAgoraRtcEngine::SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteRenderMode(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
	return ret;
}
int UAgoraRtcEngine::SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalVideoMirrorMode((agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
	return ret;
}

int UAgoraRtcEngine::EnableDualStreamMode(bool enabled, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableDualStreamMode(enabled, simulcastStreamConfig);
	streamConfig.FreeAgoraData(simulcastStreamConfig);
	return ret;
}
int UAgoraRtcEngine::SetDualStreamMode(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig AgoraSimulcastStreamConfig = streamConfig.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDualStreamMode(mode.GetRawValue(), AgoraSimulcastStreamConfig);
	streamConfig.FreeAgoraData(AgoraSimulcastStreamConfig);
	return ret;
}

int UAgoraRtcEngine::EnableCustomAudioLocalPlayback(int64 trackId, bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableCustomAudioLocalPlayback(trackId, enabled);
	return ret;
}

int UAgoraRtcEngine::SetRecordingAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRecordingAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
	return ret;
}
int UAgoraRtcEngine::SetPlaybackAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setPlaybackAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
	return ret;
}
int UAgoraRtcEngine::SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
	return ret;
}
int UAgoraRtcEngine::SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
	return ret;
}
int UAgoraRtcEngine::EnableAudioSpectrumMonitor(int intervalInMS)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableAudioSpectrumMonitor(intervalInMS);
	return ret;
}
int UAgoraRtcEngine::DisableAudioSpectrumMonitor()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->disableAudioSpectrumMonitor();
	return ret;
}

int UAgoraRtcEngine::RegisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerAudioSpectrumObserver(observer);
	return ret;
}
int UAgoraRtcEngine::UnregisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->unregisterAudioSpectrumObserver(observer);
	return ret;
}
int UAgoraRtcEngine::AdjustRecordingSignalVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustRecordingSignalVolume(volume);
	return ret;
}
int UAgoraRtcEngine::MuteRecordingSignal(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRecordingSignal(mute);
	return ret;
}
int UAgoraRtcEngine::AdjustPlaybackSignalVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustPlaybackSignalVolume(volume);
	return ret;
}
int UAgoraRtcEngine::AdjustUserPlaybackSignalVolume(int uid, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustUserPlaybackSignalVolume(uid, volume);
	return ret;
}
int UAgoraRtcEngine::SetLocalPublishFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalPublishFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	return ret;
}
int UAgoraRtcEngine::SetRemoteSubscribeFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteSubscribeFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	return ret;
}

int UAgoraRtcEngine::SetHighPriorityUserList(TArray<int64> uidList, ESTREAM_FALLBACK_OPTIONS option)
{
	int uidNum = uidList.Num();
	agora::rtc::uid_t* uidList_t = new agora::rtc::uid_t[uidNum];
	for (int i = 0; i < uidNum; i++)
	{
		uidList_t[i] = uidList[i];
	}
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setHighPriorityUserList(uidList_t, uidNum, (agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	return ret;
}

int UAgoraRtcEngine::EnableLoopbackRecording(bool enabled, FString deviceName)
{
	std::string Device = TCHAR_TO_UTF8(*deviceName);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableLoopbackRecording(enabled, Device.c_str());
	return ret;
}
int UAgoraRtcEngine::AdjustLoopbackSignalVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustLoopbackSignalVolume(volume);
	return ret;
}
int UAgoraRtcEngine::GetLoopbackRecordingVolume()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getLoopbackRecordingVolume();
	return ret;
}
int UAgoraRtcEngine::EnableInEarMonitoring(bool enabled, int includeAudioFilters)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableInEarMonitoring(enabled, includeAudioFilters);
	return ret;
}
int UAgoraRtcEngine::SetInEarMonitoringVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setInEarMonitoringVolume(volume);
	return ret;
}
int UAgoraRtcEngine::LoadExtensionProvider(FString path, bool unload_after_use)
{
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
	std::string Path = TCHAR_TO_UTF8(*path);

	return RtcEngineProxyClassWrapper::GetInstance()->loadExtensionProvider(Path.c_str(), unload_after_use);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}
int UAgoraRtcEngine::SetExtensionProviderProperty(FString provider, FString key, FString value)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Key = TCHAR_TO_UTF8(*key);
	std::string Value = TCHAR_TO_UTF8(*value);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setExtensionProviderProperty(Provider.c_str(), Key.c_str(), Value.c_str());
	return ret;
}
int UAgoraRtcEngine::EnableExtension(FString provider, FString extension, bool enable, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableExtension(Provider.c_str(), Extension.c_str(), enable, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}

int UAgoraRtcEngine::SetExtensionProperty(FString provider, FString extension, FString key, FString value, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	std::string Key = TCHAR_TO_UTF8(*key);
	std::string Value = TCHAR_TO_UTF8(*value);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), Value.c_str(), (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}


int UAgoraRtcEngine::GetExtensionProperty(FString provider, FString extension, FString key, FString value, int buf_len, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	std::string Key = TCHAR_TO_UTF8(*key);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), TCHAR_TO_UTF8(*value), buf_len, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}

int UAgoraRtcEngine::SetCameraCapturerConfiguration(const FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraCapturerConfiguration(cameraCapturerConfiguration);
	config.FreeAgoraData(cameraCapturerConfiguration);
	return ret;
}
int64 UAgoraRtcEngine::CreateCustomVideoTrack()
{
	return RtcEngineProxyClassWrapper::GetInstance()->createCustomVideoTrack();
}
int64 UAgoraRtcEngine::CreateCustomEncodedVideoTrack(const FSenderOptions& sender_option)
{
	agora::rtc::SenderOptions senderOptions = sender_option.CreateAgoraData();
	int ret = RtcEngineProxyClassWrapper::GetInstance()->createCustomEncodedVideoTrack(senderOptions);
	sender_option.FreeAgoraData(senderOptions);
	return ret;
}
int UAgoraRtcEngine::DestroyCustomVideoTrack(int64 video_track_id)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->destroyCustomVideoTrack(video_track_id);
	return ret;
}
int UAgoraRtcEngine::DestroyCustomEncodedVideoTrack(int64 video_track_id)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->destroyCustomEncodedVideoTrack(video_track_id);
	return ret;
}
int UAgoraRtcEngine::SwitchCamera()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->switchCamera();
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsCameraZoomSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraZoomSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraFaceDetectSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraFaceDetectSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraTorchSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraTorchSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraFocusSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraFocusSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraAutoFocusFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraAutoFocusFaceModeSupported();
#else
	return false;
#endif
}
int UAgoraRtcEngine::SetCameraZoomFactor(float factor)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraZoomFactor(factor);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::EnableFaceDetection(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableFaceDetection(enabled);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
float UAgoraRtcEngine::GetCameraMaxZoomFactor()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getCameraMaxZoomFactor();
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraFocusPositionInPreview(float positionX, float positionY)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraFocusPositionInPreview(positionX, positionY);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraTorchOn(bool isOn)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraTorchOn(isOn);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraAutoFocusFaceModeEnabled(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->setCameraAutoFocusFaceModeEnabled(enabled);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsCameraExposurePositionSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraExposurePositionSupported();
#else
	return false;
#endif
}
int UAgoraRtcEngine::SetCameraExposurePosition(float positionXinView, float positionYinView)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->setCameraExposurePosition(positionXinView, positionYinView);
#else
	return  -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}


bool UAgoraRtcEngine::IsCameraExposureSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraExposureSupported();
#else
	return false;
#endif
}


int UAgoraRtcEngine::SetCameraExposureFactor(float factor)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->setCameraExposureFactor(factor);
#else
	return  -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

bool UAgoraRtcEngine::IsCameraAutoExposureFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	return RtcEngineProxyClassWrapper::GetInstance()->isCameraAutoExposureFaceModeSupported();
#else
	return false;
#endif
#endif
	return false;
}
int UAgoraRtcEngine::SetCameraAutoExposureFaceModeEnabled(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraAutoExposureFaceModeEnabled(enabled);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
#endif
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
}

int UAgoraRtcEngine::SetCameraStabilizationMode(FENUMWRAP_CAMERA_STABILIZATION_MODE mode)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	return RtcEngineProxyClassWrapper::GetInstance()->setCameraStabilizationMode(mode.GetRawValue());
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
#endif
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
}

int UAgoraRtcEngine::SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker)
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetEnableSpeakerphone(bool speakerOn)
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setEnableSpeakerphone(speakerOn);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsSpeakerphoneEnabled()
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->isSpeakerphoneEnabled();
	return ret;
#else
	return false;
#endif
}


int UAgoraRtcEngine::SetRouteInCommunicationMode(int route)
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRouteInCommunicationMode(route);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}


bool UAgoraRtcEngine::IsSupportPortraitCenterStage()
{
#if defined(__APPLE__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->isSupportPortraitCenterStage();
	return ret;
#endif
	return false;
}


int UAgoraRtcEngine::EnablePortraitCenterStage(bool enabled)
{
#if defined(__APPLE__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enablePortraitCenterStage(enabled);
	return ret;
#endif
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
}

UIScreenCaptureSourceList* UAgoraRtcEngine::GetScreenCaptureSources(FSIZE thumbSize, FSIZE iconSize, bool includeScreen)
{
	if (screenCaptureSourceList == nullptr)
	{
		screenCaptureSourceList = NewObject<UIScreenCaptureSourceList>();
	}
#if PLATFORM_WINDOWS
	SIZE thumb;
	thumb.cx = thumbSize.width;
	thumb.cy = thumbSize.height;

	SIZE icon;
	icon.cx = iconSize.width;
	icon.cy = iconSize.height;
#elif (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::SIZE thumb;
	thumb.width = thumbSize.width;
	thumb.height = thumbSize.width;
	agora::rtc::SIZE icon;
	icon.width = iconSize.width;
	icon.height = iconSize.height;
#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::IScreenCaptureSourceList* screenCaptureNative = RtcEngineProxyClassWrapper::GetInstance()->getScreenCaptureSources(thumb, icon, includeScreen);
	if (screenCaptureNative != nullptr)
	{
		screenCaptureSourceList->SetScreenCaptureList(screenCaptureNative);
		return screenCaptureSourceList;
	}
#endif
	return nullptr;
}
int UAgoraRtcEngine::SetAudioSessionOperationRestriction(EAUDIO_SESSION_OPERATION_RESTRICTION restriction)
{
#if (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::GetInstance()->setAudioSessionOperationRestriction((agora::AUDIO_SESSION_OPERATION_RESTRICTION)restriction);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCaptureByDisplayId(int displayId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
	agora::rtc::Rectangle rectangle = regionRect.CreateAgoraData();
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCaptureByDisplayId(displayId, rectangle, screenCaptureParameters);
	regionRect.FreeAgoraData(rectangle);
	captureParams.FreeAgoraData(screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::StartScreenCaptureByScreenRect(const FRectangle& screenRect, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams) __deprecated
{
#if defined(_WIN32)
	agora::rtc::Rectangle AgoraScreenRect = screenRect.CreateAgoraData();
	agora::rtc::Rectangle AgoraRegionRect = regionRect.CreateAgoraData();
	agora::rtc::ScreenCaptureParameters AgoraScreenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCaptureByScreenRect(AgoraScreenRect, AgoraRegionRect, AgoraScreenCaptureParameters);
	screenRect.FreeAgoraData(AgoraScreenRect);
	regionRect.FreeAgoraData(AgoraRegionRect);
	captureParams.FreeAgoraData(AgoraScreenCaptureParameters);

	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::GetAudioDeviceInfo(FDeviceInfo& deviceInfo)
{
#if defined(__ANDROID__)
	agora::rtc::DeviceInfo Info;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getAudioDeviceInfo(Info);
	deviceInfo = Info;
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::StartScreenCaptureByWindowId(int64 windowId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle = regionRect.CreateAgoraData();
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCaptureByWindowId((agora::view_t)windowId, rectangle, screenCaptureParameters);
	regionRect.FreeAgoraData(rectangle);
	captureParams.FreeAgoraData(screenCaptureParameters);

	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setScreenCaptureContentHint((agora::rtc::VIDEO_CONTENT_HINT)contentHint);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::UpdateScreenCaptureRegion(const FRectangle& regionRect)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle = regionRect.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateScreenCaptureRegion(rectangle);
	regionRect.FreeAgoraData(rectangle);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::UpdateScreenCaptureParameters(const FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateScreenCaptureParameters(screenCaptureParameters);
	captureParams.FreeAgoraData(screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCapture(const FScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2 = captureParams.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCapture(screenCaptureParameters2);
	captureParams.FreeAgoraData(screenCaptureParameters2);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}


int UAgoraRtcEngine::StartScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType, const FScreenCaptureConfiguration& config)
{

	agora::rtc::ScreenCaptureConfiguration screenCaptureConfiguration= config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType, screenCaptureConfiguration);
	config.FreeAgoraData(screenCaptureConfiguration);
	return ret;
}

int UAgoraRtcEngine::StopScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopScreenCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}

int UAgoraRtcEngine::QueryScreenCaptureCapability()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->queryScreenCaptureCapability();
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}


int UAgoraRtcEngine::QueryCameraFocalLengthCapability(const TArray<FFocalLengthInfo>& focalLengthInfos)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	
	int TotalSize = focalLengthInfos.Num();
	agora::rtc::FocalLengthInfo* focalLengthInfo = nullptr;
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(focalLengthInfo, agora::rtc::FocalLengthInfo, TotalSize, focalLengthInfos)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->queryCameraFocalLengthCapability(focalLengthInfo, TotalSize);
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(focalLengthInfo,TotalSize,FFocalLengthInfo)
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario)
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setScreenCaptureScenario((agora::rtc::SCREEN_SCENARIO_TYPE)screenScenario);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::UpdateScreenCapture(const FScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2 = captureParams.CreateAgoraData();
	int ret = RtcEngineProxyClassWrapper::GetInstance()->updateScreenCapture(screenCaptureParameters2);
	captureParams.FreeAgoraData(screenCaptureParameters2);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StopScreenCapture()
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopScreenCapture();
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::GetCallId(FString& callId)
{
	agora::util::AString agoraStr;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getCallId(agoraStr);

	callId = UTF8_TO_TCHAR(agoraStr->c_str());

	return ret;
}
int UAgoraRtcEngine::Rate(FString callId, int rating, FString description)
{
	std::string CallId = TCHAR_TO_UTF8(*callId);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->rate(CallId.c_str(), rating, TCHAR_TO_UTF8(*description));
	return ret;
}
int UAgoraRtcEngine::Complain(FString callId, FString description)
{
	std::string CallId = TCHAR_TO_UTF8(*callId);
	std::string Description = TCHAR_TO_UTF8(*description);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->complain(CallId.c_str(), Description.c_str());
	return ret;
}
int UAgoraRtcEngine::StartRtmpStreamWithoutTranscoding(FString url)
{
	std::string Url = TCHAR_TO_UTF8(*url);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithoutTranscoding(Url.c_str());
	return ret;
}
int UAgoraRtcEngine::StartRtmpStreamWithTranscoding(FString url, FLiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();
	std::string TempUrl = TCHAR_TO_UTF8(*url);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithTranscoding(TempUrl.c_str(), liveTranscoding);
	transcoding.FreeAgoraData(liveTranscoding);
	return ret;
}
int UAgoraRtcEngine::UpdateRtmpTranscoding(FLiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateRtmpTranscoding(liveTranscoding);
	transcoding.FreeAgoraData(liveTranscoding);

	return ret;
}
int UAgoraRtcEngine::StopRtmpStream(FString url)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopRtmpStream(TCHAR_TO_UTF8(*url));
	return ret;
}

int UAgoraRtcEngine::StartCameraCapture(EVIDEO_SOURCE_TYPE sourceType, const FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startCameraCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType, cameraCapturerConfiguration);

	config.FreeAgoraData(cameraCapturerConfiguration);
	return ret;
}


int UAgoraRtcEngine::StopCameraCapture(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopCameraCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}

int UAgoraRtcEngine::StartLocalVideoTranscoder(const FLocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration AgoraLocalTranscoderConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startLocalVideoTranscoder(AgoraLocalTranscoderConfiguration);
	config.FreeAgoraData(AgoraLocalTranscoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::UpdateLocalTranscoderConfiguration(const FLocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration AgoraLocalTranscoderConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateLocalTranscoderConfiguration(AgoraLocalTranscoderConfiguration);
	config.FreeAgoraData(AgoraLocalTranscoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::StopLocalVideoTranscoder()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopLocalVideoTranscoder();
	return ret;
}

int UAgoraRtcEngine::SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraDeviceOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, orientation.GetRawValue());
	return ret;
}
int UAgoraRtcEngine::SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setScreenCaptureOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, orientation.GetRawValue());
	return ret;
}

ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionState()
{
	return (ECONNECTION_STATE_TYPE)RtcEngineProxyClassWrapper::GetInstance()->getConnectionState();
}
bool UAgoraRtcEngine::RegisterEventHandler(UIRtcEngineEventHandler* eventHandler)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerEventHandler(eventHandler);
	return ret;
}

bool UAgoraRtcEngine::RegisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerEventHandler(eventHandler);
	return ret;
}

bool UAgoraRtcEngine::UnregisterEventHandler(UIRtcEngineEventHandler* eventHandler)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->unregisterEventHandler(eventHandler);
	return ret;
}

bool UAgoraRtcEngine::UnregisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->unregisterEventHandler(eventHandler);
	return ret;
}

int UAgoraRtcEngine::SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteUserPriority(uid, (agora::rtc::PRIORITY_TYPE)userPriority);
	return ret;
}
int UAgoraRtcEngine::RegisterPacketObserver(UIPacketObserver* observer)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerPacketObserver(observer);
	return ret;
}
int UAgoraRtcEngine::SetEncryptionMode(FString encryptionMode)
{
	std::string EncryptionMode = TCHAR_TO_UTF8(*encryptionMode);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setEncryptionMode(EncryptionMode.c_str());
	return ret;
}
int UAgoraRtcEngine::SetEncryptionSecret(FString secret)
{
	std::string Secret = TCHAR_TO_UTF8(*secret);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setEncryptionSecret(Secret.c_str());
	return ret;
}
int UAgoraRtcEngine::EnableEncryption(bool enabled, const FEncryptionConfig& config)
{
	agora::rtc::EncryptionConfig AgoraEncryptionConfig = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableEncryption(enabled, AgoraEncryptionConfig);
	config.FreeAgoraData(AgoraEncryptionConfig);
	return ret;
}
int UAgoraRtcEngine::CreateDataStream(int& streamId, const FDataStreamConfig& config)
{
	agora::rtc::DataStreamConfig dataStreamConfig = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->createDataStream(&streamId, dataStreamConfig);
	config.FreeAgoraData(dataStreamConfig);
	return ret;
}
int UAgoraRtcEngine::SendStreamMessage(int streamId, FString data)
{
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	const char* Data = StdStrData.c_str();

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendStreamMessage(streamId, Data, strlen(Data) + 1);
	return ret;
}
int UAgoraRtcEngine::AddVideoWatermark(FString watermarkUrl, const FWatermarkOptions& options)
{
	std::string STDWatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	agora::rtc::WatermarkOptions watermarkOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->addVideoWatermark(STDWatermarkUrl.c_str() , watermarkOptions);
	options.FreeAgoraData(watermarkOptions);
	return ret;
}

int UAgoraRtcEngine::ClearVideoWatermarks()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->clearVideoWatermarks();
	return ret;
}

int UAgoraRtcEngine::PauseAudio()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseAudio();
	return ret;
}
int UAgoraRtcEngine::ResumeAudio()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeAudio();
	return ret;
}
int UAgoraRtcEngine::EnableWebSdkInteroperability(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableWebSdkInteroperability(enabled);
	return ret;
}
int UAgoraRtcEngine::SendCustomReportMessage(FString id, FString category, FString event, FString label, int value)
{
	std::string Id = TCHAR_TO_UTF8(*id);
	std::string Category = TCHAR_TO_UTF8(*category);
	std::string Event = TCHAR_TO_UTF8(*event);
	std::string Label = TCHAR_TO_UTF8(*label);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendCustomReportMessage(Id.c_str(), Category.c_str(), Event.c_str(), Label.c_str(), value);
	return ret;
}

int UAgoraRtcEngine::RegisterMediaMetadataObserver(UIMetadataObserver* observer, FENUMWRAP_METADATA_TYPE type)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerMediaMetadataObserver(observer, type.GetRawValue());
	return ret;
}
int UAgoraRtcEngine::UnregisterMediaMetadataObserver(UIMetadataObserver* observer, FENUMWRAP_METADATA_TYPE type)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->unregisterMediaMetadataObserver(observer, type.GetRawValue());
	return ret;
}
int UAgoraRtcEngine::StartAudioFrameDump(FString channel_id, int64 uid, FString location, FString uuid, FString passwd, int64 duration_ms, bool auto_upload)
{
	std::string Channel_id = TCHAR_TO_UTF8(*channel_id);
	std::string Location = TCHAR_TO_UTF8(*location);
	std::string Uuid = TCHAR_TO_UTF8(*uuid);
	std::string Passwd = TCHAR_TO_UTF8(*passwd);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startAudioFrameDump(Channel_id.c_str(), uid, Location.c_str(), Uuid.c_str(), Passwd.c_str(), duration_ms, auto_upload);
	return ret;
}


int UAgoraRtcEngine::StopAudioFrameDump(const FString& channel_id, int64 uid, const FString& location)
{
	std::string Channel_id = TCHAR_TO_UTF8(*channel_id);
	std::string Location = TCHAR_TO_UTF8(*location);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopAudioFrameDump(Channel_id.c_str(), uid, Location.c_str());
	return ret;
}

int UAgoraRtcEngine::SetAINSMode(bool enabled, EAUDIO_AINS_MODE mode)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAINSMode(enabled, (agora::rtc::AUDIO_AINS_MODE)mode);
	return ret;
}

int UAgoraRtcEngine::RegisterLocalUserAccount(FString appId, FString userAccount)
{
	std::string AppId = TCHAR_TO_UTF8(*appId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerLocalUserAccount(AppId.c_str(), UserAccount.c_str());
	return ret;
}
int UAgoraRtcEngine::JoinChannelWithUserAccount(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}

int UAgoraRtcEngine::JoinChannelWithUserAccountEx(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannelWithUserAccountEx(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions, eventHandler);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUserAccount(FString userAccount, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUserAccount(UserAccount.c_str(), &info);
	userInfo = info;
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUid(int64 uid, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUid(uid, &info);
	userInfo = info;
	return ret;
}


int UAgoraRtcEngine::StartOrUpdateChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration = configuration.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startOrUpdateChannelMediaRelay(channelMediaRelayConfiguration);
	configuration.FreeAgoraData(channelMediaRelayConfiguration);
	return ret;
}


int UAgoraRtcEngine::StartOrUpdateChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration = configuration.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startOrUpdateChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	configuration.FreeAgoraData(channelMediaRelayConfiguration);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StopChannelMediaRelay()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopChannelMediaRelay();
	return ret;
}
int UAgoraRtcEngine::PauseAllChannelMediaRelay()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseAllChannelMediaRelay();
	return ret;
}
int UAgoraRtcEngine::ResumeAllChannelMediaRelay()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeAllChannelMediaRelay();
	return ret;
}
int UAgoraRtcEngine::SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDirectCdnStreamingAudioConfiguration((agora::rtc::AUDIO_PROFILE_TYPE)profile);
	return ret;
}
int UAgoraRtcEngine::SetDirectCdnStreamingVideoConfiguration(const FVideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDirectCdnStreamingVideoConfiguration(videoEncoderConfiguration);
	config.FreeAgoraData(videoEncoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::StartDirectCdnStreaming(UIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options)
{
	agora::rtc::DirectCdnStreamingMediaOptions directCdnStreamingMediaOptions = options.CreateAgoraData();
	std::string PublishUrl = TCHAR_TO_UTF8(*publishUrl);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startDirectCdnStreaming(eventHandler, PublishUrl.c_str(), directCdnStreamingMediaOptions);
	options.FreeAgoraData(directCdnStreamingMediaOptions);
	return ret;
}
int UAgoraRtcEngine::StopDirectCdnStreaming()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopDirectCdnStreaming();
	return ret;
}
int UAgoraRtcEngine::UpdateDirectCdnStreamingMediaOptions(const FDirectCdnStreamingMediaOptions& options)
{
	agora::rtc::DirectCdnStreamingMediaOptions directCdnStreamingMediaOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateDirectCdnStreamingMediaOptions(directCdnStreamingMediaOptions);
	options.FreeAgoraData(directCdnStreamingMediaOptions);
	return ret;
}
int UAgoraRtcEngine::StartRhythmPlayer(FString sound1, FString sound2, const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig = config.CreateAgoraData();
	std::string Sound1 = TCHAR_TO_UTF8(*sound1);
	std::string Sound2 = TCHAR_TO_UTF8(*sound2);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRhythmPlayer(Sound1.c_str(), Sound1.c_str(), agoraRhythmPlayerConfig);
	config.FreeAgoraData(agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraRtcEngine::StopRhythmPlayer()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopRhythmPlayer();
	return ret;
}
int UAgoraRtcEngine::ConfigRhythmPlayer(const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->configRhythmPlayer(agoraRhythmPlayerConfig);
	config.FreeAgoraData(agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraRtcEngine::TakeSnapshot(int64 uid, FString filePath)
{
	std::string Filepath = TCHAR_TO_UTF8(*filePath);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->takeSnapshot(uid, Filepath.c_str());
	return ret;
}
int UAgoraRtcEngine::EnableContentInspect(bool enabled, FContentInspectConfig& config)
{
	agora::media::ContentInspectConfig contentInspectConfig = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableContentInspect(enabled, contentInspectConfig);
	config.FreeAgoraData(contentInspectConfig);
	return ret;
}

int UAgoraRtcEngine::AdjustCustomAudioPublishVolume(int64 trackId, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustCustomAudioPublishVolume(trackId, volume);
	return ret;
}


int UAgoraRtcEngine::AdjustCustomAudioPlayoutVolume(int64 trackId, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustCustomAudioPlayoutVolume(trackId, volume);
	return ret;
}

int UAgoraRtcEngine::SetCloudProxy(ECLOUD_PROXY_TYPE proxyType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCloudProxy((agora::rtc::CLOUD_PROXY_TYPE)proxyType);
	return ret;
}
int UAgoraRtcEngine::SetLocalAccessPoint(const FLocalAccessPointConfiguration& config)
{
	agora::rtc::LocalAccessPointConfiguration AgoraLocalAccessPointConfiguration = config.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalAccessPoint(AgoraLocalAccessPointConfiguration);
	config.FreeAgoraData(AgoraLocalAccessPointConfiguration);
	return ret;
}
int UAgoraRtcEngine::SetAdvancedAudioOptions(const FAdvancedAudioOptions& options)
{
	agora::rtc::AdvancedAudioOptions advancedAudioOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAdvancedAudioOptions(advancedAudioOptions);
	options.FreeAgoraData(advancedAudioOptions);
	return ret;
}
int UAgoraRtcEngine::SetAVSyncSource(FString channelId, int64 uid)
{
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAVSyncSource(ChannelId.c_str(), uid);
	return ret;
}
int UAgoraRtcEngine::EnableVideoImageSource(bool enable, const FImageTrackOptions& options)
{
	agora::rtc::ImageTrackOptions imageTrackOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableVideoImageSource(enable, imageTrackOptions);
	options.FreeAgoraData(imageTrackOptions);
	return ret;
}
int UAgoraRtcEngine::JoinChannelEx(FString token, const FRtcConnection& connection, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	std::string Token = TCHAR_TO_UTF8(*token);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannelEx(Token.c_str(), rtcConnection, channelMediaOptions, eventHandler);

	connection.FreeAgoraData(rtcConnection);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}


int UAgoraRtcEngine::LeaveChannelEx(const FRtcConnection& connection, const FLeaveChannelOptions& options)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();

	agora::rtc::LeaveChannelOptions AgoraLeaveChannelOptions = options.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->leaveChannelEx(rtcConnection, AgoraLeaveChannelOptions);
	connection.FreeAgoraData(rtcConnection);
	options.FreeAgoraData(AgoraLeaveChannelOptions);
	return ret;
}

int UAgoraRtcEngine::UpdateChannelMediaOptionsEx(const FChannelMediaOptions& options, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateChannelMediaOptionsEx(channelMediaOptions, rtcConnection);

	options.FreeAgoraData(channelMediaOptions);
	connection.FreeAgoraData(rtcConnection);

	return ret;
}
int UAgoraRtcEngine::SetVideoEncoderConfigurationEx(const FVideoEncoderConfiguration& config, const FRtcConnection& connection)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateAgoraData();

	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoEncoderConfigurationEx(videoEncoderConfiguration, rtcConnection);

	config.FreeAgoraData(videoEncoderConfiguration);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetupRemoteVideoEx(const FVideoCanvas& canvas, const FRtcConnection& connection)
{
	agora::rtc::VideoCanvas videoCanvas = canvas.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setupRemoteVideoEx(videoCanvas, rtcConnection);
	canvas.FreeAgoraData(videoCanvas);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteAudioStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRemoteAudioStreamEx(uid, mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteVideoStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRemoteVideoStreamEx(uid, mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoStreamTypeEx(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FVideoSubscriptionOptions& options, const FRtcConnection& connection)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions = options.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoSubscriptionOptionsEx(uid, videoSubscriptionOptions, rtcConnection);
	options.FreeAgoraData(videoSubscriptionOptions);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVoicePositionEx(uid, pan, gain, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParamsEx(int64 uid, const FSpatialAudioParams& params, const FRtcConnection& connection)
{
	agora::SpatialAudioParams spatialAudioParams = params.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteUserSpatialAudioParamsEx(uid, spatialAudioParams, rtcConnection);
	params.FreeAgoraData(spatialAudioParams);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteRenderModeEx(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableLoopbackRecordingEx(const FRtcConnection& connection, bool enabled, FString deviceName)
{
	std::string STDDeviceName = TCHAR_TO_UTF8(*deviceName);
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableLoopbackRecordingEx(rtcConnection, enabled, STDDeviceName.c_str());
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionStateEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret= (ECONNECTION_STATE_TYPE)RtcEngineProxyClassWrapper::GetInstance()->getConnectionStateEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableEncryptionEx(const FRtcConnection& connection, bool enabled, const FEncryptionConfig& config)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::EncryptionConfig AgoraEncryptionConfig = config.CreateAgoraData();
	
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableEncryptionEx(rtcConnection, enabled, AgoraEncryptionConfig);

	connection.FreeAgoraData(rtcConnection);
	config.FreeAgoraData(AgoraEncryptionConfig);

	return ret;
}

int UAgoraRtcEngine::CreateDataStreamEx(int& streamId, const FDataStreamConfig& config, const FRtcConnection& connection)
{
	agora::rtc::DataStreamConfig dataStreamConfig = config.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->createDataStreamEx(&streamId, dataStreamConfig, rtcConnection);
	config.FreeAgoraData(dataStreamConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SendStreamMessageEx(int streamId, FString data, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendStreamMessageEx(streamId, StdStrData.c_str(), StdStrData.size(), rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::AddVideoWatermarkEx(FString watermarkUrl, const FWatermarkOptions& options, const FRtcConnection& connection)
{
	agora::rtc::WatermarkOptions watermarkOptions = options.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string STDSWatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->addVideoWatermarkEx(STDSWatermarkUrl.c_str(), watermarkOptions, rtcConnection);
	options.FreeAgoraData(watermarkOptions);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::ClearVideoWatermarkEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->clearVideoWatermarkEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SendCustomReportMessageEx(FString id, FString category, FString event, FString label, int value, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string STDID = TCHAR_TO_UTF8(*id);
	std::string STDCategory = TCHAR_TO_UTF8(*category);
	std::string STDEvent = TCHAR_TO_UTF8(*event);
	std::string STDLabel = TCHAR_TO_UTF8(*label);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendCustomReportMessageEx(STDID.c_str(),STDCategory.c_str(),STDEvent.c_str(),STDLabel.c_str(), value, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableAudioVolumeIndicationEx(interval, smooth, reportVad, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUserAccountEx(FString userAccount, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;

	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUserAccountEx(TCHAR_TO_UTF8(*userAccount), &info, rtcConnection);

	userInfo = info;

	connection.FreeAgoraData(rtcConnection);

	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUidEx(uid, &info, rtcConnection);
	
	userInfo = info;
	connection.FreeAgoraData(rtcConnection);

	return ret;
}

int UAgoraRtcEngine::EnableDualStreamModeEx(bool enabled, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableDualStreamModeEx(enabled, simulcastStreamConfig, rtcConnection);
	streamConfig.FreeAgoraData(simulcastStreamConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetDualStreamModeEx(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig AgoraSimulcastStreamConfig = streamConfig.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDualStreamModeEx(mode.GetRawValue(), AgoraSimulcastStreamConfig, rtcConnection);
	streamConfig.FreeAgoraData(AgoraSimulcastStreamConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableWirelessAccelerate(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableWirelessAccelerate(enabled);
	return ret;
}
int UAgoraRtcEngine::TakeSnapshotEx(const FRtcConnection& connection, int64 uid, FString filePath)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->takeSnapshotEx(rtcConnection, uid, FilePath.c_str());
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraRtcEngine::EnableContentInspectEx(bool enabled, const FContentInspectConfig& config, const FRtcConnection& connection)
{
	agora::media::ContentInspectConfig contentInspectConfig = config.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableContentInspectEx(enabled, contentInspectConfig, rtcConnection);
	config.FreeAgoraData(contentInspectConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteLocalAudioStreamEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteLocalVideoStreamEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteAllRemoteAudioStreamsEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteAllRemoteVideoStreamsEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraRtcEngine::SetSubscribeAudioBlocklist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t,UEuidNumber,uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeAudioBlocklist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
	return ret;
}

int UAgoraRtcEngine::SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeAudioBlocklistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraRtcEngine::SetSubscribeAudioAllowlist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeAudioAllowlist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
	return ret;
}

int UAgoraRtcEngine::SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeAudioAllowlistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraRtcEngine::SetSubscribeVideoBlocklist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeVideoBlocklist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
	return ret;
}

int UAgoraRtcEngine::SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::uid_t* data = nullptr;
	int UEuidNumber = uidList.Num();
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeVideoBlocklistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraRtcEngine::SetSubscribeVideoAllowlist(TArray<int64> uidList, int uidNumber)
{
	agora::rtc::uid_t* data = nullptr;
	int UEuidNumber = uidList.Num();
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeVideoAllowlist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
	return ret;
}

int UAgoraRtcEngine::SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::uid_t* data = nullptr;
	int UEuidNumber = uidList.Num();
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeVideoAllowlistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustUserPlaybackSignalVolumeEx(uid, volume, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartRtmpStreamWithoutTranscodingEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string Url = TCHAR_TO_UTF8(*url);
	int ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartRtmpStreamWithTranscodingEx(FString url, const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string streamUrl = TCHAR_TO_UTF8(*url);

	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithTranscodingEx(streamUrl.c_str(), liveTranscoding, rtcConnection);
	
	connection.FreeAgoraData(rtcConnection);
	transcoding.FreeAgoraData(liveTranscoding);

	return ret;
}

int UAgoraRtcEngine::UpdateRtmpTranscodingEx(const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateRtmpTranscodingEx(liveTranscoding, rtcConnection);

	transcoding.FreeAgoraData(liveTranscoding);
	connection.FreeAgoraData(rtcConnection);

	return ret;
}

int UAgoraRtcEngine::StopRtmpStreamEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string Url = TCHAR_TO_UTF8(*url);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StopChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopChannelMediaRelayEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::PauseAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseAllChannelMediaRelayEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::ResumeAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeAllChannelMediaRelayEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetParameters(FString parameters)
{
	std::string parameterstr = TCHAR_TO_UTF8(*parameters);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setParameters(parameterstr.c_str());
	return ret;
}


int UAgoraRtcEngine::SetParametersEx(const FRtcConnection& connection, const FString& parameters)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string STDParameters = TCHAR_TO_UTF8(*parameters);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setParametersEx(rtcConnection, STDParameters.c_str());
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraRtcEngine::GetCallIdEx(FString& callId, const FRtcConnection& connection)
{
	agora::util::AString CallId;
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getCallIdEx(CallId,rtcConnection);
	connection.FreeAgoraData(rtcConnection);

	callId = UTF8_TO_TCHAR(CallId->c_str());
	return ret;
}


int UAgoraRtcEngine::SendAudioMetadata(const FString& metadata, const FString& length)
{
	std::string AMetadata = TCHAR_TO_UTF8(*metadata);
	size_t ALength = FCString::Strtoui64(*length, NULL, 10);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendAudioMetadata(AMetadata.c_str(), ALength);
	return ret;
}

int UAgoraRtcEngine::SendAudioMetadataEx(const FRtcConnection& connection, const FString& metadata, const FString& length)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string AgoraMetadata = TCHAR_TO_UTF8(*metadata);
	size_t AgoraLength = FCString::Strtoui64(*length, NULL, 10);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendAudioMetadataEx(rtcConnection, AgoraMetadata.c_str(), AgoraLength);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartMediaRenderingTracing()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startMediaRenderingTracing();
	return ret;
}


int UAgoraRtcEngine::StartMediaRenderingTracingEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startMediaRenderingTracingEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::EnableInstantMediaRendering()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableInstantMediaRendering();
	return ret;
}


FString UAgoraRtcEngine::GetNtpWallTimeInMs()
{
	FString ret = FString::Printf(TEXT("%llu"), RtcEngineProxyClassWrapper::GetInstance()->getNtpWallTimeInMs());
	return ret;
}


int UAgoraRtcEngine::SetHeadphoneEQPreset(FENUMWRAP_HEADPHONE_EQUALIZER_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setHeadphoneEQPreset(preset.GetRawValue());
	return ret;
}


int UAgoraRtcEngine::SetHeadphoneEQParameters(int lowGain, int highGain)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setHeadphoneEQParameters(lowGain, highGain);
	return ret;
}


int UAgoraRtcEngine::SetEarMonitoringAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setEarMonitoringAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)((int)mode), samplesPerCall);
	return ret;
}


int64 UAgoraRtcEngine::GetCurrentMonotonicTimeInMs()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getCurrentMonotonicTimeInMs();
	return ret;
}



int UAgoraRtcEngine::RegisterExtension(FString provider, FString extension, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerExtension(Provider.c_str(), Extension.c_str(), (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}


int UAgoraRtcEngine::GetNetworkType()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getNetworkType();
	return ret;
}


bool UAgoraRtcEngine::IsFeatureAvailableOnDevice(EFeatureType type)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->isFeatureAvailableOnDevice(static_cast<agora::rtc::FeatureType>(type));
	return ret;
}

int64 UIScreenCaptureSourceList::GetCount()
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (sourceListNative != nullptr)
	{
		return sourceListNative->getCount();
	}
#endif
	return -1;
}

FScreenCaptureSourceInfo UIScreenCaptureSourceList::GetSourceInfo(int64 index)
{
	FScreenCaptureSourceInfo sourceInfo;
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (sourceListNative != nullptr)
	{
		agora::rtc::ScreenCaptureSourceInfo info = sourceListNative->getSourceInfo(index);
		sourceInfo = info;
		UE_LOG(LogTemp, Warning, TEXT("ScreenCaptureSourceType %d"), (int)info.type)
	}
#endif
	return sourceInfo;
}

void UIScreenCaptureSourceList::Release()
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (sourceListNative != nullptr)
	{
		sourceListNative->release();
		sourceListNative = nullptr;
	}
#endif
}

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
void UIScreenCaptureSourceList::SetScreenCaptureList(agora::rtc::IScreenCaptureSourceList* sourcelist)
{
	sourceListNative = sourcelist;
}
#endif


