// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "URtcEngineProxyCompatibility.h"
#include "AgoraBluePrintPlugin/AgoraRtcEngine.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AgoraSpatialAudio.generated.h"

USTRUCT(BlueprintType)
struct FLocalSpatialAudioConfig
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalSpatialAudioConfig")
		UAgoraRtcEngine* rtcEngine;
};

USTRUCT(BlueprintType)
struct FRemoteVoicePositionInfo
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVoicePositionInfo")
		FVector position;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVoicePositionInfo")
		FVector forward;
};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UILocalSpatialAudioEngine : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int Initialize(const FLocalSpatialAudioConfig& config);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int UpdateRemotePosition(int64 uid, const FRemoteVoicePositionInfo& posInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int UpdateRemotePositionEx(int64 uid, const FRemoteVoicePositionInfo& posInfo, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int RemoveRemotePosition(int64 uid);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int RemoveRemotePositionEx(int64 uid, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int ClearRemotePositions();
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int ClearRemotePositionsEx(const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		void Release();
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int SetMaxAudioRecvCount(int maxCount);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int SetAudioRecvRange(float range);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int SetDistanceUnit(float unit);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int UpdateSelfPosition(FVector position, FVector axisForward, FVector axisRight, FVector axisUp);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int UpdateSelfPositionEx(FVector position, FVector axisForward, FVector axisRight, FVector axisUp, const FRtcConnection& connection);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int UpdatePlayerPositionInfo(int playerId, const FRemoteVoicePositionInfo& positionInfo);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int SetParameters(FString params);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int MuteLocalAudioStream(bool mute);
	UFUNCTION(BlueprintCallable, Category = "Agora|ILocalSpatialAudioEngine")
		int MuteAllRemoteAudioStreams(bool mute);
	void SetLocalSpatialAudioEngine(agora::rtc::ILocalSpatialAudioEngine* localSpatialAudioEngine);
private:
	agora::rtc::ILocalSpatialAudioEngine* LocalSpatialAudioEngine;
};
