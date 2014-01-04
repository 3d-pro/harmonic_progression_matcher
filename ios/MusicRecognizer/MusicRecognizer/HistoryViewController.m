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
    self.func = [[TypicalFunctions alloc] init];
    //[self.tableView setBackgroundView:nil];
    //[self.tableView setBackgroundColor:[self.func colorWithHexString:@"55a4cc"]];
    [[self.tableView headerViewForSection:0] setTintColor:[UIColor whiteColor]];
	// Do any additional setup after loading the view.
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
    return @"Today";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 2;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"History"];
    UIImageView *coverImageView = (UIImageView *) [cell viewWithTag:1];
    UILabel *titleLabel = (UILabel *) [cell viewWithTag:2];
    UILabel *artistLabel = (UILabel *) [cell viewWithTag:3];
    if ([indexPath row] == 0) {
        titleLabel.text = @"ของขวัญ";
        artistLabel.text = @"Musketeers";
        coverImageView.image = [UIImage imageNamed:@"cover_art_test.jpg"];
    } else if ([indexPath row] == 1) {
        titleLabel.text = @"Take Back The Night";
        artistLabel.text = @"Justin Timberlake";
        coverImageView.image = [UIImage imageNamed:@"cover_art_test_2.jpg"];
    }
    
    return cell;
}

@end
