
#ifndef __ZEGO_EXPRESS_PUBLISHER_H__
#define __ZEGO_EXPRESS_PUBLISHER_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Starts publishing a stream (for the specified channel). You can call this function to publish a second stream.
///
/// Available since: 1.1.0
/// Description: Users push their local audio and video streams to the ZEGO RTC server or CDN, and other users in the same room can pull the audio and video streams to watch through the `streamID` or CDN pull stream address.
/// Use cases: It can be used to publish streams in real-time connecting wheat, live broadcast and other scenarios.
/// When to call: After [loginRoom].
/// Restrictions: None.
/// Caution:
///   1. Before start to publish the stream, the user can choose to call [setVideoConfig] to set the relevant video parameters, and call [startPreview] to preview the video.
///   2. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the local user publishing stream successfully.
///   3. In the case of poor network quality, user publish may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error information of the stream published by monitoring the [onPublisherStateUpdate] event.
///
/// @param stream_id Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_start_publishing_stream(const char *stream_id, enum zego_publish_channel channel);

/// Starts publishing a stream. Support multi-room mode.
///
/// Available since: 1.1.0
/// Description: Users push their local audio and video streams to the ZEGO RTC server or CDN, and other users in the same room can pull the audio and video streams to watch through the `streamID` or CDN pull stream address.
/// Use cases: It can be used to publish streams in real-time connecting wheat, live broadcast and other scenarios.
/// When to call: After [loginRoom].
/// Restrictions: None.
/// Caution:
///   1. Before start to publish the stream, the user can choose to call [setVideoConfig] to set the relevant video parameters, and call [startPreview] to preview the video.
///   2. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the local user publishing stream successfully.
///   3. In the case of poor network quality, user publish may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error information of the stream published by monitoring the [onPublisherStateUpdate] event.
///   4. To call [SetRoomMode] function to select multiple rooms, the room ID must be specified explicitly.
///
/// @param stream_id Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
/// @param config Advanced publish configuration.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_start_publishing_stream_with_config(
    const char *stream_id, struct zego_publisher_config config, enum zego_publish_channel channel);

/// Stops publishing a stream (for the specified channel).
///
/// Available since: 1.1.0
/// Description: The user stops sending local audio and video streams, and other users in the room will receive a stream deletion notification.
/// Use cases: It can be used to stop publish streams in real-time connecting wheat, live broadcast and other scenarios.
/// When to call: After [startPublishingStream].
/// Restrictions: None.
/// Caution:
///   1. After stopping the streaming, other users in the same room can receive the delete notification of the stream by listening to the [onRoomStreamUpdate] callback.
///   2. If the user has initiated publish flow, this function must be called to stop the publish of the current stream before publishing the new stream (new streamID), otherwise the new stream publish will return a failure.
///   3. After stopping streaming, the developer should stop the local preview based on whether the business situation requires it.
///
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_stop_publishing_stream(enum zego_publish_channel channel);

/// Sets the extra information of the stream being published for the specified publish channel.
///
/// Available since: 1.1.0
/// Description: Use this function to set the extra info of the stream. The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the publishing process, the stream extra information can be modified midway through the stream corresponding to the stream ID. Developers can synchronize variable content related to stream IDs based on stream additional information.
/// When to call: After the engine is created [createEngine], Called before and after [startPublishingStream] can both take effect.
/// Restrictions: None.
/// Related callbacks: Users can obtain the execution result of the function through [ZegoPublisherSetStreamExtraInfoCallback] callback.
///
/// @param extra_info Stream extra information, a string of up to 1024 characters.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_seq EXP_CALL zego_express_set_stream_extra_info(const char *extra_info,
                                                                 enum zego_publish_channel channel);

/// Starts/Updates the local video preview (for the specified channel).
///
/// Available since: 1.1.0
/// Description: The user can see his own local image by calling this function.
/// Use cases: It can be used for local preview in real-time connecting wheat, live broadcast and other scenarios.
/// When to call: After [createEngine].
/// Restrictions: None.
/// Caution: 1. The preview function does not require you to log in to the room or publish the stream first. But after exiting the room, SDK internally actively stops previewing by default. 2. Local view and preview modes can be updated by calling this function again. The user can only preview on one view. If you call [startPreview] again to pass in a new view, the preview screen will only be displayed in the new view. 3. You can set the mirror mode of the preview by calling the [setVideoMirrorMode] function. The default preview setting is image mirrored. 4. When this function is called, the audio and video engine module inside SDK will start really, and it will start to try to collect audio and video..
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param canvas The view used to display the preview image. If the view is set to NULL, no preview will be made.
/// @param channel Publish stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_start_preview(struct zego_canvas *canvas,
                                                           enum zego_publish_channel channel);

/// Stops the local preview (for the specified channel).
///
/// Available since: 1.1.0
/// Description: This function can be called to stop the preview when the preview is not needed locally.
/// Caution: Stopping the preview will not affect the publish stream and playing stream functions.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publish stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_preview(enum zego_publish_channel channel);

/// Sets up the video configurations (for the specified channel).
///
/// Available since: 1.1.0
/// Description: Set the video frame rate, bit rate, video capture resolution, and video encoding output resolution.
/// Default value: The default video capture resolution is 360p, the video encoding output resolution is 360p, the bit rate is 600 kbps, and the frame rate is 15 fps.
/// When to call: After [createEngine].
/// Restrictions: It is necessary to set the relevant video configuration before publishing the stream or startPreview, and only support the modification of the encoding resolution and the bit rate after publishing the stream.
/// Caution: Developers should note that the wide and high resolution of the mobile end is opposite to the wide and high resolution of the PC. For example, in the case of 360p, the resolution of the mobile end is 360x640, and the resolution of the PC end is 640x360.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param config Video configuration, the SDK provides a common setting combination of resolution, frame rate and bit rate, they also can be customized.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_video_config(struct zego_video_config config,
                                                              enum zego_publish_channel channel);

