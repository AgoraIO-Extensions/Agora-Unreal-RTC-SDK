// Copyright(c) 2024 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

// UI
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

// UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "SpatialAudioWidget.generated.h"

using namespace agora::rtc;

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API USpatialAudioWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()


#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(USpatialAudioWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<USpatialAudioWidget> WidgetPtr;
	};

#pragma endregion


#pragma region UI

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_JoinChannel = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_LeaveChannel = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* Slider_Distance = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Txt_Distance = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnJoinChannelClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnLeaveChannelClicked();
	UFUNCTION(BlueprintCallable)
	void OnSliderDistanceValChanged(float val);

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

	inline ILocalSpatialAudioEngine* GetLocalSpatialAudioEngine() { return LocalSpatialAudioEngine; }

	inline void SetRemoteUID(uint32 uid) { RemoteUID = uid; }
	int UpdateRemotePositionWithCurrentDistanceVal();
protected:

	void CheckPermission();
	void InitUI();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void InitSpatialAudioEngine(IRtcEngine* engine);


	void NativeDestruct() override;
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";


	ILocalSpatialAudioEngine* LocalSpatialAudioEngine = nullptr;



	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;

	uint32 RemoteUID = 0;
};