//  Copyright (c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "AgoraBPuDataTypes.h"
#include "AgoraBPuIRtcEngineEventHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnJoinChannelSuccess, const FString&, channel, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaveChannel, const FUABT_RtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserJoined, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserOffline, int64, uid, EUABT_USER_OFFLINE_REASON_TYPE, reason);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRejoinChannelSuccess, const FString&, channel, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnProxyConnected, const FString&, channel, int64, uid, EUABT_PROXY_TYPE, proxyType, const FString&, localProxyIp, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnError, int, err, const FString&, msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAudioQuality, int64, uid, int, quality, int, delay, int, lost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLastmileProbeResult, const FUABT_LastmileProbeResult&, result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioVolumeIndication, const TArray<FUABT_AudioVolumeInfo>&,speakers, int, totalVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRtcStats, const FUABT_RtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioDeviceStateChanged, const FString&, deviceId, int, deviceType, int, deviceState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioMixingPositionChanged, int64, position);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioMixingFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioEffectFinished, int, soundId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVideoDeviceStateChanged, const FString&, deviceId, int, deviceType, int, deviceState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNetworkQuality, int64, uid, int, txQuality, int, rxQuality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIntraRequestReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUplinkNetworkInfoUpdated, const FUABT_UplinkNetworkInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDownlinkNetworkInfoUpdated, const FUABT_DownlinkNetworkInfo&, info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLastmileQuality, int, quality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFirstLocalVideoFrame, EUABT_VIDEO_SOURCE_TYPE, source, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstLocalVideoFramePublished, EUABT_VIDEO_SOURCE_TYPE, source, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFirstRemoteVideoDecoded, int64, uid, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnVideoSizeChanged, EUABT_VIDEO_SOURCE_TYPE, sourceType, int64, uid, int, width, int, height, int, rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLocalVideoStateChanged, EUABT_VIDEO_SOURCE_TYPE, source, EUABT_LOCAL_VIDEO_STREAM_STATE, state, EUABT_LOCAL_VIDEO_STREAM_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteVideoStateChanged, int64, uid, EUABT_REMOTE_VIDEO_STATE, state, EUABT_REMOTE_VIDEO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFirstRemoteVideoFrame, int64, userId, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserMuteAudio, int64, uid, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserMuteVideo, int64, userId, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserEnableVideo, int64, uid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserStateChanged, int64, uid, EUABT_REMOTE_USER_STATE, state);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserEnableLocalVideo, int64, uid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalAudioStats, const FUABT_LocalAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoteAudioStats, const FUABT_RemoteAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalVideoStats, EUABT_VIDEO_SOURCE_TYPE, source, const FUABT_LocalVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoteVideoStats, const FUABT_RemoteVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCameraFocusAreaChanged, int, x, int, y, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCameraExposureAreaChanged, int, x, int, y, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnFacePositionChanged, int,imageWidth, int,imageHeight, const TArray<FUABT_Rectangle>&, vecRectangle, const TArray<int>& ,vecDistance, int,numFaces);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioMixingStateChanged, EUABT_AUDIO_MIXING_STATE_TYPE, state, EUABT_AUDIO_MIXING_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRhythmPlayerStateChanged, EUABT_RHYTHM_PLAYER_STATE_TYPE, state, EUABT_RHYTHM_PLAYER_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionInterrupted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionBanned);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStreamMessage, int64,uid, int ,streamId, const FString& ,data, int, length, int64, sentTs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStreamMessageError, int64, uid, int, streamId, int, code, int, missed, int, cached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestToken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTokenPrivilegeWillExpire, const FString&, token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLicenseValidationFailure, EUABT_LICENSE_ERROR_TYPE, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFirstLocalAudioFramePublished, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstRemoteAudioFrame, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstRemoteAudioDecoded, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalAudioStateChanged, EUABT_LOCAL_AUDIO_STREAM_STATE, state, EUABT_LOCAL_AUDIO_STREAM_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteAudioStateChanged, int64, uid, EUABT_REMOTE_AUDIO_STATE, state, EUABT_REMOTE_AUDIO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveSpeaker, int64, userId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentInspectResult, EUABT_CONTENT_INSPECT_RESULT, result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSnapshotTaken, int64, uid, const FString&, filePath, int, width, int, height, int, errCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnClientRoleChanged, EUABT_CLIENT_ROLE_TYPE,oldRole, EUABT_CLIENT_ROLE_TYPE, newRole, const FUABT_ClientRoleOptions& ,newRoleOptions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClientRoleChangeFailed, EUABT_CLIENT_ROLE_CHANGE_FAILED_REASON, reason, EUABT_CLIENT_ROLE_TYPE, currentRole);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioDeviceVolumeChanged, EUABT_MEDIA_DEVICE_TYPE, deviceType, int, volume, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRtmpStreamingStateChanged, const FString&, url, EUABT_RTMP_STREAM_PUBLISH_STATE, state, EUABT_RTMP_STREAM_PUBLISH_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRtmpStreamingEvent, const FString&, url, EUABT_RTMP_STREAMING_EVENT, eventCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTranscodingUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioRoutingChanged, int, routing);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelMediaRelayStateChanged, int, state, int, code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalPublishFallbackToAudioOnly, bool, isFallbackOrRecover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteSubscribeFallbackToAudioOnly, int64, uid, bool, isFallbackOrRecover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteAudioTransportStats, int64, uid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteVideoTransportStats, int64, uid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConnectionStateChanged, EUABT_CONNECTION_STATE_TYPE, state, EUABT_CONNECTION_CHANGED_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWlAccMessage, EUABT_WLACC_MESSAGE_REASON, reason, EUABT_WLACC_SUGGEST_ACTION, action, const FString&, wlAccMsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWlAccStats, const FUABT_WlAccStats&, currentStats, const FUABT_WlAccStats&, averageStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNetworkTypeChanged, EUABT_NETWORK_TYPE, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEncryptionError, EUABT_ENCRYPTION_ERROR_TYPE, errorType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPermissionError, EUABT_PERMISSION_TYPE, permissionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalUserRegistered, int64, uid, const FString&, userAccount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserInfoUpdated, int64, uid, const FUABT_UserInfo&, info);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserAccountUpdated, int64, uid, const FString&, userAccount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVideoRenderingTracingResult, int64, uid, EUABT_MEDIA_TRACE_EVENT, currentEvent, const FUABT_VideoRenderingTracingInfo &, tracingInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalVideoTranscoderError, const FUABT_TranscodingVideoStream&, stream, EUABT_VIDEO_TRANSCODER_ERROR, error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUploadLogResult, const FString&, requestId, bool, success, EUABT_UPLOAD_ERROR_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSubscribeStateChanged, const FString&, channel, int64, uid, EUABT_STREAM_SUBSCRIBE_STATE, oldState, EUABT_STREAM_SUBSCRIBE_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnVideoSubscribeStateChanged, const FString&, channel, int64, uid, EUABT_STREAM_SUBSCRIBE_STATE, oldState, EUABT_STREAM_SUBSCRIBE_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAudioPublishStateChanged, const FString&, channel, EUABT_STREAM_PUBLISH_STATE, oldState, EUABT_STREAM_PUBLISH_STATE, newState, int, elapseSinceLastState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnVideoPublishStateChanged, EUABT_VIDEO_SOURCE_TYPE, source, const FString&, channel, EUABT_STREAM_PUBLISH_STATE, oldState, EUABT_STREAM_PUBLISH_STATE, newState, int, elapseSinceLastState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnTranscodedStreamLayoutInfo, int64, uid, int, width, int, height, int, layoutCount,const TArray<FUABT_VideoLayout> &, layoutlist);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioMetadataReceived, int64, uid, const FString&, metadata, const FString&, length);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnExtensionEventWithContext, const FUABT_ExtensionContext&, context, const FString &, key, const FString &, value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtensionStartedWithContext, const FUABT_ExtensionContext& ,context);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtensionStoppedWithContext, const FUABT_ExtensionContext&, context);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnExtensionErrorWithContext, const FUABT_ExtensionContext&, context, int, error , const FString&, message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetRtmFlagResult, int, code);