/// Gets the current video configurations (for the specified channel).
///
/// This function can be used to get the specified publish channel's current video frame rate, bit rate, video capture resolution, and video encoding output resolution.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publish stream channel
/// @return Video configuration object
ZEGOEXP_API struct zego_video_config EXP_CALL
zego_express_get_video_config(enum zego_publish_channel channel);

/// Sets the video mirroring mode (for the specified channel).
///
/// Available since: 1.1.0
/// Description: Set whether the local preview video and the published video have mirror mode enabled. For specific mirroring mode.
/// When to call: After [createEngine].
/// Restrictions: None.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mirror_mode Mirror mode for previewing or publishing the stream.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_video_mirror_mode(
    enum zego_video_mirror_mode mirror_mode, enum zego_publish_channel channel);

/// Sets the video orientation (for the specified channel).
///
/// Available since: 1.1.0
/// Description: Set the video orientation, please refer to https://doc-zh.zego.im/article/10365.
/// Use cases: When users use mobile devices to conduct live broadcasts or video calls, they can set different video directions according to the scene.
/// When to call: After [createEngine].
/// Restrictions: None.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param orientation Video orientation.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_app_orientation(enum zego_orientation orientation,
                                                                 enum zego_publish_channel channel);

/// Available since: 1.1.0
/// Description: Set the video orientation, please refer to https://doc-zh.zego.im/article/10365.
/// Use cases: When users use mobile devices to conduct live broadcasts or video calls, they can set different video directions according to the scene.
/// When to call: After [createEngine].
/// Restrictions: None.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param orientation Video orientation.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_ios_app_orientation(
    enum zego_ios_orientation orientation, enum zego_publish_channel channel);

/// Sets up the audio configurations.
///
/// Available since: 1.3.4
/// Description: You can set the combined value of the audio codec, bit rate, and audio channel through this function. If the preset value cannot meet the developer's scenario, the developer can set the parameters according to the business requirements.
/// Default value: The default audio config refers to the default value of [ZegoAudioConfig].
/// When to call: After the engine is created [createEngine], and before publishing [startPublishingStream].
/// Restrictions: None.
/// Caution: Act on the main publish channel ZegoPublishChannel.Main.
/// Related APIs: [getAudioConfig].
///
/// @param config Audio config.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_audio_config(struct zego_audio_config config);

/// Sets up the audio configurations for the specified publish channel.
///
/// Available since: 1.3.4
/// Description: You can set the combined value of the audio codec, bit rate, and audio channel through this function. If the preset value cannot meet the developer's scenario, the developer can set the parameters according to the business requirements.
/// Default value: The default audio config refers to the default value of [ZegoAudioConfig].
/// When to call: After the engine is created [createEngine], and before publishing [startPublishingStream].
/// Restrictions: None.
/// Related APIs: [getAudioConfig].
///
/// @param config Audio config.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_audio_config_by_channel(
    struct zego_audio_config config, enum zego_publish_channel channel);

/// Gets the current audio configurations.
///
/// Available since: 1.8.0
/// Description: You can get the current audio codec, bit rate, and audio channel through this function.
/// When to call: After the engine is created [createEngine].
/// Restrictions: None.
/// Caution: Act on the main publish channel ZegoPublishChannel.Main.
/// Related APIs: [setAudioConfig].
///
/// @return Audio config.
ZEGOEXP_API struct zego_audio_config EXP_CALL zego_express_get_audio_config();

/// Gets the current audio configurations from the specified publish channel.
///
/// Available since: 1.8.0
/// Description: You can get the current audio codec, bit rate, and audio channel through this function.
/// When to call: After the engine is created [createEngine].
/// Restrictions: None.
/// Related APIs: [setAudioConfig].
///
/// @param channel Publish stream channel.
/// @return Audio config.
ZEGOEXP_API struct zego_audio_config EXP_CALL
zego_express_get_audio_config_by_channel(enum zego_publish_channel channel);

/// Set encryption key for the publishing stream for the specified publish channel.
///
/// Available since: 1.19.0
/// Description: Support calling this function to update the encryption key while publishing stream.
/// When to call: After the engine is created [createEngine], Called before and after [startPublishingStream] can both take effect.
/// Restrictions: This function is only valid when publishing stream to the Zego RTC server.
/// Caution: Note that developers need to update the player's decryption key before updating the publisher's encryption key.
/// Related APIs: Calling [stopPublishingStream] or [logoutRoom] will clear the encryption key.
///
/// @param key The encryption key, note that the key length only supports 16/24/32 bytes.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_publish_stream_encryption_key(const char *key, enum zego_publish_channel channel);

/// Take a snapshot of the publishing stream for the specified publish channel.
///
/// Available since: 1.17.0
/// Description: Take a snapshot of the publishing stream.
/// When to call: Called this function after calling [startPublishingStream] or [startPreview].
/// Restrictions: None.
/// Caution: The resolution of the snapshot is the encoding resolution set in [setVideoConfig]. If you need to change it to capture resolution, please call [setCapturePipelineScaleMode] to change the capture pipeline scale mode to [Post].
/// Related callbacks: The screenshot result will be called back through [ZegoPublisherTakeSnapshotCallback].
/// Related APIs: [takePlayStreamSnapshot].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_take_publish_stream_snapshot(enum zego_publish_channel channel);

