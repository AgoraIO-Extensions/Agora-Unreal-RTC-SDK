//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/include/AgoraHeaderBase.h"
#include "URtcEngineProxyCompatibility.h"
#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandler.h"
#include "AgoraIRtcEngineEventHandlerEx.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJoinChannelSuccessEx, const FRtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRejoinChannelSuccessEx, const FRtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioQualityEx, const FRtcConnection&, connection, int64, remoteUid, int, quality, int, delay, int, lost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioVolumeIndicationEx, const FRtcConnection&, connection, const TArray<FAudioVolumeInfo>&, speakers, int, totalVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLeaveChannelEx, const FRtcConnection&, connection, const FRtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRtcStatsEx, const FRtcConnection&, connection, const FRtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnNetworkQualityEx, const FRtcConnection&, connection, int64, remoteUid, int, txQuality, int, rxQuality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntraRequestReceivedEx, const FRtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstLocalVideoFramePublishedEx, const FRtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnVideoSourceFrameSizeChangedEx, const FRtcConnection&, connection, EVIDEO_SOURCE_TYPE, sourceType, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnFirstRemoteVideoDecodedEx, const FRtcConnection&, connection, int64, remoteUid, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnVideoSizeChangedEx, const FRtcConnection&, connection, EVIDEO_SOURCE_TYPE, sourceType, int64, uid, int, width, int, height, int, rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLocalVideoStateChangedEx, const FRtcConnection&, connection, ELOCAL_VIDEO_STREAM_STATE, state, ELOCAL_VIDEO_STREAM_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteVideoStateChangedEx, const FRtcConnection&, connection, int64, remoteUid, EREMOTE_VIDEO_STATE, state, EREMOTE_VIDEO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnFirstRemoteVideoFrameEx, const FRtcConnection&, connection, int64, remoteUid, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserJoinedEx, const FRtcConnection&, connection, int64, remoteUid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserOfflineEx, const FRtcConnection&, connection, int64, remoteUid, EUSER_OFFLINE_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserMuteAudioEx, const FRtcConnection&, connection, int64, remoteUid, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserMuteVideoEx, const FRtcConnection&, connection, int64, remoteUid, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserEnableVideoEx, const FRtcConnection&, connection, int64, remoteUid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserEnableLocalVideoEx, const FRtcConnection&, connection, int64, remoteUid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserStateChangedEx, const FRtcConnection&, connection, int64, remoteUid, int, state);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalAudioStatsEx, const FRtcConnection&, connection, const FLocalAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteAudioStatsEx, const FRtcConnection&, connection, const FRemoteAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalVideoStatsEx, const FRtcConnection&, connection, const FLocalVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteVideoStatsEx, const FRtcConnection&, connection, const FRemoteVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionLostEx, const FRtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionInterruptedEx, const FRtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionBannedEx, const FRtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnStreamMessageEx, const FRtcConnection&, connection, int64, remoteUid, int, streamId, const FString, data, int64, length, int64, sentTs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnStreamMessageErrorEx, const FRtcConnection&, connection, int64, remoteUid, int, streamId, int, code, int, missed, int, cached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestTokenEx, const FRtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLicenseValidationFailureEx, const FRtcConnection&, connection, ELICENSE_ERROR_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTokenPrivilegeWillExpireEx, const FRtcConnection&, connection, const FString, token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstLocalAudioFramePublishedEx, const FRtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFirstRemoteAudioFrameEx, const FRtcConnection&, connection, int64, userId, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFirstRemoteAudioDecodedEx, const FRtcConnection&, connection, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLocalAudioStateChangedEx, const FRtcConnection&, connection, ELOCAL_AUDIO_STREAM_STATE, state, ELOCAL_AUDIO_STREAM_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteAudioStateChangedEx, const FRtcConnection&, connection, int64, remoteUid, EREMOTE_AUDIO_STATE, state, EREMOTE_AUDIO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveSpeakerEx, const FRtcConnection&, connection, int64, uid);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnClientRoleChangedEx, const FRtcConnection&, connection, ECLIENT_ROLE_TYPE, oldRole, ECLIENT_ROLE_TYPE, newRole, const FClientRoleOptions&, newRoleOptions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnClientRoleChangeFailedEx, const FRtcConnection&, connection, ECLIENT_ROLE_CHANGE_FAILED_REASON, reason, ECLIENT_ROLE_TYPE, currentRole);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteAudioTransportStatsEx, const FRtcConnection&, connection, int64, remoteUid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteVideoTransportStatsEx, const FRtcConnection&, connection, int64, remoteUid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConnectionStateChangedEx, const FRtcConnection&, connection, ECONNECTION_STATE_TYPE, state, ECONNECTION_CHANGED_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnWlAccMessageEx, const FRtcConnection&, connection, EWLACC_MESSAGE_REASON, reason, EWLACC_SUGGEST_ACTION, action, const FString, wlAccMsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWlAccStatsEx, const FRtcConnection&, connection, FWlAccStats, currentStats, FWlAccStats, averageStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNetworkTypeChangedEx, const FRtcConnection&, connection, FENUMWRAP_NETWORK_TYPE, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEncryptionErrorEx, const FRtcConnection&, connection, EENCRYPTION_ERROR_TYPE, errorType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUploadLogResultEx, const FRtcConnection&, connection, const FString, requestId, bool, success, EUPLOAD_ERROR_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserAccountUpdatedEx, const FRtcConnection&, connection, int64, remoteUid, const FString, remoteUserAccount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnSnapshotTakenEx, const FRtcConnection&, connection, int64, uid, const FString, filePath, int, width, int, height, int, errCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnVideoRenderingTracingResultEx, const FRtcConnection&, connection, int64, uid, EMEDIA_TRACE_EVENT, currentEvent, FVideoRenderingTracingInfo, tracingInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSetRtmFlagResultEx, const FRtcConnection &, connection, int, code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnTranscodedStreamLayoutInfoEx, const FRtcConnection & ,connection, int64, uid, int, width, int, height, const TArray<FVideoLayout>&,layoutlist);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAudioMetadataReceivedEx, const FRtcConnection&, connection, int64, uid, FString, metadata, FString, length);

