
#ifndef __ZEGO_EXPRESS_DEFINE_H__
#define __ZEGO_EXPRESS_DEFINE_H__

#ifndef ZEGOEXP_API
#if defined(_WIN32)
#ifdef ZEGO_EXPRESS_EXPORTS
#define ZEGOEXP_API __declspec(dllexport)
#else
#define ZEGOEXP_API __declspec(dllimport)
#endif
#define EXP_CALL __cdecl
#else
#define ZEGOEXP_API __attribute__((visibility("default")))
#define EXP_CALL
#endif
#endif

#ifdef __cplusplus
#define ZEGO_BEGIN_DECLS extern "C" {
#define ZEGO_END_DECLS }
#else
#define ZEGO_BEGIN_DECLS
#define ZEGO_END_DECLS
#endif

#ifndef __cplusplus
#define bool _Bool
#define false 0
#define true 1
#endif

#if defined(__APPLE_OS__) || defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#define ZEGO_EXPRESS_DEFAULT_LOG_SIZE (5242880) // 5 * 1024 * 1024 bytes
#define ZEGO_EXPRESS_MAX_LOG_SIZE (104857600)   // 100 * 1024 * 1024 bytes

#define zego_error int
#define zego_seq int
#define zego_instance int

#define ZEGO_EXPRESS_MAX_COMMON_LEN (512)
#define ZEGO_EXPRESS_MAX_APPSIGN_LEN (64)
#define ZEGO_EXPRESS_MAX_USERID_LEN (64)
#define ZEGO_EXPRESS_MAX_USERNAME_LEN (256)
#define ZEGO_EXPRESS_MAX_ROOMID_LEN (128)
#define ZEGO_EXPRESS_MAX_TOKEN_LEN (512)
#define ZEGO_EXPRESS_MAX_MIX_INPUT_COUNT (12)
#define ZEGO_EXPRESS_MAX_STREAM_LEN (256)
#define ZEGO_EXPRESS_MAX_MIXER_TASK_LEN (256)
#define ZEGO_EXPRESS_MAX_EXTRA_INFO_LEN (1024)
#define ZEGO_EXPRESS_MAX_DEVICE_ID_LEN (256)
#define ZEGO_EXPRESS_MAX_URL_COUNT (10)
#define ZEGO_EXPRESS_MAX_URL_LEN (1024)
#define ZEGO_EXPRESS_MAX_IMAGE_PATH (512)
#define ZEGO_EXPRESS_MAX_MESSAGE_LEN (10240)
#define ZEGO_EXPRESS_MAX_CUSTOM_CMD_LEN (1024)
#define ZEGO_EXPRESS_MAX_REAL_TIME_SEQUENTIAL_DATA_LEN (4096)
#define ZEGO_EXPRESS_MAX_MEDIAPLAYER_INSTANCE_COUNT (4)
#define ZEGO_EXPRESS_MAX_CAMERA_CAPTURE_INSTANCE_COUNT (1)
#define ZEGO_EXPRESS_MAX_MEDIA_RECORD_TASK_ID_LEN (64)
#define ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_KEY_LEN (128)
#define ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_VALUE_LEN (4096)
#define ZEGO_EXPRESS_MAX_ROOM_TOKEN_VALUE_LEN (2048)

/// Application scenario.
enum zego_scenario {
    /// General scenario
    zego_scenario_general = 0,

    /// Communication scenario
    zego_scenario_communication = 1,

    /// Live scenario
    zego_scenario_live = 2

};

/// Language.
enum zego_language {
    /// English
    zego_language_english = 0,

    /// Chinese
    zego_language_chinese = 1

};

/// Room mode.
enum zego_room_mode {
    /// Single room mode.
    zego_room_mode_single_room = 0,

    /// Multiple room mode.
    zego_room_mode_multi_room = 1

};

/// engine state.
enum zego_engine_state {
    /// The engine has started
    zego_engine_state_start = 0,

    /// The engine has stoped
    zego_engine_state_stop = 1

};

/// Room state.
enum zego_room_state {
    /// Unconnected state, enter this state before logging in and after exiting the room. If there is a steady state abnormality in the process of logging in to the room, such as AppID or Token are incorrect, or if the same user name is logged in elsewhere and the local end is KickOut, it will enter this state.
    zego_room_state_disconnected = 0,

    /// The state that the connection is being requested. It will enter this state after successful execution login room function. The display of the UI is usually performed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting connection status.
    zego_room_state_connecting = 1,

    /// The status that is successfully connected. Entering this status indicates that the login to the room has been successful. The user can receive the callback notification of the user and the stream information in the room.
    zego_room_state_connected = 2

};

/// Room state change reason.
enum zego_room_state_changed_reason {
    /// Logging in to the room. When calling [loginRoom] to log in to the room or [switchRoom] to switch to the target room, it will enter this state, indicating that it is requesting to connect to the server. The application interface is usually displayed through this state.
    zego_room_state_changed_reason_logining = 0,

    /// Log in to the room successfully. When the room is successfully logged in or switched, it will enter this state, indicating that the login to the room has been successful, and users can normally receive callback notifications of other users in the room and all stream information additions and deletions.
    zego_room_state_changed_reason_logined = 1,

    /// Failed to log in to the room. When the login or switch room fails, it will enter this state, indicating that the login or switch room has failed, for example, AppID or Token is incorrect, etc.
    zego_room_state_changed_reason_login_failed = 2,

    /// The room connection is temporarily interrupted. If the interruption occurs due to poor network quality, the SDK will retry internally.
    zego_room_state_changed_reason_reconnecting = 3,

    /// The room is successfully reconnected. If there is an interruption due to poor network quality, the SDK will retry internally, and enter this state after successful reconnection.
    zego_room_state_changed_reason_reconnected = 4,

    /// The room fails to reconnect. If there is an interruption due to poor network quality, the SDK will retry internally, and enter this state after the reconnection fails.
    zego_room_state_changed_reason_reconnect_failed = 5,

    /// Kicked out of the room by the server. For example, if you log in to the room with the same user name in other places, and the local end is kicked out of the room, it will enter this state.
    zego_room_state_changed_reason_kick_out = 6,

    /// Logout of the room is successful. It is in this state by default before logging into the room. When calling [logoutRoom] to log out of the room successfully or [switchRoom] to log out of the current room successfully, it will enter this state.
    zego_room_state_changed_reason_logout = 7,

    /// Failed to log out of the room. Enter this state when calling [logoutRoom] fails to log out of the room or [switchRoom] fails to log out of the current room internally.
    zego_room_state_changed_reason_logout_failed = 8

};

/// Publish channel.
enum zego_publish_channel {
    /// The main (default/first) publish channel.
    zego_publish_channel_main = 0,

    /// The auxiliary (second) publish channel
    zego_publish_channel_aux = 1,

    /// The third publish channel
    zego_publish_channel_third = 2,

    /// The fourth publish channel
    zego_publish_channel_fourth = 3

};

/// Publish CensorshipMode.
enum zego_stream_censorship_mode {
    /// no censorship.
    zego_stream_censorship_mode_none = 0,

    /// only censorship stream audio.
    zego_stream_censorship_mode_audio = 1,

    /// only censorship stream video.
    zego_stream_censorship_mode_video = 2,

    /// censorship stream audio and video.
    zego_stream_censorship_mode_audio_and_video = 3

};

/// Video rendering fill mode.
enum zego_view_mode {
    /// The proportional scaling up, there may be black borders
    zego_view_mode_aspect_fit = 0,

    /// The proportional zoom fills the entire View and may be partially cut
    zego_view_mode_aspect_fill = 1,

    /// Fill the entire view, the image may be stretched
    zego_view_mode_scale_to_fill = 2

};

/// Mirror mode for previewing or playing the of the stream.
enum zego_video_mirror_mode {
    /// The mirror image only for previewing locally. This mode is used by default.
    zego_video_mirror_mode_only_preview_mirror = 0,

    /// Both the video previewed locally and the far end playing the stream will see mirror image.
    zego_video_mirror_mode_both_mirror = 1,

    /// Both the video previewed locally and the far end playing the stream will not see mirror image.
    zego_video_mirror_mode_no_mirror = 2,

    /// The mirror image only for far end playing the stream.
    zego_video_mirror_mode_only_publish_mirror = 3

};

/// SEI type
enum zego_sei_type {
    /// Using H.264 SEI (nalu type = 6, payload type = 243) type packaging, this type is not specified by the SEI standard, there is no conflict with the video encoder or the SEI in the video file, users do not need to follow the SEI content Do filtering, SDK uses this type by default.
    zego_sei_type_zego_defined = 0,

    /// SEI (nalu type = 6, payload type = 5) of H.264 is used for packaging. The H.264 standard has a prescribed format for this type: startcode + nalu type (6) + payload type (5) + len + payload (uuid + content) + trailing bits. Because the video encoder itself generates an SEI with a payload type of 5, or when a video file is used for streaming, such SEI may also exist in the video file, so when using this type, the user needs to use uuid + context as a buffer sending SEI. At this time, in order to distinguish the SEI generated by the video encoder itself, when the App sends this type of SEI, it can fill in the service-specific uuid (uuid length is 16 bytes). When the receiver uses the SDK to parse the SEI of the payload type 5, it will set filter string filters out the SEI matching the uuid and throws it to the business. If the filter string is not set, the SDK will throw all received SEI to the developer. uuid filter string setting function, [ZegoEngineConfig.advancedConfig("unregister_sei_filter","XXXXXX")], where unregister_sei_filter is the key, and XXXXX is the uuid filter string to be set.
    zego_sei_type_user_unregister = 1

};

/// Publish stream status.
enum zego_publisher_state {
    /// The state is not published, and it is in this state before publishing the stream. If a steady-state exception occurs in the publish process, such as AppID or Token are incorrect, or if other users are already publishing the stream, there will be a failure and enter this state.
    zego_publisher_state_no_publish = 0,

    /// The state that it is requesting to publish the stream after the [startPublishingStream] function is successfully called. The UI is usually displayed through this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state.
    zego_publisher_state_publish_requesting = 1,

    /// The state that the stream is being published, entering the state indicates that the stream has been successfully published, and the user can communicate normally.
    zego_publisher_state_publishing = 2

};

/// Voice changer preset value.
enum zego_voice_changer_preset {
    /// No Voice changer
    zego_voice_changer_preset_none = 0,

    /// Male to child voice (loli voice effect)
    zego_voice_changer_preset_men_to_child = 1,

    /// Male to female voice (kindergarten voice effect)
    zego_voice_changer_preset_men_to_women = 2,

    /// Female to child voice
    zego_voice_changer_preset_women_to_child = 3,

    /// Female to male voice
    zego_voice_changer_preset_women_to_men = 4,

    /// Foreigner voice effect
    zego_voice_changer_preset_foreigner = 5,

    /// Autobot Optimus Prime voice effect
    zego_voice_changer_preset_optimus_prime = 6,

