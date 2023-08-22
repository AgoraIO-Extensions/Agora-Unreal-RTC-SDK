// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

// UI
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

// UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h"

#include <ctime>
#include "Misc/FileHelper.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "CustomCaptureAudioWidget.generated.h"

using namespace agora::rtc;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UCustomCaptureAudioWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()



#pragma region Event Handler

public:

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:

		FUserRtcEventHandler(UCustomCaptureAudioWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler

		void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

		void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

		void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UCustomCaptureAudioWidget> WidgetPtr;
	};

#pragma endregion


#pragma region UI

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

#pragma endregion

public:

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;



#pragma region UI Utility - Log Msg View

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel_LogMsgView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UDraggableLogMsgViewWidget> DraggableLogMsgViewTemplate;

public:
	inline UDraggableLogMsgViewWidget* GetLogMsgViewPtr() {return LogMsgViewPtr;} 

private:
	UDraggableLogMsgViewWidget* LogMsgViewPtr = nullptr;

#pragma endregion

public:
	inline FString GetAppId() { return AppId; };
	inline FString GetToken() { return Token; };
	inline FString GetChannelName() { return ChannelName; };

protected:
	void CheckPermission();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void SetExternalAudioSource();
	void JoinChannel();
	void StartPushAudio();

	void NativeDestruct() override;
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngineEx* RtcEngineProxy;
	agora::media::IMediaEngine* MediaEngine;

	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;


	TArray<uint8> RecordingBuffer;
	int AudioDataLength;
	int SAMPLE_RATE = 48000;
	int CHANNEL = 2;

	FRunnable* Runnable;
};



#pragma region AgoraThread

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAgoraOnCompleteSignature);

class FAgoraCaptureRunnable : public FRunnable
{
public:

	FAgoraCaptureRunnable(agora::media::IMediaEngine* MediaEngine, const uint8* audioData, int dataLength);
	virtual ~FAgoraCaptureRunnable();

	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	FAgoraOnCompleteSignature OnCompleteDelegate;

protected:

	TArray<int32> ProcessedNumbers;
	bool bStopThread = false;
	std::time_t getTimeStamp();
	void* sendByte;

	
	agora::media::IMediaEngine* MediaEngine;

	uint8* audioData;

	int dataLength;


	int CHANNEL = 2;

	int SAMPLE_RATE = 48000;

	int PUSH_FREQ_PER_SEC = 100;


};

#pragma endregion
