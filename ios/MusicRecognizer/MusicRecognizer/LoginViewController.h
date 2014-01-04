//
//  LoginViewController.h
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TypicalFunctions.h"

@interface LoginViewController : UIViewController

@property (weak, nonatomic) IBOutlet UIButton *signinButton;
@property (weak, nonatomic) IBOutlet UIButton *registerButton;
@property (strong, nonatomic) TypicalFunctions *func;

@end
