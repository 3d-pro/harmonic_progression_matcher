//
//  HistoryViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 12/30/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TypicalFunctions.h"

@interface HistoryViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) TypicalFunctions *func;

@end
