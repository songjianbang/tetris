//
//  AppDelegate.m
//  Tetris
//
//  Created by 建邦 宋 on 14-5-25.
//  Copyright (c) 2014年 rx. All rights reserved.
//

#import "AppDelegate.h"
#include "game.h"


@implementation AppDelegate
@synthesize m_fscale=m_fscale;
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    m_fscale = [[UIScreen mainScreen] scale];
    return YES;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touches");
    int cnt = [touches count];
    NSLog(@"%d", cnt);
    for (UITouch *touch in touches) {
        float x,y;
        x = [touch locationInView:[touch view]].x *m_fscale;
        y = [touch locationInView:[touch view]].y *m_fscale;
        NSLog(@"%f,%f", x, y);
        
        float height = [[UIScreen mainScreen] bounds].size.height;
        g_game.TouchBegin(x, height * m_fscale - y);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touches");
    int cnt = [touches count];
    NSLog(@"%d", cnt);
    for (UITouch *touch in touches) {
        float x,y;
        x = [touch locationInView:[touch view]].x *2;
        y = [touch locationInView:[touch view]].y *2;
        NSLog(@"%f,%f", x, y);
        g_game.TouchBegin(x, [[UIScreen mainScreen] bounds].size.height * m_fscale - y);
    }
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