class IRtcEngineEventHandlerExClassWrapper : public agora::rtc::IRtcEngineEventHandlerEx {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIRtcEngineEventHandlerEx : public UObject, public IRtcEngineEventHandlerExClassWrapper
{

	GENERATED_BODY()

public:
	using IRtcEngineEventHandlerEx::eventHandlerType;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnJoinChannelSuccessEx OnJoinChannelSuccessEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRejoinChannelSuccessEx OnRejoinChannelSuccessEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioQualityEx OnAudioQualityEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioVolumeIndicationEx OnAudioVolumeIndicationEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLeaveChannelEx OnLeaveChannelEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRtcStatsEx OnRtcStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnNetworkQualityEx OnNetworkQualityEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnIntraRequestReceivedEx OnIntraRequestReceivedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalVideoFramePublishedEx OnFirstLocalVideoFramePublishedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoSourceFrameSizeChangedEx OnVideoSourceFrameSizeChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteVideoDecodedEx OnFirstRemoteVideoDecodedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoSizeChangedEx OnVideoSizeChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalVideoStateChangedEx OnLocalVideoStateChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoStateChangedEx OnRemoteVideoStateChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteVideoFrameEx OnFirstRemoteVideoFrameEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserJoinedEx OnUserJoinedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserOfflineEx OnUserOfflineEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserMuteAudioEx OnUserMuteAudioEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserMuteVideoEx OnUserMuteVideoEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserEnableVideoEx OnUserEnableVideoEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserEnableLocalVideoEx OnUserEnableLocalVideoEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserStateChangedEx OnUserStateChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalAudioStatsEx OnLocalAudioStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioStatsEx OnRemoteAudioStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalVideoStatsEx OnLocalVideoStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoStatsEx OnRemoteVideoStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionLostEx OnConnectionLostEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionInterruptedEx OnConnectionInterruptedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionBannedEx OnConnectionBannedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnStreamMessageEx OnStreamMessageEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnStreamMessageErrorEx OnStreamMessageErrorEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRequestTokenEx OnRequestTokenEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLicenseValidationFailureEx OnLicenseValidationFailureEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnTokenPrivilegeWillExpireEx OnTokenPrivilegeWillExpireEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalAudioFramePublishedEx OnFirstLocalAudioFramePublishedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteAudioFrameEx OnFirstRemoteAudioFrameEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteAudioDecodedEx OnFirstRemoteAudioDecodedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLocalAudioStateChangedEx OnLocalAudioStateChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioStateChangedEx OnRemoteAudioStateChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnActiveSpeakerEx OnActiveSpeakerEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnClientRoleChangedEx OnClientRoleChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnClientRoleChangeFailedEx OnClientRoleChangeFailedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteAudioTransportStatsEx OnRemoteAudioTransportStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoTransportStatsEx OnRemoteVideoTransportStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnConnectionStateChangedEx OnConnectionStateChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnWlAccMessageEx OnWlAccMessageEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnWlAccStatsEx OnWlAccStatsEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnNetworkTypeChangedEx OnNetworkTypeChangedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnEncryptionErrorEx OnEncryptionErrorEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUploadLogResultEx OnUploadLogResultEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserAccountUpdatedEx OnUserAccountUpdatedEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSnapshotTakenEx OnSnapshotTakenEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoRenderingTracingResultEx OnVideoRenderingTracingResultEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSetRtmFlagResultEx OnSetRtmFlagResultEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnTranscodedStreamLayoutInfoEx OnTranscodedStreamLayoutInfoEx;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioMetadataReceivedEx OnAudioMetadataReceivedEx;

