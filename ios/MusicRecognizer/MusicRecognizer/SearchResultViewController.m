//
//  SearchResultViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 1/14/14.
//  Copyright (c) 2014 ITKMITL. All rights reserved.
//

#import "SearchResultViewController.h"

@interface SearchResultViewController ()

@end

@implementation SearchResultViewController

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
	[DejalKeyboardActivityView activityViewForView:self.navigationController.view withLabel:@"Loading..."];
    // Do any additional setup after loading the view.
}

- (void)viewDidAppear:(BOOL)animated {
    self.titleLabel.text = [self.parameters objectForKey:@"title"];
    self.artistLabel.text = [self.parameters objectForKey:@"artist"];
    self.albumLabel.text = [self.parameters objectForKey:@"album"];
    __weak UIImageView *weakCoverImageView = self.coverImageView;
    NSString *image = [NSString stringWithFormat:@"http://161.246.38.80:8080/static/chordle_cover/%@ - %@.jpg",[self.parameters objectForKey:@"artist"],[self.parameters objectForKey:@"album"]];
    NSString *encodedImage = [image stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    [self.coverImageView setImageWithURLRequest:[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:encodedImage]] placeholderImage:nil success:^(NSURLRequest *request, NSHTTPURLResponse *response, UIImage *image){
        weakCoverImageView.image = image;
        [DejalKeyboardActivityView removeViewAnimated:YES];
    } failure:^(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error){
        NSLog(@"%@",error);
    }];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)donePressed:(UIBarButtonItem *)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
