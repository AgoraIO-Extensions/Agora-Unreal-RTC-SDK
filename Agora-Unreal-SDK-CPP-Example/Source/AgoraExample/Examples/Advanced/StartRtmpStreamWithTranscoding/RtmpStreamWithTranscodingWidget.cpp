// Fill out your copyright notice in the Description page of Project Settings.


#include "RtmpStreamWithTranscodingWidget.h"


void URtmpStreamWithTranscodingWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	JoinChannel();
}


void URtmpStreamWithTranscodingWidget::CheckPermission()
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

void URtmpStreamWithTranscodingWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	int SDKBuild = 0;
	const char* SDKVersionInfo = RtcEngineProxy->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = RtcEngineProxy->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void URtmpStreamWithTranscodingWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [RtmpStreamWithTranscoding]\n"
		"1. Publishes the local stream with transcoding to a specified CDN live RTMP address.  (CDN live only.)\n"
		"2. Remember to enter your URL in the editable text box.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void URtmpStreamWithTranscodingWidget::JoinChannel()
{
	RtcEngineProxy->enableAudio();
	RtcEngineProxy->enableVideo();
	RtcEngineProxy->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}



void URtmpStreamWithTranscodingWidget::OnBtnStartClicked()
{
	if (UID == 0)
	{
		UBFL_Logger::Print(FString::Printf(TEXT("%s You must join channel first "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	agora::rtc::LiveTranscoding ValLiveTranscoding;

	ValLiveTranscoding.userCount = 1;

	TSharedPtr<TranscodingUser> ValTranscodingUsers = MakeShared<TranscodingUser>();
	ValTranscodingUsers->uid = UID;
	ValTranscodingUsers->x = 0;
	ValTranscodingUsers->y = 0;
	ValTranscodingUsers->width = 360;
	ValTranscodingUsers->height = 640;
	ValTranscodingUsers->alpha = 1;
	ValTranscodingUsers->zOrder = 1;
	ValTranscodingUsers->audioChannel = 0;
	ValLiveTranscoding.transcodingUsers = ValTranscodingUsers.Get();

	FString URL = ET_URL->GetText().ToString();;
	if (URL == "")
	{
		UBFL_Logger::Print(FString::Printf(TEXT("%s You must input your rtmpUrl in Inspector of videocanvas first "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	auto ret = RtcEngineProxy->startRtmpStreamWithTranscoding(TCHAR_TO_UTF8(*URL), ValLiveTranscoding);

	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

	if (ret == 0)
	{
		UBFL_Logger::Print(FString::Printf(TEXT("%s url %s"), *FString(FUNCTION_MACRO), *URL), LogMsgViewPtr);
		/*
			Way to verify the remote end
			1.install ffmpeg(brew install ffmpeg)
			2.ffplay rtmp://play.xxxxx.xxx.xxxx
			or
			1.vlc open rtmp://play.xxxxx.xxx.xxxx
		 */
	}
}

void URtmpStreamWithTranscodingWidget::OnBtnUpdateClicked()
{
	agora::rtc::LiveTranscoding ValLiveTranscoding;
	ValLiveTranscoding.userCount = 1;

	TSharedPtr<TranscodingUser> ValTranscodingUsers = MakeShared<TranscodingUser>();
	ValTranscodingUsers->uid = UID;
	ValTranscodingUsers->x = 0;
	ValTranscodingUsers->y = 0;
	ValTranscodingUsers->width = 640;
	ValTranscodingUsers->height = 960;
	ValTranscodingUsers->alpha = 1;
	ValTranscodingUsers->zOrder = 1;
	ValTranscodingUsers->audioChannel = 0;
	ValLiveTranscoding.transcodingUsers = ValTranscodingUsers.Get();

	int ret = RtcEngineProxy->updateRtmpTranscoding(ValLiveTranscoding);

	UBFL_Logger::Print(FString::Printf(TEXT("%s updateRtmpTranscoding ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void URtmpStreamWithTranscodingWidget::OnBtnStopClicked()
{
	FString url = ET_URL->GetText().ToString();
	if (url == "")
	{
		UBFL_Logger::Print(FString::Printf(TEXT("%s You must input your rtmpUrl in Inspector of videocanvas first "), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	int ret = RtcEngineProxy->stopRtmpStream(TCHAR_TO_UTF8(*url));
	UBFL_Logger::Print(FString::Printf(TEXT("%s stopRtmpStream ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void URtmpStreamWithTranscodingWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void URtmpStreamWithTranscodingWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}



void URtmpStreamWithTranscodingWidget::UnInitAgoraEngine()
{
	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->leaveChannel();
		RtcEngineProxy->unregisterEventHandler(UserRtcEventHandler.Get());
		RtcEngineProxy->release();
		RtcEngineProxy = nullptr;

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


#pragma region UI Utility

int URtmpStreamWithTranscodingWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	/*
		For local view:
			please reference the callback function Ex.[onCaptureVideoFrame]

		For remote view:
			please reference the callback function [onRenderVideoFrame]

		channelId will be set in [setupLocalVideo] / [setupRemoteVideo]
	*/

	int ret = -ERROR_NULLPTR;

	if (RtcEngineProxy == nullptr)
		return ret;

	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);
		ret = RtcEngineProxy->setupLocalVideo(videoCanvas);
	}
	else
	{

		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);

		if (channelId == "") {
			ret = RtcEngineProxy->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	}

	return ret;
}

int URtmpStreamWithTranscodingWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	int ret = -ERROR_NULLPTR;

	if (RtcEngineProxy == nullptr)
		return ret;

	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		ret = RtcEngineProxy->setupLocalVideo(videoCanvas);
	}
	else
	{
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		if (channelId == "") {
			ret = RtcEngineProxy->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
		}
	}
	return ret;
}

#pragma endregion


#pragma region AgoraCallback - IRtcEngineEventHandler

void URtmpStreamWithTranscodingWidget::FUserRtcEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) {

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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}

			WidgetPtr->SetLocalUID(uid);
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);

		});
}


void URtmpStreamWithTranscodingWidget::FUserRtcEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			WidgetPtr->MakeVideoView(uid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE);
		});
}

void URtmpStreamWithTranscodingWidget::FUserRtcEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
			WidgetPtr->ReleaseVideoView(uid, VIDEO_SOURCE_REMOTE);
		});
}

void URtmpStreamWithTranscodingWidget::FUserRtcEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s "), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}


void URtmpStreamWithTranscodingWidget::FUserRtcEventHandler::onTranscodingUpdated()
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s OnTranscodingUpdated"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());
		});
}

void URtmpStreamWithTranscodingWidget::FUserRtcEventHandler::onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR_TYPE errCode)
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
				UBFL_Logger::PrintError(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}

			UBFL_Logger::Print(FString::Printf(TEXT("%s url:%s,state:%d ,errCode:%d "), *FString(FUNCTION_MACRO), UTF8_TO_TCHAR(url), state, errCode), WidgetPtr->GetLogMsgViewPtr());
		});
}

#pragma endregion
