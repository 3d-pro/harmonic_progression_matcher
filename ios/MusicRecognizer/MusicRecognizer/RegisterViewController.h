//
//  RegisterViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AFNetworking.h>
#import <BZGFormField.h>
#import "SAMTextView.h"

@interface RegisterViewController : UIViewController <UITableViewDelegate, UITableViewDataSource, BZGFormFieldDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) BZGFormField *usernameField, *passwordField;
@property (strong, nonatomic) SAMTextView *bioTextView;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableDictionary *tokenDict;

- (IBAction)backPressed:(id)sender;
- (IBAction)registerPressed:(id)sender;

@end
