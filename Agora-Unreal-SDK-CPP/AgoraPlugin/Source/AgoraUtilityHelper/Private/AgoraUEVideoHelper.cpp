//  Copyright (c) 2024 Agora.io. All rights reserved.

#include "AgoraUEVideoHelper.h"

#include "IMediaPlayer.h"
#include "MediaPlayerFacade.h"
#include "MediaPlayer.h"


IMediaSamples& UEVideoMediaPlayer::GetSamples(UMediaPlayer* MediaPlayer)
{
	TSharedRef<FMediaPlayerFacade, ESPMode::ThreadSafe>  PlayerFacade = MediaPlayer->GetPlayerFacade();

	// Agora has a agora::rtc::IMediaPlayer interface
	TSharedPtr<::IMediaPlayer, ESPMode::ThreadSafe> IPlayer = PlayerFacade->GetPlayer();

	return IPlayer->GetSamples();
}

