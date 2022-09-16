// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAgoraUserWidget.h"

void UMainAgoraUserWidget::JoinChannelVideoClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Basic/JoinChannelVideo/BP_VideoWidget.BP_VideoWidget_C'"));
}


void UMainAgoraUserWidget::JoinChannelAudioClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Basic/JoinChannelAudio/BP_AudioWidget.BP_AudioWidget_C'"));
}

void UMainAgoraUserWidget::DvicesManagerClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Advance/DeviceManager/BP_DeviceManager.BP_DeviceManager_C'"));
}

void UMainAgoraUserWidget::JoinMultipleChannelClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Advance/JoinMultipleChannel/BP_JoinMultipleChannel.BP_JoinMultipleChannel_C'"));
}

void UMainAgoraUserWidget::MediaPlayerClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Advance/MediaPlayer/BP_Mediaplayer.BP_Mediaplayer_C'"));
}

void UMainAgoraUserWidget::ScreenShareClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Advance/ScreenShare/BP_ScreenShare.BP_ScreenShare_C'"));
}

void UMainAgoraUserWidget::SendMultiCameraStreamClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Advance/SendMultiCameraStream/BP_SendMultiCameraStream.BP_SendMultiCameraStream_C'"));
}

void UMainAgoraUserWidget::SpatialAudioClick()
{
	LoadWidget(FString("WidgetBlueprint'/Game/API-Example/Advance/SpatialAudio/BP_SpatialAudio.BP_SpatialAudio_C'"));
}


void UMainAgoraUserWidget::LoadWidget(FString WidgetName)
{
	UClass* AgoraWidgetClass = LoadClass<UBaseAgoraUserWidget>(NULL, *WidgetName);

	UBaseAgoraUserWidget* AgoraWidget = CreateWidget<UBaseAgoraUserWidget>(GetWorld(), AgoraWidgetClass);

	AgoraWidget->AddToViewport();

	AgoraWidget->InitAgoraWidget(AppidBox->GetText().ToString(), TokenBox->GetText().ToString(), ChannelBox->GetText().ToString());

	this->RemoveFromViewport();
}

void UMainAgoraUserWidget::InitAgoraWidget(FString Id, FString Token, FString Channelname)
{
	this->APP_ID = Id;

	this->TOKEN = Token;

	this->CHANNEL_NAME = Channelname;

	AppidBox->SetText(FText::FromString(APP_ID));

	TokenBox->SetText(FText::FromString(Token));

	ChannelBox->SetText(FText::FromString(Channelname));
}

void UMainAgoraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	JoinChannelVideo->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::JoinChannelVideoClick);

	JoinChannelAudio->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::JoinChannelAudioClick);

	DeviceManager->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::DvicesManagerClick);

	JoinMultipleChannel->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::JoinMultipleChannelClick);

	MediaPlayer->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::MediaPlayerClick);

	ScreenShare->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::ScreenShareClick);

	SendMultiCameraStream->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::SendMultiCameraStreamClick);

	SpatialAudio->OnClicked.AddDynamic(this, &UMainAgoraUserWidget::SpatialAudioClick);
}

