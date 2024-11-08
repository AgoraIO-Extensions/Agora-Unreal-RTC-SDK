//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "AgoraPluginInterface.h"
#include "AgoraBPuBaseDataTypes.h"
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
	FScreenCaptureSourceInfo GetSourceInfo(int index);
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
	int Initialize(const FRtcEngineContext& context);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	FString GetVersion();


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	void Release(bool sync = false);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	void ClearAllEventHandlerCBExecutors();



	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannel(const FString & token, const FString& channelId, int64 uid);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelWithOptions(const FString& token, const FString& channelId, int64 uid, const FChannelMediaOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LeaveChannel();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LeaveChannelWithOptions(const FLeaveChannelOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVideo();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DisableVideo();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudio();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int DisableAudio();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetClientRole(FClientRoleOptions options, ECLIENT_ROLE_TYPE clientroletype = ECLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);



	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetupLocalVideo(const FVideoCanvas& canvas);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetupRemoteVideo(const FVideoCanvas& canvas);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetupRemoteVideoEx(const FVideoCanvas& canvas, const FRtcConnection& connection);


#pragma region Other APIs

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	FString GetErrorDescription(int code);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryCodecCapability(TArray<FCodecCapInfo> & codecInfo, int QuerySize = 10);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryDeviceScore();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PreloadChannel(const FString & token, const FString & channelId, int64 uid);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PreloadChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdatePreloadChannelToken(const FString& token);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateChannelMediaOptions(const FChannelMediaOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int RenewToken(const FString & token);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetChannelProfile(ECHANNEL_PROFILE_TYPE profile);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartEchoTest(const FEchoTestConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopEchoTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableMultiCamera(bool enabled, const FCameraCapturerConfiguration& config);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartPreview(EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopPreview(EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartLastmileProbeTest(const FLastmileProbeConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopLastmileProbeTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoEncoderConfiguration(const FVideoEncoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetBeautyEffectOptions(bool enabled, const FBeautyOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLowlightEnhanceOptions(bool enabled, const FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoDenoiserOptions(bool enabled, const FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetColorEnhanceOptions(bool enabled, const FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoScenario(EVIDEO_APPLICATION_SCENARIO_TYPE scenarioType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoQoEPreference(EVIDEO_QOE_PREFERENCE_TYPE qoePreference);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioProfileAndScenario(EAUDIO_PROFILE_TYPE profile = EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT, EAUDIO_SCENARIO_TYPE scenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioProfile(EAUDIO_PROFILE_TYPE profile = EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableLocalAudio(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteLocalAudioStream(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteAudioStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType);
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
	int SetRemoteVideoStreamType(int64 uid, EVIDEO_STREAM_TYPE streamType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoSubscriptionOptions(int64 uid, const FVideoSubscriptionOptions& options);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudioVolumeIndication(int interval, int smooth, bool reportVad);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartAudioRecording(const FAudioRecordingConfiguration& config);
	
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
	int SetAudioMixingDualMonoMode(EAUDIO_MIXING_DUAL_MONO_MODE mode);
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
	int SetRemoteUserSpatialAudioParams(int64 uid, const FSpatialAudioParams& params);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceBeautifierPreset(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioEffectPreset(FENUMWRAP_AUDIO_EFFECT_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceConversionPreset(FENUMWRAP_VOICE_CONVERSION_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioEffectParameters(FENUMWRAP_AUDIO_EFFECT_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceBeautifierParameters(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVoiceConversionParameters(FENUMWRAP_VOICE_CONVERSION_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoicePitch(float pitch);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoiceFormant(const FString & formantRatio = "0.0");

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoiceEqualization(EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVoiceReverb(EAUDIO_REVERB_TYPE reverbKey, int value);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogFile(const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogFilter(int filter);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogLevel(ELOG_LEVEL level);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLogFileSize(int fileSizeInKBytes);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UploadLogFile(FString& requestId);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int WriteLog(ELOG_LEVEL level, const FString& Content);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode = EVIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableDualStreamMode(bool enabled, const FSimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDualStreamMode(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableCustomAudioLocalPlayback(int64 trackId, bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRecordingAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetPlaybackAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
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
	int SetLocalPublishFallbackOption(ESTREAM_FALLBACK_OPTIONS option);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteSubscribeFallbackOption(ESTREAM_FALLBACK_OPTIONS option);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetHighPriorityUserList(const TArray<int64> & uidList, ESTREAM_FALLBACK_OPTIONS option);

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
	int EnableExtension(const FString& provider, const FString& extension, bool enable = true, EMEDIA_SOURCE_TYPE type = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetExtensionProperty(const FString& provider, const FString& extension, const FString& key, const FString& value, EMEDIA_SOURCE_TYPE type = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetExtensionProperty(const FString& provider, const FString& extension,const FExtensionInfo & ExtensionInfo, const FString& key, FString& value);


	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraCapturerConfiguration(const FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int64 CreateCustomVideoTrack();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int64 CreateCustomEncodedVideoTrack(const FSenderOptions& sender_option);
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
	int SetCameraStabilizationMode(FENUMWRAP_CAMERA_STABILIZATION_MODE mode);
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
	UIScreenCaptureSourceList* GetScreenCaptureSources(const FSIZE & thumbSize, const FSIZE & iconSize, bool includeScreen);
	
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAudioSessionOperationRestriction(EAUDIO_SESSION_OPERATION_RESTRICTION restriction);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureByDisplayId(int64 displayId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureByScreenRect(const FRectangle& screenRect, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams) __deprecated;
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetAudioDeviceInfo(FDeviceInfo& deviceInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureByWindowId(int64 windowId, const FRectangle& regionRect, const  FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateScreenCaptureRegion(const FRectangle& regionRect);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateScreenCaptureParameters(const FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCapture(const FScreenCaptureParameters2& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryScreenCaptureCapability();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int QueryCameraFocalLengthCapability(const TArray<FAGFocalLengthInfo> & focalLengthInfos);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateScreenCapture(const FScreenCaptureParameters2& captureParams);
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
	int StartRtmpStreamWithTranscoding(const FString& url, const FLiveTranscoding& transcoding);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateRtmpTranscoding(const FLiveTranscoding& transcoding);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopRtmpStream(const FString& url);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartCameraCapture(EVIDEO_SOURCE_TYPE sourceType, const FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopCameraCapture(EVIDEO_SOURCE_TYPE sourceType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType, const FScreenCaptureConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartLocalVideoTranscoder(const FLocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateLocalTranscoderConfiguration(const FLocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopLocalVideoTranscoder();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	ECONNECTION_STATE_TYPE GetConnectionState();
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool RegisterEventHandler(UIRtcEngineEventHandler* eventHandler);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool RegisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool UnregisterEventHandler(UIRtcEngineEventHandler* eventHandler);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//bool UnregisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int RegisterPacketObserver(UIPacketObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableEncryption(bool enabled, const FEncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int CreateDataStream(int& streamId, const FDataStreamConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendStreamMessage(int streamId, const FString& data);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AddVideoWatermark(const FString& watermarkUrl, const FWatermarkOptions& options);
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
	int SetAINSMode(bool enabled, EAUDIO_AINS_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int RegisterLocalUserAccount(const FString& appId, const FString& userAccount);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelWithUserAccount(const FString& token, const FString& channelId, const FString& userAccount, const FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelWithUserAccountEx(const FString& token, const FString& channelId, const FString& userAccount, const FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUserAccount(const FString& userAccount, FUserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUid(int64 uid, FUserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartOrUpdateChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartOrUpdateChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDirectCdnStreamingVideoConfiguration(const FVideoEncoderConfiguration& config);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int StartDirectCdnStreaming(UIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options);
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int StopDirectCdnStreaming();
	//UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	//int UpdateDirectCdnStreamingMediaOptions(const FDirectCdnStreamingMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRhythmPlayer(const FString& sound1, const FString& sound2, const FAgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopRhythmPlayer();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ConfigRhythmPlayer(const FAgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int TakeSnapshot(int64 uid, const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableContentInspect(bool enabled, const FContentInspectConfig& config);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustCustomAudioPublishVolume(int64 trackId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustCustomAudioPlayoutVolume(int64 trackId, int volume);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetCloudProxy(ECLOUD_PROXY_TYPE proxyType);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetLocalAccessPoint(const FLocalAccessPointConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAdvancedAudioOptions(const FAdvancedAudioOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetAVSyncSource(const FString& channelId, int64 uid);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVideoImageSource(bool enable, const FImageTrackOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int JoinChannelEx(const FString& token, const FRtcConnection& connection, const FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int LeaveChannelEx(const FRtcConnection& connection, const FLeaveChannelOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateChannelMediaOptionsEx(const FChannelMediaOptions& options, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetVideoEncoderConfigurationEx(const FVideoEncoderConfiguration& config, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRemoteAudioStreamEx(int64 uid, bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteRemoteVideoStreamEx(int64 uid, bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FVideoSubscriptionOptions& options, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteUserSpatialAudioParamsEx(int64 uid, const FSpatialAudioParams& params, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableLoopbackRecordingEx(const FRtcConnection& connection, bool enabled, const FString& deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	ECONNECTION_STATE_TYPE GetConnectionStateEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableEncryptionEx(const FRtcConnection& connection, bool enabled, const FEncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int CreateDataStreamEx(int& streamId, const FDataStreamConfig& config, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendStreamMessageEx(int streamId, const FString& data, const  FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AddVideoWatermarkEx(const FString& watermarkUrl, const FWatermarkOptions& options, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ClearVideoWatermarkEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendCustomReportMessageEx(const FString& id, const FString& category, const FString& event, const FString& label, int value, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUserAccountEx(const FString& userAccount, FUserInfo& userInfo, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableDualStreamModeEx(bool enabled, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetDualStreamModeEx(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableWirelessAccelerate(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int TakeSnapshotEx(const FRtcConnection& connection, int64 uid, const FString& filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableContentInspectEx(bool enabled, const FContentInspectConfig& config, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")

	int MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioBlocklist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioAllowlist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoBlocklist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoAllowlist(TArray<int64> uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRtmpStreamWithoutTranscodingEx(const FString& url, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartRtmpStreamWithTranscodingEx(const FString& url, const FLiveTranscoding& transcoding, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int UpdateRtmpTranscodingEx(const FLiveTranscoding& transcoding, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopRtmpStreamEx(const FString& url, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StopChannelMediaRelayEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int PauseAllChannelMediaRelayEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int ResumeAllChannelMediaRelayEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetParameters(const FString& parameters);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetParametersEx(const FRtcConnection& connection, const FString & parameters);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetCallIdEx( FString & callId, const FRtcConnection& connection);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendAudioMetadata(const FString& metadata, const FString& length);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SendAudioMetadataEx(const FRtcConnection& connection,const FString & metadata, const FString & length);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartMediaRenderingTracing();
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int StartMediaRenderingTracingEx(const FRtcConnection& connection);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableInstantMediaRendering();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	FString GetNtpWallTimeInMs();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetHeadphoneEQPreset(FENUMWRAP_HEADPHONE_EQUALIZER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetHeadphoneEQParameters(int lowGain, int highGain);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int EnableVoiceAITuner(bool enabled, EVOICE_AI_TUNER_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int SetEarMonitoringAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int64 GetCurrentMonotonicTimeInMs();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int RegisterExtension(const FString& provider, const FString& extension, EMEDIA_SOURCE_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	int GetNetworkType();

	UFUNCTION(BlueprintCallable, Category = "Agora|IRtcEngine")
	bool IsFeatureAvailableOnDevice(EFeatureType type);

#pragma endregion Other APIs


private:
	//// 防止拷贝和赋值操作
	//UAgoraBPRtcEngine(const UAgoraBPRtcEngine&) = delete;
	//UAgoraBPRtcEngine& operator=(const UAgoraBPRtcEngine&) = delete;

	static UAgoraBPuRtcEngine* Instance;


	EAgoraBPuEventHandlerType EventHandlerType = EAgoraBPuEventHandlerType::None;
	TStrongObjectPtr<UAgoraBPuIRtcEngineEventHandler> UserRtcEventHandler = nullptr;
	TStrongObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> UserRtcEventHandlerEx = nullptr;

	TStrongObjectPtr<UIScreenCaptureSourceList> UserScreenCaptureSourceList = nullptr;
};
