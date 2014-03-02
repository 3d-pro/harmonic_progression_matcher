//
//  RegisterViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AFNetworking.h>
#import <NZAlertView.h>
#import <DejalActivityView.h>
#import <BZGFormField.h>
#import <GKImagePicker.h>
#import <NZCircularImageView.h>
#import "SAMTextView.h"

@interface RegisterViewController : UIViewController <UITableViewDelegate, UITableViewDataSource, BZGFormFieldDelegate, GKImagePickerDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NZCircularImageView *profileImageView;
@property (strong, nonatomic) BZGFormField *usernameField, *passwordField;
@property (strong, nonatomic) SAMTextView *bioTextView;
@property (strong, nonatomic) GKImagePicker *imagePicker;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableDictionary *tokenDict;

- (IBAction)backPressed:(id)sender;
- (IBAction)registerPressed:(id)sender;
- (IBAction)imagePickerPressed:(id)sender;

@end
