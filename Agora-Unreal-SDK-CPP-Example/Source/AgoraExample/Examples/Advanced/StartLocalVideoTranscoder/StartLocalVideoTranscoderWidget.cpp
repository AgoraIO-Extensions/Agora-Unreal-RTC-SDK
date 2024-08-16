// Copyright(c) 2024 Agora.io. All rights reserved.


#include "StartLocalVideoTranscoderWidget.h"

void UStartLocalVideoTranscoderWidget::InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	LogMsgViewPtr = UBFL_Logger::CreateLogView(CanvasPanel_LogMsgView, DraggableLogMsgViewTemplate);

	CheckPermission();

	InitAgoraEngine(APP_ID, TOKEN, CHANNEL_NAME);

	ShowUserGuide();

	InitAgoraMediaPlayer();

	JoinChannel();
}




void UStartLocalVideoTranscoderWidget::CheckPermission()
{
#if PLATFORM_ANDROID
	FString TargetPlatformName = UGameplayStatics::GetPlatformName();
	if (TargetPlatformName == "Android")
	{
		TArray<FString> AndroidPermission;
#if !AGORA_UESDK_AUDIO_ONLY || (!(PLATFORM_ANDROID || PLATFORM_IOS))
		AndroidPermission.Add(FString("android.permission.CAMERA"));
#endif
		AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
		AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
		AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
		UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
	}
#endif
}


void UStartLocalVideoTranscoderWidget::InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME)
{
	agora::rtc::RtcEngineContext RtcEngineContext;

	UserRtcEventHandlerEx = MakeShared<FUserRtcEventHandlerEx>(this);
	std::string StdStrAppId = TCHAR_TO_UTF8(*APP_ID);
	RtcEngineContext.appId = StdStrAppId.c_str();
	RtcEngineContext.eventHandler = UserRtcEventHandlerEx.Get();
	RtcEngineContext.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_LIVE_BROADCASTING;

	AppId = APP_ID;
	Token = TOKEN;
	ChannelName = CHANNEL_NAME;


	int SDKBuild = 0;
	const char* SDKVersionInfo = AgoraUERtcEngine::Get()->getVersion(&SDKBuild);
	FString SDKInfo = FString::Printf(TEXT("SDK Version: %s Build: %d"), UTF8_TO_TCHAR(SDKVersionInfo), SDKBuild);
	UBFL_Logger::Print(FString::Printf(TEXT("SDK Info:  %s"), *SDKInfo), LogMsgViewPtr);

	int ret = AgoraUERtcEngine::Get()->initialize(RtcEngineContext);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}

void UStartLocalVideoTranscoderWidget::ShowUserGuide()
{
	FString Guide =
		"Case: [StartLocalVideoTranscoder]\n"
		"1. Combine multiple video streams into one stream (e.g., Video Call, Screen Share, Media Player, Images, etc.).\n"
		"";

	UBFL_Logger::DisplayUserGuide(Guide, LogMsgViewPtr);
}

void UStartLocalVideoTranscoderWidget::InitAgoraMediaPlayer()
{
	MediaPlayer = AgoraUERtcEngine::Get()->createMediaPlayer();
	MediaPlayerSourceObserverWarpper = MakeShared<FUserIMediaPlayerSourceObserver>(this);
	MediaPlayer->registerPlayerSourceObserver(MediaPlayerSourceObserverWarpper.Get());
	UBFL_Logger::Print(FString::Printf(TEXT("%s PlayerID=%d"), *FString(FUNCTION_MACRO), MediaPlayer->getMediaPlayerId()), LogMsgViewPtr);

}

void UStartLocalVideoTranscoderWidget::JoinChannel()
{
	AgoraUERtcEngine::Get()->enableAudio();
	AgoraUERtcEngine::Get()->enableVideo();
	AgoraUERtcEngine::Get()->setClientRole(CLIENT_ROLE_BROADCASTER);
	MakeVideoView(0, VIDEO_SOURCE_TYPE::VIDEO_SOURCE_TRANSCODED, "");

	agora::rtc::ChannelMediaOptions ChannelMediaOptions;
	ChannelMediaOptions.publishCameraTrack = false;
	ChannelMediaOptions.publishSecondaryCameraTrack = false;
	ChannelMediaOptions.publishTranscodedVideoTrack = true;
	int ret = AgoraUERtcEngine::Get()->joinChannel(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*ChannelName), 0, ChannelMediaOptions);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}



