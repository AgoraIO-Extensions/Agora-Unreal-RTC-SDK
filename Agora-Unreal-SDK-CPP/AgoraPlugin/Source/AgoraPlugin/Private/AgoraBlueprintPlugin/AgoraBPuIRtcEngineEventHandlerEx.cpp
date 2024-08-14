// Copyright(c) 2024 Agora.io.All rights reserved.
#include "AgoraBPuIRtcEngineEventHandlerEx.h"

void UAgoraBPuIRtcEngineEventHandlerEx::AddBlueprintCallbackExecutorEx(UAgoraBPuIRtcEngineEventHandlerExCBExecutor* Executor)
{
	if(Executor == nullptr)
	{
		UAgoraBPuLogger::PrintWarn(FString::Printf(TEXT("%s Null Callback Executor"), *FString(AG_FUNCTION_MACRO)));
		return;
	}

	OnJoinChannelSuccessEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnJoinChannelSuccess);
	OnLeaveChannelEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLeaveChannel);
	OnUserJoinedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserJoined);
	OnUserOfflineEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserOffline);
	OnRejoinChannelSuccessEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRejoinChannelSuccess);
	OnAudioQualityEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnAudioQuality);
	OnAudioVolumeIndicationEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnAudioVolumeIndication);
	OnRtcStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRtcStats);
	OnNetworkQualityEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnNetworkQuality);
	OnIntraRequestReceivedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnIntraRequestReceived);
	OnFirstLocalVideoFramePublishedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstLocalVideoFramePublished);
	OnFirstRemoteVideoDecodedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteVideoDecoded);
	OnVideoSizeChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnVideoSizeChanged);
	OnRemoteVideoStateChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteVideoStateChanged);
	OnFirstRemoteVideoFrameEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteVideoFrame);
	OnUserMuteAudioEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserMuteAudio);
	OnUserMuteVideoEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserMuteVideo);
	OnUserEnableVideoEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserEnableVideo);
	OnUserEnableLocalVideoEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserEnableLocalVideo);
	OnUserStateChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserStateChanged);
	OnLocalAudioStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLocalAudioStats);
	OnRemoteAudioStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteAudioStats);
	OnLocalVideoStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLocalVideoStats);
	OnRemoteVideoStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteVideoStats);
	OnConnectionLostEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionLost);
	OnConnectionInterruptedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionInterrupted);
	OnConnectionBannedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionBanned);
	OnStreamMessageEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnStreamMessage);
	OnStreamMessageErrorEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnStreamMessageError);
	OnRequestTokenEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRequestToken);
	OnTokenPrivilegeWillExpireEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnTokenPrivilegeWillExpire);
	OnLicenseValidationFailureEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLicenseValidationFailure);
	OnFirstLocalAudioFramePublishedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstLocalAudioFramePublished);
	OnFirstRemoteAudioFrameEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteAudioFrame);
	OnFirstRemoteAudioDecodedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteAudioDecoded);
	OnLocalAudioStateChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLocalAudioStateChanged);
	OnRemoteAudioStateChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteAudioStateChanged);
	OnActiveSpeakerEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnActiveSpeaker);
	OnClientRoleChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnClientRoleChanged);
	OnClientRoleChangeFailedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnClientRoleChangeFailed);
	OnRemoteAudioTransportStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteAudioTransportStats);
	OnRemoteVideoTransportStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteVideoTransportStats);
	OnConnectionStateChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionStateChanged);
	OnWlAccMessageEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnWlAccMessage);
	OnWlAccStatsEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnWlAccStats);
	OnNetworkTypeChangedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnNetworkTypeChanged);
	OnEncryptionErrorEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnEncryptionError);
	OnUploadLogResultEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUploadLogResult);
	OnUserAccountUpdatedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserAccountUpdated);
	OnSnapshotTakenEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnSnapshotTaken);
	OnVideoRenderingTracingResultEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnVideoRenderingTracingResult);
	OnSetRtmFlagResultEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnSetRtmFlagResult);
	OnTranscodedStreamLayoutInfoEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnTranscodedStreamLayoutInfo);
	OnAudioMetadataReceivedEx.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnAudioMetadataReceived);


}

