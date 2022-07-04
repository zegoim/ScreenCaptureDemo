
#ifndef __ZEGO_EXPRESS_PREPROCESS_H__
#define __ZEGO_EXPRESS_PREPROCESS_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Whether to enable acoustic echo cancellation (AEC).
///
/// Available since: 1.1.0
/// Description: Turning on echo cancellation, the SDK filters the collected audio data to reduce the echo component in the audio.
/// Use case: When you need to reduce the echo to improve the call quality and user experience, you can turn on this feature.
/// Default value: When this function is not called, iOS turns off echo cancellation by default and other platforms turn on echo cancellation by default
/// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Caution: The AEC function only supports the processing of sounds playbacked through the SDK, such as sounds played by the playing stream, media player, audio effect player, etc.
/// Restrictions: None.
/// Related APIs: Developers can use [enableHeadphoneAEC] to set whether to enable AEC when using headphones, and use [setAECMode] to set the echo cancellation mode.
///
/// @param enable Whether to enable echo cancellation, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_aec(bool enable);

/// Whether to turn on acoustic echo cancellation (AEC) when using the headphone.
///
/// Available since: 1.1.0
/// Description: When [enableAEC] is used to turn on echo cancellation, it is only turned on when the speaker is used for mobile terminal equipment. Call this function if you need to turn echo cancellation on or off when using the headset.
/// Use case: It is common when the mobile device is connected to a external sound card as the audio output source. In order to eliminate the echo in this case, you need to call this function to turn on the echo cancellation.
/// Default value: Android is off by default and iOS is on by default.
/// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Caution: Turning on echo cancellation will increase the ear return delay. On the iOS platform, the SDK cannot distinguish between the headset and the external sound card. If you use this function to turn off the system echo cancellation when using the headset, the sound played by the external sound card will be collected when the user accesses the external sound card.
/// Restrictions: None.
/// Related APIs: When the headset is not used, you can set whether the SDK turns on echo cancellation through [enableAEC].
/// Platform differences: Only supports iOS and Android.
///
/// @param enable Whether to enable, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_headphone_aec(bool enable);

/// Sets the acoustic echo cancellation (AEC) mode.
///
/// Available since: 1.1.0
/// Description: When [enableAEC] is used to enable echo cancellation, this function can be used to switch between different echo cancellation modes to control the degree of echo cancellation.
/// Use case: When the default echo cancellation effect does not meet expectations, this function can be used to adjust the echo cancellation mode.
/// Default value: When this function is not called, the default echo cancellation mode is [Aggressive].
/// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Restrictions: The value set by this function is valid only after the echo cancellation function is turned on.
///
/// @param mode Echo cancellation mode
ZEGOEXP_API zego_error EXP_CALL zego_express_set_aec_mode(enum zego_aec_mode mode);

/// Enables or disables automatic gain control (AGC).
///
/// Available since: 1.1.0
/// Description: After turning on this function, the SDK can automatically adjust the microphone volume to adapt to near and far sound pickups and keep the volume stable.
/// Use case: When you need to ensure volume stability to improve call quality and user experience, you can turn on this feature.
/// Default value: When this function is not called, AGC is enabled by default.
/// When to call: It needs to be called after [createEngine] and before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager]. Note that the Mac needs to be called after [startPreview] and before [startPublishingStream].
/// Restrictions: None.
///
/// @param enable Whether to enable automatic gain control, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_agc(bool enable);

/// Enables or disables active noise suppression (ANS, aka ANC).
///
/// Available since: 1.1.0
/// Description: Enable the noise suppression can reduce the noise in the audio data and make the human voice clearer.
/// Use case: When you need to suppress noise to improve call quality and user experience, you can turn on this feature.
/// Default value: When this function is not called, ANS is enabled by default.
/// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Related APIs: This function has a better suppression effect on continuous noise (such as the sound of rain, white noise). If you need to turn on transient noise suppression, please use [enableTransientANS]. And the noise suppression mode can be set by [setANSMode].
/// Restrictions: None.
///
/// @param enable Whether to enable noise suppression, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_ans(bool enable);

/// Enables or disables transient noise suppression.
///
/// Available since: 1.17.0
/// Description: Enable the transient noise suppression can suppress the noises such as keyboard and desk knocks.
/// Use case: When you need to suppress transient noise to improve call quality and user experience, you can turn on this feature.
/// Default value: When this function is not called, this is disabled by default.
/// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Related APIs: This function will not suppress normal noise after it is turned on. If you need to turn on normal noise suppression, please use [enableANS].
/// Restrictions: None.
///
/// @param enable Whether to enable transient noise suppression, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_transient_ans(bool enable);

