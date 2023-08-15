// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandler.h"

void UIRtcEngineEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnJoinChannelSuccess.Broadcast(FString(channel), (int64)uid, elapsed);	
	});

}
void UIRtcEngineEventHandler::onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRejoinChannelSuccess.Broadcast(FString(channel), (int64)uid, elapsed);
	});
	
}
void UIRtcEngineEventHandler::onProxyConnected(const char* channel, agora::rtc::uid_t uid, agora::rtc::PROXY_TYPE proxyType, const char* localProxyIp, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnProxyConnected.Broadcast(FString(channel), (int64)uid, (EPROXY_TYPE)proxyType, FString(localProxyIp), elapsed);
	});
}
void UIRtcEngineEventHandler::onError(int err, const char* msg)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnError.Broadcast(err, FString(msg));
	});
}
void UIRtcEngineEventHandler::onAudioQuality(agora::rtc::uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioQuality.Broadcast((int64)uid, quality, delay, lost);
	});
}
void UIRtcEngineEventHandler::onLastmileProbeResult(const agora::rtc::LastmileProbeResult& result)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FLastmileProbeResult lastmileProbeResult;
		lastmileProbeResult.state = (ELASTMILE_PROBE_RESULT_STATE)result.state;
		FLastmileProbeOneWayResult uplinkReport;
		uplinkReport.availableBandwidth =result.uplinkReport.availableBandwidth;
		uplinkReport.jitter = result.uplinkReport.jitter;
		uplinkReport.packetLossRate =result.uplinkReport.packetLossRate;
		lastmileProbeResult.uplinkReport = uplinkReport;
		FLastmileProbeOneWayResult downlinkReport;
		downlinkReport.availableBandwidth = result.downlinkReport.availableBandwidth;
		downlinkReport.jitter = result.downlinkReport.jitter;
		downlinkReport.packetLossRate = result.downlinkReport.packetLossRate;
		lastmileProbeResult.downlinkReport = downlinkReport;
		lastmileProbeResult.rtt = result.rtt;
		OnLastmileProbeResult.Broadcast(lastmileProbeResult);
	});
}
void UIRtcEngineEventHandler::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
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
		OnAudioVolumeIndication.Broadcast(audioVolumeInfo, totalVolume);
	});
}
void UIRtcEngineEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FRtcStats rtcStats;
		rtcStats.duration = stats.duration;
		rtcStats.txBytes = stats.txBytes;
		rtcStats.rxBytes = stats.rxBytes;
		rtcStats.txAudioBytes = stats.txAudioBytes;
		rtcStats.txVideoBytes = stats.txVideoBytes;
		rtcStats.rxAudioBytes = stats.rxAudioBytes;
		rtcStats.rxVideoBytes = stats.rxVideoBytes;
		rtcStats.txKBitRate = stats.txKBitRate;
		rtcStats.rxKBitRate = stats.rxKBitRate;
		rtcStats.rxAudioKBitRate = stats.rxAudioKBitRate;
		rtcStats.txAudioKBitRate = stats.txAudioKBitRate;
		rtcStats.rxVideoKBitRate = stats.rxVideoKBitRate;
		rtcStats.txVideoKBitRate = stats.txVideoKBitRate;
		rtcStats.lastmileDelay = stats.lastmileDelay;
		rtcStats.userCount = stats.userCount;
		rtcStats.cpuAppUsage = stats.cpuAppUsage;
		rtcStats.cpuTotalUsage = stats.cpuTotalUsage;
		rtcStats.gatewayRtt = stats.gatewayRtt;
		rtcStats.memoryAppUsageRatio = stats.memoryAppUsageRatio;
		rtcStats.memoryTotalUsageRatio = stats.memoryTotalUsageRatio;
		rtcStats.memoryAppUsageInKbytes = stats.memoryAppUsageInKbytes;
		rtcStats.connectTimeMs = stats.connectTimeMs;
		rtcStats.firstAudioPacketDuration = stats.firstAudioPacketDuration;
		rtcStats.firstVideoPacketDuration = stats.firstVideoPacketDuration;
		rtcStats.firstVideoKeyFramePacketDuration = stats.firstVideoKeyFramePacketDuration;
		rtcStats.packetsBeforeFirstKeyFramePacket = stats.packetsBeforeFirstKeyFramePacket;
		rtcStats.firstAudioPacketDurationAfterUnmute = stats.firstAudioPacketDurationAfterUnmute;
		rtcStats.firstVideoPacketDurationAfterUnmute = stats.firstVideoPacketDurationAfterUnmute;
		rtcStats.firstVideoKeyFramePacketDurationAfterUnmute = stats.firstVideoKeyFramePacketDurationAfterUnmute;
		rtcStats.firstVideoKeyFrameDecodedDurationAfterUnmute = stats.firstVideoKeyFrameDecodedDurationAfterUnmute;
		rtcStats.firstVideoKeyFrameRenderedDurationAfterUnmute = stats.firstVideoKeyFrameRenderedDurationAfterUnmute;
		rtcStats.txPacketLossRate = stats.txPacketLossRate;
		rtcStats.rxPacketLossRate = stats.rxPacketLossRate;
		OnLeaveChannel.Broadcast(rtcStats);
	});
}
void UIRtcEngineEventHandler::onRtcStats(const agora::rtc::RtcStats& stats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FRtcStats rtcStats;
		rtcStats.duration = stats.duration;
		rtcStats.txBytes = stats.txBytes;
		rtcStats.rxBytes = stats.rxBytes;
		rtcStats.txAudioBytes = stats.txAudioBytes;
		rtcStats.txVideoBytes = stats.txVideoBytes;
		rtcStats.rxAudioBytes = stats.rxAudioBytes;
		rtcStats.rxVideoBytes = stats.rxVideoBytes;
		rtcStats.txKBitRate = stats.txKBitRate;
		rtcStats.rxKBitRate = stats.rxKBitRate;
		rtcStats.rxAudioKBitRate = stats.rxAudioKBitRate;
		rtcStats.txAudioKBitRate = stats.txAudioKBitRate;
		rtcStats.rxVideoKBitRate = stats.rxVideoKBitRate;
		rtcStats.txVideoKBitRate = stats.txVideoKBitRate;
		rtcStats.lastmileDelay = stats.lastmileDelay;
		rtcStats.userCount = stats.userCount;
		rtcStats.cpuAppUsage = stats.cpuAppUsage;
		rtcStats.cpuTotalUsage = stats.cpuTotalUsage;
		rtcStats.gatewayRtt = stats.gatewayRtt;
		rtcStats.memoryAppUsageRatio = stats.memoryAppUsageRatio;
		rtcStats.memoryTotalUsageRatio = stats.memoryTotalUsageRatio;
		rtcStats.memoryAppUsageInKbytes = stats.memoryAppUsageInKbytes;
		rtcStats.connectTimeMs = stats.connectTimeMs;
		rtcStats.firstAudioPacketDuration = stats.firstAudioPacketDuration;
		rtcStats.firstVideoPacketDuration = stats.firstVideoPacketDuration;
		rtcStats.firstVideoKeyFramePacketDuration = stats.firstVideoKeyFramePacketDuration;
		rtcStats.packetsBeforeFirstKeyFramePacket = stats.packetsBeforeFirstKeyFramePacket;
		rtcStats.firstAudioPacketDurationAfterUnmute = stats.firstAudioPacketDurationAfterUnmute;
		rtcStats.firstVideoPacketDurationAfterUnmute = stats.firstVideoPacketDurationAfterUnmute;
		rtcStats.firstVideoKeyFramePacketDurationAfterUnmute = stats.firstVideoKeyFramePacketDurationAfterUnmute;
		rtcStats.firstVideoKeyFrameDecodedDurationAfterUnmute = stats.firstVideoKeyFrameDecodedDurationAfterUnmute;
		rtcStats.firstVideoKeyFrameRenderedDurationAfterUnmute = stats.firstVideoKeyFrameRenderedDurationAfterUnmute;
		rtcStats.txPacketLossRate = stats.txPacketLossRate;
		rtcStats.rxPacketLossRate = stats.rxPacketLossRate;
		OnRtcStats.Broadcast(rtcStats);
	});
}
void UIRtcEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioDeviceStateChanged.Broadcast(FString(deviceId), deviceType, deviceState);
	});
}

