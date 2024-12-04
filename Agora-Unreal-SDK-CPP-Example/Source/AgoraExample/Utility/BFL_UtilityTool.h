// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "Components/ComboBoxString.h"
#include "BFL_UtilityTool.generated.h"

enum class EUIDFuncType : uint8 {
	UNKNOWN = 0,
	CAMERA = 1,
	SCREEN_SHARE = 2,
	MPK = 3,
};

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UBFL_UtilityTool : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static FString ConvertToAbsolutePath(FString InRelativePath, bool bAndroidUseInternalBasePath = false);

	static void CreateMediaFileWithSource(FString SrcPath, FString DstPath);

	static FString GenSimpleUIDPart_MachineCode();

	static FString GenSimpleUIDPart_FuncCode(EUIDFuncType Type);


	static FString GetAgoraSaveDataSlotName();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	static void SetCBSTextColor(UComboBoxString* CBSPtr);
};
