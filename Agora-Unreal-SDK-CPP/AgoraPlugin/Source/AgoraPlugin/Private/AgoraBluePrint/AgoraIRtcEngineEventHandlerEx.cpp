// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrint/AgoraIRtcEngineEventHandlerEx.h"

AIRtcEngineEventHandlerEx::AIRtcEngineEventHandlerEx()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AIRtcEngineEventHandlerEx::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIRtcEngineEventHandlerEx::BeginPlay()
{
	Super::BeginPlay();
}

void AIRtcEngineEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnJoinChannelSuccessEx.Broadcast(rtcConnection, elapsed);
}
void AIRtcEngineEventHandlerEx::onRejoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnRejoinChannelSuccessEx.Broadcast(rtcConnection, elapsed);
}
void AIRtcEngineEventHandlerEx::onAudioQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int quality, unsigned short delay, unsigned short lost)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnAudioQualityEx.Broadcast(rtcConnection, remoteUid, quality, delay, lost);
}
void AIRtcEngineEventHandlerEx::onAudioVolumeIndication(const agora::rtc::RtcConnection& connection, const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FAudioVolumeInfo audioVolumeInfo;
	if (speakers != nullptr)
	{
		audioVolumeInfo.uid = speakers->uid;
		audioVolumeInfo.volume = speakers->volume;
		audioVolumeInfo.vad = speakers->vad;
		audioVolumeInfo.voicePitch = speakers->voicePitch;
	}
	OnAudioVolumeIndicationEx.Broadcast(rtcConnection, audioVolumeInfo, speakerNumber, totalVolume);
}
void AIRtcEngineEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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
	OnLeaveChannelEx.Broadcast(rtcConnection, rtcStats);
}
void AIRtcEngineEventHandlerEx::onRtcStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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
	OnRtcStatsEx.Broadcast(rtcConnection, rtcStats);
}
void AIRtcEngineEventHandlerEx::onNetworkQuality(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int txQuality, int rxQuality)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnNetworkQualityEx.Broadcast(rtcConnection, remoteUid, txQuality, rxQuality);
}
void AIRtcEngineEventHandlerEx::onIntraRequestReceived(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnIntraRequestReceivedEx.Broadcast(rtcConnection);
}
void AIRtcEngineEventHandlerEx::onFirstLocalVideoFrame(const agora::rtc::RtcConnection& connection, int width, int height, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstLocalVideoFrameEx.Broadcast(rtcConnection, width, height, elapsed);
}
void AIRtcEngineEventHandlerEx::onFirstLocalVideoFramePublished(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstLocalVideoFramePublishedEx.Broadcast(rtcConnection, elapsed);
}
void AIRtcEngineEventHandlerEx::onFirstRemoteVideoDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstRemoteVideoDecodedEx.Broadcast(rtcConnection, remoteUid, width, height, elapsed);
}
void AIRtcEngineEventHandlerEx::onVideoSizeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::VIDEO_SOURCE_TYPE sourceType, agora::rtc::uid_t uid, int width, int height, int rotation)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnVideoSizeChangedEx.Broadcast(rtcConnection, (EVIDEO_SOURCE_TYPE)sourceType,uid, width, height, rotation);
}
void AIRtcEngineEventHandlerEx::onLocalVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR errorCode)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnLocalVideoStateChangedEx.Broadcast(rtcConnection, (ELOCAL_VIDEO_STREAM_STATE)state, (ELOCAL_VIDEO_STREAM_ERROR)errorCode);
}
void AIRtcEngineEventHandlerEx::onRemoteVideoStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnRemoteVideoStateChangedEx.Broadcast(rtcConnection, remoteUid, (EREMOTE_VIDEO_STATE)state, (EREMOTE_VIDEO_STATE_REASON)reason, elapsed);
}
void AIRtcEngineEventHandlerEx::onFirstRemoteVideoFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int width, int height, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstRemoteVideoFrameEx.Broadcast(rtcConnection, remoteUid, width, height, elapsed);
}
void AIRtcEngineEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserJoinedEx.Broadcast(rtcConnection, remoteUid, elapsed);
}
void AIRtcEngineEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserOfflineEx.Broadcast(rtcConnection, remoteUid, (EUSER_OFFLINE_REASON_TYPE)reason);
}
void AIRtcEngineEventHandlerEx::onUserMuteAudio(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserMuteAudioEx.Broadcast(rtcConnection, remoteUid, muted);
}
void AIRtcEngineEventHandlerEx::onUserMuteVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool muted)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserMuteVideoEx.Broadcast(rtcConnection, remoteUid, muted);
}
void AIRtcEngineEventHandlerEx::onUserEnableVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserEnableVideoEx.Broadcast(rtcConnection, remoteUid, enabled);
}
void AIRtcEngineEventHandlerEx::onUserEnableLocalVideo(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, bool enabled)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserEnableLocalVideoEx.Broadcast(rtcConnection, remoteUid, enabled);
}
void AIRtcEngineEventHandlerEx::onUserStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, uint32_t state)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserStateChangedEx.Broadcast(rtcConnection, remoteUid, state);
}
void AIRtcEngineEventHandlerEx::onLocalAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalAudioStats& stats)
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
	OnLocalAudioStatsEx.Broadcast(rtcConnection, localAudioStats);
}
void AIRtcEngineEventHandlerEx::onRemoteAudioStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteAudioStats& stats)
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
	OnRemoteAudioStatsEx.Broadcast(rtcConnection, remoteAudioStats);
}
void AIRtcEngineEventHandlerEx::onLocalVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::LocalVideoStats& stats)
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
	localVideoStats.captureBrightnessLevel=(ECAPTURE_BRIGHTNESS_LEVEL_TYPE)stats.captureBrightnessLevel;
	localVideoStats.dualStreamEnabled=stats.dualStreamEnabled;
	OnLocalVideoStatsEx.Broadcast(rtcConnection, localVideoStats);
}
void AIRtcEngineEventHandlerEx::onRemoteVideoStats(const agora::rtc::RtcConnection& connection, const agora::rtc::RemoteVideoStats& stats)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	FRemoteVideoStats remoteVideoStats;
	remoteVideoStats.uid=stats.uid;
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
	remoteVideoStats.superResolutionType=stats.superResolutionType;
	OnRemoteVideoStatsEx.Broadcast(rtcConnection, remoteVideoStats);
}
void AIRtcEngineEventHandlerEx::onConnectionLost(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnConnectionLostEx.Broadcast(rtcConnection);
}
void AIRtcEngineEventHandlerEx::onConnectionInterrupted(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnConnectionInterruptedEx.Broadcast(rtcConnection);
}
void AIRtcEngineEventHandlerEx::onConnectionBanned(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnConnectionBannedEx.Broadcast(rtcConnection);
}
void AIRtcEngineEventHandlerEx::onStreamMessage(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnStreamMessageEx.Broadcast(rtcConnection, remoteUid, streamId, FString(data), length, sentTs);
}
void AIRtcEngineEventHandlerEx::onStreamMessageError(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int streamId, int code, int missed, int cached)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnStreamMessageErrorEx.Broadcast(rtcConnection, remoteUid, streamId, code, missed, cached);
}
void AIRtcEngineEventHandlerEx::onRequestToken(const agora::rtc::RtcConnection& connection)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnRequestTokenEx.Broadcast(rtcConnection);
}
void AIRtcEngineEventHandlerEx::onTokenPrivilegeWillExpire(const agora::rtc::RtcConnection& connection, const char* token)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnTokenPrivilegeWillExpireEx.Broadcast(rtcConnection, FString(token));
}
void AIRtcEngineEventHandlerEx::onFirstLocalAudioFramePublished(const agora::rtc::RtcConnection& connection, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstLocalAudioFramePublishedEx.Broadcast(rtcConnection, elapsed);
}
void AIRtcEngineEventHandlerEx::onFirstRemoteAudioFrame(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t userId, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstRemoteAudioFrameEx.Broadcast(rtcConnection, userId, elapsed);
}
void AIRtcEngineEventHandlerEx::onFirstRemoteAudioDecoded(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnFirstRemoteAudioDecodedEx.Broadcast(rtcConnection, uid, elapsed);
}
void AIRtcEngineEventHandlerEx::onLocalAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnLocalAudioStateChangedEx.Broadcast(rtcConnection, (ELOCAL_AUDIO_STREAM_STATE)state, (ELOCAL_AUDIO_STREAM_ERROR)error);
}
void AIRtcEngineEventHandlerEx::onRemoteAudioStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnRemoteAudioStateChangedEx.Broadcast(rtcConnection, remoteUid, (EREMOTE_AUDIO_STATE)state, (EREMOTE_AUDIO_STATE_REASON)reason, elapsed);
}
void AIRtcEngineEventHandlerEx::onActiveSpeaker(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnActiveSpeakerEx.Broadcast(rtcConnection, uid);
}
void AIRtcEngineEventHandlerEx::onClientRoleChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnClientRoleChangedEx.Broadcast(rtcConnection, (ECLIENT_ROLE_TYPE)oldRole, (ECLIENT_ROLE_TYPE)newRole);
}
void AIRtcEngineEventHandlerEx::onClientRoleChangeFailed(const agora::rtc::RtcConnection& connection, agora::rtc::CLIENT_ROLE_CHANGE_FAILED_REASON reason, agora::rtc::CLIENT_ROLE_TYPE currentRole)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnClientRoleChangeFailedEx.Broadcast(rtcConnection, (ECLIENT_ROLE_CHANGE_FAILED_REASON)reason, (ECLIENT_ROLE_TYPE)currentRole);
}
void AIRtcEngineEventHandlerEx::onRemoteAudioTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnRemoteAudioTransportStatsEx.Broadcast(rtcConnection, remoteUid, delay, lost, rxKBitRate);
}
void AIRtcEngineEventHandlerEx::onRemoteVideoTransportStats(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnRemoteVideoTransportStatsEx.Broadcast(rtcConnection, remoteUid, delay, lost, rxKBitRate);
}
void AIRtcEngineEventHandlerEx::onConnectionStateChanged(const agora::rtc::RtcConnection& connection, agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnConnectionStateChangedEx.Broadcast(rtcConnection, (ECONNECTION_STATE_TYPE)state, (ECONNECTION_CHANGED_REASON_TYPE)reason);
}
void AIRtcEngineEventHandlerEx::onWlAccMessage(const agora::rtc::RtcConnection& connection, agora::rtc::WLACC_MESSAGE_REASON reason, agora::rtc::WLACC_SUGGEST_ACTION action, const char* wlAccMsg)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnWlAccMessageEx.Broadcast(rtcConnection, (EWLACC_MESSAGE_REASON)reason, (EWLACC_SUGGEST_ACTION)action, FString(wlAccMsg));
}
void AIRtcEngineEventHandlerEx::onWlAccStats(const agora::rtc::RtcConnection& connection, agora::rtc::WlAccStats currentStats, agora::rtc::WlAccStats averageStats)
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
	OnWlAccStatsEx.Broadcast(rtcConnection, current, average);
}
void AIRtcEngineEventHandlerEx::onNetworkTypeChanged(const agora::rtc::RtcConnection& connection, agora::rtc::NETWORK_TYPE type)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnNetworkTypeChangedEx.Broadcast(rtcConnection, (ENETWORK_TYPE)type);
}
void AIRtcEngineEventHandlerEx::onEncryptionError(const agora::rtc::RtcConnection& connection, agora::rtc::ENCRYPTION_ERROR_TYPE errorType)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnEncryptionErrorEx.Broadcast(rtcConnection, (EENCRYPTION_ERROR_TYPE)errorType);
}
void AIRtcEngineEventHandlerEx::onUploadLogResult(const agora::rtc::RtcConnection& connection, const char* requestId, bool success, agora::rtc::UPLOAD_ERROR_REASON reason)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUploadLogResultEx.Broadcast(rtcConnection, FString(requestId), success, (EUPLOAD_ERROR_REASON)reason);
}
void AIRtcEngineEventHandlerEx::onUserAccountUpdated(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, const char* userAccount)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnUserAccountUpdatedEx.Broadcast(rtcConnection, remoteUid, FString(userAccount));
}
void AIRtcEngineEventHandlerEx::onSnapshotTaken(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t uid, const char* filePath, int width, int height, int errCode)
{
	FRtcConnection rtcConnection;
	rtcConnection.channelId=FString(connection.channelId);
	rtcConnection.localUid=connection.localUid;
	OnSnapshotTakenEx.Broadcast(rtcConnection, uid, FString(filePath), width, height, errCode);
}
