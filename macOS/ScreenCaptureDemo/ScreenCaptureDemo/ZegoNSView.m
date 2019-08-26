//
//  ZegoNSView.m
//  ScreenCaptureDemo
//
//  Created by MrLQ  on 2019/7/22.
//  Copyright © 2019年 Zego. All rights reserved.
//

#import "ZegoNSView.h"

@implementation ZegoNSView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}


-(void)mouseDown:(NSEvent *)theEvent {
    if (self.mouseDownInsideBlock) {
        NSPoint aPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
        if (!NSPointInRect(aPoint, self.bounds)) {
            return;
        }
        // Call back
        self.mouseDownInsideBlock(theEvent); // 事件传递
    } else {
        [super mouseDown:theEvent];
    }
}

//翻转坐标系
- (BOOL)isFlipped{
    return YES;
}

@end
