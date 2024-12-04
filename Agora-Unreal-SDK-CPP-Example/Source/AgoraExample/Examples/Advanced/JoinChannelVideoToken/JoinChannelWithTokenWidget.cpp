// Copyright(c) 2024 Agora.io. All rights reserved.


#include "JoinChannelWithTokenWidget.h"


void UJoinChannelWithTokenWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitUI();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();
}


void UJoinChannelWithTokenWidget::InitUI()
{
	ET_URL->SetText(FText::FromString("http://localhost:8082/fetch_rtc_token"));
}

void UJoinChannelWithTokenWidget::CheckPermission()
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

void UJoinChannelWithTokenWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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


void UJoinChannelWithTokenWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [JoinChannelWithToken]\n"
		"1. You can join the channel using the token you provide.\n"
		"2. You can also join the channel using the token retrieved from the server.\n"
		"3. A simple server can be launched with the website link commented in the source code.\n"
		"4. The demo won't work if the engine version is under 4.27."
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UJoinChannelWithTokenWidget::OnBtnJoinOrRenewTokenlicked()
{
	if (CB_UseURL->GetCheckedState() == ECheckBoxState::Checked) {
		if (ET_URL->GetText().ToString() == "")
		{
			UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s ===  URL is Empty === "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
			return;
		}

		StopRequestToken();
		StartRequestToken();

		UBFL_Logger::Print(FString::Printf(TEXT("%s === [Token] Send HTTP POST Request === "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
	else {
		UBFL_Logger::Print(FString::Printf(TEXT("%s === [Token] Use Token Form User Input === "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);

		FString NewTokenVal = ET_Token->GetText().ToString();
		if (NewTokenVal == "")
		{
			UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s ===  You are using Empty Token! === "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		}

		CallbackForRequestToken(NewTokenVal);
	}
}



void UJoinChannelWithTokenWidget::StartRequestToken()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UJoinChannelWithTokenWidget::RequestToken, 10.0f, true, 0.f);
}

void UJoinChannelWithTokenWidget::StopRequestToken()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
}

void UJoinChannelWithTokenWidget::RequestToken()
{
	// To Deploy Server, You could follow this tutorial: 
	// https://docportal.shengwang.cn/cn/live-streaming-premium-4.x/token_server_android_ng?platform=Windows

	FString URL = ET_URL->GetText().ToString();
	std::function<void(FString, bool)> Callback = [this](FString ValToken, bool IsSuccess) {
		if (!IsSuccess)
			return;

		CallbackForRequestToken(ValToken);
		};
	UBFL_HTTPHelper::FetchToken(URL, 0, ChannelName, 0, Callback);
}


void UJoinChannelWithTokenWidget::CallbackForRequestToken(FString NewToken)
{
	Token = NewToken;

	if (ConnectionState == CONNECTION_STATE_DISCONNECTED || ConnectionState == CONNECTION_STATE_FAILED)
	{
		JoinChannel();
	}
	else {
		UpdateToken();
	}

}

void UJoinChannelWithTokenWidget::JoinChannel()
{
	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->enableVideo();
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d  Token = %s"), *FString(FUNCTION_MACRO), ret, *Token), LogMsgViewPtr);
}


void UJoinChannelWithTokenWidget::UpdateToken()
{
	int ret = AgoraUERtcEngine::Get()->renewToken(TCHAR_TO_UTF8(*Token));
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d  Token = %s"), *FString(FUNCTION_MACRO), ret, *Token), LogMsgViewPtr);
}

void UJoinChannelWithTokenWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UJoinChannelWithTokenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();

}

void UJoinChannelWithTokenWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		StopRequestToken();

		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


#pragma region UI Utility

int UJoinChannelWithTokenWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

int UJoinChannelWithTokenWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
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

void UJoinChannelWithTokenWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
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

void UJoinChannelWithTokenWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
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

void UJoinChannelWithTokenWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
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

void UJoinChannelWithTokenWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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

void UJoinChannelWithTokenWidget::FUserRtcEventHandlerEx::onTokenPrivilegeWillExpire(const RtcConnection& connection, const char* token)
{
	if (!IsWidgetValid())
		return;

	FString TokenStr = UTF8_TO_TCHAR(token);
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s token = %s"), *FString(FUNCTION_MACRO), *TokenStr), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UJoinChannelWithTokenWidget::FUserRtcEventHandlerEx::onConnectionStateChanged(const RtcConnection& connection, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

	WidgetPtr->SetConnectionState(state);
}

#pragma endregion