void UIRtcEngineEventHandler::onAudioMixingPositionChanged(int64_t position)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioEffectFinished.Broadcast(soundId);
	});
}
void UIRtcEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnVideoDeviceStateChanged.Broadcast(FString(deviceId), deviceType, deviceState);
	});
}

void UIRtcEngineEventHandler::onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnIntraRequestReceived.Broadcast();
	});
}
void UIRtcEngineEventHandler::onUplinkNetworkInfoUpdated(const agora::rtc::UplinkNetworkInfo& info)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FUplinkNetworkInfo uplinkNetworkInfo;
		uplinkNetworkInfo.video_encoder_target_bitrate_bps = info.video_encoder_target_bitrate_bps;
		OnUplinkNetworkInfoUpdated.Broadcast(uplinkNetworkInfo);
	});
}
void UIRtcEngineEventHandler::onDownlinkNetworkInfoUpdated(const agora::rtc::DownlinkNetworkInfo& info)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FDownlinkNetworkInfo downlinkNetworkInfo;
		downlinkNetworkInfo.lastmile_buffer_delay_time_ms = info.lastmile_buffer_delay_time_ms;
		downlinkNetworkInfo.bandwidth_estimation_bps = info.bandwidth_estimation_bps;
		downlinkNetworkInfo.total_downscale_level_count = info.total_downscale_level_count;
		FPeerDownlinkInfo peer_downlink_info;
		if (info.peer_downlink_info!=nullptr)
		{
			peer_downlink_info.current_downscale_level = (EREMOTE_VIDEO_DOWNSCALE_LEVEL)info.peer_downlink_info->current_downscale_level;
			peer_downlink_info.expected_bitrate_bps = info.peer_downlink_info->expected_bitrate_bps;
			peer_downlink_info.stream_type = (EVIDEO_STREAM_TYPE)info.peer_downlink_info->stream_type;
			peer_downlink_info.uid = info.peer_downlink_info->uid;
		}
		downlinkNetworkInfo.peer_downlink_info = peer_downlink_info;
		downlinkNetworkInfo.total_received_video_count = info.total_received_video_count;
		OnDownlinkNetworkInfoUpdated.Broadcast(downlinkNetworkInfo);
	});
}
void UIRtcEngineEventHandler::onLastmileQuality(int quality)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnVideoSizeChanged.Broadcast((EVIDEO_SOURCE_TYPE)sourceType,(int64)uid, width, height, rotation);
	});
}
void UIRtcEngineEventHandler::onLocalVideoStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalVideoStateChanged.Broadcast((EVIDEO_SOURCE_TYPE)source, (ELOCAL_VIDEO_STREAM_STATE)state, (ELOCAL_VIDEO_STREAM_ERROR)error);
	});
}
void UIRtcEngineEventHandler::onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteVideoStateChanged.Broadcast((int64)uid, (EREMOTE_VIDEO_STATE)state, (EREMOTE_VIDEO_STATE_REASON)reason, elapsed);
	});
}
void UIRtcEngineEventHandler::onFirstRemoteVideoFrame(agora::rtc::uid_t userId, int width, int height, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstRemoteVideoFrame.Broadcast((int64)userId, width, height, elapsed);
	});
}
void UIRtcEngineEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserMuteAudio.Broadcast((int64)uid, muted);
	});
}
void UIRtcEngineEventHandler::onUserMuteVideo(agora::rtc::uid_t userId, bool muted)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserMuteVideo.Broadcast((int64)userId, muted);
	});
}
void UIRtcEngineEventHandler::onUserEnableVideo(agora::rtc::uid_t uid, bool enabled)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserEnableVideo.Broadcast((int64)uid, enabled);
	});
}
void UIRtcEngineEventHandler::onUserStateChanged(agora::rtc::uid_t uid, uint32_t state)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserStateChanged.Broadcast((int64)uid, state);
	});
}
void UIRtcEngineEventHandler::onUserEnableLocalVideo(agora::rtc::uid_t uid, bool enabled)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserEnableLocalVideo.Broadcast((int64)uid, enabled);
	});
}
void UIRtcEngineEventHandler::onLocalAudioStats(const agora::rtc::LocalAudioStats& stats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FLocalAudioStats localAudioStats;
		localAudioStats.numChannels = stats.numChannels;
		localAudioStats.sentSampleRate = stats.sentSampleRate;
		localAudioStats.sentBitrate = stats.sentBitrate;
		localAudioStats.internalCodec = stats.internalCodec;
		localAudioStats.txPacketLossRate = stats.txPacketLossRate;
		localAudioStats.audioDeviceDelay = stats.audioDeviceDelay;
		OnLocalAudioStats.Broadcast(localAudioStats);
	});
}
void UIRtcEngineEventHandler::onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FRemoteAudioStats remoteAudioStats;
		remoteAudioStats.uid = stats.uid;
		remoteAudioStats.quality = stats.quality;
		remoteAudioStats.networkTransportDelay = stats.networkTransportDelay;
		remoteAudioStats.jitterBufferDelay = stats.jitterBufferDelay;
		remoteAudioStats.audioLossRate = stats.audioLossRate;
		remoteAudioStats.numChannels = stats.numChannels;
		remoteAudioStats.receivedSampleRate = stats.receivedSampleRate;
		remoteAudioStats.receivedBitrate = stats.receivedBitrate;
		remoteAudioStats.totalFrozenTime = stats.totalFrozenTime;
		remoteAudioStats.frozenRate = stats.frozenRate;
		remoteAudioStats.mosValue = stats.mosValue;
		remoteAudioStats.totalActiveTime = stats.totalActiveTime;
		remoteAudioStats.publishDuration = stats.publishDuration;
		remoteAudioStats.qoeQuality = stats.qoeQuality;
		remoteAudioStats.qualityChangedReason = stats.qualityChangedReason;
		OnRemoteAudioStats.Broadcast(remoteAudioStats);
	});
}
void UIRtcEngineEventHandler::onLocalVideoStats(agora::rtc::VIDEO_SOURCE_TYPE source, const agora::rtc::LocalVideoStats& stats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FLocalVideoStats localVideoStats;
		localVideoStats.uid = stats.uid;
		localVideoStats.sentBitrate = stats.sentBitrate;
		localVideoStats.sentFrameRate = stats.sentFrameRate;
		localVideoStats.captureFrameRate = stats.captureFrameRate;
		localVideoStats.captureFrameWidth = stats.captureFrameWidth;
		localVideoStats.captureFrameHeight = stats.captureFrameHeight;
		localVideoStats.regulatedCaptureFrameRate = stats.regulatedCaptureFrameRate;
		localVideoStats.regulatedCaptureFrameWidth = stats.regulatedCaptureFrameWidth;
		localVideoStats.regulatedCaptureFrameHeight = stats.regulatedCaptureFrameHeight;
		localVideoStats.encoderOutputFrameRate = stats.encoderOutputFrameRate;
		localVideoStats.encodedFrameWidth = stats.encodedFrameWidth;
		localVideoStats.encodedFrameHeight = stats.encodedFrameHeight;
		localVideoStats.rendererOutputFrameRate = stats.rendererOutputFrameRate;
		localVideoStats.targetBitrate = stats.targetBitrate;
		localVideoStats.targetFrameRate = stats.targetFrameRate;
		localVideoStats.qualityAdaptIndication = (EQUALITY_ADAPT_INDICATION)stats.qualityAdaptIndication;
		localVideoStats.encodedBitrate = stats.encodedBitrate;
		localVideoStats.encodedFrameCount = stats.encodedFrameCount;
		localVideoStats.codecType = (EVIDEO_CODEC_TYPE)stats.codecType;
		localVideoStats.txPacketLossRate = stats.txPacketLossRate;
		localVideoStats.captureBrightnessLevel =stats.captureBrightnessLevel;
		localVideoStats.dualStreamEnabled = stats.dualStreamEnabled;
		OnLocalVideoStats.Broadcast((EVIDEO_SOURCE_TYPE)source, localVideoStats);
	});
}
void UIRtcEngineEventHandler::onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FRemoteVideoStats remoteVideoStats;
		remoteVideoStats.uid = stats.uid;
		remoteVideoStats.e2eDelay = stats.e2eDelay;
		remoteVideoStats.width = stats.width;
		remoteVideoStats.height = stats.height;
		remoteVideoStats.receivedBitrate = stats.receivedBitrate;
		remoteVideoStats.decoderOutputFrameRate = stats.decoderOutputFrameRate;
		remoteVideoStats.rendererOutputFrameRate = stats.rendererOutputFrameRate;
		remoteVideoStats.frameLossRate = stats.frameLossRate;
		remoteVideoStats.packetLossRate = stats.packetLossRate;
		remoteVideoStats.rxStreamType = (EVIDEO_STREAM_TYPE)stats.rxStreamType;
		remoteVideoStats.totalFrozenTime = stats.totalFrozenTime;
		remoteVideoStats.frozenRate = stats.frozenRate;
		remoteVideoStats.avSyncTimeMs = stats.avSyncTimeMs;
		remoteVideoStats.totalActiveTime = stats.totalActiveTime;
		remoteVideoStats.publishDuration = stats.publishDuration;
		OnRemoteVideoStats.Broadcast(remoteVideoStats);
	});
}
void UIRtcEngineEventHandler::onCameraReady()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnCameraExposureAreaChanged.Broadcast(x, y, width, height);
	});
}
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
void UIRtcEngineEventHandler::onFacePositionChanged(int imageWidth, int imageHeight, const agora::rtc::Rectangle* vecRectangle, const int* vecDistance, int numFaces)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FRectangle rectangle;
		rectangle.x = vecRectangle->x;
		rectangle.y = vecRectangle->y;
		rectangle.width = vecRectangle->width;
		rectangle.height = vecRectangle->height;
		TArray<int> vecDis;
		int* tempdata = new int[numFaces];
		FMemory::Memcpy(tempdata, vecDistance, numFaces * sizeof(int));
		for (int i = 0; i < numFaces; i++)
		{
			vecDis[i] = tempdata[i];
		}
		delete[] tempdata;

		OnFacePositionChanged.Broadcast(imageWidth, imageHeight, rectangle, vecDis, numFaces);
	});
}
#endif
void UIRtcEngineEventHandler::onVideoStopped()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioMixingStateChanged.Broadcast(state,reason);
	});
}
void UIRtcEngineEventHandler::onRhythmPlayerStateChanged(agora::rtc::RHYTHM_PLAYER_STATE_TYPE state, agora::rtc::RHYTHM_PLAYER_ERROR_TYPE errorCode)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRhythmPlayerStateChanged.Broadcast(state, errorCode);
	});
}
void UIRtcEngineEventHandler::onConnectionLost()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnConnectionBanned.Broadcast();
	});
}
void UIRtcEngineEventHandler::onStreamMessage(agora::rtc::uid_t userId, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	char* tempdata = new char[length];
	FMemory::Memcpy(tempdata, data, length);
	std::string temp(tempdata);
	delete[] tempdata;
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnStreamMessage.Broadcast((int64)userId, streamId, FString(UTF8_TO_TCHAR(temp.c_str())), length, sentTs);
	});
}
void UIRtcEngineEventHandler::onStreamMessageError(agora::rtc::uid_t userId, int streamId, int code, int missed, int cached)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnStreamMessageError.Broadcast((int64)userId, streamId, code, missed, cached);
	});
}
void UIRtcEngineEventHandler::onRequestToken()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRequestToken.Broadcast();
	});
}
void UIRtcEngineEventHandler::onTokenPrivilegeWillExpire(const char* token)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnTokenPrivilegeWillExpire.Broadcast(FString(token));
	});
}

