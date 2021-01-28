//
//  zego-express-camera-capturer.h
//  ZegoExpressSDK
//
//  Created by 李展鹏@ZEGO on 2019/12/31.
//

#ifndef __ZEGO_EXPRESS_CAMERA_CAPTURER_H__
#define __ZEGO_EXPRESS_CAMERA_CAPTURER_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS

typedef void(*zego_on_camera_capturer_video_frame_data)(const char* data, unsigned int data_length, const struct zego_video_frame_param param, unsigned long long timestamp, void* user_context);

/**
* 创建 摄像头捕获器，用于获取原始摄像头数据
*
* 获取到原始摄像头数据之后，开发者可做相关视频前处理（如美颜、滤镜等），之后通过自定义采集 API 将处理后的视频数据发送给 SDK 用于编码推流
* @return (zego_instance), 摄像头对象索引
*/
ZEGOEXP_API zego_instance EXP_CALL zego_express_create_camera_capturer();

/**
* 销毁 摄像头捕获器
*
* @param instance_index, 需要销毁的摄像头对象索引
*/
ZEGOEXP_API void EXP_CALL zego_express_destroy_camera_capturer(zego_instance instance_index);

ZEGOEXP_API void EXP_CALL zego_express_camera_capturer_start(zego_instance instance_index);

ZEGOEXP_API void EXP_CALL zego_express_camera_capturer_stop(zego_instance instance_index);

ZEGOEXP_API void EXP_CALL zego_express_camera_capturer_use_device(zego_instance instance_index, const char* device_id);

ZEGOEXP_API void EXP_CALL zego_express_camera_capturer_set_parameters(zego_instance instance_index, struct zego_camera_capture_params params);

ZEGOEXP_API void EXP_CALL zego_register_camera_capturer_video_frame_data_callback(zego_on_camera_capturer_video_frame_data callback_func, void* user_context);

ZEGO_END_DECLS

#endif /* zego_express_camera_capturer_h */