    /// Android robot voice effect
    zego_voice_changer_preset_android = 7,

    /// Ethereal voice effect
    zego_voice_changer_preset_ethereal = 8,

    /// Magnetic(Male) voice effect
    zego_voice_changer_preset_male_magnetic = 9,

    /// Fresh(Female) voice effect
    zego_voice_changer_preset_female_fresh = 10,

    /// Electronic effects in C major voice effect
    zego_voice_changer_preset_major_c = 11,

    /// Electronic effects in A minor voice effect
    zego_voice_changer_preset_minor_a = 12,

    /// Electronic effects in harmonic minor voice effect
    zego_voice_changer_preset_harmonic_minor = 13

};

/// Reverberation preset value.
enum zego_reverb_preset {
    /// No Reverberation
    zego_reverb_preset_none = 0,

    /// Soft room reverb effect
    zego_reverb_preset_soft_room = 1,

    /// Large room reverb effect
    zego_reverb_preset_large_room = 2,

    /// Concert hall reverb effect
    zego_reverb_preset_concert_hall = 3,

    /// Valley reverb effect
    zego_reverb_preset_valley = 4,

    /// Recording studio reverb effect
    zego_reverb_preset_recording_studio = 5,

    /// Basement reverb effect
    zego_reverb_preset_basement = 6,

    /// KTV reverb effect
    zego_reverb_preset_ktv = 7,

    /// Popular reverb effect
    zego_reverb_preset_popular = 8,

    /// Rock reverb effect
    zego_reverb_preset_rock = 9,

    /// Vocal concert reverb effect
    zego_reverb_preset_vocal_concert = 10,

    /// Gramophone reverb effect
    zego_reverb_preset_gramo_phone = 11

};

/// Mode of Electronic Effects.
enum zego_electronic_effects_mode {
    /// Major
    zego_electronic_effects_mode_major = 0,

    /// Minor
    zego_electronic_effects_mode_minor = 1,

    /// Harmonic Minor
    zego_electronic_effects_mode_harmonic_minor = 2

};

/// Stream quality level.
enum zego_stream_quality_level {
    /// Excellent
    zego_stream_quality_level_excellent = 0,

    /// Good
    zego_stream_quality_level_good = 1,

    /// Normal
    zego_stream_quality_level_medium = 2,

    /// Bad
    zego_stream_quality_level_bad = 3,

    /// Failed
    zego_stream_quality_level_die = 4,

    /// Unknown
    zego_stream_quality_level_unknown = 5

};

/// Audio channel type.
enum zego_audio_channel {
    /// Unknown
    zego_audio_channel_unknown = 0,

    /// Mono
    zego_audio_channel_mono = 1,

    /// Stereo
    zego_audio_channel_stereo = 2

};

/// Audio capture stereo mode.
enum zego_audio_capture_stereo_mode {
    /// Disable stereo capture, that is, mono.
    zego_audio_capture_stereo_mode_none = 0,

    /// Always enable stereo capture.
    zego_audio_capture_stereo_mode_always = 1,

    /// [This mode is deprecated] Same as 'Always', that is, always enable stereo capture.
    zego_audio_capture_stereo_mode_adaptive = 2

};

/// Audio mix mode.
enum zego_audio_mix_mode {
    /// Default mode, no special behavior
    zego_audio_mix_mode_raw = 0,

    /// Audio focus mode, which can highlight the sound of a certain stream in multiple audio streams
    zego_audio_mix_mode_focused = 1

};

/// Audio Codec ID.
enum zego_audio_codec_id {
    /// default
    zego_audio_codec_id_default = 0,

    /// Normal
    zego_audio_codec_id_normal = 1,

    /// Normal2
    zego_audio_codec_id_normal2 = 2,

    /// Normal3
    zego_audio_codec_id_normal3 = 3,

    /// Low
    zego_audio_codec_id_low = 4,

    /// Low2
    zego_audio_codec_id_low2 = 5,

    /// Low3
    zego_audio_codec_id_low3 = 6

};

/// Video codec ID.
enum zego_video_codec_id {
    /// Default (H.264)
    zego_video_codec_id_default = 0,

    /// Scalable Video Coding (H.264 SVC)
    zego_video_codec_id_svc = 1,

    /// VP8
    zego_video_codec_id_vp8 = 2,

    /// H.265
    zego_video_codec_id_h265 = 3,

    /// Unknown Video Coding
    zego_video_codec_id_unknown = 100

};

/// Video screen rotation direction.
enum zego_orientation {
    /// Not rotate
    zego_orientation_0 = 0,

    /// Rotate 90 degrees counterclockwise
    zego_orientation_90 = 1,

    /// Rotate 180 degrees counterclockwise
    zego_orientation_180 = 2,

    /// Rotate 270 degrees counterclockwise
    zego_orientation_270 = 3

};

/// Player video layer.
enum zego_player_video_layer {
    /// The layer to be played depends on the network status
    zego_player_video_layer_auto = 0,

    /// Play the base layer (small resolution)
    zego_player_video_layer_base = 1,

    /// Play the extend layer (big resolution)
    zego_player_video_layer_base_extend = 2

};

/// Video stream type
enum zego_video_stream_type {
    /// The type to be played depends on the network status
    zego_video_stream_type_default = 0,

    /// small resolution type
    zego_video_stream_type_small = 1,

    /// big resolution type
    zego_video_stream_type_big = 2

};

/// Audio echo cancellation mode.
enum zego_aec_mode {
    /// Aggressive echo cancellation may affect the sound quality slightly, but the echo will be very clean.
    zego_aec_mode_aggressive = 0,

    /// Moderate echo cancellation, which may slightly affect a little bit of sound, but the residual echo will be less.
    zego_aec_mode_medium = 1,

    /// Comfortable echo cancellation, that is, echo cancellation does not affect the sound quality of the sound, and sometimes there may be a little echo, but it will not affect the normal listening.
    zego_aec_mode_soft = 2

};

/// Active Noise Suppression mode.
enum zego_ans_mode {
    /// Soft ANS. In most instances, the sound quality will not be damaged, but some noise will remain.
    zego_ans_mode_soft = 0,

    /// Medium ANS. It may damage some sound quality, but it has a good noise reduction effect.
    zego_ans_mode_medium = 1,

    /// Aggressive ANS. It may significantly impair the sound quality, but it has a good noise reduction effect.
    zego_ans_mode_aggressive = 2,

    /// AI mode ANS. It will cause great damage to music, so it can not be used for noise suppression of sound sources that need to collect background sound. Please contact ZEGO technical support before use.
    zego_ans_mode_ai = 3

};

/// video encode profile.
enum zego_encode_profile {
    /// The default video encode specifications, The default value is the video encoding specification at the Main level.
    zego_encode_profile_default = 0,

    /// Baseline-level video encode specifications have low decoding consumption and poor picture effects. They are generally used for low-level applications or applications that require additional fault tolerance.
    zego_encode_profile_baseline = 1,

    /// Main-level video encode specifications, decoding consumption is slightly higher than Baseline, the picture effect is also better, generally used in mainstream consumer electronic products.
    zego_encode_profile_main = 2,

    /// High-level video encode specifications, decoding consumption is higher than Main, the picture effect is better, generally used for broadcasting and video disc storage, high-definition TV.
    zego_encode_profile_high = 3

};

/// Stream alignment mode.
enum zego_stream_alignment_mode {
    /// Disable stream alignment.
    zego_stream_alignment_mode_none = 0,

    /// Streams should be aligned as much as possible, call the [setStreamAlignmentProperty] function to enable the stream alignment of the push stream network time alignment of the specified channel.
    zego_stream_alignment_mode_try = 1

};

/// Traffic control property (bitmask enumeration).
enum zego_traffic_control_property {
    /// Basic (Adaptive (reduce) video bitrate)
    zego_traffic_control_property_basic = 0,

    /// Adaptive (reduce) video FPS
    zego_traffic_control_property_adaptive_fps = 1,

    /// Adaptive (reduce) video resolution
    zego_traffic_control_property_adaptive_resolution = 1 << 1,

    /// Adaptive (reduce) audio bitrate
    zego_traffic_control_property_adaptive_audio_bitrate = 1 << 2

};

/// Video transmission mode when current bitrate is lower than the set minimum bitrate.
enum zego_traffic_control_min_video_bitrate_mode {
    /// Stop video transmission when current bitrate is lower than the set minimum bitrate
    zego_traffic_control_min_video_bitrate_mode_no_video = 0,

    /// Video is sent at a very low frequency (no more than 2fps) which is lower than the set minimum bitrate
    zego_traffic_control_min_video_bitrate_mode_ultra_low_fps = 1

};

/// Factors that trigger traffic control
enum zego_traffic_control_focus_on_mode {
    /// Focus only on the local network
    zego_traffic_control_founs_on_local_only = 0,

    /// Pay attention to the local network, but also take into account the remote network, currently only effective in the 1v1 scenario
    zego_traffic_control_founs_on_remote = 1

};

/// Playing stream status.
enum zego_player_state {
    /// The state of the flow is not played, and it is in this state before the stream is played. If the steady flow anomaly occurs during the playing process, such as AppID or Token are incorrect, it will enter this state.
    zego_player_state_no_play = 0,

    /// The state that the stream is being requested for playing. After the [startPlayingStream] function is successfully called, it will enter the state. The UI is usually displayed through this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state.
    zego_player_state_play_requesting = 1,

    /// The state that the stream is being playing, entering the state indicates that the stream has been successfully played, and the user can communicate normally.
    zego_player_state_playing = 2

};

/// Media event when playing.
enum zego_player_media_event {
    /// Audio stuck event when playing
    zego_player_media_event_audio_break_occur = 0,

    /// Audio stuck event recovery when playing
    zego_player_media_event_audio_break_resume = 1,

    /// Video stuck event when playing
    zego_player_media_event_video_break_occur = 2,

    /// Video stuck event recovery when playing
    zego_player_media_event_video_break_resume = 3

};

/// Resource Type.
enum zego_resource_type {
    /// CDN
    zego_resource_type_cdn = 0,

    /// RTC
    zego_resource_type_rtc = 1,

    /// L3
    zego_resource_type_l3 = 2

};

/// Stream Resource Mode
enum zego_stream_resource_mode {
    /// Default mode. The SDK will automatically select the streaming resource according to the cdnConfig parameters set by the player config and the ready-made background configuration.
    zego_stream_resource_mode_default = 0,

    /// Playing stream only from CDN.
    zego_stream_resource_mode_only_cdn = 1,

    /// Playing stream only from L3.
    zego_stream_resource_mode_only_l3 = 2,

    /// Playing stream only from RTC.
    zego_stream_resource_mode_only_rtc = 3

};

/// Update type.
enum zego_update_type {
    /// Add
    zego_update_type_add = 0,

    /// Delete
    zego_update_type_delete = 1

};

/// State of CDN relay.
enum zego_stream_relay_cdn_state {
    /// The state indicates that there is no CDN relay
    zego_stream_relay_cdn_state_no_relay = 0,

