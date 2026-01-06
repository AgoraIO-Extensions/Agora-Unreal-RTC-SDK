// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_ShaderTest.h"
#include "Engine/TextureRenderTarget2D.h"
#include "YUVRenderingShader.h"
#include "Runtime/Launch/Resources/Version.h"

TGlobalResource<FYUVShaderVertexBuffer> GMyVertexBuffer;
TGlobalResource<FYUVShaderIndexBuffer> GMyIndexBuffer;

void DrawTestShaderRenderTarget_RenderThread(
	FRHICommandListImmediate& RHIImmCmdList,
	FTextureRHIRef RenderTargetRHI,
	int32 SizeX,
	int32 SizeY,
	ERHIFeatureLevel::Type FeatureLevel,
	FTextureRHIRef InTextureY, 
	FTextureRHIRef InTextureU, 
	FTextureRHIRef InTextureV
)
{

	check(IsInRenderingThread());

#if WANTS_DRAW_MESH_EVENTS  
	SCOPED_DRAW_EVENTF(RHIImmCmdList, SceneCapture, TEXT("MyShaderLibrary"));
#else  
	SCOPED_DRAW_EVENT(RHIImmCmdList, DrawTestShaderRenderTarget_RenderThread);
#endif  

#if ENGINE_MAJOR_VERSION >= 5
	RHIImmCmdList.Transition(FRHITransitionInfo(RenderTargetRHI, ERHIAccess::Unknown, ERHIAccess::RTV));
#endif

	FRHIRenderPassInfo RPInfo(RenderTargetRHI, ERenderTargetActions::DontLoad_Store, RenderTargetRHI);
	RHIImmCmdList.BeginRenderPass(RPInfo, TEXT("YUVGlobalPixelShaderPass"));

	// Get shaders.
#if ENGINE_MAJOR_VERSION >= 5
 FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIShaderPlatform);
#else
	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
#endif
	TShaderMapRef<FYUVRenderingVS> VertexShader(GlobalShaderMap);
	TShaderMapRef<FYUVRenderingPS> PixelShader(GlobalShaderMap);


	FYUVShaderVertexDeclaration VertexDeclaration;
#if ENGINE_MAJOR_VERSION >= 5
	VertexDeclaration.InitRHI(RHIImmCmdList);
#else
	VertexDeclaration.InitRHI();
#endif

	// Set the graphic pipeline state.
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHIImmCmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDeclaration.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
#if ENGINE_MAJOR_VERSION >= 5
	SetGraphicsPipelineState(RHIImmCmdList, GraphicsPSOInit, 0);
#else
	SetGraphicsPipelineState(RHIImmCmdList, GraphicsPSOInit);
#endif

	// Update viewport.
#if ENGINE_MAJOR_VERSION >= 5
	RHIImmCmdList.SetViewport(
		0.f, 0.f, 0.f, (float)SizeX, (float)SizeY, 1.f);
#else
	RHIImmCmdList.SetViewport(
		0, 0, 0.f, SizeX, SizeY, 1.f);
#endif

	VertexShader->SetParameters(RHIImmCmdList, VertexShader.GetVertexShader(), InTextureY, InTextureU, InTextureV);
	PixelShader->SetParameters(RHIImmCmdList, PixelShader.GetPixelShader(), InTextureY, InTextureU, InTextureV);

	RHIImmCmdList.SetStreamSource(0, GMyVertexBuffer.VertexBufferRHI, 0);
	RHIImmCmdList.DrawIndexedPrimitive(
		GMyIndexBuffer.IndexBufferRHI,
		/*BaseVertexIndex=*/ 0,
		/*MinIndex=*/ 0,
		/*NumVertices=*/ 4,
		/*StartIndex=*/ 0,
		/*NumPrimitives=*/ 2,
		/*NumInstances=*/ 1);

	RHIImmCmdList.EndRenderPass();
}




void UBFL_ShaderTest::DrawTestShaderRenderTarget
(
	const UObject* WorldContextObject,
	class UTextureRenderTarget2D* OutputRenderTarget,
	UTexture2D* InTextureY,
	UTexture2D* InTextureU, 
	UTexture2D* InTextureV
)
{
	check(IsInGameThread());

	if (!OutputRenderTarget)
	{
		return;
	}

	FTextureRHIRef RenderTargetRHI = OutputRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	const UWorld* World = WorldContextObject->GetWorld();
	ERHIFeatureLevel::Type FeatureLevel = World->Scene->GetFeatureLevel();

	int32 SizeX = OutputRenderTarget->SizeX;
	int32 SizeY = OutputRenderTarget->SizeY;

	ENQUEUE_RENDER_COMMAND(CaptureCommand)(
#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
		[RenderTargetRHI, SizeX, SizeY, FeatureLevel, InTextureY, InTextureU, InTextureV](FRHICommandListImmediate& RHICmdList) {
#else
		[=](FRHICommandListImmediate& RHICmdList) {
#endif
			DrawTestShaderRenderTarget_RenderThread(RHICmdList, RenderTargetRHI, SizeX, SizeY, FeatureLevel,
			InTextureY->GetResource()->TextureRHI, InTextureU->GetResource()->TextureRHI, InTextureV->GetResource()->TextureRHI);
		});
}
