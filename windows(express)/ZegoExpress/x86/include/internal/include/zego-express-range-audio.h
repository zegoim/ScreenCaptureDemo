
#ifndef __ZEGO_EXPRESS_RANGE_AUDIO_H__
#define __ZEGO_EXPRESS_RANGE_AUDIO_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Creates a range audio instance.
///
/// Available since: 2.11.0
/// Description: Creates a range audio instance.
/// Use case: Often used in game voice scenarios, users can use related functions by creating range audio instance objects.
/// When to call: It can be called after the engine by [createEngine] has been initialized.
/// Restrictions: Currently, a maximum of 1 instances can be created, after which it will return NULL.
/// Impacts on other APIs: If you use the range audio module, you cannot use the basic push-pull stream [startPublishingStream], [startPlayingStream] interfaces and related callbacks.
///
/// @return range audio instance, NULL will be returned when the maximum number is exceeded.
ZEGOEXP_API enum zego_range_audio_instance_index EXP_CALL zego_express_create_range_audio();

/// Destroys a range audio instance.
///
/// Available since: 2.11.0
/// Description: Destroys a range audio instance.
///
/// @param instance_index range audio instance index.
ZEGOEXP_API zego_error EXP_CALL
zego_express_destroy_range_audio(enum zego_range_audio_instance_index instance_index);

/// Set the maximum range of received audio.
///
/// Available since: 2.11.0
/// Description: Set the audio receiving range, the audio source sound beyond this range will not be received.
/// Use case: Set the receiver's receiving range in the `World` mode.
/// Default value: When this function is not called, there is no distance limit, and everyone in the room can be received.
/// When to call: After initializing the range audio [createRangeAudio].
/// Restrictions: This range only takes effect for people outside the team.
///
/// @param range the audio range, the value must be greater than or equal to 0.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_set_audio_receive_range(
    float range, enum zego_range_audio_instance_index instance_index);

/// Update self position and orentation.
///
/// Available since: 2.11.0
/// Description: Update the user's position and orientation so that the SDK can calculate the distance between the user and the audio source and the stereo effect of the left and right ears.
/// Use case: When the role operated by the user in the game moves on the world map, the position information and head orientation of the role are updated.
/// When to call: Called after logging in to the room [loginRoom].
/// Caution: Before calling [enableSpeaker] to turn on the speaker, if you do not call this interface to set the location information, you will not be able to receive voices from other people except the team.
///
/// @param position The coordinates of the oneself in the world coordinate system. The parameter is a float array of length 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
/// @param axis_forward The unit vector of the front axis of its own coordinate system. The parameter is a float array with a length of 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
/// @param axis_right The unit vector of the right axis of its own coordinate system. The parameter is a float array with a length of 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
/// @param axis_up The unit vector of the up axis of its own coordinate system. The parameter is a float array with a length of 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_update_self_position(
    float position[3], float axis_forward[3], float axis_right[3], float axis_up[3],
    enum zego_range_audio_instance_index instance_index);

/// Add or update audio source position information.
///
/// Available since: 2.11.0
/// Description: Set the position of the audio source corresponding to the userID on the game map in the room, so that the SDK can calculate the distance and orientation of the listener to the audio source.
/// Use case: Update the position of the voice user in the game map coordinates.
/// When to call: Call [loginRoom] to call after logging in to the room, and the recorded audio source information will be cleared after logging out of the room.
///
/// @param userid The user ID of the sender.
/// @param position The coordinates of the speaker in the world coordinate system. The parameter is a float array of length 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_update_audio_source(
    const char *userid, float position[3], enum zego_range_audio_instance_index instance_index);

/// Turn the 3D spatial sound on or off.
///
/// Available since: 2.11.0
/// Description: After the 3D sound effect is turned on, the sound effect in the actual space will be simulated according to the position of the speaker equivalent to the listener. The intuitive feeling is that the sound size and the left and right sound difference will also change when the distance and orientation of the sound source change.
/// Use case: It is a feature of audio recognition in FPS games or social scene games.
/// Default value: When this function is not called, 3D sound effects are turned off by default.
/// When to call: After initializing the range audio [createRangeAudio].
/// Caution: The 3D audio effect will only take effect when [setRangeAudioMode] is called and set to `World` mode.
/// Related APIs: After enabling the 3D sound effect, you can use [updateAudioSource] or [updateSelfPosition] to change the position and orientation to experience the 3D effect.
///
/// @param enable Whether to enable 3D sound effects.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_enable_spatializer(
    bool enable, enum zego_range_audio_instance_index instance_index);

