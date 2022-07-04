
#ifndef __ZEGO_EXPRESS_CUSTOM_VIDEO_IO_H__
#define __ZEGO_EXPRESS_CUSTOM_VIDEO_IO_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Enables or disables custom video rendering.
///
/// Available since: 1.9.0
/// Description: When enable is `true`,video custom rendering is enabled; if the value of `false`, video custom rendering is disabled.
/// Use case: Use beauty features or apps that use a cross-platform interface framework (for example, Qt requires a complex hierarchical interface to achieve high-experience interaction) or game engines (for example, Unity3D, Cocos2d-x), etc.
/// Default value: Custom video rendering is turned off by default when this function is not called.
/// When to call: Must be set after [createEngine] before the engine starts, before calling [startPreview], [startPublishingStream],[startPlayingStream], [createRealTimeSequentialDataManager].The configuration can only be modified after the engine is stopped, that is, after [logoutRoom] is called.
/// Caution: Custom video rendering can be used in conjunction with custom video capture, but when both are enabled, the local capture frame callback for custom video rendering will no longer be triggered, and the developer should directly capture the captured video frame from the custom video capture source.
/// Related callbacks: When developers to open a custom rendering, by calling [setCustomVideoRenderHandler] can be set up to receive local and remote video data to be used for custom rendering. [onCapturedVideoFrameRawData] local bare preview video frame data correction, distal pull flow [onRemoteVideoFrameRawData] naked video frame data correction.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable enable or disable
/// @param config custom video render config
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_video_render(
    bool enable, struct zego_custom_video_render_config *config);

/// Enables or disables custom video capture (for the specified channel).
///
/// Available since: 1.9.0
/// Description: If the value of enable is true, the video collection function is enabled. If the value of enable is false, the video collection function is disabled.
/// Use case: The App developed by the developer uses the beauty SDK of a third-party beauty manufacturer to broadcast non-camera collected data.
/// Default value: When this function is not called, custom video collection is disabled by default.
/// When to call: After [createEngine], call [startPreview], [startPublishingStream], [createRealTimeSequentialDataManager], and call [logoutRoom] to modify the configuration.
/// Caution: Custom video rendering can be used in conjunction with custom video capture, but when both are enabled, the local capture frame callback for custom video rendering will no longer be triggered, and the developer should directly capture the captured video frame from the custom video capture source.
/// Related callbacks: When developers to open a custom collection, by calling [setCustomVideoCaptureHandler] can be set up to receive a custom collection start-stop event notification.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable enable or disable
/// @param config custom video capture config
/// @param channel publish channel
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_video_capture(
    bool enable, struct zego_custom_video_capture_config *config,
    enum zego_publish_channel channel);

/// Sends the video frames (Raw Data) produced by custom video capture to the SDK (for the specified channel).
///
/// Available since: 1.9.0
/// Description: Sends customized raw video frame data to the SDK.
/// When to call: After receiving the [onStart] notification, the developer starts the call after the collection logic starts and ends the call after the [onStop] notification.
/// Caution: This interface must be called with [enableCustomVideoCapture] passing the parameter type RAW_DATA.
/// Related APIs: [enableCustomVideoCapture], [setCustomVideoCaptureHandler].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param data video frame data
/// @param data_length video frame data length
/// @param params video frame param
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_raw_data(
    const unsigned char *data, unsigned int data_length, const struct zego_video_frame_param params,
    unsigned long long reference_time_millisecond, unsigned int reference_time_scale,
    enum zego_publish_channel channel);

/// Sends the video frames (Texture Data) produced by custom video capture to the SDK (for the specified channel).
///
/// Available since: 1.9.0
/// Description: Send custom captured video frame type GL_TEXTURE_2D data to the SDK.
/// When to call: After receiving the [onStart] notification, the developer starts the call after the collection logic starts and ends the call after the [onStop] notification.
/// Caution: Calling this interface must be [enableCustomVideoCapture] with an argument of type GL_TEXTURE_2D.
/// Related APIs: [enableCustomVideoCapture], [setCustomVideoCaptureHandler].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param texture_id texture ID
/// @param width Video frame width
/// @param height Video frame height
/// @param reference_time_millisecond Timestamp of this video frame
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_texture_data(
    int texture_id, int width, int height, double reference_time_millisecond,
    enum zego_publish_channel channel);

