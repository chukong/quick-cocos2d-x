//
//  UMSocialControllerServiceComment.h
//  SocialSDK
//
//  Created by yeahugo on 12-12-7.
//  Copyright (c) 2012年 Umeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UMSocialControllerService.h"

/**
 用此类的方法可以得到分享的有关UI对象，例如分享列表、评论列表、分享编辑页、分享授权页、个人中心页面等。返回都是`UINavigationController`对象，建议把这个对象present到你要添加到的`UIViewController`上
 */
@interface UMSocialControllerServiceComment : UMSocialControllerService

/**
 返回一个以[UMSocialData defaultData]来做初始化参数的`UMSocialControllerServiceComment`对象
 
 @return `UMSocialControllerServiceComment`的默认初始化对象
 */
+(UMSocialControllerServiceComment *)defaultControllerService;

/**
 评论列表页面，评论列表页面包括各评论详情、评论编辑
 
 @return `UINavigationController`对象
 */
- (UINavigationController *)getSocialCommentListController;

@end
