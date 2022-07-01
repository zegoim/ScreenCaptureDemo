
#ifndef __ZEGO_EXPRESS_ENGINE_H__
#define __ZEGO_EXPRESS_ENGINE_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
/// Create ZegoExpressEngine singleton object and initialize SDK.
///
/// Available since: 2.14.0
/// Description: Create ZegoExpressEngine singleton object and initialize SDK.
/// When to call: The engine needs to be created before calling other functions.
/// Restrictions: None.
/// Caution: The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this function return the same object.
///
/// @param profile The basic configuration information is used to create the engine.
/// @return Zego error code.
ZEGOEXP_API zego_error EXP_CALL
zego_express_engine_init_with_profile(struct zego_engine_profile profile);

/// Destroy the ZegoExpressEngine singleton object and deinitialize the SDK.
///
/// Available since: 1.1.0
/// Description: Destroy the ZegoExpressEngine singleton object and deinitialize the SDK.
/// When to call: When the SDK is no longer used, the resources used by the SDK can be released through this interface
/// Restrictions: None.
/// Caution: After using [createEngine] to create a singleton, if the singleton object has not been created or has been destroyed, you will not receive related callbacks when calling this function.
ZEGOEXP_API zego_error EXP_CALL zego_express_engine_uninit_async(void);

/// Set advanced engine configuration.
///
/// Available since: 1.1.0
/// Description: Used to enable advanced functions.
/// When to call: Different configurations have different call timing requirements. For details, please consult ZEGO technical support.
/// Restrictions: None.
///
/// @param config Advanced engine configuration
ZEGOEXP_API void EXP_CALL zego_express_set_engine_config(struct zego_engine_config config);

/// Set log configuration.
///
/// Available since: 2.3.0
/// Description: If you need to customize the log file size and path, please call this function to complete the configuration.
/// When to call: It must be set before calling [createEngine] to take effect. If it is set after [createEngine], it will take effect at the next [createEngine] after [destroyEngine].
/// Restrictions: None.
/// Caution: Once this interface is called, the method of setting log size and path via [setEngineConfig] will be invalid.Therefore, it is not recommended to use [setEngineConfig] to set the log size and path.
///
/// @param config log configuration.
ZEGOEXP_API void EXP_CALL zego_express_set_log_config(struct zego_log_config config);

/// Set room mode.
///
/// Available since: 2.9.0
/// Description: If you need to use the multi-room feature, please call this function to complete the configuration.
/// When to call: Must be set before calling [createEngine] to take effect, otherwise it will fail.
/// Restrictions: If you need to use the multi-room feature, please contact the instant technical support to configure the server support.
/// Caution: None.
///
/// @param mode Room mode. Description: Used to set the room mode. Use cases: If you need to enter multiple rooms at the same time for publish-play stream, please turn on the multi-room mode through this interface. Required: True. Default value: ZEGO_ROOM_MODE_SINGLE_ROOM.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_room_mode(enum zego_room_mode mode);

/// Gets the SDK's version number.
///
/// Available since: 1.1.0
/// Description: If you encounter an abnormality during the running of the SDK, you can submit the problem, log and other information to the ZEGO technical staff to locate and troubleshoot. Developers can also collect current SDK version information through this API, which is convenient for App operation statistics and related issues.
/// When to call: Any time.
/// Restrictions: None.
/// Caution: None.
///
/// @return SDK version.
ZEGOEXP_API const char *EXP_CALL zego_express_get_version();

/// Sets the JVM and Context for the Android platform.
///
/// Available since: 1.1.0
/// Description: Sets the JVM and Context for the Android platform.
/// When to call: It must be called before calling [createEngine] function.
/// Restrictions: Only available on Android platform.
/// Caution: None.
///
/// @param jvm Java VM Object.
/// @param context Android Context, it must be valid in the SDK lifecycle.
ZEGOEXP_API zego_error EXP_CALL zego_express_set_android_env(void *jvm, void *context);

/// Get the previously set Android context.
///
/// Available since: 1.1.0
/// Description: Get the previously set Android context.
/// When to call: None.
/// Restrictions: Only available on Android platform.
/// Caution: None.
///
/// @return If [setAndroidEnv] has not been called before [createEngine], or if it is not called on the Android platform, it returns NULL.
ZEGOEXP_API void *EXP_CALL zego_express_get_android_context();