/// Gets the SurfaceTexture instance (for the specified channel).
///
/// Available since: 1.10.0
/// Description: Get the SurfaceTexture object.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publishing stream channel
/// @return SurfaceTexture instance
ZEGOEXP_API void *EXP_CALL
zego_express_get_custom_video_capture_surface_texture(enum zego_publish_channel channel);

/// Sends the video frames (CVPixelBuffer) produced by custom video capture to the SDK (for the specified channel).
///
/// Available since: 1.9.0
/// Description: Send custom captured video frame type CVPixelBuffer data to the SDK.
/// When to call: After receiving the [onStart] notification, the developer starts the call after the collection logic starts and ends the call after the [onStop] notification.
/// Caution: Calling this interface must be [enableCustomVideoCapture] with an argument of type ZegoVideoBufferTypeCVPixelBuffer.
/// Related APIs: [enableCustomVideoCapture], [setCustomVideoCaptureHandler].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param buffer Video frame data to send to the SDK
/// @param timestamp Timestamp of this video frame
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_pixel_buffer(
    void *buffer, double timestamp, enum zego_publish_channel channel);

/// Sends the video frames (Encoded Data) produced by custom video capture to the SDK (for the specified channel).
///
/// Available since: 1.9.0
/// Description: Send custom captured video frame type CVPixelBuffer data to the SDK.
/// When to call: After receiving the [onStart] notification, the developer starts the call after the collection logic starts and ends the call after the [onStop] notification.
/// Caution: It is recommended to make a GOP every 2s, and each I frame must carry SPS and PPS and be placed at the top.  Only I and P frames are accepted, B frames are NOT accepted. Calling this interface must be [enableCustomVideoCapture] with an argument of type ZegoVideoBufferTypeEncodedData.
/// Related APIs: [enableCustomVideoCapture], [setCustomVideoCaptureHandler].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param data video frame encoded data
/// @param data_length video frame data length
/// @param params video frame param
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_encoded_data(
    const unsigned char *data, unsigned int data_length,
    const struct zego_video_encoded_frame_param params, double reference_time_millisecond,
    enum zego_publish_channel channel);

/// Sets the video fill mode of custom video capture (for the specified channel).
///
/// Available since: 1.10.0
/// Use cases: If the customized collection resolution and SDK coding resolution are inconsistent, THE SDK will process the video frame according to the fill mode and adjust it to the coding resolution.
/// Description: When the custom video collection function is enabled, you can use this interface to set the video zooming and filling mode.
/// When to call: Before [sendCustomVideoCaptureRawData], [sendCustomVideoCaptureTextureData], [sendCustomVideoCapturePixelBuffer], [sendCustomVideoCaptureEncodedData].
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mode View mode
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_fill_mode(
    enum zego_view_mode mode, enum zego_publish_channel channel);

/// Sets the video flip mode of custom video capture (for the specified channel). This function takes effect only if the custom video buffer type is Texture2D.
///
/// Available since: 1.10.0
/// Description: When the custom video collection function is enabled, you can use this interface to set the video flipping mode.
/// When to call: Before [sendCustomVideoCaptureRawData], [sendCustomVideoCaptureTextureData], [sendCustomVideoCapturePixelBuffer], [sendCustomVideoCaptureEncodedData].
/// Caution: This function takes effect only if the custom collection type is Texture2D.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mode Flip mode
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_flip_mode(
    enum zego_video_flip_mode mode, enum zego_publish_channel channel);

/// Sets the video rotation of custom video capture (for the specified channel).
///
/// Available since: 2.14.0.
/// Description: You can set the video rotation of custom video capture (for the specified channel) through this function.
/// When to call: After the callback [onStart] is received.
/// Restrictions: This function takes effect when the custom acquisition type is CVPixelBuffer or Texture2D.
/// Caution: When both the settings transform matrix and the setting rotation interface are called. the transformation matrix is executed before the rotation is set.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param rotation Clockwise angle.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_custom_video_capture_rotation(int rotation, enum zego_publish_channel channel);

/// Sets device state of custom video capture (for the specified channel).
///
/// Available since: 2.15.0.
/// Description: User can set the video device state of custom video capture (for the specified channel) through this function.
/// When to call: After the callback [onStart] is received.
/// Restrictions: None.
/// Related Callbacks: The remote user that play stream of local user publishing stream can receive state update notification by monitoring [onRemoteCameraStateUpdate] callbacks.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param is_enable Whether the device is enable.
/// @param state The device state.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_device_state(
    bool is_enable, enum zego_remote_device_state state, enum zego_publish_channel channel);

