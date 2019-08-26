//
//  ZegoAVKitManager.h
//  LiveDemo5OSX
//
//  Created by Strong on 2017/4/20.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ZegoLiveRoomOSX/ZegoLiveRoomApi.h>
#import <ZegoLiveRoomOSX/ZegoLiveRoomApi-Player.h>
#import <ZegoLiveRoomOSX/ZegoLiveRoomApi-Publisher.h>
#import <ZegoLiveRoomOSX/ZegoLiveRoomApi-IM.h>

#import "ZegoVideoCaptureFromScreen.h"

typedef enum : NSUInteger {
    ZegoAppTypeUDP      = 1,    // 国内版
    ZegoAppTypeI18N     = 2,    // 国际版
    ZegoAppTypeCustom   = 3,    // 自定义
} ZegoAppType;

@interface ZegoAVKitManager : NSObject

+ (instancetype)shareInstance;

- (ZegoLiveRoomApi *)roomApi;
- (void)releaseLiveRoom;
- (unsigned int)appID;

- (NSString *)getPublishStreamID;

- (BOOL)isWereWolfRoom:(NSString *)roomID;
- (BOOL)isSingleRoom:(NSString *)roomID;

- (void)setCustomAppID:(unsigned int)appID appSign:(NSString *)appSign;
- (NSString *)appSign;

- (void)setCaptureSource:(CaptureSource)source;

@property (nonatomic, assign) BOOL testEnvironment;

@property (nonatomic, strong, readonly) ZegoVideoCaptureScreenFactory *captureFactory;

@property (nonatomic, assign) ZegoAppType appType;

- (ZegoAppType)getDefaultAppType;

@end

