// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/IMediaRecorderObserver.h"


void UIMediaRecorderObserver::onRecorderStateChanged(agora::media::RecorderState state, agora::media::RecorderErrorCode error)
{
	TWeakObjectPtr<UIMediaRecorderObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
			
			OnRecorderStateChanged.Broadcast(state, (ERecorderErrorCode)error);
		});
}
void UIMediaRecorderObserver::onRecorderInfoUpdated(const agora::media::RecorderInfo& info)
{
	TWeakObjectPtr<UIMediaRecorderObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;
	
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		if (!SelfWeakPtr.IsValid())
			return;
			
			FRecorderInfo recorderInfo;
			recorderInfo.fileName = FString(info.fileName);
			recorderInfo.durationMs = info.durationMs;
			recorderInfo.fileSize = info.fileSize;
			OnRecorderInfoUpdated.Broadcast(recorderInfo);
		});
}
