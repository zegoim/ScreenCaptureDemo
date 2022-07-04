
#ifndef __ZEGO_EXPRESS_DEVICE_H__
#define __ZEGO_EXPRESS_DEVICE_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Mutes or unmutes the microphone.
///
/// Available since: 1.1.0
/// Description: This function is used to control whether to use the collected audio data. Mute (turn off the microphone) will use the muted data to replace the audio data collected by the device for streaming. At this time, the microphone device will still be occupied.
/// Default value: The default is `false`, which means no muting.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Related APIs: Developers who want to control whether to use microphone on the UI should use this function to avoid unnecessary performance overhead by using the [enableAudioCaptureDevice]. You can use [isMicrophoneMuted] to check if the microphone is muted.
///
/// @param mute Whether to mute (disable) the microphone, `true`: mute (disable) microphone, `false`: enable microphone.
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_microphone(bool mute);

/// Checks whether the microphone is muted.
///
/// Available since: 1.1.0
/// Description: Used to determine whether the microphone is set to mute.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Related APIs: [muteMicrophone].
///
/// @return Whether the microphone is muted; true: the microphone is muted; `false`: the microphone is enable (not muted).
ZEGOEXP_API bool EXP_CALL zego_express_is_microphone_muted();

/// Mutes or unmutes the audio output speaker.
///
/// Available since: 1.1.0
/// Description: After mute speaker, all the SDK sounds will not play, including playing stream, mediaplayer, etc. But the SDK will still occupy the output device.
/// Default value: The default is `false`, which means no muting.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
///
/// @param mute Whether to mute (disable) speaker audio output, `true`: mute (disable) speaker audio output, `false`: enable speaker audio output.
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_speaker(bool mute);

/// Checks whether the audio output speaker is muted.
///
/// Available since: 1.1.0
/// Description: Used to determine whether the audio output is muted.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Related APIs: [muteSpeaker].
///
/// @return Whether the speaker is muted; `true`: the speaker is muted; `false`: the speaker is enable (not muted).
ZEGOEXP_API bool EXP_CALL zego_express_is_speaker_muted();

/// Gets a list of audio devices.
///
/// Only supports Windows and Mac.
///
/// @param device_type Audio device type
/// @param device_count Count of device.
/// @return Audo device List
ZEGOEXP_API struct zego_device_info *EXP_CALL
zego_express_get_audio_device_list(enum zego_audio_device_type device_type, int *device_count);

/// Release a list of audio devices, only supported in Windows/macOS.
///
/// @param device_list Audio device type
ZEGOEXP_API zego_error EXP_CALL
zego_express_free_audio_device_list(struct zego_device_info *device_list);

/// Get the device ID of the default audio device.
///
/// Only supports Windows and Mac.
///
/// @param device_type Audio device type
/// @return Default Audio device ID
ZEGOEXP_API const char *EXP_CALL
zego_express_get_default_audio_device_id(enum zego_audio_device_type device_type);

/// Chooses to use the specified audio device.
///
/// Available since: 1.0.0
/// Description: Chooses to use the specified audio device.
/// When to call: After creating the engine [createEngine] and before call [startPublishingStream] or [startPlayingStream].
/// Restrictions: Only supports Windows/macOS.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
ZEGOEXP_API zego_error EXP_CALL
zego_express_use_audio_device(enum zego_audio_device_type device_type, const char *device_id);

/// Get volume for the specified audio device.
///
/// Get volume for the specified audio device. Only for Windows/macOS.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
/// @return Device volume
ZEGOEXP_API int EXP_CALL zego_express_get_audio_device_volume(
    enum zego_audio_device_type device_type, const char *device_id);

/// Set volume for the specified audio device.
///
/// Only for Windows/macOS. The direct operating system device may fail due to system restrictions. Please use [setCaptureVolume] and [setPlayVolume] first to adjust the volume of publish and play streams.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
/// @param volume Device volume
ZEGOEXP_API zego_error EXP_CALL zego_express_set_audio_device_volume(
    enum zego_audio_device_type device_type, const char *device_id, int volume);

/// Turn on audio device volume monitoring.
///
/// Only for Windows/macOS.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
ZEGOEXP_API zego_error EXP_CALL zego_express_start_audio_device_volume_monitor(
    enum zego_audio_device_type device_type, const char *device_id);

/// Turn off audio device volume monitoring. Only for Windows/macOS.
///
/// Only for Windows/macOS.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_audio_device_volume_monitor(
    enum zego_audio_device_type device_type, const char *device_id);

/// Mutes or unmutes the audio device.
///
/// Only for Windows/macOS.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
/// @param mute Whether to mute the audio device; true means to mute the audio device; false means to unmute the audio device.
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_audio_device(
    enum zego_audio_device_type device_type, const char *device_id, bool mute);

