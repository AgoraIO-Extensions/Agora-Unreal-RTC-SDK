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


int UAgoraBPuRtcEngine::Initialize(const FUABT_RtcEngineContext& context)
{
	//Instance->AddToRoot();
	UserRtcEventHandler.Reset();
	UserRtcEventHandlerEx.Reset();
	EventHandlerType = EAgoraBPuEventHandlerType::None;


	AgoraUERtcEngine::RtcEngineAppType = AgoraAppType::kAppTypeUnrealBlueprint;
	agora::rtc::RtcEngineContext AgoraData_Context = context.CreateRawData();
	
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
	context.FreeRawData(AgoraData_Context);

	return ret;
}


int UAgoraBPuRtcEngine::SetupLocalVideo(const FUABT_VideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	videoCanvas.uid = canvas.uid;
	videoCanvas.sourceType = UABTEnum::ToRawValue(canvas.sourceType);
	auto ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	return ret;
}

int UAgoraBPuRtcEngine::SetupRemoteVideo(const FUABT_VideoCanvas& canvas)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	videoCanvas.renderMode = UABTEnum::ToRawValue(canvas.renderMode);
	videoCanvas.mirrorMode = UABTEnum::ToRawValue(canvas.mirrorMode);
	videoCanvas.uid = canvas.uid;
	//videoCanvas.priv = canvas.priv;
	videoCanvas.sourceType = UABTEnum::ToRawValue(canvas.sourceType);
	//videoCanvas.cropArea = canvas.cropArea;
	videoCanvas.setupMode = UABTEnum::ToRawValue(canvas.setupMode);
	auto ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
	return ret;
}

int UAgoraBPuRtcEngine::SetupRemoteVideoEx(const FUABT_VideoCanvas& canvas, const FUABT_RtcConnection& connection)
{
	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = (agora::view_t)canvas.view;
	videoCanvas.renderMode = UABTEnum::ToRawValue(canvas.renderMode);
	videoCanvas.mirrorMode = UABTEnum::ToRawValue(canvas.mirrorMode);
	videoCanvas.uid = canvas.uid;
	//videoCanvas.priv = canvas.priv;
	videoCanvas.sourceType = UABTEnum::ToRawValue(canvas.sourceType);
	//videoCanvas.cropArea = canvas.cropArea;
	videoCanvas.setupMode = UABTEnum::ToRawValue(canvas.setupMode);
	agora::rtc::RtcConnection rtcConnection;
	std::string ChannelId = TCHAR_TO_UTF8(*connection.channelId);
	rtcConnection.channelId = ChannelId.c_str();
	//rtcConnection.localUid = connection.localUid;
	auto ret = AgoraUERtcEngine::Get()->setupRemoteVideoEx(videoCanvas, rtcConnection);
	return ret;
}


FString UAgoraBPuRtcEngine::GetVersion()
{
	auto ret = AgoraUERtcEngine::GetSDKVersion();
	return ret;
}

void UAgoraBPuRtcEngine::Release(bool sync /*= false*/)
{
	ClearAllEventHandlerCBExecutors();
	UninitInstance();
	RemoveFromRoot();

	AgoraUERtcEngine::Release(sync);
	Instance = nullptr;

}


FString UAgoraBPuRtcEngine::GetErrorDescription(int code)
{
	auto ret = AgoraUERtcEngine::Get()->getErrorDescription(code);
	return ret;
}

int UAgoraBPuRtcEngine::QueryCodecCapability(TArray<FUABT_CodecCapInfo>& codecInfo, int QuerySize /*= 10*/)
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
	auto ret = AgoraUERtcEngine::Get()->queryDeviceScore();
	return ret;
}

int UAgoraBPuRtcEngine::PreloadChannel(const FString& token, const FString& channelId, int64 uid)
{
	auto ret = AgoraUERtcEngine::Get()->preloadChannel(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), UABT::ToUID(uid));
	return ret;
}

int UAgoraBPuRtcEngine::PreloadChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount)
{
	auto ret = AgoraUERtcEngine::Get()->preloadChannelWithUserAccount(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), TCHAR_TO_UTF8(*userAccount));
	return ret;
}

int UAgoraBPuRtcEngine::UpdatePreloadChannelToken(const FString& token)
{
	auto ret = AgoraUERtcEngine::Get()->updatePreloadChannelToken(TCHAR_TO_UTF8(*token));
	return ret;
}

int UAgoraBPuRtcEngine::JoinChannel(const FString& token, const FString& channelId, int64 uid)
{
	auto ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), "", UABT::ToUID(uid));
	return ret;
}

int UAgoraBPuRtcEngine::JoinChannelWithOptions(const FString& token, const FString& channelId, int64 uid, const FUABT_ChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*token), TCHAR_TO_UTF8(*channelId), UABT::ToUID(uid), channelMediaOptions);

	options.FreeRawData(channelMediaOptions);

	return ret;
}

int UAgoraBPuRtcEngine::UpdateChannelMediaOptions(const FUABT_ChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->updateChannelMediaOptions(channelMediaOptions);

	options.FreeRawData(channelMediaOptions);

	return ret;
}

int UAgoraBPuRtcEngine::LeaveChannel()
{
	auto ret = AgoraUERtcEngine::Get()->leaveChannel();
	return ret;
}	

int UAgoraBPuRtcEngine::LeaveChannelWithOptions(const FUABT_LeaveChannelOptions& options)
{
	agora::rtc::LeaveChannelOptions leaveChannelOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->leaveChannel(leaveChannelOptions);

	options.FreeRawData(leaveChannelOptions);

	return ret;

}

int UAgoraBPuRtcEngine::RenewToken(const FString& token)
{
	auto ret = AgoraUERtcEngine::Get()->renewToken(TCHAR_TO_UTF8(*token));
	return ret;
}

int UAgoraBPuRtcEngine::SetChannelProfile(EUABT_CHANNEL_PROFILE_TYPE profile)
{
	auto ret = AgoraUERtcEngine::Get()->setChannelProfile(UABTEnum::ToRawValue(profile));
	return ret;
}

int UAgoraBPuRtcEngine::SetClientRole(EUABT_CLIENT_ROLE_TYPE clientroletype)
{
	agora::rtc::CLIENT_ROLE_TYPE roleType = UABTEnum::ToRawValue(clientroletype);
	auto ret = AgoraUERtcEngine::Get()->setClientRole(roleType);
	return ret;
}

int UAgoraBPuRtcEngine::SetClientRoleWithOptions(FUABT_ClientRoleOptions options, EUABT_CLIENT_ROLE_TYPE clientroletype)
{
	agora::rtc::ClientRoleOptions clientRoleOptions;
	clientRoleOptions.audienceLatencyLevel = UABTEnum::ToRawValue(options.audienceLatencyLevel);
	agora::rtc::CLIENT_ROLE_TYPE roleType = UABTEnum::ToRawValue(clientroletype);
	auto ret = AgoraUERtcEngine::Get()->setClientRole(roleType, clientRoleOptions);
	return ret;
}



int UAgoraBPuRtcEngine::StartEchoTest(const FUABT_EchoTestConfiguration& config)
{
	agora::rtc::EchoTestConfiguration echoTestConfiguration = config.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->startEchoTest(echoTestConfiguration);

	config.FreeRawData(echoTestConfiguration);

	return ret;
}

int UAgoraBPuRtcEngine::StopEchoTest()
{
	auto ret = AgoraUERtcEngine::Get()->stopEchoTest();
	return ret;
}



int UAgoraBPuRtcEngine::EnableMultiCamera(bool enabled, const FUABT_CameraCapturerConfiguration& config)
{
	int ret = AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);

#if defined(__APPLE__) && TARGET_OS_IOS
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateRawData();

	ret = AgoraUERtcEngine::Get()->enableMultiCamera(enabled, cameraCapturerConfiguration);

	config.FreeRawData(cameraCapturerConfiguration);

#endif

	return ret;
}


int UAgoraBPuRtcEngine::EnableVideo()
{
	auto ret = AgoraUERtcEngine::Get()->enableVideo();
	return ret;
}

int UAgoraBPuRtcEngine::DisableVideo()
{
	auto ret = AgoraUERtcEngine::Get()->disableVideo();
	return ret;
}


int UAgoraBPuRtcEngine::StartPreview()
{
	auto ret = AgoraUERtcEngine::Get()->startPreview();
	return ret;
}


int UAgoraBPuRtcEngine::StartPreviewWithOptions(EUABT_VIDEO_SOURCE_TYPE sourceType /*= EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY*/)
{
	auto ret = AgoraUERtcEngine::Get()->startPreview(UABTEnum::ToRawValue(sourceType));
	return ret;
}


int UAgoraBPuRtcEngine::StopPreview()
{
	auto ret = AgoraUERtcEngine::Get()->stopPreview();
	return ret;
}


int UAgoraBPuRtcEngine::StopPreviewWithOptions(EUABT_VIDEO_SOURCE_TYPE sourceType /*= EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY*/)
{
	auto ret = AgoraUERtcEngine::Get()->stopPreview(UABTEnum::ToRawValue(sourceType));
	return ret;
}



int UAgoraBPuRtcEngine::StartLastmileProbeTest(const FUABT_LastmileProbeConfig& config)
{
	agora::rtc::LastmileProbeConfig lastmileProbeConfig = config.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->startLastmileProbeTest(lastmileProbeConfig);

	config.FreeRawData(lastmileProbeConfig);

	return ret;
}

