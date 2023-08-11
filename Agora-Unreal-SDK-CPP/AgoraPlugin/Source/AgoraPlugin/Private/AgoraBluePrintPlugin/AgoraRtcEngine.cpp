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
	agora::rtc::RtcEngineContext rtcEngineContext;

	if (context.eventHandler != nullptr && std::strcmp(context.eventHandler->eventHandlerType(), "event_handler") == 0)
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
	rtcEngineContext.areaCode = context.areaCode.GetRawValue();
	agora::commons::LogConfig log;
	std::string FilePath = TCHAR_TO_UTF8(*context.logConfig.filePath);
	log.filePath = FilePath.c_str();
	log.fileSizeInKB = context.logConfig.fileSizeInKB;
	log.level = (agora::commons::LOG_LEVEL)context.logConfig.level.GetValue();
	rtcEngineContext.logConfig = log;
	if (context.threadPriority_SetValue)
	{
		rtcEngineContext.threadPriority = (agora::rtc::THREAD_PRIORITY_TYPE)context.threadPriority;
	}
	rtcEngineContext.useExternalEglContext = context.useExternalEglContext;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->initialize(rtcEngineContext);
	return ret;
}

int UAgoraRtcEngine::InitializeEx(const FRtcEngineContextEx& context)
{
	agora::rtc::RtcEngineContext rtcEngineContext;

	if (context.eventHandler != nullptr && std::strcmp(context.eventHandler->eventHandlerType(), "event_handler") == 0)
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
	rtcEngineContext.areaCode = context.areaCode.GetRawValue();

	agora::commons::LogConfig log;
	std::string FilePath = TCHAR_TO_UTF8(*context.logConfig.filePath);
	log.filePath = FilePath.c_str();
	log.fileSizeInKB = context.logConfig.fileSizeInKB;
	log.level = (agora::commons::LOG_LEVEL)context.logConfig.level.GetValue();
	rtcEngineContext.logConfig = log;
	if (context.threadPriority_SetValue)
	{
		rtcEngineContext.threadPriority = (agora::rtc::THREAD_PRIORITY_TYPE)context.threadPriority;
	}
	rtcEngineContext.useExternalEglContext = context.useExternalEglContext;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->initialize(rtcEngineContext);
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
	agora::rtc::CodecCapInfo* codecList = new agora::rtc::CodecCapInfo[size];
	for (int i = 0; i < size; i++)
	{
		codecList[i].codec_type = (agora::rtc::VIDEO_CODEC_TYPE)codecInfo[i].codecType;
		codecList[i].codec_cap_mask = codecInfo[i].codecCapMask;
	}
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->queryCodecCapability(codecList, size);
	delete[] codecList;
	return ret;
}


int UAgoraRtcEngine::QueryDeviceScore()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->queryDeviceScore();
	return ret;
}


int UAgoraRtcEngine::PreloadChannel(FString token, FString channelId, int64 uid)
{
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->preloadChannel(Token.c_str(), ChannelId.c_str(),uid);
	return ret;
}


int UAgoraRtcEngine::PreloadChannelWithUserAccount(FString token, FString channelId, FString userAccount)
{
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->preloadChannel(Token.c_str(), ChannelId.c_str(), UserAccount.c_str());
	return ret;
}


int UAgoraRtcEngine::UpdatePreloadChannelToken(FString token)
{
	std::string Token = TCHAR_TO_UTF8(*token);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updatePreloadChannelToken(Token.c_str());
	return ret;
}

int UAgoraRtcEngine::JoinChannel(FString token, FString channelId, int64 uid, const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(channelMediaOptions, options);
#else
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(channelMediaOptions, options);
#endif

	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannel(Token.c_str(), ChannelId.c_str(), uid, channelMediaOptions);
	return ret;
}
int UAgoraRtcEngine::UpdateChannelMediaOptions(const FChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(channelMediaOptions, options);
#else
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(channelMediaOptions, options);
#endif

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateChannelMediaOptions(channelMediaOptions);
	return ret;
}

