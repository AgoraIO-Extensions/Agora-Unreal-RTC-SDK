// Copyright(c) 2024 Agora.io. All rights reserved.


#include "AgoraBPuRtcEngine.h"
#include "AgoraHeaderBase.h"

UAgoraBPuRtcEngine* UAgoraBPuRtcEngine::Instance = nullptr;

void UAgoraBPuRtcEngine::InitInstance()
{
	UserRtcEventHandler.Reset();
	UserRtcEventHandlerEx.Reset();
	UserScreenCaptureSourceList.Reset();
}

void UAgoraBPuRtcEngine::UninitInstance()
{
	UserRtcEventHandler.Reset();
	UserRtcEventHandlerEx.Reset();
	UserScreenCaptureSourceList.Reset();
}

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

void UAgoraBPuRtcEngine::GetEventHandler(EAgoraBPuEventHandlerType& HandlerType, UAgoraBPuIRtcEngineEventHandler*& EventHandler, UAgoraBPuIRtcEngineEventHandlerEx*& EventHandlerEx)
{
	HandlerType = EventHandlerType;

	if(HandlerType == EAgoraBPuEventHandlerType::EventHandler){
		EventHandler = UserRtcEventHandler.Get();
		EventHandlerEx = nullptr;
	}
	else if (HandlerType == EAgoraBPuEventHandlerType::EventHandlerEx) {
		EventHandler = nullptr;
		EventHandlerEx = UserRtcEventHandlerEx.Get();
	}
	else {
		EventHandler = nullptr;
		EventHandlerEx = nullptr;
	}
}

int UAgoraBPuRtcEngine::Initialize(const FRtcEngineContext& context)
{
	//Instance->AddToRoot();
	UserRtcEventHandler.Reset();
	UserRtcEventHandlerEx.Reset();
	EventHandlerType = EAgoraBPuEventHandlerType::None;


	AgoraUERtcEngine::RtcEngineAppType = AgoraAppType::kAppTypeUnreal;
	agora::rtc::RtcEngineContext AgoraData_Context = context.CreateAgoraData();
	
	bool bCreateExHandler = true;

	EventHandlerType = context.EventHandlerCreationType;
	if (EventHandlerType == EAgoraBPuEventHandlerType::EventHandler) {
		UserRtcEventHandler = TStrongObjectPtr<UAgoraBPuIRtcEngineEventHandler>(NewObject<UAgoraBPuIRtcEngineEventHandler>());
		AgoraData_Context.eventHandler = UserRtcEventHandler.Get();
	}
	else if (EventHandlerType == EAgoraBPuEventHandlerType::EventHandlerEx) {
		UserRtcEventHandlerEx = TStrongObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx>(NewObject<UAgoraBPuIRtcEngineEventHandlerEx>());
		AgoraData_Context.eventHandler = UserRtcEventHandlerEx.Get();
	}


	int ret = AgoraUERtcEngine::Get()->initialize(AgoraData_Context);
	context.FreeAgoraData(AgoraData_Context);

	return ret;
}

FString UAgoraBPuRtcEngine::GetVersion()
{
	return AgoraUERtcEngine::GetSDKVersion();
}

void UAgoraBPuRtcEngine::Release(bool sync /*= false*/)
{
	ClearAllEventHandlerCBExecutors();
	UninitInstance();
	RemoveFromRoot();

	AgoraUERtcEngine::Release(sync);
	Instance = nullptr;

}

int UAgoraBPuRtcEngine::JoinChannel(const FString& token, const FString& channelId, int64 uid)
{
	return AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId),"", UABT::ToUID(uid));
}

int UAgoraBPuRtcEngine::JoinChannelWithOptions(const FString& token, const FString& channelId, int64 uid, const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), UABT::ToUID(uid), channelMediaOptions);

	options.FreeAgoraData(channelMediaOptions);

	return ret;
}

int UAgoraBPuRtcEngine::LeaveChannel()
{
	return AgoraUERtcEngine::Get()->leaveChannel();
}	

int UAgoraBPuRtcEngine::LeaveChannelWithOptions(const FLeaveChannelOptions& options)
{
	agora::rtc::LeaveChannelOptions leaveChannelOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->leaveChannel(leaveChannelOptions);

	options.FreeAgoraData(leaveChannelOptions);

	return ret;

}

int UAgoraBPuRtcEngine::EnableVideo()
{
	return AgoraUERtcEngine::Get()->enableVideo();
}

int UAgoraBPuRtcEngine::DisableVideo()
{
	return AgoraUERtcEngine::Get()->disableVideo();
}

int UAgoraBPuRtcEngine::EnableAudio()
{
	return AgoraUERtcEngine::Get()->enableAudio();
}

int UAgoraBPuRtcEngine::DisableAudio()
{
	return AgoraUERtcEngine::Get()->disableAudio();
}

int UAgoraBPuRtcEngine::SetClientRole(FClientRoleOptions options, ECLIENT_ROLE_TYPE clientroletype)
{
	agora::rtc::ClientRoleOptions clientRoleOptions;
	clientRoleOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	agora::rtc::CLIENT_ROLE_TYPE roleType = (agora::rtc::CLIENT_ROLE_TYPE)clientroletype;
	auto ret = AgoraUERtcEngine::Get()->setClientRole(roleType, clientRoleOptions);
	return ret;
}

int UAgoraBPuRtcEngine::SetupLocalVideo(const FVideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	videoCanvas.uid = canvas.uid;
	videoCanvas.sourceType = (agora::rtc::VIDEO_SOURCE_TYPE)canvas.sourceType;
	auto ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	return ret;
}

int UAgoraBPuRtcEngine::SetupRemoteVideo(const FVideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	videoCanvas.renderMode = (agora::media::base::RENDER_MODE_TYPE)canvas.renderMode;
	videoCanvas.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)canvas.mirrorMode;
	videoCanvas.uid = canvas.uid;
	//videoCanvas.priv = canvas.priv;
	videoCanvas.sourceType = (agora::rtc::VIDEO_SOURCE_TYPE)canvas.sourceType;
	//videoCanvas.cropArea = canvas.cropArea;
	videoCanvas.setupMode = (agora::rtc::VIDEO_VIEW_SETUP_MODE)canvas.setupMode;
	auto ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
	return ret;
}

int UAgoraBPuRtcEngine::SetupRemoteVideoEx(const FVideoCanvas& canvas, const FRtcConnection& connection)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	videoCanvas.renderMode = (agora::media::base::RENDER_MODE_TYPE)canvas.renderMode;
	videoCanvas.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)canvas.mirrorMode;
	videoCanvas.uid = canvas.uid;
	//videoCanvas.priv = canvas.priv;
	videoCanvas.sourceType = (agora::rtc::VIDEO_SOURCE_TYPE)canvas.sourceType;
	//videoCanvas.cropArea = canvas.cropArea;
	videoCanvas.setupMode = (agora::rtc::VIDEO_VIEW_SETUP_MODE)canvas.setupMode;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	//rtcConnection.localUid = connection.localUid;
	auto ret = AgoraUERtcEngine::Get()->setupRemoteVideoEx(videoCanvas, rtcConnection);
	return ret;
}


void UAgoraBPuRtcEngine::ClearAllEventHandlerCBExecutors()
{
	if (UserRtcEventHandler.IsValid())
	{
		UserRtcEventHandler->RemoveAllBlueprintCallbackExecutors();
	}
	if (UserRtcEventHandlerEx.IsValid())
	{
		UserRtcEventHandlerEx->RemoveAllBlueprintCallbackExecutorExs();
	}
}


#pragma region RtcEngine2

FString UAgoraBPuRtcEngine::GetErrorDescription(int code)
{
	return AgoraUERtcEngine::Get()->getErrorDescription(code);
}

int UAgoraBPuRtcEngine::QueryCodecCapability(TArray<FCodecCapInfo>& codecInfo, int QuerySize /*= 10*/)
{
	agora::rtc::CodecCapInfo* codecCapInfo = new agora::rtc::CodecCapInfo[QuerySize];
	int ret = AgoraUERtcEngine::Get()->queryCodecCapability(codecCapInfo, QuerySize);

	for (int i = 0; i < QuerySize; i++) {

		codecInfo.Add(codecCapInfo[i]);
	}

	delete[] codecCapInfo;

	return ret;
}

int UAgoraBPuRtcEngine::QueryDeviceScore()
{
	return AgoraUERtcEngine::Get()->queryDeviceScore();
}

int UAgoraBPuRtcEngine::PreloadChannel(const FString& token, const FString& channelId, int64 uid)
{
	return AgoraUERtcEngine::Get()->preloadChannel(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), UABT::ToUID(uid));
}

int UAgoraBPuRtcEngine::PreloadChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount)
{
	return AgoraUERtcEngine::Get()->preloadChannelWithUserAccount(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), TCHAR_TO_UTF8(*userAccount));
}

int UAgoraBPuRtcEngine::UpdatePreloadChannelToken(const FString& token)
{
	return AgoraUERtcEngine::Get()->updatePreloadChannelToken(TCHAR_TO_UTF8(*token));
}

int UAgoraBPuRtcEngine::UpdateChannelMediaOptions(const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->updateChannelMediaOptions(channelMediaOptions);

	options.FreeAgoraData(channelMediaOptions);

	return ret;
}

