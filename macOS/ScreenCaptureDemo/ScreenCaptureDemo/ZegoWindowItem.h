//
//  ZegoWindowItem.h
//  ScreenCaptureDemo
//
//  Created by 李展鹏 on 2018/4/1.
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef ZegoWindowItem_h
#define ZegoWindowItem_h

#import <Foundation/Foundation.h>

@interface ZegoWindowItem : NSObject

@property (nonatomic, assign)CGWindowID windowID;

@property (nonatomic, strong)NSString *title;

@property (nonatomic, strong)NSString *image_path;

@property (nonatomic, assign)BOOL isScreen;


@end

#endif /* ZegoWindowItem_h */
