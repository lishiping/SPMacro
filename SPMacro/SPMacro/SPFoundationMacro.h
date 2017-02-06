//
//  SPFoundationMacro.h
//  83118274@qq.com
//
//  Created by 李世平 on 12-2-21.
//  Copyright (c) 2012年 李世平. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <execinfo.h>
//#define TARGET_OS_IPHONE            1
//#define TARGET_IPHONE_SIMULATOR     1

//--------------------强弱引用---------------------------

#define SP_weakSelf          __weak __typeof(self) weakSelf = self;
#define SP_strongSelf        __strong __typeof(weakSelf)strongSelf = weakSelf;

//--------------------打印日志---------------------------

#pragma mark - LOG & 断言

#define SP_String_Format(fmt, ...)      [NSString stringWithFormat:(@"%z, %s(line %d) " fmt), clock(), __FUNCTION__, __LINE__, ##__VA_ARGS__]

#if DEBUG

#define SP_Log(fmt, ...)           {NSLog((@"%s (line %d) " fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__);}

#define SP_Log_If(x, fmt, ...)     if (x) {SP_Log(fmt, ##__VA_ARGS__)}

#define ASSERT(x)               assert((x))

#define SP_Printf(fmt, ...)                {printf(("%ld, %s (line %d) " fmt), clock(), __FUNCTION__, __LINE__, ##__VA_ARGS__);}

// 打印super class
#define SP_Print_FatherClasss(obj) [SPFoundationMacro printFatherClass:obj]


#else

#endif

//--------------------类型判断---------------------------

#define SP_isKindOf(x, cls)                [(x) isKindOfClass:[cls class]]         // 判断实例类型(含父类)

#define SP_isMemberOf(x, cls)              [(x) isMemberOfClass:[cls class]]       // 判断实例类型(不含父类)

//--------------------通知---------------------------

#pragma mark - NSNotificationCenter（通知）

#define __SP  [NSNotificationCenter defaultCenter]

// 添加观察者
#define SP_Add_Observer(__obj, __sel, __name, __message)      [__SP addObserver:__obj selector:__sel name:__name object:__message]

// 发送消息（同步）
#define SP_Post_Notification(__name, __message)                 [__SP postNotificationName:__name object:__message]

// 取消观察
#define SP_Remove_Self                     [__SP removeObserver:self]

#define SP_Remove(__obj)                    [__SP removeObserver:__obj]

#define SP_Remove_Name(__obj, __name, __message)      [__SP removeObserver:__obj name:__name object:__message]


//--------------------APP版本---------------------------

//获取APP版本
#ifndef SP_AppVersion
#define SP_AppVersion [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]

//获取APP的build版本
#define SP_AppBuildVersion [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]

#endif


//--------------------线程---------------------------

// 判断是否主线程
#define SP_Is_Main_Thread                [NSThread isMainThread]

// 断言在主线程中
#define ASSERT_MainThread()             ASSERT(SP_Is_Main_Thread)

// 使block在主线程中运行
#define SP_Main_Thread_Run(block)    if (SP_Is_Main_Thread) {(block);} else {dispatch_async(dispatch_get_main_queue(), ^{(block);});}

// 使block在子线程中运行
#define SP_Global_Thread_Run(block)    if (!SP_Is_Main_Thread) {(block);} else {dispatch_async(dispatch_get_global_queue(0,0), ^{(block);});}

// 安全运行block
#define SP_Call_Back_Block(block, ...)     if (block) {block(__VA_ARGS__);}

//--------------------拨打电话---------------------------


/**
 调用系统拨打电话

 @param phoneNumber 电话号码
 @param isNeedAlert 是否弹出alert询问

 */
#define SP_DialPhone(phoneNumber,isNeedAlert) [SPFoundationMacro ios_dialPhone:phoneNumber needAlert:isNeedAlert]

//--------------------沙盒路径---------------------------

//沙盒缓存路径
#define SP_Path_Cache      [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]

//沙盒文档路径
#define SP_Path_Document      [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]


//--------------------文件---------------------------

//判断文件是否存在
#define SP_Is_FileExist(path)             [[NSFileManager defaultManager] fileExistsAtPath:(path)]


//--------------------引用计数---------------------------

