
#ifndef __ZEGO_EXPRESS_PLAYER_H__
#define __ZEGO_EXPRESS_PLAYER_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Starts playing a stream from ZEGO RTC server.
///
/// Available since: 1.1.0
/// Description: Play audio and video streams from the ZEGO RTC server.
/// Use cases: In the real-time scenario, developers can listen to the [onRoomStreamUpdate] event callback to obtain the new stream information in the room where they are located, and call this interface to pass in streamID for play streams.
/// When to call: After [loginRoom].
/// Restrictions: None.
/// Caution: 1. The developer can update the player canvas by calling this function again (the streamID must be the same). 2. After the first play stream failure due to network reasons or the play stream is interrupted, the default time for SDK reconnection is 20min. 3. In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event. please refer to https://docs.zegocloud.com/faq/reconnect. 4. Playing the stream ID that does not exist, the SDK continues to try to play after calling this function. After the stream ID is successfully published, the audio and video stream can be actually played.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
/// @param canvas The view used to display the play audio and video stream's image. When the view is set to [NULL], no video is displayed, only audio is played.
ZEGOEXP_API zego_error EXP_CALL zego_express_start_playing_stream(const char *stream_id,
                                                                  struct zego_canvas *canvas);

/// Starts playing a stream from ZEGO RTC server or from third-party CDN. Support multi-room mode.
///
/// Available since: 1.1.0
/// Description: Play audio and video streams from the ZEGO RTC server or CDN.
/// Use cases: In real-time or live broadcast scenarios, developers can listen to the [onRoomStreamUpdate] event callback to obtain the new stream information in the room where they are located, and call this interface to pass in streamID for play streams.
/// When to call: After [loginRoom].
/// Restrictions: None.
/// Caution: 1. The developer can update the player canvas by calling this function again (the streamID must be the same). 2. After the first play stream failure due to network reasons or the play stream is interrupted, the default time for SDK reconnection is 20min. 3. In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event. please refer to https://docs.zegocloud.com/faq/reconnect. 4. Playing the stream ID that does not exist, the SDK continues to try to play after calling this function. After the stream ID is successfully published, the audio and video stream can be actually played.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
/// @param canvas The view used to display the play audio and video stream's image. When the view is set to [NULL], no video is displayed, only audio is played.
/// @param config Advanced player configuration.
ZEGOEXP_API zego_error EXP_CALL zego_express_start_playing_stream_with_config(
    const char *stream_id, struct zego_canvas *canvas, struct zego_player_config config);

/// Stops playing a stream.
///
/// Available since: 1.1.0
/// Description: Play audio and video streams from the ZEGO RTC server.
/// Use cases: In the real-time scenario, developers can listen to the [onRoomStreamUpdate] event callback to obtain the delete stream information in the room where they are located, and call this interface to pass in streamID for stop play streams.
/// When to call: After [loginRoom].
/// Restrictions: None.
/// Caution: When stopped, the attributes set for this stream previously, such as [setPlayVolume], [mutePlayStreamAudio], [mutePlayStreamVideo], etc., will be invalid and need to be reset when playing the the stream next time.
///
/// @param stream_id Stream ID.
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_playing_stream(const char *stream_id);

/// Set decryption key for the playing stream.
///
/// Available since: 1.19.0
/// Description: When streaming, the audio and video data will be decrypted according to the set key.
/// Use cases: Usually used in scenarios that require high security for audio and video calls.
/// When to call: after [createEngine], after the play stream can be changed at any time.
/// Restrictions: This function is only valid when calling from Zego RTC or L3 server.
/// Related APIs: [setPublishStreamEncryptionKey]Set the publish stream encryption key.
/// Caution: This interface can only be called if encryption is set on the publish. Calling [stopPlayingStream] or [logoutRoom] will clear the decryption key.
///
/// @param stream_id Stream ID.
/// @param key The decryption key, note that the key length only supports 16/24/32 bytes.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_stream_decryption_key(const char *stream_id,
                                                                            const char *key);

/// Set up cross App playing stream information.
///
/// Available since: 2.19.0
/// Description: This information is used for authentication before playing a stream or when retrying playing a stream.
/// Use cases: Used in scenarios that playing streams across apps.
/// When to call: after [createEngine], after the play stream can be changed at any time.
/// Restrictions: This function is only valid when playing stream from Zego RTC server.
/// Caution: Calling [stopPlayingStream] or [logoutRoom] will clear this information.
///
/// @param stream_id Stream ID.
/// @param info Information for cross App playing stream.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_play_stream_cross_app_info(const char *stream_id, struct zego_cross_app_info info);

