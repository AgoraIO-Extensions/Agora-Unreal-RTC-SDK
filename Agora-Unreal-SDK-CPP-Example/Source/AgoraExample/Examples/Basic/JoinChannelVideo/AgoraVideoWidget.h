// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

// UI
#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

//UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h"

#include "AgoraVideoWidget.generated.h"

using namespace agora::rtc;
using namespace agora;

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UAgoraVideoWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

public:

#pragma region Event Handler

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:

		FUserRtcEventHandler(UAgoraVideoWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler

		void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

		void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

		void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

		void onVideoSizeChanged(VIDEO_SOURCE_TYPE sourceType, uid_t uid, int width, int height, int rotation) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UAgoraVideoWidget> WidgetPtr;

	};
#pragma endregion

public:
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_JoinChannel = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_LeaveChannel = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_StartPublish = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_StopPublish = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_FPS = nullptr;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_Width = nullptr;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_Height = nullptr;


		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_BitRate = nullptr;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_MinBitRate = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_VideoConfigConfirm = nullptr;



	UFUNCTION(BlueprintCallable)
	void OnBtnJoinChannelClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnLeaveChannelClicked();


	UFUNCTION(BlueprintCallable)
	void OnBtnStartPublishClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnBtnStopPublishClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnVideoConfigConfirmClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

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


public:
	inline FString GetAppId() { return AppId; };
	inline FString GetToken() { return Token; };
	inline FString GetChannelName() { return ChannelName; };

	
protected:

	IRtcEngine* RtcEngineProxy;

	FString AppId;
	FString Token;
	FString ChannelName;

	void CheckPermission();

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void UnInitAgoraEngine();
	void NativeDestruct() override;


	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;

};
