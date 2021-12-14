﻿
#ifndef __ZEGOEXPRESSDEFINES_H__
#define __ZEGOEXPRESSDEFINES_H__

#define ZEGO_EXPRESS_VIDEO_SDK 1
#define ZEGO_EXPRESS_AUDIO_SDK 0

#if defined(__APPLE_OS__) || defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#ifdef WIN32
#include <windows.h>
#include <wchar.h>
#include <sstream>
#include <locale>
#include <codecvt>
#define ZegoStrncpy strncpy_s
#endif

#if TARGET_OS_OSX || TARGET_OS_IPHONE
#define ZegoStrncpy strncpy
#endif

#if defined(ANDROID)
#define ZegoStrncpy strncpy
#endif

#if defined(__unix__)
#define ZegoStrncpy strncpy
#include <string.h>
#endif

#ifdef ZEGO_DISABLE_SWTICH_THREAD
#define ZEGO_SWITCH_THREAD_PRE {
#define ZEGO_SWITCH_THREAD_ING }
#else
#ifdef WIN32
#define ZEGO_SWITCH_THREAD_PRE  \
        std::function<void(void)>* pFunc = new std::function<void(void)>;*pFunc = [=](void) {
#define ZEGO_SWITCH_THREAD_ING }; oInternalOriginBridge->postWindowsMessage(pFunc);
#elif TARGET_OS_OSX || TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#define ZEGO_SWITCH_THREAD_PRE dispatch_async(dispatch_get_main_queue(), ^{;
#define ZEGO_SWITCH_THREAD_ING });
#else
#define ZEGO_SWITCH_THREAD_PRE {
#define ZEGO_SWITCH_THREAD_ING }
#endif
#endif

#ifdef __GNUC__
#    define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if GCC_VERSION_AT_LEAST(3,1)
#    define ZEGO_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define ZEGO_DEPRECATED __declspec(deprecated)
#else
#    define ZEGO_DEPRECATED
#endif

#if defined(__ICL) || defined (__INTEL_COMPILER)
#    define ZEGO_DISABLE_DEPRECATION_WARNINGS __pragma(warning(push)) __pragma(warning(disable:1478))
#    define ZEGO_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(pop))
#elif defined(_MSC_VER)
#    define ZEGO_DISABLE_DEPRECATION_WARNINGS __pragma(warning(push)) __pragma(warning(disable:4996))
#    define ZEGO_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(pop))
#else
#    define ZEGO_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#    define ZEGO_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#endif

#define ZEGO_UNUSED_VARIABLE(x) ((void)(x))

#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

namespace ZEGO {
    namespace EXPRESS {

        /** Application scenario. */
        enum ZegoScenario
        {
            /** General scenario */
            ZEGO_SCENARIO_GENERAL = 0,

            /** Communication scenario */
            ZEGO_SCENARIO_COMMUNICATION = 1,

            /** Live scenario */
            ZEGO_SCENARIO_LIVE = 2

        };

        /** Language. */
        enum ZegoLanguage
        {
            /** English */
            ZEGO_LANGUAGE_ENGLISH = 0,

            /** Chinese */
            ZEGO_LANGUAGE_CHINESE = 1

        };

        /** engine state. */
        enum ZegoEngineState
        {
            /** The engine has started */
            ZEGO_ENGINE_STATE_START = 0,

            /** The engine has stoped */
            ZEGO_ENGINE_STATE_STOP = 1

        };

        /** Room state. */
        enum ZegoRoomState
        {
            /** Unconnected state, enter this state before logging in and after exiting the room. If there is a steady state abnormality in the process of logging in to the room, such as AppID and AppSign are incorrect, or if the same user name is logged in elsewhere and the local end is KickOut, it will enter this state. */
            ZEGO_ROOM_STATE_DISCONNECTED = 0,

            /** The state that the connection is being requested. It will enter this state after successful execution login room function. The display of the UI is usually performed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting connection status. */
            ZEGO_ROOM_STATE_CONNECTING = 1,

            /** The status that is successfully connected. Entering this status indicates that the login to the room has been successful. The user can receive the callback notification of the user and the stream information in the room. */
            ZEGO_ROOM_STATE_CONNECTED = 2

        };

        /** Publish channel. */
        enum ZegoPublishChannel
        {
            /** Main publish channel */
            ZEGO_PUBLISH_CHANNEL_MAIN = 0,

            /** Auxiliary publish channel */
            ZEGO_PUBLISH_CHANNEL_AUX = 1

        };

        /** Video rendering fill mode. */
        enum ZegoViewMode
        {
            /** The proportional scaling up, there may be black borders */
            ZEGO_VIEW_MODE_ASPECT_FIT = 0,

            /** The proportional zoom fills the entire View and may be partially cut */
            ZEGO_VIEW_MODE_ASPECT_FILL = 1,

            /** Fill the entire view, the image may be stretched */
            ZEGO_VIEW_MODE_SCALE_TO_FILL = 2

        };

        /** Mirror mode for previewing or playing the of the stream. */
        enum ZegoVideoMirrorMode
        {
            /** The mirror image only for previewing locally. This mode is used by default. */
            ZEGO_VIDEO_MIRROR_MODE_ONLY_PREVIEW_MIRROR = 0,

            /** Both the video previewed locally and the far end playing the stream will see mirror image. */
            ZEGO_VIDEO_MIRROR_MODE_BOTH_MIRROR = 1,

            /** Both the video previewed locally and the far end playing the stream will not see mirror image. */
            ZEGO_VIDEO_MIRROR_MODE_NO_MIRROR = 2,

            /** The mirror image only for far end playing the stream. */
            ZEGO_VIDEO_MIRROR_MODE_ONLY_PUBLISH_MIRROR = 3

        };

        /** SEI type */
        enum ZegoSEIType
        {
            /** Using H.264 SEI (nalu type = 6, payload type = 243) type packaging, this type is not specified by the SEI standard, there is no conflict with the video encoder or the SEI in the video file, users do not need to follow the SEI content Do filtering, SDK uses this type by default. */
            ZEGO_SEI_TYPE_ZEGO_DEFINED = 0,

            /** SEI (nalu type = 6, payload type = 5) of H.264 is used for packaging. The H.264 standard has a prescribed format for this type: startcode + nalu type (6) + payload type (5) + len + payload (uuid + content) + trailing bits. Because the video encoder itself generates an SEI with a payload type of 5, or when a video file is used for streaming, such SEI may also exist in the video file, so when using this type, the user needs to use uuid + context as a buffer sending SEI. At this time, in order to distinguish the SEI generated by the video encoder itself, when the App sends this type of SEI, it can fill in the service-specific uuid (uuid length is 16 bytes). When the receiver uses the SDK to parse the SEI of the payload type 5, it will set filter string filters out the SEI matching the uuid and throws it to the business. If the filter string is not set, the SDK will throw all received SEI to the developer. uuid filter string setting function, [ZegoEngineConfig.advancedConfig("unregister_sei_filter","XXXXXX")], where unregister_sei_filter is the key, and XXXXX is the uuid filter string to be set. */
            ZEGO_SEI_TYPE_USER_UNREGISTER = 1

        };

        /** Publish stream status. */
        enum ZegoPublisherState
        {
            /** The state is not published, and it is in this state before publishing the stream. If a steady-state exception occurs in the publish process, such as AppID and AppSign are incorrect, or if other users are already publishing the stream, there will be a failure and enter this state. */
            ZEGO_PUBLISHER_STATE_NO_PUBLISH = 0,

            /** The state that it is requesting to publish the stream after the [startPublishingStream] function is successfully called. The UI is usually displayed through this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
            ZEGO_PUBLISHER_STATE_PUBLISH_REQUESTING = 1,

            /** The state that the stream is being published, entering the state indicates that the stream has been successfully published, and the user can communicate normally. */
            ZEGO_PUBLISHER_STATE_PUBLISHING = 2

        };

        /** Voice changer preset value. */
        enum ZegoVoiceChangerPreset
        {
            /** No Voice changer */
            ZEGO_VOICE_CHANGER_PRESET_NONE = 0,

            /** Male to child voice (loli voice effect) */
            ZEGO_VOICE_CHANGER_PRESET_MEN_TO_CHILD = 1,

            /** Male to female voice (kindergarten voice effect) */
            ZEGO_VOICE_CHANGER_PRESET_MEN_TO_WOMEN = 2,

            /** Female to child voice */
            ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_CHILD = 3,

            /** Female to male voice */
            ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_MEN = 4,

            /** Foreigner voice effect */
            ZEGO_VOICE_CHANGER_PRESET_FOREIGNER = 5,

            /** Autobot Optimus Prime voice effect */
            ZEGO_VOICE_CHANGER_PRESET_OPTIMUS_PRIME = 6,

            /** Android robot voice effect */
            ZEGO_VOICE_CHANGER_PRESET_ANDROID = 7,

            /** Ethereal voice effect */
            ZEGO_VOICE_CHANGER_PRESET_ETHEREAL = 8,

            /** Magnetic(Male) voice effect */
            ZEGO_VOICE_CHANGER_PRESET_MALE_MAGNETIC = 9,

            /** Fresh(Female) voice effect */
            ZEGO_VOICE_CHANGER_PRESET_FEMALE_FRESH = 10

        };

        /** Reverberation preset value. */
        enum ZegoReverbPreset
        {
            /** No Reverberation */
            ZEGO_REVERB_PRESET_NONE = 0,

            /** Soft room reverb effect */
            ZEGO_REVERB_PRESET_SOFT_ROOM = 1,

            /** Large room reverb effect */
            ZEGO_REVERB_PRESET_LARGE_ROOM = 2,

            /** Concer hall reverb effect */
            ZEGO_REVERB_PRESET_CONCER_HALL = 3,

            /** Valley reverb effect */
            ZEGO_REVERB_PRESET_VALLEY = 4,

            /** Recording studio reverb effect */
            ZEGO_REVERB_PRESET_RECORDING_STUDIO = 5,

            /** Basement reverb effect */
            ZEGO_REVERB_PRESET_BASEMENT = 6,

            /** KTV reverb effect */
            ZEGO_REVERB_PRESET_KTV = 7,

            /** Popular reverb effect */
            ZEGO_REVERB_PRESET_POPULAR = 8,

            /** Rock reverb effect */
            ZEGO_REVERB_PRESET_ROCK = 9,

            /** Vocal concert reverb effect */
            ZEGO_REVERB_PRESET_VOCAL_CONCERT = 10

        };

        /** Video configuration resolution and bitrate preset enumeration. The preset resolutions are adapted for mobile and desktop. On mobile, height is longer than width, and desktop is the opposite. For example, 1080p is actually 1080(w) x 1920(h) on mobile and 1920(w) x 1080(h) on desktop. */
        enum ZegoVideoConfigPreset
        {
            /** Set the resolution to 320x180, the default is 15 fps, the code rate is 300 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_180P = 0,

            /** Set the resolution to 480x270, the default is 15 fps, the code rate is 400 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_270P = 1,

            /** Set the resolution to 640x360, the default is 15 fps, the code rate is 600 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_360P = 2,

            /** Set the resolution to 960x540, the default is 15 fps, the code rate is 1200 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_540P = 3,

            /** Set the resolution to 1280x720, the default is 15 fps, the code rate is 1500 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_720P = 4,

            /** Set the resolution to 1920x1080, the default is 15 fps, the code rate is 3000 kbps */
            ZEGO_VIDEO_CONFIG_PRESET_1080P = 5

        };

        /** Stream quality level. */
        enum ZegoStreamQualityLevel
        {
            /** Excellent */
            ZEGO_STREAM_QUALITY_LEVEL_EXCELLENT = 0,

            /** Good */
            ZEGO_STREAM_QUALITY_LEVEL_GOOD = 1,

            /** Normal */
            ZEGO_STREAM_QUALITY_LEVEL_MEDIUM = 2,

            /** Bad */
            ZEGO_STREAM_QUALITY_LEVEL_BAD = 3,

            /** Failed */
            ZEGO_STREAM_QUALITY_LEVEL_DIE = 4

        };

        /** Audio channel type. */
        enum ZegoAudioChannel
        {
            /** Unknown */
            ZEGO_AUDIO_CHANNEL_UNKNOWN = 0,

            /** Mono */
            ZEGO_AUDIO_CHANNEL_MONO = 1,

            /** Stereo */
            ZEGO_AUDIO_CHANNEL_STEREO = 2

        };

        /** Audio capture stereo mode. */
        enum ZegoAudioCaptureStereoMode
        {
            /** Disable capture stereo, i.e. capture mono */
            ZEGO_AUDIO_CAPTURE_STEREO_MODE_NONE = 0,

            /** Always enable capture stereo */
            ZEGO_AUDIO_CAPTURE_STEREO_MODE_ALWAYS = 1,

            /** Adaptive mode, capture stereo when publishing stream only, capture mono when publishing and playing stream (e.g. talk/intercom scenes) */
            ZEGO_AUDIO_CAPTURE_STEREO_MODE_ADAPTIVE = 2

        };

        /** Audio Codec ID. */
        enum ZegoAudioCodecID
        {
            /** default */
            ZEGO_AUDIO_CODEC_ID_DEFAULT = 0,

            /** Normal */
            ZEGO_AUDIO_CODEC_ID_NORMAL = 1,

            /** Normal2 */
            ZEGO_AUDIO_CODEC_ID_NORMAL2 = 2,

            /** Normal3 */
            ZEGO_AUDIO_CODEC_ID_NORMAL3 = 3,

            /** Low */
            ZEGO_AUDIO_CODEC_ID_LOW = 4,

            /** Low2 */
            ZEGO_AUDIO_CODEC_ID_LOW2 = 5,

            /** Low3 */
            ZEGO_AUDIO_CODEC_ID_LOW3 = 6

        };

        /** Video codec ID. */
        enum ZegoVideoCodecID
        {
            /** Default (H.264) */
            ZEGO_VIDEO_CODEC_ID_DEFAULT = 0,

            /** Scalable Video Coding (H.264 SVC) */
            ZEGO_VIDEO_CODEC_ID_SVC = 1,

            /** VP8 */
            ZEGO_VIDEO_CODEC_ID_VP8 = 2,

            /** H.265 */
            ZEGO_VIDEO_CODEC_ID_H265 = 3

        };

        /** Video screen rotation direction. */
        enum ZegoOrientation
        {
            /** Not rotate */
            ZEGO_ORIENTATION_0 = 0,

            /** Rotate 90 degrees counterclockwise */
            ZEGO_ORIENTATION_90 = 1,

            /** Rotate 180 degrees counterclockwise */
            ZEGO_ORIENTATION_180 = 2,

            /** Rotate 270 degrees counterclockwise */
            ZEGO_ORIENTATION_270 = 3

        };

        /** Player video layer. */
        enum ZegoPlayerVideoLayer
        {
            /** The layer to be played depends on the network status */
            ZEGO_PLAYER_VIDEO_LAYER_AUTO = 0,

            /** Play the base layer (small resolution) */
            ZEGO_PLAYER_VIDEO_LAYER_BASE = 1,

            /** Play the extend layer (big resolution) */
            ZEGO_PLAYER_VIDEO_LAYER_BASE_EXTEND = 2

        };

        /** Audio echo cancellation mode. */
        enum ZegoAECMode
        {
            /** Aggressive echo cancellation may affect the sound quality slightly, but the echo will be very clean */
            ZEGO_AEC_MODE_AGGRESSIVE = 0,

            /** Moderate echo cancellation, which may slightly affect a little bit of sound, but the residual echo will be less */
            ZEGO_AEC_MODE_MEDIUM = 1,

            /** Comfortable echo cancellation, that is, echo cancellation does not affect the sound quality of the sound, and sometimes there may be a little echo, but it will not affect the normal listening. */
            ZEGO_AEC_MODE_SOFT = 2

        };

        /** Active Noise Suppression mode. */
        enum ZegoANSMode
        {
            /** Soft ANS */
            ZEGO_ANS_MODE_SOFT = 0,

            /** Medium ANS */
            ZEGO_ANS_MODE_MEDIUM = 1,

            /** Aggressive ANS */
            ZEGO_ANS_MODE_AGGRESSIVE = 2

        };

        /** Traffic control property (bitmask enumeration). */
        enum ZegoTrafficControlProperty
        {
            /** Basic */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_BASIC = 0,

            /** Adaptive FPS */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_ADAPTIVE_FPS = 1,

            /** Adaptive resolution */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_ADAPTIVE_RESOLUTION = 1 << 1,

            /** Adaptive Audio bitrate */
            ZEGO_TRAFFIC_CONTROL_PROPERTY_ADAPTIVE_AUDIO_BITRATE = 1 << 2

        };

        /** Video transmission mode when current bitrate is lower than the set minimum bitrate. */
        enum ZegoTrafficControlMinVideoBitrateMode
        {
            /** Stop video transmission when current bitrate is lower than the set minimum bitrate */
            ZEGO_TRAFFIC_CONTROL_MIN_VIDEO_BITRATE_MODE_NO_VIDEO = 0,

            /** Video is sent at a very low frequency (no more than 2fps) which is lower than the set minimum bitrate */
            ZEGO_TRAFFIC_CONTROL_MIN_VIDEO_BITRATE_MODE_ULTRA_LOW_FPS = 1

        };

        /** Playing stream status. */
        enum ZegoPlayerState
        {
            /** The state of the flow is not played, and it is in this state before the stream is played. If the steady flow anomaly occurs during the playing process, such as AppID and AppSign are incorrect, it will enter this state. */
            ZEGO_PLAYER_STATE_NO_PLAY = 0,

            /** The state that the stream is being requested for playing. After the [startPlayingStream] function is successfully called, it will enter the state. The UI is usually displayed through this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
            ZEGO_PLAYER_STATE_PLAY_REQUESTING = 1,

            /** The state that the stream is being playing, entering the state indicates that the stream has been successfully played, and the user can communicate normally. */
            ZEGO_PLAYER_STATE_PLAYING = 2

        };

        /** Media event when playing. */
        enum ZegoPlayerMediaEvent
        {
            /** Audio stuck event when playing */
            ZEGO_PLAYER_MEDIA_EVENT_AUDIO_BREAK_OCCUR = 0,

            /** Audio stuck event recovery when playing */
            ZEGO_PLAYER_MEDIA_EVENT_AUDIO_BREAK_RESUME = 1,

            /** Video stuck event when playing */
            ZEGO_PLAYER_MEDIA_EVENT_VIDEO_BREAK_OCCUR = 2,

            /** Video stuck event recovery when playing */
            ZEGO_PLAYER_MEDIA_EVENT_VIDEO_BREAK_RESUME = 3

        };

        /** Stream Resource Mode */
        enum ZegoStreamResourceMode
        {
            /** Default mode. The SDK will automatically select the streaming resource according to the cdnConfig parameters set by the player config and the ready-made background configuration. */
            ZEGO_STREAM_RESOURCE_MODE_DEFAULT = 0,

            /** Playing stream only from CDN. */
            ZEGO_STREAM_RESOURCE_MODE_ONLY_CDN = 1,

            /** Playing stream only from L3. */
            ZEGO_STREAM_RESOURCE_MODE_ONLY_L3 = 2,

            /** Playing stream only from RTC. */
            ZEGO_STREAM_RESOURCE_MODE_ONLY_RTC = 3

        };

        /** Update type. */
        enum ZegoUpdateType
        {
            /** Add */
            ZEGO_UPDATE_TYPE_ADD = 0,

            /** Delete */
            ZEGO_UPDATE_TYPE_DELETE = 1

        };

        /** State of CDN relay. */
        enum ZegoStreamRelayCDNState
        {
            /** The state indicates that there is no CDN relay */
            ZEGO_STREAM_RELAY_CDN_STATE_NO_RELAY = 0,

            /** The CDN relay is being requested */
            ZEGO_STREAM_RELAY_CDN_STATE_RELAY_REQUESTING = 1,

            /** Entering this status indicates that the CDN relay has been successful */
            ZEGO_STREAM_RELAY_CDN_STATE_RELAYING = 2

        };

        /** Reason for state of CDN relay changed. */
        enum ZegoStreamRelayCDNUpdateReason
        {
            /** No error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_NONE = 0,

            /** Server error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_SERVER_ERROR = 1,

            /** Handshake error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_HANDSHAKE_FAILED = 2,

            /** Access point error */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_ACCESS_POINT_ERROR = 3,

            /** Stream create failure */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_CREATE_STREAM_FAILED = 4,

            /** Bad name */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_BAD_NAME = 5,

            /** CDN server actively disconnected */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_CDN_SERVER_DISCONNECTED = 6,

            /** Active disconnect */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_DISCONNECTED = 7,

            /** All mixer input streams sessions closed */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_MIX_STREAM_ALL_INPUT_STREAM_CLOSED = 8,

            /** All mixer input streams have no data */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_MIX_STREAM_ALL_INPUT_STREAM_NO_DATA = 9,

            /** Internal error of stream mixer server */
            ZEGO_STREAM_RELAY_CDN_UPDATE_REASON_MIX_STREAM_SERVER_INTERNAL_ERROR = 10

        };

        /** Remote device status. */
        enum ZegoRemoteDeviceState
        {
            /** Device on */
            ZEGO_REMOTE_DEVICE_STATE_OPEN = 0,

            /** General device error */
            ZEGO_REMOTE_DEVICE_STATE_GENERIC_ERROR = 1,

            /** Invalid device ID */
            ZEGO_REMOTE_DEVICE_STATE_INVALID_ID = 2,

            /** No permission */
            ZEGO_REMOTE_DEVICE_STATE_NO_AUTHORIZATION = 3,

            /** Captured frame rate is 0 */
            ZEGO_REMOTE_DEVICE_STATE_ZERO_FPS = 4,

            /** The device is occupied */
            ZEGO_REMOTE_DEVICE_STATE_IN_USE_BY_OTHER = 5,

            /** The device is not plugged in or unplugged */
            ZEGO_REMOTE_DEVICE_STATE_UNPLUGGED = 6,

            /** The system needs to be restarted */
            ZEGO_REMOTE_DEVICE_STATE_REBOOT_REQUIRED = 7,

            /** System media services stop, such as under the iOS platform, when the system detects that the current pressure is huge (such as playing a lot of animation), it is possible to disable all media related services. */
            ZEGO_REMOTE_DEVICE_STATE_SYSTEM_MEDIA_SERVICES_LOST = 8,

            /** Capturing disabled */
            ZEGO_REMOTE_DEVICE_STATE_DISABLE = 9,

            /** The remote device is muted */
            ZEGO_REMOTE_DEVICE_STATE_MUTE = 10,

            /** The device is interrupted, such as a phone call interruption, etc. */
            ZEGO_REMOTE_DEVICE_STATE_INTERRUPTION = 11,

            /** There are multiple apps at the same time in the foreground, such as the iPad app split screen, the system will prohibit all apps from using the camera. */
            ZEGO_REMOTE_DEVICE_STATE_IN_BACKGROUND = 12,

            /** CDN server actively disconnected */
            ZEGO_REMOTE_DEVICE_STATE_MULTI_FOREGROUND_APP = 13,

            /** The system is under high load pressure and may cause abnormal equipment. */
            ZEGO_REMOTE_DEVICE_STATE_BY_SYSTEM_PRESSURE = 14

        };

        /** Audio device type. */
        enum ZegoAudioDeviceType
        {
            /** Audio input type */
            ZEGO_AUDIO_DEVICE_TYPE_INPUT = 0,

            /** Audio output type */
            ZEGO_AUDIO_DEVICE_TYPE_OUTPUT = 1

        };

        /** Audio route */
        enum ZegoAudioRoute
        {
            /** Speaker */
            ZEGO_AUDIO_ROUTE_SPEAKER = 0,

            /** Headphone */
            ZEGO_AUDIO_ROUTE_HEADPHONE = 1,

            /** Bluetooth device */
            ZEGO_AUDIO_ROUTE_BLUETOOTH = 2,

            /** Receiver */
            ZEGO_AUDIO_ROUTE_RECEIVER = 3,

            /** External USB audio device */
            ZEGO_AUDIO_ROUTE_EXTERNAL_USB = 4,

            /** Apple AirPlay */
            ZEGO_AUDIO_ROUTE_AIR_PLAY = 5

        };

        /** Mix stream content type. */
        enum ZegoMixerInputContentType
        {
            /** Mix stream for audio only */
            ZEGO_MIXER_INPUT_CONTENT_TYPE_AUDIO = 0,

            /** Mix stream for both audio and video */
            ZEGO_MIXER_INPUT_CONTENT_TYPE_VIDEO = 1

        };

        /** Capture pipeline scale mode. */
        enum ZegoCapturePipelineScaleMode
        {
            /** Zoom immediately after acquisition, default */
            ZEGO_CAPTURE_PIPELINE_SCALE_MODE_PRE = 0,

            /** Scaling while encoding */
            ZEGO_CAPTURE_PIPELINE_SCALE_MODE_POST = 1

        };

        /** Video frame format. */
        enum ZegoVideoFrameFormat
        {
            /** Unknown format, will take platform default */
            ZEGO_VIDEO_FRAME_FORMAT_UNKNOWN = 0,

            /** I420 (YUV420Planar) format */
            ZEGO_VIDEO_FRAME_FORMAT_I420 = 1,

            /** NV12 (YUV420SemiPlanar) format */
            ZEGO_VIDEO_FRAME_FORMAT_NV12 = 2,

            /** NV21 (YUV420SemiPlanar) format */
            ZEGO_VIDEO_FRAME_FORMAT_NV21 = 3,

            /** BGRA32 format */
            ZEGO_VIDEO_FRAME_FORMAT_BGRA32 = 4,

            /** RGBA32 format */
            ZEGO_VIDEO_FRAME_FORMAT_RGBA32 = 5,

            /** ARGB32 format */
            ZEGO_VIDEO_FRAME_FORMAT_ARGB32 = 6,

            /** ABGR32 format */
            ZEGO_VIDEO_FRAME_FORMAT_ABGR32 = 7,

            /** I422 (YUV422Planar) format */
            ZEGO_VIDEO_FRAME_FORMAT_I422 = 8

        };

        /** Video encoded frame format. */
        enum ZegoVideoEncodedFrameFormat
        {
            /** AVC AVCC format */
            ZEGO_VIDEO_ENCODED_FRAME_FORMAT_AVCC = 0,

            /** AVC Annex-B format */
            ZEGO_VIDEO_ENCODED_FRAME_FORMAT_ANNEXB = 1

        };

        /** Video frame buffer type. */
        enum ZegoVideoBufferType
        {
            /** Raw data type video frame */
            ZEGO_VIDEO_BUFFER_TYPE_UNKNOWN = 0,

            /** Raw data type video frame */
            ZEGO_VIDEO_BUFFER_TYPE_RAW_DATA = 1,

            /** Encoded data type video frame */
            ZEGO_VIDEO_BUFFER_TYPE_ENCODED_DATA = 2

        };

        /** Video frame format series. */
        enum ZegoVideoFrameFormatSeries
        {
            /** RGB series */
            ZEGO_VIDEO_FRAME_FORMAT_SERIES_RGB = 0,

            /** YUV series */
            ZEGO_VIDEO_FRAME_FORMAT_SERIES_YUV = 1

        };

        /** Video frame flip mode. */
        enum ZegoVideoFlipMode
        {
            /** No flip */
            ZEGO_VIDEO_FLIP_MODE_NONE = 0,

            /** X-axis flip */
            ZEGO_VIDEO_FLIP_MODE_X = 1,

            /** Y-axis flip */
            ZEGO_VIDEO_FLIP_MODE_Y = 2,

            /** X-Y-axis flip */
            ZEGO_VIDEO_FLIP_MODE_XY = 3

        };

        /** Customize the audio processing configuration type. */
        enum ZegoCustomAudioProcessType
        {
            /** Remote audio processing */
            ZEGO_CUSTOM_AUDIO_PROCESS_TYPE_REMOTE = 0,

            /** Capture audio processing */
            ZEGO_CUSTOM_AUDIO_PROCESS_TYPE_CAPTURE = 1,

            /** Remote audio and capture audio processing */
            ZEGO_CUSTOM_AUDIO_PROCESS_TYPE_CAPTURE_AND_REMOTE = 2

        };

        /** Audio Config Preset. */
        enum ZegoAudioConfigPreset
        {
            /** Basic sound quality (16 kbps, Mono, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_BASIC_QUALITY = 0,

            /** Standard sound quality (48 kbps, Mono, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY = 1,

            /** Standard sound quality (56 kbps, Stereo, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY_STEREO = 2,

            /** High sound quality (128 kbps, Mono, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY = 3,

            /** High sound quality (192 kbps, Stereo, ZegoAudioCodecIDDefault) */
            ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY_STEREO = 4

        };

        /** Player state. */
        enum ZegoMediaPlayerState
        {
            /** Not playing */
            ZEGO_MEDIA_PLAYER_STATE_NO_PLAY = 0,

            /** Playing */
            ZEGO_MEDIA_PLAYER_STATE_PLAYING = 1,

            /** Pausing */
            ZEGO_MEDIA_PLAYER_STATE_PAUSING = 2,

            /** End of play */
            ZEGO_MEDIA_PLAYER_STATE_PLAY_ENDED = 3

        };

        /** Player network event. */
        enum ZegoMediaPlayerNetworkEvent
        {
            /** Network resources are not playing well, and start trying to cache data */
            ZEGO_MEDIA_PLAYER_NETWORK_EVENT_BUFFER_BEGIN = 0,

            /** Network resources can be played smoothly */
            ZEGO_MEDIA_PLAYER_NETWORK_EVENT_BUFFER_ENDED = 1

        };

        /** Audio channel. */
        enum ZegoMediaPlayerAudioChannel
        {
            /** Audio channel left */
            ZEGO_MEDIA_PLAYER_AUDIO_CHANNEL_LEFT = 0,

            /** Audio channel right */
            ZEGO_MEDIA_PLAYER_AUDIO_CHANNEL_RIGHT = 1,

            /** Audio channel all */
            ZEGO_MEDIA_PLAYER_AUDIO_CHANNEL_ALL = 2

        };

        /** AudioEffectPlayer state. */
        enum ZegoAudioEffectPlayState
        {
            /** Not playing */
            ZEGO_AUDIO_EFFECT_PLAY_STATE_NO_PLAY = 0,

            /** Playing */
            ZEGO_AUDIO_EFFECT_PLAY_STATE_PLAYING = 1,

            /** Pausing */
            ZEGO_AUDIO_EFFECT_PLAY_STATE_PAUSING = 2,

            /** End of play */
            ZEGO_AUDIO_EFFECT_PLAY_STATE_PLAY_ENDED = 3

        };

        /** volume type. */
        enum ZegoVolumeType
        {
            /** volume local */
            ZEGO_VOLUME_TYPE_LOCAL = 0,

            /** volume remote */
            ZEGO_VOLUME_TYPE_REMOTE = 1

        };

        /** audio sample rate. */
        enum ZegoAudioSampleRate
        {
            /** Unknown */
            ZEGO_AUDIO_SAMPLE_RATE_UNKNOWN = 0,

            /** 8K */
            ZEGO_AUDIO_SAMPLE_RATE_8K = 8000,

            /** 16K */
            ZEGO_AUDIO_SAMPLE_RATE_16K = 16000,

            /** 22.05K */
            ZEGO_AUDIO_SAMPLE_RATE_22K = 22050,

            /** 24K */
            ZEGO_AUDIO_SAMPLE_RATE_24K = 24000,

            /** 32K */
            ZEGO_AUDIO_SAMPLE_RATE_32K = 32000,

            /** 44.1K */
            ZEGO_AUDIO_SAMPLE_RATE_44K = 44100,

            /** 48K */
            ZEGO_AUDIO_SAMPLE_RATE_48K = 48000

        };

        /** Audio capture source type. */
        enum ZegoAudioSourceType
        {
            /** Default audio capture source (the main channel uses custom audio capture by default; the aux channel uses the same sound as main channel by default) */
            ZEGO_AUDIO_SOURCE_TYPE_DEFAULT = 0,

            /** Use custom audio capture, refer to [enableCustomAudioIO] */
            ZEGO_AUDIO_SOURCE_TYPE_CUSTOM = 1,

            /** Use media player as audio source, only support aux channel */
            ZEGO_AUDIO_SOURCE_TYPE_MEDIA_PLAYER = 2

        };

        /** Record type. */
        enum ZegoDataRecordType
        {
            /** This field indicates that the Express-Audio SDK records audio by default, and the Express-Video SDK records audio and video by default. When recording files in .aac format, audio is also recorded by default. */
            ZEGO_DATA_RECORD_TYPE_DEFAULT = 0,

            /** only record audio */
            ZEGO_DATA_RECORD_TYPE_ONLY_AUDIO = 1,

            /** only record video, Audio SDK and recording .aac format files are invalid. */
            ZEGO_DATA_RECORD_TYPE_ONLY_VIDEO = 2,

            /** record audio and video. Express-Audio SDK and .aac format files are recorded only audio. */
            ZEGO_DATA_RECORD_TYPE_AUDIO_AND_VIDEO = 3

        };

        /** Record state. */
        enum ZegoDataRecordState
        {
            /** Unrecorded state, which is the state when a recording error occurs or before recording starts. */
            ZEGO_DATA_RECORD_STATE_NO_RECORD = 0,

            /** Recording in progress, in this state after successfully call [startRecordingCapturedData] function */
            ZEGO_DATA_RECORD_STATE_RECORDING = 1,

            /** Record successs */
            ZEGO_DATA_RECORD_STATE_SUCCESS = 2

        };

        /** Audio data callback function enable bitmask enumeration. */
        enum ZegoAudioDataCallbackBitMask
        {
            /** The mask bit of this field corresponds to the enable [onCapturedAudioData] callback function */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_CAPTURED = 1 << 0,

            /** The mask bit of this field corresponds to the enable [onPlaybackAudioData] callback function */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_PLAYBACK = 1 << 1,

            /** The mask bit of this field corresponds to the enable [onMixedAudioData] callback function */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_MIXED = 1 << 2,

            /** The mask bit of this field corresponds to the enable [onPlayerAudioData] callback function */
            ZEGO_AUDIO_DATA_CALLBACK_BIT_MASK_PLAYER = 1 << 3

        };

        /** Network mode */
        enum ZegoNetworkMode
        {
            /** Offline (No network) */
            ZEGO_NETWORK_MODE_OFFLINE = 0,

            /** Unknown network mode */
            ZEGO_NETWORK_MODE_UNKNOWN = 1,

            /** Wired Ethernet (LAN) */
            ZEGO_NETWORK_MODE_ETHERNET = 2,

            /** Wi-Fi (WLAN) */
            ZEGO_NETWORK_MODE_WIFI = 3,

            /** 2G Network (GPRS/EDGE/CDMA1x/etc.) */
            ZEGO_NETWORK_MODE_2G = 4,

            /** 3G Network (WCDMA/HSDPA/EVDO/etc.) */
            ZEGO_NETWORK_MODE_3G = 5,

            /** 4G Network (LTE) */
            ZEGO_NETWORK_MODE_4G = 6,

            /** 5G Network (NR (NSA/SA)) */
            ZEGO_NETWORK_MODE_5G = 7

        };

        /** network speed test type */
        enum ZegoNetworkSpeedTestType
        {
            /** uplink */
            ZEGO_NETWORK_SPEED_TEST_TYPE_UPLINK = 0,

            /** downlink */
            ZEGO_NETWORK_SPEED_TEST_TYPE_DOWNLINK = 1

        };

        /**
         * Log config.
         *
         * Configure the log file save path and the maximum log file size.
         */
        struct ZegoLogConfig
        {
            /** Log file save path */
            std::string logPath;

            /** The maximum log file size (Bytes). The default maximum size is 5MB (5 * 1024 * 1024 Bytes) */
            unsigned long long logSize;

            ZegoLogConfig(){
                logSize = 5 * 1024 * 1024;
            }



        };

        /**
         * Custom video capture configuration.
         *
         * Custom video capture, that is, the developer is responsible for collecting video data and sending the collected video data to SDK for video data encoding and publishing to the ZEGO audio and video cloud.This feature is generally used by developers who use third-party beauty features or record game screen living.
         * When you need to use the custom video capture function, you need to set an instance of this class as a parameter to the [enableCustomVideoCapture] function.
         * Because when using custom video capture, SDK will no longer start the camera to capture video data. You need to collect video data from video sources by yourself.
         */
        struct ZegoCustomVideoCaptureConfig
        {
            /** Custom video capture video frame data type */
            ZegoVideoBufferType bufferType;

        };

        /**
         * Custom video render configuration.
         *
         * When you need to use the custom video render function, you need to set an instance of this class as a parameter to the [enableCustomVideoRender] function.
         */
        struct ZegoCustomVideoRenderConfig
        {
            /** Custom video capture video frame data type */
            ZegoVideoBufferType bufferType;

            /** Custom video rendering video frame data format。Useless when set bufferType as [EncodedData] */
            ZegoVideoFrameFormatSeries frameFormatSeries;

            /** Whether the engine also renders while customizing video rendering. The default value is [false]. Useless when set bufferType as [EncodedData] */
            bool enableEngineRender;

        };

        /**
         * Custom audio configuration.
         */
        struct ZegoCustomAudioConfig
        {
            /** Audio capture source type */
            ZegoAudioSourceType sourceType;

        };

        /**
         * Advanced engine configuration.
         */
        struct ZegoEngineConfig
        {
            /** Log configuration, if not set, use the default configuration. It must be set before calling [createEngine] to take effect. If it is set after [createEngine], it will take effect at the next [createEngine] after [destroyEngine]. */
            ZegoLogConfig* logConfig;

            /** Other special function switches, if not set, no special function will be used by default. Please contact ZEGO technical support before use. */
            std::unordered_map<std::string, std::string> advancedConfig;

            ZegoEngineConfig(){
                logConfig = nullptr;
            }

        };

        /**
         * Advanced room configuration.
         *
         * Configure maximum number of users in the room and authentication token, etc.
         */
        struct ZegoRoomConfig
        {
            /** The maximum number of users in the room, Passing 0 means unlimited, the default is unlimited. */
            unsigned int maxMemberCount;

            /** Whether to enable the user in and out of the room callback notification [onRoomUserUpdate], the default is off. If developers need to use ZEGO Room user notifications, make sure that each user who login sets this flag to true */
            bool isUserStatusNotify;

            /** The token issued by the developer's business server is used to ensure security. The generation rules are detailed in Room Login Authentication Description https://doc-en.zego.im/en/3881.html Default is empty string, that is, no authentication */
            std::string token;

            ZegoRoomConfig():maxMemberCount(0), isUserStatusNotify(false), token(""){
            }

        };

        /**
         * Video config.
         *
         * Configure parameters used for publishing stream, such as bitrate, frame rate, and resolution.
         * Developers should note that the width and height resolution of the mobile and desktop are opposite. For example, 360p, the resolution of the mobile is 360x640, and the desktop is 640x360.
         */
        struct ZegoVideoConfig
        {
            /** Capture resolution width, control the width of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective. For performance reasons, the SDK scales the video frame to the encoding resolution after capturing from camera and before rendering to the preview view. Therefore, the resolution of the preview image is the encoding resolution. If you need the resolution of the preview image to be this value, Please call [setCapturePipelineScaleMode] first to change the capture pipeline scale mode to [Post] */
            int captureWidth;

            /** Capture resolution height, control the height of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective. For performance reasons, the SDK scales the video frame to the encoding resolution after capturing from camera and before rendering to the preview view. Therefore, the resolution of the preview image is the encoding resolution. If you need the resolution of the preview image to be this value, Please call [setCapturePipelineScaleMode] first to change the capture pipeline scale mode to [Post] */
            int captureHeight;

            /** Encode resolution width, control the image width of the encoder when publishing stream. The settings before and after publishing stream can be effective */
            int encodeWidth;

            /** Encode resolution height, control the image height of the encoder when publishing stream. The settings before and after publishing stream can be effective */
            int encodeHeight;

            /** Frame rate, control the frame rate of the camera and the frame rate of the encoder. Only the camera is not started, the setting is effective */
            int fps;

            /** Bit rate in kbps. The settings before and after publishing stream can be effective */
            int bitrate;

            /** The codec id to be used, the default value is [default]. Settings only take effect before publishing stream */
            ZegoVideoCodecID codecID;

            ZegoVideoConfig(ZegoVideoConfigPreset preset = ZEGO_VIDEO_CONFIG_PRESET_360P){
            codecID = ZEGO_VIDEO_CODEC_ID_DEFAULT;
            switch (preset) {
            case ZEGO_VIDEO_CONFIG_PRESET_180P:
                captureWidth = 320;
                captureHeight = 180;
                encodeWidth = 320;
                encodeHeight = 180;
                bitrate = 300;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_270P:
                captureWidth = 480;
                captureHeight = 270;
                encodeWidth = 480;
                encodeHeight = 270;
                bitrate = 400;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_360P:
                captureWidth = 640;
                captureHeight = 360;
                encodeWidth = 640;
                encodeHeight = 360;
                bitrate = 600;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_540P:
                captureWidth = 960;
                captureHeight = 540;
                encodeWidth = 960;
                encodeHeight = 540;
                bitrate = 1200;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_720P:
                captureWidth = 1280;
                captureHeight = 720;
                encodeWidth = 1280;
                encodeHeight = 720;
                bitrate = 1500;
                fps = 15;
                break;
            case ZEGO_VIDEO_CONFIG_PRESET_1080P:
                captureWidth = 1920;
                captureHeight = 1080;
                encodeWidth = 1920;
                encodeHeight = 1080;
                bitrate = 3000;
                fps = 15;
                break;
            }
            }

        };

        /**
         * Externally encoded data traffic control information.
         */
        struct ZegoTrafficControlInfo
        {
            /** Video resolution width to be adjusted */
            int width;

            /** Video resolution height to be adjusted */
            int height;

            /** Video FPS to be adjusted */
            int fps;

            /** Video bitrate in kbps to be adjusted */
            int bitrate;

        };

        /**
         * SEI configuration
         *
         * Used to set the relevant configuration of the Supplemental Enhancement Information.
         */
        struct ZegoSEIConfig
        {
            /** SEI type */
            ZegoSEIType type;

        };

        /**
         * Voice changer parameter.
         *
         * Developer can use the built-in presets of the SDK to change the parameters of the voice changer.
         */
        struct ZegoVoiceChangerParam
        {
            /** Pitch parameter, value range [-8.0, 8.0], the larger the value, the sharper the sound, set it to 0.0 to turn off. Note that the voice changer effect is only valid for the captured sound. */
            float pitch;

            /**
             *
             * @deprecated This function is deprecated after 1.17.0. Please use the ZegoExpressEngine's [setVoiceChangerPreset] function instead
             */
            ZegoVoiceChangerParam(ZegoVoiceChangerPreset preset = ZEGO_VOICE_CHANGER_PRESET_NONE){
                switch(preset) {
                case ZEGO_VOICE_CHANGER_PRESET_MEN_TO_CHILD:
                    pitch = 8.0f;
                    break;
                case ZEGO_VOICE_CHANGER_PRESET_MEN_TO_WOMEN:
                    pitch = 4.0f;
                    break;
                case ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_CHILD:
                    pitch = 6.0f;
                    break;
                case ZEGO_VOICE_CHANGER_PRESET_WOMEN_TO_MEN:
                    pitch = -3.0f;
                    break;
                default:
                    pitch = 0.0f;
                    break;
                }
            }

        };

        /**
         * Audio reverberation parameters.
         *
         * Developers can use the SDK's built-in presets to change the parameters of the reverb.
         */
        struct ZegoReverbParam
        {
            /** Room size, in the range [0.0, 1.0], to control the size of the "room" in which the reverb is generated, the larger the room, the stronger the reverb. */
            float roomSize;

            /** Echo, in the range [0.0, 0.5], to control the trailing length of the reverb. */
            float reverberance;

            /** Reverb Damping, range [0.0, 2.0], controls the attenuation of the reverb, the higher the damping, the higher the attenuation. */
            float damping;

            /** Dry/wet ratio, the range is greater than or equal to 0.0, to control the ratio between reverberation, direct sound and early reflections; dry part is set to 1 by default; the smaller the dry/wet ratio, the larger the wet ratio, the stronger the reverberation effect. */
            float dryWetRatio;

            /**
             *
             * @deprecated This function is deprecated after 1.17.0. Please use the ZegoExpressEngine's [setReverbPreset] function instead
             */
            ZegoReverbParam(ZegoReverbPreset preset = ZEGO_REVERB_PRESET_NONE){
                switch(preset) {
                case ZEGO_REVERB_PRESET_SOFT_ROOM:
                    roomSize = 0.6f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 2.5f;
                    break;
                case ZEGO_REVERB_PRESET_LARGE_ROOM:
                    roomSize = 0.65f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 0.94f;
                    break;
                case ZEGO_REVERB_PRESET_CONCER_HALL:
                    roomSize = 0.8f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 1.1f;
                    break;
                case ZEGO_REVERB_PRESET_VALLEY:
                    roomSize = 0.85f;
                    reverberance = 0.03f;
                    damping = 0.25f;
                    dryWetRatio = 0.92f;
                    break;
                default:
                    roomSize = 0.0f;
                    reverberance = 0.0f;
                    damping = 0.0f;
                    dryWetRatio = 0.0f;
                    break;
                }
            }

        };

        /**
         * Audio reverberation advanced parameters.
         *
         * Developers can use the SDK's built-in presets to change the parameters of the reverb.
         */
        struct ZegoReverbAdvancedParam
        {
            /** Room size(%), in the range [0.0, 1.0], to control the size of the "room" in which the reverb is generated, the larger the room, the stronger the reverb. */
            float roomSize;

            /** Echo(%), in the range [0.0, 100.0], to control the trailing length of the reverb. */
            float reverberance;

            /** Reverb Damping(%), range [0.0, 100.0], controls the attenuation of the reverb, the higher the damping, the higher the attenuation. */
            float damping;

            /** only wet */
            bool wetOnly;

            /** wet gain(dB), range [-20.0, 10.0] */
            float wetGain;

            /** dry gain(dB), range [-20.0, 10.0] */
            float dryGain;

            /** Tone Low. 100% by default */
            float toneLow;

            /** Tone High. 100% by default */
            float toneHigh;

            /** PreDelay(ms), range [0.0, 200.0] */
            float preDelay;

            /** Stereo Width(%). 0% by default */
            float stereoWidth;

            ZegoReverbAdvancedParam() : roomSize(.0f), reverberance(.0f), damping(.0f), wetOnly(false), wetGain(.0f), dryGain(.0f), toneLow(100.0f), toneHigh(100.0f), preDelay(.0f), stereoWidth(.0f){
            }

        };

        /**
         * Audio reverberation echo parameters.
         */
        struct ZegoReverbEchoParam
        {
            /** Gain of input audio signal, in the range [0.0, 1.0] */
            float inGain;

            /** Gain of output audio signal, in the range [0.0, 1.0] */
            float outGain;

            /** Number of echos, in the range [0, 7] */
            int numDelays;

            /** Respective delay of echo signal, in milliseconds, in the range [0, 5000] ms */
            int delay[7];

            /** Respective decay coefficient of echo signal, in the range [0.0, 1.0] */
            float decay[7];

        };

        /**
         * User object.
         *
         * Configure user ID and username to identify users in the room.
         * Note that the userID must be unique under the same appID, otherwise mutual kicks out will occur.
         * It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
         */
        struct ZegoUser
        {
            /** User ID, a string with a maximum length of 64 bytes or less. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
            std::string userID;

            /** User Name, a string with a maximum length of 256 bytes or less */
            std::string userName;

            ZegoUser(){
            }

            ZegoUser(std::string userID, std::string userName):userID(userID),userName(userName){
            }

        };

        /**
         * Stream object.
         *
         * Identify an stream object
         */
        struct ZegoStream
        {
            /** User object instance */
            ZegoUser user;

            /** Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
            std::string streamID;

            /** Stream extra info */
            std::string extraInfo;

        };

        /**
         * Room extra information.
         */
        struct ZegoRoomExtraInfo
        {
            /** The key of the room extra information. */
            std::string key;

            /** The value of the room extra information. */
            std::string value;

            /** The user who update the room extra information. */
            ZegoUser updateUser;

            /** Update time of the room extra information, UNIX timestamp, in milliseconds. */
            unsigned long long updateTime;

        };

        /**
         * View related coordinates.
         */
        struct ZegoRect
        {
            /** The horizontal offset from the top-left corner */
            int x;

            /** The vertical offset from the top-left corner */
            int y;

            /** The width of the rectangle */
            int width;

            /** The height of the rectangle */
            int height;

            ZegoRect() : x(0), y(0), width(0), height(0){
            }

            ZegoRect(int x, int y, int w, int h) : x(x), y(y), width(w), height(h){
            }

        };

        /**
         * View object.
         *
         * Configure view object, view Mode, background color
         */
        struct ZegoCanvas
        {
            /** View object */
            void * view;

            /** View mode, default is ZegoViewModeAspectFit */
            ZegoViewMode viewMode;

            /** Background color, the format is 0xRRGGBB, default is black, which is 0x000000 */
            int backgroundColor;

            ZegoCanvas(void *view=nullptr, ZegoViewMode viewMode=ZEGO_VIEW_MODE_ASPECT_FIT, int backgroundColor=0x000000):view(view),viewMode(viewMode),backgroundColor(backgroundColor){
            }

        };

        /**
         * Published stream quality information.
         *
         * Audio and video parameters and network quality, etc.
         */
        struct ZegoPublishStreamQuality
        {
            /** Video capture frame rate. The unit of frame rate is f/s */
            double videoCaptureFPS;

            /** Video encoding frame rate. The unit of frame rate is f/s */
            double videoEncodeFPS;

            /** Video transmission frame rate. The unit of frame rate is f/s */
            double videoSendFPS;

            /** Video bit rate in kbps */
            double videoKBPS;

            /** Audio capture frame rate. The unit of frame rate is f/s */
            double audioCaptureFPS;

            /** Audio transmission frame rate. The unit of frame rate is f/s */
            double audioSendFPS;

            /** Audio bit rate in kbps */
            double audioKBPS;

            /** Local to server delay, in milliseconds */
            int rtt;

            /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
            double packetLostRate;

            /** Published stream quality level */
            ZegoStreamQualityLevel level;

            /** Whether to enable hardware encoding */
            bool isHardwareEncode;

            /** Video codec ID */
            ZegoVideoCodecID videoCodecID;

            /** Total number of bytes sent, including audio, video, SEI */
            double totalSendBytes;

            /** Number of audio bytes sent */
            double audioSendBytes;

            /** Number of video bytes sent */
            double videoSendBytes;

        };

        /**
         * CDN config object.
         *
         * Includes CDN URL and authentication parameter string
         */
        struct ZegoCDNConfig
        {
            /** CDN URL */
            std::string url;

            /** Auth param of URL */
            std::string authParam;

        };

        /**
         * Relay to CDN info.
         *
         * Including the URL of the relaying CDN, relaying state, etc.
         */
        struct ZegoStreamRelayCDNInfo
        {
            /** URL of publishing stream to CDN */
            std::string url;

            /** State of relaying to CDN */
            ZegoStreamRelayCDNState state;

            /** Reason for relay state changed */
            ZegoStreamRelayCDNUpdateReason updateReason;

            /** The timestamp when the state changed, UNIX timestamp, in milliseconds. */
            unsigned long long stateTime;

        };

        /**
         * Advanced player configuration.
         *
         * Configure playing stream CDN configuration, video layer
         */
        struct ZegoPlayerConfig
        {
            /** Stream resource mode */
            ZegoStreamResourceMode resourceMode;

            /** The CDN configuration for playing stream. If set, the stream is play according to the URL instead of the streamID. After that, the streamID is only used as the ID of SDK internal callback. */
            ZegoCDNConfig * cdnConfig;

            /** @deprecated This property has been deprecated since version 1.19.0, please use the [setPlayStreamVideoLayer] function instead. */
            ZegoPlayerVideoLayer videoLayer;

            ZegoPlayerConfig(): resourceMode(ZEGO_STREAM_RESOURCE_MODE_DEFAULT), cdnConfig(nullptr), videoLayer((ZegoPlayerVideoLayer)99){
            }

        };

        /**
         * Played stream quality information.
         *
         * Audio and video parameters and network quality, etc.
         */
        struct ZegoPlayStreamQuality
        {
            /** Video receiving frame rate. The unit of frame rate is f/s */
            double videoRecvFPS;

            /** Video dejitter frame rate. The unit of frame rate is f/s */
            double videoDejitterFPS;

            /** Video decoding frame rate. The unit of frame rate is f/s */
            double videoDecodeFPS;

            /** Video rendering frame rate. The unit of frame rate is f/s */
            double videoRenderFPS;

            /** Video bit rate in kbps */
            double videoKBPS;

            /** Video break rate, the unit is (number of breaks / every 10 seconds) */
            double videoBreakRate;

            /** Audio receiving frame rate. The unit of frame rate is f/s */
            double audioRecvFPS;

            /** Audio dejitter frame rate. The unit of frame rate is f/s */
            double audioDejitterFPS;

            /** Audio decoding frame rate. The unit of frame rate is f/s */
            double audioDecodeFPS;

            /** Audio rendering frame rate. The unit of frame rate is f/s */
            double audioRenderFPS;

            /** Audio bit rate in kbps */
            double audioKBPS;

            /** Audio break rate, the unit is (number of breaks / every 10 seconds) */
            double audioBreakRate;

            /** Server to local delay, in milliseconds */
            int rtt;

            /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
            double packetLostRate;

            /** Delay from peer to peer, in milliseconds */
            int peerToPeerDelay;

            /** Packet loss rate from peer to peer, in percentage, 0.0 ~ 1.0 */
            double peerToPeerPacketLostRate;

            /** Published stream quality level */
            ZegoStreamQualityLevel level;

            /** Delay after the data is received by the local end, in milliseconds */
            int delay;

            /** The difference between the video timestamp and the audio timestamp, used to reflect the synchronization of audio and video, in milliseconds. This value is less than 0 means the number of milliseconds that the video leads the audio, greater than 0 means the number of milliseconds that the video lags the audio, and 0 means no difference. When the absolute value is less than 200, it can basically be regarded as synchronized audio and video, when the absolute value is greater than 200 for 10 consecutive seconds, it can be regarded as abnormal */
            int avTimestampDiff;

            /** Whether to enable hardware decoding */
            bool isHardwareDecode;

            /** Video codec ID */
            ZegoVideoCodecID videoCodecID;

            /** Total number of bytes received, including audio, video, SEI */
            double totalRecvBytes;

            /** Number of audio bytes received */
            double audioRecvBytes;

            /** Number of video bytes received */
            double videoRecvBytes;

        };

        /**
         * Device Info.
         *
         * Including device ID and name
         */
        struct ZegoDeviceInfo
        {
            /** Device ID */
            std::string deviceID;

            /** Device name */
            std::string deviceName;

        };

        /**
         * System performance monitoring status
         */
        struct ZegoPerformanceStatus
        {
            /** Current CPU usage of the app, value range [0, 1] */
            double cpuUsageApp;

            /** Current CPU usage of the system, value range [0, 1] */
            double cpuUsageSystem;

            /** Current memory usage of the app, value range [0, 1] */
            double memoryUsageApp;

            /** Current memory usage of the system, value range [0, 1] */
            double memoryUsageSystem;

            /** Current memory used of the app, in MB */
            double memoryUsedApp;

        };

        /**
         * Mix stream audio configuration.
         *
         * Configure video frame rate, bitrate, and resolution for mixer task
         */
        struct ZegoMixerAudioConfig
        {
            /** Audio bitrate in kbps, default is 48 kbps, cannot be modified after starting a mixer task */
            int bitrate;

            /** Audio channel, default is Mono */
            ZegoAudioChannel channel;

            /** codec ID, default is ZegoAudioCodecIDDefault */
            ZegoAudioCodecID codecID;

            ZegoMixerAudioConfig():bitrate(48), channel(ZEGO_AUDIO_CHANNEL_MONO), codecID(ZEGO_AUDIO_CODEC_ID_DEFAULT){
            }

            ZegoMixerAudioConfig(int bitrate, ZegoAudioChannel channel, ZegoAudioCodecID codecID): bitrate(bitrate), channel(channel), codecID(codecID){
            }

        };

        /**
         * Mix stream video config object.
         *
         * Configure video frame rate, bitrate, and resolution for mixer task
         */
        struct ZegoMixerVideoConfig
        {
            /** Video resolution width */
            int width;

            /** Video resolution height */
            int height;

            /** Video FPS, cannot be modified after starting a mixer task */
            int fps;

            /** Video bitrate in kbps */
            int bitrate;

            ZegoMixerVideoConfig(): width(640), height(360), fps(15), bitrate(600){
            }

            ZegoMixerVideoConfig(int width, int height, int fps, int bitrate): width(width), height(height), fps(fps), bitrate(bitrate){
            }

        };

        /**
         * Mixer input.
         *
         * Configure the mix stream input stream ID, type, and the layout
         */
        struct ZegoMixerInput
        {
            /** Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
            std::string streamID;

            /** Mix stream content type */
            ZegoMixerInputContentType contentType;

            /** Stream layout. When the mixed stream is an audio stream (that is, the ContentType parameter is set to the audio mixed stream type), the layout field is not processed inside the SDK, and there is no need to pay attention to this parameter. */
            ZegoRect layout;

            /** If enable soundLevel in mix stream task, an unique soundLevelID is need for every stream */
            unsigned int soundLevelID;

            ZegoMixerInput() : contentType(ZEGO_MIXER_INPUT_CONTENT_TYPE_VIDEO), soundLevelID(0){
            }

            ZegoMixerInput(std::string streamID, ZegoMixerInputContentType contentType, ZegoRect layout, unsigned int soundLevelID): streamID(streamID), contentType(contentType), layout(layout), soundLevelID(soundLevelID){
            }

        };

        /**
         * Mixer output object.
         *
         * Configure mix stream output target URL or stream ID
         */
        struct ZegoMixerOutput
        {
            /** Mix stream output target, URL or stream ID, if set to be URL format, only RTMP URL surpported, for example rtmp://xxxxxxxx */
            std::string target;

            ZegoMixerOutput(){
            }

            ZegoMixerOutput(std::string target) :target(target){
            }

        };

        /**
         * Watermark object.
         *
         * Configure a watermark image URL and the layout of the watermark in the screen
         */
        struct ZegoWatermark
        {
            /** Watermark image URL, only png or jpg format surpport. */
            std::string imageURL;

            /** Watermark image layout */
            ZegoRect layout;

            ZegoWatermark(){
            }

            ZegoWatermark(std::string imageURL, ZegoRect layout) :imageURL(imageURL), layout(layout){
            }

        };

        /**
         * Mix stream task object.
         *
         * This class is the configuration class of the mixing stream task. When a mixing stream task is requested to the ZEGO audio and video cloud, the configuration of the mixing task is required.
         * This class describes the detailed configuration information of this mixed task.
         */
        struct ZegoMixerTask
        {
            /** The task ID of the task */
            std::string taskID;

            /** The audio config of the task */
            ZegoMixerAudioConfig audioConfig;

            /** The audio config of the task */
            ZegoMixerVideoConfig videoConfig;

            /** The input list of the task */
            std::vector<ZegoMixerInput> inputList;

            /** The output list of the task */
            std::vector<ZegoMixerOutput> outputList;

            /** The watermark of the task */
            ZegoWatermark* watermark;

            /** The background image URL of the task */
            std::string backgroundImageURL;

            /** Enable or disable sound level callback for the task. If enabled, then the remote player can get the soundLevel of every stream in the inputlist by [onMixerSoundLevelUpdate] callback. */
            bool enableSoundLevel;

            ZegoMixerTask(std::string taskID=""): taskID(taskID), watermark(nullptr){
            }

        };

        /**
         * Broadcast message info.
         *
         * The received object of the room broadcast message, including the message content, message ID, sender, sending time
         */
        struct ZegoBroadcastMessageInfo
        {
            /** message content */
            std::string message;

            /** message id */
            unsigned long long messageID;

            /** Message send time, UNIX timestamp, in milliseconds. */
            unsigned long long sendTime;

            /** Message sender */
            ZegoUser fromUser;

        };

        /**
         * Barrage message info.
         *
         * The received object of the room barrage message, including the message content, message ID, sender, sending time
         */
        struct ZegoBarrageMessageInfo
        {
            /** message content */
            std::string message;

            /** message id */
            std::string messageID;

            /** Message send time, UNIX timestamp, in milliseconds. */
            unsigned long long sendTime;

            /** Message sender */
            ZegoUser fromUser;

        };

        /**
         * Object for video frame fieldeter.
         *
         * Including video frame format, width and height, etc.
         */
        struct ZegoVideoFrameParam
        {
            /** Video frame format */
            ZegoVideoFrameFormat format;

            /** Number of bytes per line (for example: RGBA only needs to consider strides [0], I420 needs to consider strides [0,1,2]) */
            int strides[4];

            /** Video frame width */
            int width;

            /** Video frame height */
            int height;

            /** Video frame rotation */
            int rotation;

        };

        /**
         * Object for video encoded frame fieldeter.
         *
         * Including video encoded frame format, width and height, etc.
         */
        struct ZegoVideoEncodedFrameParam
        {
            /** Video encoded frame format */
            ZegoVideoEncodedFrameFormat format;

            /** Whether it is a keyframe */
            bool isKeyFrame;

            /** Video frame rotation */
            int rotation;

            /** Video frame width */
            int width;

            /** Video frame height */
            int height;

            /** SEI data */
            const unsigned char* SEIData;

            /** Length of the SEI data */
            unsigned int SEIDataLength;

        };

        /**
         * Parameter object for audio frame.
         *
         * Including the sampling rate and channel of the audio frame
         */
        struct ZegoAudioFrameParam
        {
            /** Sampling Rate */
            ZegoAudioSampleRate sampleRate;

            /** Audio channel, default is Mono */
            ZegoAudioChannel channel;

        };

        /**
         * Audio configuration.
         *
         * Configure audio bitrate, audio channel, audio encoding for publishing stream
         */
        struct ZegoAudioConfig
        {
            /** Audio bitrate in kbps, default is 48 kbps. The settings before and after publishing stream can be effective */
            int bitrate;

            /** Audio channel, default is Mono. The setting only take effect before publishing stream */
            ZegoAudioChannel channel;

            /** codec ID, default is ZegoAudioCodecIDDefault. The setting only take effect before publishing stream */
            ZegoAudioCodecID codecID;

            ZegoAudioConfig(ZegoAudioConfigPreset preset = ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY){
                codecID = ZEGO_AUDIO_CODEC_ID_DEFAULT;
                switch (preset) {
                case ZEGO_AUDIO_CONFIG_PRESET_BASIC_QUALITY:
                    bitrate = 16;
                    channel = ZEGO_AUDIO_CHANNEL_MONO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY:
                    bitrate = 48;
                    channel = ZEGO_AUDIO_CHANNEL_MONO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_STANDARD_QUALITY_STEREO:
                    bitrate = 56;
                    channel = ZEGO_AUDIO_CHANNEL_STEREO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY:
                    bitrate = 128;
                    channel = ZEGO_AUDIO_CHANNEL_MONO;
                    break;
                case ZEGO_AUDIO_CONFIG_PRESET_HIGH_QUALITY_STEREO:
                    bitrate = 192;
                    channel = ZEGO_AUDIO_CHANNEL_STEREO;
                    break;
                }
            }

        };

        /**
         * audio mixing data.
         */
        struct ZegoAudioMixingData
        {
            /** Audio PCM data that needs to be mixed into the stream */
            unsigned char* audioData;

            /** the length of the audio PCM data that needs to be mixed into the stream. If this is no enough data left to mix as audioDataLength, then you can set audioDataLength = 0. */
            unsigned int audioDataLength;

            /** Audio data attributes, including sample rate and number of channels. Currently supports 16k 32k 44.1k 48k sampling rate, mono or stereo channel, 16-bit deep PCM data. Developers need to explicitly specify audio data attributes, otherwise mixing will not take effect. */
            ZegoAudioFrameParam param;

            /** SEI data, used to transfer custom data. When audioData is null, SEIData will not be sent */
            unsigned char* SEIData;

            /** SEI data length */
            unsigned int SEIDataLength;

        };

        /**
         * Customize the audio processing configuration object.
         *
         * Including custom audio acquisition type, sampling rate, channel number, sampling number and other parameters
         */
        struct ZegoCustomAudioProcessConfig
        {
            /** Sampling rate, the sampling rate of the input data expected by the audio pre-processing module in App. If 0, the default is the SDK internal sampling rate. */
            ZegoAudioSampleRate sampleRate;

            /** Number of sound channels, the expected number of sound channels for input data of the audio pre-processing module in App. If 0, the default is the number of internal channels in the SDK */
            ZegoAudioChannel channel;

            /** The number of samples required to encode a frame; When encode = false, if samples = 0, the SDK will use the internal sample number, and the SDK will pass the audio data to the external pre-processing module. If the samples! = 0 (the effective value of samples is between [160, 2048]), and the SDK will send audio data to the external preprocessing module that sets the length of sample number. Encode = true, the number of samples for a frame of AAC encoding can be set as (480/512/1024/1960/2048) */
            int samples;

        };

        /**
         * Record config.
         */
        struct ZegoDataRecordConfig
        {
            /** The path to save the recording file, absolute path, need to include the file name, the file name need to specify the suffix, currently supports .mp4/.flv/.aac format files, if multiple recording for the same path, will overwrite the file with the same name. The maximum length should be less than 1024 bytes. */
            std::string filePath;

            /** Type of recording media */
            ZegoDataRecordType recordType;

        };

        /**
         * File recording progress.
         */
        struct ZegoDataRecordProgress
        {
            /** Current recording duration in milliseconds */
            unsigned long long duration;

            /** Current recording file size in byte */
            unsigned long long currentFileSize;

        };

        /**
         * Network speed test config
         */
        struct ZegoNetworkSpeedTestConfig
        {
            /** Test uplink or not */
            bool testUplink;

            /** The unit is kbps. Recommended to use the bitrate in ZegoVideoConfig when call startPublishingStream to determine whether the network uplink environment is suitable. */
            int expectedUplinkBitrate;

            /** Test downlink or not */
            bool testDownlink;

            /** The unit is kbps. Recommended to use the bitrate in ZegoVideoConfig when call startPublishingStream to determine whether the network downlink environment is suitable. */
            int expectedDownlinkBitrate;

        };

        /**
         * test connectivity result
         */
        struct ZegoTestNetworkConnectivityResult
        {
            /** connect cost */
            unsigned int connectCost;

        };

        /**
         * network speed test quality
         */
        struct ZegoNetworkSpeedTestQuality
        {
            /** Time to connect to the server, in milliseconds. During the speed test, if the network connection is disconnected, it will automatically initiate a reconnection, and this variable will be updated accordingly. */
            unsigned int connectCost;

            /** rtt, in milliseconds */
            unsigned int rtt;

            /** packet lost rate. in percentage, 0.0 ~ 1.0 */
            double packetLostRate;

        };

        /**
         * AudioEffectPlayer play configuration.
         */
        struct ZegoAudioEffectPlayConfig
        {
            /** The number of play counts. When set to 0, it will play in an infinite loop until the user invoke [stop]. The default is 1, which means it will play only once. */
            unsigned int playCount;

            /** Whether to mix audio effects into the publishing stream, the default is false. */
            bool isPublishOut;

        };

        /**
         * Callback for asynchronous destruction completion.
         *
         * In general, developers do not need to listen to this callback.
         */
        using ZegoDestroyCompletionCallback = std::function<void ()>;


        /**
         * Callback for setting room extra information.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoRoomSetRoomExtraInfoCallback = std::function<void (int errorCode)>;


        /**
         * Callback for setting stream extra information.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoPublisherSetStreamExtraInfoCallback = std::function<void (int errorCode)>;


        /**
         * Callback for add/remove CDN URL.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoPublisherUpdateCdnUrlCallback = std::function<void (int errorCode)>;


        /**
         * Results of take publish stream snapshot.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         * @param image Snapshot image (Windows: HBITMAP; macOS/iOS: CGImageRef; Linux: QImage; Android: Bitmap)
         */
        using ZegoPublisherTakeSnapshotCallback = std::function<void (int errorCode, void *image)>;


        /**
         * Results of take play stream snapshot.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         * @param image Snapshot image (Windows: HBITMAP; macOS/iOS: CGImageRef; Linux: QImage; Android: Bitmap)
         */
        using ZegoPlayerTakeSnapshotCallback = std::function<void (int errorCode, void *image)>;


        /**
         * Results of starting a mixer task.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         * @param extendedData Extended Information
         */
        using ZegoMixerStartCallback = std::function<void (int errorCode, std::string extendedData)>;


        /**
         * Results of stoping a mixer task.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoMixerStopCallback = std::function<void (int errorCode)>;


        /**
         * Callback for sending broadcast messages.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         * @param messageID ID of this message
         */
        using ZegoIMSendBroadcastMessageCallback = std::function<void (int errorCode, unsigned long long messageID)>;


        /**
         * Callback for sending barrage message.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         * @param messageID ID of this message
         */
        using ZegoIMSendBarrageMessageCallback = std::function<void (int errorCode, std::string messageID)>;


        /**
         * Callback for sending custom command.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoIMSendCustomCommandCallback = std::function<void (int errorCode)>;


        /**
         * Callback for test network connectivity.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         * @param result Network connectivity test results
         */
        using ZegoTestNetworkConnectivityCallback = std::function<void (int errorCode, ZegoTestNetworkConnectivityResult result)>;


        /**
         * Callback for media player loads resources.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoMediaPlayerLoadResourceCallback = std::function<void (int errorCode)>;


        /**
         * Callback for media player seek to playback progress.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoMediaPlayerSeekToCallback = std::function<void (int errorCode)>;


        /**
         * Callback for audio effect player loads resources.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoAudioEffectPlayerLoadResourceCallback = std::function<void (int errorCode)>;


        /**
         * Callback for audio effect player seek to playback progress.
         *
         * @param errorCode Error code, please refer to the error codes document https://doc-en.zego.im/en/5548.html for details.
         */
        using ZegoAudioEffectPlayerSeekToCallback = std::function<void (int errorCode)>;



        using ZegoAudioSpectrum = std::vector<float>;
        using ZegoView = void*;

    }
}

#endif /* __ZEGOEXPRESSDEFINES_H__ */