int UAgoraRtcEngine::LeaveChannel(const FLeaveChannelOptions& options)
{
	agora::rtc::LeaveChannelOptions leaveChannelOptions;
	SET_AGORA_DATA_LEAVECHANNELOPTIONS(leaveChannelOptions, options);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->leaveChannel(leaveChannelOptions);
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
	agora::rtc::ClientRoleOptions clientRoleOptions;
	clientRoleOptions.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)options.audienceLatencyLevel;
	agora::rtc::CLIENT_ROLE_TYPE roleType = (agora::rtc::CLIENT_ROLE_TYPE)clientroletype;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setClientRole(roleType, clientRoleOptions);
	return ret;
}
int UAgoraRtcEngine::StartEchoTest(const FEchoTestConfiguration& config)
{
	agora::rtc::EchoTestConfiguration echoTestConfiguration;
	echoTestConfiguration.view = (agora::view_t)config.view;
	echoTestConfiguration.enableAudio = config.enableAudio;
	echoTestConfiguration.enableVideo = config.enableVideo;
	std::string Token = TCHAR_TO_UTF8(*config.token);
	echoTestConfiguration.token = Token.c_str();
	std::string ChannelId = TCHAR_TO_UTF8(*config.channelId);
	echoTestConfiguration.channelId = ChannelId.c_str();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startEchoTest(echoTestConfiguration);
	return ret;
}
int UAgoraRtcEngine::StopEchoTest()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopEchoTest();
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
	agora::rtc::LastmileProbeConfig lastmileProbeConfig;
	lastmileProbeConfig.probeUplink = config.probeUplink;
	lastmileProbeConfig.probeDownlink = config.probeDownlink;
	lastmileProbeConfig.expectedUplinkBitrate = config.expectedUplinkBitrate;
	lastmileProbeConfig.expectedDownlinkBitrate = config.expectedDownlinkBitrate;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startLastmileProbeTest(lastmileProbeConfig);
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

	agora::rtc::AdvanceOptions advanceOptions;
	advanceOptions.encodingPreference = (agora::rtc::ENCODING_PREFERENCE)config.advanceOptions.encodingPreference.GetRawValue();
	advanceOptions.compressionPreference = (agora::rtc::COMPRESSION_PREFERENCE)config.advanceOptions.compressionPreference;
	videoEncoderConfiguration.advanceOptions = advanceOptions;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoEncoderConfiguration(videoEncoderConfiguration);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setBeautyEffectOptions(enabled, beautyOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetLowlightEnhanceOptions(bool enabled, const FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::LowlightEnhanceOptions lowlightEnhanceOptions;
	lowlightEnhanceOptions.mode = (agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_MODE)options.mode;
	lowlightEnhanceOptions.level = (agora::rtc::LowlightEnhanceOptions::LOW_LIGHT_ENHANCE_LEVEL)options.level;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLowlightEnhanceOptions(enabled, lowlightEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetVideoDenoiserOptions(bool enabled, const FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VideoDenoiserOptions videoDenoiserOptions;
	videoDenoiserOptions.mode = (agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_MODE)options.mode;
	videoDenoiserOptions.level = (agora::rtc::VideoDenoiserOptions::VIDEO_DENOISER_LEVEL)options.level;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoDenoiserOptions(enabled, videoDenoiserOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::SetColorEnhanceOptions(bool enabled, const FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::ColorEnhanceOptions colorEnhanceOptions;
	colorEnhanceOptions.strengthLevel = options.strengthLevel;
	colorEnhanceOptions.skinProtectLevel = options.skinProtectLevel;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setColorEnhanceOptions(enabled, colorEnhanceOptions, (agora::media::MEDIA_SOURCE_TYPE)type);
	return ret;
}
int UAgoraRtcEngine::EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type)
{
	agora::rtc::VirtualBackgroundSource virtualBackgroundSource;
	virtualBackgroundSource.background_source_type = (agora::rtc::VirtualBackgroundSource::BACKGROUND_SOURCE_TYPE)backgroundSource.background_source_type;
	virtualBackgroundSource.color = backgroundSource.color;
	std::string Source = TCHAR_TO_UTF8(*backgroundSource.source);
	virtualBackgroundSource.source = Source.c_str();
	virtualBackgroundSource.blur_degree = (agora::rtc::VirtualBackgroundSource::BACKGROUND_BLUR_DEGREE)backgroundSource.blur_degree;
	agora::rtc::SegmentationProperty segmentationProperty;
	segmentationProperty.modelType = (agora::rtc::SegmentationProperty::SEG_MODEL_TYPE)segproperty.modelType;
	segmentationProperty.greenCapacity = segproperty.greenCapacity;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableVirtualBackground(enabled, virtualBackgroundSource, segmentationProperty, (agora::media::MEDIA_SOURCE_TYPE)type);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setupRemoteVideo(videoCanvas);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setupLocalVideo(videoCanvas);
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
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions;
	SET_AGORA_DATA_VIDEOSUBSCRIPTIONOPTIONS(videoSubscriptionOptions, options);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoSubscriptionOptions(uid, videoSubscriptionOptions);
	return ret;
}
int UAgoraRtcEngine::SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteDefaultVideoStreamType((agora::rtc::VIDEO_STREAM_TYPE)streamType);
	return ret;
}

int UAgoraRtcEngine::EnableAudioVolumeIndication(int interval, int smooth, bool reportVad)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableAudioVolumeIndication(interval, smooth, reportVad);
	return ret;
}
int UAgoraRtcEngine::StartAudioRecording(const FAudioRecordingConfiguration& config)
{
	agora::rtc::AudioRecordingConfiguration audioRecordingConfiguration;
	std::string FilePath = TCHAR_TO_UTF8(*config.filePath);
	audioRecordingConfiguration.filePath = FilePath.c_str();
	audioRecordingConfiguration.encode = config.encode;
	audioRecordingConfiguration.sampleRate = config.sampleRate;
	audioRecordingConfiguration.fileRecordingType = (agora::rtc::AUDIO_FILE_RECORDING_TYPE)config.fileRecordingType;
	audioRecordingConfiguration.quality = (agora::rtc::AUDIO_RECORDING_QUALITY_TYPE)config.quality;
	audioRecordingConfiguration.recordingChannel = config.recordingChannel;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startAudioRecording(audioRecordingConfiguration);
	return ret;
}

int UAgoraRtcEngine::RegisterAudioEncodedFrameObserver(const FAudioEncodedFrameObserverConfig& config, UIAudioEncodedFrameObserver* observer)
{
	agora::rtc::AudioEncodedFrameObserverConfig audioEncodedFrameObserverConfig;
	audioEncodedFrameObserverConfig.postionType = (agora::rtc::AUDIO_ENCODED_FRAME_OBSERVER_POSITION)config.postionType;
	audioEncodedFrameObserverConfig.encodingType = config.encodingType.GetRawValue();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->registerAudioEncodedFrameObserver(audioEncodedFrameObserverConfig, observer);
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

int UAgoraRtcEngine::StartAudioMixing(FString filePath, bool loopback, int cycle, int startPos)
{
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startAudioMixing(FilePath.c_str(), loopback, cycle, startPos);
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
	agora::SpatialAudioParams spatialAudioParams;
	SET_AGORA_DATA_SPATIALAUDIOPARAMS(spatialAudioParams, params);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteUserSpatialAudioParams(uid, spatialAudioParams);
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
	requestId = _requestId->c_str();
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
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.height = streamConfig.dimensions.height;
	dim.width = streamConfig.dimensions.width;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableDualStreamMode(enabled, simulcastStreamConfig);
	return ret;
}
int UAgoraRtcEngine::SetDualStreamMode(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.height = streamConfig.dimensions.height;
	dim.width = streamConfig.dimensions.width;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDualStreamMode(mode.GetRawValue(), simulcastStreamConfig);
	return ret;
}


int UAgoraRtcEngine::EnableEchoCancellationExternal(bool enabled, int audioSourceDelay)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableEchoCancellationExternal(enabled, audioSourceDelay);
	return ret;
}

int UAgoraRtcEngine::EnableCustomAudioLocalPlayback(int64 trackId, bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableCustomAudioLocalPlayback(trackId, enabled);
	return ret;
}


int UAgoraRtcEngine::SetPublishAudioFrameParameters(int sampleRate, int channel, int samplesPerCall)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setPublishAudioFrameParameters(sampleRate, channel, samplesPerCall);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setCameraCapturerConfiguration(cameraCapturerConfiguration);
	return ret;
}
int64 UAgoraRtcEngine::CreateCustomVideoTrack()
{
	return RtcEngineProxyClassWrapper::GetInstance()->createCustomVideoTrack();
}
int64 UAgoraRtcEngine::CreateCustomEncodedVideoTrack(const FSenderOptions& sender_option)
{
	agora::rtc::SenderOptions senderOptions;
	senderOptions.ccMode = (agora::rtc::TCcMode)sender_option.ccMode;
	senderOptions.codecType = (agora::rtc::VIDEO_CODEC_TYPE)sender_option.codecType;
	senderOptions.targetBitrate = sender_option.targetBitrate;
	return RtcEngineProxyClassWrapper::GetInstance()->createCustomEncodedVideoTrack(senderOptions);
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
	return false;
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCaptureByDisplayId(displayId, rectangle, screenCaptureParameters);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCaptureByScreenRect(rectangle, rectangle, screenCaptureParameters);
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
	deviceInfo.isLowLatencyAudioSupported = Info.isLowLatencyAudioSupported;
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCaptureByWindowId((agora::view_t)windowId, rectangle, screenCaptureParameters);
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
	agora::rtc::Rectangle rectangle;
	rectangle.x = regionRect.x;
	rectangle.y = regionRect.y;
	rectangle.width = regionRect.width;
	rectangle.height = regionRect.height;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateScreenCaptureRegion(rectangle);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateScreenCaptureParameters(screenCaptureParameters);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCapture(screenCaptureParameters2);
	return ret;
#else
	return -AGORA_UNREAL_PLUGIN_ERROR_CODE::ERROR_NULLPTR;
#endif

}


int UAgoraRtcEngine::StartScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType, const FScreenCaptureConfiguration& config)
{

	agora::rtc::ScreenCaptureConfiguration screenCaptureConfiguration;
	screenCaptureConfiguration.isCaptureWindow = config.isCaptureWindow;
	screenCaptureConfiguration.displayId = config.displayId;
	const FRectangle* rect = &(config.screenRect);
	screenCaptureConfiguration.screenRect = agora::rtc::Rectangle(rect->x, rect->y, rect->width, rect->height);
	screenCaptureConfiguration.windowId = (agora::view_t)config.windowId;
	const FScreenCaptureParameters* scpptr = &(config.params);
	screenCaptureConfiguration.params = agora::rtc::ScreenCaptureParameters(
		scpptr->dimensions.width,
		scpptr->dimensions.height,
		scpptr->frameRate,
		scpptr->bitrate,
		scpptr->captureMouseCursor,
		scpptr->windowFocus,
		(agora::view_t*)scpptr->excludeWindowList,
		scpptr->excludeWindowCount);

	const FRectangle* regionRect = &(config.regionRect);
	screenCaptureConfiguration.regionRect = agora::rtc::Rectangle(regionRect->x, regionRect->y, regionRect->width, regionRect->height);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startScreenCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType, screenCaptureConfiguration);
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
	return RtcEngineProxyClassWrapper::GetInstance()->updateScreenCapture(screenCaptureParameters2);
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


