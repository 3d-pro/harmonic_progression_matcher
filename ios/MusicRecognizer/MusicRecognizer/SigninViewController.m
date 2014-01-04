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
    self.tokenDict = [[NSMutableArray alloc] init];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
        self.usernameTextField = (UITextField *) [cell viewWithTag:4];
    } else if ([indexPath row] == 1) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Password"];
        self.passwordTextField = (UITextField *) [cell viewWithTag:5];
    }
    return cell;
}

- (IBAction)backPressed:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)signinPressed:(id)sender {
    AFHTTPRequestOperationManager *manager = [[AFHTTPRequestOperationManager alloc] initWithBaseURL:[NSURL URLWithString:@"http://161.246.38.80:8080"]];
    NSDictionary *parameters = @{@"username": self.usernameTextField.text, @"password": self.passwordTextField.text};
    [manager POST:@"/login" parameters:parameters success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"JSON: %@", responseObject);
        //create session path
        self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"token.json"];
        
        //check for token file
        if (![[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath])
            [[NSFileManager defaultManager] createFileAtPath:self.tokenPath contents:nil attributes:nil];
        
        //create json dict for token file
        [self.tokenDict setValue:self.usernameTextField.text forKey:@"username"];
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
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", error);
    }];
    
}
@end