/// Check if the audio device is muted.
///
/// Only for Windows/macOS.
///
/// @param device_type Audio device type
/// @param device_id ID of a device obtained by [getAudioDeviceList]
/// @return Whether the audio device is muted; true means the audio device is muted; false means the audio device is not muted.
ZEGOEXP_API bool EXP_CALL
zego_express_is_audio_device_muted(enum zego_audio_device_type device_type, const char *device_id);

/// Enables or disables the audio capture device.
///
/// Available since: 1.1.0
/// Description: This function is used to control whether to use the audio collection device. When the audio collection device is turned off, the SDK will no longer occupy the audio device. Of course, if the stream is being published at this time, there is no audio data.
/// Use cases: When the user never needs to use the audio, you can call this function to close the audio collection.
/// Default value: The default is `true`.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Related APIs: Turning off or turning on the microphone on the hardware is a time-consuming operation, and there is a certain performance overhead when the user performs frequent operations. [muteMicrophone] is generally recommended.
///
/// @param enable Whether to enable the audio capture device, `true`: enable audio capture device, `false`: disable audio capture device.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_audio_capture_device(bool enable);

/// get current audio route type.
///
/// Available since: 1.1.0
/// Description: Audio routing refers to the audio output device that an app uses to play audio, and common audio routes are: speakers, handsets, headphones, Bluetooth devices, and so on.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Related APIs: Set audio route to speaker [setAudioRouteToSpeaker].
ZEGOEXP_API enum zego_audio_route EXP_CALL zego_express_get_audio_route_type();

/// Whether to use the built-in speaker to play audio.
///
/// Available since: 1.1.0
/// Description: Whether to use the speaker to play audio, when you choose not to use the built-in speaker to play the sound, the SDK will select the audio output device with the highest current priority to play the sound according to the system schedule, and common audio routes are: handsets, headphones, Bluetooth devices, and so on.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Related APIs: Get the current audio route [getAudioRouteType].
///
/// @param default_to_speaker Whether to use the built-in speaker to play sound, `true`: use the built-in speaker to play sound, `false`: use the highest priority audio output device scheduled by the current system to play sound
ZEGOEXP_API zego_error EXP_CALL zego_express_set_audio_route_to_speaker(bool default_to_speaker);

/// Turns on/off the camera (for the specified channel).
///
/// Available since: 1.1.0
/// Description: This function is used to control whether to start the capture of the camera. After the camera is turned off, the video capture will not be performed. At this time, there will be no video data for local preview and push streaming.
/// Default value: The default is `true` which means the camera is turned on.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Caution: In the case of using the custom video capture function [enableCustomVideoCapture], since the developer has taken over the video data capture, the SDK is no longer responsible for the video data capture, but this function still affects whether to encode or not. Therefore, when developers use custom video capture, please ensure that the value of this function is `true`.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable Whether to turn on the camera, `true`: turn on camera, `false`: turn off camera
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_camera(bool enable,
                                                           enum zego_publish_channel channel);

/// Switches to the front or the rear camera (for the specified channel).
///
/// Available since: 1.1.0
/// Description: This function is used to control the use of the front camera or the rear camera (only supported by Android and iOS).
/// Default value: The default is `true` which means the front camera is used.
/// When to call: After creating the engine [createEngine].
/// Restrictions: None.
/// Caution: When the custom video capture function [enableCustomVideoCapture] is turned on, since the developer has taken over the video data capture, the SDK is no longer responsible for the video data capture, and this function is no longer valid.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable Whether to use the front camera, `true`: use the front camera, `false`: use the the rear camera.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_use_front_camera(bool enable,
                                                              enum zego_publish_channel channel);

/// Whether the camera supports focusing.
///
/// Available since: 2.14.0
/// Description: Whether the camera supports focusing.
/// Trigger: Called after turn on preview [startPreivew].
/// Caution: Need to start the camera successfully.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publishing stream channel
/// @return Whether to support focus, support is true, not support is false.
ZEGOEXP_API bool EXP_CALL zego_express_is_camera_focus_supported(enum zego_publish_channel channel);

/// Set the camera focus mode.
///
/// Available since: 2.14.0
/// Description: Set the camera focus mode.
/// Trigger: Called after turn on preview [startPreivew].
/// Restrictions: Currently only supports iOS and Android platforms.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mode focus mode.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_camera_focus_mode(
    enum zego_camera_focus_mode mode, enum zego_publish_channel channel);

/// Set the focus point in the preview view.
///
/// Available since: 2.14.0
/// Description: Set the focus point in the preview view. (x, y) are the normalized coordinates in the preview view, that is, the ratio of the position of the focus point relative to the preview view and the width and height of the preview view. The upper left corner is (0, 0).
/// Trigger: Called after turn on preview [startPreivew].
/// Restrictions: Currently only supports iOS and Android platforms.
/// Caution: Every time the camera restarts the acquisition, the settings will become invalid and need to be reset.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param x Normalized X axis coordinate value, effective value [0,1].
/// @param y Normalized Y axis coordinate value, effective value [0,1].
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_camera_focus_point_in_preview(float x, float y, enum zego_publish_channel channel);