/// Uploads logs to the ZEGO server.
///
/// Available since: 1.1.0
/// Description: By default, SDK creates and prints log files in the App's default directory. Each log file defaults to a maximum of 5MB. Three log files are written over and over in a circular fashion. When calling this function, SDK will auto package and upload the log files to the ZEGO server.
/// Use cases: Developers can provide a business “feedback” channel in the App. When users feedback problems, they can call this function to upload the local log information of SDK to help locate user problems.
/// When to call: After [createEngine].
/// Restrictions: If you call this interface repeatedly within 10 minutes, only the last call will take effect.
/// Caution: After calling this interface to upload logs, if you call [destroyEngine] or exit the App too quickly, there may be a failure.It is recommended to wait a few seconds, and then call [destroyEngine] or exit the App after receiving the upload success callback.
ZEGOEXP_API zego_seq EXP_CALL zego_express_upload_log();

/// Enable the debugg assistant. Note, do not enable this feature in the online version! Use only during development phase!
///
/// Available since: 2.17.0
/// Description: After enabled, the SDK will print logs to the console, and will pop-up an alert (toast) UI message when there is a problem with calling other SDK functions.
/// Default value: This function is disabled by default.
/// When to call: This function can be called right after [createEngine].
/// Platform differences: The pop-up alert function only supports Android / iOS / macOS / Windows, and the console log function supports all platforms.
/// Caution: Be sure to confirm that this feature is turned off before the app is released to avoid pop-up UI alert when an error occurs in your release version's app. It is recommended to associate the [enable] parameter of this function with the DEBUG variable of the app, that is, only enable the debugg assistant in the DEBUG environment.
/// Restrictions: None.
///
/// @param enable Whether to enable the debugg assistant.
ZEGOEXP_API void EXP_CALL zego_express_enable_debug_assistant(bool enable);

/// Call the RTC experimental API.
///
/// Available since: 2.7.0
/// Description: ZEGO provides some technical previews or special customization functions in RTC business through this API. If you need to get the use of the function or the details, please consult ZEGO technical support.
/// When to call: After [createEngine].
///
/// @param params You need to pass in a parameter in the form of a JSON string, please consult ZEGO technical support for details.
/// @return Returns an argument in the format of a JSON string, please consult ZEGO technical support for details.
ZEGOEXP_API const char *EXP_CALL zego_express_call_experimental_api(const char *params);

/// Set the path of the static picture would be published when the camera is closed.
///
/// Available: since 2.9.0
/// Description: Set the path of the static picture would be published when enableCamera(false) is called, it would start to publish static pictures, and when enableCamera(true) is called, it would end publishing static pictures.
/// Use case: The developer wants to display a static picture when the camera is closed. For example, when the anchor exits the background, the camera would be actively closed. At this time, the audience side needs to display the image of the anchor temporarily leaving.
/// When to call: After the engine is initialized, call this API to configure the parameters before closing the camera.
/// Restrictions:
///   1. Supported picture types are JPEG/JPG, PNG, BMP, HEIF.
///   2. The function is only for SDK video capture and does not take effect for custom video capture.
///   3. Not supported that the filePath is a network link.
/// Caution:
///   1. The static picture cannot be seen in the local preview.
///   2. External filters, mirroring, watermarks, and snapshots are all invalid.
///   3. If the picture aspect ratio is inconsistent with the set code aspect ratio, it will be cropped according to the code aspect ratio.
/// Platform differences:
///   1. Windows: Fill in the location of the picture directly, such as "D://dir//image.jpg".
///   2. iOS: If it is a full path, add the prefix "file:", such as @"file:/var/image.png"; If it is a assets picture path, add the prefix "asset:", such as @"asset:watermark".
///   3. Android: If it is a full path, add the prefix "file:", such as "file:/sdcard/image.png"; If it is a assets directory path, add the prefix "asset:", such as "asset:watermark.png".
///
/// @param file_path Picture file path
/// @param channel Publish channel.
ZEGOEXP_API zego_error EXP_CALL
zego_express_set_dummy_capture_image_path(const char *file_path, enum zego_publish_channel channel);

