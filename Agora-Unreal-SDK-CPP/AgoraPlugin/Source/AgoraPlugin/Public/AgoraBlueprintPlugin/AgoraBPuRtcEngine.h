//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "AgoraPluginInterface.h"
#include "AgoraBPuDataTypes.h"
#include "UObject/StrongObjectPtr.h"


#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "Kismet/GameplayStatics.h"


#include "AgoraBPuIRtcEngineEventHandler.h"
#include "AgoraBPuIRtcEngineEventHandlerEx.h"


#include "AgoraBPuRtcEngine.generated.h"

#pragma region Screen Share


UCLASS(BlueprintType)
class AGORAPLUGIN_API UIScreenCaptureSourceList : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Agora|ScreenCaptureSourceList")
	int GetCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|ScreenCaptureSourceList")
	FUABT_ScreenCaptureSourceInfo GetSourceInfo(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|ScreenCaptureSourceList")
	void Release();

#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
public:
	void SetScreenCaptureList(agora::rtc::IScreenCaptureSourceList* sourcelist);
private:
	agora::rtc::IScreenCaptureSourceList* sourceListNative;
#endif
};


#pragma endregion Screen Share


/**
 * 
 */
UCLASS()
class AGORAPLUGIN_API UAgoraBPuRtcEngine : public UObject
{
	GENERATED_BODY()
	
public:
	void InitInstance();

	void UninitInstance();

	UFUNCTION(BlueprintPure, Category = "Agora|IRtcEngine")
	static UAgoraBPuRtcEngine* GetAgoraRtcEngine();

