// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraMediaPlayer.h"
#include "AgoraCppPlugin/IAgoraMediaPlayer.h"


int UIMediaPlayer::GetMediaPlayerId()
{
	return MediaPlayer->getMediaPlayerId();
}
int UIMediaPlayer::Open(FString url, int64 startPos)
{
	return MediaPlayer->open(TCHAR_TO_ANSI(*url), startPos);
}

int UIMediaPlayer::OpenWithCustomSource(int64 startPos, UIMediaPlayerCustomDataProvider* provider)
{
	return MediaPlayer->openWithCustomSource(startPos, provider);
}
int UIMediaPlayer::OpenWithMediaSource(FAgoraMediaSource& source)
{
	agora::media::base::MediaSource mediaSource;
	mediaSource.url = TCHAR_TO_ANSI(*source.url);
	mediaSource.uri = TCHAR_TO_ANSI(*source.uri);
	mediaSource.startPos = source.startPos;
	mediaSource.autoPlay = source.autoPlay;
	mediaSource.enableCache = source.enableCache;
	if (source.isAgoraSource != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		mediaSource.isAgoraSource = source.isAgoraSource == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	if (source.isLiveSource != AGORAOPTIONAL::AGORA_NULL_VALUE)
	{
		mediaSource.isLiveSource = source.isLiveSource == AGORAOPTIONAL::AGORA_TRUE_VALUE;
	}
	mediaSource.provider = source.provider;

	return MediaPlayer->openWithMediaSource(mediaSource);
}
int UIMediaPlayer::Play()
{
	return MediaPlayer->play();
}
int UIMediaPlayer::Pause()
{
	return MediaPlayer->pause();
}
int UIMediaPlayer::Stop()
{
	return MediaPlayer->stop();
}
int UIMediaPlayer::Resume()
{
	return MediaPlayer->resume();
}
int UIMediaPlayer::Seek(int64 newPos)
{
	return MediaPlayer->seek(newPos);
}
int UIMediaPlayer::SetAudioPitch(int pitch)
{
	return MediaPlayer->setAudioPitch(pitch);
}
int UIMediaPlayer::GetDuration(int64& duration)
{
	int64_t dur;

	int ret = MediaPlayer->getDuration(dur);

	duration = dur;

	return ret;
}
int UIMediaPlayer::GetPlayPosition(int64& pos)
{
	int64_t postion;

	int ret = MediaPlayer->getPlayPosition(postion);

	pos = postion;

	return ret;
}
int UIMediaPlayer::GetStreamCount(int64& count)
{
	int64_t con;

	int ret = MediaPlayer->getStreamCount(con);

	count = con;

	return ret;
}
int UIMediaPlayer::GetStreamInfo(int64 index, FPlayerStreamInfo& info)
{
	agora::media::base::PlayerStreamInfo playerStreamInfo;
	int ret = MediaPlayer->getStreamInfo(index, &playerStreamInfo);
	info.streamIndex = playerStreamInfo.streamIndex;
	info.streamType = (EMEDIA_STREAM_TYPE)playerStreamInfo.streamType;
	info.codecName = FString(playerStreamInfo.codecName);
	info.language = FString(playerStreamInfo.language);
	info.videoFrameRate = playerStreamInfo.videoFrameRate;
	info.videoBitRate = playerStreamInfo.videoBitRate;
	info.videoWidth = playerStreamInfo.videoWidth;
	info.videoHeight = playerStreamInfo.videoHeight;
	info.videoRotation = playerStreamInfo.videoRotation;
	info.audioSampleRate = playerStreamInfo.audioSampleRate;
	info.audioChannels = playerStreamInfo.audioChannels;
	info.audioBitsPerSample = playerStreamInfo.audioBitsPerSample;
	info.duration = playerStreamInfo.duration;

	return -ERROR_NULLPTR;
}
int UIMediaPlayer::SetLoopCount(int loopCount)
{
	return MediaPlayer->setLoopCount(loopCount);
}
int UIMediaPlayer::SetPlaybackSpeed(int speed)
{
	return MediaPlayer->setPlaybackSpeed(speed);
}
int UIMediaPlayer::SelectAudioTrack(int index)
{
	return MediaPlayer->selectAudioTrack(index);
}

int UIMediaPlayer::SetPlayerOptionInInt(FString key, int value)
{
	auto ret = MediaPlayer->setPlayerOption(TCHAR_TO_ANSI(*key), value);
	return ret;
}

int UIMediaPlayer::SetPlayerOptionInString(FString key, FString value)
{
	auto ret = MediaPlayer->setPlayerOption(TCHAR_TO_ANSI(*key), TCHAR_TO_ANSI(*value));
	return ret;
}

int UIMediaPlayer::TakeScreenshot(FString filename)
{
	return MediaPlayer->takeScreenshot(TCHAR_TO_ANSI(*filename));
}
int UIMediaPlayer::SelectInternalSubtitle(int index)
{
	return MediaPlayer->selectInternalSubtitle(index);
}
int UIMediaPlayer::SetExternalSubtitle(FString url)
{
	return MediaPlayer->setExternalSubtitle(TCHAR_TO_ANSI(*url));
}
EMEDIA_PLAYER_STATE UIMediaPlayer::GetState()
{
	return (EMEDIA_PLAYER_STATE)MediaPlayer->getState();
}
int UIMediaPlayer::Mute(bool muted)
{
	return MediaPlayer->mute(muted);
}
int UIMediaPlayer::GetMute(bool muted)
{
	return MediaPlayer->getMute(muted);
}
int UIMediaPlayer::AdjustPlayoutVolume(int volume)
{
	return MediaPlayer->adjustPlayoutVolume(volume);
}
int UIMediaPlayer::GetPlayoutVolume(int volume)
{
	return MediaPlayer->getPlayoutVolume(volume);
}
int UIMediaPlayer::AdjustPublishSignalVolume(int volume)
{
	return MediaPlayer->adjustPublishSignalVolume(volume);
}
int UIMediaPlayer::GetPublishSignalVolume(int volume)
{
	return MediaPlayer->getPublishSignalVolume(volume);
}
int UIMediaPlayer::SetView(int64 view)
{
	return MediaPlayer->setView((agora::view_t)view);
}
int UIMediaPlayer::SetRenderMode(ERENDER_MODE_TYPE renderMode)
{
	return MediaPlayer->setRenderMode((agora::media::base::RENDER_MODE_TYPE)renderMode);
}
int UIMediaPlayer::RegisterPlayerSourceObserver(UIMediaPlayerSourceObserver* observer)
{
	return MediaPlayer->registerPlayerSourceObserver(observer);
}
int UIMediaPlayer::UnregisterPlayerSourceObserver(UIMediaPlayerSourceObserver* observer)
{
	return MediaPlayer->unregisterPlayerSourceObserver(observer);
}
int UIMediaPlayer::RegisterAudioFrameObserver(UIAudioPcmFrameSink* observer, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode)
{
	return MediaPlayer->registerAudioFrameObserver((agora::media::IAudioPcmFrameSink*)observer, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode);
}
int UIMediaPlayer::UnregisterAudioFrameObserver(UIAudioPcmFrameSink* observer)
{
	return MediaPlayer->unregisterAudioFrameObserver((agora::media::IAudioPcmFrameSink*)observer);
}
int UIMediaPlayer::RegisterVideoFrameObserver(UIVideoFrameObserver* observer)
{
	return MediaPlayer->registerVideoFrameObserver((agora::media::base::IVideoFrameObserver*)observer);
}
int UIMediaPlayer::UnregisterVideoFrameObserver(UIVideoFrameObserver* observer)
{
	return MediaPlayer->unregisterVideoFrameObserver((agora::media::base::IVideoFrameObserver*)observer);
}
int UIMediaPlayer::RegisterMediaPlayerAudioSpectrumObserver(UIAudioSpectrumObserver* observer, int intervalInMS)
{
	return MediaPlayer->registerMediaPlayerAudioSpectrumObserver(observer, intervalInMS);
}
int UIMediaPlayer::UnregisterMediaPlayerAudioSpectrumObserver(UIAudioSpectrumObserver* observer)
{
	return MediaPlayer->unregisterMediaPlayerAudioSpectrumObserver(observer);
}
int UIMediaPlayer::SetAudioDualMonoMode(EAUDIO_DUAL_MONO_MODE mode)
{
	return MediaPlayer->setAudioDualMonoMode((agora::media::base::AUDIO_DUAL_MONO_MODE)mode);
}
FString UIMediaPlayer::GetPlayerSdkVersion()
{
	return MediaPlayer->getPlayerSdkVersion();
}
FString UIMediaPlayer::GetPlaySrc()
{
	return MediaPlayer->getPlaySrc();
}
int UIMediaPlayer::OpenWithAgoraCDNSrc(FString src, int64 startPos)
{
	return MediaPlayer->openWithAgoraCDNSrc(TCHAR_TO_ANSI(*src), startPos);
}
int UIMediaPlayer::GetAgoraCDNLineCount()
{
	return MediaPlayer->getAgoraCDNLineCount();
}
int UIMediaPlayer::SwitchAgoraCDNLineByIndex(int index)
{
	return MediaPlayer->switchAgoraCDNLineByIndex(index);
}
int UIMediaPlayer::GetCurrentAgoraCDNIndex()
{
	return MediaPlayer->getCurrentAgoraCDNIndex();
}
int UIMediaPlayer::EnableAutoSwitchAgoraCDN(bool enable)
{
	return MediaPlayer->enableAutoSwitchAgoraCDN(enable);
}
int UIMediaPlayer::RenewAgoraCDNSrcToken(FString token, int64 ts)
{
	return MediaPlayer->renewAgoraCDNSrcToken(TCHAR_TO_ANSI(*token), ts);
}
int UIMediaPlayer::SwitchAgoraCDNSrc(FString src, bool syncPts)
{
	return MediaPlayer->switchAgoraCDNSrc(TCHAR_TO_ANSI(*src), syncPts);
}
int UIMediaPlayer::SwitchSrc(FString src, bool syncPts)
{
	return MediaPlayer->switchSrc(TCHAR_TO_ANSI(*src), syncPts);
}
int UIMediaPlayer::PreloadSrc(FString src, int64 startPos)
{
	return MediaPlayer->preloadSrc(TCHAR_TO_ANSI(*src), startPos);
}
int UIMediaPlayer::PlayPreloadedSrc(FString src)
{
	return MediaPlayer->playPreloadedSrc(TCHAR_TO_ANSI(*src));
}
int UIMediaPlayer::UnloadSrc(FString src)
{
	return MediaPlayer->unloadSrc(TCHAR_TO_ANSI(*src));
}
int UIMediaPlayer::SetSpatialAudioParams(FSpatialAudioParams& params)
{
	agora::SpatialAudioParams spatialAudioParams;
	SET_AGORA_DATA_SPATIALAUDIOPARAMS(spatialAudioParams, params);
	return MediaPlayer->setSpatialAudioParams(spatialAudioParams);
}
int UIMediaPlayer::SetSoundPositionParams(float pan, float gain)
{
	return MediaPlayer->setSoundPositionParams(pan, gain);
}
void UIMediaPlayer::SetMediaPlayer(agora::agora_refptr<agora::rtc::IMediaPlayer> mediaPlayer)
{
	this->MediaPlayer = mediaPlayer;
}

agora::agora_refptr<agora::rtc::IMediaPlayer> UIMediaPlayer::GetMediaPlayer()
{
	return this->MediaPlayer;
}

int UIMediaPlayerCacheManager::RemoveAllCaches()
{
	return getMediaPlayerCacheManager()->removeAllCaches();
}
int UIMediaPlayerCacheManager::RemoveOldCache()
{
	return getMediaPlayerCacheManager()->removeOldCache();
}
int UIMediaPlayerCacheManager::RemoveCacheByUri(FString uri)
{
	return getMediaPlayerCacheManager()->removeCacheByUri(TCHAR_TO_ANSI(*uri));
}
int UIMediaPlayerCacheManager::SetCacheDir(FString path)
{
	return getMediaPlayerCacheManager()->setCacheDir(TCHAR_TO_ANSI(*path));
}
int UIMediaPlayerCacheManager::SetMaxCacheFileCount(int count)
{
	return getMediaPlayerCacheManager()->setMaxCacheFileCount(count);
}
int UIMediaPlayerCacheManager::SetMaxCacheFileSize(int64 cacheSize)
{
	return getMediaPlayerCacheManager()->setMaxCacheFileCount(cacheSize);
}
int UIMediaPlayerCacheManager::EnableAutoRemoveCache(bool enable)
{
	return getMediaPlayerCacheManager()->enableAutoRemoveCache(enable);
}
int UIMediaPlayerCacheManager::GetCacheDir(FString path, int length)
{
	return getMediaPlayerCacheManager()->getCacheDir(TCHAR_TO_ANSI(*path), length);
}
int UIMediaPlayerCacheManager::GetMaxCacheFileCount()
{
	return getMediaPlayerCacheManager()->getMaxCacheFileCount();
}
int64 UIMediaPlayerCacheManager::GetMaxCacheFileSize()
{
	return getMediaPlayerCacheManager()->getMaxCacheFileSize();
}
int UIMediaPlayerCacheManager::GetCacheFileCount()
{
	return getMediaPlayerCacheManager()->getCacheFileCount();
}

