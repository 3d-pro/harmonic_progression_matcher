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
    [self.signinButton setBackgroundImage:[UIImage imageNamed:@"buttonbox.png"] forState:UIControlStateNormal];
    [self.signinButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    [self.signinButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"]  forState:UIControlStateHighlighted];
    [self.signinButton setTitleColor:[self colorWithHexString:@"0093d8"] forState:UIControlStateHighlighted];
    

    [self.signinButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"] forState:UIControlStateSelected];
    [self.signinButton setTitleColor:[self colorWithHexString:@"0093d8"] forState:UIControlStateSelected];
    
    
    
    
    
    [self.registerButton setBackgroundImage:[UIImage imageNamed:@"buttonbox.png"] forState:UIControlStateNormal];
    [self.signinButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    [self.registerButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"]  forState:UIControlStateHighlighted];
    [self.registerButton setTitleColor:[self colorWithHexString:@"0093d8"] forState:UIControlStateHighlighted];
    
    
    [self.registerButton setBackgroundImage:[UIImage imageNamed:@"buttonbox_selected.png"] forState:UIControlStateSelected];
    [self.registerButton setTitleColor:[self colorWithHexString:@"0093d8"] forState:UIControlStateSelected];
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(UIColor*)colorWithHexString:(NSString*)hex
{
    NSString *cString = [[hex stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    
    // String should be 6 or 8 characters
    if ([cString length] < 6) return [UIColor grayColor];
    
    // strip 0X if it appears
    if ([cString hasPrefix:@"0X"]) cString = [cString substringFromIndex:2];
    
    if ([cString length] != 6) return  [UIColor grayColor];
    
    // Separate into r, g, b substrings
    NSRange range;
    range.location = 0;
    range.length = 2;
    NSString *rString = [cString substringWithRange:range];
    
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f)
                           green:((float) g / 255.0f)
                            blue:((float) b / 255.0f)
                           alpha:1.0f];
}

@end
