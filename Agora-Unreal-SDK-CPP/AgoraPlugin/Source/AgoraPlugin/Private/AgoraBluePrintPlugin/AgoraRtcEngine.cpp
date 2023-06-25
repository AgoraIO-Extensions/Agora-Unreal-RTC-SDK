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
		RtcEngineProxyClassWrapper::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);

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
		RtcEngineProxyClassWrapper::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&AudioDeviceManager);

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
		RtcEngineProxyClassWrapper::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_LOCAL_SPATIAL_AUDIO, (void**)&SpatialAudioEngine);

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
		RtcEngineProxyClassWrapper::queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_MEDIA_RECORDER, (void**)&MediaRecorder);

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
	return RtcEngineProxyClassWrapper::release(sync);
}
int UAgoraRtcEngine::Initialize(const FRtcEngineContext& context)
{
	agora::rtc::RtcEngineContext rtcEngineContext;

	if (context.eventHandler != nullptr && std::strcmp(context.eventHandler->eventHandlerType(), "event_handler") != 0)
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

	int ret = RtcEngineProxyClassWrapper::initialize(rtcEngineContext);
	return ret;
}
FString UAgoraRtcEngine::GetVersion(int build)
{
	return RtcEngineProxyClassWrapper::getVersion(&build);
}
FString UAgoraRtcEngine::GetErrorDescription(int code)
{
	return RtcEngineProxyClassWrapper::getErrorDescription(code);
}
int UAgoraRtcEngine::JoinChannel(FString token, FString channelId, int64 uid, const FChannelMediaOptions& options)
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
	auto ret = RtcEngineProxyClassWrapper::joinChannel(Token.c_str(), ChannelId.c_str(), uid, channelMediaOptions);
	return ret;
}
int UAgoraRtcEngine::UpdateChannelMediaOptions(const FChannelMediaOptions& options)
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
	auto ret = RtcEngineProxyClassWrapper::updateChannelMediaOptions(channelMediaOptions);
	return ret;
}

int UAgoraRtcEngine::LeaveChannel(const FLeaveChannelOptions& options)
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

	auto ret = RtcEngineProxyClassWrapper::leaveChannel(leaveChannelOptions);
	return ret;
}

