//
//  MainTabBarViewController.m
//  TestUI
//
//  Created by Chainseika on 12/23/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import "MainTabBarViewController.h"

@interface MainTabBarViewController ()

@end

@implementation MainTabBarViewController

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
    if (![[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)objectAtIndex:0]stringByAppendingPathComponent:@"token.json"];
    }
    
	// Do any additional setup after loading the view.
}

//- (void)viewWillAppear:(BOOL)animated {
//    //init nav controller.
//    self.profileNavViewController = [self.childViewControllers objectAtIndex:2];
//    
//    //check login status by using token file.
//    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
//        self.profileController = [self.storyboard instantiateViewControllerWithIdentifier:@"Profile"];
//        [self.profileNavViewController setViewControllers:@[self.profileController] animated:YES];
//        
//    } else {
//        self.loginController = [self.storyboard instantiateViewControllerWithIdentifier:@"Login"];
//        [self.profileNavViewController setViewControllers:@[self.loginController] animated:YES];
//    }
//}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
