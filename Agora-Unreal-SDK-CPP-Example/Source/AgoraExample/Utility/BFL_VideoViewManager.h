// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DraggableVideoViewWidget.h"
#include "WidgetDropOp.h"
#include "Input/DragAndDrop.h"
#include "Input/Events.h"
#include "Templates/TypeHash.h"
#include "AgoraPluginInterface.h"
#include "BFL_VideoViewManager.generated.h"

using namespace agora::rtc;

typedef struct FVideoViewIdentity {
	VIDEO_SOURCE_TYPE sourceType;
	uint32 uid;
	FString channelId;

	FVideoViewIdentity()
		: sourceType(VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA), uid(0), channelId("") {/* use as the local video */
	}
	FVideoViewIdentity(VIDEO_SOURCE_TYPE vsourceType)
		: sourceType(vsourceType), uid(0), channelId("") {/* use as the local video */
	}

	FVideoViewIdentity(uint32 vuid, VIDEO_SOURCE_TYPE vsourceType, FString vchannelId)
		: sourceType(vsourceType), uid(vuid), channelId(vchannelId) {}

	bool operator==(const FVideoViewIdentity& Other) const
	{
		return sourceType == Other.sourceType && uid == Other.uid && channelId == Other.channelId;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FVideoViewIdentity& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, (uint32)(Key.sourceType));
		Hash = HashCombine(Hash, (uint32)(Key.uid));
		Hash = HashCombine(Hash, FCrc::Strihash_DEPRECATED(*Key.channelId));
		return Hash;
	}
} FVideoViewIdentity;


/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UBFL_VideoViewManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	static UImage* CreateOneVideoViewToCanvasPanel(
		int64 uid,
		UCanvasPanel* CanvasPanel,
		TMap<int64, UDraggableVideoViewWidget*>& VideoViewMap,
		UImage* VideoView,
		TSubclassOf<UUserWidget> Template,
		bool bAutoSize = false
	);

	static void ReleaseOneVideoView(int64 uid, TMap<int64, UDraggableVideoViewWidget*>& VideoViewMap);

	static void ReleaseAllVideoView(TMap<int64, UDraggableVideoViewWidget*>& VideoViewMap);



	static UImage* CreateOneVideoViewToCanvasPanel(
		const FVideoViewIdentity& Key,
		UCanvasPanel* CanvasPanel,
		TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap,
		TSubclassOf<UUserWidget> Template,
		bool bAutoSize = false
	);

	static void ReleaseOneVideoView(const FVideoViewIdentity& Key, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap);

	static void ReleaseAllVideoView(TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap);

	static void ChangeSizeForOneVideoView(const FVideoViewIdentity& Key, int Width, int Height, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap);

	static void RotateTheVideoView(const FVideoViewIdentity& Key, int rotation, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap);

	static void ResizeTheRotationAppliedImage(const FVideoViewIdentity& Key, int Width, int Height, int rotation, TMap<FVideoViewIdentity, UDraggableVideoViewWidget*>& VideoViewMap);

	UFUNCTION(BlueprintCallable, Category = "VideoViewManager")
	static void OnDropInner(const FGeometry& InGeometry, const FPointerEvent& InDragDropEvent, UDragDropOperation* InOperation);

};
