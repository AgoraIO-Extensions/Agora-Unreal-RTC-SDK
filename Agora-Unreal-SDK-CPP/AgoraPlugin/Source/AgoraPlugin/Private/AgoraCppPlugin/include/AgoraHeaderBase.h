#pragma once

#include <AgoraCppPlugin/IAgoraMediaComponentFactory.h>
#include <AgoraCppPlugin/IAgoraMediaEngine.h>
#include <AgoraCppPlugin/IAgoraMediaPlayer.h>
#include <AgoraCppPlugin/IAgoraMediaPlayerSource.h>
#include <AgoraCppPlugin/IAgoraMediaStreamingSource.h>
#include <AgoraCppPlugin/IAgoraRtcEngineEx.h>
#include <AgoraCppPlugin/IAgoraSpatialAudio.h>
#include <AgoraCppPlugin/IAudioDeviceManager.h>
#include <AgoraCppPlugin/IAgoraMediaRecorder.h>

// additional
#include <AgoraCppPlugin/IAgoraMusicContentCenter.h>

enum AGORA_UNREAL_PLUGIN_ERROR_CODE
{
	ERROR_OK = 0,
	ERROR_NULLPTR = 1999,
	ENGINE_PROXY_NOT_CREATED = 2000,


	// videoRenderModule
	CACHE_MANAGER_NOT_ENABLE = 2001,
	VIDEO_FRAME_BUFFER_EMPTY = 2002,

};


enum AppType {
	kAppTypeNative = 0,
	kAppTypeCocos = 1,
	kAppTypeUnity = 2,
	kAppTypeElectron = 3,
	kAppTypeFlutter = 4,
	kAppTypeUnreal = 5,
	kAppTypeXamarin = 6,
	kAppTypeApiCloud = 7,
	kAppTypeReactNative = 8,
	kAppTypePython = 9,
	kAppTypeCocosCreator = 10,
	kAppTypeRust = 11,
	kAppTypeCSharp = 12,
	kAppTypeCef = 13,
	kAppTypeUniApp = 14,
};