/// Stops or resumes sending the audio part of a stream for the specified channel.
///
/// Available since: 1.1.0
/// Description: This function can be called when publishing the stream to realize not publishing the audio data stream. The SDK still collects and processes the audio, but does not send the audio data to the network.
/// When to call: Called after the engine is created [createEngine] can take effect.
/// Restrictions: None.
/// Related callbacks: If you stop sending audio streams, the remote user that play stream of local user publishing stream can receive `Mute` status change notification by monitoring [onRemoteMicStateUpdate] callbacks.
/// Related APIs: [mutePublishStreamVideo].
///
/// @param mute Whether to stop sending audio streams, true means not to send audio stream, and false means sending audio stream. The default is false.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_mute_publish_stream_audio(bool mute, enum zego_publish_channel channel);

/// Stops or resumes sending the video part of a stream for the specified channel.
///
/// Available since: 1.1.0
/// Description: This function can be called when publishing the stream to realize not publishing the video stream. The local camera can still work normally, can capture, preview and process video images normally, but does not send the video data to the network.
/// When to call: Called after the engine is created [createEngine] can take effect.
/// Restrictions: None.
/// Related callbacks: If you stop sending video streams locally, the remote user that play stream of local user publishing stream can receive `Mute` status change notification by monitoring [onRemoteCameraStateUpdate] callbacks.
/// Related APIs: [mutePublishStreamAudio].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mute Whether to stop sending video streams, true means not to send video stream, and false means sending video stream. The default is false.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_mute_publish_stream_video(bool mute, enum zego_publish_channel channel);

/// Enable or disable the stream mixing precision alignment function.
///
/// Available since: 2.11.0.
/// Description: Use this interface to enable stream alignment, the SDK will attach network time information to the stream when publishing it for accurate stream alignment.
/// Use case: Generally used in scenarios such as KTV where stream mixing alignment is required.
/// When to call: After the engine is created [createEngine].
/// Caution: If mixed flow need time for alignment, the flow through the network push flow need to call startPublishingStream and ZegoPublisherConfig.forceSynchronousNetworkTime = 1, for open network time synchronization.
/// Related APIs: [startMixerTask], [startAutoMixerTask]
///
/// @param alignment Whether to enable the stream mixing precision alignment function.
/// @param channel Publish stream channel
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_stream_alignment_property(int alignment, enum zego_publish_channel channel);

/// Enables or disables traffic control.
///
/// Available since: 1.5.0
/// Description: Enabling traffic control allows the SDK to adjust the audio and video streaming bitrate according to the current upstream network environment conditions, or according to the counterpart's downstream network environment conditions in a one-to-one interactive scenario, to ensure smooth results. At the same time, you can further specify the attributes of traffic control to adjust the corresponding control strategy.
/// Default value: Enable.
/// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
/// Restrictions: Only support RTC publish.
/// Caution: Act on the main publish channel ZegoPublishChannel.Main.
///
/// @param enable Whether to enable traffic control. The default is ture.
/// @param property Adjustable property of traffic control, bitmask OR format. Should be one or the combinations of [ZegoTrafficControlProperty] enumeration. [AdaptiveFPS] as default.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_traffic_control(bool enable, int property);

/// Enables or disables the traffic control for the specified publish channel.
///
/// Available since: 1.5.0
/// Description: Enabling traffic control allows the SDK to adjust the audio and video streaming bitrate according to the current upstream network environment conditions, or according to the counterpart's downstream network environment conditions in a one-to-one interactive scenario, to ensure smooth results. At the same time, you can further specify the attributes of traffic control to adjust the corresponding control strategy.
/// Default value: Enable.
/// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
/// Restrictions: Only support RTC publish.
///
/// @param enable Whether to enable traffic control. The default is ture.
/// @param property Adjustable property of traffic control, bitmask format. Should be one or the combinations of [ZegoTrafficControlProperty] enumeration. [AdaptiveFPS] as default.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_traffic_control_by_channel(
    bool enable, int property, enum zego_publish_channel channel);

/// Set the minimum video bitrate threshold for traffic control.
///
/// Available since: 1.1.0
/// Description: Set the control strategy when the video bitrate reaches the lowest threshold during flow control. When the bitrate is lower than the minimum threshold, you can choose not to send video data or send it at a very low frame bitrate.
/// Default value: There is no control effect of the lowest threshold of video bitrate.
/// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
/// Restrictions: The traffic control must be turned on [enableTrafficControl].
/// Caution: Act on the main publish channel ZegoPublishChannel.Main.
/// Related APIs: [enableTrafficControl].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param bitrate Minimum video bitrate threshold for traffic control(kbps).
/// @param mode Video sending mode below the minimum bitrate.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_min_video_bitrate_for_traffic_control(
    int bitrate, enum zego_traffic_control_min_video_bitrate_mode mode);

/// Sets the minimum video bitrate for traffic control for the specified publish channel.
///
/// Available since: 1.1.0
/// Description: Set the control strategy when the video bitrate reaches the lowest threshold during flow control. When the bitrate is lower than the minimum threshold, you can choose not to send video data or send it at a very low frame bitrate.
/// Default value: There is no control effect of the lowest threshold of video bitrate.
/// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
/// Restrictions: The traffic control must be turned on [enableTrafficControl].
/// Related APIs: [enableTrafficControl].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param bitrate Minimum video bitrate (kbps).
/// @param mode Video sending mode below the minimum bitrate.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_min_video_bitrate_for_traffic_control_by_channel(
    int bitrate, enum zego_traffic_control_min_video_bitrate_mode mode,
    enum zego_publish_channel channel);

