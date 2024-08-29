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
	UE_LOG(LogAgora, Warning, TEXT("FAgoraPluginModule: %s"), *(AgoraUERtcEngine::GetSDKVersion()));
}

void FAgoraPluginModule::ShutdownModule()
{
	//untested, so comment out the code for now
	//AgoraUERtcEngine::Release();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAgoraPluginModule, AgoraPlugin)