int UAgoraBPuRtcEngine::StopLastmileProbeTest()
{
	auto ret = AgoraUERtcEngine::Get()->stopLastmileProbeTest();
	return ret;
}

int UAgoraBPuRtcEngine::SetVideoEncoderConfiguration(const FUABT_VideoEncoderConfiguration& config)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setVideoEncoderConfiguration(videoEncoderConfiguration);

	config.FreeRawData(videoEncoderConfiguration);

	return ret;
}

int UAgoraBPuRtcEngine::SetBeautyEffectOptions(bool enabled, const FUABT_BeautyOptions& options, EUABT_MEDIA_SOURCE_TYPE type)
{
	agora::rtc::BeautyOptions beautyOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setBeautyEffectOptions(enabled, beautyOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(beautyOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetFaceShapeBeautyOptions(bool enabled, const FUABT_FaceShapeBeautyOptions& options, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::PRIMARY_CAMERA_SOURCE*/)
{
	agora::rtc::FaceShapeBeautyOptions faceShapeBeautyOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setFaceShapeBeautyOptions(enabled, faceShapeBeautyOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(faceShapeBeautyOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetFaceShapeAreaOptions(const FUABT_FaceShapeAreaOptions& options, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::PRIMARY_CAMERA_SOURCE*/)
{
	agora::rtc::FaceShapeAreaOptions faceShapeAreaOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setFaceShapeAreaOptions(faceShapeAreaOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(faceShapeAreaOptions);

	return ret;
}

int UAgoraBPuRtcEngine::GetFaceShapeBeautyOptions(FUABT_FaceShapeBeautyOptions& options, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::PRIMARY_CAMERA_SOURCE*/)
{
	agora::rtc::FaceShapeBeautyOptions Result;

	int ret = AgoraUERtcEngine::Get()->getFaceShapeBeautyOptions(Result, UABTEnum::ToRawValue(type));

	options = Result;

	return ret;
}

int UAgoraBPuRtcEngine::GetFaceShapeAreaOptions(EUABT_FACE_SHAPE_AREA shapeArea, FUABT_FaceShapeAreaOptions& options, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::PRIMARY_CAMERA_SOURCE*/)
{
	agora::rtc::FaceShapeAreaOptions Result;

	int ret = AgoraUERtcEngine::Get()->getFaceShapeAreaOptions(UABTEnum::ToRawValue(shapeArea), Result, UABTEnum::ToRawValue(type));

	options = Result;

	return ret;
}

int UAgoraBPuRtcEngine::SetFilterEffectOptions(bool enabled, const FUABT_FilterEffectOptions& options, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::PRIMARY_CAMERA_SOURCE*/)
{
	agora::rtc::FilterEffectOptions filterEffectOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setFilterEffectOptions(enabled, filterEffectOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(filterEffectOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetLowlightEnhanceOptions(bool enabled, const FUABT_LowlightEnhanceOptions& options, EUABT_MEDIA_SOURCE_TYPE type)
{
	agora::rtc::LowlightEnhanceOptions lowlightEnhanceOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setLowlightEnhanceOptions(enabled, lowlightEnhanceOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(lowlightEnhanceOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetVideoDenoiserOptions(bool enabled, const FUABT_VideoDenoiserOptions& options, EUABT_MEDIA_SOURCE_TYPE type)
{
	agora::rtc::VideoDenoiserOptions videoDenoiserOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setVideoDenoiserOptions(enabled, videoDenoiserOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(videoDenoiserOptions);

	return ret;
}

int UAgoraBPuRtcEngine::SetColorEnhanceOptions(bool enabled, const FUABT_ColorEnhanceOptions& options, EUABT_MEDIA_SOURCE_TYPE type)
{
	agora::rtc::ColorEnhanceOptions colorEnhanceOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setColorEnhanceOptions(enabled, colorEnhanceOptions, UABTEnum::ToRawValue(type));

	options.FreeRawData(colorEnhanceOptions);

	return ret;
}

int UAgoraBPuRtcEngine::EnableVirtualBackground(bool enabled, FUABT_VirtualBackgroundSource backgroundSource, FUABT_SegmentationProperty segproperty, EUABT_MEDIA_SOURCE_TYPE type)
{
	agora::rtc::VirtualBackgroundSource virtualBackgroundSource = backgroundSource.CreateRawData();
	agora::rtc::SegmentationProperty segmentationProperty = segproperty.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->enableVirtualBackground(enabled, virtualBackgroundSource, segmentationProperty, UABTEnum::ToRawValue(type));

	backgroundSource.FreeRawData(virtualBackgroundSource);
	segproperty.FreeRawData(segmentationProperty);

	return ret;
}


int UAgoraBPuRtcEngine::SetVideoScenario(EUABT_VIDEO_APPLICATION_SCENARIO_TYPE scenarioType)
{
	auto ret = AgoraUERtcEngine::Get()->setVideoScenario(UABTEnum::ToRawValue(scenarioType));
	return ret;
}

int UAgoraBPuRtcEngine::SetVideoQoEPreference(EUABT_VIDEO_QOE_PREFERENCE_TYPE qoePreference)
{
	auto ret = AgoraUERtcEngine::Get()->setVideoQoEPreference(UABTEnum::ToRawValue(qoePreference));
	return ret;
}

int UAgoraBPuRtcEngine::EnableAudio()
{
	auto ret = AgoraUERtcEngine::Get()->enableAudio();
	return ret;
}

int UAgoraBPuRtcEngine::DisableAudio()
{
	auto ret = AgoraUERtcEngine::Get()->disableAudio();
	return ret;
}



#pragma region RtcEngine2


int UAgoraBPuRtcEngine::SetAudioProfileAndScenario(EUABT_AUDIO_PROFILE_TYPE profile /*= EUABT_AUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT*/, EUABT_AUDIO_SCENARIO_TYPE scenario /*= EUABT_AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT*/)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioProfile(UABTEnum::ToRawValue(profile), UABTEnum::ToRawValue(scenario));
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioProfile(EUABT_AUDIO_PROFILE_TYPE profile /*= EUABT_AUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT*/)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioProfile(UABTEnum::ToRawValue(profile));
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioScenario(EUABT_AUDIO_SCENARIO_TYPE scenario /*= EUABT_AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT*/)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioScenario(UABTEnum::ToRawValue(scenario));
	return ret;
}

int UAgoraBPuRtcEngine::EnableLocalAudio(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableLocalAudio(enabled);
	return ret;
}

int UAgoraBPuRtcEngine::MuteLocalAudioStream(bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteLocalAudioStream(mute);
	return ret;
}

int UAgoraBPuRtcEngine::MuteAllRemoteAudioStreams(bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteAllRemoteAudioStreams(mute);
	return ret; 
}


int UAgoraBPuRtcEngine::MuteRemoteAudioStream(int64 uid, bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteRemoteAudioStream(UABT::ToUID(uid), mute);
	return ret;
}

int UAgoraBPuRtcEngine::MuteLocalVideoStream(bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteLocalVideoStream(mute);
	return ret;
}


int UAgoraBPuRtcEngine::EnableLocalVideo(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableLocalVideo(enabled);
	return ret;
}

int UAgoraBPuRtcEngine::MuteAllRemoteVideoStreams(bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteAllRemoteVideoStreams(mute);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteDefaultVideoStreamType(EUABT_VIDEO_STREAM_TYPE streamType)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteDefaultVideoStreamType(UABTEnum::ToRawValue(streamType));
	return ret;
}


int UAgoraBPuRtcEngine::MuteRemoteVideoStream(int64 uid, bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteRemoteVideoStream(UABT::ToUID(uid), mute);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteVideoStreamType(int64 uid, EUABT_VIDEO_STREAM_TYPE streamType)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteVideoStreamType(UABT::ToUID(uid), UABTEnum::ToRawValue(streamType));
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteVideoSubscriptionOptions(int64 uid, const FUABT_VideoSubscriptionOptions& options)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions = options.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setRemoteVideoSubscriptionOptions(UABT::ToUID(uid), videoSubscriptionOptions);

	options.FreeRawData(videoSubscriptionOptions);

	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeAudioBlocklist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioBlocklist(data, UEuidNumber);
	UABT::Free_UIDArrayPtr(data);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeAudioAllowlist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioAllowlist(data, UEuidNumber);
	UABT::Free_UIDArrayPtr(data);
	return ret;
}



int UAgoraBPuRtcEngine::SetSubscribeVideoBlocklist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoBlocklist(data, UEuidNumber);
	UABT::Free_UIDArrayPtr(data);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeVideoAllowlist(TArray<int64> uidList, int uidNumber)
{
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoAllowlist(data, UEuidNumber);
	UABT::Free_UIDArrayPtr(data);
	return ret;
}

int UAgoraBPuRtcEngine::EnableAudioVolumeIndication(int interval, int smooth, bool reportVad)
{
	auto ret = AgoraUERtcEngine::Get()->enableAudioVolumeIndication(interval, smooth, reportVad);
	return ret;
}

int UAgoraBPuRtcEngine::StartAudioRecording(const FUABT_AudioRecordingConfiguration& config)
{
	agora::rtc::AudioRecordingConfiguration audioRecordingConfiguration = config.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->startAudioRecording(audioRecordingConfiguration);

	config.FreeRawData(audioRecordingConfiguration);

	return ret;
}

int UAgoraBPuRtcEngine::StopAudioRecording()
{
	auto ret = AgoraUERtcEngine::Get()->stopAudioRecording();
	return ret;
}

int UAgoraBPuRtcEngine::StartAudioMixing(const FString& filePath, bool loopback, int cycle, int startPos /*= 0*/)
{
	auto ret = AgoraUERtcEngine::Get()->startAudioMixing(TCHAR_TO_UTF8(*filePath), loopback, cycle, startPos);
	return ret;
}

int UAgoraBPuRtcEngine::StopAudioMixing()
{
	auto ret = AgoraUERtcEngine::Get()->stopAudioMixing();
	return ret;
}

int UAgoraBPuRtcEngine::PauseAudioMixing()
{
	auto ret = AgoraUERtcEngine::Get()->pauseAudioMixing();
	return ret;
}

int UAgoraBPuRtcEngine::ResumeAudioMixing()
{
	auto ret = AgoraUERtcEngine::Get()->resumeAudioMixing();
	return ret;
}

int UAgoraBPuRtcEngine::SelectAudioTrack(int index)
{
	auto ret = AgoraUERtcEngine::Get()->selectAudioTrack(index);
	return ret;
}

int UAgoraBPuRtcEngine::GetAudioTrackCount()
{
	auto ret = AgoraUERtcEngine::Get()->getAudioTrackCount();
	return ret;
}

int UAgoraBPuRtcEngine::AdjustAudioMixingVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustAudioMixingVolume(volume);
	return ret;
}

int UAgoraBPuRtcEngine::AdjustAudioMixingPublishVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustAudioMixingPublishVolume(volume);
	return ret;
}

int UAgoraBPuRtcEngine::GetAudioMixingPublishVolume()
{
	auto ret = AgoraUERtcEngine::Get()->getAudioMixingPublishVolume();
	return ret;
}

int UAgoraBPuRtcEngine::AdjustAudioMixingPlayoutVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustAudioMixingPlayoutVolume(volume);
	return ret;
}

int UAgoraBPuRtcEngine::GetAudioMixingPlayoutVolume()
{
	auto ret = AgoraUERtcEngine::Get()->getAudioMixingPlayoutVolume();
	return ret;
}

int UAgoraBPuRtcEngine::GetAudioMixingDuration()
{
	auto ret = AgoraUERtcEngine::Get()->getAudioMixingDuration();
	return ret;
}

int UAgoraBPuRtcEngine::GetAudioMixingCurrentPosition()
{
	auto ret = AgoraUERtcEngine::Get()->getAudioMixingCurrentPosition();
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioMixingPosition(int pos)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioMixingPosition(pos);
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioMixingDualMonoMode(EUABT_AUDIO_MIXING_DUAL_MONO_MODE mode)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioMixingDualMonoMode(UABTEnum::ToRawValue(mode));
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioMixingPitch(int pitch)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioMixingPitch(pitch);
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioMixingPlaybackSpeed(int speed)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioMixingPlaybackSpeed(speed);
	return ret;
}

int UAgoraBPuRtcEngine::GetEffectsVolume()
{
	auto ret = AgoraUERtcEngine::Get()->getEffectsVolume();
	return ret;
}

int UAgoraBPuRtcEngine::SetEffectsVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->setEffectsVolume(volume);
	return ret;
}

int UAgoraBPuRtcEngine::PreloadEffect(int soundId, const FString& filePath, int startPos)
{
	auto ret = AgoraUERtcEngine::Get()->preloadEffect(soundId, TCHAR_TO_UTF8(*filePath), startPos);
	return ret;
}

int UAgoraBPuRtcEngine::PlayEffect(int soundId, const FString& filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos)
{
	auto ret = AgoraUERtcEngine::Get()->playEffect(soundId, TCHAR_TO_UTF8(*filePath), loopCount, pitch, pan, gain, publish, startPos);
	return ret;
}

int UAgoraBPuRtcEngine::PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish)
{
	auto ret = AgoraUERtcEngine::Get()->playAllEffects(loopCount, pitch, pan, gain, publish);
	return ret;
}

int UAgoraBPuRtcEngine::GetVolumeOfEffect(int soundId)
{
	auto ret = AgoraUERtcEngine::Get()->getVolumeOfEffect(soundId);
	return ret;
}

int UAgoraBPuRtcEngine::SetVolumeOfEffect(int soundId, int volume)
{
	auto ret = AgoraUERtcEngine::Get()->setVolumeOfEffect(soundId, volume);
	return ret;
}

int UAgoraBPuRtcEngine::PauseEffect(int soundId)
{
	auto ret = AgoraUERtcEngine::Get()->pauseEffect(soundId);
	return ret;
}

int UAgoraBPuRtcEngine::PauseAllEffects()
{
	auto ret = AgoraUERtcEngine::Get()->pauseAllEffects();
	return ret;
}

int UAgoraBPuRtcEngine::ResumeEffect(int soundId)
{
	auto ret = AgoraUERtcEngine::Get()->resumeEffect(soundId);
	return ret;
}

int UAgoraBPuRtcEngine::ResumeAllEffects()
{
	auto ret = AgoraUERtcEngine::Get()->resumeAllEffects();
	return ret;
}

int UAgoraBPuRtcEngine::StopEffect(int soundId)
{
	auto ret = AgoraUERtcEngine::Get()->stopEffect(soundId);
	return ret;
}

int UAgoraBPuRtcEngine::StopAllEffects()
{
	auto ret = AgoraUERtcEngine::Get()->stopAllEffects();
	return ret;
}

int UAgoraBPuRtcEngine::UnloadEffect(int soundId)
{
	auto ret = AgoraUERtcEngine::Get()->unloadEffect(soundId);
	return ret;
}

int UAgoraBPuRtcEngine::UnloadAllEffects()
{
	auto ret = AgoraUERtcEngine::Get()->unloadAllEffects();
	return ret;
}

int UAgoraBPuRtcEngine::GetEffectDuration(const FString& filePath)
{
	auto ret = AgoraUERtcEngine::Get()->getEffectDuration(TCHAR_TO_UTF8(*filePath));
	return ret;
}

int UAgoraBPuRtcEngine::SetEffectPosition(int soundId, int pos)
{
	auto ret = AgoraUERtcEngine::Get()->setEffectPosition(soundId, pos);
	return ret;
}

int UAgoraBPuRtcEngine::GetEffectCurrentPosition(int soundId)
{
	auto ret = AgoraUERtcEngine::Get()->getEffectCurrentPosition(soundId);
	return ret;
}

int UAgoraBPuRtcEngine::EnableSoundPositionIndication(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableSoundPositionIndication(enabled);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteVoicePosition(int64 uid, float pan, float gain)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteVoicePosition(UABT::ToUID(uid), pan, gain);
	return ret;
}

int UAgoraBPuRtcEngine::EnableSpatialAudio(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableSpatialAudio(enabled);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteUserSpatialAudioParams(int64 uid, const FUABT_SpatialAudioParams& params)
{
	agora::SpatialAudioParams spatialAudioParams = params.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setRemoteUserSpatialAudioParams(UABT::ToUID(uid), spatialAudioParams);

	params.FreeRawData(spatialAudioParams);

	return ret;
}

int UAgoraBPuRtcEngine::SetVoiceBeautifierPreset(EUABT_VOICE_BEAUTIFIER_PRESET preset)
{
	auto ret = AgoraUERtcEngine::Get()->setVoiceBeautifierPreset(UABTEnum::ToRawValue(preset));
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioEffectPreset(EUABT_AUDIO_EFFECT_PRESET preset)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioEffectPreset(UABTEnum::ToRawValue(preset));
	return ret;
}

int UAgoraBPuRtcEngine::SetVoiceConversionPreset(EUABT_VOICE_CONVERSION_PRESET preset)
{
	auto ret = AgoraUERtcEngine::Get()->setVoiceConversionPreset(UABTEnum::ToRawValue(preset));
	return ret;
}

int UAgoraBPuRtcEngine::SetAudioEffectParameters(EUABT_AUDIO_EFFECT_PRESET preset, int param1, int param2)
{
	auto ret = AgoraUERtcEngine::Get()->setAudioEffectParameters(UABTEnum::ToRawValue(preset), param1, param2);
	return ret;
}

int UAgoraBPuRtcEngine::SetVoiceBeautifierParameters(EUABT_VOICE_BEAUTIFIER_PRESET preset, int param1, int param2)
{
	auto ret = AgoraUERtcEngine::Get()->setVoiceBeautifierParameters(UABTEnum::ToRawValue(preset), param1, param2);
	return ret;
}

int UAgoraBPuRtcEngine::SetVoiceConversionParameters(EUABT_VOICE_CONVERSION_PRESET preset, int param1, int param2)
{
	auto ret = AgoraUERtcEngine::Get()->setVoiceConversionParameters(UABTEnum::ToRawValue(preset), param1, param2);
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalVoicePitch(float pitch)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalVoicePitch(pitch);
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalVoiceFormant(const FString& formantRatio /*= "0.0"*/)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalVoiceFormant(UABT::ToDouble(formantRatio));
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalVoiceEqualization(EUABT_AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalVoiceEqualization(UABTEnum::ToRawValue(bandFrequency), bandGain);
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalVoiceReverb(EUABT_AUDIO_REVERB_TYPE reverbKey, int value)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalVoiceReverb(UABTEnum::ToRawValue(reverbKey), value);
	return ret;
}

int UAgoraBPuRtcEngine::SetHeadphoneEQPreset(EUABT_HEADPHONE_EQUALIZER_PRESET preset)
{
	//auto ret = AgoraUERtcEngine::Get()->setHeadphoneEQPreset(UABTEnum::ToRawValue(preset));
	auto ret = AgoraUERtcEngine::Get()->setHeadphoneEQPreset(UABTEnum::ToRawValue(preset));
	return ret;
}


int UAgoraBPuRtcEngine::SetHeadphoneEQParameters(int lowGain, int highGain)
{
	auto ret = AgoraUERtcEngine::Get()->setHeadphoneEQParameters(lowGain, highGain);
	return ret;
}


int UAgoraBPuRtcEngine::EnableVoiceAITuner(bool enabled, EUABT_VOICE_AI_TUNER_TYPE type)
{
	auto ret = AgoraUERtcEngine::Get()->enableVoiceAITuner(enabled, UABTEnum::ToRawValue(type));
	return ret;
}

int UAgoraBPuRtcEngine::SetLogFile(const FString& filePath)
{
	auto ret = AgoraUERtcEngine::Get()->setLogFile(TCHAR_TO_UTF8(*filePath));
	return ret;
}

int UAgoraBPuRtcEngine::SetLogFilter(int filter)
{
	auto ret = AgoraUERtcEngine::Get()->setLogFilter(filter);
	return ret;
}

int UAgoraBPuRtcEngine::SetLogLevel(EUABT_LOG_LEVEL level)
{
	auto ret = AgoraUERtcEngine::Get()->setLogLevel(UABTEnum::ToRawValue(level));
	return ret;
}

int UAgoraBPuRtcEngine::SetLogFileSize(int fileSizeInKBytes)
{
	auto ret = AgoraUERtcEngine::Get()->setLogFileSize(fileSizeInKBytes);
	return ret;
}

int UAgoraBPuRtcEngine::UploadLogFile(FString& requestId)
{
	agora::util::AString _requestId;
	auto ret = AgoraUERtcEngine::Get()->uploadLogFile(_requestId);
	requestId = UTF8_TO_TCHAR(_requestId->c_str());
	return ret;
}

int UAgoraBPuRtcEngine::WriteLog(EUABT_LOG_LEVEL level, const FString& Content)
{
	auto ret = AgoraUERtcEngine::Get()->writeLog(UABTEnum::ToRawValue(level), TCHAR_TO_UTF8(*Content));
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalRenderMode(EUABT_RENDER_MODE_TYPE renderMode, EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode /*= EUABT_VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO*/)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalRenderMode(UABTEnum::ToRawValue(renderMode), UABTEnum::ToRawValue(mirrorMode));
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteRenderMode(int64 uid, EUABT_RENDER_MODE_TYPE renderMode, EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteRenderMode(UABT::ToUID(uid), UABTEnum::ToRawValue(renderMode), UABTEnum::ToRawValue(mirrorMode));
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalRenderTargetFps(EUABT_VIDEO_SOURCE_TYPE sourceType, int targetFps)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalRenderTargetFps(UABTEnum::ToRawValue(sourceType), targetFps);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteRenderTargetFps(int targetFps)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteRenderTargetFps(targetFps);
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalVideoMirrorMode(EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalVideoMirrorMode(UABTEnum::ToRawValue(mirrorMode));
	return ret;
}

int UAgoraBPuRtcEngine::EnableDualStreamMode(bool enabled, const FUABT_SimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->enableDualStreamMode(enabled, simulcastStreamConfig);

	streamConfig.FreeRawData(simulcastStreamConfig);

	return ret;
}


int UAgoraBPuRtcEngine::SetSimulcastConfig(const FUABT_SimulcastConfig& simulcastConfig)
{
	agora::rtc::SimulcastConfig config = simulcastConfig.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setSimulcastConfig(config);

	simulcastConfig.FreeRawData(config);

	return ret;
}


int UAgoraBPuRtcEngine::SetDualStreamMode(EUABT_SIMULCAST_STREAM_MODE mode, const FUABT_SimulcastStreamConfig& streamConfig)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setDualStreamMode(UABTEnum::ToRawValue(mode), simulcastStreamConfig);

	streamConfig.FreeRawData(simulcastStreamConfig);

	return ret;
}


int UAgoraBPuRtcEngine::EnableCustomAudioLocalPlayback(int64 trackId, bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableCustomAudioLocalPlayback(UABT::ToUID(trackId), enabled);
	return ret;
}

int UAgoraBPuRtcEngine::SetRecordingAudioFrameParameters(int sampleRate, int channel, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = AgoraUERtcEngine::Get()->setRecordingAudioFrameParameters(sampleRate, channel, UABTEnum::ToRawValue(mode), samplesPerCall);
	return ret;
}

int UAgoraBPuRtcEngine::SetPlaybackAudioFrameParameters(int sampleRate, int channel, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = AgoraUERtcEngine::Get()->setPlaybackAudioFrameParameters(sampleRate, channel, UABTEnum::ToRawValue(mode), samplesPerCall);
	return ret;
}

int UAgoraBPuRtcEngine::SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall)
{
	auto ret = AgoraUERtcEngine::Get()->setMixedAudioFrameParameters(sampleRate, channel, samplesPerCall);
	return ret;
}

int UAgoraBPuRtcEngine::SetEarMonitoringAudioFrameParameters(int sampleRate, int channel, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	auto ret = AgoraUERtcEngine::Get()->setEarMonitoringAudioFrameParameters(sampleRate, channel, UABTEnum::ToRawValue(mode), samplesPerCall);
	return ret;
}


int UAgoraBPuRtcEngine::SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel)
{
	auto ret = AgoraUERtcEngine::Get()->setPlaybackAudioFrameBeforeMixingParameters(sampleRate, channel);
	return ret;
}

int UAgoraBPuRtcEngine::EnableAudioSpectrumMonitor(int intervalInMS)
{
	auto ret = AgoraUERtcEngine::Get()->enableAudioSpectrumMonitor(intervalInMS);
	return ret;
}

int UAgoraBPuRtcEngine::DisableAudioSpectrumMonitor()
{
	auto ret = AgoraUERtcEngine::Get()->disableAudioSpectrumMonitor();
	return ret;
}

int UAgoraBPuRtcEngine::AdjustRecordingSignalVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustRecordingSignalVolume(volume);
	return ret;
}

int UAgoraBPuRtcEngine::MuteRecordingSignal(bool mute)
{
	auto ret = AgoraUERtcEngine::Get()->muteRecordingSignal(mute);
	return ret;
}

int UAgoraBPuRtcEngine::AdjustPlaybackSignalVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustPlaybackSignalVolume(volume);
	return ret;
}	

int UAgoraBPuRtcEngine::AdjustUserPlaybackSignalVolume(int64 uid, int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustUserPlaybackSignalVolume(UABT::ToUID(uid), volume);
	return ret;
}

int UAgoraBPuRtcEngine::SetLocalPublishFallbackOption(EUABT_STREAM_FALLBACK_OPTIONS option)
{
	auto ret = AgoraUERtcEngine::Get()->setLocalPublishFallbackOption(UABTEnum::ToRawValue(option));
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteSubscribeFallbackOption(EUABT_STREAM_FALLBACK_OPTIONS option)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteSubscribeFallbackOption(UABTEnum::ToRawValue(option));
	return ret;
}

int UAgoraBPuRtcEngine::SetHighPriorityUserList(const TArray<int64>& uidList, EUABT_STREAM_FALLBACK_OPTIONS option)
{
	int vNum = uidList.Num();
	agora::rtc::uid_t* uidListVec = new agora::rtc::uid_t[vNum];
	for (int i = 0; i < vNum; i++) {
		uidListVec[i] = UABT::ToUID(uidList[i]);
	}

	int ret =  AgoraUERtcEngine::Get()->setHighPriorityUserList(uidListVec, vNum, UABTEnum::ToRawValue(option));

	delete[] uidListVec;

	return ret;
}

int UAgoraBPuRtcEngine::EnableLoopbackRecording(bool enabled, const FString& deviceName)
{
	auto ret = AgoraUERtcEngine::Get()->enableLoopbackRecording(enabled, TCHAR_TO_UTF8(*deviceName));
	return ret;
}

int UAgoraBPuRtcEngine::AdjustLoopbackSignalVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->adjustLoopbackSignalVolume(volume);
	return ret;
}

int UAgoraBPuRtcEngine::GetLoopbackRecordingVolume()
{
	auto ret = AgoraUERtcEngine::Get()->getLoopbackRecordingVolume();
	return ret;
}

int UAgoraBPuRtcEngine::EnableInEarMonitoring(bool enabled, int includeAudioFilters)
{
	auto ret = AgoraUERtcEngine::Get()->enableInEarMonitoring(enabled, includeAudioFilters);
	return ret;
}

int UAgoraBPuRtcEngine::SetInEarMonitoringVolume(int volume)
{
	auto ret = AgoraUERtcEngine::Get()->setInEarMonitoringVolume(volume);
	return ret;
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



int UAgoraBPuRtcEngine::RegisterExtension(const FString& provider, const FString& extension, EUABT_MEDIA_SOURCE_TYPE type)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	auto ret = AgoraUERtcEngine::Get()->registerExtension(Provider.c_str(), Extension.c_str(), UABTEnum::ToRawValue(type));
	return ret;
}



int UAgoraBPuRtcEngine::EnableExtension(const FString& provider, const FString& extension, bool enable /*= true*/, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE*/)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	auto ret = AgoraUERtcEngine::Get()->enableExtension(Provider.c_str(), Extension.c_str(), enable, UABTEnum::ToRawValue(type));
	return ret;
}

int UAgoraBPuRtcEngine::SetExtensionProperty(const FString& provider, const FString& extension, const FString& key, const FString& value, EUABT_MEDIA_SOURCE_TYPE type /*= EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE*/)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	std::string Key = TCHAR_TO_UTF8(*key);
	std::string Value = TCHAR_TO_UTF8(*value);
	auto ret = AgoraUERtcEngine::Get()->setExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), Value.c_str(), UABTEnum::ToRawValue(type));
	return ret;
}

int UAgoraBPuRtcEngine::GetExtensionProperty(const FString& provider, const FString& extension, const FString& key, FString& value, EUABT_MEDIA_SOURCE_TYPE type /* = EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE */)
{
	std::string Provider = TCHAR_TO_UTF8(*provider);
	std::string Extension = TCHAR_TO_UTF8(*extension);
	std::string Key = TCHAR_TO_UTF8(*key);
	
	char* result = nullptr;
	int result_size = 0;

	auto ret = AgoraUERtcEngine::Get()->getExtensionProperty(Provider.c_str(), Extension.c_str(), Key.c_str(), result, result_size, UABTEnum::ToRawValue(type));
	
	value = UTF8_TO_TCHAR(result);

	return ret;
}

int UAgoraBPuRtcEngine::SetCameraCapturerConfiguration(const FUABT_CameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateRawData();

	int ret = AgoraUERtcEngine::Get()->setCameraCapturerConfiguration(cameraCapturerConfiguration);

	config.FreeRawData(cameraCapturerConfiguration);

	return ret;
}

int64 UAgoraBPuRtcEngine::CreateCustomVideoTrack()
{
	auto ret = AgoraUERtcEngine::Get()->createCustomVideoTrack();
	return ret;
}

int64 UAgoraBPuRtcEngine::CreateCustomEncodedVideoTrack(const FUABT_SenderOptions& sender_option)
{
	agora::rtc::SenderOptions senderOptions = sender_option.CreateRawData();

	int64 ret = AgoraUERtcEngine::Get()->createCustomEncodedVideoTrack(senderOptions);

	sender_option.FreeRawData(senderOptions);

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

int UAgoraBPuRtcEngine::SetCameraStabilizationMode(EUABT_CAMERA_STABILIZATION_MODE mode)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)
	auto ret =  AgoraUERtcEngine::Get()->setCameraStabilizationMode(UABTEnum::ToRawValue(mode));
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


UIScreenCaptureSourceList* UAgoraBPuRtcEngine::GetScreenCaptureSources(const FUABT_SIZE& thumbSize, const FUABT_SIZE& iconSize, bool includeScreen)
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


int UAgoraBPuRtcEngine::SetAudioSessionOperationRestriction(EUABT_AUDIO_SESSION_OPERATION_RESTRICTION restriction)
{
#if (defined(__APPLE__) && TARGET_OS_IOS)
	return AgoraUERtcEngine::Get()->setAudioSessionOperationRestriction(UABTEnum::ToRawValue(restriction));
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::StartScreenCaptureByDisplayId(int64 displayId, const FUABT_Rectangle& regionRect, const FUABT_ScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle region = regionRect.CreateRawData();

	agora::rtc::ScreenCaptureParameters params = captureParams.CreateRawData();

	auto ret = AgoraUERtcEngine::Get()->startScreenCaptureByDisplayId(displayId, region, params);

	regionRect.FreeRawData(region);
	captureParams.FreeRawData(params);

	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::StartScreenCaptureByScreenRect(const FUABT_Rectangle& screenRect, const FUABT_Rectangle& regionRect, const FUABT_ScreenCaptureParameters& captureParams) __deprecated
{
#if defined(_WIN32)
	agora::rtc::Rectangle AgoraScreenRect = screenRect.CreateRawData();
	agora::rtc::Rectangle AgoraRegionRect = regionRect.CreateRawData();
	agora::rtc::ScreenCaptureParameters AgoraScreenCaptureParameters = captureParams.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCaptureByScreenRect(AgoraScreenRect, AgoraRegionRect, AgoraScreenCaptureParameters);
	screenRect.FreeRawData(AgoraScreenRect);
	regionRect.FreeRawData(AgoraRegionRect);
	captureParams.FreeRawData(AgoraScreenCaptureParameters);

	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::GetAudioDeviceInfo(FUABT_DeviceInfo& deviceInfo)
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

int UAgoraBPuRtcEngine::StartScreenCaptureByWindowId(int64 windowId, const FUABT_Rectangle& regionRect, const FUABT_ScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle = regionRect.CreateRawData();
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCaptureByWindowId(windowId, rectangle, screenCaptureParameters);
	regionRect.FreeRawData(rectangle);
	captureParams.FreeRawData(screenCaptureParameters);

	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::SetScreenCaptureContentHint(EUABT_VIDEO_CONTENT_HINT contentHint)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	auto ret = AgoraUERtcEngine::Get()->setScreenCaptureContentHint(UABTEnum::ToRawValue(contentHint));
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::UpdateScreenCaptureRegion(const FUABT_Rectangle& regionRect)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::Rectangle rectangle = regionRect.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->updateScreenCaptureRegion(rectangle);
	regionRect.FreeRawData(rectangle);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}
int UAgoraBPuRtcEngine::UpdateScreenCaptureParameters(const FUABT_ScreenCaptureParameters& captureParams)
{
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::ScreenCaptureParameters screenCaptureParameters = captureParams.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->updateScreenCaptureParameters(screenCaptureParameters);
	captureParams.FreeRawData(screenCaptureParameters);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}


int UAgoraBPuRtcEngine::StartScreenCapture(const FUABT_ScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2 = captureParams.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCapture(screenCaptureParameters2);
	captureParams.FreeRawData(screenCaptureParameters2);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif

}



int UAgoraBPuRtcEngine::UpdateScreenCapture(const FUABT_ScreenCaptureParameters2& captureParams)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS) 
	agora::rtc::ScreenCaptureParameters2 screenCaptureParameters2 = captureParams.CreateRawData();
	int ret = AgoraUERtcEngine::Get()->updateScreenCapture(screenCaptureParameters2);
	captureParams.FreeRawData(screenCaptureParameters2);
	return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
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

int UAgoraBPuRtcEngine::QueryCameraFocalLengthCapability(const TArray<FUABT_FocalLengthInfo>& focalLengthInfos)
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)

	int TotalSize = focalLengthInfos.Num();
	agora::rtc::FocalLengthInfo* focalLengthInfo = UABT::New_RawDataArray<agora::rtc::FocalLengthInfo, FUABT_FocalLengthInfo>(focalLengthInfos);
	auto ret = AgoraUERtcEngine::Get()->queryCameraFocalLengthCapability(focalLengthInfo, TotalSize);
	UABT::Free_RawDataArray<agora::rtc::FocalLengthInfo, FUABT_FocalLengthInfo>(focalLengthInfo, TotalSize);
		return ret;
#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif
}

int UAgoraBPuRtcEngine::SetScreenCaptureScenario(EUABT_SCREEN_SCENARIO_TYPE screenScenario)
{
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)
	auto ret = AgoraUERtcEngine::Get()->setScreenCaptureScenario(UABTEnum::ToRawValue(screenScenario));
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
int UAgoraBPuRtcEngine::StartRtmpStreamWithTranscoding(const FString& url, const FUABT_LiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateRawData();
	std::string TempUrl = TCHAR_TO_UTF8(*url);
	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithTranscoding(TempUrl.c_str(), liveTranscoding);
	transcoding.FreeRawData(liveTranscoding);
	return ret;
}
int UAgoraBPuRtcEngine::UpdateRtmpTranscoding(const FUABT_LiveTranscoding& transcoding)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->updateRtmpTranscoding(liveTranscoding);
	transcoding.FreeRawData(liveTranscoding);

	return ret;
}

int UAgoraBPuRtcEngine::StartLocalVideoTranscoder(const FUABT_LocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration AgoraLocalTranscoderConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startLocalVideoTranscoder(AgoraLocalTranscoderConfiguration);
	config.FreeRawData(AgoraLocalTranscoderConfiguration);
	return ret;
}
int UAgoraBPuRtcEngine::UpdateLocalTranscoderConfiguration(const FUABT_LocalTranscoderConfiguration& config)
{
	agora::rtc::LocalTranscoderConfiguration AgoraLocalTranscoderConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->updateLocalTranscoderConfiguration(AgoraLocalTranscoderConfiguration);
	config.FreeRawData(AgoraLocalTranscoderConfiguration);
	return ret;
}

int UAgoraBPuRtcEngine::StopRtmpStream(const FString& url)
{
	auto ret = AgoraUERtcEngine::Get()->stopRtmpStream(TCHAR_TO_UTF8(*url));
	return ret;
}


int UAgoraBPuRtcEngine::StopLocalVideoTranscoder()
{
	auto ret = AgoraUERtcEngine::Get()->stopLocalVideoTranscoder();
	return ret;
}


int UAgoraBPuRtcEngine::StartLocalAudioMixer(const FUABT_LocalAudioMixerConfiguration& config)
{
	agora::rtc::LocalAudioMixerConfiguration localAudioMixerConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startLocalAudioMixer(localAudioMixerConfiguration);
	config.FreeRawData(localAudioMixerConfiguration);
	return ret;
}

int UAgoraBPuRtcEngine::UpdateLocalAudioMixerConfiguration(const FUABT_LocalAudioMixerConfiguration& config)
{
	agora::rtc::LocalAudioMixerConfiguration localAudioMixerConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->updateLocalAudioMixerConfiguration(localAudioMixerConfiguration);
	config.FreeRawData(localAudioMixerConfiguration);
	return ret;
}

int UAgoraBPuRtcEngine::StopLocalAudioMixer()
{
	auto ret = AgoraUERtcEngine::Get()->stopLocalAudioMixer();
	return ret;
}

int UAgoraBPuRtcEngine::StartCameraCapture(EUABT_VIDEO_SOURCE_TYPE sourceType, const FUABT_CameraCapturerConfiguration& config)
{
	agora::rtc::CameraCapturerConfiguration cameraCapturerConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startCameraCapture(UABTEnum::ToRawValue(sourceType), cameraCapturerConfiguration);

	config.FreeRawData(cameraCapturerConfiguration);
	return ret;
}


int UAgoraBPuRtcEngine::StopCameraCapture(EUABT_VIDEO_SOURCE_TYPE sourceType)
{
	auto ret = AgoraUERtcEngine::Get()->stopCameraCapture(UABTEnum::ToRawValue(sourceType));
	return ret;
}


int UAgoraBPuRtcEngine::SetCameraDeviceOrientation(EUABT_VIDEO_SOURCE_TYPE type, EUABT_VIDEO_ORIENTATION orientation)
{
	auto ret = AgoraUERtcEngine::Get()->setCameraDeviceOrientation(UABTEnum::ToRawValue(type), UABTEnum::ToRawValue(orientation));
	return ret;
}
int UAgoraBPuRtcEngine::SetScreenCaptureOrientation(EUABT_VIDEO_SOURCE_TYPE type, EUABT_VIDEO_ORIENTATION orientation)
{
	auto ret = AgoraUERtcEngine::Get()->setScreenCaptureOrientation(UABTEnum::ToRawValue(type), UABTEnum::ToRawValue(orientation));
	return ret;
}


int UAgoraBPuRtcEngine::StartScreenCaptureBySourceType(EUABT_VIDEO_SOURCE_TYPE sourceType, const FUABT_ScreenCaptureConfiguration& config)
{

	agora::rtc::ScreenCaptureConfiguration screenCaptureConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startScreenCapture(UABTEnum::ToRawValue(sourceType), screenCaptureConfiguration);
	config.FreeRawData(screenCaptureConfiguration);
	return ret;
}

int UAgoraBPuRtcEngine::StopScreenCaptureBySourceType(EUABT_VIDEO_SOURCE_TYPE sourceType)
{
	auto ret = AgoraUERtcEngine::Get()->stopScreenCapture(UABTEnum::ToRawValue(sourceType));
	return ret;
}



EUABT_CONNECTION_STATE_TYPE UAgoraBPuRtcEngine::GetConnectionState()
{
	auto Result = AgoraUERtcEngine::Get()->getConnectionState();
	return UABTEnum::WrapWithUE(Result);
}


int UAgoraBPuRtcEngine::SetRemoteUserPriority(int64 uid, EUABT_PRIORITY_TYPE userPriority)
{
	auto ret = AgoraUERtcEngine::Get()->setRemoteUserPriority(uid, UABTEnum::ToRawValue(userPriority));
	return ret;
}

int UAgoraBPuRtcEngine::EnableEncryption(bool enabled, const FUABT_EncryptionConfig& config)
{
	agora::rtc::EncryptionConfig AgoraEncryptionConfig = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableEncryption(enabled, AgoraEncryptionConfig);
	config.FreeRawData(AgoraEncryptionConfig);
	return ret;
}
int UAgoraBPuRtcEngine::CreateDataStream(int& streamId, const FUABT_DataStreamConfig& config)
{
	agora::rtc::DataStreamConfig dataStreamConfig = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->createDataStream(&streamId, dataStreamConfig);
	config.FreeRawData(dataStreamConfig);
	return ret;
}
int UAgoraBPuRtcEngine::SendStreamMessage(int streamId, const FString& data)
{
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	const char* Data = StdStrData.c_str();

	auto ret = AgoraUERtcEngine::Get()->sendStreamMessage(streamId, Data, strlen(Data) + 1);
	return ret;
}
int UAgoraBPuRtcEngine::AddVideoWatermark(const FString& watermarkUrl, const FUABT_WatermarkOptions& options)
{
	std::string STDWatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	agora::rtc::WatermarkOptions watermarkOptions = options.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->addVideoWatermark(STDWatermarkUrl.c_str(), watermarkOptions);
	options.FreeRawData(watermarkOptions);
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

int UAgoraBPuRtcEngine::SetAINSMode(bool enabled, EUABT_AUDIO_AINS_MODE mode)
{
	auto ret = AgoraUERtcEngine::Get()->setAINSMode(enabled, UABTEnum::ToRawValue(mode));
	return ret;
}

int UAgoraBPuRtcEngine::RegisterLocalUserAccount(const FString& appId, const FString& userAccount)
{
	std::string AppId = TCHAR_TO_UTF8(*appId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->registerLocalUserAccount(AppId.c_str(), UserAccount.c_str());
	return ret;
}

int UAgoraBPuRtcEngine::JoinChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount, const FUABT_ChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateRawData();
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->joinChannelWithUserAccount(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions);
	options.FreeRawData(channelMediaOptions);
	return ret;
}

int UAgoraBPuRtcEngine::JoinChannelWithUserAccountEx(const FString& token, const FString& channelId, const FString& userAccount, const FUABT_ChannelMediaOptions& options)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateRawData();
	std::string Token = TCHAR_TO_UTF8(*token);
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->joinChannelWithUserAccountEx(Token.c_str(), ChannelId.c_str(), UserAccount.c_str(), channelMediaOptions, nullptr);
	options.FreeRawData(channelMediaOptions);
	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUserAccount(const FString& userAccount,FUABT_UserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUserAccount(UserAccount.c_str(), &info);
	userInfo = info;
	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUid(int64 uid, FUABT_UserInfo& userInfo)
{
	agora::rtc::UserInfo info;
	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUid(uid, &info);
	userInfo = info;
	return ret;
}


int UAgoraBPuRtcEngine::StartOrUpdateChannelMediaRelay(const FUABT_ChannelMediaRelayConfiguration& configuration)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration = configuration.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startOrUpdateChannelMediaRelay(channelMediaRelayConfiguration);
	configuration.FreeRawData(channelMediaRelayConfiguration);
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
//int UAgoraBPuRtcEngine::SetDirectCdnStreamingAudioConfiguration(EUABT_AUDIO_PROFILE_TYPE profile)
//{
//	auto ret = AgoraUERtcEngine::Get()->setDirectCdnStreamingAudioConfiguration(UABTEnum::ToRawValue(profile));
//	return ret;
//}
//int UAgoraBPuRtcEngine::SetDirectCdnStreamingVideoConfiguration(const FUABT_VideoEncoderConfiguration& config)
//{
//	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateRawData();
//	auto ret = AgoraUERtcEngine::Get()->setDirectCdnStreamingVideoConfiguration(videoEncoderConfiguration);
//	config.FreeRawData(videoEncoderConfiguration);
//	return ret;
//}

int UAgoraBPuRtcEngine::StartRhythmPlayer(const FString& sound1, const FString& sound2, const FUABT_AgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig = config.CreateRawData();
	std::string Sound1 = TCHAR_TO_UTF8(*sound1);
	std::string Sound2 = TCHAR_TO_UTF8(*sound2);
	auto ret = AgoraUERtcEngine::Get()->startRhythmPlayer(Sound1.c_str(), Sound1.c_str(), agoraRhythmPlayerConfig);
	config.FreeRawData(agoraRhythmPlayerConfig);
	return ret;
}
int UAgoraBPuRtcEngine::StopRhythmPlayer()
{
	auto ret = AgoraUERtcEngine::Get()->stopRhythmPlayer();
	return ret;
}
int UAgoraBPuRtcEngine::ConfigRhythmPlayer(const FUABT_AgoraRhythmPlayerConfig& config)
{
	agora::rtc::AgoraRhythmPlayerConfig agoraRhythmPlayerConfig = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->configRhythmPlayer(agoraRhythmPlayerConfig);
	config.FreeRawData(agoraRhythmPlayerConfig);
	return ret;
}


int UAgoraBPuRtcEngine::TakeSnapshot(int64 uid, const FString& filePath)
{
	auto ret = AgoraUERtcEngine::Get()->takeSnapshot(UABT::ToUID(uid), TCHAR_TO_UTF8(*filePath));
	return ret;
}

int UAgoraBPuRtcEngine::TakeSnapshotWithConfig(int64 uid, const FUABT_SnapshotConfig& config)
{
	agora::media::SnapshotConfig snapshotConfig = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->takeSnapshot(UABT::ToUID(uid), snapshotConfig);
	config.FreeRawData(snapshotConfig);
	return ret;
}

int UAgoraBPuRtcEngine::EnableContentInspect(bool enabled, const FUABT_ContentInspectConfig& config)
{
	agora::media::ContentInspectConfig contentInspectConfig = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableContentInspect(enabled, contentInspectConfig);
	config.FreeRawData(contentInspectConfig);
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

int UAgoraBPuRtcEngine::SetCloudProxy(EUABT_CLOUD_PROXY_TYPE proxyType)
{
	auto ret = AgoraUERtcEngine::Get()->setCloudProxy(UABTEnum::ToRawValue(proxyType));
	return ret;
}
int UAgoraBPuRtcEngine::SetLocalAccessPoint(const FUABT_LocalAccessPointConfiguration& config)
{
	agora::rtc::LocalAccessPointConfiguration AgoraLocalAccessPointConfiguration = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setLocalAccessPoint(AgoraLocalAccessPointConfiguration);
	config.FreeRawData(AgoraLocalAccessPointConfiguration);
	return ret;
}
int UAgoraBPuRtcEngine::SetAdvancedAudioOptions(const FUABT_AdvancedAudioOptions& options)
{
	agora::rtc::AdvancedAudioOptions advancedAudioOptions = options.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setAdvancedAudioOptions(advancedAudioOptions);
	options.FreeRawData(advancedAudioOptions);
	return ret;
}
int UAgoraBPuRtcEngine::SetAVSyncSource(const FString& channelId, int64 uid)
{
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	auto ret = AgoraUERtcEngine::Get()->setAVSyncSource(ChannelId.c_str(), uid);
	return ret;
}
int UAgoraBPuRtcEngine::EnableVideoImageSource(bool enable, const FUABT_ImageTrackOptions& options)
{
	agora::rtc::ImageTrackOptions imageTrackOptions = options.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableVideoImageSource(enable, imageTrackOptions);
	options.FreeRawData(imageTrackOptions);
	return ret;
}


int64 UAgoraBPuRtcEngine::GetCurrentMonotonicTimeInMs()
{
	auto ret = AgoraUERtcEngine::Get()->getCurrentMonotonicTimeInMs();
	return ret;
}

int UAgoraBPuRtcEngine::EnableWirelessAccelerate(bool enabled)
{
	auto ret = AgoraUERtcEngine::Get()->enableWirelessAccelerate(enabled);
	return ret;
}

int UAgoraBPuRtcEngine::GetNetworkType()
{
	auto ret = AgoraUERtcEngine::Get()->getNetworkType();
	return ret;
}


int UAgoraBPuRtcEngine::SetParameters(const FString& parameters)
{
	std::string parameterstr = TCHAR_TO_UTF8(*parameters);

	auto ret = AgoraUERtcEngine::Get()->setParameters(parameterstr.c_str());
	return ret;
}


int UAgoraBPuRtcEngine::StartMediaRenderingTracing()
{
	auto ret = AgoraUERtcEngine::Get()->startMediaRenderingTracing();
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

bool UAgoraBPuRtcEngine::IsFeatureAvailableOnDevice(EUABT_FeatureType type)
{
	auto ret = AgoraUERtcEngine::Get()->isFeatureAvailableOnDevice(UABTEnum::ToRawValue(type));
	return ret;
}


int UAgoraBPuRtcEngine::SendAudioMetadata(const FString& metadata, const FString& length)
{
	std::string AMetadata = TCHAR_TO_UTF8(*metadata);
	size_t ALength = FCString::Strtoui64(*length, NULL, 10);
	auto ret = AgoraUERtcEngine::Get()->sendAudioMetadata(AMetadata.c_str(), ALength);
	return ret;
}

int UAgoraBPuRtcEngine::QueryHDRCapability(EUABT_VIDEO_MODULE_TYPE videoModule, EUABT_HDR_CAPABILITY& capability)
{
	agora::rtc::HDR_CAPABILITY Result;
	auto ret = AgoraUERtcEngine::Get()->queryHDRCapability(UABTEnum::ToRawValue(videoModule), Result);
	capability = UABTEnum::WrapWithUE(Result);
	return ret;
}


int UAgoraBPuRtcEngine::JoinChannelEx(const FString& token, const FUABT_RtcConnection& connection, const FUABT_ChannelMediaOptions& options)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateRawData();
	std::string Token = TCHAR_TO_UTF8(*token);

	auto ret = AgoraUERtcEngine::Get()->joinChannelEx(Token.c_str(), rtcConnection, channelMediaOptions, nullptr);

	connection.FreeRawData(rtcConnection);
	options.FreeRawData(channelMediaOptions);
	return ret;
}


int UAgoraBPuRtcEngine::LeaveChannelEx(const FUABT_RtcConnection& connection, const FUABT_LeaveChannelOptions& options)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();

	agora::rtc::LeaveChannelOptions AgoraLeaveChannelOptions = options.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->leaveChannelEx(rtcConnection, AgoraLeaveChannelOptions);
	connection.FreeRawData(rtcConnection);
	options.FreeRawData(AgoraLeaveChannelOptions);
	return ret;
}

int UAgoraBPuRtcEngine::LeaveChannelWithUserAccountEx(FString channelId, const FString& userAccount, FUABT_LeaveChannelOptions options)
{
	std::string ChannelId = TCHAR_TO_UTF8(*channelId);
	std::string UserAccount = TCHAR_TO_UTF8(*userAccount);
	agora::rtc::LeaveChannelOptions AgoraLeaveChannelOptions = options.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->leaveChannelWithUserAccountEx(ChannelId.c_str(), UserAccount.c_str(), AgoraLeaveChannelOptions);
	options.FreeRawData(AgoraLeaveChannelOptions);
	return ret;
}

int UAgoraBPuRtcEngine::UpdateChannelMediaOptionsEx(const FUABT_ChannelMediaOptions& options, const FUABT_RtcConnection& connection)
{
	agora::rtc::ChannelMediaOptions channelMediaOptions = options.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->updateChannelMediaOptionsEx(channelMediaOptions, rtcConnection);

	options.FreeRawData(channelMediaOptions);
	connection.FreeRawData(rtcConnection);

	return ret;
}
int UAgoraBPuRtcEngine::SetVideoEncoderConfigurationEx(const FUABT_VideoEncoderConfiguration& config, const FUABT_RtcConnection& connection)
{
	agora::rtc::VideoEncoderConfiguration videoEncoderConfiguration = config.CreateRawData();

	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setVideoEncoderConfigurationEx(videoEncoderConfiguration, rtcConnection);

	config.FreeRawData(videoEncoderConfiguration);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteRemoteAudioStreamEx(int64 uid, bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteRemoteAudioStreamEx(uid, mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::MuteRemoteVideoStreamEx(int64 uid, bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteRemoteVideoStreamEx(uid, mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteVideoStreamTypeEx(int64 uid, EUABT_VIDEO_STREAM_TYPE streamType, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteVideoStreamTypeEx(uid, UABTEnum::ToRawValue(streamType), rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}



int UAgoraBPuRtcEngine::MuteLocalAudioStreamEx(bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteLocalAudioStreamEx(mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteLocalVideoStreamEx(bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteLocalVideoStreamEx(mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteAllRemoteAudioStreamsEx(bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteAllRemoteAudioStreamsEx(mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteAllRemoteVideoStreamsEx(bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteAllRemoteVideoStreamsEx(mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioBlocklistEx(data, UEuidNumber, rtcConnection);
	UABT::Free_UIDArrayPtr(data);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeAudioAllowlistEx(data, UEuidNumber, rtcConnection);
	UABT::Free_UIDArrayPtr(data);
	connection.FreeRawData(rtcConnection);
	return ret;
}



int UAgoraBPuRtcEngine::SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoBlocklistEx(data, UEuidNumber, rtcConnection);
	UABT::Free_UIDArrayPtr(data);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setSubscribeVideoAllowlistEx(data, UEuidNumber, rtcConnection);
	UABT::Free_UIDArrayPtr(data);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FUABT_VideoSubscriptionOptions& options, const FUABT_RtcConnection& connection)
{
	agora::rtc::VideoSubscriptionOptions videoSubscriptionOptions = options.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteVideoSubscriptionOptionsEx(uid, videoSubscriptionOptions, rtcConnection);
	options.FreeRawData(videoSubscriptionOptions);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteVoicePositionEx(uid, pan, gain, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteUserSpatialAudioParamsEx(int64 uid, const FUABT_SpatialAudioParams& params, const FUABT_RtcConnection& connection)
{
	agora::SpatialAudioParams spatialAudioParams = params.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteUserSpatialAudioParamsEx(uid, spatialAudioParams, rtcConnection);
	params.FreeRawData(spatialAudioParams);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetRemoteRenderModeEx(int64 uid, EUABT_RENDER_MODE_TYPE renderMode, EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setRemoteRenderModeEx(uid, UABTEnum::ToRawValue(renderMode), UABTEnum::ToRawValue(mirrorMode), rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableLoopbackRecordingEx(const FUABT_RtcConnection& connection, bool enabled, const FString& deviceName)
{
	std::string STDDeviceName = TCHAR_TO_UTF8(*deviceName);
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableLoopbackRecordingEx(rtcConnection, enabled, STDDeviceName.c_str());
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::AdjustRecordingSignalVolumeEx(int volume, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->adjustRecordingSignalVolumeEx(volume, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::MuteRecordingSignalEx(bool mute, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->muteRecordingSignalEx(mute, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->adjustUserPlaybackSignalVolumeEx(uid, volume, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

EUABT_CONNECTION_STATE_TYPE UAgoraBPuRtcEngine::GetConnectionStateEx(const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = UABTEnum::WrapWithUE(AgoraUERtcEngine::Get()->getConnectionStateEx(rtcConnection));
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableEncryptionEx(const FUABT_RtcConnection& connection, bool enabled, const FUABT_EncryptionConfig& config)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	agora::rtc::EncryptionConfig AgoraEncryptionConfig = config.CreateRawData();

	auto ret = AgoraUERtcEngine::Get()->enableEncryptionEx(rtcConnection, enabled, AgoraEncryptionConfig);

	connection.FreeRawData(rtcConnection);
	config.FreeRawData(AgoraEncryptionConfig);

	return ret;
}

int UAgoraBPuRtcEngine::CreateDataStreamEx(int& streamId, const FUABT_DataStreamConfig& config, const FUABT_RtcConnection& connection)
{
	agora::rtc::DataStreamConfig dataStreamConfig = config.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->createDataStreamEx(&streamId, dataStreamConfig, rtcConnection);
	config.FreeRawData(dataStreamConfig);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SendStreamMessageEx(int streamId, const FString& data, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string StdStrData = TCHAR_TO_UTF8(*data);
	auto ret = AgoraUERtcEngine::Get()->sendStreamMessageEx(streamId, StdStrData.c_str(), StdStrData.size(), rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::AddVideoWatermarkEx(const FString& watermarkUrl, const FUABT_WatermarkOptions& options, const FUABT_RtcConnection& connection)
{
	agora::rtc::WatermarkOptions watermarkOptions = options.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string STDSWatermarkUrl = TCHAR_TO_UTF8(*watermarkUrl);
	auto ret = AgoraUERtcEngine::Get()->addVideoWatermarkEx(STDSWatermarkUrl.c_str(), watermarkOptions, rtcConnection);
	options.FreeRawData(watermarkOptions);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::ClearVideoWatermarkEx(const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->clearVideoWatermarkEx(rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SendCustomReportMessageEx(const FString& id, const FString& category, const FString& event, const FString& label, int value, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string STDID = TCHAR_TO_UTF8(*id);
	std::string STDCategory = TCHAR_TO_UTF8(*category);
	std::string STDEvent = TCHAR_TO_UTF8(*event);
	std::string STDLabel = TCHAR_TO_UTF8(*label);
	auto ret = AgoraUERtcEngine::Get()->sendCustomReportMessageEx(STDID.c_str(), STDCategory.c_str(), STDEvent.c_str(), STDLabel.c_str(), value, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableAudioVolumeIndicationEx(interval, smooth, reportVad, rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::StartRtmpStreamWithoutTranscodingEx(const FString& url, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string Url = TCHAR_TO_UTF8(*url);
	int ret = AgoraUERtcEngine::Get()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::StartRtmpStreamWithTranscodingEx(const FString& url, const FUABT_LiveTranscoding& transcoding, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string streamUrl = TCHAR_TO_UTF8(*url);

	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateRawData();

	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithTranscodingEx(streamUrl.c_str(), liveTranscoding, rtcConnection);

	connection.FreeRawData(rtcConnection);
	transcoding.FreeRawData(liveTranscoding);

	return ret;
}

int UAgoraBPuRtcEngine::UpdateRtmpTranscodingEx(const FUABT_LiveTranscoding& transcoding, const FUABT_RtcConnection& connection)
{
	agora::rtc::LiveTranscoding liveTranscoding = transcoding.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();

	auto ret = AgoraUERtcEngine::Get()->updateRtmpTranscodingEx(liveTranscoding, rtcConnection);

	transcoding.FreeRawData(liveTranscoding);
	connection.FreeRawData(rtcConnection);

	return ret;
}

int UAgoraBPuRtcEngine::StopRtmpStreamEx(const FString& url, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string Url = TCHAR_TO_UTF8(*url);
	auto ret = AgoraUERtcEngine::Get()->startRtmpStreamWithoutTranscodingEx(Url.c_str(), rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::StartOrUpdateChannelMediaRelayEx(const FUABT_ChannelMediaRelayConfiguration& configuration, const FUABT_RtcConnection& connection)
{
	agora::rtc::ChannelMediaRelayConfiguration channelMediaRelayConfiguration = configuration.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startOrUpdateChannelMediaRelayEx(channelMediaRelayConfiguration, rtcConnection);
	configuration.FreeRawData(channelMediaRelayConfiguration);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::StopChannelMediaRelayEx(const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->stopChannelMediaRelayEx(rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::PauseAllChannelMediaRelayEx(const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->pauseAllChannelMediaRelayEx(rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::ResumeAllChannelMediaRelayEx(const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->resumeAllChannelMediaRelayEx(rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::GetUserInfoByUserAccountEx(const FString& userAccount, FUABT_UserInfo& userInfo, const FUABT_RtcConnection& connection)
{
	agora::rtc::UserInfo info;

	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUserAccountEx(TCHAR_TO_UTF8(*userAccount), &info, rtcConnection);

	userInfo = info;

	connection.FreeRawData(rtcConnection);

	return ret;
}
int UAgoraBPuRtcEngine::GetUserInfoByUidEx(int64 uid, FUABT_UserInfo& userInfo, const FUABT_RtcConnection& connection)
{
	agora::rtc::UserInfo info;
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();

	auto ret = AgoraUERtcEngine::Get()->getUserInfoByUidEx(uid, &info, rtcConnection);

	userInfo = info;
	connection.FreeRawData(rtcConnection);

	return ret;
}

int UAgoraBPuRtcEngine::EnableDualStreamModeEx(bool enabled, const FUABT_SimulcastStreamConfig& streamConfig, const FUABT_RtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig simulcastStreamConfig = streamConfig.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableDualStreamModeEx(enabled, simulcastStreamConfig, rtcConnection);
	streamConfig.FreeRawData(simulcastStreamConfig);
	connection.FreeRawData(rtcConnection);
	return ret;
}
int UAgoraBPuRtcEngine::SetDualStreamModeEx(EUABT_SIMULCAST_STREAM_MODE mode, const FUABT_SimulcastStreamConfig& streamConfig, const FUABT_RtcConnection& connection)
{
	agora::rtc::SimulcastStreamConfig AgoraSimulcastStreamConfig = streamConfig.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setDualStreamModeEx(UABTEnum::ToRawValue(mode), AgoraSimulcastStreamConfig, rtcConnection);
	streamConfig.FreeRawData(AgoraSimulcastStreamConfig);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::SetSimulcastConfigEx(const FUABT_SimulcastConfig& simulcastConfig, const FUABT_RtcConnection& connection)
{
	agora::rtc::SimulcastConfig AgoraSimulcastConfig = simulcastConfig.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->setSimulcastConfigEx(AgoraSimulcastConfig, rtcConnection);
	simulcastConfig.FreeRawData(AgoraSimulcastConfig);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::SetHighPriorityUserListEx(TArray<int64> uidList, EUABT_STREAM_FALLBACK_OPTIONS option, const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	int UEuidNumber = uidList.Num();
	agora::rtc::uid_t* data = UABT::New_UIDArrayPtr(uidList);
	auto ret = AgoraUERtcEngine::Get()->setHighPriorityUserListEx(data, UEuidNumber, UABTEnum::ToRawValue(option), rtcConnection);
	UABT::Free_UIDArrayPtr(data);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::TakeSnapshotEx(const FUABT_RtcConnection& connection, int64 uid, const FString& filePath)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string FilePath = TCHAR_TO_UTF8(*filePath);
	auto ret = AgoraUERtcEngine::Get()->takeSnapshotEx(rtcConnection, UABT::ToUID(uid), FilePath.c_str());
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::TakeSnapshotWithConfigEx(const FUABT_RtcConnection& connection, int64 uid, const FUABT_SnapshotConfig& config)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	agora::media::SnapshotConfig snapshotConfig = config.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->takeSnapshotEx(rtcConnection, UABT::ToUID(uid), snapshotConfig);
	config.FreeRawData(snapshotConfig);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::EnableContentInspectEx(bool enabled, const FUABT_ContentInspectConfig& config, const FUABT_RtcConnection& connection)
{
	agora::media::ContentInspectConfig contentInspectConfig = config.CreateRawData();
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->enableContentInspectEx(enabled, contentInspectConfig, rtcConnection);
	config.FreeRawData(contentInspectConfig);
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::StartMediaRenderingTracingEx(const FUABT_RtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->startMediaRenderingTracingEx(rtcConnection);
	connection.FreeRawData(rtcConnection);
	return ret;
}

int UAgoraBPuRtcEngine::SetParametersEx(const FUABT_RtcConnection& connection, const FString& parameters)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string STDParameters = TCHAR_TO_UTF8(*parameters);
	auto ret = AgoraUERtcEngine::Get()->setParametersEx(rtcConnection, STDParameters.c_str());
	connection.FreeRawData(rtcConnection);
	return ret;
}


int UAgoraBPuRtcEngine::GetCallIdEx(FString& callId, const FUABT_RtcConnection& connection)
{
	agora::util::AString CallId;
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	auto ret = AgoraUERtcEngine::Get()->getCallIdEx(CallId, rtcConnection);
	connection.FreeRawData(rtcConnection);

	callId = UTF8_TO_TCHAR(CallId->c_str());
	return ret;
}


int UAgoraBPuRtcEngine::SendAudioMetadataEx(const FUABT_RtcConnection& connection, const FString& metadata, const FString& length)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateRawData();
	std::string AgoraMetadata = TCHAR_TO_UTF8(*metadata);
	size_t AgoraLength = FCString::Strtoui64(*length, NULL, 10);
	auto ret = AgoraUERtcEngine::Get()->sendAudioMetadataEx(rtcConnection, AgoraMetadata.c_str(), AgoraLength);
	connection.FreeRawData(rtcConnection);
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

FUABT_ScreenCaptureSourceInfo UIScreenCaptureSourceList::GetSourceInfo(int index)
{
	FUABT_ScreenCaptureSourceInfo sourceInfo;
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


#pragma endregion Screen Share

