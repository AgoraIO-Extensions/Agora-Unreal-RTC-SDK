// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraSpatialAudio.h"

int UILocalSpatialAudioEngine::Initialize(const FLocalSpatialAudioConfig& config)
{
	agora::rtc::LocalSpatialAudioConfig localSpatialAudioConfig;
	localSpatialAudioConfig.rtcEngine = config.rtcEngine;
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->initialize(localSpatialAudioConfig);
	}
	return -ERROR_NULLPTR;
}
int UILocalSpatialAudioEngine::UpdateRemotePosition(int64 uid, const FRemoteVoicePositionInfo& posInfo)
{
	agora::rtc::RemoteVoicePositionInfo remoteVoicePositionInfo;
	float pos[3];

	float forward[3];

	pos[0] = posInfo.position.X;
	pos[1] = posInfo.position.Y;
	pos[2] = posInfo.position.Z;

	forward[0] = posInfo.forward.X;
	forward[1] = posInfo.forward.Y;
	forward[2] = posInfo.forward.Z;

	FMemory::Memcpy(remoteVoicePositionInfo.position, pos);
	FMemory::Memcpy(remoteVoicePositionInfo.forward, forward);
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->updateRemotePosition(uid, remoteVoicePositionInfo);
	}
	return -ERROR_NULLPTR;
}
int UILocalSpatialAudioEngine::UpdateRemotePositionEx(int64 uid, const  FRemoteVoicePositionInfo& posInfo, const FRtcConnection& connection)
{
	agora::rtc::RemoteVoicePositionInfo remoteVoicePositionInfo;

	float pos[3];

	float forward[3];

	pos[0] = posInfo.position.X;
	pos[1] = posInfo.position.Y;
	pos[2] = posInfo.position.Z;

	forward[0] = posInfo.forward.X;
	forward[1] = posInfo.forward.Y;
	forward[2] = posInfo.forward.Z;

	FMemory::Memcpy(remoteVoicePositionInfo.position, pos);
	FMemory::Memcpy(remoteVoicePositionInfo.forward, forward);

	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->updateRemotePositionEx(uid, remoteVoicePositionInfo, rtcConnection);
	}
	return -ERROR_NULLPTR;
}
int UILocalSpatialAudioEngine::RemoveRemotePosition(int64 uid)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->removeRemotePosition(uid);
	}
	return -ERROR_NULLPTR;
}
int UILocalSpatialAudioEngine::RemoveRemotePositionEx(int64 uid, const  FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->removeRemotePositionEx(uid, rtcConnection);
	}
	return -ERROR_NULLPTR;
}
int UILocalSpatialAudioEngine::ClearRemotePositions()
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->clearRemotePositions();
	}
	return -ERROR_NULLPTR;
}
int UILocalSpatialAudioEngine::ClearRemotePositionsEx(const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->clearRemotePositionsEx(rtcConnection);
	}
	return -ERROR_NULLPTR;
}

void UILocalSpatialAudioEngine::Release()
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		LocalSpatialAudioEngine->release();
	}
}

int UILocalSpatialAudioEngine::SetMaxAudioRecvCount(int maxCount)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->setMaxAudioRecvCount(maxCount);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::SetAudioRecvRange(float range)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->setAudioRecvRange(range);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::SetDistanceUnit(float unit)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->setDistanceUnit(unit);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::UpdateSelfPosition(FVector position, FVector axisForward, FVector axisRight, FVector axisUp)
{
	float pos[3];

	pos[0] = position.X;
	pos[1] = position.Y;
	pos[2] = position.Z;

	float forward[3];

	forward[0] = axisForward.X;
	forward[1] = axisForward.Y;
	forward[2] = axisForward.Z;

	float right[3];

	right[0] = axisRight.X;
	right[1] = axisRight.Y;
	right[2] = axisRight.Z;

	float up[3];

	up[0] = axisUp.X;
	up[1] = axisUp.Y;
	up[2] = axisUp.Z;

	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->updateSelfPosition(pos, forward, right, up);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::UpdateSelfPositionEx(FVector position, FVector axisForward, FVector axisRight, FVector axisUp, const FRtcConnection& connection)
{
	float pos[3];

	pos[0] = position.X;
	pos[1] = position.Y;
	pos[2] = position.Z;

	float forward[3];

	forward[0] = axisForward.X;
	forward[1] = axisForward.Y;
	forward[2] = axisForward.Z;

	float right[3];

	right[0] = axisRight.X;
	right[1] = axisRight.Y;
	right[2] = axisRight.Z;

	float up[3];

	up[0] = axisUp.X;
	up[1] = axisUp.Y;
	up[2] = axisUp.Z;

	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;

	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->updateSelfPositionEx(pos, forward, right, up, rtcConnection);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::UpdatePlayerPositionInfo(int playerId, const FRemoteVoicePositionInfo& positionInfo)
{
	agora::rtc::RemoteVoicePositionInfo Info;

	float pos[3];
	
	float forward[3];

	pos[0] = positionInfo.position.X;
	pos[1] = positionInfo.position.Y;
	pos[2] = positionInfo.position.Z;

	forward[0] = positionInfo.forward.X;
	forward[1] = positionInfo.forward.Y;
	forward[2] = positionInfo.forward.Z;

	FMemory::Memcpy(Info.position, pos);

	FMemory::Memcpy(Info.forward, forward);

	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->updatePlayerPositionInfo(playerId, Info);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::SetParameters(FString params)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->setParameters(TCHAR_TO_ANSI(*params));
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::MuteLocalAudioStream(bool mute)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->muteLocalAudioStream(mute);
	}
	return -ERROR_NULLPTR;
}

int UILocalSpatialAudioEngine::MuteAllRemoteAudioStreams(bool mute)
{
	if (LocalSpatialAudioEngine != nullptr)
	{
		return LocalSpatialAudioEngine->muteAllRemoteAudioStreams(mute);
	}
	return -ERROR_NULLPTR;
}

void UILocalSpatialAudioEngine::SetLocalSpatialAudioEngine(agora::rtc::ILocalSpatialAudioEngine* localSpatialAudioEngine)
{
	this->LocalSpatialAudioEngine = localSpatialAudioEngine;
}
