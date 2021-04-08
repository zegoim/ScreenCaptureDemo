using System;
using System.Runtime.InteropServices;

namespace ZegoScreenCapture_.net_
{
    /** Platform language. */
    public enum zego_platform_language : int
    {
        /** C language. */
        zego_platform_language_c = 0,

        /** Objective-C language. */
        zego_platform_language_oc = 1,

        /** Java language. */
        zego_platform_language_java = 2,

        /** Cpp language. */
        zego_platform_language_cpp = 3,

        /** Dart language. */
        zego_platform_language_dart = 4,

        /** JS language. */
        zego_platform_language_js = 5,

        /** CS language. */
        zego_platform_language_cs = 6

    };

    /** Application scenario. */
    public enum zego_scenario : int
    {
        /** General scenario */
        zego_scenario_general = 0,

        /** Communication scenario */
        zego_scenario_communication = 1,

        /** Live scenario */
        zego_scenario_live = 2

    };

    /** engine state. */
    public enum zego_engine_state : int
    {
        /** The engine has started */
        zego_engine_state_start = 0,

        /** The engine has stoped */
        zego_engine_state_stop = 1

    };

    /** Video frame format. */
    public enum zego_video_frame_format : int
    {
        /** Unknown format, will take platform default */
        zego_video_frame_format_unknown = 0,

        /** I420 (YUV420Planar) format */
        zego_video_frame_format_i420 = 1,

        /** NV12 (YUV420SemiPlanar) format */
        zego_video_frame_format_nv12 = 2,

        /** NV21 (YUV420SemiPlanar) format */
        zego_video_frame_format_nv21 = 3,

        /** BGRA32 format */
        zego_video_frame_format_bgra32 = 4,

        /** RGBA32 format */
        zego_video_frame_format_rgba32 = 5,

        /** ARGB32 format */
        zego_video_frame_format_argb32 = 6,

        /** ABGR32 format */
        zego_video_frame_format_abgr32 = 7,

        /** I422 (YUV422Planar) format */
        zego_video_frame_format_i422 = 8

    };

    /** Publish channel. */
    public enum zego_publish_channel : int
    {
        /** Main publish channel */
        zego_publish_channel_main = 0,

        /** Auxiliary publish channel */
        zego_publish_channel_aux = 1

    };

    /** Room state. */
    public enum zego_room_state : int
    {
        /** Unconnected state, enter this state before logging in and after exiting the room. If there is a steady state abnormality in the process of logging in to the room, such as AppID and AppSign are incorrect, or if the same user name is logged in elsewhere and the local end is KickOut, it will enter this state. */
        zego_room_state_disconnected = 0,

        /** The state that the connection is being requested. It will enter this state after successful execution login room function. The display of the UI is usually performed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting connection status. */
        zego_room_state_connecting = 1,

        /** The status that is successfully connected. Entering this status indicates that the login to the room has been successful. The user can receive the callback notification of the user and the stream information in the room. */
        zego_room_state_connected = 2

    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_user
    {
        /** User ID, a string with a maximum length of 64 bytes or less. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'. */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string user_id;

        /** User Name, a string with a maximum length of 256 bytes or less */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string user_name;

    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_room_config
    {
        /** The maximum number of users in the room, Passing 0 means unlimited, the default is unlimited. */
        public uint max_member_count;

        /** Whether to enable the user in and out of the room callback notification [onRoomUserUpdate], the default is off. If developers need to use ZEGO Room user notifications, make sure that each user who login sets this flag to true */
        public bool is_user_status_notify;

        /** The token issued by the developer's business server is used to ensure security. The generation rules are detailed in Room Login Authentication Description https://doc-en.zego.im/en/3881.html Default is empty string, that is, no authentication */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 512)]
        public string token;

    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_log_config
    {
        /** Log file save path */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 512)]
        public string log_path;

