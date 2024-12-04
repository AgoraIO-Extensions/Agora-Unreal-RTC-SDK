// Copyright(c) 2024 Agora.io. All rights reserved.


#include "BFL_HTTPHelper.h"

void UBFL_HTTPHelper::FetchToken(FString RequestURL, int64 uid, FString ChannelName, int64 Role, std::function<void(FString, bool)> Callback)
{

#if AG_UE427_OR_LATER
	// Create Json Data
	FString ServerData;

	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&ServerData);
	JsonWriter->WriteObjectStart();

	JsonWriter->WriteValue(TEXT("uid"), uid);
	JsonWriter->WriteValue(TEXT("ChannelName"), ChannelName);
	JsonWriter->WriteValue(TEXT("role"), Role);

	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();




	FHttpModule& HttpModule = FHttpModule::Get();

	// Create an http request
   // The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule.CreateRequest();


	Request->SetHeader("Content-Type", "application/json; charset=UTF-8");

	Request->SetVerb("POST");

	Request->SetURL(RequestURL);

	Request->SetContentAsString(ServerData);

	Request->OnProcessRequestComplete().BindLambda(
		// Here, we "capture" the 'this' pointer (the "&"), so our lambda can call this
		// class's methods in the callback.

		[Callback](
			FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully
			) mutable
		{
			HandleRequest(pRequest, pResponse, connectedSuccessfully, Callback);
		}

	);

	// Send Request
	Request->ProcessRequest();

#endif
}

void UBFL_HTTPHelper::HandleRequest(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess, std::function<void(FString, bool)> Callback)
{

#if AG_UE427_OR_LATER

	if (!EHttpResponseCodes::IsOk(ResponsePtr->GetResponseCode())) {
		Callback("", false);
		return;
	}

	// Get Json Data
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponsePtr->GetContentAsString());

	// Solve garbled problem
	FString myData = ResponsePtr->GetContentAsString();


	TSharedPtr<FJsonObject> JsonObject;

	bool bIsOk = FJsonSerializer::Deserialize(JsonReader, JsonObject);

	if (bIsOk)
	{
		FString Token = JsonObject->GetStringField(TEXT("token"));
		Callback(Token, true);
	}

	Callback("", false);

#endif
}
