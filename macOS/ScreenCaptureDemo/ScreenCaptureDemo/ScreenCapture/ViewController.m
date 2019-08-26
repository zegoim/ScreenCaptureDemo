//
//  ViewController.m
//  ScreenCaptureDemo
//
//  Created by 李展鹏 on 2018/3/31.
//  Copyright © 2018年 Zego. All rights reserved.
//

#import "ViewController.h"
#import <ZegoLiveRoomOSX/ZegoLiveRoomApi.h>
#import <ZegoLiveRoomOSX/ZegoLiveRoomApi-Publisher.h>
#import "ZegoVideoCaptureFromScreen.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoScreenItem.h"
#import "ZegoWindowItem.h"
#import <Carbon/Carbon.h>


#import "zego-screencapture.h"
#import "zego-screencapture-defines.h"
#import "zego-windowthumbnail-defines.h"
#import "zego-windowthumbnail.h"


#import <Carbon/Carbon.h>
#import "ZegoShareDeskWindow.h"

#import <AppKit/NSAccessibility.h>

BOOL isCapture;

@interface ViewController() <ZegoRoomDelegate, ZegoLivePublisherDelegate>

@property (nonatomic, strong)NSMutableArray<ZegoScreenItem *>*m_screenList;

@property (nonatomic, strong)NSMutableArray<ZegoWindowItem *>*m_windowList;
@property (weak) IBOutlet NSSlider *X;
@property (weak) IBOutlet NSSlider *Y;
@property (weak) IBOutlet NSSlider *Width;
@property (weak) IBOutlet NSSlider *Height;


@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self initScreenAndWindowList];
    
    NSString* logpath = @"/Users/mrlq/ZegoScreenCapture/Mac_OSX/ScreenCaptureDemo";
    
    //注册日志
    zego_screencapture_set_log_level(4, [logpath cStringUsingEncoding:NSASCIIStringEncoding]);
    //注册数据采集回调
    zego_screencapture_reg_captured_frame_available_notify(frame_available_notify, NULL);
    //注册错误的回调通知
    zego_screencapture_reg_capture_error_notify(zego_screencapture_capture_error_notify , NULL);
    
    //初始化屏幕分享SDK
    zego_screencapture_init();
    [[ZegoAVKitManager shareInstance].roomApi setRoomDelegate:self];
    [[ZegoAVKitManager shareInstance].roomApi setPublisherDelegate:self];
    
    
    //设置每秒的采集次数
    zego_screencapture_set_fps(30);
    //设置回调的数据类型
    zego_screencapture_set_capture_video_pixel_format(kZegoPixelFormatCVImageBuffer);
    
    
    //初始化推流
    isCapture = NO;
    ZegoVideoCaptureScreenFactory *captureFactory = [ZegoAVKitManager shareInstance].captureFactory;
    captureFactory.source = CAPTURE_FROM_SCREEN;
    
    
    //获取屏幕列表
    int screenListLen = 0;
    const struct ZegoScreenCaptureScreenItem *screenList = zego_screencapture_enum_screen_list(&screenListLen);
    
    for(int i = 0; i < screenListLen; ++i)
    {
        //NSLog(@"[***] screenID: %d, isPrimary: %d", screenList[i].name, screenList[i].is_primary);
        ZegoScreenItem *screenItem = [[ZegoScreenItem alloc] init];
        screenItem.screenID = (CGDirectDisplayID)screenList[i].name;
        screenItem.isPrimary = screenList[i].is_primary;
        
        [self.m_screenList addObject:screenItem];
    }
    zego_screencapture_free_screen_list(screenList);
    

    //采集窗口
    int windowListLen = 0;
    const struct ZegoThumbnailWindowInfo * windowList = zego_windowthumbnail_find_windows(&windowListLen);
    for (int i = 0; i < windowListLen; i++)
    {
//        NSLog(@"[***] windowID: %d title: %s", windowList[i].handle, windowList[i].title);
        struct ZegoThumbnailWindowInfo info = windowList[i];
        ZegoWindowItem *windowItem = [[ZegoWindowItem alloc] init];
        windowItem.windowID = (CGWindowID)windowList[i].handle;
        windowItem.title = [NSString stringWithUTF8String:(windowList[i].window_title)];
        
        [self.m_windowList addObject:windowItem];
    }
    zego_screencapture_free_window_list(windowList);
    
    //初始化comboBox内容
    [_m_cbScreenList removeAllItems];
    for (ZegoScreenItem *screenItem in self.m_screenList)
    {
        [_m_cbScreenList addItemWithObjectValue:[NSString stringWithFormat:@"ID: %d", screenItem.screenID]];
        if (screenItem.screenID == CGMainDisplayID())
        {
            _m_cbScreenList.stringValue = [NSString stringWithFormat:@"ID: %d", screenItem.screenID];
            zego_screencapture_set_target_screen(screenItem.screenID);

        }
    }
    
    _m_radioButtonScreen.state = YES;
    
    [_m_cbWindowList removeAllItems];
    for (ZegoWindowItem *windowItem in self.m_windowList)
    {
        [_m_cbWindowList addItemWithObjectValue:[NSString stringWithFormat:@"%@", windowItem.title]];
        NSLog(@"windowID = %d, title: %@", windowItem.windowID, windowItem.title);
    }
    
    if([self.m_windowList count] > 0)
    {
        _m_cbWindowList.stringValue = [self.m_windowList firstObject].title;
    }
    
    //初始化slider & label
    _m_lbFPS.stringValue = _m_sliderFPS.stringValue;
    
    zego_screencapture_enable_click_animation(true);
    zego_screencapture_set_cursor_visible(true);
    [[ZegoAVKitManager shareInstance].roomApi startPreview];
 
}

