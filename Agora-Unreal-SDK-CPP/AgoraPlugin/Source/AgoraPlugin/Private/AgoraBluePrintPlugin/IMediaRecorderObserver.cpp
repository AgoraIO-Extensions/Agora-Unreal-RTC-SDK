//  Copyright (c) 2023 Agora.io. All rights reserved.


#include "AgoraBluePrintPlugin/IMediaRecorderObserver.h"


void UIMediaRecorderObserver::onRecorderStateChanged(const char* channelId, agora::rtc::uid_t uid, agora::media::RecorderState state, agora::media::RecorderReasonCode error)
{
	FString UEChannelId = UTF8_TO_TCHAR(channelId);

	TWeakObjectPtr<UIMediaRecorderObserver> SelfWeakPtr(this);
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

			OnRecorderStateChanged.Broadcast(UEChannelId, (int64)(uid), state, (ERecorderReasonCode)error);
		});
}
void UIMediaRecorderObserver::onRecorderInfoUpdated(const char* channelId, agora::rtc::uid_t uid, const agora::media::RecorderInfo& info)
{
	FString UEChannelId = UTF8_TO_TCHAR(channelId);
	FRecorderInfo UERecorderInfo = info;

	TWeakObjectPtr<UIMediaRecorderObserver> SelfWeakPtr(this);
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


			OnRecorderInfoUpdated.Broadcast(UEChannelId, (int64)(uid), UERecorderInfo);
		});
}
