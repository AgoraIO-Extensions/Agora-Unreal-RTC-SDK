// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraIRtcEngineEventHandler.h"

AIRtcEngineEventHandler::AIRtcEngineEventHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AIRtcEngineEventHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIRtcEngineEventHandler::BeginPlay()
{
	Super::BeginPlay();
}

void AIRtcEngineEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	OnJoinChannelSuccess.Broadcast(FString(channel), uid, elapsed);
}
void AIRtcEngineEventHandler::onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	OnRejoinChannelSuccess.Broadcast(FString(channel), uid, elapsed);
}
void AIRtcEngineEventHandler::onProxyConnected(const char* channel, agora::rtc::uid_t uid, agora::rtc::PROXY_TYPE proxyType, const char* localProxyIp, int elapsed)
{
	OnProxyConnected.Broadcast(FString(channel), uid, (EPROXY_TYPE)proxyType, FString(localProxyIp), elapsed);
}
void AIRtcEngineEventHandler::onError(int err, const char* msg)
{
	OnError.Broadcast(err, FString(msg));
}
void AIRtcEngineEventHandler::onAudioQuality(agora::rtc::uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	OnAudioQuality.Broadcast(uid, quality, delay, lost);
}
void AIRtcEngineEventHandler::onLastmileProbeResult(const agora::rtc::LastmileProbeResult& result)
{
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
}
void AIRtcEngineEventHandler::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	FAudioVolumeInfo audioVolumeInfo;
	if (speakers!=nullptr)
	{
		audioVolumeInfo.uid = speakers->uid;
		audioVolumeInfo.volume = speakers->volume;
		audioVolumeInfo.vad = speakers->vad;
		audioVolumeInfo.voicePitch = speakers->voicePitch;
	}
	OnAudioVolumeIndication.Broadcast(audioVolumeInfo, speakerNumber, totalVolume);
}
void AIRtcEngineEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
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
}
void AIRtcEngineEventHandler::onRtcStats(const agora::rtc::RtcStats& stats)
{
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
}
void AIRtcEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	OnAudioDeviceStateChanged.Broadcast(FString(deviceId), deviceType, deviceState);
}
void AIRtcEngineEventHandler::onAudioMixingFinished()
{
	OnAudioMixingFinished.Broadcast();
}
void AIRtcEngineEventHandler::onAudioEffectFinished(int soundId)
{
	OnAudioEffectFinished.Broadcast(soundId);
}
void AIRtcEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	OnVideoDeviceStateChanged.Broadcast(FString(deviceId), deviceType, deviceState);
}
void AIRtcEngineEventHandler::onMediaDeviceChanged(int deviceType)
{
	OnMediaDeviceChanged.Broadcast(deviceType);
}
void AIRtcEngineEventHandler::onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality)
{
	OnNetworkQuality.Broadcast(uid, txQuality, rxQuality);
}
void AIRtcEngineEventHandler::onIntraRequestReceived()
{
	OnIntraRequestReceived.Broadcast();
}
void AIRtcEngineEventHandler::onUplinkNetworkInfoUpdated(const agora::rtc::UplinkNetworkInfo& info)
{
	FUplinkNetworkInfo uplinkNetworkInfo;
	uplinkNetworkInfo.video_encoder_target_bitrate_bps = info.video_encoder_target_bitrate_bps;
	OnUplinkNetworkInfoUpdated.Broadcast(uplinkNetworkInfo);
}
void AIRtcEngineEventHandler::onDownlinkNetworkInfoUpdated(const agora::rtc::DownlinkNetworkInfo& info)
{
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
}
void AIRtcEngineEventHandler::onLastmileQuality(int quality)
{
	OnLastmileQuality.Broadcast(quality);
}
void AIRtcEngineEventHandler::onFirstLocalVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE source, int width, int height, int elapsed)
{
	OnFirstLocalVideoFrame.Broadcast((EVIDEO_SOURCE_TYPE)source, width, height, elapsed);
}
void AIRtcEngineEventHandler::onFirstLocalVideoFramePublished(agora::rtc::VIDEO_SOURCE_TYPE source, int elapsed)
{
	OnFirstLocalVideoFramePublished.Broadcast((EVIDEO_SOURCE_TYPE)source, elapsed);
}
void AIRtcEngineEventHandler::onFirstRemoteVideoDecoded(agora::rtc::uid_t uid, int width, int height, int elapsed)
{
	OnFirstRemoteVideoDecoded.Broadcast(uid, width, height, elapsed);
}
void AIRtcEngineEventHandler::onVideoSizeChanged(agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation)
{
	OnVideoSizeChanged.Broadcast((EVIDEO_SOURCE_TYPE)sourceType,uid, width, height, rotation);
}
void AIRtcEngineEventHandler::onLocalVideoStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error)
{
	OnLocalVideoStateChanged.Broadcast((EVIDEO_SOURCE_TYPE)source, (ELOCAL_VIDEO_STREAM_STATE)state, (ELOCAL_VIDEO_STREAM_ERROR)error);
}
void AIRtcEngineEventHandler::onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	OnRemoteVideoStateChanged.Broadcast(uid, (EREMOTE_VIDEO_STATE)state, (EREMOTE_VIDEO_STATE_REASON)reason, elapsed);
}
void AIRtcEngineEventHandler::onFirstRemoteVideoFrame(agora::rtc::uid_t userId, int width, int height, int elapsed)
{
	OnFirstRemoteVideoFrame.Broadcast(userId, width, height, elapsed);
}
void AIRtcEngineEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
	OnUserJoined.Broadcast(uid, elapsed);
}
void AIRtcEngineEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	OnUserOffline.Broadcast(uid, (EUSER_OFFLINE_REASON_TYPE)reason);
}
void AIRtcEngineEventHandler::onUserMuteAudio(agora::rtc::uid_t uid, bool muted)
{
	OnUserMuteAudio.Broadcast(uid, muted);
}
void AIRtcEngineEventHandler::onUserMuteVideo(agora::rtc::uid_t userId, bool muted)
{
	OnUserMuteVideo.Broadcast(userId, muted);
}
void AIRtcEngineEventHandler::onUserEnableVideo(agora::rtc::uid_t uid, bool enabled)
{
	OnUserEnableVideo.Broadcast(uid, enabled);
}
void AIRtcEngineEventHandler::onUserStateChanged(agora::rtc::uid_t uid, uint32_t state)
{
	OnUserStateChanged.Broadcast(uid, state);
}
void AIRtcEngineEventHandler::onUserEnableLocalVideo(agora::rtc::uid_t uid, bool enabled)
{
	OnUserEnableLocalVideo.Broadcast(uid, enabled);
}
void AIRtcEngineEventHandler::onApiCallExecuted(int err, const char* api, const char* result)
{
	OnApiCallExecuted.Broadcast(err, FString(api), FString(result));
}
void AIRtcEngineEventHandler::onLocalAudioStats(const agora::rtc::LocalAudioStats& stats)
{
	FLocalAudioStats localAudioStats;
	localAudioStats.numChannels = stats.numChannels;
	localAudioStats.sentSampleRate = stats.sentSampleRate;
	localAudioStats.sentBitrate = stats.sentBitrate;
	localAudioStats.internalCodec = stats.internalCodec;
	localAudioStats.txPacketLossRate = stats.txPacketLossRate;
	localAudioStats.audioDeviceDelay = stats.audioDeviceDelay;
	OnLocalAudioStats.Broadcast(localAudioStats);
}
void AIRtcEngineEventHandler::onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats)
{
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
}
void AIRtcEngineEventHandler::onLocalVideoStats(agora::rtc::VIDEO_SOURCE_TYPE source, const agora::rtc::LocalVideoStats& stats)
{
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
	localVideoStats.captureBrightnessLevel = (ECAPTURE_BRIGHTNESS_LEVEL_TYPE)stats.captureBrightnessLevel;
	localVideoStats.dualStreamEnabled = stats.dualStreamEnabled;
	OnLocalVideoStats.Broadcast((EVIDEO_SOURCE_TYPE)source, localVideoStats);
}
void AIRtcEngineEventHandler::onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
{
	FRemoteVideoStats remoteVideoStats;
	remoteVideoStats.uid = stats.uid;
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
	remoteVideoStats.superResolutionType = stats.superResolutionType;
	OnRemoteVideoStats.Broadcast(remoteVideoStats);
}
void AIRtcEngineEventHandler::onCameraReady()
{
	OnCameraReady.Broadcast();
}
void AIRtcEngineEventHandler::onCameraFocusAreaChanged(int x, int y, int width, int height)
{
	OnCameraFocusAreaChanged.Broadcast(x, y, width, height);
}
void AIRtcEngineEventHandler::onCameraExposureAreaChanged(int x, int y, int width, int height)
{
	OnCameraExposureAreaChanged.Broadcast(x, y, width, height);
}
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
void AIRtcEngineEventHandler::onFacePositionChanged(int imageWidth, int imageHeight, const agora::rtc::Rectangle* vecRectangle, const int* vecDistance, int numFaces)
{
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
}
#endif
void AIRtcEngineEventHandler::onVideoStopped()
{
	OnVideoStopped.Broadcast();
}
void AIRtcEngineEventHandler::onAudioMixingStateChanged(agora::rtc::AUDIO_MIXING_STATE_TYPE state, agora::rtc::AUDIO_MIXING_REASON_TYPE reason)
{
	OnAudioMixingStateChanged.Broadcast((EAUDIO_MIXING_STATE_TYPE)state, (EAUDIO_MIXING_REASON_TYPE)reason);
}
void AIRtcEngineEventHandler::onRhythmPlayerStateChanged(agora::rtc::RHYTHM_PLAYER_STATE_TYPE state, agora::rtc::RHYTHM_PLAYER_ERROR_TYPE errorCode)
{
	OnRhythmPlayerStateChanged.Broadcast((ERHYTHM_PLAYER_STATE_TYPE)state, (ERHYTHM_PLAYER_ERROR_TYPE)errorCode);
}
void AIRtcEngineEventHandler::onConnectionLost()
{
	OnConnectionLost.Broadcast();
}
void AIRtcEngineEventHandler::onConnectionInterrupted()
{
	OnConnectionInterrupted.Broadcast();
}
void AIRtcEngineEventHandler::onConnectionBanned()
{
	OnConnectionBanned.Broadcast();
}
void AIRtcEngineEventHandler::onStreamMessage(agora::rtc::uid_t userId, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	OnStreamMessage.Broadcast(userId, streamId, FString(data), length, sentTs);
}
void AIRtcEngineEventHandler::onStreamMessageError(agora::rtc::uid_t userId, int streamId, int code, int missed, int cached)
{
	OnStreamMessageError.Broadcast(userId, streamId, code, missed, cached);
}
void AIRtcEngineEventHandler::onRequestToken()
{
	OnRequestToken.Broadcast();
}
void AIRtcEngineEventHandler::onTokenPrivilegeWillExpire(const char* token)
{
	OnTokenPrivilegeWillExpire.Broadcast(FString(token));
}
void AIRtcEngineEventHandler::onFirstLocalAudioFramePublished(int elapsed)
{
	OnFirstLocalAudioFramePublished.Broadcast(elapsed);
}
void AIRtcEngineEventHandler::onFirstRemoteAudioFrame(agora::rtc::uid_t uid, int elapsed)
{
	OnFirstRemoteAudioFrame.Broadcast(uid, elapsed);
}
void AIRtcEngineEventHandler::onFirstRemoteAudioDecoded(agora::rtc::uid_t uid, int elapsed)
{
	OnFirstRemoteAudioDecoded.Broadcast(uid, elapsed);
}
void AIRtcEngineEventHandler::onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	OnLocalAudioStateChanged.Broadcast((ELOCAL_AUDIO_STREAM_STATE)state, (ELOCAL_AUDIO_STREAM_ERROR)error);
}
void AIRtcEngineEventHandler::onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	OnRemoteAudioStateChanged.Broadcast(uid, (EREMOTE_AUDIO_STATE)state, (EREMOTE_AUDIO_STATE_REASON)reason, elapsed);
}
void AIRtcEngineEventHandler::onActiveSpeaker(agora::rtc::uid_t userId)
{
	OnActiveSpeaker.Broadcast(userId);
}
void AIRtcEngineEventHandler::onContentInspectResult(agora::media::CONTENT_INSPECT_RESULT result)
{
	OnContentInspectResult.Broadcast((ECONTENT_INSPECT_RESULT)result);
}
void AIRtcEngineEventHandler::onSnapshotTaken(agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	OnSnapshotTaken.Broadcast(uid, FString(filePath), width, height, errCode);
}
void AIRtcEngineEventHandler::onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole)
{
	OnClientRoleChanged.Broadcast((ECLIENT_ROLE_TYPE)oldRole, (ECLIENT_ROLE_TYPE)newRole);
}
void AIRtcEngineEventHandler::onClientRoleChangeFailed(agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	OnClientRoleChangeFailed.Broadcast((ECLIENT_ROLE_CHANGE_FAILED_REASON)reason, (ECLIENT_ROLE_TYPE)currentRole);
}
void AIRtcEngineEventHandler::onAudioDeviceVolumeChanged(agora::rtc::MEDIA_DEVICE_TYPE deviceType, int volume, bool muted)
{
	OnAudioDeviceVolumeChanged.Broadcast((EMEDIA_DEVICE_TYPE)deviceType, volume, muted);
}
void AIRtcEngineEventHandler::onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR_TYPE errCode)
{
	OnRtmpStreamingStateChanged.Broadcast(FString(url), (ERTMP_STREAM_PUBLISH_STATE)state, (ERTMP_STREAM_PUBLISH_ERROR_TYPE)errCode);
}
void AIRtcEngineEventHandler::onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode)
{
	OnRtmpStreamingEvent.Broadcast(FString(url), (ERTMP_STREAMING_EVENT)eventCode);
}
void AIRtcEngineEventHandler::onTranscodingUpdated()
{
	OnTranscodingUpdated.Broadcast();
}
void AIRtcEngineEventHandler::onAudioRoutingChanged(int routing)
{
	OnAudioRoutingChanged.Broadcast(routing);
}
void AIRtcEngineEventHandler::onChannelMediaRelayStateChanged(int state, int code)
{
	OnChannelMediaRelayStateChanged.Broadcast(state, code);
}
void AIRtcEngineEventHandler::onChannelMediaRelayEvent(int code)
{
	OnChannelMediaRelayEvent.Broadcast(code);
}
void AIRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover)
{
	OnLocalPublishFallbackToAudioOnly.Broadcast(isFallbackOrRecover);
}
void AIRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly(agora::rtc::uid_t uid, bool isFallbackOrRecover)
{
	OnRemoteSubscribeFallbackToAudioOnly.Broadcast(uid, isFallbackOrRecover);
}
void AIRtcEngineEventHandler::onRemoteAudioTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	OnRemoteAudioTransportStats.Broadcast(uid, delay, lost, rxKBitRate);
}
void AIRtcEngineEventHandler::onRemoteVideoTransportStats(agora::rtc::uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	OnRemoteVideoTransportStats.Broadcast(uid, delay, lost, rxKBitRate);
}
void AIRtcEngineEventHandler::onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
	OnConnectionStateChanged.Broadcast((ECONNECTION_STATE_TYPE)state, (ECONNECTION_CHANGED_REASON_TYPE)reason);
}
void AIRtcEngineEventHandler::onWlAccMessage(agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	OnWlAccMessage.Broadcast((EWLACC_MESSAGE_REASON)reason, (EWLACC_SUGGEST_ACTION)action, FString(wlAccMsg));
}
void AIRtcEngineEventHandler::onWlAccStats(agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats)
{
	FWlAccStats current;
	current.e2eDelayPercent = currentStats.e2eDelayPercent;
	current.frozenRatioPercent = currentStats.frozenRatioPercent;
	current.lossRatePercent = currentStats.lossRatePercent;
	FWlAccStats average;
	average.e2eDelayPercent = averageStats.e2eDelayPercent;
	average.frozenRatioPercent = averageStats.frozenRatioPercent;
	average.lossRatePercent = averageStats.lossRatePercent;
	OnWlAccStats.Broadcast(current, average);
}
void AIRtcEngineEventHandler::onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type)
{
	OnNetworkTypeChanged.Broadcast((ENETWORK_TYPE)type);
}
void AIRtcEngineEventHandler::onEncryptionError(agora::rtc::ENCRYPTION_ERROR_TYPE errorType)
{
	OnEncryptionError.Broadcast((EENCRYPTION_ERROR_TYPE)errorType);
}
void AIRtcEngineEventHandler::onPermissionError(agora::rtc::PERMISSION_TYPE permissionType)
{
	OnPermissionError.Broadcast((EPERMISSION_TYPE)permissionType);
}
void AIRtcEngineEventHandler::onLocalUserRegistered(agora::rtc::uid_t uid, const char* userAccount)
{
	OnLocalUserRegistered.Broadcast(uid, FString(userAccount));
}
void AIRtcEngineEventHandler::onUserInfoUpdated(agora::rtc::uid_t uid, const agora::rtc::UserInfo& info)
{
	FUserInfo userInfo;
	userInfo.uid = info.uid;
	FString userAccount(info.userAccount);
	OnUserInfoUpdated.Broadcast(uid, userInfo);
}
void AIRtcEngineEventHandler::onUploadLogResult(const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	OnUploadLogResult.Broadcast(FString(requestId), success, (EUPLOAD_ERROR_REASON)reason);
}
void AIRtcEngineEventHandler::onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	OnAudioSubscribeStateChanged.Broadcast(FString(channel), uid, (ESTREAM_SUBSCRIBE_STATE)oldState, (ESTREAM_SUBSCRIBE_STATE)newState, elapseSinceLastState);
}
void AIRtcEngineEventHandler::onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapseSinceLastState)
{
	OnVideoSubscribeStateChanged.Broadcast(FString(channel), uid, (ESTREAM_SUBSCRIBE_STATE)oldState, (ESTREAM_SUBSCRIBE_STATE)newState, elapseSinceLastState);
}
void AIRtcEngineEventHandler::onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	OnAudioPublishStateChanged.Broadcast(FString(channel), (ESTREAM_PUBLISH_STATE)oldState, (ESTREAM_PUBLISH_STATE)newState, elapseSinceLastState);
}
void AIRtcEngineEventHandler::onVideoPublishStateChanged(agora::rtc::VIDEO_SOURCE_TYPE source, const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapseSinceLastState)
{
	OnVideoPublishStateChanged.Broadcast((EVIDEO_SOURCE_TYPE)source, FString(channel), (ESTREAM_PUBLISH_STATE)oldState, (ESTREAM_PUBLISH_STATE)newState, elapseSinceLastState);
}
void AIRtcEngineEventHandler::onExtensionEvent(const char* provider, const char* extension, const char* key, const char* value)
{
	OnExtensionEvent.Broadcast(FString(provider), FString(extension), FString(key), FString(value));
}
void AIRtcEngineEventHandler::onExtensionStarted(const char* provider, const char* extension)
{
	OnExtensionStarted.Broadcast(FString(provider), FString(extension));
}
void AIRtcEngineEventHandler::onExtensionStopped(const char* provider, const char* extension)
{
	OnExtensionStopped.Broadcast(FString(provider), FString(extension));
}
void AIRtcEngineEventHandler::onExtensionError(const char* provider, const char* extension, int error, const char* message)
{
	OnExtensionError.Broadcast(FString(provider), FString(extension), error, FString(message));
}
void AIRtcEngineEventHandler::onUserAccountUpdated(agora::rtc::uid_t uid, const char* userAccount)
{
	OnUserAccountUpdated.Broadcast(uid, FString(userAccount));
}


