//
//  ViewController.m
//  SPMacro
//
//  Created by uxin-lishiping on 17/2/4.
//  Copyright © 2017年 lishiping. All rights reserved.
//

#import "ViewController.h"
#import "SPUIKitMacro.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CGFloat h = SP_SCREEN_HEIGHT;
    CGFloat w = SP_SCREEN_WIDTH;
    SP_LOG(@"屏幕宽度==%f和高度==%f",w,h);
    
//    CGFloat time =  SP_EXECUTE_TIME({
//        sleep(2);
//    });
//    
//    SP_LOG(@"代码执行时间%f",time);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
