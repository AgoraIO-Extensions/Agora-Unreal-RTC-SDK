// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCaptureVideoScene.h"
#include <mutex>



void UCustomCaptureVideoScene::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{

	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetExternalVideoSource();

	JoinChannel();

	InitCamera();

	BackHomeBtn->OnClicked.AddDynamic(this, &UCustomCaptureVideoScene::BackHomeClick);
}


void UCustomCaptureVideoScene::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UTexture2D* cameraFrame = (UTexture2D*)localVideo->Brush.GetResourceObject();
	UMediaTexture* cameraFrameTexture = (UMediaTexture*)cameraFrame;
	if (cameraFrame->PlatformData !=nullptr)
	{
		if(externalVideoFrame ==nullptr)
		{
			externalVideoFrame = new agora::media::base::ExternalVideoFrame();
		}
		externalVideoFrame->type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_TYPE::VIDEO_BUFFER_RAW_DATA;
		externalVideoFrame->format = agora::media::base::VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_BGRA;

		TArray<FColor> OutColors;
		FMediaTextureResource* MediaTextureResource = static_cast<FMediaTextureResource*>(cameraFrameTexture->Resource);
		MediaTextureResource->ReadPixels(OutColors);
		externalVideoFrame->stride = cameraFrameTexture->GetWidth();
		externalVideoFrame->height = cameraFrameTexture->GetHeight();
		externalVideoFrame->cropLeft = 10;
		externalVideoFrame->cropTop = 10;
		externalVideoFrame->cropRight = 10;
		externalVideoFrame->cropBottom = 10;
		externalVideoFrame->rotation = 0;
		if (externalVideoFrame->buffer == nullptr )
		{
			externalVideoFrame->buffer = (uint8*)FMemory::Malloc(OutColors.Num() * 4);
		}
		FMemory::Memcpy(externalVideoFrame->buffer, OutColors.GetData(), OutColors.Num() * 4);
		externalVideoFrame->timestamp = getTimeStamp();

		MediaEngineManager->pushVideoFrame(externalVideoFrame);
	}

}


void UCustomCaptureVideoScene::NativeDestruct()
{
	Super::NativeConstruct();
	if (RtcEngineProxy != nullptr)
	{
		if (externalVideoFrame != nullptr)
		{
			if (externalVideoFrame->buffer != nullptr)
			{
				delete externalVideoFrame->buffer;
				externalVideoFrame->buffer = nullptr;
			}
			delete externalVideoFrame;
			externalVideoFrame = nullptr;
		}
		if(MediaEngineManager!=nullptr)
		{
			MediaEngineManager->release();
		}
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
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

	int ret1 = MediaEngineManager->setExternalVideoSource(true, false, agora::media::EXTERNAL_VIDEO_SOURCE_TYPE::VIDEO_FRAME, sendoptions);
	
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("setExternalVideoSource init is %d"), ret1));
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


void UCustomCaptureVideoScene::BackHomeClick()
{
	UClass* AgoraWidgetClass = LoadClass<UBaseAgoraUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/API-Example/Advance/MainWidgetManager.MainWidgetManager_C'"));

	UBaseAgoraUserWidget* AgoraWidget = CreateWidget<UBaseAgoraUserWidget>(GetWorld(), AgoraWidgetClass);

	AgoraWidget->AddToViewport();

	AgoraWidget->InitAgoraWidget(FString(AppID.c_str()), FString(Token.c_str()), FString(ChannelName.c_str()));

	this->RemoveFromViewport();
}