// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraRtcEngine.h"
#include "AgoraBluePrintPlugin/AgoraSpatialAudio.h"
#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandler.h"
#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandlerEx.h"


UObject* UAgoraRtcEngine::QueryInterface(EINTERFACE_ID_TYPE iid)
{
	if (iid == EINTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER)
	{
		agora::rtc::IVideoDeviceManager* VideoDeviceManager = nullptr;
		RtcEngineProxy::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);

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
		RtcEngineProxy::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&AudioDeviceManager);

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
		RtcEngineProxy::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_LOCAL_SPATIAL_AUDIO, (void**)&SpatialAudioEngine);

		if (spatialAudioEngine != nullptr)
		{
			return spatialAudioEngine;
		}
		spatialAudioEngine = NewObject<UILocalSpatialAudioEngine>();

		spatialAudioEngine->SetLocalSpatialAudioEngine(SpatialAudioEngine);

		return spatialAudioEngine;
	}
	else if (iid == EINTERFACE_ID_TYPE::AGORA_IID_MEDIA_RECORDER)
	{
		agora::rtc::IMediaRecorder* MediaRecorder = nullptr;
		RtcEngineProxy::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_MEDIA_RECORDER, (void**)&MediaRecorder);

		if (mediaRecorder != nullptr)
		{
			return mediaRecorder;
		}
		mediaRecorder = NewObject<UIMediaRecorder>();

		mediaRecorder->SetMediaRecorder(MediaRecorder);

		return mediaRecorder;
	}
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
	if (mediaRecorder != nullptr)
	{
		mediaRecorder->Release();
		mediaRecorder = nullptr;
	}
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
	return RtcEngineProxy::release(sync);
}
int UAgoraRtcEngine::Initialize(FRtcEngineContext& context)
{
	agora::rtc::RtcEngineContext rtcEngineContext;

	if (context.eventHandler!=nullptr && std::strcmp(context.eventHandler->eventHandlerType(), "event_handler") != 0)
	{
		rtcEngineContext.eventHandler = (agora::rtc::IRtcEngineEventHandler*)context.eventHandler;
	}
	else
	{
		rtcEngineContext.eventHandler = (agora::rtc::IRtcEngineEventHandlerEx*)context.eventHandler;
	}

	std::string appid = TCHAR_TO_UTF8(*context.appId);

	rtcEngineContext.appId = appid.c_str();
	rtcEngineContext.context = (void*)context.context;
	rtcEngineContext.channelProfile = (agora::CHANNEL_PROFILE_TYPE)context.channelProfile;
	rtcEngineContext.audioScenario = (agora::rtc::AUDIO_SCENARIO_TYPE)context.audioScenario;
	if ((unsigned int)context.areaCode == 0)
	{
		rtcEngineContext.areaCode = (0xFFFFFFFF);
	}
	else
	{
		rtcEngineContext.areaCode = (unsigned int)context.areaCode;
	}


	agora::commons::LogConfig log;
	std::string FilePath = TCHAR_TO_UTF8(*context.logConfig.filePath);
	log.filePath = FilePath.c_str();
	log.fileSizeInKB = context.logConfig.fileSizeInKB;
	log.level = (agora::commons::LOG_LEVEL)context.logConfig.level.GetValue();
	rtcEngineContext.logConfig = log;
	if (context.threadPriorityValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		rtcEngineContext.threadPriority = (agora::rtc::THREAD_PRIORITY_TYPE)context.threadPriority;
	}
	rtcEngineContext.useExternalEglContext = context.useExternalEglContext;

	int ret = RtcEngineProxy::initialize(rtcEngineContext);
	return ret;
}
FString UAgoraRtcEngine::GetVersion(int build)
{
	return RtcEngineProxy::getVersion(&build);
}
FString UAgoraRtcEngine::GetErrorDescription(int code)
{
	return RtcEngineProxy::getErrorDescription(code);
}
int UAgoraRtcEngine::JoinChannel(FString token, FString channelId, int64 uid, FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryCameraTrack = options.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	if (options.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureVideo = options.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureAudio = options.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#else
	if (options.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenTrack = options.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryScreenTrack = options.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#endif
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioSourceId != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioSourceId = options.publishCustomAudioSourceId == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackEnableAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackEnableAec = options.publishCustomAudioTrackEnableAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishDirectCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishDirectCustomAudioTrack = options.publishDirectCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackAec = options.publishCustomAudioTrackAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishEncodedVideoTrack = options.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerVideoTrack = options.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishTrancodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishTrancodedVideoTrack = options.publishTrancodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeAudio = options.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeVideo = options.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableAudioRecordingOrPlayout = options.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.clientRoleTypeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)options.clientRoleType;
	}
	if (options.audienceLatencyLevelValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	}
	if (options.defaultVideoStreamValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)options.defaultVideoStreamType;
	}
	if (options.channelProfileValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)options.channelProfile;
	}
	if (options.audioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audioDelayMs = options.audioDelayMs;
	}
	if (options.mediaPlayerAudioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.mediaPlayerAudioDelayMs = options.mediaPlayerAudioDelayMs;
	}
	if (options.tokenValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		std::string Token = TCHAR_TO_ANSI(*options.token);
		channelMediaOptions.token = Token.c_str();
	}
	if (options.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableBuiltInMediaEncryption = options.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishRhythmPlayerTrack = options.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isInteractiveAudience = options.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	if (options.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	int ret = RtcEngineProxy::joinChannel(Token.c_str(), ChannelId.c_str(), uid, channelMediaOptions);
	return ret;
}
int UAgoraRtcEngine::UpdateChannelMediaOptions(FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryCameraTrack = options.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	if (options.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureVideo = options.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureAudio = options.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#else
	if (options.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenTrack = options.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryScreenTrack = options.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#endif
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioSourceId != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioSourceId = options.publishCustomAudioSourceId == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackEnableAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackEnableAec = options.publishCustomAudioTrackEnableAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishDirectCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishDirectCustomAudioTrack = options.publishDirectCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackAec = options.publishCustomAudioTrackAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishEncodedVideoTrack = options.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerVideoTrack = options.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishTrancodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishTrancodedVideoTrack = options.publishTrancodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeAudio = options.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeVideo = options.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableAudioRecordingOrPlayout = options.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.clientRoleTypeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)options.clientRoleType;
	}
	if (options.audienceLatencyLevelValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	}
	if (options.defaultVideoStreamValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)options.defaultVideoStreamType;
	}
	if (options.channelProfileValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)options.channelProfile;
	}
	if (options.audioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audioDelayMs = options.audioDelayMs;
	}
	if (options.mediaPlayerAudioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.mediaPlayerAudioDelayMs = options.mediaPlayerAudioDelayMs;
	}
	if (options.tokenValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		std::string Token = TCHAR_TO_ANSI(*options.token);
		channelMediaOptions.token = Token.c_str();
	}
	if (options.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableBuiltInMediaEncryption = options.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishRhythmPlayerTrack = options.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isInteractiveAudience = options.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	if (options.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	return RtcEngineProxy::updateChannelMediaOptions(channelMediaOptions);
}
int UAgoraRtcEngine::LeaveChannel(FLeaveChannelOptions& options)
{
	agora::rtc::LeaveChannelOptions leaveChannelOptions;
	if (options.stopAudioMixing != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		leaveChannelOptions.stopAudioMixing = options.stopAudioMixing == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.stopAllEffect != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		leaveChannelOptions.stopAllEffect = options.stopAllEffect == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.stopMicrophoneRecording != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		leaveChannelOptions.stopMicrophoneRecording = options.stopMicrophoneRecording == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	return RtcEngineProxy::leaveChannel(leaveChannelOptions);
}
int UAgoraRtcEngine::RenewToken(FString token)
{
	std::string Token = TCHAR_TO_ANSI(*token);
	return RtcEngineProxy::renewToken(Token.c_str());
}
int UAgoraRtcEngine::SetChannelProfile(ECHANNEL_PROFILE_TYPE profile)
{
	return RtcEngineProxy::setChannelProfile((agora::CHANNEL_PROFILE_TYPE)profile);
}
int UAgoraRtcEngine::SetClientRole(ECLIENT_ROLE_TYPE clientroletype, FClientRoleOptions& options)
{
	agora::rtc::ClientRoleOptions clientRoleOptions;
	clientRoleOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	agora::rtc::CLIENT_ROLE_TYPE roleType = (agora::rtc::CLIENT_ROLE_TYPE)clientroletype;
	return RtcEngineProxy::setClientRole(roleType, clientRoleOptions);
}
int UAgoraRtcEngine::StartEchoTest(FEchoTestConfiguration& config)
{
	agora::rtc::EchoTestConfiguration echoTestConfiguration;
	echoTestConfiguration.view = (agora::view_t)config.view;
	echoTestConfiguration.enableAudio = config.enableAudio;
	echoTestConfiguration.enableVideo = config.enableVideo;
	std::string Token = TCHAR_TO_ANSI(*config.token);
	echoTestConfiguration.token = Token.c_str();
	std::string ChannelId = TCHAR_TO_ANSI(*config.channelId);
	echoTestConfiguration.channelId = ChannelId.c_str();
	return RtcEngineProxy::startEchoTest(echoTestConfiguration);
}
int UAgoraRtcEngine::StopEchoTest()
{
	return RtcEngineProxy::stopEchoTest();
}
int UAgoraRtcEngine::EnableVideo()
{
	return RtcEngineProxy::enableVideo();
}
int UAgoraRtcEngine::DisableVideo()
{
	return RtcEngineProxy::disableVideo();
}
int UAgoraRtcEngine::StartPreview(EVIDEO_SOURCE_TYPE sourceType)
{
	return RtcEngineProxy::startPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
}
int UAgoraRtcEngine::StopPreview(EVIDEO_SOURCE_TYPE sourceType)
{
	return RtcEngineProxy::stopPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
}
int UAgoraRtcEngine::StartLastmileProbeTest(FLastmileProbeConfig& config)
{
	agora::rtc::LastmileProbeConfig lastmileProbeConfig;
	lastmileProbeConfig.probeUplink = config.probeUplink;
	lastmileProbeConfig.probeDownlink = config.probeDownlink;
	lastmileProbeConfig.expectedUplinkBitrate = config.expectedUplinkBitrate;
	lastmileProbeConfig.expectedDownlinkBitrate = config.expectedDownlinkBitrate;
	return RtcEngineProxy::startLastmileProbeTest(lastmileProbeConfig);
}
int UAgoraRtcEngine::SetVideoEncoderConfiguration(FVideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration;
	videoEncoderConfiguration.codecType = (agora::rtc::VIDEO_CODEC_TYPE)config.codecType;

	agora::rtc::VideoDimensions dim;
	dim.height = config.dimensions.height;
	dim.width = config.dimensions.width;

	videoEncoderConfiguration.dimensions = dim;
	videoEncoderConfiguration.frameRate = config.frameRate;
	videoEncoderConfiguration.bitrate = config.bitrate;
	videoEncoderConfiguration.minBitrate = config.minBitrate;
	videoEncoderConfiguration.orientationMode = (agora::rtc::ORIENTATION_MODE)config.orientationMode;
	videoEncoderConfiguration.degradationPreference = (agora::rtc::DEGRADATION_PREFERENCE)config.degradationPreference;
	videoEncoderConfiguration.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)config.mirrorMode;
	return RtcEngineProxy::setVideoEncoderConfiguration(videoEncoderConfiguration);
}
int UAgoraRtcEngine::SetBeautyEffectOptions(bool enabled, FBeautyOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::BeautyOptions beautyOptions;
	beautyOptions.lighteningContrastLevel = (agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL)options.lighteningContrastLevel;
	beautyOptions.lighteningLevel = options.lighteningLevel;
	beautyOptions.smoothnessLevel = options.smoothnessLevel;
	beautyOptions.rednessLevel = options.rednessLevel;
	beautyOptions.sharpnessLevel = options.sharpnessLevel;
	return RtcEngineProxy::setBeautyEffectOptions(enabled, beautyOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::SetLowlightEnhanceOptions(bool enabled, FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::LowlightEnhanceOptions lowlightEnhanceOptions;
	lowlightEnhanceOptions.mode = (agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_MODE)options.mode;
	lowlightEnhanceOptions.level = (agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_LEVEL)options.level;
	return RtcEngineProxy::setLowlightEnhanceOptions(enabled, lowlightEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::SetVideoDenoiserOptions(bool enabled, FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VideoDenoiserOptions videoDenoiserOptions;
	videoDenoiserOptions.mode = (agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_MODE)options.mode;
	videoDenoiserOptions.level = (agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_LEVEL)options.level;
	return RtcEngineProxy::setVideoDenoiserOptions(enabled, videoDenoiserOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::SetColorEnhanceOptions(bool enabled, FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::ColorEnhanceOptions colorEnhanceOptions;
	colorEnhanceOptions.strengthLevel = options.strengthLevel;
	colorEnhanceOptions.skinProtectLevel = options.skinProtectLevel;
	return RtcEngineProxy::setColorEnhanceOptions(enabled, colorEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VirtualBackgroundSource virtualBackgroundSource;
	virtualBackgroundSource.background_source_type = (agora::rtc::VirtualBackgroundSource::BACKGROUND_SOURCE_TYPE)backgroundSource.background_source_type;
	virtualBackgroundSource.color = backgroundSource.color;
	std::string Source = TCHAR_TO_ANSI(*backgroundSource.source);
	virtualBackgroundSource.source = Source.c_str();
	virtualBackgroundSource.blur_degree = (agora::rtc::VirtualBackgroundSource::BACKGROUND_BLUR_DEGREE)backgroundSource.blur_degree;
	agora::rtc::SegmentationProperty segmentationProperty;
	segmentationProperty.modelType = (agora::rtc::SegmentationProperty::SEG_MODEL_TYPE)segproperty.modelType;
	segmentationProperty.greenCapacity = segproperty.greenCapacity;
	return RtcEngineProxy::enableVirtualBackground(enabled, virtualBackgroundSource, segmentationProperty, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::EnableRemoteSuperResolution(int64 userId, bool enable)
{
	return RtcEngineProxy::enableRemoteSuperResolution(userId, enable);
}
int UAgoraRtcEngine::SetupRemoteVideo(FVideoCanvas& canvas)
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
	return RtcEngineProxy::setupRemoteVideo(videoCanvas);
}
int UAgoraRtcEngine::SetupLocalVideo(FVideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	//videoCanvas.renderMode = (agora::media::base::RENDER_MODE_TYPE)canvas.renderMode;
	//videoCanvas.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)canvas.mirrorMode;
	videoCanvas.uid = canvas.uid;
	//videoCanvas.isScreenView = canvas.isScreenView;
	//videoCanvas.priv = canvas.priv;
	//videoCanvas.priv_size = canvas.priv_size;
	videoCanvas.sourceType = (agora::rtc::VIDEO_SOURCE_TYPE)canvas.sourceType;
	//videoCanvas.cropArea = canvas.cropArea;
	//videoCanvas.setupMode = (agora::rtc::VIDEO_VIEW_SETUP_MODE)canvas.setupMode;
	return RtcEngineProxy::setupLocalVideo(videoCanvas);
}
int UAgoraRtcEngine::EnableAudio()
{
	return RtcEngineProxy::enableAudio();
}
int UAgoraRtcEngine::DisableAudio()
{
	return RtcEngineProxy::disableAudio();
}
int UAgoraRtcEngine::SetAudioProfile(EAUDIO_PROFILE_TYPE profile, EAUDIO_SCENARIO_TYPE scenario)
{
	return RtcEngineProxy::setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile, (agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
}

int UAgoraRtcEngine::SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario)
{
	return RtcEngineProxy::setAudioScenario((agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
}
int UAgoraRtcEngine::EnableLocalAudio(bool enabled)
{
	return RtcEngineProxy::enableLocalAudio(enabled);
}
int UAgoraRtcEngine::MuteLocalAudioStream(bool mute)
{
	return RtcEngineProxy::muteLocalAudioStream(mute);
}
int UAgoraRtcEngine::MuteAllRemoteAudioStreams(bool mute)
{
	return RtcEngineProxy::muteAllRemoteAudioStreams(mute);
}
int UAgoraRtcEngine::SetDefaultMuteAllRemoteAudioStreams(bool mute)
{
	return RtcEngineProxy::setDefaultMuteAllRemoteAudioStreams(mute);
}
int UAgoraRtcEngine::MuteRemoteAudioStream(int64 uid, bool mute)
{
	return RtcEngineProxy::muteRemoteAudioStream(uid, mute);
}
int UAgoraRtcEngine::MuteLocalVideoStream(bool mute)
{
	return RtcEngineProxy::muteLocalVideoStream(mute);
}
int UAgoraRtcEngine::EnableLocalVideo(bool enabled)
{
	return RtcEngineProxy::enableLocalVideo(enabled);
}
int UAgoraRtcEngine::MuteAllRemoteVideoStreams(bool mute)
{
	return RtcEngineProxy::muteAllRemoteVideoStreams(mute);
}
int UAgoraRtcEngine::SetDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return RtcEngineProxy::setDefaultMuteAllRemoteVideoStreams(mute);
}
int UAgoraRtcEngine::MuteRemoteVideoStream(int64 uid, bool mute)
{
	return RtcEngineProxy::muteRemoteVideoStream(uid, mute);
}
int UAgoraRtcEngine::SetRemoteVideoStreamType(int64 uid, EVIDEO_STREAM_TYPE streamType)
{
	return RtcEngineProxy::setRemoteVideoStreamType(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType);
}
int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptions(int64 uid, FVideoSubscriptionOptions& options)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions;
	if (options.typeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		videoSubscriptionOptions.type = (agora::rtc::VIDEO_STREAM_TYPE)options.type;
	}
	if (options.encodedFrameOnly != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		videoSubscriptionOptions.encodedFrameOnly = options.encodedFrameOnly == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}

	return RtcEngineProxy::setRemoteVideoSubscriptionOptions(uid, videoSubscriptionOptions);
}
int UAgoraRtcEngine::SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType)
{
	return RtcEngineProxy::setRemoteDefaultVideoStreamType((agora::rtc::VIDEO_STREAM_TYPE)streamType);
}

int UAgoraRtcEngine::EnableAudioVolumeIndication(int interval, int smooth, bool reportVad)
{
	return RtcEngineProxy::enableAudioVolumeIndication(interval, smooth, reportVad);
}
int UAgoraRtcEngine::StartAudioRecording(FAudioRecordingConfiguration& config)
{
	agora::rtc::AudioRecordingConfiguration audioRecordingConfiguration;
	std::string FilePath = TCHAR_TO_ANSI(*config.filePath);
	audioRecordingConfiguration.filePath = FilePath.c_str();
	audioRecordingConfiguration.encode = config.encode;
	audioRecordingConfiguration.sampleRate = config.sampleRate;
	audioRecordingConfiguration.fileRecordingType = (agora::rtc::AUDIO_FILE_RECORDING_TYPE)config.fileRecordingType;
	audioRecordingConfiguration.quality = (agora::rtc::AUDIO_RECORDING_QUALITY_TYPE)config.quality;
	audioRecordingConfiguration.recordingChannel = config.recordingChannel;
	return RtcEngineProxy::startAudioRecording(audioRecordingConfiguration);
}

int UAgoraRtcEngine::RegisterAudioEncodedFrameObserver(FAudioEncodedFrameObserverConfig& config, UIAudioEncodedFrameObserver* observer)
{
	agora::rtc::AudioEncodedFrameObserverConfig audioEncodedFrameObserverConfig;
	audioEncodedFrameObserverConfig.postionType = (agora::rtc::AUDIO_ENCODED_FRAME_OBSERVER_POSITION)config.postionType;
	if ((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue()==1)
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_16000_LOW;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 2))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_16000_MEDIUM;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 3))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_LOW;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 4))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_MEDIUM;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 5))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_32000_HIGH;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 6))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_MEDIUM;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 7))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_AAC_48000_HIGH;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 8))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_16000_LOW;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 9))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_16000_MEDIUM;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 10))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_MEDIUM;
	}
	else if (((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 11))
	{
		audioEncodedFrameObserverConfig.encodingType = agora::rtc::AUDIO_ENCODING_TYPE::AUDIO_ENCODING_TYPE_OPUS_48000_HIGH;
	}	
	
	return RtcEngineProxy::registerAudioEncodedFrameObserver(audioEncodedFrameObserverConfig, observer);
}
int UAgoraRtcEngine::StopAudioRecording()
{
	return RtcEngineProxy::stopAudioRecording();
}

