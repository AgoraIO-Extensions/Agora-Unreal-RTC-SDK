//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraCppPlugin/include/AgoraHeaderBase.h"
#include "AgoraBluePrintPlugin/URtcEngineProxyCompatibility.h"
#include "IMediaStreamingSourceObserver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, ESTREAMING_SRC_STATE, state, ESTREAMING_SRC_ERR, err_code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenDone, ESTREAMING_SRC_ERR, err_code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSeekDone, ESTREAMING_SRC_ERR, err_code);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEofOnce, int64, progress_ms, int64, repeat_count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProgress, int64, position_ms);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaData, const int64, data, int, length);

class IMediaStreamingSourceObserverClassWrapper : public agora::rtc::IMediaStreamingSourceObserver {};

/**
 *
 */
UCLASS(Blueprintable)
class AGORAPLUGIN_API UIMediaStreamingSourceObserver : public UObject, public IMediaStreamingSourceObserverClassWrapper
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnStateChanged OnStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnOpenDone OnOpenDone;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnSeekDone OnSeekDone;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnEofOnce OnEofOnce;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnProgress OnProgress;
	UPROPERTY(BlueprintAssignable, Category = "Agora|Event")
	FOnMetaData OnMetaData;

	void onStateChanged(agora::rtc::STREAMING_SRC_STATE state, agora::rtc::STREAMING_SRC_ERR err_code) override;

	void onOpenDone(agora::rtc::STREAMING_SRC_ERR err_code) override;

	void onSeekDone(agora::rtc::STREAMING_SRC_ERR err_code) override;

	void onEofOnce(int64_t progress_ms, int64_t repeat_count) override;

	void onProgress(int64_t position_ms) override;

	void onMetaData(const void* data, int length) override;
};
