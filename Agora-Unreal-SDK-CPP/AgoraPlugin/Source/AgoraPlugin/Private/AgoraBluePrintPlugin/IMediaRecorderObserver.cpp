// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/IMediaRecorderObserver.h"


void UIMediaRecorderObserver::onRecorderStateChanged(agora::media::RecorderState state, agora::media::RecorderErrorCode error)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnRecorderStateChanged.Broadcast((ERecorderState)state, (ERecorderErrorCode)error);
	});
}
void UIMediaRecorderObserver::onRecorderInfoUpdated(const agora::media::RecorderInfo& info)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FRecorderInfo recorderInfo;
		recorderInfo.fileName = FString(info.fileName);
		recorderInfo.durationMs = info.durationMs;
		recorderInfo.fileSize = info.fileSize;
		OnRecorderInfoUpdated.Broadcast(recorderInfo);
	});
}