UIMediaPlayer* UAgoraRtcEngine::CreateMediaPlayer()
{
	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer = nullptr;

	if (mediaPlayer != nullptr)
	{
		return mediaPlayer;
	}

	mediaPlayer = NewObject<UIMediaPlayer>();

	MediaPlayer = RtcEngineProxy::createMediaPlayer();

	mediaPlayer->SetMediaPlayer(MediaPlayer);

	return mediaPlayer;
}
int UAgoraRtcEngine::DestroyMediaPlayer(UIMediaPlayer* media_player)
{
	return RtcEngineProxy::destroyMediaPlayer(media_player->GetMediaPlayer());
}
int UAgoraRtcEngine::StartAudioMixing(FString filePath, bool loopback, int cycle, int startPos)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	return RtcEngineProxy::startAudioMixing(FilePath.c_str(), loopback, cycle, startPos);
}
int UAgoraRtcEngine::PauseAudioMixing()
{
	return RtcEngineProxy::pauseAudioMixing();
}
int UAgoraRtcEngine::ResumeAudioMixing()
{
	return RtcEngineProxy::resumeAudioMixing();
}
int UAgoraRtcEngine::SelectAudioTrack(int index)
{
	return RtcEngineProxy::selectAudioTrack(index);
}
int UAgoraRtcEngine::GetAudioTrackCount()
{
	return RtcEngineProxy::getAudioTrackCount();
}
int UAgoraRtcEngine::AdjustAudioMixingVolume(int volume)
{
	return RtcEngineProxy::adjustAudioMixingVolume(volume);
}
int UAgoraRtcEngine::AdjustAudioMixingPublishVolume(int volume)
{
	return RtcEngineProxy::adjustAudioMixingPublishVolume(volume);
}
int UAgoraRtcEngine::GetAudioMixingPublishVolume()
{
	return RtcEngineProxy::getAudioMixingPublishVolume();
}
int UAgoraRtcEngine::AdjustAudioMixingPlayoutVolume(int volume)
{
	return RtcEngineProxy::adjustAudioMixingPlayoutVolume(volume);
}
int UAgoraRtcEngine::GetAudioMixingPlayoutVolume()
{
	return RtcEngineProxy::getAudioMixingPlayoutVolume();
}
int UAgoraRtcEngine::GetAudioMixingDuration()
{
	return RtcEngineProxy::getAudioMixingDuration();
}
int UAgoraRtcEngine::GetAudioMixingCurrentPosition()
{
	return RtcEngineProxy::getAudioMixingCurrentPosition();
}
int UAgoraRtcEngine::SetAudioMixingPosition(int pos)
{
	return RtcEngineProxy::setAudioMixingPosition(pos);
}
int UAgoraRtcEngine::SetAudioMixingDualMonoMode(EAUDIO_MIXING_DUAL_MONO_MODE mode)
{
	return RtcEngineProxy::setAudioMixingDualMonoMode((agora::media::AUDIO_MIXING_DUAL_MONO_MODE)mode);
}
int UAgoraRtcEngine::SetAudioMixingPitch(int pitch)
{
	return RtcEngineProxy::setAudioMixingPitch(pitch);
}
int UAgoraRtcEngine::GetEffectsVolume()
{
	return RtcEngineProxy::getEffectsVolume();
}
int UAgoraRtcEngine::SetEffectsVolume(int volume)
{
	return RtcEngineProxy::setEffectsVolume(volume);
}
int UAgoraRtcEngine::PreloadEffect(int soundId, FString filePath, int startPos)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	return RtcEngineProxy::preloadEffect(soundId, FilePath.c_str(), startPos);
}
int UAgoraRtcEngine::PlayEffect(int soundId, FString filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	return RtcEngineProxy::playEffect(soundId, FilePath.c_str(), loopCount, pitch, pan, gain, publish, startPos);
}
int UAgoraRtcEngine::PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish)
{
	return RtcEngineProxy::playAllEffects(loopCount, pitch, pan, gain, publish);
}
int UAgoraRtcEngine::GetVolumeOfEffect(int soundId)
{
	return RtcEngineProxy::getVolumeOfEffect(soundId);
}
int UAgoraRtcEngine::SetVolumeOfEffect(int soundId, int volume)
{
	return RtcEngineProxy::setVolumeOfEffect(soundId, volume);
}
int UAgoraRtcEngine::PauseEffect(int soundId)
{
	return RtcEngineProxy::pauseEffect(soundId);
}
int UAgoraRtcEngine::PauseAllEffects()
{
	return RtcEngineProxy::pauseAllEffects();
}
int UAgoraRtcEngine::ResumeEffect(int soundId)
{
	return RtcEngineProxy::resumeEffect(soundId);
}
int UAgoraRtcEngine::ResumeAllEffects()
{
	return RtcEngineProxy::resumeAllEffects();
}
int UAgoraRtcEngine::StopEffect(int soundId)
{
	return RtcEngineProxy::stopEffect(soundId);
}
int UAgoraRtcEngine::StopAllEffects()
{
	return RtcEngineProxy::stopAllEffects();
}
int UAgoraRtcEngine::UnloadEffect(int soundId)
{
	return RtcEngineProxy::unloadEffect(soundId);
}
int UAgoraRtcEngine::UnloadAllEffects()
{
	return RtcEngineProxy::unloadAllEffects();
}
int UAgoraRtcEngine::GetEffectDuration(FString filePath)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	return RtcEngineProxy::getEffectDuration(FilePath.c_str());
}
int UAgoraRtcEngine::SetEffectPosition(int soundId, int pos)
{
	return RtcEngineProxy::setEffectPosition(soundId, pos);
}
int UAgoraRtcEngine::GetEffectCurrentPosition(int soundId)
{
	return RtcEngineProxy::getEffectCurrentPosition(soundId);
}
int UAgoraRtcEngine::EnableSoundPositionIndication(bool enabled)
{
	return RtcEngineProxy::enableSoundPositionIndication(enabled);
}
int UAgoraRtcEngine::SetRemoteVoicePosition(int64 uid, float pan, float gain)
{
	return RtcEngineProxy::setRemoteVoicePosition(uid, pan, gain);
}
int UAgoraRtcEngine::EnableSpatialAudio(bool enabled)
{
	return RtcEngineProxy::enableSpatialAudio(enabled);
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParams(int64 uid, FSpatialAudioParams& params)
{
	agora::SpatialAudioParams spatialAudioParams;
	if (params.speaker_azimuthValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_azimuth = params.speaker_azimuth;
	}
	if (params.speaker_elevationValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_elevation = params.speaker_elevation;
	}
	if (params.speaker_distanceValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_distance = params.speaker_distance;
	}
	if (params.speaker_orientationValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_orientation = params.speaker_orientation;
	}
	if (params.enable_blurValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.enable_blur = params.enable_blur;
	}
	if (params.enable_air_absorbValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.enable_air_absorb = params.enable_air_absorb;
	}
	if (params.speaker_attenuationValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_attenuation = params.speaker_attenuation;
	}
	if (params.enable_dopplerValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.enable_doppler = params.enable_doppler;
	}
	return RtcEngineProxy::setRemoteUserSpatialAudioParams(uid, spatialAudioParams);
}
int UAgoraRtcEngine::SetVoiceBeautifierPreset(EVOICE_BEAUTIFIER_PRESET preset)
{
	return RtcEngineProxy::setVoiceBeautifierPreset((agora::rtc::VOICE_BEAUTIFIER_PRESET)preset);
}
int UAgoraRtcEngine::SetAudioEffectPreset(EAUDIO_EFFECT_PRESET preset)
{
	return RtcEngineProxy::setAudioEffectPreset((agora::rtc::AUDIO_EFFECT_PRESET)preset);
}
int UAgoraRtcEngine::SetVoiceConversionPreset(EVOICE_CONVERSION_PRESET preset)
{
	return RtcEngineProxy::setVoiceConversionPreset((agora::rtc::VOICE_CONVERSION_PRESET)preset);
}
int UAgoraRtcEngine::SetAudioEffectParameters(EAUDIO_EFFECT_PRESET preset, int param1, int param2)
{
	return RtcEngineProxy::setAudioEffectParameters((agora::rtc::AUDIO_EFFECT_PRESET)preset, param1, param2);
}
int UAgoraRtcEngine::SetVoiceBeautifierParameters(EVOICE_BEAUTIFIER_PRESET preset, int param1, int param2)
{
	return RtcEngineProxy::setVoiceBeautifierParameters((agora::rtc::VOICE_BEAUTIFIER_PRESET)preset, param1, param2);
}
int UAgoraRtcEngine::SetVoiceConversionParameters(EVOICE_CONVERSION_PRESET preset, int param1, int param2)
{
	return RtcEngineProxy::setVoiceConversionParameters((agora::rtc::VOICE_CONVERSION_PRESET)preset, param1, param2);
}
int UAgoraRtcEngine::SetLocalVoicePitch(float pitch)
{
	return RtcEngineProxy::setLocalVoicePitch(pitch);
}
int UAgoraRtcEngine::SetLocalVoiceEqualization(EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
{
	return RtcEngineProxy::setLocalVoiceEqualization((agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY)bandFrequency, bandGain);
}
int UAgoraRtcEngine::SetLocalVoiceReverb(EAUDIO_REVERB_TYPE reverbKey, int value)
{
	return RtcEngineProxy::setLocalVoiceReverb((agora::rtc::AUDIO_REVERB_TYPE)reverbKey, value);
}
int UAgoraRtcEngine::SetLogFile(FString filePath)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	return RtcEngineProxy::setLogFile(FilePath.c_str());
}
int UAgoraRtcEngine::SetLogFilter(int filter)
{
	return RtcEngineProxy::setLogFilter(filter);
}
int UAgoraRtcEngine::SetLogLevel(ELOG_LEVEL level)
{
	return RtcEngineProxy::setLogLevel((agora::commons::LOG_LEVEL)level);
}
int UAgoraRtcEngine::SetLogFileSize(int fileSizeInKBytes)
{
	return RtcEngineProxy::setLogFileSize(fileSizeInKBytes);
}
int UAgoraRtcEngine::UploadLogFile(FString& requestId)
{
	agora::util::AString _requestId;
	auto ret = RtcEngineProxy::uploadLogFile(_requestId);
	requestId = _requestId->c_str();
	return ret;
}
int UAgoraRtcEngine::SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return RtcEngineProxy::setLocalRenderMode((agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
}
int UAgoraRtcEngine::SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return RtcEngineProxy::setRemoteRenderMode(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
}
int UAgoraRtcEngine::SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return RtcEngineProxy::setLocalVideoMirrorMode((agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
}

int UAgoraRtcEngine::EnableDualStreamMode(bool enabled, FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.height = streamConfig.dimensions.height;
	dim.width = streamConfig.dimensions.width;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	return RtcEngineProxy::enableDualStreamMode(enabled, simulcastStreamConfig);
}
int UAgoraRtcEngine::SetDualStreamMode(ESIMULCAST_STREAM_MODE mode, FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.height = streamConfig.dimensions.height;
	dim.width = streamConfig.dimensions.width;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	return RtcEngineProxy::setDualStreamMode((agora::rtc::SIMULCAST_STREAM_MODE)mode, simulcastStreamConfig);
}
int UAgoraRtcEngine::EnableEchoCancellationExternal(bool enabled, int audioSourceDelay)
{
	return RtcEngineProxy::enableEchoCancellationExternal(enabled, audioSourceDelay);
}
int UAgoraRtcEngine::EnableCustomAudioLocalPlayback(int sourceId, bool enabled)
{
	return RtcEngineProxy::enableCustomAudioLocalPlayback(sourceId, enabled);
}
int UAgoraRtcEngine::StartPrimaryCustomAudioTrack(FAudioTrackConfig& config)
{
	agora::rtc::AudioTrackConfig audioTrackConfig;
	audioTrackConfig.enableLocalPlayback = config.enableLocalPlayback;
	return RtcEngineProxy::startPrimaryCustomAudioTrack(audioTrackConfig);
}
int UAgoraRtcEngine::StopPrimaryCustomAudioTrack()
{
	return RtcEngineProxy::stopPrimaryCustomAudioTrack();
}
int UAgoraRtcEngine::StartSecondaryCustomAudioTrack(FAudioTrackConfig& config)
{
	agora::rtc::AudioTrackConfig audioTrackConfig;
	audioTrackConfig.enableLocalPlayback = config.enableLocalPlayback;
	return RtcEngineProxy::startSecondaryCustomAudioTrack(audioTrackConfig);
}
int UAgoraRtcEngine::StopSecondaryCustomAudioTrack()
{
	return RtcEngineProxy::stopSecondaryCustomAudioTrack();
}
int UAgoraRtcEngine::SetRecordingAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	return RtcEngineProxy::setRecordingAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}
int UAgoraRtcEngine::SetPlaybackAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	return RtcEngineProxy::setPlaybackAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
}
int UAgoraRtcEngine::SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall)
{
	return RtcEngineProxy::setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
}
int UAgoraRtcEngine::SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel)
{
	return RtcEngineProxy::setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
}
int UAgoraRtcEngine::EnableAudioSpectrumMonitor(int intervalInMS)
{
	return RtcEngineProxy::enableAudioSpectrumMonitor(intervalInMS);
}
int UAgoraRtcEngine::DisableAudioSpectrumMonitor()
{
	return RtcEngineProxy::disableAudioSpectrumMonitor();
}

