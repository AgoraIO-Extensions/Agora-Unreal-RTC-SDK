// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandlerEx.h"

void UIRtcEngineEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnJoinChannelSuccessEx.Broadcast(rtcConnection, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onRejoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRejoinChannelSuccessEx.Broadcast(rtcConnection, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onAudioQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int quality, unsigned short delay, unsigned short lost)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioQualityEx.Broadcast(rtcConnection, (int64)remoteUid, quality, delay, lost);
	});
}
void UIRtcEngineEventHandlerEx::onAudioVolumeIndication(const agora::rtc::RtcConnection& connection, const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId = FString(connection.channelId);
	rtcConnection.localUid = connection.localUid;
	TArray<FAudioVolumeInfo> audioVolumeInfo;
	for (unsigned int i = 0; i < speakerNumber; i++)
	{
		FAudioVolumeInfo info;
		info.uid = speakers[i].uid;
		info.vad = speakers[i].vad;
		info.voicePitch = speakers[i].voicePitch;
		info.volume = speakers[i].volume;
		audioVolumeInfo.Add(info);
	}
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioVolumeIndicationEx.Broadcast(rtcConnection, audioVolumeInfo, totalVolume);
	});
}
void UIRtcEngineEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FRtcStats rtcStats;
	rtcStats.duration=stats.duration;
	rtcStats.txBytes=stats.txBytes;
	rtcStats.rxBytes=stats.rxBytes;
	rtcStats.txAudioBytes=stats.txAudioBytes;
	rtcStats.txVideoBytes=stats.txVideoBytes;
	rtcStats.rxAudioBytes=stats.rxAudioBytes;
	rtcStats.rxVideoBytes=stats.rxVideoBytes;
	rtcStats.txKBitRate=stats.txKBitRate;
	rtcStats.rxKBitRate=stats.rxKBitRate;
	rtcStats.rxAudioKBitRate=stats.rxAudioKBitRate;
	rtcStats.txAudioKBitRate=stats.txAudioKBitRate;
	rtcStats.rxVideoKBitRate=stats.rxVideoKBitRate;
	rtcStats.txVideoKBitRate=stats.txVideoKBitRate;
	rtcStats.lastmileDelay=stats.lastmileDelay;
	rtcStats.userCount=stats.userCount;
	rtcStats.cpuAppUsage=stats.cpuAppUsage;
	rtcStats.cpuTotalUsage=stats.cpuTotalUsage;
	rtcStats.gatewayRtt=stats.gatewayRtt;
	rtcStats.memoryAppUsageRatio=stats.memoryAppUsageRatio;
	rtcStats.memoryTotalUsageRatio=stats.memoryTotalUsageRatio;
	rtcStats.memoryAppUsageInKbytes=stats.memoryAppUsageInKbytes;
	rtcStats.connectTimeMs=stats.connectTimeMs;
	rtcStats.firstAudioPacketDuration=stats.firstAudioPacketDuration;
	rtcStats.firstVideoPacketDuration=stats.firstVideoPacketDuration;
	rtcStats.firstVideoKeyFramePacketDuration=stats.firstVideoKeyFramePacketDuration;
	rtcStats.packetsBeforeFirstKeyFramePacket=stats.packetsBeforeFirstKeyFramePacket;
	rtcStats.firstAudioPacketDurationAfterUnmute=stats.firstAudioPacketDurationAfterUnmute;
	rtcStats.firstVideoPacketDurationAfterUnmute=stats.firstVideoPacketDurationAfterUnmute;
	rtcStats.firstVideoKeyFramePacketDurationAfterUnmute=stats.firstVideoKeyFramePacketDurationAfterUnmute;
	rtcStats.firstVideoKeyFrameDecodedDurationAfterUnmute=stats.firstVideoKeyFrameDecodedDurationAfterUnmute;
	rtcStats.firstVideoKeyFrameRenderedDurationAfterUnmute=stats.firstVideoKeyFrameRenderedDurationAfterUnmute;
	rtcStats.txPacketLossRate=stats.txPacketLossRate;
	rtcStats.rxPacketLossRate=stats.rxPacketLossRate;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLeaveChannelEx.Broadcast(rtcConnection, rtcStats);
	});
}
void UIRtcEngineEventHandlerEx::onRtcStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FRtcStats rtcStats;
	rtcStats.duration=stats.duration;
	rtcStats.txBytes=stats.txBytes;
	rtcStats.rxBytes=stats.rxBytes;
	rtcStats.txAudioBytes=stats.txAudioBytes;
	rtcStats.txVideoBytes=stats.txVideoBytes;
	rtcStats.rxAudioBytes=stats.rxAudioBytes;
	rtcStats.rxVideoBytes=stats.rxVideoBytes;
	rtcStats.txKBitRate=stats.txKBitRate;
	rtcStats.rxKBitRate=stats.rxKBitRate;
	rtcStats.rxAudioKBitRate=stats.rxAudioKBitRate;
	rtcStats.txAudioKBitRate=stats.txAudioKBitRate;
	rtcStats.rxVideoKBitRate=stats.rxVideoKBitRate;
	rtcStats.txVideoKBitRate=stats.txVideoKBitRate;
	rtcStats.lastmileDelay=stats.lastmileDelay;
	rtcStats.userCount=stats.userCount;
	rtcStats.cpuAppUsage=stats.cpuAppUsage;
	rtcStats.cpuTotalUsage=stats.cpuTotalUsage;
	rtcStats.gatewayRtt=stats.gatewayRtt;
	rtcStats.memoryAppUsageRatio=stats.memoryAppUsageRatio;
	rtcStats.memoryTotalUsageRatio=stats.memoryTotalUsageRatio;
	rtcStats.memoryAppUsageInKbytes=stats.memoryAppUsageInKbytes;
	rtcStats.connectTimeMs=stats.connectTimeMs;
	rtcStats.firstAudioPacketDuration=stats.firstAudioPacketDuration;
	rtcStats.firstVideoPacketDuration=stats.firstVideoPacketDuration;
	rtcStats.firstVideoKeyFramePacketDuration=stats.firstVideoKeyFramePacketDuration;
	rtcStats.packetsBeforeFirstKeyFramePacket=stats.packetsBeforeFirstKeyFramePacket;
	rtcStats.firstAudioPacketDurationAfterUnmute=stats.firstAudioPacketDurationAfterUnmute;
	rtcStats.firstVideoPacketDurationAfterUnmute=stats.firstVideoPacketDurationAfterUnmute;
	rtcStats.firstVideoKeyFramePacketDurationAfterUnmute=stats.firstVideoKeyFramePacketDurationAfterUnmute;
	rtcStats.firstVideoKeyFrameDecodedDurationAfterUnmute=stats.firstVideoKeyFrameDecodedDurationAfterUnmute;
	rtcStats.firstVideoKeyFrameRenderedDurationAfterUnmute=stats.firstVideoKeyFrameRenderedDurationAfterUnmute;
	rtcStats.txPacketLossRate=stats.txPacketLossRate;
	rtcStats.rxPacketLossRate=stats.rxPacketLossRate;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRtcStatsEx.Broadcast(rtcConnection, rtcStats);
	});
}
void UIRtcEngineEventHandlerEx::onNetworkQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int txQuality, int rxQuality)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnNetworkQualityEx.Broadcast(rtcConnection, (int64)remoteUid, txQuality, rxQuality);
	});
}
void UIRtcEngineEventHandlerEx::onIntraRequestReceived(const agora::rtc::RtcConnection& connection)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnIntraRequestReceivedEx.Broadcast(rtcConnection);
	});
}