class IRtcEngineEventHandlerClassWrapper : public agora::rtc::IRtcEngineEventHandler {};

using namespace agora;
using namespace agora::rtc;

// this is a native event handler managed in cpp
UCLASS(BlueprintType)
class AGORAPLUGIN_API UAgoraBPuIRtcEngineEventHandler : public UObject, public IRtcEngineEventHandlerClassWrapper
{
	GENERATED_BODY()

public:
	using IRtcEngineEventHandler::eventHandlerType;
	//using IRtcEngineEventHandler::onJoinChannelSuccess;
	//using IRtcEngineEventHandler::onLeaveChannel;
	//using IRtcEngineEventHandler::onUserJoined;
	//using IRtcEngineEventHandler::onUserOffline;
/*

	using IRtcEngineEventHandler::onRejoinChannelSuccess;
	using IRtcEngineEventHandler::onAudioQuality;
	using IRtcEngineEventHandler::onAudioVolumeIndication;
	using IRtcEngineEventHandler::onRtcStats;
	using IRtcEngineEventHandler::onNetworkQuality;
	using IRtcEngineEventHandler::onIntraRequestReceived;
	using IRtcEngineEventHandler::onFirstLocalVideoFramePublished;
	using IRtcEngineEventHandler::onFirstRemoteVideoDecoded;
	using IRtcEngineEventHandler::onVideoSizeChanged;
	using IRtcEngineEventHandler::onLocalVideoStateChanged;
	using IRtcEngineEventHandler::onRemoteVideoStateChanged;
	using IRtcEngineEventHandler::onFirstRemoteVideoFrame;
	using IRtcEngineEventHandler::onUserMuteAudio;
	using IRtcEngineEventHandler::onUserMuteVideo;
	using IRtcEngineEventHandler::onUserEnableVideo;
	using IRtcEngineEventHandler::onUserEnableLocalVideo;
	using IRtcEngineEventHandler::onUserStateChanged;
	using IRtcEngineEventHandler::onLocalAudioStats;
	using IRtcEngineEventHandler::onRemoteAudioStats;
	using IRtcEngineEventHandler::onLocalVideoStats;
	using IRtcEngineEventHandler::onRemoteVideoStats;
	using IRtcEngineEventHandler::onConnectionLost;
	using IRtcEngineEventHandler::onConnectionInterrupted;
	using IRtcEngineEventHandler::onConnectionBanned;
	using IRtcEngineEventHandler::onStreamMessage;
	using IRtcEngineEventHandler::onStreamMessageError;
	using IRtcEngineEventHandler::onRequestToken;
	using IRtcEngineEventHandler::onTokenPrivilegeWillExpire;
	using IRtcEngineEventHandler::onLicenseValidationFailure;
	using IRtcEngineEventHandler::onFirstLocalAudioFramePublished;
	using IRtcEngineEventHandler::onFirstRemoteAudioFrame;
	using IRtcEngineEventHandler::onFirstRemoteAudioDecoded;
	using IRtcEngineEventHandler::onLocalAudioStateChanged;
	using IRtcEngineEventHandler::onRemoteAudioStateChanged;
	using IRtcEngineEventHandler::onActiveSpeaker;
	using IRtcEngineEventHandler::onClientRoleChanged;
	using IRtcEngineEventHandler::onClientRoleChangeFailed;
	using IRtcEngineEventHandler::onRemoteAudioTransportStats;
	using IRtcEngineEventHandler::onRemoteVideoTransportStats;
	using IRtcEngineEventHandler::onConnectionStateChanged;
	using IRtcEngineEventHandler::onWlAccMessage;
	using IRtcEngineEventHandler::onWlAccStats;
	using IRtcEngineEventHandler::onNetworkTypeChanged;
	using IRtcEngineEventHandler::onEncryptionError;
	using IRtcEngineEventHandler::onUploadLogResult;
	using IRtcEngineEventHandler::onUserInfoUpdated;
	using IRtcEngineEventHandler::onUserAccountUpdated;
	using IRtcEngineEventHandler::onAudioSubscribeStateChanged;
	using IRtcEngineEventHandler::onVideoSubscribeStateChanged;
	using IRtcEngineEventHandler::onAudioPublishStateChanged;
	using IRtcEngineEventHandler::onVideoPublishStateChanged;
	using IRtcEngineEventHandler::onSnapshotTaken;
	using IRtcEngineEventHandler::onVideoRenderingTracingResult;
	using IRtcEngineEventHandler::onSetRtmFlagResult;
	using IRtcEngineEventHandler::onTranscodedStreamLayoutInfo;
	using IRtcEngineEventHandler::onAudioMetadataReceived
	
*/;
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnJoinChannelSuccess OnJoinChannelSuccess;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLeaveChannel OnLeaveChannel;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserJoined OnUserJoined;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserOffline OnUserOffline;

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
	FOnRtcStats OnRtcStats;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioDeviceStateChanged OnAudioDeviceStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioMixingPositionChanged OnAudioMixingPositionChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioMixingFinished OnAudioMixingFinished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioEffectFinished OnAudioEffectFinished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoDeviceStateChanged OnVideoDeviceStateChanged;
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
	FOnLicenseValidationFailure OnLicenseValidationFailure;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalAudioFramePublished OnFirstLocalAudioFramePublished;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteAudioDecoded OnFirstRemoteAudioDecoded;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteAudioFrame OnFirstRemoteAudioFrame;
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
	FOnUserAccountUpdated OnUserAccountUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoRenderingTracingResult OnVideoRenderingTracingResult;
	
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalVideoTranscoderError OnLocalVideoTranscoderError;


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
	FOnTranscodedStreamLayoutInfo OnTranscodedStreamLayoutInfo;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioMetadataReceived OnAudioMetadataReceived;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionEventWithContext OnExtensionEventWithContext;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionStartedWithContext OnExtensionStartedWithContext;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionStoppedWithContext OnExtensionStoppedWithContext;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnExtensionErrorWithContext OnExtensionErrorWithContext;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSetRtmFlagResult OnSetRtmFlagResult;
	
