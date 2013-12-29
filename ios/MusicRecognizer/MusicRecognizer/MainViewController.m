//
//  MainViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 12/4/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import "MainViewController.h"


@interface MainViewController ()

@end

@implementation MainViewController

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
	self.recording = NO;
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)recordPressed:(id)sender {
    if (self.recording) {
        self.recording = NO;
        [self.recorder stopRecording];
        [self.statusLabel setText:@"Finding..."];
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
		NSString *filePath =[documentsDirectory stringByAppendingPathComponent:@"output.m4a"];
        unsigned long long fileSize = [[[NSFileManager defaultManager] attributesOfItemAtPath:filePath error:nil] fileSize];
        NSLog(@"filesize: %@", [NSByteCountFormatter stringFromByteCount:fileSize countStyle:NSByteCountFormatterCountStyleFile]);
        [self getCode:filePath];
    } else {
        self.recording = YES;
        //[self.recognizerButton setTitle:@"Stop" forState:UIControlStateNormal];
        [self.recorder startRecording];
        [self.statusLabel setText:@"Recording..."];
    }
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
        NSDictionary *metadata = [self.JSON objectForKey:@"metadata"];
        [self.statusLabel setText:[NSString stringWithFormat:@"%@ - %@",[metadata objectForKey:@"track"],[metadata objectForKey:@"artist"]]];
        //[self.albumLabel setText:[NSString stringWithFormat:@"%@",[metadata objectForKey:@"release"]]];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", error);
    }];
    [op start];
}

@end
