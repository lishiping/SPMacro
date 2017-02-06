//
//  SPUIKitMacro.h
//  83118274@qq.com
//
//  Created by 李世平 on 12-2-21.
//  Copyright (c) 2012年 李世平. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIDevice.h>
#import "SPFoundationMacro.h"


//----------------------屏幕尺寸-------------------------

#define SP_ScreenBounds        ([UIScreen mainScreen].bounds)

#define SP_ScreenWidth         ([UIScreen mainScreen].bounds.size.width)

#define SP_ScreenHeight        ([UIScreen mainScreen].bounds.size.height)

#define SP_ScreenScale         ([UIScreen mainScreen].scale)

#define SP_StatusBarHeight     ([[UIApplication sharedApplication] statusBarFrame].size.height)

#define SP_NavigationBarHeight (self.navigationController.navigationBar.frame.size.height)


//--------------------屏幕适配---------------------------

//通常UI给设计图标注的时候不可能三种屏幕分别给标注，太麻烦了，需要只给一种屏幕的标注就行，那么我们这里管UI要iPhone6屏幕的设计图标注
// iphone4 iphone5 iPhone7 都按照(w=375)标注为基准
#define SP_AdjustWidthToScreen(width)              (floorf((width) * SP_ScreenWidth * 2 / 375.) * .5)

// iphone4 iphone5 iPhone7 都按照(w=667)标注为基准
#define SP_AdjustHeightToScreen(height)            (floorf((height) * SP_ScreenHeight * 2 / 667.) * .5)


//--------------------设备屏幕---------------------------

//iphone4的屏幕
#define SP_IS_IPHONE4_4S ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(320, 480), [UIScreen mainScreen].bounds.size) : NO)

//iphone5的屏幕
#define SP_IS_IPHONE5_5S ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(320, 568), [UIScreen mainScreen].bounds.size) : NO)

//iphone6和iPhone7的屏幕
#define SP_IS_IPHONE6_6S_7 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(375, 667), [UIScreen mainScreen].bounds.size): NO)

//iphone6P和iPhone7P的屏幕
#define SP_IS_IPHONE6P_6SP_7P ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(414, 736), [UIScreen mainScreen].bounds.size) : NO)

//--------------------字体---------------------------

#define SP_Font(size)        [UIFont systemFontOfSize:(size)]
#define SP_Font_B(size)      [UIFont boldSystemFontOfSize:(size)]
#define SP_FontNameWithSize(name,size) [UIFont fontWithName:(name) size:(size)]


//--------------------颜色---------------------------

#define SP_Color(r, g, b) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:1.0]

//16进制数转为颜色对象
//SP_Color_RGBA(0X1E1E1E);
#define SP_Color_RGB(hexValue) [UIColor colorWith\
Red     :(hexValue & 0xFF0000)     / (float)0xFF0000 \
green   :(hexValue & 0xFF00)       / (float)0xFF00 \
blue    :(hexValue & 0xFF)         / (float)0xFF \
alpha   :1.0]

//16进制数转为颜色对象
//SP_Color_RGBA(0X1E1E1E);
#define SP_Color_RGBA(hexValue) [UIColor colorWith\
Red     :(hexValue & 0xFF000000)  / (float)0xFF000000 \
green   :(hexValue & 0xFF0000)    / (float)0xFF0000 \
blue    :(hexValue & 0xFF00)      / (float)0xFF00 \
alpha   :(hexValue & 0xFF)        / (float)0xFF]

//16进制字符串颜色转为颜色对象
//SP_Color_Hex(@"#1E1E1E");
#define SP_Color_Hex(hexstring)       [SPUIKitMacro colorWithHexString:(hexstring)]


//--------------------图片---------------------------

#define SP_IMAGE(name)           [UIImage imageNamed:(name)]
#define SP_IMAGE_VIEW(name)      [[UIImageView alloc] initWithImage:SP_IMAGE(name)]
#define SP_IMAGE_CG(x)        [UIImage imageWithCGImage:(x)]
#define SP_IMAGE_DATA(data)      [UIImage imageWithData:(data)]