/// Turn the microphone on or off.
///
/// Available since: 2.11.0
/// Description: When enable is `true`, turn on the microphone and push audio stream; when it is `false`, turn off the microphone and stop pushing audio stream.
/// Use case: The user turns on or off the microphone to communicate in the room.
/// Default value: When this function is not called, the microphone is turned off by default.
/// When to call: After initializing the range audio [createRangeAudio] and login room [loginRoom].
/// Caution: Turning on the microphone will automatically use the main channel to push the audio stream.
/// Related callbacks: Get the microphone switch state change through the callback [onRangeAudioMicrophoneStateUpdate].
///
/// @param enable Whether to turn on the microphone.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_enable_microphone(
    bool enable, enum zego_range_audio_instance_index instance_index);

/// Turn the speaker on or off.
///
/// Available since: 2.11.0
/// Description: When enable is `true`, turn on the speaker and play audio stream; when it is `false`, turn off the speaker and stop playing audio stream.
/// Use case: The user turns on or off the speaker to communicate in the room.
/// Default value: When this function is not called, the speaker is turned off by default.
/// When to call: After initializing the range audio [createRangeAudio] and login room [loginRoom].
/// Caution: Turning on the speaker will automatically pull the audio stream in the room.
///
/// @param enable Whether to turn on the speaker.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_enable_speaker(
    bool enable, enum zego_range_audio_instance_index instance_index);

/// Set range audio mode.
///
/// Available since: 2.11.0
/// Description: The audio mode can be set to `World` mode or `Team` mode.
/// Use case: The user can choose to chat with everyone in the `World` mode (with distance limitation), or to communicate within the team in the `Team` mode (without distance limitation).
/// Default value: If this function is not called, the `World` mode is used by default.
/// When to call: After initializing the range audio [createRangeAudio].
/// Related APIs: In the `World` mode, you can set the sound receiving range [setAudioReceiveRange], in the `Team` mode, you need to set [setTeamID] to join the corresponding team to hear the voice in the team.
///
/// @param mode The range audio mode.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_set_range_audio_mode(
    enum zego_range_audio_mode mode, enum zego_range_audio_instance_index instance_index);

/// Set team ID.
///
/// Available: since 2.11.0
/// Description: After setting the team ID, you will be able to communicate with other users of the same team, and the sound will not change with the distance.
/// Use case: Users join the team or exit the team.
/// Default value: When this function is not called, no team will be added by default.
/// When to call: After initializing the range audio [createRangeAudio].
/// Caution: There will be no distance limit for the sounds in the team, and there will be no 3D sound effects.
/// Restrictions: The team ID will only take effect when [setRangeAudioMode] is called and set to `Team` mode.
///
/// @param team_id Team ID, a string of up to 64 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_set_team_id(
    const char *team_id, enum zego_range_audio_instance_index instance_index);

/// Whether can receive the audio data of the specified user.
///
/// Available since: 2.16.0
/// Description: In the process of real-time audio and video interaction, local users can use this function to control whether to receive audio data from designated remote users when pulling streams as needed. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
/// Use cases: When developers need to quickly close and restore remote audio, they can call this function to enhance the interactive experience.
/// Default value: The default is `false`, which means to receive audio data from all users.
/// When to call: After initializing the range audio [createRangeAudio].
/// Caution: This function is valid only when the [muteAllPlayStreamAudio] function is set to `false`.
/// Related APIs: You can call the [muteAllPlayStreamAudio] function to control whether to receive all audio data. 1. When the [muteAllPlayStreamAudio(true)] function is called, it takes effect globally, that is, local users will be prohibited from receiving audio data from all remote users. At this time, the [muteUser] function will not take effect regardless of whether the [muteUser] function is called before or after [muteAllPlayStreamAudio]. 2. When the [muteAllPlayStreamAudio(false)] function is called, the local user can receive the audio data of all remote users. At this time, the [muteUser] function can be used to control whether to receive the audio data of the specified user. Calling the [muteUser(userID, true)] function allows the local user to receive audio data other than the `userID`; calling the [muteUser(userID, false)] function allows the local user to receive the audio data of the `userID`.
///
/// @param userid User ID.
/// @param mute Whether it can receive the audio data of the specified remote user, "true" means prohibition, "false" means receiving, the default value is "false".
/// @param instance_index range audio instance index
ZEGOEXP_API zego_error EXP_CALL zego_express_range_audio_mute_user(
    const char *userid, bool mute, enum zego_range_audio_instance_index instance_index);

/// Range audio microphone state callback.
///
/// Available since: 2.11.0
/// Description: The status change notification of the microphone, starting to send audio is an asynchronous process, and the state switching in the middle is called back through this function.
/// When to Trigger: After the [enableMicrophone] function.
/// Caution: It must be monitored before the [enableMicrophone] function is called.
///
/// @param state The use state of the range audio.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param instance_index Range audio instance index
/// @param user_context Context of user.
typedef void (*zego_on_range_audio_microphone_state_update)(
    enum zego_range_audio_microphone_state state, zego_error error_code,
    enum zego_range_audio_instance_index instance_index, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_range_audio_microphone_state_update_callback(
    zego_on_range_audio_microphone_state_update callback_func, void *user_context);

ZEGO_END_DECLS

#endif
