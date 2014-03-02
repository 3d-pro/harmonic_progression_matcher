//
//  AppDelegate.m
//  MusicRecognizer
//
//  Created by Kittipun on 11/11/13.
//  Copyright (c) 2013 ITKMITL. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    self.func = [[TypicalFunctions alloc] init];
    
    //tab bar init.
    UITabBarController *tabBarController = (UITabBarController *)self.window.rootViewController;
    UITabBar *tabBar = tabBarController.tabBar;
    [tabBar setTintColor:[self.func colorWithHexString:@"ffffff"]];
    
//    [tabBar setSelectedImageTintColor:[self.func colorWithHexString:@"74b2d7"]];
//    UITabBarItem *tabBarItem1 = [tabBar.items objectAtIndex:0];
//    UITabBarItem *tabBarItem2 = [tabBar.items objectAtIndex:1];
//    UITabBarItem *tabBarItem3 = [tabBar.items objectAtIndex:2];
//    
//    [tabBarItem1 setTitle:@"Search"];
//    [tabBarItem1 setImage:[[UIImage imageNamed:@"search.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
//    [tabBarItem1 setSelectedImage:[[UIImage imageNamed:@"search_selected.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
//    
//    [tabBarItem2 setTitle:@"History"];
//    [tabBarItem2 setImage:[[UIImage imageNamed:@"history.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
//    [tabBarItem2 setSelectedImage:[[UIImage imageNamed:@"history_selected.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
//    
//    [tabBarItem3 setTitle:@"Profile"];
//    [tabBarItem3 setImage:[[UIImage imageNamed:@"profile.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
//    [tabBarItem3 setSelectedImage:[[UIImage imageNamed:@"profile_selected.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
//    
//    [[UITabBarItem appearance] setTitleTextAttributes:@{ NSForegroundColorAttributeName :  [self.func colorWithHexString:@"ffffff"]}
//                                             forState:UIControlStateNormal];
//    [[UITabBarItem appearance] setTitleTextAttributes:@{ NSForegroundColorAttributeName : [self.func colorWithHexString:@"74b2d7"]}
//                                             forState:UIControlStateHighlighted];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