/// Sets the minimum video frame rate threshold for traffic control.
///
/// Available since: 2.17.0
/// Description: Set the control policy when the video frame rate reaches the lowest threshold when flow control.
/// Default value: There is no control effect of the lowest threshold of video frame rate.
/// When to call: The call takes effect after the engine [createEngine] is created.
/// Restrictions: The traffic control must be turned on [enableTrafficControl]. And its parameter [property] must contain AdaptiveFPS, Please refer to [ZegoTrafficControlProperty] for details.
/// Related APIs: [enableTrafficControl].
/// Caution: If you need to cancel the limit of the setting value, you can set it to 0.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param fps The minimum video frame rate threshold for traffic control(fps).
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_min_video_fps_for_traffic_control_by_channel(
    int fps, enum zego_publish_channel channel);

/// Sets the minimum video resolution threshold for traffic control.
///
/// Available since: 2.17.0
/// Description: Set the control policy when the video resolution reaches the lowest threshold when flow control.
/// Default value: There is no control effect of the lowest threshold of video resolution.
/// When to call: The call takes effect after the engine [createEngine] is created.
/// Restrictions: The traffic control must be turned on [enableTrafficControl]. And its parameter [property] must contain AdaptiveResolution, Please refer to [ZegoTrafficControlProperty] for details.
/// Related APIs: [enableTrafficControl].
/// Caution: If you need to cancel the limit of the setting value, you can set width and height to 0.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param width The flow controls the width of the lowest video resolution.
/// @param height The flow controls the height of the lowest video resolution.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_min_video_resolution_for_traffic_control_by_channel(
    int width, int height, enum zego_publish_channel channel);

/// Set the factors of concern that trigger traffic control.
///
/// Available since: 2.4.0
/// Description: Use this interface to control whether to start traffic control due to poor remote network conditions.
/// Default value: Default is disable.
/// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
/// Restrictions: The traffic control must be turned on [enableTrafficControl].
/// Related APIs: [enableTrafficControl.
///
/// @param mode When LOCAL_ONLY is selected, only the local network status is concerned. When choosing REMOTE, also take into account the remote network.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_traffic_control_focus_on(enum zego_traffic_control_focus_on_mode mode);

/// Set the factors of concern that trigger traffic control for the specified publish channel.
///
/// Available since: 2.4.0
/// Description: Use this interface to control whether to start traffic control due to poor remote network conditions.
/// Default value: Default is disable.
/// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
/// Restrictions: The traffic control must be turned on [enableTrafficControl].
/// Related APIs: [enableTrafficControl.
///
/// @param mode When LOCAL_ONLY is selected, only the local network status is concerned. When choosing REMOTE, also take into account the remote network.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_traffic_control_focus_on_by_channel(
    enum zego_traffic_control_focus_on_mode mode, enum zego_publish_channel channel);

/// Sets the audio recording volume for stream publishing.
///
/// Available since: 1.13.0
/// Description: This function is used to perform gain processing based on the device's collected volume. The local user can control the sound level of the audio stream sent to the remote end.
/// Default value: Default is 100.
/// When to call: After creating the engine [createEngine].
/// Restrictions: The capture volume can be dynamically set during publishing.
/// Related APIs: Set the playing stream volume [setPlayVolume].
///
/// @param volume The volume gain percentage, the range is 0 ~ 200, and the default value is 100, which means 100% of the original collection volume of the device.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_capture_volume(int volume);

/// Set audio capture stereo mode.
///
/// Available since: 1.15.0 (iOS/Android/Windows); support macOS since 2.16.0
/// Description: This function is used to set the audio capture channel mode. When the developer turns on the stereo capture, using a special stereo capture device, the stereo audio data can be captured and streamed.
/// Use cases: In some professional scenes, users are particularly sensitive to sound effects, such as voice radio and musical instrument performance. At this time, support for stereo and high-quality sound is required.
/// Default value: The default is None, which means mono capture.
/// When to call: It needs to be called after [createEngine]， before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Restrictions: If you need to enable stereo capture, you also need to meet the following conditions: For iOS/Android, you need to connect an external audio device that supports stereo capture and be at the media volume. For macOS, it needs to be at the media volume. For Windows, an external audio device that supports stereo capture is required.
/// Related APIs: When streaming, you need to enable the stereo audio encoding function through the [setAudioConfig] interface at the same time.
///
/// @param mode Audio stereo capture mode.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_audio_capture_stereo_mode(enum zego_audio_capture_stereo_mode mode);

/// Adds a target CDN URL to which the stream will be relayed from ZEGO RTC server.
///
/// Available since: 1.1.0
/// Description: Forward audio and video streams from ZEGO RTC servers to custom CDN content distribution networks with high latency but support for high concurrent pull streams.
/// Use cases: 1. It is often used in large-scale live broadcast scenes that do not have particularly high requirements for delay. 2. Since ZEGO RTC server itself can be configured to support CDN(content distribution networks), this function is mainly used by developers who have CDN content distribution services themselves. 3. This function supports dynamic relay to the CDN content distribution network, so developers can use this function as a disaster recovery solution for CDN content distribution services.
/// When to call: After calling the [createEngine] function to create the engine.
/// Restrictions: When the [enablePublishDirectToCDN] function is set to true to publish the stream straight to the CDN, then calling this function will have no effect.
/// Caution: Removing URLs retweeted to CDN requires calling [removePublishCdnUrl], calling [stopPublishingStream] will not remove URLs publish to CDN.
/// Related APIs: Remove URLs that are re-pushed to the CDN [removePublishCdnUrl].
///
/// @param stream_id Stream ID.
/// @param target_url CDN relay address, supported address format is rtmp, rtmps.
ZEGOEXP_API zego_seq EXP_CALL zego_express_add_publish_cdn_url(const char *stream_id,
                                                               const char *target_url);