/// Sets the automatic noise suppression (ANS) mode.
///
/// Available since: 1.1.0
/// Description: When [enableANS] is used to enable noise suppression, this function can be used to switch between different noise suppression modes to control the degree of noise suppression.
/// Use case: When the default noise suppression effect does not meet expectations, this function can be used to adjust the noise suppression mode.
/// Default value: When this function is not called, the default echo cancellation mode is [Medium].
/// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
/// Restrictions: The value set by this function is valid only after the noise suppression function is turned on.
///
/// @param mode Audio Noise Suppression mode
ZEGOEXP_API zego_error EXP_CALL zego_express_set_ans_mode(enum zego_ans_mode mode);

/// Enables or disables audio mixing function.
///
/// Available since: 1.9.0, will be deprecated soon. It is recommended to use the media player [createMediaPlayer] or the audio effect player [createAudioEffectPlayer] to implement the audio mixing function.
/// Description: After the audio mixing function is turned on, the SDK will mix the audio data prepared by the developer with the audio data collected by the SDK before publishing.
/// Use case: Developers can use this function when they need to mix their own songs, sound effects or other audio data into the publishing stream.
/// Default value: When this function is not called, this is disabled by default.
/// When to call: It needs to be called after [createEngine].
/// Related APIs: After enabling audio mixing, the developer also needs to call [setAudioMixingHandler] to set the audio mixing callback, so as to provide the SDK with the audio data that needs to be mixed in the [onAudioMixingCopyData] callback.
/// Caution: After you start audio mixing, the SDK will play the mixed audio on the local (publisher side) by default. If you do not want to play it locally but only on the remote (player side), please call [muteLocalAudioMixing] to set the local audio mixing mute. Recommend to use audio effect player or media player for audio mixing.
/// Restrictions: None.
///
/// @param enable Whether to enable audio mixting, true: enable, false: disable
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_audio_mixing(bool enable);

/// Mute or resume local playback of the mixing audio.
///
/// Available since: 1.9.0
/// Description: When calling this function to mute the local playback audio mixing, the local (publisher side) will not play the audio provided to the SDK through [onAudioMixingCopyData], but the remote (player side) can still playback it Mix.
/// Use case: When developers need to mix their own songs, sound effects or other audio data into the publishing stream, but the mixed audio only wants to be heard by the remote player, and does not want to be playback locally, you can use this function.
/// Default value: When this function is not called, the default is not mute, which is false.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
///
/// @param mute Whether to mute local audio mixting, true: mute, false: unmute
ZEGOEXP_API zego_error EXP_CALL zego_express_mute_local_audio_mixing(bool mute);

/// Sets the audio mixing output volume for both local playback and the stream to be published.
///
/// Available since: 1.9.0
/// Description: After enabling the audio mixing function through [enableAudioMixing], the developer can use this function to set the volume of the mixing audio to be mixed to SDK.
/// Use case: When developers need to mix their own songs, sound effects or other audio data into the publishing stream, and want to adjust the volume of the mixing audio, you can use this function.
/// When to call: It needs to be called after [createEngine].
/// Caution: This function will set both the mixing audio volume of the local playback and the remote playback at the same time.
/// Related APIs: If you need to set the mixing audio volume for local playback or remote playback separately, please use the function of the same name with the [type] parameter.
/// Restrictions: None.
///
/// @param volume The audio mixing volume, range from 0 to 200, 100 as default.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_audio_mixing_volume(int volume);

/// Sets the audio mixing output volume for either local playback or the stream to published.
///
/// Available since: 1.9.0
/// Description: After enabling the audio mixing function through [enableAudioMixing], the developer can use this function to set the volume of the mixing audio to be mixed to SDK.
/// Use case: When developers need to mix their own songs, sound effects or other audio data into the publishing stream, and want to adjust the volume of the mixing audio, you can use this function.
/// When to call: It needs to be called after [createEngine].
/// Caution: This function can individually set the mixing audio volume of the local playback or the remote playback.
/// Restrictions: None.
///
/// @param volume The audio mixing volume, range from 0 to 200, 100 as default.
/// @param type Local playback volume / Remote playback volume
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_audio_mixing_volume_with_type(int volume, enum zego_volume_type type);

