#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"


class FYUVRenderShaderBase : public FGlobalShader
{
    //DECLARE_TYPE_LAYOUT(FYUVRenderShaderBase, NonVirtual); // Compile Error
    DECLARE_INLINE_TYPE_LAYOUT(FYUVRenderShaderBase, NonVirtual);

public:

    FYUVRenderShaderBase() {}

    // bind shader parameters
    FYUVRenderShaderBase(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {

        YTextureVal.Bind(Initializer.ParameterMap, TEXT("YTextureVal"));
        YTextureSampler.Bind(Initializer.ParameterMap, TEXT("YTextureSampler"));

        UTextureVal.Bind(Initializer.ParameterMap, TEXT("UTextureVal"));
        UTextureSampler.Bind(Initializer.ParameterMap, TEXT("UTextureSampler"));

        VTextureVal.Bind(Initializer.ParameterMap, TEXT("VTextureVal"));
        VTextureSampler.Bind(Initializer.ParameterMap, TEXT("VTextureSampler"));
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


    template<typename TShaderRHIParamRef>
    void SetParameters(
        FRHICommandListImmediate& RHICmdList,
        const TShaderRHIParamRef ShaderRHI,
        FTexture2DRHIRef InInputTextureY,
        FTexture2DRHIRef InInputTextureU,
        FTexture2DRHIRef InInputTextureV
    )
    {
        SetTextureParameter(RHICmdList, ShaderRHI, YTextureVal, YTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(), InInputTextureY);
        SetTextureParameter(RHICmdList, ShaderRHI, UTextureVal, UTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(), InInputTextureU);
        SetTextureParameter(RHICmdList, ShaderRHI, VTextureVal, VTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(), InInputTextureV);
       
    }

    //// no need
    //virtual bool Serialize(FArchive& Ar) override
    //{
    //    bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
    //    Ar << SimpleColorVal;
    //    return bShaderHasOutdatedParameters;
    //}

private:

    LAYOUT_FIELD(FShaderResourceParameter, YTextureVal);
    LAYOUT_FIELD(FShaderResourceParameter, YTextureSampler);

    LAYOUT_FIELD(FShaderResourceParameter, UTextureVal);
    LAYOUT_FIELD(FShaderResourceParameter, UTextureSampler);

    LAYOUT_FIELD(FShaderResourceParameter, VTextureVal);
    LAYOUT_FIELD(FShaderResourceParameter, VTextureSampler);


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