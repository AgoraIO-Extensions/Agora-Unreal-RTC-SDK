//  Copyright (c) 2024 Agora.io. All rights reserved.

#include "AgoraBPuDeviceManager.h"
#include "AgoraHeaderBase.h"
#include "UtilityAgoraBPuLogger.h"


UAgoraBPuVideoDeviceManager* UAgoraBPuVideoDeviceManager::Instance = nullptr;

UAgoraBPuAudioDeviceManager* UAgoraBPuAudioDeviceManager::Instance = nullptr;


UAgoraBPuVideoDeviceManager* UAgoraBPuVideoDeviceManager::GetAgoraVideoDeviceManager()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UAgoraBPuVideoDeviceManager>();
		Instance->AddToRoot();
		AgoraUERtcEngine::Get()->queryInterface(agora::rtc::AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&Instance->VideoDeviceManager);

		if (Instance->VideoDeviceManager == nullptr) {

			UAgoraBPuLogger::PrintError("VideoDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

			Instance->VideoDeviceCollection = nullptr;
		}
		else{
		
			Instance->VideoDeviceCollection = NewObject<UVideoDeviceCollection>();
		
		}
	}
	return Instance;
}

void UAgoraBPuVideoDeviceManager::Release()
{
	if (Instance)
	{
		if(Instance->VideoDeviceCollection){
			Instance->VideoDeviceCollection->Release();
			Instance->VideoDeviceCollection = nullptr;
		}
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}


UVideoDeviceCollection* UAgoraBPuVideoDeviceManager::EnumerateVideoDevices()
{
	if (VideoDeviceManager == nullptr) {

		UAgoraBPuLogger::PrintError("VideoDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	if (VideoDeviceCollection != nullptr) {
		VideoDeviceCollection->Release();
	}

	agora::rtc::IVideoDeviceCollection* VideoCollection = VideoDeviceManager->enumerateVideoDevices();
	if (VideoCollection == nullptr) {

		UAgoraBPuLogger::PrintError("VideoCollection is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	VideoDeviceCollection->Init(VideoCollection);

	return VideoDeviceCollection;
}

int UAgoraBPuVideoDeviceManager::SetDevice(const FString& deviceIdUTF8)
{
	if(VideoDeviceManager != nullptr){
		
		std::string DeviceIdStr = TCHAR_TO_UTF8(*deviceIdUTF8);
		auto ret = VideoDeviceManager->setDevice(DeviceIdStr.c_str());
		return ret;
	
	}
	else{
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuVideoDeviceManager::GetDevice(FString& deviceIdUTF8)
{
	if (VideoDeviceManager != nullptr) {

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		auto ret = VideoDeviceManager->getDevice(tempDeviceId);

		deviceIdUTF8 = UTF8_TO_TCHAR(tempDeviceId);

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuVideoDeviceManager::NumberOfCapabilities(const FString& deviceIdUTF8)
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || \
    (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

	if (VideoDeviceManager != nullptr) {

		auto ret = VideoDeviceManager->numberOfCapabilities(TCHAR_TO_UTF8(*deviceIdUTF8));

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}

#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif 
}

int UAgoraBPuVideoDeviceManager::GetCapability(const FString& deviceIdUTF8, int deviceCapabilityNumber, FUABT_VideoFormat& capability)
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || \
    (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)

	if (VideoDeviceManager != nullptr) {

		agora::rtc::VideoFormat valCapability;
		auto ret = VideoDeviceManager->getCapability(TCHAR_TO_UTF8(*deviceIdUTF8), deviceCapabilityNumber, valCapability);
		capability = valCapability;

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}

#else
	return AGORA_UE_ERR_CODE(ERROR_NOT_SUPPORT_PLATFORM);
#endif 
}

int UAgoraBPuVideoDeviceManager::StartDeviceTest(int64 hwnd)
{
	if (VideoDeviceManager != nullptr) {

		auto ret = VideoDeviceManager->startDeviceTest((agora::view_t)hwnd);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuVideoDeviceManager::StopDeviceTest()
{
	if (VideoDeviceManager != nullptr) {

		auto ret = VideoDeviceManager->stopDeviceTest();
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

UAgoraBPuAudioDeviceManager* UAgoraBPuAudioDeviceManager::GetAgoraAudioDeviceManager()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UAgoraBPuAudioDeviceManager>();
		Instance->AddToRoot();
		AgoraUERtcEngine::Get()->queryInterface(agora::rtc::AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&Instance->AudioDeviceManager);

		if(Instance->AudioDeviceManager == nullptr){
		
			UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		}


		Instance->PlaybackDeviceCollection = NewObject<UAudioDeviceCollection>();

		Instance->RecordDeviceCollection = NewObject<UAudioDeviceCollection>();
	}
	return Instance;
}

void UAgoraBPuAudioDeviceManager::Release()
{
	if (Instance)
	{
		if (Instance->PlaybackDeviceCollection) {
			Instance->PlaybackDeviceCollection->Release();
			Instance->PlaybackDeviceCollection = nullptr;
		}

		if (Instance->RecordDeviceCollection) {
			Instance->RecordDeviceCollection->Release();
			Instance->RecordDeviceCollection = nullptr;
		}

		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}

UAudioDeviceCollection* UAgoraBPuAudioDeviceManager::EnumeratePlaybackDevices()
{
	if (AudioDeviceManager == nullptr) {
		UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);
		return nullptr;
	}

	if(PlaybackDeviceCollection != nullptr){
		PlaybackDeviceCollection->Release();
	}


	agora::rtc::IAudioDeviceCollection* AudioCollection = AudioDeviceManager->enumeratePlaybackDevices();
	if (AudioCollection == nullptr) {

		UAgoraBPuLogger::PrintError("AudioCollection is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	PlaybackDeviceCollection->Init(AudioCollection);

	return PlaybackDeviceCollection;
}

UAudioDeviceCollection* UAgoraBPuAudioDeviceManager::EnumerateRecordingDevices()
{
	if (AudioDeviceManager == nullptr) {

		UAgoraBPuLogger::PrintError("AudioDeviceManager is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	if (RecordDeviceCollection != nullptr) {
		RecordDeviceCollection->Release();
	}



	agora::rtc::IAudioDeviceCollection* AudioCollection = AudioDeviceManager->enumerateRecordingDevices();
	if (AudioCollection == nullptr) {

		UAgoraBPuLogger::PrintError("AudioCollection is nullptr." + AGORA_UEBP_ERR_STR[AGORA_UE_ERROR_CODE::ERROR_BP_RTC_ENGINE_NOT_INITIALIZED]);

		return nullptr;
	}

	RecordDeviceCollection->Init(AudioCollection);

	return RecordDeviceCollection;
}

int UAgoraBPuAudioDeviceManager::SetPlaybackDevice(const FString& deviceId)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setPlaybackDevice(TCHAR_TO_UTF8(*deviceId));
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::GetPlaybackDevice(FString& deviceId)
{
	if (AudioDeviceManager != nullptr) {

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		auto ret = AudioDeviceManager->getPlaybackDevice(tempDeviceId);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::GetPlaybackDeviceInfo(FString& deviceId, FString& deviceName, FString& deviceTypeName)
{
	if (AudioDeviceManager != nullptr) {

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];
		char tempDeviceTypeName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		auto ret = AudioDeviceManager->getPlaybackDeviceInfo(tempDeviceId, tempDeviceName, tempDeviceTypeName);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);
		deviceName = UTF8_TO_TCHAR(tempDeviceName);
		deviceTypeName = UTF8_TO_TCHAR(tempDeviceTypeName);

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::SetPlaybackDeviceVolume(int volume)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setPlaybackDeviceVolume(volume);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::GetPlaybackDeviceVolume(int& volume)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->getPlaybackDeviceVolume(&volume);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::SetRecordingDevice(const FString& deviceId)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setRecordingDevice(TCHAR_TO_UTF8(*deviceId));
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}

}

int UAgoraBPuAudioDeviceManager::GetRecordingDevice(FString& deviceId)
{
	if (AudioDeviceManager != nullptr) {

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		auto ret = AudioDeviceManager->getRecordingDevice(tempDeviceId);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::GetRecordingDeviceInfo(FString& deviceId, FString& deviceName, FString& deviceTypeName)
{
	if (AudioDeviceManager != nullptr) {

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];
		char tempDeviceTypeName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		auto ret = AudioDeviceManager->getRecordingDeviceInfo(tempDeviceId, tempDeviceName, tempDeviceTypeName);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);
		deviceName = UTF8_TO_TCHAR(tempDeviceName);
		deviceTypeName = UTF8_TO_TCHAR(tempDeviceTypeName);

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}

}

int UAgoraBPuAudioDeviceManager::SetRecordingDeviceVolume(int volume)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setRecordingDeviceVolume(volume);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}

}

int UAgoraBPuAudioDeviceManager::GetRecordingDeviceVolume(int& volume)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->getRecordingDeviceVolume(&volume);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::SetLoopbackDevice(const FString& deviceId)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setLoopbackDevice(TCHAR_TO_UTF8(*deviceId));
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::GetLoopbackDevice(FString& deviceId)
{
	if (AudioDeviceManager != nullptr) {

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		auto ret = AudioDeviceManager->getLoopbackDevice(tempDeviceId);

		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::SetPlaybackDeviceMute(bool mute)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setPlaybackDeviceMute(mute);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}

}

int UAgoraBPuAudioDeviceManager::GetPlaybackDeviceMute(bool& mute)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->getPlaybackDeviceMute(&mute);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::SetRecordingDeviceMute(bool mute)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->setRecordingDeviceMute(mute);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::GetRecordingDeviceMute(bool& mute)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->getRecordingDeviceMute(&mute);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::StartPlaybackDeviceTest(const FString& testAudioFilePath)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->startPlaybackDeviceTest(TCHAR_TO_UTF8(*testAudioFilePath));
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::StopPlaybackDeviceTest()
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->stopPlaybackDeviceTest();
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::StartRecordingDeviceTest(int indicationInterval)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->startRecordingDeviceTest(indicationInterval);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::StopRecordingDeviceTest()
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->stopRecordingDeviceTest();
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::StartAudioDeviceLoopbackTest(int indicationInterval)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->startAudioDeviceLoopbackTest(indicationInterval);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::StopAudioDeviceLoopbackTest()
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->stopAudioDeviceLoopbackTest();
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::FollowSystemPlaybackDevice(bool enable)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->followSystemPlaybackDevice(enable);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::FollowSystemRecordingDevice(bool enable)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->followSystemRecordingDevice(enable);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

int UAgoraBPuAudioDeviceManager::FollowSystemLoopbackDevice(bool enable)
{
	if (AudioDeviceManager != nullptr) {

		auto ret = AudioDeviceManager->followSystemLoopbackDevice(enable);
		return ret;

	}
	else {
		return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
	}
}

void UVideoDeviceCollection::Init(agora::rtc::IVideoDeviceCollection* VideoCollectionPtr)
{
	VideoDeviceCollection = VideoCollectionPtr;
}

int UVideoDeviceCollection::GetCount()
{
	if (VideoDeviceCollection != nullptr)
	{
		
		return VideoDeviceCollection->getCount();

	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UVideoDeviceCollection::SetDevice(const FString& deviceId)
{
	if (VideoDeviceCollection != nullptr)
	{
		std::string DeviceIdStr = TCHAR_TO_UTF8(*deviceId);
		return VideoDeviceCollection->setDevice(DeviceIdStr.c_str());
	
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UVideoDeviceCollection::GetDevice(int index, FString& deviceName, FString& deviceId)
{
	if (VideoDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = VideoDeviceCollection->getDevice(index, tempDeviceName, tempDeviceId);

		std::string StdStrDeviceName = tempDeviceName;
		std::string StdStrDeviceId = tempDeviceId;

		deviceName = StdStrDeviceName.c_str();
		deviceId = StdStrDeviceId.c_str();

		return ret;
	}
	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

void UVideoDeviceCollection::Release()
{
	if (VideoDeviceCollection != nullptr)
	{
		return VideoDeviceCollection->release();
	}
}

void UAudioDeviceCollection::Init(agora::rtc::IAudioDeviceCollection* AudioCollectionPtr)
{
	AudioDeviceCollection = AudioCollectionPtr;
}

int UAudioDeviceCollection::GetCount()
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->getCount();
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::GetDevice(int index, FString& deviceName, FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceCollection->getDevice(index, tempDeviceName, tempDeviceId);


		deviceName = UTF8_TO_TCHAR(tempDeviceName);
		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::SetDevice(const FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		std::string DeviceIdStr = TCHAR_TO_UTF8(*deviceId);
		return AudioDeviceCollection->setDevice(DeviceIdStr.c_str());
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::GetDefaultDevice(FString& deviceName, FString& deviceId)
{
	if (AudioDeviceCollection != nullptr)
	{
		char tempDeviceName[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		char tempDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH_TYPE::MAX_DEVICE_ID_LENGTH];

		int ret = AudioDeviceCollection->getDefaultDevice(tempDeviceName, tempDeviceId);

		deviceName = UTF8_TO_TCHAR(tempDeviceName);
		deviceId = UTF8_TO_TCHAR(tempDeviceId);

		return ret;
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::SetApplicationVolume(int volume)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->setApplicationVolume(volume);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::GetApplicationVolume(int & volume)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->getApplicationVolume(volume);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::SetApplicationMute(bool mute)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->setApplicationMute(mute);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

int UAudioDeviceCollection::IsApplicationMute(bool mute)
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->isApplicationMute(mute);
	}

	return AGORA_UE_ERR_CODE(ERROR_NULLPTR);
}

void UAudioDeviceCollection::Release()
{
	if (AudioDeviceCollection != nullptr)
	{
		return AudioDeviceCollection->release();
	}
}
