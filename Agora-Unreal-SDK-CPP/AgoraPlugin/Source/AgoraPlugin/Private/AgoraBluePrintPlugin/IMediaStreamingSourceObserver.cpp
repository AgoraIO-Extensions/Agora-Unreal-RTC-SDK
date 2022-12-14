// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/IMediaStreamingSourceObserver.h"


void UIMediaStreamingSourceObserver::onStateChanged(agora::rtc::STREAMING_SRC_STATE state, agora::rtc::STREAMING_SRC_ERR err_code)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnStateChanged.Broadcast((ESTREAMING_SRC_STATE)state, (ESTREAMING_SRC_ERR)err_code);
	});
}
void UIMediaStreamingSourceObserver::onOpenDone(agora::rtc::STREAMING_SRC_ERR err_code)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnOpenDone.Broadcast((ESTREAMING_SRC_ERR)err_code);
	});
}
void UIMediaStreamingSourceObserver::onSeekDone(agora::rtc::STREAMING_SRC_ERR err_code)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnSeekDone.Broadcast((ESTREAMING_SRC_ERR)err_code);
	});
}
void UIMediaStreamingSourceObserver::onEofOnce(int64_t progress_ms, int64_t repeat_count)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnEofOnce.Broadcast(progress_ms, repeat_count);
	});
}
void UIMediaStreamingSourceObserver::onProgress(int64_t position_ms)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnProgress.Broadcast(position_ms);
	});
}
void UIMediaStreamingSourceObserver::onMetaData(const void* data, int length)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnMetaData.Broadcast((int64)data, length);
	});
}