int UAgoraBPuRtcEngine::RenewToken(const FString& token)
{
	return AgoraUERtcEngine::Get()->renewToken(TCHAR_TO_UTF8(*token));
}

int UAgoraBPuRtcEngine::SetChannelProfile(ECHANNEL_PROFILE_TYPE profile)
{
	return AgoraUERtcEngine::Get()->setChannelProfile((agora::CHANNEL_PROFILE_TYPE)profile);
}

int UAgoraBPuRtcEngine::StartEchoTest(const FEchoTestConfiguration& config)
{
	agora::rtc::EchoTestConfiguration echoTestConfiguration = config.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->startEchoTest(echoTestConfiguration);

	config.FreeAgoraData(echoTestConfiguration);

	return ret;
}

int UAgoraBPuRtcEngine::StopEchoTest()
{
	return AgoraUERtcEngine::Get()->stopEchoTest();
}

int UAgoraBPuRtcEngine::EnableMultiCamera(bool enabled, const FCameraCapturerConfiguration& config)
{
	int ret = AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);

#if defined(__APPLE__) && TARGET_OS_IOS
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateAgoraData();

	ret = AgoraUERtcEngine::Get()->enableMultiCamera(enabled, cameraCapturerConfiguration);

	config.FreeAgoraData(cameraCapturerConfiguration);
	
#endif

	return ret;
}

int UAgoraBPuRtcEngine::StartPreview(EVIDEO_SOURCE_TYPE sourceType /*= EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY*/)
{
	return AgoraUERtcEngine::Get()->startPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
}

int UAgoraBPuRtcEngine::StopPreview(EVIDEO_SOURCE_TYPE sourceType /*= EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY*/)
{
	return AgoraUERtcEngine::Get()->stopPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
}

int UAgoraBPuRtcEngine::StartLastmileProbeTest(const FLastmileProbeConfig& config)
{
	agora::rtc::LastmileProbeConfig lastmileProbeConfig = config.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->startLastmileProbeTest(lastmileProbeConfig);

	config.FreeAgoraData(lastmileProbeConfig);

	return ret;
}

int UAgoraBPuRtcEngine::StopLastmileProbeTest()
{
	return AgoraUERtcEngine::Get()->stopLastmileProbeTest();
}

int UAgoraBPuRtcEngine::SetVideoEncoderConfiguration(const FVideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setVideoEncoderConfiguration(videoEncoderConfiguration);

	config.FreeAgoraData(videoEncoderConfiguration);

	return ret;
}

