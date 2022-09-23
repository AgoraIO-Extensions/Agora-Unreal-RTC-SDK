// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "IMediaRecorderObserver.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRecorderStateChanged, ERecorderState, state, ERecorderErrorCode, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecorderInfoUpdated, const FRecorderInfo&, info);


UCLASS(Blueprintable)
class AGORAPLUGIN_API AIMediaRecorderObserver : public AActor, public agora::media::IMediaRecorderObserver
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
public:
	AIMediaRecorderObserver();
	void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecorderStateChanged OnRecorderStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecorderInfoUpdated OnRecorderInfoUpdated;
	void onRecorderStateChanged(agora::media::RecorderState state, agora::media::RecorderErrorCode error) override;
	void onRecorderInfoUpdated(const agora::media::RecorderInfo& info) override;

};