    /// The CDN relay is being requested
    zego_stream_relay_cdn_state_relay_requesting = 1,

    /// Entering this status indicates that the CDN relay has been successful
    zego_stream_relay_cdn_state_relaying = 2

};

/// Reason for state of CDN relay changed.
enum zego_stream_relay_cdn_update_reason {
    /// No error
    zego_stream_relay_cdn_update_reason_none = 0,

    /// Server error
    zego_stream_relay_cdn_update_reason_server_error = 1,

    /// Handshake error
    zego_stream_relay_cdn_update_reason_handshake_failed = 2,

    /// Access point error
    zego_stream_relay_cdn_update_reason_access_point_error = 3,

    /// Stream create failure
    zego_stream_relay_cdn_update_reason_create_stream_failed = 4,

    /// Bad stream ID
    zego_stream_relay_cdn_update_reason_bad_name = 5,

    /// CDN server actively disconnected
    zego_stream_relay_cdn_update_reason_cdn_server_disconnected = 6,

    /// Active disconnect
    zego_stream_relay_cdn_update_reason_disconnected = 7,

    /// All mixer input streams sessions closed
    zego_stream_relay_cdn_update_reason_mix_stream_all_input_stream_closed = 8,

    /// All mixer input streams have no data
    zego_stream_relay_cdn_update_reason_mix_stream_all_input_stream_no_data = 9,

    /// Internal error of stream mixer server
    zego_stream_relay_cdn_update_reason_mix_stream_server_internal_error = 10

};

/// Beauty feature (bitmask enumeration).
enum zego_beautify_feature {
    /// No beautifying
    zego_beautify_feature_none = 0,

    /// Polish
    zego_beautify_feature_polish = 1 << 0,

    /// Sharpen
    zego_beautify_feature_whiten = 1 << 1,

    /// Skin whiten
    zego_beautify_feature_skin_whiten = 1 << 2,

    /// Whiten
    zego_beautify_feature_sharpen = 1 << 3

};

/// Device type.
enum zego_device_type {
    /// Unknown device type.
    zego_device_type_unknown = 0,

    /// Camera device.
    zego_device_type_camera = 1,

    /// Microphone device.
    zego_device_type_microphone = 2,

    /// Speaker device.
    zego_device_type_speaker = 3,

    /// Audio device. (Other audio device that cannot be accurately classified into microphones or speakers.)
    zego_device_type_audio_device = 4

};

/// The exception type for the device.
enum zego_device_exception_type {
    /// Unknown device exception.
    zego_device_exception_type_unknown = 0,

    /// Generic device exception.
    zego_device_exception_type_generic = 1,

    /// Invalid device ID exception.
    zego_device_exception_type_invalid_id = 2,

    /// Device permission is not granted.
    zego_device_exception_type_permission_not_granted = 3,

    /// The capture frame rate of the device is 0.
    zego_device_exception_type_zero_capture_fps = 4,

    /// The device is being occupied.
    zego_device_exception_type_device_occupied = 5,

    /// The device is unplugged (not plugged in).
    zego_device_exception_type_device_unplugged = 6,

    /// The device requires the system to restart before it can work (Windows platform only).
    zego_device_exception_type_reboot_required = 7,

    /// The system media service is unavailable, e.g. when the iOS system detects that the current pressure is huge (such as playing a lot of animation), it is possible to disable all media related services (Apple platform only).
    zego_device_exception_type_media_services_were_lost = 8,

    /// The device is being occupied by Siri (Apple platform only).
    zego_device_exception_type_siri_is_recording = 9,

    /// The device captured sound level is too low (Windows platform only).
    zego_device_exception_type_sound_level_too_low = 10,

    /// The device is being occupied, and maybe cause by iPad magnetic case (Apple platform only).
    zego_device_exception_type_magnetic_case = 11

};

/// Remote device status.
enum zego_remote_device_state {
    /// Device on
    zego_remote_device_state_open = 0,

    /// General device error
    zego_remote_device_state_generic_error = 1,

    /// Invalid device ID
    zego_remote_device_state_invalid_id = 2,

    /// No permission
    zego_remote_device_state_no_authorization = 3,

    /// Captured frame rate is 0
    zego_remote_device_state_zero_fps = 4,

    /// The device is occupied
    zego_remote_device_state_in_use_by_other = 5,

    /// The device is not plugged in or unplugged
    zego_remote_device_state_unplugged = 6,

    /// The system needs to be restarted
    zego_remote_device_state_reboot_required = 7,

    /// System media services stop, such as under the iOS platform, when the system detects that the current pressure is huge (such as playing a lot of animation), it is possible to disable all media related services.
    zego_remote_device_state_system_media_services_lost = 8,

    /// Capturing disabled
    zego_remote_device_state_disable = 9,

    /// The remote device is muted
    zego_remote_device_state_mute = 10,

    /// The device is interrupted, such as a phone call interruption, etc.
    zego_remote_device_state_interruption = 11,

    /// There are multiple apps at the same time in the foreground, such as the iPad app split screen, the system will prohibit all apps from using the camera.
    zego_remote_device_state_in_background = 12,

    /// CDN server actively disconnected
    zego_remote_device_state_multi_foreground_app = 13,

    /// The system is under high load pressure and may cause abnormal equipment.
    zego_remote_device_state_by_system_pressure = 14,

    /// The remote device is not supported to publish the device state.
    zego_remote_device_state_not_support = 15

};

/// Audio device type.
enum zego_audio_device_type {
    /// Audio input type
    zego_audio_device_type_input = 0,

    /// Audio output type
    zego_audio_device_type_output = 1

};

/// Audio route
enum zego_audio_route {
    /// Speaker
    zego_audio_route_speaker = 0,

    /// Headphone
    zego_audio_route_headphone = 1,

    /// Bluetooth device
    zego_audio_route_bluetooth = 2,

    /// Receiver
    zego_audio_route_receiver = 3,

    /// External USB audio device
    zego_audio_route_external_usb = 4,

    /// Apple AirPlay
    zego_audio_route_air_play = 5

};

/// Mix stream content type.
enum zego_mixer_input_content_type {
    /// Mix stream for audio only
    zego_mixer_input_content_type_audio = 0,

    /// Mix stream for both audio and video
    zego_mixer_input_content_type_video = 1,

    /// Mix stream for video only
    zego_mixer_input_content_type_video_only = 2

};

/// Capture pipeline scale mode.
enum zego_capture_pipeline_scale_mode {
    /// Zoom immediately after acquisition, default
    zego_capture_pipeline_scale_mode_pre = 0,

    /// Scaling while encoding
    zego_capture_pipeline_scale_mode_post = 1

};

/// Video frame format.
enum zego_video_frame_format {
    /// Unknown format, will take platform default
    zego_video_frame_format_unknown = 0,

    /// I420 (YUV420Planar) format
    zego_video_frame_format_i420 = 1,

    /// NV12 (YUV420SemiPlanar) format
    zego_video_frame_format_nv12 = 2,

    /// NV21 (YUV420SemiPlanar) format
    zego_video_frame_format_nv21 = 3,

    /// BGRA32 format
    zego_video_frame_format_bgra32 = 4,

    /// RGBA32 format
    zego_video_frame_format_rgba32 = 5,

    /// ARGB32 format
    zego_video_frame_format_argb32 = 6,

    /// ABGR32 format
    zego_video_frame_format_abgr32 = 7,

    /// I422 (YUV422Planar) format
    zego_video_frame_format_i422 = 8

};

/// Video encoded frame format.
enum zego_video_encoded_frame_format {
    /// AVC AVCC format
    zego_video_encoded_frame_format_avc_avcc = 0,

    /// AVC Annex-B format
    zego_video_encoded_frame_format_avc_annexb = 1

};

/// Video frame buffer type.
enum zego_video_buffer_type {
    /// Raw data type video frame
    zego_video_buffer_type_unknown = 0,

    /// Raw data type video frame
    zego_video_buffer_type_raw_data = 1,

    /// Encoded data type video frame
    zego_video_buffer_type_encoded_data = 2,

    /// Texture 2D type video frame
    zego_video_buffer_type_gl_texture_2d = 3,

    /// CVPixelBuffer type video frame
    zego_video_buffer_type_cv_pixel_buffer = 4,

    /// Surface Texture type video frame
    zego_video_buffer_type_surface_texture = 5,

    /// GL_TEXTURE_EXTERNAL_OES type video frame
    zego_video_buffer_type_gl_texture_external_oes = 6

};

/// Video frame format series.
enum zego_video_frame_format_series {
    /// RGB series
    zego_video_frame_format_series_rgb = 0,

    /// YUV series
    zego_video_frame_format_series_yuv = 1

};

/// Video frame flip mode.
enum zego_video_flip_mode {
    /// No flip
    zego_video_flip_mode_none = 0,

    /// X-axis flip
    zego_video_flip_mode_x = 1,

    /// Y-axis flip
    zego_video_flip_mode_y = 2,

    /// X-Y-axis flip
    zego_video_flip_mode_xy = 3

};

/// Customize the audio processing configuration type.
enum zego_custom_audio_process_type {
    /// Remote audio processing
    zego_custom_audio_process_type_remote = 0,

    /// Capture audio processing
    zego_custom_audio_process_type_capture = 1,

    /// Remote audio and capture audio processing
    zego_custom_audio_process_type_capture_and_remote = 2

};

/// Range audio mode
enum zego_range_audio_mode {
    /// World mode, you can communicate with everyone in the room.
    zego_range_audio_mode_world = 0,

    /// Team mode, only communicate with members of the team.
    zego_range_audio_mode_team = 1,

    /// Secret team mode, communicate with members of the team, can hear the voices of members who are in the world mode and are within the audio receive range.
    zego_range_audio_mode_secret_team = 2

};

/// Range audio microphone state.
enum zego_range_audio_microphone_state {
    /// The range audio microphone is off.
    zego_range_audio_microphone_state_off = 0,

    /// The range audio microphone is turning on.
    zego_range_audio_microphone_state_turning_on = 1,

    /// The range audio microphone is on.
    zego_range_audio_microphone_state_on = 2

};

/// Player state.
enum zego_media_player_state {
    /// Not playing
    zego_media_player_state_no_play = 0,

    /// Playing
    zego_media_player_state_playing = 1,

    /// Pausing
    zego_media_player_state_pausing = 2,

    /// End of play
    zego_media_player_state_play_ended = 3

};

/// Player network event.
enum zego_media_player_network_event {
    /// Network resources are not playing well, and start trying to cache data
    zego_media_player_network_event_buffer_begin = 0,

    /// Network resources can be played smoothly
    zego_media_player_network_event_buffer_ended = 1

};

/// Audio channel.
enum zego_media_player_audio_channel {
    /// Audio channel left
    zego_media_player_audio_channel_left = 0,

    /// Audio channel right
    zego_media_player_audio_channel_right = 1,

    /// Audio channel all
    zego_media_player_audio_channel_all = 2

};

