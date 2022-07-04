
#ifndef __ZEGO_EXPRESS_COPYRIGHTED_MUSIC_H__
#define __ZEGO_EXPRESS_COPYRIGHTED_MUSIC_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Creates a copyrighted music instance.
///
/// Available since: 2.13.0
/// Description: Creates a copyrighted music instance.
/// Use case: Often used in online KTV chorus scenarios, users can use related functions by creating copyrighted music instance objects.
/// When to call: It can be called after the engine by [createEngine] has been initialized.
/// Restrictions: The SDK only supports the creation of one instance of CopyrightedMusic. Multiple calls to this function return the same object.
///
/// @return copyrighted music instance, multiple calls to this function return the same object.
ZEGOEXP_API void EXP_CALL zego_express_create_copyrighted_music();

/// Destroys a copyrighted music instance.
///
/// Available since: 2.13.0
/// Description: Destroys a copyrighted music instance.
/// When to call: It can be called before the engine by [destroyEngine]
ZEGOEXP_API zego_error EXP_CALL zego_express_destroy_copyrighted_music();

/// Initialize the copyrighted music module.
///
/// Available since: 2.13.0
/// Description: Initialize the copyrighted music so that you can use the function of the copyrighted music later.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
/// Restrictions: The real user information must be passed in, otherwise the song resources cannot be obtained for playback.
///
/// @param config the copyrighted music configuration.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_copyrighted_music_init(struct zego_copyrighted_music_config config);

/// Get cache size.
///
/// Available since: 2.13.0
/// Description: When using this module, some cache files may be generated, and the size of the cache file can be obtained through this interface.
/// Use case: Used to display the cache size of the App.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @return cache file size, in byte.
ZEGOEXP_API unsigned long long EXP_CALL zego_express_copyrighted_music_get_cache_size();

/// Clear cache.
///
/// Available since: 2.13.0
/// Description: When using this module, some cache files may be generated, which can be cleared through this interface.
/// Use case: Used to clear the cache of the App.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
ZEGOEXP_API zego_error EXP_CALL zego_express_copyrighted_music_clear_cache();

/// Send extended feature request.
///
/// Available since: 2.13.0
/// Description: Initialize the copyrighted music so that you can use the function of the copyrighted music later.
/// Use case: Used to get a list of songs.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @param command request command, see details for specific supported commands.
/// @param params request parameters, each request command has corresponding request parameters.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_copyrighted_music_send_extended_request(const char *command, const char *params);

/// Get lyrics in lrc format.
///
/// Available since: 2.13.0
/// Description: Get lyrics in lrc format, support parsing lyrics line by line.
/// Use case: Used to display lyrics line by line.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @param song_id the ID of the song or accompaniment, the song and accompaniment of a song share the same ID.
ZEGOEXP_API zego_seq EXP_CALL zego_express_copyrighted_music_get_lrc_lyric(const char *song_id);

/// Get lyrics in krc format.
///
/// Available since: 2.13.0
/// Description: Get lyrics in krc format, support parsing lyrics word by word.
/// Use case: Used to display lyrics word by word.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @param krc_token The krcToken obtained by calling requestAccompaniment.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_copyrighted_music_get_krc_lyric_by_token(const char *krc_token);

/// Request a song.
///
/// Available since: 2.13.0
/// Description: In addition to obtaining the basic information of the song (duration, song name, singer, etc.), and the most important resource id that can be used for local playback, or share_token for sharing to others, there are also some related authentications. information. Support three ways to request a song, pay-per-use, monthly billing by user, and monthly billing by room.
/// Use case: Get copyrighted songs for local playback and sharing.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
/// Restrictions: This interface will trigger billing. A song may have three sound qualities: normal, high-definition, and lossless. Each sound quality has a different resource file, and each resource file has a unique resource ID.
///
/// @param config request configuration.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_copyrighted_music_request_song(struct zego_copyrighted_music_request_config config);

/// Request accompaniment.
///
/// Available since: 2.13.0
/// Description: You can get the accompaniment resources of the song corresponding to the songID, including resource_id, krc_token, share_token, etc. Support three ways to request accompaniment, pay-per-use, monthly billing by user, and monthly billing by room.
/// Use case: Get copyrighted accompaniment for local playback and sharing.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
/// Restrictions: This interface will trigger billing.
///
/// @param config request configuration.
ZEGOEXP_API zego_seq EXP_CALL zego_express_copyrighted_music_request_accompaniment(
    struct zego_copyrighted_music_request_config config);

