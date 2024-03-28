//  Copyright (c) 2023 Agora.io. All rights reserved.


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
	agora::media::MediaRecorderConfiguration mediaRecorderConfiguration =config.CreateAgoraData();
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->startRecording(mediaRecorderConfiguration);
	}
	config.FreeAgoraData(mediaRecorderConfiguration);
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
