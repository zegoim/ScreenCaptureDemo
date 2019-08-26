//
//  ZegoAVKitManager.m
//  LiveDemo5OSX
//
//  Created by Strong on 2017/4/20.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"

NSString *kZegoDemoAppTypeKey       = @"apptype";
NSString *kZegoDemoAppIDKey         = @"appid";
NSString *kZegoDemoAppSignKey       = @"appsign";

@interface ZegoAVKitManager ()

@property (nonatomic, strong) ZegoLiveRoomApi *zegoApi;
@property (nonatomic, assign) unsigned int customAppID;
@property (nonatomic, strong) NSData *customAppKey;

@end

@implementation ZegoAVKitManager

+ (instancetype)shareInstance
{
    static dispatch_once_t onceToken;
    static ZegoAVKitManager *manager;
    dispatch_once(&onceToken, ^{
        manager = [[ZegoAVKitManager alloc] init];
    });
    
    return manager;
}

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        [self getDefaultAppType];
    }
    
    return self;
}

- (ZegoLiveRoomApi *)roomApi
{
    if (self.zegoApi == nil)
    {
        [ZegoLiveRoomApi setUseTestEnv:NO];
        [ZegoLiveRoomApi setBusinessType:0];
        [ZegoLiveRoomApi setUserID:[ZegoSettings defaultSetting].userID userName:[ZegoSettings defaultSetting].userName];
        
        if (self.captureFactory == nil)
            _captureFactory = [[ZegoVideoCaptureScreenFactory alloc] init];
        
        [ZegoLiveRoomApi setVideoCaptureFactory:self.captureFactory];
        
        _zegoApi = [[ZegoLiveRoomApi alloc] initWithAppID:[self appID] appSignature:[self zegoAppSignFromServer]];
        
        //        [self userDefaultDevice];
        [ZegoLiveRoomApi requireHardwareDecoder:YES];
        [ZegoLiveRoomApi requireHardwareEncoder:YES];
    }
    
    return self.zegoApi;
}

- (void)releaseLiveRoom
{
    self.zegoApi = nil;
}

- (void)setCaptureSource:(CaptureSource)source
{
    if (self.captureFactory == nil)
        _captureFactory = [[ZegoVideoCaptureScreenFactory alloc] init];
    
    self.captureFactory.source = source;
}

- (unsigned int)appID
{
    switch (self.appType)
    {
        case ZegoAppTypeCustom:  // 自定义
        {
            NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
            uint32_t appID = [[ud objectForKey:kZegoDemoAppIDKey] unsignedIntValue];
            
            if (appID != 0) {
                return appID;
            } else {
                return 0;
            }
        }
            break;
        case ZegoAppTypeUDP:
            return 1739272706;  // 国内版
            break;
        case ZegoAppTypeI18N:
            return 3322882036;  // 国际版
            break;
    }
}

- (void)setCustomAppID:(unsigned int)appID appSign:(NSString *)appSign
{
    NSData *data = [self convertStringToSign:appSign];
    if (data.length == 32 && appID != 0)
    {
        self.appType = ZegoAppTypeCustom;
        
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud setObject:@(appID) forKey:kZegoDemoAppIDKey];
        [ud setObject:appSign forKey:kZegoDemoAppSignKey];
        
        [self releaseLiveRoom];
    }
}

- (ZegoAppType)getDefaultAppType {
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSUInteger type = [ud integerForKey:kZegoDemoAppTypeKey];
    if (type == 0) {
        _appType = ZegoAppTypeUDP;
    } else {
        _appType = (ZegoAppType)type;
    }
    return _appType;
}

- (void)setAppType:(ZegoAppType)appType
{
    if (_appType == appType)
        return;
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setInteger:appType forKey:kZegoDemoAppTypeKey];
    
    _appType = appType;
    
    [self releaseLiveRoom];
    
    if ([self roomApi] == nil)
        [self roomApi];
}

