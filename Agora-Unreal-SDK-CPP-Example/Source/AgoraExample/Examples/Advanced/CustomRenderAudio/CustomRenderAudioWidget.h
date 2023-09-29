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

#include "AudioDevice.h"
#include "HAL/Runnable.h"
#include <chrono>
#include "AgoraSoundWaveProcedural.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "CustomRenderAudioWidget.generated.h"

using namespace agora::rtc;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UCustomRenderAudioWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()


#pragma region Event Handler

public:

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:

		FUserRtcEventHandler(UCustomRenderAudioWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler

		void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

		void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

		void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

		void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UCustomRenderAudioWidget> WidgetPtr;
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

	UAgoraSoundWaveProcedural* AgoraSoundWaveProcedural;
	UAudioComponent* AgoraSound;

protected:
	void CheckPermission();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void JoinChannel();
	void InitConfig();

	void NativeDestruct() override;
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngineEx* RtcEngineProxy;
	agora::media::IMediaEngine* MediaEngine;

	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;

	int AudioDataLength;
	int SAMPLE_RATE = 44100;
	int CHANNEL = 1;
	int PULL_FREQ_PER_SEC = 100;
	FString timedata;
	TArray<uint8> RecordingBuffer;
	
	FRunnable* Runnable;

};



#pragma region AgoraThread

class FAgoraRenderRunnable : public FRunnable
{

public:

	FAgoraRenderRunnable(agora::media::IMediaEngine* MediaEngine, UAgoraSoundWaveProcedural* Soundwaveprocedural);

	virtual ~FAgoraRenderRunnable();

	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	class UAgoraSoundWaveProcedural* AgoraSoundWaveProcedural;

protected:

	TArray<int32> ProcessedNumbers;

	bool bStopThread = false;

	agora::media::IMediaEngine* MediaEngine;

	int CHANNEL = 1;

	int SAMPLE_RATE = 44100;

	int PUSH_FREQ_PER_SEC = 100;

	std::time_t getTimeStamp();

	uint8* sendByte;
};

#pragma endregion