void UStartLocalVideoTranscoderWidget::OnBtnStartClicked()
{
	LocalTranscoderConfiguration Config = GenerateLocalTranscoderConfiguration();
	int ret = AgoraUERtcEngine::Get()->startLocalVideoTranscoder(Config);
	ReleaseLocalTranscoderConfiguration(Config);
	UBFL_Logger::Print(FString::Printf(TEXT("%s startLocalVideoTranscoder ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	agora::rtc::ChannelMediaOptions options;
	options.publishCameraTrack = false;
	options.publishSecondaryCameraTrack = false;
	options.publishTranscodedVideoTrack = true;
	AgoraUERtcEngine::Get()->updateChannelMediaOptions(options);

	return;

}

void UStartLocalVideoTranscoderWidget::OnBtnUpdateClicked()
{
	LocalTranscoderConfiguration Config = GenerateLocalTranscoderConfiguration();
	int ret = AgoraUERtcEngine::Get()->updateLocalTranscoderConfiguration(Config);
	ReleaseLocalTranscoderConfiguration(Config);
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


void UStartLocalVideoTranscoderWidget::OnBtnStopClicked()
{
	if (CB_MediaPlay->GetCheckedState() == ECheckBoxState::Checked) {
		MediaPlayer->stop();
	}

	int ret = AgoraUERtcEngine::Get()->stopLocalVideoTranscoder();
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
}


agora::rtc::LocalTranscoderConfiguration UStartLocalVideoTranscoderWidget::GenerateLocalTranscoderConfiguration()
{
	TArray<TranscodingVideoStream> List;

	if (CB_PrimaryCamera->GetCheckedState() == ECheckBoxState::Checked)
	{

		CameraCapturerConfiguration Configuration;
		bool bSuccess = true;

#if PLATFORM_ANDROID || PLATFORM_IOS
		Configuration.cameraDirection = CAMERA_DIRECTION::CAMERA_FRONT;
#else 
		agora::rtc::IVideoDeviceManager* VideoDeviceManager = nullptr;
		AgoraUERtcEngine::Get()->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);
		IVideoDeviceCollection* VideoDeviceInfos = VideoDeviceManager->enumerateVideoDevices();
		if (VideoDeviceInfos->getCount() >= 1)
		{
			Configuration.format = VideoFormat(640, 320, 30);

			// Get camera information
			VideoDeviceInfos->getDevice(0, MainCameraDeviceName, MainCameraDeviceId);
			Configuration.deviceId = MainCameraDeviceId;
		}
		else
		{

			UBFL_Logger::PrintError(FString::Printf(TEXT("%s startCameraCapture PRIMARY_CAMERA Not Found!"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
			bSuccess = false;
		}
#endif

		if (bSuccess) {
			int ret = AgoraUERtcEngine::Get()->startCameraCapture(VIDEO_SOURCE_CAMERA_PRIMARY, Configuration);
			UBFL_Logger::Print(FString::Printf(TEXT("%s startCameraCapture ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
			TranscodingVideoStream TranscodingVideoStreamConfig;
			TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_CAMERA;
			TranscodingVideoStreamConfig.x = 0;
			TranscodingVideoStreamConfig.y = 0;
			TranscodingVideoStreamConfig.width = 640;
			TranscodingVideoStreamConfig.height = 320;
			TranscodingVideoStreamConfig.zOrder = 1;
			List.Add(TranscodingVideoStreamConfig);
		}

	}


	if (CB_SecondaryCamera->GetCheckedState() == ECheckBoxState::Checked)
	{

		CameraCapturerConfiguration Configuration;
		bool bSuccess = true;

#if PLATFORM_ANDROID || PLATFORM_IOS
		Configuration.cameraDirection = CAMERA_DIRECTION::CAMERA_REAR;
#else 

		agora::rtc::IVideoDeviceManager* VideoDeviceManager = nullptr;
		AgoraUERtcEngine::Get()->queryInterface(agora::rtc::INTERFACE_ID_TYPE::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&VideoDeviceManager);
		IVideoDeviceCollection* VideoDeviceInfos = VideoDeviceManager->enumerateVideoDevices();
		if (VideoDeviceInfos->getCount() >= 2)
		{

			Configuration.format = VideoFormat(640, 320, 30);

			// Get camera information
			VideoDeviceInfos->getDevice(1, SecondCameraDeviceName, SecondCameraDeviceId);
			Configuration.deviceId = SecondCameraDeviceId;

		}
		else
		{
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s startCameraCapture CB_SecondaryCamera Not Found!"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
			bSuccess = false;
		}

#endif

		if (bSuccess) {

			int ret = AgoraUERtcEngine::Get()->startCameraCapture(VIDEO_SOURCE_CAMERA_SECONDARY, Configuration);
			UBFL_Logger::Print(FString::Printf(TEXT("%s startCameraCapture VIDEO_SOURCE_CAMERA_SECONDARY ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
			TranscodingVideoStream TranscodingVideoStreamConfig;
			TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_CAMERA_SECONDARY;
			TranscodingVideoStreamConfig.x = 360;
			TranscodingVideoStreamConfig.y = 0;
			TranscodingVideoStreamConfig.width = 360;
			TranscodingVideoStreamConfig.height = 240;
			TranscodingVideoStreamConfig.zOrder = 1;
			List.Add(TranscodingVideoStreamConfig);

		}
	}


	if (CB_PNG->GetCheckedState() == ECheckBoxState::Checked)
	{
		FString Path = FPaths::ProjectContentDir() / TEXT("Image/png.png");

		if (!FPaths::FileExists(Path)) {
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s PNG Path[%s] is not valid"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
		else
		{
			UBFL_Logger::Print(FString::Printf(TEXT("%s PNG Path[%s]"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}

		TranscodingVideoStream TranscodingVideoStreamConfig;
		TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_RTC_IMAGE_PNG;

#if PLATFORM_ANDROID || PLATFORM_IOS
		UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);

		FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.png");
		ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
		UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
		UBFL_UtilityTool::CreateMediaFileWithSource(Path, ValSavedFilePath);
		Path = ValSavedFilePath;
#endif 

		int Size = Path.Len() + 1;
		char* URLDataPtr = new char[Size];
		FMemory::Memcpy(URLDataPtr, TCHAR_TO_UTF8(*Path), Size);
		TranscodingVideoStreamConfig.imageUrl = URLDataPtr;

		TranscodingVideoStreamConfig.x = 320;
		TranscodingVideoStreamConfig.y = 180;
		TranscodingVideoStreamConfig.width = 640;
		TranscodingVideoStreamConfig.height = 360;
		TranscodingVideoStreamConfig.zOrder = 1;
		List.Add(TranscodingVideoStreamConfig);
	}

	if (CB_JPG->GetCheckedState() == ECheckBoxState::Checked)
	{
		FString Path = FPaths::ProjectContentDir() / TEXT("Image/jpg.jpg");

		if (!FPaths::FileExists(Path)) {
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s JPG Path[%s] is not valid"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
		else
		{
			UBFL_Logger::Print(FString::Printf(TEXT("%s JPG Path[%s]"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}

		TranscodingVideoStream TranscodingVideoStreamConfig;
		TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_RTC_IMAGE_JPEG;

#if PLATFORM_ANDROID || PLATFORM_IOS
		UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);

		FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.jpg");
		ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
		UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
		UBFL_UtilityTool::CreateMediaFileWithSource(Path, ValSavedFilePath);
		Path = ValSavedFilePath;
#endif 

		int Size = Path.Len() + 1;
		char* URLDataPtr = new char[Size];
		FMemory::Memcpy(URLDataPtr, TCHAR_TO_UTF8(*Path), Size);
		TranscodingVideoStreamConfig.imageUrl = URLDataPtr;

		TranscodingVideoStreamConfig.x = 360;
		TranscodingVideoStreamConfig.y = 240;
		TranscodingVideoStreamConfig.width = 360;
		TranscodingVideoStreamConfig.height = 240;
		TranscodingVideoStreamConfig.zOrder = 1;
		List.Add(TranscodingVideoStreamConfig);
	}


	if (CB_GIF->GetCheckedState() == ECheckBoxState::Checked)
	{
		FString Path = FPaths::ProjectContentDir() / TEXT("Image/gif.gif");

		if (!FPaths::FileExists(Path)) {
			UBFL_Logger::PrintError(FString::Printf(TEXT("%s GIF Path[%s] is not valid"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}
		else
		{
			UBFL_Logger::Print(FString::Printf(TEXT("%s GIF Path[%s]"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);
		}

		TranscodingVideoStream TranscodingVideoStreamConfig;
		TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_RTC_IMAGE_GIF;

#if PLATFORM_ANDROID || PLATFORM_IOS
		UBFL_Logger::Print(FString::Printf(TEXT("%s SrcPath=%s"), *FString(FUNCTION_MACRO), *Path), LogMsgViewPtr);

		FString ValSavedFilePath = FPaths::ProjectSavedDir() / TEXT("Tmp.gif");
		ValSavedFilePath = UBFL_UtilityTool::ConvertToAbsolutePath(ValSavedFilePath, false);
		UBFL_Logger::Print(FString::Printf(TEXT("%s DstPath=%s"), *FString(FUNCTION_MACRO), *ValSavedFilePath), LogMsgViewPtr);
		UBFL_UtilityTool::CreateMediaFileWithSource(Path, ValSavedFilePath);
		Path = ValSavedFilePath;
#endif 

		int Size = Path.Len() + 1;
		char* URLDataPtr = new char[Size];
		FMemory::Memcpy(URLDataPtr, TCHAR_TO_UTF8(*Path), Size);
		TranscodingVideoStreamConfig.imageUrl = URLDataPtr;

		TranscodingVideoStreamConfig.x = 0;
		TranscodingVideoStreamConfig.y = 0;
		TranscodingVideoStreamConfig.width = 476;
		TranscodingVideoStreamConfig.height = 280;
		TranscodingVideoStreamConfig.zOrder = 1;
		List.Add(TranscodingVideoStreamConfig);
	}
	if (CB_ScreenShare->GetCheckedState() == ECheckBoxState::Checked) {
		StartScreenShare();

		TranscodingVideoStream TranscodingVideoStreamConfig;
		TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_SCREEN_PRIMARY;
		TranscodingVideoStreamConfig.x = 480;
		TranscodingVideoStreamConfig.y = 640;
		TranscodingVideoStreamConfig.width = 640;
		TranscodingVideoStreamConfig.height = 320;
		TranscodingVideoStreamConfig.zOrder = 1;
		List.Add(TranscodingVideoStreamConfig);
	}

	if (CB_MediaPlay->GetCheckedState() == ECheckBoxState::Checked) {
		MediaPlayer->stop();
		int ret = MediaPlayer->open("https://big-class-test.oss-cn-hangzhou.aliyuncs.com/61102.1592987815092.mp4", 0);
		int PlayerID = MediaPlayer->getMediaPlayerId();

		TranscodingVideoStream TranscodingVideoStreamConfig;
		TranscodingVideoStreamConfig.sourceType = VIDEO_SOURCE_MEDIA_PLAYER;
		TranscodingVideoStreamConfig.mediaPlayerId = PlayerID;
		TranscodingVideoStreamConfig.width = 1080;
		TranscodingVideoStreamConfig.height = 960;
		TranscodingVideoStreamConfig.zOrder = 1;
		List.Add(TranscodingVideoStreamConfig);
	}
	else {
		MediaPlayer->stop();
	}

	LocalTranscoderConfiguration Config;
	Config.streamCount = List.Num();
	Config.videoInputStreams = new TranscodingVideoStream[List.Num()];
	FMemory::Memcpy(Config.videoInputStreams, List.GetData(), sizeof(TranscodingVideoStream) * List.Num());

	Config.videoOutputConfiguration.dimensions = VideoDimensions(1080, 960);
	return Config;
}

void UStartLocalVideoTranscoderWidget::ReleaseLocalTranscoderConfiguration(LocalTranscoderConfiguration& Config)
{
	if (Config.videoInputStreams) {
		for (unsigned int i = 0; i < Config.streamCount; i++) {
			if (Config.videoInputStreams[i].imageUrl) {
				delete[] Config.videoInputStreams[i].imageUrl;
				Config.videoInputStreams[i].imageUrl = nullptr;
			}
		}
		delete[] Config.videoInputStreams;
		Config.videoInputStreams = nullptr;
	}
}

int UStartLocalVideoTranscoderWidget::StartScreenShare()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	ScreenCaptureParameters2 parameters2;
	parameters2.captureAudio = true;
	parameters2.captureVideo = true;
	auto ret = AgoraUERtcEngine::Get()->startScreenCapture(parameters2);
	UE_LOG(LogTemp, Warning, TEXT("StartScreenShrareClick JoinChannel ====== %d"), ret);
#else
	AgoraUERtcEngine::Get()->stopScreenCapture();
	agora::rtc::ScreenCaptureParameters capParam;
	VideoDimensions dimensions(640, 360);
	capParam.dimensions = dimensions;
	capParam.bitrate = 800;
	capParam.frameRate = 15;
	capParam.enableHighLight = false;
	capParam.windowFocus = false;
	capParam.captureMouseCursor = false;
	const agora::rtc::Rectangle regionRect;
#if PLATFORM_WINDOWS
	SIZE size;
	size.cx = 360;
	size.cy = 240;
#else
	agora::rtc::SIZE size;
	size.width = 360;
	size.height = 240;
#endif
	agora::rtc::IScreenCaptureSourceList* infos = AgoraUERtcEngine::Get()->getScreenCaptureSources(size, size, true);
	if (infos == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetScreenDisplay is null"));
		return -1;
	}
	agora::rtc::ScreenCaptureSourceInfo info = infos->getSourceInfo(0);
	int ret = -1;
	if (info.type == agora::rtc::ScreenCaptureSourceType_Screen)
	{
		ret = AgoraUERtcEngine::Get()->startScreenCaptureByDisplayId((uint64)(info.sourceId), regionRect, capParam);
	}
	else if (info.type == agora::rtc::ScreenCaptureSourceType_Window)
	{
		ret = AgoraUERtcEngine::Get()->startScreenCaptureByWindowId(info.sourceId, regionRect, capParam);
	}
#endif
	UBFL_Logger::Print(FString::Printf(TEXT("%s ret %d"), *FString(FUNCTION_MACRO), ret), LogMsgViewPtr);
	return ret;
}


void UStartLocalVideoTranscoderWidget::OnBtnBackToHomeClicked()
{
	UnInitAgoraEngine();
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("MainLevel"));
}

void UStartLocalVideoTranscoderWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnInitAgoraEngine();


}

void UStartLocalVideoTranscoderWidget::UnInitAgoraEngine()
{
	if (AgoraUERtcEngine::Get() != nullptr)
	{
		if (MediaPlayer)
		{
			MediaPlayer->stop();
			MediaPlayer->unregisterPlayerSourceObserver(MediaPlayerSourceObserverWarpper.Get());
		}

		AgoraUERtcEngine::Get()->leaveChannel();
		AgoraUERtcEngine::Get()->unregisterEventHandler(UserRtcEventHandlerEx.Get());
		AgoraUERtcEngine::Release();

		UBFL_Logger::Print(FString::Printf(TEXT("%s release agora engine"), *FString(FUNCTION_MACRO)), LogMsgViewPtr);
	}
}



#pragma region UI Utility

int UStartLocalVideoTranscoderWidget::MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	/*
		For local view:
			please reference the callback function Ex.[onCaptureVideoFrame]

		For remote view:
			please reference the callback function [onRenderVideoFrame]

		channelId will be set in [setupLocalVideo] / [setupRemoteVideo]
	*/

	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{

		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		videoCanvas.view = UBFL_VideoViewManager::CreateOneVideoViewToCanvasPanel(VideoViewIdentity, CanvasPanel_VideoView, VideoViewMap, DraggableVideoViewTemplate);

		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}

	return ret;
}

int UStartLocalVideoTranscoderWidget::ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType /*= VIDEO_SOURCE_CAMERA_PRIMARY*/, FString channelId /*= ""*/)
{
	int ret = 0;


	agora::rtc::VideoCanvas videoCanvas;
	videoCanvas.view = nullptr;
	videoCanvas.uid = uid;
	videoCanvas.sourceType = sourceType;

	if (uid == 0) {
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, "");
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		ret = AgoraUERtcEngine::Get()->setupLocalVideo(videoCanvas);
	}
	else
	{
		FVideoViewIdentity VideoViewIdentity(uid, sourceType, channelId);
		UBFL_VideoViewManager::ReleaseOneVideoView(VideoViewIdentity, VideoViewMap);
		if (channelId == "") {
			ret = AgoraUERtcEngine::Get()->setupRemoteVideo(videoCanvas);
		}
		else {
			agora::rtc::RtcConnection connection;
			std::string StdStrChannelId = TCHAR_TO_UTF8(*channelId);
			connection.channelId = StdStrChannelId.c_str();
			ret = ((agora::rtc::IRtcEngineEx*)AgoraUERtcEngine::Get())->setupRemoteVideoEx(videoCanvas, connection);
		}
	}
	return ret;
}

#pragma endregion


#pragma region AgoraCallback - IRtcEngineEventHandlerEx


void UStartLocalVideoTranscoderWidget::FUserRtcEventHandlerEx::onJoinChannelSuccess(const agora::rtc::RtcConnection& connection, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			//WidgetPtr->MakeVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UStartLocalVideoTranscoderWidget::FUserRtcEventHandlerEx::onLeaveChannel(const agora::rtc::RtcConnection& connection, const agora::rtc::RtcStats& stats)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s"), *FString(FUNCTION_MACRO)), WidgetPtr->GetLogMsgViewPtr());

			//WidgetPtr->ReleaseVideoView(0, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA);
		});
}

void UStartLocalVideoTranscoderWidget::FUserRtcEventHandlerEx::onUserJoined(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, int elapsed)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->MakeVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

void UStartLocalVideoTranscoderWidget::FUserRtcEventHandlerEx::onUserOffline(const agora::rtc::RtcConnection& connection, agora::rtc::uid_t remoteUid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{
			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}
			UBFL_Logger::Print(FString::Printf(TEXT("%s remote uid=%u"), *FString(FUNCTION_MACRO), remoteUid), WidgetPtr->GetLogMsgViewPtr());

			WidgetPtr->ReleaseVideoView(remoteUid, agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE, WidgetPtr->GetChannelName());
		});
}

#pragma endregion


#pragma region  AgoraCallback - IMediaPlayerSourceObserver

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPlayerSourceStateChanged(media::base::MEDIA_PLAYER_STATE state, media::base::MEDIA_PLAYER_REASON reason)
{
	if (state != media::base::MEDIA_PLAYER_STATE::PLAYER_STATE_OPEN_COMPLETED)
		return;

	if (!IsWidgetValid())
		return;

#if  ((__cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)) 
	AsyncTask(ENamedThreads::GameThread, [=, this]()
#else
	AsyncTask(ENamedThreads::GameThread, [=]()
#endif
		{

			if (!IsWidgetValid())
			{
				UBFL_Logger::Print(FString::Printf(TEXT("%s bIsDestruct "), *FString(FUNCTION_MACRO)));
				return;
			}


			auto TmpMediaPlayer = WidgetPtr->GetMediaPlayer();

			// VIDEO_SOURCE_MEDIA_PLAYER 
			int ret = TmpMediaPlayer->play();
			UBFL_Logger::Print(FString::Printf(TEXT("%s MediaPlayer Play ret %d"), *FString(FUNCTION_MACRO), ret), WidgetPtr->GetLogMsgViewPtr());

			/*WidgetPtr->MakeVideoView(TmpMediaPlayer->getMediaPlayerId(), agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_MEDIA_PLAYER, WidgetPtr->GetChannelName());*/

		});
}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPositionChanged(int64_t positionMs, int64_t timestampMs)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPlayerEvent(media::base::MEDIA_PLAYER_EVENT eventCode, int64_t elapsedTime, const char* message)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onMetaData(const void* data, int length)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPlayBufferUpdated(int64_t playCachedBuffer)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPreloadEvent(const char* src, media::base::PLAYER_PRELOAD_EVENT event)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onCompleted()
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onAgoraCDNTokenWillExpire()
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPlayerSrcInfoChanged(const media::base::SrcInfo& from, const media::base::SrcInfo& to)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onPlayerInfoUpdated(const media::base::PlayerUpdatedInfo& info)
{

}

void UStartLocalVideoTranscoderWidget::FUserIMediaPlayerSourceObserver::onAudioVolumeIndication(int volume)
{

}
#pragma endregion