int UAgoraBPuRtcEngine::SetBeautyEffectOptions(bool enabled, const FBeautyOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::BeautyOptions beautyOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setBeautyEffectOptions(enabled, beautyOptions, (agora::media::MEDIA_SOURCE_TYPE)type);

	options.FreeAgoraData(beautyOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetLowlightEnhanceOptions(bool enabled, const FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::LowlightEnhanceOptions lowlightEnhanceOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setLowlightEnhanceOptions(enabled, lowlightEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);

	options.FreeAgoraData(lowlightEnhanceOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetVideoDenoiserOptions(bool enabled, const FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VideoDenoiserOptions videoDenoiserOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setVideoDenoiserOptions(enabled, videoDenoiserOptions, (agora::media::MEDIA_SOURCE_TYPE)type);

	options.FreeAgoraData(videoDenoiserOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetColorEnhanceOptions(bool enabled, const FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::ColorEnhanceOptions colorEnhanceOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setColorEnhanceOptions(enabled, colorEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);

	options.FreeAgoraData(colorEnhanceOptions);

	return ret;
}

int UAgoraBPuRtcEngine::EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VirtualBackgroundSource virtualBackgroundSource = backgroundSource.CreateAgoraData();
	agora::rtc::SegmentationProperty segmentationProperty = segproperty.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->enableVirtualBackground(enabled, virtualBackgroundSource, segmentationProperty, (agora::media::MEDIA_SOURCE_TYPE)type);

	backgroundSource.FreeAgoraData(virtualBackgroundSource);
	segproperty.FreeAgoraData(segmentationProperty);

	return ret;
}

int UAgoraBPuRtcEngine::SetVideoScenario(EVIDEO_APPLICATION_SCENARIO_TYPE scenarioType)
{
	return AgoraUERtcEngine::Get()->setVideoScenario((agora::rtc::VIDEO_APPLICATION_SCENARIO_TYPE)scenarioType);
}

int UAgoraBPuRtcEngine::SetVideoQoEPreference(EVIDEO_QOE_PREFERENCE_TYPE qoePreference)
{
	return AgoraUERtcEngine::Get()->setVideoQoEPreference((agora::rtc::VIDEO_QOE_PREFERENCE_TYPE)qoePreference);
}

int UAgoraBPuRtcEngine::SetAudioProfileAndScenario(EAUDIO_PROFILE_TYPE profile /*= EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT*/, EAUDIO_SCENARIO_TYPE scenario /*= EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT*/)
{
	return AgoraUERtcEngine::Get()->setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile, (agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
}

int UAgoraBPuRtcEngine::SetAudioProfile(EAUDIO_PROFILE_TYPE profile /*= EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT*/)
{
	return AgoraUERtcEngine::Get()->setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile);
}

int UAgoraBPuRtcEngine::SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario /*= EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT*/)
{
	return AgoraUERtcEngine::Get()->setAudioScenario((agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
}

int UAgoraBPuRtcEngine::EnableLocalAudio(bool enabled)
{
	return AgoraUERtcEngine::Get()->enableLocalAudio(enabled);
}

int UAgoraBPuRtcEngine::MuteLocalAudioStream(bool mute)
{
	return AgoraUERtcEngine::Get()->muteLocalAudioStream(mute);
}

int UAgoraBPuRtcEngine::MuteAllRemoteAudioStreams(bool mute)
{
	return AgoraUERtcEngine::Get()->muteAllRemoteAudioStreams(mute);
}

int UAgoraBPuRtcEngine::SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType)
{
	return AgoraUERtcEngine::Get()->setRemoteDefaultVideoStreamType((agora::rtc::VIDEO_STREAM_TYPE)streamType);
}

int UAgoraBPuRtcEngine::MuteRemoteAudioStream(int64 uid, bool mute)
{
	return AgoraUERtcEngine::Get()->muteRemoteAudioStream(UABT::ToUID(uid), mute);
}

int UAgoraBPuRtcEngine::MuteLocalVideoStream(bool mute)
{
	return AgoraUERtcEngine::Get()->muteLocalVideoStream(mute);
}

int UAgoraBPuRtcEngine::EnableLocalVideo(bool enabled)
{
	return AgoraUERtcEngine::Get()->enableLocalVideo(enabled);
}

int UAgoraBPuRtcEngine::MuteAllRemoteVideoStreams(bool mute)
{
	return AgoraUERtcEngine::Get()->muteAllRemoteVideoStreams(mute);
}

int UAgoraBPuRtcEngine::MuteRemoteVideoStream(int64 uid, bool mute)
{
	return AgoraUERtcEngine::Get()->muteRemoteVideoStream(UABT::ToUID(uid), mute);
}

int UAgoraBPuRtcEngine::SetRemoteVideoStreamType(int64 uid, EVIDEO_STREAM_TYPE streamType)
{
	return AgoraUERtcEngine::Get()->setRemoteVideoStreamType(UABT::ToUID(uid), (agora::rtc::VIDEO_STREAM_TYPE)streamType);
}

int UAgoraBPuRtcEngine::SetRemoteVideoSubscriptionOptions(int64 uid, const FVideoSubscriptionOptions& options)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions = options.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setRemoteVideoSubscriptionOptions(UABT::ToUID(uid), videoSubscriptionOptions);

	options.FreeAgoraData(videoSubscriptionOptions);

	return ret;
}

int UAgoraBPuRtcEngine::EnableAudioVolumeIndication(int interval, int smooth, bool reportVad)
{
	return AgoraUERtcEngine::Get()->enableAudioVolumeIndication(interval, smooth, reportVad);
}

int UAgoraBPuRtcEngine::StartAudioRecording(const FAudioRecordingConfiguration& config)
{
	agora::rtc::AudioRecordingConfiguration audioRecordingConfiguration = config.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->startAudioRecording(audioRecordingConfiguration);

	config.FreeAgoraData(audioRecordingConfiguration);

	return ret;
}

int UAgoraBPuRtcEngine::StopAudioRecording()
{
	return AgoraUERtcEngine::Get()->stopAudioRecording();
}

int UAgoraBPuRtcEngine::StartAudioMixing(const FString& filePath, bool loopback, int cycle, int startPos /*= 0*/)
{
	return AgoraUERtcEngine::Get()->startAudioMixing(TCHAR_TO_UTF8(*filePath), loopback, cycle, startPos);
}

int UAgoraBPuRtcEngine::StopAudioMixing()
{
	return AgoraUERtcEngine::Get()->stopAudioMixing();
}

int UAgoraBPuRtcEngine::PauseAudioMixing()
{
	return AgoraUERtcEngine::Get()->pauseAudioMixing();
}

int UAgoraBPuRtcEngine::ResumeAudioMixing()
{
	return AgoraUERtcEngine::Get()->resumeAudioMixing();
}

int UAgoraBPuRtcEngine::SelectAudioTrack(int index)
{
	return AgoraUERtcEngine::Get()->selectAudioTrack(index);
}

int UAgoraBPuRtcEngine::GetAudioTrackCount()
{
	return AgoraUERtcEngine::Get()->getAudioTrackCount();
}

int UAgoraBPuRtcEngine::AdjustAudioMixingVolume(int volume)
{
	return AgoraUERtcEngine::Get()->adjustAudioMixingVolume(volume);
}

int UAgoraBPuRtcEngine::AdjustAudioMixingPublishVolume(int volume)
{
	return AgoraUERtcEngine::Get()->adjustAudioMixingPublishVolume(volume);
}

int UAgoraBPuRtcEngine::GetAudioMixingPublishVolume()
{
	return AgoraUERtcEngine::Get()->getAudioMixingPublishVolume();
}

int UAgoraBPuRtcEngine::AdjustAudioMixingPlayoutVolume(int volume)
{
	return AgoraUERtcEngine::Get()->adjustAudioMixingPlayoutVolume(volume);
}

int UAgoraBPuRtcEngine::GetAudioMixingPlayoutVolume()
{
	return AgoraUERtcEngine::Get()->getAudioMixingPlayoutVolume();
}

int UAgoraBPuRtcEngine::GetAudioMixingDuration()
{
	return AgoraUERtcEngine::Get()->getAudioMixingDuration();
}

int UAgoraBPuRtcEngine::GetAudioMixingCurrentPosition()
{
	return AgoraUERtcEngine::Get()->getAudioMixingCurrentPosition();
}

int UAgoraBPuRtcEngine::SetAudioMixingPosition(int pos)
{
	return AgoraUERtcEngine::Get()->setAudioMixingPosition(pos);
}

int UAgoraBPuRtcEngine::SetAudioMixingDualMonoMode(EAUDIO_MIXING_DUAL_MONO_MODE mode)
{
	return AgoraUERtcEngine::Get()->setAudioMixingDualMonoMode((agora::media::AUDIO_MIXING_DUAL_MONO_MODE)mode);
}

int UAgoraBPuRtcEngine::SetAudioMixingPitch(int pitch)
{
	return AgoraUERtcEngine::Get()->setAudioMixingPitch(pitch);
}

int UAgoraBPuRtcEngine::SetAudioMixingPlaybackSpeed(int speed)
{
	return AgoraUERtcEngine::Get()->setAudioMixingPlaybackSpeed(speed);
}

int UAgoraBPuRtcEngine::GetEffectsVolume()
{
	return AgoraUERtcEngine::Get()->getEffectsVolume();
}

int UAgoraBPuRtcEngine::SetEffectsVolume(int volume)
{
	return AgoraUERtcEngine::Get()->setEffectsVolume(volume);
}

int UAgoraBPuRtcEngine::PreloadEffect(int soundId, const FString& filePath, int startPos)
{
	return AgoraUERtcEngine::Get()->preloadEffect(soundId, TCHAR_TO_UTF8(*filePath), startPos);
}

int UAgoraBPuRtcEngine::PlayEffect(int soundId, const FString& filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos)
{
	return AgoraUERtcEngine::Get()->playEffect(soundId, TCHAR_TO_UTF8(*filePath), loopCount, pitch, pan, gain, publish, startPos);
}

int UAgoraBPuRtcEngine::PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish)
{
	return AgoraUERtcEngine::Get()->playAllEffects(loopCount, pitch, pan, gain, publish);
}

int UAgoraBPuRtcEngine::GetVolumeOfEffect(int soundId)
{
	return AgoraUERtcEngine::Get()->getVolumeOfEffect(soundId);
}

int UAgoraBPuRtcEngine::SetVolumeOfEffect(int soundId, int volume)
{
	return AgoraUERtcEngine::Get()->setVolumeOfEffect(soundId, volume);
}

int UAgoraBPuRtcEngine::PauseEffect(int soundId)
{
	return AgoraUERtcEngine::Get()->pauseEffect(soundId);
}

int UAgoraBPuRtcEngine::PauseAllEffects()
{
	return AgoraUERtcEngine::Get()->pauseAllEffects();
}

int UAgoraBPuRtcEngine::ResumeEffect(int soundId)
{
	return AgoraUERtcEngine::Get()->resumeEffect(soundId);
}

int UAgoraBPuRtcEngine::ResumeAllEffects()
{
	return AgoraUERtcEngine::Get()->resumeAllEffects();
}

int UAgoraBPuRtcEngine::StopEffect(int soundId)
{
	return AgoraUERtcEngine::Get()->stopEffect(soundId);
}

int UAgoraBPuRtcEngine::StopAllEffects()
{
	return AgoraUERtcEngine::Get()->stopAllEffects();
}

int UAgoraBPuRtcEngine::UnloadEffect(int soundId)
{
	return AgoraUERtcEngine::Get()->unloadEffect(soundId);
}

int UAgoraBPuRtcEngine::UnloadAllEffects()
{
	return AgoraUERtcEngine::Get()->unloadAllEffects();
}

int UAgoraBPuRtcEngine::GetEffectDuration(const FString& filePath)
{
	return AgoraUERtcEngine::Get()->getEffectDuration(TCHAR_TO_UTF8(*filePath));
}

int UAgoraBPuRtcEngine::SetEffectPosition(int soundId, int pos)
{
	return AgoraUERtcEngine::Get()->setEffectPosition(soundId, pos);
}

int UAgoraBPuRtcEngine::GetEffectCurrentPosition(int soundId)
{
	return AgoraUERtcEngine::Get()->getEffectCurrentPosition(soundId);
}

int UAgoraBPuRtcEngine::EnableSoundPositionIndication(bool enabled)
{
	return AgoraUERtcEngine::Get()->enableSoundPositionIndication(enabled);
}

int UAgoraBPuRtcEngine::SetRemoteVoicePosition(int64 uid, float pan, float gain)
{
	return AgoraUERtcEngine::Get()->setRemoteVoicePosition(UABT::ToUID(uid), pan, gain);
}

int UAgoraBPuRtcEngine::EnableSpatialAudio(bool enabled)
{
	return AgoraUERtcEngine::Get()->enableSpatialAudio(enabled);
}

int UAgoraBPuRtcEngine::SetRemoteUserSpatialAudioParams(int64 uid, const FSpatialAudioParams& params)
{
	agora::SpatialAudioParams spatialAudioParams = params.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setRemoteUserSpatialAudioParams(UABT::ToUID(uid), spatialAudioParams);

	params.FreeAgoraData(spatialAudioParams);

	return ret;
}

int UAgoraBPuRtcEngine::SetVoiceBeautifierPreset(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset)
{
	return AgoraUERtcEngine::Get()->setVoiceBeautifierPreset(preset.GetRawValue());
}

int UAgoraBPuRtcEngine::SetAudioEffectPreset(FENUMWRAP_AUDIO_EFFECT_PRESET preset)
{
	return AgoraUERtcEngine::Get()->setAudioEffectPreset(preset.GetRawValue());
}

int UAgoraBPuRtcEngine::SetVoiceConversionPreset(FENUMWRAP_VOICE_CONVERSION_PRESET preset)
{
	return AgoraUERtcEngine::Get()->setVoiceConversionPreset(preset.GetRawValue());
}

int UAgoraBPuRtcEngine::SetAudioEffectParameters(FENUMWRAP_AUDIO_EFFECT_PRESET preset, int param1, int param2)
{
	return AgoraUERtcEngine::Get()->setAudioEffectParameters(preset.GetRawValue(), param1, param2);
}

int UAgoraBPuRtcEngine::SetVoiceBeautifierParameters(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset, int param1, int param2)
{
	return AgoraUERtcEngine::Get()->setVoiceBeautifierParameters(preset.GetRawValue(), param1, param2);
}

int UAgoraBPuRtcEngine::SetVoiceConversionParameters(FENUMWRAP_VOICE_CONVERSION_PRESET preset, int param1, int param2)
{
	return AgoraUERtcEngine::Get()->setVoiceConversionParameters(preset.GetRawValue(), param1, param2);
}

int UAgoraBPuRtcEngine::SetLocalVoicePitch(float pitch)
{
	return AgoraUERtcEngine::Get()->setLocalVoicePitch(pitch);
}

int UAgoraBPuRtcEngine::SetLocalVoiceFormant(const FString& formantRatio /*= "0.0"*/)
{
	return AgoraUERtcEngine::Get()->setLocalVoiceFormant(UABT::ToDouble(formantRatio));
}

int UAgoraBPuRtcEngine::SetLocalVoiceEqualization(EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
{
	return AgoraUERtcEngine::Get()->setLocalVoiceEqualization((agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY)bandFrequency, bandGain);
}

int UAgoraBPuRtcEngine::SetLocalVoiceReverb(EAUDIO_REVERB_TYPE reverbKey, int value)
{
	return AgoraUERtcEngine::Get()->setLocalVoiceReverb((agora::rtc::AUDIO_REVERB_TYPE)reverbKey, value);
}

int UAgoraBPuRtcEngine::SetLogFile(const FString& filePath)
{
	return AgoraUERtcEngine::Get()->setLogFile(TCHAR_TO_UTF8(*filePath));
}

int UAgoraBPuRtcEngine::SetLogFilter(int filter)
{
	return AgoraUERtcEngine::Get()->setLogFilter(filter);
}

int UAgoraBPuRtcEngine::SetLogLevel(ELOG_LEVEL level)
{
	return AgoraUERtcEngine::Get()->setLogLevel((agora::commons::LOG_LEVEL)level);
}

int UAgoraBPuRtcEngine::SetLogFileSize(int fileSizeInKBytes)
{
	return AgoraUERtcEngine::Get()->setLogFileSize(fileSizeInKBytes);
}

int UAgoraBPuRtcEngine::UploadLogFile(FString& requestId)
{
	agora::util::AString _requestId;
	auto ret = AgoraUERtcEngine::Get()->uploadLogFile(_requestId);
	requestId = UTF8_TO_TCHAR(_requestId->c_str());
	return ret;
}

int UAgoraBPuRtcEngine::WriteLog(ELOG_LEVEL level, const FString& Content)
{
	return AgoraUERtcEngine::Get()->writeLog((agora::commons::LOG_LEVEL)level, TCHAR_TO_UTF8(*Content));
}

int UAgoraBPuRtcEngine::SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode /*= EVIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO*/)
{
	return AgoraUERtcEngine::Get()->setLocalRenderMode((agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
}

int UAgoraBPuRtcEngine::SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return AgoraUERtcEngine::Get()->setRemoteRenderMode(UABT::ToUID(uid), (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
}

int UAgoraBPuRtcEngine::SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return AgoraUERtcEngine::Get()->setLocalVideoMirrorMode((agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
}

int UAgoraBPuRtcEngine::EnableDualStreamMode(bool enabled, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->enableDualStreamMode(enabled, simulcastStreamConfig);

	streamConfig.FreeAgoraData(simulcastStreamConfig);

	return ret;
}

int UAgoraBPuRtcEngine::SetDualStreamMode(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setDualStreamMode(mode.GetRawValue(), simulcastStreamConfig);

	streamConfig.FreeAgoraData(simulcastStreamConfig);

	return ret;
}

int UAgoraBPuRtcEngine::EnableCustomAudioLocalPlayback(int64 trackId, bool enabled)
{
	return AgoraUERtcEngine::Get()->enableCustomAudioLocalPlayback(UABT::ToUID(trackId), enabled);
}

int UAgoraBPuRtcEngine::SetRecordingAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	return AgoraUERtcEngine::Get()->setRecordingAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}

int UAgoraBPuRtcEngine::SetPlaybackAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	return AgoraUERtcEngine::Get()->setPlaybackAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}

int UAgoraBPuRtcEngine::SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall)
{
	return AgoraUERtcEngine::Get()->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
}

int UAgoraBPuRtcEngine::SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel)
{
	return AgoraUERtcEngine::Get()->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
}

int UAgoraBPuRtcEngine::EnableAudioSpectrumMonitor(int intervalInMS)
{
	return AgoraUERtcEngine::Get()->enableAudioSpectrumMonitor(intervalInMS);
}

int UAgoraBPuRtcEngine::DisableAudioSpectrumMonitor()
{
	return AgoraUERtcEngine::Get()->disableAudioSpectrumMonitor();
}

int UAgoraBPuRtcEngine::AdjustRecordingSignalVolume(int volume)
{
	return AgoraUERtcEngine::Get()->adjustRecordingSignalVolume(volume);
}

int UAgoraBPuRtcEngine::MuteRecordingSignal(bool mute)
{
	return AgoraUERtcEngine::Get()->muteRecordingSignal(mute);
}

int UAgoraBPuRtcEngine::AdjustPlaybackSignalVolume(int volume)
{
	return AgoraUERtcEngine::Get()->adjustPlaybackSignalVolume(volume);
}	

int UAgoraBPuRtcEngine::AdjustUserPlaybackSignalVolume(int64 uid, int volume)
{
	return AgoraUERtcEngine::Get()->adjustUserPlaybackSignalVolume(UABT::ToUID(uid), volume);
}

int UAgoraBPuRtcEngine::SetLocalPublishFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	return AgoraUERtcEngine::Get()->setLocalPublishFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
}

int UAgoraBPuRtcEngine::SetRemoteSubscribeFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	return AgoraUERtcEngine::Get()->setRemoteSubscribeFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
}

int UAgoraBPuRtcEngine::SetHighPriorityUserList(const TArray<int64>& uidList, ESTREAM_FALLBACK_OPTIONS option)
{
	int vNum = uidList.Num();
	agora::rtc::uid_t* uidListVec = new agora::rtc::uid_t[vNum];
	for (int i = 0; i < vNum; i++) {
		uidListVec[i] = UABT::ToUID(uidList[i]);
	}

	int ret =  AgoraUERtcEngine::Get()->setHighPriorityUserList(uidListVec, vNum,(agora::rtc::STREAM_FALLBACK_OPTIONS)option);

	delete[] uidListVec;

	return ret;
}

int UAgoraBPuRtcEngine::EnableLoopbackRecording(bool enabled, const FString& deviceName)
{
	return AgoraUERtcEngine::Get()->enableLoopbackRecording(enabled, TCHAR_TO_UTF8(*deviceName));
}

int UAgoraBPuRtcEngine::AdjustLoopbackSignalVolume(int volume)
{
	return AgoraUERtcEngine::Get()->adjustLoopbackSignalVolume(volume);
}

int UAgoraBPuRtcEngine::GetLoopbackRecordingVolume()
{
	return AgoraUERtcEngine::Get()->getLoopbackRecordingVolume();
}

int UAgoraBPuRtcEngine::EnableInEarMonitoring(bool enabled, int includeAudioFilters)
{
	return AgoraUERtcEngine::Get()->enableInEarMonitoring(enabled, includeAudioFilters);
}

int UAgoraBPuRtcEngine::SetInEarMonitoringVolume(int volume)
{
	return AgoraUERtcEngine::Get()->setInEarMonitoringVolume(volume);
}

int UAgoraBPuRtcEngine::LoadExtensionProvider(const FString& path, bool unload_after_use)
{
	int ret = AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);

#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
	ret = AgoraUERtcEngine::Get()->loadExtensionProvider(TCHAR_TO_UTF8(*path), unload_after_use);
#endif
	return ret;
}

