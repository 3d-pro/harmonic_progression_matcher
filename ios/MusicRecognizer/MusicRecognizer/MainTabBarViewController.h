//
//  MainTabBarViewController.h
//  TestUI
//
//  Created by Chainseika on 12/23/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LoginViewController.h"
#import "ProfileViewController.h"
#import "ProfileNavViewController.h"
#import <CEFoldAnimationController.h>
#import <CEFlipAnimationController.h>

@interface MainTabBarViewController : UITabBarController <UITabBarControllerDelegate>

@property (strong, nonatomic) LoginViewController *loginController;
@property (strong, nonatomic) ProfileViewController *profileController;
@property (strong, nonatomic) ProfileNavViewController *profileNavViewController;
@property (strong, nonatomic) NSString *tokenPath;
@end