void UIRtcEngineEventHandler::onLicenseValidationFailure(agora::LICENSE_ERROR_TYPE error)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnFirstRemoteAudioDecoded.Broadcast((int64)uid, elapsed);
	});
}
void UIRtcEngineEventHandler::onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalAudioStateChanged.Broadcast((ELOCAL_AUDIO_STREAM_STATE)state, (ELOCAL_AUDIO_STREAM_ERROR)error);
	});
}
void UIRtcEngineEventHandler::onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRemoteAudioStateChanged.Broadcast((int64)uid, (EREMOTE_AUDIO_STATE)state, (EREMOTE_AUDIO_STATE_REASON)reason, elapsed);
	});
}
void UIRtcEngineEventHandler::onActiveSpeaker(agora::rtc::uid_t userId)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnActiveSpeaker.Broadcast((int64)userId);
	});
}
void UIRtcEngineEventHandler::onContentInspectResult(agora::media::CONTENT_INSPECT_RESULT result)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnContentInspectResult.Broadcast((ECONTENT_INSPECT_RESULT)result);
	});
}
void UIRtcEngineEventHandler::onSnapshotTaken(agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnSnapshotTaken.Broadcast((int64)uid, FString(filePath), width, height, errCode);
	});
}
void UIRtcEngineEventHandler::onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole, const agora::rtc::ClientRoleOptions& newRoleOptions)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FClientRoleOptions roleoptions;
		roleoptions.audienceLatencyLevel = (EAUDIENCE_LATENCY_LEVEL_TYPE)newRoleOptions.audienceLatencyLevel;
		OnClientRoleChanged.Broadcast((ECLIENT_ROLE_TYPE)oldRole, (ECLIENT_ROLE_TYPE)newRole, roleoptions);
	});
}
void UIRtcEngineEventHandler::onClientRoleChangeFailed(agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioDeviceVolumeChanged.Broadcast(deviceType, volume, muted);
	});
}
void UIRtcEngineEventHandler::onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR_TYPE errCode)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRtmpStreamingStateChanged.Broadcast(FString(url), (ERTMP_STREAM_PUBLISH_STATE)state, (ERTMP_STREAM_PUBLISH_ERROR_TYPE)errCode);
	});
}
void UIRtcEngineEventHandler::onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnRtmpStreamingEvent.Broadcast(FString(url), (ERTMP_STREAMING_EVENT)eventCode);
	});
}
void UIRtcEngineEventHandler::onTranscodingUpdated()
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnChannelMediaRelayStateChanged.Broadcast(state, code);
	});	
}
void UIRtcEngineEventHandler::onChannelMediaRelayEvent(int code)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnChannelMediaRelayEvent.Broadcast(code);
	});
}
void UIRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnConnectionStateChanged.Broadcast((ECONNECTION_STATE_TYPE)state, (ECONNECTION_CHANGED_REASON_TYPE)reason);
	});
}
void UIRtcEngineEventHandler::onWlAccMessage(agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnWlAccMessage.Broadcast((EWLACC_MESSAGE_REASON)reason, (EWLACC_SUGGEST_ACTION)action, FString(wlAccMsg));
	});
}
void UIRtcEngineEventHandler::onWlAccStats(agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FWlAccStats current;
		current.e2eDelayPercent = currentStats.e2eDelayPercent;
		current.frozenRatioPercent = currentStats.frozenRatioPercent;
		current.lossRatePercent = currentStats.lossRatePercent;
		FWlAccStats average;
		average.e2eDelayPercent = averageStats.e2eDelayPercent;
		average.frozenRatioPercent = averageStats.frozenRatioPercent;
		average.lossRatePercent = averageStats.lossRatePercent;
		OnWlAccStats.Broadcast(current, average);
	});
}
void UIRtcEngineEventHandler::onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnPermissionError.Broadcast((EPERMISSION_TYPE)permissionType);
	});
}
void UIRtcEngineEventHandler::onLocalUserRegistered(agora::rtc::uid_t uid, const char* userAccount)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnLocalUserRegistered.Broadcast((int64)uid, FString(userAccount));
	});
}
void UIRtcEngineEventHandler::onUserInfoUpdated(agora::rtc::uid_t uid, const agora::rtc::UserInfo& info)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FUserInfo userInfo;
		userInfo.uid = info.uid;
		FString userAccount(info.userAccount);
		OnUserInfoUpdated.Broadcast((int64)uid, userInfo);
	});
}
void UIRtcEngineEventHandler::onUploadLogResult(const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUploadLogResult.Broadcast(FString(requestId), success, (EUPLOAD_ERROR_REASON)reason);
	});
}
void UIRtcEngineEventHandler::onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioSubscribeStateChanged.Broadcast(FString(channel), (int64)uid, (ESTREAM_SUBSCRIBE_STATE)oldState, (ESTREAM_SUBSCRIBE_STATE)newState, elapseSinceLastState);
	});
}
void UIRtcEngineEventHandler::onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnVideoSubscribeStateChanged.Broadcast(FString(channel), (int64)uid, (ESTREAM_SUBSCRIBE_STATE)oldState, (ESTREAM_SUBSCRIBE_STATE)newState, elapseSinceLastState);
	});
}
void UIRtcEngineEventHandler::onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnAudioPublishStateChanged.Broadcast(FString(channel), (ESTREAM_PUBLISH_STATE)oldState, (ESTREAM_PUBLISH_STATE)newState, elapseSinceLastState);
	});
}
void UIRtcEngineEventHandler::onVideoPublishStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnVideoPublishStateChanged.Broadcast((EVIDEO_SOURCE_TYPE)source, FString(channel), (ESTREAM_PUBLISH_STATE)oldState, (ESTREAM_PUBLISH_STATE)newState, elapseSinceLastState);
	});
}
void UIRtcEngineEventHandler::onExtensionEvent(const char* provider, const char* extension, const char* key, const char* value)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnExtensionEvent.Broadcast(FString(provider), FString(extension), FString(key), FString(value));
	});
}
void UIRtcEngineEventHandler::onExtensionStarted(const char* provider, const char* extension)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnExtensionStarted.Broadcast(FString(provider), FString(extension));
	});
}
void UIRtcEngineEventHandler::onExtensionStopped(const char* provider, const char* extension)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnExtensionStopped.Broadcast(FString(provider), FString(extension));
	});
}
void UIRtcEngineEventHandler::onExtensionError(const char* provider, const char* extension, int error, const char* message)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnExtensionError.Broadcast(FString(provider), FString(extension), error, FString(message));
	});
}
void UIRtcEngineEventHandler::onUserAccountUpdated(agora::rtc::uid_t uid, const char* userAccount)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnUserAccountUpdated.Broadcast((int64)uid, FString(userAccount));
	});
}