int UAgoraRtcEngine::RegisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	return RtcEngineProxy::registerAudioSpectrumObserver(observer);
}
int UAgoraRtcEngine::UnregisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	return RtcEngineProxy::unregisterAudioSpectrumObserver(observer);
}
int UAgoraRtcEngine::AdjustRecordingSignalVolume(int volume)
{
	return RtcEngineProxy::adjustRecordingSignalVolume(volume);
}
int UAgoraRtcEngine::MuteRecordingSignal(bool mute)
{
	return RtcEngineProxy::muteRecordingSignal(mute);
}
int UAgoraRtcEngine::AdjustPlaybackSignalVolume(int volume)
{
	return RtcEngineProxy::adjustPlaybackSignalVolume(volume);
}
int UAgoraRtcEngine::AdjustUserPlaybackSignalVolume(int uid, int volume)
{
	return RtcEngineProxy::adjustUserPlaybackSignalVolume(uid, volume);
}
int UAgoraRtcEngine::SetLocalPublishFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	return RtcEngineProxy::setLocalPublishFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
}
int UAgoraRtcEngine::SetRemoteSubscribeFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	return RtcEngineProxy::setRemoteSubscribeFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
}
int UAgoraRtcEngine::EnableLoopbackRecording(bool enabled, FString deviceName)
{
	std::string Device = TCHAR_TO_ANSI(*deviceName);
	return RtcEngineProxy::enableLoopbackRecording(enabled, Device.c_str());
}
int UAgoraRtcEngine::AdjustLoopbackSignalVolume(int volume)
{
	return RtcEngineProxy::adjustLoopbackSignalVolume(volume);
}
int UAgoraRtcEngine::GetLoopbackRecordingVolume()
{
	return RtcEngineProxy::getLoopbackRecordingVolume();
}
int UAgoraRtcEngine::EnableInEarMonitoring(bool enabled, int includeAudioFilters)
{
	return RtcEngineProxy::enableInEarMonitoring(enabled, includeAudioFilters);
}
int UAgoraRtcEngine::SetInEarMonitoringVolume(int volume)
{
	return RtcEngineProxy::setInEarMonitoringVolume(volume);
}
int UAgoraRtcEngine::LoadExtensionProvider(FString path, bool unload_after_use)
{
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
	std::string Path = TCHAR_TO_ANSI(*path);

	return RtcEngineProxy::loadExtensionProvider(Path.c_str(), unload_after_use);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}
int UAgoraRtcEngine::SetExtensionProviderProperty(FString provider, FString key, FString value)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Key = TCHAR_TO_ANSI(*key);
	std::string Value = TCHAR_TO_ANSI(*value);
	return RtcEngineProxy::setExtensionProviderProperty(Provider.c_str(), Key.c_str(), Value.c_str());
}
int UAgoraRtcEngine::EnableExtension(FString provider, FString extension, bool enable, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Extension = TCHAR_TO_ANSI(*extension);
	return RtcEngineProxy::enableExtension(Provider.c_str(), Extension.c_str(), enable, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::SetExtensionProperty(FString provider, FString extension, FString key, FString value, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Extension = TCHAR_TO_ANSI(*extension);
	std::string Key = TCHAR_TO_ANSI(*key);
	std::string Value = TCHAR_TO_ANSI(*value);
	return RtcEngineProxy::setExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), Value.c_str(), (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::GetExtensionProperty(FString provider, FString extension, FString key, FString value, int buf_len, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Extension = TCHAR_TO_ANSI(*extension);
	std::string Key = TCHAR_TO_ANSI(*key);
	return RtcEngineProxy::getExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), TCHAR_TO_ANSI(*value), buf_len, (agora::media::MEDIA_SOURCE_TYPE)type);
}
int UAgoraRtcEngine::SetCameraCapturerConfiguration(FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	cameraCapturerConfiguration.cameraDirection = (agora::rtc::CAMERA_DIRECTION)config.cameraDirection;
#else
	sprintf(cameraCapturerConfiguration.deviceId, "%s", TCHAR_TO_UTF8(*config.deviceId));
	//FMemory::Memcpy(cameraCapturerConfiguration.deviceId, *config.deviceId, agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH);
#endif
	agora::rtc::VideoFormat format;
	format.width = config.format.width;
	format.height = config.format.height;
	cameraCapturerConfiguration.format = format;
	cameraCapturerConfiguration.followEncodeDimensionRatio = config.followEncodeDimensionRatio;
	return RtcEngineProxy::setCameraCapturerConfiguration(cameraCapturerConfiguration);
}
int64 UAgoraRtcEngine::CreateCustomVideoTrack()
{
	return RtcEngineProxy::createCustomVideoTrack();
}
int64 UAgoraRtcEngine::CreateCustomEncodedVideoTrack(FSenderOptions& sender_option)
{
	agora::rtc::SenderOptions senderOptions;
	senderOptions.ccMode = (agora::rtc::TCcMode)sender_option.ccMode;
	senderOptions.codecType = (agora::rtc::VIDEO_CODEC_TYPE)sender_option.codecType;
	senderOptions.targetBitrate = sender_option.targetBitrate;
	return RtcEngineProxy::createCustomEncodedVideoTrack(senderOptions);
}
int UAgoraRtcEngine::DestroyCustomVideoTrack(int64 video_track_id)
{
	return RtcEngineProxy::destroyCustomVideoTrack(video_track_id);
}
int UAgoraRtcEngine::DestroyCustomEncodedVideoTrack(int64 video_track_id)
{
	return RtcEngineProxy::destroyCustomEncodedVideoTrack(video_track_id);
}
int UAgoraRtcEngine::SwitchCamera()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::switchCamera();
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsCameraZoomSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::isCameraZoomSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraFaceDetectSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::isCameraFaceDetectSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraTorchSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::isCameraTorchSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraFocusSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::isCameraFocusSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraAutoFocusFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::isCameraAutoFocusFaceModeSupported();
#else
	return false;
#endif
}
int UAgoraRtcEngine::SetCameraZoomFactor(float factor)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::setCameraZoomFactor(factor);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::EnableFaceDetection(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::enableFaceDetection(enabled);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
float UAgoraRtcEngine::GetCameraMaxZoomFactor()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::getCameraMaxZoomFactor();
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraFocusPositionInPreview(float positionX, float positionY)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::setCameraFocusPositionInPreview(positionX, positionY);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraTorchOn(bool isOn)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::setCameraTorchOn(isOn);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraAutoFocusFaceModeEnabled(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::setCameraAutoFocusFaceModeEnabled(enabled);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsCameraExposurePositionSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::isCameraExposurePositionSupported();
#else
	return false;
#endif
}
int UAgoraRtcEngine::SetCameraExposurePosition(float positionXinView, float positionYinView)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxy::setCameraExposurePosition(positionXinView, positionYinView);
#else
	return false;
#endif
}

bool UAgoraRtcEngine::IsCameraAutoExposureFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	return RtcEngineProxy::isCameraAutoExposureFaceModeSupported();
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
	return RtcEngineProxy::setCameraAutoExposureFaceModeEnabled(enabled);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
