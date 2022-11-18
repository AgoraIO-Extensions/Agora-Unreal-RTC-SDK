# API-Blueprint-Example
## Overview

This project contains different scenes on how to integrate the Agora SDK APIs into your project.  You may run the project from the high level or go into a particular level to experience a single API example.

## Prerequisites
 1. Agora Developer Account
 2. Unreal Engine 4.27 or above (including UE5)
 3. Platform support

| Platform | IDE  | OS | Architecture|Note|
|--|--|--|--|--|
|  Android|  Android Studio 3.5.3 or above| [see Unreal Android requirement](https://docs.unrealengine.com/4.27/en-US/SharingAndReleasing/Mobile/Android/AndroidSDKRequirements/)|arm64-v8a, arneabi-v7a|Real devices only (not working on emulators); NDK version 21
|iOS|XCode 11.0 or above|[see Unreal IOS requirement](https://docs.unrealengine.com/4.27/en-US/SharingAndReleasing/Mobile/iOS/DeviceCompatibility/)|--|Valid Apple developer signature required
|MacOS|XCode 11.0 or above|OS X 10.11 or above|Intel, M1|same as above
|Windows 64bit|Visual Studio 2019|Windows 7 SP1 or above|Intel|Disk space: at least 1.64 GB of space after the IDE and relevant tools are installed
|Windows 32bit|Visual Studio 2019|Windows 7 SP1 or above|Intel|Unreal5 does not support it, so it is disabled by default in AgoraPluginLibrary.Build.cs, if you want to use, please uncomment it|


## Example Case

### Basic Case
- JoinChannelAudio
- JoinChannelVideo
### Advance Case
- DvicesManager
- JoinMultipleChannel
- MediaPlayer
- ScreenShare
- SendMultiCameraStream
- SpatialAudio
- StartRtmpStreamWithTranscoding
- StreamMessage
- SetEncryption
- CustomCaptureAudio(case only cpp)
- CustomCaptureVideo(case only cpp)
- CustomRenderAudio(case only cpp)
- ProcessAudioRawData(case only cpp)
- ProcessVideoRawData(case only cpp)



## Environment Requirements
- Unreal Engine 4.27.2 or above (Contain Unreal5)
- **Developing for Android:**
  - Android Studio 3.5.3 or above
  - Visual Studio 2017 15.6 or above
  - A real device for testing
- **Developing for iOS and macOS:**
  - Xcode 11.0 or above
  - OS X 10.11 or above
  - A valid developer signature for your project
- **Developing for Windows:**
    - OS: Windows 7 SP1 or above (64-bit based on x86-64)
    - Disk space: at least 1.64 GB of space after the IDE and relevant tools are installed
    - [Visual Studio 2019](https://visualstudio.microsoft.com/zh-hans/downloads/)


## Run Project

### Obtain an App ID

Before you can build and run any Agora project, you will need to add your AppID to the configuration. Go to your  [developer account’s project console](https://console.agora.io/projects), create a new AppId or copy the AppId from an existing project.

**Note**  it is important that for a production ready project, you should always use an AppId with token enabled. However, in testing a demo, you will skip this part. Using a testing mode AppId can save time for POC integration.

 ![Test Mode APPID](https://user-images.githubusercontent.com/1261195/110023464-11eb0480-7ce2-11eb-99d6-031af60715ab.png)

### Integrating the SDK

1. Download the SDK and its from [the Release area](https://github.com/AgoraIO-Extensions/Agora-Unreal-RTC-SDK-NG/releases).
2. Create a folder named *Plugins* in your project's root directory.  
3. Unzip the SDK files to *Plugins*

 ![plugins](https://user-images.githubusercontent.com/1261195/186286865-24d40426-4329-4ba1-b943-2626ce50d1b0.png)

### Compile and Run the Demo
You may run the demos at a high level loader or at any level of the individual API samples.

**1)  Running at a high level**
Compile the project and then hit the Play button on the UE Editor.  You should get a main  screen like the following:

![MainLevelPos](https://user-images.githubusercontent.com/47908151/202615511-b4ad613d-1bc8-45bf-b149-fdb00133adff.png)
![LevelImage](https://user-images.githubusercontent.com/47908151/202615260-35839bad-cd59-4f5e-a3de-4824a35640f1.jpg)

Fill in your App ID, Channel Name and optionally the token if you set up the application with certificate enabled.  You can now press a button to navigate to any of the API sample level.

2)  Open any level blueprint, for example Basic/joinChannelAudio/BasicAudioCall/ enter your appid and channelname in the position below.
  
![code_16613129312915](https://user-images.githubusercontent.com/47908151/202614467-6aa8bd6a-f9e6-4053-ba07-53c5fd2e5c8d.jpg)

## Making a Build (Project Packaging)

### Windows Packaging

File->Package Project->Windows->Windows(64-bit)

![windowspackage](https://user-images.githubusercontent.com/47908151/202615706-41df9c3e-0463-43eb-8fef-a8d154745976.jpg)

#### 32bit Windows
Since UE5 does not support 32-bit Windows, our plugin leave out the 32-bit implementation by default; otherwise, the compilation will result in error for UE5.  If you want to use the 32-bit build in UE4, please uncomment the win32 related code in AgoraPluginLibrary.Build.cs.  See this screenshot:

![code_16613129312915](https://user-images.githubusercontent.com/1261195/186325436-d8bf6543-5aea-4adc-a903-0199519339eb.png)

### MacOS Packaging

File -> Package Project -> Mac

#### Add device permissions to plist.info:

1. Right click the compiled xxx.app File - select "Show Package Contents"

![contextMenu_and_MacNoEditor](https://user-images.githubusercontent.com/1261195/186290440-ab80de0e-b87c-4a3a-a589-cc68960b6397.png)

2. Edit Contents/Info.plist (Double-click to open it in XCode,  then see Step 3 next; or Step 3b if using your favorite text editor).

3. Select "Information Property List" and add the following two permissions:

- Privacy - Camera Usage Description
- Privacy - Microphone Usage Description

![privacy_plist](https://user-images.githubusercontent.com/1261195/186293374-d550e36c-cd87-4feb-b79d-8344945af827.gif)

3b. Equivalent of editing with Xcode, you may just open the plist file with a text editor and paste the following XML snippet into it:
```xml
	<key>NSCameraUsageDescription</key>
	<string>Use camera</string>
	<key>NSMicrophoneUsageDescription</key>
	<string>Use mic</string>
```

#### Add the SDK frameworks

Copy ***.framework** from ***Plugs/AgoraPlugin/Source/ ThirdParty/Agora/MAC/Release*** to ***MacNoEditor/xxx/Contents/MacOS/*** .
![unrealMacPlugins](https://user-images.githubusercontent.com/1261195/186295172-9fea300b-77fc-4bfe-bb15-41f5727044a3.png)

### IOS Packaging
The following permissions are also required on iOS:

- Privacy - Camera Usage Description
- Privacy - Microphone Usage Description

To add the above permissions to the info.plist, you can enter them in the UE Editor.
1. **Copy the following single line text:**

```xml
<key>NSCameraUsageDescription</key><string>AgoraVideoCall</string><key>NSMicrophoneUsageDescription</key><string>AgoraVideoCall</string>
```
2. Open the screen at **Edit-> Project Settings->Platforms: iOS**
3. Enter the text to the "**additional plist data**" field:
<img width="936" alt="iOS_add_permission" src="https://user-images.githubusercontent.com/1261195/186298955-19949598-fcf8-46ac-8d8a-d0d0e320917c.png">


Finally, you can package the iOS project (*File->Package Project->iOS*).

Also iOS should add this Code to your target 

![iospackage2](https://user-images.githubusercontent.com/47908151/202614986-e641ac9b-de6a-40a6-b4e3-517651899c0a.jpg)

On the iOS platform, Unreal Engine uses the built-in Binned memory allocator by default. For related source code, please refer to FApplePlatformMemory::BaseAllocator().
Here, the global macro definition setting engine uses the standard C memory allocation method on the iOS platform, that is, directly calling malloc, free, realloc and other functions, so as to avoid some abnormal memory release problems when using the Agora plug-in on the iOS platform;

Regarding the performance difference between Ansi and Binned memory allocation: Binned's optimization of small memory usage is better than that of Ansi, but the overall memory usage will be higher, and the overall performance difference between the two is not obvious on mid-to-high-end iOS devices.

### Android Packaging
Build Android via "File -> Package Project -> Android".  Note **ASTC** is a more common target for modern Android devices.

On Android, the following permissions need to be applied.
1. android.permission.RECORD_AUDIO
2. android.permission.CAMERA
3. android.permission.READ_PHONE_STATE
4. android.permission.WRITE_EXTERNAL_STORAGE

The API-Examples provides sample code in doing so.  

the blueprint function is called to enable the permissions.
![code_16613129312915](https://user-images.githubusercontent.com/47908151/202613751-0e140839-3446-4d1b-bd56-48c4ceda5de8.jpg)



# FAQs

### What should I do if UE4 Editor crashes on MacOS?
Make sure you have added the following audio/video permissions to `info.plist` of **UE4Editor.app**.
```
<key>NSCameraUsageDescription</key>
<string>Video calls are possible only with camera permission.</string>
<key>NSMicrophoneUsageDescription</key>
<string>Audio calls are possible only with mic access.</string>
```
### The project is failing to open on MacOS, and from the Editor log, the follow error occured:
```
/Users/Shared/Epic Games/UE_4.27/Engine/Source/Runtime/Engine/Classes/Materials/Material.h:1279:26: error: variable 'LayerNames' set but not used [-Werror,-Wunused-but-set-variable]

const TArray<FText>* LayerNames = &LayersExpression->GetLayerNames();
^

1 error generated.
```
Edit Agora-Unreal-RTC-SDK-NG/Agora-Unreal-SDK-CPP-Example/Source/*.cs

Add lines to each script:
```
bOverrideBuildEnvironment = true;
AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
```

### When opening the project on MacOS, there are blocking errors on framework.  How to quickly get over this?
![framework](https://user-images.githubusercontent.com/1261195/186300244-e227f19f-eb11-43c7-a70b-3c289b6f7334.png)

Mac's Gatekeeper blocks unsigned frameworks and you have to unblock them one by one.  If your environment is safe, you can temporarily allow Apps to run from Anywhere.  See this checkbox in System Preferences:
![Security___Privacy](https://user-images.githubusercontent.com/1261195/186300847-b8c88971-371f-4a6a-b216-2189bd14d57f.png)


### What should I do for the error "failed to load because module 'AgoraPlugin' could not be loaded" ?

![import_error](https://user-images.githubusercontent.com/1261195/186298361-6e4e0007-0a7e-43f8-8338-1033e99a3e92.png)

Try deleting the [Binaries] folder in your project

### Why can't I see the shared screen in the ScreenShare case on MacOS ?

Make sure you have accepted or added "Screen Recording" permission for the App (and the UE Editor) in your Mac Security and Privacy setting.


# Connect With Us
- If you have any questions, create an issue [here](https://github.com/AgoraIO-Extensions/Agora-Unreal-SDK-CPP-NG/issues).
- You can find full API document at [Document Center](https://docs.agora.io/en/)