int UAgoraRtcEngine::RenewToken(FString token)
{
	std::string Token = TCHAR_TO_ANSI(*token);

	auto ret = RtcEngineProxyClassWrapper::renewToken(Token.c_str());
	return ret;
}
int UAgoraRtcEngine::SetChannelProfile(ECHANNEL_PROFILE_TYPE profile)
{
	auto ret = RtcEngineProxyClassWrapper::setChannelProfile((agora::CHANNEL_PROFILE_TYPE)profile);
	return ret;
}
int UAgoraRtcEngine::SetClientRole(ECLIENT_ROLE_TYPE clientroletype, const FClientRoleOptions& options)
{
	agora::rtc::ClientRoleOptions clientRoleOptions;
	clientRoleOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	agora::rtc::CLIENT_ROLE_TYPE roleType = (agora::rtc::CLIENT_ROLE_TYPE)clientroletype;
	auto ret = RtcEngineProxyClassWrapper::setClientRole(roleType, clientRoleOptions);
	return ret;
}
int UAgoraRtcEngine::StartEchoTest(const FEchoTestConfiguration& config)
{
	agora::rtc::EchoTestConfiguration echoTestConfiguration;
	echoTestConfiguration.view = (agora::view_t)config.view;
	echoTestConfiguration.enableAudio = config.enableAudio;
	echoTestConfiguration.enableVideo = config.enableVideo;
	std::string Token = TCHAR_TO_ANSI(*config.token);
	echoTestConfiguration.token = Token.c_str();
	std::string ChannelId = TCHAR_TO_ANSI(*config.channelId);
	echoTestConfiguration.channelId = ChannelId.c_str();
	auto ret = RtcEngineProxyClassWrapper::startEchoTest(echoTestConfiguration);
	return ret;
}
int UAgoraRtcEngine::StopEchoTest()
{
	auto ret = RtcEngineProxyClassWrapper::stopEchoTest();
	return ret;
}
int UAgoraRtcEngine::EnableVideo()
{
	auto ret = RtcEngineProxyClassWrapper::enableVideo();
	return ret;
}
int UAgoraRtcEngine::DisableVideo()
{
	auto ret = RtcEngineProxyClassWrapper::disableVideo();
	return ret;
}
int UAgoraRtcEngine::StartPreview(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::startPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}
int UAgoraRtcEngine::StopPreview(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::stopPreview((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}
int UAgoraRtcEngine::StartLastmileProbeTest(const FLastmileProbeConfig& config)
{
	agora::rtc::LastmileProbeConfig lastmileProbeConfig;
	lastmileProbeConfig.probeUplink = config.probeUplink;
	lastmileProbeConfig.probeDownlink = config.probeDownlink;
	lastmileProbeConfig.expectedUplinkBitrate = config.expectedUplinkBitrate;
	lastmileProbeConfig.expectedDownlinkBitrate = config.expectedDownlinkBitrate;
	auto ret = RtcEngineProxyClassWrapper::startLastmileProbeTest(lastmileProbeConfig);
	return ret;
}
int UAgoraRtcEngine::SetVideoEncoderConfiguration(const FVideoEncoderConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::setVideoEncoderConfiguration(videoEncoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::SetBeautyEffectOptions(bool enabled, const FBeautyOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::BeautyOptions beautyOptions;
	beautyOptions.lighteningContrastLevel = (agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL)options.lighteningContrastLevel;
	beautyOptions.lighteningLevel = options.lighteningLevel;
	beautyOptions.smoothnessLevel = options.smoothnessLevel;
	beautyOptions.rednessLevel = options.rednessLevel;
	beautyOptions.sharpnessLevel = options.sharpnessLevel;
	auto ret = RtcEngineProxyClassWrapper::setBeautyEffectOptions(enabled, beautyOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetLowlightEnhanceOptions(bool enabled, const FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::LowlightEnhanceOptions lowlightEnhanceOptions;
	lowlightEnhanceOptions.mode = (agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_MODE)options.mode;
	lowlightEnhanceOptions.level = (agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_LEVEL)options.level;
	auto ret = RtcEngineProxyClassWrapper::setLowlightEnhanceOptions(enabled, lowlightEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetVideoDenoiserOptions(bool enabled, const FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VideoDenoiserOptions videoDenoiserOptions;
	videoDenoiserOptions.mode = (agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_MODE)options.mode;
	videoDenoiserOptions.level = (agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_LEVEL)options.level;
	auto ret = RtcEngineProxyClassWrapper::setVideoDenoiserOptions(enabled, videoDenoiserOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetColorEnhanceOptions(bool enabled, const FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::ColorEnhanceOptions colorEnhanceOptions;
	colorEnhanceOptions.strengthLevel = options.strengthLevel;
	colorEnhanceOptions.skinProtectLevel = options.skinProtectLevel;
	auto ret = RtcEngineProxyClassWrapper::setColorEnhanceOptions(enabled, colorEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
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
	auto ret = RtcEngineProxyClassWrapper::enableVirtualBackground(enabled, virtualBackgroundSource, segmentationProperty, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}


int UAgoraRtcEngine::EnableRemoteSuperResolution(int64 userId, bool enable)
{
	auto ret = RtcEngineProxyClassWrapper::enableRemoteSuperResolution(userId, enable);
	return ret;
}

int UAgoraRtcEngine::SetupRemoteVideo(const FVideoCanvas& canvas)
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
	auto ret = RtcEngineProxyClassWrapper::setupRemoteVideo(videoCanvas);
	return ret;
}
int UAgoraRtcEngine::SetupLocalVideo(const FVideoCanvas& canvas)
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
	auto ret = RtcEngineProxyClassWrapper::setupLocalVideo(videoCanvas);
	return ret;
}
int UAgoraRtcEngine::EnableAudio()
{
	auto ret = RtcEngineProxyClassWrapper::enableAudio();
	return ret;
}
int UAgoraRtcEngine::DisableAudio()
{
	auto ret = RtcEngineProxyClassWrapper::disableAudio();
	return ret;
}

int UAgoraRtcEngine::SetAudioProfile(EAUDIO_PROFILE_TYPE profile)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile);
	return ret;
}

int UAgoraRtcEngine::SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioScenario((agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
	return ret;
}
int UAgoraRtcEngine::EnableLocalAudio(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableLocalAudio(enabled);
	return ret;
}
int UAgoraRtcEngine::MuteLocalAudioStream(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteLocalAudioStream(mute);
	return ret;
}
int UAgoraRtcEngine::MuteAllRemoteAudioStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteAllRemoteAudioStreams(mute);
	return ret;
}
int UAgoraRtcEngine::SetDefaultMuteAllRemoteAudioStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::setDefaultMuteAllRemoteAudioStreams(mute);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteAudioStream(int64 uid, bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteRemoteAudioStream(uid, mute);
	return ret;
}
int UAgoraRtcEngine::MuteLocalVideoStream(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteLocalVideoStream(mute);
	return ret;
}
int UAgoraRtcEngine::EnableLocalVideo(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableLocalVideo(enabled);
	return ret;
}
int UAgoraRtcEngine::MuteAllRemoteVideoStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteAllRemoteVideoStreams(mute);
	return ret;
}
int UAgoraRtcEngine::SetDefaultMuteAllRemoteVideoStreams(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::setDefaultMuteAllRemoteVideoStreams(mute);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteVideoStream(int64 uid, bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteRemoteVideoStream(uid, mute);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVideoStreamType(int64 uid, EVIDEO_STREAM_TYPE streamType)
{
	auto ret = RtcEngineProxyClassWrapper::setRemoteVideoStreamType(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptions(int64 uid, const FVideoSubscriptionOptions& options)
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

	auto ret = RtcEngineProxyClassWrapper::setRemoteVideoSubscriptionOptions(uid, videoSubscriptionOptions);
	return ret;
}
int UAgoraRtcEngine::SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType)
{
	auto ret = RtcEngineProxyClassWrapper::setRemoteDefaultVideoStreamType((agora::rtc::VIDEO_STREAM_TYPE)streamType);
	return ret;
}

int UAgoraRtcEngine::EnableAudioVolumeIndication(int interval, int smooth, bool reportVad)
{
	auto ret = RtcEngineProxyClassWrapper::enableAudioVolumeIndication(interval, smooth, reportVad);
	return ret;
}
int UAgoraRtcEngine::StartAudioRecording(const FAudioRecordingConfiguration& config)
{
	agora::rtc::AudioRecordingConfiguration audioRecordingConfiguration;
	std::string FilePath = TCHAR_TO_ANSI(*config.filePath);
	audioRecordingConfiguration.filePath = FilePath.c_str();
	audioRecordingConfiguration.encode = config.encode;
	audioRecordingConfiguration.sampleRate = config.sampleRate;
	audioRecordingConfiguration.fileRecordingType = (agora::rtc::AUDIO_FILE_RECORDING_TYPE)config.fileRecordingType;
	audioRecordingConfiguration.quality = (agora::rtc::AUDIO_RECORDING_QUALITY_TYPE)config.quality;
	audioRecordingConfiguration.recordingChannel = config.recordingChannel;
	auto ret = RtcEngineProxyClassWrapper::startAudioRecording(audioRecordingConfiguration);
	return ret;
}

int UAgoraRtcEngine::RegisterAudioEncodedFrameObserver(const FAudioEncodedFrameObserverConfig& config, UIAudioEncodedFrameObserver* observer)
{
	agora::rtc::AudioEncodedFrameObserverConfig audioEncodedFrameObserverConfig;
	audioEncodedFrameObserverConfig.postionType = (agora::rtc::AUDIO_ENCODED_FRAME_OBSERVER_POSITION)config.postionType;
	if ((agora::rtc::AUDIO_ENCODING_TYPE)config.encodingType.GetValue() == 1)
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

	auto ret = RtcEngineProxyClassWrapper::registerAudioEncodedFrameObserver(audioEncodedFrameObserverConfig, observer);
	return ret;
}
int UAgoraRtcEngine::StopAudioRecording()
{
	auto ret = RtcEngineProxyClassWrapper::stopAudioRecording();
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

	MediaPlayer = RtcEngineProxyClassWrapper::createMediaPlayer();

	mediaPlayer->SetMediaPlayer(MediaPlayer);

	return mediaPlayer;
}
int UAgoraRtcEngine::DestroyMediaPlayer(UIMediaPlayer* media_player)
{
	auto ret = RtcEngineProxyClassWrapper::destroyMediaPlayer(media_player->GetMediaPlayer());
	return ret;
}
int UAgoraRtcEngine::StartAudioMixing(FString filePath, bool loopback, int cycle, int startPos)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	auto ret = RtcEngineProxyClassWrapper::startAudioMixing(FilePath.c_str(), loopback, cycle, startPos);
	return ret;
}
int UAgoraRtcEngine::PauseAudioMixing()
{
	auto ret = RtcEngineProxyClassWrapper::pauseAudioMixing();
	return ret;
}
int UAgoraRtcEngine::ResumeAudioMixing()
{
	auto ret = RtcEngineProxyClassWrapper::resumeAudioMixing();
	return ret;
}
int UAgoraRtcEngine::SelectAudioTrack(int index)
{
	auto ret = RtcEngineProxyClassWrapper::selectAudioTrack(index);
	return ret;
}
int UAgoraRtcEngine::GetAudioTrackCount()
{
	auto ret = RtcEngineProxyClassWrapper::getAudioTrackCount();
	return ret;
}
int UAgoraRtcEngine::AdjustAudioMixingVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustAudioMixingVolume(volume);
	return ret;
}
int UAgoraRtcEngine::AdjustAudioMixingPublishVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustAudioMixingPublishVolume(volume);
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingPublishVolume()
{
	auto ret = RtcEngineProxyClassWrapper::getAudioMixingPublishVolume();
	return ret;
}
int UAgoraRtcEngine::AdjustAudioMixingPlayoutVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustAudioMixingPlayoutVolume(volume);
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingPlayoutVolume()
{
	auto ret = RtcEngineProxyClassWrapper::getAudioMixingPlayoutVolume();
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingDuration()
{
	auto ret = RtcEngineProxyClassWrapper::getAudioMixingDuration();
	return ret;
}
int UAgoraRtcEngine::GetAudioMixingCurrentPosition()
{
	auto ret = RtcEngineProxyClassWrapper::getAudioMixingCurrentPosition();
	return ret;
}
int UAgoraRtcEngine::SetAudioMixingPosition(int pos)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioMixingPosition(pos);
	return ret;
}
int UAgoraRtcEngine::SetAudioMixingDualMonoMode(EAUDIO_MIXING_DUAL_MONO_MODE mode)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioMixingDualMonoMode((agora::media::AUDIO_MIXING_DUAL_MONO_MODE)mode);
	return ret;
}
int UAgoraRtcEngine::SetAudioMixingPitch(int pitch)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioMixingPitch(pitch);
	return ret;
}
int UAgoraRtcEngine::GetEffectsVolume()
{
	auto ret = RtcEngineProxyClassWrapper::getEffectsVolume();
	return ret;
}
int UAgoraRtcEngine::SetEffectsVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::setEffectsVolume(volume);
	return ret;
}
int UAgoraRtcEngine::PreloadEffect(int soundId, FString filePath, int startPos)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	auto ret = RtcEngineProxyClassWrapper::preloadEffect(soundId, FilePath.c_str(), startPos);
	return ret;
}
int UAgoraRtcEngine::PlayEffect(int soundId, FString filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	auto ret = RtcEngineProxyClassWrapper::playEffect(soundId, FilePath.c_str(), loopCount, pitch, pan, gain, publish, startPos);
	return ret;
}
int UAgoraRtcEngine::PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish)
{
	auto ret = RtcEngineProxyClassWrapper::playAllEffects(loopCount, pitch, pan, gain, publish);
	return ret;
}
int UAgoraRtcEngine::GetVolumeOfEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::getVolumeOfEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::SetVolumeOfEffect(int soundId, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::setVolumeOfEffect(soundId, volume);
	return ret;
}
int UAgoraRtcEngine::PauseEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::pauseEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::PauseAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::pauseAllEffects();
	return ret;
}
int UAgoraRtcEngine::ResumeEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::resumeEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::ResumeAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::resumeAllEffects();
	return ret;
}
int UAgoraRtcEngine::StopEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::stopEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::StopAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::stopAllEffects();
	return ret;
}
int UAgoraRtcEngine::UnloadEffect(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::unloadEffect(soundId);
	return ret;
}
int UAgoraRtcEngine::UnloadAllEffects()
{
	auto ret = RtcEngineProxyClassWrapper::unloadAllEffects();
	return ret;
}
int UAgoraRtcEngine::GetEffectDuration(FString filePath)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	auto ret = RtcEngineProxyClassWrapper::getEffectDuration(FilePath.c_str());
	return ret;
}
int UAgoraRtcEngine::SetEffectPosition(int soundId, int pos)
{
	auto ret = RtcEngineProxyClassWrapper::setEffectPosition(soundId, pos);
	return ret;
}
int UAgoraRtcEngine::GetEffectCurrentPosition(int soundId)
{
	auto ret = RtcEngineProxyClassWrapper::getEffectCurrentPosition(soundId);
	return ret;
}
int UAgoraRtcEngine::EnableSoundPositionIndication(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableSoundPositionIndication(enabled);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVoicePosition(int64 uid, float pan, float gain)
{
	auto ret = RtcEngineProxyClassWrapper::setRemoteVoicePosition(uid, pan, gain);
	return ret;
}
int UAgoraRtcEngine::EnableSpatialAudio(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableSpatialAudio(enabled);
	return ret;
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParams(int64 uid, const FSpatialAudioParams& params)
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

	auto ret = RtcEngineProxyClassWrapper::setRemoteUserSpatialAudioParams(uid, spatialAudioParams);
	return ret;
}
int UAgoraRtcEngine::SetVoiceBeautifierPreset(EVOICE_BEAUTIFIER_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::setVoiceBeautifierPreset((agora::rtc::VOICE_BEAUTIFIER_PRESET)preset);
	return ret;
}
int UAgoraRtcEngine::SetAudioEffectPreset(EAUDIO_EFFECT_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioEffectPreset((agora::rtc::AUDIO_EFFECT_PRESET)preset);
	return ret;
}
int UAgoraRtcEngine::SetVoiceConversionPreset(EVOICE_CONVERSION_PRESET preset)
{
	auto ret = RtcEngineProxyClassWrapper::setVoiceConversionPreset((agora::rtc::VOICE_CONVERSION_PRESET)preset);
	return ret;
}
int UAgoraRtcEngine::SetAudioEffectParameters(EAUDIO_EFFECT_PRESET preset, int param1, int param2)
{
	auto ret = RtcEngineProxyClassWrapper::setAudioEffectParameters((agora::rtc::AUDIO_EFFECT_PRESET)preset, param1, param2);
	return ret;
}
int UAgoraRtcEngine::SetVoiceBeautifierParameters(EVOICE_BEAUTIFIER_PRESET preset, int param1, int param2)
{
	auto ret = RtcEngineProxyClassWrapper::setVoiceBeautifierParameters((agora::rtc::VOICE_BEAUTIFIER_PRESET)preset, param1, param2);
	return ret;
}
int UAgoraRtcEngine::SetVoiceConversionParameters(EVOICE_CONVERSION_PRESET preset, int param1, int param2)
{
	auto ret = RtcEngineProxyClassWrapper::setVoiceConversionParameters((agora::rtc::VOICE_CONVERSION_PRESET)preset, param1, param2);
	return ret;
}
int UAgoraRtcEngine::SetLocalVoicePitch(float pitch)
{
	auto ret = RtcEngineProxyClassWrapper::setLocalVoicePitch(pitch);
	return ret;
}
int UAgoraRtcEngine::SetLocalVoiceEqualization(EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
{
	auto ret = RtcEngineProxyClassWrapper::setLocalVoiceEqualization((agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY)bandFrequency, bandGain);
	return ret;
}
int UAgoraRtcEngine::SetLocalVoiceReverb(EAUDIO_REVERB_TYPE reverbKey, int value)
{
	auto ret = RtcEngineProxyClassWrapper::setLocalVoiceReverb((agora::rtc::AUDIO_REVERB_TYPE)reverbKey, value);
	return ret;
}
int UAgoraRtcEngine::SetLogFile(FString filePath)
{
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	auto ret = RtcEngineProxyClassWrapper::setLogFile(FilePath.c_str());
	return ret;
}
int UAgoraRtcEngine::SetLogFilter(int filter)
{
	auto ret = RtcEngineProxyClassWrapper::setLogFilter(filter);
	return ret;
}
int UAgoraRtcEngine::SetLogLevel(ELOG_LEVEL level)
{
	auto ret = RtcEngineProxyClassWrapper::setLogLevel((agora::commons::LOG_LEVEL)level);
	return ret;
}
int UAgoraRtcEngine::SetLogFileSize(int fileSizeInKBytes)
{
	auto ret = RtcEngineProxyClassWrapper::setLogFileSize(fileSizeInKBytes);
	return ret;
}
int UAgoraRtcEngine::UploadLogFile(FString& requestId)
{
	agora::util::AString _requestId;
	auto ret = RtcEngineProxyClassWrapper::uploadLogFile(_requestId);
	requestId = _requestId->c_str();
	return ret;
}
int UAgoraRtcEngine::SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = RtcEngineProxyClassWrapper::setLocalRenderMode((agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
	return ret;
}
int UAgoraRtcEngine::SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = RtcEngineProxyClassWrapper::setRemoteRenderMode(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
	return ret;
}
int UAgoraRtcEngine::SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = RtcEngineProxyClassWrapper::setLocalVideoMirrorMode((agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
	return ret;
}

int UAgoraRtcEngine::EnableDualStreamMode(bool enabled, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.height = streamConfig.dimensions.height;
	dim.width = streamConfig.dimensions.width;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	auto ret = RtcEngineProxyClassWrapper::enableDualStreamMode(enabled, simulcastStreamConfig);
	return ret;
}
int UAgoraRtcEngine::SetDualStreamMode(ESIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.height = streamConfig.dimensions.height;
	dim.width = streamConfig.dimensions.width;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	auto ret = RtcEngineProxyClassWrapper::setDualStreamMode((agora::rtc::SIMULCAST_STREAM_MODE)mode, simulcastStreamConfig);
	return ret;
}


int UAgoraRtcEngine::EnableEchoCancellationExternal(bool enabled, int audioSourceDelay)
{
	auto ret = RtcEngineProxyClassWrapper::enableEchoCancellationExternal(enabled, audioSourceDelay);
	return ret;
}

int UAgoraRtcEngine::EnableCustomAudioLocalPlayback(int sourceId, bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableCustomAudioLocalPlayback(sourceId, enabled);
	return ret;
}

int UAgoraRtcEngine::StartPrimaryCustomAudioTrack(const FAudioTrackConfig& config)
{
	agora::rtc::AudioTrackConfig audioTrackConfig;
	audioTrackConfig.enableLocalPlayback = config.enableLocalPlayback;
	auto ret = RtcEngineProxyClassWrapper::startPrimaryCustomAudioTrack(audioTrackConfig);
	return ret;
}
int UAgoraRtcEngine::StopPrimaryCustomAudioTrack()
{
	auto ret = RtcEngineProxyClassWrapper::stopPrimaryCustomAudioTrack();
	return ret;
}
int UAgoraRtcEngine::StartSecondaryCustomAudioTrack(const FAudioTrackConfig& config)
{
	agora::rtc::AudioTrackConfig audioTrackConfig;
	audioTrackConfig.enableLocalPlayback = config.enableLocalPlayback;
	auto ret = RtcEngineProxyClassWrapper::startSecondaryCustomAudioTrack(audioTrackConfig);
	return ret;
}
int UAgoraRtcEngine::StopSecondaryCustomAudioTrack()
{
	auto ret = RtcEngineProxyClassWrapper::stopSecondaryCustomAudioTrack();
	return ret;
}
int UAgoraRtcEngine::SetRecordingAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::setRecordingAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
	return ret;
}
int UAgoraRtcEngine::SetPlaybackAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::setPlaybackAudioFrameParameters(sampleRate, channel, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
	return ret;
}
int UAgoraRtcEngine::SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
	return ret;
}
int UAgoraRtcEngine::SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel)
{
	auto ret = RtcEngineProxyClassWrapper::setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
	return ret;
}
int UAgoraRtcEngine::EnableAudioSpectrumMonitor(int intervalInMS)
{
	auto ret = RtcEngineProxyClassWrapper::enableAudioSpectrumMonitor(intervalInMS);
	return ret;
}
int UAgoraRtcEngine::DisableAudioSpectrumMonitor()
{
	auto ret = RtcEngineProxyClassWrapper::disableAudioSpectrumMonitor();
	return ret;
}

int UAgoraRtcEngine::RegisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	auto ret = RtcEngineProxyClassWrapper::registerAudioSpectrumObserver(observer);
	return ret;
}
int UAgoraRtcEngine::UnregisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	auto ret = RtcEngineProxyClassWrapper::unregisterAudioSpectrumObserver(observer);
	return ret;
}
int UAgoraRtcEngine::AdjustRecordingSignalVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustRecordingSignalVolume(volume);
	return ret;
}
int UAgoraRtcEngine::MuteRecordingSignal(bool mute)
{
	auto ret = RtcEngineProxyClassWrapper::muteRecordingSignal(mute);
	return ret;
}
int UAgoraRtcEngine::AdjustPlaybackSignalVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustPlaybackSignalVolume(volume);
	return ret;
}
int UAgoraRtcEngine::AdjustUserPlaybackSignalVolume(int uid, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustUserPlaybackSignalVolume(uid, volume);
	return ret;
}
int UAgoraRtcEngine::SetLocalPublishFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	auto ret = RtcEngineProxyClassWrapper::setLocalPublishFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	return ret;
}
int UAgoraRtcEngine::SetRemoteSubscribeFallbackOption(ESTREAM_FALLBACK_OPTIONS option)
{
	auto ret = RtcEngineProxyClassWrapper::setRemoteSubscribeFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	return ret;
}
int UAgoraRtcEngine::EnableLoopbackRecording(bool enabled, FString deviceName)
{
	std::string Device = TCHAR_TO_ANSI(*deviceName);
	auto ret = RtcEngineProxyClassWrapper::enableLoopbackRecording(enabled, Device.c_str());
	return ret;
}
int UAgoraRtcEngine::AdjustLoopbackSignalVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustLoopbackSignalVolume(volume);
	return ret;
}
int UAgoraRtcEngine::GetLoopbackRecordingVolume()
{
	auto ret = RtcEngineProxyClassWrapper::getLoopbackRecordingVolume();
	return ret;
}
int UAgoraRtcEngine::EnableInEarMonitoring(bool enabled, int includeAudioFilters)
{
	auto ret = RtcEngineProxyClassWrapper::enableInEarMonitoring(enabled, includeAudioFilters);
	return ret;
}
int UAgoraRtcEngine::SetInEarMonitoringVolume(int volume)
{
	auto ret = RtcEngineProxyClassWrapper::setInEarMonitoringVolume(volume);
	return ret;
}
int UAgoraRtcEngine::LoadExtensionProvider(FString path, bool unload_after_use)
{
#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)
	std::string Path = TCHAR_TO_ANSI(*path);

	auto ret = RtcEngineProxyClassWrapper::loadExtensionProvider(Path.c_str(), unload_after_use);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}
