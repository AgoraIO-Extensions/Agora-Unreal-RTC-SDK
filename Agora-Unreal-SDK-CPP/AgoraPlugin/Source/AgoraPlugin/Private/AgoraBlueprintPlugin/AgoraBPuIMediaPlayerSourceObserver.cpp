// Copyright(c) 2024 Agora.io. All rights reserved.

#include "AgoraBPuIMediaPlayerSourceObserver.h"
#include "Async/Async.h"

#pragma region IMediaPlayerSourceObserver

void UAgoraBPuIMediaPlayerSourceObserver::AddBlueprintCallbackExecutor(UAgoraBPuIMediaPlayerSourceObserverCBExecutor* Executor)
{
	if (Executor == nullptr)
	{
		UAgoraBPuLogger::PrintWarn(FString::Printf(TEXT("%s Null Callback Executor"), *FString(AG_FUNCTION_MACRO)));
		return;
	}

	OnPlayerSourceStateChanged.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerSourceStateChanged);

	OnPositionChanged.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPositionChanged);

	OnPlayerEvent.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerEvent);

	OnMetaData.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnMetaData);

	OnPlayBufferUpdated.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayBufferUpdated);

	OnPreloadEvent.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPreloadEvent);

	OnCompleted.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnCompleted);

	OnAgoraCDNTokenWillExpire.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnAgoraCDNTokenWillExpire);

	OnPlayerSrcInfoChanged.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerSrcInfoChanged);

	OnPlayerInfoUpdated.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerInfoUpdated);

	OnPlayerCacheStats.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerCacheStats);

	OnPlayerPlaybackStats.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerPlaybackStats);

	OnAudioVolumeIndication.AddDynamic(Executor, &UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnAudioVolumeIndication);
}



void UAgoraBPuIMediaPlayerSourceObserver::RemoveAllBlueprintCallbackExecutors()
{
	OnPlayerSourceStateChanged.Clear();
	OnPositionChanged.Clear();
	OnPlayerEvent.Clear();
	OnMetaData.Clear();
	OnPlayBufferUpdated.Clear();
	OnPreloadEvent.Clear();
	OnCompleted.Clear();
	OnAgoraCDNTokenWillExpire.Clear();
	OnPlayerSrcInfoChanged.Clear();
	OnPlayerInfoUpdated.Clear();
	OnPlayerCacheStats.Clear();
	OnPlayerPlaybackStats.Clear();
	OnAudioVolumeIndication.Clear();
}

void UAgoraBPuIMediaPlayerSourceObserver::onPlayerSourceStateChanged(agora::media::base::MEDIA_PLAYER_STATE state, agora::media::base::MEDIA_PLAYER_REASON ec)
{
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerSourceStateChanged.Broadcast((EMEDIA_PLAYER_STATE)state, FENUMWRAP_MEDIA_PLAYER_REASON(ec));
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onPositionChanged(int64_t position_ms, int64_t timestampMs)
{
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPositionChanged.Broadcast(position_ms, timestampMs);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{
	FString UEMessage = UTF8_TO_TCHAR(message);

	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerEvent.Broadcast((EMEDIA_PLAYER_EVENT)eventCode, elapsedTime, UEMessage);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{
	FString UEStr = UTF8_TO_TCHAR((char*)data);

	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnMetaData.Broadcast(UEStr);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayBufferUpdated.Broadcast(playCachedBuffer);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onPreloadEvent(const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event)
{
	FString UEStr = UTF8_TO_TCHAR(src);
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPreloadEvent.Broadcast(UEStr, (EPLAYER_PRELOAD_EVENT)event);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onCompleted()
{
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnCompleted.Broadcast();
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnAgoraCDNTokenWillExpire.Broadcast();
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from, const agora::media::base::SrcInfo& to)
{

	FSrcInfo UESrcInfoFrom = from;
	FSrcInfo UESrcInfoTo = to;

	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerSrcInfoChanged.Broadcast(UESrcInfoFrom, UESrcInfoTo);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onPlayerInfoUpdated(const agora::media::base::PlayerUpdatedInfo& info)
{
	FPlayerUpdatedInfo UEPlayerUpdatedInfo = info;

	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerInfoUpdated.Broadcast(UEPlayerUpdatedInfo);
		});
}
void UAgoraBPuIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnAudioVolumeIndication.Broadcast(volume);
		});
}




void UAgoraBPuIMediaPlayerSourceObserver::onPlayerCacheStats(const agora::media::base::CacheStatistics& stats)
{
	FCacheStatistics UEStats = stats;
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerCacheStats.Broadcast(UEStats);
		});
}



void UAgoraBPuIMediaPlayerSourceObserver::onPlayerPlaybackStats(const agora::media::base::PlayerPlaybackStats& stats)
{


	FPlayerPlaybackStats UEStats = stats;
	TWeakObjectPtr<UAgoraBPuIMediaPlayerSourceObserver> SelfWeakPtr(this);
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

			OnPlayerPlaybackStats.Broadcast(UEStats);
		});
}


#pragma endregion IMediaPlayerSourceObserver


#pragma region IMediaPlayerSourceObserverCBExecutor

void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerSourceStateChanged_Implementation(EMEDIA_PLAYER_STATE state, FENUMWRAP_MEDIA_PLAYER_REASON ec)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPositionChanged_Implementation(int64 position_ms, int64 timestampMs)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerEvent_Implementation(EMEDIA_PLAYER_EVENT eventCode, int64 elapsedTime, const FString& message)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnMetaData_Implementation(const FString& data)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayBufferUpdated_Implementation(int64 playCachedBuffer)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}

void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPreloadEvent_Implementation(const FString& src, EPLAYER_PRELOAD_EVENT event)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnCompleted_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnAgoraCDNTokenWillExpire_Implementation()
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerSrcInfoChanged_Implementation(const FSrcInfo& from, const FSrcInfo& to)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerInfoUpdated_Implementation(const FPlayerUpdatedInfo& info)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerCacheStats_Implementation(const FCacheStatistics& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnPlayerPlaybackStats_Implementation(const FPlayerPlaybackStats& stats)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


void UAgoraBPuIMediaPlayerSourceObserverCBExecutor::OnAudioVolumeIndication_Implementation(int volume)
{
	UE_LOG(LogAgora, Warning, TEXT("%s"), *FString(AG_FUNCTION_MACRO));
}


#pragma endregion IMediaPlayerSourceObserverCBExecutor
