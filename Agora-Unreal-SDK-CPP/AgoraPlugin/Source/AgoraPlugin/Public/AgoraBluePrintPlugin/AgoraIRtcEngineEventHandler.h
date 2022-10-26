// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "URtcEngineProxyCompatibility.h"
#include <iostream>
#include <string.h>
#include "AgoraIRtcEngineEventHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventHandlerType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnJoinChannelSuccess, FString, channel, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRejoinChannelSuccess, FString, channel, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnProxyConnected, FString, channel, int64, uid, EPROXY_TYPE, proxyType, FString, localProxyIp, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnError, int, err, FString, msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAudioQuality, int64, uid, int, quality, int, delay, int, lost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLastmileProbeResult, const FLastmileProbeResult&, result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioVolumeIndication,const TArray<FAudioVolumeInfo>&, speakers, int, totalVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaveChannel,const FRtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRtcStats,const FRtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioDeviceStateChanged, FString, deviceId, int, deviceType, int, deviceState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioMixingFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioEffectFinished, int, soundId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVideoDeviceStateChanged, FString, deviceId, int, deviceType, int, deviceState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMediaDeviceChanged, int, deviceType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNetworkQuality, int64, uid, int, txQuality, int, rxQuality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIntraRequestReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUplinkNetworkInfoUpdated,const FUplinkNetworkInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDownlinkNetworkInfoUpdated,const FDownlinkNetworkInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLastmileQuality, int, quality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFirstLocalVideoFrame, EVIDEO_SOURCE_TYPE, source, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstLocalVideoFramePublished, EVIDEO_SOURCE_TYPE, source, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVideoSourceFrameSizeChanged, EVIDEO_SOURCE_TYPE, sourceType, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFirstRemoteVideoDecoded, int64, uid, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnVideoSizeChanged, EVIDEO_SOURCE_TYPE , sourceType, int64, uid, int, width, int, height, int, rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLocalVideoStateChanged, EVIDEO_SOURCE_TYPE, source, ELOCAL_VIDEO_STREAM_STATE, state, ELOCAL_VIDEO_STREAM_ERROR, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteVideoStateChanged, int64, uid, EREMOTE_VIDEO_STATE, state, EREMOTE_VIDEO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFirstRemoteVideoFrame, int64, userId, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserJoined, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserOffline, int64, uid, EUSER_OFFLINE_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserMuteAudio, int64, uid, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserMuteVideo, int64, userId, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserEnableVideo, int64, uid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserStateChanged, int64, uid, int, state);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserEnableLocalVideo, int64, uid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnApiCallExecuted, int, err, FString, api, FString, result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalAudioStats,const FLocalAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoteAudioStats,const FRemoteAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalVideoStats, EVIDEO_SOURCE_TYPE, source,const FLocalVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoteVideoStats,const FRemoteVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCameraFocusAreaChanged, int, x, int, y, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCameraExposureAreaChanged, int, x, int, y, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnFacePositionChanged, int, imageWidth, int, imageHeight, FRectangle, vecRectangle, TArray<int>, vecDistance, int, numFaces);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioMixingStateChanged, EAUDIO_MIXING_STATE_TYPE, state, EAUDIO_MIXING_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRhythmPlayerStateChanged, ERHYTHM_PLAYER_STATE_TYPE, state, ERHYTHM_PLAYER_ERROR_TYPE, errorCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionInterrupted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionBanned);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStreamMessage, int64, userId, int, streamId, FString, data, int64, length, int, sentTs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStreamMessageError, int64, userId, int, streamId, int, code, int, missed, int, cached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestToken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTokenPrivilegeWillExpire, FString, token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFirstLocalAudioFramePublished, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstRemoteAudioFrame, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstRemoteAudioDecoded, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalAudioStateChanged, ELOCAL_AUDIO_STREAM_STATE, state, ELOCAL_AUDIO_STREAM_ERROR, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteAudioStateChanged, int64, uid, EREMOTE_AUDIO_STATE, state, EREMOTE_AUDIO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveSpeaker, int64, userId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentInspectResult, ECONTENT_INSPECT_RESULT, result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSnapshotTaken, int64, uid, FString, filePath, int, width, int, height, int, errCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClientRoleChanged, ECLIENT_ROLE_TYPE, oldRole, ECLIENT_ROLE_TYPE, newRole);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClientRoleChangeFailed, ECLIENT_ROLE_CHANGE_FAILED_REASON, reason, ECLIENT_ROLE_TYPE, currentRole);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioDeviceVolumeChanged, EMEDIA_DEVICE_TYPE, deviceType, int, volume, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRtmpStreamingStateChanged, FString, url, ERTMP_STREAM_PUBLISH_STATE, state, ERTMP_STREAM_PUBLISH_ERROR_TYPE, errCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRtmpStreamingEvent, FString, url, ERTMP_STREAMING_EVENT, eventCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTranscodingUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioRoutingChanged, int, routing);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelMediaRelayStateChanged, int, state, int, code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChannelMediaRelayEvent, int, code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalPublishFallbackToAudioOnly, bool, isFallbackOrRecover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteSubscribeFallbackToAudioOnly, int64, uid, bool, isFallbackOrRecover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteAudioTransportStats, int64, uid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteVideoTransportStats, int64, uid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConnectionStateChanged, ECONNECTION_STATE_TYPE, state, ECONNECTION_CHANGED_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWlAccMessage, EWLACC_MESSAGE_REASON, reason, EWLACC_SUGGEST_ACTION, action, FString, wlAccMsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWlAccStats, FWlAccStats, currentStats, FWlAccStats, averageStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNetworkTypeChanged, ENETWORK_TYPE, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEncryptionError, EENCRYPTION_ERROR_TYPE, errorType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPermissionError, EPERMISSION_TYPE, permissionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalUserRegistered, int64, uid, FString, userAccount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserInfoUpdated, int64, uid,const FUserInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUploadLogResult, FString, requestId, bool, success, EUPLOAD_ERROR_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSubscribeStateChanged, FString, channel, int64, uid, ESTREAM_SUBSCRIBE_STATE, oldState, ESTREAM_SUBSCRIBE_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnVideoSubscribeStateChanged, FString, channel, int64, uid, ESTREAM_SUBSCRIBE_STATE, oldState, ESTREAM_SUBSCRIBE_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAudioPublishStateChanged, FString, channel, ESTREAM_PUBLISH_STATE, oldState, ESTREAM_PUBLISH_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnVideoPublishStateChanged, EVIDEO_SOURCE_TYPE, source, FString, channel, ESTREAM_PUBLISH_STATE, oldState, ESTREAM_PUBLISH_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnExtensionEvent, FString, provider, FString, extension, FString, key, FString, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExtensionStarted, FString, provider, FString, extension);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExtensionStopped, FString, provider, FString, extension);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnExtensionError, FString, provider, FString, extension, int, error, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserAccountUpdated, int64, uid, FString, userAccount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetMaxMetadataSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReadyToSendMetadata,const FAgoraMetadata&, metadata, EVIDEO_SOURCE_TYPE, source_type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetadataReceived, const FAgoraMetadata&, metadata);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDirectCdnStreamingStateChanged, EDIRECT_CDN_STREAMING_STATE, state, EDIRECT_CDN_STREAMING_ERROR, error, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirectCdnStreamingStats, const FDirectCdnStreamingStats&, stats);