int UAgoraRtcEngine::SetExtensionProviderProperty(FString provider, FString key, FString value)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Key = TCHAR_TO_ANSI(*key);
	std::string Value = TCHAR_TO_ANSI(*value);
	auto ret = RtcEngineProxyClassWrapper::setExtensionProviderProperty(Provider.c_str(), Key.c_str(), Value.c_str());
	return ret;
}
int UAgoraRtcEngine::EnableExtension(FString provider, FString extension, bool enable, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Extension = TCHAR_TO_ANSI(*extension);
	auto ret = RtcEngineProxyClassWrapper::enableExtension(Provider.c_str(), Extension.c_str(), enable, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetExtensionProperty(FString provider, FString extension, FString key, FString value, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Extension = TCHAR_TO_ANSI(*extension);
	std::string Key = TCHAR_TO_ANSI(*key);
	std::string Value = TCHAR_TO_ANSI(*value);
	auto ret = RtcEngineProxyClassWrapper::setExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), Value.c_str(), (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::GetExtensionProperty(FString provider, FString extension, FString key, FString & value, int buf_len, EMEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_ANSI(*provider);
	std::string Extension = TCHAR_TO_ANSI(*extension);
	std::string Key = TCHAR_TO_ANSI(*key);
	char* val =  new char[buf_len];
	auto ret = RtcEngineProxyClassWrapper::getExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), val, buf_len, (agora::media::MEDIA_SOURCE_TYPE)type);
	value = UTF8_TO_TCHAR(val);
	delete[] val;
	return ret;
}
int UAgoraRtcEngine::SetCameraCapturerConfiguration(const FCameraCapturerConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::setCameraCapturerConfiguration(cameraCapturerConfiguration);
	return ret;
}
int64 UAgoraRtcEngine::CreateCustomVideoTrack()
{
	return RtcEngineProxyClassWrapper::createCustomVideoTrack();
}
int64 UAgoraRtcEngine::CreateCustomEncodedVideoTrack(const FSenderOptions& sender_option)
{
	agora::rtc::SenderOptions senderOptions;
	senderOptions.ccMode = (agora::rtc::TCcMode)sender_option.ccMode;
	senderOptions.codecType = (agora::rtc::VIDEO_CODEC_TYPE)sender_option.codecType;
	senderOptions.targetBitrate = sender_option.targetBitrate;
	return RtcEngineProxyClassWrapper::createCustomEncodedVideoTrack(senderOptions);
}
int UAgoraRtcEngine::DestroyCustomVideoTrack(int64 video_track_id)
{
	auto ret = RtcEngineProxyClassWrapper::destroyCustomVideoTrack(video_track_id);
	return ret;
}
int UAgoraRtcEngine::DestroyCustomEncodedVideoTrack(int64 video_track_id)
{
	auto ret = RtcEngineProxyClassWrapper::destroyCustomEncodedVideoTrack(video_track_id);
	return ret;
}
int UAgoraRtcEngine::SwitchCamera()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::switchCamera();
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsCameraZoomSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::isCameraZoomSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraFaceDetectSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::isCameraFaceDetectSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraTorchSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::isCameraTorchSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraFocusSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::isCameraFocusSupported();
#else
	return false;
#endif
}
bool UAgoraRtcEngine::IsCameraAutoFocusFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	return RtcEngineProxyClassWrapper::isCameraAutoFocusFaceModeSupported();
#else
	return false;
