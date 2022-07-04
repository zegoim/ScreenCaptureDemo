
#ifndef __ZEGO_EXPRESS_MEDIAPLAYER_H__
#define __ZEGO_EXPRESS_MEDIAPLAYER_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Creates a media player instance.
///
/// Available since: 2.1.0
/// Description: Creates a media player instance.
/// Use case: It is often used to play media resource scenes, For example, play video files, push the video of media resources in combination with custom video acquisition, and the remote end can pull the stream for viewing.
/// When to call: It can be called after the SDK by [createEngine] has been initialized.
/// Restrictions: Currently, a maximum of 4 instances can be created, after which it will return NULL.
/// Caution: The more instances of a media player, the greater the performance overhead on the device.
/// Related APIs: User can call [destroyMediaPlayer] function to destroy a media player instance.
///
/// @return Media player instance, NULL will be returned when the maximum number is exceeded.
ZEGOEXP_API enum zego_media_player_instance_index EXP_CALL zego_express_create_media_player();

/// Destroys a media player instance.
///
/// Available since: 2.1.0
/// Description: Destroys a media player instance.
/// Related APIs: User can call [createMediaPlayer] function to create a media player instance.
ZEGOEXP_API zego_error EXP_CALL
zego_express_destroy_media_player(enum zego_media_player_instance_index instance_index);

/// Start playing.
///
/// You need to load resources before playing
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_start(enum zego_media_player_instance_index instance_index);

/// Stop playing.
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_stop(enum zego_media_player_instance_index instance_index);

/// Pause playing.
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_pause(enum zego_media_player_instance_index instance_index);

/// Resume playing.
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_resume(enum zego_media_player_instance_index instance_index);

/// Load media resource.
///
/// Yon can pass the absolute path of the local resource or the URL of the network resource
///
/// @param path The absolute resource path or the URL of the network resource and cannot be NULL or "".
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_load_resource(
    const char *path, enum zego_media_player_instance_index instance_index);

/// Load media resource.
///
/// TODO
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_load_resource_from_media_data(
    unsigned char *media_data, int media_data_length, long start_position,
    enum zego_media_player_instance_index instance_index);

/// Load media resource.
///
/// Available: since 2.14.0
/// Description: Load media resources, and specify the progress, in milliseconds, at which playback begins.
/// Use case: Developers can load the absolute path to the local resource or the URL of the network resource incoming.
/// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Caution: When [start_position] exceeds the total playing time, it will start playing from the beginning.
///
/// @param path The absolute resource path or the URL of the network resource and cannot be NULL or "".
/// @param start_position The progress at which the playback started.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_load_resource_with_position(
    const char *path, long start_position, enum zego_media_player_instance_index instance_index);

/// Load media resource.
///
/// Available: since 2.14.0
/// Description: Load media resources, and specify the progress, in milliseconds, at which playback begins.
/// Use case: Developers can load the absolute path to the local resource or the URL of the network resource incoming.
/// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Caution: When [start_position] exceeds the total playing time, it will start playing from the beginning.
///
/// @param resource_id The resource ID obtained from the copyrighted music module.
/// @param start_position The progress at which the playback started.
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_load_copyrighted_music_resource_with_position(
    const char *resource_id, long start_position,
    enum zego_media_player_instance_index instance_index);

/// Get the current playback status.
ZEGOEXP_API enum zego_media_player_state EXP_CALL
zego_express_media_player_get_current_state(enum zego_media_player_instance_index instance_index);

/// Set the specified playback progress.
///
/// Unit is millisecond
///
/// @param millisecond Point in time of specified playback progress
ZEGOEXP_API zego_seq EXP_CALL zego_express_media_player_seek_to(
    unsigned long long millisecond, enum zego_media_player_instance_index instance_index);

/// Set mediaplayer volume. Both the local play volume and the publish volume are set.
///
/// @param volume The range is 0 ~ 200. The default is 60.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_volume(
    int volume, enum zego_media_player_instance_index instance_index);

