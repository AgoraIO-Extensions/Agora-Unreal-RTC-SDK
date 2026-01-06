#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "ShaderParameterStruct.h"
#include "Runtime/Launch/Resources/Version.h"

// Engine version compatibility macros
#if ENGINE_MAJOR_VERSION >= 5
#define ENABLE_UE5_RENDER 1
#else
    #define ENABLE_UE5_RENDER 0
#endif

class FYUVRenderShaderBase : public FGlobalShader
{
    DECLARE_INLINE_TYPE_LAYOUT(FYUVRenderShaderBase, NonVirtual);

public:

    FYUVRenderShaderBase() {}

    // bind shader parameters
    FYUVRenderShaderBase(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {
#if !ENABLE_UE5_RENDER
        // UE4.27 parameter binding
        YTextureVal.Bind(Initializer.ParameterMap, TEXT("YTextureVal"));
        YTextureSampler.Bind(Initializer.ParameterMap, TEXT("YTextureSampler"));

        UTextureVal.Bind(Initializer.ParameterMap, TEXT("UTextureVal"));
        UTextureSampler.Bind(Initializer.ParameterMap, TEXT("UTextureSampler"));

        VTextureVal.Bind(Initializer.ParameterMap, TEXT("VTextureVal"));
        VTextureSampler.Bind(Initializer.ParameterMap, TEXT("VTextureSampler"));
#endif
    }

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
    // For All Platforms
        return true;
    }


    static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
    {
      FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
     OutEnvironment.SetDefine(TEXT("TEST_MICRO"), 1);
    }

#if ENABLE_UE5_RENDER
    // UE5 Shader Parameters Structure
    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_TEXTURE(Texture2D, YTextureVal)
        SHADER_PARAMETER_SAMPLER(SamplerState, YTextureSampler)
        SHADER_PARAMETER_TEXTURE(Texture2D, UTextureVal)
        SHADER_PARAMETER_SAMPLER(SamplerState, UTextureSampler)
        SHADER_PARAMETER_TEXTURE(Texture2D, VTextureVal)
        SHADER_PARAMETER_SAMPLER(SamplerState, VTextureSampler)
    END_SHADER_PARAMETER_STRUCT()
#endif

    template<typename TShaderRHIParamRef>
    void SetParameters(
  FRHICommandListImmediate& RHICmdList,
    const TShaderRHIParamRef ShaderRHI,
 FTextureRHIRef InInputTextureY,
  FTextureRHIRef InInputTextureU,
 FTextureRHIRef InInputTextureV
    )
{

#if ENABLE_UE5_RENDER
     // UE5: Create parameter struct and set values
     FParameters ShaderParameters;
     ShaderParameters.YTextureVal = InInputTextureY;
     ShaderParameters.YTextureSampler = TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
     ShaderParameters.UTextureVal = InInputTextureU;
     ShaderParameters.UTextureSampler = TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
     ShaderParameters.VTextureVal = InInputTextureV;
     ShaderParameters.VTextureSampler = TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
    
     // UE5.5 correct API: Get batched parameters and set them using the metadata from the struct
     FRHIBatchedShaderParameters& BatchedParameters = RHICmdList.GetScratchShaderParameters();
     SetUniformBufferParameterImmediate(BatchedParameters, GetUniformBufferParameter<FParameters>(), ShaderParameters);
     RHICmdList.SetBatchedShaderParameters(ShaderRHI, BatchedParameters);
#else
    // UE4.27 parameter binding
    SetTextureParameter(RHICmdList, ShaderRHI, YTextureVal, YTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(), InInputTextureY);
    SetTextureParameter(RHICmdList, ShaderRHI, UTextureVal, UTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(), InInputTextureU);
    SetTextureParameter(RHICmdList, ShaderRHI, VTextureVal, VTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(), InInputTextureV);
#endif
    }


private:

#if !ENABLE_UE5_RENDER
    // UE4.27 shader parameter fields
  LAYOUT_FIELD(FShaderResourceParameter, YTextureVal);
  LAYOUT_FIELD(FShaderResourceParameter, YTextureSampler);

  LAYOUT_FIELD(FShaderResourceParameter, UTextureVal);
  LAYOUT_FIELD(FShaderResourceParameter, UTextureSampler);
  
  LAYOUT_FIELD(FShaderResourceParameter, VTextureVal);
  LAYOUT_FIELD(FShaderResourceParameter, VTextureSampler);
#endif
};



class FYUVRenderingVS : public FYUVRenderShaderBase {
public:
  DECLARE_GLOBAL_SHADER(FYUVRenderingVS);

public:
FYUVRenderingVS() {}

    FYUVRenderingVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
     : FYUVRenderShaderBase(Initializer) {}
};



class FYUVRenderingPS : public FYUVRenderShaderBase {
public:
  DECLARE_GLOBAL_SHADER(FYUVRenderingPS);

public:
    FYUVRenderingPS() {}

    FYUVRenderingPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
: FYUVRenderShaderBase(Initializer) {}
};