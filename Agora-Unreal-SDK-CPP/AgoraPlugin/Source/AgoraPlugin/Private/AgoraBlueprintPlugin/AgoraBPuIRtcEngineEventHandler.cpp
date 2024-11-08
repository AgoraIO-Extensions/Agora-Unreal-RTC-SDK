// Copyright(c) 2024 Agora.io. All rights reserved.

#include "AgoraBPuIRtcEngineEventHandler.h"
#include "Async/Async.h"



void UAgoraBPuIRtcEngineEventHandler::AddBlueprintCallbackExecutor(UAgoraBPuIRtcEngineEventHandlerCBExecutor* Executor)
{

	if (Executor == nullptr)
	{
		UAgoraBPuLogger::PrintWarn(FString::Printf(TEXT("%s Null Callback Executor"), *FString(AG_FUNCTION_MACRO)));
		return;
	}


	//FScriptDelegate Delegate;
	//Delegate.BindUFunction(Executor, "OnJoinChannelSuccessCB");
	//OnJoinChannelSuccess.Add(Delegate);

	OnJoinChannelSuccess.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnJoinChannelSuccess);
	OnLeaveChannel.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLeaveChannel);
	OnUserJoined.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserJoined);
	OnUserOffline.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserOffline);
	OnRejoinChannelSuccess.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRejoinChannelSuccess);
	OnProxyConnected.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnProxyConnected);
	OnError.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnError);
	OnAudioQuality.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioQuality);
	OnLastmileProbeResult.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLastmileProbeResult);
	OnAudioVolumeIndication.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioVolumeIndication);
	OnRtcStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRtcStats);
	OnAudioDeviceStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioDeviceStateChanged);
	OnAudioMixingPositionChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMixingPositionChanged);
	OnAudioMixingFinished.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMixingFinished);
	OnAudioEffectFinished.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioEffectFinished);
	OnVideoDeviceStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoDeviceStateChanged);
	OnNetworkQuality.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnNetworkQuality);
	OnIntraRequestReceived.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnIntraRequestReceived);
	OnUplinkNetworkInfoUpdated.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUplinkNetworkInfoUpdated);
	OnDownlinkNetworkInfoUpdated.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnDownlinkNetworkInfoUpdated);
	OnLastmileQuality.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLastmileQuality);
	OnFirstLocalVideoFrame.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstLocalVideoFrame);
	OnFirstLocalVideoFramePublished.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstLocalVideoFramePublished);
	OnFirstRemoteVideoDecoded.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteVideoDecoded);
	OnVideoSizeChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoSizeChanged);
	OnLocalVideoStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalVideoStateChanged);
	OnRemoteVideoStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteVideoStateChanged);
	OnFirstRemoteVideoFrame.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteVideoFrame);
	OnUserMuteAudio.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserMuteAudio);
	OnUserMuteVideo.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserMuteVideo);
	OnUserEnableVideo.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserEnableVideo);
	OnUserStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserStateChanged);
	OnUserEnableLocalVideo.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserEnableLocalVideo);
	OnLocalAudioStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalAudioStats);
	OnRemoteAudioStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteAudioStats);
	OnLocalVideoStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalVideoStats);
	OnRemoteVideoStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteVideoStats);
	OnCameraReady.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnCameraReady);
	OnCameraFocusAreaChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnCameraFocusAreaChanged);
	OnCameraExposureAreaChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnCameraExposureAreaChanged);
	OnFacePositionChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFacePositionChanged);
	OnVideoStopped.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoStopped);
	OnAudioMixingStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMixingStateChanged);
	OnRhythmPlayerStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRhythmPlayerStateChanged);
	OnConnectionLost.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionLost);
	OnConnectionInterrupted.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionInterrupted);
	OnConnectionBanned.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionBanned);
	OnStreamMessage.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnStreamMessage);
	OnStreamMessageError.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnStreamMessageError);
	OnRequestToken.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRequestToken);
	OnTokenPrivilegeWillExpire.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnTokenPrivilegeWillExpire);
	OnLicenseValidationFailure.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLicenseValidationFailure);
	OnFirstLocalAudioFramePublished.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstLocalAudioFramePublished);
	OnFirstRemoteAudioDecoded.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteAudioDecoded);
	OnFirstRemoteAudioFrame.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteAudioFrame);
	OnLocalAudioStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalAudioStateChanged);
	OnRemoteAudioStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteAudioStateChanged);
	OnActiveSpeaker.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnActiveSpeaker);
	OnContentInspectResult.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnContentInspectResult);
	OnSnapshotTaken.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnSnapshotTaken);
	OnClientRoleChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnClientRoleChanged);
	OnClientRoleChangeFailed.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnClientRoleChangeFailed);
	OnAudioDeviceVolumeChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioDeviceVolumeChanged);
	OnRtmpStreamingStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRtmpStreamingStateChanged);
	OnRtmpStreamingEvent.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRtmpStreamingEvent);
	OnTranscodingUpdated.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnTranscodingUpdated);
	OnAudioRoutingChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioRoutingChanged);
	OnChannelMediaRelayStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnChannelMediaRelayStateChanged);
	OnLocalPublishFallbackToAudioOnly.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalPublishFallbackToAudioOnly);
	OnRemoteSubscribeFallbackToAudioOnly.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteSubscribeFallbackToAudioOnly);
	OnRemoteAudioTransportStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteAudioTransportStats);
	OnRemoteVideoTransportStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteVideoTransportStats);
	OnConnectionStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionStateChanged);
	OnWlAccMessage.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnWlAccMessage);
	OnWlAccStats.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnWlAccStats);
	OnNetworkTypeChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnNetworkTypeChanged);
	OnEncryptionError.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnEncryptionError);
	OnPermissionError.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnPermissionError);
	OnLocalUserRegistered.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalUserRegistered);
	OnUserInfoUpdated.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserInfoUpdated);
	OnUserAccountUpdated.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserAccountUpdated);
	OnVideoRenderingTracingResult.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoRenderingTracingResult);
	OnLocalVideoTranscoderError.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalVideoTranscoderError);
	OnUploadLogResult.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUploadLogResult);
	OnAudioSubscribeStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioSubscribeStateChanged);
	OnVideoSubscribeStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoSubscribeStateChanged);
	OnAudioPublishStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioPublishStateChanged);
	OnVideoPublishStateChanged.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoPublishStateChanged);
	OnTranscodedStreamLayoutInfo.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnTranscodedStreamLayoutInfo);
	OnAudioMetadataReceived.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMetadataReceived);
	OnExtensionEventWithContext.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionEventWithContext);
	OnExtensionStartedWithContext.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionStartedWithContext);
	OnExtensionStoppedWithContext.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionStoppedWithContext);
	OnExtensionErrorWithContext.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionErrorWithContext);
	OnSetRtmFlagResult.AddDynamic(Executor, &UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnSetRtmFlagResult);
}


