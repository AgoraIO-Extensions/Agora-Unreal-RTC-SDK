//  Copyright (c) 2024 Agora.io. All rights reserved.

#pragma once

// AgoraHeaderBase should be included first.

#include "AgoraHeaderBase.h"
#include <mutex>
#include "Templates/SharedPointer.h"


namespace agora {
	namespace rtc {
		namespace ue {

			// there would be some naming conflicts:
			// Ex. Unreal has already define Rectangle as a function
			class VideoFrameRenderManager;
			class AgoraUEVideoFrameObserver;



			// This is a ue singleton wrapper for Agora Rtc Engine.
			class AGORAPLUGIN_API AgoraUERtcEngine : public agora::rtc::IRtcEngineEx {

			public:
				AgoraUERtcEngine();
				~AgoraUERtcEngine();

				static AgoraUERtcEngine* Get();
				static agora::rtc::IRtcEngine* NativeRtcEnginePtr();
				static FString GetSDKVersion();
				static void EnableIOSAudioSession(bool bEnable);
				static void Release(bool sync = false);
				static AgoraAppType RtcEngineAppType;


			protected:
				//static variables
				static AgoraUERtcEngine* Instance;
				static std::mutex MutexLock;

				// member variables
				agora::rtc::IRtcEngine* RtcEngine;
				agora::util::AutoPtr<agora::media::IMediaEngine> MediaEngine;

#if AGORA_UESDK_ENABLE_VIDEO
				TSharedPtr<VideoFrameRenderManager> _VideoFrameRenderManager;
				TSharedPtr< AgoraUEVideoFrameObserver>_VideoObserver;
#endif

			private:
				void CreateEngine();
				void DestroyEngine(bool sync = false);


			public:


#pragma region Agora API Wrapper
				virtual int initialize(const agora::rtc::RtcEngineContext& context) override;

				// Use Unreal Rendering
				virtual int setupRemoteVideo(const agora::rtc::VideoCanvas& canvas) override;
				virtual int setupLocalVideo(const agora::rtc::VideoCanvas& canvas) override;
				virtual int setupRemoteVideoEx(const agora::rtc::VideoCanvas& canvas, const agora::rtc::RtcConnection& connection) override;
				virtual int writeLog (commons::LOG_LEVEL level, const char * fmt,  ...) override;

				// Set Parameter

				// Audio Dump

