using System;
using System.Runtime.InteropServices;

namespace ZegoScreenCapture_.net_
{
    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct ZegoScreenCaptureRect
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct ZegoScreenCaptureScreenItem
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string ZegoScreenName;
        public int is_primary;
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct ZegoScreenCaptureWindowItem
    {
        public IntPtr handle;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string title;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string image_path;
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    public struct ZegoScreenCaptureProcessWindow
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string process_path;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string window_title;
        public IntPtr handle;
    };

    public enum ZegoScreenCaptureLogLevel : int
    {
        kZegoLogLevelGrievous = 0,
        kZegoLogLevelError = 1,
        kZegoLogLevelWarning = 2,
        kZegoLogLevelGeneric = 3,
        kZegoLogLevelDebug = 4
    };

    public enum ZegoScreenCaptureCaptureError : int
    {
        kZegoCaptureErrorUnexpected = 1,
        kZegoCaptureErrorTargetUnspecified = 2,
        kZegoCaptureErrorTargetInvalid = 3,
        kZegoCaptureErrorCaptureFunctionFailed = 4,
        KZegoCaptureErrorScreenChange = 5,
        KZegoCaptureErrorExcludeInvalid = 6,
    };

    public enum ZegoScreenCaptureWindowStatus : int
    {
        kZegoScreenCaptureWindowNoChange = 0,
        kZegoScreenCaptureWindowDestroy,
        kZegoScreenCaptureWindowMaximize,
        kZegoScreenCaptureWindowMinimize,
        kZegoScreenCaptureWindowActive,
        kZegoScreenCaptureWindowDeactive,
        kZegoScreenCaptureWindowShow,
        kZegoScreenCaptureWindowHide,
        kZegoScreenCaptureWindowMove,
        kZegoScreenCaptureWindowCover,
        kZegoScreenCaptureWindowUnCover
    };

    public enum ZegoScreenCaptureVideoPixelFormat : int
    {
        kZegoPixelFormatUnknown = 0,
        kZegoPixelFormatI420 = 1,
        kZegoPixelFormatNV12 = 2,
        kZegoPixelFormatNV21 = 3,
        kZegoPixelFormatBGRA32 = 4,
        kZegoPixelFormatRGBA32 = 5,
        kZegoPixelFormatCVImageBuffer = 100,
    };

    public enum ZegoScreenCaptureWindowMode : int
    {
        kZegoScreenCaptureWindowModeWindow = 1,
        kZegoScreenCaptureWindowModeClient = 2,
        kZegoScreenCaptureWindowModeRgn1 = 3,
        kZegoScreenCaptureWindowModeRgn2 = 4,
        kZegoScreenCaptureWindowModeRgn3 = 5,
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
    struct ZegoScreenCaptureVideoCaptureFormat
    {
        public int width;
        public int height;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int[] strides;
        public int rotation;
        public ZegoScreenCaptureVideoPixelFormat video_pixel_format;
    };
}
