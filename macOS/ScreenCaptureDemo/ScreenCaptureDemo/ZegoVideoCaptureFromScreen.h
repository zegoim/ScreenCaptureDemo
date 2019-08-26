//
//  ZegoVideoCaptureFromScreen.h
//  LiveDemo5OSX
//
//  Created by Strong on 2017/5/3.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <ZegoLiveRoomOSX/ZegoVideoCapture.h>

typedef NS_ENUM(NSInteger, CaptureSource)
{
    CAPTURE_FROM_CAMERA,
    CAPTURE_FROM_SCREEN,
    CAPTURE_FROM_WINDOW,
};

@interface ZegoVideoCaptureFromScreen : NSObject <ZegoVideoCaptureDevice>

@property (nonatomic, assign) CMTime currentPts;

- (void)captureOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnectrion:(AVCaptureConnection*)connection;

- (void)captureOutputPixelBuffer:(CVPixelBufferRef)pixelBuffer timeStamp:(CMTime)time;

@end

@interface ZegoVideoCaptureScreenFactory : NSObject<ZegoVideoCaptureFactory>

@property (nonatomic, strong, readonly) ZegoVideoCaptureFromScreen *screenDevice;

@property (nonatomic, assign) CaptureSource source;

@end