/// Deletes the specified CDN URL, which is used for relaying streams from ZEGO RTC server to CDN.
///
/// Available since: 1.1.0
/// Description: When a CDN forwarding address has been added via [addPublishCdnUrl], this function is called when the stream needs to be stopped.
/// When to call: After calling the [createEngine] function to create the engine, When you don't need to continue publish to the CDN.
/// Restrictions: When the [enablePublishDirectToCDN] function is set to true to publish the stream straight to the CDN, then calling this function will have no effect.
/// Caution: This function does not stop publishing audio and video stream to the ZEGO ZEGO RTC server.
/// Related APIs: Add URLs that are re-pushed to the CDN [addPublishCdnUrl].
///
/// @param stream_id Stream ID.
/// @param target_url CDN relay address, supported address format rtmp.
ZEGOEXP_API zego_seq EXP_CALL zego_express_remove_publish_cdn_url(const char *stream_id,
                                                                  const char *target_url);

/// Whether to directly push to CDN (without going through the ZEGO RTC server), for the specified channel.
///
/// Available since: 1.5.0
/// Description: Whether to publish streams directly from the client to CDN without passing through Zego RTC server.
/// Use cases: It is often used in large-scale live broadcast scenes that do not have particularly high requirements for delay.
/// Default value: The default is false, and direct push is not enabled.
/// When to call: After creating the engine [createEngine], before starting to push the stream [startPublishingStream].
/// Caution: The Direct Push CDN feature does not pass through the ZEGO Real-Time Audio and Video Cloud during network transmission, so you cannot use ZEGO's ultra-low latency audio and video services.
/// Related APIs: Dynamic re-push to CDN function [addPublishCdnUrl], [removePublishCdnUrl].
///
/// @param enable Whether to enable direct publish CDN, true: enable direct publish CDN, false: disable direct publish CDN.
/// @param config CDN configuration, if NULL, use Zego's background default configuration.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_publish_direct_to_cdn(
    bool enable, struct zego_cdn_config *config, enum zego_publish_channel channel);

/// Sets up the stream watermark before stream publishing (for the specified channel).
///
/// Available since: 1.1.0
/// Description: Set watermark for publish stream screen.
/// Use cases: It is often used to identify the source of the publish.
/// When to call: After creating the engine through [createEngine] function.
/// Caution: The layout of the watermark cannot exceed the video encoding resolution of the stream. It can be set at any time before or during the publishing stream.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param is_preview_visible the watermark is visible on local preview
/// @param watermark The upper left corner of the watermark layout is the origin of the coordinate system, and the area cannot exceed the size set by the encoding resolution. If it is NULL, the watermark is cancelled.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_publish_watermark(
    bool is_preview_visible, struct zego_watermark *watermark, enum zego_publish_channel channel);

/// Set the Supplemental Enhancement Information type.
///
/// Available since: 1.18.0
/// Description: By default, the SDK wraps the data with ZEGO's self-defined SEI type, which is not specified by the SEI standard. When the developer needs to use a third-party decoder to decode the SEI, the correct SEI will not be decoded and the [setSEIConfig] interface needs to be called to change the type of the SEI sent by the SDK to UserUnregister type.
/// Use cases: This function needs to be executed when the developer uses a third-party decoder to decode the SEI.
/// When to call: After creating the engine [createEngine], before starting to push the stream [startPublishingStream].
/// Restrictions: None.
///
/// @param config SEI configuration. The SEI defined by ZEGO is used by default.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_sei_config(struct zego_sei_config config);

/// Sends Supplemental Enhancement Information.
///
/// Available since: 1.1.0
/// Description: While pushing the stream to transmit the audio and video stream data, the stream media enhancement supplementary information is sent to synchronize some other additional information.
/// Use cases: Generally used in scenes such as synchronizing music lyrics or precise video layout, you can choose to send SEI.
/// When to call: After starting to push the stream [startPublishingStream].
/// Restrictions: Do not exceed 30 times per second, and the SEI data length is limited to 4096 bytes.
/// Caution: Since the SEI information follows the video frame, there may be frame loss due to network problems, so the SEI information may also be lost. In order to solve this situation, it should be sent several times within the restricted frequency.
/// Related APIs: After the pusher sends the SEI, the puller can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
///
/// @param data SEI data.
/// @param data_length SEI data length.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_sei(const unsigned char *data,
                                                      unsigned int data_length,
                                                      enum zego_publish_channel channel);

