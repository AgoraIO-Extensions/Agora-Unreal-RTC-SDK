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
public:
	void SetScreenCaptureList(agora::rtc::IScreenCaptureSourceList* sourcelist);
private:
	agora::rtc::IScreenCaptureSourceList* sourceListNative;
#endif
};


class RtcEngineProxyClassWrapper : public agora::rtc::ue::RtcEngineProxy {};

/**
 *
 */
UCLASS(Blueprintable)
class AGORAPLUGIN_API UAgoraRtcEngine : public UObject, public RtcEngineProxyClassWrapper
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	UObject* QueryInterface(EINTERFACE_ID_TYPE iid);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	void Release(bool sync);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int Initialize(const FRtcEngineContext& context);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int InitializeEx(const FRtcEngineContextEx& context);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	FString GetVersion(int build);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	FString GetErrorDescription(int code);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int QueryCodecCapability(TArray<FCodecCapInfo> codecInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannel(FString token, FString channelId, int64 uid, const FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaOptions(const FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int LeaveChannel(const FLeaveChannelOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RenewToken(FString token);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetChannelProfile(ECHANNEL_PROFILE_TYPE profile);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetClientRole(ECLIENT_ROLE_TYPE clientroletype, FClientRoleOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartEchoTest(const FEchoTestConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopEchoTest();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableVideo();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DisableVideo();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartPreview(EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopPreview(EVIDEO_SOURCE_TYPE sourceType = EVIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA_PRIMARY);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartLastmileProbeTest(const FLastmileProbeConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoEncoderConfiguration(const FVideoEncoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetBeautyEffectOptions(bool enabled, const FBeautyOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLowlightEnhanceOptions(bool enabled, const FLowlightEnhanceOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoDenoiserOptions(bool enabled, const FVideoDenoiserOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetColorEnhanceOptions(bool enabled, const FColorEnhanceOptions& options, EMEDIA_SOURCE_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableVirtualBackground(bool enabled, FVirtualBackgroundSource backgroundSource, FSegmentationProperty segproperty, EMEDIA_SOURCE_TYPE type);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetupRemoteVideo(const FVideoCanvas& canvas);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetupLocalVideo(const FVideoCanvas& canvas);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoScenario(EVIDEO_APPLICATION_SCENARIO_TYPE scenarioType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DisableAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioProfile(EAUDIO_PROFILE_TYPE profile = EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT, EAUDIO_SCENARIO_TYPE scenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioScenario(EAUDIO_SCENARIO_TYPE scenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
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
	int SetRemoteVideoSubscriptionOptions(int64 uid, const FVideoSubscriptionOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteDefaultVideoStreamType(EVIDEO_STREAM_TYPE streamType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudioVolumeIndication(int interval, int smooth, bool reportVad);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartAudioRecording(const FAudioRecordingConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterAudioEncodedFrameObserver(const FAudioEncodedFrameObserverConfig& config, UIAudioEncodedFrameObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopAudioRecording();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	UIMediaPlayer* CreateMediaPlayer();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DestroyMediaPlayer(UIMediaPlayer* media_player);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	UIMediaRecorder* CreateMediaRecorder(FRecorderStreamInfo info);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int DestroyMediaRecorder(UIMediaRecorder* mediaRecorder);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartAudioMixing(FString filePath, bool loopback, int cycle, int startPos = 0);
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
	int SetRemoteUserSpatialAudioParams(int64 uid, const FSpatialAudioParams& params);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceBeautifierPreset(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioEffectPreset(FENUMWRAP_AUDIO_EFFECT_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceConversionPreset(FENUMWRAP_VOICE_CONVERSION_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAudioEffectParameters(FENUMWRAP_AUDIO_EFFECT_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceBeautifierParameters(FENUMWRAP_VOICE_BEAUTIFIER_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVoiceConversionParameters(FENUMWRAP_VOICE_CONVERSION_PRESET preset, int param1, int param2);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVoicePitch(float pitch);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVoiceFormant(FString formantRatio = "0.0");

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
	int SetLocalRenderMode(ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode = EVIDEO_MIRROR_MODE_TYPE::VIDEO_MIRROR_MODE_AUTO);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteRenderMode(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalVideoMirrorMode(EVIDEO_MIRROR_MODE_TYPE mirrorMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableDualStreamMode(bool enabled, const FSimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDualStreamMode(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableCustomAudioLocalPlayback(int64 trackId, bool enabled);
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
	int RegisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UnregisterAudioSpectrumObserver(UIAudioSpectrumObserver* observer);
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
	int SetHighPriorityUserList(TArray<int64> uidList, ESTREAM_FALLBACK_OPTIONS option);

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
	int EnableExtension(FString provider, FString extension, bool enable = true, EMEDIA_SOURCE_TYPE type = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetExtensionProperty(FString provider, FString extension, FString key, FString value, EMEDIA_SOURCE_TYPE type = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetExtensionProperty(FString provider, FString extension, FString key, FString value, int buf_len, EMEDIA_SOURCE_TYPE type = EMEDIA_SOURCE_TYPE::UNKNOWN_MEDIA_SOURCE);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraCapturerConfiguration(const FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int64 CreateCustomVideoTrack();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int64 CreateCustomEncodedVideoTrack(const FSenderOptions& sender_option);
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
	int StartScreenCaptureByDisplayId(int displayId, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCaptureByScreenRect(const FRectangle& screenRect, const FRectangle& regionRect, const FScreenCaptureParameters& captureParams) __deprecated;
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetAudioDeviceInfo(FDeviceInfo& deviceInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCaptureByWindowId(int64 windowId, const FRectangle& regionRect, const  FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetScreenCaptureContentHint(EVIDEO_CONTENT_HINT contentHint);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateScreenCaptureRegion(const FRectangle& regionRect);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateScreenCaptureParameters(const FScreenCaptureParameters& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCapture(const FScreenCaptureParameters2& captureParams);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int QueryScreenCaptureCapability();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetScreenCaptureScenario(ESCREEN_SCENARIO_TYPE screenScenario);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateScreenCapture(const FScreenCaptureParameters2& captureParams);
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
	int StartCameraCapture(EVIDEO_SOURCE_TYPE sourceType, const FCameraCapturerConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopCameraCapture(EVIDEO_SOURCE_TYPE sourceType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType, const FScreenCaptureConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopScreenCaptureBySourceType(EVIDEO_SOURCE_TYPE sourceType);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartLocalVideoTranscoder(const FLocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateLocalTranscoderConfiguration(const FLocalTranscoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopLocalVideoTranscoder();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCameraDeviceOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetScreenCaptureOrientation(EVIDEO_SOURCE_TYPE type, FENUMWRAP_VIDEO_ORIENTATION orientation);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	ECONNECTION_STATE_TYPE GetConnectionState();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool RegisterEventHandler(UIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool RegisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool UnregisterEventHandler(UIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	bool UnregisterEventHandlerEx(UIRtcEngineEventHandlerEx* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteUserPriority(int64 uid, EPRIORITY_TYPE userPriority);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterPacketObserver(UIPacketObserver* observer);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEncryptionMode(FString encryptionMode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetEncryptionSecret(FString secret);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableEncryption(bool enabled, const FEncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int CreateDataStream(int& streamId, const FDataStreamConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendStreamMessage(int streamId, FString data);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AddVideoWatermark(FString watermarkUrl, const FWatermarkOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ClearVideoWatermarks();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAudio();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableWebSdkInteroperability(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendCustomReportMessage(FString id, FString category, FString event, FString label, int value);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterMediaMetadataObserver(UIMetadataObserver* observer, FENUMWRAP_METADATA_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UnregisterMediaMetadataObserver(UIMetadataObserver* observer, FENUMWRAP_METADATA_TYPE type);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartAudioFrameDump(FString channel_id, int64 user_id, FString location, FString uuid, FString passwd, int64 duration_ms, bool auto_upload);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAINSMode(bool enabled, EAUDIO_AINS_MODE mode);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int RegisterLocalUserAccount(FString appId, FString userAccount);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannelWithUserAccount(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannelWithUserAccountEx(FString token, FString channelId, FString userAccount, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUserAccount(FString userAccount, FUserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUid(int64 uid, FUserInfo& userInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartOrUpdateChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration) __deprecated;
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaRelay(const FChannelMediaRelayConfiguration& configuration) __deprecated;
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAllChannelMediaRelay();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDirectCdnStreamingAudioConfiguration(EAUDIO_PROFILE_TYPE profile);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDirectCdnStreamingVideoConfiguration(const FVideoEncoderConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartDirectCdnStreaming(UIDirectCdnStreamingEventHandler* eventHandler, FString publishUrl, FDirectCdnStreamingMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopDirectCdnStreaming();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateDirectCdnStreamingMediaOptions(const FDirectCdnStreamingMediaOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartRhythmPlayer(FString sound1, FString sound2, const FAgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopRhythmPlayer();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ConfigRhythmPlayer(const FAgoraRhythmPlayerConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int TakeSnapshot(int64 uid, FString filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableContentInspect(bool enabled, FContentInspectConfig& config);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustCustomAudioPublishVolume(int64 trackId, int volume);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustCustomAudioPlayoutVolume(int64 trackId, int volume);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetCloudProxy(ECLOUD_PROXY_TYPE proxyType);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetLocalAccessPoint(const FLocalAccessPointConfiguration& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAdvancedAudioOptions(const FAdvancedAudioOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetAVSyncSource(FString channelId, int64 uid);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableVideoImageSource(bool enable, const FImageTrackOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int JoinChannelEx(FString token, const FRtcConnection& connection, const FChannelMediaOptions& options, UIRtcEngineEventHandler* eventHandler);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int LeaveChannelEx(const FRtcConnection& connection, const FLeaveChannelOptions& options);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaOptionsEx(const FChannelMediaOptions& options, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetVideoEncoderConfigurationEx(const FVideoEncoderConfiguration& config, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetupRemoteVideoEx(const FVideoCanvas& canvas, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRemoteAudioStreamEx(int64 uid, bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteRemoteVideoStreamEx(int64 uid, bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVideoStreamTypeEx(int64 uid, EVIDEO_STREAM_TYPE streamType, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVideoSubscriptionOptionsEx(int64 uid, const FVideoSubscriptionOptions& options, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteVoicePositionEx(int64 uid, float pan, float gain, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteUserSpatialAudioParamsEx(int64 uid, const FSpatialAudioParams& params, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetRemoteRenderModeEx(int64 uid, ERENDER_MODE_TYPE renderMode, EVIDEO_MIRROR_MODE_TYPE mirrorMode, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableLoopbackRecordingEx(const FRtcConnection& connection, bool enabled, FString deviceName);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	ECONNECTION_STATE_TYPE GetConnectionStateEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableEncryptionEx(const FRtcConnection& connection, bool enabled, const FEncryptionConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int CreateDataStreamEx(int& streamId, const FDataStreamConfig& config, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendStreamMessageEx(int streamId, FString data, const  FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AddVideoWatermarkEx(FString watermarkUrl, const FWatermarkOptions& options, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ClearVideoWatermarkEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SendCustomReportMessageEx(FString id, FString category, FString event, FString label, int value, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableAudioVolumeIndicationEx(int interval, int smooth, bool reportVad, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUserAccountEx(FString userAccount, FUserInfo& userInfo, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int GetUserInfoByUidEx(int64 uid, FUserInfo& userInfo, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableDualStreamModeEx(bool enabled, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetDualStreamModeEx(FENUMWRAP_SIMULCAST_STREAM_MODE mode, const FSimulcastStreamConfig& streamConfig, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableWirelessAccelerate(bool enabled);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int TakeSnapshotEx(const FRtcConnection& connection, int64 uid, FString filePath);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteLocalAudioStreamEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteLocalVideoStreamEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteAllRemoteAudioStreamsEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int MuteAllRemoteVideoStreamsEx(bool mute, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeAudioBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeAudioAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeVideoBlocklistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetSubscribeVideoAllowlistEx(TArray<int64> uidList, int uidNumber, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int AdjustUserPlaybackSignalVolumeEx(int64 uid, int volume, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartRtmpStreamWithoutTranscodingEx(FString url, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartRtmpStreamWithTranscodingEx(FString url, const FLiveTranscoding& transcoding, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateRtmpTranscodingEx(const FLiveTranscoding& transcoding, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopRtmpStreamEx(FString url, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int UpdateChannelMediaRelayEx(const FChannelMediaRelayConfiguration& configuration, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StopChannelMediaRelayEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int PauseAllChannelMediaRelayEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int ResumeAllChannelMediaRelayEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetParameters(FString parameters);

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int StartMediaRenderingTracing();
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int EnableInstantMediaRendering();

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	FString GetNtpWallTimeInMs();

	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetHeadphoneEQPreset(FENUMWRAP_HEADPHONE_EQUALIZER_PRESET preset);
	UFUNCTION(BlueprintCallable, Category = "Agora|RtcEngineProxy")
	int SetHeadphoneEQParameters(int lowGain, int highGain);

private:
	UIVideoDeviceManager* videoDeviceManager;
	UIAudioDeviceManager* audioDeviceManager;
	class UILocalSpatialAudioEngine* spatialAudioEngine;
	UIMediaRecorder* mediaRecorder;
	UIMediaPlayer* mediaPlayer;
	UIScreenCaptureSourceList* screenCaptureSourceList;

};

