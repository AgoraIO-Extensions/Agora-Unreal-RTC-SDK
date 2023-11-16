// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCaptureVideoScene.h"
#include "RHICommandList.h"
#include "Math/IntRect.h"
#include "RHI.h"
#include "Rendering/SlateRenderer.h"
#include "Widgets/SWindow.h"
#include "RHIDefinitions.h"
#include <chrono>

void UCustomCaptureVideoScene::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	UserExternalVideoFrame = nullptr;

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	SetExternalVideoSource();

	JoinChannel();

	if (FSlateApplication::IsInitialized())
	{
		eventId = FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().AddUObject(this, &UCustomCaptureVideoScene::OnBackBufferReady_RenderThread);
	}
}


void UCustomCaptureVideoScene::CheckPermission()
{
#if PLATFORM_ANDROID
	FString TargetPlatformName = UGameplayStatics::GetPlatformName();
	if (TargetPlatformName == "Android")
	{
		TArray<FString> AndroidPermission;
#if !AGORA_UESDK_AUDIO_ONLY || (!(PLATFORM_ANDROID || PLATFORM_IOS))
		AndroidPermission.Add(FString("android.permission.CAMERA"));
#endif
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UCustomCaptureVideoScene::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandler = MakeShared<FUserRtcEventHandler>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandler.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngineEx();

	int SDKBuild = 0;
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UCustomCaptureVideoScene::ShowUserGuide()
{
	FString Guide =
		"Case: [CustomCaptureVideo]\n"
		"1. It will push the video data to the remote side with the custom data you provide.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UCustomCaptureVideoScene::SetExternalVideoSource()
{
	int ret = RtcEngineProxy->queryInterface(INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngineManager);

	UBFL_Logger::Print(FString::Printf(TEXT("%s queryInterface ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	agora::rtc::SenderOptions sendoptions;

	ret = MediaEngineManager->setExternalVideoSource(true, false, agora::media::EXTERNAL_VIDEO_SOURCE_TYPE::VIDEO_FRAME, sendoptions);

	UBFL_Logger::Print(FString::Printf(TEXT("%s setExternalVideoSource ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UCustomCaptureVideoScene::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UCustomCaptureVideoScene::OnBackBufferReady_RenderThread(SWindow& window, const FTexture2DRHIRef& BackBuffer)
{
	FRHICommandListImmediate& RHICmdList = FRHICommandListExecutor::GetImmediateCommandList();
	auto width = BackBuffer->GetSizeX();
	auto height = BackBuffer->GetSizeY();
	FIntRect Rect(0, 0, BackBuffer->GetSizeX(), BackBuffer->GetSizeY());
	TArray<FColor> Data;

	RHICmdList.ReadSurfaceData(BackBuffer, Rect, Data, FReadSurfaceDataFlags());
	if (UserExternalVideoFrame == nullptr)
	{
		UserExternalVideoFrame = new agora::media::base::ExternalVideoFrame();
	}
	UserExternalVideoFrame->type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_TYPE::VIDEO_BUFFER_RAW_DATA;
	UserExternalVideoFrame->format = agora::media::base::VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_BGRA;
	UserExternalVideoFrame->stride = BackBuffer->GetSizeX();
	UserExternalVideoFrame->height = BackBuffer->GetSizeY();
	UserExternalVideoFrame->cropLeft = 10;
	UserExternalVideoFrame->cropTop = 10;
	UserExternalVideoFrame->cropRight = 10;
	UserExternalVideoFrame->cropBottom = 10;
	UserExternalVideoFrame->rotation = 0;
	UserExternalVideoFrame->timestamp = getTimeStamp();
	if (UserExternalVideoFrame->buffer == nullptr)
	{
		UserExternalVideoFrame->buffer = (uint8*)FMemory::Malloc(BackBuffer->GetSizeX() * BackBuffer->GetSizeY() * 4);
	}
	if (Data.Num() > 4)
	{
		FMemory::Memcpy(UserExternalVideoFrame->buffer, Data.GetData(), BackBuffer->GetSizeX() * BackBuffer->GetSizeY() * 4);
		if (MediaEngineManager != nullptr)
		{
			MediaEngineManager->pushVideoFrame(UserExternalVideoFrame);
		}
	}
}

std::time_t UCustomCaptureVideoScene::getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	std::time_t timestamp = tp.time_since_epoch().count();
	return timestamp;
}


void UCustomCaptureVideoScene::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UCustomCaptureVideoScene::NativeDestruct()
{
	Super::NativeDestruct();
	FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().Remove(eventId);

	UnInitAgoraEngine();

}



void UCustomCaptureVideoScene::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandler.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;
		MediaEngineManager = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}