/// Enable the Effects beauty environment.
///
/// Available since: 2.16.0
/// Description: Enable the Effects beauty environment. The SDK uses the specified video frame data type for transmission. The Windows platform only supports video frame raw data, the Apple platform only supports CVPixelBuffer, and the Android platform only supports texture2d.
/// Use cases: It is often used in scenes such as video calls and live broadcasts.
/// Default value: When this function is not called, the beauty environment is not activated by default.
/// When to call: Must be called before calling [startPreview], [startPublishingStream]. If you need to modify the configuration, please call [logoutRoom] to log out of the room first, otherwise it will not take effect.
/// Related APIs: [enableEffectsBeauty] switch beauty, [setEffectsBeautyParam] set beauty parameters.
/// Caution: This beauty function is the basic function. If it does not meet the expectations of the developer, you can use the custom video pre-processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] docking and constructing the AI ​​vision SDK [ZegoEffects] https://doc-zh.zego.im/article/9556 for best results.
/// Restrictions: This function only supports Android system 5.0 and above, Android SDK version 21 and above.
/// Note: This function is only available in ZegoExpressVideo SDK!
ZEGOEXP_API zego_error EXP_CALL zego_express_start_effects_env();

/// Disable the Effects beauty environment.
///
/// Available since: 2.16.0
/// Description: Disable the Effects beauty environment.
/// Use cases: It is often used in scenes such as video calls and live broadcasts.
/// When to call: Must be called before calling [startPreview], [startPublishingStream]. If you need to modify the configuration, please call [logoutRoom] to log out of the room first, otherwise it will not take effect.
/// Related APIs: [enableEffectsBeauty] switch beauty, [setEffectsBeautyParam] set beauty parameters.
/// Caution: This beauty function is the basic function. If it does not meet the expectations of the developer, you can use the custom video pre-processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] docking and constructing the AI ​​vision SDK [ZegoEffects] for best results.
/// Restrictions: This function only supports Android system 5.0 and above, Android SDK version 21 and above.
/// Note: This function is only available in ZegoExpressVideo SDK!
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_effects_env();

/// Enables or disables the beauty effect.
///
/// Available since: 2.16.0
/// Description: Support basic beauty functions, including whiten, rosy, smooth, and sharpen.
/// Use cases: It is often used in scenes such as video calls and live broadcasts.
/// When to call: You must call [startEffectsEnv] to enable the beauty environment before calling this function.
/// Default value: When this function is not called, the beauty effect is not enabled by default.
/// Related APIs: You can call the [setBeautifyOption] function to adjust the beauty parameters.
/// Caution: This beauty function is the basic function. If it does not meet the expectations of the developer, you can use the custom video pre-processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] docking and constructing the AI ​​vision SDK [ZegoEffects] for best results.
/// Restrictions: If this function is used on the Android platform, it only supports 5.0 and above, SDK version 21 and above.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param enable Whether to enable the beauty effect, true is enabled; false is disabled, and the default is false.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_effects_beauty(bool enable);

/// Set beautify param.
///
/// Available since: 2.16.0
/// Description: Set the beauty parameters, including whiten, rosy, smooth, and sharpen.
/// Use cases: It is often used in scenes such as video calls and live broadcasts.
/// When to call: You must call [startEffectsEnv] to enable the beauty environment before calling this function.
/// Related APIs: You can call [enableEffectsBeauty] to turn on or off the beauty function.
/// Restrictions: This function only supports Android system 5.0 and above, Android SDK version 21 and above.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @param param Beauty option param.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_effects_beauty_param(struct zego_effects_beauty_param param);

/// Set the sound equalizer (EQ).
///
/// Available since: 1.12.0
/// Description: Call this function to set the sound equalizer adjust the tone.
/// Use cases: Often used in voice chatroom, KTV.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
///
/// @param band_index Band frequency index, the value range is [0, 9], corresponding to 10 frequency bands, and the center frequencies are [31, 62, 125, 250, 500, 1K, 2K, 4K, 8K, 16K] Hz.
/// @param band_gain Band gain for the index, the value range is [-15, 15]. Default value is 0, if all gain values in all frequency bands are 0, EQ function will be disabled.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_audio_equalizer_gain(int band_index,
                                                                      float band_gain);