/// Set the camera exposure mode.
///
/// Available since: 2.14.0
/// Description: Set the camera exposure mode.
/// Trigger: Called after turn on preview [startPreivew].
/// Restrictions: Currently only supports iOS and Android platforms.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param mode Exposure mode.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_camera_exposure_mode(
    enum zego_camera_exposure_mode mode, enum zego_publish_channel channel);

/// Set the exposure point in the preview view.
///
/// Available since: 2.14.0
/// Description: Set the exposure point in the preview view. (x, y) are the normalized coordinates in the preview view, that is, the ratio of the position of the exposure point relative to the preview view and the width and height of the preview view. The upper left corner is (0, 0).
/// Trigger: Called after turn on preview [startPreivew].
/// Restrictions: Currently only supports iOS and Android platforms.
/// Caution: Every time the camera restarts the acquisition, the settings will become invalid and need to be reset.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param x Normalized X axis coordinate value, effective value [0,1].
/// @param y Normalized Y axis coordinate value, effective value [0,1].
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_set_camera_exposure_point_in_preview(
    float x, float y, enum zego_publish_channel channel);

/// Set the camera exposure compensation value.
///
/// Available since: 2.10.0
/// Description: Set the camera exposure compensation value.
/// Use cases: User can call this function to set the camera exposure compensation value.
/// When to call /Trigger: Called this function after calling [startPublishingStream] or [startPreview].
/// Restrictions: None.
/// Caution: The setting will be invalid when the camera is restarted.
/// Platform differences: Only supports iOS and Android.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param value Camera exposure, the value range is [-1,1], the default 0, -1 tends to darken, 1 tends to brighten.
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_camera_exposure_compensation(float value, enum zego_publish_channel channel);

/// Set the zoom factor of the camera. Every time the camera is restarted, the camera zoom factor will return to the initial value (1.0).
///
/// Available since: 1.20.0
/// Description: Set the camera zoom factor. Every time the camera is restarted, the camera zoom factor will be restored to its initial value.
/// When to call: After creating the engine [createEngine].
/// Restrictions: The settings will not take effect until the camera is started.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param factor The zoom factor of the camera, the minimum value is 1.0, and the maximum value is the return value of [getCameraMaxZoomFactor].
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_camera_zoom_factor(float factor, enum zego_publish_channel channel);

/// Get the maximum zoom factor of the camera.
///
/// Available since: 1.20.0
/// Description: Set the camera zoom factor. Every time the camera is restarted, the camera zoom factor will be restored to its initial value.
/// When to call: This is only available after the camera has been successfully started, and can generally be called when the captured first frame is received [onPublisherCapturedVideoFirstFrame] callback.
/// Restrictions: None.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param channel Publishing stream channel
/// @return The maximum zoom factor of the camera.
ZEGOEXP_API float EXP_CALL
zego_express_get_camera_max_zoom_factor(enum zego_publish_channel channel);

/// Enable camera adaptive frame rate.
///
/// Available since: 2.20.0
/// Description: After enabling, the SDK matches the capture frame rate range supported by the camera according to the set frame rate range, and dynamically adjusts the capture frame rate of the camera according to the ambient brightness within this range to improve the screen brightness when the set frame rate is too high.
/// Use cases: The frame rate set by the user on the streaming end is too high, and the ambient lighting is low, so the subject cannot be displayed or recognized normally. For example, live broadcast scenes with high exposure requirements.
/// When to call: After creating the engine [createEngine], before the camera starts.
/// Caution: Takes When calling [setVideoConfig] to set the frame rate lower than the expected minimum frame rate, the frame rate value set by [setVideoConfig] will be used. Due to the different hardware and algorithm strategies of different mobile phone manufacturers, the effect of this interface is different on different models or on the front and rear cameras of the same model.
/// Related APIs: Through [setVideoConfig], you can set the camera capture frame rate and the encoder encoding frame rate.
///
/// @param enable Whether to enable camera adaptive frame rate. true means on, false means off.Off by default.
/// @param min_fps Desired minimum frame rate, 15 recommended. Unit: fps.
/// @param max_fps Desired minimum frame rate, 25 recommended. Unit: fps.
/// @param channel Publishing stream channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_camera_adaptive_fps(
    bool enable, int min_fps, int max_fps, enum zego_publish_channel channel);

/// Chooses to use the specified video device (for the specified channel).
///
/// Only for Windows/macOS.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param device_id ID of a device obtained by getVideoDeviceList
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_use_video_device(const char *device_id,
                                                              enum zego_publish_channel channel);

