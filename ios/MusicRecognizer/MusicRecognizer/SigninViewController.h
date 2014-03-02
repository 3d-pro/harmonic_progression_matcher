//
//  SigninViewController.h
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BZGFormField.h>
#import <DejalActivityView.h>
#import <NZAlertView.h>
#import <AFNetworking.h>

@interface SigninViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, BZGFormFieldDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) BZGFormField *usernameField, *passwordField;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableDictionary *tokenDict;

- (IBAction)backPressed:(id)sender;
- (IBAction)signinPressed:(id)sender;

@end