/// Take a snapshot of the playing stream.
///
/// Available since: 1.17.0
/// Description: Take a screenshot of the specified stream ID.
/// When to call: after called [startPlayingStream].
/// Restrictions: None.
/// Related callbacks: [onPlayerTakeSnapshotResult] Screenshot data callback.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID to be snapshot.
ZEGOEXP_API zego_error EXP_CALL zego_express_take_play_stream_snapshot(const char *stream_id);

/// Sets the stream playback volume.
///
/// Available since: 1.16.0
/// Description: Set the sound size of the stream, the local user can control the playback volume of the audio stream.
/// When to call: after called [startPlayingStream].
/// Restrictions: None.
/// Related APIs: [setAllPlayStreamVolume] Set all stream volume.
/// Caution: You need to reset after [stopPlayingStream] and [startPlayingStream]. This function and the [setAllPlayStreamVolume] function overwrite each other, and the last call takes effect.
///
/// @param stream_id Stream ID.
/// @param volume Volume percentage. The value ranges from 0 to 200, and the default value is 100.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_volume(const char *stream_id, int volume);

/// Sets the all stream playback volume.
///
/// Available since: 2.3.0
/// Description: Set the sound size of the stream, the local user can control the playback volume of the audio stream.
/// When to call: after called [startPlayingStream].
/// Restrictions: None.
/// Related APIs: [setPlayVolume] Set the specified streaming volume.
/// Caution: You need to reset after [stopPlayingStream] and [startPlayingStream]. Set the specified streaming volume and [setAllPlayStreamVolume] interface to override each other, and the last call takes effect.
///
/// @param volume Volume percentage. The value ranges from 0 to 200, and the default value is 100.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_all_play_stream_volume(int volume);

/// Set play video stream type.
///
/// Available since: 2.3.0
/// Description: When the publish stream sets the codecID to SVC through [setVideoConfig], the puller can dynamically set and select different stream types (small resolution is one-half of the standard layer).
/// Use cases: In general, when the network is weak or the rendered UI window is small, you can choose to pull videos with small resolutions to save bandwidth.
/// When to call: before or after called [startPlayingStream].
/// Restrictions: None.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID.
/// @param stream_type Video stream type.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_stream_video_type(
    const char *stream_id, enum zego_video_stream_type stream_type);

/// Set the adaptive adjustment interval range of the buffer for playing stream.
///
/// Available since: 2.1.0
/// Description: Set the range of adaptive adjustment of the internal buffer of the sdk when streaming is 0-4000ms.
/// Use cases: Generally, in the case of a poor network environment, adjusting and increasing the playback buffer of the pull stream will significantly reduce the audio and video freezes, but will increase the delay.
/// When to call: after called [createEngine].
/// Restrictions: None.
/// Caution: When the upper limit of the cache interval set by the developer exceeds 4000ms, the value will be 4000ms. When the upper limit of the cache interval set by the developer is less than the lower limit of the cache interval, the upper limit will be automatically set as the lower limit.
///
/// @param stream_id Stream ID.
/// @param min_buffer_interval The lower limit of the buffer adaptation interval, in milliseconds. The default value is 0ms.
/// @param max_buffer_interval The upper limit of the buffer adaptation interval, in milliseconds. The default value is 4000ms.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_stream_buffer_interval_range(
    const char *stream_id, unsigned int min_buffer_interval, unsigned int max_buffer_interval);

/// Set the weight of the pull stream priority.
///
/// Available since: 1.1.0
/// Description: Set the weight of the streaming priority.
/// Use cases: This interface can be used when developers need to prioritize the quality of a stream in business. For example: in class scene, if students pull multiple streams, you can set high priority for teacher stream.
/// When to call: after called [startPlayingStream].
/// Restrictions: None.
/// Caution: By default, all streams have the same weight. Only one stream can be set with high priority, whichever is set last. After the flow is stopped, the initial state is automatically restored, and all flows have the same weight.When the local network is not good, while ensuring the focus flow, other stalls may be caused more.
///
/// @param stream_id Stream ID.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_stream_focus_on(const char *stream_id);

