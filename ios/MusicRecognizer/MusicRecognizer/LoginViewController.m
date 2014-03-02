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
    self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"token.json"];
    [[self.tableView headerViewForSection:0] setTintColor:[UIColor whiteColor]];
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    self.func = [[TypicalFunctions alloc] init];
}

- (void)viewWillAppear:(BOOL)animated {
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        self.tokenDict = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:self.tokenPath] options:NSJSONReadingMutableContainers error:nil];
        self.profileView.hidden = NO;
        self.loginView.hidden = YES;
        self.logoutBarButton = [[UIBarButtonItem alloc] initWithTitle:@"Logout" style:UIBarButtonItemStyleDone target:self action:@selector(logoutPressed)];
        self.navigationItem.rightBarButtonItem = self.logoutBarButton;
        self.navigationItem.title = [self.tokenDict objectForKey:@"username"];
        [self loadHistory];
    } else {
        self.profileView.hidden = YES;
        self.loginView.hidden = NO;
        self.navigationItem.title = @"Profile";
        self.navigationItem.rightBarButtonItem = nil;
        
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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)logoutPressed {
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        [[NSFileManager defaultManager] removeItemAtPath:self.tokenPath error:nil];
        [self viewWillAppear:YES];
    }
}

- (void)loadHistory {
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        AFHTTPRequestOperationManager *manager = [[AFHTTPRequestOperationManager alloc] initWithBaseURL:[NSURL URLWithString:@"http://161.246.38.80:8080"]];
        NSDictionary *parameters = @{@"username": [self.tokenDict objectForKey:@"username"]};
        [manager GET:@"/history" parameters:parameters success:^(AFHTTPRequestOperation *operation, id responseObject) {
            if ([[responseObject objectForKey:@"message"] isEqualToString:@"Query success."]) {
                self.historyArray = [responseObject objectForKey:@"history"];
                [self.tableView reloadData];
            }
        } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
            NSLog(@"Error: %@", error);
        }];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    [DejalBezelActivityView activityViewForView:self.view withLabel:@"Loading.."];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return @"Today";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        return [self.historyArray count];
    } else {
        return 1;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    if ([[self historyArray] count] == 0) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"History"];
        UIImageView *coverImageView = (UIImageView *) [cell viewWithTag:1];
        UILabel *titleLabel = (UILabel *) [cell viewWithTag:2];
        UILabel *artistLabel = (UILabel *) [cell viewWithTag:3];
        
        NSDictionary *songDict = [self.historyArray objectAtIndex:[indexPath row]];
        titleLabel.text = [songDict objectForKey:@"title"];
        artistLabel.text = [songDict objectForKey:@"artist"];
        [DejalKeyboardActivityView activityViewForView:coverImageView];
        __weak UIImageView *weakCoverImageView = coverImageView;
        NSString *image = [NSString stringWithFormat:@"http://161.246.38.80:8080/static/chordle_cover/%@ - %@.jpg",[songDict objectForKey:@"artist"],[songDict objectForKey:@"album"]];
        NSString *encodedImage = [image stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        [coverImageView setImageWithURLRequest:[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:encodedImage]] placeholderImage:nil success:^(NSURLRequest *request, NSHTTPURLResponse *response, UIImage *image){
            weakCoverImageView.image = image;
            [DejalKeyboardActivityView removeViewAnimated:YES];
        } failure:^(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error){
            NSLog(@"%@",error);
        }];
    } else {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Unused"];
    }
    return cell;
}

@end