#endif
}
int UAgoraRtcEngine::SetCameraZoomFactor(float factor)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::setCameraZoomFactor(factor);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::EnableFaceDetection(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::enableFaceDetection(enabled);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
float UAgoraRtcEngine::GetCameraMaxZoomFactor()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::getCameraMaxZoomFactor();
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraFocusPositionInPreview(float positionX, float positionY)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::setCameraFocusPositionInPreview(positionX, positionY);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraTorchOn(bool isOn)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::setCameraTorchOn(isOn);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetCameraAutoFocusFaceModeEnabled(bool enabled)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::setCameraAutoFocusFaceModeEnabled(enabled);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsCameraExposurePositionSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::isCameraExposurePositionSupported();
	return ret;
#else
	return false;
#endif
}
int UAgoraRtcEngine::SetCameraExposurePosition(float positionXinView, float positionYinView)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	auto ret = RtcEngineProxyClassWrapper::setCameraExposurePosition(positionXinView, positionYinView);
	return ret;
#else
	return false;
#endif
}

bool UAgoraRtcEngine::IsCameraAutoExposureFaceModeSupported()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	return RtcEngineProxyClassWrapper::isCameraAutoExposureFaceModeSupported();
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
	auto ret = RtcEngineProxyClassWrapper::setCameraAutoExposureFaceModeEnabled(enabled);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