/// The callback for obtaining debugging error information.
///
/// Available since: 1.1.0
/// Description: When the SDK functions are not used correctly, the callback prompts for detailed error information.
/// Trigger: Notify the developer when an exception occurs in the SDK.
/// Restrictions: None.
/// Caution: None.
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param func_name Function name.
/// @param info Detailed error information.
/// @param user_context context of user.
typedef void (*zego_on_debug_error)(int error_code, const char *func_name, const char *info,
                                    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_debug_error_callback(zego_on_debug_error callback_func,
                                                             void *user_context);

/// Method execution result callback
///
/// Available since: 2.3.0
/// Description: When the monitoring is turned on through [setApiCalledCallback], the results of the execution of all methods will be called back through this callback.
/// Trigger: When the developer calls the SDK method, the execution result of the method is called back.
/// Restrictions: None.
/// Caution: It is recommended to monitor and process this callback in the development and testing phases, and turn off the monitoring of this callback after going online.
///
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param func_name Function name.
/// @param info Detailed error information.
/// @param user_context context of user.
typedef void (*zego_on_api_called_result)(int error_code, const char *func_name, const char *info,
                                          void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_api_called_result_callback(
    zego_on_api_called_result callback_func, void *user_context);

/// The callback triggered when the audio/video engine state changes.
///
/// Available since: 1.1.0
/// Description: Callback notification of audio/video engine status update. When audio/video functions are enabled, such as preview, push streaming, local media player, audio data observering, etc., the audio/video engine will enter the start state. When you exit the room or disable all audio/video functions , The audio/video engine will enter the stop state.
/// Trigger: The developer called the relevant function to change the state of the audio and video engine. For example: 1. Called ZegoExpressEngine's [startPreview], [stopPreview], [startPublishingStream], [stopPublishingStream], [startPlayingStream], [stopPlayingStream], [startAudioDataObserver], [stopAudioDataObserver] and other functions. 2. The related functions of MediaPlayer are called. 3. The [LogoutRoom] function was called. 4. The related functions of RealTimeSequentialDataManager are called.
/// Restrictions: None.
/// Caution:
///   1. When the developer calls [destroyEngine], this notification will not be triggered because the resources of the SDK are completely released.
///   2. If there is no special need, the developer does not need to pay attention to this callback.
///
/// @param state The audio/video engine state.
/// @param user_context context of user.
typedef void (*zego_on_engine_state_update)(enum zego_engine_state state, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_engine_state_update_callback(
    zego_on_engine_state_update callback_func, void *user_context);

/// Audio and video engine destruction notification callback.
///
/// When you use the asynchronous destruction engine function, you can obtain whether the SDK has completely released resources by listening to this callback.
///
/// @param user_context context of user.
typedef void (*zego_on_engine_uninit)(void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_engine_uninit_callback(zego_on_engine_uninit callback_func,
                                                               void *user_context);

/// Successful callback of network time synchronization..
///
/// Available since: 2.12.0
/// This callback is triggered when internal network time synchronization completes after a developer calls [createEngine].
///
/// @param user_context context of user
typedef void (*zego_on_network_time_synchronized)(void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_network_time_synchronized_callback(
    zego_on_network_time_synchronized callback_func, void *user_context);

/// Receive experiment API JSON content.
///
/// Available since: 2.7.0
/// Description: Receive experiment API JSON content.
/// When to trigger: This callback will triggered after call LiveRoom experiment API.
/// Restrictions: None.
///
/// @param content Experiment API JSON content.
/// @param user_context Context of user.
typedef void (*zego_on_recv_experimental_api)(const char *content, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_recv_experimental_api_callback(
    zego_on_recv_experimental_api callback_func, void *user_context);

/// The network quality callback of users who are publishing in the room.
///
/// Available since: 2.10.0
/// Description: The uplink and downlink network callbacks of the local and remote users, that would be called by default every two seconds for the local and each playing remote user's network quality.
///   Versions 2.10.0 to 2.13.1:
///   1. Developer must both publish and play streams before you receive your own network quality callback.
///   2. When playing a stream, the publish end has a play stream and the publish end is in the room where it is located, then the user's network quality will be received.
///   Version 2.14.0 and above:
///   1. As long as you publish or play a stream, you will receive your own network quality callback.
///   2. When you play a stream, the publish end is in the room where you are, and you will receive the user's network quality.
/// Use case: When the developer wants to analyze the network condition on the link, or wants to know the network condition of local and remote users.
/// When to Trigger: After publishing a stream by called [startPublishingStream] or playing a stream by called [startPlayingStream].
///
/// @param userid User ID, empty means local user
/// @param upstream_quality Upstream network quality
/// @param downstream_quality Downstream network quality
/// @param user_context Context of user.
typedef void (*zego_on_network_quality)(const char *userid,
                                        enum zego_stream_quality_level upstream_quality,
                                        enum zego_stream_quality_level downstream_quality,
                                        void *user_context);

ZEGOEXP_API void EXP_CALL
zego_register_network_quality_callback(zego_on_network_quality callback_func, void *user_context);

/// [Deprecated] Create ZegoExpressEngine singleton object and initialize SDK.
///
/// Available: 1.1.0 ~ 2.13.1, deprecated since 2.14.0, please use the method with the same name without [isTestEnv] parameter instead
/// Description: Create ZegoExpressEngine singleton object and initialize SDK.
/// When to call: The engine needs to be created before calling other functions.
/// Restrictions: None.
/// Caution: The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this function return the same object.
///
/// @deprecated Deprecated since 2.14.0, please use the method with the same name without [isTestEnv] parameter instead.
/// @param app_id Application ID issued by ZEGO for developers, please apply from the ZEGO Admin Console https://console.zegocloud.com The value ranges from 0 to 4294967295.
/// @param app_sign Application signature for each AppID, please apply from the ZEGO Admin Console. Application signature is a 64 character string. Each character has a range of '0' ~ '9', 'a' ~ 'z'. AppSign 2.17.0 and later allows NULL or no transmission. If the token is passed empty or not passed, the token must be entered in the [ZegoRoomConfig] parameter for authentication when the [loginRoom] interface is called to login to the room.
/// @param is_test_env Choose to use a test environment or a formal commercial environment, the formal environment needs to submit work order configuration in the ZEGO management console. The test environment is for test development, with a limit of 10 rooms and 50 users. Official environment App is officially launched. ZEGO will provide corresponding server resources according to the configuration records submitted by the developer in the management console. The test environment and the official environment are two sets of environments and cannot be interconnected.
/// @param scenario The application scenario. Developers can choose one of ZegoScenario based on the scenario of the app they are developing, and the engine will preset a more general setting for specific scenarios based on the set scenario. After setting specific scenarios, developers can still call specific functions to set specific parameters if they have customized parameter settings.
/// @return Zego error code.
ZEGOEXP_API zego_error EXP_CALL zego_express_engine_init(unsigned int app_id, const char *app_sign,
                                                         bool is_test_env,
                                                         enum zego_scenario scenario);

/// [Deprecated] Turns on/off verbose debugging and sets up the log language. This function is deprecated in version 2.3.0, please use [enableDebugAssistant] to achieve the original function.
///
/// This feature is disabled by default and the language of debug information is English.
///
/// @deprecated This function is deprecated in version 2.3.0, please use [enableDebugAssistant] to achieve the original function.
/// @param enable Detailed debugging information switch
/// @param language Debugging information language. Note that Chinese is deprecated, if you need Chinese info, please refer to the document https://docs.zegocloud.com/en/5548.html
ZEGOEXP_API void EXP_CALL zego_express_set_debug_verbose(bool enable, enum zego_language language);

/// Log upload result callback.
///
/// Description: After calling [uploadLog] to upload the log, get the upload result through this callback.
/// Use cases: When uploading logs, in order to determine whether the logs are uploaded successfully, you can get them through this callback.
/// Caution: In the case of poor network, the return time of this callback may be longer.
///
/// @param seq The serial number returned by calling [uploadLog] is used to match calls and callbacks.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param user_context Context of user.
typedef void (*zego_on_upload_log_result)(zego_seq seq, zego_error error_code, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_upload_log_result_callback(
    zego_on_upload_log_result callback_func, void *user_context);

ZEGO_END_DECLS

#endif
