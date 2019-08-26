//
//  ZegoShareDeskWindow.m
//  ScreenCaptureDemo
//
//  Created by MrLQ  on 2019/7/23.
//  Copyright © 2019年 Zego. All rights reserved.
//
#import "ZegoShareDeskWindow.h"
#import "ZegoWindowItem.h"

#import "zego-screencapture.h"
#import "zego-screencapture-defines.h"
#import "zego-windowthumbnail-defines.h"
#import "zego-windowthumbnail.h"

//#import <ScreenCapture/zego-screencapture.h>
//#import <ScreenCapture/zego-screencapture-defines.h>
//#import <ScreenCapture/zego-windowthumbnail-defines.h>
//#import <ScreenCapture/zego-windowthumbnail.h>

#import "ZegoNSView.h"

@interface ZegoShareDeskWindow ()
@property (weak) IBOutlet NSScrollView *scrollView;

@property (nonatomic, strong) NSWindowController *layerWindow;

@property (nonatomic, strong) ZegoLayerWindow *window;

@property (nonatomic, strong) NSMutableArray *dataArray;

@property (nonatomic, strong) NSMutableDictionary *viewDic;

@property (nonatomic, strong) NSMutableDictionary *iconViewDic;


@end

static ZegoShareDeskWindow *object;


@implementation ZegoShareDeskWindow

- (void)close
{
    
}

- (void)windowDidLoad {
    [super windowDidLoad];
    [[self.scrollView contentView] setPostsBoundsChangedNotifications: YES];

    int windowListLen = 0;
    object = self;
    
    //注册窗口移动通知
    zego_screencapture_reg_captured_window_moved_notify(zego_screencapture_captured_window_moved_notify, NULL);
    //注册缩略图状态改变通知
    zego_windowthumbnail_reg_window_status_change_notify(window_status_change_notify,NULL);
    //注册窗口状态改变通知
    zego_screencapture_reg_captured_window_status_change_notify(zego_screencapture_captured_window_status_change_notify,NULL);

    
    //枚举缩略图列表（包含桌面）
    const struct ZegoThumbnailWindowInfo * windowList = zego_windowthumbnail_find_windows(&windowListLen);
    
    
    NSInteger rows = 0;
    NSInteger cols = 3;
    
    CGFloat left = 24 ;
    
    CGFloat itemW = 64 * 2;
    CGFloat itemH = 64 * 2;
    CGFloat spaceH = 30 ;
    CGFloat spacew = (900 * 2 - left * 2 - itemW * 7)/6.0;
    spacew = 30;
    rows = windowListLen / cols + 1;
    
    CGFloat h = 0;
    
    ZegoNSView * documentView = [[ZegoNSView alloc]initWithFrame:NSZeroRect];
    
    for (int i = 0; i < windowListLen; i++)
    {
        //NSLog(@"[***] windowID: %d title: %s", windowList[i].handle, windowList[i].title);
        ZegoWindowItem *windowItem = [[ZegoWindowItem alloc] init];
        struct ZegoThumbnailWindowInfo info = windowList[i];
        windowItem.windowID = (CGWindowID)windowList[i].handle;
        windowItem.title = [NSString stringWithUTF8String:(windowList[i].window_title)];
        [self.dataArray addObject:windowItem];
        
        ZegoNSView * view = [[ZegoNSView alloc]initWithFrame:NSMakeRect(i % cols * (itemW + spacew) + left , i / cols * (itemH + spaceH), itemW, itemH)];
        view.wantsLayer = YES;
        view.layer.backgroundColor = NSColor.whiteColor.CGColor;
        
        [documentView addSubview:view];
        [self.viewDic setObject:view forKey:@(windowItem.windowID)];
    
        NSImageView * imageView = [[NSImageView alloc]initWithFrame:view.bounds];
        [view addSubview:imageView];
        
        [view setMouseDownInsideBlock:^(NSEvent * _Nonnull theEvent) {
            
            struct ZegoRect newrect;
            //获取当前采集窗口的区域
            zego_screencapture_get_window_rect(windowItem.windowID, &newrect);
           
            //检测是否可以采集画面（没有开启辅助功能权限可以采集数据m，但是窗口状态回调可能异常）
            bool isValid = zego_windowthumbnail_window_checkStatus(windowItem.windowID);
            if (isValid) {
                //显示窗口
                zego_windowthumbnail_show_source_window(windowItem.windowID,kZegoThumbnailShowWindowCmdShow);
                //设置采集窗口或者桌面
                zego_screencapture_set_target_window(windowItem.windowID);
                view.wantsLayer = YES;
                view.layer.backgroundColor = NSColor.redColor.CGColor;
            }else{
                NSAlert *alert = [[NSAlert alloc] init];
                alert.messageText = @"无法共享";
                alert.informativeText = @"当前窗口无法共享，请检查权限并且将窗口置顶";
                [alert runModal];
                NSLog(@"%@ ,isNotValid",windowItem.title);
            }
            
        }];
        struct ZegoRect rect;
        rect.left = view.frame.origin.x;
        rect.top = view.frame.origin.y;
        rect.right = view.frame.origin.x + view.frame.size.width;
        rect.bottom = view.frame.origin.y + view.frame.size.height;
     
        
        NSTextField *label0 = [[NSTextField alloc]init];
        label0.editable = NO;
        label0.bordered = NO; //不显示边框
        label0.backgroundColor = [NSColor greenColor]; //控件背景色
        label0.textColor = [NSColor magentaColor];  //文字颜色
        label0.alignment = NSCenterTextAlignment; //水平显示方式
        label0.frame = NSMakeRect(view.frame.origin.x , view.frame.origin.y + view.frame.size.height + 5, itemW, 20);
        label0.stringValue = windowItem.title;
        [documentView addSubview:label0];
        
        h = label0.frame.origin.y + label0.frame.size.height + 10;
        
        [self.iconViewDic setObject:label0 forKey:@( windowItem.windowID)];
        
    }
    
    for (int i = 0; i < windowListLen; i++)
    {
        //注册缩略图以获取缩略图和应用图标
        zego_windowthumbnail_register((CGWindowID)windowList[i].handle);
    }

    //释放窗口列表
    zego_screencapture_free_window_list(windowList);
    
    
    documentView.frame = NSMakeRect(0, 0, self.scrollView.frame.size.width, h);
    self.scrollView.documentView = documentView;
    
}

