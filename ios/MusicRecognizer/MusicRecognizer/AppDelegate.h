//
//  AppDelegate.h
//  MusicRecognizer
//
//  Created by Kittipun on 11/11/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TypicalFunctions.h"
#import "LoginViewController.h"
#import "ProfileNavViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UIStoryboard *storyboard;
@property (strong, nonatomic) LoginViewController *loginController;
@property (strong, nonatomic) ProfileNavViewController *profileNavViewController;
@property (strong, nonatomic) TypicalFunctions *func;
@property (strong, nonatomic) NSString *tokenPath;

@end
