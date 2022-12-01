// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraBluePrintPlugin/AgoraMediaRecorder.h"

int UIMediaRecorder::SetMediaRecorderObserver(FRtcConnection& connection, UIMediaRecorderObserver* callback)
{
	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->setMediaRecorderObserver(rtcConnection, callback);
	}
	return -ERROR_NULLPTR;
}
int UIMediaRecorder::StartRecording(FRtcConnection& connection, FMediaRecorderConfiguration& config)
{
	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;
	agora::media::MediaRecorderConfiguration mediaRecorderConfiguration;
	mediaRecorderConfiguration.storagePath = TCHAR_TO_ANSI(*config.storagePath);
	mediaRecorderConfiguration.containerFormat = (agora::media::MediaRecorderContainerFormat)config.containerFormat;
	mediaRecorderConfiguration.streamType = (agora::media::MediaRecorderStreamType)config.streamType;
	mediaRecorderConfiguration.maxDurationMs = config.maxDurationMs;
	mediaRecorderConfiguration.recorderInfoUpdateInterval = config.recorderInfoUpdateInterval;
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->startRecording(rtcConnection, mediaRecorderConfiguration);
	}
	return -ERROR_NULLPTR;
}
int UIMediaRecorder::StopRecording(FRtcConnection& connection)
{
	agora::rtc::RtcConnection rtcConnection;
	rtcConnection.channelId = TCHAR_TO_ANSI(*connection.channelId);
	rtcConnection.localUid = connection.localUid;
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->stopRecording(rtcConnection);
	}
	return -ERROR_NULLPTR;
}
void UIMediaRecorder::Release()
{
	if (MediaRecorder != nullptr)
	{
		return MediaRecorder->release();
	}
}
void UIMediaRecorder::SetMediaRecorder(agora::rtc::IMediaRecorder* mediaRecorder)
{
	this->MediaRecorder = mediaRecorder;
}
