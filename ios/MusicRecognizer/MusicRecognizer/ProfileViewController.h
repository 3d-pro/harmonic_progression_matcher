//
//  ProfileViewController.h
//  
//
//  Created by Kittipun on 1/3/14.
//
//

#import <UIKit/UIKit.h>
#import "ProfileNavViewController.h"
#import "LoginViewController.h"

@interface ProfileViewController : UIViewController

@property (strong, nonatomic) UIBarButtonItem *logoutBarButton;
@property (strong, nonatomic) NSString *tokenPath;
@property (strong, nonatomic) NSMutableDictionary *tokenDict;
@property (strong, nonatomic) ProfileNavViewController *profileNavViewController;
@property (strong, nonatomic) LoginViewController *loginController;

@end
