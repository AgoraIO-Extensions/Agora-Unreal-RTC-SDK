// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"


// UI
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CheckBox.h"
#include "Components/EditableText.h"

// UI Utility
#include "../../../Utility/BFL_VideoViewManager.h" 
#include "../../../Utility/BFL_Logger.h" 
#include "../../../Utility/BFL_UtilityTool.h" 
#include "AgoraUserObjectPool.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

#include "AudioSpectrumWidget.generated.h"

using namespace agora::rtc;
using namespace agora;


class FUserRtcEventHandler;

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UAudioSpectrumWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

public:

#pragma region Event Handler

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler
	{

	public:

		FUserRtcEventHandler(UAudioSpectrumWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler


		void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

		void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

		void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;


#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UAudioSpectrumWidget> WidgetPtr;
	};




	class FUserIMediaPlayerSourceObserver : public agora::rtc::IMediaPlayerSourceObserver
	{

	public:
#pragma region AgoraCallback - IMediaPlayerSourceObserver

		FUserIMediaPlayerSourceObserver(UAudioSpectrumWidget* Widget) : WidgetPtr(Widget) {}

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
		TWeakObjectPtr<UAudioSpectrumWidget> WidgetPtr;
	};


	class FUserAudioSpectrumObserver : public agora::media::IAudioSpectrumObserver
	{

	public:
#pragma region AgoraCallback - IAudioSpectrumObserver

		FUserAudioSpectrumObserver(UAudioSpectrumWidget* Widget) : WidgetPtr(Widget) {}

		bool onLocalAudioSpectrum(const agora::media::AudioSpectrumData& data) override;

		bool onRemoteAudioSpectrum(const agora::media::UserAudioSpectrumInfo* spectrums, unsigned int spectrumNumber) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UAudioSpectrumWidget> WidgetPtr;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UEditableText* ET_URL = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UCheckBox* CB_URL = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UCheckBox* CB_Loop = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UCanvasPanel* CanvasPanel_Spectrum = nullptr;


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
	inline agora::agora_refptr<agora::rtc::IMediaPlayer> GetMediaPlayer() { return MediaPlayer; };
	inline void UpdateSpectrumData(const agora::media::AudioSpectrumData& data);
	inline void VisualizeSpectrumData();
protected:
	void InitUI();
	void CheckPermission();
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void InitAgoraMediaPlayer();
	void JoinChannelWithMPK();


	// Tick
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	void UnInitAgoraEngine();
	void NativeDestruct() override;

	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	const char* MPK_URL = "https://agora-adc-artifacts.oss-cn-beijing.aliyuncs.com/video/meta_live_mpk.mov";

	IRtcEngine* RtcEngineProxy;
	agora::agora_refptr<agora::rtc::IMediaPlayer> MediaPlayer;


	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;
	TSharedPtr<FUserIMediaPlayerSourceObserver> UserIMediaPlayerSourceObserver;
	TSharedPtr<FUserAudioSpectrumObserver> UserAudioSpectrumObserver;

	TArray<float> AudioSpectrumData;

	FCriticalSection CriticalSectionForAudioSpectrumDataRW;
};


