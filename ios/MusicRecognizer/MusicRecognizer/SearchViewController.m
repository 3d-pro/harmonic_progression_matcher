//
//  SearchViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 2/19/14.
//  Copyright (c) 2014 ITKMITL. All rights reserved.
//

#import "SearchViewController.h"

@interface SearchViewController ()

@end

@implementation SearchViewController

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
    self.recorder = [[MicrophoneInput alloc] init];
    self.func = [[TypicalFunctions alloc] init];
    self.timeCounter.delegate = self;
    NSNumber* interval = [NSNumber numberWithLong:20000.0];
    self.timeCounter.intervals = @[interval];
    self.timeCounter.backgroundColor = [UIColor blackColor];
    self.timeCounter.outerProgressColor = [UIColor whiteColor];
    self.timeCounter.labelColor = [UIColor whiteColor];
    // Do any additional setup after loading the view.
}

- (void)viewWillAppear:(BOOL)animated {
    self.searchResultDict = [[NSMutableDictionary alloc] init];
    self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"token.json"];
}

- (void)viewDidAppear:(BOOL)animated {
    [self.recorder startRecording];
    [self.timeCounter start];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)countdownDidEnd:(SFRoundProgressCounterView *)progressCounterView {
    [self.recorder stopRecording];
    [DejalKeyboardActivityView activityViewForView:self.view withLabel:@"Finding..."];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *filePath = [documentsDirectory stringByAppendingPathComponent:@"output.m4a"];
    unsigned long long fileSize = [[[NSFileManager defaultManager] attributesOfItemAtPath:filePath error:nil] fileSize];
    NSLog(@"filesize: %@", [NSByteCountFormatter stringFromByteCount:fileSize countStyle:NSByteCountFormatterCountStyleFile]);
    [self getCode:filePath];
}

- (void)getCode:(NSString *)filePath {
    NSData *audioData = [NSData dataWithContentsOfFile:filePath];
    AFHTTPRequestOperationManager *manager = [[AFHTTPRequestOperationManager alloc] initWithBaseURL:[NSURL URLWithString:@"http://161.246.38.80:8080"]];
    AFHTTPRequestOperation *op = [manager POST:@"/code" parameters:nil constructingBodyWithBlock:^(id<AFMultipartFormData> formData) {
        [formData appendPartWithFileData:audioData name:@"myfile" fileName:@"output.m4a" mimeType:@"audio/m4a"];
    } success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"Success! %@", operation.responseString);
        self.JSON = [NSJSONSerialization JSONObjectWithData: operation.responseData
                                                    options: NSJSONReadingMutableContainers
                                                      error: nil];
        self.metadata = [self.JSON objectForKey:@"metadata"];
        if (![self.metadata objectForKey:@"track"] || ![self.metadata objectForKey:@"artist"]) {
            UIAlertView *notFoundAlert = [[UIAlertView alloc] initWithTitle:@"Song not found!"
                                                                    message:@"Please try again!"
                                                                   delegate:self
                                                          cancelButtonTitle:@"OK"
                                                          otherButtonTitles:nil, nil];
            [notFoundAlert show];
        } else {
            //check for token path. if exists, send to /history
            if ([[NSFileManager defaultManager] fileExistsAtPath:self.tokenPath]) {
                self.tokenDict = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:self.tokenPath] options:NSJSONReadingMutableContainers error:nil];
                NSString *album;
                if ([self.metadata objectForKey:@"release"] == nil) {
                    album = @"-";
                } else {
                    album = [self.metadata objectForKey:@"release"];
                }
                NSDictionary *parameters = @{@"username": [self.tokenDict objectForKey:@"username"], @"artist": [self.metadata objectForKey:@"artist"], @"album": album, @"title": [self.metadata objectForKey:@"track"]};
                [manager POST:@"/history" parameters:parameters success:^(AFHTTPRequestOperation *operation, id responseObject) {
                    if ([[responseObject objectForKey:@"message"] isEqualToString:@"Update success."]) {
                        NSLog(@"Update Success.");
                    } else {
                        NSLog(@"Update Failed.");
                    }
                } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                    NSLog(@"Error: %@", error);
                }];
                SearchResultViewController *searchResultController = [self.storyboard instantiateViewControllerWithIdentifier:@"Search Result"];
                [searchResultController setParameters:parameters];
                [self.navigationController setViewControllers:@[searchResultController] animated:YES];
            } else {
                NSDictionary *parameters = @{@"artist": [self.metadata objectForKey:@"artist"], @"album": [self.metadata objectForKey:@"release"], @"title": [self.metadata objectForKey:@"track"]};
                SearchResultViewController *searchResultController = [self.storyboard instantiateViewControllerWithIdentifier:@"Search Result"];
                [searchResultController setParameters:parameters];
                [self.navigationController setViewControllers:@[searchResultController] animated:YES];
            }
        }
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", error);
    }];
    [op start];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)cancelPressed:(UIBarButtonItem *)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}
@end