	UFUNCTION(BlueprintPure, Category = "Agora|IRtcEngine")
	void GetEventHandler(EAgoraBPuEventHandlerType& HandlerType, UAgoraBPuIRtcEngineEventHandler*& EventHandler, UAgoraBPuIRtcEngineEventHandlerEx* & EventHandlerEx);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int Initialize(const FUABT_RtcEngineContext& context);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	FString GetVersion();


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	void Release(bool sync = false);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	void ClearAllEventHandlerCBExecutors();



	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannel(const FString & token, const FString& channelId, int64 uid);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelWithOptions(const FString& token, const FString& channelId, int64 uid, const FUABT_ChannelMediaOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LeaveChannel();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LeaveChannelWithOptions(const FUABT_LeaveChannelOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVideo();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DisableVideo();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudio();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DisableAudio();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetClientRole(FUABT_ClientRoleOptions options, EUABT_CLIENT_ROLE_TYPE clientroletype = EUABT_CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);



	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetupLocalVideo(const FUABT_VideoCanvas& canvas);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetupRemoteVideo(const FUABT_VideoCanvas& canvas);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetupRemoteVideoEx(const FUABT_VideoCanvas& canvas, const FUABT_RtcConnection& connection);


#pragma region Other APIs

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	FString GetErrorDescription(int code);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryCodecCapability(TArray<FUABT_CodecCapInfo> & codecInfo, int QuerySize = 10);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryDeviceScore();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PreloadChannel(const FString & token, const FString & channelId, int64 uid);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PreloadChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdatePreloadChannelToken(const FString& token);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateChannelMediaOptions(const FUABT_ChannelMediaOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int RenewToken(const FString & token);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetChannelProfile(EUABT_CHANNEL_PROFILE_TYPE profile);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartEchoTest(const FUABT_EchoTestConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopEchoTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableMultiCamera(bool enabled, const FUABT_CameraCapturerConfiguration& config);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartPreview(EUABT_VIDEO_SOURCE_TYPE sourceType = EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopPreview(EUABT_VIDEO_SOURCE_TYPE sourceType = EUABT_VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartLastmileProbeTest(const FUABT_LastmileProbeConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopLastmileProbeTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoEncoderConfiguration(const FUABT_VideoEncoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetBeautyEffectOptions(bool enabled, const FUABT_BeautyOptions& options, EUABT_MEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLowlightEnhanceOptions(bool enabled, const FUABT_LowlightEnhanceOptions& options, EUABT_MEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoDenoiserOptions(bool enabled, const FUABT_VideoDenoiserOptions& options, EUABT_MEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetColorEnhanceOptions(bool enabled, const FUABT_ColorEnhanceOptions& options, EUABT_MEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVirtualBackground(bool enabled, FUABT_VirtualBackgroundSource backgroundSource, FUABT_SegmentationProperty segproperty, EUABT_MEDIA_SOURCE_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoScenario(EUABT_VIDEO_APPLICATION_SCENARIO_TYPE scenarioType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoQoEPreference(EUABT_VIDEO_QOE_PREFERENCE_TYPE qoePreference);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioProfileAndScenario(EUABT_AUDIO_PROFILE_TYPE profile = EUABT_AUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT, EUABT_AUDIO_SCENARIO_TYPE scenario = EUABT_AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioProfile(EUABT_AUDIO_PROFILE_TYPE profile = EUABT_AUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioScenario(EUABT_AUDIO_SCENARIO_TYPE scenario = EUABT_AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableLocalAudio(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteLocalAudioStream(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteAudioStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteDefaultVideoStreamType(EUABT_VIDEO_STREAM_TYPE streamType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRemoteAudioStream(int64 uid, bool mute);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteLocalVideoStream(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableLocalVideo(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteVideoStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRemoteVideoStream(int64 uid, bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoStreamType(int64 uid, EUABT_VIDEO_STREAM_TYPE streamType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoSubscriptionOptions(int64 uid, const FUABT_VideoSubscriptionOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudioVolumeIndication(int interval, int smooth, bool reportVad);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartAudioRecording(const FUABT_AudioRecordingConfiguration& config);
	
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int RegisterAudioEncodedFrameObserver(const FAudioEncodedFrameObserverConfig& config, UIAudioEncodedFrameObserver* observer);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopAudioRecording();
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//UIMediaPlayer* CreateMediaPlayer();
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int DestroyMediaPlayer(UIMediaPlayer* media_player);

	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//UIMediaRecorder* CreateMediaRecorder(FRecorderStreamInfo info);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int DestroyMediaRecorder(UIMediaRecorder* mediaRecorder);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartAudioMixing(const FString & filePath, bool loopback, int cycle, int startPos = 0);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopAudioMixing();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAudioMixing();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAudioMixing();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SelectAudioTrack(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioTrackCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustAudioMixingVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustAudioMixingPublishVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioMixingPublishVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustAudioMixingPlayoutVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioMixingPlayoutVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioMixingDuration();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioMixingCurrentPosition();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioMixingPosition(int pos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioMixingDualMonoMode(EUABT_AUDIO_MIXING_DUAL_MONO_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioMixingPitch(int pitch);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioMixingPlaybackSpeed(int speed);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetEffectsVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetEffectsVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PreloadEffect(int soundId, const FString & filePath, int startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PlayEffect(int soundId, const FString& filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetVolumeOfEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVolumeOfEffect(int soundId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UnloadEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UnloadAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetEffectDuration(const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetEffectPosition(int soundId, int pos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetEffectCurrentPosition(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableSoundPositionIndication(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVoicePosition(int64 uid, float pan, float gain);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableSpatialAudio(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteUserSpatialAudioParams(int64 uid, const FUABT_SpatialAudioParams& params);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceBeautifierPreset(EUABT_VOICE_BEAUTIFIER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioEffectPreset(EUABT_AUDIO_EFFECT_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceConversionPreset(EUABT_VOICE_CONVERSION_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioEffectParameters(EUABT_AUDIO_EFFECT_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceBeautifierParameters(EUABT_VOICE_BEAUTIFIER_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceConversionParameters(EUABT_VOICE_CONVERSION_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoicePitch(float pitch);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoiceFormant(const FString & formantRatio = "0.0");

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoiceEqualization(EUABT_AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoiceReverb(EUABT_AUDIO_REVERB_TYPE reverbKey, int value);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogFile(const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogFilter(int filter);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogLevel(EUABT_LOG_LEVEL level);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogFileSize(int fileSizeInKBytes);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UploadLogFile(FString& requestId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int WriteLog(EUABT_LOG_LEVEL level, const FString& Content);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalRenderMode(EUABT_RENDER_MODE_TYPE renderMode, EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode = EUABT_VIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteRenderMode(int64 uid, EUABT_RENDER_MODE_TYPE renderMode, EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVideoMirrorMode(EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableDualStreamMode(bool enabled, const FUABT_SimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDualStreamMode(EUABT_SIMULCAST_STREAM_MODE mode, const FUABT_SimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableCustomAudioLocalPlayback(int64 trackId, bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRecordingAudioFrameParameters(int sampleRate, int channel, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetPlaybackAudioFrameParameters(int sampleRate, int channel, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudioSpectrumMonitor(int intervalInMS);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DisableAudioSpectrumMonitor();


	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int RegisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int UnregisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer);
	
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustRecordingSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRecordingSignal(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustPlaybackSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustUserPlaybackSignalVolume(int64 uid, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalPublishFallbackOption(EUABT_STREAM_FALLBACK_OPTIONS option);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteSubscribeFallbackOption(EUABT_STREAM_FALLBACK_OPTIONS option);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetHighPriorityUserList(const TArray<int64> & uidList, EUABT_STREAM_FALLBACK_OPTIONS option);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableLoopbackRecording(bool enabled, const FString & deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustLoopbackSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetLoopbackRecordingVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableInEarMonitoring(bool enabled, int includeAudioFilters);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetInEarMonitoringVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LoadExtensionProvider(const FString& path, bool unload_after_use);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetExtensionProviderProperty(const FString& provider, const FString& key, const FString& value);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableExtension(const FString& provider, const FString& extension, bool enable = true, EUABT_MEDIA_SOURCE_TYPE type = EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetExtensionProperty(const FString& provider, const FString& extension, const FString& key, const FString& value, EUABT_MEDIA_SOURCE_TYPE type = EUABT_MEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetExtensionProperty(const FString& provider, const FString& extension,const FUABT_ExtensionInfo & ExtensionInfo, const FString& key, FString& value);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraCapturerConfiguration(const FUABT_CameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int64 CreateCustomVideoTrack();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int64 CreateCustomEncodedVideoTrack(const FUABT_SenderOptions& sender_option);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DestroyCustomVideoTrack(int64 video_track_id);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DestroyCustomEncodedVideoTrack(int64 video_track_id);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SwitchCamera();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraZoomSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraFaceDetectSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraTorchSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraFocusSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraAutoFocusFaceModeSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraZoomFactor(float factor);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableFaceDetection(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	float GetCameraMaxZoomFactor();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraFocusPositionInPreview(float positionX, float positionY);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraTorchOn(bool isOn);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraAutoFocusFaceModeEnabled(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraExposurePositionSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraExposurePosition(float positionXinView, float positionYinView);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraExposureSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraExposureFactor(float factor);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraAutoExposureFaceModeSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraAutoExposureFaceModeEnabled(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraStabilizationMode(EUABT_CAMERA_STABILIZATION_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetEnableSpeakerphone(bool speakerOn);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsSpeakerphoneEnabled();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRouteInCommunicationMode(int route);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsCameraCenterStageSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableCameraCenterStage(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	UIScreenCaptureSourceList* GetScreenCaptureSources(const FUABT_SIZE & thumbSize, const FUABT_SIZE & iconSize, bool includeScreen);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioSessionOperationRestriction(EUABT_AUDIO_SESSION_OPERATION_RESTRICTION restriction);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureByDisplayId(int64 displayId, const FUABT_Rectangle& regionRect, const FUABT_ScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureByScreenRect(const FUABT_Rectangle& screenRect, const FUABT_Rectangle& regionRect, const FUABT_ScreenCaptureParameters& captureParams) __deprecated;
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioDeviceInfo(FUABT_DeviceInfo& deviceInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureByWindowId(int64 windowId, const FUABT_Rectangle& regionRect, const  FUABT_ScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetScreenCaptureContentHint(EUABT_VIDEO_CONTENT_HINT contentHint);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateScreenCaptureRegion(const FUABT_Rectangle& regionRect);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateScreenCaptureParameters(const FUABT_ScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCapture(const FUABT_ScreenCaptureParameters2& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryScreenCaptureCapability();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryCameraFocalLengthCapability(const TArray<FUABT_FocalLengthInfo> & focalLengthInfos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetScreenCaptureScenario(EUABT_SCREEN_SCENARIO_TYPE screenScenario);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateScreenCapture(const FUABT_ScreenCaptureParameters2& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopScreenCapture();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetCallId(FString& callId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int Rate(const FString& callId, int rating, const FString& description);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int Complain(const FString& callId, const FString& description);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRtmpStreamWithoutTranscoding(const FString& url);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRtmpStreamWithTranscoding(const FString& url, const FUABT_LiveTranscoding& transcoding);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateRtmpTranscoding(const FUABT_LiveTranscoding& transcoding);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopRtmpStream(const FString& url);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartCameraCapture(EUABT_VIDEO_SOURCE_TYPE sourceType, const FUABT_CameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopCameraCapture(EUABT_VIDEO_SOURCE_TYPE sourceType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureBySourceType(EUABT_VIDEO_SOURCE_TYPE sourceType, const FUABT_ScreenCaptureConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopScreenCaptureBySourceType(EUABT_VIDEO_SOURCE_TYPE sourceType);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartLocalVideoTranscoder(const FUABT_LocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateLocalTranscoderConfiguration(const FUABT_LocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopLocalVideoTranscoder();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraDeviceOrientation(EUABT_VIDEO_SOURCE_TYPE type, EUABT_VIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetScreenCaptureOrientation(EUABT_VIDEO_SOURCE_TYPE type, EUABT_VIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	EUABT_CONNECTION_STATE_TYPE GetConnectionState();
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool RegisterEventHandler(UIRtcEngineEventHandler* eventHandler);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool RegisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool UnregisterEventHandler(UIRtcEngineEventHandler* eventHandler);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool UnregisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteUserPriority(int64 uid, EUABT_PRIORITY_TYPE userPriority);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int RegisterPacketObserver(UIPacketObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableEncryption(bool enabled, const FUABT_EncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int CreateDataStream(int& streamId, const FUABT_DataStreamConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendStreamMessage(int streamId, const FString& data);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AddVideoWatermark(const FString& watermarkUrl, const FUABT_WatermarkOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ClearVideoWatermarks();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableWebSdkInteroperability(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendCustomReportMessage(const FString& id, const FString& category, const FString& event, const FString& label, int value);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int RegisterMediaMetadataObserver(UIMetadataObserver* observer, FENUMWRAP_METADATA_TYPE type);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int UnregisterMediaMetadataObserver(UIMetadataObserver* observer, FENUMWRAP_METADATA_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartAudioFrameDump(const FString& channel_id, int64 uid, const FString& location, const FString& uuid, const FString& passwd, int64 duration_ms, bool auto_upload);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopAudioFrameDump(const FString & channel_id, int64 uid, const FString & location);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAINSMode(bool enabled, EUABT_AUDIO_AINS_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int RegisterLocalUserAccount(const FString& appId, const FString& userAccount);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount, const FUABT_ChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelWithUserAccountEx(const FString& token, const FString& channelId, const FString& userAccount, const FUABT_ChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUserAccount(const FString& userAccount, FUABT_UserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUid(int64 uid, FUABT_UserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartOrUpdateChannelMediaRelay(const FUABT_ChannelMediaRelayConfiguration& configuration);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartOrUpdateChannelMediaRelayEx(const FUABT_ChannelMediaRelayConfiguration& configuration, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDirectCdnStreamingAudioConfiguration(EUABT_AUDIO_PROFILE_TYPE profile);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDirectCdnStreamingVideoConfiguration(const FUABT_VideoEncoderConfiguration& config);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int StartDirectCdnStreaming(UIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int StopDirectCdnStreaming();
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int UpdateDirectCdnStreamingMediaOptions(const FDirectCdnStreamingMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRhythmPlayer(const FString& sound1, const FString& sound2, const FUABT_AgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopRhythmPlayer();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ConfigRhythmPlayer(const FUABT_AgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int TakeSnapshot(int64 uid, const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableContentInspect(bool enabled, const FUABT_ContentInspectConfig& config);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustCustomAudioPublishVolume(int64 trackId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustCustomAudioPlayoutVolume(int64 trackId, int volume);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCloudProxy(EUABT_CLOUD_PROXY_TYPE proxyType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalAccessPoint(const FUABT_LocalAccessPointConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAdvancedAudioOptions(const FUABT_AdvancedAudioOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAVSyncSource(const FString& channelId, int64 uid);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVideoImageSource(bool enable, const FUABT_ImageTrackOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelEx(const FString& token, const FUABT_RtcConnection& connection, const FUABT_ChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LeaveChannelEx(const FUABT_RtcConnection& connection, const FUABT_LeaveChannelOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateChannelMediaOptionsEx(const FUABT_ChannelMediaOptions& options, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoEncoderConfigurationEx(const FUABT_VideoEncoderConfiguration& config, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRemoteAudioStreamEx(int64 uid, bool mute, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRemoteVideoStreamEx(int64 uid, bool mute, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoStreamTypeEx(int64 uid, EUABT_VIDEO_STREAM_TYPE streamType, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FUABT_VideoSubscriptionOptions& options, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteUserSpatialAudioParamsEx(int64 uid, const FUABT_SpatialAudioParams& params, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteRenderModeEx(int64 uid, EUABT_RENDER_MODE_TYPE renderMode, EUABT_VIDEO_MIRROR_MODE_TYPE mirrorMode, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableLoopbackRecordingEx(const FUABT_RtcConnection& connection, bool enabled, const FString& deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	EUABT_CONNECTION_STATE_TYPE GetConnectionStateEx(const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableEncryptionEx(const FUABT_RtcConnection& connection, bool enabled, const FUABT_EncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int CreateDataStreamEx(int& streamId, const FUABT_DataStreamConfig& config, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendStreamMessageEx(int streamId, const FString& data, const  FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AddVideoWatermarkEx(const FString& watermarkUrl, const FUABT_WatermarkOptions& options, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ClearVideoWatermarkEx(const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendCustomReportMessageEx(const FString& id, const FString& category, const FString& event, const FString& label, int value, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUserAccountEx(const FString& userAccount, FUABT_UserInfo& userInfo, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUidEx(int64 uid, FUABT_UserInfo& userInfo, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableDualStreamModeEx(bool enabled, const FUABT_SimulcastStreamConfig& streamConfig, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDualStreamModeEx(EUABT_SIMULCAST_STREAM_MODE mode, const FUABT_SimulcastStreamConfig& streamConfig, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableWirelessAccelerate(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int TakeSnapshotEx(const FUABT_RtcConnection& connection, int64 uid, const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableContentInspectEx(bool enabled, const FUABT_ContentInspectConfig& config, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")

	int MuteLocalAudioStreamEx(bool mute, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteLocalVideoStreamEx(bool mute, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteAudioStreamsEx(bool mute, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteVideoStreamsEx(bool mute, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioBlocklist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioAllowlist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoBlocklist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoAllowlist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRtmpStreamWithoutTranscodingEx(const FString& url, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRtmpStreamWithTranscodingEx(const FString& url, const FUABT_LiveTranscoding& transcoding, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateRtmpTranscodingEx(const FUABT_LiveTranscoding& transcoding, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopRtmpStreamEx(const FString& url, const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopChannelMediaRelayEx(const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAllChannelMediaRelayEx(const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAllChannelMediaRelayEx(const FUABT_RtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetParameters(const FString& parameters);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetParametersEx(const FUABT_RtcConnection& connection, const FString & parameters);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetCallIdEx( FString & callId, const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendAudioMetadata(const FString& metadata, const FString& length);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendAudioMetadataEx(const FUABT_RtcConnection& connection,const FString & metadata, const FString & length);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartMediaRenderingTracing();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartMediaRenderingTracingEx(const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableInstantMediaRendering();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	FString GetNtpWallTimeInMs();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetHeadphoneEQPreset(EUABT_HEADPHONE_EQUALIZER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetHeadphoneEQParameters(int lowGain, int highGain);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVoiceAITuner(bool enabled, EUABT_VOICE_AI_TUNER_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetEarMonitoringAudioFrameParameters(int sampleRate, int channel, EUABT_RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int64 GetCurrentMonotonicTimeInMs();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int RegisterExtension(const FString& provider, const FString& extension, EUABT_MEDIA_SOURCE_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetNetworkType();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsFeatureAvailableOnDevice(EUABT_FeatureType type);

#pragma endregion Other APIs


private:
	//// avoid copy constructor
	//UAgoraBPRtcEngine(const UAgoraBPRtcEngine&) = delete;
	//UAgoraBPRtcEngine& operator=(const UAgoraBPRtcEngine&) = delete;

	static UAgoraBPuRtcEngine* Instance;


	EAgoraBPuEventHandlerType EventHandlerType = EAgoraBPuEventHandlerType::None;
	TStrongObjectPtr<UAgoraBPuIRtcEngineEventHandler> UserRtcEventHandler = nullptr;
	TStrongObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> UserRtcEventHandlerEx = nullptr;

	TStrongObjectPtr<UIScreenCaptureSourceList> UserScreenCaptureSourceList = nullptr;
};