/// Whether the pull stream can receive the specified audio data.
///
/// Available since: 1.1.0
/// Description: In the process of real-time audio and video interaction, local users can use this function to control whether to receive audio data from designated remote users when pulling streams as needed. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
/// Use cases: Call this function when developers need to quickly close and restore remote audio. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
/// When to call: This function can be called after calling [createEngine].
/// Caution: This function is valid only when the [muteAllPlayStreamAudio] function is set to `false`.
/// Related APIs: You can call the [muteAllPlayStreamAudio] function to control whether to receive all audio data. When the two functions [muteAllPlayStreamAudio] and [mutePlayStreamAudio] are set to `false` at the same time, the local user can receive the audio data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamAudio(true)] function is called, it is globally effective, that is, local users will be prohibited from receiving all remote users' audio data. At this time, the [mutePlayStreamAudio] function will not take effect whether it is called before or after [muteAllPlayStreamAudio].2. When the [muteAllPlayStreamAudio(false)] function is called, the local user can receive the audio data of all remote users. At this time, the [mutePlayStreamAudio] function can be used to control whether to receive a single audio data. Calling the [mutePlayStreamAudio(true, streamID)] function allows the local user to receive audio data other than the `streamID`; calling the [mutePlayStreamAudio(false, streamID)] function allows the local user to receive all audio data.
///
/// @param stream_id Stream ID.
/// @param mute Whether it can receive the audio data of the specified remote user when streaming, "true" means prohibition, "false" means receiving, the default value is "false".
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_play_stream_audio(const char *stream_id,
                                                                    bool mute);

/// Whether the pull stream can receive the specified video data.
///
/// Available since: 1.1.0
/// Description: In the process of real-time video and video interaction, local users can use this function to control whether to receive video data from designated remote users when pulling streams as needed. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
/// Use cases: This function can be called when developers need to quickly close and resume watching remote video. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
/// When to call: This function can be called after calling [createEngine].
/// Caution: This function is valid only when the [muteAllPlayStreamVideo] function is set to `false`. When you mute the video stream, the view remains at the last frame by default, if you need to clear the last frame, please contact ZEGO technical support.
/// Related APIs: You can call the [muteAllPlayStreamVideo] function to control whether to receive all video data. When the two functions [muteAllPlayStreamVideo] and [mutePlayStreamVideo] are set to `false` at the same time, the local user can receive the video data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamVideo(true)] function is called, it will take effect globally, that is, local users will be prohibited from receiving all remote users' video data. At this time, the [mutePlayStreamVideo] function will not take effect whether it is called before or after [muteAllPlayStreamVideo]. 2. When the [muteAllPlayStreamVideo(false)] function is called, the local user can receive the video data of all remote users. At this time, the [mutePlayStreamVideo] function can be used to control whether to receive a single video data. Call the [mutePlayStreamVideo(true, streamID)] function, the local user can receive other video data other than the `streamID`; call the [mutePlayStreamVideo(false, streamID)] function, the local user can receive all the video data.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID.
/// @param mute Whether it is possible to receive the video data of the specified remote user when streaming, "true" means prohibition, "false" means receiving, the default value is "false".
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_play_stream_video(const char *stream_id,
                                                                    bool mute);

/// Can the pull stream receive all audio data.
///
/// Available since: 2.4.0
/// Description: In the process of real-time audio and video interaction, local users can use this function to control whether to receive audio data from all remote users when pulling streams (including the audio streams pushed by users who have newly joined the room after calling this function). By default, users can receive audio data pushed by all remote users after joining the room. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
/// Use cases: Call this function when developers need to quickly close and restore remote audio. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
/// When to call: This function can be called after calling [createEngine].
/// Related APIs: You can call the [mutePlayStreamAudio] function to control whether to receive a single piece of audio data. When the two functions [muteAllPlayStreamAudio] and [mutePlayStreamAudio] are set to `false` at the same time, the local user can receive the audio data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamAudio(true)] function is called, it takes effect globally, that is, local users will be prohibited from receiving audio data from all remote users. At this time, the [mutePlayStreamAudio] function will not take effect no matter if the [mutePlayStreamAudio] function is called before or after [muteAllPlayStreamAudio]. 2. When the [muteAllPlayStreamAudio(false)] function is called, the local user can receive the audio data of all remote users. At this time, the [mutePlayStreamAudio] function can be used to control whether to receive a single audio data. Calling the [mutePlayStreamAudio(true, streamID)] function allows the local user to receive audio data other than the `streamID`; calling the [mutePlayStreamAudio(false, streamID)] function allows the local user to receive all audio data.
///
/// @param mute Whether it is possible to receive audio data from all remote users when streaming, "true" means prohibition, "false" means receiving, and the default value is "false".
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_all_play_stream_audio(bool mute);

