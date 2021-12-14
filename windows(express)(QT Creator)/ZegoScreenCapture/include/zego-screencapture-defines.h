﻿#ifndef ZEGO_SCREENCAPTURE_DEFINES_H_
#define ZEGO_SCREENCAPTURE_DEFINES_H_

#include <stdint.h>
#ifdef WIN32
#ifdef SCREENCAPTURE_EXPORTS
#define SCREENCAPTURE_API __declspec(dllexport)
#else
#define SCREENCAPTURE_API __declspec(dllimport)
#endif
#else
#define SCREENCAPTURE_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
	typedef void* ZegoWindowHandle;			///< windows窗口句柄
	typedef char ZegoScreenName[32];		///< windows屏幕名称
	typedef char* ZegoScreenID;				///< windows屏幕名称
#else
	typedef unsigned int ZegoWindowHandle;	///< macOS窗口ID
	typedef unsigned int ZegoScreenName;    ///< macOS屏幕ID 
	typedef ZegoScreenName ZegoScreenID;	///< macOS屏幕ID
#endif

struct ZegoScreenCaptureRect
{
	int left;									///< 左上角横坐标
	int top;									///< 左上角纵坐标
	int right;									///< 右下角横坐标
	int bottom;									///< 右下角纵坐标
};

enum ZegoScreenCaptureLogLevel
{
    kZegoLogLevelGrievous = 0,
    kZegoLogLevelError = 1,
    kZegoLogLevelWarning = 2,
    kZegoLogLevelGeneric = 3,    ///< 通常在发布产品中使用
    kZegoLogLevelDebug = 4       ///< 调试阶段使用
};

enum ZegoScreenCaptureCaptureError
{
    kZegoCaptureErrorUnexpected = 1,
    kZegoCaptureErrorTargetUnspecified = 2,			///< 采集目标未指定
    kZegoCaptureErrorTargetInvalid = 3, 			///< 采集目标失效，比如显示器被拔掉、窗口被关闭
    kZegoCaptureErrorCaptureFunctionFailed = 4,
	KZegoCaptureErrorScreenChange = 5				//屏幕分辨率改变
};

/// \brief 采集错误回调
/// \param error 错误代码
/// \param user_data 用户自定义数据
/// \see ZegoScreenCaptureCaptureError
typedef void (*zego_screencapture_capture_error_notify_func)(enum ZegoScreenCaptureCaptureError error, void *data);

enum ZegoScreenCaptureWindowStatus
{
	kZegoScreenCaptureWindowNoChange = 0,			///< 窗口无变化
	kZegoScreenCaptureWindowDestroy,				///< 窗口销毁
	kZegoScreenCaptureWindowMaximize,				///< 窗口最大化
	kZegoScreenCaptureWindowMinimize,				///< 窗口最小化
	kZegoScreenCaptureWindowActive,					///< 窗口激活
	kZegoScreenCaptureWindowDeactive,				///< 窗口失去激活
	kZegoScreenCaptureWindowShow,					///< 窗口显示
	kZegoScreenCaptureWindowHide,					///< 窗口隐藏
	kZegoScreenCaptureWindowMove,					///< 窗口移动
	kZegoScreenCaptureWindowCover,					///< 窗口被覆盖
	kZegoScreenCaptureWindowUnCover					///< 覆盖窗口被移开
};

struct ZegoScreenCaptureScreenItem
{
	ZegoScreenName name;							///< 屏幕唯一标识名
    int is_primary;									///< 是否主屏
};

struct ZegoScreenCaptureWindowItem
{
	ZegoWindowHandle handle;						///< 窗口唯一标识
    char title[256];								///< 窗口标题
    char image_path[256];							///< 窗口对应进程所在路径
};

/// \brief 采集目标窗口位置、大小发生改变（zego_screencapture_start_capture 之后生效）
/// \param handle 窗口ID
/// \param left 窗口原点坐标（左上角）横坐标
/// \param top 窗口原点坐标（左上角）纵坐标
/// \param width 窗口宽度
/// \param height 窗口高度
/// \param user_data 用户自定义数据
/// \note 采集目标窗口位置、大小发生改变（当采集目标为窗口时,zego_screencapture_start_capture之后生效）窗口如果被最小化，也会调用此回调，坐标为(0,0,0,0)
/// \see zego_screencapture_start_capture
/// \see zego_screencapture_captured_window_status_change_notify_func
typedef void (*zego_screencapture_captured_window_moved_notify_func)(ZegoWindowHandle handle, int left, int top, int width, int height, void *user_data);