int UAgoraBPuRtcEngine::SetExtensionProviderProperty(const FString& provider, const FString& key, const FString& value)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Key = TCHAR_TO_UTF8(*key);
	std::string Value = TCHAR_TO_UTF8(*value);
	auto ret = AgoraUERtcEngine::Get()->setExtensionProviderProperty(Provider.c_str(), Key.c_str(), Value.c_str());
	return ret;
}

int UAgoraBPuRtcEngine::EnableExtension(const FString& provider, const FString& extension, bool enable /*= true*/, EMEDIA_SOURCE_TYPE type /*= EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE*/)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	auto ret = AgoraUERtcEngine::Get()->enableExtension(Provider.c_str(), Extension.c_str(), enable, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}

int UAgoraBPuRtcEngine::SetExtensionProperty(const FString& provider, const FString& extension, const FString& key, const FString& value, EMEDIA_SOURCE_TYPE type /*= EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE*/)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	std::string Key = TCHAR_TO_UTF8(*key);
	std::string Value = TCHAR_TO_UTF8(*value);
	auto ret = AgoraUERtcEngine::Get()->setExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), Value.c_str(), (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}

int UAgoraBPuRtcEngine::GetExtensionProperty(const FString& provider, const FString& extension, const FExtensionInfo& ExtensionInfo, const FString& key, FString& value)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	std::string Key = TCHAR_TO_UTF8(*key);

	agora::rtc::ExtensionInfo vextensionInfo = ExtensionInfo.CreateAgoraData();

	int BufLen = 512;
	char* ValPtr = new char[BufLen];

	auto ret = AgoraUERtcEngine::Get()->getExtensionProperty(Provider.c_str(), Extension.c_str(), vextensionInfo, Key.c_str(), ValPtr, BufLen);

	value = UTF8_TO_TCHAR(ValPtr);
	delete[] ValPtr;

	ExtensionInfo.FreeAgoraData(vextensionInfo);

	return ret;
}

int UAgoraBPuRtcEngine::SetCameraCapturerConfiguration(const FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateAgoraData();

	int ret = AgoraUERtcEngine::Get()->setCameraCapturerConfiguration(cameraCapturerConfiguration);

	config.FreeAgoraData(cameraCapturerConfiguration);

	return ret;
}

int64 UAgoraBPuRtcEngine::CreateCustomVideoTrack()
{
	return AgoraUERtcEngine::Get()->createCustomVideoTrack();
}

int64 UAgoraBPuRtcEngine::CreateCustomEncodedVideoTrack(const FSenderOptions& sender_option)
{
	agora::rtc::SenderOptions senderOptions = sender_option.CreateAgoraData();

	int64 ret = AgoraUERtcEngine::Get()->createCustomEncodedVideoTrack(senderOptions);

	sender_option.FreeAgoraData(senderOptions);

	return ret;
}