/// Gets a list of video devices.
///
/// Only for Windows/macOS.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @return Video device List
ZEGOEXP_API struct zego_device_info *EXP_CALL zego_express_get_video_device_list(int *device_count);

/// Release a list of video devices.
///
/// Only for Windows/macOS.
///
/// @param device_list Video device type
ZEGOEXP_API zego_error EXP_CALL
zego_express_free_video_device_list(struct zego_device_info *device_list);

/// Get the deviceID of the default video device.
///
/// Only for Windows/macOS.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @return Default video device ID
ZEGOEXP_API const char *EXP_CALL zego_express_get_default_video_device_id();

/// Starts sound level monitoring. Support setting the listening interval.
///
/// Available since: 1.15.0
/// Description: After starting monitoring, you can receive local audio sound level via [onCapturedSoundLevelUpdate] callback, and receive remote audio sound level via [onRemoteSoundLevelUpdate] callback. Before entering the room, you can call [startPreview] with this function and combine it with [onCapturedSoundLevelUpdate] callback to determine whether the audio device is working properly.
/// Use cases: During the publishing and playing process, determine who is talking on the wheat and do a UI presentation.
/// When to call: After the engine is created [createEngine].
/// Caution:
///   1. [onCapturedSoundLevelUpdate] and [onRemoteSoundLevelUpdate] callback notification period is the value set by the parameter. If you want to use advanced feature of sound level, please use the function of the same name (the parameter type is ZegoSoundLevelConfig) instead.
///   2. After the sound monitoring is started, even if the local audio capture is not started, [onCapturedSoundLevelUpdate] will have a callback, and the sound level is 0.
///
/// @param millisecond Monitoring time period of the sound level, in milliseconds, has a value range of [100, 3000]. Default is 100 ms.
ZEGOEXP_API zego_error EXP_CALL zego_express_start_sound_level_monitor(unsigned int millisecond);

/// Starts sound level monitoring. Support enable some advanced feature.
///
/// Available since: 2.10.0
/// Description: After starting monitoring, you can receive local audio sound level via [onCapturedSoundLevelUpdate] callback, and receive remote audio sound level via [onRemoteSoundLevelUpdate] callback. Before entering the room, you can call [startPreview] with this function and combine it with [onCapturedSoundLevelUpdate] callback to determine whether the audio device is working properly.
/// Use cases: During the publishing and playing process, determine who is talking on the wheat and do a UI presentation.
/// When to call: After the engine is created [createEngine].
/// Caution:
///   1. [onCapturedSoundLevelUpdate] and [onRemoteSoundLevelUpdate] callback notification period is the value set by the parameter.
///   2. After the sound monitoring is started, even if the local audio capture is not started, [onCapturedSoundLevelUpdate] will have a callback, and the sound level is 0.
///
/// @param config Configuration for starts the sound level monitor.
ZEGOEXP_API zego_error EXP_CALL
zego_express_start_sound_level_monitor_with_config(struct zego_sound_level_config config);

/// Stops sound level monitoring.
///
/// Available since: 1.1.0
/// Description: After the monitoring is stopped, the callback of the local/remote audio sound level will be stopped.
/// When to call: After the engine is created [createEngine].
/// Related APIs: Soundwave monitoring can be initiated via [startSoundLevelMonitor].
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_sound_level_monitor();

/// Starts audio spectrum monitoring. Support setting the listening interval.
///
/// Available since: 1.15.0
/// Description: After starting monitoring, you can receive local audio spectrum via [onCapturedAudioSpectrumUpdate] callback, and receive remote audio spectrum via [onRemoteAudioSpectrumUpdate] callback.
/// Use cases: In the host K song scene, has been published or played under the premise that the host or audience to see the tone and volume change animation.
/// When to call: After the engine is created [createEngine].
/// Caution: [onCapturedAudioSpectrumUpdate] and [onRemoteAudioSpectrumUpdate] callback notification period is the value set by the parameter.
///
/// @param millisecond Monitoring time period of the audio spectrum, in milliseconds, has a value range of [100, 3000]. Default is 100 ms.
ZEGOEXP_API zego_error EXP_CALL zego_express_start_audio_spectrum_monitor(unsigned int millisecond);

/// Stops audio spectrum monitoring.
///
/// Available since: 1.1.0
/// Description: After the monitoring is stopped, the callback of the local/remote audio spectrum will be stopped.
/// When to call: After the engine is created [createEngine].
/// Related APIs: Audio spectrum monitoring can be initiated via [startAudioSpectrumMonitor].
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_audio_spectrum_monitor();