#endif
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
}
int UAgoraRtcEngine::SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker)
{
#if defined(__ANDROID__)
	return RtcEngineProxy::setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetEnableSpeakerphone(bool speakerOn)
{
#if defined(__ANDROID__)
	return RtcEngineProxy::setEnableSpeakerphone(speakerOn);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsSpeakerphoneEnabled()
{
#if defined(__ANDROID__)
	return RtcEngineProxy::isSpeakerphoneEnabled();
#else
	return false;
#endif
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
	agora::rtc::IScreenCaptureSourceList* screenCaptureNative = RtcEngineProxy::getScreenCaptureSources(thumb, icon, includeScreen);
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
	return RtcEngineProxy::setAudioSessionOperationRestriction((agora::AUDIO_SESSION_OPERATION_RESTRICTION)restriction);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCaptureByDisplayId(int displayId, FRectangle& regionRect, FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)
	agora::rtc::Rectangle rectangle;
	rectangle.x = regionRect.x;
	rectangle.y = regionRect.y;
	rectangle.width = regionRect.width;
	rectangle.height = regionRect.height;
	agora::rtc::ScreenCaptureParameters screenCaptureParameters;
	agora::rtc::VideoDimensions dim;
	dim.width = captureParams.dimensions.width;
	dim.height = captureParams.dimensions.height;
	screenCaptureParameters.dimensions = dim;
	screenCaptureParameters.frameRate = captureParams.frameRate;
	screenCaptureParameters.bitrate = captureParams.bitrate;
	screenCaptureParameters.captureMouseCursor = captureParams.captureMouseCursor;
	screenCaptureParameters.windowFocus = captureParams.windowFocus;
	screenCaptureParameters.excludeWindowList = (agora::view_t*)captureParams.excludeWindowList;
	screenCaptureParameters.excludeWindowCount = captureParams.excludeWindowCount;
	screenCaptureParameters.highLightWidth = captureParams.highLightWidth;
	screenCaptureParameters.highLightColor = captureParams.highLightColor;
	screenCaptureParameters.enableHighLight = captureParams.enableHighLight;
	int ret = RtcEngineProxy::startScreenCaptureByDisplayId(displayId, rectangle, screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCaptureByScreenRect(FRectangle& screenRect, FRectangle& regionRect, FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32)
	agora::rtc::Rectangle rectangle;
	rectangle.x = screenRect.x;
	rectangle.y = screenRect.y;
	rectangle.width = screenRect.width;
	rectangle.height = screenRect.height;
	agora::rtc::ScreenCaptureParameters screenCaptureParameters;
	agora::rtc::VideoDimensions dim;
	dim.width = captureParams.dimensions.width;
	dim.height = captureParams.dimensions.height;
	screenCaptureParameters.dimensions = dim;
	screenCaptureParameters.frameRate = captureParams.frameRate;
	screenCaptureParameters.bitrate = captureParams.bitrate;
	screenCaptureParameters.captureMouseCursor = captureParams.captureMouseCursor;
	screenCaptureParameters.windowFocus = captureParams.windowFocus;
	screenCaptureParameters.excludeWindowList = (agora::view_t*)captureParams.excludeWindowList;
	screenCaptureParameters.excludeWindowCount = captureParams.excludeWindowCount;
	screenCaptureParameters.highLightWidth = captureParams.highLightWidth;
	screenCaptureParameters.highLightColor = captureParams.highLightColor;
	screenCaptureParameters.enableHighLight = captureParams.enableHighLight;
	return RtcEngineProxy::startScreenCaptureByScreenRect(rectangle, rectangle, screenCaptureParameters);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::GetAudioDeviceInfo(FDeviceInfo& deviceInfo)
{
#if defined(__ANDROID__)
	agora::rtc::DeviceInfo Info;
	deviceInfo.isLowLatencyAudioSupported = deviceInfo.isLowLatencyAudioSupported;
	return RtcEngineProxy::getAudioDeviceInfo(Info);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::StartScreenCaptureByWindowId(int64 windowId, FRectangle& regionRect, FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle;
	rectangle.x = regionRect.x;
	rectangle.y = regionRect.y;
	rectangle.width = regionRect.width;
	rectangle.height = regionRect.height;
	agora::rtc::ScreenCaptureParameters screenCaptureParameters;
	agora::rtc::VideoDimensions dis;
	dis.width = captureParams.dimensions.width;
	dis.height = captureParams.dimensions.height;
	screenCaptureParameters.dimensions = dis;
	screenCaptureParameters.frameRate = captureParams.frameRate;
	screenCaptureParameters.bitrate = captureParams.bitrate;
	screenCaptureParameters.captureMouseCursor = captureParams.captureMouseCursor;
	screenCaptureParameters.windowFocus = captureParams.windowFocus;
	screenCaptureParameters.excludeWindowList = (agora::view_t*)captureParams.excludeWindowList;
	screenCaptureParameters.excludeWindowCount = captureParams.excludeWindowCount;
	screenCaptureParameters.highLightWidth = captureParams.highLightWidth;
	screenCaptureParameters.highLightColor = captureParams.highLightColor;
	screenCaptureParameters.enableHighLight = captureParams.enableHighLight;
	return RtcEngineProxy::startScreenCaptureByWindowId((agora::view_t)windowId, rectangle, screenCaptureParameters);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	return RtcEngineProxy::setScreenCaptureContentHint((agora::rtc::VIDEO_CONTENT_HINT)contentHint);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	return RtcEngineProxy::setScreenCaptureScenario((agora::rtc::SCREEN_SCENARIO_TYPE)screenScenario);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::UpdateScreenCaptureRegion(FRectangle& regionRect)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle;
	rectangle.x = regionRect.x;
	rectangle.y = regionRect.y;
	rectangle.width = regionRect.width;
	rectangle.height = regionRect.height;
	return RtcEngineProxy::updateScreenCaptureRegion(rectangle);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::UpdateScreenCaptureParameters(FScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::ScreenCaptureParameters screenCaptureParameters;
	agora::rtc::VideoDimensions dim;
	dim.width = captureParams.dimensions.width;
	dim.height = captureParams.dimensions.height;
	screenCaptureParameters.dimensions = dim;
	screenCaptureParameters.frameRate = captureParams.frameRate;
	screenCaptureParameters.bitrate = captureParams.bitrate;
	screenCaptureParameters.captureMouseCursor = captureParams.captureMouseCursor;
	screenCaptureParameters.windowFocus = captureParams.windowFocus;
	screenCaptureParameters.excludeWindowList = (agora::view_t*)captureParams.excludeWindowList;
	screenCaptureParameters.excludeWindowCount = captureParams.excludeWindowCount;
	screenCaptureParameters.highLightWidth = captureParams.highLightWidth;
	screenCaptureParameters.highLightColor = captureParams.highLightColor;
	screenCaptureParameters.enableHighLight = captureParams.enableHighLight;
	return RtcEngineProxy::updateScreenCaptureParameters(screenCaptureParameters);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCapture(FScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2;
	screenCaptureParameters2.captureAudio = captureParams.captureAudio;
	screenCaptureParameters2.captureVideo = captureParams.captureVideo;
	screenCaptureParameters2.audioParams.sampleRate = captureParams.audioParams.sampleRate;
	screenCaptureParameters2.audioParams.channels = captureParams.audioParams.channels;
	screenCaptureParameters2.audioParams.captureSignalVolume = captureParams.audioParams.captureSignalVolume;
	screenCaptureParameters2.videoParams.bitrate = captureParams.videoParams.bitrate;
	screenCaptureParameters2.videoParams.contentHint = (agora::rtc::VIDEO_CONTENT_HINT)captureParams.videoParams.contentHint;
	screenCaptureParameters2.videoParams.dimensions.height = captureParams.videoParams.dimensions.height;
	screenCaptureParameters2.videoParams.dimensions.width = captureParams.videoParams.dimensions.width;
	screenCaptureParameters2.videoParams.frameRate = captureParams.videoParams.frameRate;
	return RtcEngineProxy::startScreenCapture(screenCaptureParameters2);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}
int UAgoraRtcEngine::UpdateScreenCapture(FScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2;
	screenCaptureParameters2.captureAudio = captureParams.captureAudio;
	screenCaptureParameters2.captureVideo = captureParams.captureVideo;
	screenCaptureParameters2.audioParams.sampleRate = captureParams.audioParams.sampleRate;
	screenCaptureParameters2.audioParams.channels = captureParams.audioParams.channels;
	screenCaptureParameters2.audioParams.captureSignalVolume = captureParams.audioParams.captureSignalVolume;
	screenCaptureParameters2.videoParams.bitrate = captureParams.videoParams.bitrate;
	screenCaptureParameters2.videoParams.contentHint = (agora::rtc::VIDEO_CONTENT_HINT)captureParams.videoParams.contentHint;
	screenCaptureParameters2.videoParams.dimensions.height = captureParams.videoParams.dimensions.height;
	screenCaptureParameters2.videoParams.dimensions.width = captureParams.videoParams.dimensions.width;
	screenCaptureParameters2.videoParams.frameRate = captureParams.videoParams.frameRate;
	return RtcEngineProxy::updateScreenCapture(screenCaptureParameters2);
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StopScreenCapture()
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	return RtcEngineProxy::stopScreenCapture();
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::GetCallId(FString& callId)
{
	agora::util::AString agoraStr;

	int ret = RtcEngineProxy::getCallId(agoraStr);

	callId = agoraStr->c_str();

	return ret;
}
int UAgoraRtcEngine::Rate(FString callId, int rating, FString description)
{
	std::string CallId = TCHAR_TO_ANSI(*callId);
	return RtcEngineProxy::rate(CallId.c_str(), rating, TCHAR_TO_ANSI(*description));
}
int UAgoraRtcEngine::Complain(FString callId, FString description)
{
	std::string CallId = TCHAR_TO_ANSI(*callId);
	std::string Description = TCHAR_TO_ANSI(*description);
	return RtcEngineProxy::complain(CallId.c_str(), Description.c_str());
}
int UAgoraRtcEngine::StartRtmpStreamWithoutTranscoding(FString url)
{
	std::string Url = TCHAR_TO_ANSI(*url);

	return RtcEngineProxy::startRtmpStreamWithoutTranscoding(Url.c_str());
}
int UAgoraRtcEngine::StartRtmpStreamWithTranscoding(FString url, FLiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding;
	liveTranscoding.width = transcoding.width;
	liveTranscoding.height = transcoding.height;
	liveTranscoding.videoBitrate = transcoding.videoBitrate;
	liveTranscoding.videoFramerate = transcoding.videoFramerate;
	liveTranscoding.lowLatency = transcoding.lowLatency;
	liveTranscoding.videoGop = transcoding.videoGop;
	liveTranscoding.videoCodecProfile = (agora::rtc::VIDEO_CODEC_PROFILE_TYPE)transcoding.videoCodecProfile;
	liveTranscoding.backgroundColor = transcoding.backgroundColor;
	liveTranscoding.videoCodecType = (agora::rtc::VIDEO_CODEC_TYPE_FOR_STREAM)transcoding.videoCodecType;
	liveTranscoding.userCount = transcoding.userCount;
	agora::rtc::TranscodingUser* trans = new agora::rtc::TranscodingUser[transcoding.userCount];
	for (int i = 0; i < transcoding.userCount; i++)
	{
		trans[i].alpha = transcoding.transcodingUsers[i].alpha;
		trans[i].audioChannel = transcoding.transcodingUsers[i].audioChannel;
		trans[i].height = transcoding.transcodingUsers[i].height;
		trans[i].uid = transcoding.transcodingUsers[i].uid;
		trans[i].width = transcoding.transcodingUsers[i].width;
		trans[i].x = transcoding.transcodingUsers[i].x;
		trans[i].y = transcoding.transcodingUsers[i].y;
		trans[i].zOrder = transcoding.transcodingUsers[i].zOrder;
	}
	liveTranscoding.transcodingUsers = trans;
	std::string TranscodingExtraInfo = TCHAR_TO_ANSI(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_ANSI(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.watermark[i].url);
		image[i].url = Url.c_str();
		image[i].height = transcoding.watermark[i].height;
		image[i].width = transcoding.watermark[i].width;
		image[i].x = transcoding.watermark[i].x;
		image[i].y = transcoding.watermark[i].y;
		image[i].zOrder = transcoding.watermark[i].zOrder;
	}
	liveTranscoding.watermark = image;
	liveTranscoding.watermarkCount = transcoding.watermarkCount;

	agora::rtc::RtcImage* bgImage = new agora::rtc::RtcImage[transcoding.backgroundImageCount];
	for (int i = 0; i < transcoding.backgroundImageCount; i++)
	{
		bgImage[i].alpha = transcoding.backgroundImage[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.backgroundImage[i].url);
		bgImage[i].url = Url.c_str();
		bgImage[i].height = transcoding.backgroundImage[i].height;
		bgImage[i].width = transcoding.backgroundImage[i].width;
		bgImage[i].x = transcoding.backgroundImage[i].x;
		bgImage[i].y = transcoding.backgroundImage[i].y;
		bgImage[i].zOrder = transcoding.backgroundImage[i].zOrder;
	}
	liveTranscoding.backgroundImage = bgImage;
	liveTranscoding.backgroundImageCount = transcoding.backgroundImageCount;
	if (transcoding.audioSampleRate.GetValue() ==1)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_32000;
	}
	else if (transcoding.audioSampleRate.GetValue() == 2)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_44100;
	}
	else if (transcoding.audioSampleRate.GetValue() == 3)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	}
	liveTranscoding.audioBitrate = transcoding.audioBitrate;
	liveTranscoding.audioChannels = transcoding.audioChannels;
	liveTranscoding.audioCodecProfile = (agora::rtc::AUDIO_CODEC_PROFILE_TYPE)transcoding.audioCodecProfile;

	agora::rtc::LiveStreamAdvancedFeature* feature = new agora::rtc::LiveStreamAdvancedFeature[transcoding.advancedFeatureCount];
	for (int i = 0; i < transcoding.advancedFeatureCount; i++)
	{
		std::string FeatureName = TCHAR_TO_ANSI(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;
	std::string TempUrl = TCHAR_TO_ANSI(*url);
	int ret = RtcEngineProxy::startRtmpStreamWithTranscoding(TempUrl.c_str(), liveTranscoding);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;
	return ret;
}
int UAgoraRtcEngine::UpdateRtmpTranscoding(FLiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding;
	liveTranscoding.width = transcoding.width;
	liveTranscoding.height = transcoding.height;
	liveTranscoding.videoBitrate = transcoding.videoBitrate;
	liveTranscoding.videoFramerate = transcoding.videoFramerate;
	liveTranscoding.lowLatency = transcoding.lowLatency;
	liveTranscoding.videoGop = transcoding.videoGop;
	liveTranscoding.videoCodecProfile = (agora::rtc::VIDEO_CODEC_PROFILE_TYPE)transcoding.videoCodecProfile;
	liveTranscoding.backgroundColor = transcoding.backgroundColor;
	liveTranscoding.videoCodecType = (agora::rtc::VIDEO_CODEC_TYPE_FOR_STREAM)transcoding.videoCodecType;
	liveTranscoding.userCount = transcoding.userCount;
	agora::rtc::TranscodingUser* trans = new agora::rtc::TranscodingUser[transcoding.userCount];
	for (int i = 0; i < transcoding.userCount; i++)
	{
		trans[i].alpha = transcoding.transcodingUsers[i].alpha;
		trans[i].audioChannel = transcoding.transcodingUsers[i].audioChannel;
		trans[i].height = transcoding.transcodingUsers[i].height;
		trans[i].uid = transcoding.transcodingUsers[i].uid;
		trans[i].width = transcoding.transcodingUsers[i].width;
		trans[i].x = transcoding.transcodingUsers[i].x;
		trans[i].y = transcoding.transcodingUsers[i].y;
		trans[i].zOrder = transcoding.transcodingUsers[i].zOrder;
	}
	liveTranscoding.transcodingUsers = trans;
	std::string TranscodingExtraInfo = TCHAR_TO_ANSI(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_ANSI(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.watermark[i].url);
		image[i].url = Url.c_str();
		image[i].height = transcoding.watermark[i].height;
		image[i].width = transcoding.watermark[i].width;
		image[i].x = transcoding.watermark[i].x;
		image[i].y = transcoding.watermark[i].y;
		image[i].zOrder = transcoding.watermark[i].zOrder;
	}
	liveTranscoding.watermark = image;
	liveTranscoding.watermarkCount = transcoding.watermarkCount;

	agora::rtc::RtcImage* bgImage = new agora::rtc::RtcImage[transcoding.backgroundImageCount];
	for (int i = 0; i < transcoding.backgroundImageCount; i++)
	{
		bgImage[i].alpha = transcoding.backgroundImage[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.backgroundImage[i].url);
		bgImage[i].url = Url.c_str();
		bgImage[i].height = transcoding.backgroundImage[i].height;
		bgImage[i].width = transcoding.backgroundImage[i].width;
		bgImage[i].x = transcoding.backgroundImage[i].x;
		bgImage[i].y = transcoding.backgroundImage[i].y;
		bgImage[i].zOrder = transcoding.backgroundImage[i].zOrder;
	}
	liveTranscoding.backgroundImage = bgImage;
	liveTranscoding.backgroundImageCount = transcoding.backgroundImageCount;
	if (transcoding.audioSampleRate.GetValue() == 1)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_32000;
	}
	else if (transcoding.audioSampleRate.GetValue() == 2)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_44100;
	}
	else if (transcoding.audioSampleRate.GetValue() == 3)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	}
	liveTranscoding.audioBitrate = transcoding.audioBitrate;
	liveTranscoding.audioChannels = transcoding.audioChannels;
	liveTranscoding.audioCodecProfile = (agora::rtc::AUDIO_CODEC_PROFILE_TYPE)transcoding.audioCodecProfile;

	agora::rtc::LiveStreamAdvancedFeature* feature = new agora::rtc::LiveStreamAdvancedFeature[transcoding.advancedFeatureCount];
	for (int i = 0; i < transcoding.advancedFeatureCount; i++)
	{
		std::string FeatureName = TCHAR_TO_ANSI(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;
	int ret = RtcEngineProxy::updateRtmpTranscoding(liveTranscoding);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;

	return ret;
}
int UAgoraRtcEngine::StopRtmpStream(FString url)
{
	return RtcEngineProxy::stopRtmpStream(TCHAR_TO_ANSI(*url));
}
int UAgoraRtcEngine::StartLocalVideoTranscoder(FLocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration localTranscoderConfiguration;
	localTranscoderConfiguration.streamCount = config.streamCount;
	agora::rtc::TranscodingVideoStream* videoStream = new agora::rtc::TranscodingVideoStream[config.streamCount];
	for (int i = 0; i < config.streamCount; i++)
	{
		videoStream[i].alpha = config.VideoInputStreams[i].alpha;
		videoStream[i].height = config.VideoInputStreams[i].height;
		std::string ImageUrl = TCHAR_TO_ANSI(*config.VideoInputStreams[i].imageUrl);
		videoStream[i].imageUrl = ImageUrl.c_str();
		videoStream[i].mirror = config.VideoInputStreams[i].mirror;
		videoStream[i].remoteUserUid = config.VideoInputStreams[i].remoteUserUid;
		videoStream[i].sourceType = (agora::media::MEDIA_SOURCE_TYPE)config.VideoInputStreams[i].sourceType;
		videoStream[i].width = config.VideoInputStreams[i].width;
		videoStream[i].x = config.VideoInputStreams[i].x;
		videoStream[i].y = config.VideoInputStreams[i].y;
		videoStream[i].zOrder = config.VideoInputStreams[i].zOrder;
	}
	localTranscoderConfiguration.VideoInputStreams = videoStream;

	agora::rtc::VideoEncoderConfiguration Configration;
	Configration.bitrate = config.videoOutputConfiguration.bitrate;
	Configration.codecType = (agora::rtc::VIDEO_CODEC_TYPE)config.videoOutputConfiguration.codecType;
	Configration.degradationPreference = (agora::rtc::DEGRADATION_PREFERENCE)config.videoOutputConfiguration.bitrate;
	agora::rtc::VideoDimensions dim;
	dim.height = config.videoOutputConfiguration.dimensions.height;
	dim.width = config.videoOutputConfiguration.dimensions.width;

	Configration.dimensions = dim;
	Configration.frameRate = config.videoOutputConfiguration.frameRate;
	Configration.minBitrate = config.videoOutputConfiguration.minBitrate;
	Configration.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)config.videoOutputConfiguration.mirrorMode;
	Configration.orientationMode = (agora::rtc::ORIENTATION_MODE)config.videoOutputConfiguration.orientationMode;
	localTranscoderConfiguration.videoOutputConfiguration = Configration;
	int ret = RtcEngineProxy::startLocalVideoTranscoder(localTranscoderConfiguration);
	delete[] videoStream;
	return ret;
}
int UAgoraRtcEngine::UpdateLocalTranscoderConfiguration(FLocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration localTranscoderConfiguration;
	localTranscoderConfiguration.streamCount = config.streamCount;
	agora::rtc::TranscodingVideoStream* videoStream = new agora::rtc::TranscodingVideoStream[config.streamCount];
	for (int i = 0; i < config.streamCount; i++)
	{
		videoStream[i].alpha = config.VideoInputStreams[i].alpha;
		videoStream[i].height = config.VideoInputStreams[i].height;
		std::string ImageUrl = TCHAR_TO_ANSI(*config.VideoInputStreams[i].imageUrl);
		videoStream[i].imageUrl = ImageUrl.c_str();
		videoStream[i].mirror = config.VideoInputStreams[i].mirror;
		videoStream[i].remoteUserUid = config.VideoInputStreams[i].remoteUserUid;
		videoStream[i].sourceType = (agora::media::MEDIA_SOURCE_TYPE)config.VideoInputStreams[i].sourceType;
		videoStream[i].width = config.VideoInputStreams[i].width;
		videoStream[i].x = config.VideoInputStreams[i].x;
		videoStream[i].y = config.VideoInputStreams[i].y;
		videoStream[i].zOrder = config.VideoInputStreams[i].zOrder;
	}
	localTranscoderConfiguration.VideoInputStreams = videoStream;

	agora::rtc::VideoEncoderConfiguration Configration;
	Configration.bitrate = config.videoOutputConfiguration.bitrate;
	Configration.codecType = (agora::rtc::VIDEO_CODEC_TYPE)config.videoOutputConfiguration.codecType;
	Configration.degradationPreference = (agora::rtc::DEGRADATION_PREFERENCE)config.videoOutputConfiguration.bitrate;
	agora::rtc::VideoDimensions dim;
	dim.height = config.videoOutputConfiguration.dimensions.height;
	dim.width = config.videoOutputConfiguration.dimensions.width;

	Configration.dimensions = dim;
	Configration.frameRate = config.videoOutputConfiguration.frameRate;
	Configration.minBitrate = config.videoOutputConfiguration.minBitrate;
	Configration.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)config.videoOutputConfiguration.mirrorMode;
	Configration.orientationMode = (agora::rtc::ORIENTATION_MODE)config.videoOutputConfiguration.orientationMode;
	localTranscoderConfiguration.videoOutputConfiguration = Configration;
	delete[] videoStream;
	return RtcEngineProxy::updateLocalTranscoderConfiguration(localTranscoderConfiguration);
}
int UAgoraRtcEngine::StopLocalVideoTranscoder()
{
	return RtcEngineProxy::stopLocalVideoTranscoder();
}
int UAgoraRtcEngine::StartPrimaryCameraCapture(FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration;
	agora::rtc::VideoFormat format;
	format.width = config.format.width;
	format.height = config.format.height;
	cameraCapturerConfiguration.format = format;
	cameraCapturerConfiguration.followEncodeDimensionRatio = config.followEncodeDimensionRatio;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	cameraCapturerConfiguration.cameraDirection = (agora::rtc::CAMERA_DIRECTION)config.cameraDirection;
#else
	sprintf(cameraCapturerConfiguration.deviceId, "%s", TCHAR_TO_UTF8(*config.deviceId));
#endif
	
	return RtcEngineProxy::startPrimaryCameraCapture(cameraCapturerConfiguration);
}
int UAgoraRtcEngine::StartSecondaryCameraCapture(FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration;
	agora::rtc::VideoFormat format;
	cameraCapturerConfiguration.format.width = config.format.width;
	cameraCapturerConfiguration.format.height = config.format.height;
	cameraCapturerConfiguration.followEncodeDimensionRatio = config.followEncodeDimensionRatio;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	cameraCapturerConfiguration.cameraDirection = (agora::rtc::CAMERA_DIRECTION)config.cameraDirection;
#else
	sprintf(cameraCapturerConfiguration.deviceId,"%s", TCHAR_TO_UTF8(*config.deviceId));
	//FMemory::Memcpy(cameraCapturerConfiguration.deviceId, *config.deviceId, agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH);
#endif
	return RtcEngineProxy::startSecondaryCameraCapture(cameraCapturerConfiguration);
}
int UAgoraRtcEngine::StopPrimaryCameraCapture()
{
	return RtcEngineProxy::stopPrimaryCameraCapture();
}
int UAgoraRtcEngine::StopSecondaryCameraCapture()
{
	return RtcEngineProxy::stopSecondaryCameraCapture();
}
int UAgoraRtcEngine::SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, EVIDEO_ORIENTATION orientation)
{
	return RtcEngineProxy::setCameraDeviceOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, (agora::rtc::VIDEO_ORIENTATION)orientation);
}
int UAgoraRtcEngine::SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, EVIDEO_ORIENTATION orientation)
{
	return RtcEngineProxy::setScreenCaptureOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, (agora::rtc::VIDEO_ORIENTATION)orientation);
}
int UAgoraRtcEngine::StartPrimaryScreenCapture(FScreenCaptureConfiguration& config)
{
	agora::rtc::ScreenCaptureConfiguration screenCaptureConfiguration;
	screenCaptureConfiguration.isCaptureWindow = config.isCaptureWindow;
	screenCaptureConfiguration.displayId = config.displayId;
	agora::rtc::Rectangle screenRect;
	screenRect.x = config.screenRect.x;
	screenRect.width = config.screenRect.width;
	screenRect.height = config.screenRect.height;
	screenRect.y = config.screenRect.y;
	screenCaptureConfiguration.screenRect = screenRect;
	screenCaptureConfiguration.windowId = (agora::view_t)config.windowId;
	agora::rtc::ScreenCaptureParameters params;
	params.bitrate = config.params.bitrate;
	params.captureMouseCursor = config.params.captureMouseCursor;
	agora::rtc::VideoDimensions dis;
	dis.height = config.params.dimensions.height;
	dis.width = config.params.dimensions.width;
	params.dimensions = dis;
	params.enableHighLight = config.params.enableHighLight;
	params.excludeWindowCount = config.params.excludeWindowCount;
	params.excludeWindowList = (agora::view_t*)config.params.excludeWindowList;
	params.frameRate = config.params.frameRate;
	params.highLightColor = config.params.highLightColor;
	params.highLightWidth = config.params.highLightWidth;
	params.windowFocus = config.params.windowFocus;

	screenCaptureConfiguration.params = params;
	agora::rtc::Rectangle tangle;
	tangle.height = config.regionRect.height;
	tangle.width = config.regionRect.width;
	tangle.x = config.regionRect.x;
	tangle.y = config.regionRect.y;
	screenCaptureConfiguration.regionRect = tangle;
	return RtcEngineProxy::startPrimaryScreenCapture(screenCaptureConfiguration);
}
int UAgoraRtcEngine::StartSecondaryScreenCapture(FScreenCaptureConfiguration& config)
{
	agora::rtc::ScreenCaptureConfiguration screenCaptureConfiguration;
	screenCaptureConfiguration.isCaptureWindow = config.isCaptureWindow;
	screenCaptureConfiguration.displayId = config.displayId;

	agora::rtc::Rectangle screenRect;
	screenRect.height = config.screenRect.height;
	screenRect.width = config.screenRect.width;
	screenRect.x = config.screenRect.x;
	screenRect.y = config.screenRect.y;

	screenCaptureConfiguration.screenRect = screenRect;
	screenCaptureConfiguration.windowId = (agora::view_t)config.windowId;

	agora::rtc::ScreenCaptureParameters params;
	params.bitrate = config.params.bitrate;
	params.captureMouseCursor = config.params.captureMouseCursor;
	agora::rtc::VideoDimensions dis;
	dis.height = config.params.dimensions.height;
	dis.width = config.params.dimensions.width;
	params.dimensions = dis;
	params.enableHighLight = config.params.enableHighLight;
	params.excludeWindowCount = config.params.excludeWindowCount;
	params.excludeWindowList = (agora::view_t*)config.params.excludeWindowList;
	params.frameRate = config.params.frameRate;
	params.highLightColor = config.params.highLightColor;
	params.highLightWidth = config.params.highLightWidth;
	params.windowFocus = config.params.windowFocus;

	screenCaptureConfiguration.params = params;

	agora::rtc::Rectangle tangle;
	tangle.height = config.regionRect.height;
	tangle.width = config.regionRect.width;
	tangle.x = config.regionRect.x;
	tangle.y = config.regionRect.y;
	screenCaptureConfiguration.regionRect = tangle;
	return RtcEngineProxy::startSecondaryScreenCapture(screenCaptureConfiguration);
}
int UAgoraRtcEngine::StopPrimaryScreenCapture()
{
	return RtcEngineProxy::stopPrimaryScreenCapture();
}
int UAgoraRtcEngine::StopSecondaryScreenCapture()
{
	return RtcEngineProxy::stopSecondaryScreenCapture();
}
ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionState()
{
	return (ECONNECTION_STATE_TYPE)RtcEngineProxy::getConnectionState();
}
bool UAgoraRtcEngine::RegisterEventHandler(UIRtcEngineEventHandler* eventHandler)
{
	return RtcEngineProxy::registerEventHandler(eventHandler);
}
bool UAgoraRtcEngine::UnregisterEventHandler(UIRtcEngineEventHandler* eventHandler)
{
	return RtcEngineProxy::unregisterEventHandler(eventHandler);
}
int UAgoraRtcEngine::SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority)
{
	return RtcEngineProxy::setRemoteUserPriority(uid, (agora::rtc::PRIORITY_TYPE)userPriority);
}
int UAgoraRtcEngine::RegisterPacketObserver(UIPacketObserver* observer)
{
	return RtcEngineProxy::registerPacketObserver(observer);
}
int UAgoraRtcEngine::SetEncryptionMode(FString encryptionMode)
{
	std::string EncryptionMode = TCHAR_TO_ANSI(*encryptionMode);
	return RtcEngineProxy::setEncryptionMode(EncryptionMode.c_str());
}
int UAgoraRtcEngine::SetEncryptionSecret(FString secret)
{
	std::string Secret = TCHAR_TO_ANSI(*secret);
	return RtcEngineProxy::setEncryptionSecret(Secret.c_str());
}
int UAgoraRtcEngine::EnableEncryption(bool enabled, FEncryptionConfig& config)
{
	agora::rtc::EncryptionConfig encryptionConfig;
	encryptionConfig.encryptionMode = (agora::rtc::ENCRYPTION_MODE)config.encryptionMode;
	std::string EncryptionKey = TCHAR_TO_ANSI(*config.encryptionKey);
	encryptionConfig.encryptionKey = EncryptionKey.c_str();
	std::string encryptionKdfSalt = TCHAR_TO_ANSI(*config.encryptionKdfSalt);
	FMemory::Memcpy(encryptionConfig.encryptionKdfSalt, encryptionKdfSalt.c_str(), strlen(encryptionKdfSalt.c_str())+1);
	int ret = RtcEngineProxy::enableEncryption(enabled, encryptionConfig);
	return ret;
}
int UAgoraRtcEngine::CreateDataStream(int& streamId, FDataStreamConfig& config)
{
	agora::rtc::DataStreamConfig dataStreamConfig;
	dataStreamConfig.syncWithAudio = config.syncWithAudio;
	dataStreamConfig.ordered = config.ordered;
	return RtcEngineProxy::createDataStream(&streamId, dataStreamConfig);
}
int UAgoraRtcEngine::SendStreamMessage(int streamId, FString data)
{
	const char* Data = TCHAR_TO_UTF8(*data);

	return RtcEngineProxy::sendStreamMessage(streamId, Data, strlen(Data)+1);
}
int UAgoraRtcEngine::AddVideoWatermark(FString watermarkUrl, FWatermarkOptions& options)
{
	agora::rtc::WatermarkOptions watermarkOptions;
	watermarkOptions.visibleInPreview = options.visibleInPreview;
	agora::rtc::Rectangle LandscapeMode;
	LandscapeMode.height = options.positionInLandscapeMode.height;
	LandscapeMode.width = options.positionInLandscapeMode.width;
	watermarkOptions.positionInLandscapeMode = LandscapeMode;
	agora::rtc::Rectangle positionInPortraitMode;
	positionInPortraitMode.height = options.positionInPortraitMode.height;
	positionInPortraitMode.width = options.positionInPortraitMode.width;
	watermarkOptions.positionInPortraitMode = positionInPortraitMode;
	agora::rtc::WatermarkRatio markradio;
	markradio.xRatio = options.watermarkRatio.xRatio;
	markradio.yRatio = options.watermarkRatio.xRatio;
	markradio.widthRatio = options.watermarkRatio.widthRatio;
	watermarkOptions.watermarkRatio = markradio;
	watermarkOptions.mode = (agora::rtc::WATERMARK_FIT_MODE)options.mode;
	std::string WatermarkUrl= TCHAR_TO_ANSI(*watermarkUrl);
	return RtcEngineProxy::addVideoWatermark(WatermarkUrl.c_str(), watermarkOptions);
}

