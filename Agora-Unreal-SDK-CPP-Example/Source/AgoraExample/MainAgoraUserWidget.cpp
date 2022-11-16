// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAgoraUserWidget.h"
#include "GameFramework/GameUserSettings.h"

void UMainAgoraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
#if PLATFORM_MAC
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1920, 1080));
	GEngine->GetGameUserSettings()->ApplySettings(true);
#endif

	if (UAgoraConfig* LoadedGame = Cast<UAgoraConfig>(UGameplayStatics::LoadGameFromSlot(FString("AgoraSave"), 0)))
	{
		this->APP_ID = LoadedGame->AppId;

		this->TOKEN = LoadedGame->Token;

		this->CHANNEL_NAME = LoadedGame->Channelname;

		AppidBox->SetText(FText::FromString(LoadedGame->AppId));

		TokenBox->SetText(FText::FromString(LoadedGame->Token));

		ChannelBox->SetText(FText::FromString(LoadedGame->Channelname));
	}

	InitLevelArray();

	for (int i = 0; i < LevelArray.Num(); i++)
	{
		ULevelSwitchItem* temp = NewObject<ULevelSwitchItem>();

		temp->LevelName = LevelArray[i];

		LevelTileView->AddItem(temp);
	}

}

void UMainAgoraUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UAgoraConfig* SaveGameInstance = Cast<UAgoraConfig>(UGameplayStatics::CreateSaveGameObject(UAgoraConfig::StaticClass()));
	SaveGameInstance->AppId = FString(AppidBox->GetText().ToString());
	SaveGameInstance->Token = FString(TokenBox->GetText().ToString());
	SaveGameInstance->Channelname = FString(ChannelBox->GetText().ToString());

	if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, FString("AgoraSave"), 0))
	{
		UE_LOG(LogTemp,Warning,TEXT("Save Config Succeed"));
	}
	
}

void UMainAgoraUserWidget::InitLevelArray()
{
	LevelArray.Add(FString("BasicAudioCallScene"));
	LevelArray.Add(FString("BasicVideoCallScene"));
#if PLATFORM_MAC&&!PLATFORM_WINDOWS
	LevelArray.Add(FString("DeviceManager"));
	LevelArray.Add(FString("SendMultiCameraStream"));
#endif
	LevelArray.Add(FString("JoinMultipleChannel"));
	LevelArray.Add(FString("MediaPlayer"));
	LevelArray.Add(FString("ScreenShare"));
	LevelArray.Add(FString("SpatialAudio"));
	LevelArray.Add(FString("SetEncryptionScene"));
	LevelArray.Add(FString("StreamMessageScene"));
	LevelArray.Add(FString("StartRtmpStreamWithTranscoding"));
	LevelArray.Add(FString("CustomCaptureAudio"));
	LevelArray.Add(FString("CustomCaptureVideo"));
	LevelArray.Add(FString("CustomRenderAudio"));
	LevelArray.Add(FString("ProcessAudioRawData"));
	LevelArray.Add(FString("ProcessVideoRawData"));
}

