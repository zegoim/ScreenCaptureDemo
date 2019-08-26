//
//  ZegoScreenItem.h
//  ScreenCaptureDemo
//
//  Created by 李展鹏 on 2018/4/1.
//  Copyright © 2019年 Zego. All rights reserved.
//

#ifndef ZegoScreenItem_h
#define ZegoScreenItem_h

#import <Foundation/Foundation.h>

@interface ZegoScreenItem : NSObject

@property (nonatomic, assign)CGDirectDisplayID screenID;

@property (nonatomic, assign)BOOL isPrimary;

@end

#endif /* ZegoScreenItem_h */
