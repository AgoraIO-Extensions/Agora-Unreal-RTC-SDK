// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"


// UI
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableText.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"

// UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h" 

#include "MusicPlayerWidget.generated.h"

using namespace agora::rtc;
using namespace agora;


class FUserRtcEventHandler;

/**
 *
 */
UCLASS()
class AGORAEXAMPLE_API UMusicPlayerWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

public:

#pragma region Event Handler


	class FUserRtcEventHandlerEx : public agora::rtc::IRtcEngineEventHandlerEx
	{

	public:

		FUserRtcEventHandlerEx(UMusicPlayerWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandlerEx

		void onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed) override;

		void onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats) override;

		void onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed) override;

		void onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UMusicPlayerWidget> WidgetPtr;
	};

	class FUserIMediaPlayerSourceObserver : public agora::rtc::IMediaPlayerSourceObserver
	{

	public:
#pragma region AgoraCallback - IMediaPlayerSourceObserver

		FUserIMediaPlayerSourceObserver(UMusicPlayerWidget* Widget) : WidgetPtr(Widget) {}

		void onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_REASON reason) override;


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
		TWeakObjectPtr<UMusicPlayerWidget> WidgetPtr;
	};



	class FUserMusicContentCenterEventHandler : public agora::rtc::IMusicContentCenterEventHandler
	{

	public:

		FUserMusicContentCenterEventHandler(UMusicPlayerWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IMusicContentCenterEventHandler

		void onMusicChartsResult(const char* requestId, agora_refptr<MusicChartCollection> result, MusicContentCenterStateReason reason) override;


		void onMusicCollectionResult(const char* requestId, agora_refptr<MusicCollection> result, MusicContentCenterStateReason reason) override;


		void onLyricResult(const char* requestId, int64_t songCode, const char* lyricUrl, MusicContentCenterStateReason reason) override;

		void onSongSimpleInfoResult(const char* requestId, int64_t songCode, const char* simpleInfo, MusicContentCenterStateReason reason)  override;

		void onPreLoadEvent(const char* requestId, int64_t songCode, int percent, const char* lyricUrl, PreloadState state, MusicContentCenterStateReason reason) override;
#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UMusicPlayerWidget> WidgetPtr;
	};
#pragma endregion


public:

#pragma region UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_BackToHome = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_RTMAPPID = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_RTMTOKEN = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_RTMUID = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_JoinChannel = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_GetCaches = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_RemoveCaches = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_GetMusicCharts = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* CBS_MusicCharts = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* CBS_SelectedSong = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Txt_SelectedSong = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_GetLyric = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Open = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_IsPreload = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Preload = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* ET_SearchMusicName = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_SearchMusic = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnBtnBackToHomeClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnJoinChannelClicked();


	UFUNCTION(BlueprintCallable)
	void OnBtnGetCachesClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnRemoveCachesClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnGetMusicChartsClicked();

	UFUNCTION(BlueprintCallable)
	void OnCBSMusicChartsValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION(BlueprintCallable)
	void OnCBSSelectedSongValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION(BlueprintCallable)
	void OnBtnGetLyricClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnOpenClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnIsPreloadClicked();
	UFUNCTION(BlueprintCallable)
	void OnBtnPreloadClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnSearchMusicClicked();

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

	inline agora_refptr<IMusicPlayer> GetMusicPlayer() { return MusicPlayer; };

protected:
	//void JoinChannel();
	void NativeDestruct() override;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	void ShowUserGuide();
	void UnInitAgoraEngine();

	void UpdateUIMusicChartInfo();
	void UpdateUIMusicCollectionList();
	void UpdateDataMusicChartInfoListData(agora_refptr<MusicChartCollection> result);
	void UpdateDataMusicCollectionList(agora_refptr<MusicCollection> result);


	FString AppId = "";
	FString Token = "";
	FString ChannelName = "";

	IRtcEngine* RtcEngineProxy;
	agora::media::IMediaEngine* MusicContentCenter;



	TSharedPtr<FUserRtcEventHandlerEx> UserRtcEventHandlerEx;
	IMusicContentCenter* MusicContentCenterPtr;
	TSharedPtr<FUserMusicContentCenterEventHandler> UserMusicContentCenterEventHandler;
	agora_refptr<IMusicPlayer> MusicPlayer = nullptr;

	TSharedPtr< FUserIMediaPlayerSourceObserver> UserIMediaPlayerSourceObserver;

	int64 CurSongId = 0;
	int CurChartId = 0;

	TArray<MusicChartInfo> MusicChartInfoList;
	TArray<Music> MusicCollectionList;

	FCriticalSection CriticalSectionForMusicChartInfoList;
	FCriticalSection CriticalSectionForMusicCollectionList;
};


