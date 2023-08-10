	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

// UI 
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

// UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h" 

#include "ScreenShareWidget.generated.h"
using namespace agora::rtc;
using namespace agora;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UScreenShareWidget : public UBaseAgoraUserWidget
{	GENERATED_BODY()

#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{

	public:

		FUserRtcEventHandlerEx(UScreenShareWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UScreenShareWidget> WidgetPtr;
	};


#pragma endregion



public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UComboBoxString* CBS_DisplayID = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StartScreenShare = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_StopScreenShare = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnStartScreenShareClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnStopScreenShareClicked();


	UFUNCTION(BlueprintCallable)
	void OnCBSDisplayIDSelectedValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

#pragma endregion


	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;


#pragma region UI Utility - Video View

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel_VideoView = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDraggableVideoViewWidget> DraggableVideoViewTemplate;
	
protected:

	int MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType = VIDEO_SOURCE_CAMERA_PRIMARY,FString channelId = "");
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
	inline UDraggableLogMsgViewWidget* GetLogMsgViewPtr() {return LogMsgViewPtr;} 

private:
	UDraggableLogMsgViewWidget* LogMsgViewPtr = nullptr;

#pragma endregion


public:
	inline FString GetAppId() { return AppId; };
	inline FString GetToken() { return Token; };
	inline FString GetChannelName() { return ChannelName; };

	inline uint32 GetUID_Screen() { return UID_Screen; };

protected:
	void InitData();
	void CheckPermission();
	void PrepareScreenShare();
	void NativeDestruct() override;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void UnInitAgoraEngine();

	void JoinChannel_ScreenShare();

	FString AppId;
	FString Token = "";
	FString ChannelName;

	uint32 UID_Screen = 456;
	int SelectDisplayId;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	agora::rtc::IScreenCaptureSourceList* infos;
#endif


	IRtcEngineEx* RtcEngineProxy;



	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;
};