/// Can the pull stream receive all video data.
///
/// Available since: 2.4.0
/// Description: In the process of real-time video and video interaction, local users can use this function to control whether to receive all remote users' video data when pulling the stream (including the video stream pushed by the new user who joins the room after calling this function). By default, users can receive video data pushed by all remote users after joining the room. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
/// Use cases: This function can be called when developers need to quickly close and resume watching remote video. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
/// When to call: This function can be called after calling [createEngine].
/// Caution: When you mute the video stream, the view remains at the last frame by default, if you need to clear the last frame, please contact ZEGO technical support.
/// Related APIs: You can call the [mutePlayStreamVideo] function to control whether to receive a single piece of video data. When the two functions [muteAllPlayStreamVideo] and [mutePlayStreamVideo] are set to `false` at the same time, the local user can receive the video data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamVideo(true)] function is called, it will take effect globally, that is, the local user will be prohibited from receiving all remote users' video data. At this time, the [mutePlayStreamVideo] function will not take effect whether it is called before or after [muteAllPlayStreamVideo]. 2. When the [muteAllPlayStreamVideo(false)] function is called, the local user can receive the video data of all remote users. At this time, the [mutePlayStreamVideo] function can be used to control whether to receive a single video data. Call the [mutePlayStreamVideo(true, streamID)] function, the local user can receive other video data other than the `streamID`; call the [mutePlayStreamVideo(false, streamID)] function, the local user can receive all the video data.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mute Whether it is possible to receive all remote users' video data when streaming, "true" means prohibition, "false" means receiving, and the default value is "false".
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_all_play_stream_video(bool mute);

/// Enables or disables hardware decoding.
///
/// Available since: 1.1.0
/// Description: Control whether hardware decoding is used when playing streams, with hardware decoding enabled the SDK will use the GPU for decoding, reducing CPU usage.
/// Use cases: If developers find that the device heats up badly when playing large resolution audio and video streams during testing on some models, consider calling this function to enable hardware decoding.
/// Default value: Hardware decoding is disabled by default when this interface is not called.
/// When to call: This function needs to be called after [createEngine] creates an instance.
/// Restrictions: None.
/// Caution: Need to be called before calling [startPlayingStream], if called after playing the stream, it will only take effect after stopping the stream and re-playing it. Once this configuration has taken effect, it will remain in force until the next call takes effect.
///
/// @param enable Whether to turn on hardware decoding switch, true: enable hardware decoding, false: disable hardware decoding.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_hardware_decoder(bool enable);

/// Enables or disables frame order detection.
///
/// Available since: 1.1.0
/// Description: Control whether to turn on frame order detection, on to not support B frames, off to support B frames.
/// Use cases: Turning on frame order detection when pulling cdn's stream will prevent splash screens.
/// Default value: Turn on frame order detection by default when this interface is not called.
/// When to call: This function needs to be called after [createEngine] creates an instance.
/// Restrictions: None.
/// Caution: Turn off frame order detection during playing stream may result in a brief splash screen.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable Whether to turn on frame order detection, true: enable check poc,not support B frames, false: disable check poc, support B frames.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_check_poc(bool enable);

/// Whether the specified video decoding format is supported.
///
/// Available since: 2.12.0
/// Description: Whether the specified video decoding is supported depends on the following aspects: whether the hardware model supports hard decoding, whether the performance of the hardware model supports soft decoding, and whether the SDK includes the decoding module.
/// When to call: After creating the engine.
/// Caution: It is recommended that users call this interface to obtain the H.265 decoding support capability before pulling the H.265 stream. If it is not supported, the user can pull the stream of other encoding formats, such as H.264.
///
/// @param codec_id Video codec id.Required: Yes.
/// @return Whether the specified video decoding format is supported; true means support, you can use this decoding format for playing stream; false means the is not supported, and the decoding format cannot be used for play stream.
ZEGOEXP_API bool EXP_CALL
zego_express_is_video_decoder_supported(enum zego_video_codec_id codec_id);

