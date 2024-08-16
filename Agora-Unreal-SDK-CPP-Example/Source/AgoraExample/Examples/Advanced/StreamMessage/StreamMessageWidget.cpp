// Copyright(c) 2024 Agora.io. All rights reserved.


#include "StreamMessageWidget.h"
#include <string>

void UStreamMessageWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	JoinChannel();

	CreateDataStreamId();
}

void UStreamMessageWidget::CheckPermission()
{
#if PLATFORM_ANDROID
	FString TargetPlatformName = UGameplayStatics::GetPlatformName();
	if (TargetPlatformName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UStreamMessageWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
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


	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);

}

void UStreamMessageWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [StreamMessage]\n"
		"1. You need to use 2 examples of StreamMessage. One is for sending messages and the other one is for receiving.\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UStreamMessageWidget::JoinChannel()
{
	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->enableVideo();
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_BROADCASTER);
	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), "", 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UStreamMessageWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UStreamMessageWidget::OnBtnSendClicked()
{
	FString SentMsg = ET_MsgText->GetText().ToString();

	if (SentMsg == "")
	{
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s Dont send empty message!"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	int streamId = CreateDataStreamId();
	if (streamId < 0)
	{

		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s CreateDataStream failed!"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	else
	{
		SendStreamMessage(streamId, SentMsg);
		ET_MsgText->SetText(FText::GetEmpty());
	}
}


int UStreamMessageWidget::CreateDataStreamId()
{
	if (StreamId == -1)
	{
		DataStreamConfig config;
		config.syncWithAudio = false;
		config.ordered = true;
		int ret = AgoraUERtcEngine::Get()->createDataStream(&StreamId, config);
		UBFL_Logger::Print(FString::Printf(TEXT("%s createDataStream ret %d, streamId %d"), *FString(FUNCTION_MACRO), ret, StreamId), LogMsgViewPtr);
	}
	return StreamId;
}

void UStreamMessageWidget::SendStreamMessage(int StreamID, FString Msg)
{
	std::string StdStrMsg = TCHAR_TO_UTF8(*Msg);
	int Size = strlen(StdStrMsg.c_str()) + 1;
	int ret = AgoraUERtcEngine::Get()->sendStreamMessage(StreamID, TCHAR_TO_UTF8(*Msg), Size);
	UBFL_Logger::Print(FString::Printf(TEXT("%s sendStreamMessage ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s sendStreamMessage  message %s,length %d"), *FString(FUNCTION_MACRO), *Msg, Msg.Len()), LogMsgViewPtr);
}


void UStreamMessageWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}



void UStreamMessageWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandler.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}

#pragma region AgoraCallback - IRtcEngineEventHandler

void UStreamMessageWidget::FUserRtcEventHandler::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s uid=%u"), *FString(FUNCTION_MACRO), uid), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UStreamMessageWidget::FUserRtcEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

		});

}


void UStreamMessageWidget::FUserRtcEventHandler::onUserJoined(agora::rtc::uid_t uid, int elapsed)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s uid=%u"), *FString(FUNCTION_MACRO), uid), WidgetPtr->GetLogMsgViewPtr());

		});

}

void UStreamMessageWidget::FUserRtcEventHandler::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
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
			UBFL_Logger::Print(FString::Printf(TEXT("%s uid=%u"), *FString(FUNCTION_MACRO), uid), WidgetPtr->GetLogMsgViewPtr());

		});
}

void UStreamMessageWidget::FUserRtcEventHandler::onStreamMessage(uid_t userId, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	if (!IsWidgetValid())
		return;

	FString Msg = UTF8_TO_TCHAR(data);

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

			UBFL_Logger::Print(FString::Printf(TEXT("%s  uid: %u,streamId %d,length %d,sentTs %d"), *FString(FUNCTION_MACRO), userId, streamId, Msg.Len(), sentTs), WidgetPtr->GetLogMsgViewPtr());
			UBFL_Logger::Print(FString::Printf(TEXT("===> Msg[%s]"), *Msg), WidgetPtr->GetLogMsgViewPtr());
		});
}

void UStreamMessageWidget::FUserRtcEventHandler::onStreamMessageError(uid_t userId, int streamId, int code, int missed, int cached)
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

			UBFL_Logger::Print(FString::Printf(TEXT("%s uid: %u,streamId %d,code %d,missed %d,cached %d"), *FString(FUNCTION_MACRO), userId, streamId, code, missed, cached), WidgetPtr->GetLogMsgViewPtr());

		});
}

#pragma endregion RtcEngineCallBack