				// WITH_AGORA_CALLBACKS

#pragma endregion Agora API Wrapper


#pragma region Other Native APIs



/*
 * Gets the pointer to the specified interface.
 * 
 * @param iid The ID of the interface. See #INTERFACE_ID_TYPE for details.
 * @param inter Output parameter. The pointer to the specified interface.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int queryInterface (INTERFACE_ID_TYPE iid, void ** inter)  override;



/*
 * Gets the SDK version.
 * @param build The build number.
 * @return The version of the current SDK in the string format.
 */
					virtual char const* getVersion (int * build)  override;



/*
 * Gets the warning or error description.
 * @param code The error code or warning code reported by the SDK.
 * @return The specific error or warning description.
 */
					virtual char const* getErrorDescription (int code)  override;



/*
 * Queries the capacity of the current device codec.
 * 
 * @param codec_info An array of the codec cap information: CodecCapInfo.
 * @param size The array size.
 * @return
 * 0: Success.
 * < 0: Failure.
 */
					virtual int queryCodecCapability (CodecCapInfo * codecInfo, int & size)  override;



/*
 * Queries the score of the current device.
 * 
 * @return
 * > 0: If the value is greater than 0, it means that the device score has been retrieved and represents the score value.
 * Most devices score between 60-100, with higher scores indicating better performance.
 * 
 * < 0: Failure.
 */
					virtual int queryDeviceScore ()  override;



/*
 * Preload a channel.
 * 
 * This method enables users to preload a channel.
 * 
 * A successful call of this method will reduce the time of joining the same channel.
 * 
 * Note:
 *  1. The SDK supports preloading up to 20 channels. Once the preloaded channels exceed the limit, the SDK will keep the latest 20 available.
 *  2. Renew the token of the preloaded channel by calling this method with the same 'channelId' and 'uid'.
 * 
 * @param token The token generated on your server for authentication.
 * @param channelId The channel name. This parameter signifies the channel in which users engage in
 * real-time audio and video interaction. Under the premise of the same App ID, users who fill in
 * the same channel ID enter the same channel for audio and video interaction. The string length
 * must be less than 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 * ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param uid The user ID. This parameter is used to identify the user in the channel for real-time
 * audio and video interaction. You need to set and manage user IDs yourself, and ensure that each
 * user ID in the same channel is unique. This parameter is a 32-bit unsigned integer. The value
 * range is 1 to 2<h>32</h>-1. If the user ID is not assigned (or set to 0), the SDK assigns a random user
 * ID and returns it in the onJoinChannelSuccess callback. Your application must record and maintain
 * the returned user ID, because the SDK does not do so.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * preload the channel again.
 */
					virtual int preloadChannel (const char * token, const char * channelId, uid_t uid)  override;



/*
 * Preload a channel.
 * 
 * This method enables users to preload a channel.
 * 
 * A successful call of this method will reduce the time of joining the same channel.
 * 
 * Note:
 *  1. The SDK supports preloading up to 20 channels. Once the preloaded channels exceed the limit, the SDK will keep the latest 20 available.
 *  2. Renew the token of the preloaded channel by calling this method with the same 'channelId' and 'userAccount'.
 * 
 * @param token The token generated on your server for authentication.
 * @param channelId The channel name. This parameter signifies the channel in which users engage in
 * real-time audio and video interaction. Under the premise of the same App ID, users who fill in
 * the same channel ID enter the same channel for audio and video interaction. The string length
 * must be less than 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 * ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -2: The parameter is invalid. For example, the userAccount parameter is empty.
 * You need to pass in a valid parameter and preload the channel again.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * preload the channel again.
 */
					virtual int preloadChannelWithUserAccount (const char * token, const char * channelId, const char * userAccount)  override;



/*
 * Update token of the preloaded channels.
 * 
 * An easy way to update all preloaded channels' tokens, if all preloaded channels use the same token.
 * 
 * If preloaded channels use different tokens, we need to call the 'preloadChannel' method with the same 'channelId'
 * and 'uid' or 'userAccount' to update the corresponding token.
 * 
 * @param token The token generated on your server for authentication.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -2: The token is invalid. You need to pass in a valid token and update the token again.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 */
					virtual int updatePreloadChannelToken (const char * token)  override;



/*
 * Joins a channel.
 * 
 * This method enables users to join a channel. Users in the same channel can talk to each other,
 * and multiple users in the same channel can start a group chat. Users with different App IDs
 * cannot call each other.
 * 
 * A successful call of this method triggers the following callbacks:
 * - The local client: The `onJoinChannelSuccess` and `onConnectionStateChanged` callbacks.
 * - The remote client: `onUserJoined`, if the user joining the channel is in the Communication
 * profile or is a host in the Live-broadcasting profile.
 * 
 * When the connection between the client and Agora's server is interrupted due to poor network
 * conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins
 * the channel, the SDK triggers the `onRejoinChannelSuccess` callback on the local client.
 * 
 * @note Once a user joins the channel, the user subscribes to the audio and video streams of all
 * the other users in the channel by default, giving rise to usage and billing calculation. To
 * stop subscribing to a specified stream or all remote streams, call the corresponding `mute` methods.
 * 
 * @param token The token generated on your server for authentication.
 * @param channelId The channel name. This parameter signifies the channel in which users engage in
 * real-time audio and video interaction. Under the premise of the same App ID, users who fill in
 * the same channel ID enter the same channel for audio and video interaction. The string length
 * must be less than 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 * ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param info (Optional) Reserved for future use.
 * @param uid The user ID. This parameter is used to identify the user in the channel for real-time
 * audio and video interaction. You need to set and manage user IDs yourself, and ensure that each
 * user ID in the same channel is unique. This parameter is a 32-bit unsigned integer. The value
 * range is 1 to 2<h>32</h>-1. If the user ID is not assigned (or set to 0), the SDK assigns a random user
 * ID and returns it in the onJoinChannelSuccess callback. Your application must record and maintain
 * the returned user ID, because the SDK does not do so.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -2: The parameter is invalid. For example, the token is invalid, the uid parameter is not set
 * to an integer, or the value of a member in the `ChannelMediaOptions` structure is invalid. You need
 * to pass in a valid parameter and join the channel again.
 *   - -3: Failes to initialize the `IRtcEngine` object. You need to reinitialize the IRtcEngine object.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -8: The internal state of the IRtcEngine object is wrong. The typical cause is that you call
 * this method to join the channel without calling `stopEchoTest` to stop the test after calling
 * `startEchoTest` to start a call loop test. You need to call `stopEchoTest` before calling this method.
 *   - -17: The request to join the channel is rejected. The typical cause is that the user is in the
 * channel. Agora recommends using the `onConnectionStateChanged` callback to get whether the user is
 * in the channel. Do not call this method to join the channel unless you receive the
 * `CONNECTION_STATE_DISCONNECTED(1)` state.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * rejoin the channel.
 *   - -121: The user ID is invalid. You need to pass in a valid user ID in uid to rejoin the channel.
 */
					virtual int joinChannel (const char * token, const char * channelId, const char * info, uid_t uid)  override;



/*
 * Joins a channel with media options.
 * 
 * This method enables users to join a channel. Users in the same channel can talk to each other,
 * and multiple users in the same channel can start a group chat. Users with different App IDs
 * cannot call each other.
 * 
 * A successful call of this method triggers the following callbacks:
 * - The local client: The `onJoinChannelSuccess` and `onConnectionStateChanged` callbacks.
 * - The remote client: `onUserJoined`, if the user joining the channel is in the Communication
 * profile or is a host in the Live-broadcasting profile.
 * 
 * When the connection between the client and Agora's server is interrupted due to poor network
 * conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins
 * the channel, the SDK triggers the `onRejoinChannelSuccess` callback on the local client.
 * 
 * Compared to `joinChannel`, this method adds the options parameter to configure whether to
 * automatically subscribe to all remote audio and video streams in the channel when the user
 * joins the channel. By default, the user subscribes to the audio and video streams of all
 * the other users in the channel, giving rise to usage and billings. To unsubscribe, set the
 * `options` parameter or call the `mute` methods accordingly.
 * 
 * @note
 * - This method allows users to join only one channel at a time.
 * - Ensure that the app ID you use to generate the token is the same app ID that you pass in the
 * `initialize` method; otherwise, you may fail to join the channel by token.
 * 
 * @param token The token generated on your server for authentication.
 * 
 * @param channelId The channel name. This parameter signifies the channel in which users engage in
 * real-time audio and video interaction. Under the premise of the same App ID, users who fill in
 * the same channel ID enter the same channel for audio and video interaction. The string length
 * must be less than 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 * ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param uid The user ID. This parameter is used to identify the user in the channel for real-time
 * audio and video interaction. You need to set and manage user IDs yourself, and ensure that each
 * user ID in the same channel is unique. This parameter is a 32-bit unsigned integer. The value
 * range is 1 to 2<h>32</h>-1. If the user ID is not assigned (or set to 0), the SDK assigns a random user
 * ID and returns it in the `onJoinChannelSuccess` callback. Your application must record and maintain
 * the returned user ID, because the SDK does not do so.
 * @param options The channel media options: ChannelMediaOptions.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -2: The parameter is invalid. For example, the token is invalid, the uid parameter is not set
 * to an integer, or the value of a member in the `ChannelMediaOptions` structure is invalid. You need
 * to pass in a valid parameter and join the channel again.
 *   - -3: Failes to initialize the `IRtcEngine` object. You need to reinitialize the IRtcEngine object.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -8: The internal state of the IRtcEngine object is wrong. The typical cause is that you call
 * this method to join the channel without calling `stopEchoTest` to stop the test after calling
 * `startEchoTest` to start a call loop test. You need to call `stopEchoTest` before calling this method.
 *   - -17: The request to join the channel is rejected. The typical cause is that the user is in the
 * channel. Agora recommends using the `onConnectionStateChanged` callback to get whether the user is
 * in the channel. Do not call this method to join the channel unless you receive the
 * `CONNECTION_STATE_DISCONNECTED(1)` state.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * rejoin the channel.
 *   - -121: The user ID is invalid. You need to pass in a valid user ID in uid to rejoin the channel.
 */
					virtual int joinChannel (const char * token, const char * channelId, uid_t uid, const ChannelMediaOptions & options)  override;



/*
 * Updates the channel media options after joining the channel.
 * 
 * @param options The channel media options: ChannelMediaOptions.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int updateChannelMediaOptions (const ChannelMediaOptions & options)  override;



/*
 * Leaves the channel.
 * 
 * This method allows a user to leave the channel, for example, by hanging up or exiting a call.
 * 
 * This method is an asynchronous call, which means that the result of this method returns even before
 * the user has not actually left the channel. Once the user successfully leaves the channel, the
 * SDK triggers the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.
 * 
 * @note
 * If you call \ref release "release" immediately after this method, the leaveChannel process will be
 * interrupted, and the SDK will not trigger the `onLeaveChannel` callback.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int leaveChannel ()  override;



/*
 * Leaves the channel.
 * 
 * @param options The leave channel options.
 * 
 * This method allows a user to leave the channel, for example, by hanging up or exiting a call.
 * 
 * This method is an asynchronous call, which means that the result of this method returns even before
 * the user has not actually left the channel. Once the user successfully leaves the channel, the
 * SDK triggers the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.
 * 
 * @note
 * If you call \ref release "release" immediately after this method, the leaveChannel process will be
 * interrupted, and the SDK will not trigger the `onLeaveChannel` callback.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int leaveChannel (const LeaveChannelOptions & options)  override;



/*
 * Renews the token.
 * 
 * Once a token is enabled and used, it expires after a certain period of time.
 * 
 * Under the following circumstances, generate a new token on your server, and then call this method to
 * renew it. Failure to do so results in the SDK disconnecting from the server.
 * - The \ref IRtcEngineEventHandler onTokenPrivilegeWillExpire "onTokenPrivilegeWillExpire" callback is triggered;
 * - The \ref IRtcEngineEventHandler::onRequestToken "onRequestToken" callback is triggered;
 * - The `ERR_TOKEN_EXPIRED(-109)` error is reported.
 * 
 * @param token The new token.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int renewToken (const char * token)  override;



/*
 * Sets the channel profile.
 * 
 * The IRtcEngine differentiates channel profiles and applies different optimization algorithms accordingly.
 * For example, it prioritizes smoothness and low latency for a video call, and prioritizes video quality
 * for a video broadcast.
 * 
 * @note
 * - To ensure the quality of real-time communication, we recommend that all users in a channel use the
 * same channel profile.
 * - Call this method before calling `joinChannel`. You cannot set the channel profile
 * once you have joined the channel.
 * 
 * @param profile The channel profile: #CHANNEL_PROFILE_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - -8(ERR_INVALID_STATE): The current status is invalid, only allowed to be called when the connection is disconnected.
 */
					virtual int setChannelProfile (CHANNEL_PROFILE_TYPE profile)  override;



/*
 * Sets the role of a user.
 * 
 * This method sets the user role as either BROADCASTER or AUDIENCE (default).
 * - The broadcaster sends and receives streams.
 * - The audience receives streams only.
 * 
 * By default, all users are audience regardless of the channel profile.
 * Call this method to change the user role to BROADCASTER so that the user can
 * send a stream.
 * 
 * @note
 * After calling the setClientRole() method to CLIENT_ROLE_AUDIENCE, the SDK stops audio recording.
 * However, CLIENT_ROLE_AUDIENCE will keep audio recording with AUDIO_SCENARIO_CHATROOM(5).
 * Normally, app developer can also use mute api to achieve the same result, and we implement
 * this 'non-orthogonal' behavior only to make API backward compatible.
 * 
 * @param role The role of the client: #CLIENT_ROLE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setClientRole (CLIENT_ROLE_TYPE role)  override;



/*
 * Sets the role of the user, such as a host or an audience (default), before joining a channel in the live interactive streaming.
 * 
 * This method can be used to switch the user role in the live interactive streaming after the user joins a channel.
 * 
 * In the `LIVE_BROADCASTING` profile, when a user switches user roles after joining a channel, a successful \ref agora::rtc::IRtcEngine::setClientRole "setClientRole" method call triggers the following callbacks:
 * - The local client: \ref agora::rtc::IRtcEngineEventHandler::onClientRoleChanged "onClientRoleChanged"
 * - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" or \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" (BECOME_AUDIENCE)
 * 
 * @note
 * This method applies only to the `LIVE_BROADCASTING` profile.
 * 
 * @param role Sets the role of the user. See #CLIENT_ROLE_TYPE.
 * @param options Sets the audience latency level of the user. See #ClientRoleOptions.
 * 
 * @return
 * - 0(ERR_OK): Success.
 * - < 0: Failure.
 *  - -1(ERR_FAILED): A general error occurs (no specified reason).
 *  - -2(ERR_INALID_ARGUMENT): The parameter is invalid.
 *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized.
 *  - -8(ERR_INVALID_STATE): The channel profile is not `LIVE_BROADCASTING`.
 */
					virtual int setClientRole (CLIENT_ROLE_TYPE role, const ClientRoleOptions & options)  override;



/*
 * Starts a video call test.
 * 
 * @param config: configuration for video call test.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startEchoTest (const EchoTestConfiguration & config)  override;



/*
 * Stops the audio call test.
 * @return int
 * 
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopEchoTest ()  override;

#if defined(__APPLE__) && TARGET_OS_IOS


					virtual int enableMultiCamera (bool enabled, const CameraCapturerConfiguration & config)  override;

#endif


/*
 * Enables the video.
 * 
 * You can call this method either before joining a channel or during a call.
 * If you call this method before entering a channel, the service starts the video; if you call it
 * during a call, the audio call switches to a video call.
 * 
 * @note
 * This method controls the underlying states of the Engine. It is still
 * valid after one leaves the channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableVideo ()  override;



/*
 * Disables the video.
 * 
 * This method stops capturing the local video and receiving any remote video.
 * To enable the local preview function, call \ref enableLocalVideo "enableLocalVideo" (true).
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int disableVideo ()  override;



/*
 * Starts the local video preview before joining a channel.
 * 
 * Once you call this method to start the local video preview, if you leave
 * the channel by calling \ref leaveChannel "leaveChannel", the local video preview remains until
 * you call \ref stopPreview "stopPreview" to disable it.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startPreview ()  override;



/*
 * Starts the local video preview for specific source type.
 * @param sourceType - The video source type.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startPreview (VIDEO_SOURCE_TYPE sourceType)  override;



/*
 * Stops the local video preview and the video.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopPreview ()  override;



/*
 * Stops the local video preview for specific source type.
 * @param sourceType - The video source type.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopPreview (VIDEO_SOURCE_TYPE sourceType)  override;



/*
 * Starts the last-mile network probe test.
 * 
 * This method starts the last-mile network probe test before joining a channel
 * to get the uplink and downlink last-mile network statistics, including the
 * bandwidth, packet loss, jitter, and round-trip time (RTT).
 * 
 * Call this method to check the uplink network quality before users join a
 * channel or before an audience switches to a host. Once this method is
 * enabled, the SDK returns the following callbacks:
 * - \ref IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality": the
 * SDK triggers this callback depending on the network
 * conditions. This callback rates the network conditions and is more closely
 * linked to the user experience.
 * - \ref IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult":
 * the SDK triggers this callback within 30 seconds depending on the network
 * conditions. This callback returns the real-time statistics of the network
 * conditions and is more objective.
 * 
 * @note
 * - Do not call other methods before receiving the
 * \ref IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" and
 * \ref IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult"
 * callbacks. Otherwise, the callbacks may be interrupted.
 * - In the Live-broadcast profile, a host should not call this method after
 * joining a channel.
 * 
 * @param config Sets the configurations of the last-mile network probe test. See
 * LastmileProbeConfig.
 * 
 *  @return
 *  - 0: Success.
 *  - < 0: Failure.
 */
					virtual int startLastmileProbeTest (const LastmileProbeConfig & config)  override;



/*
 * Stops the last-mile network probe test.
 */
					virtual int stopLastmileProbeTest ()  override;



/*
 * Sets the video encoder configuration.
 * 
 * Each configuration profile corresponds to a set of video parameters, including
 * the resolution, frame rate, and bitrate.
 * 
 * The parameters specified in this method are the maximum values under ideal network conditions.
 * If the video engine cannot render the video using the specified parameters due
 * to poor network conditions, the parameters further down the list are considered
 * until a successful configuration is found.
 * 
 * @param config The local video encoder configuration: VideoEncoderConfiguration.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVideoEncoderConfiguration (const VideoEncoderConfiguration & config)  override;



/*
 * Enables/Disables image enhancement and sets the options.
 * 
 * @note Call this method after calling the \ref IRtcEngine::enableVideo "enableVideo" method.
 * 
 * @param enabled Sets whether or not to enable image enhancement:
 * - true: enables image enhancement.
 * - false: disables image enhancement.
 * @param options Sets the image enhancement option. See BeautyOptions.
 */
					virtual int setBeautyEffectOptions (bool enabled, const BeautyOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Enables/Disables face shape and sets the beauty options.
 * 
 * @note Call this method after calling the \ref IRtcEngine::enableVideo "enableVideo" method.
 * 
 * @param enabled Sets whether or not to enable face shape:
 * - true: enables face shape.
 * - false: disables face shape.
 * @param options Sets the face shape beauty option. See FaceShapeBeautyOptions.
 */
					virtual int setFaceShapeBeautyOptions (bool enabled, const FaceShapeBeautyOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Enables/Disables face shape and sets the area options.
 * 
 * @note Call this method after calling the \ref IRtcEngine::setFaceShapeBeautyOptions "setFaceShapeBeautyOptions" method.
 * 
 * @param options Sets the face shape area option. See FaceShapeAreaOptions.
 */
					virtual int setFaceShapeAreaOptions (const FaceShapeAreaOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Gets the face shape beauty options.
 * 
 * @note Call this method after calling the \ref IRtcEngine::enableVideo "enableVideo" method.
 * 
 * @param options Gets the face shape beauty option. See FaceShapeBeautyOptions.
 */
					virtual int getFaceShapeBeautyOptions (FaceShapeBeautyOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Gets the face shape area options.
 * 
 * @note Call this method after calling the \ref IRtcEngine::enableVideo "enableVideo" method.
 * 
 * @param shapeArea  The face area. See FaceShapeAreaOptions::FACE_SHAPE_AREA.
 * @param options Gets the face area beauty option. See FaceShapeAreaOptions.
 */
					virtual int getFaceShapeAreaOptions (agora::rtc::FaceShapeAreaOptions::FACE_SHAPE_AREA shapeArea, FaceShapeAreaOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Sets filter effect options.
 * 
 * @since v4.4.1
 * You can call this method to enable the filter effect feature and set the options of the filter effect.
 * 
 * @note
 * - Before calling this method, ensure that you have integrated the following dynamic library into your project:
 *  - Android: `libagora_clear_vision_extension.so`
 *  - iOS/macOS: `AgoraClearVisionExtension.xcframework`
 *  - Windows: `libagora_clear_vision_extension.dll`
 * - Call this method after calling the \ref IRtcEngine::enableVideo "enableVideo" method.
 * - You can call this method either before or after joining a channel.
 * - The filter effect feature has specific performance requirements for devices. If your device overheats after enabling the filter effect, Agora recommends disabling it entirely.
 * 
 * @param enabled. Whether to enable filter effect:
 * - `true`: Enable.
 * - `false`: (Default) Disable.
 * @param options. Set the filter effect options. See FilterEffectOptions.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setFilterEffectOptions (bool enabled, const FilterEffectOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Sets low-light enhancement.
 * 
 * @since v4.0.0
 * 
 * The low-light enhancement feature can adaptively adjust the brightness value of the video captured in situations with low or uneven lighting, such as backlit, cloudy, or dark scenes. It restores or highlights the image details and improves the overall visual effect of the video.
 * 
 * You can call this method to enable the low-light enhancement feature and set the options of the low-light enhancement effect.
 * 
 * @note
 * - Before calling this method, ensure that you have integrated the following dynamic library into your project:
 *  - Android: `libagora_clear_vision_extension.so`
 *  - iOS/macOS: `AgoraClearVisionExtension.xcframework`
 *  - Windows: `libagora_clear_vision_extension.dll`
 * - Call this method after \ref IRtcEngine::enableVideo "enableVideo".
 * - The low-light enhancement feature has certain performance requirements on devices. If your device overheats after you enable low-light enhancement, Agora recommends modifying the low-light enhancement options to a less performance-consuming level or disabling low-light enhancement entirely.
 * 
 * @param enabled Sets whether to enable low-light enhancement:
 * - `true`: Enable.
 * - `false`: (Default) Disable.
 * @param options The low-light enhancement options. See LowlightEnhanceOptions.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLowlightEnhanceOptions (bool enabled, const LowlightEnhanceOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Sets video noise reduction.
 * 
 * @since v4.0.0
 * 
 * Underlit environments and low-end video capture devices can cause video images to contain significant noise, which affects video quality. In real-time interactive scenarios, video noise also consumes bitstream resources and reduces encoding efficiency during encoding.
 * 
 * You can call this method to enable the video noise reduction feature and set the options of the video noise reduction effect.
 * 
 * @note
 * - Before calling this method, ensure that you have integrated the following dynamic library into your project:
 *  - Android: `libagora_clear_vision_extension.so`
 *  - iOS/macOS: `AgoraClearVisionExtension.xcframework`
 *  - Windows: `libagora_clear_vision_extension.dll`
 * - Call this method after \ref IRtcEngine::enableVideo "enableVideo".
 * - The video noise reduction feature has certain performance requirements on devices. If your device overheats after you enable video noise reduction, Agora recommends modifying the video noise reduction options to a less performance-consuming level or disabling video noise reduction entirely.
 * 
 * @param enabled Sets whether to enable video noise reduction:
 * - `true`: Enable.
 * - `false`: (Default) Disable.
 * @param options The video noise reduction options. See VideoDenoiserOptions.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVideoDenoiserOptions (bool enabled, const VideoDenoiserOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Sets color enhancement.
 * 
 * @since v4.0.0
 * 
 * The video images captured by the camera can have color distortion. The color enhancement feature intelligently adjusts video characteristics such as saturation and contrast to enhance the video color richness and color reproduction, making the video more vivid.
 * 
 * You can call this method to enable the color enhancement feature and set the options of the color enhancement effect.
 * 
 * @note
 * - Before calling this method, ensure that you have integrated the following dynamic library into your project:
 *  - Android: `libagora_clear_vision_extension.so`
 *  - iOS/macOS: `AgoraClearVisionExtension.xcframework`
 *  - Windows: `libagora_clear_vision_extension.dll`
 * - Call this method after \ref IRtcEngine::enableVideo "enableVideo".
 * - The color enhancement feature has certain performance requirements on devices. If your device overheats after you enable color enhancement, Agora recommends modifying the color enhancement options to a less performance-consuming level or disabling color enhancement entirely.
 * 
 * @param enabled Sets whether to enable color enhancement:
 * - `true`: Enable.
 * - `false`: (Default) Disable.
 * @param options The color enhancement options. See ColorEnhanceOptions.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setColorEnhanceOptions (bool enabled, const ColorEnhanceOptions & options, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Enables/Disables the virtual background. (beta function)
 * 
 * @since v3.7.200
 * 
 * After enabling the virtual background function, you can replace the original background image of the local user
 * with a custom background image. After the replacement, all users in the channel can see the custom background
 * image.
 * 
 * @note
 * - Before calling this method, ensure that you have integrated the
 * `libagora_segmentation_extension.dll` (Windows)/`AgoraVideoSegmentationExtension.framework` (macOS) dynamic
 * library into the project folder.
 * - Call this method after \ref IRtcEngine::enableVideo "enableVideo".
 * - This function requires a high-performance device. Agora recommends that you use this function on devices with
 * an i5 CPU and better.
 * - Agora recommends that you use this function in scenarios that meet the following conditions:
 *  - A high-definition camera device is used, and the environment is uniformly lit.
 *  - The captured video image is uncluttered, the user's portrait is half-length and largely unobstructed, and the
 * background is a single color that differs from the color of the user's clothing.
 * 
 * @param enabled Sets whether to enable the virtual background:
 * - true: Enable.
 * - false: Disable.
 * @param backgroundSource The custom background image. See VirtualBackgroundSource. **Note**: To adapt the
 * resolution of the custom background image to the resolution of the SDK capturing video, the SDK scales and crops
 * the custom background image while ensuring that the content of the custom background image is not distorted.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableVirtualBackground (bool enabled, VirtualBackgroundSource backgroundSource, SegmentationProperty segproperty, agora::media::MEDIA_SOURCE_TYPE type = agora::media::PRIMARY_CAMERA_SOURCE)  override;



/*
 * Sets the Video application scenario.
 * 
 * @since v4.2.0
 * 
 * You can call this method to set the expected video scenario.
 * The SDK will optimize the video experience for each scenario you set.
 * 
 * 
 * @param scenarioType The video application scenario. See #ApplicationScenarioType.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 * - ERR_FAILED (1): A general error occurs (no specified reason).
 * - ERR_NOT_SUPPORTED (4): Unable to set video application scenario.
 * - ERR_NOT_INITIALIZED (7): The SDK is not initialized.
 */
					virtual int setVideoScenario (VIDEO_APPLICATION_SCENARIO_TYPE scenarioType)  override;



/*
 * Sets the video qoe preference.
 * 
 * @since v4.2.1
 * 
 * You can call this method to set the expected QoE Preference.
 * The SDK will optimize the video experience for each preference you set.
 * 
 * 
 * @param qoePreference The qoe preference type. See #VIDEO_QOE_PREFERENCE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 * - ERR_FAILED (1): A general error occurs (no specified reason).
 * - ERR_NOT_SUPPORTED (4): Unable to set video application scenario.
 * - ERR_NOT_INITIALIZED (7): The SDK is not initialized.
 */
					virtual int setVideoQoEPreference (VIDEO_QOE_PREFERENCE_TYPE qoePreference)  override;



/*
 * Enables the audio.
 * 
 * The audio is enabled by default.
 * 
 * @note
 * This method controls the underlying states of the Engine. It is still
 * valid after one leaves channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableAudio ()  override;



/*
 * Disables the audio.
 * 
 * @note
 * This method controls the underlying states of the Engine. It is still
 * valid after one leaves channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int disableAudio ()  override;



/*
 * Sets the audio parameters and application scenarios.
 * 
 * @deprecated This method is deprecated. You can use the
 * \ref IRtcEngine::setAudioProfile(AUDIO_PROFILE_TYPE) "setAudioProfile"
 * method instead. To set the audio scenario, call the \ref IRtcEngine::initialize "initialize"
 * method and pass value in the `audioScenario` member in the RtcEngineContext struct.
 * 
 * @note
 * - Call this method before calling the `joinChannel` method.
 * - In scenarios requiring high-quality audio, we recommend setting `profile` as `MUSIC_HIGH_QUALITY`(4)
 * and `scenario` as `AUDIO_SCENARIO_GAME_STREAMING`(3).
 * 
 * @param profile Sets the sample rate, bitrate, encoding mode, and the number of channels:
 * #AUDIO_PROFILE_TYPE.
 * @param scenario Sets the audio application scenarios: #AUDIO_SCENARIO_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioProfile (AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) __deprecated override;



/*
 * Sets the audio profile.
 * 
 * @note
 * - Call this method before calling the `joinChannel` method.
 * - In scenarios requiring high-quality audio, Agora recommends setting `profile` as `MUSIC_HIGH_QUALITY`(4).
 * - To set the audio scenario, call the \ref IRtcEngine::initialize "initialize"
 * method and pass value in the `audioScenario` member in the RtcEngineContext struct.
 * 
 * @param profile The audio profile, such as the sample rate, bitrate and codec type: #AUDIO_PROFILE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioProfile (AUDIO_PROFILE_TYPE profile)  override;



/*
 * Set the audio scenario.
 * 
 * @param scenario The audio scenario: #AUDIO_SCENARIO_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioScenario (AUDIO_SCENARIO_TYPE scenario)  override;



/*
 * Enables or disables the local audio capture.
 * 
 * The audio function is enabled by default. This method disables or re-enables the
 * local audio function, that is, to stop or restart local audio capture and
 * processing.
 * 
 * This method does not affect receiving or playing the remote audio streams,
 * and `enableLocalAudio` (false) is applicable to scenarios where the user wants
 * to receive remote audio streams without sending any audio stream to other users
 * in the channel.
 * 
 * @param enabled Determines whether to disable or re-enable the local audio function:
 * - true: (Default) Re-enable the local audio function, that is, to start local
 * audio capture and processing.
 * - false: Disable the local audio function, that is, to stop local audio
 * capture and processing.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableLocalAudio (bool enabled)  override;



/*
 * Stops or resumes sending the local audio stream.
 * 
 * After calling this method successfully, the SDK triggers the
 * \ref IRtcEngineEventHandler::onRemoteAudioStateChanged "onRemoteAudioStateChanged"
 * callback with the following parameters:
 * - REMOTE_AUDIO_STATE_STOPPED(0) and REMOTE_AUDIO_REASON_REMOTE_MUTED(5).
 * - REMOTE_AUDIO_STATE_DECODING(2) and REMOTE_AUDIO_REASON_REMOTE_UNMUTED(6).
 * 
 * @note
 * - When `mute` is set as `true`, this method does not disable the
 * microphone, which does not affect any ongoing recording.
 * - If you call \ref IRtcEngine::setChannelProfile "setChannelProfile" after
 * this method, the SDK resets whether or not to mute the local audio
 * according to the channel profile and user role. Therefore, we recommend
 * calling this method after the `setChannelProfile` method.
 * 
 * @param mute Determines whether to send or stop sending the local audio stream:
 * - true: Stop sending the local audio stream.
 * - false: (Default) Send the local audio stream.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteLocalAudioStream (bool mute)  override;



/*
 * Stops or resumes receiving all remote audio stream.
 * 
 * This method works for all remote users that join or will join a channel
 * using the `joinChannel` method. It is
 * equivalent to the `autoSubscribeAudio` member in the ChannelMediaOptions
 * class.
 * - Ensure that you call this method after joining a channel.
 * - If you call muteAllRemoteAudioStreams(true) after joining a channel, the
 * local use stops receiving any audio stream from any user in the channel,
 * including any user who joins the channel after you call this method.
 * - If you call muteAllRemoteAudioStreams(true) after leaving a channel, the
 * local user does not receive any audio stream the next time the user joins a
 * channel.
 * 
 * After you successfully call muteAllRemoteAudioStreams(true), you can take
 * the following actions:
 * - To resume receiving all remote audio streams, call
 * muteAllRemoteAudioStreams(false).
 * - To resume receiving the audio stream of a specified user, call
 * muteRemoteAudioStream(uid, false), where uid is the ID of the user whose
 * audio stream you want to resume receiving.
 * 
 * @note
 * - The result of calling this method is affected by calling
 * \ref IRtcEngine::enableAudio "enableAudio" and
 * \ref IRtcEngine::disableAudio "disableAudio". Settings in
 * muteAllRemoteAudioStreams stop taking effect if either of the following occurs:
 *   - Calling `enableAudio` after muteAllRemoteAudioStreams(true).
 *   - Calling `disableAudio` after muteAllRemoteAudioStreams(false).
 * - This method only works for the channel created by calling
 * `joinChannel`. To set whether to receive remote
 * audio streams for a specific channel, Agora recommends using
 * `autoSubscribeAudio` in the ChannelMediaOptions class.
 * @param mute Whether to stop receiving remote audio streams:
 * - true: Stop receiving any remote audio stream.
 * - false: (Default) Resume receiving all remote audio streams.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteAllRemoteAudioStreams (bool mute)  override;



/*
 * Stops or resumes receiving the audio stream of a specified user.
 * 
 * @note
 * You can call this method before or after joining a channel. If a user
 * leaves a channel, the settings in this method become invalid.
 * 
 * @param uid The ID of the specified user.
 * @param mute Whether to stop receiving the audio stream of the specified user:
 * - true: Stop receiving the audio stream of the specified user.
 * - false: (Default) Resume receiving the audio stream of the specified user.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteRemoteAudioStream (uid_t uid, bool mute)  override;



/*
 * Stops or resumes sending the local video stream.
 * 
 * @param mute Determines whether to send or stop sending the local video stream:
 * - true: Stop sending the local video stream.
 * - false: (Default) Send the local video stream.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteLocalVideoStream (bool mute)  override;



/*
 * Disables or re-enables the local video capture.
 * 
 * Once you enable the video using \ref enableVideo "enableVideo", the local video is enabled
 * by default. This method disables or re-enables the local video capture.
 * 
 * `enableLocalVideo(false)` applies to scenarios when the user wants to watch the remote video
 * without sending any video stream to the other user.
 * 
 * @note
 * Call this method after `enableVideo`. Otherwise, this method may not work properly.
 * 
 * @param enabled Determines whether to disable or re-enable the local video, including
 * the capturer, renderer, and sender:
 * - true:  (Default) Re-enable the local video.
 * - false: Disable the local video. Once the local video is disabled, the remote
 * users can no longer receive the video stream of this user, while this user
 * can still receive the video streams of other remote users. When you set
 * `enabled` as `false`, this method does not require a local camera.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableLocalVideo (bool enabled)  override;



/*
 * Stops or resumes receiving all remote video streams.
 * 
 * This method works for all remote users that join or will join a channel
 * using the `joinChannel` method. It is
 * equivalent to the `autoSubscribeVideo` member in the ChannelMediaOptions
 * class.
 * - Ensure that you call this method after joining a channel.
 * - If you call muteAllRemoteVideoStreams(true) after joining a channel, the
 * local use stops receiving any video stream from any user in the channel,
 * including any user who joins the channel after you call this method.
 * - If you call muteAllRemoteVideoStreams(true) after leaving a channel,
 * the local user does not receive any video stream the next time the user
 * joins a channel.
 * 
 * After you successfully call muteAllRemoteVideoStreams(true), you can take
 * the following actions:
 * - To resume receiving all remote video streams, call
 * muteAllRemoteVideoStreams(false).
 * - To resume receiving the video stream of a specified user, call
 * muteRemoteVideoStream(uid, false), where uid is the ID of the user whose
 * video stream you want to resume receiving.
 * 
 * @note
 * - The result of calling this method is affected by calling
 * \ref IRtcEngine::enableVideo "enableVideo" and
 * \ref IRtcEngine::disableVideo "disableVideo". Settings in
 * muteAllRemoteVideoStreams stop taking effect if either of the following occurs:
 *   - Calling `enableVideo` after muteAllRemoteVideoStreams(true).
 *   - Calling `disableVideo` after muteAllRemoteVideoStreams(false).
 * - This method only works for the channel created by calling `joinChannel`.
 * To set whether to receive remote audio streams for a specific channel, Agora
 * recommends using `autoSubscribeVideo` in the ChannelMediaOptions class.
 * @param mute Whether to stop receiving remote video streams:
 * - true: Stop receiving any remote video stream.
 * - false: (Default) Resume receiving all remote video streams.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteAllRemoteVideoStreams (bool mute)  override;



/*
 * Sets the default stream type of the remote video if the remote user has enabled dual-stream.
 * 
 * @param streamType Sets the default video stream type: #VIDEO_STREAM_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteDefaultVideoStreamType (VIDEO_STREAM_TYPE streamType)  override;



/*
 * Stops or resumes receiving the video stream of a specified user.
 * 
 * @note
 * You can call this method before or after joining a channel. If a user
 * leaves a channel, the settings in this method become invalid.
 * 
 * @param uid The ID of the specified user.
 * @param mute Whether to stop receiving the video stream of the specified user:
 * - true: Stop receiving the video stream of the specified user.
 * - false: (Default) Resume receiving the video stream of the specified user.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteRemoteVideoStream (uid_t uid, bool mute)  override;



/*
 * Sets the remote video stream type.
 * 
 * If the remote user has enabled the dual-stream mode, by default the SDK receives the high-stream video by
 * Call this method to switch to the low-stream video.
 * 
 * @note
 * This method applies to scenarios where the remote user has enabled the dual-stream mode using
 * \ref enableDualStreamMode "enableDualStreamMode"(true) before joining the channel.
 * 
 * @param uid ID of the remote user sending the video stream.
 * @param streamType Sets the video stream type: #VIDEO_STREAM_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteVideoStreamType (uid_t uid, VIDEO_STREAM_TYPE streamType)  override;



/*
 * Sets the remote video subscription options
 * 
 * 
 * @param uid ID of the remote user sending the video stream.
 * @param options Sets the video subscription options.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteVideoSubscriptionOptions (uid_t uid, const VideoSubscriptionOptions & options)  override;



/*
 * Sets the blocklist of subscribe remote stream audio.
 * 
 * @param uidList The id list of users whose audio you do not want to subscribe to.
 * @param uidNumber The number of uid in uidList.
 * 
 * @note
 * If uid is in uidList, the remote user's audio will not be subscribed,
 * even if muteRemoteAudioStream(uid, false) and muteAllRemoteAudioStreams(false) are operated.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeAudioBlocklist (uid_t * uidList, int uidNumber)  override;



/*
 * Sets the allowlist of subscribe remote stream audio.
 * 
 * @param uidList The id list of users whose audio you want to subscribe to.
 * @param uidNumber The number of uid in uidList.
 * 
 * @note
 * If uid is in uidList, the remote user's audio will be subscribed,
 * even if muteRemoteAudioStream(uid, true) and muteAllRemoteAudioStreams(true) are operated.
 * 
 * If a user is in the blocklist and allowlist at the same time, only the blocklist takes effect.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeAudioAllowlist (uid_t * uidList, int uidNumber)  override;



/*
 * Sets the blocklist of subscribe remote stream video.
 * 
 * @param uidList The id list of users whose video you do not want to subscribe to.
 * @param uidNumber The number of uid in uidList.
 * 
 * @note
 * If uid is in uidList, the remote user's video will not be subscribed,
 * even if muteRemoteVideoStream(uid, false) and muteAllRemoteVideoStreams(false) are operated.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeVideoBlocklist (uid_t * uidList, int uidNumber)  override;



/*
 * Sets the allowlist of subscribe remote stream video.
 * 
 * @param uidList The id list of users whose video you want to subscribe to.
 * @param uidNumber The number of uid in uidList.
 * 
 * @note
 * If uid is in uidList, the remote user's video will be subscribed,
 * even if muteRemoteVideoStream(uid, true) and muteAllRemoteVideoStreams(true) are operated.
 * 
 * If a user is in the blocklist and allowlist at the same time, only the blocklist takes effect.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeVideoAllowlist (uid_t * uidList, int uidNumber)  override;



/*
 * Enables the `onAudioVolumeIndication` callback to report on which users are speaking
 * and the speakers' volume.
 * 
 * Once the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication"
 * callback is enabled, the SDK returns the volume indication in the at the time interval set
 * in `enableAudioVolumeIndication`, regardless of whether any user is speaking in the channel.
 * 
 * @param interval Sets the time interval between two consecutive volume indications:
 * - <= 0: Disables the volume indication.
 * - > 0: Time interval (ms) between two consecutive volume indications,
 * and should be integral multiple of 200 (less than 200 will be set to 200).
 * @param smooth The smoothing factor that sets the sensitivity of the audio volume
 * indicator. The value range is [0, 10]. The greater the value, the more sensitive the
 * indicator. The recommended value is 3.
 * @param reportVad
 * - `true`: Enable the voice activity detection of the local user. Once it is enabled, the `vad` parameter of the
 * `onAudioVolumeIndication` callback reports the voice activity status of the local user.
 * - `false`: (Default) Disable the voice activity detection of the local user. Once it is disabled, the `vad` parameter
 * of the `onAudioVolumeIndication` callback does not report the voice activity status of the local user, except for
 * the scenario where the engine automatically detects the voice activity of the local user.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableAudioVolumeIndication (int interval, int smooth, bool reportVad)  override;



/*
 * Starts an audio recording.
 * 
 * The SDK allows recording during a call, which supports either one of the
 * following two formats:
 * 
 * - .wav: Large file size with high sound fidelity
 * - .aac: Small file size with low sound fidelity
 * 
 * Ensure that the directory to save the recording file exists and is writable.
 * This method is usually called after the joinChannel() method.
 * The recording automatically stops when the leaveChannel() method is
 * called.
 * 
 * @param filePath Full file path of the recording file. The string of the file
 * name is in UTF-8 code.
 * @param quality Sets the audio recording quality: #AUDIO_RECORDING_QUALITY_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startAudioRecording (const char * filePath, AUDIO_RECORDING_QUALITY_TYPE quality)  override;



/*
 * Starts an audio recording.
 * 
 * The SDK allows recording during a call, which supports either one of the
 * following two formats:
 * 
 * - .wav: Large file size with high sound fidelity
 * - .aac: Small file size with low sound fidelity
 * 
 * Ensure that the directory to save the recording file exists and is writable.
 * This method is usually called after the joinChannel() method.
 * The recording automatically stops when the leaveChannel() method is
 * called.
 * 
 * @param filePath Full file path of the recording file. The string of the file
 * name is in UTF-8 code.
 * @param sampleRate Sample rate, value should be 16000, 32000, 44100, or 48000.
 * @param quality Sets the audio recording quality: #AUDIO_RECORDING_QUALITY_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startAudioRecording (const char * filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality)  override;



/*
 * Starts an audio recording.
 * 
 * The SDK allows recording during a call, which supports either one of the
 * following two formats:
 * 
 * - .wav: Large file size with high sound fidelity
 * - .aac: Small file size with low sound fidelity
 * 
 * Ensure that the directory to save the recording file exists and is writable.
 * This method is usually called after the joinChannel() method.
 * The recording automatically stops when the leaveChannel() method is
 * called.
 * 
 * @param config Audio recording config.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startAudioRecording (const AudioRecordingConfiguration & config)  override;



/*
 * register encoded audio frame observer
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int registerAudioEncodedFrameObserver (const AudioEncodedFrameObserverConfig & config, IAudioEncodedFrameObserver * observer)  override;



/*
 * Stops the audio recording on the client.
 * 
 * The recording automatically stops when the leaveChannel() method is called.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopAudioRecording ()  override;



/*
 * Creates a media player source object and return its pointer. If full featured
 * media player source is supported, it will create it, or it will create a simple
 * media player.
 * 
 * @return
 * - The pointer to \ref rtc::IMediaPlayerSource "IMediaPlayerSource",
 *   if the method call succeeds.
 * - The empty pointer NULL, if the method call fails.
 */
					virtual agora_refptr<agora::rtc::IMediaPlayer> createMediaPlayer ()  override;



/*
 * Destroy a media player source instance.
 * If a media player source instance is destroyed, the video and audio of it cannot
 * be published.
 * 
 * @param media_player The pointer to \ref rtc::IMediaPlayerSource.
 * 
 * @return
 * - >0: The id of media player source instance.
 * - < 0: Failure.
 */
					virtual int destroyMediaPlayer (agora_refptr<IMediaPlayer> media_player)  override;



/*
 * Creates a media recorder object and return its pointer.
 * 
 * @param info The RecorderStreamInfo object. It contains the user ID and the channel name.
 * 
 * @return
 * - The pointer to \ref rtc::IMediaRecorder "IMediaRecorder",
 *   if the method call succeeds.
 * - The empty pointer NULL, if the method call fails.
 */
					virtual agora_refptr<agora::rtc::IMediaRecorder> createMediaRecorder (const RecorderStreamInfo & info)  override;



/*
 * Destroy a media recorder object.
 * 
 * @param mediaRecorder The pointer to \ref rtc::IMediaRecorder.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int destroyMediaRecorder (agora_refptr<IMediaRecorder> mediaRecorder)  override;



/*
 * Starts playing and mixing the music file.
 * 
 * This method mixes the specified local audio file with the audio stream from
 * the microphone. You can choose whether the other user can hear the local
 * audio playback and specify the number of playback loops. This method also
 * supports online music playback.
 * 
 * After calling this method successfully, the SDK triggers the
 * 
 * \ref IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (PLAY)
 * callback on the local client.
 * When the audio mixing file playback finishes after calling this method, the
 * SDK triggers the
 * \ref IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (STOPPED)
 * callback on the local client.
 * 
 * @note
 * - Call this method after joining a channel, otherwise issues may occur.
 * - If the local audio mixing file does not exist, or if the SDK does not
 * support the file format or cannot access the music file URL, the SDK returns
 * #WARN_AUDIO_MIXING_OPEN_ERROR (701).
 * - If you want to play an online music file, ensure that the time interval
 * between calling this method is more than 100 ms, or the
 * `AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL(702)` error code occurs.
 * 
 * @param filePath Pointer to the absolute path (including the suffixes of the
 * filename) of the local or online audio file to mix, for example, c:/music/au
 * dio.mp4. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MP4, MPEG-4,
 * SAMI, and WAVE.
 * @param loopback Sets which user can hear the audio mixing:
 * - true: Only the local user can hear the audio mixing.
 * - false: Both users can hear the audio mixing.
 * 
 * @param cycle Sets the number of playback loops:
 * - Positive integer: Number of playback loops.
 * - `-1`: Infinite playback loops.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startAudioMixing (const char * filePath, bool loopback, int cycle)  override;



/*
 * Starts playing and mixing the music file.
 * 
 * This method mixes the specified local audio file with the audio stream from
 * the microphone. You can choose whether the other user can hear the local
 * audio playback and specify the number of playback loops. This method also
 * supports online music playback.
 * 
 * After calling this method successfully, the SDK triggers the
 * 
 * \ref IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (PLAY)
 * callback on the local client.
 * When the audio mixing file playback finishes after calling this method, the
 * SDK triggers the
 * \ref IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (STOPPED)
 * callback on the local client.
 * 
 * @note
 * - Call this method after joining a channel, otherwise issues may occur.
 * - If the local audio mixing file does not exist, or if the SDK does not
 * support the file format or cannot access the music file URL, the SDK returns
 * #WARN_AUDIO_MIXING_OPEN_ERROR (701).
 * - If you want to play an online music file, ensure that the time interval
 * between calling this method is more than 100 ms, or the
 * `AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL(702)` error code occurs.
 * 
 * @param filePath Pointer to the absolute path (including the suffixes of the
 * filename) of the local or online audio file to mix, for example, c:/music/au
 * dio.mp4. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MP4, MPEG-4,
 * SAMI, and WAVE.
 * @param loopback Sets which user can hear the audio mixing:
 * - true: Only the local user can hear the audio mixing.
 * - false: Both users can hear the audio mixing.
 * 
 * @param cycle Sets the number of playback loops:
 * - Positive integer: Number of playback loops.
 * - `-1`: Infinite playback loops.
 * 
 * @param startPos The playback position (ms) of the music file.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startAudioMixing (const char * filePath, bool loopback, int cycle, int startPos)  override;



/*
 * Stops playing and mixing the music file.
 * 
 * Call this method when you are in a channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopAudioMixing ()  override;



/*
 * Pauses playing and mixing the music file.
 * 
 * Call this method when you are in a channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int pauseAudioMixing ()  override;



/*
 * Resumes playing and mixing the music file.
 * 
 * Call this method when you are in a channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int resumeAudioMixing ()  override;



/*
 * Select audio track for the music file.
 * 
 * Call this method when you are in a channel.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int selectAudioTrack (int index)  override;



/*
 * Get audio track count of the music file.
 * 
 * Call this method when you are in a channel.
 * 
 * @return
 * - &ge; 0: Audio track count of the music file, if the method call is successful.
 * - < 0: Failure.
 */
					virtual int getAudioTrackCount ()  override;



/*
 * Adjusts the volume during audio mixing.
 * 
 * Call this method when you are in a channel.
 * 
 * @note This method does not affect the volume of audio effect file playback
 * invoked by the \ref IRtcEngine::playEffect "playEffect" method.
 * 
 * @param volume The audio mixing volume. The value ranges between 0 and 100
 * (default).
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int adjustAudioMixingVolume (int volume)  override;



/*
 * Adjusts the audio mixing volume for publishing (for remote users).
 * @note Call this method when you are in a channel.
 * @param volume Audio mixing volume for publishing. The value ranges between 0 and 100 (default).
 * @return
 *  - 0: Success.
 *  - < 0: Failure.
 */
					virtual int adjustAudioMixingPublishVolume (int volume)  override;



/*
 * Retrieves the audio mixing volume for publishing.
 * This method helps troubleshoot audio volume related issues.
 * @note Call this method when you are in a channel.
 * @return
 *  - &ge; 0: The audio mixing volume for publishing, if this method call succeeds. The value range is [0,100].
 *  - < 0: Failure.
 */
					virtual int getAudioMixingPublishVolume ()  override;



/*
 * Adjusts the audio mixing volume for local playback.
 * @note Call this method when you are in a channel.
 * @param volume Audio mixing volume for local playback. The value ranges between 0 and 100 (default).
 * @return
 *  - 0: Success.
 *  - < 0: Failure.
 */
					virtual int adjustAudioMixingPlayoutVolume (int volume)  override;



/*
 * Retrieves the audio mixing volume for local playback.
 * This method helps troubleshoot audio volume related issues.
 * @note Call this method when you are in a channel.
 * @return
 *  - &ge; 0: The audio mixing volume, if this method call succeeds. The value range is [0,100].
 *  - < 0: Failure.
 */
					virtual int getAudioMixingPlayoutVolume ()  override;



/*
 * Gets the duration (ms) of the music file.
 * 
 * Call this API when you are in a channel.
 * 
 * @return
 * - Returns the audio mixing duration, if the method call is successful.
 * - < 0: Failure.
 */
					virtual int getAudioMixingDuration ()  override;



/*
 * Gets the playback position (ms) of the music file.
 * 
 * Call this method when you are in a channel.
 * 
 * @return
 * - &ge; 0: The current playback position of the audio mixing, if this method
 * call succeeds.
 * - < 0: Failure.
 */
					virtual int getAudioMixingCurrentPosition ()  override;



/*
 * Sets the playback position of the music file to a different starting
 * position (the default plays from the beginning).
 * 
 * @param pos The playback starting position (ms) of the audio mixing file.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioMixingPosition (int pos)  override;



/*
 * In dual-channel music files, different audio data can be stored on the left and right channels.
 * According to actual needs, you can set the channel mode as the original mode,
 * the left channel mode, the right channel mode or the mixed mode
 * 
 * @param mode The mode of channel mode
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioMixingDualMonoMode (media::AUDIO_MIXING_DUAL_MONO_MODE mode)  override;



/*
 * Sets the pitch of the local music file.
 * 
 * When a local music file is mixed with a local human voice, call this method to set the pitch of the local music file only.
 * 
 * @note Call this method after calling \ref IRtcEngine::startAudioMixing "startAudioMixing" and
 * receiving the \ref IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (AUDIO_MIXING_STATE_PLAYING) callback.
 * 
 * @param pitch Sets the pitch of the local music file by chromatic scale. The default value is 0,
 * which means keeping the original pitch. The value ranges from -12 to 12, and the pitch value between
 * consecutive values is a chromatic value. The greater the absolute value of this parameter, the
 * higher or lower the pitch of the local music file.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioMixingPitch (int pitch)  override;



/*
 * Sets the playback speed of the current music file.
 * 
 * @note Call this method after calling \ref IRtcEngine::startAudioMixing(const char*,bool,bool,int,int) "startAudioMixing" [2/2]
 * and receiving the \ref IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (AUDIO_MIXING_STATE_PLAYING) callback.
 * 
 * @param speed The playback speed. Agora recommends that you limit this value to between 50 and 400, defined as follows:
 * - 50: Half the original speed.
 * - 100: The original speed.
 * - 400: 4 times the original speed.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioMixingPlaybackSpeed (int speed)  override;



/*
 * Gets the volume of audio effects.
 * 
 * @return
 * - &ge; 0: The volume of audio effects. The value ranges between 0 and 100 (original volume).
 * - < 0: Failure.
 */
					virtual int getEffectsVolume ()  override;



/*
 * Sets the volume of audio effects.
 * 
 * @param volume The volume of audio effects. The value ranges between 0
 * and 100 (original volume).
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setEffectsVolume (int volume)  override;



/*
 * Preloads a specified audio effect.
 * 
 * This method preloads only one specified audio effect into the memory each time
 * it is called. To preload multiple audio effects, call this method multiple times.
 * 
 * After preloading, you can call \ref IRtcEngine::playEffect "playEffect"
 * to play the preloaded audio effect or call
 * \ref IRtcEngine::playAllEffects "playAllEffects" to play all the preloaded
 * audio effects.
 * 
 * @note
 * - To ensure smooth communication, limit the size of the audio effect file.
 * - Agora recommends calling this method before joining the channel.
 * 
 * @param soundId The ID of the audio effect.
 * @param filePath The absolute path of the local audio effect file or the URL
 * of the online audio effect file. Supported audio formats: mp3, mp4, m4a, aac,
 * 3gp, mkv, and wav.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int preloadEffect (int soundId, const char * filePath, int startPos = 0)  override;



/*
 * Plays a specified audio effect.
 * 
 * After calling \ref IRtcEngine::preloadEffect "preloadEffect", you can call
 * this method to play the specified audio effect for all users in
 * the channel.
 * 
 * This method plays only one specified audio effect each time it is called.
 * To play multiple audio effects, call this method multiple times.
 * 
 * @note
 * - Agora recommends playing no more than three audio effects at the same time.
 * - The ID and file path of the audio effect in this method must be the same
 * as that in the \ref IRtcEngine::preloadEffect "preloadEffect" method.
 * 
 * @param soundId The ID of the audio effect.
 * @param filePath The absolute path of the local audio effect file or the URL
 * of the online audio effect file. Supported audio formats: mp3, mp4, m4a, aac,
 * 3gp, mkv, and wav.
 * @param loopCount The number of times the audio effect loops:
 * - `-1`: Play the audio effect in an indefinite loop until
 * \ref IRtcEngine::stopEffect "stopEffect" or
 * \ref IRtcEngine::stopAllEffects "stopAllEffects"
 * - `0`: Play the audio effect once.
 * - `1`: Play the audio effect twice.
 * @param pitch The pitch of the audio effect. The value ranges between 0.5 and 2.0.
 * The default value is `1.0` (original pitch). The lower the value, the lower the pitch.
 * @param pan The spatial position of the audio effect. The value ranges between -1.0 and 1.0:
 * - `-1.0`: The audio effect displays to the left.
 * - `0.0`: The audio effect displays ahead.
 * - `1.0`: The audio effect displays to the right.
 * @param gain The volume of the audio effect. The value ranges between 0 and 100.
 * The default value is `100` (original volume). The lower the value, the lower
 * the volume of the audio effect.
 * @param publish Sets whether to publish the audio effect to the remote:
 * - true: Publish the audio effect to the remote.
 * - false: (Default) Do not publish the audio effect to the remote.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int playEffect (int soundId, const char * filePath, int loopCount, double pitch, double pan, int gain, bool publish = false, int startPos = 0)  override;



/*
 * Plays all audio effects.
 * 
 * After calling \ref IRtcEngine::preloadEffect "preloadEffect" multiple times
 * to preload multiple audio effects into the memory, you can call this
 * method to play all the specified audio effects for all users in
 * the channel.
 * 
 * @param loopCount The number of times the audio effect loops:
 * - `-1`: Play the audio effect in an indefinite loop until
 * \ref IRtcEngine::stopEffect "stopEffect" or
 * \ref IRtcEngine::stopAllEffects "stopAllEffects"
 * - `0`: Play the audio effect once.
 * - `1`: Play the audio effect twice.
 * @param pitch The pitch of the audio effect. The value ranges between 0.5 and 2.0.
 * The default value is `1.0` (original pitch). The lower the value, the lower the pitch.
 * @param pan The spatial position of the audio effect. The value ranges between -1.0 and 1.0:
 * - `-1.0`: The audio effect displays to the left.
 * - `0.0`: The audio effect displays ahead.
 * - `1.0`: The audio effect displays to the right.
 * @param gain The volume of the audio effect. The value ranges between 0 and 100.
 * The default value is `100` (original volume). The lower the value, the lower
 * the volume of the audio effect.
 * @param publish Sets whether to publish the audio effect to the remote:
 * - true: Publish the audio effect to the remote.
 * - false: (Default) Do not publish the audio effect to the remote.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int playAllEffects (int loopCount, double pitch, double pan, int gain, bool publish = false)  override;



/*
 * Gets the volume of the specified audio effect.
 * 
 * @param soundId The ID of the audio effect.
 * 
 * @return
 * - &ge; 0: The volume of the specified audio effect. The value ranges
 * between 0 and 100 (original volume).
 * - < 0: Failure.
 */
					virtual int getVolumeOfEffect (int soundId)  override;



/*
 * Sets the volume of the specified audio effect.
 * 
 * @param soundId The ID of the audio effect.
 * @param volume The volume of the specified audio effect. The value ranges
 * between 0 and 100 (original volume).
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVolumeOfEffect (int soundId, int volume)  override;



/*
 * Pauses playing the specified audio effect.
 * 
 * @param soundId The ID of the audio effect.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int pauseEffect (int soundId)  override;



/*
 * Pauses playing audio effects.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int pauseAllEffects ()  override;



/*
 * Resumes playing the specified audio effect.
 * 
 * @param soundId The ID of the audio effect.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int resumeEffect (int soundId)  override;



/*
 * Resumes playing audio effects.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int resumeAllEffects ()  override;



/*
 * Stops playing the specified audio effect.
 * 
 * @param soundId The ID of the audio effect.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopEffect (int soundId)  override;



/*
 * Stops playing audio effects.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopAllEffects ()  override;



/*
 * Releases the specified preloaded audio effect from the memory.
 * 
 * @param soundId The ID of the audio effect.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int unloadEffect (int soundId)  override;



/*
 * Releases preloaded audio effects from the memory.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int unloadAllEffects ()  override;



/*
 * Gets the duration of the audio effect file.
 * @note
 * - Call this method after joining a channel.
 * - For the audio file formats supported by this method, see [What formats of audio files does the Agora RTC SDK support](https://docs.agora.io/en/faq/audio_format).
 * 
 * @param filePath The absolute path or URL address (including the filename extensions)
 * of the music file. For example: `C:\music\audio.mp4`.
 * When you access a local file on Android, Agora recommends passing a URI address or the path starts
 * with `/assets/` in this parameter.
 * 
 * @return
 * - &ge; 0: A successful method call. Returns the total duration (ms) of
 * the specified audio effect file.
 * - < 0: Failure.
 *  - `-22(ERR_RESOURCE_LIMITED)`: Cannot find the audio effect file. Please
 * set a correct `filePath`.
 */
					virtual int getEffectDuration (const char * filePath)  override;



/*
 * Sets the playback position of an audio effect file.
 * After a successful setting, the local audio effect file starts playing at the specified position.
 * 
 * @note Call this method after \ref IRtcEngine::playEffect(int,const char*,int,double,double,int,bool,int) "playEffect" .
 * 
 * @param soundId Audio effect ID. Ensure that this parameter is set to the
 * same value as in \ref IRtcEngine::playEffect(int,const char*,int,double,double,int,bool,int) "playEffect" .
 * @param pos The playback position (ms) of the audio effect file.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - `-22(ERR_RESOURCE_LIMITED)`: Cannot find the audio effect file. Please
 * set a correct `soundId`.
 */
					virtual int setEffectPosition (int soundId, int pos)  override;



/*
 * Gets the playback position of the audio effect file.
 * @note Call this method after \ref IRtcEngine::playEffect(int,const char*,int,double,double,int,bool,int) "playEffect" .
 * 
 * @param soundId Audio effect ID. Ensure that this parameter is set to the
 * same value as in \ref IRtcEngine::playEffect(int,const char*,int,double,double,int,bool,int) "playEffect" .
 * 
 * @return
 * - &ge; 0: A successful method call. Returns the playback position (ms) of
 * the specified audio effect file.
 * - < 0: Failure.
 *  - `-22(ERR_RESOURCE_LIMITED)`: Cannot find the audio effect file. Please
 * set a correct `soundId`.
 */
					virtual int getEffectCurrentPosition (int soundId)  override;



/*
 * Enables/Disables stereo panning for remote users.
 * 
 * Ensure that you call this method before joinChannel to enable stereo panning for remote users so that the local user can track the position of a remote user by calling \ref agora::rtc::IRtcEngine::setRemoteVoicePosition "setRemoteVoicePosition".
 * 
 * @param enabled Sets whether or not to enable stereo panning for remote users:
 * - true: enables stereo panning.
 * - false: disables stereo panning.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableSoundPositionIndication (bool enabled)  override;



/*
 * Sets the sound position and gain of a remote user.
 * 
 * When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.
 * 
 * @note
 * - For this method to work, enable stereo panning for remote users by calling the \ref agora::rtc::IRtcEngine::enableSoundPositionIndication "enableSoundPositionIndication" method before joining a channel.
 * - This method requires hardware support. For the best sound positioning, we recommend using a wired headset.
 * - Ensure that you call this method after joining a channel.
 * 
 * @param uid The ID of the remote user.
 * @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:
 * - 0.0: the remote sound comes from the front.
 * - -1.0: the remote sound comes from the left.
 * - 1.0: the remote sound comes from the right.
 * @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteVoicePosition (uid_t uid, double pan, double gain)  override;



/*
 * enable spatial audio
 * 
 * @param enabled enable/disable spatial audio:
 * - true: enable spatial audio.
 * - false: disable spatial audio.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableSpatialAudio (bool enabled)  override;



/*
 * Sets remote user parameters for spatial audio
 * 
 * @param uid The ID of the remote user.
 * @param param spatial audio parameters: SpatialAudioParams.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteUserSpatialAudioParams (uid_t uid, const agora::SpatialAudioParams & params)  override;



/*
 * Sets an SDK preset voice beautifier effect.
 * 
 * Call this method to set an SDK preset voice beautifier effect for the local user who sends an
 * audio stream. After setting a voice beautifier effect, all users in the channel can hear the
 * effect.
 * 
 * You can set different voice beautifier effects for different scenarios. See *Set the Voice
 * Beautifier and Audio Effects*.
 * 
 * To achieve better audio effect quality, Agora recommends calling \ref
 * IRtcEngine::setAudioProfile "setAudioProfile" and setting the `scenario` parameter to
 * `AUDIO_SCENARIO_GAME_STREAMING(3)` and the `profile` parameter to
 * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
 * calling this method.
 * 
 * @note
 * - You can call this method either before or after joining a channel.
 * - Do not set the `profile` parameter of \ref IRtcEngine::setAudioProfile "setAudioProfile" to
 * `AUDIO_PROFILE_SPEECH_STANDARD(1)` or `AUDIO_PROFILE_IOT(6)`; otherwise, this method call
 * fails.
 * - This method works best with the human voice. Agora does not recommend using this method for
 * audio containing music.
 * - After calling this method, Agora recommends not calling the following methods, because they
 * can override \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters":
 *  - \ref IRtcEngine::setAudioEffectPreset "setAudioEffectPreset"
 *  - \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"
 *  - \ref IRtcEngine::setLocalVoicePitch "setLocalVoicePitch"
 *  - \ref IRtcEngine::setLocalVoiceEqualization "setLocalVoiceEqualization"
 *  - \ref IRtcEngine::setLocalVoiceReverb "setLocalVoiceReverb"
 *  - \ref IRtcEngine::setVoiceBeautifierParameters "setVoiceBeautifierParameters"
 * 
 * @param preset The options for SDK preset voice beautifier effects: #VOICE_BEAUTIFIER_PRESET.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVoiceBeautifierPreset (VOICE_BEAUTIFIER_PRESET preset)  override;



/*
 * Sets an SDK preset audio effect.
 * 
 * Call this method to set an SDK preset audio effect for the local user who sends an audio
 * stream. This audio effect does not change the gender characteristics of the original voice.
 * After setting an audio effect, all users in the channel can hear the effect.
 * 
 * You can set different audio effects for different scenarios. See *Set the Voice Beautifier and
 * Audio Effects*.
 * 
 * To achieve better audio effect quality, Agora recommends calling \ref
 * IRtcEngine::setAudioProfile "setAudioProfile" and setting the `scenario` parameter to
 * `AUDIO_SCENARIO_GAME_STREAMING(3)` before calling this method.
 * 
 * @note
 * - You can call this method either before or after joining a channel.
 * - Do not set the profile `parameter` of `setAudioProfile` to `AUDIO_PROFILE_SPEECH_STANDARD(1)`
 * or `AUDIO_PROFILE_IOT(6)`; otherwise, this method call fails.
 * - This method works best with the human voice. Agora does not recommend using this method for
 * audio containing music.
 * - If you call this method and set the `preset` parameter to enumerators except
 * `ROOM_ACOUSTICS_3D_VOICE` or `PITCH_CORRECTION`, do not call \ref
 * IRtcEngine::setAudioEffectParameters "setAudioEffectParameters"; otherwise,
 * `setAudioEffectParameters` overrides this method.
 * - After calling this method, Agora recommends not calling the following methods, because they
 * can override `setAudioEffectPreset`:
 *  - \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"
 *  - \ref IRtcEngine::setLocalVoicePitch "setLocalVoicePitch"
 *  - \ref IRtcEngine::setLocalVoiceEqualization "setLocalVoiceEqualization"
 *  - \ref IRtcEngine::setLocalVoiceReverb "setLocalVoiceReverb"
 *  - \ref IRtcEngine::setVoiceBeautifierParameters "setVoiceBeautifierParameters"
 * 
 * @param preset The options for SDK preset audio effects. See #AUDIO_EFFECT_PRESET.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioEffectPreset (AUDIO_EFFECT_PRESET preset)  override;



/*
 * Sets an SDK preset voice conversion.
 * 
 * Call this method to set an SDK preset voice conversion for the local user who sends an audio
 * stream. After setting an voice conversion, all users in the channel can hear the effect.
 * 
 * You can set different voice conversion for different scenarios. See *Set the Voice Beautifier and
 * Audio Effects*.
 * 
 * To achieve better voice conversion quality, Agora recommends calling \ref
 * IRtcEngine::setAudioProfile "setAudioProfile" and setting the `scenario` parameter to
 * `AUDIO_SCENARIO_GAME_STREAMING(3)` before calling this method.
 * 
 * @note
 * - You can call this method either before or after joining a channel.
 * - Do not set the profile `parameter` of `setAudioProfile` to `AUDIO_PROFILE_SPEECH_STANDARD(1)`
 * or `AUDIO_PROFILE_IOT(6)`; otherwise, this method call fails.
 * - This method works best with the human voice. Agora does not recommend using this method for
 * audio containing music.
 * - If you call this method and set the `preset` parameter to enumerators,
 * - After calling this method, Agora recommends not calling the following methods, because they
 * can override `setVoiceConversionPreset`:
 *  - \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"
 *  - \ref IRtcEngine::setAudioEffectPreset "setAudioEffectPreset"
 *  - \ref IRtcEngine::setLocalVoicePitch "setLocalVoicePitch"
 *  - \ref IRtcEngine::setLocalVoiceFormant "setLocalVoiceFormant"
 *  - \ref IRtcEngine::setLocalVoiceEqualization "setLocalVoiceEqualization"
 *  - \ref IRtcEngine::setLocalVoiceReverb "setLocalVoiceReverb"
 *  - \ref IRtcEngine::setVoiceBeautifierParameters "setVoiceBeautifierParameters"
 *  - \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters"
 * 
 * @param preset The options for SDK preset voice conversion. See #VOICE_CONVERSION_PRESET.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVoiceConversionPreset (VOICE_CONVERSION_PRESET preset)  override;



/*
 * Sets parameters for SDK preset audio effects.
 * 
 * Call this method to set the following parameters for the local user who send an audio stream:
 * - 3D voice effect: Sets the cycle period of the 3D voice effect.
 * - Pitch correction effect: Sets the basic mode and tonic pitch of the pitch correction effect.
 * Different songs have different modes and tonic pitches. Agora recommends bounding this method
 * with interface elements to enable users to adjust the pitch correction interactively.
 * 
 * After setting parameters, all users in the channel can hear the relevant effect.
 * 
 * You can call this method directly or after \ref IRtcEngine::setAudioEffectPreset
 * "setAudioEffectPreset". If you call this method after \ref IRtcEngine::setAudioEffectPreset
 * "setAudioEffectPreset", ensure that you set the preset parameter of `setAudioEffectPreset` to
 * `ROOM_ACOUSTICS_3D_VOICE` or `PITCH_CORRECTION` and then call this method to set the same
 * enumerator; otherwise, this method overrides `setAudioEffectPreset`.
 * 
 * @note
 * - You can call this method either before or after joining a channel.
 * - To achieve better audio effect quality, Agora recommends calling \ref
 * IRtcEngine::setAudioProfile "setAudioProfile" and setting the `scenario` parameter to
 * `AUDIO_SCENARIO_GAME_STREAMING(3)` before calling this method.
 * - Do not set the `profile` parameter of \ref IRtcEngine::setAudioProfile "setAudioProfile" to
 * `AUDIO_PROFILE_SPEECH_STANDARD(1)` or `AUDIO_PROFILE_IOT(6)`; otherwise, this method call
 * fails.
 * - This method works best with the human voice. Agora does not recommend using this method for
 * audio containing music.
 * - After calling this method, Agora recommends not calling the following methods, because they
 * can override `setAudioEffectParameters`:
 *  - \ref IRtcEngine::setAudioEffectPreset "setAudioEffectPreset"
 *  - \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"
 *  - \ref IRtcEngine::setLocalVoicePitch "setLocalVoicePitch"
 *  - \ref IRtcEngine::setLocalVoiceEqualization "setLocalVoiceEqualization"
 *  - \ref IRtcEngine::setLocalVoiceReverb "setLocalVoiceReverb"
 *  - \ref IRtcEngine::setVoiceBeautifierParameters "setVoiceBeautifierParameters"
 * @param preset The options for SDK preset audio effects:
 * - 3D voice effect: `ROOM_ACOUSTICS_3D_VOICE`.
 *  - Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and set the `profile` parameter to
 * `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
 * setting this enumerator; otherwise, the enumerator setting does not take effect.
 *  - If the 3D voice effect is enabled, users need to use stereo audio playback devices to hear
 * the anticipated voice effect.
 * - Pitch correction effect: `PITCH_CORRECTION`. To achieve better audio effect quality, Agora
 * recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting the `profile`
 * parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or
 * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting this enumerator.
 * @param param1
 * - If you set `preset` to `ROOM_ACOUSTICS_3D_VOICE`, the `param1` sets the cycle period of the
 * 3D voice effect. The value range is [1,60] and the unit is a second. The default value is 10
 * seconds, indicating that the voice moves around you every 10 seconds.
 * - If you set `preset` to `PITCH_CORRECTION`, `param1` sets the basic mode of the pitch
 * correction effect:
 *  - `1`: (Default) Natural major scale.
 *  - `2`: Natural minor scale.
 *  - `3`: Japanese pentatonic scale.
 * @param param2
 * - If you set `preset` to `ROOM_ACOUSTICS_3D_VOICE`, you need to set `param2` to `0`.
 * - If you set `preset` to `PITCH_CORRECTION`, `param2` sets the tonic pitch of the pitch
 * correction effect:
 *  - `1`: A
 *  - `2`: A#
 *  - `3`: B
 *  - `4`: (Default) C
 *  - `5`: C#
 *  - `6`: D
 *  - `7`: D#
 *  - `8`: E
 *  - `9`: F
 *  - `10`: F#
 *  - `11`: G
 *  - `12`: G#
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAudioEffectParameters (AUDIO_EFFECT_PRESET preset, int param1, int param2)  override;



/*
 * Sets parameters for SDK preset voice beautifier effects.
 * 
 * Call this method to set a gender characteristic and a reverberation effect for the singing
 * beautifier effect. This method sets parameters for the local user who sends an audio stream.
 * 
 * After you call this method successfully, all users in the channel can hear the relevant effect.
 * 
 * To achieve better audio effect quality, before you call this method, Agora recommends calling
 * \ref IRtcEngine::setAudioProfile "setAudioProfile", and setting the `scenario` parameter as
 * `AUDIO_SCENARIO_GAME_STREAMING(3)` and the `profile` parameter as
 * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
 * 
 * @note
 * - You can call this method either before or after joining a channel.
 * - Do not set the `profile` parameter of \ref IRtcEngine::setAudioProfile "setAudioProfile" as
 * `AUDIO_PROFILE_SPEECH_STANDARD(1)` or `AUDIO_PROFILE_IOT(6)`; otherwise, this method call does
 * not take effect.
 * - This method works best with the human voice. Agora does not recommend using this method for
 * audio containing music.
 * - After you call this method, Agora recommends not calling the following methods, because they
 * can override `setVoiceBeautifierParameters`:
 *    - \ref IRtcEngine::setAudioEffectPreset "setAudioEffectPreset"
 *    - \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters"
 *    - \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"
 *    - \ref IRtcEngine::setLocalVoicePitch "setLocalVoicePitch"
 *    - \ref IRtcEngine::setLocalVoiceEqualization "setLocalVoiceEqualization"
 *    - \ref IRtcEngine::setLocalVoiceReverb "setLocalVoiceReverb"
 * 
 * @param preset The options for SDK preset voice beautifier effects:
 * - `SINGING_BEAUTIFIER`: Singing beautifier effect.
 * @param param1 The gender characteristics options for the singing voice:
 * - `1`: A male-sounding voice.
 * - `2`: A female-sounding voice.
 * @param param2 The reverberation effects options:
 * - `1`: The reverberation effect sounds like singing in a small room.
 * - `2`: The reverberation effect sounds like singing in a large room.
 * - `3`: The reverberation effect sounds like singing in a hall.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVoiceBeautifierParameters (VOICE_BEAUTIFIER_PRESET preset, int param1, int param2)  override;



/*
 * Set parameters for SDK preset voice conversion.
 * 
 * @note
 * - reserved interface
 * 
 * @param preset The options for SDK preset audio effects. See #VOICE_CONVERSION_PRESET.
 * @param param1 reserved.
 * @param param2 reserved.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVoiceConversionParameters (VOICE_CONVERSION_PRESET preset, int param1, int param2)  override;



/*
 * Changes the voice pitch of the local speaker.
 * 
 * @param pitch The voice pitch. The value ranges between 0.5 and 2.0. The lower
 * the value, the lower the voice pitch. The default value is 1.0 (no change to
 * the local voice pitch).
 * 
 * @return
 * - 0: Success.
 * - -1: Failure.
 */
					virtual int setLocalVoicePitch (double pitch)  override;



/*
 * Changes the voice formant ratio for local speaker.
 * 
 * @param formantRatio The voice formant ratio. The value ranges between -1.0 and 1.0.
 * The lower the value, the deeper the sound, and the higher the value, the more it
 * sounds like a child. The default value is 0.0 (the local user's voice will not be changed).
 * 
 * @return
 * - 0: Success.
 * - -1: Failure.
 */
					virtual int setLocalVoiceFormant (double formantRatio)  override;



/*
 * Sets the local voice equalization effect.
 * 
 * @param bandFrequency The band frequency ranging from 0 to 9, representing the
 * respective 10-band center frequencies of the voice effects, including 31, 62,
 * 125, 500, 1k, 2k, 4k, 8k, and 16k Hz.
 * @param bandGain  Gain of each band in dB. The value ranges from -15 to 15. The
 * default value is 0.
 * @return
 * - 0: Success.
 * - -1: Failure.
 */
					virtual int setLocalVoiceEqualization (AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)  override;



/*
 * Sets the local voice reverberation.
 * 
 * @param reverbKey The reverberation key: #AUDIO_REVERB_TYPE.
 * @param value The value of the reverberation key: #AUDIO_REVERB_TYPE.
 * @return
 * - 0: Success.
 * - -1: Failure.
 */
					virtual int setLocalVoiceReverb (AUDIO_REVERB_TYPE reverbKey, int value)  override;



/*
 * Sets preset audio playback effect for remote headphones after remote audio is mixed.
 * 
 * @param preset The preset key: #HEADPHONE_EQUALIZER_PRESET.
 * - HEADPHONE_EQUALIZER_OFF = 0x00000000 : Turn off the eualizer effect for headphones.
 * - HEADPHONE_EQUALIZER_OVEREAR = 0x04000001 : For over-ear headphones only.
 * - HEADPHONE_EQUALIZER_INEAR = 0x04000002 : For in-ear headphones only.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 */
					virtual int setHeadphoneEQPreset (HEADPHONE_EQUALIZER_PRESET preset)  override;



/*
 * Sets the parameters of audio playback effect for remote headphones after remote audio is mixed.
 * 
 * @param lowGain The higher the parameter value, the deeper the sound. The value range is [-10,10].
 * @param highGain The higher the parameter value, the sharper the sound. The value range is [-10,10].
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 */
					virtual int setHeadphoneEQParameters (int lowGain, int highGain)  override;



/*
 * Enables or disables the voice AI tuner.
 * 
 * @param enabled Determines whether to enable the voice AI tuner:
 * - true: Enable the voice AI tuner
 * - false: (default) Disable the voice AI tuner.
 * 
 * @param type. The options for SDK voice AI tuner types. See #VOICE_AI_TUNER_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableVoiceAITuner (bool enabled, VOICE_AI_TUNER_TYPE type)  override;



/*
 * **DEPRECATED** Specifies an SDK output log file.
 * 
 * The log file records all log data for the SDK’s operation. Ensure that the
 * directory for the log file exists and is writable.
 * 
 * @note
 * Ensure that you call this method immediately after \ref initialize "initialize",
 * or the output log may not be complete.
 * 
 * @param filePath File path of the log file. The string of the log file is in UTF-8.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLogFile (const char * filePath)  override;



/*
 * Sets the output log filter level of the SDK.
 * 
 * You can use one or a combination of the filters. The log filter level follows the
 * sequence of `OFF`, `CRITICAL`, `ERROR`, `WARNING`, `INFO`, and `DEBUG`. Choose a filter level
 * and you will see logs preceding that filter level. For example, if you set the log filter level to
 * `WARNING`, you see the logs within levels `CRITICAL`, `ERROR`, and `WARNING`.
 * 
 * @param filter The log filter level:
 * - `LOG_FILTER_DEBUG(0x80f)`: Output all API logs. Set your log filter as DEBUG
 * if you want to get the most complete log file.
 * - `LOG_FILTER_INFO(0x0f)`: Output logs of the CRITICAL, ERROR, WARNING, and INFO
 * level. We recommend setting your log filter as this level.
 * - `LOG_FILTER_WARNING(0x0e)`: Output logs of the CRITICAL, ERROR, and WARNING level.
 * - `LOG_FILTER_ERROR(0x0c)`: Output logs of the CRITICAL and ERROR level.
 * - `LOG_FILTER_CRITICAL(0x08)`: Output logs of the CRITICAL level.
 * - `LOG_FILTER_OFF(0)`: Do not output any log.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLogFilter (unsigned int filter)  override;



/*
 * Sets the output log level of the SDK.
 * 
 * You can set the SDK to ouput the log files of the specified level.
 * 
 * @param level The log level:
 * - `LOG_LEVEL_NONE (0x0000)`: Do not output any log file.
 * - `LOG_LEVEL_INFO (0x0001)`: (Recommended) Output log files of the INFO level.
 * - `LOG_LEVEL_WARN (0x0002)`: Output log files of the WARN level.
 * - `LOG_LEVEL_ERROR (0x0004)`: Output log files of the ERROR level.
 * - `LOG_LEVEL_FATAL (0x0008)`: Output log files of the FATAL level.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLogLevel (commons::LOG_LEVEL level)  override;



/*
 * Sets the log file size (KB).
 * 
 * The SDK has two log files, each with a default size of 512 KB. If you set
 * `fileSizeInBytes` as 1024 KB, the SDK outputs log files with a total
 * maximum size of 2 MB.
 * If the total size of the log files exceed the set value,
 * the new output log files overwrite the old output log files.
 * 
 * @param fileSizeInKBytes The SDK log file size (KB).
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLogFileSize (unsigned int fileSizeInKBytes)  override;



/*
 * Upload current log file immediately to server.
 *  only use this when an error occurs
 *  block before log file upload success or timeout.
 * 
 *  @return
 *  - 0: Success.
 *  - < 0: Failure.
 */
					virtual int uploadLogFile (agora::util::AString & requestId)  override;



/*
 * Updates the display mode of the local video view.
 * 
 * After initializing the local video view, you can call this method to  update its rendering mode.
 * It affects only the video view that the local user sees, not the published local video stream.
 * 
 * @note
 * - Ensure that you have called \ref setupLocalVideo "setupLocalVideo" to initialize the local video
 * view before this method.
 * - During a call, you can call this method as many times as necessary to update the local video view.
 * 
 * @param renderMode Sets the local display mode. See #RENDER_MODE_TYPE.
 * @param mirrorMode Sets the local mirror mode. See #VIDEO_MIRROR_MODE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLocalRenderMode (media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode)  override;



/*
 * Updates the display mode of the video view of a remote user.
 * 
 * After initializing the video view of a remote user, you can call this method to update its
 * rendering and mirror modes. This method affects only the video view that the local user sees.
 * 
 * @note
 * - Ensure that you have called \ref setupRemoteVideo "setupRemoteVideo" to initialize the remote video
 * view before calling this method.
 * - During a call, you can call this method as many times as necessary to update the display mode
 * of the video view of a remote user.
 * 
 * @param uid ID of the remote user.
 * @param renderMode Sets the remote display mode. See #RENDER_MODE_TYPE.
 * @param mirrorMode Sets the mirror type. See #VIDEO_MIRROR_MODE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteRenderMode (uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode)  override;



/*
 * Sets the target frames per second (FPS) for the local render target.
 * 
 * @param sourceType The type of video source.
 * @param targetFps The target frames per second to be set.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLocalRenderTargetFps (VIDEO_SOURCE_TYPE sourceType, int targetFps)  override;



/*
 * Sets the target frames per second (FPS) for the remote render target.
 * 
 * @param targetFps The target frames per second to be set for the remote render target.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteRenderTargetFps (int targetFps)  override;



/*
 * Updates the display mode of the local video view.
 * 
 * After initializing the local video view, you can call this method to  update its rendering mode.
 * It affects only the video view that the local user sees, not the published local video stream.
 * 
 * @note
 * - Ensure that you have called \ref setupLocalVideo "setupLocalVideo" to initialize the local video
 * view before this method.
 * - During a call, you can call this method as many times as necessary to update the local video view.
 * 
 * @param renderMode Sets the local display mode. See #RENDER_MODE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLocalRenderMode (media::base::RENDER_MODE_TYPE renderMode) __deprecated override;



/*
 * Sets the local video mirror mode.
 * 
 * Use this method before calling the \ref startPreview "startPreview" method, or the mirror mode
 * does not take effect until you call the `startPreview` method again.
 * @param mirrorMode Sets the local video mirror mode. See #VIDEO_MIRROR_MODE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLocalVideoMirrorMode (VIDEO_MIRROR_MODE_TYPE mirrorMode) __deprecated override;



/*
 * Enables or disables the dual video stream mode.
 * 
 * If dual-stream mode is enabled, the subscriber can choose to receive the high-stream
 * (high-resolution high-bitrate video stream) or low-stream (low-resolution low-bitrate video stream)
 * video using \ref setRemoteVideoStreamType "setRemoteVideoStreamType".
 * 
 * @param enabled
 * - true: Enable the dual-stream mode.
 * - false: (default) Disable the dual-stream mode.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableDualStreamMode (bool enabled) __deprecated override;



/*
 * Enables or disables the dual video stream mode.
 * 
 * If dual-stream mode is enabled, the subscriber can choose to receive the high-stream
 * (high-resolution high-bitrate video stream) or low-stream (low-resolution low-bitrate video stream)
 * video using \ref setRemoteVideoStreamType "setRemoteVideoStreamType".
 * 
 * @param enabled
 * - true: Enable the dual-stream mode.
 * - false: (default) Disable the dual-stream mode.
 * @param streamConfig
 * - The minor stream config
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableDualStreamMode (bool enabled, const SimulcastStreamConfig & streamConfig) __deprecated override;



/*
 * Enables, disables or auto enable the dual video stream mode.
 * 
 * If dual-stream mode is enabled, the subscriber can choose to receive the high-stream
 * (high-resolution high-bitrate video stream) or low-stream (low-resolution low-bitrate video stream)
 * video using \ref setRemoteVideoStreamType "setRemoteVideoStreamType".
 * 
 * @param mode
 * - The dual stream mode
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setDualStreamMode (SIMULCAST_STREAM_MODE mode)  override;



/*
 * Sets the multi-layer video stream configuration.
 * 
 * If multi-layer is configured, the subscriber can choose to receive the coresponding layer
 * of video stream using {@link setRemoteVideoStreamType setRemoteVideoStreamType}.
 * 
 * @param simulcastConfig
 * - The configuration for multi-layer video stream. It includes seven layers, ranging from
 *   STREAM_LAYER_1 to STREAM_LOW. A maximum of 3 layers can be enabled simultaneously.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 * @technical preview
 */
					virtual int setSimulcastConfig (const SimulcastConfig & simulcastConfig)  override;



/*
 * Enables, disables or auto enable the dual video stream mode.
 * 
 * If dual-stream mode is enabled, the subscriber can choose to receive the high-stream
 * (high-resolution high-bitrate video stream) or low-stream (low-resolution low-bitrate video stream)
 * video using \ref setRemoteVideoStreamType "setRemoteVideoStreamType".
 * 
 * @param mode Dual stream mode: #SIMULCAST_STREAM_MODE.
 * @param streamConfig Configurations of the low stream: SimulcastStreamConfig.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setDualStreamMode (SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig & streamConfig)  override;



/*
 * Sets the external audio track.
 * 
 * @note
 * Ensure that you call this method before joining the channel.
 * 
 * @param trackId custom audio track id.
 * @param enabled Determines whether to local playback the external audio track:
 * - true: Local playback the external audio track.
 * - false: Local don`t playback the external audio track.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableCustomAudioLocalPlayback (track_id_t trackId, bool enabled)  override;



/*
 * Sets the audio recording format for the
 * \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" callback.
 * 
 * @param sampleRate The sample rate (Hz) of the audio data returned in the `onRecordAudioFrame` callback, which can set be
 * as 8000, 16000, 32000, 44100, or 48000.
 * @param channel The number of audio channels of the audio data returned in the `onRecordAudioFrame` callback, which can
 * be set as 1 or 2:
 * - 1: Mono.
 * - 2: Stereo.
 * @param mode This mode is deprecated.
 * @param samplesPerCall not support. Sampling points in the called data returned in
 * onRecordAudioFrame(). For example, it is usually set as 1024 for stream
 * pushing.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRecordingAudioFrameParameters (int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)  override;



/*
 * Sets the audio playback format for the
 * \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.
 * 
 * @param sampleRate Sets the sample rate (Hz) of the audio data returned in the `onPlaybackAudioFrame` callback,
 * which can set be as 8000, 16000, 32000, 44100, or 48000.
 * @param channel The number of channels of the audio data returned in the `onPlaybackAudioFrame` callback, which
 * can be set as 1 or 2:
 * - 1: Mono
 * - 2: Stereo
 * @param mode Deprecated. The use mode of the onPlaybackAudioFrame() callback:
 * agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE.
 * @param samplesPerCall not support. Sampling points in the called data returned in
 * onPlaybackAudioFrame(). For example, it is usually set as 1024 for stream
 * pushing.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setPlaybackAudioFrameParameters (int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)  override;



/*
 * Sets the mixed audio format for the
 * \ref agora::media::IAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" callback.
 * 
 * @param sampleRate The sample rate (Hz) of the audio data returned in the `onMixedAudioFrame` callback, which can set
 * be as 8000, 16000, 32000, 44100, or 48000.
 * @param channel The number of channels of the audio data in `onMixedAudioFrame` callback, which can be set as 1 or 2:
 * - 1: Mono
 * - 2: Stereo
 * @param samplesPerCall not support. Sampling points in the called data returned in
 * `onMixedAudioFrame`. For example, it is usually set as 1024 for stream pushing.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setMixedAudioFrameParameters (int sampleRate, int channel, int samplesPerCall)  override;



/*
 * Sets the audio ear monitoring format for the
 * \ref agora::media::IAudioFrameObserver::onEarMonitoringAudioFrame "onEarMonitoringAudioFrame" callback.
 * 
 * @param sampleRate Sets the sample rate (Hz) of the audio data returned in the `onEarMonitoringAudioFrame` callback,
 * which can set be as 8000, 16000, 32000, 44100, or 48000.
 * @param channel The number of channels of the audio data returned in the `onEarMonitoringAudioFrame` callback, which
 * can be set as 1 or 2:
 * - 1: Mono
 * - 2: Stereo
 * @param mode Deprecated. The use mode of the onEarMonitoringAudioFrame() callback:
 * agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE.
 * @param samplesPerCall not support. Sampling points in the called data returned in
 * onEarMonitoringAudioFrame(). For example, it is usually set as 1024 for stream
 * pushing.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setEarMonitoringAudioFrameParameters (int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)  override;



/*
 * Sets the audio playback format before mixing in the
 * \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrameBeforeMixing "onPlaybackAudioFrameBeforeMixing"
 * callback.
 * 
 * @param sampleRate The sample rate (Hz) of the audio data returned in
 * `onPlaybackAudioFrameBeforeMixing`, which can set be as 8000, 16000, 32000, 44100, or 48000.
 * @param channel Number of channels of the audio data returned in `onPlaybackAudioFrameBeforeMixing`,
 * which can be set as 1 or 2:
 * - 1: Mono
 * - 2: Stereo
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setPlaybackAudioFrameBeforeMixingParameters (int sampleRate, int channel)  override;



/*
 * Enable the audio spectrum monitor.
 * 
 * @param intervalInMS Sets the time interval(ms) between two consecutive audio spectrum callback.
 * The default value is 100. This param should be larger than 10.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableAudioSpectrumMonitor (int intervalInMS = 100)  override;



/*
 * Disalbe the audio spectrum monitor.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int disableAudioSpectrumMonitor ()  override;



/*
 * Registers an audio spectrum observer.
 * 
 * You need to implement the `IAudioSpectrumObserver` class in this method, and register the following callbacks
 * according to your scenario:
 * - \ref agora::media::IAudioSpectrumObserver::onAudioSpectrumComputed "onAudioSpectrumComputed": Occurs when
 * the SDK receives the audio data and at set intervals.
 * 
 * @param observer A pointer to the audio spectrum observer: \ref agora::media::IAudioSpectrumObserver
 * "IAudioSpectrumObserver".
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int registerAudioSpectrumObserver (agora::media::IAudioSpectrumObserver * observer)  override;



/*
 * Releases the audio spectrum observer.
 * 
 * @param observer The pointer to the audio spectrum observer: \ref agora::media::IAudioSpectrumObserver
 * "IAudioSpectrumObserver".
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int unregisterAudioSpectrumObserver (agora::media::IAudioSpectrumObserver * observer)  override;



/*
 * Adjusts the recording volume.
 * 
 * @param volume The recording volume, which ranges from 0 to 400:
 * 
 * - 0: Mute the recording volume.
 * - 100: The Original volume.
 * - 400: (Maximum) Four times the original volume with signal clipping
 * protection.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int adjustRecordingSignalVolume (int volume)  override;



/*
 * Mute or resume recording signal volume.
 * 
 * @param mute Determines whether to mute or resume the recording signal volume.
 * - true: Mute the recording signal volume.
 * - false: (Default) Resume the recording signal volume.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteRecordingSignal (bool mute)  override;



/*
 * Adjusts the playback volume.
 * 
 * @param volume The playback volume, which ranges from 0 to 400:
 * 
 * - 0: Mute the recoridng volume.
 * - 100: The Original volume.
 * - 400: (Maximum) Four times the original volume with signal clipping
 * protection.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int adjustPlaybackSignalVolume (int volume)  override;




					virtual int adjustUserPlaybackSignalVolume (uid_t uid, int volume)  override;



/*
 * Sets the fallback option for the published video stream based on the network conditions.
 * 
 * If `option` is set as #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2), the SDK will:
 * 
 * - Disable the upstream video but enable audio only when the network conditions deteriorate and cannot support both video and audio.
 * - Re-enable the video when the network conditions improve.
 * 
 * When the published video stream falls back to audio only or when the audio-only stream switches back to the video, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly "onLocalPublishFallbackToAudioOnly" callback.
 * 
 * @note
 * - Agora does not recommend using this method for CDN live streaming, because the remote CDN live user will have a noticeable lag when the published video stream falls back to audio only.
 * - Ensure that you call this method before joining a channel.
 * 
 * @param option Sets the fallback option for the published video stream:
 * - #STREAM_FALLBACK_OPTION_DISABLED (0): (Default) No fallback behavior for the published video stream when the uplink network condition is poor. The stream quality is not guaranteed.
 * - #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2): The published video stream falls back to audio only when the uplink network condition is poor.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setLocalPublishFallbackOption (STREAM_FALLBACK_OPTIONS option)  override;



/*
 * Sets the fallback option for the remotely subscribed video stream based on the network conditions.
 * 
 * The default setting for `option` is #STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW (1), where the remotely subscribed video stream falls back to the low-stream video (low resolution and low bitrate) under poor downlink network conditions.
 * 
 * If `option` is set as #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2), the SDK automatically switches the video from a high-stream to a low-stream, or disables the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The SDK monitors the network quality and restores the video stream when the network conditions improve.
 * 
 * When the remotely subscribed video stream falls back to audio only or when the audio-only stream switches back to the video stream, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly "onRemoteSubscribeFallbackToAudioOnly" callback.
 * 
 * @note Ensure that you call this method before joining a channel.
 * 
 * @param  option  Sets the fallback option for the remotely subscribed video stream. See #STREAM_FALLBACK_OPTIONS.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteSubscribeFallbackOption (STREAM_FALLBACK_OPTIONS option)  override;



/*
 * Sets the high priority user list and their fallback level in weak network condition.
 * @note
 * - This method can be called before and after joining a channel.
 * - If a subscriber is set to high priority, this stream only fallback to lower stream after all normal priority users fallback to their fallback level on weak network condition if needed.
 * 
 * @param uidList The high priority user list.
 * @param uidNum The size of uidList.
 * @param option The fallback level of high priority users.
 * 
 * @return int
 * - 0 : Success.
 * - <0 : Failure.
 */
					virtual int setHighPriorityUserList (uid_t * uidList, int uidNum, STREAM_FALLBACK_OPTIONS option)  override;



/*
 * Enable/Disable an extension.
 * By calling this function, you can dynamically enable/disable the extension without changing the pipeline.
 * For example, enabling/disabling Extension_A means the data will be adapted/bypassed by Extension_A.
 * 
 * NOTE: For compatibility reasons, if you haven't call registerExtension,
 * enableExtension will automatically register the specified extension.
 * We suggest you call registerExtension explicitly.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension.
 * @param enable Whether to enable the extension:
 * - true: (Default) Enable the extension.
 * - false: Disable the extension.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableExtension (const char * provider, const char * extension, const ExtensionInfo & extensionInfo, bool enable = true)  override;



/*
 * Sets the properties of an extension.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension.
 * @param key The key of the extension.
 * @param value The JSON formatted value of the extension key.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setExtensionProperty (const char * provider, const char * extension, const ExtensionInfo & extensionInfo, const char * key, const char * value)  override;



/*
 * Gets the properties of an extension.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension.
 * @param key The key of the extension.
 * @param value The value of the extension key.
 * @param buf_len Maximum length of the JSON string indicating the extension property.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int getExtensionProperty (const char * provider, const char * extension, const ExtensionInfo & extensionInfo, const char * key, char * value, int buf_len)  override;



/*
 * Enables loopback recording.
 * 
 * If you enable loopback recording, the output of the default sound card is mixed into
 * the audio stream sent to the other end.
 * 
 * @note This method is for Windows only.
 * 
 * @param enabled Sets whether to enable/disable loopback recording.
 * - true: Enable loopback recording.
 * - false: (Default) Disable loopback recording.
 * @param deviceName Pointer to the device name of the sound card. The default value is NULL (the default sound card).
 * - This method is for macOS and Windows only.
 * - macOS does not support loopback capturing of the default sound card. If you need to use this method,
 * please use a virtual sound card and pass its name to the deviceName parameter. Agora has tested and recommends using soundflower.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableLoopbackRecording (bool enabled, const char * deviceName = nullptr)  override;



/*
 * Adjusts the loopback recording volume.
 * 
 * @param volume The loopback volume, which ranges from 0 to 100:
 * 
 * - 0: Mute the recoridng volume.
 * - 100: The Original volume.
 * protection.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int adjustLoopbackSignalVolume (int volume)  override;



/*
 * Retrieves the audio volume for recording loopback.
 * @note Call this method when you are in a channel.
 * @return
 * - &ge; 0: The audio volume for loopback, if this method call succeeds. The value range is [0,100].
 * - < 0: Failure.
 */
					virtual int getLoopbackRecordingVolume ()  override;



/*
 * Enables in-ear monitoring.
 * 
 * @param enabled Determines whether to enable in-ear monitoring.
 * - true: Enable.
 * - false: (Default) Disable.
 * @param includeAudioFilters The type of the ear monitoring: #EAR_MONITORING_FILTER_TYPE
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableInEarMonitoring (bool enabled, int includeAudioFilters)  override;



/*
 * Sets the volume of the in-ear monitor.
 * 
 * @param volume Sets the volume of the in-ear monitor. The value ranges
 * between 0 and 100 (default).
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setInEarMonitoringVolume (int volume)  override;

#if defined (_WIN32) || defined(__linux__) || defined(__ANDROID__)


					virtual int loadExtensionProvider (const char * path, bool unload_after_use = false)  override;

#endif


/*
 * Sets the provider property of an extension.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param key The key of the extension.
 * @param value The JSON formatted value of the extension key.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setExtensionProviderProperty (const char * provider, const char * key, const char * value)  override;



/*
 * Registers an extension. Normally you should call this function immediately after engine initialization.
 * Once an extension is registered, the SDK will automatically create and add it to the pipeline.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param type The source type of the extension, e.g. PRIMARY_CAMERA_SOURCE. The default is UNKNOWN_MEDIA_SOURCE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int registerExtension (const char * provider, const char * extension, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE)  override;



/*
 * Enable/Disable an extension.
 * By calling this function, you can dynamically enable/disable the extension without changing the pipeline.
 * For example, enabling/disabling Extension_A means the data will be adapted/bypassed by Extension_A.
 * 
 * NOTE: For compatibility reasons, if you haven't call registerExtension,
 * enableExtension will automatically register the specified extension.
 * We suggest you call registerExtension explicitly.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param enable Whether to enable the extension:
 * - true: (Default) Enable the extension.
 * - false: Disable the extension.
 * @param type The source type of the extension, e.g. PRIMARY_CAMERA_SOURCE. The default is UNKNOWN_MEDIA_SOURCE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableExtension (const char * provider, const char * extension, bool enable = true, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE)  override;



/*
 * Sets the properties of an extension.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param key The key of the extension.
 * @param value The JSON formatted value of the extension key.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setExtensionProperty (const char * provider, const char * extension, const char * key, const char * value, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE)  override;



/*
 * Gets the properties of an extension.
 * 
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param key The key of the extension.
 * @param value The value of the extension key.
 * @param buf_len Maximum length of the JSON string indicating the extension property.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int getExtensionProperty (const char * provider, const char * extension, const char * key, char * value, int buf_len, agora::media::MEDIA_SOURCE_TYPE type = agora::media::UNKNOWN_MEDIA_SOURCE)  override;



/*
 * Sets the camera capture configuration.
 * @note Call this method before enabling the local camera.
 * That said, you can call this method before calling \ref IRtcEngine::joinChannel "joinChannel",
 * \ref IRtcEngine::enableVideo "enableVideo", or \ref IRtcEngine::enableLocalVideo "enableLocalVideo",
 * depending on which method you use to turn on your local camera.
 * 
 * @param config Sets the camera capturer configuration. See CameraCapturerConfiguration.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setCameraCapturerConfiguration (const CameraCapturerConfiguration & config)  override;



/*
 * Get an custom video track id created by internal,which could used to publish or preview
 * 
 * @return
 * - > 0: the useable video track id.
 * - < 0: Failure.
 */
					virtual agora::rtc::video_track_id_t createCustomVideoTrack ()  override;



/*
 * Get an custom encoded video track id created by internal,which could used to publish or preview
 * 
 * @return
 * - > 0: the useable video track id.
 * - < 0: Failure.
 */
					virtual agora::rtc::video_track_id_t createCustomEncodedVideoTrack (const SenderOptions & sender_option)  override;



/*
 * destroy a created custom video track id
 * 
 * @param video_track_id The video track id which was created by createCustomVideoTrack
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int destroyCustomVideoTrack (video_track_id_t video_track_id)  override;



/*
 * destroy a created custom encoded video track id
 * 
 * @param video_track_id The video track id which was created by createCustomEncodedVideoTrack
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int destroyCustomEncodedVideoTrack (video_track_id_t video_track_id)  override;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int switchCamera ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraZoomSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraFaceDetectSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraTorchSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraFocusSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraAutoFocusFaceModeSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setCameraZoomFactor (float factor)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int enableFaceDetection (bool enabled)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual float getCameraMaxZoomFactor ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setCameraFocusPositionInPreview (float positionX, float positionY)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setCameraTorchOn (bool isOn)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setCameraAutoFocusFaceModeEnabled (bool enabled)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraExposurePositionSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setCameraExposurePosition (float positionXinView, float positionYinView)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isCameraExposureSupported ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setCameraExposureFactor (float factor)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)

/*
 * 
 */
					virtual bool isCameraAutoExposureFaceModeSupported ()  override;

#endif
#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)

/*
 * 
 */
					virtual int setCameraAutoExposureFaceModeEnabled (bool enabled)  override;

#endif
#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__APPLE__)

/*
 * 
 */
					virtual int setCameraStabilizationMode (CAMERA_STABILIZATION_MODE mode)  override;

#endif
#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setDefaultAudioRouteToSpeakerphone (bool defaultToSpeaker)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setEnableSpeakerphone (bool speakerOn)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual bool isSpeakerphoneEnabled ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setRouteInCommunicationMode (int route)  override;

#endif
#if defined(__APPLE__)


					virtual bool isCameraCenterStageSupported ()  override;

#endif
#if defined(__APPLE__)


					virtual int enableCameraCenterStage (bool enabled)  override;

#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)


					virtual agora::rtc::IScreenCaptureSourceList* getScreenCaptureSources (const SIZE & thumbSize, const SIZE & iconSize, const bool includeScreen)  override;

#endif
#if (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int setAudioSessionOperationRestriction (AUDIO_SESSION_OPERATION_RESTRICTION restriction)  override;

#endif
#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IPHONE && TARGET_OS_MAC)


					virtual int startScreenCaptureByDisplayId (int64_t displayId, const Rectangle & regionRect, const ScreenCaptureParameters & captureParams)  override;

#endif
#if defined(_WIN32)


					virtual int startScreenCaptureByScreenRect (const Rectangle & screenRect, const Rectangle & regionRect, const ScreenCaptureParameters & captureParams) __deprecated override;

#endif
#if defined(__ANDROID__)


					virtual int getAudioDeviceInfo (DeviceInfo & deviceInfo)  override;

#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)


					virtual int startScreenCaptureByWindowId (int64_t windowId, const Rectangle & regionRect, const ScreenCaptureParameters & captureParams)  override;

#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)


					virtual int setScreenCaptureContentHint (VIDEO_CONTENT_HINT contentHint)  override;

#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)


					virtual int updateScreenCaptureRegion (const Rectangle & regionRect)  override;

#endif
#if defined(_WIN32) || (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)


					virtual int updateScreenCaptureParameters (const ScreenCaptureParameters & captureParams)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int startScreenCapture (const ScreenCaptureParameters2 & captureParams)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int updateScreenCapture (const ScreenCaptureParameters2 & captureParams)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int queryScreenCaptureCapability ()  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)


					virtual int queryCameraFocalLengthCapability (agora::rtc::FocalLengthInfo * focalLengthInfos, int & size)  override;

#endif
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
#if defined(__ANDROID__)

/*
 * 
 */
					virtual int setExternalMediaProjection (void * mediaProjection)  override;

#endif
#endif
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)


					virtual int setScreenCaptureScenario (SCREEN_SCENARIO_TYPE screenScenario)  override;

#endif
#if defined(_WIN32) || defined(__APPLE__) || defined(__ANDROID__)


					virtual int stopScreenCapture ()  override;

#endif


/*
 * Gets the current call ID.
 * 
 * When a user joins a channel on a client, a `callId` is generated to identify
 * the call.
 * 
 * After a call ends, you can call `rate` or `complain` to gather feedback from the customer.
 * These methods require a `callId` parameter. To use these feedback methods, call the this
 * method first to retrieve the `callId` during the call, and then pass the value as an
 * argument in the `rate` or `complain` method after the call ends.
 * 
 * @param callId The reference to the call ID.
 * @return
 * - The call ID if the method call is successful.
 * - < 0: Failure.
 */
					virtual int getCallId (agora::util::AString & callId)  override;



/*
 * Allows a user to rate the call.
 * 
 * It is usually called after the call ends.
 * 
 * @param callId The call ID retrieved from the \ref getCallId "getCallId" method.
 * @param rating The rating of the call between 1 (the lowest score) to 5 (the highest score).
 * @param description (Optional) The description of the rating. The string length must be less than
 * 800 bytes.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int rate (const char * callId, int rating, const char * description)  override;



/*
 * Allows a user to complain about the call quality.
 * 
 * This method is usually called after the call ends.
 * 
 * @param callId The call ID retrieved from the `getCallId` method.
 * @param description (Optional) The description of the complaint. The string length must be less than
 * 800 bytes.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int complain (const char * callId, const char * description)  override;



/*
 * Publishes the local stream without transcoding to a specified CDN live RTMP address.  (CDN live only.)
 * 
 * The SDK returns the result of this method call in the \ref IRtcEngineEventHandler::onStreamPublished "onStreamPublished" callback.
 * 
 * The \ref agora::rtc::IRtcEngine::startRtmpStreamWithoutTranscoding "startRtmpStreamWithoutTranscoding" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of adding a local stream to the CDN.
 * @note
 * - Ensure that the user joins the channel before calling this method.
 * - This method adds only one stream RTMP URL address each time it is called.
 * - The RTMP URL address must not contain special characters, such as Chinese language characters.
 * - This method applies to Live Broadcast only.
 * 
 * @param url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - #ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
 *   - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
 *   - #ERR_ALREADY_IN_USE (19): This streaming URL is already in use. Use a new streaming URL for CDN streaming.
 */
					virtual int startRtmpStreamWithoutTranscoding (const char * url)  override;



/*
 * Publishes the local stream with transcoding to a specified CDN live RTMP address.  (CDN live only.)
 * 
 * The SDK returns the result of this method call in the \ref IRtcEngineEventHandler::onStreamPublished "onStreamPublished" callback.
 * 
 * The \ref agora::rtc::IRtcEngine::startRtmpStreamWithTranscoding "startRtmpStreamWithTranscoding" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of adding a local stream to the CDN.
 * @note
 * - Ensure that the user joins the channel before calling this method.
 * - This method adds only one stream RTMP URL address each time it is called.
 * - The RTMP URL address must not contain special characters, such as Chinese language characters.
 * - This method applies to Live Broadcast only.
 * 
 * @param url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes.
 * @param transcoding Sets the CDN live audio/video transcoding settings.  See LiveTranscoding.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - #ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
 *   - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
 *   - #ERR_ALREADY_IN_USE (19): This streaming URL is already in use. Use a new streaming URL for CDN streaming.
 */
					virtual int startRtmpStreamWithTranscoding (const char * url, const LiveTranscoding & transcoding)  override;



/*
 * Update the video layout and audio settings for CDN live. (CDN live only.)
 * @note This method applies to Live Broadcast only.
 * 
 * @param transcoding Sets the CDN live audio/video transcoding settings. See LiveTranscoding.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int updateRtmpTranscoding (const LiveTranscoding & transcoding)  override;




					virtual int startLocalVideoTranscoder (const LocalTranscoderConfiguration & config)  override;




					virtual int updateLocalTranscoderConfiguration (const LocalTranscoderConfiguration & config)  override;



/*
 * Stop an RTMP stream with transcoding or without transcoding from the CDN. (CDN live only.)
 * 
 * This method removes the RTMP URL address (added by the \ref IRtcEngine::startRtmpStreamWithoutTranscoding "startRtmpStreamWithoutTranscoding" method
 * or IRtcEngine::startRtmpStreamWithTranscoding "startRtmpStreamWithTranscoding" method) from a CDN live stream.
 * The SDK returns the result of this method call in the \ref IRtcEngineEventHandler::onStreamUnpublished "onStreamUnpublished" callback.
 * 
 * The \ref agora::rtc::IRtcEngine::stopRtmpStream "stopRtmpStream" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of removing an RTMP stream from the CDN.
 * @note
 * - This method removes only one RTMP URL address each time it is called.
 * - The RTMP URL address must not contain special characters, such as Chinese language characters.
 * - This method applies to Live Broadcast only.
 * 
 * @param url The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopRtmpStream (const char * url)  override;




					virtual int stopLocalVideoTranscoder ()  override;



/*
 * Starts the local audio with a mixed audio stream.
 * @param config Sets the mixed audio stream source settings.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the
 * stream.
 */
					virtual int startLocalAudioMixer (const LocalAudioMixerConfiguration & config)  override;



/*
 * Update the source stream settings for the mixed audio stream.
 * @param config Update the source audio stream settings.  See
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the
 * stream.
 */
					virtual int updateLocalAudioMixerConfiguration (const LocalAudioMixerConfiguration & config)  override;



/*
 * Stops a mixed audio track.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the
 * stream.
 */
					virtual int stopLocalAudioMixer ()  override;



/*
 * Starts video capture with a camera.
 * 
 * @param config The configuration of the video capture with a primary camera. For details, see CameraCaptureConfiguration.
 * @param sourceType Source type of camera. See #VIDEO_SOURCE_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startCameraCapture (VIDEO_SOURCE_TYPE sourceType, const CameraCapturerConfiguration & config)  override;



/*
 * Stops capturing video through camera.
 * 
 * You can call this method to stop capturing video through the first camera after calling `startCameraCapture`.
 * 
 * @param sourceType Source type of camera. See #VIDEO_SOURCE_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopCameraCapture (VIDEO_SOURCE_TYPE sourceType)  override;



/*
 * Sets the rotation angle of the video captured by the camera.
 * 
 * When the video capture device does not have the gravity sensing function, you can call this method to manually adjust the rotation angle of the captured video.
 * 
 * @param type The video source type. See #VIDEO_SOURCE_TYPE.
 * @param orientation The clockwise rotation angle. See #VIDEO_ORIENTATION.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setCameraDeviceOrientation (VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation)  override;



/*
 * Sets the rotation angle of the video captured by the screen.
 * 
 * When the screen capture device does not have the gravity sensing function, you can call this method to manually adjust the rotation angle of the captured video.
 * 
 * @param type The video source type. See #VIDEO_SOURCE_TYPE.
 * @param orientation The clockwise rotation angle. See #VIDEO_ORIENTATION.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setScreenCaptureOrientation (VIDEO_SOURCE_TYPE type, VIDEO_ORIENTATION orientation)  override;



/*
 * Starts sharing a screen.
 * 
 * @param config The configuration of the captured screen. For details, see ScreenCaptureConfiguration.
 * @param sourceType source type of screen. See #VIDEO_SOURCE_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startScreenCapture (VIDEO_SOURCE_TYPE sourceType, const ScreenCaptureConfiguration & config)  override;



/*
 * Stop sharing the screen.
 * 
 * After calling `startScreenCapture`, you can call this method to stop sharing the first screen.
 * 
 * @param sourceType source type of screen. See #VIDEO_SOURCE_TYPE.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopScreenCapture (VIDEO_SOURCE_TYPE sourceType)  override;



/*
 * Gets the current connection state of the SDK.
 * 
 * @return #CONNECTION_STATE_TYPE.
 */
					virtual agora::rtc::CONNECTION_STATE_TYPE getConnectionState ()  override;




					virtual bool registerEventHandler (IRtcEngineEventHandler * eventHandler)  override;




					virtual bool unregisterEventHandler (IRtcEngineEventHandler * eventHandler)  override;




					virtual int setRemoteUserPriority (uid_t uid, PRIORITY_TYPE userPriority)  override;



/*
 * Registers a packet observer.
 * 
 * The Agora Native SDK allows your app to register a packet observer to
 * receive events whenever a voice or video packet is transmitting.
 * 
 * @param observer The IPacketObserver object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int registerPacketObserver (IPacketObserver * observer)  override;



/*
 * Enables/Disables the built-in encryption.
 * 
 * In scenarios requiring high security, Agora recommends calling this method to enable the built-in encryption before joining a channel.
 * 
 * All users in the same channel must use the same encryption mode and encryption key. Once all users leave the channel, the encryption key of this channel is automatically cleared.
 * 
 * @note
 * - If you enable the built-in encryption, you cannot use the RTMP streaming function.
 * 
 * @param enabled Whether to enable the built-in encryption:
 * - true: Enable the built-in encryption.
 * - false: Disable the built-in encryption.
 * @param config Configurations of built-in encryption schemas. See EncryptionConfig.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - -2(ERR_INVALID_ARGUMENT): An invalid parameter is used. Set the parameter with a valid value.
 *  - -4(ERR_NOT_SUPPORTED): The encryption mode is incorrect or the SDK fails to load the external encryption library. Check the enumeration or reload the external encryption library.
 *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized. Initialize the `IRtcEngine` instance before calling this method.
 */
					virtual int enableEncryption (bool enabled, const EncryptionConfig & config)  override;



/*
 * Creates a data stream.
 * 
 * You can call this method to create a data stream and improve the
 * reliability and ordering of data tranmission.
 * 
 * @note
 * - Ensure that you set the same value for `reliable` and `ordered`.
 * - Each user can only create a maximum of 5 data streams during a RtcEngine
 * lifecycle.
 * - The data channel allows a data delay of up to 5 seconds. If the receiver
 * does not receive the data stream within 5 seconds, the data channel reports
 * an error.
 * 
 * @param[out] streamId The ID of the stream data.
 * @param reliable Sets whether the recipients are guaranteed to receive
 * the data stream from the sender within five seconds:
 * - true: The recipients receive the data stream from the sender within
 * five seconds. If the recipient does not receive the data stream within
 * five seconds, an error is reported to the application.
 * - false: There is no guarantee that the recipients receive the data stream
 * within five seconds and no error message is reported for any delay or
 * missing data stream.
 * @param ordered Sets whether the recipients receive the data stream
 * in the sent order:
 * - true: The recipients receive the data stream in the sent order.
 * - false: The recipients do not receive the data stream in the sent order.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int createDataStream (int * streamId, bool reliable, bool ordered)  override;



/*
 * Creates a data stream.
 * 
 * Each user can create up to five data streams during the lifecycle of the IChannel.
 * @param streamId The ID of the created data stream.
 * @param config  The config of data stream.
 * @return int
 * - Returns 0: Success.
 * - < 0: Failure.
 */
					virtual int createDataStream (int * streamId, const DataStreamConfig & config)  override;



/*
 * Sends a data stream.
 * 
 * After calling \ref IRtcEngine::createDataStream "createDataStream", you can call
 * this method to send a data stream to all users in the channel.
 * 
 * The SDK has the following restrictions on this method:
 * - Up to 60 packets can be sent per second in a channel with each packet having a maximum size of 1 KB.
 * - Each client can send up to 30 KB of data per second.
 * - Each user can have up to five data streams simultaneously.
 * 
 * After the remote user receives the data stream within 5 seconds, the SDK triggers the
 * \ref IRtcEngineEventHandler::onStreamMessage "onStreamMessage" callback on
 * the remote client. After the remote user does not receive the data stream within 5 seconds,
 * the SDK triggers the \ref IRtcEngineEventHandler::onStreamMessageError "onStreamMessageError"
 * callback on the remote client.
 * 
 * @note
 * - Call this method after calling \ref IRtcEngine::createDataStream "createDataStream".
 * - This method applies only to the `COMMUNICATION` profile or to
 * the hosts in the `LIVE_BROADCASTING` profile. If an audience in the
 * `LIVE_BROADCASTING` profile calls this method, the audience may be switched to a host.
 * 
 * @param streamId The ID of the stream data.
 * @param data The data stream.
 * @param length The length (byte) of the data stream.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int sendStreamMessage (int streamId, const char * data, size_t length)  override;



/*
 * **DEPRECATED** Adds a watermark image to the local video or CDN live stream.
 * 
 * This method is not recommend, Use \ref agora::rtc::IRtcEngine::addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options) "addVideoWatermark"2 instead.
 * 
 * This method adds a PNG watermark image to the local video stream for the recording device, channel audience, and CDN live audience to view and capture.
 * 
 * To add the PNG file to the CDN live publishing stream, see the \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" method.
 * 
 * @param watermark Pointer to the watermark image to be added to the local video stream. See RtcImage.
 * 
 * @note
 * - The URL descriptions are different for the local video and CDN live streams:
 *    - In a local video stream, `url` in RtcImage refers to the absolute path of the added watermark image file in the local video stream.
 *    - In a CDN live stream, `url` in RtcImage refers to the URL address of the added watermark image in the CDN live broadcast.
 * - The source file of the watermark image must be in the PNG file format. If the width and height of the PNG file differ from your settings in this method, the PNG file will be cropped to conform to your settings.
 * - The Agora SDK supports adding only one watermark image onto a local video or CDN live stream. The newly added watermark image replaces the previous one.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int addVideoWatermark (const RtcImage & watermark) __deprecated override;



/*
 * Adds a watermark image to the local video.
 * 
 * This method adds a PNG watermark image to the local video in a live broadcast. Once the watermark image is added, all the audience in the channel (CDN audience included),
 * and the recording device can see and capture it. Agora supports adding only one watermark image onto the local video, and the newly watermark image replaces the previous one.
 * 
 * The watermark position depends on the settings in the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method:
 * - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_LANDSCAPE, or the landscape mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the landscape orientation.
 * - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_PORTRAIT, or the portrait mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the portrait orientation.
 * - When setting the watermark position, the region must be less than the dimensions set in the `setVideoEncoderConfiguration` method. Otherwise, the watermark image will be cropped.
 * 
 * @note
 * - Ensure that you have called the \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" method to enable the video module before calling this method.
 * - If you only want to add a watermark image to the local video for the audience in the CDN live broadcast channel to see and capture, you can call this method or the \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" method.
 * - This method supports adding a watermark image in the PNG file format only. Supported pixel formats of the PNG image are RGBA, RGB, Palette, Gray, and Alpha_gray.
 * - If the dimensions of the PNG image differ from your settings in this method, the image will be cropped or zoomed to conform to your settings.
 * - If you have enabled the local video preview by calling the \ref agora::rtc::IRtcEngine::startPreview "startPreview" method, you can use the `visibleInPreview` member in the WatermarkOptions class to set whether or not the watermark is visible in preview.
 * - If you have enabled the mirror mode for the local video, the watermark on the local video is also mirrored. To avoid mirroring the watermark, Agora recommends that you do not use the mirror and watermark functions for the local video at the same time. You can implement the watermark function in your application layer.
 * 
 * @param watermarkUrl The local file path of the watermark image to be added. This method supports adding a watermark image from the local absolute or relative file path.
 * @param options Pointer to the watermark's options to be added. See WatermarkOptions for more infomation.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int addVideoWatermark (const char * watermarkUrl, const WatermarkOptions & options)  override;



/*
 * Removes the watermark image on the video stream added by
 * addVideoWatermark().
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int clearVideoWatermarks ()  override;



/*
 * @deprecated Use disableAudio() instead.
 * 
 * Disables the audio function in the channel.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int pauseAudio () __deprecated override;



/*
 * @deprecated Use enableAudio() instead.
 * 
 * Resumes the audio function in the channel.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int resumeAudio () __deprecated override;



/*
 * Enables interoperability with the Agora Web SDK (Live Broadcast only).
 * 
 * @deprecated The Agora NG SDK enables the interoperablity with the Web SDK.
 * 
 * Use this method when the channel profile is Live Broadcast. Interoperability
 * with the Agora Web SDK is enabled by default when the channel profile is
 * Communication.
 * 
 * @param enabled Determines whether to enable interoperability with the Agora Web SDK.
 * - true: (Default) Enable interoperability with the Agora Native SDK.
 * - false: Disable interoperability with the Agora Native SDK.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableWebSdkInteroperability (bool enabled) __deprecated override;



/*
 * Agora supports reporting and analyzing customized messages.
 * 
 * This function is in the beta stage with a free trial. The ability provided
 * in its beta test version is reporting a maximum of 10 message pieces within
 * 6 seconds, with each message piece not exceeding 256 bytes.
 * 
 * To try out this function, contact [support@agora.io](mailto:support@agora.io)
 * and discuss the format of customized messages with us.
 */
					virtual int sendCustomReportMessage (const char * id, const char * category, const char * event, const char * label, int value)  override;



/*
 * Registers the metadata observer.
 * 
 * You need to implement the IMetadataObserver class and specify the metadata type
 * in this method. This method enables you to add synchronized metadata in the video
 * stream for more diversified live interactive streaming, such as sending
 * shopping links, digital coupons, and online quizzes.
 * 
 * A successful call of this method triggers
 * the \ref agora::rtc::IMetadataObserver::getMaxMetadataSize "getMaxMetadataSize" callback.
 * 
 * @note
 * - Call this method before the `joinChannel` method.
 * - This method applies to the `LIVE_BROADCASTING` channel profile.
 * 
 * @param observer IMetadataObserver.
 * @param type The metadata type. See \ref IMetadataObserver::METADATA_TYPE "METADATA_TYPE". The SDK supports VIDEO_METADATA (0) only for now.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int registerMediaMetadataObserver (IMetadataObserver * observer, IMetadataObserver::METADATA_TYPE type)  override;



/*
 * Unregisters the metadata observer.
 * @param observer IMetadataObserver.
 * @param type The metadata type. See \ref IMetadataObserver::METADATA_TYPE "METADATA_TYPE". The SDK supports VIDEO_METADATA (0) only for now.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int unregisterMediaMetadataObserver (IMetadataObserver * observer, IMetadataObserver::METADATA_TYPE type)  override;



/*
 * Start audio frame dump.
 * 
 * Optional `location` is: "pre_apm_proc", "apm", "pre_send_proc", "filter", "enc", "tx_mixer",
 *                       "at_record", "atw_record" for audio sending.
 *                       "dec", "mixed", "play", "rx_mixer", "playback_mixer", "pcm_source_playback_mixer",
 *                       "pre_play_proc", "at_playout", "atw_playout" for audio receiving.
 */
					virtual int startAudioFrameDump (const char * channel_id, uid_t uid, const char * location, const char * uuid, const char * passwd, long duration_ms, bool auto_upload)  override;



/*
 * Stops the audio frame dump.
 */
					virtual int stopAudioFrameDump (const char * channel_id, uid_t uid, const char * location)  override;



/*
 * Enables/Disables Agora AI Noise Suppression(AINS) with preset mode.
 * 
 * @param enabled Sets whether or not to enable AINS.
 * - true: Enables the AINS.
 * - false: Disables the AINS.
 * @param mode The preset AINS mode, range is [0,1,2]:
 * 0: AINS mode with soft suppression level.
 * 1: AINS mode with aggressive suppression level.
 * 2: AINS mode with aggressive suppression level and low algorithm latency.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAINSMode (bool enabled, AUDIO_AINS_MODE mode)  override;



/*
 * Registers a user account.
 * 
 * Once registered, the user account can be used to identify the local user when the user joins the channel.
 * After the user successfully registers a user account, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" callback on the local client,
 * reporting the user ID and user account of the local user.
 * 
 * To join a channel with a user account, you can choose either of the following:
 * 
 * - Call the \ref agora::rtc::IRtcEngine::registerLocalUserAccount "registerLocalUserAccount" method to create a user account, and then the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method to join the channel.
 * - Call the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method to join the channel.
 * 
 * The difference between the two is that for the former, the time elapsed between calling the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method
 * and joining the channel is shorter than the latter.
 * 
 * @note
 * - Ensure that you set the `userAccount` parameter. Otherwise, this method does not take effect.
 * - Ensure that the value of the `userAccount` parameter is unique in the channel.
 * - To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 * 
 * @param appId The App ID of your project.
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int registerLocalUserAccount (const char * appId, const char * userAccount)  override;



/*
 * Joins the channel with a user account.
 * 
 * After the user successfully joins the channel, the SDK triggers the following callbacks:
 * 
 * - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" .
 * - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" , if the user joining the channel is in the `COMMUNICATION` profile, or is a host in the `LIVE_BROADCASTING` profile.
 * 
 * @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
 * If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 * 
 * @param token The token generated at your server:
 * - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
 * - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int joinChannelWithUserAccount (const char * token, const char * channelId, const char * userAccount)  override;



/*
 * Joins the channel with a user account.
 * 
 * After the user successfully joins the channel, the SDK triggers the following callbacks:
 * 
 * - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" .
 * - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" , if the user joining the channel is in the `COMMUNICATION` profile, or is a host in the `LIVE_BROADCASTING` profile.
 * 
 * @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
 * If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 * 
 * @param token The token generated at your server:
 * - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
 * - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param options  The channel media options: \ref agora::rtc::ChannelMediaOptions::ChannelMediaOptions "ChannelMediaOptions"
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int joinChannelWithUserAccount (const char * token, const char * channelId, const char * userAccount, const ChannelMediaOptions & options)  override;



/*
 * Joins the channel with a user account.
 * 
 * After the user successfully joins the channel, the SDK triggers the following callbacks:
 * 
 * - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" .
 * - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" , if the user joining the channel is in the `COMMUNICATION` profile, or is a host in the `LIVE_BROADCASTING` profile.
 * 
 * @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
 * If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 * 
 * @param token The token generated at your server:
 * - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
 * - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param options  The channel media options: \ref agora::rtc::ChannelMediaOptions::ChannelMediaOptions "ChannelMediaOptions"
 * @param eventHandler The pointer to the IRtcEngine event handler: IRtcEngineEventHandler.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int joinChannelWithUserAccountEx (const char * token, const char * channelId, const char * userAccount, const ChannelMediaOptions & options, IRtcEngineEventHandler * eventHandler)  override;



/*
 * Gets the user information by passing in the user account.
 * 
 * After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them
 * in a mapping table object (`userInfo`), and triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback on the local client.
 * 
 * After receiving the o\ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback, you can call this method to get the user ID of the
 * remote user from the `userInfo` object by passing in the user account.
 * 
 * @param userAccount The user account of the user. Ensure that you set this parameter.
 * @param [in,out] userInfo  A userInfo object that identifies the user:
 * - Input: A userInfo object.
 * - Output: A userInfo object that contains the user account and user ID of the user.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int getUserInfoByUserAccount (const char * userAccount, rtc::UserInfo * userInfo)  override;



/*
 * Gets the user information by passing in the user ID.
 * 
 * After a remote user joins the channel, the SDK gets the user ID and user account of the remote user,
 * caches them in a mapping table object (`userInfo`), and triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback on the local client.
 * 
 * After receiving the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback, you can call this method to get the user account of the remote user
 * from the `userInfo` object by passing in the user ID.
 * 
 * @param uid The user ID of the remote user. Ensure that you set this parameter.
 * @param[in,out] userInfo A userInfo object that identifies the user:
 * - Input: A userInfo object.
 * - Output: A userInfo object that contains the user account and user ID of the user.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int getUserInfoByUid (uid_t uid, rtc::UserInfo * userInfo)  override;



/*
 * Starts relaying media streams across channels or updates the channels for media relay.
 * 
 * After a successful method call, the SDK triggers the
 * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
 *  "onChannelMediaRelayStateChanged" callback, and this callback return the state of the media stream relay.
 * - If the
 * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
 *  "onChannelMediaRelayStateChanged" callback returns
 * #RELAY_STATE_RUNNING (2) and #RELAY_OK (0), the host starts sending data to the destination channel.
 * - If the
 * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
 *  "onChannelMediaRelayStateChanged" callback returns
 * #RELAY_STATE_FAILURE (3), an exception occurs during the media stream
 * relay.
 * 
 * @note
 * - Call this method after the \ref joinChannel() "joinChannel" method.
 * - This method takes effect only when you are a host in a
 * `LIVE_BROADCASTING` channel.
 * - Contact sales-us@agora.io before implementing this function.
 * - We do not support string user accounts in this API.
 * 
 * @since v4.2.0
 * @param configuration The configuration of the media stream relay:
 * ChannelMediaRelayConfiguration.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -8(ERR_INVALID_STATE): The current status is invalid, only allowed to be called when the role is the broadcaster.
 */
					virtual int startOrUpdateChannelMediaRelay (const ChannelMediaRelayConfiguration & configuration)  override;



/*
 * Stops the media stream relay.
 * 
 * Once the relay stops, the host quits all the destination
 * channels.
 * 
 * After a successful method call, the SDK triggers the
 * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
 *  "onChannelMediaRelayStateChanged" callback. If the callback returns
 * #RELAY_STATE_IDLE (0) and #RELAY_OK (0), the host successfully
 * stops the relay.
 * 
 * @note
 * If the method call fails, the SDK triggers the
 * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
 *  "onChannelMediaRelayStateChanged" callback with the
 * #RELAY_ERROR_SERVER_NO_RESPONSE (2) or
 * #RELAY_ERROR_SERVER_CONNECTION_LOST (8) state code. You can leave the
 * channel by calling the \ref leaveChannel() "leaveChannel" method, and
 * the media stream relay automatically stops.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -7(ERR_NOT_INITIALIZED): cross channel media streams are not relayed.
 */
					virtual int stopChannelMediaRelay ()  override;



/*
 * pause the channels for media stream relay.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -7(ERR_NOT_INITIALIZED): cross channel media streams are not relayed.
 */
					virtual int pauseAllChannelMediaRelay ()  override;



/*
 * resume the channels for media stream relay.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -7(ERR_NOT_INITIALIZED): cross channel media streams are not relayed.
 */
					virtual int resumeAllChannelMediaRelay ()  override;



/*
 * Set audio parameters for direct streaming to CDN
 * 
 * @note
 * Must call this api before "startDirectCdnStreaming"
 * 
 * @param profile Sets the sample rate, bitrate, encoding mode, and the number of channels:
 * #AUDIO_PROFILE_TYPE.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setDirectCdnStreamingAudioConfiguration (AUDIO_PROFILE_TYPE profile)  override;



/*
 * Set video parameters for direct streaming to CDN
 * 
 * Each configuration profile corresponds to a set of video parameters, including
 * the resolution, frame rate, and bitrate.
 * 
 * @note
 * Must call this api before "startDirectCdnStreaming"
 * 
 * @param config The local video encoder configuration: VideoEncoderConfiguration.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setDirectCdnStreamingVideoConfiguration (const VideoEncoderConfiguration & config)  override;



/*
 * Start direct cdn streaming
 * 
 * @param eventHandler A pointer to the direct cdn streaming event handler: \ref agora::rtc::IDirectCdnStreamingEventHandler
 * "IDirectCdnStreamingEventHandler".
 * @param publishUrl The url of the cdn used to publish the stream.
 * @param options The direct cdn streaming media options: DirectCdnStreamingMediaOptions.
 * This API must pass an audio-related option, and temporarily cannot pass more than one.
 * For video-related options, you can either choose to not pass any, or only one.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startDirectCdnStreaming (IDirectCdnStreamingEventHandler * eventHandler, const char * publishUrl, const DirectCdnStreamingMediaOptions & options)  override;



/*
 * Stop direct cdn streaming
 * 
 * @note
 * This method is synchronous.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopDirectCdnStreaming ()  override;



/*
 * Change the media source during the pushing
 * 
 * @note
 * This method is temporarily not supported.
 * 
 * @param options The direct cdn streaming media options: DirectCdnStreamingMediaOptions.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int updateDirectCdnStreamingMediaOptions (const DirectCdnStreamingMediaOptions & options)  override;



/*
 * Enables the rhythm player.
 * 
 * @param sound1 The absolute path or URL address (including the filename extensions) of the file for the downbeat.
 * @param sound2 The absolute path or URL address (including the filename extensions) of the file for the upbeats.
 * @param config The configuration of rhythm player.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startRhythmPlayer (const char * sound1, const char * sound2, const AgoraRhythmPlayerConfig & config)  override;



/*
 * Disables the rhythm player.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopRhythmPlayer ()  override;



/*
 * Configures the rhythm player.
 * 
 * @param config The configuration of rhythm player.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int configRhythmPlayer (const AgoraRhythmPlayerConfig & config)  override;



/*
 * Takes a snapshot of a video stream.
 * 
 * This method takes a snapshot of a video stream from the specified user, generates a JPG
 * image, and saves it to the specified path.
 * 
 * The method is asynchronous, and the SDK has not taken the snapshot when the method call
 * returns. After a successful method call, the SDK triggers the `onSnapshotTaken` callback
 * to report whether the snapshot is successfully taken, as well as the details for that
 * snapshot.
 * 
 * @note
 * - Call this method after joining a channel.
 * - This method takes a snapshot of the published video stream specified in `ChannelMediaOptions`.
 * - If the user's video has been preprocessed, for example, watermarked or beautified, the resulting
 * snapshot includes the pre-processing effect.
 * 
 * @param uid The user ID. Set uid as 0 if you want to take a snapshot of the local user's video.
 * @param filePath The local path (including filename extensions) of the snapshot. For example:
 * - Windows: `C:\Users\<user_name>\AppData\Local\Agora\<process_name>\example.jpg`
 * - iOS: `/App Sandbox/Library/Caches/example.jpg`
 * - macOS: `～/Library/Logs/example.jpg`
 * - Android: `/storage/emulated/0/Android/data/<package name>/files/example.jpg`
 * 
 * Ensure that the path you specify exists and is writable.
 * @return
 * - 0 : Success.
 * - < 0 : Failure.
 */
					virtual int takeSnapshot (uid_t uid, const char * filePath)  override;



/*
 * Takes a snapshot of a video stream.
 * 
 * This method takes a snapshot of a video stream from the specified user, generates a JPG
 * image, and saves it to the specified path.
 * 
 * The method is asynchronous, and the SDK has not taken the snapshot when the method call
 * returns. After a successful method call, the SDK triggers the `onSnapshotTaken` callback
 * to report whether the snapshot is successfully taken, as well as the details for that
 * snapshot.
 * 
 * @note
 * - Call this method after joining a channel.
 * - This method takes a snapshot of the published video stream specified in `ChannelMediaOptions`.
 * 
 * @param uid The user ID. Set uid as 0 if you want to take a snapshot of the local user's video.
 * @param config The configuration for the take snapshot. See SnapshotConfig.
 * 
 * Ensure that the path you specify exists and is writable.
 * @return
 * - 0 : Success.
 * - &lt; 0: Failure.
 *   - -4: Incorrect observation position. Modify the input observation position according to the reqiurements specified in SnapshotConfig.
 */
					virtual int takeSnapshot (uid_t uid, const media::SnapshotConfig & config)  override;



/*
 * Enables the content inspect.
 * @param enabled Whether to enable content inspect:
 * - `true`: Yes.
 * - `false`: No.
 * @param config The configuration for the content inspection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableContentInspect (bool enabled, const media::ContentInspectConfig & config)  override;




					virtual int adjustCustomAudioPublishVolume (track_id_t trackId, int volume)  override;




					virtual int adjustCustomAudioPlayoutVolume (track_id_t trackId, int volume)  override;



/*
 * Sets the Agora cloud proxy service.
 * 
 * @since v3.3.0
 * 
 * When the user's firewall restricts the IP address and port, refer to *Use Cloud Proxy* to add the specific
 * IP addresses and ports to the firewall allowlist; then, call this method to enable the cloud proxy and set
 * the `proxyType` parameter as `UDP_PROXY(1)`, which is the cloud proxy for the UDP protocol.
 * 
 * After a successfully cloud proxy connection, the SDK triggers
 * the \ref IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" (CONNECTION_STATE_CONNECTING, CONNECTION_CHANGED_SETTING_PROXY_SERVER) callback.
 * 
 * To disable the cloud proxy that has been set, call `setCloudProxy(NONE_PROXY)`. To change the cloud proxy type that has been set,
 * call `setCloudProxy(NONE_PROXY)` first, and then call `setCloudProxy`, and pass the value that you expect in `proxyType`.
 * 
 * @note
 * - Agora recommends that you call this method before joining the channel or after leaving the channel.
 * - For the SDK v3.3.x, the services for pushing streams to CDN and co-hosting across channels are not available
 * when you use the cloud proxy for the UDP protocol. For the SDK v3.4.0 and later, the services for pushing streams
 * to CDN and co-hosting across channels are not available when the user is in a network environment with a firewall
 * and uses the cloud proxy for the UDP protocol.
 * 
 * @param proxyType The cloud proxy type, see #CLOUD_PROXY_TYPE. This parameter is required, and the SDK reports an error if you do not pass in a value.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - `-2(ERR_INVALID_ARGUMENT)`: The parameter is invalid.
 *  - `-7(ERR_NOT_INITIALIZED)`: The SDK is not initialized.
 */
					virtual int setCloudProxy (CLOUD_PROXY_TYPE proxyType)  override;



/*
 * set local access point addresses in local proxy mode. use this method before join channel.
 * 
 * @param config The LocalAccessPointConfiguration class, See the definition of LocalAccessPointConfiguration for details.
 * 
 * @return
 * - 0: Success
 * - < 0: Failure
 */
					virtual int setLocalAccessPoint (const LocalAccessPointConfiguration & config)  override;



/*
 * set advanced audio options.
 * @param options The AdvancedAudioOptions class, See the definition of AdvancedAudioOptions for details.
 * 
 * @return
 * - 0: Success
 * - < 0: Failure
 */
					virtual int setAdvancedAudioOptions (AdvancedAudioOptions & options, int sourceType = 0)  override;



/*
 * Bind local user and a remote user as an audio&video sync group. The remote user is defined by cid and uid.
 *  There’s a usage limit that local user must be a video stream sender. On the receiver side, media streams from same sync group will be time-synced
 * 
 * @param channelId The channel id
 * @param uid The user ID of the remote user to be bound with (local user)
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setAVSyncSource (const char * channelId, uid_t uid)  override;



/*
 * @brief enable or disable video image source to replace the current video source published or resume it
 * 
 * @param enable true for enable, false for disable
 * @param options options for image track
 */
					virtual int enableVideoImageSource (bool enable, const ImageTrackOptions & options)  override;




					virtual int64_t getCurrentMonotonicTimeInMs ()  override;



/*
 * Turns WIFI acceleration on or off.
 * 
 * @note
 * - This method is called before and after joining a channel.
 * - Users check the WIFI router app for information about acceleration. Therefore, if this interface is invoked, the caller accepts that the caller's name will be displayed to the user in the WIFI router application on behalf of the caller.
 * 
 * @param enabled
 * - true：Turn WIFI acceleration on.
 * - false：Turn WIFI acceleration off.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableWirelessAccelerate (bool enabled)  override;




					virtual int getNetworkType ()  override;



/*
 * Provides the technical preview functionalities or special customizations by configuring the SDK with JSON options.
 * 
 * @param parameters Pointer to the set parameters in a JSON string.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setParameters (const char * parameters)  override;



/*
 * @brief Start tracing media rendering events.
 * @since v4.1.1
 * @discussion
 * - SDK will trace media rendering events when this API is called.
 * - The tracing result can be obtained through callback `IRtcEngineEventHandler::onVideoRenderingTracingResult`
 * @note
 * - By default, SDK will trace media rendering events when `IRtcEngine::joinChannel` is called.
 * - The start point of event tracing will be reset after leaving channel.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized. Initialize the `IRtcEngine` instance before calling this method.
 */
					virtual int startMediaRenderingTracing ()  override;



/*
 * @brief Enable instant media rendering.
 * @since v4.1.1
 * @discussion
 * - This method enable SDK to render video or playout audio faster.
 * @note
 * - Once enable this mode, we should destroy rtc engine to disable it.
 * - Enable this mode, will sacrifice some part of experience.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized. Initialize the `IRtcEngine` instance before calling this method.
 */
					virtual int enableInstantMediaRendering ()  override;



/*
 * Return current NTP(unix timestamp) time in milliseconds.
 */
					virtual uint64_t getNtpWallTimeInMs ()  override;



/*
 * @brief Whether the target feature is available for the device.
 * @since v4.3.0
 * @param type The feature type. See FeatureType.
 * @return
 * - true: available.
 * - false: not available.
 */
					virtual bool isFeatureAvailableOnDevice (FeatureType type)  override;



/*
 * @brief send audio metadata
 * @since v4.3.1
 * @param metadata The pointer of metadata
 * @param length Size of metadata
 * @return
 * - 0: success
 * - <0: failure
 * @technical preview
 */
					virtual int sendAudioMetadata (const char * metadata, size_t length)  override;



/*
 * @brief Queries the HDR capability of the video module
 * @param videoModule The video module. See VIDEO_MODULE_TYPE
 * @param capability HDR capability of video module. See HDR_CAPABILITY
 * @return
 * - 0: success
 * - <0: failure
 * @technical preview
 */
					virtual int queryHDRCapability (VIDEO_MODULE_TYPE videoModule, HDR_CAPABILITY & capability)  override;



/*
 * Joins a channel with media options.
 * 
 * This method enables users to join a channel. Users in the same channel can talk to each other,
 * and multiple users in the same channel can start a group chat. Users with different App IDs
 * cannot call each other.
 * 
 * A successful call of this method triggers the following callbacks:
 * - The local client: The `onJoinChannelSuccess` and `onConnectionStateChanged` callbacks.
 * - The remote client: `onUserJoined`, if the user joining the channel is in the Communication
 * profile or is a host in the Live-broadcasting profile.
 * 
 * When the connection between the client and Agora's server is interrupted due to poor network
 * conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins
 * the channel, the SDK triggers the `onRejoinChannelSuccess` callback on the local client.
 * 
 * Compared to `joinChannel`, this method adds the options parameter to configure whether to
 * automatically subscribe to all remote audio and video streams in the channel when the user
 * joins the channel. By default, the user subscribes to the audio and video streams of all
 * the other users in the channel, giving rise to usage and billings. To unsubscribe, set the
 * `options` parameter or call the `mute` methods accordingly.
 * 
 * @note
 * - This method allows users to join only one channel at a time.
 * - Ensure that the app ID you use to generate the token is the same app ID that you pass in the
 * `initialize` method; otherwise, you may fail to join the channel by token.
 * 
 * @param connection The RtcConnection object.
 * @param token The token generated on your server for authentication.
 * @param options The channel media options: ChannelMediaOptions.
 * @param eventHandler The event handler: IRtcEngineEventHandler.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -2: The parameter is invalid. For example, the token is invalid, the uid parameter is not set
 * to an integer, or the value of a member in the `ChannelMediaOptions` structure is invalid. You need
 * to pass in a valid parameter and join the channel again.
 *   - -3: Failes to initialize the `IRtcEngine` object. You need to reinitialize the IRtcEngine object.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -8: The internal state of the IRtcEngine object is wrong. The typical cause is that you call
 * this method to join the channel without calling `stopEchoTest` to stop the test after calling
 * `startEchoTest` to start a call loop test. You need to call `stopEchoTest` before calling this method.
 *   - -17: The request to join the channel is rejected. The typical cause is that the user is in the
 * channel. Agora recommends using the `onConnectionStateChanged` callback to get whether the user is
 * in the channel. Do not call this method to join the channel unless you receive the
 * `CONNECTION_STATE_DISCONNECTED(1)` state.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * rejoin the channel.
 *   - -121: The user ID is invalid. You need to pass in a valid user ID in uid to rejoin the channel.
 */
					virtual int joinChannelEx (const char * token, const RtcConnection & connection, const ChannelMediaOptions & options, IRtcEngineEventHandler * eventHandler)  override;



/*
 * Leaves the channel.
 * 
 * This method allows a user to leave the channel, for example, by hanging up or exiting a call.
 * 
 * This method is an asynchronous call, which means that the result of this method returns even before
 * the user has not actually left the channel. Once the user successfully leaves the channel, the
 * SDK triggers the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.
 * 
 * @param connection The RtcConnection object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int leaveChannelEx (const RtcConnection & connection)  override;



/*
 * Leaves the channel with the connection ID.
 * 
 * @param connection connection.
 * @param options The options for leaving the channel. See #LeaveChannelOptions.
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int leaveChannelEx (const RtcConnection & connection, const LeaveChannelOptions & options)  override;



/*
 * Leaves a channel with the channel ID and user account.
 * 
 * This method allows a user to leave the channel, for example, by hanging up or exiting a call.
 * 
 * This method is an asynchronous call, which means that the result of this method returns even before
 * the user has not actually left the channel. Once the user successfully leaves the channel, the
 * SDK triggers the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.
 * 
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int leaveChannelWithUserAccountEx (const char * channelId, const char * userAccount)  override;



/*
 * Leaves a channel with the channel ID and user account and sets the options for leaving.
 * 
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param options The options for leaving the channel. See #LeaveChannelOptions.
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int leaveChannelWithUserAccountEx (const char * channelId, const char * userAccount, const LeaveChannelOptions & options)  override;



/*
 * Updates the channel media options after joining the channel.
 * 
 * @param options The channel media options: ChannelMediaOptions.
 * @param connection The RtcConnection object.
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int updateChannelMediaOptionsEx (const ChannelMediaOptions & options, const RtcConnection & connection)  override;



/*
 * Sets the video encoder configuration.
 * 
 * Each configuration profile corresponds to a set of video parameters, including
 * the resolution, frame rate, and bitrate.
 * 
 * The parameters specified in this method are the maximum values under ideal network conditions.
 * If the video engine cannot render the video using the specified parameters due
 * to poor network conditions, the parameters further down the list are considered
 * until a successful configuration is found.
 * 
 * @param config The local video encoder configuration: VideoEncoderConfiguration.
 * @param connection The RtcConnection object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setVideoEncoderConfigurationEx (const VideoEncoderConfiguration & config, const RtcConnection & connection)  override;



/*
 * Stops or resumes receiving the audio stream of a specified user.
 * 
 * @note
 * You can call this method before or after joining a channel. If a user
 * leaves a channel, the settings in this method become invalid.
 * 
 * @param uid The ID of the specified user.
 * @param mute Whether to stop receiving the audio stream of the specified user:
 * - true: Stop receiving the audio stream of the specified user.
 * - false: (Default) Resume receiving the audio stream of the specified user.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteRemoteAudioStreamEx (uid_t uid, bool mute, const RtcConnection & connection)  override;



/*
 * Stops or resumes receiving the video stream of a specified user.
 * 
 * @note
 * You can call this method before or after joining a channel. If a user
 * leaves a channel, the settings in this method become invalid.
 * 
 * @param uid The ID of the specified user.
 * @param mute Whether to stop receiving the video stream of the specified user:
 * - true: Stop receiving the video stream of the specified user.
 * - false: (Default) Resume receiving the video stream of the specified user.
 * @param connection The RtcConnetion object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteRemoteVideoStreamEx (uid_t uid, bool mute, const RtcConnection & connection)  override;



/*
 * Sets the remote video stream type.
 * 
 * If the remote user has enabled the dual-stream mode, by default the SDK receives the high-stream video by
 * Call this method to switch to the low-stream video.
 * 
 * @note
 * This method applies to scenarios where the remote user has enabled the dual-stream mode using
 * \ref enableDualStreamMode "enableDualStreamMode"(true) before joining the channel.
 * 
 * @param uid ID of the remote user sending the video stream.
 * @param streamType Sets the video stream type: #VIDEO_STREAM_TYPE.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteVideoStreamTypeEx (uid_t uid, VIDEO_STREAM_TYPE streamType, const RtcConnection & connection)  override;



/*
 * Stops or resumes sending the local audio stream with connection.
 * 
 * @param mute Determines whether to send or stop sending the local audio stream:
 * - true: Stop sending the local audio stream.
 * - false: Send the local audio stream.
 * 
 * @param connection The connection of the user ID.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteLocalAudioStreamEx (bool mute, const RtcConnection & connection)  override;



/*
 * Stops or resumes sending the local video stream with connection.
 * 
 * @param mute Determines whether to send or stop sending the local video stream:
 * - true: Stop sending the local video stream.
 * - false: Send the local video stream.
 * 
 * @param connection The connection of the user ID.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteLocalVideoStreamEx (bool mute, const RtcConnection & connection)  override;



/*
 * Stops or resumes receiving all remote audio stream with connection.
 * 
 * @param mute Whether to stop receiving remote audio streams:
 * - true: Stop receiving any remote audio stream.
 * - false: Resume receiving all remote audio streams.
 * 
 * @param connection The connection of the user ID.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteAllRemoteAudioStreamsEx (bool mute, const RtcConnection & connection)  override;



/*
 * Stops or resumes receiving all remote video stream with connection.
 * 
 * @param mute Whether to stop receiving remote audio streams:
 * - true: Stop receiving any remote audio stream.
 * - false: Resume receiving all remote audio streams.
 * 
 * @param connection The connection of the user ID.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int muteAllRemoteVideoStreamsEx (bool mute, const RtcConnection & connection)  override;



/*
 * Sets the blocklist of subscribe remote stream audio.
 * 
 * @note
 * If uid is in uidList, the remote user's audio will not be subscribed,
 * even if muteRemoteAudioStream(uid, false) and muteAllRemoteAudioStreams(false) are operated.
 * 
 * @param uidList The id list of users who do not subscribe to audio.
 * @param uidNumber The number of uid in uidList.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeAudioBlocklistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)  override;



/*
 * Sets the allowlist of subscribe remote stream audio.
 * 
 * @note
 * - If uid is in uidList, the remote user's audio will be subscribed,
 * even if muteRemoteAudioStream(uid, true) and muteAllRemoteAudioStreams(true) are operated.
 * - If a user is in the blacklist and whitelist at the same time, the user will not subscribe to audio.
 * 
 * @param uidList The id list of users who do subscribe to audio.
 * @param uidNumber The number of uid in uidList.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeAudioAllowlistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)  override;



/*
 * Sets the blocklist of subscribe remote stream video.
 * 
 * @note
 * If uid is in uidList, the remote user's video will not be subscribed,
 * even if muteRemoteVideoStream(uid, false) and muteAllRemoteVideoStreams(false) are operated.
 * 
 * @param uidList The id list of users who do not subscribe to video.
 * @param uidNumber The number of uid in uidList.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeVideoBlocklistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)  override;



/*
 * Sets the allowlist of subscribe remote stream video.
 * 
 * @note
 * - If uid is in uidList, the remote user's video will be subscribed,
 * even if muteRemoteVideoStream(uid, true) and muteAllRemoteVideoStreams(true) are operated.
 * - If a user is in the blacklist and whitelist at the same time, the user will not subscribe to video.
 * 
 * @param uidList The id list of users who do subscribe to video.
 * @param uidNumber The number of uid in uidList.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setSubscribeVideoAllowlistEx (uid_t * uidList, int uidNumber, const RtcConnection & connection)  override;



/*
 * Sets the remote video subscription options
 * 
 * 
 * @param uid ID of the remote user sending the video stream.
 * @param options Sets the video subscription options: VideoSubscriptionOptions.
 * @param connection The RtcConnection object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteVideoSubscriptionOptionsEx (uid_t uid, const VideoSubscriptionOptions & options, const RtcConnection & connection)  override;



/*
 * Sets the sound position and gain of a remote user.
 * 
 * When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.
 * 
 * @note
 * - For this method to work, enable stereo panning for remote users by calling the \ref agora::rtc::IRtcEngine::enableSoundPositionIndication "enableSoundPositionIndication" method before joining a channel.
 * - This method requires hardware support. For the best sound positioning, we recommend using a wired headset.
 * - Ensure that you call this method after joining a channel.
 * 
 * @param uid The ID of the remote user.
 * @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:
 * - 0.0: the remote sound comes from the front.
 * - -1.0: the remote sound comes from the left.
 * - 1.0: the remote sound comes from the right.
 * @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteVoicePositionEx (uid_t uid, double pan, double gain, const RtcConnection & connection)  override;



/*
 * Sets remote user parameters for spatial audio
 * 
 * @param uid The ID of the remote user.
 * @param param Spatial audio parameters. See SpatialAudioParams.
 * @param connection The RtcConnection object.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteUserSpatialAudioParamsEx (uid_t uid, const agora::SpatialAudioParams & params, const RtcConnection & connection)  override;



/*
 * Updates the display mode of the video view of a remote user.
 * 
 * After initializing the video view of a remote user, you can call this method to update its
 * rendering and mirror modes. This method affects only the video view that the local user sees.
 * 
 * @note
 * - Ensure that you have called \ref setupRemoteVideo "setupRemoteVideo" to initialize the remote video
 * view before calling this method.
 * - During a call, you can call this method as many times as necessary to update the display mode
 * of the video view of a remote user.
 * 
 * @param uid ID of the remote user.
 * @param renderMode Sets the remote display mode. See #RENDER_MODE_TYPE.
 * @param mirrorMode Sets the mirror type. See #VIDEO_MIRROR_MODE_TYPE.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setRemoteRenderModeEx (uid_t uid, media::base::RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode, const RtcConnection & connection)  override;



/*
 * Enables loopback recording.
 * 
 * If you enable loopback recording, the output of the default sound card is mixed into
 * the audio stream sent to the other end.
 * 
 * @note This method is for Windows only.
 * 
 * @param connection The RtcConnection object.
 * @param enabled Sets whether to enable/disable loopback recording.
 * - true: Enable loopback recording.
 * - false: (Default) Disable loopback recording.
 * @param deviceName Pointer to the device name of the sound card. The default value is NULL (the default sound card).
 * - This method is for macOS and Windows only.
 * - macOS does not support loopback capturing of the default sound card. If you need to use this method,
 * please use a virtual sound card and pass its name to the deviceName parameter. Agora has tested and recommends using soundflower.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableLoopbackRecordingEx (const RtcConnection & connection, bool enabled, const char * deviceName = nullptr)  override;



/*
 * Adjusts the recording volume.
 * 
 * @param volume The recording volume, which ranges from 0 to 400:
 * - 0  : Mute the recording volume.
 * - 100: The original volume.
 * - 400: (Maximum) Four times the original volume with signal clipping protection.
 * 
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0  : Success.
 * - < 0: Failure.
 */
					virtual int adjustRecordingSignalVolumeEx (int volume, const RtcConnection & connection)  override;



/*
 * Mute or resume recording signal volume.
 * 
 * @param mute Determines whether to mute or resume the recording signal volume.
 * -  true: Mute the recording signal volume.
 * - false: (Default) Resume the recording signal volume.
 * 
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0  : Success.
 * - < 0: Failure.
 */
					virtual int muteRecordingSignalEx (bool mute, const RtcConnection & connection)  override;



/*
 * Adjust the playback signal volume of a specified remote user.
 * You can call this method as many times as necessary to adjust the playback volume of different remote users, or to repeatedly adjust the playback volume of the same remote user.
 * 
 * @note
 * The playback volume here refers to the mixed volume of a specified remote user.
 * This method can only adjust the playback volume of one specified remote user at a time. To adjust the playback volume of different remote users, call the method as many times, once for each remote user.
 * 
 * @param uid The ID of the remote user.
 * @param volume The playback volume of the specified remote user. The value ranges between 0 and 400, including the following:
 * 
 * - 0: Mute.
 * - 100: (Default) Original volume.
 * @param connection  RtcConnection
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int adjustUserPlaybackSignalVolumeEx (uid_t uid, int volume, const RtcConnection & connection)  override;



/*
 * Gets the current connection state of the SDK.
 * @param connection The RtcConnection object.
 * @return #CONNECTION_STATE_TYPE.
 */
					virtual agora::rtc::CONNECTION_STATE_TYPE getConnectionStateEx (const RtcConnection & connection)  override;



/*
 * Enables/Disables the built-in encryption.
 * 
 * In scenarios requiring high security, Agora recommends calling this method to enable the built-in encryption before joining a channel.
 * 
 * All users in the same channel must use the same encryption mode and encryption key. Once all users leave the channel, the encryption key of this channel is automatically cleared.
 * 
 * @note
 * - If you enable the built-in encryption, you cannot use the RTMP streaming function.
 * 
 * @param connection The RtcConnection object.
 * @param enabled Whether to enable the built-in encryption:
 * - true: Enable the built-in encryption.
 * - false: Disable the built-in encryption.
 * @param config Configurations of built-in encryption schemas. See EncryptionConfig.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - -2(ERR_INVALID_ARGUMENT): An invalid parameter is used. Set the parameter with a valid value.
 *  - -4(ERR_NOT_SUPPORTED): The encryption mode is incorrect or the SDK fails to load the external encryption library. Check the enumeration or reload the external encryption library.
 *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized. Initialize the `IRtcEngine` instance before calling this method.
 */
					virtual int enableEncryptionEx (const RtcConnection & connection, bool enabled, const EncryptionConfig & config)  override;



/*
 * Creates a data stream.
 * 
 * You can call this method to create a data stream and improve the
 * reliability and ordering of data tranmission.
 * 
 * @note
 * - Ensure that you set the same value for `reliable` and `ordered`.
 * - Each user can only create a maximum of 5 data streams during a RtcEngine
 * lifecycle.
 * - The data channel allows a data delay of up to 5 seconds. If the receiver
 * does not receive the data stream within 5 seconds, the data channel reports
 * an error.
 * 
 * @param[out] streamId The ID of the stream data.
 * @param reliable Sets whether the recipients are guaranteed to receive
 * the data stream from the sender within five seconds:
 * - true: The recipients receive the data stream from the sender within
 * five seconds. If the recipient does not receive the data stream within
 * five seconds, an error is reported to the application.
 * - false: There is no guarantee that the recipients receive the data stream
 * within five seconds and no error message is reported for any delay or
 * missing data stream.
 * @param ordered Sets whether the recipients receive the data stream
 * in the sent order:
 * - true: The recipients receive the data stream in the sent order.
 * - false: The recipients do not receive the data stream in the sent order.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int createDataStreamEx (int * streamId, bool reliable, bool ordered, const RtcConnection & connection)  override;



/*
 * Creates a data stream.
 * 
 * Each user can create up to five data streams during the lifecycle of the IChannel.
 * @param streamId The ID of the created data stream.
 * @param config  The config of data stream.
 * @param connection The RtcConnection object.
 * @return int
 * - Returns 0: Success.
 * - < 0: Failure.
 */
					virtual int createDataStreamEx (int * streamId, const DataStreamConfig & config, const RtcConnection & connection)  override;



/*
 * Sends a data stream.
 * 
 * After calling \ref IRtcEngine::createDataStream "createDataStream", you can call
 * this method to send a data stream to all users in the channel.
 * 
 * The SDK has the following restrictions on this method:
 * - Up to 60 packets can be sent per second in a channel with each packet having a maximum size of 1 KB.
 * - Each client can send up to 30 KB of data per second.
 * - Each user can have up to five data streams simultaneously.
 * 
 * After the remote user receives the data stream within 5 seconds, the SDK triggers the
 * \ref IRtcEngineEventHandler::onStreamMessage "onStreamMessage" callback on
 * the remote client. After the remote user does not receive the data stream within 5 seconds,
 * the SDK triggers the \ref IRtcEngineEventHandler::onStreamMessageError "onStreamMessageError"
 * callback on the remote client.
 * 
 * @note
 * - Call this method after calling \ref IRtcEngine::createDataStream "createDataStream".
 * - This method applies only to the `COMMUNICATION` profile or to
 * the hosts in the `LIVE_BROADCASTING` profile. If an audience in the
 * `LIVE_BROADCASTING` profile calls this method, the audience may be switched to a host.
 * 
 * @param streamId The ID of the stream data.
 * @param data The data stream.
 * @param length The length (byte) of the data stream.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int sendStreamMessageEx (int streamId, const char * data, size_t length, const RtcConnection & connection)  override;



/*
 * Adds a watermark image to the local video.
 * 
 * This method adds a PNG watermark image to the local video in a live broadcast. Once the watermark image is added, all the audience in the channel (CDN audience included),
 * and the recording device can see and capture it. Agora supports adding only one watermark image onto the local video, and the newly watermark image replaces the previous one.
 * 
 * The watermark position depends on the settings in the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method:
 * - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_LANDSCAPE, or the landscape mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the landscape orientation.
 * - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_PORTRAIT, or the portrait mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the portrait orientation.
 * - When setting the watermark position, the region must be less than the dimensions set in the `setVideoEncoderConfiguration` method. Otherwise, the watermark image will be cropped.
 * 
 * @note
 * - Ensure that you have called the \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" method to enable the video module before calling this method.
 * - If you only want to add a watermark image to the local video for the audience in the CDN live broadcast channel to see and capture, you can call this method or the \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" method.
 * - This method supports adding a watermark image in the PNG file format only. Supported pixel formats of the PNG image are RGBA, RGB, Palette, Gray, and Alpha_gray.
 * - If the dimensions of the PNG image differ from your settings in this method, the image will be cropped or zoomed to conform to your settings.
 * - If you have enabled the local video preview by calling the \ref agora::rtc::IRtcEngine::startPreview "startPreview" method, you can use the `visibleInPreview` member in the WatermarkOptions class to set whether or not the watermark is visible in preview.
 * - If you have enabled the mirror mode for the local video, the watermark on the local video is also mirrored. To avoid mirroring the watermark, Agora recommends that you do not use the mirror and watermark functions for the local video at the same time. You can implement the watermark function in your application layer.
 * 
 * @param watermarkUrl The local file path of the watermark image to be added. This method supports adding a watermark image from the local absolute or relative file path.
 * @param options Pointer to the watermark's options to be added. See WatermarkOptions for more infomation.
 * @param connection The RtcConnection object.
 * 
 * @return int
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int addVideoWatermarkEx (const char * watermarkUrl, const WatermarkOptions & options, const RtcConnection & connection)  override;



/*
 * Removes the watermark image on the video stream added by
 * addVideoWatermark().
 * 
 * @param connection The RtcConnection object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int clearVideoWatermarkEx (const RtcConnection & connection)  override;



/*
 * Agora supports reporting and analyzing customized messages.
 * 
 * This function is in the beta stage with a free trial. The ability provided
 * in its beta test version is reporting a maximum of 10 message pieces within
 * 6 seconds, with each message piece not exceeding 256 bytes.
 * 
 * To try out this function, contact [support@agora.io](mailto:support@agora.io)
 * and discuss the format of customized messages with us.
 */
					virtual int sendCustomReportMessageEx (const char * id, const char * category, const char * event, const char * label, int value, const RtcConnection & connection)  override;



/*
 * Enables the `onAudioVolumeIndication` callback to report on which users are speaking
 * and the speakers' volume.
 * 
 * Once the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication"
 * callback is enabled, the SDK returns the volume indication in the at the time interval set
 * in `enableAudioVolumeIndication`, regardless of whether any user is speaking in the channel.
 * 
 * @param interval Sets the time interval between two consecutive volume indications:
 * - <= 0: Disables the volume indication.
 * - > 0: Time interval (ms) between two consecutive volume indications,
 * and should be integral multiple of 200 (less than 200 will be set to 200).
 * @param smooth The smoothing factor that sets the sensitivity of the audio volume
 * indicator. The value range is [0, 10]. The greater the value, the more sensitive the
 * indicator. The recommended value is 3.
 * @param reportVad
 * - `true`: Enable the voice activity detection of the local user. Once it is enabled, the `vad` parameter of the
 * `onAudioVolumeIndication` callback reports the voice activity status of the local user.
 * - `false`: (Default) Disable the voice activity detection of the local user. Once it is disabled, the `vad` parameter
 * of the `onAudioVolumeIndication` callback does not report the voice activity status of the local user, except for
 * the scenario where the engine automatically detects the voice activity of the local user.
 * @param connection The RtcConnection object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableAudioVolumeIndicationEx (int interval, int smooth, bool reportVad, const RtcConnection & connection)  override;



/*
 * Publishes the local stream without transcoding to a specified CDN live RTMP address.  (CDN live only.)
 * 
 * @param url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes.
 * @param connection RtcConnection.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startRtmpStreamWithoutTranscodingEx (const char * url, const RtcConnection & connection)  override;



/*
 * Publishes the local stream with transcoding to a specified CDN live RTMP address.  (CDN live only.)
 * 
 * @param url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes.
 * @param transcoding Sets the CDN live audio/video transcoding settings.  See LiveTranscoding.
 * @param connection RtcConnection.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int startRtmpStreamWithTranscodingEx (const char * url, const LiveTranscoding & transcoding, const RtcConnection & connection)  override;



/*
 * Update the video layout and audio settings for CDN live. (CDN live only.)
 * @note This method applies to Live Broadcast only.
 * 
 * @param transcoding Sets the CDN live audio/video transcoding settings. See LiveTranscoding.
 * @param connection RtcConnection.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int updateRtmpTranscodingEx (const LiveTranscoding & transcoding, const RtcConnection & connection)  override;



/*
 * Stop an RTMP stream with transcoding or without transcoding from the CDN. (CDN live only.)
 * @param url The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.
 * @param connection RtcConnection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int stopRtmpStreamEx (const char * url, const RtcConnection & connection)  override;



/*
 * Starts relaying media streams across channels or updates the channels for media relay.
 * 
 * @since v4.2.0
 * @param configuration The configuration of the media stream relay:ChannelMediaRelayConfiguration.
 * @param connection RtcConnection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -8(ERR_INVALID_STATE): The current status is invalid, only allowed to be called when the role is the broadcaster.
 */
					virtual int startOrUpdateChannelMediaRelayEx (const ChannelMediaRelayConfiguration & configuration, const RtcConnection & connection)  override;



/*
 * Stops the media stream relay.
 * 
 * Once the relay stops, the host quits all the destination
 * channels.
 * 
 * @param connection RtcConnection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -7(ERR_NOT_INITIALIZED): cross channel media streams are not relayed.
 */
					virtual int stopChannelMediaRelayEx (const RtcConnection & connection)  override;



/*
 * pause the channels for media stream relay.
 * 
 * @param connection RtcConnection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -7(ERR_NOT_INITIALIZED): cross channel media streams are not relayed.
 */
					virtual int pauseAllChannelMediaRelayEx (const RtcConnection & connection)  override;



/*
 * resume the channels for media stream relay.
 * 
 * @param connection RtcConnection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -1(ERR_FAILED): A general error occurs (no specified reason).
 *   - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
 *   - -5(ERR_REFUSED): The request is rejected.
 *   - -7(ERR_NOT_INITIALIZED): cross channel media streams are not relayed.
 */
					virtual int resumeAllChannelMediaRelayEx (const RtcConnection & connection)  override;



/*
 * Gets the user information by passing in the user account.
 *  It is same as agora::rtc::IRtcEngine::getUserInfoByUserAccount.
 * 
 * @param userAccount The user account of the user. Ensure that you set this parameter.
 * @param [in,out] userInfo  A userInfo object that identifies the user:
 * - Input: A userInfo object.
 * - Output: A userInfo object that contains the user account and user ID of the user.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int getUserInfoByUserAccountEx (const char * userAccount, rtc::UserInfo * userInfo, const RtcConnection & connection)  override;



/*
 * Gets the user information by passing in the user ID.
 *  It is same as agora::rtc::IRtcEngine::getUserInfoByUid.
 * 
 * @param uid The user ID of the remote user. Ensure that you set this parameter.
 * @param[in,out] userInfo A userInfo object that identifies the user:
 * - Input: A userInfo object.
 * - Output: A userInfo object that contains the user account and user ID of the user.
 * @param connection The RtcConnection object.
 * 
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int getUserInfoByUidEx (uid_t uid, rtc::UserInfo * userInfo, const RtcConnection & connection)  override;



/*
 * Enables or disables the dual video stream mode.
 * 
 * @deprecated v4.2.0. This method is deprecated. Use setDualStreamModeEx instead
 * 
 * If dual-stream mode is enabled, the subscriber can choose to receive the high-stream
 * (high-resolution high-bitrate video stream) or low-stream (low-resolution low-bitrate video
 * stream) video using {@link setRemoteVideoStreamType setRemoteVideoStreamType}.
 * 
 * @param enabled
 * - true: Enable the dual-stream mode.
 * - false: (default) Disable the dual-stream mode.
 * @param streamConfig The minor stream config
 * @param connection The RtcConnection object.
 */
					virtual int enableDualStreamModeEx (bool enabled, const SimulcastStreamConfig & streamConfig, const RtcConnection & connection)  override;



/*
 * Enables, disables or auto enable the dual video stream mode.
 * 
 * If dual-stream mode is enabled, the subscriber can choose to receive the high-stream
 * (high-resolution high-bitrate video stream) or low-stream (low-resolution low-bitrate video
 * stream) video using {@link setRemoteVideoStreamType setRemoteVideoStreamType}.
 * 
 * @param mode The dual stream mode: #SIMULCAST_STREAM_MODE.
 * @param streamConfig The configuration of the low stream: SimulcastStreamConfig.
 * @param connection The RtcConnection object.
 */
					virtual int setDualStreamModeEx (SIMULCAST_STREAM_MODE mode, const SimulcastStreamConfig & streamConfig, const RtcConnection & connection)  override;



/*
 * Set the multi-layer video stream configuration.
 * 
 * If multi-layer is configed, the subscriber can choose to receive the coresponding layer
 * of video stream using {@link setRemoteVideoStreamType setRemoteVideoStreamType}.
 * 
 * @param simulcastConfig
 * - The configuration for multi-layer video stream. It includes seven layers, ranging from
 *   STREAM_LAYER_1 to STREAM_LOW. A maximum of 3 layers can be enabled simultaneously.
 * @param connection The RtcConnection object.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 * @technical preview
 */
					virtual int setSimulcastConfigEx (const SimulcastConfig & simulcastConfig, const RtcConnection & connection)  override;



/*
 * Set the high priority user list and their fallback level in weak network condition.
 * 
 * @note
 * - This method can be called before and after joining a channel.
 * - If a subscriber is set to high priority, this stream only fallback to lower stream after all normal priority users fallback to their fallback level on weak network condition if needed.
 * 
 * @param uidList The high priority user list.
 * @param uidNum The size of uidList.
 * @param option The fallback level of high priority users.
 * @param connection An output parameter which is used to control different connection instances.
 * 
 * @return int
 * - 0 : Success.
 * - <0 : Failure.
 */
					virtual int setHighPriorityUserListEx (uid_t * uidList, int uidNum, STREAM_FALLBACK_OPTIONS option, const RtcConnection & connection)  override;



/*
 * Takes a snapshot of a video stream.
 * 
 * This method takes a snapshot of a video stream from the specified user, generates a JPG
 * image, and saves it to the specified path.
 * 
 * The method is asynchronous, and the SDK has not taken the snapshot when the method call
 * returns. After a successful method call, the SDK triggers the `onSnapshotTaken` callback
 * to report whether the snapshot is successfully taken, as well as the details for that
 * snapshot.
 * 
 * @note
 * - Call this method after joining a channel.
 * - This method takes a snapshot of the published video stream specified in `ChannelMediaOptions`.
 * - If the user's video has been preprocessed, for example, watermarked or beautified, the resulting
 * snapshot includes the pre-processing effect.
 * @param connection The RtcConnection object.
 * @param uid The user ID. Set uid as 0 if you want to take a snapshot of the local user's video.
 * @param filePath The local path (including filename extensions) of the snapshot. For example:
 * - Windows: `C:\Users\<user_name>\AppData\Local\Agora\<process_name>\example.jpg`
 * - iOS: `/App Sandbox/Library/Caches/example.jpg`
 * - macOS: `～/Library/Logs/example.jpg`
 * - Android: `/storage/emulated/0/Android/data/<package name>/files/example.jpg`
 * 
 * Ensure that the path you specify exists and is writable.
 * @return
 * - 0 : Success.
 * - < 0 : Failure.
 */
					virtual int takeSnapshotEx (const RtcConnection & connection, uid_t uid, const char * filePath)  override;



/*
 * Takes a snapshot of a video stream.
 * 
 * This method takes a snapshot of a video stream from the specified user, generates a JPG
 * image, and saves it to the specified path.
 * 
 * The method is asynchronous, and the SDK has not taken the snapshot when the method call
 * returns. After a successful method call, the SDK triggers the `onSnapshotTaken` callback
 * to report whether the snapshot is successfully taken, as well as the details for that
 * snapshot.
 * 
 * @note
 * - Call this method after joining a channel.
 * - This method takes a snapshot of the published video stream specified in `ChannelMediaOptions`.
 * 
 * @param connection The RtcConnection object.
 * @param uid The user ID. Set uid as 0 if you want to take a snapshot of the local user's video.
 * @param config The configuration for the take snapshot. See SnapshotConfig.
 * 
 * Ensure that the path you specify exists and is writable.
 * @return
 * - 0 : Success.
 * - &lt; 0: Failure.
 *   - -4: Incorrect observation position. Modify the input observation position according to the reqiurements specified in SnapshotConfig.
 */
					virtual int takeSnapshotEx (const RtcConnection & connection, uid_t uid, const media::SnapshotConfig & config)  override;



/*
 * Enables video screenshot and upload with the connection ID.
 * @param enabled Whether to enable video screenshot and upload:
 * - `true`: Yes.
 * - `false`: No.
 * @param config The configuration for video screenshot and upload.
 * @param connection The connection information. See RtcConnection.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int enableContentInspectEx (bool enabled, const media::ContentInspectConfig & config, const RtcConnection & connection)  override;



/*
 * @brief Start tracing media rendering events.
 * @since v4.1.1
 * @discussion
 * - SDK will trace media rendering events when this API is called.
 * - The tracing result can be obtained through callback `IRtcEngineEventHandler(Ex)::onVideoRenderingTracingResult`
 * @param connection The RtcConnection object.
 * @note
 * - By default, SDK will trace media rendering events when `IRtcEngineEx::joinChannelEx` is called.
 * - The start point of event tracing will be reset after leaving channel.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - -2(ERR_INVALID_ARGUMENT): The parameter is invalid. Check the channel ID and local uid set by parameter `connection`.
 *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized. Initialize the `IRtcEngine` instance before calling this method.
 */
					virtual int startMediaRenderingTracingEx (const RtcConnection & connection)  override;



/*
 * Provides the technical preview functionalities or special customizations by configuring the SDK with JSON options.
 * @since v4.3.0
 * @param connection The connection information. See RtcConnection.
 * @param parameters Pointer to the set parameters in a JSON string.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
					virtual int setParametersEx (const RtcConnection & connection, const char * parameters)  override;



/*
 * Gets the current call ID.
 * 
 * When a user joins a channel on a client, a `callId` is generated to identify
 * the call.
 * 
 * After a call ends, you can call `rate` or `complain` to gather feedback from the customer.
 * These methods require a `callId` parameter. To use these feedback methods, call the this
 * method first to retrieve the `callId` during the call, and then pass the value as an
 * argument in the `rate` or `complain` method after the call ends.
 * 
 * @param callId The reference to the call ID.
 * @param connection The RtcConnection object.
 * @return
 * - The call ID if the method call is successful.
 * - < 0: Failure.
 */
					virtual int getCallIdEx (agora::util::AString & callId, const RtcConnection & connection)  override;



/*
 * send audio metadata
 * @since v4.3.1
 * @param connection The RtcConnection object.
 * @param metadata The pointer of metadata
 * @param length Size of metadata
 * @return
 * - 0: success
 * - <0: failure
 * @technical preview
 */
					virtual int sendAudioMetadataEx (const RtcConnection & connection, const char * metadata, size_t length)  override;


#pragma endregion Other Native APIs

            };
		}
	}
}

