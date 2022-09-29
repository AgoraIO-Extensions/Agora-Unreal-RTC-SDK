// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgoraPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include <string>
#include "AgoraCppPlugin/Include/AgoraHeaderBase.h"

#define LOCTEXT_NAMESPACE "FAgoraPluginModule"

void FAgoraPluginModule::StartupModule()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("AgoraPlugin")->GetBaseDir();

	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/AgoraPluginLibrary/x64/Release/agora_rtc_sdk.dll"));

	AgoraLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (AgoraLibraryHandle)
	{
		int build = 0;

		getAgoraRtcEngineVersion(&build);

		std::string buildVersion = std::to_string(build);
		buildVersion = "Hello from Agora! buildVersion: " + buildVersion;

		UE_LOG(LogTemp, Warning, TEXT("FAgoraPluginModule: %s"), ANSI_TO_TCHAR(buildVersion.c_str()));
	}
#endif
}

void FAgoraPluginModule::ShutdownModule()
{
	if (AgoraLibraryHandle)
	{
		FPlatformProcess::FreeDllHandle(AgoraLibraryHandle);
		AgoraLibraryHandle = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAgoraPluginModule, AgoraPlugin)
