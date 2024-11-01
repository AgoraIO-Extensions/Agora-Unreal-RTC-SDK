//  Copyright (c) 2024 Agora.io. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "AgoraPluginInterface.h"
#include "AgoraBPuDataTypes.h"
#include "AgoraBPuIRtcEngineEventHandlerEx.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJoinChannelSuccessEx, const FUABT_RtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLeaveChannelEx, const FUABT_RtcConnection&, connection, const FUABT_RtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserJoinedEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserOfflineEx, const FUABT_RtcConnection&, connection, int64, remoteUid, EUABT_USER_OFFLINE_REASON_TYPE, reason);



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRejoinChannelSuccessEx, const FUABT_RtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioQualityEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, quality, int, delay, int, lost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioVolumeIndicationEx, const FUABT_RtcConnection&, connection, const TArray<FUABT_AudioVolumeInfo>&, speakers, int, totalVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRtcStatsEx, const FUABT_RtcConnection&, connection, const FUABT_RtcStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnNetworkQualityEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, txQuality, int, rxQuality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntraRequestReceivedEx, const FUABT_RtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstLocalVideoFramePublishedEx, const FUABT_RtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnVideoSourceFrameSizeChangedEx, const FUABT_RtcConnection&, connection, EUABT_VIDEO_SOURCE_TYPE, sourceType, int, width, int, height);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnFirstRemoteVideoDecodedEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, width, int, height, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnVideoSizeChangedEx, const FUABT_RtcConnection&, connection, EUABT_VIDEO_SOURCE_TYPE, sourceType, int64, uid, int, width, int, height, int, rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteVideoStateChangedEx, const FUABT_RtcConnection&, connection, int64, remoteUid, EUABT_REMOTE_VIDEO_STATE, state, EUABT_REMOTE_VIDEO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnFirstRemoteVideoFrameEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, width, int, height, int, elapsed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserMuteAudioEx, const FUABT_RtcConnection&, connection, int64, remoteUid, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserMuteVideoEx, const FUABT_RtcConnection&, connection, int64, remoteUid, bool, muted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserEnableVideoEx, const FUABT_RtcConnection&, connection, int64, remoteUid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserEnableLocalVideoEx, const FUABT_RtcConnection&, connection, int64, remoteUid, bool, enabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserStateChangedEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, state);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalAudioStatsEx, const FUABT_RtcConnection&, connection, const FUABT_LocalAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteAudioStatsEx, const FUABT_RtcConnection&, connection, const FUABT_RemoteAudioStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalVideoStatsEx, const FUABT_RtcConnection&, connection, const FUABT_LocalVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteVideoStatsEx, const FUABT_RtcConnection&, connection, const FUABT_RemoteVideoStats&, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionLostEx, const FUABT_RtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionInterruptedEx, const FUABT_RtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionBannedEx, const FUABT_RtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnStreamMessageEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, streamId, const FString &, data, int64, length, int64, sentTs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnStreamMessageErrorEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, streamId, int, code, int, missed, int, cached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestTokenEx, const FUABT_RtcConnection&, connection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLicenseValidationFailureEx, const FUABT_RtcConnection&, connection, EUABT_LICENSE_ERROR_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTokenPrivilegeWillExpireEx, const FUABT_RtcConnection&, connection, const FString &, token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFirstLocalAudioFramePublishedEx, const FUABT_RtcConnection&, connection, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFirstRemoteAudioFrameEx, const FUABT_RtcConnection&, connection, int64, userId, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFirstRemoteAudioDecodedEx, const FUABT_RtcConnection&, connection, int64, uid, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLocalAudioStateChangedEx, const FUABT_RtcConnection&, connection, EUABT_LOCAL_AUDIO_STREAM_STATE, state, EUABT_LOCAL_AUDIO_STREAM_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteAudioStateChangedEx, const FUABT_RtcConnection&, connection, int64, remoteUid, EUABT_REMOTE_AUDIO_STATE, state, EUABT_REMOTE_AUDIO_STATE_REASON, reason, int, elapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveSpeakerEx, const FUABT_RtcConnection&, connection, int64, uid);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnClientRoleChangedEx, const FUABT_RtcConnection&, connection, EUABT_CLIENT_ROLE_TYPE, oldRole, EUABT_CLIENT_ROLE_TYPE, newRole, const FUABT_ClientRoleOptions&, newRoleOptions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnClientRoleChangeFailedEx, const FUABT_RtcConnection&, connection, EUABT_CLIENT_ROLE_CHANGE_FAILED_REASON, reason, EUABT_CLIENT_ROLE_TYPE, currentRole);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteAudioTransportStatsEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnRemoteVideoTransportStatsEx, const FUABT_RtcConnection&, connection, int64, remoteUid, int, delay, int, lost, int, rxKBitRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConnectionStateChangedEx, const FUABT_RtcConnection&, connection, EUABT_CONNECTION_STATE_TYPE, state, EUABT_CONNECTION_CHANGED_REASON_TYPE, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnWlAccMessageEx, const FUABT_RtcConnection&, connection, EUABT_WLACC_MESSAGE_REASON, reason, EUABT_WLACC_SUGGEST_ACTION, action, const FString &, wlAccMsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWlAccStatsEx, const FUABT_RtcConnection&, connection, const FUABT_WlAccStats &, currentStats, const FUABT_WlAccStats &, averageStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNetworkTypeChangedEx, const FUABT_RtcConnection&, connection, EUABT_NETWORK_TYPE, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEncryptionErrorEx, const FUABT_RtcConnection&, connection, EUABT_ENCRYPTION_ERROR_TYPE, errorType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUploadLogResultEx, const FUABT_RtcConnection&, connection, const FString &, requestId, bool, success, EUABT_UPLOAD_ERROR_REASON, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserAccountUpdatedEx, const FUABT_RtcConnection&, connection, int64, remoteUid, const FString &, remoteUserAccount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnSnapshotTakenEx, const FUABT_RtcConnection&, connection, int64, uid, const FString &, filePath, int, width, int, height, int, errCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnVideoRenderingTracingResultEx, const FUABT_RtcConnection&, connection, int64, uid, EUABT_MEDIA_TRACE_EVENT, currentEvent, const FUABT_VideoRenderingTracingInfo &, tracingInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSetRtmFlagResultEx, const FUABT_RtcConnection&, connection, int, code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnTranscodedStreamLayoutInfoEx, const FUABT_RtcConnection&, connection, int64, uid, int, width, int, height, const TArray<FUABT_VideoLayout>&, layoutlist);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAudioMetadataReceivedEx, const FUABT_RtcConnection&, connection, int64, uid, const FString &, metadata);