void UIRtcEngineEventHandler::onLocalVideoTranscoderError(const agora::rtc::TranscodingVideoStream& stream, agora::rtc::VIDEO_TRANSCODER_ERROR error)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FTranscodingVideoStream videoStream;
		videoStream.sourceType = (EMEDIA_SOURCE_TYPE)stream.sourceType;
		videoStream.remoteUserUid = stream.remoteUserUid;
		videoStream.imageUrl = FString(stream.imageUrl);
		videoStream.x = stream.x;
		videoStream.y = stream.y;
		videoStream.width = stream.width;
		videoStream.height = stream.height;
		videoStream.zOrder = stream.zOrder;
		videoStream.alpha = stream.alpha;
		videoStream.mirror = stream.mirror;
		OnLocalVideoTranscoderError.Broadcast(videoStream, (EVIDEO_TRANSCODER_ERROR)error);
	});
}


void UIRtcEngineEventHandler::onVideoRenderingTracingResult(agora::rtc::uid_t uid, agora::rtc::MEDIA_TRACE_EVENT currentEvent, agora::rtc::VideoRenderingTracingInfo tracingInfo)
{
	TWeakObjectPtr<UIRtcEngineEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
			FVideoRenderingTracingInfo videoRenderingTracingInfo;
			videoRenderingTracingInfo.elapsedTime = tracingInfo.elapsedTime;
			videoRenderingTracingInfo.start2JoinChannel = tracingInfo.start2JoinChannel;
			videoRenderingTracingInfo.join2JoinSuccess = tracingInfo.join2JoinSuccess;
			videoRenderingTracingInfo.joinSuccess2RemoteJoined = tracingInfo.joinSuccess2RemoteJoined;
			videoRenderingTracingInfo.remoteJoined2SetView = tracingInfo.remoteJoined2SetView;
			videoRenderingTracingInfo.remoteJoined2UnmuteVideo = tracingInfo.remoteJoined2UnmuteVideo;
			videoRenderingTracingInfo.remoteJoined2PacketReceived = tracingInfo.remoteJoined2PacketReceived;
			OnVideoRenderingTracingResult.Broadcast((int64)uid,(EMEDIA_TRACE_EVENT)currentEvent, videoRenderingTracingInfo);
		});
}