UCLASS()
class AGORAPLUGIN_API AIRtcEngineEventHandler : public AActor, public agora::rtc::IRtcEngineEventHandlerEx
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	using IRtcEngineEventHandlerEx::eventHandlerType;
	using IRtcEngineEventHandlerEx::onJoinChannelSuccess;
	using IRtcEngineEventHandlerEx::onRejoinChannelSuccess;
	using IRtcEngineEventHandlerEx::onAudioQuality;
	using IRtcEngineEventHandlerEx::onAudioVolumeIndication;
	using IRtcEngineEventHandlerEx::onLeaveChannel;
	using IRtcEngineEventHandlerEx::onRtcStats;
	using IRtcEngineEventHandlerEx::onNetworkQuality;
	using IRtcEngineEventHandlerEx::onIntraRequestReceived;
	using IRtcEngineEventHandlerEx::onFirstLocalVideoFrame;
	using IRtcEngineEventHandlerEx::onFirstLocalVideoFramePublished;
	using IRtcEngineEventHandlerEx::onFirstRemoteVideoDecoded;
	using IRtcEngineEventHandlerEx::onVideoSizeChanged;
	using IRtcEngineEventHandlerEx::onLocalVideoStateChanged;
	using IRtcEngineEventHandlerEx::onRemoteVideoStateChanged;
	using IRtcEngineEventHandlerEx::onFirstRemoteVideoFrame;
	using IRtcEngineEventHandlerEx::onUserJoined;
	using IRtcEngineEventHandlerEx::onUserOffline;
	using IRtcEngineEventHandlerEx::onUserMuteAudio;
	using IRtcEngineEventHandlerEx::onUserMuteVideo;
	using IRtcEngineEventHandlerEx::onUserEnableVideo;
	using IRtcEngineEventHandlerEx::onUserEnableLocalVideo;
	using IRtcEngineEventHandlerEx::onUserStateChanged;
	using IRtcEngineEventHandlerEx::onLocalAudioStats;
	using IRtcEngineEventHandlerEx::onRemoteAudioStats;
	using IRtcEngineEventHandlerEx::onLocalVideoStats;
	using IRtcEngineEventHandlerEx::onRemoteVideoStats;
	using IRtcEngineEventHandlerEx::onConnectionLost;
	using IRtcEngineEventHandlerEx::onConnectionInterrupted;
	using IRtcEngineEventHandlerEx::onConnectionBanned;
	using IRtcEngineEventHandlerEx::onStreamMessage;
	using IRtcEngineEventHandlerEx::onStreamMessageError;
	using IRtcEngineEventHandlerEx::onRequestToken;
	using IRtcEngineEventHandlerEx::onTokenPrivilegeWillExpire;
	using IRtcEngineEventHandlerEx::onFirstLocalAudioFramePublished;
	using IRtcEngineEventHandlerEx::onFirstRemoteAudioFrame;
	using IRtcEngineEventHandlerEx::onFirstRemoteAudioDecoded;
	using IRtcEngineEventHandlerEx::onLocalAudioStateChanged;
	using IRtcEngineEventHandlerEx::onRemoteAudioStateChanged;
	using IRtcEngineEventHandlerEx::onActiveSpeaker;
	using IRtcEngineEventHandlerEx::onClientRoleChanged;
	using IRtcEngineEventHandlerEx::onClientRoleChangeFailed;
	using IRtcEngineEventHandlerEx::onRemoteAudioTransportStats;
	using IRtcEngineEventHandlerEx::onRemoteVideoTransportStats;
	using IRtcEngineEventHandlerEx::onConnectionStateChanged;
	using IRtcEngineEventHandlerEx::onWlAccMessage;
	using IRtcEngineEventHandlerEx::onWlAccStats;
	using IRtcEngineEventHandlerEx::onNetworkTypeChanged;
	using IRtcEngineEventHandlerEx::onEncryptionError;
	using IRtcEngineEventHandlerEx::onUploadLogResult;
	using IRtcEngineEventHandlerEx::onUserAccountUpdated;
	using IRtcEngineEventHandlerEx::onAudioSubscribeStateChanged;
	using IRtcEngineEventHandlerEx::onVideoSubscribeStateChanged;
	using IRtcEngineEventHandlerEx::onAudioPublishStateChanged;
	using IRtcEngineEventHandlerEx::onVideoPublishStateChanged;
	using IRtcEngineEventHandlerEx::onSnapshotTaken;
