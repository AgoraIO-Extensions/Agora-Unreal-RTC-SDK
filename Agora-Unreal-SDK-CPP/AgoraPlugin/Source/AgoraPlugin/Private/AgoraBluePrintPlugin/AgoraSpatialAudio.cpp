//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/AgoraSpatialAudio.h"

int UILocalSpatialAudioEngine::Initialize(FLocalSpatialAudioConfig& config)
{
	agora::rtc::LocalSpatialAudioConfig localSpatialAudioConfig = config.CreateAgoraData();
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->initialize(localSpatialAudioConfig);
	}
	config.FreeAgoraData(localSpatialAudioConfig);
	return ret;
}
int UILocalSpatialAudioEngine::UpdateRemotePosition(int64 uid, FRemoteVoicePositionInfo& posInfo)
{
	agora::rtc::RemoteVoicePositionInfo remoteVoicePositionInfo = posInfo.CreateAgoraData();
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->updateRemotePosition(uid, remoteVoicePositionInfo);
	}
	posInfo.FreeAgoraData(remoteVoicePositionInfo);
	return ret;
}
int UILocalSpatialAudioEngine::UpdateRemotePositionEx(int64 uid, FRemoteVoicePositionInfo& posInfo, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	agora::rtc::RemoteVoicePositionInfo remoteVoicePositionInfo = posInfo.CreateAgoraData();
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->updateRemotePositionEx(uid, remoteVoicePositionInfo, rtcConnection);
	}
	connection.FreeAgoraData(rtcConnection);
	posInfo.FreeAgoraData(remoteVoicePositionInfo);
	return ret;
}
int UILocalSpatialAudioEngine::RemoveRemotePosition(int64 uid)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->removeRemotePosition(uid);
	}
	return ret;
}
int UILocalSpatialAudioEngine::RemoveRemotePositionEx(int64 uid, FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->removeRemotePositionEx(uid,rtcConnection);
	}
	connection.FreeAgoraData(rtcConnection);
	return ret;
}
int UILocalSpatialAudioEngine::ClearRemotePositions()
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->clearRemotePositions();
	}
	return ret;
}
int UILocalSpatialAudioEngine::ClearRemotePositionsEx(FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->clearRemotePositions();
	}
	connection.FreeAgoraData(rtcConnection);
	return ret;
}


int UILocalSpatialAudioEngine::SetRemoteAudioAttenuation(int64 uid, bool forceSet, FString attenuation /*= "0.0"*/)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		double ValAttenuation = FCString::Atod(*attenuation);
		ret = LocalSpatialAudioEngine->setRemoteAudioAttenuation(uid, ValAttenuation, forceSet);
	}
	return ret;

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
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->setMaxAudioRecvCount(maxCount);
	}
	return ret;
}

int UILocalSpatialAudioEngine::SetAudioRecvRange(float range)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->setAudioRecvRange(range);
	}
	return ret;
}

int UILocalSpatialAudioEngine::SetDistanceUnit(float unit)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->setDistanceUnit(unit);
	}
	return ret;
}

int UILocalSpatialAudioEngine::UpdateSelfPosition(FVector position, FVector axisForward, FVector axisRight, FVector axisUp)
{
	float pos[3] = {};
	float forward[3] = {};
	float right[3] = {};
	float up[3] = {};
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(pos, position)
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(forward, axisForward)
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(right, axisRight)
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(up, axisUp)

	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->updateSelfPosition(pos, forward, right, up);
	}
	return ret;
}

int UILocalSpatialAudioEngine::UpdateSelfPositionEx(FVector position, FVector axisForward, FVector axisRight, FVector axisUp, const FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection = connection.CreateAgoraData();

	float pos[3] = {};
	float forward[3] = {};
	float right[3] = {};
	float up[3] = {};
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(pos, position)
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(forward, axisForward)
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(right, axisRight)
	SET_UABT_FVECTOR_TO_AGORA_FLOAT3(up, axisUp)

	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->updateSelfPositionEx(pos, forward, right, up, rtcConnection);
	}
	connection.FreeAgoraData(rtcConnection);
	return ret;
}

int UILocalSpatialAudioEngine::UpdatePlayerPositionInfo(int playerId, const FRemoteVoicePositionInfo& positionInfo)
{
	agora::rtc::RemoteVoicePositionInfo Info = positionInfo.CreateAgoraData();

	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->updatePlayerPositionInfo(playerId,Info);
	}
	positionInfo.FreeAgoraData(Info);
	return ret;
}

int UILocalSpatialAudioEngine::SetParameters(FString params)
{
	std::string STDParameters = TCHAR_TO_UTF8(*params);
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->setParameters(STDParameters.c_str());
	}
	return ret;
}

int UILocalSpatialAudioEngine::MuteLocalAudioStream(bool mute)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->muteLocalAudioStream(mute);
	}
	return ret;
}

int UILocalSpatialAudioEngine::MuteAllRemoteAudioStreams(bool mute)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->muteAllRemoteAudioStreams(mute);
	}
	return ret;
}


int UILocalSpatialAudioEngine::SetZones(TArray<FSpatialAudioZone> zones)
{
	int ret = -ERROR_NULLPTR;

	if (LocalSpatialAudioEngine != nullptr)
	{
		agora::rtc::SpatialAudioZone* valZones = nullptr;
		int zoneCount = zones.Num();
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(valZones, agora::rtc::SpatialAudioZone, zoneCount, zones)
		
		ret = LocalSpatialAudioEngine->setZones(valZones, zoneCount);
		
		SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(valZones, zoneCount, FSpatialAudioZone)
	}
	return ret;
}

int UILocalSpatialAudioEngine::SetPlayerAttenuation(int playerId, bool forceSet, FString attenuation /*= "0.0"*/)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		double ValAttenuation = FCString::Atod(*attenuation);
		ret = LocalSpatialAudioEngine->setPlayerAttenuation(playerId, ValAttenuation, forceSet);
	}
	return ret;
}

int UILocalSpatialAudioEngine::muteRemoteAudioStream(int64 uid, bool mute)
{
	int ret = -ERROR_NULLPTR;
	if (LocalSpatialAudioEngine != nullptr)
	{
		ret = LocalSpatialAudioEngine->muteRemoteAudioStream(uid, mute);
	}
	return ret;
}

void UILocalSpatialAudioEngine::SetLocalSpatialAudioEngine(agora::rtc::ILocalSpatialAudioEngine* localSpatialAudioEngine)
{
	this->LocalSpatialAudioEngine = localSpatialAudioEngine;
}
