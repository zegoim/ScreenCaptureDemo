//
//  ZegoSettings.h
//  LiveDemo5OSX
//
//  Created by Strong on 2017/4/21.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZegoAVKitManager.h"

typedef NS_ENUM(NSInteger, ZegoLiveQuality)
{
    kLiveQualityVeryLow     = 0,
    kLiveQualityLow         = 1,
    kLiveQualityGeneric     = 2,
    kLiveQualityHigh        = 3,
    kLiveQualityVeryHigh    = 4,
    kLiveQualityCustom      = 5
};

@interface ZegoSettings : NSObject

+ (instancetype)defaultSetting;

@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *userName;

@property (nonatomic, strong) ZegoAVConfig *currentConfig;

@property (nonatomic, assign) ZegoLiveQuality quality;

@end

