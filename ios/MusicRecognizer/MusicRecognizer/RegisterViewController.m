//
//  RegisterViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import "RegisterViewController.h"

@interface RegisterViewController ()

@end

@implementation RegisterViewController

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
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    self.imagePicker = [[GKImagePicker alloc] init];
    self.imagePicker.delegate = self;
    self.imagePicker.cropSize = CGSizeMake(116.,116.);
	// Do any additional setup after loading the view.
}

-(void)viewWillAppear:(BOOL)animated {
    self.tokenDict = [[NSMutableDictionary alloc] init];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    return [textField resignFirstResponder];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 3;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([indexPath row] == 2) {
        return 125;
    } else {
        return 43;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    if ([indexPath row] == 0) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Username"];
        self.usernameField = (BZGFormField *) [cell viewWithTag:6];
        self.usernameField.textField.placeholder = @"Username";
        self.usernameField.delegate = self;
        [self.usernameField.textField becomeFirstResponder];
        [self.usernameField setTextValidationBlock:^BOOL(NSString *text) {
            if (text.length < 5) {
                self.usernameField.alertView.title = @"Username is too short";
                return NO;
            } else {
                return YES;
            }
        }];
    } else if ([indexPath row] == 1) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Password"];
        self.passwordField = (BZGFormField *) [cell viewWithTag:7];
        self.passwordField.textField.placeholder = @"Password";
        self.passwordField.textField.secureTextEntry = YES;
        self.passwordField.delegate = self;
        [self.passwordField setTextValidationBlock:^BOOL(NSString *text) {
            if (text.length < 8) {
                self.passwordField.alertView.title = @"Password is too short";
                return NO;
            } else {
                return YES;
            }
        }];
    } else if ([indexPath row] == 2) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Bio"];
        self.bioTextView = (SAMTextView *) [cell viewWithTag:8];
        self.bioTextView.placeholder = @"Describe Yourself Here";
        self.profileImageView = (NZCircularImageView *) [cell viewWithTag:9];
    }
    return cell;
}

- (IBAction)backPressed:(id)sender {
    [self dismissViewControllerAnimated:YES completion:^{[DejalBezelActivityView removeViewAnimated:YES];}];
}

- (IBAction)registerPressed:(id)sender {
    [DejalBezelActivityView activityViewForView:self.view withLabel:@"Loading.."];
    AFHTTPRequestOperationManager *manager = [[AFHTTPRequestOperationManager alloc] initWithBaseURL:[NSURL URLWithString:@"http://161.246.38.80:8080"]];
    NSDictionary *parameters = @{@"username": self.usernameField.textField.text, @"password": self.passwordField.textField.text, @"bio":self.bioTextView.text};
    NSData *imageData = UIImageJPEGRepresentation([self.profileImageView image], 0.7);
    [manager POST:@"/register" parameters:parameters constructingBodyWithBlock:^(id<AFMultipartFormData> formData) {
            [formData appendPartWithFileData:imageData name:@"files" fileName:self.usernameField.textField.text mimeType:@"image/jpeg"];
        } success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"JSON: %@", responseObject);
        if ([[responseObject objectForKey:@"message"] isEqualToString:@"Register success."]) {
            //create session path
            self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"token.json"];
            
            //check for token file
            if (![[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath])
                [[NSFileManager defaultManager] createFileAtPath:self.tokenPath contents:nil attributes:nil];
            
            //create json dict for token file
            [self.tokenDict setValue:self.usernameField.textField.text forKey:@"username"];
            [self.tokenDict setValue:[responseObject objectForKey:@"token"] forKey:@"token"];
            
            //json output
            NSOutputStream *jsonOutput = [[NSOutputStream alloc] initToFileAtPath:self.tokenPath append:NO];
            [jsonOutput open];
            NSInteger bytesWritten = [NSJSONSerialization writeJSONObject:self.tokenDict toStream:jsonOutput options:NSJSONWritingPrettyPrinted error:nil];
            [jsonOutput close];
            if (bytesWritten <= 0) {
                NSLog(@"ERROR!");
            }
            [self dismissViewControllerAnimated:YES completion:^{[DejalBezelActivityView removeViewAnimated:YES];}];
            
        } else {
            NZAlertView *failedAlert = [[NZAlertView alloc] initWithStyle:NZAlertStyleError
                                                                    title:@"Register Failed"                                                                   message:@"Something not right. Please recheck all the info and try again."
                                                                 delegate:nil];
            [failedAlert setStatusBarColor:[UIColor redColor]];
            [failedAlert setTextAlignment:NSTextAlignmentCenter];
            [failedAlert show];
            [DejalBezelActivityView removeViewAnimated:YES];
        }
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", error);
        NZAlertView *errorAlert = [[NZAlertView alloc] initWithStyle:NZAlertStyleError
                                                               title:@"Register Error"
                                                             message:@"There was a problem connecting to the network!"
                                                            delegate:nil];
        [errorAlert setStatusBarColor:[UIColor redColor]];
        [errorAlert setTextAlignment:NSTextAlignmentCenter];
        [errorAlert show];
        [DejalBezelActivityView removeViewAnimated:YES];
    }];
}

- (IBAction)imagePickerPressed:(id)sender {
    [self.imagePicker showActionSheetOnViewController:self onPopoverFromView:self.view];
}

- (void)imagePicker:(GKImagePicker *)imagePicker pickedImage:(UIImage *)image {
    [self.profileImageView setImage:image];
}


@end