void UAgoraBPuIRtcEngineEventHandler::RemoveAllBlueprintCallbackExecutors()
{
	OnJoinChannelSuccess.Clear();
	OnLeaveChannel.Clear();
	OnUserJoined.Clear();
	OnUserOffline.Clear();
	OnRejoinChannelSuccess.Clear();
	OnProxyConnected.Clear();
	OnError.Clear();
	OnAudioQuality.Clear();
	OnLastmileProbeResult.Clear();
	OnAudioVolumeIndication.Clear();
	OnRtcStats.Clear();
	OnAudioDeviceStateChanged.Clear();
	OnAudioMixingPositionChanged.Clear();
	OnAudioMixingFinished.Clear();
	OnAudioEffectFinished.Clear();
	OnVideoDeviceStateChanged.Clear();
	OnNetworkQuality.Clear();
	OnIntraRequestReceived.Clear();
	OnUplinkNetworkInfoUpdated.Clear();
	OnDownlinkNetworkInfoUpdated.Clear();
	OnLastmileQuality.Clear();
	OnFirstLocalVideoFrame.Clear();
	OnFirstLocalVideoFramePublished.Clear();
	OnFirstRemoteVideoDecoded.Clear();
	OnVideoSizeChanged.Clear();
	OnLocalVideoStateChanged.Clear();
	OnRemoteVideoStateChanged.Clear();
	OnFirstRemoteVideoFrame.Clear();
	OnUserMuteAudio.Clear();
	OnUserMuteVideo.Clear();
	OnUserEnableVideo.Clear();
	OnUserStateChanged.Clear();
	OnUserEnableLocalVideo.Clear();
	OnLocalAudioStats.Clear();
	OnRemoteAudioStats.Clear();
	OnLocalVideoStats.Clear();
	OnRemoteVideoStats.Clear();
	OnCameraReady.Clear();
	OnCameraFocusAreaChanged.Clear();
	OnCameraExposureAreaChanged.Clear();
	OnFacePositionChanged.Clear();
	OnVideoStopped.Clear();
	OnAudioMixingStateChanged.Clear();
	OnRhythmPlayerStateChanged.Clear();
	OnConnectionLost.Clear();
	OnConnectionInterrupted.Clear();
	OnConnectionBanned.Clear();
	OnStreamMessage.Clear();
	OnStreamMessageError.Clear();
	OnRequestToken.Clear();
	OnTokenPrivilegeWillExpire.Clear();
	OnLicenseValidationFailure.Clear();
	OnFirstLocalAudioFramePublished.Clear();
	OnFirstRemoteAudioDecoded.Clear();
	OnFirstRemoteAudioFrame.Clear();
	OnLocalAudioStateChanged.Clear();
	OnRemoteAudioStateChanged.Clear();
	OnActiveSpeaker.Clear();
	OnContentInspectResult.Clear();
	OnSnapshotTaken.Clear();
	OnClientRoleChanged.Clear();
	OnClientRoleChangeFailed.Clear();
	OnAudioDeviceVolumeChanged.Clear();
	OnRtmpStreamingStateChanged.Clear();
	OnRtmpStreamingEvent.Clear();
	OnTranscodingUpdated.Clear();
	OnAudioRoutingChanged.Clear();
	OnChannelMediaRelayStateChanged.Clear();
	OnLocalPublishFallbackToAudioOnly.Clear();
	OnRemoteSubscribeFallbackToAudioOnly.Clear();
	OnRemoteAudioTransportStats.Clear();
	OnRemoteVideoTransportStats.Clear();
	OnConnectionStateChanged.Clear();
	OnWlAccMessage.Clear();
	OnWlAccStats.Clear();
	OnNetworkTypeChanged.Clear();
	OnEncryptionError.Clear();
	OnPermissionError.Clear();
	OnLocalUserRegistered.Clear();
	OnUserInfoUpdated.Clear();
	OnUserAccountUpdated.Clear();
	OnVideoRenderingTracingResult.Clear();
	OnLocalVideoTranscoderError.Clear();
	OnUploadLogResult.Clear();
	OnAudioSubscribeStateChanged.Clear();
	OnVideoSubscribeStateChanged.Clear();
	OnAudioPublishStateChanged.Clear();
	OnVideoPublishStateChanged.Clear();
	OnTranscodedStreamLayoutInfo.Clear();
	OnAudioMetadataReceived.Clear();
	OnExtensionEventWithContext.Clear();
	OnExtensionStartedWithContext.Clear();
	OnExtensionStoppedWithContext.Clear();
	OnExtensionErrorWithContext.Clear();
	OnSetRtmFlagResult.Clear();

}

