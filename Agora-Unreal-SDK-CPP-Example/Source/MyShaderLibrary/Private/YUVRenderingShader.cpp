#include "YUVRenderingShader.h"


IMPLEMENT_SHADER_TYPE(, FYUVRenderingVS, TEXT("/MyShaderLibrary/YUVRenderingShader.usf"), TEXT("YUVRenderingVS"), SF_Vertex)
IMPLEMENT_SHADER_TYPE(, FYUVRenderingPS, TEXT("/MyShaderLibrary/YUVRenderingShader.usf"), TEXT("YUVRenderingPS"), SF_Pixel)