int UAgoraBPuRtcEngine::DestroyCustomVideoTrack(int64 video_track_id)
{
	auto ret = AgoraUERtcEngine::Get()->destroyCustomVideoTrack(UABT::ToVTID(video_track_id));

	return ret;
}

int UAgoraBPuRtcEngine::DestroyCustomEncodedVideoTrack(int64 video_track_id)
{
	auto ret = AgoraUERtcEngine::Get()->destroyCustomEncodedVideoTrack(UABT::ToVTID(video_track_id));

	return ret;
}

int UAgoraBPuRtcEngine::SwitchCamera()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->switchCamera();
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
bool UAgoraBPuRtcEngine::IsCameraZoomSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraZoomSupported();
	return ret;
#else
	return false;
#endif
}
bool UAgoraBPuRtcEngine::IsCameraFaceDetectSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraFaceDetectSupported();
	return ret;
#else
	return false;
#endif
}
bool UAgoraBPuRtcEngine::IsCameraTorchSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraTorchSupported();
	return ret;
#else
	return false;
#endif
}
bool UAgoraBPuRtcEngine::IsCameraFocusSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraFocusSupported();
	return ret;
#else
	return false;
#endif
}
bool UAgoraBPuRtcEngine::IsCameraAutoFocusFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraAutoFocusFaceModeSupported();
	return ret;
#else
	return false;
#endif
}
int UAgoraBPuRtcEngine::SetCameraZoomFactor(float factor)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->setCameraZoomFactor(factor);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::EnableFaceDetection(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->enableFaceDetection(enabled);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
float UAgoraBPuRtcEngine::GetCameraMaxZoomFactor()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->getCameraMaxZoomFactor();
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::SetCameraFocusPositionInPreview(float positionX, float positionY)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->setCameraFocusPositionInPreview(positionX, positionY);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::SetCameraTorchOn(bool isOn)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->setCameraTorchOn(isOn);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::SetCameraAutoFocusFaceModeEnabled(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->setCameraAutoFocusFaceModeEnabled(enabled);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
bool UAgoraBPuRtcEngine::IsCameraExposurePositionSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraExposurePositionSupported();
	return ret;
#else
	return false;
#endif
}
int UAgoraBPuRtcEngine::SetCameraExposurePosition(float positionXinView, float positionYinView)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->setCameraExposurePosition(positionXinView, positionYinView);
	return ret;
#else
	return  AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}


bool UAgoraBPuRtcEngine::IsCameraExposureSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->isCameraExposureSupported();
	return ret;
#else
	return false;
#endif
}


int UAgoraBPuRtcEngine::SetCameraExposureFactor(float factor)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->setCameraExposureFactor(factor);
	return ret;
#else
	return  AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

bool UAgoraBPuRtcEngine::IsCameraAutoExposureFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	auto ret= AgoraUERtcEngine::Get()->isCameraAutoExposureFaceModeSupported();
	return ret;
#else
	return false;
#endif
#endif
	return false;
}
int UAgoraBPuRtcEngine::SetCameraAutoExposureFaceModeEnabled(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	auto ret = AgoraUERtcEngine::Get()->setCameraAutoExposureFaceModeEnabled(enabled);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
#endif
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
}

int UAgoraBPuRtcEngine::SetCameraStabilizationMode(FENUMWRAP_CAMERA_STABILIZATION_MODE mode)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	auto ret =  AgoraUERtcEngine::Get()->setCameraStabilizationMode(mode.GetRawValue());
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
#endif
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
}

int UAgoraBPuRtcEngine::SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker)
{
#if defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::SetEnableSpeakerphone(bool speakerOn)
{
#if defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->setEnableSpeakerphone(speakerOn);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
bool UAgoraBPuRtcEngine::IsSpeakerphoneEnabled()
{
#if defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->isSpeakerphoneEnabled();
	return ret;
#else
	return false;
#endif
}


int UAgoraBPuRtcEngine::SetRouteInCommunicationMode(int route)
{
#if defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->setRouteInCommunicationMode(route);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

bool UAgoraBPuRtcEngine::IsCameraCenterStageSupported()
{
#if defined(__APPLE__)
	auto ret = AgoraUERtcEngine::Get()->isCameraCenterStageSupported();
	return ret;
#else
	return false;
#endif
}

int UAgoraBPuRtcEngine::EnableCameraCenterStage(bool enabled)
{
#if defined(__APPLE__)
	auto ret = AgoraUERtcEngine::Get()->enableCameraCenterStage(enabled);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::QueryCameraFocalLengthCapability(const TArray<FFocalLengthInfo>& focalLengthInfos)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)

	int TotalSize = focalLengthInfos.Num();
	agora::rtc::FocalLengthInfo* focalLengthInfo = nullptr;
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(focalLengthInfo, agora::rtc::FocalLengthInfo, TotalSize, focalLengthInfos)
		auto ret = AgoraUERtcEngine::Get()->queryCameraFocalLengthCapability(focalLengthInfo, TotalSize);
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(focalLengthInfo, TotalSize, FFocalLengthInfo)
		return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario)
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->setScreenCaptureScenario((agora::rtc::SCREEN_SCENARIO_TYPE)screenScenario);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::UpdateScreenCapture(const FScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2 = captureParams.CreateAgoraData();
	int ret = AgoraUERtcEngine::Get()->updateScreenCapture(screenCaptureParameters2);
	captureParams.FreeAgoraData(screenCaptureParameters2);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::StopScreenCapture()
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->stopScreenCapture();
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::GetCallId(FString& callId)
{
	agora::util::AString agoraStr;

	auto ret = AgoraUERtcEngine::Get()->getCallId(agoraStr);

	callId = UTF8_TO_TCHAR(agoraStr->c_str());

	return ret;
}
int UAgoraBPuRtcEngine::Rate(const FString& callId, int rating, const FString& description)
{
	std::string CallId = TCHAR_TO_UTF8(*callId);
	auto ret = AgoraUERtcEngine::Get()->rate(CallId.c_str(), rating, TCHAR_TO_UTF8(*description));
	return ret;
}
int UAgoraBPuRtcEngine::Complain(const FString& callId, const FString& description)
{
	std::string CallId = TCHAR_TO_UTF8(*callId);
	std::string Description = TCHAR_TO_UTF8(*description);
	auto ret = AgoraUERtcEngine::Get()->complain(CallId.c_str(), Description.c_str());
	return ret;
}
int UAgoraBPuRtcEngine::StartRtmpStreamWithoutTranscoding(const FString& url)
{
	std::string Url = TCHAR_TO_UTF8(*url);

	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithoutTranscoding(Url.c_str());
	return ret;
}
int UAgoraBPuRtcEngine::StartRtmpStreamWithTranscoding(const FString& url, const FLiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();
	std::string TempUrl = TCHAR_TO_UTF8(*url);
	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithTranscoding(TempUrl.c_str(), liveTranscoding);
	transcoding.FreeAgoraData(liveTranscoding);
	return ret;
}
int UAgoraBPuRtcEngine::UpdateRtmpTranscoding(const FLiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->updateRtmpTranscoding(liveTranscoding);
	transcoding.FreeAgoraData(liveTranscoding);

	return ret;
}
int UAgoraBPuRtcEngine::StopRtmpStream(const FString& url)
{
	auto ret = AgoraUERtcEngine::Get()->stopRtmpStream(TCHAR_TO_UTF8(*url));
	return ret;
}

int UAgoraBPuRtcEngine::StartCameraCapture(EVIDEO_SOURCE_TYPE sourceType, const FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startCameraCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType, cameraCapturerConfiguration);

	config.FreeAgoraData(cameraCapturerConfiguration);
	return ret;
}


int UAgoraBPuRtcEngine::StopCameraCapture(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = AgoraUERtcEngine::Get()->stopCameraCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}

int UAgoraBPuRtcEngine::StartLocalVideoTranscoder(const FLocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration AgoraLocalTranscoderConfiguration = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startLocalVideoTranscoder(AgoraLocalTranscoderConfiguration);
	config.FreeAgoraData(AgoraLocalTranscoderConfiguration);
	return ret;
}
int UAgoraBPuRtcEngine::UpdateLocalTranscoderConfiguration(const FLocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration AgoraLocalTranscoderConfiguration = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->updateLocalTranscoderConfiguration(AgoraLocalTranscoderConfiguration);
	config.FreeAgoraData(AgoraLocalTranscoderConfiguration);
	return ret;
}
int UAgoraBPuRtcEngine::StopLocalVideoTranscoder()
{
	auto ret = AgoraUERtcEngine::Get()->stopLocalVideoTranscoder();
	return ret;
}

int UAgoraBPuRtcEngine::SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation)
{
	auto ret = AgoraUERtcEngine::Get()->setCameraDeviceOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, orientation.GetRawValue());
	return ret;
}
int UAgoraBPuRtcEngine::SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation)
{
	auto ret = AgoraUERtcEngine::Get()->setScreenCaptureOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, orientation.GetRawValue());
	return ret;
}

ECONNECTION_STATE_TYPE UAgoraBPuRtcEngine::GetConnectionState()
{
	return (ECONNECTION_STATE_TYPE)AgoraUERtcEngine::Get()->getConnectionState();
}


int UAgoraBPuRtcEngine::SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteUserPriority(uid, (agora::rtc::PRIORITY_TYPE)userPriority);
	return ret;
}

