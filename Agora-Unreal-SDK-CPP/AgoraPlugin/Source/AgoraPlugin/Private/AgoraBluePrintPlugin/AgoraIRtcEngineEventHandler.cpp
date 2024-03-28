//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandler.h"

void UIRtcEngineEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	FString UEChannelName = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	FString UEChannelName = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onProxyConnected(const char* channel, agora::rtc::uid_t uid, agora::rtc::PROXY_TYPE proxyType, const char* localProxyIp, int elapsed)
{
	FString UEChannelName = UTF8_TO_TCHAR(channel);
	FString UEProxyIp = UTF8_TO_TCHAR(localProxyIp);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnProxyConnected.Broadcast(UEChannelName, (int64)uid, (EPROXY_TYPE)proxyType, UEProxyIp, elapsed);
		});
}
void UIRtcEngineEventHandler::onError(int err, const char* msg)
{
	FString UEErrorMsg = UTF8_TO_TCHAR(msg);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioQuality(agora::rtc::uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLastmileProbeResult(const agora::rtc::LastmileProbeResult& result)
{
	FLastmileProbeResult UEProbeResult = result;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	TArray<FAudioVolumeInfo> audioVolumeInfo;

	for (unsigned int i = 0; i < speakerNumber; i++)
	{
		audioVolumeInfo.Add(speakers[i]);
	}

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	FRtcStats UEStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
			OnLeaveChannel.Broadcast(UEStats);
		});
}
void UIRtcEngineEventHandler::onRtcStats(const agora::rtc::RtcStats& stats)
{
	FRtcStats UEStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	FString UEDeviceId = UTF8_TO_TCHAR(deviceId);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onAudioMixingPositionChanged(int64_t position)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onAudioMixingFinished()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioEffectFinished(int soundId)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	FString UEDeviceId = UTF8_TO_TCHAR(deviceId);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onIntraRequestReceived()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUplinkNetworkInfoUpdated(const agora::rtc::UplinkNetworkInfo& info)
{
	FUplinkNetworkInfo UEUplinkNetworkInfo = info;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onDownlinkNetworkInfoUpdated(const agora::rtc::DownlinkNetworkInfo& info)
{
	FDownlinkNetworkInfo UEDownlinkNetworkInfo = info;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLastmileQuality(int quality)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFirstLocalVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE source, int width, int height, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFirstLocalVideoFramePublished(agora::rtc::VIDEO_SOURCE_TYPE source, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFirstRemoteVideoDecoded(agora::rtc::uid_t uid, int width, int height, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onVideoSizeChanged(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLocalVideoStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_REASON reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFirstRemoteVideoFrame(agora::rtc::uid_t uid, int width, int height, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserMuteAudio(agora::rtc::uid_t uid, bool muted)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserMuteVideo(agora::rtc::uid_t uid, bool muted)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserEnableVideo(agora::rtc::uid_t uid, bool enabled)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_USER_STATE state)
{
	
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserEnableLocalVideo(agora::rtc::uid_t uid, bool enabled)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLocalAudioStats(const agora::rtc::LocalAudioStats& stats)
{
	FLocalAudioStats UELocalAudioStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats)
{
	FRemoteAudioStats UERemoteAudioStats = stats;
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLocalVideoStats(agora::rtc::VIDEO_SOURCE_TYPE source, const agora::rtc::LocalVideoStats& stats)
{
	FLocalVideoStats UELocalVideoStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	FRemoteVideoStats UERemoteVBideoStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onCameraReady()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onCameraFocusAreaChanged(int x, int y, int width, int height)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onCameraExposureAreaChanged(int x, int y, int width, int height)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFacePositionChanged(int imageWidth, int imageHeight, const agora::rtc::Rectangle* vecRectangle, const int* vecDistance, int numFaces)
{
	TArray<FRectangle> UEVecRectangle;
	for(int i =0; i< numFaces;i++){
		UEVecRectangle.Add(vecRectangle[i]);
	}
	TArray<int> UEVecDistance;
	FMemory::Memcpy(UEVecDistance.GetData(), vecDistance, numFaces * sizeof(int));
	
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

#if defined(__ANDROID__)
void UIRtcEngineEventHandler::onCameraCapturerConfigurationChanged(int direction, int focalLengthType, int width, int height, int frameRate) 
{

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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


			OnCameraCapturerConfigurationChanged.Broadcast(direction,focalLengthType, width,height,frameRate);
		});
}
#endif // __ANDROID__

void UIRtcEngineEventHandler::onVideoStopped()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioMixingStateChanged(agora::rtc::AUDIO_MIXING_STATE_TYPE state, agora::rtc::AUDIO_MIXING_REASON_TYPE reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRhythmPlayerStateChanged(agora::rtc::RHYTHM_PLAYER_STATE_TYPE state, agora::rtc::RHYTHM_PLAYER_REASON reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onConnectionLost()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onConnectionInterrupted()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onConnectionBanned()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onStreamMessage(agora::rtc::uid_t uid, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	
	FString UEErrorMsg = UTF8_TO_TCHAR(data);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onStreamMessageError(agora::rtc::uid_t uid, int streamId, int code, int missed, int cached)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRequestToken()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onTokenPrivilegeWillExpire(const char* token)
{
	FString UEToken = UTF8_TO_TCHAR(token);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onLicenseValidationFailure(agora::LICENSE_ERROR_TYPE error)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onFirstLocalAudioFramePublished(int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFirstRemoteAudioFrame(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onFirstRemoteAudioDecoded(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_REASON reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onActiveSpeaker(agora::rtc::uid_t uid)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onContentInspectResult(agora::media::CONTENT_INSPECT_RESULT result)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onSnapshotTaken(agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	FString UEFilePath = UTF8_TO_TCHAR(filePath);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole, const agora::rtc::ClientRoleOptions& newRoleOptions)
{
	FClientRoleOptions UEClientRoleOptions = newRoleOptions;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onClientRoleChangeFailed(agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioDeviceVolumeChanged(agora::rtc::MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_REASON reason)
{
	FString UEUrl = UTF8_TO_TCHAR(url);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode)
{
	FString UEUrl = UTF8_TO_TCHAR(url);
	
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onTranscodingUpdated()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioRoutingChanged(int routing)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onChannelMediaRelayStateChanged(int state, int code)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly(agora::rtc::uid_t uid, bool isFallbackOrRecover)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteAudioTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onRemoteVideoTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onWlAccMessage(agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	FString UEWlAccMsg = UTF8_TO_TCHAR(wlAccMsg);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onWlAccStats(const agora::rtc::WlAccStats & currentStats, const agora::rtc::WlAccStats & averageStats)
{
	FWlAccStats UECurrentStats = currentStats;
	FWlAccStats UEAverageStats = averageStats;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onEncryptionError(agora::rtc::ENCRYPTION_ERROR_TYPE errorType)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onPermissionError(agora::rtc::PERMISSION_TYPE permissionType)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onLocalUserRegistered(agora::rtc::uid_t uid, const char* userAccount)
{
	FString UEUserAccount = UTF8_TO_TCHAR(userAccount);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onUserInfoUpdated(agora::rtc::uid_t uid, const agora::rtc::UserInfo& info)
{
	FUserInfo UEInfo = info;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onUploadLogResult(const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	FString UERequestId = UTF8_TO_TCHAR(requestId);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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
void UIRtcEngineEventHandler::onVideoPublishStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	FString UEChannel = UTF8_TO_TCHAR(channel);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

void UIRtcEngineEventHandler::onTranscodedStreamLayoutInfo(agora::rtc::uid_t uid, int width, int height, int layoutCount, const agora::VideoLayout* layoutlist)
{
	TArray<FVideoLayout> UELayoutlist;
	for(int i =0 ; i< layoutCount; i++){
		UELayoutlist.Add(layoutlist[i]);
	}
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnTranscodedStreamLayoutInfo.Broadcast((int64)uid, width, height,  layoutCount, UELayoutlist);
		});
}

void UIRtcEngineEventHandler::onAudioMetadataReceived(agora::rtc::uid_t uid, const char* metadata, size_t length)
{
	FString UEMetadata = UTF8_TO_TCHAR(metadata);
	FString UELength = FString::Printf(TEXT("%llu"), length);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnAudioMetadataReceived.Broadcast((int64)uid, UEMetadata,UELength);
		});
}


void UIRtcEngineEventHandler::onExtensionEvent(const char* provider, const char* extension, const char* key, const char* value)
{
	FString UEProvider = UTF8_TO_TCHAR(provider);
	FString UEExtension = UTF8_TO_TCHAR(extension);
	FString UEKey = UTF8_TO_TCHAR(key);
	FString UEValue = UTF8_TO_TCHAR(value);


	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionEvent.Broadcast(UEProvider, UEExtension, UEKey, UEValue);
		});
}
void UIRtcEngineEventHandler::onExtensionStarted(const char* provider, const char* extension)
{
	FString UEProvider = UTF8_TO_TCHAR(provider);
	FString UEExtension = UTF8_TO_TCHAR(extension);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionStarted.Broadcast(UEProvider, UEExtension);
		});
}
void UIRtcEngineEventHandler::onExtensionStopped(const char* provider, const char* extension)
{
	FString UEProvider = UTF8_TO_TCHAR(provider);
	FString UEExtension = UTF8_TO_TCHAR(extension);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionStopped.Broadcast(UEProvider, UEExtension);
		});
}
void UIRtcEngineEventHandler::onExtensionError(const char* provider, const char* extension, int error, const char* message)
{
	FString UEProvider = UTF8_TO_TCHAR(provider);
	FString UEExtension = UTF8_TO_TCHAR(extension);
	FString UEMessage = UTF8_TO_TCHAR(message);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

			OnExtensionError.Broadcast(UEProvider, UEExtension, error, UEMessage);
		});
}
void UIRtcEngineEventHandler::onUserAccountUpdated(agora::rtc::uid_t uid, const char* userAccount)
{
	FString UEUserAccount = UTF8_TO_TCHAR(userAccount);

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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


void UIRtcEngineEventHandler::onLocalVideoTranscoderError(const agora::rtc::TranscodingVideoStream& stream, agora::rtc::VIDEO_TRANSCODER_ERROR error)
{
	FTranscodingVideoStream UEStream = stream;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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


void UIRtcEngineEventHandler::onVideoRenderingTracingResult(agora::rtc::uid_t uid, agora::rtc::MEDIA_TRACE_EVENT currentEvent, agora::rtc::VideoRenderingTracingInfo tracingInfo)
{

	FVideoRenderingTracingInfo UETracingInfo = tracingInfo;

	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
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

int UIMetadataObserver::getMaxMetadataSize()
{
	TWeakObjectPtr<UIMetadataObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return DEFAULT_METADATA_SIZE_IN_BYTE;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			GetMaxMetadataSize.Broadcast();
		});
	return DEFAULT_METADATA_SIZE_IN_BYTE;
}
bool UIMetadataObserver::onReadyToSendMetadata(agora::rtc::IMetadataObserver::Metadata& metadata, agora::rtc::VIDEO_SOURCE_TYPE source_type)
{
	FAgoraMetadata data;
	TWeakObjectPtr<UIMetadataObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return false;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnReadyToSendMetadata.Broadcast(data, (EVIDEO_SOURCE_TYPE)source_type);
		});

	metadata.uid = data.uid;
	metadata.size = data.size;
	unsigned char* tempdata = new unsigned char[data.size];
	for (int i = 0; i < data.size; i++)
	{
		tempdata[i] = data.buffer[i];
	}
	FMemory::Memcpy(metadata.buffer, tempdata, data.size);
	delete[] tempdata;
	metadata.timeStampMs = data.timeStampMs;
	return true;
}
void UIMetadataObserver::onMetadataReceived(const agora::rtc::IMetadataObserver::Metadata& metadata)
{

	FAgoraMetadata UEMetaData = metadata ;
	TWeakObjectPtr<UIMetadataObserver> SelfWeakPtr(this);
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

			OnMetadataReceived.Broadcast(UEMetaData);
		});
}
void UIDirectCdnStreamingEventHandler::onDirectCdnStreamingStateChanged(agora::rtc::DIRECT_CDN_STREAMING_STATE state, agora::rtc::DIRECT_CDN_STREAMING_REASON reason, const char* message)
{
	FString UEMessage = UTF8_TO_TCHAR(message);

	TWeakObjectPtr<UIDirectCdnStreamingEventHandler> SelfWeakPtr(this);
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

			OnDirectCdnStreamingStateChanged.Broadcast((EDIRECT_CDN_STREAMING_STATE)state, (EDIRECT_CDN_STREAMING_REASON)reason, UEMessage);
		});
}
void UIDirectCdnStreamingEventHandler::onDirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats& stats)
{
	FDirectCdnStreamingStats UEStats = stats;

	TWeakObjectPtr<UIDirectCdnStreamingEventHandler> SelfWeakPtr(this);
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

			OnDirectCdnStreamingStats.Broadcast(UEStats);
		});
}