int UAgoraRtcEngine::ClearVideoWatermarks()
{
	return RtcEngineProxy::clearVideoWatermarks();
}

int UAgoraRtcEngine::PauseAudio()
{
	return RtcEngineProxy::pauseAudio();
}
int UAgoraRtcEngine::ResumeAudio()
{
	return RtcEngineProxy::resumeAudio();
}
int UAgoraRtcEngine::EnableWebSdkInteroperability(bool enabled)
{
	return RtcEngineProxy::enableWebSdkInteroperability(enabled);
}
int UAgoraRtcEngine::SendCustomReportMessage(FString id, FString category, FString event, FString label, int value)
{
	std::string Id = TCHAR_TO_ANSI(*id);
	std::string Category = TCHAR_TO_ANSI(*category);
	std::string Event = TCHAR_TO_ANSI(*event);
	std::string Label = TCHAR_TO_ANSI(*label);
	return RtcEngineProxy::sendCustomReportMessage(Id.c_str(), Category.c_str(), Event.c_str(), Label.c_str(), value);
}

int UAgoraRtcEngine::RegisterMediaMetadataObserver(UIMetadataObserver* observer, EMETADATA_TYPE type)
{
	return RtcEngineProxy::registerMediaMetadataObserver(observer, (agora::rtc::IMetadataObserver::METADATA_TYPE)type);
}
int UAgoraRtcEngine::UnregisterMediaMetadataObserver(UIMetadataObserver* observer, EMETADATA_TYPE type)
{
	return RtcEngineProxy::unregisterMediaMetadataObserver(observer, (agora::rtc::IMetadataObserver::METADATA_TYPE)type);
}
int UAgoraRtcEngine::StartAudioFrameDump(FString channel_id, int64 user_id, FString location, FString uuid, FString passwd, int64 duration_ms, bool auto_upload)
{
	std::string Channel_id = TCHAR_TO_ANSI(*channel_id);
	std::string Location = TCHAR_TO_ANSI(*location);
	std::string Uuid = TCHAR_TO_ANSI(*uuid);
	std::string Passwd = TCHAR_TO_ANSI(*passwd);
	return RtcEngineProxy::startAudioFrameDump(Channel_id.c_str(), user_id, Location.c_str(), Uuid.c_str(), Passwd.c_str(), duration_ms, auto_upload);
}
int UAgoraRtcEngine::RegisterLocalUserAccount(FString appId, FString userAccount)
{
	std::string AppId = TCHAR_TO_ANSI(*appId);
	std::string UserAccount = TCHAR_TO_ANSI(*userAccount);
	return RtcEngineProxy::registerLocalUserAccount(AppId.c_str(), UserAccount.c_str());
}
int UAgoraRtcEngine::JoinChannelWithUserAccount(FString token, FString channelId, FString userAccount, FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryCameraTrack = options.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	if (options.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureVideo = options.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureAudio = options.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#else
	if (options.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenTrack = options.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryScreenTrack = options.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#endif
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioSourceId != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioSourceId = options.publishCustomAudioSourceId == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackEnableAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackEnableAec = options.publishCustomAudioTrackEnableAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishDirectCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishDirectCustomAudioTrack = options.publishDirectCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackAec = options.publishCustomAudioTrackAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishEncodedVideoTrack = options.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerVideoTrack = options.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishTrancodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishTrancodedVideoTrack = options.publishTrancodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeAudio = options.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeVideo = options.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableAudioRecordingOrPlayout = options.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.clientRoleTypeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)options.clientRoleType;
	}
	if (options.audienceLatencyLevelValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	}
	if (options.defaultVideoStreamValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)options.defaultVideoStreamType;
	}
	if (options.channelProfileValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)options.channelProfile;
	}
	if (options.audioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audioDelayMs = options.audioDelayMs;
	}
	if (options.mediaPlayerAudioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.mediaPlayerAudioDelayMs = options.mediaPlayerAudioDelayMs;
	}
	if (options.tokenValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		std::string Token = TCHAR_TO_ANSI(*options.token);
		channelMediaOptions.token = Token.c_str();
	}
	if (options.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableBuiltInMediaEncryption = options.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishRhythmPlayerTrack = options.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isInteractiveAudience = options.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	if (options.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	std::string Token = TCHAR_TO_ANSI(*token);
	std::string ChannelId = TCHAR_TO_ANSI(*channelId);
	std::string UserAccount = TCHAR_TO_ANSI(*userAccount);
	return RtcEngineProxy::joinChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions);
}

