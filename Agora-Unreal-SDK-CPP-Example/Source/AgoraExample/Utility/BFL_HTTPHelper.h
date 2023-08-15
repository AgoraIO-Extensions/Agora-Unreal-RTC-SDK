// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include <functional>
#include "BFL_HTTPHelper.generated.h"

/**
 * 
 */
UCLASS()
class AGORAEXAMPLE_API UBFL_HTTPHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static void FetchToken(FString RequestURL, int64 uid, FString ChannelName, int64 Role, std::function<void(FString,bool)> Callback);

	static void HandleRequest(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess, std::function<void(FString, bool)> Callback);
};