/// Sets the video transform matrix of custom video capture (for the specified channel).
///
/// Available since: 2.14.0.
/// Description: You can set the video transform matrix of custom video capture (for the specified channel) through this function. The transformation matrix can include rotation, flipping, and scaling. It is recommended for developers with some OpenGL development experience.
/// When to call: After the callback [onStart] is received.
/// Restrictions: This function takes effect only when the custom acquisition type is Texture2D.
/// References: Please refer to the documentation https://docs.zegocloud.com/article/4054 for details.
/// Caution: When both the settings transform matrix and the setting rotation interface are called. the transformation matrix is executed before the rotation is set.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param matrix 4x4 transformation matrix.
/// @param channel Publishing stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_transform_matrix(
    float matrix[16], enum zego_publish_channel channel);

/// Set the region of interest (ROI) for encoder of custom video capture (for the specified channel).
///
/// Available since: 2.16.0.
/// Description: You can set the video encoder's region of interest rectangle areas of custom video capture (for the specified channel) through this function.
/// When to call: After the callback [onStart] is received.
/// Restrictions: Currently, only certain video encoders support this function, please contact ZEGO technical support before using it.
/// Caution: This function is currently an experimental feature, please contact ZEGO technical support before using it.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param rect_list ROI rectangle area list, currently supports up to 6 areas.
/// @param rect_count Length of the rectangle list (count of rectangle).
/// @param channel Publish channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_region_of_interest(
    struct zego_roi_rect *rect_list, unsigned int rect_count, enum zego_publish_channel channel);

