// Copyright(c) 2024 Agora.io. All rights reserved.


#include "EncryptionSampleWidget.h"

void UEncryptionSampleWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();
}


void UEncryptionSampleWidget::CheckPermission()
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


void UEncryptionSampleWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}


void UEncryptionSampleWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [EncryptionSample]\n"
		"1. Join the channel with the encryption.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UEncryptionSampleWidget::OnBtnJoinChannelClicked()
{
	SetEncryption();
	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->enableVideo();
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UEncryptionSampleWidget::SetEncryption()
{
	if (ET_RoomPassword->GetText().ToString() == "")
	{
		UBFL_Logger::PrintError(FString::Printf(TEXT("%s RoomPassword is empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	char ValEncryptionKdfSalt[32] = "EncryptionKdfSaltInBase64String";

	EncryptionConfig config;
	config.encryptionMode = ENCRYPTION_MODE::AES_128_GCM2;
	std::string StdStrKey = TCHAR_TO_UTF8(*ET_RoomPassword->GetText().ToString());
	config.encryptionKey = StdStrKey.c_str();
	FMemory::Memcpy(config.encryptionKdfSalt, ValEncryptionKdfSalt, 32);

	int ret = AgoraUERtcEngine::Get()->enableEncryption(true, config);

	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UEncryptionSampleWidget::OnBtnLeaveChannelClicked()
{
	int ret = AgoraUERtcEngine::Get()->leaveChannel();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UEncryptionSampleWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UEncryptionSampleWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}



void UEncryptionSampleWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


#pragma region UI Utility

int UEncryptionSampleWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	/*
		For local view:
			please reference the callback function Ex.[onCaptureVideoFrame]

		For remote view:
			please reference the callback function [onRenderVideoFrame]

		channelId will be set in [setupLocalVideo] / [setupRemoteVideo]
	*/

	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{

		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);

		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}

	return ret;
}

int UEncryptionSampleWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}
	return ret;
}

#pragma endregion


#pragma region AgoraCallback - IRtcEngineEventHandlerEx

void UEncryptionSampleWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UEncryptionSampleWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UEncryptionSampleWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UEncryptionSampleWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

#pragma endregion