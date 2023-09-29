// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"
#include "AgoraPlugin/Private/AgoraCppPlugin/include/VideoObserverInternal.h"

// UI
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

// UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h"
#include "../../../Utility/BFL_UtilityTool.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "Misc/FileHelper.h"
#include "TimerManager.h"

#include "PushEncodedVideoImageWidget.generated.h"


using namespace agora::rtc;
using namespace agora;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UPushEncodedVideoImageWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()
	

#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(UPushEncodedVideoImageWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UPushEncodedVideoImageWidget> WidgetPtr;
	};


	class FUserIVideoEncodedFrameObserver : public agora::media::IVideoEncodedFrameObserver
	{
	public:

		FUserIVideoEncodedFrameObserver(UPushEncodedVideoImageWidget* WidgetPtr);

		~FUserIVideoEncodedFrameObserver();

#pragma region  AgoraCallback - IVideoEncodedFrameObserver
		
		virtual bool onEncodedVideoFrameReceived(rtc::uid_t uid, const uint8_t* imageBuffer, size_t length,
			const rtc::EncodedVideoFrameInfo& videoEncodedFrameInfo) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	public:
		TWeakObjectPtr<UPushEncodedVideoImageWidget> WidgetPtr;
	};

#pragma endregion


public:
	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Btn_BackToHome = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

#pragma endregion



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
	inline IRtcEngineEx* GetRtcEngine() { return RtcEngineProxy; };
	inline FString GetChannelName() { return ChannelName; };

	inline uint32 GetUID1() { return UID1; };
	inline uint32 GetUID2() { return UID2; };


protected:
	void CheckPermission();
	void JoinChannel();
	void JoinChannel2();
	void NativeDestruct() override;


	void StartPushEncodeVideoImage();
	void StopPushEncodeVideoImage();
	void UpdateForPushEncodeVideoImage();

	void InitData();

	FTimerHandle TimerHandler;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void UnInitAgoraEngine();

	FString AppId;
	FString Token;
	FString ChannelName;

	IRtcEngineEx* RtcEngineProxy;

	agora::media::IMediaEngine* MediaEngine;
	TSharedPtr<FUserIVideoEncodedFrameObserver> VideoObserver;



	uint32 UID1 = 123;
	uint32 UID2 = 456;

	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;

};
