
This page introduces the main steps to upgrade the [Unreal C++ SDK](https://github.com/AgoraIO-Community/Agora-Unreal-SDK) from v3.x (v3.5.0.4) to v4.x, as well as the related changes.

### 1. Integrate the SDK

To integrate Video SDK for Unreal Engine v4.2.1 into your project, see [Project setup](https://docs-beta.agora.io/en/interactive-live-streaming/get-started/get-started-sdk?platform=unreal#project-setup).

### 2. Update the Agora code in your app

This section explains the main changes between Video SDK for Unreal Engine v3.x and v4.x. Use this information to upgrade your app.

**Basic changes**

Video SDK for Unreal Engine v4.x is based on Video SDK for C++ v4.x. First follow the steps in [Migrate from Video SDK 3.x]().

**Other changes**
- The `agora::rtc::ue4::AgoraRtcEngine*` interface class is renamed to `agora::rtc::ue::RtcEngineProxy*`. Rename `agora::rtc::ue4::AgoraRtcEngine*` to `agora::rtc::ue::RtcEngineProxy*` in your app.
- The v4.x SDK simplifies the implementation steps for video rendering. The `OnTick` function is handled by the `VideoRenderingManager`. Remove all code related to `OnTick` from your project files.
- To directly import Video SDK for Unreal Engine v4.x objects, include `AgoraPluginInterface.h` into all your classes. You may also need `AgoraPlugin\Private\AgoraCppPlugin\include\AgoraHeaderBase.h`.