#endif
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
}
int UAgoraRtcEngine::SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker)
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetEnableSpeakerphone(bool speakerOn)
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::setEnableSpeakerphone(speakerOn);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
bool UAgoraRtcEngine::IsSpeakerphoneEnabled()
{
#if defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::isSpeakerphoneEnabled();
	return ret;
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
	agora::rtc::IScreenCaptureSourceList* screenCaptureNative = RtcEngineProxyClassWrapper::getScreenCaptureSources(thumb, icon, includeScreen);
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
	auto ret = RtcEngineProxyClassWrapper::setAudioSessionOperationRestriction((agora::AUDIO_SESSION_OPERATION_RESTRICTION)restriction);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCaptureByDisplayId(int displayId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams)
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
	auto ret = RtcEngineProxyClassWrapper::startScreenCaptureByDisplayId(displayId, rectangle, screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::StartScreenCaptureByScreenRect(const FRectangle& screenRect, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams) __deprecated
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
	auto ret = RtcEngineProxyClassWrapper::startScreenCaptureByScreenRect(rectangle, rectangle, screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::GetAudioDeviceInfo(FDeviceInfo& deviceInfo)
{
#if defined(__ANDROID__)
	agora::rtc::DeviceInfo Info;
	auto ret = RtcEngineProxyClassWrapper::getAudioDeviceInfo(Info);
	if(ret == 0){
		deviceInfo.isLowLatencyAudioSupported = Info.isLowLatencyAudioSupported;
	}
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::StartScreenCaptureByWindowId(int64 windowId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams)
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
	auto ret = RtcEngineProxyClassWrapper::startScreenCaptureByWindowId((agora::view_t)windowId, rectangle, screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	auto ret = RtcEngineProxyClassWrapper::setScreenCaptureContentHint((agora::rtc::VIDEO_CONTENT_HINT)contentHint);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}


int UAgoraRtcEngine::SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	auto ret = RtcEngineProxyClassWrapper::setScreenCaptureScenario((agora::rtc::SCREEN_SCENARIO_TYPE)screenScenario);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::UpdateScreenCaptureRegion(const FRectangle& regionRect)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle;
	rectangle.x = regionRect.x;
	rectangle.y = regionRect.y;
	rectangle.width = regionRect.width;
	rectangle.height = regionRect.height;
	auto ret = RtcEngineProxyClassWrapper::updateScreenCaptureRegion(rectangle);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::UpdateScreenCaptureParameters(const FScreenCaptureParameters& captureParams)
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
	auto ret = RtcEngineProxyClassWrapper::updateScreenCaptureParameters(screenCaptureParameters);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}
int UAgoraRtcEngine::StartScreenCapture(const FScreenCaptureParameters2& captureParams)
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
	auto ret = RtcEngineProxyClassWrapper::startScreenCapture(screenCaptureParameters2);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}


int UAgoraRtcEngine::UpdateScreenCapture(const FScreenCaptureParameters2& captureParams)
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
	auto ret = RtcEngineProxyClassWrapper::updateScreenCapture(screenCaptureParameters2);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::StopScreenCapture()
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	auto ret = RtcEngineProxyClassWrapper::stopScreenCapture();
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif
}

int UAgoraRtcEngine::GetCallId(FString& callId)
{
	agora::util::AString agoraStr;

	auto ret = RtcEngineProxyClassWrapper::getCallId(agoraStr);

	callId = agoraStr->c_str();

	return ret;
}
int UAgoraRtcEngine::Rate(FString callId, int rating, FString description)
{
	std::string CallId = TCHAR_TO_ANSI(*callId);
	auto ret = RtcEngineProxyClassWrapper::rate(CallId.c_str(), rating, TCHAR_TO_ANSI(*description));
	return ret;
}
int UAgoraRtcEngine::Complain(FString callId, FString description)
{
	std::string CallId = TCHAR_TO_ANSI(*callId);
	std::string Description = TCHAR_TO_ANSI(*description);
	auto ret = RtcEngineProxyClassWrapper::complain(CallId.c_str(), Description.c_str());
	return ret;
}
int UAgoraRtcEngine::StartRtmpStreamWithoutTranscoding(FString url)
{
	std::string Url = TCHAR_TO_ANSI(*url);

	auto ret = RtcEngineProxyClassWrapper::startRtmpStreamWithoutTranscoding(Url.c_str());
	return ret;
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
	std::string TempUrl = TCHAR_TO_ANSI(*url);
	auto ret = RtcEngineProxyClassWrapper::startRtmpStreamWithTranscoding(TempUrl.c_str(), liveTranscoding);
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
	auto ret = RtcEngineProxyClassWrapper::updateRtmpTranscoding(liveTranscoding);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;

	return ret;
}
int UAgoraRtcEngine::StopRtmpStream(FString url)
{
	auto ret = RtcEngineProxyClassWrapper::stopRtmpStream(TCHAR_TO_ANSI(*url));
	return ret;
}

int UAgoraRtcEngine::StartLocalVideoTranscoder(const FLocalTranscoderConfiguration& config)
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

int UAgoraRtcEngine::UpdateLocalTranscoderConfiguration(const FLocalTranscoderConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::updateLocalTranscoderConfiguration(localTranscoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::StopLocalVideoTranscoder()
{
	auto ret = RtcEngineProxyClassWrapper::stopLocalVideoTranscoder();
	return ret;
}
int UAgoraRtcEngine::StartPrimaryCameraCapture(const FCameraCapturerConfiguration& config)
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

	auto ret = RtcEngineProxyClassWrapper::startPrimaryCameraCapture(cameraCapturerConfiguration);
	return ret;
}
int UAgoraRtcEngine::StartSecondaryCameraCapture(const FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration;
	agora::rtc::VideoFormat format;
	cameraCapturerConfiguration.format.width = config.format.width;
	cameraCapturerConfiguration.format.height = config.format.height;
	cameraCapturerConfiguration.followEncodeDimensionRatio = config.followEncodeDimensionRatio;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	cameraCapturerConfiguration.cameraDirection = (agora::rtc::CAMERA_DIRECTION)config.cameraDirection;
#else
	sprintf(cameraCapturerConfiguration.deviceId, "%s", TCHAR_TO_UTF8(*config.deviceId));
	//FMemory::Memcpy(cameraCapturerConfiguration.deviceId, *config.deviceId, agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH);
#endif
	auto ret = RtcEngineProxyClassWrapper::startSecondaryCameraCapture(cameraCapturerConfiguration);
	return ret;
}
int UAgoraRtcEngine::StopPrimaryCameraCapture()
{
	auto ret = RtcEngineProxyClassWrapper::stopPrimaryCameraCapture();
	return ret;
}
int UAgoraRtcEngine::StopSecondaryCameraCapture()
{
	auto ret = RtcEngineProxyClassWrapper::stopSecondaryCameraCapture();
	return ret;
}
int UAgoraRtcEngine::SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, EVIDEO_ORIENTATION orientation)
{
	auto ret = RtcEngineProxyClassWrapper::setCameraDeviceOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, (agora::rtc::VIDEO_ORIENTATION)orientation);
	return ret;
}
int UAgoraRtcEngine::SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, EVIDEO_ORIENTATION orientation)
{
	auto ret = RtcEngineProxyClassWrapper::setScreenCaptureOrientation((agora::rtc::VIDEO_SOURCE_TYPE)type, (agora::rtc::VIDEO_ORIENTATION)orientation);
	return ret;
}
int UAgoraRtcEngine::StartPrimaryScreenCapture(const FScreenCaptureConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::startPrimaryScreenCapture(screenCaptureConfiguration);
	return ret;
}
int UAgoraRtcEngine::StartSecondaryScreenCapture(const FScreenCaptureConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::startSecondaryScreenCapture(screenCaptureConfiguration);
	return ret;
}


