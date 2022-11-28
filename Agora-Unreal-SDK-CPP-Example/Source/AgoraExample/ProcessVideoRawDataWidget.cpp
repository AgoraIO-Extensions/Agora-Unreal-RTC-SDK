// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessVideoRawDataWidget.h"

void UProcessVideoRawDataWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();
}


void UProcessVideoRawDataWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) {

	RtcEngineContext RtcEngineContext;
	std::string APP_IDStr(TCHAR_TO_ANSI(*APP_ID));
	AppID = APP_IDStr;
	std::string TOKENStr(TCHAR_TO_ANSI(*TOKEN));
	Token = TOKENStr;
	std::string CHANNEL_NAMEStr(TCHAR_TO_ANSI(*CHANNEL_NAME));
	ChannelName = CHANNEL_NAMEStr;

	RtcEngineContext.appId = AppID.c_str();
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();
	RtcEngineProxy->initialize(RtcEngineContext);

	RtcEngineProxy->queryInterface(AGORA_IID_MEDIA_ENGINE, (void**)&MediaEngine);

	MediaEngine->registerVideoFrameObserver(this);


}

void UProcessVideoRawDataWidget::SetUpUIEvent() {

	JoinBtn->OnClicked.AddDynamic(this, &UProcessVideoRawDataWidget::OnJoinButtonClick);
	LeaveBtn->OnClicked.AddDynamic(this, &UProcessVideoRawDataWidget::OnLeaveButtonClick);
}


void UProcessVideoRawDataWidget::OnJoinButtonClick() {

	UE_LOG(LogTemp, Warning, TEXT("UProcessVideoRawDataWidget OnJoinButtonClick ======"));
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->joinChannel(Token.c_str(), ChannelName.c_str(), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

}


void UProcessVideoRawDataWidget::CheckAndroidPermission()
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

void UProcessVideoRawDataWidget::OnLeaveButtonClick() {
	UE_LOG(LogTemp, Warning, TEXT("UProcessVideoRawDataWidget OnLeaveButtonClick ======"));

	RtcEngineProxy->leaveChannel();
	localVideo->SetBrush(EmptyBrush);
	remoteVideo->SetBrush(EmptyBrush);

}

#pragma region RtcEngineCallBack


void UProcessVideoRawDataWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("UProcessVideoRawDataWidget::onUserOffline  uid: %u"), uid);

		remoteVideo->SetBrush(EmptyBrush);
	});
}



void UProcessVideoRawDataWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UE_LOG(LogTemp, Warning, TEXT("UProcessVideoRawDataWidget::onLeaveChannel"));
	});
}
#pragma endregion RtcEngineCallBack


bool bisRelease = false;


void UProcessVideoRawDataWidget::NativeDestruct() {

	Super::NativeDestruct();

	if (RtcEngineProxy != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UProcessVideoRawDataWidget::NativeDestruct"));
		if (MediaEngine!=nullptr)
		{
			MediaEngine->registerVideoFrameObserver(nullptr);
		}
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}

}


#pragma region RtcEngineCallBack

bool UProcessVideoRawDataWidget::onCaptureVideoFrame(VideoFrame& videoFrame)
{
	//UE_LOG(LogTemp, Warning, TEXT("UProcessVideoRawDataWidget::onCaptureVideoFrame"));
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}
		if (LocalRenderTexture == nullptr || !LocalRenderTexture->IsValidLowLevel())
		{
			LocalRenderTexture = UTexture2D::CreateTransient(videoFrame.width, videoFrame.height, PF_R8G8B8A8);
		}
		else
		{
			UTexture2D* tex = (UTexture2D*)LocalRenderTexture;
			uint8* raw = (uint8*)tex->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			memcpy(raw, videoFrame.yBuffer, videoFrame.height * videoFrame.width * 4);
			tex->PlatformData->Mips[0].BulkData.Unlock();
			tex->UpdateResource();
			LocalRenderBrush.SetResourceObject(tex);
			if (localVideo != nullptr) {
				localVideo->SetBrush(LocalRenderBrush);
			}
		}
	});
	return true;
}

bool UProcessVideoRawDataWidget::onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!bInitialized)
		{
			return;
		}
		if (RemoteRenderTexture == nullptr || !RemoteRenderTexture->IsValidLowLevel())
		{
			RemoteRenderTexture = UTexture2D::CreateTransient(videoFrame.width, videoFrame.height, PF_R8G8B8A8);
		}
		else
		{
			UTexture2D* tex = (UTexture2D*)RemoteRenderTexture;
			uint8* raw = (uint8*)tex->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			memcpy(raw, videoFrame.yBuffer, videoFrame.height * videoFrame.width * 4);
			tex->PlatformData->Mips[0].BulkData.Unlock();
			tex->UpdateResource();
			RemoteRenderBrush.SetResourceObject(tex);
			if (remoteVideo != nullptr) {
				remoteVideo->SetBrush(RemoteRenderBrush);
			}
		}
	});
	return true;
}

bool UProcessVideoRawDataWidget::onPreEncodeVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onScreenCaptureVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onPreEncodeScreenVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId)
{

	return true;
}

bool UProcessVideoRawDataWidget::onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame)
{

	return true;
}

bool UProcessVideoRawDataWidget::onTranscodedVideoFrame(VideoFrame& videoFrame)
{
	return true;
}

agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE UProcessVideoRawDataWidget::getVideoFrameProcessMode()
{

	return PROCESS_MODE_READ_ONLY;
}

agora::media::base::VIDEO_PIXEL_FORMAT UProcessVideoRawDataWidget::getVideoFormatPreference()
{
	return agora::media::base::VIDEO_PIXEL_RGBA;
}

bool UProcessVideoRawDataWidget::getRotationApplied()
{

	return true;
}

bool UProcessVideoRawDataWidget::getMirrorApplied()
{

	return false;
}

uint32_t UProcessVideoRawDataWidget::getObservedFramePosition()
{

	return agora::media::base::POSITION_POST_CAPTURER | agora::media::base::POSITION_PRE_RENDERER;
}

bool UProcessVideoRawDataWidget::isExternal()
{

	return true;
}

#pragma endregion RtcEngineCallBack
