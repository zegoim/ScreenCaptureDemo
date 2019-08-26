//
//  ZegoVideoCaptureFromScreen.m
//  LiveDemo5OSX
//
//  Created by Strong on 2017/5/3.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import "ZegoVideoCaptureFromScreen.h"
#import <AVFoundation/AVFoundation.h>

@interface ZegoVideoCaptureFromScreen ()
@property (nonatomic, strong) id<ZegoVideoCaptureClientDelegate> client;
@property (nonatomic, assign) BOOL isCapturing;

@end

@implementation ZegoVideoCaptureFromScreen

- (void)zego_allocateAndStart:(id<ZegoVideoCaptureClientDelegate>)client
{
    self.client = client;
    
    [self.client setFillMode:ZegoVideoFillModeBlackBar];
}

- (void)zego_stopAndDeAllocate
{
    [self.client destroy];
    self.client = nil;
}

- (int)zego_startCapture
{
    self.isCapturing = YES;
    return 0;
}

- (int)zego_stopCapture
{
    self.isCapturing = NO;
    return 0;
}

- (void)captureOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnectrion:(AVCaptureConnection*)connection
{
    CMTime pts = CMSampleBufferGetPresentationTimeStamp(sampleBuffer);
    //    NSTimeInterval currentCTime = CMTimeGetSeconds(pts);
    
    //    if (self.timeDelta == 0)
    //        self.timeDelta = currentCTime - [[NSDate date] timeIntervalSince1970];
    
    CVImageBufferRef buffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    
    if (self.isCapturing)
        [self.client onIncomingCapturedData:buffer withPresentationTimeStamp:pts];
}

- (void)captureOutputPixelBuffer:(CVPixelBufferRef)pixelBuffer timeStamp:(CMTime)time
{
    if (self.isCapturing){
        [self.client onIncomingCapturedData:pixelBuffer withPresentationTimeStamp:time];
        }
}

@end


@interface ZegoVideoCaptureScreenFactory ()

@end

@implementation ZegoVideoCaptureScreenFactory

- (id<ZegoVideoCaptureDevice>)zego_create:(NSString *)deviceId
{
    if (self.screenDevice == nil)
    {
        _screenDevice = [[ZegoVideoCaptureFromScreen alloc] init];
    }
    
    return self.screenDevice;
}

- (void)zego_destroy:(id<ZegoVideoCaptureDevice>)device
{
    _screenDevice = nil;
}

@end