	virtual void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
	virtual void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	virtual void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	virtual void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;


	virtual void onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;

	virtual void onProxyConnected(const char* channel, agora::rtc::uid_t uid, agora::rtc::PROXY_TYPE proxyType, const char* localProxyIp, int elapsed) override;

	virtual void onError(int err, const char* msg) override;


	virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) __deprecated override;


	virtual void onLastmileProbeResult(const LastmileProbeResult& result) override;

	virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber,
		int totalVolume) override;

	virtual void onRtcStats(const RtcStats& stats) override;


	virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;


	virtual void onAudioMixingPositionChanged(int64_t position) override;


	virtual void onAudioMixingFinished() __deprecated override;


	virtual void onAudioEffectFinished(int soundId) override;


	virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;


	virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) override;

	virtual void onIntraRequestReceived() override;

	virtual void onUplinkNetworkInfoUpdated(const UplinkNetworkInfo& info) override;


	virtual void onDownlinkNetworkInfoUpdated(const DownlinkNetworkInfo& info) override;


	virtual void onLastmileQuality(int quality) override;


	virtual void onFirstLocalVideoFrame(VIDEO_SOURCE_TYPE source, int width, int height, int elapsed) override;

	virtual void onFirstLocalVideoFramePublished(VIDEO_SOURCE_TYPE source, int elapsed) override;


	virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) __deprecated override;


	virtual void onVideoSizeChanged(VIDEO_SOURCE_TYPE sourceType, uid_t uid, int width, int height, int rotation) override;


	virtual void onLocalVideoStateChanged(VIDEO_SOURCE_TYPE source, LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_REASON reason) override;


	virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;


	virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) override;


	virtual void onUserMuteAudio(uid_t uid, bool muted) override;


	virtual void onUserMuteVideo(uid_t uid, bool muted) override;


	virtual void onUserEnableVideo(uid_t uid, bool enabled) __deprecated override;


	virtual void onUserStateChanged(uid_t uid, REMOTE_USER_STATE state) override;


	virtual void onUserEnableLocalVideo(uid_t uid, bool enabled) __deprecated override;


	

	virtual void onRemoteAudioStats(const RemoteAudioStats& stats) override;

	virtual void onLocalAudioStats(const LocalAudioStats& stats) override;

	virtual void onLocalVideoStats(VIDEO_SOURCE_TYPE source, const LocalVideoStats& stats) override;


	virtual void onRemoteVideoStats(const RemoteVideoStats& stats) override;


	virtual void onCameraReady() __deprecated override;

	virtual void onCameraFocusAreaChanged(int x, int y, int width, int height) override;


	virtual void onCameraExposureAreaChanged(int x, int y, int width, int height) override;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)

	virtual void onFacePositionChanged(int imageWidth, int imageHeight,
		const Rectangle* vecRectangle, const int* vecDistance,
		int numFaces) override;