int UAgoraRtcEngine::StopPrimaryScreenCapture()
{
	auto ret = RtcEngineProxy::stopSecondaryScreenCapture();
	return ret;
}
int UAgoraRtcEngine::StopSecondaryScreenCapture()
{
	auto ret = RtcEngineProxy::stopSecondaryScreenCapture();
	return ret;
}

ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionState()
{
	return (ECONNECTION_STATE_TYPE)RtcEngineProxy::getConnectionState();
}

bool UAgoraRtcEngine::RegisterEventHandler(UIRtcEngineEventHandler* eventHandler)
{
	auto ret = RtcEngineProxyClassWrapper::registerEventHandler(eventHandler);
	return ret;
}

bool UAgoraRtcEngine::UnregisterEventHandler(UIRtcEngineEventHandler* eventHandler)
{
	auto ret = RtcEngineProxyClassWrapper::unregisterEventHandler(eventHandler);
	return ret;
}

int UAgoraRtcEngine::SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority)
{
	auto ret = RtcEngineProxyClassWrapper::setRemoteUserPriority(uid, (agora::rtc::PRIORITY_TYPE)userPriority);
	return ret;
}
int UAgoraRtcEngine::RegisterPacketObserver(UIPacketObserver* observer)
{
	auto ret = RtcEngineProxyClassWrapper::registerPacketObserver(observer);
	return ret;
}
int UAgoraRtcEngine::SetEncryptionMode(FString encryptionMode)
{
	std::string EncryptionMode = TCHAR_TO_ANSI(*encryptionMode);
	auto ret = RtcEngineProxyClassWrapper::setEncryptionMode(EncryptionMode.c_str());
	return ret;
}
int UAgoraRtcEngine::SetEncryptionSecret(FString secret)
{
	std::string Secret = TCHAR_TO_ANSI(*secret);
	auto ret = RtcEngineProxyClassWrapper::setEncryptionSecret(Secret.c_str());
	return ret;
}
int UAgoraRtcEngine::EnableEncryption(bool enabled, const FEncryptionConfig& config)
{
	agora::rtc::EncryptionConfig encryptionConfig;
	encryptionConfig.encryptionMode = (agora::rtc::ENCRYPTION_MODE)config.encryptionMode;
	std::string EncryptionKey = TCHAR_TO_ANSI(*config.encryptionKey);
	encryptionConfig.encryptionKey = EncryptionKey.c_str();
	std::string encryptionKdfSalt = TCHAR_TO_ANSI(*config.encryptionKdfSalt);
	FMemory::Memcpy(encryptionConfig.encryptionKdfSalt, encryptionKdfSalt.c_str(), strlen(encryptionKdfSalt.c_str()) + 1);
	auto ret = RtcEngineProxyClassWrapper::enableEncryption(enabled, encryptionConfig);
	return ret;
}
int UAgoraRtcEngine::CreateDataStream(int& streamId, const FDataStreamConfig& config)
{
	agora::rtc::DataStreamConfig dataStreamConfig;
	dataStreamConfig.syncWithAudio = config.syncWithAudio;
	dataStreamConfig.ordered = config.ordered;
	auto ret = RtcEngineProxyClassWrapper::createDataStream(&streamId, dataStreamConfig);
	return ret;
}
int UAgoraRtcEngine::SendStreamMessage(int streamId, FString data)
{
	const char* Data = TCHAR_TO_UTF8(*data);

	auto ret = RtcEngineProxyClassWrapper::sendStreamMessage(streamId, Data, strlen(Data) + 1);
	return ret;
}
int UAgoraRtcEngine::AddVideoWatermark(FString watermarkUrl, const FWatermarkOptions& options)
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
	std::string WatermarkUrl = TCHAR_TO_ANSI(*watermarkUrl);
	auto ret = RtcEngineProxyClassWrapper::addVideoWatermark(WatermarkUrl.c_str(), watermarkOptions);
	return ret;
}

int UAgoraRtcEngine::ClearVideoWatermarks()
{
	auto ret = RtcEngineProxyClassWrapper::clearVideoWatermarks();
	return ret;
}

int UAgoraRtcEngine::PauseAudio()
{
	auto ret = RtcEngineProxyClassWrapper::pauseAudio();
	return ret;
}
int UAgoraRtcEngine::ResumeAudio()
{
	auto ret = RtcEngineProxyClassWrapper::resumeAudio();
	return ret;
}
int UAgoraRtcEngine::EnableWebSdkInteroperability(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableWebSdkInteroperability(enabled);
	return ret;
}
int UAgoraRtcEngine::SendCustomReportMessage(FString id, FString category, FString event, FString label, int value)
{
	std::string Id = TCHAR_TO_ANSI(*id);
	std::string Category = TCHAR_TO_ANSI(*category);
	std::string Event = TCHAR_TO_ANSI(*event);
	std::string Label = TCHAR_TO_ANSI(*label);
	auto ret = RtcEngineProxyClassWrapper::sendCustomReportMessage(Id.c_str(), Category.c_str(), Event.c_str(), Label.c_str(), value);
	return ret;
}

