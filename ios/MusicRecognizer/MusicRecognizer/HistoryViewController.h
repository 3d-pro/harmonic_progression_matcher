//
//  HistoryViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AFNetworking.h>
#import <AFNetworking/UIImageView+AFNetworking.h>
#import <DejalActivityView.h>
#import "TypicalFunctions.h"

@interface HistoryViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableDictionary *tokenDict;
@property (strong, nonatomic) NSArray *historyArray;

@end
