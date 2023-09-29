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

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "VoiceChangerWidget.generated.h"


using namespace agora::rtc;
using namespace agora;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UVoiceChangerWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(UVoiceChangerWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UVoiceChangerWidget> WidgetPtr;
	};

#pragma endregion


public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_ChatBeautifier = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_SingingBeautifier = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_TimbreTransformation = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_TurnOffVoiceBeautifier = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StyleTransformation = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_RoomAcoustuics = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_Pitch = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_TurnOffAudioEffect = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_VoiceChanger = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_TurnOffVoiceChanger = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_CustomVocalEffects = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();


#pragma region UI VoiceBeautifier

	UFUNCTION(BlueprintCallable)
	void OnBtn_ChatBeautifierClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_SingingBeautifierClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_TimbreTransformationClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_TurnOffVoiceBeautifierClicked();

#pragma endregion

#pragma region UI AudioEffect

	UFUNCTION(BlueprintCallable)
	void OnBtn_StyleTransformationClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_RoomAcoustuicsClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_PitchClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_TurnOffAudioEffectClicked();

#pragma endregion

#pragma region UI VoiceConversion

	UFUNCTION(BlueprintCallable)
	void OnBtn_VoiceChangerClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtn_TurnOffVoiceChangerClicked();

#pragma endregion

#pragma region UI CustomVocalEffects

	UFUNCTION(BlueprintCallable)
	void OnBtn_CustomVocalEffectsClicked();

#pragma endregion




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
	void CheckPermission();
	void JoinChannel();
	void NativeDestruct() override;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngine* RtcEngineProxy;


	
	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;

};

