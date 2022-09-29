// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "URtcEngineProxyCompatibility.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IVideoDeviceManager.h"
#include "AgoraAudioDeviceManager.h"
#include "AgoraMediaRecorder.h"
#include "AgoraMediaPlayer.h"
#include "IAudioEncodedFrameObserver.h"
#include "IFrameObserver.h"
#include "string.h"
#include "AgoraCppPlugin/Include/RtcEngineProxy.h"
#include "AgoraRtcEngine.generated.h"


UCLASS()
class AGORAPLUGIN_API UIScreenCaptureSourceList : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Agora|ScreenCaptureSourceList")
	int64 GetCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|ScreenCaptureSourceList")
	FScreenCaptureSourceInfo GetSourceInfo(int64 index);
	UFUNCTION(BlueprintCallable, Category = "Agora|ScreenCaptureSourceList")
	void Release();
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	void SetScreenCaptureList(agora::rtc::IScreenCaptureSourceList* sourcelist);
#endif
private:
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
	agora::rtc::IScreenCaptureSourceList* sourceListNative;
#endif
};


/**
 * 
 */
UCLASS()
class AGORAPLUGIN_API AAgoraRtcEngine : public AActor, public agora::rtc::ue::RtcEngineProxy
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
public:
	AAgoraRtcEngine();
	void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	UObject* QueryInterface(EINTERFACE_ID_TYPE iid);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	void Release(bool sync);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int Initialize(FRtcEngineContext& context);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	FString GetVersion(int build);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	FString GetErrorDescription(int code);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannel(FString token, FString channelId, int64 uid, FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaOptions(FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int LeaveChannel(FLeaveChannelOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RenewToken(FString token);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetChannelProfile(ECHANNEL_PROFILE_TYPE profile);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetClientRole(ECLIENT_ROLE_TYPE clientroletype, FClientRoleOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartEchoTest(FEchoTestConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopEchoTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableVideo();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DisableVideo();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartPreview(EVIDEO_SOURCE_TYPE sourceType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopPreview(EVIDEO_SOURCE_TYPE sourceType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartLastmileProbeTest(FLastmileProbeConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoEncoderConfiguration(FVideoEncoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetBeautyEffectOptions(bool enabled, FBeautyOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLowlightEnhanceOptions(bool enabled, FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoDenoiserOptions(bool enabled, FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetColorEnhanceOptions(bool enabled, FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableRemoteSuperResolution(int64 userId, bool enable);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetupRemoteVideo(FVideoCanvas& canvas);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetupLocalVideo(FVideoCanvas& canvas);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DisableAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioProfile(EAUDIO_PROFILE_TYPE profile, EAUDIO_SCENARIO_TYPE scenario);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableLocalAudio(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteLocalAudioStream(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteAllRemoteAudioStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDefaultMuteAllRemoteAudioStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRemoteAudioStream(int64 uid, bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteLocalVideoStream(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableLocalVideo(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteAllRemoteVideoStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDefaultMuteAllRemoteVideoStreams(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRemoteVideoStream(int64 uid, bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVideoStreamType(int64 uid, EVIDEO_STREAM_TYPE streamType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVideoSubscriptionOptions(int64 uid, FVideoSubscriptionOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeAudioBlacklist(int64 uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeAudioWhitelist(int64 uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeVideoBlacklist(int64 uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeVideoWhitelist(int64 uidList, int uidNumber);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudioVolumeIndication(int interval, int smooth, bool reportVad);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartAudioRecording(FAudioRecordingConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterAudioEncodedFrameObserver(FAudioEncodedFrameObserverConfig& config, AIAudioEncodedFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopAudioRecording();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	UIMediaPlayer* CreateMediaPlayer();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DestroyMediaPlayer(UIMediaPlayer* media_player);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartAudioMixing(FString filePath, bool loopback, int cycle, int startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAudioMixing();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAudioMixing();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SelectAudioTrack(int index);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioTrackCount();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustAudioMixingVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustAudioMixingPublishVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioMixingPublishVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustAudioMixingPlayoutVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioMixingPlayoutVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioMixingDuration();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioMixingCurrentPosition();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioMixingPosition(int pos);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioMixingDualMonoMode(EAUDIO_MIXING_DUAL_MONO_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioMixingPitch(int pitch);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetEffectsVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEffectsVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PreloadEffect(int soundId, FString filePath, int startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PlayEffect(int soundId, FString filePath, int loopCount, float pitch, float pan, int gain, bool publish, int startPos);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PlayAllEffects(int loopCount, float pitch, float pan, int gain, bool publish);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetVolumeOfEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVolumeOfEffect(int soundId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UnloadEffect(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UnloadAllEffects();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetEffectDuration(FString filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEffectPosition(int soundId, int pos);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetEffectCurrentPosition(int soundId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableSoundPositionIndication(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVoicePosition(int64 uid, float pan, float gain);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableSpatialAudio(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteUserSpatialAudioParams(int64 uid, FSpatialAudioParams& params);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceBeautifierPreset(EVOICE_BEAUTIFIER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioEffectPreset(EAUDIO_EFFECT_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceConversionPreset(EVOICE_CONVERSION_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioEffectParameters(EAUDIO_EFFECT_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceBeautifierParameters(EVOICE_BEAUTIFIER_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceConversionParameters(EVOICE_CONVERSION_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVoicePitch(float pitch);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVoiceEqualization(EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVoiceReverb(EAUDIO_REVERB_TYPE reverbKey, int value);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLogFile(FString filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLogFilter(int filter);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLogLevel(ELOG_LEVEL level);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLogFileSize(int fileSizeInKBytes);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UploadLogFile(FString& requestId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableDualStreamMode(EVIDEO_SOURCE_TYPE sourceType, bool enabled, FSimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDualStreamMode(EVIDEO_SOURCE_TYPE sourceType, ESIMULCAST_STREAM_MODE mode, FSimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableEchoCancellationExternal(bool enabled, int audioSourceDelay);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableCustomAudioLocalPlayback(int sourceId, bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartPrimaryCustomAudioTrack(FAudioTrackConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopPrimaryCustomAudioTrack();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartSecondaryCustomAudioTrack(FAudioTrackConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopSecondaryCustomAudioTrack();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRecordingAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetPlaybackAudioFrameParameters(int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetMixedAudioFrameParameters(int sampleRate, int channel, int samplesPerCall);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetPlaybackAudioFrameBeforeMixingParameters(int sampleRate, int channel);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudioSpectrumMonitor(int intervalInMS);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DisableAudioSpectrumMonitor();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterAudioSpectrumObserver(AIAudioSpectrumObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UnregisterAudioSpectrumObserver(AIAudioSpectrumObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustRecordingSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRecordingSignal(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustPlaybackSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustUserPlaybackSignalVolume(int uid, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalPublishFallbackOption(ESTREAM_FALLBACK_OPTIONS option);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteSubscribeFallbackOption(ESTREAM_FALLBACK_OPTIONS option);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableLoopbackRecording(bool enabled, FString deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustLoopbackSignalVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetLoopbackRecordingVolume();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableInEarMonitoring(bool enabled, int includeAudioFilters);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetInEarMonitoringVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int LoadExtensionProvider(FString path, bool unload_after_use);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetExtensionProviderProperty(FString provider, FString key, FString value);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableExtension(FString provider, FString extension, bool enable, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetExtensionProperty(FString provider, FString extension, FString key, FString value, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetExtensionProperty(FString provider, FString extension, FString key, FString value, int buf_len, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraCapturerConfiguration(FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int64 CreateCustomVideoTrack();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int64 CreateCustomEncodedVideoTrack(FSenderOptions& sender_option);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DestroyCustomVideoTrack(int64 video_track_id);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DestroyCustomEncodedVideoTrack(int64 video_track_id);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SwitchCamera();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraZoomSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraFaceDetectSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraTorchSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraFocusSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraAutoFocusFaceModeSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraZoomFactor(float factor);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableFaceDetection(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	float GetCameraMaxZoomFactor();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraFocusPositionInPreview(float positionX, float positionY);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraTorchOn(bool isOn);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraAutoFocusFaceModeEnabled(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraExposurePositionSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraExposurePosition(float positionXinView, float positionYinView);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsCameraAutoExposureFaceModeSupported();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraAutoExposureFaceModeEnabled(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEnableSpeakerphone(bool speakerOn);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool IsSpeakerphoneEnabled();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	UIScreenCaptureSourceList* GetScreenCaptureSources(FSIZE thumbSize, FSIZE iconSize, bool includeScreen);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioSessionOperationRestriction(EAUDIO_SESSION_OPERATION_RESTRICTION restriction);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCaptureByDisplayId(int displayId, FRectangle& regionRect, FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCaptureByScreenRect(FRectangle& screenRect, FRectangle& regionRect, FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioDeviceInfo(FDeviceInfo& deviceInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCaptureByWindowId(int64 windowId, FRectangle& regionRect, FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateScreenCaptureRegion(FRectangle& regionRect);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateScreenCaptureParameters(FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCapture(FScreenCaptureParameters2& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateScreenCapture(FScreenCaptureParameters2& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopScreenCapture();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetCallId(FString& callId);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int Rate(FString callId, int rating, FString description);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int Complain(FString callId, FString description);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartRtmpStreamWithoutTranscoding(FString url);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartRtmpStreamWithTranscoding(FString url, FLiveTranscoding& transcoding);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateRtmpTranscoding(FLiveTranscoding& transcoding);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopRtmpStream(FString url);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartLocalVideoTranscoder(FLocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateLocalTranscoderConfiguration(FLocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopLocalVideoTranscoder();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartPrimaryCameraCapture(FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartSecondaryCameraCapture(FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopPrimaryCameraCapture();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopSecondaryCameraCapture();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, EVIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, EVIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartPrimaryScreenCapture(FScreenCaptureConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartSecondaryScreenCapture(FScreenCaptureConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopPrimaryScreenCapture();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopSecondaryScreenCapture();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	ECONNECTION_STATE_TYPE GetConnectionState();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool RegisterEventHandler(AIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool UnregisterEventHandler(AIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterPacketObserver(AIPacketObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEncryptionMode(FString encryptionMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEncryptionSecret(FString secret);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableEncryption(bool enabled, FEncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int CreateDataStream(int streamId, FDataStreamConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendStreamMessage(int streamId, FString data, int64 length);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AddVideoWatermark(FString watermarkUrl, FWatermarkOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ClearVideoWatermark();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ClearVideoWatermarks();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AddInjectStreamUrl(FString url, FInjectStreamConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RemoveInjectStreamUrl(FString url);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableWebSdkInteroperability(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendCustomReportMessage(FString id, FString category, FString event, FString label, int value);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterMediaMetadataObserver(AIMetadataObserver* observer, EMETADATA_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UnregisterMediaMetadataObserver(AIMetadataObserver* observer, EMETADATA_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartAudioFrameDump(FString channel_id, int64 user_id, FString location, FString uuid, FString passwd, int64 duration_ms, bool auto_upload);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterLocalUserAccount(FString appId, FString userAccount);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannelWithUserAccount(FString token, FString channelId, FString userAccount, FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannelWithUserAccountEx(FString token, FString channelId, FString userAccount, FChannelMediaOptions& options, AIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUserAccount(FString userAccount, FUserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUid(int64 uid, FUserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartChannelMediaRelay(FChannelMediaRelayConfiguration& configuration);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaRelay(FChannelMediaRelayConfiguration& configuration);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDirectCdnStreamingVideoConfiguration(FVideoEncoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartDirectCdnStreaming(AIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopDirectCdnStreaming();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateDirectCdnStreamingMediaOptions(FDirectCdnStreamingMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartRhythmPlayer(FString sound1, FString sound2, FAgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopRhythmPlayer();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ConfigRhythmPlayer(FAgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int TakeSnapshot(int64 uid, FString filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableContentInspect(bool enabled, FContentInspectConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustCustomAudioPublishVolume(int64 sourceId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustCustomAudioPlayoutVolume(int64 sourceId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCloudProxy(ECLOUD_PROXY_TYPE proxyType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalAccessPoint(FLocalAccessPointConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAdvancedAudioOptions(FAdvancedAudioOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAVSyncSource(FString channelId, int64 uid);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableVideoImageSource(bool enable, FImageTrackOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannelEx(FString token, FRtcConnection& connection, FChannelMediaOptions& options, AIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int LeaveChannelEx(FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaOptionsEx(FChannelMediaOptions& options, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoEncoderConfigurationEx(FVideoEncoderConfiguration& config, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetupRemoteVideoEx(FVideoCanvas& canvas, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRemoteAudioStreamEx(int64 uid, bool mute, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRemoteVideoStreamEx(int64 uid, bool mute, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeAudioBlacklistEx(int64 uidList, int uidNumber, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeAudioWhitelistEx(int64 uidList, int uidNumber, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeVideoBlacklistEx(int64 uidList, int uidNumber, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeVideoWhitelistEx(int64 uidList, int uidNumber, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVideoSubscriptionOptionsEx(int64 uid, FVideoSubscriptionOptions& options, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVoicePositionEx(int64 uid, float pan, float gain, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteUserSpatialAudioParamsEx(int64 uid, FSpatialAudioParams& params, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableLoopbackRecordingEx(FRtcConnection& connection, bool enabled, FString deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	ECONNECTION_STATE_TYPE GetConnectionStateEx(FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableEncryptionEx(FRtcConnection& connection, bool enabled, FEncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int CreateDataStreamEx(int streamId, FDataStreamConfig& config, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendStreamMessageEx(int streamId, FString data, int64 length, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AddVideoWatermarkEx(FString watermarkUrl, FWatermarkOptions& options, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ClearVideoWatermarkEx(FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendCustomReportMessageEx(FString id, FString category, FString event, FString label, int value, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUserAccountEx(FString userAccount, FUserInfo& userInfo, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoProfileEx(int width, int height, int frameRate, int bitrate);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableDualStreamModeEx(EVIDEO_SOURCE_TYPE sourceType, bool enabled, FSimulcastStreamConfig& streamConfig, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDualStreamModeEx(EVIDEO_SOURCE_TYPE sourceType, ESIMULCAST_STREAM_MODE mode, FSimulcastStreamConfig& streamConfig, FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableWirelessAccelerate(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int TakeSnapshotEx(FRtcConnection& connection, int64 uid, FString filePath);
	private:
		UIVideoDeviceManager* videoDeviceManager;
		UIAudioDeviceManager* audioDeviceManager;
		class UILocalSpatialAudioEngine* spatialAudioEngine;
		UIMediaRecorder* mediaRecorder;
		UIMediaPlayer* mediaPlayer;
		UIScreenCaptureSourceList* screenCaptureSourceList;

};