/// Customize the notification of the start of video capture.
///
/// Available since: 1.1.0
/// Description: The SDK informs that the video frame is about to be collected, and the video frame data sent to the SDK is valid after receiving the callback.
/// Use cases: Live data collected by non-cameras. For example, local video file playback, screen sharing, game live broadcast, etc.
/// When to Trigger: After calling [startPreview] or [startPublishingStream] successfully.
/// Caution: The video frame data sent to the SDK after receiving the callback is valid.
/// Related callbacks: Customize the end of capture notification [onCaptureStop].
/// Related APIs: Call [setCustomVideoCaptureHandler] to set custom video capture callback.
///
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_capture_start)(enum zego_publish_channel channel,
                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_capture_start_callback(
    zego_on_custom_video_capture_start callback_func, void *user_context);

/// Customize the notification of the end of the collection.
///
/// Available since: 1.1.0
/// Description: The SDK informs that it is about to end the video frame capture.
/// Use cases: Live data collected by non-cameras. For example, local video file playback, screen sharing, game live broadcast, etc.
/// When to Trigger: After calling [stopPreview] or [stopPublishingStream] successfully.
/// Caution: If you call [startPreview] and [startPublishingStream] to start preview and push stream at the same time after you start custom capture, you should call [stopPreview] and [stopPublishingStream] to stop the preview and push stream before triggering the callback.
/// Related callbacks: Custom video capture start notification [onCaptureStart].
/// Related APIs: Call [setCustomVideoCaptureHandler] to set custom video capture callback.
///
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_capture_stop)(enum zego_publish_channel channel,
                                                  void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_capture_stop_callback(
    zego_on_custom_video_capture_stop callback_func, void *user_context);

/// When network changes are detected during custom video capture, the developer is notified that traffic control is required, and the encoding configuration is adjusted according to the recommended parameters of the SDK.
///
/// Available since: 1.14.0
/// Description: When using custom video capture, the SDK detects a network change, informs the developer that it needs to do flow control, and adjust the encoding configuration according to the recommended parameters of the SDK. In the case of custom collection and transmission of encoded data, the SDK cannot know the external encoding configuration, so the flow control operation needs to be completed by the developer. The SDK will notify the developer of the recommended value of the video configuration according to the current network situation, and the developer needs to modify the encoder configuration by himself to ensure the smoothness of video transmission.
/// Use cases: Live data collected by non-cameras. For example, local video file playback, screen sharing, game live broadcast, etc.
/// When to Trigger: When network status changes during the process of custom video capture and flow control is required.
/// Caution: Please do not perform time-consuming operations in this callback, such as reading and writing large files. If you need to perform time-consuming operations, please switch threads.
/// Related APIs: Call [setCustomVideoCaptureHandler] to set custom video capture callback.
///
/// @param traffic_control_info traffic control info.
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_capture_encoded_data_traffic_control)(
    struct zego_traffic_control_info traffic_control_info, enum zego_publish_channel channel,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_capture_encoded_data_traffic_control_callback(
    zego_on_custom_video_capture_encoded_data_traffic_control callback_func, void *user_context);

/// When custom video rendering is enabled, the original video frame data collected by the local preview is called back.
///
/// Available since: 1.1.0
/// Description: When using custom video rendering, the SDK callbacks the original video frame data collected by the local preview, which is rendered by the developer.
/// Use cases: Use a cross-platform interface framework or game engine; need to obtain the video frame data collected or streamed by the SDK for special processing.
/// When to Trigger: When the local preview is turned on, when the SDK collects the local preview video frame data.
/// Related APIs: Call [setCustomVideoRenderHandler] to set custom video rendering callback.
///
/// @param data Raw video frame data (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2]).
/// @param data_length Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2]).
/// @param param Video frame parameters.
/// @param flip_mode video flip mode.
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_render_captured_frame_data)(
    unsigned char **data, unsigned int *data_length, const struct zego_video_frame_param param,
    enum zego_video_flip_mode flip_mode, enum zego_publish_channel channel, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_captured_frame_data_callback(
    zego_on_custom_video_render_captured_frame_data callback_func, void *user_context);

/// When custom video rendering is enabled, the remote end pulls the original video frame data to call back, and distinguishes different streams by streamID.
///
/// Available since: 1.1.0
/// Description: When custom video rendering is enabled, the SDK calls back the remote end to pull the original video frame data, distinguishes different streams by streamID, and renders them by the developer.
/// Use cases: Use a cross-platform interface framework or game engine; need to obtain the video frame data collected or streamed by the SDK for special processing.
/// When to Trigger: After starting to stream, when the SDK receives the video frame data of the remote stream.
/// Related APIs: Call [setCustomVideoRenderHandler] to set custom video rendering callback.
///
/// @param stream_id Stream ID.
/// @param data Raw video frame data (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2]).
/// @param data_length Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2]).
/// @param param Video frame parameters.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_render_remote_frame_data)(
    const char *stream_id, unsigned char **data, unsigned int *data_length,
    const struct zego_video_frame_param param, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_remote_frame_data_callback(
    zego_on_custom_video_render_remote_frame_data callback_func, void *user_context);

/// The callback for obtianing the video frames (Encoded Data) of the remote stream. Different streams can be identified by streamID.
///
/// Available since: 1.1.0
/// Description: When custom video rendering is enabled, the remote end pulls the video frame encoded data callback, distinguishes different streams by streamID, and renders by the developer.
/// Use cases: Scenes where a cross-platform interface framework or game engine is used, or the video frame data collected or streamed by the SDK needs to be obtained for special processing.
/// When to Trigger: After starting to stream, the SDK receives the video frame data of the remote stream.
/// Related APIs: Call [setCustomVideoRenderHandler] to set custom video rendering callback.
///
/// @param data Encoded data of video frames.
/// @param data_length Data length.
/// @param param Video frame parameters.
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param stream_id Stream ID.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_render_remote_frame_encoded_data)(
    const unsigned char *data, unsigned int data_length,
    const struct zego_video_encoded_frame_param param,
    unsigned long long reference_time_millisecond, const char *stream_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_remote_frame_encoded_data_callback(
    zego_on_custom_video_render_remote_frame_encoded_data callback_func, void *user_context);

/// Enables or disables custom video processing.
///
/// Available since: 2.2.0 (Android/iOS/macOS native), 2.4.0 (Windows/macOS C++).
/// Description: When the developer opens custom pre-processing, by calling [setCustomVideoProcessHandler] you can set the custom video pre-processing callback.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// Default value: Off by default
/// When to call: Must be set before calling [startPreview], [startPublishingStream], [createRealTimeSequentialDataManager]. If you need to modify the configuration, please call [logoutRoom] to log out of the room first, otherwise it will not take effect.
/// Restrictions: None.
/// Related APIs: Call the [setCustomVideoProcessHandler] function to set the callback before custom video processing.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable enable or disable. Required: Yes.
/// @param config custom video processing configuration. Required: Yes.Caution: If NULL is passed, the platform default value is used.
/// @param channel Publishing stream channel.Required: No.Default value: Main publish channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_video_processing(
    bool enable, struct zego_custom_video_process_config *config,
    enum zego_publish_channel channel);