//根据视图截屏
#define SP_IMAGE_Capture(view)     [SPUIKitMacro captureWithView:view]

//获取指定大小的图片，保存原图片比例
#define SP_IMAGE_Compress(image,size)     [SPUIKitMacro compressImage:image toSize:size]

//--------------------警告框---------------------------

#define SP_Show_Alert(message)   _ShowAlertView(0, nil, (message), nil, @"确定", nil)

#define SP_Show_AlertView(_tag_, title, msg, _delegate_, cancelTitle, ...) {\
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: title\
                                                    message: msg\
                                                   delegate: _delegate_\
                                          cancelButtonTitle: cancelTitle\
                                          otherButtonTitles: __VA_ARGS__];\
    alert.tag = _tag_;\
    [alert show];\
}

//--------------------ios版本---------------------------


#define SP_IOS_Version  [SPUIKitMacro getSystemVersion]

//该方法不准确，只对于整数版本准确，如果输入9.2判断不对因为实际版本9.2.1转为float值为9.199998，小于9.2，所以不能输入小数
#define SP_IOS_Version_Or_later(v)  {[SPUIKitMacro getSystemVersion]>=v?YES:NO}

//以下判断准确可用
#define SP_IOS5_Or_Later SP_IOS_Version_Or_later(5)
#define SP_IOS6_Or_Later SP_IOS_Version_Or_later(6)
#define SP_IOS7_Or_Later SP_IOS_Version_Or_later(7)
#define SP_IOS8_Or_Later SP_IOS_Version_Or_later(8)
#define SP_IOS9_Or_Later SP_IOS_Version_Or_later(9)
#define SP_IOS10_Or_Later SP_IOS_Version_Or_later(10)

//--------------------打印---------------------------

//遍历子视图打印指针地址
#define SP_PrintAllView(view)        [SPUIKitMacro printAllViews:view]

@interface SPUIKitMacro : NSObject

/**
 获取系统版本，不准确，如系统版本9.2.1，则返回9.199998

 @return 系统版本
 */
+(float)getSystemVersion;


/**
 16进制#开头的字符串颜色转为颜色对象

 @param color 16进制字符串

 @return 颜色对象
 */
+ (UIColor *)colorWithHexString:(NSString *)color;


/**
 打印当前视图名称和指针地址以及子视图的遍历打印

 @param view 当前视图
 */
+(void)printAllViews:(UIView *)view;


+ (UIImage*)createImageWithColor:(UIColor *)color;



/**
 视图转为图片

 @param view 视图对象

 @return 图片对象
 */
+ (UIImage *)captureWithView:(UIView *)view;


/**
 *  获取指定大小的图片，保存原图片比例
 *
 *  @param size  指定大小
 *
 *  @return 符合要求的图片
 */
+ (UIImage *)compressImage:(UIImage*)image toSize:(CGSize)size;



/**
 图片写入指定目录，默认写入jpg格式，如果图片质量为0，则开始是否允许转为png格式

 @param image              图片
 @param filePath           目录
 @param compressionQuality 图片质量
 @param canPNG             是否允许转为png

 @return 是否写入成功
 */
+ (BOOL)saveImageToFileWith:(UIImage*)image path:(NSString *)filePath withJPEG:(float)compressionQuality orPNG:(BOOL)canPNG;

/**
 将图片写入沙盒，

 @param image              图片
 @param name               图片名字

 @return 是否写入成功
 */
+ (BOOL)saveImageToDocumentWith:(UIImage*)image name:(NSString *)name;


/**
 图片转为png写入沙盒

 @param image 图片
 @param name  图片名字

 @return 是否成功写入
 */
+ (BOOL)savePNGImageToDocumentWith:(UIImage*)image name:(NSString *)name;


@end