int UAgoraRtcEngine::StopScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopScreenCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
	return ret;
}


int UAgoraRtcEngine::GetCallId(FString& callId)
{
	agora::util::AString agoraStr;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getCallId(agoraStr);

	callId = agoraStr->c_str();

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
	std::string TranscodingExtraInfo = TCHAR_TO_UTF8(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_UTF8(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_UTF8(*transcoding.watermark[i].url);
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
		std::string Url = TCHAR_TO_UTF8(*transcoding.backgroundImage[i].url);
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
		std::string FeatureName = TCHAR_TO_UTF8(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;
	std::string TempUrl = TCHAR_TO_UTF8(*url);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithTranscoding(TempUrl.c_str(), liveTranscoding);
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
	std::string TranscodingExtraInfo = TCHAR_TO_UTF8(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_UTF8(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_UTF8(*transcoding.watermark[i].url);
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
		std::string Url = TCHAR_TO_UTF8(*transcoding.backgroundImage[i].url);
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
		std::string FeatureName = TCHAR_TO_UTF8(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateRtmpTranscoding(liveTranscoding);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;

	return ret;
}
int UAgoraRtcEngine::StopRtmpStream(FString url)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopRtmpStream(TCHAR_TO_UTF8(*url));
	return ret;
}

int UAgoraRtcEngine::StartCameraCapture(EVIDEO_SOURCE_TYPE sourceType, const FCameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	cameraCapturerConfiguration.cameraDirection = (agora::rtc::CAMERA_DIRECTION)config.cameraDirection;
#else
	const TCHAR* str = config.deviceId.GetCharArray().GetData();
	FMemory::Memcpy(cameraCapturerConfiguration.deviceId, str, config.deviceId.Len());
#endif
	agora::rtc::VideoFormat videoFormat(config.format.width, config.format.height, config.format.fps);
	cameraCapturerConfiguration.format = videoFormat;
	cameraCapturerConfiguration.followEncodeDimensionRatio = config.followEncodeDimensionRatio;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startCameraCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType, cameraCapturerConfiguration);
	return ret;
}


int UAgoraRtcEngine::StopCameraCapture(EVIDEO_SOURCE_TYPE sourceType)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopCameraCapture((agora::rtc::VIDEO_SOURCE_TYPE)sourceType);
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
		std::string ImageUrl = TCHAR_TO_UTF8(*config.VideoInputStreams[i].imageUrl);
		videoStream[i].imageUrl = ImageUrl.c_str();
		videoStream[i].mirror = config.VideoInputStreams[i].mirror;
		videoStream[i].remoteUserUid = config.VideoInputStreams[i].remoteUserUid;
		videoStream[i].sourceType = (agora::rtc::VIDEO_SOURCE_TYPE)config.VideoInputStreams[i].sourceType;
		videoStream[i].width = config.VideoInputStreams[i].width;
		videoStream[i].x = config.VideoInputStreams[i].x;
		videoStream[i].y = config.VideoInputStreams[i].y;
		videoStream[i].zOrder = config.VideoInputStreams[i].zOrder;
	}
	localTranscoderConfiguration.videoInputStreams = videoStream;

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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startLocalVideoTranscoder(localTranscoderConfiguration);
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
		std::string ImageUrl = TCHAR_TO_UTF8(*config.VideoInputStreams[i].imageUrl);
		videoStream[i].imageUrl = ImageUrl.c_str();
		videoStream[i].mirror = config.VideoInputStreams[i].mirror;
		videoStream[i].remoteUserUid = config.VideoInputStreams[i].remoteUserUid;
		videoStream[i].sourceType = (agora::rtc::VIDEO_SOURCE_TYPE)config.VideoInputStreams[i].sourceType;
		videoStream[i].width = config.VideoInputStreams[i].width;
		videoStream[i].x = config.VideoInputStreams[i].x;
		videoStream[i].y = config.VideoInputStreams[i].y;
		videoStream[i].zOrder = config.VideoInputStreams[i].zOrder;
	}
	localTranscoderConfiguration.videoInputStreams = videoStream;

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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateLocalTranscoderConfiguration(localTranscoderConfiguration);
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
	agora::rtc::EncryptionConfig encryptionConfig;
	encryptionConfig.encryptionMode = (agora::rtc::ENCRYPTION_MODE)config.encryptionMode;
	std::string EncryptionKey = TCHAR_TO_UTF8(*config.encryptionKey);
	encryptionConfig.encryptionKey = EncryptionKey.c_str();
	std::string encryptionKdfSalt = TCHAR_TO_UTF8(*config.encryptionKdfSalt);
	FMemory::Memcpy(encryptionConfig.encryptionKdfSalt, encryptionKdfSalt.c_str(), strlen(encryptionKdfSalt.c_str()) + 1);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableEncryption(enabled, encryptionConfig);
	return ret;
}
int UAgoraRtcEngine::CreateDataStream(int& streamId, const FDataStreamConfig& config)
{
	agora::rtc::DataStreamConfig dataStreamConfig;
	dataStreamConfig.syncWithAudio = config.syncWithAudio;
	dataStreamConfig.ordered = config.ordered;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->createDataStream(&streamId, dataStreamConfig);
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
	std::string WatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->addVideoWatermark(WatermarkUrl.c_str(), watermarkOptions);
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
int UAgoraRtcEngine::StartAudioFrameDump(FString channel_id, int64 user_id, FString location, FString uuid, FString passwd, int64 duration_ms, bool auto_upload)
{
	std::string Channel_id = TCHAR_TO_UTF8(*channel_id);
	std::string Location = TCHAR_TO_UTF8(*location);
	std::string Uuid = TCHAR_TO_UTF8(*uuid);
	std::string Passwd = TCHAR_TO_UTF8(*passwd);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startAudioFrameDump(Channel_id.c_str(), user_id, Location.c_str(), Uuid.c_str(), Passwd.c_str(), duration_ms, auto_upload);
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
	agora::rtc::ChannelMediaOptions channelMediaOptions;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(channelMediaOptions, options);
#else
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(channelMediaOptions, options);
#endif

	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions);
	return ret;
}

int UAgoraRtcEngine::JoinChannelWithUserAccountEx(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(channelMediaOptions, options);
#else
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(channelMediaOptions, options);
#endif

	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannelWithUserAccountEx(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions, eventHandler);
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUserAccount(FString userAccount, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUserAccount(UserAccount.c_str(), &info);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUid(int64 uid, FUserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUid(uid, &info);
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
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startChannelMediaRelay(channelMediaRelayConfiguration);
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
	int ret = RtcEngineProxyClassWrapper::GetInstance()->updateChannelMediaRelay(channelMediaRelayConfiguration);
	delete mediaInfo;
	delete[] mediaInfos;
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
	agora::rtc::AdvanceOptions advanceOptions;
	advanceOptions.encodingPreference = (agora::rtc::ENCODING_PREFERENCE)config.advanceOptions.encodingPreference.GetRawValue();
	advanceOptions.compressionPreference = (agora::rtc::COMPRESSION_PREFERENCE)config.advanceOptions.compressionPreference;
	videoEncoderConfiguration.advanceOptions = advanceOptions;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDirectCdnStreamingVideoConfiguration(videoEncoderConfiguration);
	return ret;
}
int UAgoraRtcEngine::StartDirectCdnStreaming(UIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options)
{
	agora::rtc::DirectCdnStreamingMediaOptions directCdnStreamingMediaOptions;
	SET_AGORA_DATA_DIRECTCDNSTREAMINGMEDIAOPTIONS(directCdnStreamingMediaOptions, options);
	std::string PublishUrl = TCHAR_TO_UTF8(*publishUrl);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startDirectCdnStreaming(eventHandler, PublishUrl.c_str(), directCdnStreamingMediaOptions);
	return ret;
}
int UAgoraRtcEngine::StopDirectCdnStreaming()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopDirectCdnStreaming();
	return ret;
}
int UAgoraRtcEngine::UpdateDirectCdnStreamingMediaOptions(const FDirectCdnStreamingMediaOptions& options)
{
	agora::rtc::DirectCdnStreamingMediaOptions directCdnStreamingMediaOptions;
	SET_AGORA_DATA_DIRECTCDNSTREAMINGMEDIAOPTIONS(directCdnStreamingMediaOptions, options);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateDirectCdnStreamingMediaOptions(directCdnStreamingMediaOptions);
	return ret;
}
int UAgoraRtcEngine::StartRhythmPlayer(FString sound1, FString sound2, const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig;
	agoraRhythmPlayerConfig.beatsPerMeasure = config.beatsPerMeasure;
	agoraRhythmPlayerConfig.beatsPerMinute = config.beatsPerMinute;
	std::string Sound1 = TCHAR_TO_UTF8(*sound1);
	std::string Sound2 = TCHAR_TO_UTF8(*sound2);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRhythmPlayer(Sound1.c_str(), Sound1.c_str(), agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraRtcEngine::StopRhythmPlayer()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopRhythmPlayer();
	return ret;
}
int UAgoraRtcEngine::ConfigRhythmPlayer(const FAgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig;
	agoraRhythmPlayerConfig.beatsPerMeasure = config.beatsPerMeasure;
	agoraRhythmPlayerConfig.beatsPerMinute = config.beatsPerMinute;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->configRhythmPlayer(agoraRhythmPlayerConfig);
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
	agora::media::ContentInspectConfig contentInspectConfig;
	std::string ExtraInfo = TCHAR_TO_UTF8(*config.extraInfo);
	contentInspectConfig.extraInfo = ExtraInfo.c_str();
	agora::media::ContentInspectModule modules[MAX_CONTENT_INSPECT_MODULE_COUNT];
	for (int i = 0; i < config.moduleCount; i++)
	{
		modules[i].interval = config.modules[i].interval;
		modules[i].type = (agora::media::CONTENT_INSPECT_TYPE)config.modules[i].type;
	}
	FMemory::Memcpy(contentInspectConfig.modules, modules, sizeof(agora::media::ContentInspectModule) * config.moduleCount);
	contentInspectConfig.moduleCount = config.moduleCount;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableContentInspect(enabled, contentInspectConfig);
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
	agora::rtc::LocalAccessPointConfiguration localAccessPointConfiguration;
	std::string Iplist = TCHAR_TO_UTF8(*config.ipList);
	const char* iplist = Iplist.c_str();
	localAccessPointConfiguration.ipList = &iplist;
	localAccessPointConfiguration.ipListSize = config.ipListSize;
	std::string DomainList = TCHAR_TO_UTF8(*config.domainList);
	const char* domainList = DomainList.c_str();
	localAccessPointConfiguration.domainList = &domainList;
	localAccessPointConfiguration.domainListSize = config.domainListSize;
	std::string VerifyDomainName = TCHAR_TO_UTF8(*config.domainList);
	localAccessPointConfiguration.verifyDomainName = VerifyDomainName.c_str();
	localAccessPointConfiguration.mode = (agora::rtc::LOCAL_PROXY_MODE)config.mode;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setLocalAccessPoint(localAccessPointConfiguration);
	return ret;
}
int UAgoraRtcEngine::SetAdvancedAudioOptions(const FAdvancedAudioOptions& options)
{
	agora::rtc::AdvancedAudioOptions advancedAudioOptions;
	SET_AGORA_DATA_ADVANCEDAUDIOOPTIONS(advancedAudioOptions, options);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setAdvancedAudioOptions(advancedAudioOptions);
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
	agora::rtc::ImageTrackOptions imageTrackOptions;
	std::string ImageUrl = TCHAR_TO_UTF8(*options.imageUrl);
	imageTrackOptions.imageUrl = ImageUrl.c_str();
	imageTrackOptions.fps = options.fps;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableVideoImageSource(enable, imageTrackOptions);
	return ret;
}
int UAgoraRtcEngine::JoinChannelEx(FString token, const FRtcConnection& connection, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string channel = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = channel.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::ChannelMediaOptions channelMediaOptions;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(channelMediaOptions, options);
#else
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(channelMediaOptions, options);
#endif

	std::string Token = TCHAR_TO_UTF8(*token);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->joinChannelEx(Token.c_str(), rtcConnection, channelMediaOptions, eventHandler);
	return ret;
}


int UAgoraRtcEngine::LeaveChannelEx(const FRtcConnection& connection, const FLeaveChannelOptions& options)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::LeaveChannelOptions leaveChannelOptions;
	SET_AGORA_DATA_LEAVECHANNELOPTIONS(leaveChannelOptions, options);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->leaveChannelEx(rtcConnection, leaveChannelOptions);
	return ret;
}

int UAgoraRtcEngine::UpdateChannelMediaOptionsEx(const FChannelMediaOptions& options, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions;

#if defined(__ANDROID__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_MOBILE(channelMediaOptions, options);
#else
	SET_AGORA_DATA_CHANNELMEDIAOPTIONS_NONMOBILE_PLATFORM(channelMediaOptions, options);
#endif

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateChannelMediaOptionsEx(channelMediaOptions, rtcConnection);
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
	agora::rtc::AdvanceOptions advanceOptions;
	advanceOptions.encodingPreference = (agora::rtc::ENCODING_PREFERENCE)config.advanceOptions.encodingPreference.GetRawValue();
	advanceOptions.compressionPreference = (agora::rtc::COMPRESSION_PREFERENCE)config.advanceOptions.compressionPreference;
	videoEncoderConfiguration.advanceOptions = advanceOptions;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoEncoderConfigurationEx(videoEncoderConfiguration, rtcConnection);
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
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	//rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setupRemoteVideoEx(videoCanvas, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteAudioStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRemoteAudioStreamEx(uid, mute, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::MuteRemoteVideoStreamEx(int64 uid, bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteRemoteVideoStreamEx(uid, mute, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoStreamTypeEx(uid, (agora::rtc::VIDEO_STREAM_TYPE)streamType, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FVideoSubscriptionOptions& options, const FRtcConnection& connection)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions;
	SET_AGORA_DATA_VIDEOSUBSCRIPTIONOPTIONS(videoSubscriptionOptions, options);
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVideoSubscriptionOptionsEx(uid, videoSubscriptionOptions, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteVoicePositionEx(uid, pan, gain, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteUserSpatialAudioParamsEx(int64 uid, const FSpatialAudioParams& params, const FRtcConnection& connection)
{
	agora::SpatialAudioParams spatialAudioParams;
	SET_AGORA_DATA_SPATIALAUDIOPARAMS(spatialAudioParams, params);
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteUserSpatialAudioParamsEx(uid, spatialAudioParams, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setRemoteRenderModeEx(uid, (agora::media::base::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableLoopbackRecordingEx(const FRtcConnection& connection, bool enabled, FString deviceName)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableLoopbackRecordingEx(rtcConnection, enabled, TCHAR_TO_UTF8(*deviceName));
	return ret;
}
ECONNECTION_STATE_TYPE UAgoraRtcEngine::GetConnectionStateEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	return (ECONNECTION_STATE_TYPE)RtcEngineProxyClassWrapper::GetInstance()->getConnectionStateEx(rtcConnection);
}
int UAgoraRtcEngine::EnableEncryptionEx(const FRtcConnection& connection, bool enabled, const FEncryptionConfig& config)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::EncryptionConfig encryptionConfig;
	encryptionConfig.encryptionMode = (agora::rtc::ENCRYPTION_MODE)config.encryptionMode;
	std::string EncryptionKey = TCHAR_TO_UTF8(*config.encryptionKey);
	encryptionConfig.encryptionKey = EncryptionKey.c_str();
	std::string encryptionKdfSalt = TCHAR_TO_UTF8(*config.encryptionKdfSalt);
	FMemory::Memcpy(encryptionConfig.encryptionKdfSalt, encryptionKdfSalt.c_str(), 32);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableEncryptionEx(rtcConnection, enabled, encryptionConfig);
	return ret;
}

int UAgoraRtcEngine::CreateDataStreamEx(int& streamId, const FDataStreamConfig& config, const FRtcConnection& connection)
{
	agora::rtc::DataStreamConfig dataStreamConfig;
	dataStreamConfig.syncWithAudio = config.syncWithAudio;
	dataStreamConfig.ordered = config.ordered;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->createDataStreamEx(&streamId, dataStreamConfig, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SendStreamMessageEx(int streamId, FString data, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	const char* Data = StdStrData.c_str();
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendStreamMessageEx(streamId, Data, strlen(Data), rtcConnection);
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
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->addVideoWatermarkEx(TCHAR_TO_UTF8(*watermarkUrl), watermarkOptions, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::ClearVideoWatermarkEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->clearVideoWatermarkEx(rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SendCustomReportMessageEx(FString id, FString category, FString event, FString label, int value, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->sendCustomReportMessageEx(TCHAR_TO_UTF8(*id), TCHAR_TO_UTF8(*category), TCHAR_TO_UTF8(*event), TCHAR_TO_UTF8(*label), value, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableAudioVolumeIndicationEx(interval, smooth, reportVad, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUserAccountEx(FString userAccount, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUserAccountEx(TCHAR_TO_UTF8(*userAccount), &info, rtcConnection);

	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;

	return ret;
}
int UAgoraRtcEngine::GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, const FRtcConnection& connection)
{
	agora::rtc::UserInfo info;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->getUserInfoByUidEx(uid, &info, rtcConnection);
	userInfo.uid = info.uid;
	userInfo.userAccount = info.userAccount;

	return ret;
}


int UAgoraRtcEngine::SetVideoProfileEx(int width, int height, int frameRate, int bitrate)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setVideoProfileEx(width, height, frameRate, bitrate);
	return ret;
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
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableDualStreamModeEx(enabled, simulcastStreamConfig, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::SetDualStreamModeEx(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig;
	agora::rtc::VideoDimensions dim;
	dim.width = streamConfig.dimensions.width;
	dim.height = streamConfig.dimensions.height;
	simulcastStreamConfig.dimensions = dim;
	simulcastStreamConfig.kBitrate = streamConfig.bitrate;
	simulcastStreamConfig.framerate = streamConfig.framerate;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setDualStreamModeEx(mode.GetRawValue(), simulcastStreamConfig, rtcConnection);
	return ret;
}
int UAgoraRtcEngine::EnableWirelessAccelerate(bool enabled)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->enableWirelessAccelerate(enabled);
	return ret;
}
int UAgoraRtcEngine::TakeSnapshotEx(const FRtcConnection& connection, int64 uid, FString filePath)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->takeSnapshotEx(rtcConnection, uid, FilePath.c_str());
	return ret;
}


int UAgoraRtcEngine::MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteLocalAudioStreamEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteLocalVideoStreamEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteAllRemoteAudioStreamsEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->muteAllRemoteVideoStreamsEx(mute, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeAudioBlocklistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeAudioAllowlistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeVideoBlocklistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	agora::rtc::uid_t* data = new agora::rtc::uid_t[uidList.Num()];
	for (int i = 0; i < uidList.Num(); i++)
	{
		data[i] = (agora::rtc::uid_t)uidList[i];
	}
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setSubscribeVideoAllowlistEx(data, uidNumber, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->adjustUserPlaybackSignalVolumeEx(uid, volume, rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartRtmpStreamWithoutTranscodingEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string Url = TCHAR_TO_UTF8(*url);
	int ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartRtmpStreamWithTranscodingEx(FString url, const FLiveTranscoding& transcoding, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string streamUrl = TCHAR_TO_UTF8(*url);

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
	std::string TranscodingExtraInfo = TCHAR_TO_UTF8(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_UTF8(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_UTF8(*transcoding.watermark[i].url);
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
		std::string Url = TCHAR_TO_UTF8(*transcoding.backgroundImage[i].url);
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
		std::string FeatureName = TCHAR_TO_UTF8(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithTranscodingEx(streamUrl.c_str(), liveTranscoding, rtcConnection);
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
	std::string TranscodingExtraInfo = TCHAR_TO_UTF8(*transcoding.transcodingExtraInfo);
	liveTranscoding.transcodingExtraInfo = TranscodingExtraInfo.c_str();
	std::string Metadata = TCHAR_TO_UTF8(*transcoding.metadata);
	liveTranscoding.metadata = Metadata.c_str();
	agora::rtc::RtcImage* image = new agora::rtc::RtcImage[transcoding.watermarkCount];
	for (int i = 0; i < transcoding.watermarkCount; i++)
	{
		image[i].alpha = transcoding.watermark[i].alpha;
		std::string Url = TCHAR_TO_UTF8(*transcoding.watermark[i].url);
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
		std::string Url = TCHAR_TO_UTF8(*transcoding.backgroundImage[i].url);
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
		std::string FeatureName = TCHAR_TO_UTF8(*transcoding.advancedFeatures[i].featureName);
		feature[i].featureName = FeatureName.c_str();
		feature[i].opened = transcoding.advancedFeatures[i].opened;
	}
	liveTranscoding.advancedFeatures = feature;
	liveTranscoding.advancedFeatureCount = transcoding.advancedFeatureCount;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateRtmpTranscodingEx(liveTranscoding, rtcConnection);
	delete[] trans;
	delete[] image;
	delete[] bgImage;
	delete[] feature;
	return ret;
}

int UAgoraRtcEngine::StopRtmpStreamEx(FString url, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	std::string Url = TCHAR_TO_UTF8(*url);
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	return ret;
}

int UAgoraRtcEngine::StartChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration;
	agora::rtc::ChannelMediaInfo* mediaInfo = new agora::rtc::ChannelMediaInfo();
	std::string ChannelName = TCHAR_TO_UTF8(*configuration.srcInfo.channelName);
	mediaInfo->channelName = ChannelName.c_str();
	std::string Token = TCHAR_TO_UTF8(*configuration.srcInfo.token);
	mediaInfo->token = Token.c_str();
	mediaInfo->uid = configuration.srcInfo.uid;
	channelMediaRelayConfiguration.srcInfo = mediaInfo;
	agora::rtc::ChannelMediaInfo* mediaInfos = new agora::rtc::ChannelMediaInfo[configuration.destCount];
	for (int i = 0; i < configuration.destCount; i++)
	{
		std::string ChannelNameTemp = TCHAR_TO_UTF8(*configuration.srcInfo.channelName);
		mediaInfos[i].channelName = ChannelNameTemp.c_str();
		std::string TokenTemp = TCHAR_TO_UTF8(*configuration.srcInfo.channelName);
		mediaInfos[i].token = TokenTemp.c_str();
		mediaInfos[i].uid = configuration.destInfos[i].uid;
	}
	channelMediaRelayConfiguration.destInfos = mediaInfos;
	channelMediaRelayConfiguration.destCount = configuration.destCount;

	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}

int UAgoraRtcEngine::UpdateChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration;
	agora::rtc::ChannelMediaInfo* mediaInfo = new agora::rtc::ChannelMediaInfo();
	std::string ChannelName = TCHAR_TO_UTF8(*configuration.srcInfo.channelName);
	mediaInfo->channelName = ChannelName.c_str();
	std::string Token = TCHAR_TO_UTF8(*configuration.srcInfo.token);
	mediaInfo->token = Token.c_str();
	mediaInfo->uid = configuration.srcInfo.uid;
	channelMediaRelayConfiguration.srcInfo = mediaInfo;
	agora::rtc::ChannelMediaInfo* mediaInfos = new agora::rtc::ChannelMediaInfo[configuration.destCount];
	for (int i = 0; i < configuration.destCount; i++)
	{
		std::string ChannelNameTemp = TCHAR_TO_UTF8(*configuration.srcInfo.channelName);
		mediaInfos[i].channelName = ChannelNameTemp.c_str();
		std::string TokenTemp = TCHAR_TO_UTF8(*configuration.srcInfo.channelName);
		mediaInfos[i].token = TokenTemp.c_str();
		mediaInfos[i].uid = configuration.destInfos[i].uid;
	}
	channelMediaRelayConfiguration.destInfos = mediaInfos;
	channelMediaRelayConfiguration.destCount = configuration.destCount;
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->updateChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	delete mediaInfo;
	delete[] mediaInfos;
	return ret;
}

int UAgoraRtcEngine::StopChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->stopChannelMediaRelayEx(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::PauseAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->pauseAllChannelMediaRelayEx(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::ResumeAllChannelMediaRelayEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	rtcConnection.localUid = connection.localUid;
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->resumeAllChannelMediaRelayEx(rtcConnection);
	return ret;
}

int UAgoraRtcEngine::SetParameters(FString parameters)
{
	std::string parameterstr = TCHAR_TO_UTF8(*parameters);

	auto ret = RtcEngineProxyClassWrapper::GetInstance()->setParameters(parameterstr.c_str());
	return ret;
}


int UAgoraRtcEngine::StartMediaRenderingTracing()
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->startMediaRenderingTracing();
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


bool UAgoraRtcEngine::IsFeatureAvailableOnDevice(EFeatureType type)
{
	auto ret = RtcEngineProxyClassWrapper::GetInstance()->isFeatureAvailableOnDevice((agora::rtc::FeatureType)(int)type);
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
		sourceInfo.type = info.type;
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