#endif


	virtual void onVideoStopped() __deprecated override;

	virtual void onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_REASON_TYPE reason) override;


	virtual void onRhythmPlayerStateChanged(RHYTHM_PLAYER_STATE_TYPE state, RHYTHM_PLAYER_REASON reason) override;

	virtual void onConnectionLost() override;

	virtual void onConnectionInterrupted() __deprecated override;

	virtual void onConnectionBanned() __deprecated override;

	virtual void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length, uint64_t sentTs) override;

	virtual void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) override;

	virtual void onRequestToken() override;

	virtual void onTokenPrivilegeWillExpire(const char* token) override;


	virtual void onLicenseValidationFailure(LICENSE_ERROR_TYPE error) override;

	virtual void onFirstLocalAudioFramePublished(int elapsed) override;

	virtual void onFirstRemoteAudioDecoded(uid_t uid, int elapsed) __deprecated override;

	virtual void onFirstRemoteAudioFrame(uid_t uid, int elapsed) __deprecated override;

	virtual void onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_REASON reason) override;

	virtual void onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;


	virtual void onActiveSpeaker(uid_t uid) override;

	virtual void onContentInspectResult(media::CONTENT_INSPECT_RESULT result) override;


	virtual void onSnapshotTaken(uid_t uid, const char* filePath, int width, int height, int errCode) override;

	virtual void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole, const ClientRoleOptions& newRoleOptions) override;


	virtual void onClientRoleChangeFailed(CLIENT_ROLE_CHANGE_FAILED_REASON reason, CLIENT_ROLE_TYPE currentRole) override;

	virtual void onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted) override;

	virtual void onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_REASON reason) override;

	virtual void onRtmpStreamingEvent(const char* url, RTMP_STREAMING_EVENT eventCode) override;


	virtual void onTranscodingUpdated() override;

	virtual void onAudioRoutingChanged(int routing) override;


	virtual void onChannelMediaRelayStateChanged(int state, int code) override;

	virtual void onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) override;

	virtual void onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover) override;

	virtual void onRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) __deprecated override;

	virtual void onRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) __deprecated override;


	virtual void onConnectionStateChanged(
		CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason) override;

	virtual void onWlAccMessage(WLACC_MESSAGE_REASON reason, WLACC_SUGGEST_ACTION action, const char* wlAccMsg) override;


	virtual void onWlAccStats(const WlAccStats& currentStats, const WlAccStats& averageStats) override;

	virtual void onNetworkTypeChanged(NETWORK_TYPE type) override;

	virtual void onEncryptionError(ENCRYPTION_ERROR_TYPE errorType) override;

	virtual void onPermissionError(PERMISSION_TYPE permissionType) override;

	virtual void onLocalUserRegistered(uid_t uid, const char* userAccount) override;

	virtual void onUserInfoUpdated(uid_t uid, const agora::rtc::UserInfo& info) override;

	virtual void onUserAccountUpdated(uid_t uid, const char* userAccount) override;

	virtual void onVideoRenderingTracingResult(uid_t uid, MEDIA_TRACE_EVENT currentEvent, VideoRenderingTracingInfo tracingInfo) override;

	virtual void onLocalVideoTranscoderError(const TranscodingVideoStream& stream, VIDEO_TRANSCODER_ERROR error) override;

	virtual void onUploadLogResult(const char* requestId, bool success, UPLOAD_ERROR_REASON reason) override;

	virtual void onAudioSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState) override;

	virtual void onVideoSubscribeStateChanged(const char* channel, uid_t uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState) override;

	virtual void onAudioPublishStateChanged(const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState) override;

	virtual void onVideoPublishStateChanged(VIDEO_SOURCE_TYPE source, const char* channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, int elapseSinceLastState) override;

	virtual void onTranscodedStreamLayoutInfo(uid_t uid, int width, int height, int layoutCount, const VideoLayout* layoutlist) override;

	virtual void onAudioMetadataReceived(uid_t uid, const char* metadata, size_t length) override;

	virtual void onExtensionEventWithContext(const ExtensionContext& context, const char* key, const char* value) override;

	virtual void onExtensionStartedWithContext(const ExtensionContext& context) override;

	virtual void onExtensionStoppedWithContext(const ExtensionContext& context) override;

	virtual void onExtensionErrorWithContext(const ExtensionContext& context, int error, const char* message) override;

	virtual void onSetRtmFlagResult(int code) override;




	// You could add multiple executors to the target handler
	UFUNCTION(BlueprintCallable, Category = "Agora|Event")
	void AddBlueprintCallbackExecutor(UAgoraBPuIRtcEngineEventHandlerCBExecutor* Executor);

	UFUNCTION(BlueprintCallable, Category = "Agora|Event")
	void RemoveAllBlueprintCallbackExecutors();

