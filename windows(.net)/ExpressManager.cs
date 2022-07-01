using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ZegoScreenCapture_.net_
{
    class ExpressManager
    {
        // 注册各回调类型
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_on_engine_state_update(zego_engine_state state, IntPtr user_context);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_on_engine_uninit(zego_engine_state state, IntPtr user_context);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_on_room_state_update(string room_id, zego_room_state state, int error_code, string extended_data, IntPtr user_context);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_on_publisher_state_update(string stream_id, zego_publisher_state state, int error_code, string extend_data, IntPtr user_context);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_on_publisher_quality_update(string stream_id, zego_publish_stream_quality quality, IntPtr user_context);

        // 引入DLL中的func
        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_express_set_platform_language(zego_platform_language platform_language);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_express_set_engine_config(zego_engine_config config);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_express_set_log_config(zego_log_config config);

        //[DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern int zego_express_engine_init(uint app_id, string app_sign, bool is_test_env, zego_scenario scenario);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_engine_init_with_profile(zego_engine_profile profile);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_express_engine_uninit_async();

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_register_engine_state_update_callback(zego_on_engine_state_update fn, IntPtr data);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_register_engine_uninit_callback(zego_on_engine_uninit fn, IntPtr data);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_login_room(string room_id, zego_user user, IntPtr config);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_logout_room(string room_id);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_start_publishing_stream(string stream_id, zego_publish_channel channel);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_stop_publishing_stream(zego_publish_channel channel);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_set_video_config(zego_video_config config, zego_publish_channel channel);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern zego_video_config zego_express_get_video_config(zego_publish_channel channel);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_enable_custom_video_capture(bool enable, ref zego_custom_video_capture_config config, zego_publish_channel channel);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_express_send_custom_video_capture_raw_data(IntPtr data, uint data_length, zego_video_frame_param param, UInt64 reference_time_millisecond, uint reference_time_scale, zego_publish_channel channel);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_register_room_state_update_callback(zego_on_room_state_update callback_func, IntPtr data);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_register_publisher_state_update_callback(zego_on_publisher_state_update callback_func, IntPtr data);

        [DllImport("ZegoExpressEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_register_publisher_quality_update_callback(zego_on_publisher_quality_update callback_func, IntPtr data);
    }
}