/// Send the original video data after the pre-processing of the custom video to the SDK, and support other channels to push the stream.
///
/// Available since: 2.4.0
/// Description: When the developer opens the custom pre-processing, by calling [setCustomVideoProcessHandler], you can set the custom video pre-processing callback to obtain the original video data.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to call: Must be called in the [onCapturedUnprocessedCVPixelbuffer] callback.
/// Restrictions: None.
/// Platform differences: Only valid on Windows platform.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param data Raw video data. RGB format data storage location is data[0], YUV format data storage location is Y component：data[0], U component：data[1], V component：data[2].
/// @param data_length Raw video data length. RGB format data length storage location is dataLength[0], YUV format data storage location respectively Y component length：dataLength[0], U component length：dataLength[1], V component length：dataLength[2].
/// @param params video frame param.
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel.Required: No.Default value: Main publish channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_processed_raw_data(
    const unsigned char **data, unsigned int *data_length, struct zego_video_frame_param params,
    unsigned long long reference_time_millisecond, enum zego_publish_channel channel);

/// Send the [CVPixelBuffer] type video data after the custom video processing to the SDK (for the specified channel).
///
/// Available since: 2.2.0 (iOS native), 2.4.0 (macOS C++).
/// Description: When the custom video pre-processing is turned on, the [CVPixelBuffer] format video data after the custom video pre-processing is sent to the SDK, and other channels are supported.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to call: Must be called in the [onCapturedUnprocessedCVPixelbuffer] callback.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeCVPixelBuffer].
/// Platform differences: Only valid on Windows platform.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param buffer CVPixelBuffer type video frame data to be sent to the SDK.
/// @param timestamp Timestamp of this video frame.
/// @param channel Publishing stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_processed_cv_pixel_buffer(
    void *buffer, unsigned long long timestamp, enum zego_publish_channel channel);

/// Send the [Texture] type video data after the pre-processing of the custom video to the SDK (for the specified channel).
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, the [Texture] format video data after the custom video pre-processing is sent to the SDK, and other channels are supported.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to call: Must be called in the [onCapturedUnprocessedTextureData] callback.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeGLTexture2D].
/// Platform differences: Only valid on Android platform.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param texture_id texture ID.
/// @param width Texture width.
/// @param height Texture height.
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_processed_texture_data(
    int texture_id, int width, int height, unsigned long long reference_time_millisecond,
    enum zego_publish_channel channel);

/// The SDK informs the developer that it is about to start custom video processing.
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, the SDK informs the developer that the video pre-processing is about to start, and it is recommended to initialize other resources(E.g. Beauty SDK) in this callback.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to Trigger: Open custom video pre-processing, after calling [startPreview] or [startPublishingStream] successfully.
/// Related callbacks: Custom video pre-processing end notification [onProcessStop].
/// Related APIs: Call [setCustomVideoProcessHandler] function to set custom video pre-processing callback.
///
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_process_start)(enum zego_publish_channel channel,
                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_process_start_callback(
    zego_on_custom_video_process_start callback_func, void *user_context);

/// The SDK informs the developer to stop custom video processing.
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, the SDK informs the developer that the video pre-processing is about to end, and it is recommended to destroy other resources(E.g. Beauty SDK) in this callback.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to Trigger: If you call [startPreview] to start the preview and [startPublishingStream] to start the push stream at the same time after you start the custom capture, you should call [stopPreview] to stop the preview and [stopPublishingStream] to stop the push stream before the callback will be triggered.
/// Related callbacks: Custom video pre-processing start notification [onProcessStart].
/// Related APIs: Call [setCustomVideoProcessHandler] function to set custom video pre-processing callback.
///
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_process_stop)(enum zego_publish_channel channel,
                                                  void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_process_stop_callback(
    zego_on_custom_video_process_stop callback_func, void *user_context);

/// Get SurfaceTexture for output data (for the specified channel).
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, after the developer obtains the raw data of the SurfaceTexture type, this interface is called to obtain the SurfaceTexture used to output the video data, as the producer of the output data. After the developer completes the video pre-processing, send the processed video data to the SDK through this SurfaceTexture.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to call: It is recommended to call in the [onGetSurfaceTexture] callback function.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeSurfaceTexture].
/// Platform differences: It only takes effect on the Android platform.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param width Specify the width of the output video data.
/// @param height Specify the height of the output video data.
/// @param channel Publishing stream channel.
/// @return SurfaceTexture instance.
ZEGOEXP_API void *EXP_CALL zego_express_get_custom_video_process_output_surface_texture(
    int width, int height, enum zego_publish_channel channel);

