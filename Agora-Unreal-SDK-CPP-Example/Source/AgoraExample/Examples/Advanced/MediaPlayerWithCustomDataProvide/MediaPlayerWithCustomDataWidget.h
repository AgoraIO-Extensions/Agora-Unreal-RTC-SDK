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

#include "MediaPlayerWithCustomDataWidget.generated.h"

using namespace agora::rtc;
using namespace agora;


class FUserRtcEventHandler;

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UMediaPlayerWithCustomDataWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

public:

#pragma region Event Handler

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{

	public:

		FUserRtcEventHandlerEx(UMediaPlayerWithCustomDataWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UMediaPlayerWithCustomDataWidget> WidgetPtr;
	};




	class FUserIMediaPlayerSourceObserver : public agora::rtc::IMediaPlayerSourceObserver
	{

	public:
#pragma region AgoraCallback - IMediaPlayerSourceObserver

		FUserIMediaPlayerSourceObserver(UMediaPlayerWithCustomDataWidget* Widget) : WidgetPtr(Widget) {}

		void onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_REASON reaason) override;


		void onPositionChanged(int64_t positionMs, int64_t timestampMs) override;


		void onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message) override;


		void onMetaData(const void* data, int length) override;


		void onPlayBufferUpdated(int64_t playCachedBuffer) override;


		void onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event) override;


		void onCompleted() override;


		void onAgoraCDNTokenWillExpire() override;


		void onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to) override;


		void onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info) override;

		void  onAudioVolumeIndication(int volume) override;

#pragma endregion
		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }


	private:
		TWeakObjectPtr<UMediaPlayerWithCustomDataWidget> WidgetPtr;
	};



	class FUserIMediaPlayerCustomDataProvider : public agora::media::base::IMediaPlayerCustomDataProvider
	{
	public:

		void Init(FString Path);
		void Release();

#pragma region AgoraCallback - IMediaPlayerCustomDataProvider


		int onReadData(unsigned char* buffer, int bufferSize) override;


		int64_t onSeek(int64_t offset, int whence) override;


#pragma endregion


		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }


	private:
		TWeakObjectPtr<UMediaPlayerWithCustomDataWidget> WidgetPtr;

		FILE* DataFile;
		int64_t FileSize;
	};



#pragma endregion


public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Open = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Play = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Stop = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Pause = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Resume = nullptr;


	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnOpenClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnPlayClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnStopClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnPauseClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnResumeClicked();
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

	inline agora::agora_refptr<agora::rtc::IMediaPlayer> GetMediaPlayer() { return MediaPlayer; };

protected:
	void CheckPermission();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void InitAgoraMediaPlayer();
	void JoinChannelWithMPK();

	void UnInitAgoraEngine();
	void NativeDestruct() override;

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngineEx* RtcEngineProxy;
	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer;



	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;
	TSharedPtr<FUserIMediaPlayerSourceObserver> UserIMediaPlayerSourceObserver;

	TSharedPtr< FUserIMediaPlayerCustomDataProvider> UserIMediaPlayerCustomDataProvider;
};
