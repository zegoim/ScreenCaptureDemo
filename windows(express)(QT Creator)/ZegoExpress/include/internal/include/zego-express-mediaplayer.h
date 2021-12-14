
#ifndef __ZEGO_EXPRESS_MEDIAPLAYER_H__
#define __ZEGO_EXPRESS_MEDIAPLAYER_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/**
 * Creates a media player instance.
 *
 * Currently, a maximum of 4 instances can be created, after which it will return NULL. The more instances of a media player, the greater the performance overhead on the device.
 *
 * @return Media player instance, NULL will be returned when the maximum number is exceeded.
 */
ZEGOEXP_API enum zego_media_player_instance_index EXP_CALL zego_express_create_media_player();


/**
 * Destroys a media player instance.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_destroy_media_player(enum zego_media_player_instance_index instance_index);


/**
 * Start playing.
 *
 * You need to load resources before playing
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_start(enum zego_media_player_instance_index instance_index);


/**
 * Stop playing.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_stop(enum zego_media_player_instance_index instance_index);


/**
 * Pause playing.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_pause(enum zego_media_player_instance_index instance_index);


/**
 * Resume playing.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_resume(enum zego_media_player_instance_index instance_index);


/**
 * Load media resource.
 *
 * Yon can pass the absolute path of the local resource or the URL of the network resource
 *
 * @param path the absolute path of the local resource or the URL of the network resource
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_load_resource(const char * path, enum zego_media_player_instance_index instance_index);


/**
 * Get the current playback status.
 */
ZEGOEXP_API enum zego_media_player_state EXP_CALL zego_express_media_player_get_current_state(enum zego_media_player_instance_index instance_index);


/**
 * Set the specified playback progress.
 *
 * Unit is millisecond
 *
 * @param millisecond Point in time of specified playback progress
 */
ZEGOEXP_API zego_seq EXP_CALL zego_express_media_player_seek_to(unsigned long long millisecond, enum zego_media_player_instance_index instance_index);


/**
 * Set mediaplayer volume. Both the local play volume and the publish volume are set.
 *
 * @param volume The range is 0 ~ 200. The default is 60.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_volume(int volume, enum zego_media_player_instance_index instance_index);


/**
 * Set mediaplayer local playback volume.
 *
 * @param volume The range is 0 ~ 200. The default is 60.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_play_volume(int volume, enum zego_media_player_instance_index instance_index);


/**
 * Set mediaplayer publish volume.
 *
 * @param volume The range is 0 ~ 200. The default is 60.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_publish_volume(int volume, enum zego_media_player_instance_index instance_index);


/**
 * Gets the current local playback volume of the mediaplayer, the range is 0 ~ 200, with the default value of 60.
 */
ZEGOEXP_API int EXP_CALL zego_express_media_player_get_play_volume(enum zego_media_player_instance_index instance_index);


/**
 * Gets the current publish volume of the mediaplayer, the range is 0 ~ 200, with the default value of 60.
 */
ZEGOEXP_API int EXP_CALL zego_express_media_player_get_publish_volume(enum zego_media_player_instance_index instance_index);


/**
 * Get the total progress of your media resources.
 *
 * You should load resource before invoking this function, otherwise the return value is 0
 *
 * @return Unit is millisecond
 */
ZEGOEXP_API unsigned long long EXP_CALL zego_express_media_player_get_total_duration(enum zego_media_player_instance_index instance_index);


/**
 * Get current playing progress.
 *
 * You should load resource before invoking this function, otherwise the return value is 0
 */
ZEGOEXP_API unsigned long long EXP_CALL zego_express_media_player_get_current_progress(enum zego_media_player_instance_index instance_index);


