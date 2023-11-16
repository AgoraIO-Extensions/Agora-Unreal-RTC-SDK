//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/IMediaStreamingSourceObserver.h"


void UIMediaStreamingSourceObserver::onStateChanged(agora::rtc::STREAMING_SRC_STATE state, agora::rtc::STREAMING_SRC_ERR err_code)
{
	TWeakObjectPtr<UIMediaStreamingSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnStateChanged.Broadcast((ESTREAMING_SRC_STATE)state, (ESTREAMING_SRC_ERR)err_code);
		});
}
void UIMediaStreamingSourceObserver::onOpenDone(agora::rtc::STREAMING_SRC_ERR err_code)
{
	TWeakObjectPtr<UIMediaStreamingSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnOpenDone.Broadcast((ESTREAMING_SRC_ERR)err_code);
		});
}
void UIMediaStreamingSourceObserver::onSeekDone(agora::rtc::STREAMING_SRC_ERR err_code)
{
	TWeakObjectPtr<UIMediaStreamingSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnSeekDone.Broadcast((ESTREAMING_SRC_ERR)err_code);
		});
}
void UIMediaStreamingSourceObserver::onEofOnce(int64_t progress_ms, int64_t repeat_count)
{
	TWeakObjectPtr<UIMediaStreamingSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnEofOnce.Broadcast(progress_ms, repeat_count);
		});
}
void UIMediaStreamingSourceObserver::onProgress(int64_t position_ms)
{
	TWeakObjectPtr<UIMediaStreamingSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnProgress.Broadcast(position_ms);
		});
}
void UIMediaStreamingSourceObserver::onMetaData(const void* data, int length)
{
	TWeakObjectPtr<UIMediaStreamingSourceObserver> SelfWeakPtr(this);
	if (!SelfWeakPtr.IsValid())
		return;

#if (__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!SelfWeakPtr.IsValid())
				return;

			OnMetaData.Broadcast((int64)data, length);
		});
}