int UAgoraRtcEngine::JoinChannelWithUserAccountEx(FString token, FString channelId, FString userAccount, FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryCameraTrack = options.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	if (options.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureVideo = options.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureAudio = options.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#else
	if (options.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenTrack = options.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryScreenTrack = options.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#endif
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioSourceId != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioSourceId = options.publishCustomAudioSourceId == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackEnableAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackEnableAec = options.publishCustomAudioTrackEnableAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishDirectCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishDirectCustomAudioTrack = options.publishDirectCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackAec = options.publishCustomAudioTrackAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishEncodedVideoTrack = options.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerVideoTrack = options.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishTrancodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishTrancodedVideoTrack = options.publishTrancodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeAudio = options.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeVideo = options.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableAudioRecordingOrPlayout = options.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.clientRoleTypeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)options.clientRoleType;
	}
	if (options.audienceLatencyLevelValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	}
	if (options.defaultVideoStreamValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)options.defaultVideoStreamType;
	}
	if (options.channelProfileValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)options.channelProfile;
	}
	if (options.audioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audioDelayMs = options.audioDelayMs;
	}
	if (options.mediaPlayerAudioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.mediaPlayerAudioDelayMs = options.mediaPlayerAudioDelayMs;
	}
	if (options.tokenValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		std::string Token = TCHAR_TO_ANSI(*options.token);
		channelMediaOptions.token = Token.c_str();
	}
	if (options.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableBuiltInMediaEncryption = options.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishRhythmPlayerTrack = options.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isInteractiveAudience = options.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	if (options.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	std::string Token = TCHAR_TO_ANSI(*token);
	std::string ChannelId = TCHAR_TO_ANSI(*channelId);
	std::string UserAccount = TCHAR_TO_ANSI(*userAccount);
	return RtcEngineProxy::joinChannelWithUserAccountEx(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions, eventHandler);
}
int UAgoraRtcEngine::GetUserInfoByUserAccount(FString userAccount, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	std::string UserAccount = TCHAR_TO_ANSI(*userAccount);
	int ret = RtcEngineProxy::getUserInfoByUserAccount(UserAccount.c_str(), &info);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUid(int64 uid, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	int ret = RtcEngineProxy::getUserInfoByUid(uid, &info);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;
	return ret;
}
int UAgoraRtcEngine::StartChannelMediaRelay(FChannelMediaRelayConfiguration& configuration)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration;
	agora::rtc::ChannelMediaInfo* mediaInfo = new agora::rtc::ChannelMediaInfo();
	std::string ChannelName = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
	mediaInfo->channelName = ChannelName.c_str();
	std::string Token = TCHAR_TO_ANSI(*configuration.srcInfo.token);
	mediaInfo->token = Token.c_str();
	mediaInfo->uid = configuration.srcInfo.uid;
	channelMediaRelayConfiguration.srcInfo = mediaInfo;
	agora::rtc::ChannelMediaInfo* mediaInfos = new agora::rtc::ChannelMediaInfo[configuration.destCount];
	for (int i = 0; i < configuration.destCount; i++)
	{
		std::string ChannelNameTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].channelName = ChannelNameTemp.c_str();
		std::string TokenTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].token = TokenTemp.c_str();
		mediaInfos[i].uid = configuration.destInfos[i].uid;
	}
	channelMediaRelayConfiguration.destInfos = mediaInfos;
	channelMediaRelayConfiguration.destCount = configuration.destCount;
	int ret = RtcEngineProxy::startChannelMediaRelay(channelMediaRelayConfiguration);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}
int UAgoraRtcEngine::UpdateChannelMediaRelay(FChannelMediaRelayConfiguration& configuration)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration;
	agora::rtc::ChannelMediaInfo* mediaInfo = new agora::rtc::ChannelMediaInfo();
	std::string ChannelName = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
	mediaInfo->channelName = ChannelName.c_str();
	std::string Token = TCHAR_TO_ANSI(*configuration.srcInfo.token);
	mediaInfo->token = Token.c_str();
	mediaInfo->uid = configuration.srcInfo.uid;
	channelMediaRelayConfiguration.srcInfo = mediaInfo;
	agora::rtc::ChannelMediaInfo* mediaInfos = new agora::rtc::ChannelMediaInfo[configuration.destCount];
	for (int i = 0; i < configuration.destCount; i++)
	{
		std::string ChannelNameTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].channelName = ChannelNameTemp.c_str();
		std::string TokenTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].token = TokenTemp.c_str();
		mediaInfos[i].uid = configuration.destInfos[i].uid;
	}
	channelMediaRelayConfiguration.destInfos = mediaInfos;
	channelMediaRelayConfiguration.destCount = configuration.destCount;
	int ret = RtcEngineProxy::updateChannelMediaRelay(channelMediaRelayConfiguration);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}
int UAgoraRtcEngine::StopChannelMediaRelay()
{
	return RtcEngineProxy::stopChannelMediaRelay();
}
int UAgoraRtcEngine::PauseAllChannelMediaRelay()
{
	return RtcEngineProxy::pauseAllChannelMediaRelay();
}
int UAgoraRtcEngine::ResumeAllChannelMediaRelay()
{
	return RtcEngineProxy::resumeAllChannelMediaRelay();
}
int UAgoraRtcEngine::SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile)
{
	return RtcEngineProxy::setDirectCdnStreamingAudioConfiguration((agora::rtc::AUDIO_PROFILE_TYPE)profile);
}
int UAgoraRtcEngine::SetDirectCdnStreamingVideoConfiguration(FVideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration;
	videoEncoderConfiguration.codecType = (agora::rtc::VIDEO_CODEC_TYPE)config.codecType;
	agora::rtc::VideoDimensions dimensions;
	dimensions.height = config.dimensions.height;
	dimensions.width = config.dimensions.width;
	videoEncoderConfiguration.dimensions = dimensions;
	videoEncoderConfiguration.frameRate = config.frameRate;
	videoEncoderConfiguration.bitrate = config.bitrate;
	videoEncoderConfiguration.minBitrate = config.minBitrate;
	videoEncoderConfiguration.orientationMode = (agora::rtc::ORIENTATION_MODE)config.orientationMode;
	videoEncoderConfiguration.degradationPreference = (agora::rtc::DEGRADATION_PREFERENCE)config.degradationPreference;
	videoEncoderConfiguration.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)config.mirrorMode;
	return RtcEngineProxy::setDirectCdnStreamingVideoConfiguration(videoEncoderConfiguration);
}
int UAgoraRtcEngine::StartDirectCdnStreaming(UIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options)
{
	agora::rtc::DirectCdnStreamingMediaOptions directCdnStreamingMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	std::string PublishUrl = TCHAR_TO_ANSI(*publishUrl);
	return RtcEngineProxy::startDirectCdnStreaming(eventHandler, PublishUrl.c_str(), directCdnStreamingMediaOptions);
}
int UAgoraRtcEngine::StopDirectCdnStreaming()
{
	return RtcEngineProxy::stopDirectCdnStreaming();
}
int UAgoraRtcEngine::UpdateDirectCdnStreamingMediaOptions(FDirectCdnStreamingMediaOptions& options)
{
	agora::rtc::DirectCdnStreamingMediaOptions directCdnStreamingMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		directCdnStreamingMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	return RtcEngineProxy::updateDirectCdnStreamingMediaOptions(directCdnStreamingMediaOptions);
}
int UAgoraRtcEngine::StartRhythmPlayer(FString sound1, FString sound2, FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig;
	agoraRhythmPlayerConfig.beatsPerMeasure = config.beatsPerMeasure;
	agoraRhythmPlayerConfig.beatsPerMinute = config.beatsPerMinute;
	std::string Sound1 = TCHAR_TO_ANSI(*sound1);
	std::string Sound2 = TCHAR_TO_ANSI(*sound2);
	return RtcEngineProxy::startRhythmPlayer(Sound1.c_str(), Sound1.c_str(), agoraRhythmPlayerConfig);
}
int UAgoraRtcEngine::StopRhythmPlayer()
{
	return RtcEngineProxy::stopRhythmPlayer();
}
int UAgoraRtcEngine::ConfigRhythmPlayer(FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig;
	agoraRhythmPlayerConfig.beatsPerMeasure = config.beatsPerMeasure;
	agoraRhythmPlayerConfig.beatsPerMinute = config.beatsPerMinute;
	return RtcEngineProxy::configRhythmPlayer(agoraRhythmPlayerConfig);
}
int UAgoraRtcEngine::TakeSnapshot(int64 uid, FString filePath)
{
	std::string Filepath = TCHAR_TO_ANSI(*filePath);

	return RtcEngineProxy::takeSnapshot(uid, Filepath.c_str());
}
int UAgoraRtcEngine::EnableContentInspect(bool enabled, FContentInspectConfig& config)
{
	agora::media::ContentInspectConfig contentInspectConfig;
	std::string ExtraInfo = TCHAR_TO_ANSI(*config.extraInfo);
	contentInspectConfig.extraInfo = ExtraInfo.c_str();
	agora::media::ContentInspectModule modules[MAX_CONTENT_INSPECT_MODULE_COUNT];
	for (int i = 0; i < config.moduleCount; i++)
	{
		modules[i].interval = config.modules[i].interval;
		modules[i].type = (agora::media::CONTENT_INSPECT_TYPE)config.modules[i].type;
	}
	FMemory::Memcpy(contentInspectConfig.modules, modules, sizeof(agora::media::ContentInspectModule) * config.moduleCount);
	contentInspectConfig.moduleCount = config.moduleCount;
	int ret = RtcEngineProxy::enableContentInspect(enabled, contentInspectConfig);
	return ret;
}
int UAgoraRtcEngine::AdjustCustomAudioPublishVolume(int64 sourceId, int volume)
{
	return RtcEngineProxy::adjustCustomAudioPublishVolume(sourceId, volume);
}
int UAgoraRtcEngine::AdjustCustomAudioPlayoutVolume(int64 sourceId, int volume)
{
	return RtcEngineProxy::adjustCustomAudioPlayoutVolume(sourceId, volume);
}
int UAgoraRtcEngine::SetCloudProxy(ECLOUD_PROXY_TYPE proxyType)
{
	return RtcEngineProxy::setCloudProxy((agora::rtc::CLOUD_PROXY_TYPE)proxyType);
}
int UAgoraRtcEngine::SetLocalAccessPoint(FLocalAccessPointConfiguration& config)
{
	agora::rtc::LocalAccessPointConfiguration localAccessPointConfiguration;
	std::string Iplist = TCHAR_TO_ANSI(*config.ipList);
	const char* iplist = Iplist.c_str();
	localAccessPointConfiguration.ipList = &iplist;
	localAccessPointConfiguration.ipListSize = config.ipListSize;
	std::string DomainList = TCHAR_TO_ANSI(*config.domainList);
	const char* domainList = DomainList.c_str();
	localAccessPointConfiguration.domainList = &domainList;
	localAccessPointConfiguration.domainListSize = config.domainListSize;
	std::string VerifyDomainName = TCHAR_TO_ANSI(*config.domainList);
	localAccessPointConfiguration.verifyDomainName = VerifyDomainName.c_str();
	localAccessPointConfiguration.mode = (agora::rtc::LOCAL_PROXY_MODE)config.mode;
	return RtcEngineProxy::setLocalAccessPoint(localAccessPointConfiguration);
}
int UAgoraRtcEngine::SetAdvancedAudioOptions(FAdvancedAudioOptions& options)
{
	agora::rtc::AdvancedAudioOptions advancedAudioOptions;
	if (options.audioProcessingChannelsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		advancedAudioOptions.audioProcessingChannels = options.audioProcessingChannels;
	}
	return RtcEngineProxy::setAdvancedAudioOptions(advancedAudioOptions);
}
int UAgoraRtcEngine::SetAVSyncSource(FString channelId, int64 uid)
{
	std::string ChannelId = TCHAR_TO_ANSI(*channelId);
	return RtcEngineProxy::setAVSyncSource(ChannelId.c_str(), uid);
}
int UAgoraRtcEngine::EnableVideoImageSource(bool enable, FImageTrackOptions& options)
{
	agora::rtc::ImageTrackOptions imageTrackOptions;
	std::string ImageUrl = TCHAR_TO_ANSI(*options.imageUrl);
	imageTrackOptions.imageUrl = ImageUrl.c_str();
	imageTrackOptions.fps = options.fps;
	return RtcEngineProxy::enableVideoImageSource(enable, imageTrackOptions);
}
int UAgoraRtcEngine::JoinChannelEx(FString token, FRtcConnection& connection, FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string channel = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = channel.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::ChannelMediaOptions channelMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryCameraTrack = options.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	if (options.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureVideo = options.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureAudio = options.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#else
	if (options.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenTrack = options.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryScreenTrack = options.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#endif
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioSourceId != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioSourceId = options.publishCustomAudioSourceId == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackEnableAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackEnableAec = options.publishCustomAudioTrackEnableAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishDirectCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishDirectCustomAudioTrack = options.publishDirectCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackAec = options.publishCustomAudioTrackAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishEncodedVideoTrack = options.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerVideoTrack = options.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishTrancodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishTrancodedVideoTrack = options.publishTrancodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeAudio = options.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeVideo = options.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableAudioRecordingOrPlayout = options.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.clientRoleTypeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)options.clientRoleType;
	}
	if (options.audienceLatencyLevelValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	}
	if (options.defaultVideoStreamValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)options.defaultVideoStreamType;
	}
	if (options.channelProfileValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)options.channelProfile;
	}
	if (options.audioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audioDelayMs = options.audioDelayMs;
	}
	if (options.mediaPlayerAudioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.mediaPlayerAudioDelayMs = options.mediaPlayerAudioDelayMs;
	}
	if (options.tokenValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		std::string Token = TCHAR_TO_ANSI(*options.token);

		channelMediaOptions.token = Token.c_str();
	}
	if (options.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableBuiltInMediaEncryption = options.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishRhythmPlayerTrack = options.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isInteractiveAudience = options.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	if (options.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	std::string Token = TCHAR_TO_ANSI(*token);

	return RtcEngineProxy::joinChannelEx(Token.c_str(), rtcConnection, channelMediaOptions, eventHandler);
}


int UAgoraRtcEngine::LeaveChannelEx(const FRtcConnection& connection, const FLeaveChannelOptions& options)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::LeaveChannelOptions leaveChannelOptions;
	if (options.stopAudioMixing != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		leaveChannelOptions.stopAudioMixing = options.stopAudioMixing == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.stopAllEffect != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		leaveChannelOptions.stopAllEffect = options.stopAllEffect == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.stopMicrophoneRecording != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		leaveChannelOptions.stopMicrophoneRecording = options.stopMicrophoneRecording == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}

	return RtcEngineProxy::leaveChannelEx(rtcConnection, leaveChannelOptions);
}