- (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)newFrame
{
    NSRect frame = [[NSScreen mainScreen] visibleFrame];
    return frame;
}

- (IBAction)changeLayer:(id)sender {
    if (self.window.sharingType == NSWindowSharingNone) {
        self.window.sharingType = NSWindowSharingReadOnly;
    }else{
        self.window.sharingType = NSWindowSharingNone;
    }
}

- (BOOL)isFlipped{
    return YES;
}


void window_status_change_notify(enum ZegoThumbnailWindowStatus status_code, struct ZegoThumbnailWindowInfo* window_info ,void *user_data){
    
    switch (status_code) {
        case kZegoThumbnailWindowStatusDestroy:{
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                NSAlert *alert = [[NSAlert alloc] init];
                alert.messageText = @"被关闭";
                alert.informativeText = @"停止吧";
                [alert runModal];
            });
        }
            break;
        case kZegoThumbnailWindowStatusInvalid:{
        
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                NSAlert *alert = [[NSAlert alloc] init];
                alert.messageText = @"异常";
                alert.informativeText = @"停止吧";
                [alert runModal];
            });
            
        }
            break;
        case kZegoThumbnailWindowStatusCaptureChange:{
            
            
        }
            break;
            //缩略图采集回调
        case kZegoThumbnailWindowStatusThumbnail:{
            
            NSString * str = [NSString stringWithUTF8String:(window_info->window_title)];
            NSImage * image = nil;
            NSImage * icon = nil;
            
            ZegoThumbnailIconBits *imageBits = window_info->image_bits;
            if (imageBits -> len > 0 && imageBits->bits && imageBits != NULL) {
                image = [object imageFromBRGABytes:imageBits->bits imageSize:CGSizeMake(imageBits->width, imageBits->height)];
            }
            
            ZegoThumbnailIconBits *iconBits = window_info->icon_bits;
            if(iconBits != NULL){
                if (iconBits -> len > 0 && iconBits->bits && iconBits != NULL) {
                    NSData * data = [[NSData alloc]initWithBytes:iconBits->bits length:iconBits->len];
                    icon = [[NSImage alloc]initWithData:data];
                    icon = [object imageFromBRGABytes:iconBits->bits imageSize:CGSizeMake(iconBits->width, iconBits->height)];
                }
            }
            
            ZegoNSView * view = [object.viewDic objectForKey:@(window_info->handle)];
            ZegoNSView * iconView = [object.iconViewDic objectForKey:@(window_info->handle)];
            
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                NSImageView * imageView = [[NSImageView alloc]initWithFrame:view.bounds];
                [view addSubview:imageView];
                
                imageView.image = image;
                
                NSImageView * iconImageView = [[NSImageView alloc]initWithFrame:iconView.bounds];
                [iconView addSubview:iconImageView];
                iconImageView.image = icon;
                //        zego_windowthumbnail_free_windows(window_info,1);
            });
            
            
        }
            break;
            
        default:
            break;
    }
}

