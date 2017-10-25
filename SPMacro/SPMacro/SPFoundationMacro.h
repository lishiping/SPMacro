//
//  SPFoundationMacro.h
//  e-mail:83118274@qq.com
//
//  Created by lishiping on 16/11/11.
//  Copyright (c) 2016年 lishiping. All rights reserved.
//
//If you think this open source library is of great help to you, please open the URL to click the Star,your approbation can encourage me, the author will publish the better open source library for guys again
//如果您认为本开源库对您很有帮助，请打开URL给作者点个赞，您的认可给作者极大的鼓励，作者还会发布更好的开源库给大家

//github address//https://github.com/lishiping/SPWebView
//github address//https://github.com/lishiping/SPDebugBar
//github address//https://github.com/lishiping/SPFastPush
//github address//https://github.com/lishiping/SPMacro
//github address//https://github.com/lishiping/SafeData
//github address//https://github.com/lishiping/SPCategory
//github address//https://github.com/lishiping/SPBaseClass

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <mach/mach_time.h>
//#import <execinfo.h>

//------------------weak strong reference----------------
//--------------------弱强引用---------------------------

//判断是不是支持arc模式
#if __has_feature(objc_arc)

#define SP_WEAK_SELF          __weak __typeof(self) weakSelf = self;
#define SP_WEAK(obj)          __weak __typeof(obj) weak##obj = obj;
#define SP_STRONG_SELF        __strong __typeof(weakSelf)strongSelf = weakSelf;

#else

#define SP_WEAK_SELF          __block __typeof(self) weakSelf = self;
#define SP_WEAK(obj)          __block __typeof(obj) weak##obj = obj;
#define SP_STRONG_SELF        __strong __typeof(weakSelf)strongSelf = weakSelf;

#endif


//--------------------Print log---------------------------
//--------------------打印日志---------------------------

#define SP_STRING_FORMAT(fmt, ...)      [NSString stringWithFormat:(@"%z, %s(line %d) " fmt), clock(), __FUNCTION__, __LINE__, ##__VA_ARGS__]



#if DEBUG

#define SP_LOG(...) NSLog(__VA_ARGS__);

#define SP_LOG_FMT(fmt, ...) NSLog((@"%s (line %d) " fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__);

#define SP_LOG_IF(x, fmt, ...) if (x) {SP_LOG_FMT(fmt, ##__VA_ARGS__);}

#define SP_PRINTF(fmt, ...)  printf(("%ld, %s (line %d) " fmt), clock(), __FUNCTION__, __LINE__, ##__VA_ARGS__);

// 打印super class
#define SP_PRINT_FATHERCLASS(obj) [SPFoundationMacro printFatherClass:obj];


#else


#define SP_LOG(...)

#define SP_LOG_FMT(fmt, ...)

#define SP_LOG_IF(x, fmt, ...)

#define SP_PRINTF(fmt, ...)

#define SP_PRINT_FATHERCLASS(obj)


#endif


//--------------------assert---------------------------
//--------------------断言---------------------------

#if DEBUG


#define SP_ASSERT(obj)               assert((obj))

#define SP_ASSERT_CLASS(obj, cls)  SP_ASSERT((x) && SP_IS_KIND_OF(obj,cls))//断言实例有值和类型

// (assert main thread)断言在主线程中
#define SP_ASSERT_MAIN_THREAD             SP_ASSERT(SP_IS_MAIN_THREAD)


#else


#define SP_ASSERT(obj)

#define SP_ASSERT_CLASS(obj, cls)

#define SP_ASSERT_MAIN_THREAD


#endif



//------Code execution time(return min seconds）-------------
//------------------代码运算时间(返回毫秒时间)------------------

/*
 CGFloat time =  SP_EXECUTE_TIME({
 sleep(2);
 });
 
 SP_LOG(@"代码执行时间%fms",time);
 */
#define SP_EXECUTE_TIME(block) [SPFoundationMacro calculateRunTimeBlock:^{(block);}];


//------------------Kind Of Class---------------------
//------------------类型判断---------------------------