/// Request accompaniment clip.
///
/// Available since: 2.13.0
/// Description: You can obtain the climax clip resources of the song corresponding to the songID, including resource_id, krc_token, share_token, etc. Support three ways to request accompaniment clip, pay-per-use, monthly billing by user, and monthly billing by room.
/// Use case: Get copyrighted accompaniment clip for local playback and sharing.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
/// Restrictions: This interface will trigger billing.
///
/// @param config request configuration.
ZEGOEXP_API zego_seq EXP_CALL zego_express_copyrighted_music_request_accompaniment_clip(
    struct zego_copyrighted_music_request_config config);

/// Get a song or accompaniment.
///
/// Available since: 2.13.0
/// Description: After the user successfully obtains the song/accompaniment/climax clip resource, he can get the corresponding shareToken, share the shareToken with other users, and other users call this interface to obtain the shared music resources.
/// Use case: In the online KTV scene, after receiving the song or accompaniment token shared by the lead singer, the chorus obtains the corresponding song or accompaniment through this interface, and then plays it on the local end.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @param share_token access the corresponding authorization token for a song or accompaniment.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_copyrighted_music_get_music_by_token(const char *share_token);

/// Download song or accompaniment.
///
/// Available since: 2.13.0
/// Description: Download a song or accompaniment. It can only be played after downloading successfully.
/// Use case: Get copyrighted accompaniment for local playback and sharing.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
/// Restrictions: Loading songs or accompaniment resources is affected by the network.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API zego_seq EXP_CALL zego_express_copyrighted_music_download(const char *resource_id);

/// Query the resource's cache is existed or not.
///
/// Available since: 2.13.0
/// Description: Query the resource is existed or not.
/// Use case: Can be used to check the resource's cache is existed or not
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @param song_id the ID of the song or accompaniment, the song and accompaniment of a song share the same ID.
/// @param type the song resource type.
ZEGOEXP_API bool EXP_CALL zego_express_copyrighted_music_query_cache(
    const char *song_id, enum zego_copyrighted_music_type type);

/// Get the playing time of a song or accompaniment file.
///
/// Available since: 2.13.0
/// Description: Get the playing time of a song or accompaniment file.
/// Use case: Can be used to display the playing time information of the song or accompaniment on the view.
/// When to call: After initializing the copyrighted music [createCopyrightedMusic].
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API unsigned long long EXP_CALL
zego_express_copyrighted_music_get_duration(const char *resource_id);

/// Start scoring.
///
/// Available since: 2.15.0
/// Description: Start the scoring function.After starting scoring, the scoring result OnCurrentPitchValueUpdate callback will be received according to the set callback time interval.
/// Use case: Can be used to display the singing score on the view.
/// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.
/// Restrictions: Only support use this api after [startPublishingStream].
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
/// @param pitch_value_interval the time interval of real-time pitch line callback, in milliseconds, the default is 50 milliseconds.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_start_score(const char *resource_id,
                                                                    int pitch_value_interval);

/// Pause scoring.
///
/// Available since: 2.15.0
/// Description: Pause ongoing scoring,will stop the [OnCurrentPitchValueUpdate] callback.
/// Use case: You can call this interface to pause the scoring function while scoring.
/// When to call: It can be called while grading.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_pause_score(const char *resource_id);

/// Resume scoring.
///
/// Available since: 2.15.0
/// Description: Resume currently paused scoring.
/// Use case: When there is currently paused scoring, this interface can be called to resume the scoring function.
/// When to call: It can be called when there is currently a paused scoring.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_resume_score(const char *resource_id);

/// Stop scoring.
///
/// Available since: 2.15.0
/// Description: End the current rating.The [OnCurrentPitchValueUpdate] callback will be stopped, but the average or total score can still be obtained normally.
/// Use case: You can call this interface to end the scoring while scoring.
/// When to call: It can be called while grading.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_stop_score(const char *resource_id);

/// Reset scoring.
///
/// Available since: 2.15.0
/// Description: Reset the scores that have already been performed,The [OnCurrentPitchValueUpdate] callback will be stopped and the average or total score will be 0.
/// Use case: Often used in scenes where the same song is re-sung.
/// When to call: It can be called after scoring has been performed.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_reset_score(const char *resource_id);

/// Get the score of the previous sentence.
///
/// Available since: 2.15.0
/// Description: Get the score of the previous sentence.
/// Use case: Can be used to display the score of each sentence on the view.
/// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.The user gets it once after singing each sentence.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_get_previous_score(const char *resource_id);

/// Get average score.
///
/// Available since: 2.15.0
/// Description: Get the average score.
/// Use case: Can be used to display the average score on the view.
/// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_get_average_score(const char *resource_id);

/// Get total score .
///
/// Available since: 2.15.0
/// Description: Get the total score.
/// Use case: Can be used to display the total score on the view.
/// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_get_total_score(const char *resource_id);

