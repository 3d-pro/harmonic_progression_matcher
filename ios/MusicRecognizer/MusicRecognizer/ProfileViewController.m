//
//  ProfileViewController.m
//  
//
//  Created by Kittipun on 1/3/14.
//
//

#import "ProfileViewController.h"

@interface ProfileViewController ()

@end

@implementation ProfileViewController

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
    self.logoutBarButton = [[UIBarButtonItem alloc] initWithTitle:@"Logout" style:UIBarButtonItemStyleDone target:self action:@selector(logoutPressed)];
    self.navigationItem.rightBarButtonItem = self.logoutBarButton;
	// Do any additional setup after loading the view.
}

-(void)viewWillAppear:(BOOL)animated {
    self.tokenPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"token.json"];
    //NSLog(@"%@",[NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:self.tokenPath] options:NSJSONReadingMutableContainers error:nil]);
    self.tokenDict = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:self.tokenPath] options:NSJSONReadingMutableContainers error:nil];
    self.navigationItem.title = [self.tokenDict objectForKey:@"username"];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)logoutPressed {
    [[NSFileManager defaultManager] removeItemAtPath:self.tokenPath error:nil];
    self.profileNavViewController = [self.view.window.rootViewController.childViewControllers objectAtIndex:2];
    self.loginController = [self.storyboard instantiateViewControllerWithIdentifier:@"Login"];
    [self.profileNavViewController setViewControllers:@[self.loginController] animated:YES];
}

@end