// 判断实例类型(含父类)
#define SP_IS_KIND_OF(obj, cls)                [(obj) isKindOfClass:[cls class]]

// 判断实例类型(不含父类)
#define SP_IS_MEMBER_OF(x, cls)              [(x) isMemberOfClass:[cls class]]

// 判断实例类型(是否是子类)
#define SP_IS_SUBCLASS_OF(x, cls)              [(x) isSubclassOfClass:[cls class]]


//--------------------Notification---------------------------
//--------------------通知---------------------------

#define __SP  [NSNotificationCenter defaultCenter]

// 添加观察者
#define SP_ADD_OBSERVER(__obj, __sel, __name, __message)      [__SP addObserver:__obj selector:__sel name:__name object:__message]

// 发送消息（同步）
#define SP_POST_NOTI(__name, __message)                 [__SP postNotificationName:__name object:__message]

// 取消观察
#define SP_REMOVE_SELF                     [__SP removeObserver:self]

#define SP_REMOVE(__obj)                    [__SP removeObserver:__obj]

#define SP_REMOVE_NAME(__obj, __name, __message)      [__SP removeObserver:__obj name:__name object:__message]


//--------------------APP Version----------------------
//--------------------APP版本---------------------------

//获取APP版本
#ifndef SP_APP_VERSION
#define SP_APP_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]

//获取APP的build版本
#define SP_APP_BUILD_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]

#endif


//--------------------Thread------------------------
//--------------------线程---------------------------

// (is main thread)判断是否主线程
#define SP_IS_MAIN_THREAD                [NSThread isMainThread]

// (run in main thread)使block在主线程中运行
#define SP_RUN_MAIN_THREAD(block)    if (SP_IS_MAIN_THREAD) {(block);} else {dispatch_async(dispatch_get_main_queue(), ^{(block);});}

// (run in global thread)使block在子线程中运行
#define SP_RUN_GlOBAL_THREAD(block)    if (!SP_IS_MAIN_THREAD) {(block);} else {dispatch_async(dispatch_get_global_queue(0,0), ^{(block);});}

// (safe run block)安全运行block
#define SP_BLOCK(block, ...)     if (block) {block(__VA_ARGS__);}



//--------------------dial phone------------------------
//--------------------拨打电话---------------------------


/**
 Call the system call
 调用系统拨打电话
 
 @param phoneNumber 电话号码
 @param isNeedAlert 是否弹出alert询问
 
 */
#define SP_DIAL_PHONE(phoneNumber,isNeedAlert) [SPFoundationMacro ios_dialPhone:phoneNumber needAlert:isNeedAlert]



//--------------------SandBox Path---------------------------
//--------------------沙盒路径---------------------------

//获取沙盒主目录路径
#define SP_PATH_HOME NSHomeDirectory()

//沙盒文档路径
/*Documents 目录：您应该将所有应用程序数据文件写入到这个目录下。这个目录用于存储用户数据或其它应该定期备份的信息。
 ②是否会被iTunes同步
 是
 */
#define SP_PATH_DOCUMENT     [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]


//沙盒library路径
/*Library目录：这个目录下有两个子目录：Preference,Caches
 ①存放内容
 苹果建议用来存放默认设置或其它状态信息。该路径下的文件夹，除Caches以外，都会被iTunes备份。
 ②是否会被iTunes同步
 是，但是要除了Caches子目录外
 */
#define SP_PATH_LIBRARY      [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0]


//沙盒Preference路径
/*①存放内容
 应用程序的偏好设置文件,配置目录，配置文件。我们使用NSUserDefaults写的设置数据都会保存到该目录下的一个plist文件中，这就是所谓的写到plist中！
 ②是否会被iTunes同步
 是
 */
#define SP_PATH_PREFERENCE      [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"Preference"]


//沙盒Caches缓存路径
//Caches 目录：用于存放应用程序专用的支持文件，保存应用程序再次启动过程中需要的信息,存储项目缓存,常用设置。可创建子文件夹。可以用来放置您希望被备份但不希望被用户看到的数据。
/*①存放内容
 主要是缓存文件，用户使用过程中缓存都可以保存在这个目录中。前面说过，Documents目录用于保存不可再生的文件，那么这个目录就用于保存那些可再生的文件，比如网络请求的数据。鉴于此，应用程序通常还需要负责删除这些文件。
 ②是否会被iTunes同步
 否。
 */
