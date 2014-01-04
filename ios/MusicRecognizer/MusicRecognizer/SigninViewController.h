//
//  SigninViewController.h
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AFNetworking.h"

@interface SigninViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) UITextField *usernameTextField, *passwordTextField;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableArray *tokenDict;

- (IBAction)backPressed:(id)sender;
- (IBAction)signinPressed:(id)sender;

@end