void UIRtcEngineEventHandlerEx::onFirstLocalVideoFramePublished(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstLocalVideoFramePublishedEx.Broadcast(rtcConnection, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onFirstRemoteVideoDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstRemoteVideoDecodedEx.Broadcast(rtcConnection, (int64)remoteUid, width, height, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onVideoSizeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnVideoSizeChangedEx.Broadcast(rtcConnection, (EVIDEO_SOURCE_TYPE)sourceType,(int64)uid, width, height, rotation);
	});
}
void UIRtcEngineEventHandlerEx::onLocalVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR errorCode)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalVideoStateChangedEx.Broadcast(rtcConnection, (ELOCAL_VIDEO_STREAM_STATE)state, (ELOCAL_VIDEO_STREAM_ERROR)errorCode);
	});
}
void UIRtcEngineEventHandlerEx::onRemoteVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteVideoStateChangedEx.Broadcast(rtcConnection, (int64)remoteUid, (EREMOTE_VIDEO_STATE)state, (EREMOTE_VIDEO_STATE_REASON)reason, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onFirstRemoteVideoFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstRemoteVideoFrameEx.Broadcast(rtcConnection, (int64)remoteUid, width, height, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserJoinedEx.Broadcast(rtcConnection, (int64)remoteUid, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserOfflineEx.Broadcast(rtcConnection, (int64)remoteUid, (EUSER_OFFLINE_REASON_TYPE)reason);
	});
}
void UIRtcEngineEventHandlerEx::onUserMuteAudio(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserMuteAudioEx.Broadcast(rtcConnection, (int64)remoteUid, muted);
	});
}
void UIRtcEngineEventHandlerEx::onUserMuteVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserMuteVideoEx.Broadcast(rtcConnection, (int64)remoteUid, muted);
	});
}
void UIRtcEngineEventHandlerEx::onUserEnableVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserEnableVideoEx.Broadcast(rtcConnection, (int64)remoteUid, enabled);
	});
}
void UIRtcEngineEventHandlerEx::onUserEnableLocalVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserEnableLocalVideoEx.Broadcast(rtcConnection, (int64)remoteUid, enabled);
	});
}
void UIRtcEngineEventHandlerEx::onUserStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, uint32_t state)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserStateChangedEx.Broadcast(rtcConnection, (int64)remoteUid, state);
	});
}
void UIRtcEngineEventHandlerEx::onLocalAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalAudioStats& stats)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;

	FLocalAudioStats localAudioStats;
	localAudioStats.numChannels=stats.numChannels;
	localAudioStats.sentSampleRate=stats.sentSampleRate;
	localAudioStats.sentBitrate=stats.sentBitrate;
	localAudioStats.internalCodec=stats.internalCodec;
	localAudioStats.txPacketLossRate=stats.txPacketLossRate;
	localAudioStats.audioDeviceDelay=stats.audioDeviceDelay;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalAudioStatsEx.Broadcast(rtcConnection, localAudioStats);
	});
}
void UIRtcEngineEventHandlerEx::onRemoteAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteAudioStats& stats)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FRemoteAudioStats remoteAudioStats;
	remoteAudioStats.uid=stats.uid;
	remoteAudioStats.quality=stats.quality;
	remoteAudioStats.networkTransportDelay=stats.networkTransportDelay;
	remoteAudioStats.jitterBufferDelay=stats.jitterBufferDelay;
	remoteAudioStats.audioLossRate=stats.audioLossRate;
	remoteAudioStats.numChannels=stats.numChannels;
	remoteAudioStats.receivedSampleRate=stats.receivedSampleRate;
	remoteAudioStats.receivedBitrate=stats.receivedBitrate;
	remoteAudioStats.totalFrozenTime=stats.totalFrozenTime;
	remoteAudioStats.frozenRate=stats.frozenRate;
	remoteAudioStats.mosValue=stats.mosValue;
	remoteAudioStats.totalActiveTime=stats.totalActiveTime;
	remoteAudioStats.publishDuration=stats.publishDuration;
	remoteAudioStats.qoeQuality=stats.qoeQuality;
	remoteAudioStats.qualityChangedReason=stats.qualityChangedReason;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteAudioStatsEx.Broadcast(rtcConnection, remoteAudioStats);
	});
}
void UIRtcEngineEventHandlerEx::onLocalVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalVideoStats& stats)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FLocalVideoStats localVideoStats;
	localVideoStats.uid=stats.uid;
	localVideoStats.sentBitrate=stats.sentBitrate;
	localVideoStats.sentFrameRate=stats.sentFrameRate;
	localVideoStats.captureFrameRate=stats.captureFrameRate;
	localVideoStats.captureFrameWidth=stats.captureFrameWidth;
	localVideoStats.captureFrameHeight=stats.captureFrameHeight;
	localVideoStats.regulatedCaptureFrameRate=stats.regulatedCaptureFrameRate;
	localVideoStats.regulatedCaptureFrameWidth=stats.regulatedCaptureFrameWidth;
	localVideoStats.regulatedCaptureFrameHeight=stats.regulatedCaptureFrameHeight;
	localVideoStats.encoderOutputFrameRate=stats.encoderOutputFrameRate;
	localVideoStats.encodedFrameWidth=stats.encodedFrameWidth;
	localVideoStats.encodedFrameHeight=stats.encodedFrameHeight;
	localVideoStats.rendererOutputFrameRate=stats.rendererOutputFrameRate;
	localVideoStats.targetBitrate=stats.targetBitrate;
	localVideoStats.targetFrameRate=stats.targetFrameRate;
	localVideoStats.qualityAdaptIndication=(EQUALITY_ADAPT_INDICATION)stats.qualityAdaptIndication;
	localVideoStats.encodedBitrate=stats.encodedBitrate;
	localVideoStats.encodedFrameCount=stats.encodedFrameCount;
	localVideoStats.codecType=(EVIDEO_CODEC_TYPE)stats.codecType;
	localVideoStats.txPacketLossRate=stats.txPacketLossRate;
	localVideoStats.captureBrightnessLevel=stats.captureBrightnessLevel;
	localVideoStats.dualStreamEnabled=stats.dualStreamEnabled;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalVideoStatsEx.Broadcast(rtcConnection, localVideoStats);
	});
}
void UIRtcEngineEventHandlerEx::onRemoteVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteVideoStats& stats)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FRemoteVideoStats remoteVideoStats;
	remoteVideoStats.uid=stats.uid;
	remoteVideoStats.e2eDelay = stats.e2eDelay;
	remoteVideoStats.width=stats.width;
	remoteVideoStats.height=stats.height;
	remoteVideoStats.receivedBitrate=stats.receivedBitrate;
	remoteVideoStats.decoderOutputFrameRate=stats.decoderOutputFrameRate;
	remoteVideoStats.rendererOutputFrameRate=stats.rendererOutputFrameRate;
	remoteVideoStats.frameLossRate=stats.frameLossRate;
	remoteVideoStats.packetLossRate=stats.packetLossRate;
	remoteVideoStats.rxStreamType=(EVIDEO_STREAM_TYPE)stats.rxStreamType;
	remoteVideoStats.totalFrozenTime=stats.totalFrozenTime;
	remoteVideoStats.frozenRate=stats.frozenRate;
	remoteVideoStats.avSyncTimeMs=stats.avSyncTimeMs;
	remoteVideoStats.totalActiveTime=stats.totalActiveTime;
	remoteVideoStats.publishDuration=stats.publishDuration;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteVideoStatsEx.Broadcast(rtcConnection, remoteVideoStats);
	});
}
void UIRtcEngineEventHandlerEx::onConnectionLost(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnConnectionLostEx.Broadcast(rtcConnection);
	});
}
void UIRtcEngineEventHandlerEx::onConnectionInterrupted(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnConnectionInterruptedEx.Broadcast(rtcConnection);
	});
}
void UIRtcEngineEventHandlerEx::onConnectionBanned(const agora::rtc::RtcConnection& connection)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnConnectionBannedEx.Broadcast(rtcConnection);
	});
}
void UIRtcEngineEventHandlerEx::onStreamMessage(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, const char* data, size_t length, uint64_t sentTs)
{

	char* tempdata = new char[length];
	FMemory::Memcpy(tempdata, data, length);
	std::string temp(tempdata);
	delete[] tempdata;

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnStreamMessageEx.Broadcast(rtcConnection, (int64)remoteUid, streamId, FString(UTF8_TO_TCHAR(temp.c_str())), length, sentTs);
	});
}
void UIRtcEngineEventHandlerEx::onStreamMessageError(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, int code, int missed, int cached)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnStreamMessageErrorEx.Broadcast(rtcConnection, (int64)remoteUid, streamId, code, missed, cached);
	});
}
void UIRtcEngineEventHandlerEx::onRequestToken(const agora::rtc::RtcConnection& connection)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRequestTokenEx.Broadcast(rtcConnection);
	});
}