class IRtcEngineEventHandlerExClassWrapper : public agora::rtc::IRtcEngineEventHandlerEx {};


using namespace agora;
using namespace agora::rtc;

// this is a native event handler managed in cpp
UCLASS(BlueprintType)
class AGORAPLUGIN_API UAgoraBPuIRtcEngineEventHandlerEx : public UObject, public IRtcEngineEventHandlerExClassWrapper
{
	GENERATED_BODY()

public:
	using IRtcEngineEventHandlerEx::eventHandlerType;
	//using IRtcEngineEventHandlerEx::onJoinChannelSuccess;
	//using IRtcEngineEventHandlerEx::onRejoinChannelSuccess;
	//using IRtcEngineEventHandlerEx::onAudioQuality;
	//using IRtcEngineEventHandlerEx::onAudioVolumeIndication;
	//using IRtcEngineEventHandlerEx::onLeaveChannel;
	//using IRtcEngineEventHandlerEx::onRtcStats;
	//using IRtcEngineEventHandlerEx::onNetworkQuality;
	//using IRtcEngineEventHandlerEx::onIntraRequestReceived;
	//using IRtcEngineEventHandlerEx::onFirstLocalVideoFramePublished;
	//using IRtcEngineEventHandlerEx::onFirstRemoteVideoDecoded;
	//using IRtcEngineEventHandlerEx::onVideoSizeChanged;
	//using IRtcEngineEventHandlerEx::onLocalVideoStateChanged;
	//using IRtcEngineEventHandlerEx::onRemoteVideoStateChanged;
	//using IRtcEngineEventHandlerEx::onFirstRemoteVideoFrame;
	//using IRtcEngineEventHandlerEx::onUserJoined;
	//using IRtcEngineEventHandlerEx::onUserOffline;
	//using IRtcEngineEventHandlerEx::onUserMuteAudio;
	//using IRtcEngineEventHandlerEx::onUserMuteVideo;
	//using IRtcEngineEventHandlerEx::onUserEnableVideo;
	//using IRtcEngineEventHandlerEx::onUserEnableLocalVideo;
	//using IRtcEngineEventHandlerEx::onUserStateChanged;
	//using IRtcEngineEventHandlerEx::onLocalAudioStats;
	//using IRtcEngineEventHandlerEx::onRemoteAudioStats;
	//using IRtcEngineEventHandlerEx::onLocalVideoStats;
	//using IRtcEngineEventHandlerEx::onRemoteVideoStats;
	//using IRtcEngineEventHandlerEx::onConnectionLost;
	//using IRtcEngineEventHandlerEx::onConnectionInterrupted;
	//using IRtcEngineEventHandlerEx::onConnectionBanned;
	//using IRtcEngineEventHandlerEx::onStreamMessage;
	//using IRtcEngineEventHandlerEx::onStreamMessageError;
	//using IRtcEngineEventHandlerEx::onRequestToken;
	//using IRtcEngineEventHandlerEx::onTokenPrivilegeWillExpire;
	//using IRtcEngineEventHandlerEx::onLicenseValidationFailure;
	//using IRtcEngineEventHandlerEx::onFirstLocalAudioFramePublished;
	//using IRtcEngineEventHandlerEx::onFirstRemoteAudioFrame;
	//using IRtcEngineEventHandlerEx::onFirstRemoteAudioDecoded;
	//using IRtcEngineEventHandlerEx::onLocalAudioStateChanged;
	//using IRtcEngineEventHandlerEx::onRemoteAudioStateChanged;
	//using IRtcEngineEventHandlerEx::onActiveSpeaker;
	//using IRtcEngineEventHandlerEx::onClientRoleChanged;
	//using IRtcEngineEventHandlerEx::onClientRoleChangeFailed;
	//using IRtcEngineEventHandlerEx::onRemoteAudioTransportStats;
	//using IRtcEngineEventHandlerEx::onRemoteVideoTransportStats;
	//using IRtcEngineEventHandlerEx::onConnectionStateChanged;
	//using IRtcEngineEventHandlerEx::onWlAccMessage;
	//using IRtcEngineEventHandlerEx::onWlAccStats;
	//using IRtcEngineEventHandlerEx::onNetworkTypeChanged;
	//using IRtcEngineEventHandlerEx::onEncryptionError;
	//using IRtcEngineEventHandlerEx::onUploadLogResult;
	//using IRtcEngineEventHandlerEx::onUserInfoUpdated;
	//using IRtcEngineEventHandlerEx::onUserAccountUpdated;
	//using IRtcEngineEventHandlerEx::onAudioSubscribeStateChanged;
	//using IRtcEngineEventHandlerEx::onVideoSubscribeStateChanged;
	//using IRtcEngineEventHandlerEx::onAudioPublishStateChanged;
	//using IRtcEngineEventHandlerEx::onVideoPublishStateChanged;
	//using IRtcEngineEventHandlerEx::onSnapshotTaken;
	//using IRtcEngineEventHandlerEx::onVideoRenderingTracingResult;
	//using IRtcEngineEventHandlerEx::onSetRtmFlagResult;
	//using IRtcEngineEventHandlerEx::onTranscodedStreamLayoutInfo;
	//using IRtcEngineEventHandlerEx::onAudioMetadataReceived;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnJoinChannelSuccessEx OnJoinChannelSuccessEx;
	
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnLeaveChannelEx OnLeaveChannelEx;
	
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserJoinedEx OnUserJoinedEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnUserOfflineEx OnUserOfflineEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRejoinChannelSuccessEx OnRejoinChannelSuccessEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioQualityEx OnAudioQualityEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnAudioVolumeIndicationEx OnAudioVolumeIndicationEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRtcStatsEx OnRtcStatsEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnNetworkQualityEx OnNetworkQualityEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnIntraRequestReceivedEx OnIntraRequestReceivedEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstLocalVideoFramePublishedEx OnFirstLocalVideoFramePublishedEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteVideoDecodedEx OnFirstRemoteVideoDecodedEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnVideoSizeChangedEx OnVideoSizeChangedEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRemoteVideoStateChangedEx OnRemoteVideoStateChangedEx;

	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnFirstRemoteVideoFrameEx OnFirstRemoteVideoFrameEx;

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


