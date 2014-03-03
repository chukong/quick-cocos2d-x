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


// 该类是为开发者提供的展示Banner、精品推荐、弹出广告的快捷调用
@interface PunchBoxAd : NSObject

/**
 *	@brief	开启会话，在程序一启动的时候调用
 *          建议放在协议方法application:didFinishLaunchingWithOptions:中调用
 *
 *	@param 	publisherID 	publisherID
 */
+ (void)startSession:(NSString *)publisherID;

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
 *	@param 	position 	Banner显示位置
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
 *	@param 	orientationSupported 	支持的方向
 */
+ (void)showInterstitialWithScale:(CGFloat)scale
          andOrientationSupported:(PBOrientationSupported)orientationSupported;

/**
 *	@brief	快捷显示弹出广告
 *
 *	@param 	rootView 	弹出广告的父视图
 *	@param 	scale 	图片显示比例
 *	@param 	orientationSupported 	支持的方向
 */
+ (void)showInterstitialOnRootView:(UIView *)rootView withScale:(CGFloat)scale
           andOrientationSupported:(PBOrientationSupported)orientationSupported;

/**
 *	@brief	关闭弹出广告
 */
+ (void)closeInterstitial;


#pragma mark - 精品推荐

/**
 *	@brief	快捷显示精品推荐
 *
 *	@param 	scale 	精品推荐显示比例
 *	@param 	orientationSupported 	支持的方向
 */
+ (void)showMoreGameWithScale:(CGFloat)scale
      andOrientationSupported:(PBOrientationSupported)orientationSupported;

/**
 *	@brief	快捷显示精品推荐
 *
 *	@param 	rootView 	精品推荐的父视图
 *	@param 	scale 	精品推荐显示比例
 *	@param 	orientationSupported 	支持的方向
 */
+ (void)showMoreGameOnRootView:(UIView *)rootView withScale:(CGFloat)scale
       andOrientationSupported:(PBOrientationSupported)orientationSupported;

/**
 *	@brief	关闭精品推荐
 */
+ (void)closeMoreGame;

/**
 *	@brief	显示精品推荐动画按钮
 *
 *	@param 	frameButton 	按钮位置。默认按钮尺寸：iPhone为55，iPad为110
 *	@param 	superViewButton 	按钮的父视图
 *	@param 	showBadge 	是否显示徽章
 *	@param 	animationImages 	按钮的帧图片
 *	@param 	duration 	帧间隔时间
 *	@param 	target 	按钮响应的target
 *	@param 	action 	按钮响应的action
 */
+ (void)showMoreGameButton:(CGRect)frameButton andBadge:(BOOL)showBadge onView:(UIView *)superViewButton
       withAnimationImages:(NSArray *)animationImages duration:(NSTimeInterval)duration
                 andTarget:(id)target action:(SEL)action;

/**
 *	@brief	移除精品推荐动画按钮
 */
+ (void)removeMoreGameButton;

@end

