// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAgoraUserWidget.h"
#include "AgoraPluginInterface.h"
#include "GameFramework/GameUserSettings.h"

#pragma region CustomTileView


UCustomTileView::UCustomTileView(const FObjectInitializer& Initializer) :Super(Initializer)
{
	BarThickness = FVector2D(50, 50);
}

TSharedRef<STableViewBase> UCustomTileView::RebuildListWidget()
{
	auto TileViewRef = ConstructTileView<STileView>();
	auto CustomTileViewRef = StaticCastSharedRef<SCustomListView<UObject*>>(TileViewRef);

	CustomTileViewRef->UpdateScrollBarThickness(BarThickness);
	return CustomTileViewRef;
}


#pragma endregion



void UMainAgoraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


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

	if(Txt_SDKVer){
		Txt_SDKVer->SetText(FText::FromString(AgoraUERtcEngine::GetSDKVersion()));
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
	// Audio Only Example List

#if AGORA_UESDK_AUDIO_ONLY

	LevelArray.Add(FString("BasicAudioCallScene"));
	LevelArray.Add(FString("AudioMixing"));
	LevelArray.Add(FString("AudioSpectrum"));
	LevelArray.Add(FString("ChannelMediaReplay"));
	LevelArray.Add(FString("CustomCaptureAudio"));
	LevelArray.Add(FString("CustomRenderAudio"));

#if PLATFORM_MAC||PLATFORM_WINDOWS
	LevelArray.Add(FString("DeviceManager"));
#endif

	LevelArray.Add(FString("JoinChannelWithToken"));
	LevelArray.Add(FString("JoinChannelWithUserAccount"));
	LevelArray.Add(FString("JoinMultipleChannels"));

	LevelArray.Add(FString("MediaPlayer"));
	LevelArray.Add(FString("ProcessAudioRawData"));
	LevelArray.Add(FString("SetEncryptionScene"));

	LevelArray.Add(FString("SpatialAudio"));
	LevelArray.Add(FString("SpatialAudioWithMediaPlayer"));
	LevelArray.Add(FString("StartRhythmPlayer"));
	LevelArray.Add(FString("StreamMessageScene"));
	LevelArray.Add(FString("VoiceChanger"));

	LevelArray.Add(FString("MusicPlayer"));

#else

	//  Full Example List

	LevelArray.Add(FString("BasicAudioCallScene"));
	LevelArray.Add(FString("BasicVideoCallScene"));
	LevelArray.Add(FString("ScreenShare"));
	LevelArray.Add(FString("ScreenShareWhileVideoCall"));

	LevelArray.Add(FString("DualCamera"));
	LevelArray.Add(FString("StartLocalVideoTranscoder"));

#if PLATFORM_MAC||PLATFORM_WINDOWS
	LevelArray.Add(FString("DeviceManager"));
#endif

	LevelArray.Add(FString("MediaPlayer"));
	LevelArray.Add(FString("SpatialAudio"));
	LevelArray.Add(FString("SetEncryptionScene"));
	LevelArray.Add(FString("StreamMessageScene"));
	LevelArray.Add(FString("StartRtmpStreamWithTranscoding"));
	LevelArray.Add(FString("CustomCaptureAudio"));
	LevelArray.Add(FString("CustomCaptureVideo"));
	LevelArray.Add(FString("CustomRenderAudio"));
	LevelArray.Add(FString("ProcessAudioRawData"));
	LevelArray.Add(FString("ProcessVideoRawData"));
	LevelArray.Add(FString("AudioMixing"));
	LevelArray.Add(FString("JoinChannelWithToken"));
	LevelArray.Add(FString("JoinChannelWithUserAccount"));
	LevelArray.Add(FString("JoinMultipleChannels"));
	LevelArray.Add(FString("PushEncodedVideoImage"));
	LevelArray.Add(FString("SpatialAudioWithMediaPlayer"));
	LevelArray.Add(FString("StartDirectCdnStreaming"));
	LevelArray.Add(FString("Metadata"));
	LevelArray.Add(FString("TakeSnapshot"));
	LevelArray.Add(FString("VirtualBackground"));
	LevelArray.Add(FString("VoiceChanger"));
	LevelArray.Add(FString("MusicPlayer"));
	//LevelArray.Add(FString("RenderWithYUV"));
	LevelArray.Add(FString("MediaPlayerWithCustomDataProvide"));
	LevelArray.Add(FString("WriteBackVideoRawData"));

	LevelArray.Add(FString("AudioSpectrum"));
	LevelArray.Add(FString("ChannelMediaReplay"));
	LevelArray.Add(FString("ContentInspect"));
	LevelArray.Add(FString("MediaRecorder"));
	LevelArray.Add(FString("SetBeautyEffectOptions"));
	LevelArray.Add(FString("StartRhythmPlayer"));

#endif 

}
