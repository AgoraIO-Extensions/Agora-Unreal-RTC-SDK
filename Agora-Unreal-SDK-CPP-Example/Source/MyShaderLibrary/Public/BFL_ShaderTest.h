// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Launch/Resources/Version.h"
#include "BFL_ShaderTest.generated.h"


struct FYUVShaderVertex
{
    FVector4 Position;
    FVector2D UV;
};

class FYUVShaderVertexBuffer: public FVertexBuffer
{
public:
#if ENGINE_MAJOR_VERSION >= 5
    virtual void InitRHI(FRHICommandListBase& RHICmdList) override {
#else
    virtual void InitRHI() override {
#endif
        TResourceArray<FYUVShaderVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
        Vertices.SetNumUninitialized(4);

    Vertices[0].Position = FVector4(-1, 1, 0, 1);
        Vertices[0].UV = FVector2D(0, 0);

        Vertices[1].Position = FVector4(1, 1, 0, 1);
        Vertices[1].UV = FVector2D(1, 0);

    Vertices[2].Position = FVector4(-1, -1, 0, 1);
 Vertices[2].UV = FVector2D(0, 1);

        Vertices[3].Position = FVector4(1, -1, 0, 1);
  Vertices[3].UV = FVector2D(1, 1);

      // Create vertex buffer. Fill buffer with initial data upon creation
#if ENGINE_MAJOR_VERSION >= 5
        FRHIResourceCreateInfo CreateInfo(TEXT("YUVVertexBuffer"));
        CreateInfo.ResourceArray = &Vertices;
        VertexBufferRHI = RHICmdList.CreateBuffer(Vertices.GetResourceDataSize(), BUF_Static | BUF_VertexBuffer, 0, ERHIAccess::VertexOrIndexBuffer, CreateInfo);
#else
        FRHIResourceCreateInfo CreateInfo(&Vertices);
        VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);
#endif
    }
};

class FYUVShaderIndexBuffer : public FIndexBuffer {

public:
#if ENGINE_MAJOR_VERSION >= 5
    virtual void InitRHI(FRHICommandListBase& RHICmdList) override
#else
    virtual void InitRHI() override
#endif
    {
        const uint16 Indices[] = { 0, 1, 2, 2, 1, 3 };

    	TResourceArray<uint16, INDEXBUFFER_ALIGNMENT> IndexBuffer;
        uint32 NumIndices = UE_ARRAY_COUNT(Indices);
        IndexBuffer.SetNumUninitialized(NumIndices);
    FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint16));

#if ENGINE_MAJOR_VERSION >= 5
        FRHIResourceCreateInfo CreateInfo(TEXT("YUVIndexBuffer"));
        CreateInfo.ResourceArray = &IndexBuffer;
      IndexBufferRHI = RHICmdList.CreateBuffer(IndexBuffer.GetResourceDataSize(), BUF_Static | BUF_IndexBuffer, sizeof(uint16), ERHIAccess::VertexOrIndexBuffer, CreateInfo);
#else
        FRHIResourceCreateInfo CreateInfo(&IndexBuffer);
        IndexBufferRHI = RHICreateIndexBuffer(sizeof(uint16), IndexBuffer.GetResourceDataSize(), (uint32)BUF_Static, CreateInfo);
#endif
    }
};


class FYUVShaderVertexDeclaration : public FRenderResource
{
public:

    FVertexDeclarationRHIRef VertexDeclarationRHI;
#if ENGINE_MAJOR_VERSION >= 5
    virtual void InitRHI(FRHICommandListBase& RHICmdList) override
#else
    virtual void InitRHI() override
#endif
{
        FVertexDeclarationElementList Elements;
        uint32 Stride = sizeof(FYUVShaderVertex);
        Elements.Add(FVertexElement(0, STRUCT_OFFSET(FYUVShaderVertex, Position), VET_Float4, 0, Stride));
    Elements.Add(FVertexElement(0, STRUCT_OFFSET(FYUVShaderVertex, UV), VET_Float2, 1, Stride));
#if ENGINE_MAJOR_VERSION >= 5
        VertexDeclarationRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
#else
        VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
#endif
    }
    
    virtual void ReleaseRHI() override {
        VertexDeclarationRHI.SafeRelease();
    }
};



/**
 * 
 */
UCLASS()
class MYSHADERLIBRARY_API UBFL_ShaderTest : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

UFUNCTION(BlueprintCallable, Category = "MyShaderTest", meta = (WorldContext = "WorldContextObject"))
	static void DrawTestShaderRenderTarget(const UObject* WorldContextObject, class UTextureRenderTarget2D* OutputRenderTarget, UTexture2D* InTextureY, UTexture2D* InTextureU, UTexture2D* InTextureV);
};
