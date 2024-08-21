// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once


#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAgora, Log, All);

class FAgoraPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Handle to the test dll we will load */
	void* AgoraLibraryHandle;
};