int UIMetadataObserver::getMaxMetadataSize()
{
	TWeakObjectPtr<UIMetadataObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return DEFAULT_METADATA_SIZE_IN_BYTE;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	
	AsyncTask(ENamedThreads::GameThread, [=]()
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
	TWeakObjectPtr<UIMetadataObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FAgoraMetadata data;
		data.uid = metadata.uid;
		data.size = metadata.size;
		unsigned char* tempdata = new unsigned char[data.size];
		FMemory::Memcpy((void*)tempdata,metadata.buffer,metadata.size);
		TArray<int64> callBackdata;
		for (int i = 0; i < data.size; i++)
		{
			callBackdata.Add(tempdata[i]);
		}
		delete[] tempdata;
		data.buffer = callBackdata;
		data.timeStampMs = metadata.timeStampMs;
		OnMetadataReceived.Broadcast(data);
	});
}
void UIDirectCdnStreamingEventHandler::onDirectCdnStreamingStateChanged(agora::rtc::DIRECT_CDN_STREAMING_STATE state, agora::rtc::DIRECT_CDN_STREAMING_ERROR error, const char* message)
{
	TWeakObjectPtr<UIDirectCdnStreamingEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		OnDirectCdnStreamingStateChanged.Broadcast((EDIRECT_CDN_STREAMING_STATE)state, (EDIRECT_CDN_STREAMING_ERROR)error, FString(message));
	});
}
void UIDirectCdnStreamingEventHandler::onDirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats& stats)
{
	TWeakObjectPtr<UIDirectCdnStreamingEventHandler> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
		
		FDirectCdnStreamingStats directCdnStreamingStats;
		directCdnStreamingStats.videoWidth = stats.videoWidth;
		directCdnStreamingStats.videoHeight = stats.videoHeight;
		directCdnStreamingStats.fps = stats.fps;
		directCdnStreamingStats.videoBitrate = stats.videoBitrate;
		directCdnStreamingStats.audioBitrate = stats.audioBitrate;
		OnDirectCdnStreamingStats.Broadcast(directCdnStreamingStats);
	});
}

