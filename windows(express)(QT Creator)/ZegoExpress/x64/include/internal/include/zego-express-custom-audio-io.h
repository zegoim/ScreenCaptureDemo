
#ifndef __ZEGO_EXPRESS_CUSTOM_AUDIO_IO_H__
#define __ZEGO_EXPRESS_CUSTOM_AUDIO_IO_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Enable local collection and custom audio processing(before ear return).
///
/// Available since: 1.13.0
/// Description: Enable custom audio processing(before ear return), developers can receive locally collected audio frames through [onProcessCapturedAudioData], and can modify the audio data.
/// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
/// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
/// Restrictions: None.
///
/// @param enable Whether to enable local capture custom audio processing.
/// @param config Custom audio processing configuration.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_capture_processing(
    bool enable, struct zego_custom_audio_process_config *config);

/// Turn on local collection and custom audio processing (after ear return).
///
/// Available since: 1.13.0
/// Description: Enable custom audio processing(after ear return), developers can receive locally collected audio frames through [onProcessCapturedAudioData], and can modify the audio data.
/// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
/// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
/// Restrictions: None.
///
/// @param enable Whether to enable local capture custom audio processing.
/// @param config Custom audio processing configuration.
ZEGOEXP_API zego_error EXP_CALL
zego_express_enable_custom_audio_capture_processing_after_headphone_monitor(
    bool enable, struct zego_custom_audio_process_config *config);

/// Enable custom audio processing for remote playing stream.
///
/// Available since: 1.13.0
/// Description: Enable remote streaming custom audio processing, developers can receive remote streaming audio frames through [onProcessRemoteAudioData], and can modify the audio data.
/// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing before pulling the remote audio data for rendering.
/// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
/// Restrictions: None.
///
/// @param enable Whether to enable custom audio processing for remote playing stream.
/// @param config Custom audio processing configuration.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_remote_processing(
    bool enable, struct zego_custom_audio_process_config *config);

/// Enable custom audio processing for SDK playback audio data.
///
/// Available since: 1.13.0
/// Description: Enable remote streaming custom audio processing, developers can receive remote streaming audio frames through [onProcessRemoteAudioData], and can modify the audio data.
/// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after collecting audio data.
/// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
/// Restrictions: None.
///
/// @param enable Whether to enable custom audio processing for SDK playback audio data.
/// @param config Custom audio processing configuration.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_playback_processing(
    bool enable, struct zego_custom_audio_process_config *config);

/// Enable audio data observering.
///
/// Available since: 1.1.0
/// Description: When custom audio processing is turned on, use this function to turn on audio data callback monitoring.
/// Use cases: When develop need to monitor the original audio.
/// When to call: After creating the engine.
/// Restrictions: None.
///
/// @param observer_bit_mask The callback function bitmask marker for receive audio data, refer to enum [ZegoAudioDataCallbackBitMask], when this param converted to binary, 0b01 that means 1 << 0 for triggering [onCapturedAudioData], 0x10 that means 1 << 1 for triggering [onPlaybackAudioData], 0x100 that means 1 << 2 for triggering [onMixedAudioData], 0x1000 that means 1 << 3 for triggering [onPlayerAudioData]. The masks can be combined to allow different callbacks to be triggered simultaneously.
/// @param param param of audio frame.
ZEGOEXP_API zego_error EXP_CALL zego_express_start_audio_data_observer(
    unsigned int observer_bit_mask, struct zego_audio_frame_param param);

/// Disable audio data observering.
///
/// Available since: 1.1.0
/// Description: Disable audio data observering.
/// Use cases: When develop need to monitor the original audio.
/// When to call: After calling [startAudioDataObserver] to start audio data monitoring.
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_audio_data_observer();

/// Enables the custom audio I/O function (for the specified channel), support PCM, AAC format data.
///
/// Available since: 1.10.0
/// Description: Enable custom audio IO function, support PCM, AAC format data.
/// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
/// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
/// Restrictions: None.
///
/// @param enable Whether to enable custom audio IO, default is false.
/// @param config Custom audio IO config.
/// @param channel Specify the publish channel to enable custom audio IO.
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_custom_audio_io(
    bool enable, struct zego_custom_audio_config *config, enum zego_publish_channel channel);

