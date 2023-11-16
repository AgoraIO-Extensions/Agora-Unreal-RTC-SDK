//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"
#include "IMediaRecorderObserver.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRecorderStateChanged, FString, channelId, int64, uid, FENUMWRAP_RecorderState, state, ERecorderErrorCode, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRecorderInfoUpdated, FString, channelId, int64, uid, const FRecorderInfo&, info);

class IMediaRecorderObserverClassWrapper : public agora::media::IMediaRecorderObserver {};

UCLASS(Blueprintable)
class AGORAPLUGIN_API UIMediaRecorderObserver : public UObject, public IMediaRecorderObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecorderStateChanged OnRecorderStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnRecorderInfoUpdated OnRecorderInfoUpdated;
	void onRecorderStateChanged(const char* channelId, agora::rtc::uid_t uid, agora::media::RecorderState state, agora::media::RecorderErrorCode error) override;
	void onRecorderInfoUpdated(const char* channelId, agora::rtc::uid_t uid, const agora::media::RecorderInfo& info) override;

};