/// Set mediaplayer local playback volume.
///
/// @param volume The range is 0 ~ 200. The default is 60.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_play_volume(
    int volume, enum zego_media_player_instance_index instance_index);

/// Set mediaplayer publish volume.
///
/// @param volume The range is 0 ~ 200. The default is 60.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_publish_volume(
    int volume, enum zego_media_player_instance_index instance_index);

/// Gets the current local playback volume of the mediaplayer, the range is 0 ~ 200, with the default value of 60.
ZEGOEXP_API int EXP_CALL
zego_express_media_player_get_play_volume(enum zego_media_player_instance_index instance_index);

/// Gets the current publish volume of the mediaplayer, the range is 0 ~ 200, with the default value of 60.
ZEGOEXP_API int EXP_CALL
zego_express_media_player_get_publish_volume(enum zego_media_player_instance_index instance_index);

/// Get the total progress of your media resources.
///
/// You should load resource before invoking this function, otherwise the return value is 0
///
/// @return Unit is millisecond
ZEGOEXP_API unsigned long long EXP_CALL
zego_express_media_player_get_total_duration(enum zego_media_player_instance_index instance_index);

/// Get current playing progress.
///
/// You should load resource before invoking this function, otherwise the return value is 0
ZEGOEXP_API unsigned long long EXP_CALL zego_express_media_player_get_current_progress(
    enum zego_media_player_instance_index instance_index);

/// Whether to play locally silently.
///
/// If [enableAux] switch is turned on, there is still sound in the publishing stream. The default is false.
///
/// @param mute Mute local audio flag, The default is false.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_mute_local_audio(
    bool mute, enum zego_media_player_instance_index instance_index);

/// Set the view of the player playing video.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param canvas Video rendered canvas object
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_player_canvas(
    struct zego_canvas *canvas, enum zego_media_player_instance_index instance_index);

/// Whether to mix the player's sound into the stream being published.
///
/// This interface will only mix the media player sound into the main channel
///
/// @param enable Aux audio flag. The default is false.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_aux(
    bool enable, enum zego_media_player_instance_index instance_index);

/// Whether to repeat playback.
///
/// @param enable repeat playback flag. The default is false.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_repeat(
    bool enable, enum zego_media_player_instance_index instance_index);

/// Set the count of play loops.
///
/// Available: since 2.10.0
/// Description: Set the count of play loops.
/// Use cases: Users can call this function when they need to use the media player to loop playback resources.
/// When to call /Trigger: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Restrictions: None.
/// Caution: Please note that after using this interface, the [enableRepeat] interface will become invalid.
///
/// @param count the count of play loops.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_play_loop_count(
    int count, enum zego_media_player_instance_index instance_index);

/// Set the speed of play.
///
/// Available since: 2.12.0
/// Description: Set the playback speed of the player.
/// When to call: You should load resource before invoking this function.
/// Restrictions: None.
/// Related APIs: Resources can be loaded through the [loadResource] function.
///
/// @param speed The speed of play. The range is 0.5 ~ 2.0. The default is 1.0.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_play_speed(
    float speed, enum zego_media_player_instance_index instance_index);

/// Set playback progress callback interval.
///
/// This function can control the callback frequency of [onMediaPlayerPlayingProgress]. When the callback interval is set to 0, the callback is stopped. The default callback interval is 1s
/// This callback are not returned exactly at the set callback interval, but rather at the frequency at which the audio or video frames are processed to determine whether the callback is needed to call
///
/// @param millisecond Interval of playback progress callback in milliseconds
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_progress_interval(
    unsigned long long millisecond, enum zego_media_player_instance_index instance_index);

/// Get the number of audio tracks of the playback file.
///
/// @return Number of audio tracks
ZEGOEXP_API unsigned int EXP_CALL zego_express_media_player_get_audio_track_count(
    enum zego_media_player_instance_index instance_index);

/// Set the audio track of the playback file.
///
/// @param index Audio track index, the number of audio tracks can be obtained through the [getAudioTrackCount] function.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_audio_track_index(
    unsigned int index, enum zego_media_player_instance_index instance_index);