int UAgoraRtcEngine::RegisterMediaMetadataObserver(UIMetadataObserver* observer, EMETADATA_TYPE type)
{
	auto ret = RtcEngineProxyClassWrapper::registerMediaMetadataObserver(observer, (agora::rtc::IMetadataObserver::METADATA_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::UnregisterMediaMetadataObserver(UIMetadataObserver* observer, EMETADATA_TYPE type)
{
	auto ret = RtcEngineProxyClassWrapper::unregisterMediaMetadataObserver(observer, (agora::rtc::IMetadataObserver::METADATA_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::StartAudioFrameDump(FString channel_id, int64 user_id, FString location, FString uuid, FString passwd, int64 duration_ms, bool auto_upload)
{
	std::string Channel_id = TCHAR_TO_ANSI(*channel_id);
	std::string Location = TCHAR_TO_ANSI(*location);
	std::string Uuid = TCHAR_TO_ANSI(*uuid);
	std::string Passwd = TCHAR_TO_ANSI(*passwd);
	auto ret = RtcEngineProxyClassWrapper::startAudioFrameDump(Channel_id.c_str(), user_id, Location.c_str(), Uuid.c_str(), Passwd.c_str(), duration_ms, auto_upload);
	return ret;
}

int UAgoraRtcEngine::RegisterLocalUserAccount(FString appId, FString userAccount)
{
	std::string AppId = TCHAR_TO_ANSI(*appId);
	std::string UserAccount = TCHAR_TO_ANSI(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::registerLocalUserAccount(AppId.c_str(), UserAccount.c_str());
	return ret;
}
int UAgoraRtcEngine::JoinChannelWithUserAccount(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options)
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
	auto ret = RtcEngineProxyClassWrapper::joinChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions);
	return ret;
}

int UAgoraRtcEngine::JoinChannelWithUserAccountEx(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
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
	auto ret = RtcEngineProxyClassWrapper::joinChannelWithUserAccountEx(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions, eventHandler);
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUserAccount(FString userAccount, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	std::string UserAccount = TCHAR_TO_ANSI(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::getUserInfoByUserAccount(UserAccount.c_str(), &info);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUid(int64 uid, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	auto ret = RtcEngineProxyClassWrapper::getUserInfoByUid(uid, &info);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;
	return ret;
}

int UAgoraRtcEngine::StartChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration)
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
	auto ret = RtcEngineProxyClassWrapper::startChannelMediaRelay(channelMediaRelayConfiguration);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}

int UAgoraRtcEngine::UpdateChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration)
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
	auto ret = RtcEngineProxyClassWrapper::stopChannelMediaRelay();
	return ret;
}
int UAgoraRtcEngine::PauseAllChannelMediaRelay()
{
	auto ret = RtcEngineProxyClassWrapper::pauseAllChannelMediaRelay();
	return ret;
}
int UAgoraRtcEngine::ResumeAllChannelMediaRelay()
{
	auto ret = RtcEngineProxyClassWrapper::resumeAllChannelMediaRelay();
	return ret;
}
int UAgoraRtcEngine::SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile)
{
	auto ret = RtcEngineProxyClassWrapper::setDirectCdnStreamingAudioConfiguration((agora::rtc::AUDIO_PROFILE_TYPE)profile);
	return ret;
}
int UAgoraRtcEngine::SetDirectCdnStreamingVideoConfiguration(const FVideoEncoderConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::setDirectCdnStreamingVideoConfiguration(videoEncoderConfiguration);
	return ret;
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
	auto ret = RtcEngineProxyClassWrapper::startDirectCdnStreaming(eventHandler, PublishUrl.c_str(), directCdnStreamingMediaOptions);
	return ret;
}
int UAgoraRtcEngine::StopDirectCdnStreaming()
{
	auto ret = RtcEngineProxyClassWrapper::stopDirectCdnStreaming();
	return ret;
}
int UAgoraRtcEngine::UpdateDirectCdnStreamingMediaOptions(const FDirectCdnStreamingMediaOptions& options)
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
	return RtcEngineProxyClassWrapper::updateDirectCdnStreamingMediaOptions(directCdnStreamingMediaOptions);
}
int UAgoraRtcEngine::StartRhythmPlayer(FString sound1, FString sound2, const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig;
	agoraRhythmPlayerConfig.beatsPerMeasure = config.beatsPerMeasure;
	agoraRhythmPlayerConfig.beatsPerMinute = config.beatsPerMinute;
	std::string Sound1 = TCHAR_TO_ANSI(*sound1);
	std::string Sound2 = TCHAR_TO_ANSI(*sound2);
	auto ret = RtcEngineProxyClassWrapper::startRhythmPlayer(Sound1.c_str(), Sound1.c_str(), agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraRtcEngine::StopRhythmPlayer()
{
	auto ret = RtcEngineProxyClassWrapper::stopRhythmPlayer();
	return ret;
}
int UAgoraRtcEngine::ConfigRhythmPlayer(const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig;
	agoraRhythmPlayerConfig.beatsPerMeasure = config.beatsPerMeasure;
	agoraRhythmPlayerConfig.beatsPerMinute = config.beatsPerMinute;
	auto ret = RtcEngineProxyClassWrapper::configRhythmPlayer(agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraRtcEngine::TakeSnapshot(int64 uid, FString filePath)
{
	std::string Filepath = TCHAR_TO_ANSI(*filePath);

	auto ret = RtcEngineProxyClassWrapper::takeSnapshot(uid, Filepath.c_str());
	return ret;
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
	auto ret = RtcEngineProxyClassWrapper::enableContentInspect(enabled, contentInspectConfig);
	return ret;
}

int UAgoraRtcEngine::AdjustCustomAudioPublishVolume(int64 trackId, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustCustomAudioPublishVolume(trackId, volume);
	return ret;
}


int UAgoraRtcEngine::AdjustCustomAudioPlayoutVolume(int64 trackId, int volume)
{
	auto ret = RtcEngineProxyClassWrapper::adjustCustomAudioPlayoutVolume(trackId, volume);
	return ret;
}

int UAgoraRtcEngine::SetCloudProxy(ECLOUD_PROXY_TYPE proxyType)
{
	auto ret = RtcEngineProxyClassWrapper::setCloudProxy((agora::rtc::CLOUD_PROXY_TYPE)proxyType);
	return ret;
}
int UAgoraRtcEngine::SetLocalAccessPoint(const FLocalAccessPointConfiguration& config)
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
	auto ret = RtcEngineProxyClassWrapper::setLocalAccessPoint(localAccessPointConfiguration);
	return ret;
}
int UAgoraRtcEngine::SetAdvancedAudioOptions(const FAdvancedAudioOptions& options)
{
	agora::rtc::AdvancedAudioOptions advancedAudioOptions;
	if (options.audioProcessingChannelsValue != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		advancedAudioOptions.audioProcessingChannels = options.audioProcessingChannels;
	}
	auto ret = RtcEngineProxyClassWrapper::setAdvancedAudioOptions(advancedAudioOptions);
	return ret;
}
int UAgoraRtcEngine::SetAVSyncSource(FString channelId, int64 uid)
{
	std::string ChannelId = TCHAR_TO_ANSI(*channelId);
	auto ret = RtcEngineProxyClassWrapper::setAVSyncSource(ChannelId.c_str(), uid);
	return ret;
}
int UAgoraRtcEngine::EnableVideoImageSource(bool enable, const FImageTrackOptions& options)
{
	agora::rtc::ImageTrackOptions imageTrackOptions;
	std::string ImageUrl = TCHAR_TO_ANSI(*options.imageUrl);
	imageTrackOptions.imageUrl = ImageUrl.c_str();
	imageTrackOptions.fps = options.fps;
	auto ret = RtcEngineProxyClassWrapper::enableVideoImageSource(enable, imageTrackOptions);
	return ret;
}
int UAgoraRtcEngine::JoinChannelEx(FString token, const FRtcConnection& connection, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
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

	auto ret = RtcEngineProxyClassWrapper::joinChannelEx(Token.c_str(), rtcConnection, channelMediaOptions, eventHandler);
	return ret;
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

	auto ret = RtcEngineProxyClassWrapper::leaveChannelEx(rtcConnection, leaveChannelOptions);
	return ret;
}

int UAgoraRtcEngine::UpdateChannelMediaOptionsEx(const FChannelMediaOptions& options, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::updateChannelMediaOptionsEx(channelMediaOptions, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetVideoEncoderConfigurationEx(const FVideoEncoderConfiguration& config, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::setVideoEncoderConfigurationEx(videoEncoderConfiguration, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetupRemoteVideoEx(const FVideoCanvas& canvas, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::setupRemoteVideoEx(videoCanvas, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteAudioStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::muteRemoteAudioStreamEx(uid, mute, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteVideoStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::muteRemoteVideoStreamEx(uid, mute, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::setRemoteVideoStreamTypeEx(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FVideoSubscriptionOptions& options, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::setRemoteVideoSubscriptionOptionsEx(uid, videoSubscriptionOptions, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::setRemoteVoicePositionEx(uid, pan, gain, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParamsEx(int64 uid, const FSpatialAudioParams& params, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::setRemoteUserSpatialAudioParamsEx(uid, spatialAudioParams, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::setRemoteRenderModeEx(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableLoopbackRecordingEx(const FRtcConnection& connection, bool enabled, FString deviceName)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::enableLoopbackRecordingEx(rtcConnection, enabled, TCHAR_TO_ANSI(*deviceName));
	return ret;
}
ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionStateEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return (ECONNECTION_STATE_TYPE)RtcEngineProxyClassWrapper::getConnectionStateEx(rtcConnection);
}
int UAgoraRtcEngine::EnableEncryptionEx(const FRtcConnection& connection, bool enabled, const FEncryptionConfig& config)
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

	auto ret = RtcEngineProxyClassWrapper::enableEncryptionEx(rtcConnection, enabled, encryptionConfig);
	return ret;
}

int UAgoraRtcEngine::CreateDataStreamEx(int& streamId, const FDataStreamConfig& config, const FRtcConnection& connection)
{
	agora::rtc::DataStreamConfig dataStreamConfig;
	dataStreamConfig.syncWithAudio = config.syncWithAudio;
	dataStreamConfig.ordered = config.ordered;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::createDataStreamEx(&streamId, dataStreamConfig, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SendStreamMessageEx(int streamId, FString data, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	const char* Data = TCHAR_TO_ANSI(*data);
	auto ret = RtcEngineProxyClassWrapper::sendStreamMessageEx(streamId, Data, strlen(Data), rtcConnection);
	return ret;
}
int UAgoraRtcEngine::AddVideoWatermarkEx(FString watermarkUrl, const FWatermarkOptions& options, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::addVideoWatermarkEx(TCHAR_TO_ANSI(*watermarkUrl), watermarkOptions, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::ClearVideoWatermarkEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::clearVideoWatermarkEx(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SendCustomReportMessageEx(FString id, FString category, FString event, FString label, int value, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::sendCustomReportMessageEx(TCHAR_TO_ANSI(*id), TCHAR_TO_ANSI(*category), TCHAR_TO_ANSI(*event), TCHAR_TO_ANSI(*label), value, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::enableAudioVolumeIndicationEx(interval, smooth, reportVad, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUserAccountEx(FString userAccount, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::getUserInfoByUserAccountEx(TCHAR_TO_ANSI(*userAccount), &info, rtcConnection);

	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;

	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	auto ret = RtcEngineProxyClassWrapper::getUserInfoByUidEx(uid, &info, rtcConnection);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;

	return ret;
}
int UAgoraRtcEngine::SetVideoProfileEx(int width, int height, int frameRate, int bitrate)
{
	return RtcEngineProxyClassWrapper::setVideoProfileEx(width, height, frameRate, bitrate);
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
	auto ret = RtcEngineProxyClassWrapper::enableDualStreamModeEx(enabled, simulcastStreamConfig, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetDualStreamModeEx(ESIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
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
	auto ret = RtcEngineProxyClassWrapper::setDualStreamModeEx((agora::rtc::SIMULCAST_STREAM_MODE)mode, simulcastStreamConfig, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableWirelessAccelerate(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::enableWirelessAccelerate(enabled);
	return ret;
}
int UAgoraRtcEngine::TakeSnapshotEx(const FRtcConnection& connection, int64 uid, FString filePath)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string FilePath = TCHAR_TO_ANSI(*filePath);
	auto ret = RtcEngineProxyClassWrapper::takeSnapshotEx(rtcConnection, uid, FilePath.c_str());
	return ret;
}


int UAgoraRtcEngine::MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::muteLocalAudioStreamEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::muteLocalVideoStreamEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::muteAllRemoteAudioStreamsEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::muteAllRemoteVideoStreamsEx(mute, rtcConnection);
	return ret;
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
	auto ret = RtcEngineProxyClassWrapper::setSubscribeAudioBlocklistEx(data, uidNumber, rtcConnection);
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
	auto ret = RtcEngineProxyClassWrapper::setSubscribeAudioAllowlistEx(data, uidNumber, rtcConnection);
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
	auto ret = RtcEngineProxyClassWrapper::setSubscribeVideoBlocklistEx(data, uidNumber, rtcConnection);
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
	auto ret = RtcEngineProxyClassWrapper::setSubscribeVideoAllowlistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::adjustUserPlaybackSignalVolumeEx(uid, volume, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartRtmpStreamWithoutTranscodingEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string Url = TCHAR_TO_ANSI(*url);
	int ret = RtcEngineProxyClassWrapper::startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	return ret;
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

	auto ret = RtcEngineProxyClassWrapper::startRtmpStreamWithTranscodingEx(streamUrl.c_str(), liveTranscoding, rtcConnection);
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

	auto ret = RtcEngineProxyClassWrapper::updateRtmpTranscodingEx(liveTranscoding, rtcConnection);
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
	auto ret = RtcEngineProxyClassWrapper::startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	return ret;
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

	auto ret = RtcEngineProxyClassWrapper::startChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
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
	auto ret = RtcEngineProxyClassWrapper::updateChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
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
	auto ret = RtcEngineProxyClassWrapper::stopChannelMediaRelayEx(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::PauseAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::pauseAllChannelMediaRelayEx(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::ResumeAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::resumeAllChannelMediaRelayEx(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetParameters(FString parameters)
{
	std::string parameterstr = TCHAR_TO_ANSI(*parameters);

	auto ret = RtcEngineProxyClassWrapper::setParameters(parameterstr.c_str());
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
		UE_LOG(LogTemp, Warning, TEXT("ScreenCaptureSourceType %d"), sourceInfo.type)
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