#pragma mark - 内存 & 引用计数

#define MRC_Retain(x)           [(x) retain]
#define MRC_Copy(x)             [(x) copy]
#define MRC_Release(x)          {if(x){[(x) release];(x)=nil;}}
#define MRC_Release_View(x)     {if(x){[(x) removeFromSuperview];[(x) release];(x)=nil;}}
#define MRC_Dealloc(x)          [(x) dealloc];


#define ARC_Retain(x)           (x)
#define ARC_Copy(x)             (x)
#define ARC_Release(x)          {(x)=nil;}
#define ARC_Release_View(x)     {if(x){[(x) removeFromSuperview];(x)=nil;}}
#define ARC_Dealloc(x)


#define SAFE_Free(x)            if(x){free(x);(x)=NULL;}
#define SAFE_Delete(x)          {if(x){delete (x);(x)=NULL;}}
#define SAFE_DeleteA(x)         {if(x){delete [](x);(x)=NULL;}}

//判断是不是支持arc模式
#if __has_feature(objc_arc)

#define OC_Retain(x)            ARC_Retain(x)
#define OC_Copy(x)              ARC_Copy(x)
#define OC_Release(x)           ARC_Release(x)
#define OC_Release_View(x)      ARC_Release_View(x)
#define OC_SuperDealloc         

#else

#define OC_Retain(x)            MRC_Retain(x)
#define OC_Copy(x)              MRC_Copy(x)
#define OC_Release(x)           MRC_Release(x)
#define OC_Release_View(x)      MRC_Release_View(x)
#define OC_SuperDealloc         MRC_Dealloc(super)

#endif

//--------------------ios版本---------------------------


//#define _iOSVerBigger(x)        (NSFoundationVersionNumber >= (x) - 0.0001)//FLT_EPSILON)
//
//#define IOS5_OR_LATER           _iOSVerBigger(NSFoundationVersionNumber_iOS_5_0)
//#define IOS6_OR_LATER           _iOSVerBigger(NSFoundationVersionNumber_iOS_6_0)
//#define IOS7_OR_LATER           _iOSVerBigger(NSFoundationVersionNumber_iOS_7_0)
//#define IOS8_OR_LATER           _iOSVerBigger(NSFoundationVersionNumber_iOS_8_0)
//#define IOS9_OR_LATER           _iOSVerBigger(NSFoundationVersionNumber_iOS_9_0)

//--------------------本地语言---------------------------

#define SP_LanguageIsEnglish()         [preferredLanguage() isEqualToString:@"en"]


//--------------------runtime---------------------------


//runtime换类方法
#define SP_ExchangeImplementations_Class_Method(_cls_, _sel_1, _sel_2) {\
Method method1 = class_getClassMethod(_cls_, _sel_1);\
Method method2 = class_getClassMethod(_cls_, _sel_2);\
ASSERT(method1 != NULL);\
ASSERT(method2 != NULL);\
SP_LOG(@"exchange [%@], +%@(0x%08lx) ==> +%@(0x%08lx), ", NSStringFromClass(_cls_), NSStringFromSelector(_sel_1), (long)method1, NSStringFromSelector(_sel_2), (long)method2);\
if (method1 && method2) {\
method_exchangeImplementations(method1, method2);\
}\
}

//runtime换实例方法
#define SP_ExchangeImplementations_Class_Instance(_cls_, _sel_1, _sel_2) {\
Method method1 = class_getInstanceMethod(_cls_, _sel_1);\
Method method2 = class_getInstanceMethod(_cls_, _sel_2);\
ASSERT(method1 != NULL);\
ASSERT(method2 != NULL);\
SP_LOG(@"exchange (%@), -%@(0x%08lx) ==> -%@(0x%08lx), ", NSStringFromClass(_cls_), NSStringFromSelector(_sel_1), (long)method1, NSStringFromSelector(_sel_2), (long)method2);\
if (method1 && method2) {\
method_exchangeImplementations(method1, method2);\
}\
}



@interface SPFoundationMacro : NSObject

+(void)printBacktrace;  // 函数调用堆栈

+(void)printFatherClass:(id)obj;    // 打印super class

+(void)ios_dialPhone:(NSString *)phoneNumber needAlert:(BOOL)isNeedAlert;

@end
