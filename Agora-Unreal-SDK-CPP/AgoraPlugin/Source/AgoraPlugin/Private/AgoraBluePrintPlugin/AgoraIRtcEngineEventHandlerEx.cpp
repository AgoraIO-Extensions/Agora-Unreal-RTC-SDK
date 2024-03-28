//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandlerEx.h"

void UIRtcEngineEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onRejoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onAudioQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int quality, unsigned short delay, unsigned short lost)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onAudioVolumeIndication(const agora::rtc::RtcConnection& connection, const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	FRtcConnection UERtcConnection = connection;

	TArray<FAudioVolumeInfo> audioVolumeInfo;
	for (unsigned int i = 0; i < speakerNumber; i++)
	{
		audioVolumeInfo.Add(speakers[i]);
	}

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnAudioVolumeIndicationEx.Broadcast(UERtcConnection, audioVolumeInfo, totalVolume);
		});
}
void UIRtcEngineEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	FRtcConnection UERtcConnection = connection;
	FRtcStats UERtcStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onRtcStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	FRtcConnection UERtcConnection = connection;
	FRtcStats UERtcStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onNetworkQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int txQuality, int rxQuality)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onIntraRequestReceived(const agora::rtc::RtcConnection& connection)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

void UIRtcEngineEventHandlerEx::onFirstLocalVideoFramePublished(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onFirstRemoteVideoDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onVideoSizeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnVideoSizeChangedEx.Broadcast(UERtcConnection, (EVIDEO_SOURCE_TYPE)sourceType, (int64)uid, width, height, rotation);
		});
}
void UIRtcEngineEventHandlerEx::onLocalVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_REASON reason)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnLocalVideoStateChangedEx.Broadcast(UERtcConnection, (ELOCAL_VIDEO_STREAM_STATE)state, (ELOCAL_VIDEO_STREAM_REASON)reason);
		});
}
void UIRtcEngineEventHandlerEx::onRemoteVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnRemoteVideoStateChangedEx.Broadcast(UERtcConnection, (int64)remoteUid, (EREMOTE_VIDEO_STATE)state, (EREMOTE_VIDEO_STATE_REASON)reason, elapsed);
		});
}
void UIRtcEngineEventHandlerEx::onFirstRemoteVideoFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnUserOfflineEx.Broadcast(UERtcConnection, (int64)remoteUid, (EUSER_OFFLINE_REASON_TYPE)reason);
		});
}
void UIRtcEngineEventHandlerEx::onUserMuteAudio(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onUserMuteVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onUserEnableVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onUserEnableLocalVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onUserStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, uint32_t state)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onLocalAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalAudioStats& stats)
{

	FRtcConnection UERtcConnection = connection;

	FLocalAudioStats UELocalAudioStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onRemoteAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteAudioStats& stats)
{

	FRtcConnection UERtcConnection = connection;

	FRemoteAudioStats UERemoteAudioStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onLocalVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalVideoStats& stats)
{

	FRtcConnection UERtcConnection = connection;
	FLocalVideoStats UELocalVideoStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onRemoteVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteVideoStats& stats)
{

	FRtcConnection UERtcConnection = connection;
	FRemoteVideoStats UERemoteVideoStats = stats;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onConnectionLost(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onConnectionInterrupted(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onConnectionBanned(const agora::rtc::RtcConnection& connection)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onStreamMessage(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, const char* data, size_t length, uint64_t sentTs)
{

	char* tempdata = new char[length];
	FMemory::Memcpy(tempdata, data, length);
	std::string temp(tempdata);
	delete[] tempdata;

	FRtcConnection UERtcConnection = connection;

	FString UETempData = FString(UTF8_TO_TCHAR(temp.c_str()));

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnStreamMessageEx.Broadcast(UERtcConnection, (int64)remoteUid, streamId, UETempData, length, sentTs);
		});
}
void UIRtcEngineEventHandlerEx::onStreamMessageError(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, int code, int missed, int cached)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onRequestToken(const agora::rtc::RtcConnection& connection)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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



void UIRtcEngineEventHandlerEx::onLicenseValidationFailure(const agora::rtc::RtcConnection& connection, agora::LICENSE_ERROR_TYPE reason)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnLicenseValidationFailureEx.Broadcast(UERtcConnection, (ELICENSE_ERROR_TYPE)reason);
		});
}

