#pragma once
#include "CoreMinimal.h"
#include "Templates/TypeHash.h"
#include "AgoraHeaderBase.h"
#include <string>

namespace agora {
	namespace rtc {
		namespace ue {
			
			using VideoFrame = media::base::VideoFrame;

			enum class VideoRenderType :uint8 {
				RGBA = 0,
				YUV = 1,
			};

			/*
				Since [setupRemoteVideo] doesn't pass the channel name, and Agora doesn't support joining multiple video channels, we don't use the channel ID to judge.
			*/
			typedef struct VideoFrameId {
				
				VIDEO_SOURCE_TYPE Type;
				agora::rtc::uid_t Id;
				std::string Channel;

				VideoFrameId() :Type(VIDEO_SOURCE_CAMERA), Id(0), Channel("") {}
				VideoFrameId(VIDEO_SOURCE_TYPE Type, uid_t Id, const char* ChannelName) :Type(Type), Id(Id), Channel(ChannelName) {}


				bool operator <(const VideoFrameId& Other) const
				{
					if (Type < Other.Type)
					{
						return true;
					}
					else if (Type == Other.Type)
					{
						if (Id < Other.Id)
						{
							return true;
						}
						//else if (Id == Other.Id)
						//{
						//	if (Channel== Other.Channel)
						//	{
						//		return true;
						//	}
						//}

					}
					return false;
				}
				bool operator==(const VideoFrameId& Other) const
				{
					//return Type == Other.Type && Id == Other.Id && Channel == Other.Channel;

					return Type == Other.Type && Id == Other.Id;
				}

				friend FORCEINLINE uint32 GetTypeHash(const VideoFrameId& Key)
				{
					uint32 Hash = 0;

					Hash = HashCombine(Hash, (uint32)(Key.Type));
					Hash = HashCombine(Hash, (uint32)(Key.Id));
					//Hash = HashCombine(Hash, FCrc::StrCrc32<TCHAR>(*FString(Key.Channel.c_str())));
					return Hash;
				}

			} VideoFrameId;




		}
	}
}