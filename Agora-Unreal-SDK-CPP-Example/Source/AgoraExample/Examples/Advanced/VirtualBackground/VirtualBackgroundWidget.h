// Copyright(c) 2024 Agora.io. All rights reserved.

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
#include "../../../Utility/BFL_UtilityTool.h" 

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "VirtualBackgroundWidget.generated.h"


using namespace agora::rtc;
using namespace agora;

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UVirtualBackgroundWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(UVirtualBackgroundWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UVirtualBackgroundWidget> WidgetPtr;
	};

#pragma endregion

public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_EnableVirtualBackgroundColor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_EnableVirtualBackgroundImage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_DisableVirtualBackground = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnEnableVirtualBackgroundColorClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnEnableVirtualBackgroundImageClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnDisableVirtualBackgroundClicked();

#pragma endregion


	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;


#pragma region UI Utility - Video View

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel_VideoView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDraggableVideoViewWidget> DraggableVideoViewTemplate;

protected:

	int MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType = VIDEO_SOURCE_CAMERA_PRIMARY, FString channelId = "");
	int ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType = VIDEO_SOURCE_CAMERA_PRIMARY, FString channelId = "");

	TMap<FVideoViewIdentity, UDraggableVideoViewWidget*> VideoViewMap;

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
	void CheckPermission();
	void JoinChannel();
	void NativeDestruct() override;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";




	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;

};
