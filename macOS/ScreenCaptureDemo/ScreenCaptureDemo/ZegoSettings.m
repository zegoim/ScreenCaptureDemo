//
//  ZegoSettings.m
//  LiveDemo5OSX
//
//  Created by Strong on 2017/4/21.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import "ZegoSettings.h"

NSString *kZegoDemoUserIDKey            = @"userId";
NSString *kZegoDemoUserNameKey          = @"userName";
NSString *kZegoDemoVideoPresetKey       = @"preset";
NSString *kZegoDemoVideoWitdhKey        = @"resolution-width";
NSString *kZegoDemoVideoHeightKey       = @"resolution-height";
NSString *kZegoDemoVideoFrameRateKey    = @"framerate";
NSString *kZegoDemoVideoBitRateKey      = @"bitrate";

@implementation ZegoSettings
{
    NSString *_userID;
    NSString *_userName;
    ZegoLiveQuality _quality;
    
}

+ (instancetype)defaultSetting
{
    static ZegoSettings *settings = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        settings = [[ZegoSettings alloc] init];
    });
    
    return settings;
}

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        _currentConfig = [ZegoAVConfig new];
        
        [self loadConfig];
    }
    
    return self;
}

#pragma mark UserID & UserName
- (NSString *)userID
{
    if (_userID.length == 0)
    {
        NSString *defaultUserID = [[NSUserDefaults standardUserDefaults] stringForKey:kZegoDemoUserIDKey];
        if (defaultUserID.length != 0)
            _userID = defaultUserID;
        else
        {
            srand((unsigned)time(0));
            _userID = [NSString stringWithFormat:@"%u", (unsigned)rand()];
            [[NSUserDefaults standardUserDefaults] setObject:_userID forKey:kZegoDemoUserIDKey];
        }
    }
    
    return _userID;
}

- (void)setUserID:(NSString *)userID
{
    if ([userID isEqualToString:_userID])
        return;
    
    if (userID.length != 0)
    {
        _userID = userID;
        
        [[NSUserDefaults standardUserDefaults] setObject:_userID forKey:kZegoDemoUserIDKey];
        [[ZegoAVKitManager shareInstance] releaseLiveRoom];
    }
}

- (NSString *)userName
{
    if (_userName.length == 0)
    {
        NSString *defaultUserID = [[NSUserDefaults standardUserDefaults] stringForKey:kZegoDemoUserNameKey];
        if (defaultUserID.length != 0)
            _userName = defaultUserID;
        else
        {
            srand((unsigned)time(0));
            _userName = [NSString stringWithFormat:@"osx_%u", (unsigned)rand()];
            [[NSUserDefaults standardUserDefaults] setObject:_userName forKey:kZegoDemoUserNameKey];
        }
    }
    
    return _userName;
}

- (void)setUserName:(NSString *)userName
{
    if ([userName isEqualToString:_userName])
        return;
    
    if (userName.length != 0)
    {
        _userName = userName;
        
        [[NSUserDefaults standardUserDefaults] setObject:_userName forKey:kZegoDemoUserNameKey];
        [[ZegoAVKitManager shareInstance] releaseLiveRoom];
    }
}

- (void)setQuality:(ZegoLiveQuality)quality
{
    _quality = quality;
    
    if (quality == kLiveQualityVeryLow)
    {
        _currentConfig.fps = 10;
        _currentConfig.bitrate = 400 * 1000;
        _currentConfig.videoEncodeResolution = CGSizeMake(320, 240);
        _currentConfig.videoCaptureResolution = _currentConfig.videoEncodeResolution;
    }
    else if (quality == kLiveQualityLow)
    {
        _currentConfig.fps = 10;
        _currentConfig.bitrate = 600 * 1000;
        _currentConfig.videoEncodeResolution = CGSizeMake(352, 288);
        _currentConfig.videoCaptureResolution = _currentConfig.videoEncodeResolution;
    }
    else if (quality == kLiveQualityGeneric)
    {
        _currentConfig.fps = 15;
        _currentConfig.bitrate = 800 * 1000;
        _currentConfig.videoEncodeResolution = CGSizeMake(640, 360);
        _currentConfig.videoCaptureResolution = _currentConfig.videoEncodeResolution;
    }
    else if (quality == kLiveQualityHigh)
    {
        _currentConfig.fps = 20;
        _currentConfig.bitrate = 1200 * 1000;
        _currentConfig.videoEncodeResolution = CGSizeMake(1280, 720);
        _currentConfig.videoCaptureResolution = _currentConfig.videoEncodeResolution;
    }
    else if (quality == kLiveQualityVeryHigh)
    {
        _currentConfig.fps = 25;
        _currentConfig.bitrate = 2000 * 1000;
        _currentConfig.videoEncodeResolution = CGSizeMake(1920, 1080);
        _currentConfig.videoCaptureResolution = _currentConfig.videoEncodeResolution;
    }
    else if (quality == kLiveQualityCustom)
    {
        
    }
    [self saveConfig];
}

- (void)saveConfig
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@(_quality) forKey:kZegoDemoVideoPresetKey];
    
    [ud setInteger:_currentConfig.videoEncodeResolution.width forKey:kZegoDemoVideoWitdhKey];
    [ud setInteger:_currentConfig.videoEncodeResolution.height forKey:kZegoDemoVideoHeightKey];
    [ud setObject:@([_currentConfig fps]) forKey:kZegoDemoVideoFrameRateKey];
    [ud setObject:@([_currentConfig bitrate]) forKey:kZegoDemoVideoBitRateKey];
}

- (void)loadConfig
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    id quality = [ud objectForKey:kZegoDemoVideoPresetKey];
    if (quality)
    {
        _quality = (ZegoLiveQuality)[quality integerValue];
        NSInteger vWidth = [ud integerForKey:kZegoDemoVideoWitdhKey];
        NSInteger vHeight = [ud integerForKey:kZegoDemoVideoHeightKey];
        
        if (vWidth && vHeight)
        {
            CGSize r = CGSizeMake(vWidth, vHeight);
            _currentConfig.videoEncodeResolution = r;
            _currentConfig.videoCaptureResolution = r;
        }
        else
        {
            self.quality = kLiveQualityGeneric;
            return;
        }
        
        id frameRate = [ud objectForKey:kZegoDemoVideoFrameRateKey];
        if (frameRate)
        {
            _currentConfig.fps = (int)[frameRate integerValue];
        }
        else
        {
            self.quality = kLiveQualityGeneric;
            return;
        }
        
        id bitRate = [ud objectForKey:kZegoDemoVideoBitRateKey];
        if (bitRate)
        {
            _currentConfig.bitrate = (int)[bitRate integerValue];
        }
        else
        {
            self.quality = kLiveQualityGeneric;
            return;
        }
    }
    else
    {
        self.quality = kLiveQualityGeneric;
    }
}

@end

