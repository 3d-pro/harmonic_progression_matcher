//
//  MainViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 12/4/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import "MainViewController.h"


@interface MainViewController ()

@end

@implementation MainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)notFound {
    self.failedAlert = [[NZAlertView alloc] initWithStyle:NZAlertStyleError
                                                    title:@"Search Not Found!"
                                                  message:@"Please try again."
                                                 delegate:nil];
    [self.failedAlert setStatusBarColor:[UIColor redColor]];
    [self.failedAlert setTextAlignment:NSTextAlignmentCenter];
    [self.failedAlert show];
}

@end