/// Call back when the original video data is obtained.
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, after calling [setCustomVideoProcessHandler] to set the callback, the SDK receives the original video data and calls back to the developer. After the developer has processed the original image, he must call [sendCustomVideoProcessedRawData] to send the processed data back to the SDK, otherwise it will cause frame loss.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to Trigger: When the custom video pre-processing is enabled, the SDK collects the original video data.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeRawData].
/// Platform differences: It only takes effect on the Windows platform.
///
/// @param data Raw video data. RGB format data storage location is data[0], YUV format data storage location is Y component：data[0], U component：data[1], V component：data[2].
/// @param data_length Raw video data length. RGB format data length storage location is dataLength[0], YUV format data storage location respectively Y component length：dataLength[0], U component length：dataLength[1], V component length：dataLength[2].
/// @param param Video frame parameters.
/// @param reference_time_millisecond Video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_process_captured_unprocessed_raw_data)(
    const unsigned char **data, unsigned int *data_length,
    const struct zego_video_frame_param param, unsigned long long reference_time_millisecond,
    enum zego_publish_channel channel, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_process_captured_unprocessed_raw_data_callback(
    zego_on_custom_video_process_captured_unprocessed_raw_data callback_func, void *user_context);

/// Call back when the original video data of type [CVPixelBuffer] is obtained.
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, after calling [setCustomVideoProcessHandler] to set the callback, the SDK receives the original video data and calls back to the developer. After the developer has processed the original image, he must call [sendCustomVideoProcessedCVPixelbuffer] to send the processed data back to the SDK, otherwise it will cause frame loss.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to Trigger: When the custom video pre-processing is enabled, the SDK collects the original video data.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeCVPixelBuffer].
/// Platform differences: It only takes effect on the iOS/macOS platform.
///
/// @param buffer CVPixelBufferRef type data.
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_process_captured_unprocessed_cvpixelbuffer)(
    void *buffer, unsigned long long reference_time_millisecond, enum zego_publish_channel channel,
    void *user_context);

ZEGOEXP_API void EXP_CALL
zego_register_custom_video_process_captured_unprocessed_cvpixelbuffer_callback(
    zego_on_custom_video_process_captured_unprocessed_cvpixelbuffer callback_func,
    void *user_context);

/// Call back when the original video data of type [Texture] is obtained.
///
/// Available since: 2.2.0
/// Description: When the custom video pre-processing is turned on, after calling [setCustomVideoProcessHandler] to set the callback, the SDK receives the original video data and calls back to the developer. After the developer has processed the original image, he must call [sendCustomVideoProcessedTextureData] to send the processed data back to the SDK, otherwise it will cause frame loss.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// When to Trigger: When the custom video pre-processing is enabled, the SDK collects the original video data.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeGLTexture2D].
/// Platform differences: It only takes effect on the Android platform.
///
/// @param texture_id Texture ID.
/// @param width Texture width.
/// @param height Texture height.
/// @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
typedef void (*zego_on_custom_video_process_captured_unprocessed_texture_data)(
    int texture_id, int width, int height, unsigned long long reference_time_millisecond,
    enum zego_publish_channel channel, void *user_context);

ZEGOEXP_API void EXP_CALL
zego_register_custom_video_process_captured_unprocessed_texture_data_callback(
    zego_on_custom_video_process_captured_unprocessed_texture_data callback_func,
    void *user_context);

/// When the developer chooses the SurfaceTexture video pre-processing type, the SurfaceTexture used to input the original video data is obtained through this interface and passed to the SDK.
///
/// Available since: 2.2.0
/// Description: To enable custom video pre-processing, developers need to create a SurfaceTexture object and listen to its member method [setOnFrameAvailableListener], and then return the corresponding SurfaceTexture. When the SDK raw video data input is completed, the developer will receive [onFrameAvailable]. After the developer passes the SurfaceTexture(input) object to the SDK, he can call [getCustomVideoProcessOutputSurfaceTexture] to get the SurfaceTexture used by the SDK to encode and push the stream, and then the developer can pass the video processed data into this SurfaceTexture(output) object.
/// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
/// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeSurfaceTexture].
/// Platform differences: It only takes effect on the Android platform.
///
/// @param width The capture width of the original video.
/// @param height The capture height of the original video.
/// @param channel Publishing stream channel.
/// @param user_context Context of user.
/// @return SurfaceTexture instance.
typedef void *(*zego_on_custom_video_process_get_input_surface_texture)(
    int width, int height, enum zego_publish_channel channel, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_process_get_input_surface_texture_callback(
    zego_on_custom_video_process_get_input_surface_texture callback_func, void *user_context);

ZEGO_END_DECLS

#endif
