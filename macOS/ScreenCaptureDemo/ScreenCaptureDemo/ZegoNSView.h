//
//  ZegoNSView.h
//  ScreenCaptureDemo
//
//  Created by MrLQ  on 2019/7/22.
//  Copyright © 2019 李展鹏. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZegoNSView : NSView

@property (nonatomic, copy) void (^mouseDownInsideBlock)(NSEvent *theEvent); // 这个block用于接受mouseDown传递过来的event



@end

NS_ASSUME_NONNULL_END
