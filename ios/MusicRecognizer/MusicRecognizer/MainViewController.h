//
//  MainViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/4/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <NZAlertView.h>
#import "SearchResultViewController.h"
#import "SearchViewController.h"

@interface MainViewController : UIViewController

@property (weak, nonatomic) IBOutlet UIButton *recordButton;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (strong, nonatomic) NZAlertView *failedAlert;

- (void)notFound;

@end
