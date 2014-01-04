//
//  RegisterViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AFNetworking.h>

@interface RegisterViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;
@property (weak, nonatomic) IBOutlet UITextView *bioTextView;
@property (strong, nonatomic) NSString *tokenPath;

- (IBAction)backPressed:(id)sender;
- (IBAction)registerPressed:(id)sender;

@end