	void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

	void onRejoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

	void onAudioQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int quality, unsigned short delay, unsigned short lost) override;

	void onAudioVolumeIndication(const agora::rtc::RtcConnection& connection, const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

	void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

	void onRtcStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

	void onNetworkQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int txQuality, int rxQuality) override;

	void onIntraRequestReceived(const agora::rtc::RtcConnection& connection) override;

	void onFirstLocalVideoFramePublished(const agora::rtc::RtcConnection& connection, int elapsed) override;

	void onFirstRemoteVideoDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed) override;

	void onVideoSizeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation) override;

	void onLocalVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_REASON reason) override;

	void onRemoteVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;

	void onFirstRemoteVideoFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed) override;

	void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

	void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

	void onUserMuteAudio(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted) override;

	void onUserMuteVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted) override;

	void onUserEnableVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled) override;

	void onUserEnableLocalVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled) override;

	void onUserStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, uint32_t state) override;

	void onLocalAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalAudioStats& stats) override;

	void onRemoteAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteAudioStats& stats) override;

	void onLocalVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalVideoStats& stats) override;

	void onRemoteVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteVideoStats& stats) override;

	void onConnectionLost(const agora::rtc::RtcConnection& connection) override;

	void onConnectionInterrupted(const agora::rtc::RtcConnection& connection) override;

	void onConnectionBanned(const agora::rtc::RtcConnection& connection) override;

	void onStreamMessage(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, const char* data, size_t length, uint64_t sentTs) override;

	void onStreamMessageError(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, int code, int missed, int cached) override;

	void onRequestToken(const agora::rtc::RtcConnection& connection) override;

	void onLicenseValidationFailure(const agora::rtc::RtcConnection& connection, agora::LICENSE_ERROR_TYPE reason) override;

	void onTokenPrivilegeWillExpire(const agora::rtc::RtcConnection& connection, const char* token) override;

	void onFirstLocalAudioFramePublished(const agora::rtc::RtcConnection& connection, int elapsed) override;

	void onFirstRemoteAudioFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t userId, int elapsed) override;

	void onFirstRemoteAudioDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, int elapsed) override;

	void onLocalAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_REASON reason)	override;

	void onRemoteAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;

	void onActiveSpeaker(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid) override;

	void onClientRoleChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole, const agora::rtc::ClientRoleOptions& newRoleOptions) override;

	void onClientRoleChangeFailed(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole) override;

	void onRemoteAudioTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) override;

	void onRemoteVideoTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) override;

	void onConnectionStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason) override;

	void onWlAccMessage(const agora::rtc::RtcConnection& connection, agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg) override;

	void onWlAccStats(const agora::rtc::RtcConnection& connection, agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats) override;

	void onNetworkTypeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::NETWORK_TYPE type) override;

	void onEncryptionError(const agora::rtc::RtcConnection& connection, agora::rtc::ENCRYPTION_ERROR_TYPE errorType) override;

	void onUploadLogResult(const agora::rtc::RtcConnection& connection, const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason) override;

	void onUserAccountUpdated(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, const char* remoteUserAccount) override;

	void onSnapshotTaken(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode) override;

	void onVideoRenderingTracingResult(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, agora::rtc::MEDIA_TRACE_EVENT currentEvent, agora::rtc::VideoRenderingTracingInfo tracingInfo) override;

	void onSetRtmFlagResult(const agora::rtc::RtcConnection& connection, int code)override;

	void onTranscodedStreamLayoutInfo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, int width, int height, int layoutCount, const agora::VideoLayout* layoutlist) override;

	void onAudioMetadataReceived(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, const char* metadata, size_t length) override;
};