/// Sends AAC audio data produced by custom audio capture to the SDK (for the specified channel).
///
/// Available since: 2.20.0
/// Description: Sends the captured audio AAC data to the SDK.
/// Use cases: The customer needs to obtain input after acquisition from the existing audio stream, audio file, or customized acquisition system, and hand it over to the SDK for transmission.
/// When to call: After [enableCustomAudioIO] and publishing stream successfully.
/// Restrictions: None.
/// Related APIs: Enable the custom audio IO function [enableCustomAudioIO], and start the push stream [startPublishingStream].
///
/// @param data AAC buffer data.
/// @param data_length The total length of the buffer data.
/// @param config_length The length of AAC specific config (Note: The AAC encoded data length is 'encodedLength = dataLength - configLength').Value range: [0,64]
/// @param reference_time_millisecond The UNIX timestamp of this AAC audio frame in millisecond.
/// @param samples The number of samples for this AAC audio frame.Value range: [480,512,1024,1960,2048].
/// @param param The param of this AAC audio frame.
/// @param channel Publish channel for capturing audio frames.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_audio_capture_aac_data(
    unsigned char *data, unsigned int data_length, unsigned int config_length,
    unsigned long long reference_time_millisecond, unsigned int samples,
    struct zego_audio_frame_param param, enum zego_publish_channel channel);

/// Sends PCM audio data produced by custom audio capture to the SDK (for the specified channel).
///
/// Available since: 1.10.0
/// Description: Sends the captured audio PCM data to the SDK.
/// Use cases: 1.The customer needs to obtain input after acquisition from the existing audio stream, audio file, or customized acquisition system, and hand it over to the SDK for transmission. 2.Customers have their own requirements for special sound processing for PCM input sources. After the sound processing, the input will be sent to the SDK for transmission.
/// When to call: After [enableCustomAudioIO] and publishing stream successfully.
/// Restrictions: None.
/// Related APIs: Enable the custom audio IO function [enableCustomAudioIO], and start the push stream [startPublishingStream].
///
/// @param data PCM buffer data.
/// @param data_length The total length of the buffer data.
/// @param param The param of this PCM audio frame.
/// @param channel Publish channel for capturing audio frames.
ZEGOEXP_API zego_error EXP_CALL zego_express_send_custom_audio_capture_pcm_data(
    unsigned char *data, unsigned int data_length, struct zego_audio_frame_param param,
    enum zego_publish_channel channel);

/// Fetches PCM audio data of the remote stream from the SDK for custom audio rendering.
///
/// Available since: 1.10.0
/// Description: Fetches PCM audio data of the remote stream from the SDK for custom audio rendering, it is recommended to use the system framework to periodically invoke this function to drive audio data rendering.
/// Use cases: When developers have their own rendering requirements, such as special applications or processing and rendering of the original PCM data that are pulled, it is recommended to use the custom audio rendering function of the SDK.
/// When to call: After [enableCustomAudioIO] and playing stream successfully.
/// Restrictions: None.
/// Related APIs: Enable the custom audio IO function [enableCustomAudioIO], and start the play stream [startPlayingStream].
///
/// @param data A block of memory for storing audio PCM data that requires user to manage the memory block's lifecycle, the SDK will copy the audio frame rendering data to this memory block.
/// @param data_length The length of the audio data to be fetch this time (dataLength = duration * sampleRate * channels * 2(16 bit depth i.e. 2 Btye)).
/// @param param Specify the parameters of the fetched audio frame. sampleRate in ZegoAudioFrameParam must assignment
ZEGOEXP_API zego_error EXP_CALL zego_express_fetch_custom_audio_render_pcm_data(
    unsigned char *data, unsigned int data_length, struct zego_audio_frame_param param);

/// Send the PCM audio data customized by the developer to the SDK, which is used as a reference for custom rendering audio to eliminate echo.
///
/// Available since：2.13.0.
/// Description：Developers use the audio device clock as the driver to capture PCM audio data, and use it for custom audio rendering after processing. When submitting for rendering, call this function to send the processed audio data back to the SDK so that the SDK can use it as an echo cancellation reference.
/// Use cases：In entertainment scenarios, it may be necessary to customize the processing of PCM audio data from the remote end, such as synthesizing a background sound and KTV accompaniment before rendering and playing. At the same time, developers are required to send the audio data processed by themselves to the SDK for reference, so that the processed sound effects can be echo canceled after collection.
/// When to call：After calling [fetchCustomAudioRenderPCMData] to fetch and process the PCM audio data, this function is called while submitting to the system for rendering and playback.
/// Restrictions：You must call [setEngineConfig] to enable the external audio data as a reference for this function to take effect. If you need to get the use of the function or the details, please consult ZEGO technical support.
///
/// @param data PCM buffer data
/// @param data_length The total length of the buffer data
/// @param param The param of this PCM audio frame
ZEGOEXP_API zego_error EXP_CALL zego_express_send_reference_audio_pcm_data(
    unsigned char *data, unsigned int data_length, struct zego_audio_frame_param param);