void UIRtcEngineEventHandlerEx::onLicenseValidationFailure(const agora::rtc::RtcConnection& connection, agora::LICENSE_ERROR_TYPE reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	ELICENSE_ERROR_TYPE licenseErrorType = (ELICENSE_ERROR_TYPE)reason;

	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!SelfWeakPtr.IsValid())
				return;
			
			OnLicenseValidationFailureEx.Broadcast(rtcConnection, licenseErrorType);
		});
}

void UIRtcEngineEventHandlerEx::onTokenPrivilegeWillExpire(const agora::rtc::RtcConnection& connection, const char* token)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnTokenPrivilegeWillExpireEx.Broadcast(rtcConnection, FString(token));
	});
}
void UIRtcEngineEventHandlerEx::onFirstLocalAudioFramePublished(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstLocalAudioFramePublishedEx.Broadcast(rtcConnection, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onFirstRemoteAudioFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t userId, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstRemoteAudioFrameEx.Broadcast(rtcConnection, userId, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onFirstRemoteAudioDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstRemoteAudioDecodedEx.Broadcast(rtcConnection, (int64)uid, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onLocalAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalAudioStateChangedEx.Broadcast(rtcConnection, (ELOCAL_AUDIO_STREAM_STATE)state, (ELOCAL_AUDIO_STREAM_ERROR)error);
	});
}
void UIRtcEngineEventHandlerEx::onRemoteAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteAudioStateChangedEx.Broadcast(rtcConnection, remoteUid, (EREMOTE_AUDIO_STATE)state, (EREMOTE_AUDIO_STATE_REASON)reason, elapsed);
	});
}
void UIRtcEngineEventHandlerEx::onActiveSpeaker(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnActiveSpeakerEx.Broadcast(rtcConnection, (int64)uid);
	});
}
void UIRtcEngineEventHandlerEx::onClientRoleChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole, const agora::rtc::ClientRoleOptions& newRoleOptions)
{

	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;

	FClientRoleOptions options;
	options.audienceLatencyLevel = (EAUDIENCE_LATENCY_LEVEL_TYPE)newRoleOptions.audienceLatencyLevel;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnClientRoleChangedEx.Broadcast(rtcConnection, (ECLIENT_ROLE_TYPE)oldRole, (ECLIENT_ROLE_TYPE)newRole, options);
	});
}
void UIRtcEngineEventHandlerEx::onClientRoleChangeFailed(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnClientRoleChangeFailedEx.Broadcast(rtcConnection, (ECLIENT_ROLE_CHANGE_FAILED_REASON)reason, (ECLIENT_ROLE_TYPE)currentRole);
	});
}
void UIRtcEngineEventHandlerEx::onRemoteAudioTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteAudioTransportStatsEx.Broadcast(rtcConnection, remoteUid, delay, lost, rxKBitRate);
	});
}
void UIRtcEngineEventHandlerEx::onRemoteVideoTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteVideoTransportStatsEx.Broadcast(rtcConnection, (int64)remoteUid, delay, lost, rxKBitRate);
	});
}
void UIRtcEngineEventHandlerEx::onConnectionStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnConnectionStateChangedEx.Broadcast(rtcConnection, (ECONNECTION_STATE_TYPE)state, (ECONNECTION_CHANGED_REASON_TYPE)reason);
	});
}
void UIRtcEngineEventHandlerEx::onWlAccMessage(const agora::rtc::RtcConnection& connection, agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnWlAccMessageEx.Broadcast(rtcConnection, (EWLACC_MESSAGE_REASON)reason, (EWLACC_SUGGEST_ACTION)action, FString(wlAccMsg));
	});
}
void UIRtcEngineEventHandlerEx::onWlAccStats(const agora::rtc::RtcConnection& connection, agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FWlAccStats current;
	current.e2eDelayPercent=currentStats.e2eDelayPercent;
	current.frozenRatioPercent=currentStats.frozenRatioPercent;
	current.lossRatePercent=currentStats.lossRatePercent;
	FWlAccStats average;
	average.e2eDelayPercent=averageStats.e2eDelayPercent;
	average.frozenRatioPercent=averageStats.frozenRatioPercent;
	average.lossRatePercent=averageStats.lossRatePercent;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnWlAccStatsEx.Broadcast(rtcConnection, current, average);
	});
}
void UIRtcEngineEventHandlerEx::onNetworkTypeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::NETWORK_TYPE type)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnNetworkTypeChangedEx.Broadcast(rtcConnection,type);
	});
}
void UIRtcEngineEventHandlerEx::onEncryptionError(const agora::rtc::RtcConnection& connection, agora::rtc::ENCRYPTION_ERROR_TYPE errorType)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnEncryptionErrorEx.Broadcast(rtcConnection, (EENCRYPTION_ERROR_TYPE)errorType);
	});
}
void UIRtcEngineEventHandlerEx::onUploadLogResult(const agora::rtc::RtcConnection& connection, const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUploadLogResultEx.Broadcast(rtcConnection, FString(requestId), success, (EUPLOAD_ERROR_REASON)reason);
	});
}
void UIRtcEngineEventHandlerEx::onUserAccountUpdated(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, const char* userAccount)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserAccountUpdatedEx.Broadcast(rtcConnection, remoteUid, FString(userAccount));
	});
}
void UIRtcEngineEventHandlerEx::onSnapshotTaken(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnSnapshotTakenEx.Broadcast(rtcConnection, (int64)uid, FString(filePath), width, height, errCode);
	});
}