/// Setting up the specific voice changer parameters.
///
/// @param audio_channel The audio channel to be voice changed
/// @param param Voice changer parameters
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_voice_changer_param(
    enum zego_media_player_audio_channel audio_channel, float param,
    enum zego_media_player_instance_index instance_index);

/// Whether to audio data playback.
///
/// @param enable Audio data playback flag. The default is false.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_audio_data(
    bool enable, enum zego_media_player_instance_index instance_index);

/// Whether to video data playback.
///
/// @param enable Video data playback flag. The default is false.
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_enable_video_data(bool enable, enum zego_video_frame_format format,
                                            enum zego_media_player_instance_index instance_index);

/// Take a screenshot of the current playing screen of the media player.
///
/// Only in the case of calling `setPlayerCanvas` to set the display controls and the playback state, can the screenshot be taken normally
/// Note: This function is only available in ZegoExpressVideo SDK!
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_take_snapshot(enum zego_media_player_instance_index instance_index);

/// Open precise seek and set relevant attributes.
///
/// The setting must be called before loading the resource, and it will take effect during the entire life cycle of the media player.
///
/// @param enable Whether to enable accurate seek
/// @param config The property setting of precise seek is valid only when enable is true.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_accurate_seek(
    bool enable, struct zego_accurate_seek_config *config,
    enum zego_media_player_instance_index instance_index);

/// Set the maximum cache duration and cache data size of web materials.
///
/// The setting must be called before loading the resource, and it will take effect during the entire life cycle of the media player.
/// Time and size are not allowed to be 0 at the same time. The SDK internal default time is 5000, and the size is 15*1024*1024 byte.When one of time and size reaches the set value first, the cache will stop.
///
/// @param time The maximum length of the cache time, in ms, the SDK internal default is 5000; the effective value is greater than or equal to 2000; if you fill in 0, it means no limit.
/// @param size The maximum size of the cache, the unit is byte, the internal default size of the SDK is 15*1024*1024 byte; the effective value is greater than or equal to 5000000, if you fill in 0, it means no limit.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_network_resource_max_cache(
    unsigned int time, unsigned int size, enum zego_media_player_instance_index instance_index);

/// Get the playable duration and size of the cached data of the current network material cache queue
///
/// @return Returns the current cached information, including the length of time the data can be played and the size of the cached data.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_get_network_resource_cache(
    struct zego_network_resource_cache *cache,
    enum zego_media_player_instance_index instance_index);

/// Use this interface to set the cache threshold that the media player needs to resume playback. The SDK default value is 5000ms，The valid value is greater than or equal to 1000ms
///
/// The setting must be called before loading the resource, and it will take effect during the entire life cycle of the media player.
/// When the network status is poor and the media player has finished playing the cached network resources, it will stop playing, and notify the user through the `ZegoMediaPlayerNetworkEvent.BUFFER_BEGIN` state of the callback interface `onMediaPlayerNetworkEvent` that the network resources are being recached.
/// Only when the cached network resources are greater than the set threshold, the media player will automatically resume playback at the original paused position, and notify the user through the `ZegoMediaPlayerNetworkEvent.BUFFER_ENDED` of the callback interface `onMediaPlayerNetworkEvent` that the user has cached the network resources The threshold was reached and playback resumed.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_network_buffer_threshold(
    unsigned int threshold, enum zego_media_player_instance_index instance_index);

/// Whether to enable sound level monitoring.
///
/// Available since: 2.15.0
/// Description: Whether to enable sound level monitoring.
/// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Restrictions: None.
/// Related callbacks: After it is turned on, user can use the [onMediaPlayerSoundLevelUpdate] callback to monitor sound level updates.
///
/// @param enable Whether to enable monitoring, true is enabled, false is disabled.
/// @param millisecond Monitoring time period of the sound level, in milliseconds, has a value range of [100, 3000].
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_sound_level_monitor(
    bool enable, unsigned int millisecond, enum zego_media_player_instance_index instance_index);

