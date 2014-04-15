//
//  HistoryViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import "HistoryViewController.h"

@interface HistoryViewController ()

@end

@implementation HistoryViewController

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
    //[self.tableView setBackgroundView:nil];
    //[self.tableView setBackgroundColor:[self.func colorWithHexString:@"55a4cc"]];
    [[self.tableView headerViewForSection:0] setTintColor:[UIColor whiteColor]];
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"token.json"];
	// Do any additional setup after loading the view.
}

- (void)viewWillAppear:(BOOL)animated {
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        self.tokenDict = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:self.tokenPath] options:NSJSONReadingMutableContainers error:nil];
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
    } else {
        [self.tableView reloadData];
    }
}

- (void)viewDidAppear:(BOOL)animated {
    [self.tableView reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return @"All";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        if ([self.historyArray count] != 0) {
            return [self.historyArray count];
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
        if ([self.historyArray count] != 0) {
            cell = [tableView dequeueReusableCellWithIdentifier:@"History"];
            UIImageView *coverImageView = (UIImageView *) [cell viewWithTag:1];
            UILabel *titleLabel = (UILabel *) [cell viewWithTag:2];
            UILabel *artistLabel = (UILabel *) [cell viewWithTag:3];
            
            NSDictionary *songDict = [self.historyArray objectAtIndex:[indexPath row]];
            titleLabel.text = [songDict objectForKey:@"title"];
            artistLabel.text = [songDict objectForKey:@"artist"];
            if (![[songDict objectForKey:@"album"] isEqualToString:@"-"]) {
                [DejalKeyboardActivityView activityViewForView:coverImageView];
                __weak UIImageView *weakCoverImageView = coverImageView;
                NSString *image = [NSString stringWithFormat:@"http://161.246.38.80:8080/static/chordle_cover/%@ - %@.jpg",[songDict objectForKey:@"artist"],[songDict objectForKey:@"album"]];
                NSString *encodedImage = [image stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                [coverImageView setImageWithURLRequest:[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:encodedImage]] placeholderImage:nil success:^(NSURLRequest *request, NSHTTPURLResponse *response, UIImage *image){
                    weakCoverImageView.image = image;
                    [DejalKeyboardActivityView removeViewAnimated:YES];
                } failure:^(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error){
                    weakCoverImageView.image = [UIImage imageNamed:@"album_placeholder.png"];
                    NSLog(@"%@",error);
                }];
            }
        } else {
            cell = [tableView dequeueReusableCellWithIdentifier:@"No History"];
        }
    } else {
        cell = [tableView dequeueReusableCellWithIdentifier:@"Not Login"];
    }
    return cell;
}

@end