/**
 * Whether to play locally silently.
 *
 * If [enableAux] switch is turned on, there is still sound in the publishing stream. The default is false.
 *
 * @param mute Mute local audio flag, The default is false.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_mute_local_audio(bool mute, enum zego_media_player_instance_index instance_index);


/**
 * Set the view of the player playing video.
 *
 * @param canvas Video rendered canvas object
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_player_canvas(struct zego_canvas * canvas, enum zego_media_player_instance_index instance_index);


/**
 * Whether to mix the player's sound into the stream being published.
 *
 * @param enable Aux audio flag. The default is false.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_aux(bool enable, enum zego_media_player_instance_index instance_index);


/**
 * Whether to repeat playback.
 *
 * @param enable repeat playback flag. The default is false.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_repeat(bool enable, enum zego_media_player_instance_index instance_index);


/**
 * Set playback progress callback interval.
 *
 * This function can control the callback frequency of [onMediaPlayerPlayingProgress]. When the callback interval is set to 0, the callback is stopped. The default callback interval is 1s
 * This callback are not returned exactly at the set callback interval, but rather at the frequency at which the audio or video frames are processed to determine whether the callback is needed to call
 *
 * @param millisecond Interval of playback progress callback in milliseconds
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_progress_interval(unsigned long long millisecond, enum zego_media_player_instance_index instance_index);


/**
 * Get the number of audio tracks of the playback file.
 *
 * @return Number of audio tracks
 */
ZEGOEXP_API unsigned int EXP_CALL zego_express_media_player_get_audio_track_count(enum zego_media_player_instance_index instance_index);


/**
 * Set the audio track of the playback file.
 *
 * @param index Audio track index, the number of audio tracks can be obtained through the [getAudioTrackCount] function.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_audio_track_index(unsigned int index, enum zego_media_player_instance_index instance_index);


/**
 * Setting up the specific voice changer parameters.
 *
 * @param audio_channel The audio channel to be voice changed
 * @param param Voice changer parameters
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_voice_changer_param(enum zego_media_player_audio_channel audio_channel, float param, enum zego_media_player_instance_index instance_index);


/**
 * Whether to audio data playback.
 *
 * @param enable Audio data playback flag. The default is false.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_audio_data(bool enable, enum zego_media_player_instance_index instance_index);


/**
 * Whether to video data playback.
 *
 * @param enable Video data playback flag. The default is false.
 */
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_video_data(bool enable, enum zego_video_frame_format format, enum zego_media_player_instance_index instance_index);


/**
 * The callback triggered when the state of the media player changes.
 *
 * @param state Media player status
 * @param error_code Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_state_update)(enum zego_media_player_state state, zego_error error_code, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_state_update_callback(zego_on_media_player_state_update callback_func, void * user_context);


/**
 * The callback triggered when the network status of the media player changes.
 *
 * @param network_event Network status event
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_network_event)(enum zego_media_player_network_event network_event, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_network_event_callback(zego_on_media_player_network_event callback_func, void * user_context);


/**
 * The callback to report the current playback progress of the media player.
 *
 * @param millisecond Progress in milliseconds
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_playing_progress)(unsigned long long millisecond, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_playing_progress_callback(zego_on_media_player_playing_progress callback_func, void * user_context);


/**
 * The callback triggered when the media player throws out video frame data.
 *
 * @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
 * @param data_length Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
 * @param param Video frame flip mode
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_video_frame)(const unsigned char** data, unsigned int* data_length, const struct zego_video_frame_param param, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_video_frame_callback(zego_on_media_player_video_frame callback_func, void * user_context);


/**
 * The callback triggered when the media player throws out audio frame data.
 *
 * @param data Raw data of audio frames
 * @param data_length Data length
 * @param param audio frame flip mode
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_audio_frame)(const unsigned char* data, unsigned int data_length, const struct zego_audio_frame_param param, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_audio_frame_callback(zego_on_media_player_audio_frame callback_func, void * user_context);


/**
 * Callback for media player loads resources.
 *
 * @param error_code Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_load_resource)(zego_error error_code, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_load_resource_callback(zego_on_media_player_load_resource callback_func, void * user_context);


/**
 * Callback for media player seek to playback progress.
 *
 * @param seq Sequence.
 * @param error_code Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
 * @param instance_index Media player instance index
 * @param user_context Context of user.
 */
typedef void(*zego_on_media_player_seek_to)(zego_seq seq, zego_error error_code, enum zego_media_player_instance_index instance_index, void * user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_seek_to_callback(zego_on_media_player_seek_to callback_func, void * user_context);



ZEGO_END_DECLS

#endif