/// Send the media supplementary enhancement information synchronized with the current video frame during custom video capture.
///
/// Available since: 2.15.0
/// Description: When using custom video capture, push the stream to transmit the video stream data, and send the stream media enhancement supplementary information to synchronize some other additional information, which is synchronized with the current video frame.
/// Use cases: Generally used in scenes that need to be played back in strong synchronization with the video frame, such as video karaoke, video and lyrics are strongly synchronized; or scenes that need to be accurate to the frame level for strategic processing.
/// When to call: To ensure that the SEI is synchronized with the current video frame, it must be called before sending the video frame data.
/// Restrictions: Only used for custom video capture; only supports video-driven SEI sending; you should try to avoid calling this interface to send SEI continuously; to ensure that SEI is synchronized with the current video frame, it must be kept in the same thread as the interface for sending custom video frame data; SEI data length is limited to 4096 bytes.
/// Caution: The sent SEI information follows the video frame. Due to network problems, there may be frame loss. At this time, the SEI will follow the next frame of video data. Therefore, in order to keep the SEI synchronized with the video frame, you should avoid sending SEI continuously; only when using SurfaceTexture on the Android platform , Need to pass the time stamp parameter timeStampNs, otherwise the parameter is invalid.
/// Related APIs: After the pusher sends the SEI, the puller can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
///
/// @param data SEI data.
/// @param data_length SEI data length.
/// @param timestamp_ns video frame reference time, UNIX timestamp, in nanosecond.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_sei_sync_with_custom_video(
    const unsigned char *data, unsigned int data_length, unsigned long long timestamp_ns,
    enum zego_publish_channel channel);

/// Send audio side information.
///
/// Available since: 2.19.0
/// Description: While streaming audio data, send audio side information to synchronize some additional information.
/// Use cases: In the carousel scene, the audio data channel is required to carry accompanying information, such as timestamps to help align the accompaniment, and the need to know who the user is currently singing, whether to amplify the volume, and so on.
/// When to call: After starting to push the stream [startPublishingStream].
/// Restrictions: 1. This function is only valid when publishing stream to the Zego RTC server and it also doesn't work when retweeting the stream from the RTC server to the CDN. 2. The audio side information data length is limited to 1024 bytes.
/// Caution: 1. Audio side information is driven by audio data, so audio data must be pushed (audio side information may be lost when the DTX function is enabled via the interface [setEngineConfig]). 2. Due to network issues, audio side information may be lost, and the SDK is responsible for transmission but does not guarantee reliability.
/// Related APIs: After the pusher sends the side information, the puller can obtain the side information content by monitoring the callback of [onPlayerRecvAudioSideInfo].
///
/// @param data Audio side info data.
/// @param data_length Audio side info data length.
/// @param timestamp_ms timeStampMs, derived from custom audio processing, in milliseconds. If you fill in 0, it is sent along with the frame that is currently ready to be sent.
/// @param channel Publish stream channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_send_audio_side_info(const unsigned char *data, unsigned int data_length,
                                  double timestamp_ms, enum zego_publish_channel channel);

/// Enables or disables hardware encoding.
///
/// Available since: 1.1.0
/// Description: Whether to use the hardware encoding function when publishing the stream, the GPU is used to encode the stream and to reduce the CPU usage.
/// When to call: The setting can take effect before the stream published. If it is set after the stream published, the stream should be stopped first before it takes effect.
/// Caution: Because hard-coded support is not particularly good for a few models, SDK uses software encoding by default. If the developer finds that the device is hot when publishing a high-resolution audio and video stream during testing of some models, you can consider calling this function to enable hard coding.
///
/// @param enable Whether to enable hardware encoding, true: enable hardware encoding, false: disable hardware encoding.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_hardware_encoder(bool enable);

/// Sets the timing of video scaling in the video capture workflow. You can choose to do video scaling right after video capture (the default value) or before encoding.
///
/// Available since: 1.1.0
/// When to call: This function needs to be set before call [startPreview] or [startPublishingStream].
/// Caution: The main effect is Whether the local preview is affected when the acquisition resolution is different from the encoding resolution.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mode The capture scale timing mode.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_capture_pipeline_scale_mode(enum zego_capture_pipeline_scale_mode mode);

/// Whether to enable H.265 encoding to automatically downgrade to H.264 encoding.
///
/// Available since: 2.12.0
/// Description: When using H.265 encoding to push the stream, whether to enable the strategy of automatically degrading H.265 encoding to H.264 encoding under abnormal circumstances.After enabling automatic downgrade, when H.265 encoding is not supported or H.265 encoding fails, the SDK will try to downgrade and use H.264 encoding to push the stream.After turning off automatic downgrade, when H.265 encoding is not supported or H.265 encoding fails, the direct streaming fails.
/// Use cases: In the Co-hosting and Showroom Live Streaming scenarios, use H265 encoding to push the stream to save CDN traffic without degrading the picture quality.
/// Default Value: When this interface is not called, the default is yes, which means that H.265 encoding is turned on and automatically downgraded to H.264 encoding.
/// When to call: After creating the engine, call the [startPublishingStream] function before pushing the stream.
/// Related callbacks: When the H.265 encoding is automatically downgraded to the H.264 encoding strategy, the [onPublisherVideoEncoderChanged] callback will be triggered when the encoding method changes.
/// Caution: When downgrading from H.265 to H.264 encoding occurs during the streaming process, if you are recording local video or cloud recording, multiple recording files will be generated, which needs to be dealt with.
///
/// @param enable Whether to enable H.265 coding automatically fallback to H.264 coding, true: enable, false: disable, and the default value is true
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_h_265_encode_fallback(bool enable);

/// Whether the specified video encoding type is supported.
///
/// Available since: 2.12.0 and above
/// Description: Whether the specified video encoding is supported depends on the following aspects, whether the hardware model supports hard encoding, whether the performance of the hardware model supports soft encoding, and whether the SDK has the encoding module.
/// When to call: After creating the engine.
/// Caution: It is recommended that users call this interface to obtain H.265 encoding support capability before publish stream with H.265 encoding, if not supported, you can use other encodings for publish, such as H.264.On the mobile platform, the SDK only supports H.265 hardware encoding, and it is affected by the model and hardware capabilities. You need to call the [enableHardwareEncoder] function to enable hardware encoding, and then use this function to determine whether H.265 hardware encoding is supported.
///
/// @param codec_id Video codec id. Required: Yes.
/// @return Whether the specified video encoding is supported.Value range: true means support, you can use this encoding format for publish; false means the is not supported, and the encoding format cannot be used for publish.
ZEGOEXP_API bool EXP_CALL
zego_express_is_video_encoder_supported(enum zego_video_codec_id codec_id);