/// AudioEffectPlayer state.
enum zego_audio_effect_play_state {
    /// Not playing
    zego_audio_effect_play_state_no_play = 0,

    /// Playing
    zego_audio_effect_play_state_playing = 1,

    /// Pausing
    zego_audio_effect_play_state_pausing = 2,

    /// End of play
    zego_audio_effect_play_state_play_ended = 3

};

/// volume type.
enum zego_volume_type {
    /// volume local
    zego_volume_type_local = 0,

    /// volume remote
    zego_volume_type_remote = 1

};

/// audio sample rate.
enum zego_audio_sample_rate {
    /// Unknown
    zego_audio_sample_rate_unknown = 0,

    /// 8K
    zego_audio_sample_rate_8k = 8000,

    /// 16K
    zego_audio_sample_rate_16k = 16000,

    /// 22.05K
    zego_audio_sample_rate_22k = 22050,

    /// 24K
    zego_audio_sample_rate_24k = 24000,

    /// 32K
    zego_audio_sample_rate_32k = 32000,

    /// 44.1K
    zego_audio_sample_rate_44k = 44100,

    /// 48K
    zego_audio_sample_rate_48k = 48000

};

/// Audio capture source type.
enum zego_audio_source_type {
    /// Default audio capture source (the main channel uses custom audio capture by default; the aux channel uses the same sound as main channel by default)
    zego_audio_source_type_default = 0,

    /// Use custom audio capture, refer to [enableCustomAudioIO]
    zego_audio_source_type_custom = 1,

    /// Use media player as audio source, only support aux channel
    zego_audio_source_type_media_player = 2

};

/// Record type.
enum zego_data_record_type {
    /// This field indicates that the Express-Audio SDK records audio by default, and the Express-Video SDK records audio and video by default. When recording files in .aac format, audio is also recorded by default.
    zego_data_record_type_default = 0,

    /// only record audio
    zego_data_record_type_only_audio = 1,

    /// only record video, Audio SDK and recording .aac format files are invalid.
    zego_data_record_type_only_video = 2,

    /// record audio and video. Express-Audio SDK and .aac format files are recorded only audio.
    zego_data_record_type_audio_and_video = 3

};

/// Record state.
enum zego_data_record_state {
    /// Unrecorded state, which is the state when a recording error occurs or before recording starts.
    zego_data_record_state_no_record = 0,

    /// Recording in progress, in this state after successfully call [startRecordingCapturedData] function
    zego_data_record_state_recording = 1,

    /// Record successs
    zego_data_record_state_success = 2

};

/// Audio data callback function enable bitmask enumeration.
enum zego_audio_data_callback_bit_mask {
    /// The mask bit of this field corresponds to the enable [onCapturedAudioData] callback function
    zego_audio_data_callback_bit_mask_captured = 1 << 0,

    /// The mask bit of this field corresponds to the enable [onPlaybackAudioData] callback function
    zego_audio_data_callback_bit_mask_playback = 1 << 1,

    /// The mask bit of this field corresponds to the enable [onMixedAudioData] callback function
    zego_audio_data_callback_bit_mask_mixed = 1 << 2,

    /// The mask bit of this field corresponds to the enable [onPlayerAudioData] callback function
    zego_audio_data_callback_bit_mask_player = 1 << 3

};

/// Network mode
enum zego_network_mode {
    /// Offline (No network)
    zego_network_mode_offline = 0,

    /// Unknown network mode
    zego_network_mode_unknown = 1,

    /// Wired Ethernet (LAN)
    zego_network_mode_ethernet = 2,

    /// Wi-Fi (WLAN)
    zego_network_mode_wifi = 3,

    /// 2G Network (GPRS/EDGE/CDMA1x/etc.)
    zego_network_mode_2g = 4,

    /// 3G Network (WCDMA/HSDPA/EVDO/etc.)
    zego_network_mode_3g = 5,

    /// 4G Network (LTE)
    zego_network_mode_4g = 6,

    /// 5G Network (NR (NSA/SA))
    zego_network_mode_5g = 7

};

/// network speed test type
enum zego_network_speed_test_type {
    /// uplink
    zego_network_speed_test_type_uplink = 0,

    /// downlink
    zego_network_speed_test_type_downlink = 1

};

/// Enumeration of iOS screen orientation.
enum zego_ios_orientation {
    /// Unknown value
    zego_ios_orientation_unknown = 0,

    /// Portrait
    zego_ios_orientation_portrait = 1,

    /// Portrait upsidedown
    zego_ios_orientation_portrait_upsidedown = 2,

    /// Landscape right
    zego_ios_orientation_landscape_right = 3,

    /// Landscape left
    zego_ios_orientation_landscape_left = 4

};

/// MediaPlayer instance index.
enum zego_media_player_instance_index {
    /// Unknown value
    zego_media_player_instance_index_null = -1,

    /// The first mediaplayer instance index
    zego_media_player_instance_index_first = 0,

    /// The second mediaplayer instance index
    zego_media_player_instance_index_second = 1,

    /// The third mediaplayer instance index
    zego_media_player_instance_index_third = 2,

    /// The forth mediaplayer instance index
    zego_media_player_instance_index_forth = 3

};

/// AudioEffectPlayer instance index.
enum zego_audio_effect_player_instance_index {
    /// Unknown value
    zego_audio_effect_player_instance_index_null = -1,

    /// The first AudioEffectPlayer instance index
    zego_audio_effect_player_instance_index_first = 0

};

/// RangeAudio instance index.
enum zego_range_audio_instance_index {
    /// Unknown value
    zego_range_audio_instance_index_null = -1,

    /// The first RangeAudio instance index
    zego_range_audio_instance_index_first = 0

};

/// Platform language.
enum zego_platform_language {
    /// C language.
    zego_platform_language_c = 0,

    /// Objective-C language.
    zego_platform_language_oc = 1,

    /// Java language.
    zego_platform_language_java = 2,

    /// Cpp language.
    zego_platform_language_cpp = 3,

    /// Dart language.
    zego_platform_language_dart = 4,

    /// JS language.
    zego_platform_language_js = 5,

    /// CS language.
    zego_platform_language_cs = 6

};

/// VOD billing mode.
enum zego_copyrighted_music_billing_mode {
    /// Pay-per-use.Each time a user obtains a song resource, a charge is required, that is, the user will be charged for each time based on the actual call to obtain the song resource interface (such as [requestSong], [requestAccompaniment], etc.).
    zego_copyrighted_music_billing_mode_count = 0,

    /// Monthly billing by user.Billing for a single user is based on the monthly dimension, that is, the statistics call to obtain song resources (such as [requestSong], [requestAccompaniment], etc.) and the parameters are the user ID of the monthly subscription, and the charging is based on the monthly dimension.
    zego_copyrighted_music_billing_mode_user = 1,

    /// Monthly billing by room.The room users are billed on a monthly basis, that is, statistical calls to obtain song resources (such as [requestSong], [requestAccompaniment], etc.) are passed as Roomid for a monthly subscription of the room, and fees are charged on a monthly basis.
    zego_copyrighted_music_billing_mode_room = 2

};

/// The music resource type.
enum zego_copyrighted_music_type {
    /// Song.
    zego_copyrighted_music_song = 0,

    /// Song with high quality.
    zego_copyrighted_music_song_hq = 1,

    /// Song with super quality.
    zego_copyrighted_music_song_sq = 2,

    /// Song accompaniment.
    zego_copyrighted_music_accompaniment = 3,

    /// Song accompaniment clip.
    zego_copyrighted_music_accompaniment_clip = 4

};

/// Font type.
enum zego_font_type {
    /// Source han sans.
    zego_font_type_source_han_sans = 0,

    /// Alibaba sans.
    zego_font_type_alibaba_sans = 1,

    /// Pang men zheng dao title.
    zego_font_type_pang_men_zheng_dao_title = 2,

    /// HappyZcool.
    zego_font_type_happy_zcool = 3

};

/// Mixing stream video view render mode.
enum zego_mix_render_mode {
    /// The proportional zoom fills the entire area and may be partially cut.
    zego_mix_render_mode_fill = 0,

    /// Scale the filled area proportionally. If the scale does not match the set size after scaling, the extra part will be displayed as transparent.
    zego_mix_render_mode_fit = 1

};

/// Camera focus mode.
enum zego_camera_focus_mode {
    /// Auto focus.
    zego_camera_focus_mode_auto_focus = 0,

    /// Continuous auto focus.
    zego_camera_focus_mode_continuous_auto_focus = 1

};

/// Camera exposure mode.
enum zego_camera_exposure_mode {
    /// Auto exposure.
    zego_camera_exposure_mode_auto_exposure = 0,

    /// Continuous auto exposure.
    zego_camera_exposure_mode_continuous_auto_exposure = 1

};

/// voice activity detection type
enum zego_audio_vad_type {
    /// noise
    zego_audio_vad_type_noise = 0,

    /// speech
    zego_audio_vad_type_speech = 1

};

/// stable voice activity detection type
enum zego_audio_vad_stable_state_monitor_type {
    /// captured
    zego_audio_vad_stable_state_monitor_type_captured = 0,

    /// custom processed
    zego_audio_vad_stable_state_monitor_type_custom_processed = 1

};

/// Orientation mode of the captured video.
enum zego_orientation_mode {
    /// Custom mode.
    zego_orientation_mode_custom = 0,

    /// Adaptive mode.
    zego_orientation_mode_adaptive = 1

};

/// CDN network protocol types supported by ZEGO
enum zego_cdn_protocol {
    /// TCP protocol
    zego_cdn_protocol_tcp = 1,

    /// QUIC protocol
    zego_cdn_protocol_quic = 2

};

/// Publish or play stream event
enum zego_stream_event {
    /// Start publishing stream
    zego_stream_event_publish_start = 100,

    /// The first publish stream was successful
    zego_stream_event_publish_success = 101,

    /// Failed to publish stream for the first time
    zego_stream_event_publish_fail = 102,

    /// Start retrying publishing stream
    zego_stream_event_retry_publish_start = 103,

    /// Retry publishing stream successfully
    zego_stream_event_retry_publish_success = 104,

    /// Failed to retry publishing stream
    zego_stream_event_retry_publish_fail = 105,

    /// End of publishing stream
    zego_stream_event_publish_end = 106,

    /// Start playing stream
    zego_stream_event_play_start = 200,

    /// The first play stream was successful
    zego_stream_event_play_success = 201,

    /// Failed to play stream for the first time
    zego_stream_event_play_fail = 202,

    /// Start retrying playing stream
    zego_stream_event_retry_play_start = 203,

    /// Retry playing stream successfully
    zego_stream_event_retry_play_success = 204,

    /// Failed to retry playing stream
    zego_stream_event_retry_play_fail = 205,

    /// End of playing stream
    zego_stream_event_play_end = 206

};