void UAgoraBPuIRtcEngineEventHandlerEx::RemoveAllBlueprintCallbackExecutorExs()
{
	OnJoinChannelSuccessEx.Clear();
	OnLeaveChannelEx.Clear();
	OnUserJoinedEx.Clear();
	OnUserOfflineEx.Clear();
	OnRejoinChannelSuccessEx.Clear();
	OnAudioQualityEx.Clear();
	OnAudioVolumeIndicationEx.Clear();
	OnRtcStatsEx.Clear();
	OnNetworkQualityEx.Clear();
	OnIntraRequestReceivedEx.Clear();
	OnFirstLocalVideoFramePublishedEx.Clear();
	OnFirstRemoteVideoDecodedEx.Clear();
	OnVideoSizeChangedEx.Clear();
	OnRemoteVideoStateChangedEx.Clear();
	OnFirstRemoteVideoFrameEx.Clear();
	OnUserMuteAudioEx.Clear();
	OnUserMuteVideoEx.Clear();
	OnUserEnableVideoEx.Clear();
	OnUserEnableLocalVideoEx.Clear();
	OnUserStateChangedEx.Clear();
	OnLocalAudioStatsEx.Clear();
	OnRemoteAudioStatsEx.Clear();
	OnLocalVideoStatsEx.Clear();
	OnRemoteVideoStatsEx.Clear();
	OnConnectionLostEx.Clear();
	OnConnectionInterruptedEx.Clear();
	OnConnectionBannedEx.Clear();
	OnStreamMessageEx.Clear();
	OnStreamMessageErrorEx.Clear();
	OnRequestTokenEx.Clear();
	OnTokenPrivilegeWillExpireEx.Clear();
	OnLicenseValidationFailureEx.Clear();
	OnFirstLocalAudioFramePublishedEx.Clear();
	OnFirstRemoteAudioFrameEx.Clear();
	OnFirstRemoteAudioDecodedEx.Clear();
	OnLocalAudioStateChangedEx.Clear();
	OnRemoteAudioStateChangedEx.Clear();
	OnActiveSpeakerEx.Clear();
	OnClientRoleChangedEx.Clear();
	OnClientRoleChangeFailedEx.Clear();
	OnRemoteAudioTransportStatsEx.Clear();
	OnRemoteVideoTransportStatsEx.Clear();
	OnConnectionStateChangedEx.Clear();
	OnWlAccMessageEx.Clear();
	OnWlAccStatsEx.Clear();
	OnNetworkTypeChangedEx.Clear();
	OnEncryptionErrorEx.Clear();
	OnUploadLogResultEx.Clear();
	OnUserAccountUpdatedEx.Clear();
	OnSnapshotTakenEx.Clear();
	OnVideoRenderingTracingResultEx.Clear();
	OnSetRtmFlagResultEx.Clear();
	OnTranscodedStreamLayoutInfoEx.Clear();
	OnAudioMetadataReceivedEx.Clear();
}

#pragma region Native Callback Functions

void UAgoraBPuIRtcEngineEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnJoinChannelSuccessEx.Broadcast(UERtcConnection, elapsed);
		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	FRtcConnection UERtcConnection = connection;

	FRtcStats UERtcStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnLeaveChannelEx.Broadcast(UERtcConnection, UERtcStats);
		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserJoinedEx.Broadcast(UERtcConnection, (int64)remoteUid, elapsed);
		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserOfflineEx.Broadcast(UERtcConnection, (int64)remoteUid, (EUSER_OFFLINE_REASON_TYPE) reason);
		});
}


void UAgoraBPuIRtcEngineEventHandlerEx::onRejoinChannelSuccess(const RtcConnection& connection, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRejoinChannelSuccessEx.Broadcast(UERtcConnection, elapsed);
		});
}



void UAgoraBPuIRtcEngineEventHandlerEx::onAudioQuality(const RtcConnection& connection, uid_t remoteUid, int quality, unsigned short delay, unsigned short lost) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnAudioQualityEx.Broadcast(UERtcConnection, (int64)remoteUid, quality, delay, lost);
		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onAudioVolumeIndication(const RtcConnection& connection, const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	FRtcConnection UERtcConnection = connection;

	TArray<FAudioVolumeInfo> UESpeakers;
	for (unsigned int i = 0; i < speakerNumber; i++)
	{
		UESpeakers.Add(speakers[i]);
	}

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnAudioVolumeIndicationEx.Broadcast(UERtcConnection, UESpeakers, totalVolume);
		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onRtcStats(const RtcConnection& connection, const RtcStats& stats)
{
	FRtcConnection UERtcConnection = connection;

	FRtcStats UERtcStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRtcStatsEx.Broadcast(UERtcConnection, UERtcStats);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onNetworkQuality(const RtcConnection& connection, uid_t remoteUid, int txQuality, int rxQuality)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnNetworkQualityEx.Broadcast(UERtcConnection, (int64)remoteUid, txQuality, rxQuality);

		});


}

