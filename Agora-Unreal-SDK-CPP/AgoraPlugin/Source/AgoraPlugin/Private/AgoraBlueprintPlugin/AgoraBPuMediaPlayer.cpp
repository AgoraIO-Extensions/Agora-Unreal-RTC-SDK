// Copyright(c) 2024 Agora.io. All rights reserved.


#include "AgoraBPuMediaPlayer.h"
#include "AgoraHeaderBase.h"


UAgoraBPuMediaPlayer* UAgoraBPuMediaPlayer::Instance = nullptr;

UAgoraBPuMediaPlayer* UAgoraBPuMediaPlayer::GetAgoraMediaPlayer()
{
	if (!Instance)
	{
		Instance = NewObject<UAgoraBPuMediaPlayer>();
		Instance->AddToRoot();

		Instance->MediaPlayer = AgoraUERtcEngine::Get()->createMediaPlayer();

		// register player source observer
		Instance->UserMediaPlayerSourceObserver =TStrongObjectPtr<UAgoraBPuIMediaPlayerSourceObserver>(NewObject<UAgoraBPuIMediaPlayerSourceObserver>());

		Instance->MediaPlayer->registerPlayerSourceObserver(Instance->UserMediaPlayerSourceObserver.Get());

	}
	return Instance;
}

void UAgoraBPuMediaPlayer::Release()
{
	if (Instance)
	{
		if (Instance->MediaPlayer.get() != nullptr) {
			//MediaPlayer->stop();
			//MediaPlayer->unregisterPlayerSourceObserver(UserIMediaPlayerSourceObserver.Get());
			Instance->UserMediaPlayerSourceObserver->RemoveAllBlueprintCallbackExecutors();
			Instance->MediaPlayer->unregisterPlayerSourceObserver(Instance->UserMediaPlayerSourceObserver.Get());
			Instance->UserMediaPlayerSourceObserver.Reset();
			AgoraUERtcEngine::Get()->destroyMediaPlayer(MediaPlayer);
			Instance->MediaPlayer= nullptr;
		}
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}


UAgoraBPuIMediaPlayerSourceObserver* UAgoraBPuMediaPlayer::GetMediaPlayerSourceObserver()
{
	if (UserMediaPlayerSourceObserver.IsValid()) {
		return UserMediaPlayerSourceObserver.Get();
	}
	return nullptr;
}

#pragma region Media Player

int UAgoraBPuMediaPlayer::GetMediaPlayerId()
{
	if(MediaPlayer){
		return MediaPlayer->getMediaPlayerId();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::Open(const FString & url, int64 startPos)
{
	if (MediaPlayer) {
		return MediaPlayer->open(TCHAR_TO_UTF8(*url), startPos);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAgoraBPuMediaPlayer::OpenWithMediaSource(const FAgoraMediaSource& source)
{
	if (MediaPlayer) {
		agora::media::base::MediaSource mediaSource = source.CreateAgoraData();
		int ret = MediaPlayer->openWithMediaSource(mediaSource);
		source.FreeAgoraData(mediaSource);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::Play()
{
	if (MediaPlayer) {
		return MediaPlayer->play();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::Pause()
{
	if (MediaPlayer) {
		return MediaPlayer->pause();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::Stop()
{
	if (MediaPlayer) {
		return MediaPlayer->stop();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::Resume()
{
	if (MediaPlayer) {
		return MediaPlayer->resume();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::Seek(int64 newPos)
{
	if (MediaPlayer) {
		return MediaPlayer->seek(newPos);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetAudioPitch(int pitch)
{
	if (MediaPlayer) {
		return MediaPlayer->setAudioPitch(pitch);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetDuration(int64& duration)
{
	if (MediaPlayer) {
		int64_t val;
		int ret = MediaPlayer->getDuration(val);
		duration = val;
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetPlayPosition(int64& pos)
{
	if (MediaPlayer) {
		int64_t val;
		int ret = MediaPlayer->getPlayPosition(val);
		pos = val;
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetStreamCount(int64& count)
{
	if (MediaPlayer) {
		int64_t val;
		int ret = MediaPlayer->getStreamCount(val);
		count = val;
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetStreamInfo(int64 index, FPlayerStreamInfo& info)
{
	if (MediaPlayer) {
		agora::media::base::PlayerStreamInfo* playerStreamInfo = nullptr;
		int ret = MediaPlayer->getStreamInfo(index, playerStreamInfo);
		info = *playerStreamInfo;
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetLoopCount(int loopCount)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setLoopCount(loopCount);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetPlaybackSpeed(int speed)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setPlaybackSpeed(speed);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SelectAudioTrack(int index)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->selectAudioTrack(index);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAgoraBPuMediaPlayer::SelectMultiAudioTrack(int playoutTrackIndex, int publishTrackIndex)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->selectMultiAudioTrack(playoutTrackIndex, publishTrackIndex);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAgoraBPuMediaPlayer::SetPlayerOptionWithInt(const FString & key, int value)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setPlayerOption(TCHAR_TO_UTF8(*key), value);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAgoraBPuMediaPlayer::SetPlayerOptionWithString(const FString& key, const FString& value)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setPlayerOption(TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value));
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAgoraBPuMediaPlayer::TakeScreenshot(const FString& filename)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->takeScreenshot(TCHAR_TO_UTF8(*filename));
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SelectInternalSubtitle(int index)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->selectInternalSubtitle(index);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetExternalSubtitle(const FString& url)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setExternalSubtitle(TCHAR_TO_UTF8(*url));
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
EMEDIA_PLAYER_STATE UAgoraBPuMediaPlayer::GetState()
{
	if (MediaPlayer) {
		return (EMEDIA_PLAYER_STATE)MediaPlayer->getState();
	}
	return EMEDIA_PLAYER_STATE::PLAYER_STATE_FAILED;
}
int UAgoraBPuMediaPlayer::Mute(bool muted)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->mute(muted);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetMute(bool & muted)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->getMute(muted);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::AdjustPlayoutVolume(int volume)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->adjustPlayoutVolume(volume);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetPlayoutVolume(int & volume)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->getPlayoutVolume(volume);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::AdjustPublishSignalVolume(int volume)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->adjustPublishSignalVolume(volume);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetPublishSignalVolume(int & volume)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->getPublishSignalVolume(volume);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetView(int64 view)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setView(UABT::ToView(view));
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetRenderMode(ERENDER_MODE_TYPE renderMode)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setRenderMode((agora::media::base::RENDER_MODE_TYPE)renderMode);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAgoraBPuMediaPlayer::SetAudioDualMonoMode(EAUDIO_DUAL_MONO_MODE mode)
{
	if (MediaPlayer) {
		int ret = MediaPlayer->setAudioDualMonoMode((agora::media::base::AUDIO_DUAL_MONO_MODE)mode);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
FString UAgoraBPuMediaPlayer::GetPlayerSdkVersion()
{
    if (MediaPlayer) {
		return MediaPlayer->getPlayerSdkVersion();
	}
	return AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_NULLPTR];
}
FString UAgoraBPuMediaPlayer::GetPlaySrc()
{
	if (MediaPlayer) {
		return MediaPlayer->getPlaySrc();
	}
	return AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_NULLPTR];
}
int UAgoraBPuMediaPlayer::OpenWithAgoraCDNSrc(const FString& src, int64 startPos)
{
	if (MediaPlayer) {
		return MediaPlayer->openWithAgoraCDNSrc(TCHAR_TO_UTF8(*src), startPos);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetAgoraCDNLineCount()
{
	if (MediaPlayer) {
		return MediaPlayer->getAgoraCDNLineCount();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SwitchAgoraCDNLineByIndex(int index)
{
	if (MediaPlayer) {
		return MediaPlayer->switchAgoraCDNLineByIndex(index);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::GetCurrentAgoraCDNIndex()
{
	if (MediaPlayer) {
		return MediaPlayer->getCurrentAgoraCDNIndex();
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::EnableAutoSwitchAgoraCDN(bool enable)
{
	if (MediaPlayer) {
		return MediaPlayer->enableAutoSwitchAgoraCDN(enable);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::RenewAgoraCDNSrcToken(const FString& token, int64 ts)
{
	if (MediaPlayer) {
		return MediaPlayer->renewAgoraCDNSrcToken(TCHAR_TO_UTF8(*token), ts);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SwitchAgoraCDNSrc(const FString& src, bool syncPts)
{
	if (MediaPlayer) {
		return MediaPlayer->switchAgoraCDNSrc(TCHAR_TO_UTF8(*src), syncPts);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SwitchSrc(const FString& src, bool syncPts)
{
	if (MediaPlayer) {
		return MediaPlayer->switchSrc(TCHAR_TO_UTF8(*src), syncPts);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::PreloadSrc(const FString& src, int64 startPos)
{
	if (MediaPlayer) {
		return MediaPlayer->preloadSrc(TCHAR_TO_UTF8(*src), startPos);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::PlayPreloadedSrc(const FString& src)
{
	if (MediaPlayer) {
		return MediaPlayer->playPreloadedSrc(TCHAR_TO_UTF8(*src));
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::UnloadSrc(const FString& src)
{
	if (MediaPlayer) {
		return MediaPlayer->unloadSrc(TCHAR_TO_UTF8(*src));
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetSpatialAudioParams(const FSpatialAudioParams& params)
{
	if (MediaPlayer) {
		agora::SpatialAudioParams spatialAudioParams = params.CreateAgoraData();
		int ret = MediaPlayer->setSpatialAudioParams(spatialAudioParams);
		params.FreeAgoraData(spatialAudioParams);
		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}
int UAgoraBPuMediaPlayer::SetSoundPositionParams(float pan, float gain)
{
	if (MediaPlayer) {
		return MediaPlayer->setSoundPositionParams(pan, gain);
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

#pragma endregion Media Player