/// Log config.
///
/// Description: This parameter is required when calling [setlogconfig] to customize log configuration.
/// Use cases: This configuration is required when you need to customize the log storage path or the maximum log file size.
/// Caution: None.
struct zego_log_config {
    /// The storage path of the log file. Description: Used to customize the storage path of the log file. Use cases: This configuration is required when you need to customize the log storage path. Required: False. Default value: The default path of each platform is different, please refer to the official website document https://docs.zegocloud.com/faq/express_sdkLog. Caution: Developers need to ensure read and write permissions for files under this path.
    char log_path[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// Maximum log file size(Bytes). Description: Used to customize the maximum log file size. Use cases: This configuration is required when you need to customize the upper limit of the log file size. Required: False. Default value: 5MB (5 * 1024 * 1024 Bytes). Value range: Minimum 1MB (1 * 1024 * 1024 Bytes), maximum 100M (100 * 1024 * 1024 Bytes), 0 means no need to write logs. Caution: The larger the upper limit of the log file size, the more log information it carries, but the log upload time will be longer.
    unsigned long long log_size;
};

/// Custom video capture configuration.
///
/// Custom video capture, that is, the developer is responsible for collecting video data and sending the collected video data to SDK for video data encoding and publishing to the ZEGO RTC server. This feature is generally used by developers who use third-party beauty features or record game screen living.
/// When you need to use the custom video capture function, you need to set an instance of this class as a parameter to the [enableCustomVideoCapture] function.
/// Because when using custom video capture, SDK will no longer start the camera to capture video data. You need to collect video data from video sources by yourself.
struct zego_custom_video_capture_config {
    /// Custom video capture video frame data type
    enum zego_video_buffer_type buffer_type;
};

/// Custom video process configuration.
struct zego_custom_video_process_config {
    /// Custom video process video frame data type
    enum zego_video_buffer_type buffer_type;
};

/// Custom video render configuration.
///
/// When you need to use the custom video render function, you need to set an instance of this class as a parameter to the [enableCustomVideoRender] function.
struct zego_custom_video_render_config {
    /// Custom video capture video frame data type
    enum zego_video_buffer_type buffer_type;

    /// Custom video rendering video frame data format。Useless when set bufferType as [EncodedData]
    enum zego_video_frame_format_series frame_format_series;

    /// Whether the engine also renders while customizing video rendering. The default value is [false]. Useless when set bufferType as [EncodedData]
    bool enable_engine_render;
};

/// Custom audio configuration.
struct zego_custom_audio_config {
    /// Audio capture source type
    enum zego_audio_source_type source_type;
};

/// Profile for create engine
///
/// Profile for create engine
struct zego_engine_profile {
    /// Application ID issued by ZEGO for developers, please apply from the ZEGO Admin Console https://console.zegocloud.com The value ranges from 0 to 4294967295.
    unsigned int app_id;

    /// Application signature for each AppID, please apply from the ZEGO Admin Console. Application signature is a 64 character string. Each character has a range of '0' ~ '9', 'a' ~ 'z'. AppSign 2.17.0 and later allows null or no transmission. If the token is passed empty or not passed, the token must be entered in the [ZegoRoomConfig] parameter for authentication when the [loginRoom] interface is called to login to the room.
    char app_sign[ZEGO_EXPRESS_MAX_APPSIGN_LEN];

    /// The application scenario. Developers can choose one of ZegoScenario based on the scenario of the app they are developing, and the engine will preset a more general setting for specific scenarios based on the set scenario. After setting specific scenarios, developers can still call specific functions to set specific parameters if they have customized parameter settings.
    enum zego_scenario scenario;
};

/// Advanced engine configuration.
struct zego_engine_config {
    /// @deprecated This property has been deprecated since version 2.3.0, please use the [setLogConfig] function instead.
    struct zego_log_config *log_config;

    /// Other special function switches, if not set, no special function will be used by default. Please contact ZEGO technical support before use.
    char advanced_config[ZEGO_EXPRESS_MAX_COMMON_LEN];
};

/// Advanced room configuration.
///
/// Configure maximum number of users in the room and authentication token, etc.
struct zego_room_config {
    /// The maximum number of users in the room, Passing 0 means unlimited, the default is unlimited.
    unsigned int max_member_count;

    /// Whether to enable the user in and out of the room callback notification [onRoomUserUpdate], the default is off. If developers need to use ZEGO Room user notifications, make sure that each user who login sets this flag to true
    bool is_user_status_notify;

    /// The token issued by the developer's business server is used to ensure security. For the generation rules, please refer to [Using Token Authentication](https://doc-zh.zego.im/article/10360), the default is an empty string, that is, no authentication. In versions 2.17.0 and above, if appSign is not passed in when calling the [createEngine] API to create an engine, or if appSign is empty, this parameter must be set for authentication when logging in to a room.
    char token[ZEGO_EXPRESS_MAX_ROOM_TOKEN_VALUE_LEN];
};

/// Video config.
///
/// Configure parameters used for publishing stream, such as bitrate, frame rate, and resolution.
/// Developers should note that the width and height resolution of the mobile and desktop are opposite. For example, 360p, the resolution of the mobile is 360x640, and the desktop is 640x360.
struct zego_video_config {
    /// Capture resolution width, control the width of camera image acquisition. SDK requires this member to be set to an even number. Only the camera is not started and the custom video capture is not used, the setting is effective. For performance reasons, the SDK scales the video frame to the encoding resolution after capturing from camera and before rendering to the preview view. Therefore, the resolution of the preview image is the encoding resolution. If you need the resolution of the preview image to be this value, Please call [setCapturePipelineScaleMode] first to change the capture pipeline scale mode to [Post]
    int capture_width;

    /// Capture resolution height, control the height of camera image acquisition. SDK requires this member to be set to an even number. Only the camera is not started and the custom video capture is not used, the setting is effective. For performance reasons, the SDK scales the video frame to the encoding resolution after capturing from camera and before rendering to the preview view. Therefore, the resolution of the preview image is the encoding resolution. If you need the resolution of the preview image to be this value, Please call [setCapturePipelineScaleMode] first to change the capture pipeline scale mode to [Post]
    int capture_height;

    /// Encode resolution width, control the image width of the encoder when publishing stream. SDK requires this member to be set to an even number. The settings before and after publishing stream can be effective
    int encode_width;

    /// Encode resolution height, control the image height of the encoder when publishing stream. SDK requires this member to be set to an even number. The settings before and after publishing stream can be effective
    int encode_height;

    /// Frame rate, control the frame rate of the camera and the frame rate of the encoder. Only the camera is not started, the setting is effective. Publishing stream set to 60 fps, playing stream to take effect need contact technical support
    int fps;

    /// Bit rate in kbps. The settings before and after publishing stream can be effective
    int bitrate;

    /// The codec id to be used, the default value is [default]. Settings only take effect before publishing stream
    enum zego_video_codec_id codec_id;

    /// Video keyframe interval, in seconds. Required: No. Default value: 2 seconds. Value range: [2, 5]. Caution: The setting is only valid before pushing.
    int key_frame_interval;
};

/// Externally encoded data traffic control information.
struct zego_traffic_control_info {
    /// Video resolution width to be adjusted
    int width;

    /// Video resolution height to be adjusted
    int height;

    /// Video FPS to be adjusted
    int fps;

    /// Video bitrate in kbps to be adjusted
    int bitrate;
};

/// SEI configuration
///
/// Used to set the relevant configuration of the Supplemental Enhancement Information.
struct zego_sei_config {
    /// SEI type
    enum zego_sei_type type;
};

/// Audio reverberation parameters.
///
/// Developers can use the SDK's built-in presets to change the parameters of the reverb.
struct zego_reverb_param {
    /// Room size, in the range [0.0, 1.0], to control the size of the "room" in which the reverb is generated, the larger the room, the stronger the reverb.
    float room_size;

    /// Echo, in the range [0.0, 0.5], to control the trailing length of the reverb.
    float reverberance;

    /// Reverb Damping, range [0.0, 2.0], controls the attenuation of the reverb, the higher the damping, the higher the attenuation.
    float damping;

    /// Dry/wet ratio, the range is greater than or equal to 0.0, to control the ratio between reverberation, direct sound and early reflections; dry part is set to 1 by default; the smaller the dry/wet ratio, the larger the wet ratio, the stronger the reverberation effect.
    float dry_wet_ratio;
};

/// Audio reverberation advanced parameters.
///
/// Developers can use the SDK's built-in presets to change the parameters of the reverb.
struct zego_reverb_advanced_param {
    /// Room size(%), in the range [0.0, 1.0], to control the size of the "room" in which the reverb is generated, the larger the room, the stronger the reverb.
    float room_size;

    /// Echo(%), in the range [0.0, 100.0], to control the trailing length of the reverb.
    float reverberance;

    /// Reverb Damping(%), range [0.0, 100.0], controls the attenuation of the reverb, the higher the damping, the higher the attenuation.
    float damping;

    /// only wet
    bool wet_only;

    /// wet gain(dB), range [-20.0, 10.0]
    float wet_gain;

    /// dry gain(dB), range [-20.0, 10.0]
    float dry_gain;

    /// Tone Low. 100% by default
    float tone_low;

    /// Tone High. 100% by default
    float tone_high;

    /// PreDelay(ms), range [0.0, 200.0]
    float pre_delay;

    /// Stereo Width(%). 0% by default
    float stereo_width;
};

/// Audio reverberation echo parameters.
struct zego_reverb_echo_param {
    /// Gain of input audio signal, in the range [0.0, 1.0]
    float in_gain;

    /// Gain of output audio signal, in the range [0.0, 1.0]
    float out_gain;

    /// Number of echos, in the range [0, 7]
    int num_delays;

    /// Respective delay of echo signal, in milliseconds, in the range [0, 5000] ms
    int delay[7];

    /// Respective decay coefficient of echo signal, in the range [0.0, 1.0]
    float decay[7];
};

/// User object.
///
/// Configure user ID and username to identify users in the room.
/// Note that the userID must be unique under the same appID, otherwise mutual kicks out will occur.
/// It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
struct zego_user {
    /// User ID, a string with a maximum length of 64 bytes or less.Please do not fill in sensitive user information in this field, including but not limited to mobile phone number, ID number, passport number, real name, etc. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    char user_id[ZEGO_EXPRESS_MAX_USERID_LEN];

    /// User Name, a string with a maximum length of 256 bytes or less.Please do not fill in sensitive user information in this field, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    char user_name[ZEGO_EXPRESS_MAX_USERNAME_LEN];
};

/// Stream object.
///
/// Identify an stream object
struct zego_stream {
    /// User object instance.Please do not fill in sensitive user information in this field, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    struct zego_user user;

    /// Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /// Stream extra info
    char extra_info[ZEGO_EXPRESS_MAX_EXTRA_INFO_LEN];
};

/// Room extra information.
struct zego_room_extra_info {
    /// The key of the room extra information.
    char key[ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_KEY_LEN];

    /// The value of the room extra information.
    char value[ZEGO_EXPRESS_MAX_ROOM_EXTRA_INFO_VALUE_LEN];

