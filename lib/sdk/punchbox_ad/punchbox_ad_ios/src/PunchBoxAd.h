//
//  PunchBoxAd.h
//  PunchBoxAd
//
//  Created by CocoaChina_yangjh on 13-10-15.
//  Copyright (c) 2013年 CocoaChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "PBADRequest.h"
#import "PBRequestError.h"
#import "PBBannerView.h"
#import "PBInterstitial.h"
#import "PBMoreGame.h"
#import "PBOfferWall.h"
#import "PBOfferWallData.h"


#define SDK_Version  @"4.2.1"


// 该类是为开发者提供的展示Banner、精品推荐、弹出广告的快捷调用，即一句代码展现广告
@interface PunchBoxAd : NSObject

/**
 *	@brief	开启会话，在程序一启动的时候调用
 *          建议放在协议方法application:didFinishLaunchingWithOptions:中调用
 *
 *	@param 	publisherID 	publisherID
 */
+ (void)startSession:(NSString *)publisherID;

/**
 *	@brief	用于积分墙广告，开发者设置自己的用户系统信息，长度限制64（不建议使用中文符号）
 *
 *	@param 	userInfo 	用户信息，可设置用户ID等信息
 */
+ (void)setUserInfo:(NSString *)userInfo;

/**
 *	@brief	获取SDK版本号
 *
 *	@return	SDK版本号
 */
+ (NSString *)sdkVersion;


#pragma mark - Banner

/**
 *	@brief	快捷显示Banner广告
 *
 *	@param 	superView 	父视图
 *	@param 	position 	Banner左上角所在位置
 */
+ (void)showBannerViewOn:(UIView *)superView atPosition:(CGPoint)position;

/**
 *	@brief	移除快捷方式创建的Banner广告
 */
+ (void)removeBannerView;


#pragma mark - 弹出广告

/**
 *	@brief	快捷显示弹出广告
 *
 *	@param 	scale 	图片显示比例
 */
+ (void)showInterstitialWithScale:(CGFloat)scale;

/**
 *	@brief	快捷显示弹出广告
 *
 *	@param 	rootView 	弹出广告的父视图
 *	@param 	scale 	图片显示比例
 */
+ (void)showInterstitialOnRootView:(UIView *)rootView withScale:(CGFloat)scale;

/**
 *	@brief	关闭弹出广告
 */
+ (void)closeInterstitial;


#pragma mark - 精品推荐

/**
 *	@brief	显示精品推荐动画按钮
 *
 *	@param 	frameButton 	按钮位置。默认按钮尺寸：iPhone为55，iPad为110
 *	@param 	superViewButton 	按钮的父视图
 *	@param 	showBadge 	是否显示徽章
 *	@param 	animationImages 	按钮的帧图片
 *	@param 	duration 	帧间隔时间
 */
+ (void)showMoreGameButton:(CGRect)frameButton andBadge:(BOOL)showBadge onView:(UIView *)superViewButton
       withAnimationImages:(NSArray *)animationImages duration:(NSTimeInterval)duration;

/**
 *	@brief	移除精品推荐动画按钮
 */
+ (void)removeMoreGameButton;

@end