int UAgoraBPuRtcEngine::EnableEncryption(bool enabled, const FEncryptionConfig& config)
{
	agora::rtc::EncryptionConfig AgoraEncryptionConfig = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableEncryption(enabled, AgoraEncryptionConfig);
	config.FreeAgoraData(AgoraEncryptionConfig);
	return ret;
}
int UAgoraBPuRtcEngine::CreateDataStream(int& streamId, const FDataStreamConfig& config)
{
	agora::rtc::DataStreamConfig dataStreamConfig = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->createDataStream(&streamId, dataStreamConfig);
	config.FreeAgoraData(dataStreamConfig);
	return ret;
}
int UAgoraBPuRtcEngine::SendStreamMessage(int streamId, const FString& data)
{
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	const char* Data = StdStrData.c_str();

	auto ret = AgoraUERtcEngine::Get()->sendStreamMessage(streamId, Data, strlen(Data) + 1);
	return ret;
}
int UAgoraBPuRtcEngine::AddVideoWatermark(const FString& watermarkUrl, const FWatermarkOptions& options)
{
	std::string STDWatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	agora::rtc::WatermarkOptions watermarkOptions = options.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->addVideoWatermark(STDWatermarkUrl.c_str(), watermarkOptions);
	options.FreeAgoraData(watermarkOptions);
	return ret;
}

int UAgoraBPuRtcEngine::ClearVideoWatermarks()
{
	auto ret = AgoraUERtcEngine::Get()->clearVideoWatermarks();
	return ret;
}

int UAgoraBPuRtcEngine::PauseAudio()
{
	auto ret = AgoraUERtcEngine::Get()->pauseAudio();
	return ret;
}
int UAgoraBPuRtcEngine::ResumeAudio()
{
	auto ret = AgoraUERtcEngine::Get()->resumeAudio();
	return ret;
}
int UAgoraBPuRtcEngine::EnableWebSdkInteroperability(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableWebSdkInteroperability(enabled);
	return ret;
}
int UAgoraBPuRtcEngine::SendCustomReportMessage(const FString& id, const FString& category, const FString& event, const FString& label, int value)
{
	std::string Id = TCHAR_TO_UTF8(*id);
	std::string Category = TCHAR_TO_UTF8(*category);
	std::string Event = TCHAR_TO_UTF8(*event);
	std::string Label = TCHAR_TO_UTF8(*label);
	auto ret = AgoraUERtcEngine::Get()->sendCustomReportMessage(Id.c_str(), Category.c_str(), Event.c_str(), Label.c_str(), value);
	return ret;
}

int UAgoraBPuRtcEngine::StartAudioFrameDump(const FString& channel_id, int64 uid, const FString& location, const FString& uuid, const FString& passwd, int64 duration_ms, bool auto_upload)
{
	std::string Channel_id = TCHAR_TO_UTF8(*channel_id);
	std::string Location = TCHAR_TO_UTF8(*location);
	std::string Uuid = TCHAR_TO_UTF8(*uuid);
	std::string Passwd = TCHAR_TO_UTF8(*passwd);
	auto ret = AgoraUERtcEngine::Get()->startAudioFrameDump(Channel_id.c_str(), uid, Location.c_str(), Uuid.c_str(), Passwd.c_str(), duration_ms, auto_upload);
	return ret;
}


int UAgoraBPuRtcEngine::StopAudioFrameDump(const FString& channel_id, int64 uid, const FString& location)
{
	std::string Channel_id = TCHAR_TO_UTF8(*channel_id);
	std::string Location = TCHAR_TO_UTF8(*location);
	auto ret = AgoraUERtcEngine::Get()->stopAudioFrameDump(Channel_id.c_str(), uid, Location.c_str());
	return ret;
}

int UAgoraBPuRtcEngine::SetAINSMode(bool enabled, EAUDIO_AINS_MODE mode)
{
	auto ret = AgoraUERtcEngine::Get()->setAINSMode(enabled, (agora::rtc::AUDIO_AINS_MODE)mode);
	return ret;
}

int UAgoraBPuRtcEngine::RegisterLocalUserAccount(const FString& appId, const FString& userAccount)
{
	std::string AppId = TCHAR_TO_UTF8(*appId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->registerLocalUserAccount(AppId.c_str(), UserAccount.c_str());
	return ret;
}
int UAgoraBPuRtcEngine::JoinChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount, const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->joinChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}

int UAgoraBPuRtcEngine::JoinChannelWithUserAccountEx(const FString& token, const FString& channelId, const FString& userAccount, const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->joinChannelWithUserAccountEx(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions, nullptr);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUserAccount(const FString& userAccount,FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUserAccount(UserAccount.c_str(), &info);
	userInfo = info;
	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUid(int64 uid, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUid(uid, &info);
	userInfo = info;
	return ret;
}


int UAgoraBPuRtcEngine::StartOrUpdateChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration = configuration.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startOrUpdateChannelMediaRelay(channelMediaRelayConfiguration);
	configuration.FreeAgoraData(channelMediaRelayConfiguration);
	return ret;
}


int UAgoraBPuRtcEngine::StartOrUpdateChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration = configuration.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startOrUpdateChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	configuration.FreeAgoraData(channelMediaRelayConfiguration);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::StopChannelMediaRelay()
{
	auto ret = AgoraUERtcEngine::Get()->stopChannelMediaRelay();
	return ret;
}
int UAgoraBPuRtcEngine::PauseAllChannelMediaRelay()
{
	auto ret = AgoraUERtcEngine::Get()->pauseAllChannelMediaRelay();
	return ret;
}
int UAgoraBPuRtcEngine::ResumeAllChannelMediaRelay()
{
	auto ret = AgoraUERtcEngine::Get()->resumeAllChannelMediaRelay();
	return ret;
}
int UAgoraBPuRtcEngine::SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile)
{
	auto ret = AgoraUERtcEngine::Get()->setDirectCdnStreamingAudioConfiguration((agora::rtc::AUDIO_PROFILE_TYPE)profile);
	return ret;
}
int UAgoraBPuRtcEngine::SetDirectCdnStreamingVideoConfiguration(const FVideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setDirectCdnStreamingVideoConfiguration(videoEncoderConfiguration);
	config.FreeAgoraData(videoEncoderConfiguration);
	return ret;
}