        /** The maximum log file size (Bytes). The default maximum size is 5MB (5 * 1024 * 1024 Bytes) */
        public UInt64 log_size;
    };


    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_engine_config
    {
        /** Log configuration, if not set, use the default configuration. It must be set before calling [createEngine] to take effect. If it is set after [createEngine], it will take effect at the next [createEngine] after [destroyEngine]. */
        public IntPtr log_config;

        /** Other special function switches, if not set, no special function will be used by default. Please contact ZEGO technical support before use. */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 512)]
        public string advanced_config;
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_video_frame_param
    {
        /** Video frame format */
        public zego_video_frame_format format;

        /** Number of bytes per line (for example: RGBA only needs to consider strides [0], I420 needs to consider strides [0,1,2]) */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int[] strides;

        /** Video frame width */
        public int width;

        /** Video frame height */
        public int height;

        /** Video frame rotation */
        public int rotation;

    };

    /** Publish stream status. */
    public enum zego_publisher_state : int
    {
        /** The state is not published, and it is in this state before publishing the stream. If a steady-state exception occurs in the publish process, such as AppID and AppSign are incorrect, or if other users are already publishing the stream, there will be a failure and enter this state. */
        zego_publisher_state_no_publish = 0,

        /** The state that it is requesting to publish the stream after the [startPublishingStream] function is successfully called. The UI is usually displayed through this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state. */
        zego_publisher_state_publish_requesting = 1,

        /** The state that the stream is being published, entering the state indicates that the stream has been successfully published, and the user can communicate normally. */
        zego_publisher_state_publishing = 2

    };

    /** Stream quality level. */
    public enum zego_stream_quality_level : int
    {
        /** Excellent */
        zego_stream_quality_level_excellent = 0,

        /** Good */
        zego_stream_quality_level_good = 1,

        /** Normal */
        zego_stream_quality_level_medium = 2,

        /** Bad */
        zego_stream_quality_level_bad = 3,

        /** Failed */
        zego_stream_quality_level_die = 4

    };

    /** Video codec ID. */
    public enum zego_video_codec_id:int
    {
        /** Default (H.264) */
        zego_video_codec_id_default = 0,

        /** Scalable Video Coding (H.264 SVC) */
        zego_video_codec_id_svc = 1,

        /** VP8 */
        zego_video_codec_id_vp8 = 2,

        /** H.265 */
        zego_video_codec_id_h265 = 3

    };

    /**
    * Published stream quality information.
    *
    * Audio and video parameters and network quality, etc.
    */
    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_publish_stream_quality
    {
        /** Video capture frame rate. The unit of frame rate is f/s */
        public double video_capture_fps;

        /** Video encoding frame rate. The unit of frame rate is f/s */
        public double video_encode_fps;

        /** Video transmission frame rate. The unit of frame rate is f/s */
        public double video_send_fps;

        /** Video bit rate in kbps */
        public double video_kbps;

        /** Audio capture frame rate. The unit of frame rate is f/s */
        public double audio_capture_fps;

        /** Audio transmission frame rate. The unit of frame rate is f/s */
        public double audio_send_fps;

        /** Audio bit rate in kbps */
        public double audio_kbps;

        /** Local to server delay, in milliseconds */
        public int rtt;

        /** Packet loss rate, in percentage, 0.0 ~ 1.0 */
        public double packet_lost_rate;

        /** Published stream quality level */
        public zego_stream_quality_level level;

        /** Whether to enable hardware encoding */
        public bool is_hardware_encode;

        /** Video codec ID */
        public zego_video_codec_id video_codec_id;

        /** Total number of bytes sent, including audio, video, SEI */
        public double total_send_bytes;

        /** Number of audio bytes sent */
        public double audio_send_bytes;

        /** Number of video bytes sent */
        public double video_send_bytes;

    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_video_config
    {
        /** Capture resolution width, control the width of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective. For performance reasons, the SDK scales the video frame to the encoding resolution after capturing from camera and before rendering to the preview view. Therefore, the resolution of the preview image is the encoding resolution. If you need the resolution of the preview image to be this value, Please call [setCapturePipelineScaleMode] first to change the capture pipeline scale mode to [Post] */
        public int capture_width;

        /** Capture resolution height, control the height of camera image acquisition. Only the camera is not started and the custom video capture is not used, the setting is effective. For performance reasons, the SDK scales the video frame to the encoding resolution after capturing from camera and before rendering to the preview view. Therefore, the resolution of the preview image is the encoding resolution. If you need the resolution of the preview image to be this value, Please call [setCapturePipelineScaleMode] first to change the capture pipeline scale mode to [Post] */
        public int capture_height;

        /** Encode resolution width, control the image width of the encoder when publishing stream. The settings before and after publishing stream can be effective */
        public int encode_width;

        /** Encode resolution height, control the image height of the encoder when publishing stream. The settings before and after publishing stream can be effective */
        public int encode_height;

        /** Frame rate, control the frame rate of the camera and the frame rate of the encoder. Only the camera is not started, the setting is effective */
        public int fps;

        /** Bit rate in kbps. The settings before and after publishing stream can be effective */
        public int bitrate;

        /** The codec id to be used, the default value is [default]. Settings only take effect before publishing stream */
        public zego_video_codec_id codec_id;
    };

    public enum zego_video_buffer_type:int
    {
        /** Raw data type video frame */
        zego_video_buffer_type_unknown = 0,

        /** Raw data type video frame */
        zego_video_buffer_type_raw_data = 1,

        /** Encoded data type video frame */
        zego_video_buffer_type_encoded_data = 2,

        /** Texture 2D type video frame */
        zego_video_buffer_type_gl_texture_2d = 3,

        /** CVPixelBuffer type video frame */
        zego_video_buffer_type_cv_pixel_buffer = 4,

        /** Surface Texture type video frame */
        zego_video_buffer_type_surface_texture = 5,

        /** GL_TEXTURE_EXTERNAL_OES type video frame */
        zego_video_buffer_type_gl_texture_external_oes = 6

    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct zego_custom_video_capture_config
    {
        /** Custom video capture video frame data type */
        public zego_video_buffer_type buffer_type;
    };
}