    /// The user who update the room extra information.Please do not fill in sensitive user information in this field, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    struct zego_user update_user;

    /// Update time of the room extra information, UNIX timestamp, in milliseconds.
    unsigned long long update_time;
};

/// View related coordinates.
struct zego_rect {
    /// The value at the left of the horizontal axis of the rectangle
    int left;

    /// The value at the top of the vertical axis of the rectangle
    int top;

    /// The value at the right of the horizontal axis of the rectangle
    int right;

    /// The value at the bottom of the vertical axis of the rectangle
    int bottom;
};

/// Coordinates used by the ROI function.
struct zego_roi_rect {
    /// The horizontal offset from the top-left corner
    int x;

    /// The vertical offset from the top-left corner
    int y;

    /// The width of the rectangle
    int width;

    /// The height of the rectangle
    int height;

    /// ROI strength, currently supported value range is [0, 4], 0 is no effect, 4 is the strongest.
    int strength;
};

/// View object.
///
/// Configure view object, view Mode, background color
struct zego_canvas {
    /// View object
    void *view;

    /// View mode, default is ZegoViewModeAspectFit
    enum zego_view_mode view_mode;

    /// Background color, the format is 0xRRGGBB, default is black, which is 0x000000
    int background_color;
};

/// Advanced publisher configuration.
///
/// Configure room id
struct zego_publisher_config {
    /// The Room ID, It is not necessary to pass in single room mode, but the ID of the corresponding room must be passed in multi-room mode
    char room_id[ZEGO_EXPRESS_MAX_ROOMID_LEN];

    /// Whether to synchronize the network time when pushing streams. 1 is synchronized with 0 is not synchronized. And must be used with setStreamAlignmentProperty. It is used to align multiple streams at the mixed stream service or streaming end, such as the chorus scene of KTV.
    int force_synchronous_network_time;

    /// When pushing a flow, review the pattern of the flow. By default, no audit is performed. If you want to use this function, contact ZEGO technical support.
    enum zego_stream_censorship_mode stream_censorship_mode;
};

/// Published stream quality information.
///
/// Audio and video parameters and network quality, etc.
struct zego_publish_stream_quality {
    /// Video capture frame rate. The unit of frame rate is f/s
    double video_capture_fps;

    /// Video encoding frame rate. The unit of frame rate is f/s
    double video_encode_fps;

    /// Video transmission frame rate. The unit of frame rate is f/s
    double video_send_fps;

    /// Video bit rate in kbps
    double video_kbps;

    /// Audio capture frame rate. The unit of frame rate is f/s
    double audio_capture_fps;

    /// Audio transmission frame rate. The unit of frame rate is f/s
    double audio_send_fps;

    /// Audio bit rate in kbps
    double audio_kbps;

    /// Local to server delay, in milliseconds
    int rtt;

    /// Packet loss rate, in percentage, 0.0 ~ 1.0
    double packet_lost_rate;

    /// Published stream quality level
    enum zego_stream_quality_level level;

    /// Whether to enable hardware encoding
    bool is_hardware_encode;

    /// Video codec ID (Available since 1.17.0)
    enum zego_video_codec_id video_codec_id;

    /// Total number of bytes sent, including audio, video, SEI
    double total_send_bytes;

    /// Number of audio bytes sent
    double audio_send_bytes;

    /// Number of video bytes sent
    double video_send_bytes;
};

/// CDN config object.
///
/// Includes CDN URL and authentication parameter string
struct zego_cdn_config {
    /// CDN URL
    char url[ZEGO_EXPRESS_MAX_URL_LEN];