const char* AIRtcEngineEventHandler::eventHandlerType() const
{
	 return "event_handler"; 
}

int AIMetadataObserver::getMaxMetadataSize()
{
	GetMaxMetadataSize.Broadcast();

	return DEFAULT_METADATA_SIZE_IN_BYTE;
}
bool AIMetadataObserver::onReadyToSendMetadata(agora::rtc::IMetadataObserver::Metadata& metadata, agora::rtc::VIDEO_SOURCE_TYPE source_type)
{
	FAgoraMetadata data;
	OnReadyToSendMetadata.Broadcast(data, (EVIDEO_SOURCE_TYPE)source_type);

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
void AIMetadataObserver::onMetadataReceived(const agora::rtc::IMetadataObserver::Metadata& metadata)
{
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
}
void AIDirectCdnStreamingEventHandler::onDirectCdnStreamingStateChanged(agora::rtc::DIRECT_CDN_STREAMING_STATE state, agora::rtc::DIRECT_CDN_STREAMING_ERROR error, const char* message)
{
	OnDirectCdnStreamingStateChanged.Broadcast((EDIRECT_CDN_STREAMING_STATE)state, (EDIRECT_CDN_STREAMING_ERROR)error, FString(message));
}
void AIDirectCdnStreamingEventHandler::onDirectCdnStreamingStats(const agora::rtc::DirectCdnStreamingStats& stats)
{
	FDirectCdnStreamingStats directCdnStreamingStats;
	directCdnStreamingStats.videoWidth = stats.videoWidth;
	directCdnStreamingStats.videoHeight = stats.videoHeight;
	directCdnStreamingStats.fps = stats.fps;
	directCdnStreamingStats.videoBitrate = stats.videoBitrate;
	directCdnStreamingStats.audioBitrate = stats.audioBitrate;
	OnDirectCdnStreamingStats.Broadcast(directCdnStreamingStats);
}

