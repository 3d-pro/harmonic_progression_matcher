//
//  MicrophoneInput.m
//  Echoprint
//
//  Created by Brian Whitman on 1/23/11.
//  Copyright 2011 The Echo Nest. All rights reserved.
//

#import "MicrophoneInput.h"


@implementation MicrophoneInput

- (void)viewDidLoad
{
    [super viewDidLoad];
}

-(IBAction) startRecording
{
	NSLog(@"startRecording");
	audioRecorder = nil;
	
	// Init audio with record capability
	AVAudioSession *audioSession = [AVAudioSession sharedInstance];
	[audioSession setCategory:AVAudioSessionCategoryRecord error:nil];
	[audioSession overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:nil];
    
	NSMutableDictionary *recordSettings = [[NSMutableDictionary alloc] initWithCapacity:10];
	[recordSettings setObject:[NSNumber numberWithInt: kAudioFormatMPEG4AAC] forKey: AVFormatIDKey];
	[recordSettings setObject:[NSNumber numberWithFloat:44100.0] forKey: AVSampleRateKey];
	[recordSettings setObject:[NSNumber numberWithInt:1] forKey:AVNumberOfChannelsKey];
	[recordSettings setObject:[NSNumber numberWithInt:16] forKey:AVLinearPCMBitDepthKey];
    [recordSettings setObject:[NSNumber numberWithInt: AVAudioQualityHigh] forKey: AVEncoderAudioQualityKey];
    
	//set the export session's outputURL to <Documents>/output.m4a
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSURL *outURL = [NSURL fileURLWithPath:[documentsDirectory stringByAppendingPathComponent:@"output.m4a"]];
	[[NSFileManager defaultManager] removeItemAtURL:outURL error:nil];
	NSLog(@"url loc is %@", outURL);
	
	NSError *error = nil;
	audioRecorder = [[AVAudioRecorder alloc] initWithURL:outURL settings:recordSettings error:&error];
	audioRecorder.meteringEnabled = YES;
	if ([audioRecorder prepareToRecord] == YES) {
		[audioRecorder record];
	} else {
		int errorCode = CFSwapInt32HostToBig ([error code]); 
		NSLog(@"Error: %@ [%4.4s])" , [error localizedDescription], (char*)&errorCode); 
		
	}
	NSLog(@"recording");
}

-(IBAction) stopRecording
{
	NSLog(@"stopRecording");
	[audioRecorder stop];
	NSLog(@"stopped");
}

-(IBAction) playRecording
{
	NSLog(@"playRecording");
	// Init audio with playback capability
	AVAudioSession *audioSession = [AVAudioSession sharedInstance];
	[audioSession setCategory:AVAudioSessionCategoryPlayback error:nil];
	
	NSURL *url = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%@/recordTest.m4a", [[NSBundle mainBundle] resourcePath]]];
	NSError *error;
	audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
	audioPlayer.numberOfLoops = 0;
	[audioPlayer play];
	NSLog(@"playing");
}

-(IBAction) stopPlaying
{
	NSLog(@"stopPlaying");
	[audioPlayer stop];
	NSLog(@"stopped");
}


@end
