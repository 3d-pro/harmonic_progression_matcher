//
//  SigninViewController.h
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AFNetworking.h"

@interface SigninViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableArray *tokenDict;

- (IBAction)backPressed:(id)sender;
- (IBAction)signinPressed:(id)sender;

@end
