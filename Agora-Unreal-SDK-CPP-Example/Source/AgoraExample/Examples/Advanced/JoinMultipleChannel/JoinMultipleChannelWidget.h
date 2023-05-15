// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAgoraUserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include <iostream>
#include <string.h>
#include "AgoraPluginInterface.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "JoinMultipleChannelWidget.generated.h"
using namespace agora::rtc;
using namespace agora;

struct UserImageData
{
	UImage* image;

	uid_t uid;

	UserImageData(UImage* image, uid_t uid)
	{
		this->image = image;
		this->uid = uid;
	}

	UserImageData()
	{
		this->image = nullptr;
		this->uid = 0;
	}
	bool operator==(const UserImageData& s)
	{
		if (this->image == s.image || this->uid ==s.uid)
		{
			return true;
		}
		return false;
	}
};


/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UJoinMultipleChannelWidget : public UBaseAgoraUserWidget, public IRtcEngineEventHandlerEx
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideoUser1 = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideoUser2 = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideoUser3 = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideoUser4 = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideoUser5 = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* remoteVideoUser6 = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LocalVideo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LeaveBtn = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackHomeBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConfirmBtn = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ScenarioComboBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ProfileComboBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* FPSComboBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* WidthTextBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* HeightTextBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* BitRateTextBox = nullptr;

	UFUNCTION(BlueprintCallable)
	void StartScreenShare(int width,int height,int bitRate,int frameRate);

	UFUNCTION(BlueprintCallable)
	void JoinChannelClick();

	UFUNCTION(BlueprintCallable)
	void ScreenShareClick();

	UFUNCTION(BlueprintCallable)
	void LeaveChannelClick();

	UFUNCTION(BlueprintCallable)
	void OnBackHomeButtonClick();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ComboBoxDisplayId = nullptr;

	UFUNCTION(BlueprintCallable)
	void SelectValueCallBack(FString SelectedItem, ESelectInfo::Type SelectionType);

	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;

	void onJoinChannelSuccess(const RtcConnection& connection, int elapsed) override;

	void onLeaveChannel(const RtcConnection& connection, const RtcStats& stats) override;

	void onUserJoined(const RtcConnection& connection, uid_t remoteUid, int elapsed) override;

	void onUserOffline(const RtcConnection& connection, uid_t remoteUid, USER_OFFLINE_REASON_TYPE reason) override;

protected:

	void NativeDestruct() override;

private:

	agora::rtc::IRtcEngine* RtcEngineProxy;

	std::string AppID;

	std::string Token;

	std::string ChannelName;

	TArray<UserImageData> NotUseArray;

	TArray<UserImageData> UsedArray;

	UserImageData GetUImageNoData(agora::rtc::uid_t uid);

	UserImageData RemoveUImageData(agora::rtc::uid_t uid);

	void InitUI();

	TMap<FString, CHANNEL_PROFILE_TYPE> AgoraChannelProfileEnumMap;

	TMap<FString, AUDIO_SCENARIO_TYPE> AgoraAudioScenarioEnumMap;

	unsigned int Uid1 = 123;

	unsigned int Uid2 = 456;

	int SelectDisplayId;

	FSlateBrush EmptyBrush;

#if PLATFORM_WINDOWS || PLATFORM_MAC
	agora::rtc::IScreenCaptureSourceList* infos;
#endif
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);

	void PrepareScreenCapture();


	void ScreenShareJoinChannel();

	void SetUpUIEvent();

	void CheckAndroidPermission();
};