/// Set the play stream alignment properties.
///
/// Available since: 2.14.0
/// Description: When playing at the streaming end, control whether the playing RTC stream needs to be accurately aligned. If necessary, all the streams that contain precise alignment parameters will be aligned; if not, all streams are not aligned.
/// Use case: It is often used in scenes that require mixed stream alignment such as KTV to ensure that users can switch between singing anchors, ordinary Maishangyu chat anchors, and Maixia audiences at any time during use.
/// Default value: If this interface is not called, the default is not aligned.
/// When to call: Called after [createEngine]. Call the interface repeatedly, and the latest setting is valid.
/// Related APIs: Set the precise alignment parameter of the stream channel [setStreamAlignmentProperty].
///
/// @param mode Setting the stream alignment mode.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_play_streams_alignment_property(enum zego_stream_alignment_mode mode);

/// The callback triggered when the state of stream playing changes.
///
/// Available since: 1.1.0
/// Description: After calling the [startPlayingStream] successfully, the notification of the playing stream state change can be obtained through the callback function. You can roughly judge the user's downlink network status based on whether the state parameter is in [PLAY_REQUESTING].
/// When to trigger:  After calling the [startPublishingStream], this callback is triggered when a playing stream's state changed.
/// Related callbacks: After calling the [startPublishingStream] successfully, the notification of the publish stream state change can be obtained through the callback function [onPublisherStateUpdate]. You can roughly judge the user's uplink network status based on whether the state parameter is in [PUBLISH_REQUESTING].
///
/// @param stream_id stream ID.
/// @param state State of playing stream.
/// @param error_code The error code corresponding to the status change of the playing stream, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param extended_data Extended Information with state updates. As the standby, only an empty json table is currently returned.
/// @param user_context Context of user.
typedef void (*zego_on_player_state_update)(const char *stream_id, enum zego_player_state state,
                                            zego_error error_code, const char *extended_data,
                                            void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_state_update_callback(
    zego_on_player_state_update callback_func, void *user_context);

/// Callback for current stream playing quality.
///
/// Available since: 1.1.0
/// Description: After calling the [startPlayingStream] successfully, this callback will be triggered every 3 seconds. The collection frame rate, bit rate, RTT, packet loss rate and other quality data can be obtained, and the health of the played audio and video streams can be monitored in real time.
/// Use cases: You can monitor the health of the played audio and video streams in real time according to the quality parameters of the callback function, in order to show the downlink network status on the device UI in real time.
/// Caution: If you does not know how to use the various parameters of the callback function, you can only focus on the level field of the quality parameter, which is a comprehensive value describing the downlink network calculated by SDK based on the quality parameters.
/// Related callbacks: After calling the [startPublishingStream] successfully, a callback [onPublisherQualityUpdate] will be received every 3 seconds. You can monitor the health of publish streams in real time based on quality data such as frame rate, code rate, RTT, packet loss rate, etc.
///
/// @param stream_id Stream ID.
/// @param quality Playing stream quality, including audio and video framerate, bitrate, RTT, etc.
/// @param user_context Context of user.
typedef void (*zego_on_player_quality_update)(const char *stream_id,
                                              struct zego_play_stream_quality quality,
                                              void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_quality_update_callback(
    zego_on_player_quality_update callback_func, void *user_context);

/// The callback triggered when a media event occurs during streaming playing.
///
/// Available since: 1.1.0
/// Description: This callback is used to receive pull streaming events.
/// Use cases: You can use this callback to make statistics on stutters or to make friendly displays in the UI of the app.
/// When to trigger:  After calling the [startPublishingStream], this callback is triggered when an event such as audio and video jamming and recovery occurs in the playing stream.
///
/// @param stream_id Stream ID.
/// @param event Specific events received when playing the stream.
/// @param user_context Context of user.
typedef void (*zego_on_player_media_event)(const char *stream_id,
                                           enum zego_player_media_event event, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_media_event_callback(
    zego_on_player_media_event callback_func, void *user_context);

/// The callback triggered when the first audio frame is received.
///
/// Available since: 1.1.0
/// Description: After the [startPlayingStream] function is called successfully, this callback will be called when SDK received the first frame of audio data.
/// Use cases: Developer can use this callback to count time consuming that take the first frame time or update the UI for playing stream.
/// Trigger: This callback is triggered when SDK receives the first frame of audio data from the network.
/// Related callbacks: After a successful call to [startPlayingStream], the callback function [onPlayerRecvVideoFirstFrame] determines whether the SDK has received the video data, and the callback [onPlayerRenderVideoFirstFrame] determines whether the SDK has rendered the first frame of the received video data.
///
/// @param stream_id Stream ID.
/// @param user_context Context of user.
typedef void (*zego_on_player_recv_audio_first_frame)(const char *stream_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_recv_audio_first_frame_callback(
    zego_on_player_recv_audio_first_frame callback_func, void *user_context);

/// The callback triggered when the first video frame is received.
///
/// Available since: 1.1.0
/// Description: After the [startPlayingStream] function is called successfully, this callback will be called when SDK received the first frame of video data.
/// Use cases: Developer can use this callback to count time consuming that take the first frame time or update the UI for playing stream.
/// Trigger: This callback is triggered when SDK receives the first frame of video data from the network.
/// Related callbacks: After a successful call to [startPlayingStream], the callback function [onPlayerRecvAudioFirstFrame] determines whether the SDK has received the audio data, and the callback [onPlayerRenderVideoFirstFrame] determines whether the SDK has rendered the first frame of the received video data.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID.
/// @param user_context Context of user.
typedef void (*zego_on_player_recv_video_first_frame)(const char *stream_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_recv_video_first_frame_callback(
    zego_on_player_recv_video_first_frame callback_func, void *user_context);

/// The callback triggered when the first video frame is rendered.
///
/// Available since: 1.1.0
/// Description: After the [startPlayingStream] function is called successfully, this callback will be called when SDK rendered the first frame of video data.
/// Use cases: Developer can use this callback to count time consuming that take the first frame time or update the UI for playing stream.
/// Trigger: This callback is triggered when SDK rendered the first frame of video data from the network.
/// Related callbacks: After a successful call to [startPlayingStream], the callback function [onPlayerRecvAudioFirstFrame] determines whether the SDK has received the audio data, and the callback [onPlayerRecvVideoFirstFrame] determines whether the SDK has received the video data.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID.
/// @param user_context Context of user.
typedef void (*zego_on_player_render_video_first_frame)(const char *stream_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_render_video_first_frame_callback(
    zego_on_player_render_video_first_frame callback_func, void *user_context);

/// The callback triggered when the stream playback resolution changes.
///
/// Available since: 1.1.0
/// Description: After the [startPlayingStream] function is called successfully, the play resolution will change when the first frame of video data is received, or when the publisher changes the encoding resolution by calling [setVideoConfig], or when the network traffic control strategies work.
/// Use cases: Developers can update or switch the UI components that actually play the stream based on the final resolution of the stream.
/// Trigger: After the [startPlayingStream] function is called successfully, this callback is triggered when the video resolution changes while playing the stream.
/// Caution: If the stream is only audio data, the callback will not be triggered.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID.
/// @param width Video decoding resolution width.
/// @param height Video decoding resolution height.
/// @param user_context Context of user.
typedef void (*zego_on_player_video_size_changed)(const char *stream_id, int width, int height,
                                                  void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_video_size_changed_callback(
    zego_on_player_video_size_changed callback_func, void *user_context);

/// The callback triggered when Supplemental Enhancement Information is received.
///
/// Available since: 1.1.0
/// Description: After the [startPlayingStream] function is called successfully, when the remote stream sends SEI (such as directly calling [sendSEI], audio mixing with SEI data, and sending custom video capture encoded data with SEI, etc.), the local end will receive this callback.
/// Trigger: After the [startPlayingStream] function is called successfully, when the remote stream sends SEI, the local end will receive this callback.
/// Caution: 1. Since the video encoder itself generates an SEI with a payload type of 5, or when a video file is used for publishing, such SEI may also exist in the video file. Therefore, if the developer needs to filter out this type of SEI, it can be before [createEngine] Call [ZegoEngineConfig.advancedConfig("unregister_sei_filter", "XXXXX")]. Among them, unregister_sei_filter is the key, and XXXXX is the uuid filter string to be set. 2. When [mutePlayStreamVideo] or [muteAllPlayStreamVideo] is called to set only the audio stream to be pulled, the SEI will not be received.
///
/// @param stream_id Stream ID.
/// @param data SEI content.
/// @param data_length SEI content length.
/// @param user_context Context of user.
typedef void (*zego_on_player_recv_sei)(const char *stream_id, const unsigned char *data,
                                        unsigned int data_length, void *user_context);

ZEGOEXP_API void EXP_CALL
zego_register_player_recv_sei_callback(zego_on_player_recv_sei callback_func, void *user_context);

/// Receive the audio side information content of the remote stream.
///
/// Available since: 2.19.0
/// Description: After the [startPlayingStream] function is called successfully, when the remote stream sends audio side information, the local end will receive this callback.
/// Trigger: After the [startPlayingStream] function is called successfully, when the remote stream sends audio side information, the local end will receive this callback.
/// Caution: 1. When [mutePlayStreamAudio] or [muteAllPlayStreamAudio] is called to set only the video stream to be pulled, the audio side information not be received. 2. Due to factors such as the network, the received data may be missing, but the order is guaranteed.
/// Related APIs: Send audio side information by the [sendAudioSideInfo] function.
///
/// @param stream_id Stream ID.
/// @param data Audio side information content.
/// @param data_length Audio side information content length.
/// @param user_context Context of user.
typedef void (*zego_on_player_recv_audio_side_info)(const char *stream_id,
                                                    const unsigned char *data,
                                                    unsigned int data_length, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_recv_audio_side_info_callback(
    zego_on_player_recv_audio_side_info callback_func, void *user_context);

/// Playing stream low frame rate warning.
///
/// Available since: 2.14.0
/// Description: This callback triggered by low frame rate when playing stream.
/// When to trigger: This callback triggered by low frame rate when playing stream.
/// Caution: If the callback is triggered when the user playing the h.265 stream, you can stop playing the h.265 stream and switch to play the H.264 stream.
///
/// @param codec_id Video codec ID.
/// @param stream_id Stream ID.
/// @param user_context Context of user.
typedef void (*zego_on_player_low_fps_warning)(enum zego_video_codec_id codec_id,
                                               const char *stream_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_low_fps_warning_callback(
    zego_on_player_low_fps_warning callback_func, void *user_context);

/// The callback triggered when playing stream.
///
/// Available since: 2.18.0
/// Description: After start playing stream, this callback will return the current stream address, resource type and protocol-related information.
/// When to trigger: Play and retry play events.
/// Caution: None.
///
/// @param event_id Play stream event ID
/// @param stream_id Stream ID.
/// @param extra_info extra info. it is in JSON format. Included information includes "url" for address, "streamProtocol" for stream protocol, including rtmp, flv, avertp, hls, webrtc, etc. "netProtocol" for network protocol, including tcp, udp, quic, "resourceType" for resource type , including cdn, rtc, l3.
/// @param user_context Context of user.
typedef void (*zego_on_player_stream_event)(enum zego_stream_event event_id, const char *stream_id,
                                            const char *extra_info, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_stream_event_callback(
    zego_on_player_stream_event callback_func, void *user_context);

/// [Deprecated] Set the selected video layer of playing stream. This function has been deprecated since version 2.3.0, Please use [setPlayStreamVideoType] instead.
///
/// Available: 1.19.0 to 2.3.0, deprecated.
/// This function has been deprecated since version 2.3.0, Please use [setPlayStreamVideoType] instead.
/// When the publisher has set the codecID to SVC through [setVideoConfig], the player can dynamically set whether to use the standard layer or the base layer (the resolution of the base layer is one-half of the standard layer)
/// Under normal circumstances, when the network is weak or the rendered UI form is small, you can choose to use the video that plays the base layer to save bandwidth.
/// It can be set before and after playing stream.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @deprecated This function has been deprecated since version 2.3.0, Please use [setPlayStreamVideoType] instead.
/// @param stream_id Stream ID.
/// @param video_layer Video layer of playing stream. AUTO by default.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_play_stream_video_layer(
    const char *stream_id, enum zego_player_video_layer video_layer);

/// Results of take play stream snapshot.
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param stream_id Stream ID
/// @param image Snapshot image (Windows: HBITMAP; macOS/iOS: CGImageRef; Linux: QImage; Android: Bitmap)
/// @param user_context Context of user.
typedef void (*zego_on_player_take_snapshot_result)(zego_error error_code, const char *stream_id,
                                                    void *image, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_take_snapshot_result_callback(
    zego_on_player_take_snapshot_result callback_func, void *user_context);

ZEGO_END_DECLS

#endif