/// Setting up the voice changer via preset enumeration.
///
/// Available since: 1.17.0
/// Description: Call this function to use preset voice changer effect.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: Voice changer effect is only effective for SDK captured sound.
/// Related APIs:
/// If you need advanced voice changer effect, please use [setVoiceChangerParam].
/// This function is mutually exclusive with [setReverbPreset]. If used at the same time, it will produce undefined effect.
/// Using ANDROID/ETHEREAL preset voice changer effect will modify reverberation or reverberation echo parameters. Calling [setVoiceChangerParam], [setReverbAdvancedParam], [setReverbEchoParam] may affect the voice changer effect after use these preset voice changer effect.
/// If you need advanced reverb/echo/electronic effects/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setElectronicEffects], [setVoiceChangerParam] together.
///
/// @param preset The voice changer preset enumeration.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_voice_changer_preset(enum zego_voice_changer_preset preset);

/// Setting up the specific voice changer parameters.
///
/// Available since: 1.10.0
/// Description: Call this function to set custom voice changer effect.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: Voice changer effect is only effective for SDK captured sound.
/// Related APIs:
/// [setVoiceChangerPreset] provide a set of preset voice changer effects.
/// If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
///
/// @param param Voice changer parameters.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_voice_changer_param(float param);

/// Setting up the reverberation via preset enumeration.
///
/// Available since: 1.17.0
/// Description: Call this function to set preset reverb effect.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine]. Support call this function to change preset reverb effect during publishing stream.
/// Restrictions: Reverb effect is only effective for SDK captured sound.
/// Related APIs:
/// If you need advanced reverb effect, please use [setReverbAdvancedParam].
/// This function is mutually exclusive with [setVoiceChangerPreset]. If used at the same time, it will produce undefined effects.
/// If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
///
/// @param preset The reverberation preset enumeration.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_reverb_preset(enum zego_reverb_preset preset);

/// Setting up the specific reverberation parameters.
///
/// Available since: 1.10.0
/// Description: Call this function to set preset reverb effect.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: Reverb effect is only effective for SDK captured sound.
/// Caution: Different values dynamically set during publishing stream will take effect. When all parameters are set to 0, the reverberation is turned off.
/// Related APIs:
/// [setReverbPreset] provide a set of preset reverb effects.
/// If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
///
/// @param param Reverb advanced parameter.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_reverb_advanced_param(struct zego_reverb_advanced_param param);

/// Setting up the specific reverberation echo parameters.
///
/// Available since: 1.17.0
/// Description: Call this function to set reverb echo effect. This function can be used with voice changer and reverb to achieve a variety of custom sound effects.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: Reverb echo effect is only effective for SDK captured sound.
/// Related APIs: If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
///
/// @param param The reverberation echo parameter.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_reverb_echo_param(struct zego_reverb_echo_param param);

/// Enable or disable the virtual stereo effect when publishing stream..
///
/// Available since: 1.10.0; Note: Starting from 2.15.0, the angle parameter supports setting -1 to present a all round virtual stereo effect.
/// Description: Call this function to enable / disable the virtual stereo effect when publishing stream.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: Virtual stereo effect is only effective for SDK captured sound.
/// Caution: You need to set up a dual channel with [setAudioConfig] for the virtual stereo to take effect.
///
/// @param enable true to turn on the virtual stereo, false to turn off the virtual stereo.
/// @param angle The angle of the sound source in virtual stereo in the range of -1 ~ 360, with 90 being directly in front, 0 / 180 / 270 corresponding to the rightmost and leftmost respectively. In particular, when set to -1, it is all round virtual stereo effects.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_virtual_stereo(bool enable, int angle);

/// Enable or disable the virtual stereo effect when playing stream.
///
/// Available since: 2.8.0
/// Description: Call this function to enable/disable the virtual stereo effect when playing stream.
/// Use cases: Often used in live broadcasting, voice chatroom and KTV.
/// When to call: It needs to be called after [createEngine].
/// Caution: It can dynamically switch and set angle parameters before and after playing stream. After stopping playing stream, it will automatically reset and disable.
///
/// @param enable true to turn on the virtual stereo, false to turn off the virtual stereo.
/// @param angle The angle of the sound source in virtual stereo in the range of 0 ~ 360, with 90 being directly in front, 0 / 180 / 270 corresponding to the rightmost and leftmost respectively.
/// @param stream_id Stream ID.
ZEGOEXP_API zego_error EXP_CALL
zego_express_enable_play_stream_virtual_stereo(bool enable, int angle, const char *stream_id);