#pragma region Native Callback Functions

void UAgoraBPuIRtcEngineEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	FString UEChannelName = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnJoinChannelSuccess.Broadcast(UEChannelName, (int64)uid, elapsed);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
{

	FRtcStats UERtcStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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
			OnLeaveChannel.Broadcast(UERtcStats);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserJoined.Broadcast((int64)uid, elapsed);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserOffline.Broadcast((int64)uid, (EUSER_OFFLINE_REASON_TYPE)reason);
		});
}


void UAgoraBPuIRtcEngineEventHandler::onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	FString UEChannelName = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRejoinChannelSuccess.Broadcast(UEChannelName, (int64)uid, elapsed);
		});
}




void UAgoraBPuIRtcEngineEventHandler::onProxyConnected(const char* channel, agora::rtc::uid_t uid, agora::rtc::PROXY_TYPE proxyType, const char* localProxyIp, int elapsed)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);
	FString UELocalProxyIp = UTF8_TO_TCHAR(localProxyIp);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnProxyConnected.Broadcast(UEChannel, (int64)uid, (EPROXY_TYPE)proxyType, UELocalProxyIp, elapsed);
		});

}



void UAgoraBPuIRtcEngineEventHandler::onError(int err, const char* msg)
{
	FString UEErrorMsg = UTF8_TO_TCHAR(msg);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnError.Broadcast(err, UEErrorMsg);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioQuality.Broadcast((int64)uid, quality, delay, lost);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onLastmileProbeResult(const LastmileProbeResult& result)
{
	FLastmileProbeResult UEProbeResult = result;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLastmileProbeResult.Broadcast(UEProbeResult);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	TArray<FAudioVolumeInfo> audioVolumeInfo;

	for (unsigned int i = 0; i < speakerNumber; i++)
	{
		audioVolumeInfo.Add(speakers[i]);
	}

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioVolumeIndication.Broadcast(audioVolumeInfo, totalVolume);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onRtcStats(const RtcStats& stats)
{
	FRtcStats UEStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRtcStats.Broadcast(UEStats);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{

	FString UEDeviceId = UTF8_TO_TCHAR(deviceId);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioDeviceStateChanged.Broadcast(UEDeviceId, deviceType, deviceState);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioMixingPositionChanged(int64_t position)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioMixingPositionChanged.Broadcast(position);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioMixingFinished() __deprecated
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioMixingFinished.Broadcast();
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioEffectFinished(int soundId)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioEffectFinished.Broadcast(soundId);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	FString UEDeviceId = UTF8_TO_TCHAR(deviceId);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnVideoDeviceStateChanged.Broadcast(UEDeviceId, deviceType, deviceState);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnNetworkQuality.Broadcast((int64)uid, txQuality, rxQuality);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onIntraRequestReceived()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnIntraRequestReceived.Broadcast();
		});
}

void UAgoraBPuIRtcEngineEventHandler::onUplinkNetworkInfoUpdated(const UplinkNetworkInfo& info)
{
	FUplinkNetworkInfo UEUplinkNetworkInfo = info;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUplinkNetworkInfoUpdated.Broadcast(UEUplinkNetworkInfo);
		});
}


