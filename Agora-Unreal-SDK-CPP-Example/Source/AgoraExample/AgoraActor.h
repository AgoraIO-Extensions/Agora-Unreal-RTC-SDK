// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Examples/BaseAgoraUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Config/AgoraConfig.h"
#include "AgoraActor.generated.h"

UCLASS()
class AGORAEXAMPLE_API AAgoraActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAgoraActor();
	UPROPERTY(EditAnywhere, Category = "Agora|Widget")
	UBaseAgoraUserWidget* VideoWidget;

	UPROPERTY(EditAnywhere, Category = "Agora|Context")
	FString APP_ID = "YOUR_APPID";

	UPROPERTY(EditAnywhere, Category = "Agora|Context")
	FString TOKEN = "";

	UPROPERTY(EditAnywhere, Category = "Agora|Context")
	FString CHANNEL_NAME = "YOUR_CHANNEL_NAME";

	UPROPERTY(EditAnywhere, Category = "Agora|LoadConfig")
	bool bLoadConfig = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
