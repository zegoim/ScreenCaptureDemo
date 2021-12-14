#ifndef ZEGO_WINDOWTHUMBNAIL_H_
#define ZEGO_WINDOWTHUMBNAIL_H_

#include "zego-windowthumbnail-defines.h"

#ifdef __cplusplus
extern "C" {
#endif

    /// \brief 异步获取窗口列表的缩略图(windows未实现)
    /// \param isAsync  默认为false。设置为true,zego_windowthumbnail_find_windows接口不返回缩略图，需要通过zego_windowthumbnail_register异步获取缩略图
    /// \see 需在zego_windowthumbnail_find_windows调用。
    SCREENCAPTURE_API void zego_windowthumbnail_find_windows_async(bool isAsync);

	/// \brief 枚举可建立缩略图的窗口列表,包括窗口标题和窗口句柄
	/// \param count 窗口数量
	/// \return 窗口列表首地址,需配对调用zego_thumbnail_free_windows释放
	/// \see zego_thumbnail_free_windows
	SCREENCAPTURE_API struct ZegoThumbnailWindowInfo* zego_windowthumbnail_find_windows(int *count);

	/// \brief 释放枚举到的窗口列表
	/// \param window_list 枚举到的窗口列表首地址,由zego_windowthumbnail_find_windows返回的窗口信息列表
	/// \param count 窗口信息列表长度
	/// \see zego_windowthumbnail_find_windows
	SCREENCAPTURE_API void zego_windowthumbnail_free_windows(struct ZegoThumbnailWindowInfo* window_list, int count);

#ifdef WIN32
	/// \brief 注册缩略图同时注册窗口状态检测
	/// \param destination_handle 目的窗口的句柄,必须是顶层窗口(如果为空,只注册状态检测)
	/// \param thumbnail_id 缩略图标志 为zego_thumbnail_find_windows或者zego_windowthumbnail_window_status_change_notify_func返回的窗口列表中的thumbnail_id
	/// \param destination_rect 目的窗口缩略图显示区域,目的窗口坐标系
	/// \param destination_client_rect 目的窗口客户区区域,目的窗口坐标系
	/// \return 成功或失败
	/// \see zego_thumbnail_find_windows
	/// \see zego_windowthumbnail_window_status_change_notify_func
	SCREENCAPTURE_API bool zego_windowthumbnail_register(ZegoWindowHandle destination_handle, int thumbnail_id, struct ZegoScreenCaptureRect* destination_rect, struct ZegoScreenCaptureRect* destination_client_rect);
#else
	/// \brief 同步注册缩略图
	/// \param handle 缩略图标志 为zego_thumbnail_find_windows或者zego_windowthumbnail_window_status_change_notify_func返回的窗口列表中的handle
	/// \return 成功或失败
	/// \see zego_thumbnail_find_windows
	/// \see zego_windowthumbnail_window_status_change_notify_func
	SCREENCAPTURE_API bool zego_windowthumbnail_register(ZegoWindowHandle handle);
#endif
	/// \brief 更新缩略图位置
	/// \param thumbnail_id 缩略图标志 为zego_thumbnail_find_windows或者zego_windowthumbnail_window_status_change_notify_func返回的窗口列表中的thumbnail_id
	/// \param destination_rect 缩略图显示新的区域,目的窗口坐标系
	/// \param destination_client_rect 目的窗口客户区区域,目的窗口坐标系
	/// \return 成功或失败
	/// \see zego_thumbnail_find_windows
	/// \see zego_windowthumbnail_window_status_change_notify_func
	/// \see macOS没有实现
	SCREENCAPTURE_API bool zego_windowthumbnail_update(int thumbnail_id, struct ZegoScreenCaptureRect* destination_rect, struct ZegoScreenCaptureRect* destination_client_rect);

	/// \brief 检测是否能够开始共享
	/// \param handle 缩略图标志 为zego_thumbnail_find_windows或者zego_windowthumbnail_window_status_change_notify_func返回的窗口列表中的handle
	/// \return 是否能够共享窗口
	/// \see zego_thumbnail_find_windows
	/// \see zego_windowthumbnail_window_status_change_notify_func
	/// \note Windows下总会返回true
	SCREENCAPTURE_API bool zego_windowthumbnail_window_checkStatus(ZegoWindowHandle handle);

	/// \brief 反注册缩略图同时反注册状态监测
	/// \param thumbnail_id 缩略图标志为zego_thumbnail_find_windows或者zego_windowthumbnail_window_status_change_notify_func返回的窗口列表中的thumbnail_id
	/// \return 成功或失败
	/// \see zego_thumbnail_find_windows
	/// \see zego_windowthumbnail_window_status_change_notify_func
	SCREENCAPTURE_API bool zego_windowthumbnail_unregister(int thumbnail_id);

	/// \brief 显示或隐藏源窗口
	/// \param handle 窗口句柄
	/// \param cmd 最大化、最小化、显示、隐藏
	/// \return 成功或失败
	SCREENCAPTURE_API bool zego_windowthumbnail_show_source_window(ZegoWindowHandle handle, enum ZegoThumbnailShowWindowCmd cmd);

	/// \brief 注册窗口状态变化回调
	/// \param notify 通知函数
	/// \param user_data 用户自定义数据，回调时透传
	SCREENCAPTURE_API void zego_windowthumbnail_reg_window_status_change_notify(zego_windowthumbnail_window_status_change_notify_func notify, void *user_data);

#ifdef __cplusplus
}
#endif

#endif