/// Turn on or off the electronic sound effect.
///
/// Available since: 2.13.0
/// Description: Call this function to turn on or off the electronic sound effect.
/// Use cases: Often used in live broadcasting, voice chatroom and sung unaccompanied scenes.
/// Default value: When this function is not called, the electronic sound effect is not enabled by default.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
/// Caution: When the mode parameter is Harmonic Minor, the tonal parameter does not take effect.
/// Related APIs: Common electronic sound effect configurations can be set via [setVoiceChangerPreset].
///
/// @param enable true to turn on the electronic sound effect, false to turn off the electronic sound effect.
/// @param mode Mode of Electronic Effects reference.
/// @param tonal The starting pitch of an electric tone in a given mode, representing 12 semitones in one octave of the sound, in the range [0, 11].
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_electronic_effects(bool enable, enum zego_electronic_effects_mode mode, int tonal);

/// Audio mixing callback.
///
/// Available since: 1.9.0
/// Description: The callback for copying audio data to the SDK for audio mixing. This function should be used together with [enableAudioMixing].
/// Use cases: Developers can use this function when they need to mix their own songs, sound effects or other audio data into the publishing stream.
/// When to trigger: It will triggered after [createEngine], and call [enableAudioMixing] turn on audio mixing, and call [setAudioMixingHandler] set audio mixing callback handler.
/// Restrictions: Supports 16k 32k 44.1k 48k sample rate, mono or dual channel, 16-bit deep PCM audio data.
/// Caution: This callback is a high frequency callback. To ensure the quality of the mixing data, please do not handle time-consuming operations in this callback.
///
/// @param data Audio mixing data. Note that this parameter is an input parameter, and the developer needs to modify the value of each parameter in the struct.
/// @param user_context Context of user.
typedef void (*zego_on_copy_audio_mixing_data)(struct zego_audio_mixing_data *data,
                                               void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_copy_audio_mixing_data_callback(
    zego_on_copy_audio_mixing_data callback_func, void *user_context);

/// Enables or disables the beauty features for the specified publish channel.
///
/// Available since: 1.1.0
/// Description: When developers do not have much need for beauty features, they can use this function to set some very simple beauty effects.
/// When to call: It needs to be called after [createEngine].
/// Default value: When this function is not called, the beauty feature is not enabled by default.
/// Related APIs: After turning on the beauty features, you can call the [setBeautifyOption] function to adjust the beauty parameters.
/// Caution: This beauty feature is very simple and may not meet the developer’s expectations. It is recommended to use the custom video processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] to connect the [ZegoEffects] AI SDK https://docs.zegocloud.com/article/9896 for best results.
/// Restrictions: In the case of using the custom video capture function, since the developer has handle the video data capturing, the SDK is no longer responsible for the video data capturing, so this function is no longer valid. It is also invalid when using the custom video processing function.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @deprecated Deprecated since 2.16.0, please use the [enableEffectsBeauty] function instead.
/// @param feature_bit_mask Beauty features, bitmask format, you can choose to enable several features in [ZegoBeautifyFeature] at the same time
/// @param channel Publishing stream channel
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_beautify(int feature_bit_mask,
                                                             enum zego_publish_channel channel);

/// Set beautify option.
///
/// Available since: 1.1.0
/// Description: set beautify option for specified stream publish channel.
/// Use cases: Often used in video call, live broadcasting.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
/// Caution: In the case of using a custom video capture function, because the developer has taken over the video data capturing, the SDK is no longer responsible for the video data capturing, call this function will not take effect. When using custom video processing, the video data collected by the SDK will be handed over to the business for further processing, call this function will not take effect either.
/// Note: This function is only available in ZegoExpressVideo SDK!
///
/// @deprecated Deprecated since 2.16.0, please use the [setEffectsBeautyParam] function instead.
/// @param option Beautify option.
/// @param channel stream publish channel.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_beautify_option(struct zego_beautify_option option,
                                                                 enum zego_publish_channel channel);

/// [Deprecated] Setting up the specific reverberation parameters. This function has been deprecated since version 1.18.0, please use [setReverbAdvancedParam] instead.
///
/// This function has been deprecated since version 1.18.0, please use [setReverbAdvancedParam] instead.
/// Different values dynamically set during publishing stream will take effect. When all parameters are set to 0, the reverberation is turned off.
/// This function is an advanced version of [setReverbPreset], you can configure the reverb effect by yourself.
/// If you need to configure the reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
///
/// @deprecated This function has been deprecated since version 1.18.0, please use [setReverbAdvancedParam] instead.
/// @param param Reverb parameter
ZEGOEXP_API zego_error EXP_CALL zego_express_set_reverb_param(struct zego_reverb_param param);

ZEGO_END_DECLS

#endif
