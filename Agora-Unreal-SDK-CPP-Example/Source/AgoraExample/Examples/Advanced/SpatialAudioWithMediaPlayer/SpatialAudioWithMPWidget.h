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

#include "SpatialAudioWithMPWidget.generated.h"


using namespace agora::rtc;
using namespace agora;


/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API USpatialAudioWithMPWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

#pragma region Event Handler

public:

	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{
	public:

		FUserRtcEventHandlerEx(USpatialAudioWithMPWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<USpatialAudioWithMPWidget> WidgetPtr;
	};




	class FUserIMediaPlayerSourceObserver : public agora::rtc::IMediaPlayerSourceObserver
	{

	public:

#pragma region AgoraCallback - IMediaPlayerSourceObserver

		FUserIMediaPlayerSourceObserver(USpatialAudioWithMPWidget* Widget) : WidgetPtr(Widget) {}

		void onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_ERROR ec) override;


		void onPositionChanged(int64_t position_ms) override;


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
		TWeakObjectPtr<USpatialAudioWithMPWidget> WidgetPtr;
	};

#pragma endregion

public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Left = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Play = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Right = nullptr;


	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnLeftClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnPlayClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnRightClicked();
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
	inline IRtcEngineEx* GetRtcEngine() { return RtcEngineProxy; }
	inline agora::agora_refptr<agora::rtc::IMediaPlayer> GetMediaPlayer() { return MediaPlayer; }
	inline FString GetChannelName() { return ChannelName; }
	inline ILocalSpatialAudioEngine* GetLocalSpatialAudioEngine() { return LocalSpatialAudioEngine; }
	inline uint32 GetUID_Camrea() { return UID; }
	inline uint32 GetUID_UsedInMPK() { return UID_UsedInMPK; }
protected:
	void CheckPermission();
	void JoinChannel();
	void JoinChannelWithMPK();
	void NativeDestruct() override;

	void InitAgoraMediaPlayer();
	void InitAgoraSpatialAudioEngine();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void InitData();
	void ShowUserGuide();
	void UnInitAgoraEngine();

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	uint32 UID = 123;
	uint32 UID_UsedInMPK = 67890;
	IRtcEngineEx* RtcEngineProxy;
	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer;
	ILocalSpatialAudioEngine* LocalSpatialAudioEngine;

#if AGORA_UESDK_AUDIO_ONLY
	// In 4.2.1 AudioOnly SDK, the mp4 format is not supported.

	// You could use the following URL, but playback may experience stuttering or lagging due to the current audio - only SDK's use of the system's SimplePlayer.
	// FString MPL_URL = "https://agora-adc-artifacts.oss-cn-beijing.aliyuncs.com/video/meta_live_mpk.mov";

	FString MPL_URL = "https://download.agora.io/demo/test/Agora.io-Interactions.wav";

#else
	FString MPL_URL =
		"https://agoracdn.s3.us-west-1.amazonaws.com/videos/Agora.io-Interactions.mp4";
#endif

	TSharedPtr<FUserIMediaPlayerSourceObserver> MediaPlayerSourceObserverWarpper;
	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;

};