void UIRtcEngineEventHandlerEx::onVideoRenderingTracingResult(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, agora::rtc::MEDIA_TRACE_EVENT currentEvent, agora::rtc::VideoRenderingTracingInfo tracingInfo)
{
	TWeakObjectPtr<UIRtcEngineEventHandlerEx> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (!SelfWeakPtr.IsValid())
				return;

			FRtcConnection rtcConnection;
			rtcConnection.channelId = FString(connection.channelId);
			rtcConnection.localUid = connection.localUid;

			FVideoRenderingTracingInfo videoRenderingTracingInfo;
			videoRenderingTracingInfo.elapsedTime = tracingInfo.elapsedTime;
			videoRenderingTracingInfo.start2JoinChannel = tracingInfo.start2JoinChannel;
			videoRenderingTracingInfo.join2JoinSuccess = tracingInfo.join2JoinSuccess;
			videoRenderingTracingInfo.joinSuccess2RemoteJoined = tracingInfo.joinSuccess2RemoteJoined;
			videoRenderingTracingInfo.remoteJoined2SetView = tracingInfo.remoteJoined2SetView;
			videoRenderingTracingInfo.remoteJoined2UnmuteVideo = tracingInfo.remoteJoined2UnmuteVideo;
			videoRenderingTracingInfo.remoteJoined2PacketReceived = tracingInfo.remoteJoined2PacketReceived;

			OnVideoRenderingTracingResultEx.Broadcast(rtcConnection, (int64)uid, (EMEDIA_TRACE_EVENT)currentEvent, videoRenderingTracingInfo);
		});

}