private:
	EAgoraBPuEventHandlerType Type = EAgoraBPuEventHandlerType::EventHandler;
};



// this is a blueprint callback executor which you could add to the target handler
UCLASS(Blueprintable,Meta = (ShowWorldContextPin))
class AGORAPLUGIN_API UAgoraBPuIRtcEngineEventHandlerCBExecutor : public UObject {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnJoinChannelSuccess(const FString& Channel, int64 Uid, int Elapsed);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLeaveChannel(const FUABT_RtcStats& stats);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserJoined(int64 uid, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserOffline(int64 uid, EUABT_USER_OFFLINE_REASON_TYPE reason);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRejoinChannelSuccess(const FString& channel, int64 uid, int elapsed);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnProxyConnected(const FString& channel, int64 uid, EUABT_PROXY_TYPE proxyType, const FString& localProxyIp, int elapsed);

	
	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnError(int error, const FString& msg);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioQuality(int64 uid, int quality, int delay, int lost);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLastmileProbeResult(const FUABT_LastmileProbeResult& result);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioVolumeIndication(const TArray<FUABT_AudioVolumeInfo>& speakers, int totalVolume);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRtcStats(const FUABT_RtcStats& stats);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioDeviceStateChanged(const FString& deviceId, int deviceType, int deviceState);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioMixingPositionChanged(int64 position);

	
	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioMixingFinished();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioEffectFinished(int soundId);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnVideoDeviceStateChanged(const FString& deviceId, int deviceType, int deviceState);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnNetworkQuality(int64 uid, int txQuality, int rxQuality);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnIntraRequestReceived();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUplinkNetworkInfoUpdated(const FUABT_UplinkNetworkInfo& info);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnDownlinkNetworkInfoUpdated(const FUABT_DownlinkNetworkInfo& info);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLastmileQuality(int quality);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstLocalVideoFrame(EUABT_VIDEO_SOURCE_TYPE source, int width, int height, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstLocalVideoFramePublished(EUABT_VIDEO_SOURCE_TYPE source, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstRemoteVideoDecoded(int64 uid, int width, int height, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnVideoSizeChanged(EUABT_VIDEO_SOURCE_TYPE sourceType, int64 uid, int width, int height, int rotation);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalVideoStateChanged(EUABT_VIDEO_SOURCE_TYPE source, EUABT_LOCAL_VIDEO_STREAM_STATE state, EUABT_LOCAL_VIDEO_STREAM_REASON reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteVideoStateChanged(int64 uid, EUABT_REMOTE_VIDEO_STATE state, EUABT_REMOTE_VIDEO_STATE_REASON reason, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstRemoteVideoFrame(int64 uid, int width, int height, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserMuteAudio(int64 uid, bool muted);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserMuteVideo(int64 uid, bool muted);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserEnableVideo(int64 uid, bool enabled);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserStateChanged(int64 uid, EUABT_REMOTE_USER_STATE state);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserEnableLocalVideo(int64 uid, bool enabled);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteAudioStats(const FUABT_RemoteAudioStats& stats);
	

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalAudioStats(const FUABT_LocalAudioStats& stats);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalVideoStats(EUABT_VIDEO_SOURCE_TYPE source, const FUABT_LocalVideoStats& stats);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteVideoStats(const FUABT_RemoteVideoStats& stats);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnCameraReady();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnCameraFocusAreaChanged(int x, int y, int width, int height);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnCameraExposureAreaChanged(int x, int y, int width, int height);

	
	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFacePositionChanged(int imageWidth, int imageHeight, const TArray<FUABT_Rectangle>& vecRectangle, const TArray<int>& vecDistance, int numFaces);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnVideoStopped();

	
	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioMixingStateChanged(EUABT_AUDIO_MIXING_STATE_TYPE state, EUABT_AUDIO_MIXING_REASON_TYPE reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRhythmPlayerStateChanged(EUABT_RHYTHM_PLAYER_STATE_TYPE state, EUABT_RHYTHM_PLAYER_REASON reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnConnectionLost();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnConnectionInterrupted();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnConnectionBanned();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnStreamMessage(int64 uid, int streamId, const FString& data, int length, int64 sentTs);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnStreamMessageError(int64 uid, int streamId, int code, int missed, int cached);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRequestToken();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnTokenPrivilegeWillExpire(const FString& token);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLicenseValidationFailure(EUABT_LICENSE_ERROR_TYPE error);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstLocalAudioFramePublished(int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstRemoteAudioDecoded(int64 uid, int elapsed);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnFirstRemoteAudioFrame(int64 uid, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalAudioStateChanged(EUABT_LOCAL_AUDIO_STREAM_STATE state, EUABT_LOCAL_AUDIO_STREAM_REASON reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteAudioStateChanged(int64 uid, EUABT_REMOTE_AUDIO_STATE state, EUABT_REMOTE_AUDIO_STATE_REASON reason, int elapsed);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnActiveSpeaker(int64 uid);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnContentInspectResult(EUABT_CONTENT_INSPECT_RESULT result);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnSnapshotTaken(int64 uid, const FString& filePath, int width, int height, int errCode);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnClientRoleChanged(EUABT_CLIENT_ROLE_TYPE oldRole, EUABT_CLIENT_ROLE_TYPE newRole, const FUABT_ClientRoleOptions& newRoleOptions);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnClientRoleChangeFailed(EUABT_CLIENT_ROLE_CHANGE_FAILED_REASON reason, EUABT_CLIENT_ROLE_TYPE currentRole);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioDeviceVolumeChanged(EUABT_MEDIA_DEVICE_TYPE deviceType, int volume, bool muted);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRtmpStreamingStateChanged(const FString& url, EUABT_RTMP_STREAM_PUBLISH_STATE state, EUABT_RTMP_STREAM_PUBLISH_REASON reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRtmpStreamingEvent(const FString& url, EUABT_RTMP_STREAMING_EVENT eventCode);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnTranscodingUpdated();


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioRoutingChanged(int routing);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnChannelMediaRelayStateChanged(int state, int code);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteSubscribeFallbackToAudioOnly(int64 uid, bool isFallbackOrRecover);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteAudioTransportStats(int64 uid, int delay, int lost, int rxKBitRate);

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnRemoteVideoTransportStats(int64 uid, int delay, int lost, int rxKBitRate);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnConnectionStateChanged(EUABT_CONNECTION_STATE_TYPE state, EUABT_CONNECTION_CHANGED_REASON_TYPE reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnWlAccMessage(EUABT_WLACC_MESSAGE_REASON reason, EUABT_WLACC_SUGGEST_ACTION action, const FString& wlAccMsg);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnWlAccStats(const FUABT_WlAccStats& currentStats, const FUABT_WlAccStats& averageStats);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnNetworkTypeChanged(EUABT_NETWORK_TYPE type);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnEncryptionError(EUABT_ENCRYPTION_ERROR_TYPE errorType);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnPermissionError(EUABT_PERMISSION_TYPE permissionType);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalUserRegistered(int64 uid, const FString& userAccount);
	

	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserInfoUpdated(int64 uid, const FUABT_UserInfo& info);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUserAccountUpdated(int64 uid, const FString& userAccount);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnVideoRenderingTracingResult(int64 uid, EUABT_MEDIA_TRACE_EVENT currentEvent, const FUABT_VideoRenderingTracingInfo& tracingInfo);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnLocalVideoTranscoderError(const FUABT_TranscodingVideoStream& stream, EUABT_VIDEO_TRANSCODER_ERROR error);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnUploadLogResult(const FString& requestId, bool success, EUABT_UPLOAD_ERROR_REASON reason);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioSubscribeStateChanged(const FString& channel, int64 uid, EUABT_STREAM_SUBSCRIBE_STATE oldState, EUABT_STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnVideoSubscribeStateChanged(const FString& channel, int64 uid, EUABT_STREAM_SUBSCRIBE_STATE oldState, EUABT_STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioPublishStateChanged(const FString& channel, EUABT_STREAM_PUBLISH_STATE oldState, EUABT_STREAM_PUBLISH_STATE newState, int elapseSinceLastState);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnVideoPublishStateChanged(EUABT_VIDEO_SOURCE_TYPE source, const FString& channel, EUABT_STREAM_PUBLISH_STATE oldState, EUABT_STREAM_PUBLISH_STATE newState, int elapseSinceLastState);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnTranscodedStreamLayoutInfo(int64 uid, int width, int height, int layoutCount, const TArray<FUABT_VideoLayout>& layoutlist);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnAudioMetadataReceived(int64 uid, const FString& metadata, const FString& length);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnExtensionEventWithContext(const FUABT_ExtensionContext& context, const FString& key, const FString& value);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnExtensionStartedWithContext(const FUABT_ExtensionContext& context);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnExtensionStoppedWithContext(const FUABT_ExtensionContext& context);



	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnExtensionErrorWithContext(const FUABT_ExtensionContext& context, int error, const FString& message);


	UFUNCTION(BlueprintNativeEvent, Category = "Agora|Event")
	void OnSetRtmFlagResult(int code);

};