/// Enables or disables headphone monitoring.
///
/// Available since: 1.9.0
/// Description: Enable/Disable headphone monitor, and users hear their own voices as they use the microphone to capture sounds.
/// When to call: After the engine is created [createEngine].
/// Default value: Disable.
/// Caution:
///   1. This setting does not actually take effect until both the headset and microphone are connected.
///   2. The default is to return after acquisition and before pre-processing. If you need to return after pre-processing, please contact ZEGO technical support.
///
/// @param enable Whether to use headphone monitor, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_headphone_monitor(bool enable);

/// Sets the headphone monitor volume.
///
/// Available since: 1.9.0
/// Description: set headphone monitor volume.
/// When to call: After the engine is created [createEngine].
/// Caution: This setting does not actually take effect until both the headset and microphone are connected.
/// Related APIs: Enables or disables headphone monitoring via [enableHeadphoneMonitor].
///
/// @param volume headphone monitor volume, range from 0 to 200, 60 as default.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_headphone_monitor_volume(int volume);

/// Enable or disable system audio capture.
///
/// Available since: 1.9.0
/// Description: Enable sound card capture to mix sounds played by the system into the publishing stream, such as sounds played by the browser, sounds played by the third-party player, etc.
/// Default value: Default is disable.
/// When to call: Called this function after calling [startPublishingStream] or [startPreview].
/// Restrictions: None.
/// Caution: The system sound card sound does not include streaming sound, media player sound and sound effect player sound.
/// Related APIs: [setMixSystemPlayoutVolume] function can set system audio capture volume.
/// Platform differences: Only supports Windows and macOS.
///
/// @param enable Whether to mix system playout.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_mix_system_playout(bool enable);

/// set system audio capture volume.
///
/// Available since: 2.4.0
/// Description:  set system audio capture volume.
/// Use cases: User needs to adjust the volume which system playout mix to stream publishing.
/// When to call /Trigger: Called this function after calling [startPublishingStream] or [startPreview].
/// Restrictions: None.
/// Related APIs: [enableMixSystemPlayout] enable or disable mix system playout.
/// Platform differences: Only supports Windows and macOS.
///
/// @param volume the volume. Valid range [0, 200], default is 100.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_mix_system_playout_volume(int volume);

/// Enable or disable mix SDK playout to stream publishing.
///
/// Available since: 1.0.0
/// Description: Enable mix SDK playout sounds into the stream publishing.
/// Use cases: Users need to mix the sound of SDK playout into stream publishing. For example, when the class scene, the teacher and student Co-hosting, and the teacher can mix the play streaming sound into the publish streaming.
/// Default value: Default is disable.
/// When to call /Trigger: Called this function after calling [startPublishingStream] or [startPreview].
/// Restrictions: None.
/// Platform differences: Only supports Windows and macOS.
///
/// @param enable Whether to mix engine playout
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_mix_engine_playout(bool enable);

/// Start audio VAD stable state monitoring, and the monitoring period can be set.
///
/// Available: since 2.17.0
/// Description: After monitoring is started, you can use the [onAudioVADStateUpdate] callback to receive the specified type of audio VAD callback.
/// Use cases: For example, when you specify the type of collection and use the microphone to collect, you can check whether the host has continuous and stable voice input through this interface.
/// When to call: Before publish stream, you can call [startPreview] with this function and combine it with [onAudioVADStateUpdate] callback to determine whether the audio device is working properly.
/// Restrictions: None.
/// Related APIs: [stopAudioVADStableStateMonitor].
///
/// @param type audio VAD monitor type.
/// @param millisecond monitoring period
ZEGOEXP_API zego_error EXP_CALL zego_express_start_audio_vad_stable_state_monitor(
    enum zego_audio_vad_stable_state_monitor_type type, int millisecond);

/// Stop audio VAD stable state monitoring.
///
/// Available: since 2.14.0
/// Description: After calling this interface, the specified type of [onAudioVADStateUpdate] callback can no longer be received.
/// When to call: None.
/// Restrictions: None.
/// Related APIs: [startAudioVADStableStateMonitor].
///
/// @param type audio VAD monitor type.
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_audio_vad_stable_state_monitor(
    enum zego_audio_vad_stable_state_monitor_type type);

