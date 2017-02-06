//
//  SPFoundationMacro.h
//  83118274@qq.com
//
//  Created by 李世平 on 12-2-21.
//  Copyright (c) 2012年 李世平. All rights reserved.
//

#import "SPFoundationMacro.h"


@interface SPFoundationMacro()

@end

@implementation SPFoundationMacro


// 函数调用堆栈
+(void)printBacktrace
{
    void *callstack[128] = {0};
    int frameCount = backtrace(callstack, 128);
    char **frameStrings = backtrace_symbols(callstack, frameCount);
    if ( frameStrings != NULL ) {
        // Start with frame 1 because frame 0 is PrintBacktrace()
        for ( int i = 1; i < frameCount; i++ ) {
            printf("%s\n", frameStrings[i]);
            
        }
        free(frameStrings);
    }
}


+(void)printFatherClass:(id)obj
{
#if DEBUG
    printf("\n class:");
    Class cls = object_getClass(obj);
    while (cls)
    {
        printf(" %s -->", class_getName(cls));
        cls = class_getSuperclass(cls);
    }
    printf("\n");
#endif
}


+(void)ios_dialPhone:(NSString *)phoneNumber needAlert:(BOOL)isNeedAlert
{
    if (phoneNumber.length > 0)
    {
        NSString *tel = [NSString stringWithFormat:(isNeedAlert ? @"telprompt://%@" : @"tel://%@"), phoneNumber];
        
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:tel]];
    }
}

@end





