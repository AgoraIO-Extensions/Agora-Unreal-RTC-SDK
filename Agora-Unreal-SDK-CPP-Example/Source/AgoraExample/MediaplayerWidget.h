// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"
#include "FileMediaSource.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/CanvasPanelSlot.h"
#include <iostream>
#include <string.h>
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "MediaplayerWidget.generated.h"
using namespace agora::rtc;
using namespace agora;
/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UMediaplayerWidget : public UBaseAgoraUserWidget, public agora::rtc::IRtcEngineEventHandler 
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PlayButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* StopButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* PauseButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* ResumeButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* OpenButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* CheckBoxUrl;

	UFUNCTION(BlueprintCallable)
	void OnPlayButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnStopButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnPauseButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnResumeButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnOpenButtonClick();

	UFUNCTION(BlueprintCallable)
	void CheckBoxValueChange(bool isOn);

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	IRtcEngine* RtcEngineProxy;

	agora_refptr<IMediaPlayer> MediaPlayer;

	FSlateBrush EmptyBrush;


	void onVideoSizeChanged(uid_t uid, int width, int height, int rotation) override;

private:

	const char* MPK_URL ="https://agora-adc-artifacts.oss-cn-beijing.aliyuncs.com/video/meta_live_mpk.mov";

	class MpkEventHandler* handler;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	bool bURLOpen;

	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void SetUpUIEvent();

	void InitMediaPlayer();

	void JoinChannelWithMPK();

	void CheckAndroidPermission();
protected:

	void NativeDestruct() override;

};

class MpkEventHandler : public agora::rtc::IMediaPlayerSourceObserver
{

public:

	MpkEventHandler(UMediaplayerWidget* MediaPlayer);

	void onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_ERROR ec) override;

	void onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message) override;

	void onPositionChanged(int64_t position_ms) override;

	void onMetaData(const void* data, int length) override;

	void onPlayBufferUpdated(int64_t playCachedBuffer) override;

	void onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event) override;

	void onCompleted() override;

	void onAgoraCDNTokenWillExpire() override;

	void onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to) override;

	void onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info) override;

	void onAudioVolumeIndication(int volume) override;


private:
	UMediaplayerWidget* MediaplayerWidget;
};