void UAgoraBPuIRtcEngineEventHandler::onDownlinkNetworkInfoUpdated(const DownlinkNetworkInfo& info)
{
	FDownlinkNetworkInfo UEDownlinkNetworkInfo = info;
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnDownlinkNetworkInfoUpdated.Broadcast(UEDownlinkNetworkInfo);
		});
}



void UAgoraBPuIRtcEngineEventHandler::onLastmileQuality(int quality)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLastmileQuality.Broadcast(quality);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onFirstLocalVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE source, int width, int height, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstLocalVideoFrame.Broadcast((EVIDEO_SOURCE_TYPE)source, width, height, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onFirstLocalVideoFramePublished(agora::rtc::VIDEO_SOURCE_TYPE source, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstLocalVideoFramePublished.Broadcast((EVIDEO_SOURCE_TYPE)source, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onFirstRemoteVideoDecoded(agora::rtc::uid_t uid, int width, int height, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstRemoteVideoDecoded.Broadcast((int64)uid, width, height, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onVideoSizeChanged(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnVideoSizeChanged.Broadcast((EVIDEO_SOURCE_TYPE)sourceType, (int64)uid, width, height, rotation);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onLocalVideoStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_REASON reason)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalVideoStateChanged.Broadcast((EVIDEO_SOURCE_TYPE)source, (ELOCAL_VIDEO_STREAM_STATE)state, (ELOCAL_VIDEO_STREAM_REASON)reason);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteVideoStateChanged.Broadcast((int64)uid, (EREMOTE_VIDEO_STATE)state, (EREMOTE_VIDEO_STATE_REASON)reason, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onFirstRemoteVideoFrame(agora::rtc::uid_t uid, int width, int height, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstRemoteVideoFrame.Broadcast((int64)uid, width, height, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onUserMuteAudio(agora::rtc::uid_t uid, bool muted)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserMuteAudio.Broadcast((int64)uid, muted);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onUserMuteVideo(agora::rtc::uid_t uid, bool muted)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserMuteVideo.Broadcast((int64)uid, muted);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onUserEnableVideo(agora::rtc::uid_t uid, bool enabled)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserEnableVideo.Broadcast((int64)uid, enabled);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onUserStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_USER_STATE state)
{

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserStateChanged.Broadcast((int64)uid, FENUMWRAP_REMOTE_USER_STATE(state));
		});
}
void UAgoraBPuIRtcEngineEventHandler::onUserEnableLocalVideo(agora::rtc::uid_t uid, bool enabled)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserEnableLocalVideo.Broadcast((int64)uid, enabled);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onLocalAudioStats(const agora::rtc::LocalAudioStats& stats)
{
	FLocalAudioStats UELocalAudioStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalAudioStats.Broadcast(UELocalAudioStats);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats)
{
	FRemoteAudioStats UERemoteAudioStats = stats;
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteAudioStats.Broadcast(UERemoteAudioStats);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onLocalVideoStats(agora::rtc::VIDEO_SOURCE_TYPE source, const agora::rtc::LocalVideoStats& stats)
{
	FLocalVideoStats UELocalVideoStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalVideoStats.Broadcast((EVIDEO_SOURCE_TYPE)source, UELocalVideoStats);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	FRemoteVideoStats UERemoteVBideoStats = stats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteVideoStats.Broadcast(UERemoteVBideoStats);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onCameraReady()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnCameraReady.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onCameraFocusAreaChanged(int x, int y, int width, int height)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnCameraFocusAreaChanged.Broadcast(x, y, width, height);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onCameraExposureAreaChanged(int x, int y, int width, int height)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnCameraExposureAreaChanged.Broadcast(x, y, width, height);
		});
}

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
void UAgoraBPuIRtcEngineEventHandler::onFacePositionChanged(int imageWidth, int imageHeight, const agora::rtc::Rectangle* vecRectangle, const int* vecDistance, int numFaces)
{
	TArray<FRectangle> UEVecRectangle;
	for (int i = 0; i < numFaces; i++) {
		UEVecRectangle.Add(vecRectangle[i]);
	}
	TArray<int> UEVecDistance;
	FMemory::Memcpy(UEVecDistance.GetData(), vecDistance, numFaces * sizeof(int));

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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


			OnFacePositionChanged.Broadcast(imageWidth, imageHeight, UEVecRectangle, UEVecDistance, numFaces);
		});
}
#endif


void UAgoraBPuIRtcEngineEventHandler::onVideoStopped()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnVideoStopped.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onAudioMixingStateChanged(agora::rtc::AUDIO_MIXING_STATE_TYPE state, agora::rtc::AUDIO_MIXING_REASON_TYPE reason)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioMixingStateChanged.Broadcast(state, reason);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRhythmPlayerStateChanged(agora::rtc::RHYTHM_PLAYER_STATE_TYPE state, agora::rtc::RHYTHM_PLAYER_REASON reason)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRhythmPlayerStateChanged.Broadcast(state, reason);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onConnectionLost()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnConnectionLost.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onConnectionInterrupted()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnConnectionInterrupted.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onConnectionBanned()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnConnectionBanned.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onStreamMessage(agora::rtc::uid_t uid, int streamId, const char* data, size_t length, uint64_t sentTs)
{

	FString UEErrorMsg = UTF8_TO_TCHAR(data);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnStreamMessage.Broadcast((int64)uid, streamId, UEErrorMsg, length, sentTs);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onStreamMessageError(agora::rtc::uid_t uid, int streamId, int code, int missed, int cached)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnStreamMessageError.Broadcast((int64)uid, streamId, code, missed, cached);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRequestToken()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRequestToken.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onTokenPrivilegeWillExpire(const char* token)
{
	FString UEToken = UTF8_TO_TCHAR(token);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnTokenPrivilegeWillExpire.Broadcast(UEToken);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onLicenseValidationFailure(agora::LICENSE_ERROR_TYPE error)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLicenseValidationFailure.Broadcast((ELICENSE_ERROR_TYPE)error);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onFirstLocalAudioFramePublished(int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstLocalAudioFramePublished.Broadcast(elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onFirstRemoteAudioFrame(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstRemoteAudioFrame.Broadcast((int64)uid, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onFirstRemoteAudioDecoded(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnFirstRemoteAudioDecoded.Broadcast((int64)uid, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_REASON reason)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalAudioStateChanged.Broadcast((ELOCAL_AUDIO_STREAM_STATE)state, (ELOCAL_AUDIO_STREAM_REASON)reason);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteAudioStateChanged.Broadcast((int64)uid, (EREMOTE_AUDIO_STATE)state, (EREMOTE_AUDIO_STATE_REASON)reason, elapsed);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onActiveSpeaker(agora::rtc::uid_t uid)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnActiveSpeaker.Broadcast((int64)uid);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onContentInspectResult(agora::media::CONTENT_INSPECT_RESULT result)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnContentInspectResult.Broadcast((ECONTENT_INSPECT_RESULT)result);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onSnapshotTaken(agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	FString UEFilePath = UTF8_TO_TCHAR(filePath);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnSnapshotTaken.Broadcast((int64)uid, UEFilePath, width, height, errCode);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole, const agora::rtc::ClientRoleOptions& newRoleOptions)
{
	FClientRoleOptions UEClientRoleOptions = newRoleOptions;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnClientRoleChanged.Broadcast((ECLIENT_ROLE_TYPE)oldRole, (ECLIENT_ROLE_TYPE)newRole, UEClientRoleOptions);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onClientRoleChangeFailed(agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnClientRoleChangeFailed.Broadcast((ECLIENT_ROLE_CHANGE_FAILED_REASON)reason, (ECLIENT_ROLE_TYPE)currentRole);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onAudioDeviceVolumeChanged(agora::rtc::MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioDeviceVolumeChanged.Broadcast(deviceType, volume, muted);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_REASON reason)
{
	FString UEUrl = UTF8_TO_TCHAR(url);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRtmpStreamingStateChanged.Broadcast(UEUrl, (ERTMP_STREAM_PUBLISH_STATE)state, (ERTMP_STREAM_PUBLISH_REASON)reason);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode)
{
	FString UEUrl = UTF8_TO_TCHAR(url);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRtmpStreamingEvent.Broadcast(UEUrl, (ERTMP_STREAMING_EVENT)eventCode);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onTranscodingUpdated()
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnTranscodingUpdated.Broadcast();
		});
}
void UAgoraBPuIRtcEngineEventHandler::onAudioRoutingChanged(int routing)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioRoutingChanged.Broadcast(routing);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onChannelMediaRelayStateChanged(int state, int code)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnChannelMediaRelayStateChanged.Broadcast(state, code);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalPublishFallbackToAudioOnly.Broadcast(isFallbackOrRecover);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly(agora::rtc::uid_t uid, bool isFallbackOrRecover)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteSubscribeFallbackToAudioOnly.Broadcast((int64)uid, isFallbackOrRecover);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteAudioTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteAudioTransportStats.Broadcast((int64)uid, delay, lost, rxKBitRate);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onRemoteVideoTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnRemoteVideoTransportStats.Broadcast((int64)uid, delay, lost, rxKBitRate);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnConnectionStateChanged.Broadcast((ECONNECTION_STATE_TYPE)state, (ECONNECTION_CHANGED_REASON_TYPE)reason);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onWlAccMessage(agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	FString UEWlAccMsg = UTF8_TO_TCHAR(wlAccMsg);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnWlAccMessage.Broadcast((EWLACC_MESSAGE_REASON)reason, (EWLACC_SUGGEST_ACTION)action, UEWlAccMsg);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onWlAccStats(const agora::rtc::WlAccStats& currentStats, const agora::rtc::WlAccStats& averageStats)
{
	FWlAccStats UECurrentStats = currentStats;
	FWlAccStats UEAverageStats = averageStats;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnWlAccStats.Broadcast(UECurrentStats, UEAverageStats);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnNetworkTypeChanged.Broadcast(type);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onEncryptionError(agora::rtc::ENCRYPTION_ERROR_TYPE errorType)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnEncryptionError.Broadcast((EENCRYPTION_ERROR_TYPE)errorType);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onPermissionError(agora::rtc::PERMISSION_TYPE permissionType)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnPermissionError.Broadcast((EPERMISSION_TYPE)permissionType);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onLocalUserRegistered(agora::rtc::uid_t uid, const char* userAccount)
{
	FString UEUserAccount = UTF8_TO_TCHAR(userAccount);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalUserRegistered.Broadcast((int64)uid, UEUserAccount);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onUserInfoUpdated(agora::rtc::uid_t uid, const agora::rtc::UserInfo& info)
{
	FUserInfo UEInfo = info;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserInfoUpdated.Broadcast((int64)uid, UEInfo);
		});
}


void UAgoraBPuIRtcEngineEventHandler::onUserAccountUpdated(agora::rtc::uid_t uid, const char* userAccount)
{
	FString UEUserAccount = UTF8_TO_TCHAR(userAccount);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUserAccountUpdated.Broadcast((int64)uid, UEUserAccount);
		});
}


void UAgoraBPuIRtcEngineEventHandler::onVideoRenderingTracingResult(agora::rtc::uid_t uid, agora::rtc::MEDIA_TRACE_EVENT currentEvent, agora::rtc::VideoRenderingTracingInfo tracingInfo)
{

	FVideoRenderingTracingInfo UETracingInfo = tracingInfo;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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


			OnVideoRenderingTracingResult.Broadcast((int64)uid, (EMEDIA_TRACE_EVENT)currentEvent, UETracingInfo);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onLocalVideoTranscoderError(const agora::rtc::TranscodingVideoStream& stream, agora::rtc::VIDEO_TRANSCODER_ERROR error)
{
	FTranscodingVideoStream UEStream = stream;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnLocalVideoTranscoderError.Broadcast(UEStream, (EVIDEO_TRANSCODER_ERROR)error);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onUploadLogResult(const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	FString UERequestId = UTF8_TO_TCHAR(requestId);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnUploadLogResult.Broadcast(UERequestId, success, (EUPLOAD_ERROR_REASON)reason);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioSubscribeStateChanged.Broadcast(UEChannel, (int64)uid, (ESTREAM_SUBSCRIBE_STATE)oldState, (ESTREAM_SUBSCRIBE_STATE)newState, elapseSinceLastState);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnVideoSubscribeStateChanged.Broadcast(UEChannel, (int64)uid, (ESTREAM_SUBSCRIBE_STATE)oldState, (ESTREAM_SUBSCRIBE_STATE)newState, elapseSinceLastState);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioPublishStateChanged.Broadcast(UEChannel, (ESTREAM_PUBLISH_STATE)oldState, (ESTREAM_PUBLISH_STATE)newState, elapseSinceLastState);
		});
}
void UAgoraBPuIRtcEngineEventHandler::onVideoPublishStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnVideoPublishStateChanged.Broadcast((EVIDEO_SOURCE_TYPE)source, UEChannel, (ESTREAM_PUBLISH_STATE)oldState, (ESTREAM_PUBLISH_STATE)newState, elapseSinceLastState);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onTranscodedStreamLayoutInfo(agora::rtc::uid_t uid, int width, int height, int layoutCount, const agora::VideoLayout* layoutlist)
{
	TArray<FVideoLayout> UELayoutlist;
	for (int i = 0; i < layoutCount; i++) {
		UELayoutlist.Add(layoutlist[i]);
	}
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnTranscodedStreamLayoutInfo.Broadcast((int64)uid, width, height, layoutCount, UELayoutlist);
		});
}



void UAgoraBPuIRtcEngineEventHandler::onAudioMetadataReceived(agora::rtc::uid_t uid, const char* metadata, size_t length)
{
	FString UEMetadata = UTF8_TO_TCHAR(metadata);
	FString UELength = FString::Printf(TEXT("%llu"), length);

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioMetadataReceived.Broadcast((int64)uid, UEMetadata, UELength);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onExtensionEventWithContext(const ExtensionContext& context, const char* key, const char* value)
{
	FString UEKey = UTF8_TO_TCHAR(key);
	FString UEValue = UTF8_TO_TCHAR(value);
	FExtensionContext UEContext = context;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionEventWithContext.Broadcast(UEContext, UEKey,UEValue);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onExtensionStartedWithContext(const ExtensionContext& context)
{
	FExtensionContext UEContext = context;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionStartedWithContext.Broadcast(UEContext);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onExtensionStoppedWithContext(const ExtensionContext& context)
{
	FExtensionContext UEContext = context;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionStoppedWithContext.Broadcast(UEContext);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onExtensionErrorWithContext(const ExtensionContext& context, int error, const char* message)
{
	FString UEMessage = UTF8_TO_TCHAR(message);
	FExtensionContext UEContext = context;

	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionErrorWithContext.Broadcast(UEContext, error, UEMessage);
		});
}

void UAgoraBPuIRtcEngineEventHandler::onSetRtmFlagResult(int code)
{
	TWeakObjectPtr<UAgoraBPuIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnSetRtmFlagResult.Broadcast(code);
		});
}

#pragma endregion Native Callback Functions


#pragma region  BP Executor

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnJoinChannelSuccess_Implementation(const FString& Channel, int64 Uid, int Elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"),*FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLeaveChannel_Implementation(const FRtcStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserJoined_Implementation(int64 uid, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserOffline_Implementation(int64 uid, EUSER_OFFLINE_REASON_TYPE reason )
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRejoinChannelSuccess_Implementation(const FString& channel, int64 uid, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnProxyConnected_Implementation(const FString& channel, int64 uid, EPROXY_TYPE proxyType, const FString& localProxyIp, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnError_Implementation(int error, const FString& msg)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioQuality_Implementation(int64 uid, int quality, int delay, int lost)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLastmileProbeResult_Implementation(const FLastmileProbeResult& result)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioVolumeIndication_Implementation(const TArray<FAudioVolumeInfo>& speakers, int totalVolume)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRtcStats_Implementation(const FRtcStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioDeviceStateChanged_Implementation(const FString& deviceId, int deviceType, int deviceState)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMixingPositionChanged_Implementation(int64 position)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMixingFinished_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioEffectFinished_Implementation(int soundId)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoDeviceStateChanged_Implementation(const FString& deviceId, int deviceType, int deviceState)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnNetworkQuality_Implementation(int64 uid, int txQuality, int rxQuality)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnIntraRequestReceived_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUplinkNetworkInfoUpdated_Implementation(const FUplinkNetworkInfo& info)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnDownlinkNetworkInfoUpdated_Implementation(const FDownlinkNetworkInfo& info)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLastmileQuality_Implementation(int quality)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstLocalVideoFrame_Implementation(EVIDEO_SOURCE_TYPE source, int width, int height, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstLocalVideoFramePublished_Implementation(EVIDEO_SOURCE_TYPE source, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteVideoDecoded_Implementation(int64 uid, int width, int height, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoSizeChanged_Implementation(EVIDEO_SOURCE_TYPE sourceType, int64 uid, int width, int height, int rotation)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalVideoStateChanged_Implementation(EVIDEO_SOURCE_TYPE source, ELOCAL_VIDEO_STREAM_STATE state, ELOCAL_VIDEO_STREAM_REASON reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteVideoStateChanged_Implementation(int64 uid, EREMOTE_VIDEO_STATE state, EREMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteVideoFrame_Implementation(int64 uid, int width, int height, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserMuteAudio_Implementation(int64 uid, bool muted)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserMuteVideo_Implementation(int64 uid, bool muted)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserEnableVideo_Implementation(int64 uid, bool enabled)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserStateChanged_Implementation(int64 uid, FENUMWRAP_REMOTE_USER_STATE state)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserEnableLocalVideo_Implementation(int64 uid, bool enabled)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteAudioStats_Implementation(const FRemoteAudioStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalAudioStats_Implementation(const FLocalAudioStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalVideoStats_Implementation(EVIDEO_SOURCE_TYPE source, const FLocalVideoStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteVideoStats_Implementation(const FRemoteVideoStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnCameraReady_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnCameraFocusAreaChanged_Implementation(int x, int y, int width, int height)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnCameraExposureAreaChanged_Implementation(int x, int y, int width, int height)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFacePositionChanged_Implementation(int imageWidth, int imageHeight, const TArray<FRectangle>& vecRectangle, const TArray<int>& vecDistance, int numFaces)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoStopped_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMixingStateChanged_Implementation(FENUMWRAP_AUDIO_MIXING_STATE_TYPE state, FENUMWRAP_AUDIO_MIXING_REASON_TYPE reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRhythmPlayerStateChanged_Implementation(FENUMWRAP_RHYTHM_PLAYER_STATE_TYPE state, FENUMWRAP_RHYTHM_PLAYER_REASON reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionLost_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionInterrupted_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionBanned_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnStreamMessage_Implementation(int64 uid, int streamId, const FString& data, int length, int64 sentTs)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnStreamMessageError_Implementation(int64 uid, int streamId, int code, int missed, int cached)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRequestToken_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnTokenPrivilegeWillExpire_Implementation(const FString& token)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLicenseValidationFailure_Implementation(ELICENSE_ERROR_TYPE error)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstLocalAudioFramePublished_Implementation(int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteAudioDecoded_Implementation(int64 uid, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnFirstRemoteAudioFrame_Implementation(int64 uid, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalAudioStateChanged_Implementation(ELOCAL_AUDIO_STREAM_STATE state, ELOCAL_AUDIO_STREAM_REASON reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteAudioStateChanged_Implementation(int64 uid, EREMOTE_AUDIO_STATE state, EREMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnActiveSpeaker_Implementation(int64 uid)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnContentInspectResult_Implementation(ECONTENT_INSPECT_RESULT result)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnSnapshotTaken_Implementation(int64 uid, const FString& filePath, int width, int height, int errCode)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnClientRoleChanged_Implementation(ECLIENT_ROLE_TYPE oldRole, ECLIENT_ROLE_TYPE newRole, const FClientRoleOptions& newRoleOptions)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnClientRoleChangeFailed_Implementation(ECLIENT_ROLE_CHANGE_FAILED_REASON reason, ECLIENT_ROLE_TYPE currentRole)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioDeviceVolumeChanged_Implementation(FENUMWRAP_MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRtmpStreamingStateChanged_Implementation(const FString& url, ERTMP_STREAM_PUBLISH_STATE state, ERTMP_STREAM_PUBLISH_REASON reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRtmpStreamingEvent_Implementation(const FString& url, ERTMP_STREAMING_EVENT eventCode)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnTranscodingUpdated_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioRoutingChanged_Implementation(int routing)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnChannelMediaRelayStateChanged_Implementation(int state, int code)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalPublishFallbackToAudioOnly_Implementation(bool isFallbackOrRecover)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteSubscribeFallbackToAudioOnly_Implementation(int64 uid, bool isFallbackOrRecover)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteAudioTransportStats_Implementation(int64 uid, int delay, int lost, int rxKBitRate)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnRemoteVideoTransportStats_Implementation(int64 uid, int delay, int lost, int rxKBitRate)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnConnectionStateChanged_Implementation(ECONNECTION_STATE_TYPE state, ECONNECTION_CHANGED_REASON_TYPE reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnWlAccMessage_Implementation(EWLACC_MESSAGE_REASON reason, EWLACC_SUGGEST_ACTION action, const FString& wlAccMsg)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnWlAccStats_Implementation(const FWlAccStats& currentStats, const FWlAccStats& averageStats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnNetworkTypeChanged_Implementation(FENUMWRAP_NETWORK_TYPE type)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnEncryptionError_Implementation(EENCRYPTION_ERROR_TYPE errorType)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnPermissionError_Implementation(EPERMISSION_TYPE permissionType)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalUserRegistered_Implementation(int64 uid, const FString& userAccount)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserInfoUpdated_Implementation(int64 uid, const FUserInfo& info)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUserAccountUpdated_Implementation(int64 uid, const FString& userAccount)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoRenderingTracingResult_Implementation(int64 uid, EMEDIA_TRACE_EVENT currentEvent, const FVideoRenderingTracingInfo& tracingInfo)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnLocalVideoTranscoderError_Implementation(const FTranscodingVideoStream& stream, EVIDEO_TRANSCODER_ERROR error)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnUploadLogResult_Implementation(const FString& requestId, bool success, EUPLOAD_ERROR_REASON reason)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioSubscribeStateChanged_Implementation(const FString& channel, int64 uid, ESTREAM_SUBSCRIBE_STATE oldState, ESTREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoSubscribeStateChanged_Implementation(const FString& channel, int64 uid, ESTREAM_SUBSCRIBE_STATE oldState, ESTREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioPublishStateChanged_Implementation(const FString& channel, ESTREAM_PUBLISH_STATE oldState, ESTREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnVideoPublishStateChanged_Implementation(EVIDEO_SOURCE_TYPE source, const FString& channel, ESTREAM_PUBLISH_STATE oldState, ESTREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnTranscodedStreamLayoutInfo_Implementation(int64 uid, int width, int height, int layoutCount, const TArray<FVideoLayout>& layoutlist)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnAudioMetadataReceived_Implementation(int64 uid, const FString& metadata, const FString& length)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionEventWithContext_Implementation(const FExtensionContext& context, const FString& key, const FString& value)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionStartedWithContext_Implementation(const FExtensionContext& context)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionStoppedWithContext_Implementation(const FExtensionContext& context)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnExtensionErrorWithContext_Implementation(const FExtensionContext& context, int error, const FString& message)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIRtcEngineEventHandlerCBExecutor::OnSetRtmFlagResult_Implementation(int code)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

#pragma endregion  BP Executor