int UAgoraBPuRtcEngine::StartRhythmPlayer(const FString& sound1, const FString& sound2, const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig = config.CreateAgoraData();
	std::string Sound1 = TCHAR_TO_UTF8(*sound1);
	std::string Sound2 = TCHAR_TO_UTF8(*sound2);
	auto ret = AgoraUERtcEngine::Get()->startRhythmPlayer(Sound1.c_str(), Sound1.c_str(), agoraRhythmPlayerConfig);
	config.FreeAgoraData(agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraBPuRtcEngine::StopRhythmPlayer()
{
	auto ret = AgoraUERtcEngine::Get()->stopRhythmPlayer();
	return ret;
}
int UAgoraBPuRtcEngine::ConfigRhythmPlayer(const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->configRhythmPlayer(agoraRhythmPlayerConfig);
	config.FreeAgoraData(agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraBPuRtcEngine::TakeSnapshot(int64 uid, const FString& filePath)
{
	std::string Filepath = TCHAR_TO_UTF8(*filePath);

	auto ret = AgoraUERtcEngine::Get()->takeSnapshot(uid, Filepath.c_str());
	return ret;
}
int UAgoraBPuRtcEngine::EnableContentInspect(bool enabled, const FContentInspectConfig& config)
{
	agora::media::ContentInspectConfig contentInspectConfig = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableContentInspect(enabled, contentInspectConfig);
	config.FreeAgoraData(contentInspectConfig);
	return ret;
}

int UAgoraBPuRtcEngine::AdjustCustomAudioPublishVolume(int64 trackId, int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustCustomAudioPublishVolume(trackId, volume);
	return ret;
}


int UAgoraBPuRtcEngine::AdjustCustomAudioPlayoutVolume(int64 trackId, int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustCustomAudioPlayoutVolume(trackId, volume);
	return ret;
}

int UAgoraBPuRtcEngine::SetCloudProxy(ECLOUD_PROXY_TYPE proxyType)
{
	auto ret = AgoraUERtcEngine::Get()->setCloudProxy((agora::rtc::CLOUD_PROXY_TYPE)proxyType);
	return ret;
}
int UAgoraBPuRtcEngine::SetLocalAccessPoint(const FLocalAccessPointConfiguration& config)
{
	agora::rtc::LocalAccessPointConfiguration AgoraLocalAccessPointConfiguration = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setLocalAccessPoint(AgoraLocalAccessPointConfiguration);
	config.FreeAgoraData(AgoraLocalAccessPointConfiguration);
	return ret;
}
int UAgoraBPuRtcEngine::SetAdvancedAudioOptions(const FAdvancedAudioOptions& options)
{
	agora::rtc::AdvancedAudioOptions advancedAudioOptions = options.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setAdvancedAudioOptions(advancedAudioOptions);
	options.FreeAgoraData(advancedAudioOptions);
	return ret;
}
int UAgoraBPuRtcEngine::SetAVSyncSource(const FString& channelId, int64 uid)
{
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = AgoraUERtcEngine::Get()->setAVSyncSource(ChannelId.c_str(), uid);
	return ret;
}
int UAgoraBPuRtcEngine::EnableVideoImageSource(bool enable, const FImageTrackOptions& options)
{
	agora::rtc::ImageTrackOptions imageTrackOptions = options.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableVideoImageSource(enable, imageTrackOptions);
	options.FreeAgoraData(imageTrackOptions);
	return ret;
}
int UAgoraBPuRtcEngine::JoinChannelEx(const FString& token, const FRtcConnection& connection, const FChannelMediaOptions& options)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	std::string Token = TCHAR_TO_UTF8(*token);

	auto ret = AgoraUERtcEngine::Get()->joinChannelEx(Token.c_str(), rtcConnection, channelMediaOptions, nullptr);

	connection.FreeAgoraData(rtcConnection);
	options.FreeAgoraData(channelMediaOptions);
	return ret;
}


int UAgoraBPuRtcEngine::LeaveChannelEx(const FRtcConnection& connection, const FLeaveChannelOptions& options)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();

	agora::rtc::LeaveChannelOptions AgoraLeaveChannelOptions = options.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->leaveChannelEx(rtcConnection, AgoraLeaveChannelOptions);
	connection.FreeAgoraData(rtcConnection);
	options.FreeAgoraData(AgoraLeaveChannelOptions);
	return ret;
}

int UAgoraBPuRtcEngine::UpdateChannelMediaOptionsEx(const FChannelMediaOptions& options, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(channelMediaOptions, rtcConnection);

	options.FreeAgoraData(channelMediaOptions);
	connection.FreeAgoraData(rtcConnection);

	return ret;
}
int UAgoraBPuRtcEngine::SetVideoEncoderConfigurationEx(const FVideoEncoderConfiguration& config, const FRtcConnection& connection)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateAgoraData();

	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setVideoEncoderConfigurationEx(videoEncoderConfiguration, rtcConnection);

	config.FreeAgoraData(videoEncoderConfiguration);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteRemoteAudioStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->muteRemoteAudioStreamEx(uid, mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::MuteRemoteVideoStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->muteRemoteVideoStreamEx(uid, mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteVideoStreamTypeEx(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FVideoSubscriptionOptions& options, const FRtcConnection& connection)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions = options.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteVideoSubscriptionOptionsEx(uid, videoSubscriptionOptions, rtcConnection);
	options.FreeAgoraData(videoSubscriptionOptions);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteVoicePositionEx(uid, pan, gain, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteUserSpatialAudioParamsEx(int64 uid, const FSpatialAudioParams& params, const FRtcConnection& connection)
{
	agora::SpatialAudioParams spatialAudioParams = params.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteUserSpatialAudioParamsEx(uid, spatialAudioParams, rtcConnection);
	params.FreeAgoraData(spatialAudioParams);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteRenderModeEx(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableLoopbackRecordingEx(const FRtcConnection& connection, bool enabled, const FString& deviceName)
{
	std::string STDDeviceName = TCHAR_TO_UTF8(*deviceName);
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableLoopbackRecordingEx(rtcConnection, enabled, STDDeviceName.c_str());
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
ECONNECTION_STATE_TYPE UAgoraBPuRtcEngine::GetConnectionStateEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = (ECONNECTION_STATE_TYPE)AgoraUERtcEngine::Get()->getConnectionStateEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableEncryptionEx(const FRtcConnection& connection, bool enabled, const FEncryptionConfig& config)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::EncryptionConfig AgoraEncryptionConfig = config.CreateAgoraData();

	auto ret = AgoraUERtcEngine::Get()->enableEncryptionEx(rtcConnection, enabled, AgoraEncryptionConfig);

	connection.FreeAgoraData(rtcConnection);
	config.FreeAgoraData(AgoraEncryptionConfig);

	return ret;
}

int UAgoraBPuRtcEngine::CreateDataStreamEx(int& streamId, const FDataStreamConfig& config, const FRtcConnection& connection)
{
	agora::rtc::DataStreamConfig dataStreamConfig = config.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->createDataStreamEx(&streamId, dataStreamConfig, rtcConnection);
	config.FreeAgoraData(dataStreamConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SendStreamMessageEx(int streamId, const FString& data, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	auto ret = AgoraUERtcEngine::Get()->sendStreamMessageEx(streamId, StdStrData.c_str(), StdStrData.size(), rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::AddVideoWatermarkEx(const FString& watermarkUrl, const FWatermarkOptions& options, const FRtcConnection& connection)
{
	agora::rtc::WatermarkOptions watermarkOptions = options.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string STDSWatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	auto ret = AgoraUERtcEngine::Get()->addVideoWatermarkEx(STDSWatermarkUrl.c_str(), watermarkOptions, rtcConnection);
	options.FreeAgoraData(watermarkOptions);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::ClearVideoWatermarkEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->clearVideoWatermarkEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SendCustomReportMessageEx(const FString& id, const FString& category, const FString& event, const FString& label, int value, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string STDID = TCHAR_TO_UTF8(*id);
	std::string STDCategory = TCHAR_TO_UTF8(*category);
	std::string STDEvent = TCHAR_TO_UTF8(*event);
	std::string STDLabel = TCHAR_TO_UTF8(*label);
	auto ret = AgoraUERtcEngine::Get()->sendCustomReportMessageEx(STDID.c_str(), STDCategory.c_str(), STDEvent.c_str(), STDLabel.c_str(), value, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableAudioVolumeIndicationEx(interval, smooth, reportVad, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUserAccountEx(const FString& userAccount, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;

	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUserAccountEx(TCHAR_TO_UTF8(*userAccount), &info, rtcConnection);

	userInfo = info;

	connection.FreeAgoraData(rtcConnection);

	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();

	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUidEx(uid, &info, rtcConnection);

	userInfo = info;
	connection.FreeAgoraData(rtcConnection);

	return ret;
}

int UAgoraBPuRtcEngine::EnableDualStreamModeEx(bool enabled, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableDualStreamModeEx(enabled, simulcastStreamConfig, rtcConnection);
	streamConfig.FreeAgoraData(simulcastStreamConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetDualStreamModeEx(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig AgoraSimulcastStreamConfig = streamConfig.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->setDualStreamModeEx(mode.GetRawValue(), AgoraSimulcastStreamConfig, rtcConnection);
	streamConfig.FreeAgoraData(AgoraSimulcastStreamConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableWirelessAccelerate(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableWirelessAccelerate(enabled);
	return ret;
}
int UAgoraBPuRtcEngine::TakeSnapshotEx(const FRtcConnection& connection, int64 uid, const FString& filePath)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = AgoraUERtcEngine::Get()->takeSnapshotEx(rtcConnection, uid, FilePath.c_str());
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::EnableContentInspectEx(bool enabled, const FContentInspectConfig& config, const FRtcConnection& connection)
{
	agora::media::ContentInspectConfig contentInspectConfig = config.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->enableContentInspectEx(enabled, contentInspectConfig, rtcConnection);
	config.FreeAgoraData(contentInspectConfig);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->muteLocalAudioStreamEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->muteLocalVideoStreamEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->muteAllRemoteAudioStreamsEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->muteAllRemoteVideoStreamsEx(mute, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeAudioBlocklist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioBlocklist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		return ret;
}

int UAgoraBPuRtcEngine::SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioBlocklistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeAudioAllowlist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioAllowlist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		return ret;
}

int UAgoraBPuRtcEngine::SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioAllowlistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeVideoBlocklist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = nullptr;
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoBlocklist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		return ret;
}

int UAgoraBPuRtcEngine::SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::uid_t* data = nullptr;
	int UEuidNumber = uidList.Num();
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoBlocklistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeVideoAllowlist(TArray<int64> uidList, int uidNumber)
{
	agora::rtc::uid_t* data = nullptr;
	int UEuidNumber = uidList.Num();
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoAllowlist(data, UEuidNumber);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		return ret;
}

int UAgoraBPuRtcEngine::SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::uid_t* data = nullptr;
	int UEuidNumber = uidList.Num();
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(data, agora::rtc::uid_t, UEuidNumber, uidList)
		auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoAllowlistEx(data, UEuidNumber, rtcConnection);
	SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(data)
		connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->adjustUserPlaybackSignalVolumeEx(uid, volume, rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::StartRtmpStreamWithoutTranscodingEx(const FString& url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string Url = TCHAR_TO_UTF8(*url);
	int ret = AgoraUERtcEngine::Get()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::StartRtmpStreamWithTranscodingEx(const FString& url, const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string streamUrl = TCHAR_TO_UTF8(*url);

	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();

	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithTranscodingEx(streamUrl.c_str(), liveTranscoding, rtcConnection);

	connection.FreeAgoraData(rtcConnection);
	transcoding.FreeAgoraData(liveTranscoding);

	return ret;
}

int UAgoraBPuRtcEngine::UpdateRtmpTranscodingEx(const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateAgoraData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();

	auto ret = AgoraUERtcEngine::Get()->updateRtmpTranscodingEx(liveTranscoding, rtcConnection);

	transcoding.FreeAgoraData(liveTranscoding);
	connection.FreeAgoraData(rtcConnection);

	return ret;
}

int UAgoraBPuRtcEngine::StopRtmpStreamEx(const FString& url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string Url = TCHAR_TO_UTF8(*url);
	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::StopChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->stopChannelMediaRelayEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::PauseAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->pauseAllChannelMediaRelayEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::ResumeAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->resumeAllChannelMediaRelayEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::SetParameters(const FString& parameters)
{
	std::string parameterstr = TCHAR_TO_UTF8(*parameters);

	auto ret = AgoraUERtcEngine::Get()->setParameters(parameterstr.c_str());
	return ret;
}


int UAgoraBPuRtcEngine::SetParametersEx(const FRtcConnection& connection, const FString& parameters)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string STDParameters = TCHAR_TO_UTF8(*parameters);
	auto ret = AgoraUERtcEngine::Get()->setParametersEx(rtcConnection, STDParameters.c_str());
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::GetCallIdEx(FString& callId, const FRtcConnection& connection)
{
	agora::util::AString CallId;
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->getCallIdEx(CallId, rtcConnection);
	connection.FreeAgoraData(rtcConnection);

	callId = UTF8_TO_TCHAR(CallId->c_str());
	return ret;
}


int UAgoraBPuRtcEngine::SendAudioMetadata(const FString& metadata, const FString& length)
{
	std::string AMetadata = TCHAR_TO_UTF8(*metadata);
	size_t ALength = FCString::Strtoui64(*length, NULL, 10);
	auto ret = AgoraUERtcEngine::Get()->sendAudioMetadata(AMetadata.c_str(), ALength);
	return ret;
}

int UAgoraBPuRtcEngine::SendAudioMetadataEx(const FRtcConnection& connection, const FString& metadata, const FString& length)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	std::string AgoraMetadata = TCHAR_TO_UTF8(*metadata);
	size_t AgoraLength = FCString::Strtoui64(*length, NULL, 10);
	auto ret = AgoraUERtcEngine::Get()->sendAudioMetadataEx(rtcConnection, AgoraMetadata.c_str(), AgoraLength);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::StartMediaRenderingTracing()
{
	auto ret = AgoraUERtcEngine::Get()->startMediaRenderingTracing();
	return ret;
}


int UAgoraBPuRtcEngine::StartMediaRenderingTracingEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startMediaRenderingTracingEx(rtcConnection);
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::EnableInstantMediaRendering()
{
	auto ret = AgoraUERtcEngine::Get()->enableInstantMediaRendering();
	return ret;
}


FString UAgoraBPuRtcEngine::GetNtpWallTimeInMs()
{
	FString ret = FString::Printf(TEXT("%llu"), AgoraUERtcEngine::Get()->getNtpWallTimeInMs());
	return ret;
}


int UAgoraBPuRtcEngine::SetHeadphoneEQPreset(FENUMWRAP_HEADPHONE_EQUALIZER_PRESET preset)
{
	auto ret = AgoraUERtcEngine::Get()->setHeadphoneEQPreset(preset.GetRawValue());
	return ret;
}


int UAgoraBPuRtcEngine::SetHeadphoneEQParameters(int lowGain, int highGain)
{
	auto ret = AgoraUERtcEngine::Get()->setHeadphoneEQParameters(lowGain, highGain);
	return ret;
}


int UAgoraBPuRtcEngine::EnableVoiceAITuner(bool enabled, EVOICE_AI_TUNER_TYPE type)
{
	auto ret = AgoraUERtcEngine::Get()->enableVoiceAITuner(enabled, (agora::rtc::VOICE_AI_TUNER_TYPE)type);
	return ret;
}

int UAgoraBPuRtcEngine::SetEarMonitoringAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = AgoraUERtcEngine::Get()->setEarMonitoringAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)((int)mode), samplesPerCall);
	return ret;
}


int64 UAgoraBPuRtcEngine::GetCurrentMonotonicTimeInMs()
{
	auto ret = AgoraUERtcEngine::Get()->getCurrentMonotonicTimeInMs();
	return ret;
}



int UAgoraBPuRtcEngine::RegisterExtension(const FString& provider, const FString& extension, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	auto ret = AgoraUERtcEngine::Get()->registerExtension(Provider.c_str(), Extension.c_str(), (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}


int UAgoraBPuRtcEngine::GetNetworkType()
{
	auto ret = AgoraUERtcEngine::Get()->getNetworkType();
	return ret;
}


bool UAgoraBPuRtcEngine::IsFeatureAvailableOnDevice(EFeatureType type)
{
	auto ret = AgoraUERtcEngine::Get()->isFeatureAvailableOnDevice(static_cast<agora::rtc::FeatureType>(type));
	return ret;
}

#pragma endregion RtcEngine2


#pragma region Screen Share


int UIScreenCaptureSourceList::GetCount()
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	if (sourceListNative != nullptr)
	{
		return sourceListNative->getCount();
	}
#endif
	return 0;
}

FScreenCaptureSourceInfo UIScreenCaptureSourceList::GetSourceInfo(int index)
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


UIScreenCaptureSourceList* UAgoraBPuRtcEngine::GetScreenCaptureSources(const FSIZE& thumbSize, const FSIZE& iconSize, bool includeScreen)
{
	if (!UserScreenCaptureSourceList.IsValid()) {
		UserScreenCaptureSourceList = TStrongObjectPtr<UIScreenCaptureSourceList>(NewObject<UIScreenCaptureSourceList>());
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
	agora::rtc::IScreenCaptureSourceList* screenCaptureNative = AgoraUERtcEngine::Get()->getScreenCaptureSources(thumb, icon, includeScreen);

	if (screenCaptureNative != nullptr)
	{
		UserScreenCaptureSourceList->SetScreenCaptureList(screenCaptureNative);
		return UserScreenCaptureSourceList.Get();
	}

#endif

	return nullptr;
}


int UAgoraBPuRtcEngine::SetAudioSessionOperationRestriction(EAUDIO_SESSION_OPERATION_RESTRICTION restriction)
{
#if (defined(__APPLE__) && TARGET_OS_IOS)
	return AgoraUERtcEngine::Get()->setAudioSessionOperationRestriction((agora::AUDIO_SESSION_OPERATION_RESTRICTION)restriction);
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::StartScreenCaptureByDisplayId(int64 displayId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle region = regionRect.CreateAgoraData();

	agora::rtc::ScreenCaptureParameters params = captureParams.CreateAgoraData();

	auto ret = AgoraUERtcEngine::Get()->startScreenCaptureByDisplayId(displayId, region, params);

	regionRect.FreeAgoraData(region);
	captureParams.FreeAgoraData(params);

	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::StartScreenCaptureByScreenRect(const FRectangle& screenRect, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams) __deprecated
{
#if defined(_WIN32)
	agora::rtc::Rectangle AgoraScreenRect = screenRect.CreateAgoraData();
	agora::rtc::Rectangle AgoraRegionRect = regionRect.CreateAgoraData();
	agora::rtc::ScreenCaptureParameters AgoraScreenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCaptureByScreenRect(AgoraScreenRect, AgoraRegionRect, AgoraScreenCaptureParameters);
	screenRect.FreeAgoraData(AgoraScreenRect);
	regionRect.FreeAgoraData(AgoraRegionRect);
	captureParams.FreeAgoraData(AgoraScreenCaptureParameters);

	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::GetAudioDeviceInfo(FDeviceInfo& deviceInfo)
{
#if defined(__ANDROID__)
	agora::rtc::DeviceInfo Info;
	auto ret = AgoraUERtcEngine::Get()->getAudioDeviceInfo(Info);
	deviceInfo = Info;
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::StartScreenCaptureByWindowId(int64 windowId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle = regionRect.CreateAgoraData();
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCaptureByWindowId(UABT::ToView(windowId), rectangle, screenCaptureParameters);
	regionRect.FreeAgoraData(rectangle);
	captureParams.FreeAgoraData(screenCaptureParameters);

	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	auto ret = AgoraUERtcEngine::Get()->setScreenCaptureContentHint((agora::rtc::VIDEO_CONTENT_HINT)contentHint);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::UpdateScreenCaptureRegion(const FRectangle& regionRect)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle = regionRect.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->updateScreenCaptureRegion(rectangle);
	regionRect.FreeAgoraData(rectangle);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::UpdateScreenCaptureParameters(const FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->updateScreenCaptureParameters(screenCaptureParameters);
	captureParams.FreeAgoraData(screenCaptureParameters);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::StartScreenCapture(const FScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2 = captureParams.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCapture(screenCaptureParameters2);
	captureParams.FreeAgoraData(screenCaptureParameters2);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif

}


int UAgoraBPuRtcEngine::StartScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType, const FScreenCaptureConfiguration& config)
{

	agora::rtc::ScreenCaptureConfiguration screenCaptureConfiguration = config.CreateAgoraData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType, screenCaptureConfiguration);
	config.FreeAgoraData(screenCaptureConfiguration);
	return ret;
}

int UAgoraBPuRtcEngine::StopScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = AgoraUERtcEngine::Get()->stopScreenCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}

int UAgoraBPuRtcEngine::QueryScreenCaptureCapability()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = AgoraUERtcEngine::Get()->queryScreenCaptureCapability();
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
#pragma endregion Screen Share

