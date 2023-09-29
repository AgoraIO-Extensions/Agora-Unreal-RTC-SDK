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

// UAgoraSoundWaveProcedural
#include "Misc/ScopeLock.h" 
#include "Sound/SoundWaveProcedural.h"
#include "AgoraSoundWaveProcedural.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "ProcessAudioRawDataWidget.generated.h"

using namespace agora::rtc;

class UAudioComponent;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UProcessAudioRawDataWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()


#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(UProcessAudioRawDataWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UProcessAudioRawDataWidget> WidgetPtr;
	};


	class FUserAudioFrameObserver : public agora::media::IAudioFrameObserver
	{

	public:

		FUserAudioFrameObserver(UProcessAudioRawDataWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {
		};

#pragma region AgoraCallback - IAudioFrameObserver

		bool onPlaybackAudioFrameBeforeMixing(const char* channelId, agora::rtc::uid_t uid, AudioFrame& audioFrame) override;


		bool onRecordAudioFrame(const char* channelId, AudioFrame& audioFrame) override;


		bool onPlaybackAudioFrame(const char* channelId, AudioFrame& audioFrame) override;


		bool onMixedAudioFrame(const char* channelId, AudioFrame& audioFrame) override;


		bool onEarMonitoringAudioFrame(AudioFrame& audioFrame) override;


		int getObservedAudioFramePosition() override;


		AudioParams getPlaybackAudioParams() override;


		AudioParams getRecordAudioParams() override;


		AudioParams getMixedAudioParams() override;


		AudioParams getEarMonitoringAudioParams() override;
		
#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:
		TWeakObjectPtr<UProcessAudioRawDataWidget> WidgetPtr;
	};

#pragma endregion


#pragma region UI

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_JoinChannel = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_LeaveChannel = nullptr;
	
	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnJoinChannelClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnLeaveChannelClicked();

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

	inline agora::media::IAudioFrameObserverBase::AudioParams GetAudioParams() { return audioParams; };
	inline 	UAgoraSoundWaveProcedural* GetAgoraSoundWaveProcedural() { return AgoraSoundWaveProcedural; };

protected:
	void CheckPermission();
	void InitConfig();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();

	void NativeDestruct() override;
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngineEx* RtcEngineProxy;
	agora::media::IMediaEngine* MediaEngine;



	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;
	TSharedPtr<FUserAudioFrameObserver> UserAudioFrameObserver;
	agora::media::IAudioFrameObserverBase::AudioParams audioParams;
	UAgoraSoundWaveProcedural* AgoraSoundWaveProcedural = nullptr;
	UAudioComponent* AgoraSound = nullptr;

};