int UAgoraRtcEngine::UpdateChannelMediaOptionsEx(FChannelMediaOptions& options, FRtcConnection& connection)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;
	if (options.publishCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCameraTrack = options.publishCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryCameraTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryCameraTrack = options.publishSecondaryCameraTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMicrophoneTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMicrophoneTrack = options.publishMicrophoneTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	if (options.publishScreenCaptureVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureVideo = options.publishScreenCaptureVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishScreenCaptureAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenCaptureAudio = options.publishScreenCaptureAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#else
	if (options.publishScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishScreenTrack = options.publishScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishSecondaryScreenTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishSecondaryScreenTrack = options.publishSecondaryScreenTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
#endif
	if (options.publishCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrack = options.publishCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioSourceId != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioSourceId = options.publishCustomAudioSourceId == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackEnableAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackEnableAec = options.publishCustomAudioTrackEnableAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishDirectCustomAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishDirectCustomAudioTrack = options.publishDirectCustomAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomAudioTrackAec != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomAudioTrackAec = options.publishCustomAudioTrackAec == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishCustomVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishCustomVideoTrack = options.publishCustomVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishEncodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishEncodedVideoTrack = options.publishEncodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerAudioTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerAudioTrack = options.publishMediaPlayerAudioTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerVideoTrack = options.publishMediaPlayerVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishTrancodedVideoTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishTrancodedVideoTrack = options.publishTrancodedVideoTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeAudio != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeAudio = options.autoSubscribeAudio == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.autoSubscribeVideo != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.autoSubscribeVideo = options.autoSubscribeVideo == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.enableAudioRecordingOrPlayout != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableAudioRecordingOrPlayout = options.enableAudioRecordingOrPlayout == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishMediaPlayerIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishMediaPlayerId = options.publishMediaPlayerId;
	}
	if (options.clientRoleTypeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.clientRoleType = (agora::rtc::CLIENT_ROLE_TYPE)options.clientRoleType;
	}
	if (options.audienceLatencyLevelValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	}
	if (options.defaultVideoStreamValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.defaultVideoStreamType = (agora::rtc::VIDEO_STREAM_TYPE)options.defaultVideoStreamType;
	}
	if (options.channelProfileValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.channelProfile = (agora::CHANNEL_PROFILE_TYPE)options.channelProfile;
	}
	if (options.audioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.audioDelayMs = options.audioDelayMs;
	}
	if (options.mediaPlayerAudioDelayMsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.mediaPlayerAudioDelayMs = options.mediaPlayerAudioDelayMs;
	}
	if (options.tokenValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		std::string Token = TCHAR_TO_ANSI(*options.token);
		channelMediaOptions.token = Token.c_str();
	}
	if (options.enableBuiltInMediaEncryption != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.enableBuiltInMediaEncryption = options.enableBuiltInMediaEncryption == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.publishRhythmPlayerTrack != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.publishRhythmPlayerTrack = options.publishRhythmPlayerTrack == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.isInteractiveAudience != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isInteractiveAudience = options.isInteractiveAudience == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (options.customVideoTrackIdValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.customVideoTrackId = options.customVideoTrackId;
	}
	if (options.isAudioFilterable != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		channelMediaOptions.isAudioFilterable = options.isAudioFilterable == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::updateChannelMediaOptionsEx(channelMediaOptions, rtcConnection);
}
int UAgoraRtcEngine::SetVideoEncoderConfigurationEx(FVideoEncoderConfiguration& config, FRtcConnection& connection)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration;
	videoEncoderConfiguration.codecType = (agora::rtc::VIDEO_CODEC_TYPE)config.codecType;
	agora::rtc::VideoDimensions dim;
	dim.height = config.dimensions.height;
	dim.width = config.dimensions.width;
	videoEncoderConfiguration.dimensions = dim;
	videoEncoderConfiguration.frameRate = config.frameRate;
	videoEncoderConfiguration.bitrate = config.bitrate;
	videoEncoderConfiguration.minBitrate = config.minBitrate;
	videoEncoderConfiguration.orientationMode = (agora::rtc::ORIENTATION_MODE)config.orientationMode;
	videoEncoderConfiguration.degradationPreference = (agora::rtc::DEGRADATION_PREFERENCE)config.degradationPreference;
	videoEncoderConfiguration.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)config.mirrorMode;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setVideoEncoderConfigurationEx(videoEncoderConfiguration, rtcConnection);
}
int UAgoraRtcEngine::SetupRemoteVideoEx(FVideoCanvas& canvas, FRtcConnection& connection)
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
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	//rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setupRemoteVideoEx(videoCanvas, rtcConnection);
}
int UAgoraRtcEngine::MuteRemoteAudioStreamEx(int64 uid, bool mute, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::muteRemoteAudioStreamEx(uid, mute, rtcConnection);
}
int UAgoraRtcEngine::MuteRemoteVideoStreamEx(int64 uid, bool mute, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::muteRemoteVideoStreamEx(uid, mute, rtcConnection);
}
int UAgoraRtcEngine::SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setRemoteVideoStreamTypeEx(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType, rtcConnection);
}

int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptionsEx(int64 uid, FVideoSubscriptionOptions& options, FRtcConnection& connection)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions;
	if (options.typeValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		videoSubscriptionOptions.type = (agora::rtc::VIDEO_STREAM_TYPE)options.type;
	}
	if (options.encodedFrameOnly != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		videoSubscriptionOptions.encodedFrameOnly = options.encodedFrameOnly == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setRemoteVideoSubscriptionOptionsEx(uid, videoSubscriptionOptions, rtcConnection);
}
int UAgoraRtcEngine::SetRemoteVoicePositionEx(int64 uid, float pan, float gain, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setRemoteVoicePositionEx(uid, pan, gain, rtcConnection);
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParamsEx(int64 uid, FSpatialAudioParams& params, FRtcConnection& connection)
{
	agora::SpatialAudioParams spatialAudioParams;
	if (params.speaker_azimuthValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_azimuth = params.speaker_azimuth;
	}
	if (params.speaker_elevationValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_elevation = params.speaker_elevation;
	}
	if (params.speaker_distanceValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_distance = params.speaker_distance;
	}
	if (params.speaker_orientationValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_orientation = params.speaker_orientation;
	}
	if (params.enable_blurValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.enable_blur = params.enable_blur;
	}
	if (params.enable_air_absorbValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.enable_air_absorb = params.enable_air_absorb;
	}
	if (params.speaker_attenuationValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.speaker_attenuation = params.speaker_attenuation;
	}
	if (params.enable_dopplerValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		spatialAudioParams.enable_doppler = params.enable_doppler;
	}
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setRemoteUserSpatialAudioParamsEx(uid, spatialAudioParams, rtcConnection);
}
int UAgoraRtcEngine::SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setRemoteRenderModeEx(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode, rtcConnection);
}
int UAgoraRtcEngine::EnableLoopbackRecordingEx(FRtcConnection& connection, bool enabled, FString deviceName)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::enableLoopbackRecordingEx(rtcConnection, enabled, TCHAR_TO_ANSI(*deviceName));
}
ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionStateEx(FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return (ECONNECTION_STATE_TYPE)RtcEngineProxy::getConnectionStateEx(rtcConnection);
}
int UAgoraRtcEngine::EnableEncryptionEx(FRtcConnection& connection, bool enabled, FEncryptionConfig& config)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::EncryptionConfig encryptionConfig;
	encryptionConfig.encryptionMode = (agora::rtc::ENCRYPTION_MODE)config.encryptionMode;
	std::string EncryptionKey = TCHAR_TO_ANSI(*config.encryptionKey);
	encryptionConfig.encryptionKey = EncryptionKey.c_str();
	std::string encryptionKdfSalt = TCHAR_TO_ANSI(*config.encryptionKdfSalt);
	FMemory::Memcpy(encryptionConfig.encryptionKdfSalt, encryptionKdfSalt.c_str(), 32);

	int ret = RtcEngineProxy::enableEncryptionEx(rtcConnection, enabled, encryptionConfig);
	return ret;
}

int UAgoraRtcEngine::CreateDataStreamEx(int& streamId, FDataStreamConfig& config, FRtcConnection& connection)
{
	agora::rtc::DataStreamConfig dataStreamConfig;
	dataStreamConfig.syncWithAudio = config.syncWithAudio;
	dataStreamConfig.ordered = config.ordered;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::createDataStreamEx(&streamId, dataStreamConfig, rtcConnection);
}
int UAgoraRtcEngine::SendStreamMessageEx(int streamId, FString data, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	const char* Data = TCHAR_TO_ANSI(*data);
	return RtcEngineProxy::sendStreamMessageEx(streamId, Data, strlen(Data), rtcConnection);
}
int UAgoraRtcEngine::AddVideoWatermarkEx(FString watermarkUrl, FWatermarkOptions& options, FRtcConnection& connection)
{
	agora::rtc::WatermarkOptions watermarkOptions;
	watermarkOptions.visibleInPreview = options.visibleInPreview;

	agora::rtc::Rectangle LandscapeMode;
	LandscapeMode.height = options.positionInLandscapeMode.height;
	LandscapeMode.width = options.positionInLandscapeMode.width;
	watermarkOptions.positionInLandscapeMode = LandscapeMode;
	agora::rtc::Rectangle positionInPortraitMode;
	positionInPortraitMode.height = options.positionInPortraitMode.height;
	positionInPortraitMode.width = options.positionInPortraitMode.width;

	watermarkOptions.positionInLandscapeMode = LandscapeMode;
	watermarkOptions.positionInPortraitMode = positionInPortraitMode;
	agora::rtc::WatermarkRatio markradio;
	markradio.xRatio = options.watermarkRatio.xRatio;
	markradio.yRatio = options.watermarkRatio.xRatio;
	markradio.widthRatio = options.watermarkRatio.widthRatio;
	watermarkOptions.watermarkRatio = markradio;
	watermarkOptions.mode = (agora::rtc::WATERMARK_FIT_MODE)options.mode;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::addVideoWatermarkEx(TCHAR_TO_ANSI(*watermarkUrl), watermarkOptions, rtcConnection);
}
int UAgoraRtcEngine::ClearVideoWatermarkEx(FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::clearVideoWatermarkEx(rtcConnection);
}
int UAgoraRtcEngine::SendCustomReportMessageEx(FString id, FString category, FString event, FString label, int value, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::sendCustomReportMessageEx(TCHAR_TO_ANSI(*id), TCHAR_TO_ANSI(*category), TCHAR_TO_ANSI(*event), TCHAR_TO_ANSI(*label), value, rtcConnection);
}
int UAgoraRtcEngine::EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::enableAudioVolumeIndicationEx(interval, smooth, reportVad, rtcConnection);
}
int UAgoraRtcEngine::GetUserInfoByUserAccountEx(FString userAccount, FUserInfo& userInfo, FRtcConnection& connection)
{
	agora::rtc::UserInfo info;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	int ret = RtcEngineProxy::getUserInfoByUserAccountEx(TCHAR_TO_ANSI(*userAccount), &info, rtcConnection);

	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;

	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, FRtcConnection& connection)
{
	agora::rtc::UserInfo info;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	int ret = RtcEngineProxy::getUserInfoByUidEx(uid, &info, rtcConnection);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;

	return ret;
}
int UAgoraRtcEngine::SetVideoProfileEx(int width, int height, int frameRate, int bitrate)
{
	return RtcEngineProxy::setVideoProfileEx(width, height, frameRate, bitrate);
}
int UAgoraRtcEngine::EnableDualStreamModeEx(bool enabled, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.width = streamConfig.dimensions.width;
	dim.height = streamConfig.dimensions.height;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::enableDualStreamModeEx(enabled,simulcastStreamConfig, rtcConnection);
}
int UAgoraRtcEngine::SetDualStreamModeEx(ESIMULCAST_STREAM_MODE mode, FSimulcastStreamConfig& streamConfig, FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.width = streamConfig.dimensions.width;
	dim.height = streamConfig.dimensions.height;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::setDualStreamModeEx((agora::rtc::SIMULCAST_STREAM_MODE)mode, simulcastStreamConfig, rtcConnection);
}
int UAgoraRtcEngine::EnableWirelessAccelerate(bool enabled)
{
	return RtcEngineProxy::enableWirelessAccelerate(enabled);
}
int UAgoraRtcEngine::TakeSnapshotEx(FRtcConnection& connection, int64 uid, FString filePath)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	return RtcEngineProxy::takeSnapshotEx(rtcConnection, uid, FilePath.c_str());
}


