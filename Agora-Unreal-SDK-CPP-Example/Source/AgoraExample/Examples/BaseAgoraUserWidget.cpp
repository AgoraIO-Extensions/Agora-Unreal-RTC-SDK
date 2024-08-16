// Copyright(c) 2024 Agora.io. All rights reserved.


#include "BaseAgoraUserWidget.h"

void UBaseAgoraUserWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{

}

void UBaseAgoraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		PlayerController->bShowMouseCursor = true;
	}
}
