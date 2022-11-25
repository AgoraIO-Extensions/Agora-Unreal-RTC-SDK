// Fill out your copyright notice in the Description page of Project Settings.


#include "StreamMessageWidget.h"

void UStreamMessageWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	CheckAndroidPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	SetUpUIEvent();

	OnJoinChannel();
}


void UStreamMessageWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	RtcEngineContext.appId = TCHAR_TO_ANSI(*APP_ID);
	RtcEngineContext.eventHandler = this;
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	RtcEngineContext.audioScenario = agora::rtc::AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	RtcEngineProxy = agora::rtc::ue::createAgoraRtcEngine();

	RtcEngineProxy->initialize(RtcEngineContext);
}

void UStreamMessageWidget::SetUpUIEvent()
{
	SendBtn->OnClicked.AddDynamic(this, &UStreamMessageWidget::onSendButtonClick);
}

void UStreamMessageWidget::onSendButtonClick()
{
	FString sendMessage = SendTextBox->GetText().ToString();

	if (sendMessage =="")
	{
		UE_LOG(LogTemp, Warning, TEXT("Dont send empty message!"));
		return;
	}
	int streamId = CreateDataStreamId();
	if (streamId < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateDataStream failed!"));
		return;
	}
	else
	{
		SendStreamMessage(streamId, TCHAR_TO_UTF8(*sendMessage));

		SendTextBox->SetText(FText::GetEmpty());
	}
}


int UStreamMessageWidget::CreateDataStreamId()
{
	if (this->StreamId == -1)
	{
		DataStreamConfig config;
		config.syncWithAudio = false;
		config.ordered = true;
		int ret = RtcEngineProxy->createDataStream(&StreamId, config);
		UE_LOG(LogTemp, Warning, TEXT("CreateDataStream: ret %d, streamId %d"), ret,StreamId);
	}
	return StreamId;
}

void UStreamMessageWidget::SendStreamMessage(int streamId, const char* message)
{
	int ret = RtcEngineProxy->sendStreamMessage(streamId, message, strlen(message)+1);
	UE_LOG(LogTemp, Warning, TEXT("sendStreamMessage: message %s,length %d"), UTF8_TO_TCHAR(message), strlen(message));
	UE_LOG(LogTemp, Warning, TEXT("SendStreamMessage: ret %d"), ret);
}

void UStreamMessageWidget::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
	FString pathfromName = UGameplayStatics::GetPlatformName();
	if (pathfromName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}

void UStreamMessageWidget::OnJoinChannel() {
	UE_LOG(LogTemp, Warning, TEXT("UStreamMessageWidget OnJoinButtonClick ======"));

	RtcEngineProxy->enableAudio();
	RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(*Token), TCHAR_TO_ANSI(*ChannelName), "", 0);
	RtcEngineProxy->setClientRole(agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
}


#pragma region RtcEngineCallBack
void UStreamMessageWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UStreamMessageWidget::JoinChannelSuccess uid: %u"), (int64)uid));
	});
}


void UStreamMessageWidget::onStreamMessage(uid_t userId, int streamId, const char* data, size_t length, uint64_t sentTs)
{
	char* tempdata = new char[length];
	FMemory::Memcpy(tempdata, data, length*sizeof(char));
	FString temp = FString(UTF8_TO_TCHAR(tempdata));
	//std::string temp(tempdata);
	delete[] tempdata;
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UStreamMessageWidget::onStreamMessage uid: %u,streamId %d,data %s,length %d,sentTs %d"), (int64)userId, streamId, *temp,length,sentTs));
	});

}

void UStreamMessageWidget::onStreamMessageError(uid_t userId, int streamId, int code, int missed, int cached)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UStreamMessageWidget::onStreamMessage uid: %u,streamId %d,code %d,missed %d,cached %d"), (int64)userId, streamId, code, missed, cached));
	});
}

void UStreamMessageWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed) {
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("UStreamMessageWidget::onUserJoined uid: %u"), uid));
	});

}
#pragma endregion RtcEngineCallBack


void UStreamMessageWidget::NativeDestruct() {
	Super::NativeDestruct();

	if (RtcEngineProxy != nullptr)
	{
		RtcEngineProxy->unregisterEventHandler(this);
		RtcEngineProxy->release();
		delete RtcEngineProxy;
		RtcEngineProxy = nullptr;
	}
}
