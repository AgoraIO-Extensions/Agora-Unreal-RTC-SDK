#pragma once

#if AGORA_UESDK_ENABLE_VIDEO

#include "AgoraHeaderBase.h"
#include <string>
#include <memory>

namespace agora {
	namespace rtc {
		namespace ue {

			using namespace media;
			using VideoFrame = media::IVideoFrameObserver::VideoFrame;

			typedef struct VideoFrameIdentity {

				VIDEO_SOURCE_TYPE Type;
				unsigned int Id;
				std::string Channel;

				VideoFrameIdentity(VIDEO_SOURCE_TYPE Type, unsigned int Id, const char* ChannelName)
				{
					this->Type = Type;
					this->Id = Id;
					Channel = std::string(ChannelName);
				}

				bool operator <(const VideoFrameIdentity& Other) const
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
						else if (Id == Other.Id)
						{
							if (Channel.c_str() == Other.Channel.c_str())
							{
								return true;
							}
						}

					}
					return false;
				}
			} VideoFrameIdentity;

			class ICacheManager
			{
			public:
				virtual ~ICacheManager() {}
				virtual void enableVideoFrameObserver(const VideoFrameIdentity* Identity) = 0;
				virtual void disableVideoFrameObserver(const VideoFrameIdentity* Identity) = 0;
				virtual int pushVideo(const VideoFrameIdentity* Identity, VideoFrame* Frame) = 0;
				virtual int popVideo(const VideoFrameIdentity* Identity, VideoFrame*& Frame) = 0;
				virtual void clear(const VideoFrameIdentity* Identity) = 0;
				virtual void clearAll() = 0;
			};

			ICacheManager* createCacheManager();

		}
	}
}

#endif