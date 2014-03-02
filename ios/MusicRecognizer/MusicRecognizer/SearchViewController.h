//
//  SearchViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 2/19/14.
//  Copyright (c) 2014 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AFNetworking.h>
#import <SFRoundProgressCounterView.h>
#import <DejalActivityView.h>
#import <NZAlertView.h>
#import "MicrophoneInput.h"
#import "TypicalFunctions.h"
#import "SearchResultViewController.h"
#import "MainViewController.h"

@interface SearchViewController : UIViewController  <MPMediaPickerControllerDelegate, SFRoundProgressCounterViewDelegate, UIAlertViewDelegate>
@property (strong, nonatomic) IBOutlet SFRoundProgressCounterView *timeCounter;
@property (strong, nonatomic) MicrophoneInput *recorder;
@property (strong, nonatomic) NSDictionary *JSON, *metadata;
@property (strong, nonatomic) NSMutableDictionary *searchResultDict, *tokenDict;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) TypicalFunctions *func;

- (IBAction)cancelPressed:(UIBarButtonItem *)sender;

@end