- (void)initScreenAndWindowList
{
    _m_screenList = [[NSMutableArray alloc] init];
    _m_windowList = [[NSMutableArray alloc] init];
    
    _m_cbScreenList.editable = NO;
    _m_cbWindowList.editable = NO;
    
    [_m_cbScreenList setAction:@selector(buttonClick:)];
    [_m_cbWindowList setAction:@selector(buttonClick:)];
}

- (void)buttonClick:(NSComboBox *)boc
{
    ZegoVideoCaptureScreenFactory *captureFactory = [ZegoAVKitManager shareInstance].captureFactory;
    NSInteger index_for_combox = [boc indexOfSelectedItem];

    //设置采集屏幕
    if (captureFactory.source == CAPTURE_FROM_SCREEN && boc == _m_cbScreenList) {
        zego_screencapture_set_target_screen([_m_screenList objectAtIndex:index_for_combox].screenID);
    //设置采集窗口
    }else if(captureFactory.source == CAPTURE_FROM_WINDOW && boc == _m_cbWindowList){
        zego_screencapture_set_target_window([_m_windowList objectAtIndex:index_for_combox].windowID);
    }
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}



//开始采集，停止采集
- (IBAction)onButtonStartCapture:(id)sender {
    
    if(isCapture)
    {
        zego_screencapture_stop_capture();
        _m_bStartCapture.stringValue = @"开始采集";
        isCapture = NO;
    }
    else
    {
    zego_screencapture_start_capture();
    _m_bStartCapture.stringValue = @"停止采集";
    isCapture = YES;
    }
}


//设置采集类型
- (IBAction)onRadioButtonClick:(id)sender {
    
    ZegoVideoCaptureScreenFactory *captureFactory = [ZegoAVKitManager shareInstance].captureFactory;
    
    if (sender == _m_radioButtonScreen)
    {
        NSLog(@"clicked screen button.");
        captureFactory.source = CAPTURE_FROM_SCREEN;
        zego_screencapture_set_target_screen([_m_screenList objectAtIndex:0].screenID);
    }
    else if (sender == _m_radioButtonWindow)
    {
        NSLog(@"clicked window button.");
        captureFactory.source = CAPTURE_FROM_WINDOW;
        zego_screencapture_set_target_window([_m_windowList objectAtIndex:3].windowID);
        //zego_screencapture_start_capture();
    }
    else if (sender == _m_radioButtonScreenRect)
    {
        NSLog(@"clicked rect button.");
        captureFactory.source = CAPTURE_FROM_SCREEN;
        zego_screencapture_set_target_rect(CGMainDisplayID(), self.X.integerValue, self.Y.integerValue, self.Width.integerValue, self.Height.integerValue);
    }

}