/// Whether to enable frequency spectrum monitoring.
///
/// Available since: 2.15.0
/// Description: Whether to enable frequency spectrum monitoring.
/// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Restrictions: None.
/// Related APIs: After it is turned on, user can use the [onMediaPlayerFrequencySpectrumUpdate] callback to monitor frequency spectrum updates.
///
/// @param enable Whether to enable monitoring, true is enabled, false is disabled.
/// @param millisecond Monitoring time period of the frequency spectrum, in milliseconds, has a value range of [100, 3000].
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_enable_frequency_spectrum_monitor(
    bool enable, unsigned int millisecond, enum zego_media_player_instance_index instance_index);

/// Set the playback channel.
///
/// Available since: 2.20.0
/// Description: Set the playback channel.
/// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Restrictions: None.
///
/// @param audio_channel Playback channel, the default is ZegoMediaPlayerAudioChannelAll.
ZEGOEXP_API zego_error EXP_CALL zego_express_media_player_set_active_audio_channel(
    enum zego_media_player_audio_channel audio_channel,
    enum zego_media_player_instance_index instance_index);

/// Clears the last frame of the playback control that remains on the control after playback ends.
///
/// Available since: 2.20.0
/// Description: Clears the last frame of the playback control that remains on the control after playback ends.
/// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
/// Restrictions: The interface call takes effect only when the media player ends playing.
ZEGOEXP_API zego_error EXP_CALL
zego_express_media_player_clear_view(enum zego_media_player_instance_index instance_index);

/// MediaPlayer playback status callback.
///
/// Available since: 1.3.4
/// Description: MediaPlayer playback status callback.
/// Trigger: The callback triggered when the state of the media player changes.
/// Restrictions: None.
///
/// @param state Media player status.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_state_update)(
    enum zego_media_player_state state, zego_error error_code,
    enum zego_media_player_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_state_update_callback(
    zego_on_media_player_state_update callback_func, void *user_context);

/// The callback triggered when the network status of the media player changes.
///
/// Available since: 1.3.4
/// Description: The callback triggered when the network status of the media player changes.
/// Trigger: When the media player is playing network resources, this callback will be triggered when the status change of the cached data.
/// Restrictions: The callback will only be triggered when the network resource is played.
/// Related APIs: [setNetWorkBufferThreshold].
///
/// @param network_event Network status event.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_network_event)(
    enum zego_media_player_network_event network_event,
    enum zego_media_player_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_network_event_callback(
    zego_on_media_player_network_event callback_func, void *user_context);

/// The callback to report the current playback progress of the media player.
///
/// Available since: 1.3.4
/// Description: The callback triggered when the network status of the media player changes. Set the callback interval by calling [setProgressInterval]. When the callback interval is set to 0, the callback is stopped. The default callback interval is 1 second.
/// Trigger: When the media player is playing network resources, this callback will be triggered when the status change of the cached data.
/// Restrictions: None.
/// Related APIs: [setProgressInterval].
///
/// @param millisecond Progress in milliseconds.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_playing_progress)(
    unsigned long long millisecond, enum zego_media_player_instance_index instance_index,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_playing_progress_callback(
    zego_on_media_player_playing_progress callback_func, void *user_context);

/// The callback triggered when the media player got media side info.
///
/// Available since: 2.2.0
/// Description: The callback triggered when the media player got media side info.
/// Trigger: When the media player starts playing media files, the callback is triggered if the SEI is resolved to the media file.
/// Caution: The callback does not actually take effect until call [setEventHandler] to set.
///
/// @param data SEI content.
/// @param data_length SEI content length.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_recv_sei)(const unsigned char *data, unsigned int data_length,
                                              enum zego_media_player_instance_index instance_index,
                                              void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_recv_sei_callback(
    zego_on_media_player_recv_sei callback_func, void *user_context);

