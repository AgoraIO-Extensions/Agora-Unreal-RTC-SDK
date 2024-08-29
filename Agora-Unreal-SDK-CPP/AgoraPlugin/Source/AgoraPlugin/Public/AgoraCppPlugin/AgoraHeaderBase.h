//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"
#define AG_UE_5_4_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 4) 
#define AG_UE_5_3_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
#define AG_UE_5_2_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2)
#define AG_UE_5_1_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
#define AG_UE5_OR_LATER   (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 0)

// For compiling the plugin independently using UAT's BuildPlugin command
#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif


#if AG_UE_5_4_OR_LATER
// remove UE_DEPRECATED_MACRO deprecated warning
#undef CONSTEXPR
#define CONSTEXPR constexpr 
#endif

THIRD_PARTY_INCLUDES_START
#include <AgoraCppPlugin/include/IAgoraMediaComponentFactory.h>
#include <AgoraCppPlugin/include/IAgoraMediaEngine.h>
#include <AgoraCppPlugin/include/IAgoraMediaPlayer.h>
#include <AgoraCppPlugin/include/IAgoraMediaPlayerSource.h>
#include <AgoraCppPlugin/include/IAgoraMediaStreamingSource.h>
#include <AgoraCppPlugin/include/IAgoraRtcEngineEx.h>
#include <AgoraCppPlugin/include/IAgoraSpatialAudio.h>
#include <AgoraCppPlugin/include/IAudioDeviceManager.h>
#include <AgoraCppPlugin/include/IAgoraMediaRecorder.h>

// additional
#include <AgoraCppPlugin/include/IAgoraMusicContentCenter.h>
THIRD_PARTY_INCLUDES_END

#define AGORA_UE_ERR_CODE(ERROR_TYPE) (-static_cast<int>(AGORA_UE_ERROR_CODE::ERROR_TYPE))
#define AGORA_GET_ERR_TYPE(CODE) (static_cast<AGORA_UE_ERROR_CODE>(-CODE))


enum class AGORA_UE_ERROR_CODE 
{
	ERROR_OK = 0,
	ERROR_NULLPTR = 12,
	ERROR_NOT_SUPPORT_PLATFORM = 13,
	ERROR_VIDEO_NOT_ENABLED = 14,

	// VideoRenderError
	ERROR_RENDER_NULL_FRAME = 15,
	ERROR_RENDER_NULL_BUFFER = 16,
	ERROR_RENDER_BUFFER_STOP_UPDATEING =17,
	ERROR_RENDER_NO_NEW_FRAME_DATA = 18,

	// BP
	ERROR_BP_RTC_ENGINE_NOT_INITIALIZED = 50,

};


enum class AgoraAppType {
	kAppTypeNative = 0,
	kAppTypeCocos = 1,
	kAppTypeUnity = 2,
	kAppTypeElectron = 3,
	kAppTypeFlutter = 4,
	kAppTypeUnreal = 5, // Unreal Engine Cpp Version
	kAppTypeXamarin = 6,
	kAppTypeApiCloud = 7,
	kAppTypeReactNative = 8,
	kAppTypePython = 9,
	kAppTypeCocosCreator = 10,
	kAppTypeRust = 11,
	kAppTypeCSharp = 12,
	kAppTypeCef = 13,
	kAppTypeUniApp = 14,
	//kAppTypeUnrealBlueprint = 15, // Unreal Engine Blueprint Version
};


// For UE4.25 or older versions - Target Platforms like: Android, define CONSTEXPR back
// Currently AgoraOptional.h would undefine CONSTEXPR at the end of the file.
// This issue would be resolved in a later SDK version.

#ifndef CONSTEXPR
#if __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
#define CONSTEXPR constexpr
#endif
#endif  // !CONSTEXPR