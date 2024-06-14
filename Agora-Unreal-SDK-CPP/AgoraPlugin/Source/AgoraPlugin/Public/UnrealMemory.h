//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#define AG_UE_5_3_OR_LATER (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)

#if USE_ANSI_ALLOCATOR && AG_UE_5_3_OR_LATER
#include <stdio.h>

void* StdRealloc(void* Original, std::size_t Size, std::size_t Alignment);
void StdFree(void* Ptr);
void* StdMalloc(std::size_t Size, std::size_t Alignment);

#endif

