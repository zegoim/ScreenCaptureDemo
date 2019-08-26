//
//  ViewController.h
//  ScreenCaptureDemo
//
//  Created by 李展鹏 on 2018/3/31.
//  Copyright © 2018年 Zego. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController

@property (weak) IBOutlet NSButton *m_radioButtonScreen;

@property (weak) IBOutlet NSButton *m_radioButtonWindow;

@property (weak) IBOutlet NSButton *m_radioButtonScreenRect;

@property (weak) IBOutlet NSSlider *m_sliderFPS;

@property (weak) IBOutlet NSTextField *m_lbFPS;

@property (weak) IBOutlet NSButton *m_bStartCapture;

@property (weak) IBOutlet NSButton *m_bStartPublish;

@property (weak) IBOutlet NSComboBox *m_cbScreenList;

@property (weak) IBOutlet NSComboBox *m_cbWindowList;

@property (weak) IBOutlet NSTextField *m_edRtmp;

@property (weak) IBOutlet NSButton *m_bCursorCapture;

@property (weak) IBOutlet NSButton *m_bMouseAnimation;

@end

