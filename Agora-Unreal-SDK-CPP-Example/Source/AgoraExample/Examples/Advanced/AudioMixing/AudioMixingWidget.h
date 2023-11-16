// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

// UI
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableText.h"

//UI Utility
#include "../../../Utility/BFL_Logger.h"
#include "../../../Utility/BFL_UtilityTool.h" 

#include "AudioMixingWidget.generated.h"

using namespace agora::rtc;


/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UAudioMixingWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

public:

#pragma region Event Handler
	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(UAudioMixingWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UAudioMixingWidget> WidgetPtr;
	};

#pragma endregion


public:
	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

#pragma region UI

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_StartMixing = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_StopMixing = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_StartEffect = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_StopEffect = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* CB_LocalOnly = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* CB_URL = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* CB_Loop = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_URL = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnStartMixingClicked();

	UFUNCTION(BlueprintCallable)
	void OnStopMixingClicked();

	UFUNCTION(BlueprintCallable)
	void OnStartEffectClicked();

	UFUNCTION(BlueprintCallable)
	void OnStopEffectClicked();
#pragma endregion

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
	void ShowUserGuide();
	void JoinChannel();
	void NativeDestruct() override;
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void UnInitAgoraEngine();

	FString AppId;
	FString Token;
	FString ChannelName;

	IRtcEngine* RtcEngineProxy;

	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;
};