	void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;



	void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

	void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;


    virtual void onRejoinChannelSuccess(const RtcConnection& connection, int elapsed) override;

    virtual void onAudioQuality(const RtcConnection& connection, uid_t remoteUid, int quality, unsigned short delay, unsigned short lost) __deprecated override;

    virtual void onAudioVolumeIndication(const RtcConnection& connection, const AudioVolumeInfo* speakers,
        unsigned int speakerNumber, int totalVolume)  override;

    virtual void onRtcStats(const RtcConnection& connection, const RtcStats& stats) override;

    virtual void onNetworkQuality(const RtcConnection& connection, uid_t remoteUid, int txQuality, int rxQuality) override;

    virtual void onIntraRequestReceived(const RtcConnection& connection) override;

    virtual void onFirstLocalVideoFramePublished(const RtcConnection& connection, int elapsed) override;


    virtual void onFirstRemoteVideoDecoded(const RtcConnection& connection, uid_t remoteUid, int width, int height, int elapsed)    override;


    virtual void onVideoSizeChanged(const RtcConnection& connection, VIDEO_SOURCE_TYPE sourceType, uid_t uid, int width, int height, int rotation)  override;


    virtual void onRemoteVideoStateChanged(const RtcConnection& connection, uid_t remoteUid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;


    virtual void onFirstRemoteVideoFrame(const RtcConnection& connection, uid_t remoteUid, int width, int height, int elapsed) override;

    virtual void onUserMuteAudio(const RtcConnection& connection, uid_t remoteUid, bool muted) __deprecated override;


    virtual void onUserMuteVideo(const RtcConnection& connection, uid_t remoteUid, bool muted) override;


    virtual void onUserEnableVideo(const RtcConnection& connection, uid_t remoteUid, bool enabled) override;

    virtual void onUserEnableLocalVideo(const RtcConnection& connection, uid_t remoteUid, bool enabled) __deprecated override;


    virtual void onUserStateChanged(const RtcConnection& connection, uid_t remoteUid, uint32_t state) override;


    virtual void onLocalAudioStats(const RtcConnection& connection, const LocalAudioStats& stats) override;


    virtual void onRemoteAudioStats(const RtcConnection& connection, const RemoteAudioStats& stats) override;


    virtual void onLocalVideoStats(const RtcConnection& connection, const LocalVideoStats& stats) override;

    virtual void onRemoteVideoStats(const RtcConnection& connection, const RemoteVideoStats& stats) override;

    virtual void onConnectionLost(const RtcConnection& connection) override;

    virtual void onConnectionInterrupted(const RtcConnection& connection) __deprecated override;

    virtual void onConnectionBanned(const RtcConnection& connection)    override;

    virtual void onStreamMessage(const RtcConnection& connection, uid_t remoteUid, int streamId, const char* data, size_t length, uint64_t sentTs) override;


    virtual void onStreamMessageError(const RtcConnection& connection, uid_t remoteUid, int streamId, int code, int missed, int cached) override;


    virtual void onRequestToken(const RtcConnection& connection) override;

    virtual void onLicenseValidationFailure(const RtcConnection& connection, LICENSE_ERROR_TYPE reason) override;


    virtual void onTokenPrivilegeWillExpire(const RtcConnection& connection, const char* token) override;


    virtual void onFirstLocalAudioFramePublished(const RtcConnection& connection, int elapsed) override;


    virtual void onFirstRemoteAudioFrame(const RtcConnection& connection, uid_t userId, int elapsed) __deprecated override;

    
    virtual void onFirstRemoteAudioDecoded(const RtcConnection& connection, uid_t uid, int elapsed) __deprecated override;

    
    virtual void onLocalAudioStateChanged(const RtcConnection& connection, LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_REASON reason) override;


    virtual void onRemoteAudioStateChanged(const RtcConnection& connection, uid_t remoteUid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;

    
    virtual void onActiveSpeaker(const RtcConnection& connection, uid_t uid)  override;
    
    virtual void onClientRoleChanged(const RtcConnection& connection, CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole, const ClientRoleOptions& newRoleOptions)  override;

    virtual void onClientRoleChangeFailed(const RtcConnection& connection, CLIENT_ROLE_CHANGE_FAILED_REASON reason, CLIENT_ROLE_TYPE currentRole)  override;

    virtual void onRemoteAudioTransportStats(const RtcConnection& connection, uid_t remoteUid, unsigned short delay, unsigned short lost,
        unsigned short rxKBitRate) __deprecated  override;
        
    
    virtual void onRemoteVideoTransportStats(const RtcConnection& connection, uid_t remoteUid, unsigned short delay, unsigned short lost,
        unsigned short rxKBitRate) __deprecated  override;


    virtual void onConnectionStateChanged(const RtcConnection& connection,
        CONNECTION_STATE_TYPE state,
        CONNECTION_CHANGED_REASON_TYPE reason) override;


    virtual void onWlAccMessage(const RtcConnection& connection, WLACC_MESSAGE_REASON reason, WLACC_SUGGEST_ACTION action, const char* wlAccMsg)  override;

    
    virtual void onWlAccStats(const RtcConnection& connection, WlAccStats currentStats, WlAccStats averageStats)  override;

    virtual void onNetworkTypeChanged(const RtcConnection& connection, NETWORK_TYPE type)  override;

    
    virtual void onEncryptionError(const RtcConnection& connection, ENCRYPTION_ERROR_TYPE errorType) override;
    
    virtual void onUploadLogResult(const RtcConnection& connection, const char* requestId, bool success, UPLOAD_ERROR_REASON reason)override;

    virtual void onUserAccountUpdated(const RtcConnection& connection, uid_t remoteUid, const char* remoteUserAccount) override;

    
    virtual void onSnapshotTaken(const RtcConnection& connection, uid_t uid, const char* filePath, int width, int height, int errCode)  override;
    
    virtual void onVideoRenderingTracingResult(const RtcConnection& connection, uid_t uid, MEDIA_TRACE_EVENT currentEvent, VideoRenderingTracingInfo tracingInfo) override;
    
    
    virtual void onSetRtmFlagResult(const RtcConnection& connection, int code)  override;
    
    virtual void onTranscodedStreamLayoutInfo(const RtcConnection& connection, uid_t uid, int width, int height, int layoutCount, const VideoLayout* layoutlist)  override;

    virtual void onAudioMetadataReceived(const RtcConnection& connection, uid_t uid, const char* metadata, size_t length) override;
	
	// You could add multiple executors to the target handler
	UFUNCTION(BlueprintCallable, Category = "Agora|Event")
	void AddBlueprintCallbackExecutorEx(UAgoraBPuIRtcEngineEventHandlerExCBExecutor* Executor);

	UFUNCTION(BlueprintCallable, Category = "Agora|Event")
	void RemoveAllBlueprintCallbackExecutorExs();

private:
	EAgoraBPuEventHandlerType Type = EAgoraBPuEventHandlerType::EventHandlerEx;
};

// this is a blueprint callback executor which you could add to the target handler
UCLASS(Blueprintable, Meta = (ShowWorldContextPin))
class AGORAPLUGIN_API UAgoraBPuIRtcEngineEventHandlerExCBExecutor: public UObject{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnJoinChannelSuccess(const FUABT_RtcConnection& Connection, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnLeaveChannel(const FUABT_RtcConnection& connection, const FUABT_RtcStats&  stats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserJoined(const FUABT_RtcConnection& connection, int64 RemoteUid, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserOffline(const FUABT_RtcConnection& connection, int64 RemoteUid, EUABT_USER_OFFLINE_REASON_TYPE Reason);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRejoinChannelSuccess(const FUABT_RtcConnection& connection, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnAudioQuality(const FUABT_RtcConnection& connection, int64 RemoteUid, int Quality, int Delay, int Lost);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnAudioVolumeIndication(const FUABT_RtcConnection& connection, const TArray<FUABT_AudioVolumeInfo>& Speakers, int TotalVolume);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRtcStats(const FUABT_RtcConnection& connection, const FUABT_RtcStats& Stats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnNetworkQuality(const FUABT_RtcConnection& connection, int64 RemoteUid, int TxQuality, int RxQuality);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnIntraRequestReceived(const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnFirstLocalVideoFramePublished(const FUABT_RtcConnection& connection, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnFirstRemoteVideoDecoded(const FUABT_RtcConnection& connection, int64 RemoteUid, int Width, int Height, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnVideoSizeChanged(const FUABT_RtcConnection& connection, EUABT_VIDEO_SOURCE_TYPE SourceType, int64 Uid, int Width, int Height, int Rotation);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRemoteVideoStateChanged(const FUABT_RtcConnection& connection, int64 RemoteUid, EUABT_REMOTE_VIDEO_STATE State, EUABT_REMOTE_VIDEO_STATE_REASON Reason, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnFirstRemoteVideoFrame(const FUABT_RtcConnection& connection, int64 RemoteUid, int Width, int Height, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserMuteAudio(const FUABT_RtcConnection& connection, int64 RemoteUid, bool Muted);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserMuteVideo(const FUABT_RtcConnection& connection, int64 RemoteUid, bool Muted);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserEnableVideo(const FUABT_RtcConnection& connection, int64 RemoteUid, bool Enabled);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserEnableLocalVideo(const FUABT_RtcConnection& connection, int64 RemoteUid, bool Enabled);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserStateChanged(const FUABT_RtcConnection& connection, int64 RemoteUid, int State);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnLocalAudioStats(const FUABT_RtcConnection& connection, const FUABT_LocalAudioStats& Stats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRemoteAudioStats(const FUABT_RtcConnection& connection, const FUABT_RemoteAudioStats& Stats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnLocalVideoStats(const FUABT_RtcConnection& connection, const FUABT_LocalVideoStats& Stats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRemoteVideoStats(const FUABT_RtcConnection& connection, const FUABT_RemoteVideoStats& Stats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnConnectionLost(const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnConnectionInterrupted(const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnConnectionBanned(const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnStreamMessage(const FUABT_RtcConnection& connection, int64 RemoteUid, int StreamId, const FString& Data, int64 Length, int64 SentTs);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnStreamMessageError(const FUABT_RtcConnection& connection, int64 RemoteUid, int StreamId, int Code, int Missed, int Cached);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRequestToken(const FUABT_RtcConnection& connection);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnLicenseValidationFailure(const FUABT_RtcConnection& connection, EUABT_LICENSE_ERROR_TYPE Reason);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnTokenPrivilegeWillExpire(const FUABT_RtcConnection& connection, const FString& Token);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnFirstLocalAudioFramePublished(const FUABT_RtcConnection& connection, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnFirstRemoteAudioFrame(const FUABT_RtcConnection& connection, int64 UserId, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnFirstRemoteAudioDecoded(const FUABT_RtcConnection& connection, int64 Uid, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnLocalAudioStateChanged(const FUABT_RtcConnection& connection, EUABT_LOCAL_AUDIO_STREAM_STATE State, EUABT_LOCAL_AUDIO_STREAM_REASON Reason);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRemoteAudioStateChanged(const FUABT_RtcConnection& connection, int64 RemoteUid, EUABT_REMOTE_AUDIO_STATE State, EUABT_REMOTE_AUDIO_STATE_REASON Reason, int Elapsed);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnActiveSpeaker(const FUABT_RtcConnection& connection, int64 Uid);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnClientRoleChanged(const FUABT_RtcConnection& connection, EUABT_CLIENT_ROLE_TYPE OldRole, EUABT_CLIENT_ROLE_TYPE NewRole, const FUABT_ClientRoleOptions& NewRoleOptions);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnClientRoleChangeFailed(const FUABT_RtcConnection& connection, EUABT_CLIENT_ROLE_CHANGE_FAILED_REASON Reason, EUABT_CLIENT_ROLE_TYPE CurrentRole);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRemoteAudioTransportStats(const FUABT_RtcConnection& connection, int64 RemoteUid, int Delay, int Lost, int RxKBitRate);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnRemoteVideoTransportStats(const FUABT_RtcConnection& connection, int64 RemoteUid, int Delay, int Lost, int RxKBitRate);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnConnectionStateChanged(const FUABT_RtcConnection& connection, EUABT_CONNECTION_STATE_TYPE State, EUABT_CONNECTION_CHANGED_REASON_TYPE Reason);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnWlAccMessage(const FUABT_RtcConnection& connection, EUABT_WLACC_MESSAGE_REASON Reason, EUABT_WLACC_SUGGEST_ACTION Action, const FString& WlAccMsg);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnWlAccStats(const FUABT_RtcConnection& connection, const FUABT_WlAccStats& CurrentStats, const FUABT_WlAccStats& AverageStats);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnNetworkTypeChanged(const FUABT_RtcConnection& connection, EUABT_NETWORK_TYPE Type);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnEncryptionError(const FUABT_RtcConnection& connection, EUABT_ENCRYPTION_ERROR_TYPE ErrorType);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUploadLogResult(const FUABT_RtcConnection& connection, const FString& RequestId, bool Success, EUABT_UPLOAD_ERROR_REASON Reason);


	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnUserAccountUpdated(const FUABT_RtcConnection& connection, int64 RemoteUid, const FString& RemoteUserAccount);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnSnapshotTaken(const FUABT_RtcConnection& connection, int64 Uid, const FString& FilePath, int Width, int Height, int ErrCode);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnVideoRenderingTracingResult(const FUABT_RtcConnection& connection, int64 Uid, EUABT_MEDIA_TRACE_EVENT CurrentEvent, const FUABT_VideoRenderingTracingInfo& TracingInfo);

	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnSetRtmFlagResult(const FUABT_RtcConnection& connection, int Code);


	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnTranscodedStreamLayoutInfo(const FUABT_RtcConnection& connection, int64 Uid, int Width, int Height, const TArray<FUABT_VideoLayout>& Layoutlist);


	UFUNCTION(BlueprintNativeEvent,Category= "Agora|Event")
	void OnAudioMetadataReceived(const FUABT_RtcConnection& connection, int64 Uid, const FString& Metadata);


};
