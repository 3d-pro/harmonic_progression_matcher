//
//  LoginViewController.m
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import "LoginViewController.h"

@interface LoginViewController ()

@end

@implementation LoginViewController

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
    
    self.func = [[TypicalFunctions alloc] init];
    
    [self.signinButton setBackgroundImage:[UIImage imageNamed:@"buttonbox.png"] forState:UIControlStateNormal];
    [self.signinButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    [self.signinButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"]  forState:UIControlStateHighlighted];
    [self.signinButton setTitleColor:[self.func colorWithHexString:@"0093d8"] forState:UIControlStateHighlighted];
    

    [self.signinButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"] forState:UIControlStateSelected];
    [self.signinButton setTitleColor:[self.func colorWithHexString:@"0093d8"] forState:UIControlStateSelected];
    
    
    [self.registerButton setBackgroundImage:[UIImage imageNamed:@"buttonbox.png"] forState:UIControlStateNormal];
    [self.signinButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    [self.registerButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"]  forState:UIControlStateHighlighted];
    [self.registerButton setTitleColor:[self.func colorWithHexString:@"0093d8"] forState:UIControlStateHighlighted];
    
    
    [self.registerButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"] forState:UIControlStateSelected];
    [self.registerButton setTitleColor:[self.func colorWithHexString:@"0093d8"] forState:UIControlStateSelected];
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