/// \brief 采集目标窗口状态发生改变（zego_screencapture_start_capture 之后生效）
/// \param status_code 窗口状态
/// \param handle 窗口ID
/// \param rect 窗口矩形
/// \param user_data 用户自定义数据
/// \note 采集目标窗口状态发生改变（当采集目标为窗口时,zego_screencapture_start_capture之后生效)
/// \see zego_screencapture_start_capture
typedef void(*zego_screencapture_captured_window_status_change_notify_func)(enum ZegoScreenCaptureWindowStatus status_code, ZegoWindowHandle handle, struct ZegoScreenCaptureRect rect, void *user_data);

enum ZegoScreenCaptureVideoPixelFormat
{
    kZegoPixelFormatUnknown = 0,
    kZegoPixelFormatI420 = 1,						///< 仅windows下支持
    kZegoPixelFormatNV12 = 2,						///< 暂未支持
    kZegoPixelFormatNV21 = 3,						///< 暂未支持
    kZegoPixelFormatBGRA32 = 4,						///< 默认的画面数据的颜色空间类型
    kZegoPixelFormatRGBA32 = 5,						///< 暂未支持
	kZegoPixelFormatCVImageBuffer = 100,			///< macOS下CVImageBufferRef类型数据
};

enum ZegoScreenCaptureWindowMode
{
	kZegoScreenCaptureWindowModeWindow = 1,			///< 截取窗口整体画面
	kZegoScreenCaptureWindowModeClient = 2,			///< 截取窗口客户区
	kZegoScreenCaptureWindowModeRgn1 = 3,			///< 截取窗口对应屏幕区域	(窗口被覆盖后继续捕获对应区域)
	kZegoScreenCaptureWindowModeRgn2 = 4,			///< 截取窗口对应屏幕区域	(窗口被覆盖后继续捕获，覆盖区域涂黑)
	kZegoScreenCaptureWindowModeRgn3 = 5,			///< 截取窗口对应屏幕区域	(窗口被覆盖后继续捕获，过滤上层覆盖的窗口，win8及以后系统生效)
};

struct ZegoScreenCaptureVideoCaptureFormat
{
    int width;						///< 采集画面宽（像素）
    int height;						///< 采集画面高（像素）
    int strides[4];					///< 采集画面的步长
    int rotation;
    enum ZegoScreenCaptureVideoPixelFormat video_pixel_format;	///< 采集画面数据格式
};

struct ZegoScreenCaptureProcessWindow
{
	char process_path[256];							///< 采集窗口所属进程路径
	char window_title[256];							///< 窗口标题
	ZegoWindowHandle handle;						///< 窗口id		
};

/// \brief 采集数据回调
/// \param data 每一帧截图元数据
/// \param length 元数据大小
/// \param video_frame_format 帧信息: format、长宽等
/// \param reference_time 时间戳
/// \param reference_time_scale 时间戳单位,如果是ms则是1000
/// \param user_data 用户自定义数据
/// \see ZegoScreenCaptureVideoCaptureFormat
typedef void(*zego_screencapture_captured_frame_available_notify_func)(const void *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data);

/// \brief 采集数据回调
/// \param data 每一帧截图元数据
/// \param length 元数据大小
/// \param video_frame_format 帧信息: format、长宽等
/// \param reference_time 时间戳
/// \param reference_time_scale 时间戳单位,如果是ms则是1000
/// \param handle 采集到窗口ID
/// \param user_data 用户自定义数据
/// \see ZegoScreenCaptureVideoCaptureFormat
typedef void(*zego_screencapture_mutiple_captured_frame_available_notify_func)(const void *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, ZegoWindowHandle handle, void *user_data);

/// \brief 桌面组合变更回调(win7下使用)
/// \param enable 是否开启桌面组合
/// \param user_data 用户自定义数据
/// \see ZegoScreenCaptureCaptureError
typedef void(*zego_screencapture_capture_dwm_composition_change_notify_func)(bool enable, void *data);

/// \brief 窗口采集时窗口所属进程的其他窗口状态变化回调
/// \param status 窗口状态
/// \param window_info 窗口信息
/// \user_info 用户自定义数据
/// \note status只支持kZegoScreenCaptureWindowActive
typedef void(*zego_screencapture_capture_process_window_change_notify_func)(enum ZegoScreenCaptureWindowStatus status, struct ZegoScreenCaptureProcessWindow window_info, void *user_data);
#ifdef __cplusplus
}
#endif

#endif