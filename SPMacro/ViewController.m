//
//  ViewController.m
//  SPMacro
//
//  Created by uxin-lishiping on 17/2/4.
//  Copyright © 2017年 lishiping. All rights reserved.
//

#import "ViewController.h"
#import "SPMacro.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    CGFloat h = SP_SCREEN_HEIGHT;
    CGFloat w = SP_SCREEN_WIDTH;
    SP_LOG_FMT(@"屏幕宽度==%f和高度==%f",w,h);
    SP_SUPER_LOG(@"屏幕宽度==%f和高度==%f",w,h);

    //    CGFloat time =  SP_EXECUTE_TIME({
    //        sleep(2);
    //    });
    //
    //    SP_LOG(@"代码执行时间%f",time);
    //    NSAssert(1, nil);
    //    assert(3);
    
    SP_RUN_MAIN_THREAD
    (self.view.backgroundColor = [UIColor blueColor];
     NSLog(@"打印当前线程%@",[NSThread currentThread]);
     )
    
//    double  time =   SP_EXECUTE_TIME(
//
//                                     sleep(2);
//                                     )
//
//    SP_LOG(@"执行时间==%fms",time);
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