int UAgoraRtcEngine::MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::muteLocalAudioStreamEx(mute, rtcConnection);
}

int UAgoraRtcEngine::MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::muteLocalVideoStreamEx(mute, rtcConnection);
}

int UAgoraRtcEngine::MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::muteAllRemoteAudioStreamsEx(mute, rtcConnection);
}

int UAgoraRtcEngine::MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::muteAllRemoteVideoStreamsEx(mute, rtcConnection);
}

int UAgoraRtcEngine::SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	int ret = RtcEngineProxy::setSubscribeAudioBlocklistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	int ret = RtcEngineProxy::setSubscribeAudioAllowlistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	int ret = RtcEngineProxy::setSubscribeVideoBlocklistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	int ret = RtcEngineProxy::setSubscribeVideoAllowlistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::adjustUserPlaybackSignalVolumeEx(uid, volume, rtcConnection);
}

int UAgoraRtcEngine::StartRtmpStreamWithoutTranscodingEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string Url = TCHAR_TO_ANSI(*url);
	return RtcEngineProxy::startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
}

int UAgoraRtcEngine::StartRtmpStreamWithTranscodingEx(FString url, const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string streamUrl = TCHAR_TO_ANSI(*url);

	agora::rtc::LiveTranscoding liveTranscoding;
	liveTranscoding.width = transcoding.width;
	liveTranscoding.height = transcoding.height;
	liveTranscoding.videoBitrate = transcoding.videoBitrate;
	liveTranscoding.videoFramerate = transcoding.videoFramerate;
	liveTranscoding.lowLatency = transcoding.lowLatency;
	liveTranscoding.videoGop = transcoding.videoGop;
	liveTranscoding.videoCodecProfile = (agora::rtc::VIDEO_CODEC_PROFILE_TYPE)transcoding.videoCodecProfile;
	liveTranscoding.backgroundColor = transcoding.backgroundColor;
	liveTranscoding.videoCodecType = (agora::rtc::VIDEO_CODEC_TYPE_FOR_STREAM)transcoding.videoCodecType;
	liveTranscoding.userCount = transcoding.userCount;
	agora::rtc::TranscodingUser* trans = new agora::rtc::TranscodingUser[transcoding.userCount];
	for (int i = 0; i < transcoding.userCount; i++)
	{
		trans[i].alpha = transcoding.transcodingUsers[i].alpha;
		trans[i].audioChannel = transcoding.transcodingUsers[i].audioChannel;
		trans[i].height = transcoding.transcodingUsers[i].height;
		trans[i].uid = transcoding.transcodingUsers[i].uid;
		trans[i].width = transcoding.transcodingUsers[i].width;
		trans[i].x = transcoding.transcodingUsers[i].x;
		trans[i].y = transcoding.transcodingUsers[i].y;
		trans[i].zOrder = transcoding.transcodingUsers[i].zOrder;
	}
	liveTranscoding.transcodingUsers = trans;
	std::string TranscodingExtraInfo = TCHAR_TO_ANSI(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_ANSI(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.watermark[i].url);
		image[i].url = Url.c_str();
		image[i].height = transcoding.watermark[i].height;
		image[i].width = transcoding.watermark[i].width;
		image[i].x = transcoding.watermark[i].x;
		image[i].y = transcoding.watermark[i].y;
		image[i].zOrder = transcoding.watermark[i].zOrder;
	}
	liveTranscoding.watermark = image;
	liveTranscoding.watermarkCount = transcoding.watermarkCount;

	agora::rtc::RtcImage* bgImage = new agora::rtc::RtcImage[transcoding.backgroundImageCount];
	for (int i = 0; i < transcoding.backgroundImageCount; i++)
	{
		bgImage[i].alpha = transcoding.backgroundImage[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.backgroundImage[i].url);
		bgImage[i].url = Url.c_str();
		bgImage[i].height = transcoding.backgroundImage[i].height;
		bgImage[i].width = transcoding.backgroundImage[i].width;
		bgImage[i].x = transcoding.backgroundImage[i].x;
		bgImage[i].y = transcoding.backgroundImage[i].y;
		bgImage[i].zOrder = transcoding.backgroundImage[i].zOrder;
	}
	liveTranscoding.backgroundImage = bgImage;
	liveTranscoding.backgroundImageCount = transcoding.backgroundImageCount;
	if (transcoding.audioSampleRate.GetValue() == 1)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_32000;
	}
	else if (transcoding.audioSampleRate.GetValue() == 2)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_44100;
	}
	else if (transcoding.audioSampleRate.GetValue() == 3)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	}
	liveTranscoding.audioBitrate = transcoding.audioBitrate;
	liveTranscoding.audioChannels = transcoding.audioChannels;
	liveTranscoding.audioCodecProfile = (agora::rtc::AUDIO_CODEC_PROFILE_TYPE)transcoding.audioCodecProfile;

	agora::rtc::LiveStreamAdvancedFeature* feature = new agora::rtc::LiveStreamAdvancedFeature[transcoding.advancedFeatureCount];
	for (int i = 0; i < transcoding.advancedFeatureCount; i++)
	{
		std::string FeatureName = TCHAR_TO_ANSI(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;

	int ret = RtcEngineProxy::startRtmpStreamWithTranscodingEx(streamUrl.c_str(),liveTranscoding, rtcConnection);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;

	return ret;
}

int UAgoraRtcEngine::UpdateRtmpTranscodingEx(const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::LiveTranscoding liveTranscoding;
	liveTranscoding.width = transcoding.width;
	liveTranscoding.height = transcoding.height;
	liveTranscoding.videoBitrate = transcoding.videoBitrate;
	liveTranscoding.videoFramerate = transcoding.videoFramerate;
	liveTranscoding.lowLatency = transcoding.lowLatency;
	liveTranscoding.videoGop = transcoding.videoGop;
	liveTranscoding.videoCodecProfile = (agora::rtc::VIDEO_CODEC_PROFILE_TYPE)transcoding.videoCodecProfile;
	liveTranscoding.backgroundColor = transcoding.backgroundColor;
	liveTranscoding.videoCodecType = (agora::rtc::VIDEO_CODEC_TYPE_FOR_STREAM)transcoding.videoCodecType;
	liveTranscoding.userCount = transcoding.userCount;
	agora::rtc::TranscodingUser* trans = new agora::rtc::TranscodingUser[transcoding.userCount];
	for (int i = 0; i < transcoding.userCount; i++)
	{
		trans[i].alpha = transcoding.transcodingUsers[i].alpha;
		trans[i].audioChannel = transcoding.transcodingUsers[i].audioChannel;
		trans[i].height = transcoding.transcodingUsers[i].height;
		trans[i].uid = transcoding.transcodingUsers[i].uid;
		trans[i].width = transcoding.transcodingUsers[i].width;
		trans[i].x = transcoding.transcodingUsers[i].x;
		trans[i].y = transcoding.transcodingUsers[i].y;
		trans[i].zOrder = transcoding.transcodingUsers[i].zOrder;
	}
	liveTranscoding.transcodingUsers = trans;
	std::string TranscodingExtraInfo = TCHAR_TO_ANSI(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_ANSI(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.watermark[i].url);
		image[i].url = Url.c_str();
		image[i].height = transcoding.watermark[i].height;
		image[i].width = transcoding.watermark[i].width;
		image[i].x = transcoding.watermark[i].x;
		image[i].y = transcoding.watermark[i].y;
		image[i].zOrder = transcoding.watermark[i].zOrder;
	}
	liveTranscoding.watermark = image;
	liveTranscoding.watermarkCount = transcoding.watermarkCount;

	agora::rtc::RtcImage* bgImage = new agora::rtc::RtcImage[transcoding.backgroundImageCount];
	for (int i = 0; i < transcoding.backgroundImageCount; i++)
	{
		bgImage[i].alpha = transcoding.backgroundImage[i].alpha;
		std::string Url = TCHAR_TO_ANSI(*transcoding.backgroundImage[i].url);
		bgImage[i].url = Url.c_str();
		bgImage[i].height = transcoding.backgroundImage[i].height;
		bgImage[i].width = transcoding.backgroundImage[i].width;
		bgImage[i].x = transcoding.backgroundImage[i].x;
		bgImage[i].y = transcoding.backgroundImage[i].y;
		bgImage[i].zOrder = transcoding.backgroundImage[i].zOrder;
	}
	liveTranscoding.backgroundImage = bgImage;
	liveTranscoding.backgroundImageCount = transcoding.backgroundImageCount;
	if (transcoding.audioSampleRate.GetValue() == 1)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_32000;
	}
	else if (transcoding.audioSampleRate.GetValue() == 2)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_44100;
	}
	else if (transcoding.audioSampleRate.GetValue() == 3)
	{
		liveTranscoding.audioSampleRate = agora::rtc::AUDIO_SAMPLE_RATE_TYPE::AUDIO_SAMPLE_RATE_48000;
	}
	liveTranscoding.audioBitrate = transcoding.audioBitrate;
	liveTranscoding.audioChannels = transcoding.audioChannels;
	liveTranscoding.audioCodecProfile = (agora::rtc::AUDIO_CODEC_PROFILE_TYPE)transcoding.audioCodecProfile;

	agora::rtc::LiveStreamAdvancedFeature* feature = new agora::rtc::LiveStreamAdvancedFeature[transcoding.advancedFeatureCount];
	for (int i = 0; i < transcoding.advancedFeatureCount; i++)
	{
		std::string FeatureName = TCHAR_TO_ANSI(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	int ret = RtcEngineProxy::updateRtmpTranscodingEx(liveTranscoding, rtcConnection);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;
	return ret;
}

int UAgoraRtcEngine::StopRtmpStreamEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string Url = TCHAR_TO_ANSI(*url);
	return RtcEngineProxy::startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
}

int UAgoraRtcEngine::StartChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration;
	agora::rtc::ChannelMediaInfo* mediaInfo = new agora::rtc::ChannelMediaInfo();
	std::string ChannelName = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
	mediaInfo->channelName = ChannelName.c_str();
	std::string Token = TCHAR_TO_ANSI(*configuration.srcInfo.token);
	mediaInfo->token = Token.c_str();
	mediaInfo->uid = configuration.srcInfo.uid;
	channelMediaRelayConfiguration.srcInfo = mediaInfo;
	agora::rtc::ChannelMediaInfo* mediaInfos = new agora::rtc::ChannelMediaInfo[configuration.destCount];
	for (int i = 0; i < configuration.destCount; i++)
	{
		std::string ChannelNameTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].channelName = ChannelNameTemp.c_str();
		std::string TokenTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].token = TokenTemp.c_str();
		mediaInfos[i].uid = configuration.destInfos[i].uid;
	}
	channelMediaRelayConfiguration.destInfos = mediaInfos;
	channelMediaRelayConfiguration.destCount = configuration.destCount;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	int ret = RtcEngineProxy::startChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}

int UAgoraRtcEngine::UpdateChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration;
	agora::rtc::ChannelMediaInfo* mediaInfo = new agora::rtc::ChannelMediaInfo();
	std::string ChannelName = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
	mediaInfo->channelName = ChannelName.c_str();
	std::string Token = TCHAR_TO_ANSI(*configuration.srcInfo.token);
	mediaInfo->token = Token.c_str();
	mediaInfo->uid = configuration.srcInfo.uid;
	channelMediaRelayConfiguration.srcInfo = mediaInfo;
	agora::rtc::ChannelMediaInfo* mediaInfos = new agora::rtc::ChannelMediaInfo[configuration.destCount];
	for (int i = 0; i < configuration.destCount; i++)
	{
		std::string ChannelNameTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].channelName = ChannelNameTemp.c_str();
		std::string TokenTemp = TCHAR_TO_ANSI(*configuration.srcInfo.channelName);
		mediaInfos[i].token = TokenTemp.c_str();
		mediaInfos[i].uid = configuration.destInfos[i].uid;
	}
	channelMediaRelayConfiguration.destInfos = mediaInfos;
	channelMediaRelayConfiguration.destCount = configuration.destCount;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	int ret = RtcEngineProxy::updateChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}

int UAgoraRtcEngine::StopChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::stopChannelMediaRelayEx(rtcConnection);
}

int UAgoraRtcEngine::PauseAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::pauseAllChannelMediaRelayEx(rtcConnection);
}

int UAgoraRtcEngine::ResumeAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return RtcEngineProxy::resumeAllChannelMediaRelayEx(rtcConnection);
}

int UAgoraRtcEngine::SetParameters(FString parameters)
{
	std::string parameterstr = TCHAR_TO_ANSI(*parameters);

	return RtcEngineProxy::setParameters(parameterstr.c_str());
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

		FThumbImageBuffer iconImagebuffer;
		char* icon = new char[info.iconImage.length];
		FMemory::Memcpy(icon, info.iconImage.buffer, info.iconImage.length);
		for (unsigned int i = 0; i < info.iconImage.length; i++)
		{
			iconImagebuffer.buffer.Add(icon[i]);
		}
		delete[] icon;
		iconImagebuffer.height = info.iconImage.height;
		iconImagebuffer.width = info.iconImage.width;
		iconImagebuffer.length = info.iconImage.length;

		sourceInfo.iconImage = iconImagebuffer;
		sourceInfo.isOccluded = info.isOccluded;
		sourceInfo.primaryMonitor = info.primaryMonitor;
		sourceInfo.processPath = info.processPath;
		sourceInfo.sourceId = (int64)info.sourceId;
		sourceInfo.sourceName = UTF8_TO_TCHAR(info.sourceName);
		sourceInfo.sourceTitle = info.sourceTitle;

		FThumbImageBuffer thumbImagebuffer;
		char* icon2 = new char[info.thumbImage.length];
		FMemory::Memcpy(icon2, info.thumbImage.buffer, info.thumbImage.length);
		for (unsigned int i = 0; i < info.thumbImage.length; i++)
		{
			thumbImagebuffer.buffer.Add(icon2[i]);
		}
		delete[] icon2;
		thumbImagebuffer.height = info.thumbImage.height;
		thumbImagebuffer.width = info.thumbImage.width;
		thumbImagebuffer.length = info.thumbImage.length;
		sourceInfo.thumbImage = thumbImagebuffer;
		sourceInfo.type = (EScreenCaptureSourceType)info.type;
		UE_LOG(LogTemp,Warning,TEXT("ScreenCaptureSourceType %d"), sourceInfo.type)
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
		 sourceListNative =nullptr;
	}
#endif
}
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
void UIScreenCaptureSourceList::SetScreenCaptureList(agora::rtc::IScreenCaptureSourceList* sourcelist)
{
	sourceListNative = sourcelist;
}
#endif