/// Custom audio processing local captured PCM audio frame callback.
///
/// Available: Since 2.13.0
/// Description: In this callback, you can receive the PCM audio frames captured locally after used headphone monitor. Developers can modify the audio frame data, as well as the audio channels and sample rate. The timestamp can be used for data synchronization, such as lyrics, etc. If you need the data after used headphone monitor, please use the [onProcessCapturedAudioDataAfterUsedHeadphoneMonitor] callback.
/// When to trigger: You need to call [enableCustomAudioCaptureProcessing] to enable the function first, and call [startPreivew] or [startPublishingStream] to trigger this callback function.
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param timestamp The audio frame timestamp, starting from 0 when capture is started, the unit is milliseconds.
/// @param user_context Context of user.
typedef void (*zego_on_process_captured_audio_data)(unsigned char *data, unsigned int data_length,
                                                    struct zego_audio_frame_param *param,
                                                    double timestamp, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_process_captured_audio_data_callback(
    zego_on_process_captured_audio_data callback_func, void *user_context);

/// Custom audio processing local captured PCM audio frame callback after used headphone monitor.
///
/// Available: Since 2.13.0
/// Description: In this callback, you can receive the PCM audio frames captured locally after used headphone monitor. Developers can modify the audio frame data, as well as the audio channels and sample rate. The timestamp can be used for data synchronization, such as lyrics, etc.
/// When to trigger: You need to call [enableCustomAudioCaptureProcessingAfterHeadphoneMonitor] to enable the function first, and call [startPreivew] or [startPublishingStream] to trigger this callback function.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format
/// @param data_length Length of the data
/// @param param Parameters of the audio frame
/// @param timestamp The audio frame timestamp, starting from 0 when capture is started, the unit is milliseconds.
/// @param user_context Context of user.
typedef void (*zego_on_process_captured_audio_data_after_used_headphone_monitor)(
    unsigned char *data, unsigned int data_length, struct zego_audio_frame_param *param,
    double timestamp, void *user_context);

ZEGOEXP_API void EXP_CALL
zego_register_process_captured_audio_data_after_used_headphone_monitor_callback(
    zego_on_process_captured_audio_data_after_used_headphone_monitor callback_func,
    void *user_context);

/// Custom audio processing remote playing stream PCM audio frame callback.
///
/// Available: Since 2.13.0
/// Description: In this callback, you can receive the PCM audio frames of remote playing stream. Developers can modify the audio frame data, as well as the audio channels and sample rate. The timestamp can be used for data synchronization, such as lyrics, etc.
/// When to trigger: You need to call [enableCustomAudioRemoteProcessing] to enable the function first, and call [startPlayingStream] to trigger this callback function.
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param stream_id Corresponding stream ID.
/// @param timestamp The audio frame timestamp, starting from 0 when capture is started, the unit is milliseconds.
/// @param user_context Context of user.
typedef void (*zego_on_process_remote_audio_data)(unsigned char *data, unsigned int data_length,
                                                  struct zego_audio_frame_param *param,
                                                  const char *stream_id, double timestamp,
                                                  void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_process_remote_audio_data_callback(
    zego_on_process_remote_audio_data callback_func, void *user_context);

/// Custom audio processing SDK playback PCM audio frame callback.
///
/// Available: Since 2.13.0
/// Description: In this callback, you can receive the SDK playback PCM audio frame. Developers can modify the audio frame data, as well as the audio channels and sample rate. The timestamp can be used for data synchronization, such as lyrics, etc.
/// When to trigger: You need to call [enableCustomAudioPlaybackProcessing] to enable the function first, and call [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer] or [createAudioEffectPlayer] to trigger this callback function.
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param timestamp The audio frame timestamp, starting from 0 when capture is started, the unit is milliseconds (It is effective when there is one and only one stream).
/// @param user_context Context of user.
typedef void (*zego_on_process_playback_audio_data)(unsigned char *data, unsigned int data_length,
                                                    struct zego_audio_frame_param *param,
                                                    double timestamp, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_process_playback_audio_data_callback(
    zego_on_process_playback_audio_data callback_func, void *user_context);

/// The callback for obtaining the audio data captured by the local microphone.
///
/// Available: Since 1.1.0
/// Description: In non-custom audio capture mode, the SDK capture the microphone's sound, but the developer may also need to get a copy of the audio data captured by the SDK is available through this callback.
/// When to trigger: On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [startAudioDataObserver] to set the mask 0b01 that means 1 << 0, this callback will be triggered only when it is in the publishing stream state.
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param user_context Context of user.
typedef void (*zego_on_captured_audio_data)(const unsigned char *data, unsigned int data_length,
                                            struct zego_audio_frame_param param,
                                            void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_captured_audio_data_callback(
    zego_on_captured_audio_data callback_func, void *user_context);

/// The callback for obtaining the audio data of all the streams playback by SDK.
///
/// Available: Since 1.1.0
/// Description: This function will callback all the mixed audio data to be playback. This callback can be used for that you needs to fetch all the mixed audio data to be playback to proccess.
/// When to trigger: On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [startAudioDataObserver] to set the mask 0b10 that means 1 << 1, this callback will be triggered only when it is in the SDK inner audio and video engine started(called the [startPreivew] or [startPlayingStream] or [startPublishingStream]).
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback. When the engine is started in the non-playing stream state or the media player is not used to play the media file, the audio data to be called back is muted audio data.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param user_context Context of user.
typedef void (*zego_on_playback_audio_data)(const unsigned char *data, unsigned int data_length,
                                            struct zego_audio_frame_param param,
                                            void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_playback_audio_data_callback(
    zego_on_playback_audio_data callback_func, void *user_context);

/// The callback for obtaining the mixed audio data. Such mixed auido data are generated by the SDK by mixing the audio data of all the remote playing streams and the auido data captured locally.
///
/// Available: Since 1.1.0
/// Description: The audio data of all playing data is mixed with the data captured by the local microphone before it is sent to the loudspeaker, and calleback out in this way.
/// When to trigger: On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [startAudioDataObserver] to set the mask 0x04, this callback will be triggered only when it is in the publishing stream state or playing stream state.
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param user_context Context of user.
typedef void (*zego_on_mixed_audio_data)(const unsigned char *data, unsigned int data_length,
                                         struct zego_audio_frame_param param, void *user_context);

ZEGOEXP_API void EXP_CALL
zego_register_mixed_audio_data_callback(zego_on_mixed_audio_data callback_func, void *user_context);

/// The callback for obtaining the audio data of each stream.
///
/// Available: Since 1.1.0
/// Description: This function will call back the data corresponding to each playing stream. Different from [onPlaybackAudioData], the latter is the mixed data of all playing streams. If developers need to process a piece of data separately, they can use this callback.
/// When to trigger: On the premise of calling [setAudioDataHandler] to set up listening for this callback, calling [startAudioDataObserver] to set the mask 0x08 that is 1 << 3, and this callback will be triggered when the SDK audio and video engine starts to play the stream.
/// Restrictions: None.
/// Caution: This callback is a high-frequency callback, please do not perform time-consuming operations in this callback.
///
/// @param data Audio data in PCM format.
/// @param data_length Length of the data.
/// @param param Parameters of the audio frame.
/// @param stream_id Corresponding stream ID.
/// @param user_context Context of user.
typedef void (*zego_on_player_audio_data)(const unsigned char *data, unsigned int data_length,
                                          struct zego_audio_frame_param param,
                                          const char *stream_id, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_player_audio_data_callback(
    zego_on_player_audio_data callback_func, void *user_context);

/// [Deprecated] Enables the callback for receiving audio data. This function has been deprecated since version 2.7.0, please use [startAudioDataObserver] and [stopAudioDataObserver] instead.
///
/// This function has been deprecated since version 2.7.0, please use [startAudioDataObserver] and [stopAudioDataObserver] instead.
/// The callback to the corresponding setting of [setAudioDataHandler] is triggered when this function is called and at publishing stream state or playing stream state. If you want to enable the [onPlayerAudioData] callback, the sample rate passed in by calling the [enableAudioDataCallback] function does not support 8000Hz, 22050Hz and 24000Hz.
///
/// @deprecated This function has been deprecated since version 2.7.0, please use [startAudioDataObserver] and [stopAudioDataObserver] instead.
/// @param enable Whether to enable audio data callback
/// @param callback_bit_mask The callback function bitmask marker for receive audio data, refer to enum [ZegoAudioDataCallbackBitMask], when this param converted to binary, 0b01 that means 1 << 0 for triggering [onCapturedAudioData], 0x10 that means 1 << 1 for triggering [onPlaybackAudioData], 0x100 that means 1 << 2 for triggering [onMixedAudioData], 0x1000 that means 1 << 3 for triggering [onPlayerAudioData]. The masks can be combined to allow different callbacks to be triggered simultaneously.
/// @param param param of audio frame
ZEGOEXP_API zego_error EXP_CALL zego_express_enable_audio_data_callback(
    bool enable, unsigned int callback_bit_mask, struct zego_audio_frame_param param);

ZEGO_END_DECLS

#endif
