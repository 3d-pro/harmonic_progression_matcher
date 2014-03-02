//
//  SearchResultViewController.h
//  MusicRecognizer
//
//  Created by Kittipun on 1/14/14.
//  Copyright (c) 2014 ITKMITL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AFNetworking/UIImageView+AFNetworking.h>
#import <DejalActivityView.h>

@interface SearchResultViewController : UIViewController

@property (strong, nonatomic) IBOutlet UILabel *titleLabel;
@property (strong, nonatomic) IBOutlet UILabel *artistLabel;
@property (strong, nonatomic) IBOutlet UILabel *albumLabel;
@property (strong, nonatomic) IBOutlet UIImageView *coverImageView;
@property (strong, nonatomic) NSDictionary *parameters;

@end