- (NSString *)appSign
{
    NSData *data = [self zegoAppSignFromServer];
    if (data == nil)
        return @"";
    
    NSMutableString *strAppSign = [NSMutableString stringWithCapacity:data.length * 2];
    const unsigned char *buffer = (const unsigned char *)data.bytes;
    for (int i = 0; i < data.length; i++)
        [strAppSign appendFormat:@"0x%02X, ", buffer[i]];
    
    [strAppSign deleteCharactersInRange:NSMakeRange(strAppSign.length - 2, 1)];
    
    return strAppSign;
}

-(Byte)toByte:(NSString*)c
{
    NSString *str = @"0123456789abcdef";
    Byte b = [str rangeOfString:c].location;
    return b;
}

- (NSData *)convertStringToSign:(NSString *)strSign
{
    if(strSign == nil || strSign.length == 0)
        return nil;
    strSign = [strSign lowercaseString];
    strSign = [strSign stringByReplacingOccurrencesOfString:@" " withString:@""];
    strSign = [strSign stringByReplacingOccurrencesOfString:@"0x" withString:@""];
    NSArray* szStr = [strSign componentsSeparatedByString:@","];
    int nLen = (int)[szStr count];
    Byte szSign[32];
    for(int i = 0; i < nLen; i++)
    {
        NSString *strTmp = [szStr objectAtIndex:i];
        if(strTmp.length == 1)
            szSign[i] = [self toByte:strTmp];
        else
        {
            szSign[i] = [self toByte: [strTmp substringWithRange:NSMakeRange(0, 1)]] << 4 | [self toByte:[strTmp substringWithRange:NSMakeRange(1, 1)]];
        }
        
        NSLog(@"%x,", szSign[i]);
    }
    
    NSData *sign = [NSData dataWithBytes:szSign length:32];
    return sign;
}

- (NSData *)zegoAppSignFromServer
{
    ZegoAppType type = self.appType;
    
    if (type == ZegoAppTypeUDP)
    {
        Byte signkey[] = {0x1e,0xc3,0xf8,0x5c,0xb2 ,0xf2,0x13,0x70,0x26,0x4e,0xb3,0x71,0xc8,0xc6,0x5c,0xa3,0x7f,0xa3,0x3b,0x9d,0xef,0xef,0x2a,0x85,0xe0,0xc8,0x99,0xae,0x82,0xc0,0xf6,0xf8};
        return [NSData dataWithBytes:signkey length:32];
    }
    else if (type == ZegoAppTypeI18N)
    {
        Byte signkey[] = {0x5d,0xe6,0x83,0xac,0xa4,0xe5,0xad,0x43,0xe5,0xea,0xe3,0x70,0x6b,0xe0,0x77,0xa4,0x18,0x79,0x38,0x31,0x2e,0xcc,0x17,0x19,0x32,0xd2,0xfe,0x22,0x5b,0x6b,0x2b,0x2f};
        return [NSData dataWithBytes:signkey length:32];
    }
    else
    {
        // 自定义模式下从本地持久化文件中加载
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        NSString *appSign = [ud objectForKey:kZegoDemoAppSignKey];
        if (appSign)
        {
            return [self convertStringToSign:appSign];
        }
        else
        {
            return nil;
        }
    }
}

- (void)setTestEnvironment:(BOOL)testEnvironment
{
    if (self.testEnvironment != testEnvironment)
    {
        [self releaseLiveRoom];
        
        _testEnvironment = testEnvironment;
    }
}

- (NSString *)getPublishStreamID
{
    NSString *userID = [ZegoSettings defaultSetting].userID;
    unsigned long currentTime = (unsigned long)[[NSDate date] timeIntervalSince1970];
    return [NSString stringWithFormat:@"s-%@-%lu", userID, currentTime];
}

- (void)userDefaultDevice
{
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *device in devices)
    {
        if ([device.manufacturer isEqualToString:@"Apple Inc."])
        {
            [ZegoLiveRoomApi setVideoDevice:device.uniqueID];
            break;
        }
    }
}

- (BOOL)isWereWolfRoom:(NSString *)roomID
{
    if ([roomID hasPrefix:@"#i-"] || [roomID hasPrefix:@"#w-"])
        return YES;
    
    return NO;
}

- (BOOL)isSingleRoom:(NSString *)roomID
{
    if ([roomID hasPrefix:@"#d-"])
        return YES;
    
    return NO;
}

@end

