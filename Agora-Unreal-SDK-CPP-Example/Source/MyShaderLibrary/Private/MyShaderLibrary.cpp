#include "MyShaderLibrary.h"

void FMyShaderLibrary::StartupModule() {
	FString BaseDir = FPaths::Combine(FPaths::GameSourceDir(), TEXT("MyShaderLibrary"));
	FString ModuleShaderDir = FPaths::Combine(BaseDir, TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/MyShaderLibrary"), ModuleShaderDir);
}


void FMyShaderLibrary::ShutdownModule()
{

}


IMPLEMENT_MODULE(FMyShaderLibrary, MyShaderLibrary)
