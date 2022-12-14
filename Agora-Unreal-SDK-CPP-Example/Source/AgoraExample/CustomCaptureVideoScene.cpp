// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCaptureVideoScene.h"
#include "RHICommandList.h"
#include "Math/IntRect.h"
#include "RHI.h"
#include "Rendering/SlateRenderer.h"
#include "Widgets/SWindow.h"
#include "RHIDefinitions.h"


void UCustomCaptureVideoScene::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetExternalVideoSource();

	JoinChannel();

	if (FSlateApplication::IsInitialized())
	{
		eventId = FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().AddUObject(this, &UCustomCaptureVideoScene::OnBackBufferReady_RenderThread);
	}

	BackHomeBtn->OnClicked.AddDynamic(this, &UCustomCaptureVideoScene::OnBackHomeButtonClick);
}


void UCustomCaptureVideoScene::OnBackHomeButtonClick()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
		MediaEngineManager = nullptr;
	}
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UCustomCaptureVideoScene::OnBackBufferReady_RenderThread(SWindow& window, const FTexture2DRHIRef& BackBuffer)
{
	FRHICommandListImmediate& RHICmdList = FRHICommandListExecutor::GetImmediateCommandList();
	auto width = BackBuffer->GetSizeX();
	auto height = BackBuffer->GetSizeY();
	FIntRect Rect(0, 0, BackBuffer->GetSizeX(), BackBuffer->GetSizeY());
	TArray<FColor> Data;

	RHICmdList.ReadSurfaceData(BackBuffer, Rect, Data, FReadSurfaceDataFlags());
	if (externalVideoFrame == nullptr)
	{
		externalVideoFrame = new agora::media::base::ExternalVideoFrame();
	}
	externalVideoFrame->type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_TYPE::VIDEO_BUFFER_RAW_DATA;
	externalVideoFrame->format = agora::media::base::VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_BGRA;
	externalVideoFrame->stride = BackBuffer->GetSizeX();
	externalVideoFrame->height = BackBuffer->GetSizeY();
	externalVideoFrame->cropLeft = 10;
	externalVideoFrame->cropTop = 10;
	externalVideoFrame->cropRight = 10;
	externalVideoFrame->cropBottom = 10;
	externalVideoFrame->rotation = 0;
	externalVideoFrame->timestamp = getTimeStamp();
	if (externalVideoFrame->buffer == nullptr)
	{
		externalVideoFrame->buffer = (uint8*)FMemory::Malloc(BackBuffer->GetSizeX() * BackBuffer->GetSizeY() * 4);
	}
	if (Data.Num() > 4)
	{
		FMemory::Memcpy(externalVideoFrame->buffer, Data.GetData(), BackBuffer->GetSizeX() * BackBuffer->GetSizeY() * 4);
		if (MediaEngineManager!=nullptr)
		{
			MediaEngineManager->pushVideoFrame(externalVideoFrame);
		}
	}
}


void UCustomCaptureVideoScene::NativeDestruct()
{
	Super::NativeConstruct();
	FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().Remove(eventId);
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
		MediaEngineManager = nullptr;
	}
}

void UCustomCaptureVideoScene::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
	FString pathfromName = UGameplayStatics::GetPlatformName();
	if (pathfromName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.CAMERA"));
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
	std::string APP_IDStr(TCHAR_TO_ANSI(*APP_ID));
	AppID = APP_IDStr;
	std::string TOKENStr(TCHAR_TO_ANSI(*TOKEN));
	Token = TOKENStr;
	std::string CHANNEL_NAMEStr(TCHAR_TO_ANSI(*CHANNEL_NAME));
	ChannelName = CHANNEL_NAMEStr;

	RtcEngineContext.appId = AppID.c_str();
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);
}

void UCustomCaptureVideoScene::SetExternalVideoSource()
{
	int ret = RtcEngineProxy->queryInterface(INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE,(void**)&MediaEngineManager);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("MediaEngine init is %d"),ret));

	agora::rtc::SenderOptions sendoptions;

	ret = MediaEngineManager->setExternalVideoSource(true, false, agora::media::EXTERNAL_VIDEO_SOURCE_TYPE::VIDEO_FRAME, sendoptions);
	
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("setExternalVideoSource init is %d"), ret));
}



void UCustomCaptureVideoScene::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
}

std::time_t UCustomCaptureVideoScene::getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	std::time_t timestamp = tp.time_since_epoch().count();
	return timestamp;
}


void UCustomCaptureVideoScene::NativeConstruct()
{
	Super::NativeConstruct();


	externalVideoFrame = nullptr; 
}
