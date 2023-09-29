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
#include "../../../Utility/BFL_UtilityTool.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "DualCameraWidget.generated.h"

using namespace agora::rtc;
/**
 * 
 */

UCLASS()
class AGORAEXAMPLE_API UDualCameraWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(UDualCameraWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UDualCameraWidget> WidgetPtr;
	};

#pragma endregion

public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_MainCameraJoin = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_MainCameraLeave = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_SecondCameraJoin = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_SecondCameraLeave = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_PublishMainCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_UnPublishMainCam = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_PublishSecondCam = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_UnPublishSecondCam = nullptr;

	UFUNCTION(BlueprintCallable)
		void OnBtnBackToHomeClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_MainCameraJoinClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_MainCameraLeaveClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_SecondCameraJoinClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_SecondCameraLeaveClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_PublishMainCameraClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_UnPublishMainCamClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_PublishSecondCamClicked();
	UFUNCTION(BlueprintCallable)
		void OnBtn_UnPublishSecondCamClicked();

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
	inline uint32 GetUID1() { return UID1; };
	inline uint32 GetUID2() { return UID2; };

protected:
	void InitData();
	void CheckPermission();
	void GetVideoDeviceManager();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void UnInitAgoraEngine();
	void NativeDestruct() override;


	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	uint32 UID1 = 123;
	uint32 UID2 = 456;

	IRtcEngineEx* RtcEngineProxy;
	
	CameraCapturerConfiguration MainCameraConfig;
	CameraCapturerConfiguration SecondCameraConfig;

	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;

};