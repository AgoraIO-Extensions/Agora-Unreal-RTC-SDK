// Copyright(c) 2024 Agora.io. All rights reserved.


#include "BFL_UtilityTool.h"
#include "Misc/EngineVersion.h"


bool UBFL_UtilityTool::IsAgoraAudioOnlySDK()
{
#if AGORA_UESDK_AUDIO_ONLY
	return true;
#else
	return false;
#endif

}

FString UBFL_UtilityTool::GetAgoraSaveDataSlotName()
{
	
	FEngineVersion EngineVersion = FEngineVersion::Current();
	FString VersionString = EngineVersion.ToString(EVersionComponent::Patch);
	// UE_LOG(LogTemp, Log, TEXT("Current Engine Version: %s"), *VersionString);

	FString SlotName = "AgoraSaveData_" + VersionString;
	FString FinalSlotName = SlotName.Replace(TEXT("."), TEXT("_"));

	return FinalSlotName;

}
