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

#include "DeviceManagerUserWidget.generated.h"

using namespace agora::rtc;

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UDeviceManagerUserWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()


#pragma region Event Handler

public:

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:

		FUserRtcEventHandler(UDeviceManagerUserWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler


#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UDeviceManagerUserWidget> WidgetPtr;
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
	inline UDraggableLogMsgViewWidget* GetLogMsgViewPtr() { return LogMsgViewPtr; }

private:
	UDraggableLogMsgViewWidget* LogMsgViewPtr = nullptr;

#pragma endregion

public:
	inline FString GetAppId() { return AppId; };
	inline FString GetToken() { return Token; };
	inline FString GetChannelName() { return ChannelName; };

protected:
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void NativeDestruct() override;
	void UnInitAgoraEngine();

	void CallDeviceManagerApi();
	void GetAudioRecordingDevice();
	void GetAudioPlaybackDevice();
	void GetVideoDeviceManager();
	void SetCurrentDevice();
	void SetCurrentDeviceVolume();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngineEx* RtcEngineProxy;

	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;

	IAudioDeviceManager* AudioDeviceManager;

	IVideoDeviceManager* VideoDeviceManager;

	IAudioDeviceCollection* AudioRecordingDeviceInfos;

	IAudioDeviceCollection* AudioPlaybackDeviceInfos;

	IVideoDeviceCollection* VideoDeviceInfos;
};