#ifndef ZEGO_WINDOWTHUMBNAIL_DEFINES_H_
#define ZEGO_WINDOWTHUMBNAIL_DEFINES_H_

#include "zego-screencapture-defines.h"

#define ZEGO_MAX_TITLE    (256)

typedef struct ZegoThumbnailBitmap ZegoThumbnailBitmap;

struct ZegoThumbnailBitmap
{
	int width;				///< 图像宽（像素）
	int height;				///< 图像高（像素）
	int format;				///< (未使用) 默认BGRA32
	unsigned int len;		///< 图像数据长度
	unsigned char* bits;	///< 图像数据
};

struct ZegoThumbnailWindowInfo
{
	int thumbnail_id;							///< 缩略图ID
	ZegoWindowHandle handle;					///< 窗口句柄
	char window_title[ZEGO_MAX_TITLE];			///< 窗口标题（windows当isScreen为true时 格式为 屏幕1----\\\\.\\DISPLAY1)
	ZegoThumbnailBitmap *icon_bits;				///< 源窗口进程图标数据
	ZegoThumbnailBitmap *image_bits;			///< 缩略图数据
	bool isScreen;								///< 是否是屏幕
	bool isSDKRender;							///< 是否可以SDK渲染, 当为true时，调用register后可以由SDK将缩略图渲染到指定区域，MacOS默认为false				
};

enum ZegoThumbnailShowWindowCmd
{
	kZegoThumbnailShowWindowCmdShow = 1,			///< 置顶显示
	kZegoThumbnailShowWindowCmdHide = 2,			///< 隐藏
	kZegoThumbnailShowWindowCmdMax = 3,             ///< 最大化窗口
	kZegoThumbnailShowWindowCmdMin = 4,				///< 最小化窗口
	kZegoThumbnailShowWindowCmdActive = 5			///< 激活窗口
};

enum ZegoThumbnailWindowStatus
{
	kZegoThumbnailWindowStatusCreate = 1,			///< 窗口建立
	kZegoThumbnailWindowStatusDestroy = 2,          ///< 窗口销毁
	kZegoThumbnailWindowStatusInvalid = 3,          ///< 窗口无法建立缩略图
	kZegoThumbnailWindowStatusCaptureChange = 4,    ///< 窗口名称改变
    kZegoThumbnailWindowStatusThumbnail = 5         ///< (macOS使用)获取到缩略图数据
};

/// \brief 窗口状态变化回调
/// \param status_code 窗口状态  参考ZegoThumbnailWindowStatus
/// \param window_info 窗口信息
/// \param user_data 透传的用户上下文数据
/// \see ZegoThumbnailWindowStatus
/// \see zego_windowthumbnail_free_windows
typedef void(*zego_windowthumbnail_window_status_change_notify_func)(enum ZegoThumbnailWindowStatus status_code, struct ZegoThumbnailWindowInfo* window_info, void *user_data);

#endif
