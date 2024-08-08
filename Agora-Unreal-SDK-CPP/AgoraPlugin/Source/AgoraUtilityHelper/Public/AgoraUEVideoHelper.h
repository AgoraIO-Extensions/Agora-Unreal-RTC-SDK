// Copyright(c) 2024 Agora.io.All rights reserved.

#pragma once


class UMediaPlayer;
class IMediaSamples;

// the reason for making a new module is:
// agora has agora::rtc::IMediaPlayer interface, UE also has this one, but it doesn't have a namespace for it.
// Inside the FMediaPlayerFacade, it has a class forward declaration of IMediaPlayer, which would cause ambiguious symbol error.

class AGORAUTILITYHELPER_API UEVideoMediaPlayer {


public:

	static IMediaSamples& GetSamples(UMediaPlayer* MediaPlayer);

};