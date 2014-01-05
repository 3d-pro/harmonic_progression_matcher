//
//  SigninViewController.m
//  TestUI
//
//  Created by Chainseika on 12/29/2556 BE.
//  Copyright (c) 2556 Chainseika. All rights reserved.
//

#import "SigninViewController.h"

@interface SigninViewController ()

@end

@implementation SigninViewController

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
	// Do any additional setup after loading the view.
}

- (void)viewWillAppear:(BOOL)animated {
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
    return 2;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    if ([indexPath row] == 0) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Username"];
        self.usernameField = (BZGFormField *) [cell viewWithTag:4];
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
        self.passwordField = (BZGFormField *) [cell viewWithTag:5];
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
    }
    return cell;
}

- (IBAction)backPressed:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)signinPressed:(id)sender {
    AFHTTPRequestOperationManager *manager = [[AFHTTPRequestOperationManager alloc] initWithBaseURL:[NSURL URLWithString:@"http://161.246.38.80:8080"]];
    NSDictionary *parameters = @{@"username": self.usernameField.textField.text, @"password": self.passwordField.textField.text};
    [manager POST:@"/login" parameters:parameters success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"JSON: %@", responseObject);
        if ([[responseObject objectForKey:@"message"] isEqualToString:@"Login success."]) {
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
            [self dismissViewControllerAnimated:YES completion:nil];
        } else {
            
        }
        
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", error);
    }];
}
@end