/// The callback triggered when the state of stream publishing changes.
///
/// Available since: 1.1.0
/// Description: After calling the [startPublishingStream] successfully, the notification of the publish stream state change can be obtained through the callback function. You can roughly judge the user's uplink network status based on whether the state parameter is in [PUBLISH_REQUESTING].
/// Caution: The parameter [extendedData] is extended information with state updates. If you use ZEGO's CDN content distribution network, after the stream is successfully published, the keys of the content of this parameter are [flv_url_list], [rtmp_url_list], [hls_url_list], these correspond to the publishing stream URLs of the flv, rtmp, and hls protocols.
/// Related callbacks: After calling the [startPlayingStream] successfully, the notification of the play stream state change can be obtained through the callback function [onPlayerStateUpdate]. You can roughly judge the user's downlink network status based on whether the state parameter is in [PLAY_REQUESTING].
///
/// @param stream_id Stream ID.
/// @param state State of publishing stream.
/// @param error_code The error code corresponding to the status change of the publish stream, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param extended_data Extended information with state updates.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_state_update)(const char *stream_id,
                                               enum zego_publisher_state state,
                                               zego_error error_code, const char *extended_data,
                                               void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_state_update_callback(
    zego_on_publisher_state_update callback_func, void *user_context);

/// Callback for current stream publishing quality.
///
/// Available since: 1.1.0
/// Description: After calling the [startPublishingStream] successfully, the callback will be received every 3 seconds default(If you need to change the time, please contact the instant technical support to configure). Through the callback, the collection frame rate, bit rate, RTT, packet loss rate and other quality data of the published audio and video stream can be obtained, and the health of the publish stream can be monitored in real time.You can monitor the health of the published audio and video streams in real time according to the quality parameters of the callback function, in order to show the uplink network status in real time on the device UI.
/// Caution: If you does not know how to use the parameters of this callback function, you can only pay attention to the [level] field of the [quality] parameter, which is a comprehensive value describing the uplink network calculated by SDK based on the quality parameters.
/// Related callbacks: After calling the [startPlayingStream] successfully, the callback [onPlayerQualityUpdate] will be received every 3 seconds. You can monitor the health of play streams in real time based on quality data such as frame rate, code rate, RTT, packet loss rate, etc.
///
/// @param stream_id Stream ID.
/// @param quality Publishing stream quality, including audio and video framerate, bitrate, RTT, etc.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_quality_update)(const char *stream_id,
                                                 struct zego_publish_stream_quality quality,
                                                 void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_quality_update_callback(
    zego_on_publisher_quality_update callback_func, void *user_context);