    /// Auth param of URL
    char auth_param[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// protocol supported by the URL. If there are more than one, separate them with English commas and try them in order.
    char protocol[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// QUIC version。 If [protocol] has the QUIC protocol, this information needs to be filled in. If there are multiple version numbers, separate them with commas.
    char quic_version[ZEGO_EXPRESS_MAX_COMMON_LEN];
};

/// Relay to CDN info.
///
/// Including the URL of the relaying CDN, relaying state, etc.
struct zego_stream_relay_cdn_info {
    /// URL of publishing stream to CDN
    char url[ZEGO_EXPRESS_MAX_URL_LEN];

    /// State of relaying to CDN
    enum zego_stream_relay_cdn_state state;

    /// Reason for relay state changed
    enum zego_stream_relay_cdn_update_reason update_reason;

    /// The timestamp when the state changed, UNIX timestamp, in milliseconds.
    unsigned long long state_time;
};

/// Advanced player configuration.
///
/// Configure playing stream CDN configuration, video layer, room id.
struct zego_player_config {
    /// Stream resource mode.
    enum zego_stream_resource_mode resource_mode;

    /// The CDN configuration for playing stream. If set, the stream is play according to the URL instead of the streamID. After that, the streamID is only used as the ID of SDK internal callback.
    struct zego_cdn_config *cdn_config;

    /// @deprecated This property has been deprecated since version 1.19.0, please use the [setPlayStreamVideoLayer] function instead.
    enum zego_player_video_layer video_layer;

    /// The Room ID.
    char room_id[ZEGO_EXPRESS_MAX_ROOMID_LEN];

    /// The video encoding type of the stream.
    enum zego_video_codec_id video_codec_id;

    /// The resource type of the source stream.
    enum zego_resource_type source_resource_type;
};

/// Played stream quality information.
///
/// Audio and video parameters and network quality, etc.
struct zego_play_stream_quality {
    /// Video receiving frame rate. The unit of frame rate is f/s
    double video_recv_fps;

    /// Video dejitter frame rate. The unit of frame rate is f/s (Available since 1.17.0)
    double video_dejitter_fps;

    /// Video decoding frame rate. The unit of frame rate is f/s
    double video_decode_fps;

    /// Video rendering frame rate. The unit of frame rate is f/s
    double video_render_fps;

    /// Video bit rate in kbps
    double video_kbps;

    /// Video break rate, the unit is (number of breaks / every 10 seconds) (Available since 1.17.0)
    double video_break_rate;

    /// Audio receiving frame rate. The unit of frame rate is f/s
    double audio_recv_fps;

    /// Audio dejitter frame rate. The unit of frame rate is f/s (Available since 1.17.0)
    double audio_dejitter_fps;

    /// Audio decoding frame rate. The unit of frame rate is f/s
    double audio_decode_fps;

    /// Audio rendering frame rate. The unit of frame rate is f/s
    double audio_render_fps;

    /// Audio bit rate in kbps
    double audio_kbps;

    /// Audio break rate, the unit is (number of breaks / every 10 seconds) (Available since 1.17.0)
    double audio_break_rate;

    /// The audio quality of the playing stream determined by the audio MOS (Mean Opinion Score) measurement method, value range [-1, 5], where -1 means unknown, [0, 5] means valid score, the higher the score, the better the audio quality. For the subjective perception corresponding to the MOS value, please refer to https://docs.zegocloud.com/article/3720#4_4 (Available since 2.16.0)
    double mos;

    /// Server to local delay, in milliseconds
    int rtt;

    /// Packet loss rate, in percentage, 0.0 ~ 1.0
    double packet_lost_rate;

    /// Delay from peer to peer, in milliseconds
    int peer_to_peer_delay;

    /// Packet loss rate from peer to peer, in percentage, 0.0 ~ 1.0
    double peer_to_peer_packet_lost_rate;

    /// Published stream quality level
    enum zego_stream_quality_level level;

    /// Delay after the data is received by the local end, in milliseconds
    int delay;

    /// The difference between the video timestamp and the audio timestamp, used to reflect the synchronization of audio and video, in milliseconds. This value is less than 0 means the number of milliseconds that the video leads the audio, greater than 0 means the number of milliseconds that the video lags the audio, and 0 means no difference. When the absolute value is less than 200, it can basically be regarded as synchronized audio and video, when the absolute value is greater than 200 for 10 consecutive seconds, it can be regarded as abnormal (Available since 1.19.0)
    int av_timestamp_diff;

    /// Whether to enable hardware decoding
    bool is_hardware_decode;

    /// Video codec ID (Available since 1.17.0)
    enum zego_video_codec_id video_codec_id;

    /// Total number of bytes received, including audio, video, SEI
    double total_recv_bytes;

    /// Number of audio bytes received
    double audio_recv_bytes;

    /// Number of video bytes received
    double video_recv_bytes;

    /// Accumulated audio break count (Available since 2.9.0)
    unsigned int audio_cumulative_break_count;

    /// Accumulated audio break time, in milliseconds (Available since 2.9.0)
    unsigned int audio_cumulative_break_time;

    /// Accumulated audio break rate, in percentage, 0.0 ~ 1.0 (Available since 2.9.0)
    double audio_cumulative_break_rate;

    /// Accumulated audio decode time, in milliseconds (Available since 2.9.0)
    unsigned int audio_cumulative_decode_time;

    /// Accumulated video break count (Available since 2.9.0)
    unsigned int video_cumulative_break_count;

    /// Accumulated video break time, in milliseconds (Available since 2.9.0)
    unsigned int video_cumulative_break_time;

    /// Accumulated video break rate, in percentage, 0.0 ~ 1.0 (Available since 2.9.0)
    double video_cumulative_break_rate;

    /// Accumulated video decode time, in milliseconds (Available since 2.9.0)
    unsigned int video_cumulative_decode_time;
};

/// Cross APP playing stream configuration.
struct zego_cross_app_info {
    /// AppID for playing streams across apps.
    unsigned int app_id;

    /// The token that needs to be set.
    char token[ZEGO_EXPRESS_MAX_TOKEN_LEN];
};

/// Device Info.
///
/// Including device ID and name
struct zego_device_info {
    /// Device ID
    char device_id[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// Device name
    char device_name[ZEGO_EXPRESS_MAX_COMMON_LEN];
};

/// System performance monitoring status
struct zego_performance_status {
    /// Current CPU usage of the app, value range [0, 1]
    double cpu_usage_app;

    /// Current CPU usage of the system, value range [0, 1]
    double cpu_usage_system;

    /// Current memory usage of the app, value range [0, 1]
    double memory_usage_app;

    /// Current memory usage of the system, value range [0, 1]
    double memory_usage_system;

    /// Current memory used of the app, in MB
    double memory_used_app;
};

/// Beauty configuration options.
///
/// Configure the parameters of skin peeling, whitening and sharpening
struct zego_beautify_option {
    /// The sample step size of beauty peeling, the value range is [0,1], default 0.2
    double polish_step;

    /// Brightness parameter for beauty and whitening, the larger the value, the brighter the brightness, ranging from [0,1], default 0.5
    double whiten_factor;

    /// Beauty sharpening parameter, the larger the value, the stronger the sharpening, value range [0,1], default 0.1
    double sharpen_factor;
};

/// Beauty configuration param.
///
/// Configure the whiten, rosy, smooth, and sharpen parameters for beauty.
struct zego_effects_beauty_param {
    /// The whiten intensity parameter, the value range is [0,100], and the default is 50.
    int whiten_intensity;

    /// the rosy intensity parameter, value range [0,100], and the default is 50.
    int rosy_intensity;

    /// the smooth intensity parameter, value range [0,100], and the default is 50.
    int smooth_intensity;

    /// the sharpen intensity parameter, value range [0,100], and the default is 50.
    int sharpen_intensity;
};

/// Mix stream audio configuration.
///
/// Configure video frame rate, bitrate, and resolution for mixer task
struct zego_mixer_audio_config {
    /// Audio bitrate in kbps, default is 48 kbps, cannot be modified after starting a mixer task
    int bitrate;

    /// Audio channel, default is Mono
    enum zego_audio_channel channel;

    /// codec ID, default is ZegoAudioCodecIDDefault
    enum zego_audio_codec_id codec_id;

    /// Multi-channel audio stream mixing mode. If [ZegoAudioMixMode] is selected as [Focused], the SDK will select 4 input streams with [isAudioFocus] set as the focus voice highlight. If it is not selected or less than 4 channels are selected, it will automatically fill in 4 channels
    enum zego_audio_mix_mode mix_mode;
};

/// Mix stream video config object.
///
/// Configure video frame rate, bitrate, and resolution for mixer task
struct zego_mixer_video_config {
    /// Video resolution width
    int width;

    /// Video resolution height
    int height;

    /// Video FPS, cannot be modified after starting a mixer task
    int fps;

    /// Video bitrate in kbps
    int bitrate;
};

/// Mix stream output video config object.
///
/// Description: Configure the video parameters, coding format and bitrate of mix stream output.
/// Use cases: Manual mixed stream scenario, such as Co-hosting.
struct zego_mixer_output_video_config {
    /// Mix stream output video coding format, supporting H.264 and h.265 coding.
    enum zego_video_codec_id video_codec_id;

    /// Mix stream output video bitrate in kbps. The default value is the bitrate configured in [ZegoMixerVideoConfig].
    int bitrate;

    /// Mix stream video encode profile. Default value is [ZegoEncodeProfileDefault].
    enum zego_encode_profile encode_profile;

    /// The video encoding delay of mixed stream output, Valid value range [0, 2000], in milliseconds. The default value is 0.
    int encode_latency;
};

/// Font style.
///
/// Description: Font style configuration, can be used to configure font type, font size, font color, font transparency.
/// Use cases: Set text watermark in manual stream mixing scene, such as Co-hosting.
struct zego_font_style {
    /// Font type. Required: False. Default value: Source han sans [ZegoFontTypeSourceHanSans]
    enum zego_font_type type;

    /// Font size in px. Required: False. Default value: 24. Value range: [12,100].
    int size;

    /// Font color, the calculation formula is: R + G x 256 + B x 65536, the value range of R (red), G (green), and B (blue) [0,255]. Required: False. Default value: 16777215(white). Value range: [0,16777215].
    int color;

    /// Font transparency. Required: False. Default value: 0. Value range: [0,100], 100 is completely opaque, 0 is completely transparent.
    int transparency;

    /// Whether the font has a border. Required: False. Default value: False. Value range: True/False.
    bool border;

    /// Font border color, the calculation formula is: R + G x 256 + B x 65536, the value range of R (red), G (green), and B (blue) [0,255]. Required: False. Default value: 0. Value range: [0,16777215].
    int bordercolor;
};

/// Label info.
///
/// Description: Font style configuration, can be used to configure font type, font si-e, font color, font transparency.
/// Use cases: Set text watermark in manual stream mixing scene, such as Co-hosting.
struct zego_label_info {
    /// Text content, support for setting simplified Chinese, English, half-width, not full-width. Required: True.Value range: Maximum support for displaying 100 Chinese characters and 300 English characters.
    char text[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// The distance between the font and the left border of the output canvas, in px. Required: False. Default value: 0.
    int left;

    /// The distance between the font and the top border of the output canvas, in px. Required: False. Default value: 0.
    int top;

    /// Font style. Required: False.
    struct zego_font_style font;
};

/// Set the image information of a single input stream in the mux.
///
/// Available since: 2.19.0
/// Description: Sets a picture for the content of a single input stream, which is used in place of the video, i.e. the video is not displayed when the picture is used. The `layout` layout in [ZegoMixerInput] for image multiplexing.
/// Use case: The developer needs to temporarily turn off the camera to display the image during the video connection to the microphone, or display the picture when the audio is connected to the microphone.
/// Restrictions: Image size is limited to 1M.
struct zego_mixer_image_info {
    /// The image path, if not empty, the image will be displayed, otherwise, the video will be displayed. JPG and PNG formats are supported. There are 2 ways to use it: 1. URI: Provide the picture to ZEGO technical support for configuration. After the configuration is complete, the picture URI will be provided, for example: preset-id://xxx.jpg. 2. URL: Only HTTP protocol is supported.
    char url[ZEGO_EXPRESS_MAX_URL_LEN];
};

/// Mixer input.
///
/// Configure the mix stream input stream ID, type, and the layout
struct zego_mixer_input {
    /// Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /// Mix stream content type
    enum zego_mixer_input_content_type content_type;

    /// Stream layout. When the mixed stream is an audio stream (that is, the ContentType parameter is set to the audio mixed stream type), the layout field is not processed inside the SDK, and there is no need to pay attention to this parameter.
    struct zego_rect layout;

    /// If enable soundLevel in mix stream task, an unique soundLevelID is need for every stream
    unsigned int sound_level_id;

    /// Input stream volume, valid range [0, 200], default is 100
    unsigned int volume;

    /// Whether the focus voice is enabled in the current input stream, the sound of this stream will be highlighted if enabled
    bool is_audio_focus;

    /// The direction of the audio. Valid direction is between 0 to 360. Set -1 means disable. Default value is -1
    int audio_direction;

    /// Text watermark.
    struct zego_label_info label;

    /// Video view render mode.
    enum zego_mix_render_mode render_mode;

    /// User image information.
    struct zego_mixer_image_info image_info;

    bool enable_audio_direction;
};

/// Mixer output object.
///
/// Configure mix stream output target URL or stream ID
struct zego_mixer_output {
    /// Mix stream output target, URL or stream ID, if set to be URL format, only RTMP URL surpported, for example rtmp://xxxxxxxx, addresses with two identical mixed-stream outputs cannot be passed in.
    char target[ZEGO_EXPRESS_MAX_URL_LEN];

    /// Mix stream output video config
    zego_mixer_output_video_config *video_config;
};

/// Watermark object.
///
/// Configure a watermark image URL and the layout of the watermark in the screen.
struct zego_watermark {
    /// The path of the watermark image. Support local file absolute path (file://xxx). The format supports png, jpg.
    char image_url[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// Watermark image layout
    struct zego_rect layout;
};

/// Mix stream task object.
///
/// This class is the configuration class of the stream mixing task. When a stream mixing task is requested to the ZEGO RTC server, the configuration of the stream mixing task is required.
/// This class describes the detailed configuration information of this stream mixing task.
struct zego_mixer_task {
    char task_id[ZEGO_EXPRESS_MAX_MIXER_TASK_LEN];

    struct zego_mixer_input *input_list;

    unsigned int input_list_count;

    struct zego_mixer_output *output_list;

    unsigned int output_list_count;

    struct zego_mixer_video_config video_config;

    struct zego_mixer_audio_config audio_config;

    struct zego_watermark *watermark;

    int background_color;

    char background_image_url[ZEGO_EXPRESS_MAX_URL_LEN];

    bool enable_sound_level;

    zego_stream_alignment_mode stream_alignment_mode;

    const unsigned char *user_data;

    unsigned int user_data_length;

    char advanced_config[ZEGO_EXPRESS_MAX_COMMON_LEN];
};

/// Mix stream sound level info object.
struct zego_mixer_sound_level_info {
    /// Sound level ID.
    unsigned int sound_level_id;

    /// Sound level value.
    float sound_level;
};

/// Configuration for start sound level monitor.
struct zego_sound_level_config {
    /// Monitoring time period of the sound level, in milliseconds, has a value range of [100, 3000]. Default is 100 ms.
    unsigned int millisecond;

    /// Set whether the sound level callback includes the VAD detection result.
    bool enable_vad;
};

/// Sound level info object.
struct zego_sound_level_info {
    /// Stream ID.
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /// Sound level value.
    float sound_level;

    /// Whether the stream corresponding to StreamID contains voice, 0 means noise, 1 means normal voice. This value is valid only when the [enableVAD] parameter in the [ZegoSoundLevelConfig] configuration is set to true when calling [startSoundLevelMonitor].
    int vad;
};

/// Audio spectrum info object.
struct zego_audio_spectrum_info {
    /// Stream ID.
    char stream_id[ZEGO_EXPRESS_MAX_STREAM_LEN];

    /// Spectrum values list.
    float *spectrum_list;

    /// Spectrum values list of count.
    unsigned int spectrum_count;
};

/// Auto mix stream task object.
///
/// Description: When using [StartAutoMixerTask] function to start an auto stream mixing task to the ZEGO RTC server, user need to set this parameter to configure the auto stream mixing task, including the task ID, room ID, audio configuration, output stream list, and whether to enable the sound level callback.
/// Use cases: This configuration is required when an auto stream mixing task is requested to the ZEGO RTC server.
/// Caution: As an argument passed when [StartAutoMixerTask] function is called.
struct zego_auto_mixer_task {
    /// The taskID of the auto mixer task.Description: Auto stream mixing task id, must be unique in a room.Use cases: User need to set this parameter when initiating an auto stream mixing task.Required: Yes.Recommended value: Set this parameter based on requirements.Value range: A string up to 256 bytes.Caution: When starting a new auto stream mixing task, only one auto stream mixing task ID can exist in a room, that is, to ensure the uniqueness of task ID. You are advised to associate task ID with room ID. You can directly use the room ID as the task ID.Cannot include URL keywords, for example, 'http' and '?' etc, otherwise publishing stream and playing stream will fail. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    char task_id[ZEGO_EXPRESS_MAX_MIXER_TASK_LEN];

    /// The roomID of the auto mixer task.Description: Auto stream mixing task id.Use cases: User need to set this parameter when initiating an auto stream mixing task.Required: Yes.Recommended value: Set this parameter based on requirements.Value range: A string up to 128 bytes.Caution: Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    char room_id[ZEGO_EXPRESS_MAX_ROOMID_LEN];

    /// The audio config of the auto mixer task.Description: The audio config of the auto mixer task.Use cases: If user needs special requirements for the audio config of the auto stream mixing task, such as adjusting the audio bitrate, user can set this parameter as required. Otherwise, user do not need to set this parameter.Required: No.Default value: The default audio bitrate is `48 kbps`, the default audio channel is `ZEGO_AUDIO_CHANNEL_MONO`, the default encoding ID is `ZEGO_AUDIO_CODEC_ID_DEFAULT`, and the default multi-channel audio stream mixing mode is `ZEGO_AUDIO_MIX_MODE_RAW`.Recommended value: Set this parameter based on requirements.
    struct zego_mixer_audio_config audio_config;

    /// The output list of the auto mixer task.Description: The output list of the auto stream mixing task, items in the list are URL or stream ID, if the item set to be URL format, only RTMP URL surpported, for example rtmp://xxxxxxxx.Use cases: User need to set this parameter to specify the mix stream output target when starting an auto stream mixing task.Required: Yes.
    struct zego_mixer_output *output_list;

    /// Enable or disable sound level callback for the task. If enabled, then the remote player can get the sound level of every stream in the inputlist by [onAutoMixerSoundLevelUpdate] callback.Description: Enable or disable sound level callback for the task.If enabled, then the remote player can get the sound level of every stream in the inputlist by [onAutoMixerSoundLevelUpdate] callback.Use cases: This parameter needs to be configured if user need the sound level information of every stream when an auto stream mixing task started.Required: No.Default value: `false`.Recommended value: Set this parameter based on requirements.
    bool enable_sound_level;

    /// Stream mixing alignment mode.
    enum zego_stream_alignment_mode stream_alignment_mode;

    /// The output list count of the auto mixer task
    unsigned int output_list_count;
};

/// Broadcast message info.
///
/// The received object of the room broadcast message, including the message content, message ID, sender, sending time
struct zego_broadcast_message_info {
    /// message content
    char message[ZEGO_EXPRESS_MAX_MESSAGE_LEN];

    /// message id
    unsigned long long message_id;

    /// Message send time, UNIX timestamp, in milliseconds.
    unsigned long long send_time;

    /// Message sender.Please do not fill in sensitive user information in this field, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    struct zego_user from_user;
};

/// Barrage message info.
///
/// The received object of the room barrage message, including the message content, message ID, sender, sending time
struct zego_barrage_message_info {
    /// message content
    char message[ZEGO_EXPRESS_MAX_MESSAGE_LEN];

    /// message id
    char message_id[64];

    /// Message send time, UNIX timestamp, in milliseconds.
    unsigned long long send_time;

    /// Message sender.Please do not fill in sensitive user information in this field, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    struct zego_user from_user;
};

struct zego_camera_capture_params {
    int capture_resolution_width;

    int capture_resolution_height;

    int capture_fps;
};

/// Object for video frame fieldeter.
///
/// Including video frame format, width and height, etc.
struct zego_video_frame_param {
    /// Video frame format
    enum zego_video_frame_format format;

    /// Number of bytes per line (for example: BGRA only needs to consider strides [0], I420 needs to consider strides [0,1,2])
    int strides[4];

    /// Video frame width. When use custom video capture, the video data meeting the 32-bit alignment can obtain the maximum performance. Taking BGRA as an example, width * 4 is expected to be multiple of 32.
    int width;

    /// Video frame height
    int height;

    /// The rotation direction of the video frame, the SDK rotates clockwise
    int rotation;
};

/// Object for video encoded frame fieldeter.
///
/// Including video encoded frame format, width and height, etc.
struct zego_video_encoded_frame_param {
    /// Video encoded frame format
    enum zego_video_encoded_frame_format format;

    /// Whether it is a keyframe
    bool is_key_frame;

    /// Video frame counterclockwise rotation angle
    int rotation;

    /// Video frame width
    int width;

    /// Video frame height
    int height;

    /// SEI data (Optional, if you don't need to send SEI, set it to null)
    const unsigned char *sei_data;

    /// Length of the SEI data (Optional, if you don't need to send SEI, set it to 0)
    unsigned int sei_data_length;
};

/// Parameter object for audio frame.
///
/// Including the sampling rate and channel of the audio frame
struct zego_audio_frame_param {
    /// Sampling Rate
    enum zego_audio_sample_rate sample_rate;

    /// Audio channel, default is Mono
    enum zego_audio_channel channel;
};

/// Audio configuration.
///
/// Configure audio bitrate, audio channel, audio encoding for publishing stream
struct zego_audio_config {
    /// Audio bitrate in kbps, default is 48 kbps. The settings before and after publishing stream can be effective
    int bitrate;

    /// Audio channel, default is Mono. The setting only take effect before publishing stream
    enum zego_audio_channel channel;

    /// codec ID, default is ZegoAudioCodecIDDefault. The setting only take effect before publishing stream
    enum zego_audio_codec_id codec_id;
};

/// audio mixing data.
struct zego_audio_mixing_data {
    /// Audio PCM data that needs to be mixed into the stream
    unsigned char *audio_data;

    /// the length of the audio PCM data that needs to be mixed into the stream. If the data length is sufficient, it must be the same as expectedDataLength
    unsigned int audio_data_length;

    /// Audio data attributes, including sample rate and number of channels. Currently supports 16k, 32k, 44.1k, 48k sampling rate, mono or stereo, 16-bit deep PCM data. Developers need to explicitly specify audio data attributes, otherwise mixing will not take effect.
    struct zego_audio_frame_param param;

    /// SEI data, used to transfer custom data. When audioData is null, SEIData will not be sent
    unsigned char *sei_data;

    /// SEI data length
    unsigned int sei_data_length;
};

/// Customize the audio processing configuration object.
///
/// Including custom audio acquisition type, sampling rate, channel number, sampling number and other parameters
struct zego_custom_audio_process_config {
    /// Sampling rate, the sampling rate of the input data expected by the audio pre-processing module in App. If 0, the default is the SDK internal sampling rate.
    enum zego_audio_sample_rate sample_rate;

    /// Number of sound channels, the expected number of sound channels for input data of the audio pre-processing module in App. If 0, the default is the number of internal channels in the SDK
    enum zego_audio_channel channel;

    /// The number of samples required to encode a frame; When encode = false, if samples = 0, the SDK will use the internal sample number, and the SDK will pass the audio data to the external pre-processing module. If the samples! = 0 (the effective value of samples is between [160, 2048]), and the SDK will send audio data to the external preprocessing module that sets the length of sample number. Encode = true, the number of samples for a frame of AAC encoding can be set as (480/512/1024/1960/2048)
    int samples;
};

/// Record config.
struct zego_data_record_config {
    /// The path to save the recording file, absolute path, need to include the file name, the file name need to specify the suffix, currently supports .mp4/.flv/.aac format files, if multiple recording for the same path, will overwrite the file with the same name. The maximum length should be less than 1024 bytes.
    char file_path[ZEGO_EXPRESS_MAX_URL_LEN];

    /// Type of recording media
    enum zego_data_record_type record_type;
};

/// File recording progress.
struct zego_data_record_progress {
    /// Current recording duration in milliseconds
    unsigned long long duration;

    /// Current recording file size in byte
    unsigned long long current_file_size;
};

/// Network probe config
struct zego_network_probe_config {
    /// Whether do traceroute, enabling tranceRoute will significantly increase network detection time
    bool enable_traceroute;
};

/// http probe result
struct zego_network_probe_http_result {
    /// http probe errorCode, 0 means the connection is normal
    int error_code;

    /// http request cost time, the unit is millisecond
    unsigned int request_cost_time;
};

/// tcp probe result
struct zego_network_probe_tcp_result {
    /// tcp probe errorCode, 0 means the connection is normal
    int error_code;

    /// tcp rtt, the unit is millisecond
    unsigned int rtt;

    /// tcp connection cost time, the unit is millisecond
    unsigned int connect_cost_time;
};

/// udp probe result
struct zego_network_probe_udp_result {
    /// udp probe errorCode, 0 means the connection is normal
    int error_code;

    /// The total time that the SDK send udp data to server and receive a reply, the unit is millisecond
    unsigned int rtt;
};

/// traceroute result
///
/// Jump up to 30 times. The traceroute result is for reference and does not represent the final network connection result. The priority is http, tcp, udp probe result.
struct zego_network_probe_traceroute_result {
    /// traceroute error code, 0 means normal
    int error_code;

    /// Time consumed by trace route, the unit is millisecond
    unsigned int traceroute_cost_time;
};

/// Network probe result
struct zego_network_probe_result {
    /// http probe result
    struct zego_network_probe_http_result *http_probe_result;

    /// tcp probe result
    struct zego_network_probe_tcp_result *tcp_probe_result;

    /// udp probe result
    struct zego_network_probe_udp_result *udp_probe_result;

    /// traceroute result
    struct zego_network_probe_traceroute_result *traceroute_result;
};

/// Network speed test config
struct zego_network_speed_test_config {
    /// Test uplink or not
    bool test_uplink;

    /// The unit is kbps. Recommended to use the bitrate in ZegoVideoConfig when call startPublishingStream to determine whether the network uplink environment is suitable.
    int expected_uplink_bitrate;

    /// Test downlink or not
    bool test_downlink;

    /// The unit is kbps. Recommended to use the bitrate in ZegoVideoConfig when call startPublishingStream to determine whether the network downlink environment is suitable.
    int expected_downlink_bitrate;
};

/// test connectivity result
struct zego_test_network_connectivity_result {
    /// connect cost
    unsigned int connect_cost;
};

/// network speed test quality
struct zego_network_speed_test_quality {
    /// Time to connect to the server, in milliseconds. During the speed test, if the network connection is disconnected, it will automatically initiate a reconnection, and this variable will be updated accordingly.
    unsigned int connect_cost;

    /// rtt, in milliseconds
    unsigned int rtt;

    /// packet lost rate. in percentage, 0.0 ~ 1.0
    double packet_lost_rate;

    /// network quality. excellent, good, medium and poor
    enum zego_stream_quality_level quality;
};

/// The NTP info
struct zego_network_time_info {
    /// Network timestamp after synchronization, 0 indicates not yet synchronized
    unsigned long long timestamp;

    /// The max deviation
    int max_deviation;
};

/// AudioEffectPlayer play configuration.
struct zego_audio_effect_play_config {
    /// The number of play counts. When set to 0, it will play in an infinite loop until the user invoke [stop]. The default is 1, which means it will play only once.
    unsigned int play_count;

    /// Whether to mix audio effects into the publishing stream, the default is false.
    bool is_publish_out;
};

/// Precise seek configuration
struct zego_accurate_seek_config {
    /// The timeout time for precise search; if not set, the SDK internal default is set to 5000 milliseconds, the effective value range is [2000, 10000], the unit is ms
    unsigned long long time_out;
};

/// Media player network cache information
struct zego_network_resource_cache {
    /// Cached duration, unit ms
    unsigned int time;

    /// Cached size, unit byte
    unsigned int size;
};

/// CopyrightedMusic play configuration.
struct zego_copyrighted_music_config {
    /// User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
    struct zego_user user;
};

/// Request configuration of song or accompaniment.
struct zego_copyrighted_music_request_config {
    /// the ID of the song.
    char song_id[ZEGO_EXPRESS_MAX_COMMON_LEN];

    /// VOD billing mode.
    enum zego_copyrighted_music_billing_mode mode;
};

#endif /* __ZEGO_EXPRESS_DEFINE_H__ */
