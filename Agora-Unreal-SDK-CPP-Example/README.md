# Agora Unreal C++ SDK API-Example
## Overview

This project contains different scenes on how to integrate the Agora SDK APIs into your project.  You may run the project from the high level or go into a particular level to experience a single API example.

## Prerequisites
- An Agora [account](https://docs.agora.io/en/video-calling/reference/manage-agora-account#create-an-agora-account) and [project](https://docs.agora.io/en/video-calling/reference/manage-agora-account#create-an-agora-project).
- Unreal Engine 4.27 or above (including UE5)
- Platform support

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


## Project setup

### Get the App ID

Before you build and run your project, you need to get the App ID. To copy this App ID, find your project on the [Project Management](https://console.agora.io/projects) page in Agora Console, and click the copy icon in the App ID column.

Get the App Certificate
When generating a token on your app server, you need to fill in parameters such as the App ID, channel name, user ID, and App Certificate.

To get an App Certificate, do the following:  

1. On the [Project Management](https://console.agora.io/projects) page, click **Config** for the project you want to use.  
2. Click the copy icon under Primary Certificate.   
	
### Generate a temporary token
When a user attempts to join a channel, your app passes an encrypted authentication token to Agora SD-RTN™. This token is unique for each channel. It is generated using the App ID of your project and the channel name. In a test or production environment, your app retrieves the token from a token server. However, for local testing, you can generate a temporary token in Agora Console.

1. In Agora Console, open [Project Management](https://console.agora.io/projects), select your project, and click **Config**.  
2. Under Features, click **Generate temp Video SDK token**.  
3. Type the channel name, then click **Generate**.  
   Agora Console generates a token valid to join that channel only.
4. Click Copy.  
   The temporary token is added to the clipboard of your development machine.

	
### Integrating the SDK

1. Download the [SDK](https://github.com/AgoraIO-Extensions/Agora-Unreal-RTC-SDK-NG/releases).  
2. Create a folder named Plugins in the root directory of your project.  
3. Unzip the SDK files to *Plugins*

 ![plugins](https://user-images.githubusercontent.com/1261195/186286865-24d40426-4329-4ba1-b943-2626ce50d1b0.png)


### Compile and Run the Demo  
1.Compile and run the project in the main level, and then click the Play button on the UE Editor. You see the main screen as shown in the following image:

![AgoraExample_-_Unreal_Editor](https://user-images.githubusercontent.com/1261195/186287084-9d462257-93eb-4913-b6fa-cba892de004e.png)

Fill in your App ID, channel name, and token (optional). You can now click a button on the left to navigate to a particular level of the API examples.  
2.Run in a particular level if you want experience an API example. Take *Basic/joinChannelAudio/BasicAudioCall/* as an example:
 1. Find a blueprint named BP_Agoractor in the World outliner.
 2. Fill in your App ID and channel name below the BP_Agoractor.

![Sample-PlayAudio](https://user-images.githubusercontent.com/1261195/186288166-50bb7c3f-66e2-4b88-a0de-df2ab2ac19af.gif)

## Project Packaging



### Windows Packaging

File->Package Project->Windows->Windows(64-bit)

![windowspackage](https://user-images.githubusercontent.com/47908151/202615706-41df9c3e-0463-43eb-8fef-a8d154745976.jpg)

#### 32bit Windows
Since UE5 does not support 32-bit Windows, the Agora plugin omits the 32-bit implementation by default. If you want to use 32-bit Windows with UE4, uncomment the code relating to Win32 in the **AgoraPluginLibrary.Build.cs** file, as shown in the red box in the following image:

![code_16613129312915](https://user-images.githubusercontent.com/1261195/186325436-d8bf6543-5aea-4adc-a903-0199519339eb.png)

### MacOS Packaging

1. Click File > Package Project > Mac.

2. Add device permissions to plist.info

	a. Right click the compiled xxx.app File - select "Show Package Contents"

![contextMenu_and_MacNoEditor](https://user-images.githubusercontent.com/1261195/186290440-ab80de0e-b87c-4a3a-a589-cc68960b6397.png)

b. Edit Contents/Info.plist (Double-click to open it in XCode,  then see Step 3 next; or Step 3b if using your favorite text editor).

3. Add permissions.

Double click to open *Contents/Info.plist* in XCode, then click **Information Property List** to add the following permissions:

- Privacy - Camera Usage Description
- Privacy - Microphone Usage Description

![privacy_plist](https://user-images.githubusercontent.com/1261195/186293374-d550e36c-cd87-4feb-b79d-8344945af827.gif)

If you are editing with Xcode, you can just open the plist file with a text editor and paste the following XML snippet into it:
```xml
	<key>NSCameraUsageDescription</key>
	<string>Use camera</string>
	<key>NSMicrophoneUsageDescription</key>
	<string>Use mic</string>
```

4. Add the SDK frameworks.

Copy ***.framework** from ***Plugs/AgoraPlugin/Source/ ThirdParty/Agora/MAC/Release*** to ***MacNoEditor/xxx/Contents/MacOS/*** .
![unrealMacPlugins](https://user-images.githubusercontent.com/1261195/186295172-9fea300b-77fc-4bfe-bb15-41f5727044a3.png)

### IOS Packaging
The following permissions are also required on iOS:

- Privacy - Camera Usage Description
- Privacy - Microphone Usage Description

To add the above permissions to the info.plist, you can enter them in the UE Editor.
1. Copy the following single line text:

```xml
<key>NSCameraUsageDescription</key><string>AgoraVideoCall</string><key>NSMicrophoneUsageDescription</key><string>AgoraVideoCall</string>
```
2. Click Edit > Project Settings >Platforms > iOS.
3. Enter the text to the "**additional plist data**" field:
<img width="936" alt="iOS_add_permission" src="https://user-images.githubusercontent.com/1261195/186298955-19949598-fcf8-46ac-8d8a-d0d0e320917c.png">


You can package the iOS project (File > Package Project > iOS).

iOS should add the following code to your target as well:

![iospackage2](https://user-images.githubusercontent.com/47908151/202614986-e641ac9b-de6a-40a6-b4e3-517651899c0a.jpg)

On the iOS platform, Unreal Engine uses the built-in Binned memory allocator by default. For related source code, please refer to FApplePlatformMemory::BaseAllocator().
Here, the global macro definition setting engine uses the standard C memory allocation method on the iOS platform, that is, directly calling malloc, free, realloc and other functions, so as to avoid some abnormal memory release problems when using the Agora plug-in on the iOS platform;

Regarding the performance difference between Ansi and Binned memory allocation: Binned's optimization of small memory usage is better than that of Ansi, but the overall memory usage will be higher, and the overall performance difference between the two is not obvious on mid-to-high-end iOS devices.

### Android Packaging
Build Android via File > Package Project > Android. Note that ASTC is a more common target for modern Android devices.

On Android, the following permissions need to be applied:

- android.permission.RECORD_AUDIO
- android.permission.CAMERA
- android.permission.READ_PHONE_STATE
- android.permission.WRITE_EXTERNAL_STORAGE

Take AgoraVideoWidget.cpp as an example, the following function is called to enable the permissions.

```cpp
void UAgoraVideoWidget::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
	FString pathfromName = UGameplayStatics::GetPlatformName();
	if (pathfromName == "Android")
	{
		TArray<FString> AndroidPermission;
		AndroidPermission.Add(FString("android.permission.CAMERA"));
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}
```



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