void zego_screencapture_captured_window_moved_notify(ZegoWindowHandle handle, int left, int top, int width, int height, void *user_data){
    
//    [object.window setFrame:NSMakeRect(left, top, width, height) display:YES];
    [object.window setFrame:NSMakeRect(left, top, width, height) display:YES animate:YES];
    
    if(width ==0 && height == 0){
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSAlert *alert = [[NSAlert alloc] init];
            alert.messageText = @"最小化了停止吧！";
            alert.informativeText = @"最小化了停止吧";
            [alert runModal];
        });
    }
}

void zego_screencapture_captured_window_status_change_notify(enum ZegoScreenCaptureWindowStatus status_code, ZegoWindowHandle handle,struct ZegoRect rect, void *user_data)
{
    
}



- (NSImage *)imageFromBRGABytes:(unsigned char *)imageBytes imageSize:(CGSize)imageSize {
    CGImageRef imageRef = [self imageRefFromBGRABytes:imageBytes imageSize:imageSize];
    NSImage *image = [[NSImage alloc] init];

    if (imageRef) {
        NSBitmapImageRep *bitmapRep = [[NSBitmapImageRep alloc] initWithCGImage:imageRef];
        
        [image addRepresentation:bitmapRep];
        CGImageRelease(imageRef);
    }

    return image;
}

- (CGImageRef)imageRefFromBGRABytes:(unsigned char *)imageBytes imageSize:(CGSize)imageSize {
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(imageBytes,
                                                 imageSize.width,
                                                 imageSize.height,
                                                 8,
                                                 imageSize.width * 4,
                                                 colorSpace, kCGImageAlphaPremultipliedLast);
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    
    return imageRef;
}


- (NSWindowController *)layerWindow
{
    if (!_layerWindow) {
        ZegoLayerWindow * window = [[ZegoLayerWindow alloc] initWithContentRect:NSMakeRect(100, 100, 100, 100) styleMask:NSBorderlessWindowMask backing:NSBackingStoreRetained defer:NO];
//        self.window = window;
//
//        _layerWindow = [[NSWindowController alloc]initWithWindow:window];
//        _layerWindow.window.level = 1000;
//        _layerWindow.window.titleVisibility = NO;
//        [_layerWindow.window orderFront:nil];
        //        [_layerWindow.window setOpaque:NO];
        //        [_layerWindow.window setBackgroundColor:NSColor.clearColor];
        
    }
    return _layerWindow;
}

- (NSMutableArray *)dataArray {
    if (!_dataArray) {
        _dataArray = [[NSMutableArray alloc]init];
    }
    return _dataArray;
}

- (NSMutableDictionary *)viewDic
{
    if (!_viewDic) {
        _viewDic = [[NSMutableDictionary alloc]init];
    }
    return _viewDic;
    
}

- (NSMutableDictionary *)iconViewDic
{
    if (!_iconViewDic) {
        _iconViewDic = [[NSMutableDictionary alloc]init];
    }
    return _iconViewDic;
}

@end


@interface ZegoLayerWindow ()

@property (nonatomic, strong) NSView *layerView;



@end

@implementation ZegoLayerWindow


- (id)initWithContentRect:(NSRect)contentRect
                styleMask:(NSUInteger)windowStyle
                  backing:(NSBackingStoreType)bufferingType
                    defer:(BOOL)deferCreation
{
    self = [super
            initWithContentRect:contentRect
            styleMask:NSBorderlessWindowMask
            backing:bufferingType
            defer:deferCreation];
    if (self)
    {
        [self setOpaque:NO];
        [self setBackgroundColor:[NSColor clearColor]];
        
        self.titlebarAppearsTransparent=YES;
        self.titleVisibility = NSWindowTitleHidden;
        
        self.contentView.layer.backgroundColor = [NSColor redColor].CGColor;
        self.contentView.wantsLayer = YES;
        self.contentView.layer.borderWidth = 10;
        self.contentView.layer.borderColor = [NSColor redColor].CGColor;
        
        self.backgroundColor = [NSColor clearColor];
        
        [self setSharingType:NSWindowSharingNone];
    }
    return self;
}


//翻转坐标系
- (BOOL)isFlipped{
    return YES;
}




@end
