
#ifndef __ZEGO_EXPRESS_CUSTOM_VIDEO_IO_H__
#define __ZEGO_EXPRESS_CUSTOM_VIDEO_IO_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/**
 * Enables or disables custom video rendering.
 *
 * It must be set before the engine starts, that is, before calling [startPreview], [startPublishingStream], [startPlayingStream]; and the configuration can be modified after the engine is stopped， that is after calling [logoutRoom].
 * When the developer starts custom rendering, by calling [setCustomVideoRenderHandler], you can set to receive local and remote video frame data for custom rendering
 *
 * @param enable enable or disable
 * @param config custom video render config
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_video_render(bool enable, struct zego_custom_video_render_config* config);


/**
 * Enables or disables custom video capture (for the specified channel).
 *
 * It must be set before the engine starts, that is, before calling [startPreview], [startPublishingStream]; and the configuration can be modified after the engine is stopped, that is, after calling [logoutRoom].
 * When the developer starts the custom capture, it can be set to receive notification of the start and stop of the custom capture by calling [setCustomVideoCaptureHandler].
 *
 * @param enable enable or disable
 * @param config custom video capture config
 * @param channel publish channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_video_capture(bool enable, struct zego_custom_video_capture_config* config, enum zego_publish_channel channel);


/**
 * Sends the video frames (Raw Data) produced by custom video capture to the SDK (for the specified channel).
 *
 * This function need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
 *
 * @param data video frame data
 * @param data_length video frame data length
 * @param params video frame param
 * @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_raw_data(const unsigned char* data, unsigned int data_length, const struct zego_video_frame_param params, unsigned long long reference_time_millisecond, unsigned int reference_time_scale, enum zego_publish_channel channel);


/**
 * Sends the video frames (Texture Data) produced by custom video capture to the SDK (for the specified channel).
 *
 * This function need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
 *
 * @param texture_id texture ID
 * @param width Video frame width
 * @param height Video frame height
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_texture_data(int texture_id, int width, int height, double reference_time_millisecond, enum zego_publish_channel channel);


/**
 * Gets the SurfaceTexture instance (for the specified channel).
 *
 * @param channel Publishing stream channel
 * @return SurfaceTexture instance
 */
ZEGOEXP_API void* EXP_CALL zego_express_get_custom_video_capture_surface_texture(enum zego_publish_channel channel);


/**
 * Sends the video frames (CVPixelBuffer) produced by custom video capture to the SDK (for the specified channel).
 *
 * This function need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
 *
 * @param buffer Video frame data to send to the SDK
 * @param timestamp Timestamp of this video frame
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_pixel_buffer(void* buffer, double timestamp, enum zego_publish_channel channel);


/**
 * Sends the video frames (Encoded Data) produced by custom video capture to the SDK (for the specified channel).
 *
 * This function need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
 *
 * @param data video frame encoded data
 * @param data_length video frame data length
 * @param params video frame param
 * @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_video_capture_encoded_data(const unsigned char* data, unsigned int data_length, const struct zego_video_encoded_frame_param params, double reference_time_millisecond, enum zego_publish_channel channel);


/**
 * Sets the video fill mode of custom video capture (for the specified channel).
 *
 * @param mode View mode
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_fill_mode(enum zego_view_mode mode, enum zego_publish_channel channel);


/**
 * Sets the video flip mode of custom video capture (for the specified channel). This function takes effect only if the custom video buffer type is Texture2D.
 *
 * @param mode Flip mode
 * @param channel Publishing stream channel
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_set_custom_video_capture_flip_mode(enum zego_video_flip_mode mode, enum zego_publish_channel channel);


/**
 * The callback triggered when the SDK is ready to receive captured video data. Only those video data that are sent to the SDK after this callback is received are valid.
 *
 * @param channel Publishing stream channel
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_capture_start)(enum zego_publish_channel channel, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_capture_start_callback(zego_on_custom_video_capture_start callback_func, void * user_context);


/**
 * The callback triggered when SDK stops receiving captured video data.
 *
 * @param channel Publishing stream channel
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_capture_stop)(enum zego_publish_channel channel, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_capture_stop_callback(zego_on_custom_video_capture_stop callback_func, void * user_context);


/**
 * SDK detects network changes and informs developers that it needs to do traffic control
 * In the case of custom video capture by sending encoded data, the SDK cannot know the external encoding configuration, so the traffic control operation needs to be completed by the developer.
 * The SDK will notify the developer of the recommended value of the video configuration according to the current network situation, and the developer needs to modify the encoder configuration by himself to ensure the smoothness of video transmission
 * Please do not perform time-consuming operations in this callback. If you need to perform time-consuming operations, please switch threads
 *
 * @param traffic_control_info traffic control info
 * @param channel Publishing stream channel
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_capture_encoded_data_traffic_control)(struct zego_traffic_control_info traffic_control_info, enum zego_publish_channel channel, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_capture_encoded_data_traffic_control_callback(zego_on_custom_video_capture_encoded_data_traffic_control callback_func, void * user_context);


/**
 * The callback for obtaining the locally captured video frames (Raw Data).
 *
 * @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
 * @param data_length Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
 * @param param Video frame parameters
 * @param flip_mode video flip mode
 * @param channel Publishing stream channel
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_render_captured_frame_data)(unsigned char** data, unsigned int* data_length, const struct zego_video_frame_param param, enum zego_video_flip_mode flip_mode, enum zego_publish_channel channel, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_captured_frame_data_callback(zego_on_custom_video_render_captured_frame_data callback_func, void * user_context);


/**
 * The callback for obtaining the video frames (Raw Data) of the remote stream. Different streams can be identified by streamID.
 *
 * @param stream_id Stream ID
 * @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
 * @param data_length Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
 * @param param Video frame parameters
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_render_remote_frame_data)(const char * stream_id, unsigned char** data, unsigned int* data_length, const struct zego_video_frame_param param, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_remote_frame_data_callback(zego_on_custom_video_render_remote_frame_data callback_func, void * user_context);


/**
 * The callback for obtaining the locally captured video frames (Encoded Data).
 *
 * @param data Encoded data of video frames
 * @param data_length Data length
 * @param param Video frame parameters
 * @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
 * @param channel Publishing stream channel
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_render_captured_frame_encoded_data)(const unsigned char* data, unsigned int data_length, const struct zego_video_encoded_frame_param param, unsigned long long reference_time_millisecond, enum zego_publish_channel channel, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_captured_frame_encoded_data_callback(zego_on_custom_video_render_captured_frame_encoded_data callback_func, void * user_context);


/**
 * The callback for obtianing the video frames (Encoded Data) of the remote stream. Different streams can be identified by streamID.
 *
 * @param data Encoded data of video frames
 * @param data_length Data length
 * @param param Video frame parameters
 * @param reference_time_millisecond video frame reference time, UNIX timestamp, in milliseconds.
 * @param stream_id Stream ID
 * @param user_context Context of user.
 */
typedef void(*zego_on_custom_video_render_remote_frame_encoded_data)(const unsigned char* data, unsigned int data_length, const struct zego_video_encoded_frame_param param, unsigned long long reference_time_millisecond, const char * stream_id, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_custom_video_render_remote_frame_encoded_data_callback(zego_on_custom_video_render_remote_frame_encoded_data callback_func, void * user_context);



ZEGO_END_DECLS

#endif