//设置鼠标是否可见
- (IBAction)onCheckCursorCapture:(id)sender {
    if (_m_bCursorCapture.state == YES)
    {
        zego_screencapture_set_cursor_visible(true);
    }
    else
    {
        zego_screencapture_set_cursor_visible(false);
    }
}


//设置鼠标动画
- (IBAction)onCheckMouseAnimation:(id)sender {
    if (_m_bMouseAnimation.state == YES)
    {
        zego_screencapture_enable_click_animation(true);
    }
    else
    {
        zego_screencapture_enable_click_animation(false);
    }
}

//设置采集局部区域大小
- (IBAction)sliderChange:(id)sender {
    zego_screencapture_set_target_rect(CGMainDisplayID(), self.X.integerValue, self.Y.integerValue, self.Width.integerValue, self.Height.integerValue);
    
    NSLog(@"--- %@",NSStringFromRect(CGRectMake(self.X.integerValue, self.Y.integerValue, self.Width.integerValue, self.Height.integerValue)));
}



//使用预览缩略图的功能
- (IBAction)startShare:(id)sender {

    //如果需要使用thumbnail功能，需要检测是否开启了辅助功能
    CFDictionaryRef options = (__bridge CFDictionaryRef)@{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @YES};
    if (!AXIsProcessTrustedWithOptions(options)) {
        // Ask for permission
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"打开辅助功能";
        alert.informativeText = @"你需要打开辅助功能，开启后重启应用！";
        [alert runModal];
    }else{
        ZegoShareDeskWindow * _mainWindow = [[ZegoShareDeskWindow alloc]initWithWindowNibName:@"ZegoShareDeskWindow"];
        [[_mainWindow window] center];
        [_mainWindow.window orderFront:nil];
    }
}



//开始推流
- (IBAction)onButtonPublishStream:(id)sender {
    
    [[ZegoAVKitManager shareInstance].roomApi loginRoom:@"#d-564318119" roomName: @"ScreenCapture" role:ZEGO_ANCHOR withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
        if (errorCode == 0)
        {
            NSLog(@"login room success!");
            [ZegoSettings defaultSetting].quality = kLiveQualityVeryHigh;
            ZegoAVConfig *config = [ZegoSettings defaultSetting].currentConfig;
            config.fps = 30;
            config.videoCaptureResolution = CGSizeMake(1920, 1080);
            config.videoEncodeResolution = CGSizeMake(1920, 1080);
            config.bitrate = 2000 * 1000;
            [[ZegoAVKitManager shareInstance].roomApi setAVConfig:config];

            [[ZegoAVKitManager shareInstance].roomApi startPublishing:@"s-screencapture-564318119" title:@"mac_screenCapture" flag:ZEGO_SINGLE_ANCHOR];
        }
        else
        {
            NSLog(@"login room failed. error: %d", errorCode);
        }
    }];
}


//数据采集的回调
void frame_available_notify(void *data, uint32_t length, const struct ZegoScreenCaptureVideoCaptureFormat *video_frame_format, uint64_t reference_time, uint32_t reference_time_scale, void *user_data)
{
    CMTime pts= CMTimeMake(reference_time, reference_time_scale);
    ZegoVideoCaptureScreenFactory *captureFactory = [ZegoAVKitManager shareInstance].captureFactory;
    if (captureFactory)
    {
        if(isCapture)
        [captureFactory.screenDevice captureOutputPixelBuffer:data timeStamp:pts];
    }
}


//采集错误的回调
void zego_screencapture_capture_error_notify(enum ZegoScreenCaptureCaptureError error, void *data)
{
    if (error == kCaptureErrorNotify) {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"采集异常";
        alert.informativeText = @"当前窗口无法共享，请检查权限并且将窗口置顶";
        [alert runModal];
        zego_screencapture_stop_capture();
    }
}




#pragma mark ZegoLivePublisherDelegate
- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    if(stateCode != 0)
        return;
    
    NSString *rtmp = [info[kZegoRtmpUrlListKey] firstObject];
    _m_edRtmp.stringValue = rtmp;
}

- (IBAction)uninit:(id)sender {
    
    zego_screencapture_uninit();
}

- (IBAction)init:(id)sender {
    
    zego_screencapture_init();
}


@end

