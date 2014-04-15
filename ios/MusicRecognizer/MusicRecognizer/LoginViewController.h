//
//  LoginViewController.h
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DejalActivityView.h>
#import <AFNetworking.h>
#import <AFNetworking/UIImageView+AFNetworking.h>
#import <NZCircularImageView.h>
#import "TypicalFunctions.h"

@interface LoginViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UIButton *signinButton;
@property (weak, nonatomic) IBOutlet UIButton *registerButton;
@property (strong, nonatomic) IBOutlet UIView *profileView;
@property (strong, nonatomic) IBOutlet UIView *loginView;
@property (strong, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) IBOutlet NZCircularImageView *profileImageView;
@property (strong, nonatomic) IBOutlet UITextView *bioTextView;
@property (strong, nonatomic) UIBarButtonItem *logoutBarButton;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableArray *historyArray;
@property (strong, nonatomic) NSMutableDictionary *tokenDict;
@property (strong, nonatomic) TypicalFunctions *func;

- (void)loadHistory;

@end
