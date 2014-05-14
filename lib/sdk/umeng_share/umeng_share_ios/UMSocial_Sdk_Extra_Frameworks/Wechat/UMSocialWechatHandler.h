//
//  ;
//  SocialSDK
//
//  Created by yeahugo on 13-8-6.
//  Copyright (c) 2013年 Umeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UMSocialWechatHandler : NSObject 

/**
 设置微信AppId和url地址
 
 @param appId 微信应用Id
 @param url 微信消息url地址
 
 */
+ (void)setWXAppId:(NSString *)appId url:(NSString *)url;

@end
