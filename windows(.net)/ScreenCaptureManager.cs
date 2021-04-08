using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ZegoScreenCapture_.net_
{
    class ScreenCaptureManager
    {
        // 注册各回调类型
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_screencapture_capture_error_notify_func(
            ZegoScreenCaptureCaptureError error,
            IntPtr user_data);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_screencapture_captured_frame_available_notify_func(
            IntPtr data,
            uint length,
            IntPtr video_frame_format,
            UInt64 reference_time,
            uint reference_time_scale,
            IntPtr user_data);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_screencapture_mutiple_captured_frame_available_notify_func(
            IntPtr data,
            uint length,
            IntPtr video_frame_format,
            UInt64 reference_time,
            uint reference_time_scale,
            uint handle,
            IntPtr user_data);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_screencapture_capture_dwm_composition_change_notify_func(
            bool enable,
            IntPtr data);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_screencapture_capture_process_window_change_notify_func(
            int status,
            ZegoScreenCaptureProcessWindow window_info,
            IntPtr user_data);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void zego_screencapture_captured_window_status_change_notify_func(
            int status_code,
            uint handle,
            ZegoScreenCaptureRect rect,
            IntPtr user_data);

        // 引入DLL中的func
        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_init();

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_uninit();

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_log_level(ZegoScreenCaptureLogLevel level, string path);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_start_capture();

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_stop_capture();

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_is_capturing();

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_fps(int fps);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_excluded_windows(IntPtr[] handle_list, int count, bool add);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_cover_excluded_windows(IntPtr[] handle_list, int count, bool add);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_timestamp_offset(UInt64 offset);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_resolution(int width, int height);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_activate_window_when_capturing(int active);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_set_target_window(IntPtr handle);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_set_extra_target_windows(IntPtr[] handle_list, int count, bool add);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_set_target_window_mode(int mode);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_set_target_window_rect(int left, int top, int width, int height);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string zego_screencapture_get_window_screen(IntPtr handle);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool zego_screencapture_get_window_rect(IntPtr handle, ref ZegoScreenCaptureRect rect);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_set_target_rect(string screen, int left, int top, int width, int height);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int zego_screencapture_set_target_screen(string screen);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_cursor_visible(int visible);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_enable_click_animation(int enable);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_get_virtual_desktop_rect(ref int left, ref int top, ref int width, ref int height);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr zego_screencapture_enum_screen_list(ref uint count);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_free_screen_list(IntPtr screen_list);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr zego_screencapture_enum_window_list(int isIncludeIconic, ref uint count);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_free_window_list(IntPtr screen_list);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_set_capture_video_pixel_format(ZegoScreenCaptureVideoPixelFormat format);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_reg_captured_frame_available_notify(zego_screencapture_captured_frame_available_notify_func notify, IntPtr data);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_reg_mutiple_captured_frame_available_notify(zego_screencapture_mutiple_captured_frame_available_notify_func notify, IntPtr data);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_reg_captured_window_status_change_notify(zego_screencapture_captured_window_status_change_notify_func notify, IntPtr data);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_reg_capture_error_notify(zego_screencapture_capture_error_notify_func notify, IntPtr data);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_reg_capture_dwm_composition_change_notify(zego_screencapture_capture_dwm_composition_change_notify_func notify, IntPtr data);

        [DllImport("ZegoScreenCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zego_screencapture_reg_capture_process_window_change_notify(zego_screencapture_capture_process_window_change_notify_func notify, IntPtr data);
    }

}