/// Get standard pitch data.
///
/// Available since: 2.15.0
/// Description: Get standard pitch data.
/// Use case: Can be used to display standard pitch lines on the view.
/// Restrictions: Only accompaniment or climactic clip assets have pitch lines.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_copyrighted_music_get_standard_pitch(const char *resource_id);

/// Get total score .
///
/// Available since: 2.15.0
/// Description: Get real-time pitch data.
/// Use case: Can be used to display real-time pitch lines on the view.
/// When to call: It can be called after playing the copyright accompaniment and starting to score.
///
/// @param resource_id the resource ID corresponding to the song or accompaniment.
ZEGOEXP_API int EXP_CALL zego_express_copyrighted_music_get_current_pitch(const char *resource_id);

/// Callback for download song or accompaniment progress rate.
///
/// @param seq Sequence.
/// @param resource_id The resource ID of the song or accompaniment that triggered this callback.
/// @param progress_rate download progress rate.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_download_progress_update)(zego_seq seq,
                                                                   const char *resource_id,
                                                                   float progress_rate,
                                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_download_progress_update_callback(
    zego_on_copyrighted_music_download_progress_update callback_func, void *user_context);

/// Real-time pitch line callback.
///
/// @param resource_id The resource ID of the song or accompaniment that triggered this callback.
/// @param current_duration Current playback progress.
/// @param pitch_value Real-time pitch accuracy or value.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_current_pitch_value_update)(const char *resource_id,
                                                                     int current_duration,
                                                                     int pitch_value,
                                                                     void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_current_pitch_value_update_callback(
    zego_on_copyrighted_music_current_pitch_value_update callback_func, void *user_context);

/// Callback for copyrighted music init.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_init)(zego_seq seq, zego_error error_code,
                                               void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_init_callback(
    zego_on_copyrighted_music_init callback_func, void *user_context);

/// Callback for copyrighted music init.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param command request command.
/// @param result request result, each request command has corresponding request result.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_send_extended_request)(zego_seq seq, zego_error error_code,
                                                                const char *command,
                                                                const char *result,
                                                                void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_send_extended_request_callback(
    zego_on_copyrighted_music_send_extended_request callback_func, void *user_context);

/// Get lrc format lyrics complete callback.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param lyrics lrc format lyrics.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_get_lrc_lyric)(zego_seq seq, zego_error error_code,
                                                        const char *lyrics, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_get_lrc_lyric_callback(
    zego_on_copyrighted_music_get_lrc_lyric callback_func, void *user_context);

/// Get krc format lyrics complete callback.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param lyrics krc format lyrics.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_get_krc_lyric_by_token)(zego_seq seq,
                                                                 zego_error error_code,
                                                                 const char *lyrics,
                                                                 void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_get_krc_lyric_by_token_callback(
    zego_on_copyrighted_music_get_krc_lyric_by_token callback_func, void *user_context);

/// Callback for request song.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param resource The JSON string returned by the song ordering service, including song resource information.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_request_song)(zego_seq seq, zego_error error_code,
                                                       const char *resource, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_request_song_callback(
    zego_on_copyrighted_music_request_song callback_func, void *user_context);

/// Callback for request accompaniment.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param resource accompany resource information.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_request_accompaniment)(zego_seq seq, zego_error error_code,
                                                                const char *resource,
                                                                void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_request_accompaniment_callback(
    zego_on_copyrighted_music_request_accompaniment callback_func, void *user_context);

/// Callback for request accompaniment clip.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param resource accompany clip resource information.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_request_accompaniment_clip)(zego_seq seq,
                                                                     zego_error error_code,
                                                                     const char *resource,
                                                                     void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_request_accompaniment_clip_callback(
    zego_on_copyrighted_music_request_accompaniment_clip callback_func, void *user_context);

/// Callback for acquire songs or accompaniment through authorization token.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param resource song or accompany resource information.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_get_music_by_token)(zego_seq seq, zego_error error_code,
                                                             const char *resource,
                                                             void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_get_music_by_token_callback(
    zego_on_copyrighted_music_get_music_by_token callback_func, void *user_context);

/// Callback for download song or accompaniment.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_download)(zego_seq seq, zego_error error_code,
                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_download_callback(
    zego_on_copyrighted_music_download callback_func, void *user_context);

/// Get standard pitch data complete callback.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param pitch Standard pitch data.
/// @param user_context Context of user.
typedef void (*zego_on_copyrighted_music_get_standard_pitch)(zego_seq seq, zego_error error_code,
                                                             const char *pitch, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copyrighted_music_get_standard_pitch_callback(
    zego_on_copyrighted_music_get_standard_pitch callback_func, void *user_context);

ZEGO_END_DECLS

#endif