/// The callback triggered when the first audio frame is captured.
///
/// Available since: 1.1.0
/// Description: After the [startPublishingStream] function is called successfully, this callback will be called when SDK received the first frame of audio data. Developers can use this callback to determine whether SDK has actually collected audio data. If the callback is not received, the audio capture device is occupied or abnormal.
/// Trigger: In the case of no startPublishingStream audio and video stream or preview [startPreview], the first startPublishingStream audio and video stream or first preview, that is, when the engine of the audio and video module inside SDK starts, it will collect audio data of the local device and receive this callback.
/// Related callbacks: After the [startPublishingStream] function is called successfully, determine if the SDK actually collected video data by the callback function [onPublisherCapturedVideoFirstFrame], determine if the SDK has rendered the first frame of video data collected by calling back [onPublisherRenderVideoFirstFrame].
///
/// @param user_context Context of user.
typedef void (*zego_on_publisher_captured_audio_first_frame)(void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_captured_audio_first_frame_callback(
    zego_on_publisher_captured_audio_first_frame callback_func, void *user_context);

/// The callback triggered when the first video frame is captured.
///
/// Available since: 1.1.0
/// Description: After the [startPublishingStream] function is called successfully, this callback will be called when SDK received the first frame of video data. Developers can use this callback to determine whether SDK has actually collected video data. If the callback is not received, the video capture device is occupied or abnormal.
/// Trigger: In the case of no startPublishingStream video stream or preview, the first startPublishingStream video stream or first preview, that is, when the engine of the audio and video module inside SDK starts, it will collect video data of the local device and receive this callback.
/// Related callbacks: After the [startPublishingStream] function is called successfully, determine if the SDK actually collected audio data by the callback function [onPublisherCapturedAudioFirstFrame], determine if the SDK has rendered the first frame of video data collected by calling back [onPublisherRenderVideoFirstFrame].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_captured_video_first_frame)(enum zego_publish_channel channel,
                                                             void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_captured_video_first_frame_callback(
    zego_on_publisher_captured_video_first_frame callback_func, void *user_context);

/// The callback triggered when the first video frame is rendered.
///
/// Available since: 2.4.0
/// Description: this callback will be called after SDK rendered the first frame of video data captured. This interface is for preview rendering. The first frame callback is only available for external collection and internal preview. If it is not for SDK rendering, there is no such callback.
/// Related callbacks: After the [startPublishingStream] function is called successfully, determine if the SDK actually collected audio data by the callback function [onPublisherCapturedAudioFirstFrame], determine if the SDK actually collected video data by the callback function [onPublisherCapturedVideoFirstFrame].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_render_video_first_frame)(enum zego_publish_channel channel,
                                                           void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_render_video_first_frame_callback(
    zego_on_publisher_render_video_first_frame callback_func, void *user_context);

/// The callback triggered when the video capture resolution changes.
///
/// Available since: 1.1.0
/// Description: When the audio and video stream is not published [startPublishingStream] or previewed [startPreview] for the first time, the publishing stream or preview first time, that is, the engine of the audio and video module inside the SDK is started, the video data of the local device will be collected, and the collection resolution will change at this time.
/// Trigger: After the successful publish [startPublishingStream], the callback will be received if there is a change in the video capture resolution in the process of publishing the stream.
/// Use cases: You can use this callback to remove the cover of the local preview UI and similar operations.You can also dynamically adjust the scale of the preview view based on the resolution of the callback.
/// Caution: What is notified during external collection is the change in encoding resolution, which will be affected by flow control.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param width Video capture resolution width.
/// @param height Video capture resolution height.
/// @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_video_size_changed)(int width, int height,
                                                     enum zego_publish_channel channel,
                                                     void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_video_size_changed_callback(
    zego_on_publisher_video_size_changed callback_func, void *user_context);

/// The callback triggered when the state of relayed streaming to CDN changes.
///
/// Available since: 1.1.0
/// Description: Developers can use this callback to determine whether the audio and video streams of the relay CDN are normal. If they are abnormal, further locate the cause of the abnormal audio and video streams of the relay CDN and make corresponding disaster recovery strategies.
/// Trigger: After the ZEGO RTC server relays the audio and video streams to the CDN, this callback will be received if the CDN relay status changes, such as a stop or a retry.
/// Caution: If you do not understand the cause of the abnormality, you can contact ZEGO technicians to analyze the specific cause of the abnormality.
///
/// @param stream_id Stream ID.
/// @param info_list List of information that the current CDN is relaying.
/// @param info_count List of information count that the current CDN is relaying.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_relay_cdn_state_update)(
    const char *stream_id, const struct zego_stream_relay_cdn_info *info_list,
    unsigned int info_count, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_relay_cdn_state_update_callback(
    zego_on_publisher_relay_cdn_state_update callback_func, void *user_context);

/// The callback triggered when the video encoder changes in publishing stream.
///
/// Available since: 2.12.0
/// Description: After the H.265 automatic downgrade policy is enabled, if H.265 encoding is not supported or the encoding fails during the streaming process with H.265 encoding, the SDK will actively downgrade to the specified encoding (H.264), and this callback will be triggered at this time.
/// When to trigger: In the process of streaming with H.265 encoding, if H.265 encoding is not supported or encoding fails, the SDK will actively downgrade to the specified encoding (H.264), and this callback will be triggered at this time.
/// Caution: When this callback is triggered, if local video recording or cloud recording is in progress, multiple recording files will be generated. Developers need to collect all the recording files for processing after the recording ends. When this callback is triggered, because the streaming code has changed, the developer can evaluate whether to notify the streaming end, so that the streaming end can deal with it accordingly.
///
/// @param from_codec_id Video codec ID before the change.
/// @param to_codec_id Video codec ID after the change.
/// @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_video_encoder_changed)(enum zego_video_codec_id from_codec_id,
                                                        enum zego_video_codec_id to_codec_id,
                                                        enum zego_publish_channel channel,
                                                        void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_video_encoder_changed_callback(
    zego_on_publisher_video_encoder_changed callback_func, void *user_context);

/// The callback triggered when publishing stream.
///
/// Available since: 2.18.0
/// Description: After start publishing stream, this callback will return the current stream address, resource type and protocol-related information.
/// When to trigger: Publish and retry publish events.
/// Caution: None.
///
/// @param event_id Publish stream event ID
/// @param stream_id Stream ID.
/// @param extra_info extra info. it is in JSON format. Included information includes "url" for address, "streamProtocol" for stream protocol, including rtmp, flv, avertp, hls, webrtc, etc. "netProtocol" for network protocol, including tcp, udp, quic, "resourceType" for resource type , including cdn, rtc, l3.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_stream_event)(enum zego_stream_event event_id,
                                               const char *stream_id, const char *extra_info,
                                               void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_stream_event_callback(
    zego_on_publisher_stream_event callback_func, void *user_context);

/// Callback for setting stream extra information.
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param seq Message sequence.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_update_stream_extra_info_result)(zego_error error_code,
                                                                  zego_seq seq, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_update_stream_extra_info_result_callback(
    zego_on_publisher_update_stream_extra_info_result callback_func, void *user_context);

/// Callback for add/remove CDN URL.
///
/// @param stream_id Stream ID.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param seq Message sequence.
/// @param user_context Context of user.
typedef void (*zego_on_publisher_update_cdn_url_result)(const char *stream_id,
                                                        zego_error error_code, zego_seq seq,
                                                        void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_update_cdn_url_result_callback(
    zego_on_publisher_update_cdn_url_result callback_func, void *user_context);

/// Results of take publish stream snapshot.
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param channel Publish stream channel
/// @param image Snapshot image (Windows: HBITMAP; macOS/iOS: CGImageRef; Linux: QImage; Android: Bitmap)
/// @param user_context Context of user.
typedef void (*zego_on_publisher_take_snapshot_result)(zego_error error_code,
                                                       enum zego_publish_channel channel,
                                                       void *image, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_publisher_take_snapshot_result_callback(
    zego_on_publisher_take_snapshot_result callback_func, void *user_context);

ZEGO_END_DECLS

#endif
