//
//  SPUIKitMacro.m
//  83118274@qq.com
//
//  Created by 李世平 on 12-2-21.
//  Copyright (c) 2012年 李世平. All rights reserved.
//

#import "SPUIKitMacro.h"


void doPrintViewAndSubviews(UIView *view, int level)
{
    printf("%d--", level);
    for (int i=0; i<level; ++i)
    {
        printf("--");
    }
    NSString *str = [NSString stringWithFormat:@"%@,", view];
    printf("%s\n", [str UTF8String]);
    ++level;
    for (UIView *v in view.subviews)
    {
        doPrintViewAndSubviews(v, level);
    }
}

@interface SPUIKitMacro ()
{
    
}
@end

@implementation SPUIKitMacro

+(float)getSystemVersion
{
    NSArray *ar = [[UIDevice currentDevice].systemVersion componentsSeparatedByString:@"."];
    
    NSMutableString *str = [[NSMutableString alloc] init];
    if (ar.count>=2) {
        [str appendString:[ar objectAtIndex:0]];
        [str appendString:@"."];
        [str appendString:[ar objectAtIndex:1]];
    }
    else
    {
        [str appendString:[UIDevice currentDevice].systemVersion];
    }
    
    float version = [str floatValue];
    
    return version;
}

+ (UIColor *)colorWithHexString:(NSString *)color
{
    NSString *cString = [[color stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    
    // String should be 6 or 8 characters
    if ([cString length] < 6) {
        return [UIColor clearColor];
    }
    // 判断前缀
    if ([cString hasPrefix:@"0X"])
        cString = [cString substringFromIndex:2];
    if ([cString hasPrefix:@"#"])
        cString = [cString substringFromIndex:1];
    if ([cString length] != 6)
        return [UIColor clearColor];
    // 从六位数值中找到RGB对应的位数并转换
    NSRange range;
    range.location = 0;
    range.length = 2;
    //R、G、B
    NSString *rString = [cString substringWithRange:range];
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f) green:((float) g / 255.0f) blue:((float) b / 255.0f) alpha:1.0f];
}

+(void)printAllViews:(UIView *)view
{
#if DEBUG
    doPrintViewAndSubviews(view, 0);
#endif
}

+ (UIImage*)createImageWithColor:(UIColor *)color;
{
    CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

+ (UIImage *)captureWithView:(UIView *)view;
{
    UIImage *ret = nil;
    if (SP_isKindOf(view, UIScrollView))
    {
        UIScrollView *scrollView = (UIScrollView *)view;
        UIGraphicsBeginImageContextWithOptions(scrollView.contentSize, scrollView.opaque, 0.0);
        {
            CGPoint savedContentOffset = scrollView.contentOffset;
            CGRect savedFrame          = scrollView.frame;

            scrollView.frame           = CGRectMake(0, 0, scrollView.contentSize.width, scrollView.contentSize.height);
            scrollView.contentOffset   = CGPointZero;

            [scrollView.layer renderInContext: UIGraphicsGetCurrentContext()];
            ret = UIGraphicsGetImageFromCurrentImageContext();

            scrollView.frame           = savedFrame;
            scrollView.contentOffset   = savedContentOffset;
        }
        UIGraphicsEndImageContext();
    }
    else
    {
        UIGraphicsBeginImageContextWithOptions(view.bounds.size, NO, 0.0);
        [view.layer renderInContext:UIGraphicsGetCurrentContext()];
        ret = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    return (ret);
}


+ (UIImage *)compressImage:(UIImage *)image toSize:(CGSize)size
{
    size.width = MAX(10, size.width);
    size.height = MAX(10, size.height);
    
    CGSize sz = image.size;
    float ss = (sz.height >= 10) ? (sz.width / sz.height) : 1;
    int w = MIN(size.height * ss, MIN(sz.width, size.width));
    int h = MIN(size.width / ss, MIN(sz.height, size.height));
    
    UIGraphicsBeginImageContext(CGSizeMake(w, h));
    [image drawInRect:CGRectMake(0, 0, w, h)];
    UIImage *compressImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return (compressImage);
}


- (NSString *)saveToCacheDisk;
{
    NSString *timestamp = [NSString stringWithFormat:@"%llu", (UInt64)([[NSDate date] timeIntervalSince1970] * 1000)];
    //    NSString *fileName = [kPath_Cache stringByAppendingPathComponent:timestamp];
    //    ASSERT(![[NSFileManager defaultManager] fileExistsAtPath:fileName]);
    //    [self saveToFile:fileName withJPEG:.8 orPNG:NO];
    return (timestamp);
}


+ (BOOL)saveImageToFileWith:(UIImage*)image path:(NSString *)filePath withJPEG:(float)compressionQuality orPNG:(BOOL)canPNG;
{
    BOOL ret = NO;
    if (filePath.length > 0) {
        NSData *data = UIImageJPEGRepresentation(image, compressionQuality);
        if (!data && canPNG) {
            data = UIImagePNGRepresentation(image);
        }
        if (data.length) {
          ret = [data writeToFile:filePath atomically:YES];
        }
    }
    return ret;
}


+ (BOOL)saveImageToDocumentWith:(UIImage*)image name:(NSString *)name
{
    if (!(name.length>0)) {
        return NO;
    }
    NSString *filepath = SP_Path_Document;
    [filepath stringByAppendingString:name];
    
    BOOL ret = [[self class] saveImageToFileWith:image path:filepath withJPEG:1 orPNG:YES];
    return ret;
}

+ (BOOL)savePNGImageToDocumentWith:(UIImage*)image name:(NSString *)name
{
    if (!(name.length>0)) {
        return NO;
    }
    NSString *filepath = SP_Path_Document;
    [filepath stringByAppendingString:name];
    
    BOOL ret = [[self class] saveImageToFileWith:image path:filepath withJPEG:0 orPNG:YES];
    return ret;
}


@end