public:
	AIRtcEngineEventHandler();

	void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FEventHandlerType EventHandlerType;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnJoinChannelSuccess OnJoinChannelSuccess;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRejoinChannelSuccess OnRejoinChannelSuccess;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnProxyConnected OnProxyConnected;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnError OnError;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioQuality OnAudioQuality;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLastmileProbeResult OnLastmileProbeResult;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioVolumeIndication OnAudioVolumeIndication;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLeaveChannel OnLeaveChannel;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRtcStats OnRtcStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioDeviceStateChanged OnAudioDeviceStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioMixingFinished OnAudioMixingFinished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioEffectFinished OnAudioEffectFinished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoDeviceStateChanged OnVideoDeviceStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMediaDeviceChanged OnMediaDeviceChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnNetworkQuality OnNetworkQuality;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnIntraRequestReceived OnIntraRequestReceived;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUplinkNetworkInfoUpdated OnUplinkNetworkInfoUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnDownlinkNetworkInfoUpdated OnDownlinkNetworkInfoUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLastmileQuality OnLastmileQuality;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalVideoFrame OnFirstLocalVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalVideoFramePublished OnFirstLocalVideoFramePublished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoSourceFrameSizeChanged OnVideoSourceFrameSizeChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteVideoDecoded OnFirstRemoteVideoDecoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoSizeChanged OnVideoSizeChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalVideoStateChanged OnLocalVideoStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoStateChanged OnRemoteVideoStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteVideoFrame OnFirstRemoteVideoFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserJoined OnUserJoined;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserOffline OnUserOffline;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserMuteAudio OnUserMuteAudio;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserMuteVideo OnUserMuteVideo;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserEnableVideo OnUserEnableVideo;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserStateChanged OnUserStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserEnableLocalVideo OnUserEnableLocalVideo;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnApiCallExecuted OnApiCallExecuted;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalAudioStats OnLocalAudioStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioStats OnRemoteAudioStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalVideoStats OnLocalVideoStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoStats OnRemoteVideoStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnCameraReady OnCameraReady;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnCameraFocusAreaChanged OnCameraFocusAreaChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnCameraExposureAreaChanged OnCameraExposureAreaChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFacePositionChanged OnFacePositionChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoStopped OnVideoStopped;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioMixingStateChanged OnAudioMixingStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRhythmPlayerStateChanged OnRhythmPlayerStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionLost OnConnectionLost;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionInterrupted OnConnectionInterrupted;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionBanned OnConnectionBanned;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnStreamMessage OnStreamMessage;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnStreamMessageError OnStreamMessageError;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRequestToken OnRequestToken;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnTokenPrivilegeWillExpire OnTokenPrivilegeWillExpire;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalAudioFramePublished OnFirstLocalAudioFramePublished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteAudioFrame OnFirstRemoteAudioFrame;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteAudioDecoded OnFirstRemoteAudioDecoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalAudioStateChanged OnLocalAudioStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioStateChanged OnRemoteAudioStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnActiveSpeaker OnActiveSpeaker;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnContentInspectResult OnContentInspectResult;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSnapshotTaken OnSnapshotTaken;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnClientRoleChanged OnClientRoleChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnClientRoleChangeFailed OnClientRoleChangeFailed;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioDeviceVolumeChanged OnAudioDeviceVolumeChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRtmpStreamingStateChanged OnRtmpStreamingStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRtmpStreamingEvent OnRtmpStreamingEvent;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnTranscodingUpdated OnTranscodingUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioRoutingChanged OnAudioRoutingChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnChannelMediaRelayStateChanged OnChannelMediaRelayStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnChannelMediaRelayEvent OnChannelMediaRelayEvent;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalPublishFallbackToAudioOnly OnLocalPublishFallbackToAudioOnly;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteSubscribeFallbackToAudioOnly OnRemoteSubscribeFallbackToAudioOnly;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioTransportStats OnRemoteAudioTransportStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoTransportStats OnRemoteVideoTransportStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionStateChanged OnConnectionStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnWlAccMessage OnWlAccMessage;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnWlAccStats OnWlAccStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnNetworkTypeChanged OnNetworkTypeChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnEncryptionError OnEncryptionError;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnPermissionError OnPermissionError;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalUserRegistered OnLocalUserRegistered;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserInfoUpdated OnUserInfoUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUploadLogResult OnUploadLogResult;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioSubscribeStateChanged OnAudioSubscribeStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoSubscribeStateChanged OnVideoSubscribeStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioPublishStateChanged OnAudioPublishStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoPublishStateChanged OnVideoPublishStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionEvent OnExtensionEvent;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionStarted OnExtensionStarted;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionStopped OnExtensionStopped;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionError OnExtensionError;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserAccountUpdated OnUserAccountUpdated;

	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;

	void onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;

	void onProxyConnected(const char* channel, agora::rtc::uid_t uid, agora::rtc::PROXY_TYPE proxyType, const char* localProxyIp, int elapsed) override;

	void onError(int err, const char* msg) override;

	void onAudioQuality(agora::rtc::uid_t uid, int quality, unsigned short delay, unsigned short lost) override;

	void onLastmileProbeResult(const agora::rtc::LastmileProbeResult& result) override;

	void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	void onRtcStats(const agora::rtc::RtcStats& stats) override;

	void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;

	void onAudioMixingFinished() override;

	void onAudioEffectFinished(int soundId) override;

	void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;

	void onMediaDeviceChanged(int deviceType) override;

	void onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality) override;

	void onIntraRequestReceived() override;

	void onUplinkNetworkInfoUpdated(const agora::rtc::UplinkNetworkInfo& info) override;

	void onDownlinkNetworkInfoUpdated(const agora::rtc::DownlinkNetworkInfo& info) override;

	void onLastmileQuality(int quality) override;

	void onFirstLocalVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE source, int width, int height, int elapsed) override;

	void onFirstLocalVideoFramePublished(agora::rtc::VIDEO_SOURCE_TYPE source, int elapsed) override;

	void onFirstRemoteVideoDecoded(agora::rtc::uid_t uid, int width, int height, int elapsed) override;

	void onVideoSizeChanged(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation) override;

	void onLocalVideoStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error) override;

	void onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;

	void onFirstRemoteVideoFrame(agora::rtc::uid_t userId, int width, int height, int elapsed) override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

	void onUserMuteAudio(agora::rtc::uid_t uid, bool muted) override;

	void onUserMuteVideo(agora::rtc::uid_t userId, bool muted) override;

	void onUserEnableVideo(agora::rtc::uid_t uid, bool enabled) override;

	void onUserStateChanged(agora::rtc::uid_t uid, uint32_t state) override;

	void onUserEnableLocalVideo(agora::rtc::uid_t uid, bool enabled) override;

	void onApiCallExecuted(int err, const char* api, const char* result) override;

	void onLocalAudioStats(const agora::rtc::LocalAudioStats& stats) override;

	void onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats) override;

	void onLocalVideoStats(agora::rtc::VIDEO_SOURCE_TYPE source, const agora::rtc::LocalVideoStats& stats) override;

	void onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats) override;

	void onCameraReady() override;

	void onCameraFocusAreaChanged(int x, int y, int width, int height) override;

	void onCameraExposureAreaChanged(int x, int y, int width, int height) override;
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	void onFacePositionChanged(int imageWidth, int imageHeight, const agora::rtc::Rectangle* vecRectangle, const int* vecDistance, int numFaces) override;
#endif
	void onVideoStopped() override;

	void onAudioMixingStateChanged(agora::rtc::AUDIO_MIXING_STATE_TYPE state, agora::rtc::AUDIO_MIXING_REASON_TYPE reason) override;

	void onRhythmPlayerStateChanged(agora::rtc::RHYTHM_PLAYER_STATE_TYPE state, agora::rtc::RHYTHM_PLAYER_ERROR_TYPE errorCode) override;

	void onConnectionLost() override;

	void onConnectionInterrupted() override;

	void onConnectionBanned() override;

	void onStreamMessage(agora::rtc::uid_t userId, int streamId, const char* data, size_t length, uint64_t sentTs) override;

	void onStreamMessageError(agora::rtc::uid_t userId, int streamId, int code, int missed, int cached) override;

	void onRequestToken() override;

	void onTokenPrivilegeWillExpire(const char* token) override;

	void onFirstLocalAudioFramePublished(int elapsed) override;

	void onFirstRemoteAudioFrame(agora::rtc::uid_t uid, int elapsed) override;

	void onFirstRemoteAudioDecoded(agora::rtc::uid_t uid, int elapsed) override;

	void onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error) override;

	void onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;

	void onActiveSpeaker(agora::rtc::uid_t userId) override;

	void onContentInspectResult(agora::media::CONTENT_INSPECT_RESULT result) override;

	void onSnapshotTaken(agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode) override;

	void onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole) override;

	void onClientRoleChangeFailed(agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole) override;

	void onAudioDeviceVolumeChanged(agora::rtc::MEDIA_DEVICE_TYPE deviceType, int volume, bool muted) override;

	void onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR_TYPE errCode) override;

	void onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode) override;

	void onTranscodingUpdated() override;

	void onAudioRoutingChanged(int routing) override;

	void onChannelMediaRelayStateChanged(int state, int code) override;

	void onChannelMediaRelayEvent(int code) override;

	void onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) override;

	void onRemoteSubscribeFallbackToAudioOnly(agora::rtc::uid_t uid, bool isFallbackOrRecover) override;

	void onRemoteAudioTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) override;

	void onRemoteVideoTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) override;

	void onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason) override;

	void onWlAccMessage(agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg) override;

	void onWlAccStats(agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats) override;

	void onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type) override;

	void onEncryptionError(agora::rtc::ENCRYPTION_ERROR_TYPE errorType) override;

	void onPermissionError(agora::rtc::PERMISSION_TYPE permissionType) override;

	void onLocalUserRegistered(agora::rtc::uid_t uid, const char* userAccount) override;

	void onUserInfoUpdated(agora::rtc::uid_t uid, const agora::rtc::UserInfo& info) override;

	void onUploadLogResult(const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason) override;

	void onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState) override;

	void onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState) override;

	void onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState) override;

	void onVideoPublishStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState) override;

	void onExtensionEvent(const char* provider, const char* extension, const char* key, const char* value) override;

	void onExtensionStarted(const char* provider, const char* extension) override;

	void onExtensionStopped(const char* provider, const char* extension) override;

	void onExtensionError(const char* provider, const char* extension, int error, const char* message) override;

	void onUserAccountUpdated(agora::rtc::uid_t uid, const char* userAccount) override;


	const char* eventHandlerType() const override;

};



UCLASS(Blueprintable)
class AGORAPLUGIN_API AIMetadataObserver : public AActor, public agora::rtc::IMetadataObserver
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FGetMaxMetadataSize GetMaxMetadataSize;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnReadyToSendMetadata OnReadyToSendMetadata;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMetadataReceived OnMetadataReceived;
	int getMaxMetadataSize() override;

	bool onReadyToSendMetadata(agora::rtc::IMetadataObserver::Metadata& metadata, agora::rtc::VIDEO_SOURCE_TYPE source_type) override;

	void onMetadataReceived(const agora::rtc::IMetadataObserver::Metadata& metadata) override;

};


UCLASS(Blueprintable)
class AGORAPLUGIN_API AIDirectCdnStreamingEventHandler : public AActor, public agora::rtc::IDirectCdnStreamingEventHandler
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnDirectCdnStreamingStateChanged OnDirectCdnStreamingStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnDirectCdnStreamingStats OnDirectCdnStreamingStats;

	void onDirectCdnStreamingStateChanged(agora::rtc::DIRECT_CDN_STREAMING_STATE state, agora::rtc::DIRECT_CDN_STREAMING_ERROR error, const char* message) override;

	void onDirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats& stats) override;

};
