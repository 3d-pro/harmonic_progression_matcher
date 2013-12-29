//
//  MainViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/4/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import "MicrophoneInput.h"
#import "AFNetworking.h"

@interface MainViewController : UIViewController <MPMediaPickerControllerDelegate>

@property (weak, nonatomic) IBOutlet UILabel *metaLabel;
@property (weak, nonatomic) IBOutlet UILabel *albumLabel;
@property (strong, nonatomic) IBOutlet UIButton *recognizerButton;
@property (strong, nonatomic) MicrophoneInput *recorder;
@property (strong, nonatomic) NSDictionary *JSON;
@property const char *fpCode;
@property BOOL recording;

@end
