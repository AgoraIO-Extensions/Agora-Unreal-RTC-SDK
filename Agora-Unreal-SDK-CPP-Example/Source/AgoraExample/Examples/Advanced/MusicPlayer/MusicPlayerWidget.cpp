// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicPlayerWidget.h"
#include <string>
void UMusicPlayerWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

}

void UMusicPlayerWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;
	RtcEngineContext.audioScenario = agora::rtc::AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_GAME_STREAMING;
	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;

	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMusicPlayerWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [MusicPlayer]\n"
		"1. Currently, it is only supported on mobile platforms.\n"
		"2. It requires an [RTM AppID, not the RTC one], an [RTM Token], and an [RTM UID].\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UMusicPlayerWidget::OnBtnJoinChannelClicked()
{
	if (ET_RTMAPPID->GetText().ToString() == "") {
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s Please enter your rtm appid first"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	if (ET_RTMTOKEN->GetText().ToString() == "") {
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s Please enter your rtm token first"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	if (ET_RTMUID->GetText().ToString() == "") {
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s Please enter your rtm uid first"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);

	agora::rtc::MusicContentCenterConfiguration Config;
	std::string StdStrAppID = TCHAR_TO_UTF8(*ET_RTMAPPID->GetText().ToString());
	std::string StdStrToken = TCHAR_TO_UTF8(*ET_RTMTOKEN->GetText().ToString());
	Config.appId = StdStrAppID.c_str();
	Config.token = StdStrToken.c_str();
	Config.mccUid = FCString::Atoi64(*ET_RTMUID->GetText().ToString());
	Config.maxCacheSize = 10;

	AgoraUERtcEngine::Get()->queryInterface(AGORA_IID_MUSIC_CONTENT_CENTER, (void**)&MusicContentCenterPtr);
	int ret = MusicContentCenterPtr->initialize(Config);
	UBFL_Logger::Print(FString::Printf(TEXT("%s MusicContentCenterPtr initialize ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	if (ret != 0)
		return;

	UserMusicContentCenterEventHandler = MakeShared<FUserMusicContentCenterEventHandler>(this);
	MusicContentCenterPtr->registerEventHandler(UserMusicContentCenterEventHandler.Get());
	MusicPlayer = MusicContentCenterPtr->createMusicPlayer();
	ChannelMediaOptions Options;
	Options.autoSubscribeAudio = true;
	Options.autoSubscribeVideo = true;
	Options.publishMicrophoneTrack = false;
	Options.publishCameraTrack = false;
	Options.publishMediaPlayerAudioTrack = true;
	Options.publishMediaPlayerVideoTrack = true;
	Options.enableAudioRecordingOrPlayout = true;
	Options.clientRoleType = CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
	if (MusicPlayer) {
		int MediaPlayerID = MusicPlayer->getMediaPlayerId();
		Options.publishMediaPlayerId = MediaPlayerID;
		UserIMediaPlayerSourceObserver = MakeShared<FUserIMediaPlayerSourceObserver>(this);
		MusicPlayer->registerPlayerSourceObserver(UserIMediaPlayerSourceObserver.Get());
		UBFL_Logger::Print(FString::Printf(TEXT("%s MediaPlayer ID = %d"), *FString(FUNCTION_MACRO), MediaPlayerID), LogMsgViewPtr);
	}

	int ret2 = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), 0, Options);
	UBFL_Logger::Print(FString::Printf(TEXT("%s JoinChannel ret %d"), *FString(FUNCTION_MACRO), ret2), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnBtnGetCachesClicked()
{
	// to retrieve the song's data cache

	int CacheInfoSize = 10;
	agora::rtc::MusicCacheInfo* Infos = new MusicCacheInfo[CacheInfoSize];
	// if the actaul size is less than CacheInfoSize, CacheInfoSize will be the actual size
	int ret = MusicContentCenterPtr->getCaches(Infos, &CacheInfoSize);
	UBFL_Logger::Print(FString::Printf(TEXT("%s getCaches ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	if (ret == 0) {
		for (int i = 0; i < CacheInfoSize; i++)
		{
			UBFL_Logger::Print(FString::Printf(TEXT("%s song code %lld status %d"), *FString(FUNCTION_MACRO), Infos[i].songCode, Infos[i].status), LogMsgViewPtr);
		}
	}
	delete[] Infos;
}


void UMusicPlayerWidget::OnBtnRemoveCachesClicked()
{
	if (CurSongId == 0)
	{
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s CurSong is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	int ret = MusicContentCenterPtr->removeCache(CurSongId);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnBtnGetMusicChartsClicked()
{
	agora::util::AString RequestId;
	int ret = MusicContentCenterPtr->getMusicCharts(RequestId);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s requestid=%s"), *FString(FUNCTION_MACRO), UTF8_TO_TCHAR(RequestId->c_str())), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnCBSMusicChartsValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int Index = CBS_MusicCharts->FindOptionIndex(SelectedItem);
	if (Index == -1 || Index > MusicChartInfoList.Num())
		return;

	MusicChartInfo Info = MusicChartInfoList[Index];
	CurChartId = Info.id;
	agora::util::AString RequestId;
	int ret = MusicContentCenterPtr->getMusicCollectionByMusicChartId(RequestId, CurChartId, 0, 20, "");
	UBFL_Logger::Print(FString::Printf(TEXT("%s Selected Chart %s"), *FString(FUNCTION_MACRO), UTF8_TO_TCHAR(Info.chartName)), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s requestid=%s"), *FString(FUNCTION_MACRO), UTF8_TO_TCHAR(RequestId->c_str())), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnCBSSelectedSongValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int Index = CBS_SelectedSong->FindOptionIndex(SelectedItem);
	if (Index == -1 || Index > MusicCollectionList.Num())
		return;
	Music TargetMusic = MusicCollectionList[Index];
	CurSongId = TargetMusic.songCode;
	Txt_SelectedSong->SetText(FText::FromString(FString(UTF8_TO_TCHAR(TargetMusic.name))));
}

void UMusicPlayerWidget::OnBtnGetLyricClicked()
{
	if (CurSongId == 0)
	{
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s CurSong is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	agora::util::AString RequestId;
	int ret = MusicContentCenterPtr->getLyric(RequestId, CurSongId, 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s GetLyrics ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	UBFL_Logger::Print(FString::Printf(TEXT("%s RequestId=%s"), *FString(FUNCTION_MACRO), UTF8_TO_TCHAR(RequestId->c_str())), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnBtnOpenClicked()
{
	if (CurSongId == 0)
	{
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s CurSong is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}
	MusicPlayer->stop();
	int ret = MusicPlayer->open(CurSongId, 0);
	UBFL_Logger::Print(FString::Printf(TEXT("%s MusicPlayer Open Ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	MakeVideoView(MusicPlayer->getMediaPlayerId(), VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER, "");
}

void UMusicPlayerWidget::OnBtnIsPreloadClicked()
{
	if (CurSongId == 0)
	{
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s CurSong is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	int ret = MusicContentCenterPtr->isPreloaded(CurSongId);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnBtnPreloadClicked()
{
	if (CurSongId == 0)
	{
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s CurSong is Empty"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	int ret = MusicContentCenterPtr->preload(CurSongId, "");
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UMusicPlayerWidget::OnBtnSearchMusicClicked()
{
	if (ET_SearchMusicName->GetText().ToString() == "") {
		UBFL_Logger::PrintWarn(FString::Printf(TEXT("%s Please enter the music name you want to search"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
		return;
	}

	FString MusicName = ET_SearchMusicName->GetText().ToString();
	agora::util::AString RequestId;
	int ret = MusicContentCenterPtr->searchMusic(RequestId, TCHAR_TO_UTF8(*MusicName), 0, 5, "");
	UBFL_Logger::Print(FString::Printf(TEXT("%s MusicPlayer Open Ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	if (ret == 0) {
		MakeVideoView(MusicPlayer->getMediaPlayerId(), VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER, "");
	}
}

void UMusicPlayerWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}


void UMusicPlayerWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}

void UMusicPlayerWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		if (MusicPlayer) {
			MusicPlayer->unregisterPlayerSourceObserver(UserIMediaPlayerSourceObserver.Get());
			AgoraUERtcEngine::Get()->destroyMediaPlayer(MusicPlayer);
		}

		if (MusicContentCenterPtr != nullptr) {
			MusicContentCenterPtr->unregisterEventHandler();
			MusicContentCenterPtr->release();
			MusicContentCenterPtr = nullptr;
		}

		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());

		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}


void UMusicPlayerWidget::UpdateUIMusicChartInfo()
{
	check(IsInGameThread());
	FScopeLock Lock(&CriticalSectionForMusicChartInfoList);
	CBS_MusicCharts->ClearOptions();
	if (MusicChartInfoList.Num() == 0)
		return;

	for (int i = 0; i < MusicChartInfoList.Num(); i++) {
		MusicChartInfo Tmp = MusicChartInfoList[i];
		CBS_MusicCharts->AddOption(UTF8_TO_TCHAR(Tmp.chartName));
		if (i == 0) {
			CurChartId = Tmp.id;
		}

		UBFL_Logger::Print(FString::Printf(TEXT("[Agora-MusicChartAfter] ChartName=%s  Id=%d"), UTF8_TO_TCHAR(Tmp.chartName), Tmp.id), LogMsgViewPtr);
	}

}

void UMusicPlayerWidget::UpdateUIMusicCollectionList()
{
	check(IsInGameThread());

	FScopeLock Lock(&CriticalSectionForMusicCollectionList);

	CBS_SelectedSong->ClearOptions();
	if (MusicCollectionList.Num() == 0)
		return;

	for (int i = 0; i < MusicCollectionList.Num(); i++) {
		Music Tmp = MusicCollectionList[i];
		CBS_SelectedSong->AddOption(UTF8_TO_TCHAR(Tmp.name));
		if (i == 0) {
			CurSongId = Tmp.songCode;
			Txt_SelectedSong->SetText(FText::FromString(FString(UTF8_TO_TCHAR(Tmp.name))));
		}

		UBFL_Logger::Print(FString::Printf(TEXT("[Agora-MusicCollectionAfter] SongName=%s  Code=%lld"), UTF8_TO_TCHAR(Tmp.name), Tmp.songCode), LogMsgViewPtr);
	}
}


void UMusicPlayerWidget::UpdateDataMusicChartInfoListData(agora_refptr<MusicChartCollection> result)
{
	// Not in Game Thread, no UI logic here
	FScopeLock Lock(&CriticalSectionForMusicChartInfoList);
	for (auto MusicChartInfo : MusicChartInfoList)
		delete[] MusicChartInfo.chartName;
	MusicChartInfoList.Empty();


	for (int i = 0; i < result->getCount(); i++) {
		MusicChartInfo* ItemResult = result->get(i);
		MusicChartInfo OneItem;

		const size_t Len = strlen(ItemResult->chartName);
		char* TmpDataToCopy = new char[Len + 1];
		strncpy(TmpDataToCopy, ItemResult->chartName, Len);
		TmpDataToCopy[Len] = '\0';
		OneItem.chartName = TmpDataToCopy;

		OneItem.id = ItemResult->id;
		UE_LOG(LogTemp, Warning, TEXT("[Agora-MusicChart] ChartName=%s  Id=%d"), UTF8_TO_TCHAR(OneItem.chartName), OneItem.id);
		MusicChartInfoList.Add(OneItem);
	}
}

void UMusicPlayerWidget::UpdateDataMusicCollectionList(agora_refptr<MusicCollection> result)
{
	// Not in Game Thread, no UI logic here

	FScopeLock Lock(&CriticalSectionForMusicCollectionList);

	for (auto MusicCollection : MusicCollectionList)
		delete[] MusicCollection.name;
	MusicCollectionList.Empty();

	for (int i = 0; i < result->getCount(); i++) {
		Music* ItemResult = result->getMusic(i);
		Music OneItem;
		OneItem.songCode = ItemResult->songCode;

		const size_t Len = strlen(ItemResult->name);
		char* TmpDataToCopy = new char[Len + 1];
		strncpy(TmpDataToCopy, ItemResult->name, Len);
		TmpDataToCopy[Len] = '\0';
		OneItem.name = TmpDataToCopy;

		MusicCollectionList.Add(OneItem);
		UE_LOG(LogTemp, Warning, TEXT("[Agora-MusicCollection] SongName=%s  Code=%d"), UTF8_TO_TCHAR(OneItem.name), OneItem.songCode);
	}

}

#pragma region UI Utility

int UMusicPlayerWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	/*
		For local view:
			please reference the callback function Ex.[onCaptureVideoFrame]

		For remote view:
			please reference the callback function [onRenderVideoFrame]

		channelId will be set in [setupLocalVideo] / [setupRemoteVideo]
	*/

	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{

		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);

		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}

	return ret;
}

int UMusicPlayerWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}
	return ret;
}


#pragma endregion



#pragma region AgoraCallback - IRtcEngineEventHandlerEx

void UMusicPlayerWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			// WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UMusicPlayerWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			// WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UMusicPlayerWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UMusicPlayerWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

#pragma endregion


#pragma region AgoraCallback - IMediaPlayerSourceObserver


void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_REASON reason)
{
	if (state == media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_OPEN_COMPLETED)
		WidgetPtr->GetMusicPlayer()->play();
}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPositionChanged(int64_t positionMs, int64_t timestampMs)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onCompleted()
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info)
{

}

void UMusicPlayerWidget::FUserIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{

}

#pragma endregion


#pragma region AgoraCallback - IMusicContentCenterEventHandler

void UMusicPlayerWidget::FUserMusicContentCenterEventHandler::onMusicChartsResult(const char* requestId, agora_refptr<MusicChartCollection> result, MusicContentCenterStateReason reason)
{
	if (!IsWidgetValid())
		return;

	WidgetPtr->UpdateDataMusicChartInfoListData(result);

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{

			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->UpdateUIMusicChartInfo();

		});
}

void UMusicPlayerWidget::FUserMusicContentCenterEventHandler::onMusicCollectionResult(const char* requestId, agora_refptr<MusicCollection> result, MusicContentCenterStateReason reason)
{
	if (!IsWidgetValid())
		return;

	WidgetPtr->UpdateDataMusicCollectionList(result);

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{

			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());


			WidgetPtr->UpdateUIMusicCollectionList();

		});
}

void UMusicPlayerWidget::FUserMusicContentCenterEventHandler::onLyricResult(const char* requestId, int64_t songCode, const char* lyricUrl, MusicContentCenterStateReason reason)
{
	if (!IsWidgetValid())
		return;


	FString RequestId = UTF8_TO_TCHAR(requestId);
	FString URLLyric = UTF8_TO_TCHAR(lyricUrl);


#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s LyricURL=%s RequestId=%s error_code=%d"), *FString(FUNCTION_MACRO), *URLLyric, *RequestId, reason), WidgetPtr->GetLogMsgViewPtr());
		});
}


void UMusicPlayerWidget::FUserMusicContentCenterEventHandler::onSongSimpleInfoResult(const char* requestId, int64_t songCode, const char* simpleInfo, MusicContentCenterStateReason reason)
{

	if (!IsWidgetValid())
		return;


	FString RequestId = UTF8_TO_TCHAR(requestId);
	FString SimpleInfo = UTF8_TO_TCHAR(simpleInfo);


#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s RequestId=%s SongCode=%lld SimpleInfo=%s error_code=%d"), *FString(FUNCTION_MACRO), *RequestId,songCode, *SimpleInfo, reason), WidgetPtr->GetLogMsgViewPtr());
		});
}


void UMusicPlayerWidget::FUserMusicContentCenterEventHandler::onPreLoadEvent(const char* requestId, int64_t songCode, int percent, const char* lyricUrl, PreloadState state, MusicContentCenterStateReason reason)
{


	if (!IsWidgetValid())
		return;

	FString URLLyric = UTF8_TO_TCHAR(lyricUrl);

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s songcode=%d percent=%d LyricURL=%s status=%d errorcode=%d "), *FString(FUNCTION_MACRO), songCode, percent, *URLLyric, state, reason), WidgetPtr->GetLogMsgViewPtr());
		});
}


#pragma endregion


