//  Copyright (c) 2023 Agora.io. All rights reserved.

#include "AgoraPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "AgoraPluginInterface.h"

#define LOCTEXT_NAMESPACE "FAgoraPluginModule"

DEFINE_LOG_CATEGORY(LogAgora);

void FAgoraPluginModule::StartupModule()
{
	UE_LOG(LogAgora, Display, TEXT("FAgoraPluginModule - StartupModule: %s"), *(AgoraUERtcEngine::GetSDKVersion()));
}

void FAgoraPluginModule::ShutdownModule()
{
	AgoraUERtcEngine::Release();
	UE_LOG(LogAgora, Display, TEXT("FAgoraPluginModule - ShutdownModule: Release RTC Engine"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAgoraPluginModule, AgoraPlugin)
