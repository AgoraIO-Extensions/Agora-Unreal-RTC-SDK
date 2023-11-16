//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

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