/// The callback of sound level update.
///
/// Available since: 2.15.0
/// Description: The callback of sound level update.
/// Trigger: The callback frequency is specified by [EnableSoundLevelMonitor].
/// Caution: The callback does not actually take effect until call [setEventHandler] to set.
/// Related APIs: To monitor this callback, you need to enable it through [EnableSoundLevelMonitor].
///
/// @param sound_level Sound level value, value range: [0.0, 100.0].
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_sound_level_update)(
    float sound_level, enum zego_media_player_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_sound_level_update_callback(
    zego_on_media_player_sound_level_update callback_func, void *user_context);

/// The callback of frequency spectrum update.
///
/// Available since: 2.15.0
/// Description: The callback of frequency spectrum update.
/// Trigger: The callback frequency is specified by [EnableFrequencySpectrumMonitor].
/// Caution: The callback does not actually take effect until call [setEventHandler] to set.
/// Related APIs: To monitor this callback, you need to enable it through [EnableFrequencySpectrumMonitor].
///
/// @param spectrum_list Spectrum values list.
/// @param spectrum_count Spectrum values list of count.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_frequency_spectrum_update)(
    float *spectrum_list, unsigned int spectrum_count,
    enum zego_media_player_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_frequency_spectrum_update_callback(
    zego_on_media_player_frequency_spectrum_update callback_func, void *user_context);

/// The callback triggered when the media player throws out video frame data.
///
/// Available since: 2.16.0
/// Description: The callback triggered when the media player throws out video frame data.
/// Trigger: The callback is generated when the media player starts playing.
/// Caution: The callback does not actually take effect until call [setVideoHandler] to set.
///
/// @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2]).
/// @param data_length Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2]).
/// @param param Video frame flip mode.
/// @param extra_info Video frame extra info. json format data.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_video_frame)(
    const unsigned char **data, unsigned int *data_length,
    const struct zego_video_frame_param param, const char *extra_info,
    enum zego_media_player_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_video_frame_callback(
    zego_on_media_player_video_frame callback_func, void *user_context);

/// The callback triggered when the media player throws out audio frame data.
///
/// Available since: 1.3.4
/// Description: The callback triggered when the media player throws out audio frame data.
/// Trigger: The callback is generated when the media player starts playing.
/// Caution: The callback does not actually take effect until call [setAudioHandler] to set.
///
/// @param data Raw data of audio frames.
/// @param data_length Data length.
/// @param param audio frame flip mode.
/// @param instance_index Media player instance index.
/// @param user_context Context of user.
typedef void (*zego_on_media_player_audio_frame)(
    const unsigned char *data, unsigned int data_length, const struct zego_audio_frame_param param,
    enum zego_media_player_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_audio_frame_callback(
    zego_on_media_player_audio_frame callback_func, void *user_context);

/// Callback for media player loads resources.
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param instance_index Media player instance index
/// @param user_context Context of user.
typedef void (*zego_on_media_player_load_resource)(
    zego_error error_code, enum zego_media_player_instance_index instance_index,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_load_resource_callback(
    zego_on_media_player_load_resource callback_func, void *user_context);

/// Callback for media player seek to playback progress.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param instance_index Media player instance index
/// @param user_context Context of user.
typedef void (*zego_on_media_player_seek_to)(zego_seq seq, zego_error error_code,
                                             enum zego_media_player_instance_index instance_index,
                                             void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_seek_to_callback(
    zego_on_media_player_seek_to callback_func, void *user_context);

/// The callback of the screenshot of the media player playing screen
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param image Snapshot image (Windows: HBITMAP; macOS/iOS: CGImageRef; Linux: QImage; Android: Bitmap)
/// @param instance_index Media player instance index
/// @param user_context Context of user.
typedef void (*zego_on_media_player_take_snapshot_result)(
    zego_error error_code, void *image, enum zego_media_player_instance_index instance_index,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_media_player_take_snapshot_result_callback(
    zego_on_media_player_take_snapshot_result callback_func, void *user_context);

ZEGO_END_DECLS

#endif