/// The callback triggered when there is a change to audio devices (i.e. new device added or existing device deleted).
///
/// Only supports desktop.
/// This callback is triggered when an audio device is added or removed from the system. By listening to this callback, users can update the sound collection or output using a specific device when necessary.
///
/// @param update_type Update type (add/delete)
/// @param device_type Audio device type
/// @param device_info Audio device information
/// @param user_context Context of user.
typedef void (*zego_on_audio_device_state_changed)(enum zego_update_type update_type,
                                                   enum zego_audio_device_type device_type,
                                                   struct zego_device_info device_info,
                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_audio_device_state_changed_callback(
    zego_on_audio_device_state_changed callback_func, void *user_context);

/// The callback triggered when there is a change of the volume for the audio devices.
///
/// Available since: 1.0.0
/// Description: This callback is used to receive audio device volume change events.
/// When to trigger: The callback triggered when there is a change of the volume fo the audio devices.
/// Restrictions: None
/// Platform differences: Only supports Windows and macOS.
///
/// @param device_type Audio device type
/// @param device_id Audio device ID
/// @param volume audio device volume
/// @param user_context Context of user.
typedef void (*zego_on_audio_device_volume_changed)(enum zego_audio_device_type device_type,
                                                    const char *device_id, int volume,
                                                    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_audio_device_volume_changed_callback(
    zego_on_audio_device_volume_changed callback_func, void *user_context);

/// The callback triggered when there is a change to video devices (i.e. new device added or existing device deleted).
///
/// Available since: 1.0.0
/// Description: By listening to this callback, users can update the video capture using a specific device when necessary.
/// When to trigger: This callback is triggered when a video device is added or removed from the system.
/// Restrictions: None
/// Platform differences: Only supports Windows and macOS.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param update_type Update type (add/delete)
/// @param device_info Audio device information
/// @param user_context Context of user.
typedef void (*zego_on_video_device_state_changed)(enum zego_update_type update_type,
                                                   struct zego_device_info device_info,
                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_video_device_state_changed_callback(
    zego_on_video_device_state_changed callback_func, void *user_context);

/// The local captured audio sound level callback.
///
/// Available since: 1.1.0
/// Description: The local captured audio sound level callback.
/// Trigger: After you start the sound level monitor by calling [startSoundLevelMonitor].
/// Caution:
///   1. The callback notification period is the parameter value set when the [startSoundLevelMonitor] is called. The callback value is the default value of 0 When you have not called the interface [startPublishingStream] or [startPreview].
///   2. This callback is a high-frequency callback, and it is recommended not to do complex logic processing inside the callback.
/// Related APIs: Start sound level monitoring via [startSoundLevelMonitor]. Monitoring remote played audio sound level by callback [onRemoteSoundLevelUpdate]
///
/// @param sound_level Locally captured sound level value, ranging from 0.0 to 100.0.
/// @param user_context Context of user.
typedef void (*zego_on_captured_sound_level_update)(const struct zego_sound_level_info *sound_level,
                                                    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_sound_level_update_callback(
    zego_on_captured_sound_level_update callback_func, void *user_context);

/// The local captured audio sound level callback.
///
/// Available since: 2.10.0
/// Description: The local captured audio sound level callback.
/// Trigger: After you start the sound level monitor by calling [startSoundLevelMonitor].
/// Caution:
///   1. The callback notification period is the parameter value set when the [startSoundLevelMonitor] is called.
///   2. This callback is a high-frequency callback, and it is recommended not to do complex logic processing inside the callback.
/// Related APIs: Start sound level monitoring via [startSoundLevelMonitor]. Monitoring remote played audio sound level by callback [onRemoteSoundLevelUpdate] or [onRemoteSoundLevelInfoUpdate].
///
/// @param sound_level_info Locally captured sound level value, ranging from 0.0 to 100.0.
/// @param user_context Context of user.
typedef void (*zego_on_captured_sound_level_info_update)(
    const struct zego_sound_level_info *sound_level_info, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_sound_level_info_update_callback(
    zego_on_captured_sound_level_info_update callback_func, void *user_context);

/// The remote playing streams audio sound level callback.
///
/// Available since: 1.1.0
/// Description: The remote playing streams audio sound level callback.
/// Trigger: After you start the sound level monitor by calling [startSoundLevelMonitor], you are in the state of playing the stream [startPlayingStream].
/// Caution: The callback notification period is the parameter value set when the [startSoundLevelMonitor] is called.
/// Related APIs: Start sound level monitoring via [startSoundLevelMonitor]. Monitoring local captured audio sound by callback [onCapturedSoundLevelUpdate] or [onCapturedSoundLevelInfoUpdate].
///
/// @param sound_levels Remote sound level hash map, key is the streamID, value is the sound level value of the corresponding streamID, value ranging from 0.0 to 100.0.
/// @param info_count Count of sound level info.
/// @param user_context Context of user.
typedef void (*zego_on_remote_sound_level_update)(const struct zego_sound_level_info *sound_levels,
                                                  unsigned int info_count, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_sound_level_update_callback(
    zego_on_remote_sound_level_update callback_func, void *user_context);

/// The remote playing streams audio sound level callback.
///
/// Available since: 2.10.0
/// Description: The remote playing streams audio sound level callback.
/// Trigger: After you start the sound level monitor by calling [startSoundLevelMonitor], you are in the state of playing the stream [startPlayingStream].
/// Caution: The callback notification period is the parameter value set when the [startSoundLevelMonitor] is called.
/// Related APIs: Start sound level monitoring via [startSoundLevelMonitor]. Monitoring local captured audio sound by callback [onCapturedSoundLevelUpdate] or [onCapturedSoundLevelInfoUpdate].
///
/// @param sound_level_info Remote sound level hash map, key is the streamID, value is the sound level value of the corresponding streamID, value ranging from 0.0 to 100.0.
/// @param info_count Count of sound level info.
/// @param user_context Context of user.
typedef void (*zego_on_remote_sound_level_info_update)(
    const struct zego_sound_level_info *sound_level_info, unsigned int info_count,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_sound_level_info_update_callback(
    zego_on_remote_sound_level_info_update callback_func, void *user_context);

/// The local captured audio spectrum callback.
///
/// Available since: 1.1.0
/// Description: The local captured audio spectrum callback.
/// Trigger: After you start the audio spectrum monitor by calling [startAudioSpectrumMonitor].
/// Caution: The callback notification period is the parameter value set when the [startAudioSpectrumMonitor] is called. The callback value is the default value of 0 When you have not called the interface [startPublishingStream] or [startPreview].
/// Related APIs: Start audio spectrum monitoring via [startAudioSpectrumMonitor]. Monitoring remote played audio spectrum by callback [onRemoteAudioSpectrumUpdate]
///
/// @param audio_spectrum Locally captured audio spectrum value list. Spectrum value range is [0-2^30].
/// @param user_context Context of user.
typedef void (*zego_on_captured_audio_spectrum_update)(
    const struct zego_audio_spectrum_info *audio_spectrum, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_audio_spectrum_update_callback(
    zego_on_captured_audio_spectrum_update callback_func, void *user_context);

/// The remote playing streams audio spectrum callback.
///
/// Available since: 1.1.0
/// Description: The remote playing streams audio spectrum callback.
/// Trigger: After you start the audio spectrum monitor by calling [startAudioSpectrumMonitor], you are in the state of playing the stream [startPlayingStream].
/// Caution: The callback notification period is the parameter value set when the [startAudioSpectrumMonitor] is called.
/// Related APIs: Start audio spectrum monitoring via [startAudioSpectrumMonitor]. Monitoring local played audio spectrum by callback [onCapturedAudioSpectrumUpdate].
///
/// @param audio_spectrums Remote audio spectrum hash map, key is the streamID, value is the audio spectrum list of the corresponding streamID. Spectrum value range is [0-2^30]
/// @param info_count Count of audio spectrum.
/// @param user_context Context of user.
typedef void (*zego_on_remote_audio_spectrum_update)(
    const struct zego_audio_spectrum_info *audio_spectrums, unsigned int info_count,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_audio_spectrum_update_callback(
    zego_on_remote_audio_spectrum_update callback_func, void *user_context);

/// The callback triggered when a local device exception occurred.
///
/// Available since: 2.15.0
/// Description: The callback triggered when a local device exception occurs.
/// Trigger: This callback is triggered when the function of the local audio or video device is abnormal.
///
/// @param exception_type The type of the device exception.
/// @param device_type The type of device where the exception occurred.
/// @param device_id Device ID. Currently, only desktop devices are supported to distinguish different devices; for mobile devices, this parameter will return an empty string.
/// @param user_context Context of user.
typedef void (*zego_on_local_device_exception_occurred)(
    enum zego_device_exception_type exception_type, enum zego_device_type device_type,
    const char *device_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_local_device_exception_occurred_callback(
    zego_on_local_device_exception_occurred callback_func, void *user_context);

/// The callback triggered when the state of the remote camera changes.
///
/// Available since: 1.1.0
/// Description: The callback triggered when the state of the remote camera changes.
/// Use cases: Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the camera device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
/// Trigger: When the state of the remote camera device changes, such as switching the camera, by monitoring this callback, it is possible to obtain an event related to the far-end camera, which can be used to prompt the user that the video may be abnormal.
/// Caution: This callback will not be called back when the remote stream is play from the CDN, or when custom video acquisition is used at the peer.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param stream_id Stream ID.
/// @param state Remote camera status.
/// @param user_context Context of user.
typedef void (*zego_on_remote_camera_state_update)(const char *stream_id,
                                                   enum zego_remote_device_state state,
                                                   void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_camera_state_update_callback(
    zego_on_remote_camera_state_update callback_func, void *user_context);

/// The callback triggered when the state of the remote microphone changes.
///
/// Available since: 1.1.0
/// Description: The callback triggered when the state of the remote microphone changes.
/// Use cases: Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the microphone device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
/// Trigger: When the state of the remote microphone device is changed, such as switching a microphone, etc., by listening to the callback, it is possible to obtain an event related to the remote microphone, which can be used to prompt the user that the audio may be abnormal.
/// Caution: This callback will not be called back when the remote stream is play from the CDN, or when custom audio acquisition is used at the peer (But the stream is not published to the ZEGO RTC server.).
///
/// @param stream_id Stream ID.
/// @param state Remote microphone status.
/// @param user_context Context of user.
typedef void (*zego_on_remote_mic_state_update)(const char *stream_id,
                                                enum zego_remote_device_state state,
                                                void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_mic_state_update_callback(
    zego_on_remote_mic_state_update callback_func, void *user_context);

/// The callback triggered when the state of the remote speaker changes.
///
/// Available since: 1.1.0
/// Description: The callback triggered when the state of the remote microphone changes.
/// Use cases: Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the speaker device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
/// Trigger: When the state of the remote speaker device changes, such as switching the speaker, by monitoring this callback, you can get events related to the remote speaker.
/// Caution: This callback will not be called back when the remote stream is play from the CDN.
///
/// @param stream_id Stream ID.
/// @param state Remote speaker status.
/// @param user_context Context of user.
typedef void (*zego_on_remote_speaker_state_update)(const char *stream_id,
                                                    enum zego_remote_device_state state,
                                                    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_remote_speaker_state_update_callback(
    zego_on_remote_speaker_state_update callback_func, void *user_context);

/// Callback for device's audio route changed.
///
/// Available since: 1.20.0
/// Description: Callback for device's audio route changed.
/// Trigger: This callback will be called when there are changes in audio routing such as earphone plugging, speaker and receiver switching, etc.
///
/// @param audio_route Current audio route.
/// @param user_context Context of user.
typedef void (*zego_on_audio_route_change)(enum zego_audio_route audio_route, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_audio_route_change_callback(
    zego_on_audio_route_change callback_func, void *user_context);

/// Callback for audio VAD  stable state update.
///
/// Available since: 2.14.0
/// Description: Callback for audio VAD  stable state update.
/// When to trigger: the [startAudioVADStableStateMonitor] function must be called to start the audio VAD monitor and you must be in a state where it is publishing the audio and video stream or be in [startPreview] state.
/// Restrictions: The callback notification period is 3 seconds.
/// Related APIs: [startAudioVADStableStateMonitor], [stopAudioVADStableStateMonitor].
///
/// @param type audio VAD monitor type
/// @param state VAD result
/// @param user_context Context of user.
typedef void (*zego_on_audio_vad_state_update)(enum zego_audio_vad_stable_state_monitor_type type,
                                               enum zego_audio_vad_type state, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_audio_vad_state_update_callback(
    zego_on_audio_vad_state_update callback_func, void *user_context);

/// Get the audio device information currently in use.
///
/// Available since: 2.12.0
/// Description: Get the audio device information currently in use.
/// Use cases: Used for scenes that need to manually switch between multiple audio devices.
/// When to call: Called this function after calling [startPublishingStream] or [startPreview].
/// Restrictions: Only supports Windows and macOS.
/// Related APIs: The default audio device ID can be obtained through [getDefaultAudioDeviceID].
///
/// @param device_type Audio device type.Required:Yes.
/// @return Audio device information.
ZEGOEXP_API struct zego_device_info EXP_CALL
zego_express_get_current_audio_device(enum zego_audio_device_type device_type);

/// [Deprecated] Whether to use the built-in speaker to play audio.This function has been deprecated since version 2.3.0 Please use [setAudioRouteToSpeaker] instead.
///
/// This function has been deprecated since version 2.3.0 Please use [setAudioRouteToSpeaker] instead.
/// When you choose not to use the built-in speaker to play sound, that is, set to false, the SDK will select the currently highest priority audio output device to play the sound according to the system schedule
///
/// @deprecated This function has been deprecated since version 2.3.0 Please use [setAudioRouteToSpeaker] instead.
/// @param enable Whether to use the built-in speaker to play sound, true: use the built-in speaker to play sound, false: use the highest priority audio output device scheduled by the current system to play sound
ZEGOEXP_API zego_error EXP_CALL zego_express_set_built_in_speaker_on(bool enable);

/// [Deprecated] The callback triggered when a device exception occurs. Deprecated since 2.15.0, please use [onLocalDeviceExceptionOccurred] instead.
///
/// This callback is triggered when an exception occurs when reading or writing the audio and video device.
///
/// @deprecated Deprecated since 2.15.0, please use [onLocalDeviceExceptionOccurred] instead.
/// @param error_code The error code corresponding to the status change of the playing stream, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param device_id device id. Currently only supports Windows and macOS devices
/// @param device_name device name
/// @param user_context Context of user.
typedef void (*zego_on_device_error)(zego_error error_code, const char *device_id,
                                     const char *device_name, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_device_error_callback(zego_on_device_error callback_func,
                                                              void *user_context);

ZEGO_END_DECLS

#endif
