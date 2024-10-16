//  Copyright (c) 2023 Agora.io. All rights reserved.

#pragma once


#include "Runtime/Launch/Resources/Version.h"
#define AG_UE_5_4_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 4) 
#define AG_UE_5_3_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
#define AG_UE_5_2_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2) 
#define AG_UE_5_1_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
#define AG_UE5_OR_LATER   (ENGINE_MAJOR_VERSION == 5)

// For compiling the plugin independently using UAT's BuildPlugin command
#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif

#include <AgoraCppPlugin/IAgoraMediaComponentFactory.h>
#include <AgoraCppPlugin/IAgoraMediaEngine.h>
#include <AgoraCppPlugin/IAgoraMediaPlayer.h>
#include <AgoraCppPlugin/IAgoraMediaPlayerSource.h>
#include <AgoraCppPlugin/IAgoraMediaStreamingSource.h>
#include <AgoraCppPlugin/IAgoraRtcEngineEx.h>
#include <AgoraCppPlugin/IAgoraSpatialAudio.h>
#include <AgoraCppPlugin/IAudioDeviceManager.h>
#include <AgoraCppPlugin/IAgoraMediaRecorder.h>



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


// For UE4.25 or older versions - Target Platforms like: Android, define CONSTEXPR back
// Currently AgoraOptional.h would undefine CONSTEXPR at the end of the file.
// This issue would be resolved in a later SDK version.

#ifndef CONSTEXPR
#if __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif
#endif  // !CONSTEXPR