//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once


#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAgoraUtilityHelperModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