#define SP_PATH_CACHE      [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]

//沙盒tmp路径
//tmp 目录：这个目录用于存放临时文件，保存应用程序再次启动过程中不需要的信息。该路径下的文件不会被iTunes备份。
/*①存放内容
 各种临时文件，保存应用再次启动时不需要的文件。而且，当应用不再需要这些文件时应该主动将其删除，因为该目录下的东西随时有可能被系统清理掉，目前已知的一种可能清理的原因是系统磁盘存储空间不足的时候。
 ②是否会被iTunes同步
 否
 */
#define SP_PATH_TMP      NSTemporaryDirectory()


//--------------------file---------------------------
//--------------------文件---------------------------

//判断文件是否存在
#define SP_IS_FILE_EXIST(path)             [[NSFileManager defaultManager] fileExistsAtPath:(path)]


//--------------Reference counting----------------------
//--------------------引用计数---------------------------


#define MRC_Retain(x)           [(x) retain];
#define MRC_Copy(x)             [(x) copy];
#define MRC_Release(x)          {if(x){[(x) release];}}
#define MRC_Release_View(x)     {if(x){[(x) removeFromSuperview];[(x) release];(x)=nil;}}
#define MRC_Dealloc(x)          [(x) dealloc];


#define ARC_Retain(x)           (x)
#define ARC_Copy(x)             (x)
#define ARC_Release(x)          {(x)=nil;}
#define ARC_Release_View(x)     {if(x){[(x) removeFromSuperview];(x)=nil;}}
#define ARC_Dealloc(x)


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


//--------------------local Language---------------------------
//--------------------本地语言---------------------------

//判断本地语言是不是英语
#define SP_LANGUAGE_IS_EN()         [[[NSLocale preferredLanguages] objectAtIndex:0] isEqualToString:@"en"]


//--------------------runtime---------------------------


//runtime换类方法
#define SP_EXCHANGE_IMP_CLASS_METHOD(_cls_, _sel_1, _sel_2) {\
Method method1 = class_getClassMethod(_cls_, _sel_1);\
Method method2 = class_getClassMethod(_cls_, _sel_2);\
SP_ASSERT(method1 != NULL);\
SP_ASSERT(method2 != NULL);\
SP_LOG(@"exchange [%@], +%@(0x%08lx) ==> +%@(0x%08lx), ", NSStringFromClass(_cls_), NSStringFromSelector(_sel_1), (long)method1, NSStringFromSelector(_sel_2), (long)method2);\
if (method1 && method2) {\
method_exchangeImplementations(method1, method2);\
}\
}

//runtime换实例方法
#define SP_EXCHANGE_IMP_CLASS_INSTANCE(_cls_, _sel_1, _sel_2) {\
Method method1 = class_getInstanceMethod(_cls_, _sel_1);\
Method method2 = class_getInstanceMethod(_cls_, _sel_2);\
SP_ASSERT(method1 != NULL);\
SP_ASSERT(method2 != NULL);\
SP_LOG(@"exchange (%@), -%@(0x%08lx) ==> -%@(0x%08lx), ", NSStringFromClass(_cls_), NSStringFromSelector(_sel_1), (long)method1, NSStringFromSelector(_sel_2), (long)method2);\
if (method1 && method2) {\
method_exchangeImplementations(method1, method2);\
}\
}



@interface SPFoundationMacro : NSObject

//+(void)printBacktrace;  // 函数调用堆栈

+(void)printFatherClass:(id)obj;    // 打印super class

+(void)ios_dialPhone:(NSString *)phoneNumber needAlert:(BOOL)isNeedAlert;

/**
 计算代码块的执行时间的方法,用来验证算法的执行效率等其他需要测试执行时间的代码
 
 @param block 代码块
 @return (return ms time)返回毫秒运算时间
 */
+(CGFloat)calculateRunTimeBlock:(void (^)(void))block;


@end
