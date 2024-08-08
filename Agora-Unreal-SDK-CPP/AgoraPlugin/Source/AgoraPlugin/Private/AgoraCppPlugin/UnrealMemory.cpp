//  Copyright (c) 2024 Agora.io. All rights reserved.


#include "UnrealMemory.h"

#if USE_ANSI_ALLOCATOR  && AG_UE_5_3_OR_LATER
#include "src/Core/util/Macros.h"
#include "src/Core/util/ConfigureVectorization.h"
#endif 

#if USE_ANSI_ALLOCATOR  && AG_UE_5_3_OR_LATER

void* StdRealloc(void* Original, std::size_t Size, std::size_t Alignment){
    if(ensure(Alignment == EIGEN_DEFAULT_ALIGN_BYTES)){
        return std::realloc(Original,Size);
    }
    else{
        
        UE_LOG(LogTemp,Warning,TEXT("[AG Memory Allocator] Unexpected StdRealloc %lu"),Alignment);
        return FMemory::Realloc(Original, Size ? Size : 1, Alignment );
    }
}
void StdFree(void* Ptr){
    std::free(Ptr);
}
void* StdMalloc(std::size_t Size, std::size_t Alignment){
    if(ensure(Alignment == EIGEN_DEFAULT_ALIGN_BYTES)){
        return std::malloc(Size);
    }
    else{
        UE_LOG(LogTemp,Warning,TEXT("[AG Memory Allocator] Unexpected StdMalloc %lu"),Alignment);
        return FMemory::Malloc( Size ? Size : 1, (std::size_t)Alignment );
    }

}

#endif

