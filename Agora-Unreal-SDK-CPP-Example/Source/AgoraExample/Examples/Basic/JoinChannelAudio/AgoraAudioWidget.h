// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

// UI
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"

//UI Utility
#include "../../../Utility/BFL_Logger.h"

#include "AgoraAudioWidget.generated.h"

using namespace agora::rtc;
using namespace agora;
/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UAgoraAudioWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()


#pragma region Event Handler

public:

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler 
	{
	public:

		FUserRtcEventHandler(UAgoraAudioWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler

		void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

		void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

		void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

		void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UAgoraAudioWidget> WidgetPtr;
	};

#pragma endregion



public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StartEchoTest = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StopEchoTest = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_JoinChannel = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_LeaveChannel = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StartPublish = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StopPublish = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		USlider* Slider_PlaybackSignalVolume = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		USlider* Slider_RecordingSignalVolume = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Txt_PlaybackSignalVolume = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Txt_RecordingSignalVolume = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_EnableAudioIndication = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UComboBoxString* CBS_AudioProfile = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UComboBoxString* CBS_AudioSenario = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnStartEchoTestClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnStopEchoTestClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnJoinChannelClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnLeaveChannelClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnStartPublishClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnStopPublishClicked();

	UFUNCTION(BlueprintCallable)
	void OnSliderPlaybackSignalVolumeValChanged(float val);
	UFUNCTION(BlueprintCallable)
	void OnSliderRecordingSignalVolumeValChanged(float val);

	UFUNCTION(BlueprintCallable)
	void OnBtnEnableAudioIndicationClicked();

	UFUNCTION(BlueprintCallable)
	void OnCBSAudioProfileSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION(BlueprintCallable)
	void OnCBSAudioSenarioSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
#pragma endregion


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

	void InitUI();
	void CheckPermission();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void UnInitAgoraEngine();

	void NativeDestruct() override;

	FString AppId;
	FString Token;
	FString ChannelName;

	IRtcEngine* RtcEngineProxy;


	
	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;
};
