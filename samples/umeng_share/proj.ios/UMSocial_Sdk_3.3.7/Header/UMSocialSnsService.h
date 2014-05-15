//
//  UMSocialSnsService.h
//  SocialSDK
//
//  Created by Jiahuan Ye on 13-1-8.
//  Copyright (c) 2013年 Umeng. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol WXApiDelegate ;
@protocol UMSocialUIDelegate;

/*
 实现快速分享，类方法传入相应的参数，既可以弹出分享列表。现在提供两种列表样式。
 */
@interface UMSocialSnsService : NSObject

/**
 当应用从后台唤起时，应调用此方法，需要完成退出当前登录状态的功能
 
 */
+(void)applicationDidBecomeActive;

/**
 处理app的URL方法
 
 如果你要处理自己的url，你可以把这个方法的实现，复制到你的代码中：
 
 if ([url.description hasPrefix:@"sina"]) {
    return (BOOL)[[UMSocialSnsService sharedInstance] performSelector:@selector(handleSinaSsoOpenURL:) withObject:url];
 }
 else if([url.description hasPrefix:@"wx"]){
    return [WXApi handleOpenURL:url delegate:(id <WXApiDelegate>)[UMSocialSnsService sharedInstance]];
 }
 
 @param url 传入的url
 
 @return wxApiDelegate 实现微信代理对象
 */
+(BOOL)handleOpenURL:(NSURL *)url wxApiDelegate:(id<WXApiDelegate>)wxApiDelegate;

///---------------------------------------
/// @name 快速分享
///---------------------------------------

/**
 弹出一个分享列表的UITableViewController
 
 @param controller 在该controller弹出分享列表的UIActionSheet
 @param appKey 友盟appKey
 @param shareText  分享编辑页面的内嵌文字
 @param shareImage 分享内嵌图片,用户可以在编辑页面删除
 @param snsNames 你要分享到的sns平台类型，该NSArray值是`UMSocialSnsPlatformManager.h`定义的平台名的字符串常量，有UMShareToSina，UMShareToTencent，UMShareToRenren，UMShareToDouban，UMShareToQzone，UMShareToEmail，UMShareToSms等
 @param delegate 实现分享完成后的回调对象，如果不关注分享完成的状态，可以设为nil
 */
+(void)presentSnsController:(UIViewController *)controller
                     appKey:(NSString *)appKey
                  shareText:(NSString *)shareText
                 shareImage:(UIImage *)shareImage
            shareToSnsNames:(NSArray *)snsNames
                   delegate:(id <UMSocialUIDelegate>)delegate;

/**
 弹出一个分享列表的类似iOS6的UIActivityViewController控件
 
 @param controller 在该controller弹出分享列表的UIActionSheet
 @param appKey 友盟appKey
 @param shareText  分享编辑页面的内嵌文字
 @param shareImage 分享内嵌图片,用户可以在编辑页面删除
 @param snsNames 你要分享到的sns平台类型，该NSArray值是`UMSocialSnsPlatformManager.h`定义的平台名的字符串常量，有UMShareToSina，UMShareToTencent，UMShareToRenren，UMShareToDouban，UMShareToQzone，UMShareToEmail，UMShareToSms等
 @param delegate 实现分享完成后的回调对象，如果不关注分享完成的状态，可以设为nil
 */
+(void)presentSnsIconSheetView:(UIViewController *)controller
                        appKey:(NSString *)appKey
                     shareText:(NSString *)shareText
                    shareImage:(UIImage *)shareImage
               shareToSnsNames:(NSArray *)snsNames
                      delegate:(id <UMSocialUIDelegate>)delegate;

/**
 得到单例对象的类方法
 
 @return `UMSocialSnsService`的单例对象
 */
+ (UMSocialSnsService *)sharedInstance;

@end