void UAgoraBPuIRtcEngineEventHandlerEx::onIntraRequestReceived(const RtcConnection& connection)
{
	
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnIntraRequestReceivedEx.Broadcast(UERtcConnection);

		});

}

void UAgoraBPuIRtcEngineEventHandlerEx::onFirstLocalVideoFramePublished(const RtcConnection& connection, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFirstLocalVideoFramePublishedEx.Broadcast(UERtcConnection, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onFirstRemoteVideoDecoded(const RtcConnection& connection, uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFirstRemoteVideoDecodedEx.Broadcast(UERtcConnection, (int64)remoteUid, width, height, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onVideoSizeChanged(const RtcConnection& connection, VIDEO_SOURCE_TYPE sourceType, uid_t uid, int width, int height, int rotation)
{
	FRtcConnection UERtcConnection = connection;

	EVIDEO_SOURCE_TYPE UEVideoSourceType = (EVIDEO_SOURCE_TYPE)sourceType;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnVideoSizeChangedEx.Broadcast(UERtcConnection, UEVideoSourceType, (int64)uid, width, height, rotation);

		});
}


void UAgoraBPuIRtcEngineEventHandlerEx::onRemoteVideoStateChanged(const RtcConnection& connection, uid_t remoteUid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	EREMOTE_VIDEO_STATE UERemoteVideoState = (EREMOTE_VIDEO_STATE)state;
	EREMOTE_VIDEO_STATE_REASON UERemoteVideoStateReason = (EREMOTE_VIDEO_STATE_REASON)reason;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteVideoStateChangedEx.Broadcast(UERtcConnection, (int64)remoteUid, UERemoteVideoState, UERemoteVideoStateReason, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onFirstRemoteVideoFrame(const RtcConnection& connection, uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFirstRemoteVideoFrameEx.Broadcast(UERtcConnection, (int64)remoteUid, width, height, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserMuteAudio(const RtcConnection& connection, uid_t remoteUid, bool muted) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserMuteAudioEx.Broadcast(UERtcConnection, (int64)remoteUid, muted);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserMuteVideo(const RtcConnection& connection, uid_t remoteUid, bool muted)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserMuteVideoEx.Broadcast(UERtcConnection, (int64)remoteUid, muted);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserEnableVideo(const RtcConnection& connection, uid_t remoteUid, bool enabled)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserEnableVideoEx.Broadcast(UERtcConnection, (int64)remoteUid, enabled);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserEnableLocalVideo(const RtcConnection& connection, uid_t remoteUid, bool enabled) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserEnableLocalVideoEx.Broadcast(UERtcConnection, (int64)remoteUid, enabled);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserStateChanged(const RtcConnection& connection, uid_t remoteUid, uint32_t state)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserStateChangedEx.Broadcast(UERtcConnection, (int64)remoteUid, state);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onLocalAudioStats(const RtcConnection& connection, const LocalAudioStats& stats)
{
	FRtcConnection UERtcConnection = connection;

	FLocalAudioStats UELocalAudioStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnLocalAudioStatsEx.Broadcast(UERtcConnection, UELocalAudioStats);
		});

}

void UAgoraBPuIRtcEngineEventHandlerEx::onRemoteAudioStats(const RtcConnection& connection, const RemoteAudioStats& stats)
{
	
	FRtcConnection UERtcConnection = connection;

	FRemoteAudioStats UERemoteAudioStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteAudioStatsEx.Broadcast(UERtcConnection, UERemoteAudioStats);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onLocalVideoStats(const RtcConnection& connection, const LocalVideoStats& stats)
{
	FRtcConnection UERtcConnection = connection;

	FLocalVideoStats UELocalVideoStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnLocalVideoStatsEx.Broadcast(UERtcConnection, UELocalVideoStats);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onRemoteVideoStats(const RtcConnection& connection, const RemoteVideoStats& stats)
{
	FRtcConnection UERtcConnection = connection;

	FRemoteVideoStats UERemoteVideoStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteVideoStatsEx.Broadcast(UERtcConnection, UERemoteVideoStats);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onConnectionLost(const RtcConnection& connection)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnConnectionLostEx.Broadcast(UERtcConnection);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onConnectionInterrupted(const RtcConnection& connection) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnConnectionInterruptedEx.Broadcast(UERtcConnection);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onConnectionBanned(const RtcConnection& connection)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnConnectionBannedEx.Broadcast(UERtcConnection);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onStreamMessage(const RtcConnection& connection, uid_t remoteUid, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	FRtcConnection UERtcConnection = connection;

	FString UEData = FString(UTF8_TO_TCHAR(data));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnStreamMessageEx.Broadcast(UERtcConnection, (int64)remoteUid, streamId, UEData, length, sentTs);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onStreamMessageError(const RtcConnection& connection, uid_t remoteUid, int streamId, int code, int missed, int cached)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnStreamMessageErrorEx.Broadcast(UERtcConnection, (int64)remoteUid, streamId, code, missed, cached);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onRequestToken(const RtcConnection& connection)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRequestTokenEx.Broadcast(UERtcConnection);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onLicenseValidationFailure(const RtcConnection& connection, LICENSE_ERROR_TYPE reason)
{
	FRtcConnection UERtcConnection = connection;

	ELICENSE_ERROR_TYPE UELicenseErrorType = (ELICENSE_ERROR_TYPE)reason;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnLicenseValidationFailureEx.Broadcast(UERtcConnection, UELicenseErrorType);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onTokenPrivilegeWillExpire(const RtcConnection& connection, const char* token)
{
	FRtcConnection UERtcConnection = connection;

	FString UEToken = FString(UTF8_TO_TCHAR(token));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnTokenPrivilegeWillExpireEx.Broadcast(UERtcConnection, UEToken);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onFirstLocalAudioFramePublished(const RtcConnection& connection, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFirstLocalAudioFramePublishedEx.Broadcast(UERtcConnection, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onFirstRemoteAudioFrame(const RtcConnection& connection, uid_t userId, int elapsed) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFirstRemoteAudioFrameEx.Broadcast(UERtcConnection, (int64)userId, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onFirstRemoteAudioDecoded(const RtcConnection& connection, uid_t uid, int elapsed) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnFirstRemoteAudioDecodedEx.Broadcast(UERtcConnection, (int64)uid, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onLocalAudioStateChanged(const RtcConnection& connection, LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_REASON reason)
{
	FRtcConnection UERtcConnection = connection;

	ELOCAL_AUDIO_STREAM_STATE UEState = (ELOCAL_AUDIO_STREAM_STATE)state;
	ELOCAL_AUDIO_STREAM_REASON UEReason = (ELOCAL_AUDIO_STREAM_REASON)reason;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnLocalAudioStateChangedEx.Broadcast(UERtcConnection, UEState, UEReason);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onRemoteAudioStateChanged(const RtcConnection& connection, uid_t remoteUid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	EREMOTE_AUDIO_STATE UERemoteAudioState = (EREMOTE_AUDIO_STATE)state;
	EREMOTE_AUDIO_STATE_REASON UERemoteAudioStateReason = (EREMOTE_AUDIO_STATE_REASON)reason;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteAudioStateChangedEx.Broadcast(UERtcConnection, (int64)remoteUid, UERemoteAudioState, UERemoteAudioStateReason, elapsed);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onActiveSpeaker(const RtcConnection& connection, uid_t uid)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnActiveSpeakerEx.Broadcast(UERtcConnection, (int64)uid);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onClientRoleChanged(const RtcConnection& connection, CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole, const ClientRoleOptions& newRoleOptions)
{
	FRtcConnection UERtcConnection = connection;

	ECLIENT_ROLE_TYPE UEOldRole = (ECLIENT_ROLE_TYPE)oldRole;
	ECLIENT_ROLE_TYPE UENewRole = (ECLIENT_ROLE_TYPE)newRole;
	FClientRoleOptions UEClientRoleOptions = newRoleOptions;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnClientRoleChangedEx.Broadcast(UERtcConnection, UEOldRole, UENewRole, UEClientRoleOptions);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onClientRoleChangeFailed(const RtcConnection& connection, CLIENT_ROLE_CHANGE_FAILED_REASON reason, CLIENT_ROLE_TYPE currentRole)
{
	FRtcConnection UERtcConnection = connection;

	ECLIENT_ROLE_CHANGE_FAILED_REASON UEClientRoleChangeFailedReason = (ECLIENT_ROLE_CHANGE_FAILED_REASON)reason;
	ECLIENT_ROLE_TYPE UECurrentRole = (ECLIENT_ROLE_TYPE)currentRole;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnClientRoleChangeFailedEx.Broadcast(UERtcConnection, UEClientRoleChangeFailedReason, UECurrentRole);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onRemoteAudioTransportStats(const RtcConnection& connection, uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) __deprecated
{
	FRtcConnection UERtcConnection = connection;
	
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteAudioTransportStatsEx.Broadcast(UERtcConnection, (int64)remoteUid, delay, lost, rxKBitRate);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onRemoteVideoTransportStats(const RtcConnection& connection, uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) __deprecated
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnRemoteVideoTransportStatsEx.Broadcast(UERtcConnection, (int64)remoteUid, delay, lost, rxKBitRate);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onConnectionStateChanged(const RtcConnection& connection, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	FRtcConnection UERtcConnection = connection;

	ECONNECTION_STATE_TYPE UEConnectionStateType = (ECONNECTION_STATE_TYPE)state;
	ECONNECTION_CHANGED_REASON_TYPE UEConnectionChangedReasonType = (ECONNECTION_CHANGED_REASON_TYPE)reason;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnConnectionStateChangedEx.Broadcast(UERtcConnection, UEConnectionStateType, UEConnectionChangedReasonType);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onWlAccMessage(const RtcConnection& connection, WLACC_MESSAGE_REASON reason, WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	FRtcConnection UERtcConnection = connection;

	EWLACC_MESSAGE_REASON UEWlAccMessageReason = (EWLACC_MESSAGE_REASON)reason;
	EWLACC_SUGGEST_ACTION UEWlAccSuggestAction = (EWLACC_SUGGEST_ACTION)action;
	FString UEWlAccMsg = FString(UTF8_TO_TCHAR(wlAccMsg));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnWlAccMessageEx.Broadcast(UERtcConnection, UEWlAccMessageReason, UEWlAccSuggestAction, UEWlAccMsg);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onWlAccStats(const RtcConnection& connection, WlAccStats currentStats, WlAccStats averageStats)
{
	FRtcConnection UERtcConnection = connection;

	FWlAccStats UECurrentStats = currentStats;
	FWlAccStats UEAverageStats = averageStats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnWlAccStatsEx.Broadcast(UERtcConnection, UECurrentStats, UEAverageStats);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onNetworkTypeChanged(const RtcConnection& connection, NETWORK_TYPE type)
{
	FRtcConnection UERtcConnection = connection;

	FENUMWRAP_NETWORK_TYPE UENetworkType = type;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnNetworkTypeChangedEx.Broadcast(UERtcConnection, UENetworkType);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onEncryptionError(const RtcConnection& connection, ENCRYPTION_ERROR_TYPE errorType)
{
	FRtcConnection UERtcConnection = connection;

	EENCRYPTION_ERROR_TYPE UEErrorType = (EENCRYPTION_ERROR_TYPE)errorType;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnEncryptionErrorEx.Broadcast(UERtcConnection, UEErrorType);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUploadLogResult(const RtcConnection& connection, const char* requestId, bool success, UPLOAD_ERROR_REASON reason)
{
	FRtcConnection UERtcConnection = connection;

	FString UERequestId = FString(UTF8_TO_TCHAR(requestId));
	EUPLOAD_ERROR_REASON UEUploadErrorReason = (EUPLOAD_ERROR_REASON)reason;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUploadLogResultEx.Broadcast(UERtcConnection, UERequestId, success, UEUploadErrorReason);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onUserAccountUpdated(const RtcConnection& connection, uid_t remoteUid, const char* remoteUserAccount)
{
	FRtcConnection UERtcConnection = connection;

	FString UERemoteUserAccount = FString(UTF8_TO_TCHAR(remoteUserAccount));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnUserAccountUpdatedEx.Broadcast(UERtcConnection, (int64)remoteUid, UERemoteUserAccount);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onSnapshotTaken(const RtcConnection& connection, uid_t uid, const char* filePath, int width, int height, int errCode)
{
	FRtcConnection UERtcConnection = connection;

	FString UEFilePath = FString(UTF8_TO_TCHAR(filePath));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnSnapshotTakenEx.Broadcast(UERtcConnection, (int64)uid, UEFilePath, width, height, errCode);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onVideoRenderingTracingResult(const RtcConnection& connection, uid_t uid, MEDIA_TRACE_EVENT currentEvent, VideoRenderingTracingInfo tracingInfo)
{
	FRtcConnection UERtcConnection = connection;

	EMEDIA_TRACE_EVENT UEMediaTraceEvent = (EMEDIA_TRACE_EVENT)currentEvent;
	FVideoRenderingTracingInfo UETracingInfo = tracingInfo;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnVideoRenderingTracingResultEx.Broadcast(UERtcConnection, (int64)uid, UEMediaTraceEvent, UETracingInfo);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onSetRtmFlagResult(const RtcConnection& connection, int code)
{
	FRtcConnection UERtcConnection = connection;

	int32 UECode = code;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnSetRtmFlagResultEx.Broadcast(UERtcConnection, UECode);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onTranscodedStreamLayoutInfo(const RtcConnection& connection, uid_t uid, int width, int height, int layoutCount, const VideoLayout* layoutlist)
{
	FRtcConnection UERtcConnection = connection;

	TArray<FVideoLayout> UELayoutList;
	for (int i = 0; i < layoutCount; i++)
	{
		FVideoLayout UEVideoLayout = layoutlist[i];
		UELayoutList.Add(UEVideoLayout);
	}

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnTranscodedStreamLayoutInfoEx.Broadcast(UERtcConnection, uid, width, height, UELayoutList);

		});
}

void UAgoraBPuIRtcEngineEventHandlerEx::onAudioMetadataReceived(const RtcConnection& connection, uid_t uid, const char* metadata, size_t length)
{
	FRtcConnection UERtcConnection = connection;

	FString UEMetadata = FString(UTF8_TO_TCHAR(metadata));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnAudioMetadataReceivedEx.Broadcast(UERtcConnection, (int64)uid, UEMetadata);

		});
}

#pragma endregion Native Callback Functions


#pragma region BP Executor

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnJoinChannelSuccess_Implementation(const FRtcConnection& Connection, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLeaveChannel_Implementation(const FRtcConnection& connection, const FRtcStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserJoined_Implementation(const FRtcConnection& connection, int64 RemoteUid, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserOffline_Implementation(const FRtcConnection& connection, int64 RemoteUid, EUSER_OFFLINE_REASON_TYPE Reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRejoinChannelSuccess_Implementation(const FRtcConnection& connection, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnAudioQuality_Implementation(const FRtcConnection& connection, int64 RemoteUid, int Quality, int Delay, int Lost)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnAudioVolumeIndication_Implementation(const FRtcConnection& connection, const TArray<FAudioVolumeInfo>& Speakers, int TotalVolume)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRtcStats_Implementation(const FRtcConnection& connection, const FRtcStats& Stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnNetworkQuality_Implementation(const FRtcConnection& connection, int64 RemoteUid, int TxQuality, int RxQuality)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnIntraRequestReceived_Implementation(const FRtcConnection& connection)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstLocalVideoFramePublished_Implementation(const FRtcConnection& connection, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteVideoDecoded_Implementation(const FRtcConnection& connection, int64 RemoteUid, int Width, int Height, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnVideoSizeChanged_Implementation(const FRtcConnection& connection, EVIDEO_SOURCE_TYPE SourceType, int64 Uid, int Width, int Height, int Rotation)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteVideoStateChanged_Implementation(const FRtcConnection& connection, int64 RemoteUid, EREMOTE_VIDEO_STATE State, EREMOTE_VIDEO_STATE_REASON Reason, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteVideoFrame_Implementation(const FRtcConnection& connection, int64 RemoteUid, int Width, int Height, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserMuteAudio_Implementation(const FRtcConnection& connection, int64 RemoteUid, bool Muted)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserMuteVideo_Implementation(const FRtcConnection& connection, int64 RemoteUid, bool Muted)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserEnableVideo_Implementation(const FRtcConnection& connection, int64 RemoteUid, bool Enabled)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserEnableLocalVideo_Implementation(const FRtcConnection& connection, int64 RemoteUid, bool Enabled)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserStateChanged_Implementation(const FRtcConnection& connection, int64 RemoteUid, int State)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLocalAudioStats_Implementation(const FRtcConnection& connection, const FLocalAudioStats& Stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteAudioStats_Implementation(const FRtcConnection& connection, const FRemoteAudioStats& Stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLocalVideoStats_Implementation(const FRtcConnection& connection, const FLocalVideoStats& Stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteVideoStats_Implementation(const FRtcConnection& connection, const FRemoteVideoStats& Stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionLost_Implementation(const FRtcConnection& connection)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionInterrupted_Implementation(const FRtcConnection& connection)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionBanned_Implementation(const FRtcConnection& connection)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnStreamMessage_Implementation(const FRtcConnection& connection, int64 RemoteUid, int StreamId, const FString& Data, int64 Length, int64 SentTs)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnStreamMessageError_Implementation(const FRtcConnection& connection, int64 RemoteUid, int StreamId, int Code, int Missed, int Cached)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRequestToken_Implementation(const FRtcConnection& connection)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLicenseValidationFailure_Implementation(const FRtcConnection& connection, ELICENSE_ERROR_TYPE Reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnTokenPrivilegeWillExpire_Implementation(const FRtcConnection& connection, const FString& Token)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstLocalAudioFramePublished_Implementation(const FRtcConnection& connection, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteAudioFrame_Implementation(const FRtcConnection& connection, int64 UserId, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnFirstRemoteAudioDecoded_Implementation(const FRtcConnection& connection, int64 Uid, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnLocalAudioStateChanged_Implementation(const FRtcConnection& connection, ELOCAL_AUDIO_STREAM_STATE State, ELOCAL_AUDIO_STREAM_REASON Reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteAudioStateChanged_Implementation(const FRtcConnection& connection, int64 RemoteUid, EREMOTE_AUDIO_STATE State, EREMOTE_AUDIO_STATE_REASON Reason, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnActiveSpeaker_Implementation(const FRtcConnection& connection, int64 Uid)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnClientRoleChanged_Implementation(const FRtcConnection& connection, ECLIENT_ROLE_TYPE OldRole, ECLIENT_ROLE_TYPE NewRole, const FClientRoleOptions& NewRoleOptions)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnClientRoleChangeFailed_Implementation(const FRtcConnection& connection, ECLIENT_ROLE_CHANGE_FAILED_REASON Reason, ECLIENT_ROLE_TYPE CurrentRole)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteAudioTransportStats_Implementation(const FRtcConnection& connection, int64 RemoteUid, int Delay, int Lost, int RxKBitRate)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnRemoteVideoTransportStats_Implementation(const FRtcConnection& connection, int64 RemoteUid, int Delay, int Lost, int RxKBitRate)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnConnectionStateChanged_Implementation(const FRtcConnection& connection, ECONNECTION_STATE_TYPE State, ECONNECTION_CHANGED_REASON_TYPE Reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnWlAccMessage_Implementation(const FRtcConnection& connection, EWLACC_MESSAGE_REASON Reason, EWLACC_SUGGEST_ACTION Action, const FString& WlAccMsg)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnWlAccStats_Implementation(const FRtcConnection& connection, const FWlAccStats& CurrentStats, const FWlAccStats& AverageStats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnNetworkTypeChanged_Implementation(const FRtcConnection& connection, FENUMWRAP_NETWORK_TYPE Type)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnEncryptionError_Implementation(const FRtcConnection& connection, EENCRYPTION_ERROR_TYPE ErrorType)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUploadLogResult_Implementation(const FRtcConnection& connection, const FString& RequestId, bool Success, EUPLOAD_ERROR_REASON Reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnUserAccountUpdated_Implementation(const FRtcConnection& connection, int64 RemoteUid, const FString& RemoteUserAccount)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnSnapshotTaken_Implementation(const FRtcConnection& connection, int64 Uid, const FString& FilePath, int Width, int Height, int ErrCode)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnVideoRenderingTracingResult_Implementation(const FRtcConnection& connection, int64 Uid, EMEDIA_TRACE_EVENT CurrentEvent, const FVideoRenderingTracingInfo& TracingInfo)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnSetRtmFlagResult_Implementation(const FRtcConnection& connection, int Code)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnTranscodedStreamLayoutInfo_Implementation(const FRtcConnection& connection, int64 Uid, int Width, int Height, const TArray<FVideoLayout>& Layoutlist)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerExCBExecutor::OnAudioMetadataReceived_Implementation(const FRtcConnection& connection, int64 Uid, const FString& Metadata)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

#pragma endregion BP Executor

