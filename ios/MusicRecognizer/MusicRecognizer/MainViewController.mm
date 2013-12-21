//
//  MainViewController.m
//  MusicRecognizer
//
//  Created by Kittipun on 12/4/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import "MainViewController.h"

extern std::string *GetPCMFromFile(char * filename);

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
- (IBAction)startRecognizer:(id)sender {
    if (self.recording) {
        self.recording = NO;
        [self.recorder stopRecording];
        
        [self.recognizerButton setTitle:@"Start Recognizer" forState:UIControlStateNormal];
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
		NSString *filePath =[documentsDirectory stringByAppendingPathComponent:@"output.caf"];
        std::string *fpCode = GetPCMFromFile((char*) [filePath cStringUsingEncoding:NSUTF8StringEncoding]);
        [self getSong:fpCode];
    } else {
        self.recording = YES;
        [self.recognizerButton setTitle:@"Stop" forState:UIControlStateNormal];
        [self.recorder startRecording];
    }
    
}

- (void)getSong:(std::string *)fpCode {
	NSLog(@"Done: %c", fpCode);
	AFHTTPRequestOperationManager *manager = [AFHTTPRequestOperationManager manager];
    NSMutableDictionary *params = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                   [NSString stringWithFormat:@"%@", fpCode], @"fp_code", nil];
    [manager POST:@"http://161.246.38.80:8080/query" parameters:params success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"JSON: %@", responseObject);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", error);
    }];
}

@end