void UIRtcEngineEventHandlerEx::onTokenPrivilegeWillExpire(const agora::rtc::RtcConnection& connection, const char* token)
{
	FRtcConnection UERtcConnection = connection;

	FString UEToken = UTF8_TO_TCHAR(token);

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onFirstLocalAudioFramePublished(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onFirstRemoteAudioFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t userId, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnFirstRemoteAudioFrameEx.Broadcast(UERtcConnection, userId, elapsed);
		});
}
void UIRtcEngineEventHandlerEx::onFirstRemoteAudioDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, int elapsed)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onLocalAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_REASON reason)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnLocalAudioStateChangedEx.Broadcast(UERtcConnection, (ELOCAL_AUDIO_STREAM_STATE)state, (ELOCAL_AUDIO_STREAM_REASON)reason);
		});
}
void UIRtcEngineEventHandlerEx::onRemoteAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnRemoteAudioStateChangedEx.Broadcast(UERtcConnection, remoteUid, (EREMOTE_AUDIO_STATE)state, (EREMOTE_AUDIO_STATE_REASON)reason, elapsed);
		});
}
void UIRtcEngineEventHandlerEx::onActiveSpeaker(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid)
{

	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onClientRoleChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole, const agora::rtc::ClientRoleOptions& newRoleOptions)
{
	FRtcConnection UERtcConnection = connection;

	FClientRoleOptions UEClientRoleOptions = newRoleOptions;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnClientRoleChangedEx.Broadcast(UERtcConnection, (ECLIENT_ROLE_TYPE)oldRole, (ECLIENT_ROLE_TYPE)newRole, UEClientRoleOptions);
		});
}
void UIRtcEngineEventHandlerEx::onClientRoleChangeFailed(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnClientRoleChangeFailedEx.Broadcast(UERtcConnection, (ECLIENT_ROLE_CHANGE_FAILED_REASON)reason, (ECLIENT_ROLE_TYPE)currentRole);
		});
}
void UIRtcEngineEventHandlerEx::onRemoteAudioTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnRemoteAudioTransportStatsEx.Broadcast(UERtcConnection, remoteUid, delay, lost, rxKBitRate);
		});
}
void UIRtcEngineEventHandlerEx::onRemoteVideoTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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
void UIRtcEngineEventHandlerEx::onConnectionStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnConnectionStateChangedEx.Broadcast(UERtcConnection, (ECONNECTION_STATE_TYPE)state, (ECONNECTION_CHANGED_REASON_TYPE)reason);
		});
}
void UIRtcEngineEventHandlerEx::onWlAccMessage(const agora::rtc::RtcConnection& connection, agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	FRtcConnection UERtcConnection = connection;
	FString UEWlAccMsg = UTF8_TO_TCHAR(wlAccMsg);

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnWlAccMessageEx.Broadcast(UERtcConnection, (EWLACC_MESSAGE_REASON)reason, (EWLACC_SUGGEST_ACTION)action, UEWlAccMsg);
		});
}
void UIRtcEngineEventHandlerEx::onWlAccStats(const agora::rtc::RtcConnection& connection, agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats)
{
	FRtcConnection UERtcConnection = connection;
	FWlAccStats UEWlAccStatsCurrent = currentStats;
	FWlAccStats UEWlAccStatsAverage = averageStats;


	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnWlAccStatsEx.Broadcast(UERtcConnection, UEWlAccStatsCurrent, UEWlAccStatsAverage);
		});
}
void UIRtcEngineEventHandlerEx::onNetworkTypeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::NETWORK_TYPE type)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnNetworkTypeChangedEx.Broadcast(UERtcConnection, type);
		});
}
void UIRtcEngineEventHandlerEx::onEncryptionError(const agora::rtc::RtcConnection& connection, agora::rtc::ENCRYPTION_ERROR_TYPE errorType)
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnEncryptionErrorEx.Broadcast(UERtcConnection, (EENCRYPTION_ERROR_TYPE)errorType);
		});
}
void UIRtcEngineEventHandlerEx::onUploadLogResult(const agora::rtc::RtcConnection& connection, const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	FRtcConnection UERtcConnection = connection;
	FString UERequestId = UTF8_TO_TCHAR(requestId);

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnUploadLogResultEx.Broadcast(UERtcConnection, UERequestId, success, (EUPLOAD_ERROR_REASON)reason);
		});
}
void UIRtcEngineEventHandlerEx::onUserAccountUpdated(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, const char* remoteUserAccount)
{
	FRtcConnection UERtcConnection = connection;
	FString UERemoteUserAccount = UTF8_TO_TCHAR(remoteUserAccount);

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnUserAccountUpdatedEx.Broadcast(UERtcConnection, remoteUid, UERemoteUserAccount);
		});
}
void UIRtcEngineEventHandlerEx::onSnapshotTaken(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	FRtcConnection UERtcConnection = connection;
	FString UEFIlePath = UTF8_TO_TCHAR(filePath);


	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnSnapshotTakenEx.Broadcast(UERtcConnection, (int64)uid, UEFIlePath, width, height, errCode);
		});
}

void UIRtcEngineEventHandlerEx::onVideoRenderingTracingResult(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, agora::rtc::MEDIA_TRACE_EVENT currentEvent, agora::rtc::VideoRenderingTracingInfo tracingInfo)
{
	FRtcConnection UERtcConnection = connection;
	FVideoRenderingTracingInfo UEVideoRenderingTracingInfo = tracingInfo;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnVideoRenderingTracingResultEx.Broadcast(UERtcConnection, (int64)uid, (EMEDIA_TRACE_EVENT)currentEvent, UEVideoRenderingTracingInfo);
		});

}


void UIRtcEngineEventHandlerEx::onSetRtmFlagResult(const agora::rtc::RtcConnection& connection, int code) 
{
	FRtcConnection UERtcConnection = connection;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnSetRtmFlagResultEx.Broadcast(UERtcConnection, code);
		});
}

void UIRtcEngineEventHandlerEx::onTranscodedStreamLayoutInfo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, int width, int height, int layoutCount, const agora::VideoLayout* layoutlist)
{
	FRtcConnection UERtcConnection = connection;
	TArray<FVideoLayout> UELayoutlist;
	for (int i = 0; i < layoutCount; i++) {
		UELayoutlist.Add(layoutlist[i]);
	}
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnTranscodedStreamLayoutInfoEx.Broadcast(UERtcConnection,uid,width,height, UELayoutlist);
		});
}

void UIRtcEngineEventHandlerEx::onAudioMetadataReceived(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, const char* metadata, size_t length)
{
	FRtcConnection UERtcConnection = connection;
	FString UEMetadata = UTF8_TO_TCHAR(metadata);
	FString UELength = FString::Printf(TEXT("%llu"), length);

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
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

			OnAudioMetadataReceivedEx.Broadcast(UERtcConnection,uid, UEMetadata, UELength);
		});
}