// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_ShaderTest.h"
#include "Engine/TextureRenderTarget2D.h"
#include "YUVRenderingShader.h"

TGlobalResource<FYUVShaderVertexBuffer> GMyVertexBuffer;
TGlobalResource<FYUVShaderIndexBuffer> GMyIndexBuffer;

void DrawTestShaderRenderTarget_RenderThread(
	FRHICommandListImmediate& RHIImmCmdList,
	FTexture2DRHIRef RenderTargetRHI,
	ERHIFeatureLevel::Type FeatureLevel,
	FTexture2DRHIRef InTextureY, 
	FTexture2DRHIRef InTextureU, 
	FTexture2DRHIRef InTextureV
)
{

	check(IsInRenderingThread());

#if WANTS_DRAW_MESH_EVENTS  
	SCOPED_DRAW_EVENTF(RHIImmCmdList, SceneCapture, TEXT("MyShaderLibrary"));
#else  
	SCOPED_DRAW_EVENT(RHIImmCmdList, DrawTestShaderRenderTarget_RenderThread);
#endif  


	RHIImmCmdList.TransitionResource(ERHIAccess::WritableMask, RenderTargetRHI);

	FRHIRenderPassInfo RPInfo(RenderTargetRHI, ERenderTargetActions::DontLoad_Store, RenderTargetRHI);
	RHIImmCmdList.BeginRenderPass(RPInfo, TEXT("YUVGlobalPixelShaderPass"));

	// Get shaders.
	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
	TShaderMapRef<FYUVRenderingVS> VertexShader(GlobalShaderMap);
	TShaderMapRef<FYUVRenderingPS> PixelShader(GlobalShaderMap);


	FYUVShaderVertexDeclaration VertexDeclaration;
	VertexDeclaration.InitRHI();

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
	SetGraphicsPipelineState(RHIImmCmdList, GraphicsPSOInit);

	// Update viewport.
	//void SetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ)
	RHIImmCmdList.SetViewport(
		0, 0, 0.f, RenderTargetRHI->GetSizeX(), RenderTargetRHI->GetSizeY(), 1.f);

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

	FTexture2DRHIRef RenderTargetRHI = OutputRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	const UWorld* World = WorldContextObject->GetWorld();
	ERHIFeatureLevel::Type FeatureLevel = World->Scene->GetFeatureLevel();

	ENQUEUE_RENDER_COMMAND(CaptureCommand)(

		[RenderTargetRHI, FeatureLevel, InTextureY, InTextureU, InTextureV](FRHICommandListImmediate& RHICmdList) {
			DrawTestShaderRenderTarget_RenderThread(RHICmdList, RenderTargetRHI, FeatureLevel,
			InTextureY->GetResource()->TextureRHI->GetTexture2D(), InTextureU->GetResource()->TextureRHI->GetTexture2D(), InTextureV->GetResource()->TextureRHI->GetTexture2D());
		});
}
