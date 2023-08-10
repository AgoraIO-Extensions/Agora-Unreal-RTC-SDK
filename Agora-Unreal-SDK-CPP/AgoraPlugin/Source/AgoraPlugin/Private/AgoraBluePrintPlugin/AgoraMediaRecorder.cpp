// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraMediaRecorder.h"
#include <string>

int UIMediaRecorder::SetMediaRecorderObserver(UIMediaRecorderObserver* callback)
{
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->setMediaRecorderObserver(callback);
	}
	return -ERROR_NULLPTR;
}
int UIMediaRecorder::StartRecording(FMediaRecorderConfiguration& config)
{
	agora::media::MediaRecorderConfiguration mediaRecorderConfiguration;
	std::string StdStrStoragePath = TCHAR_TO_UTF8(*config.storagePath);
	mediaRecorderConfiguration.storagePath = StdStrStoragePath.c_str();
	mediaRecorderConfiguration.containerFormat = (agora::media::MediaRecorderContainerFormat)config.containerFormat;
	mediaRecorderConfiguration.streamType = (agora::media::MediaRecorderStreamType)config.streamType;
	mediaRecorderConfiguration.maxDurationMs = config.maxDurationMs;
	mediaRecorderConfiguration.recorderInfoUpdateInterval = config.recorderInfoUpdateInterval;
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->startRecording(mediaRecorderConfiguration);
	}
	return -ERROR_NULLPTR;
}
int UIMediaRecorder::StopRecording()
{
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->stopRecording();
	}
	return -ERROR_NULLPTR;
}

void UIMediaRecorder::SetMediaRecorder(agora::rtc::IMediaRecorder* mediaRecorder)
{
	this->MediaRecorder = mediaRecorder;
}
