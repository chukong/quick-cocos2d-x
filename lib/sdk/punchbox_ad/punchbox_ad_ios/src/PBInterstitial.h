//
//  PBInterstitial.h
//  PBADSDK
//
//  Created by CocoaChina_yangjh on 13-10-28.
//  Copyright (c) 2013年 CocoaChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "PBADRequest.h"
#import "PBRequestError.h"

@protocol PBInterstitialDelegate;

@interface PBInterstitial : NSObject

// 是否准备好
@property (nonatomic, readonly) BOOL isReady;
// 关闭按钮显示前的倒计时时长（秒）
@property (nonatomic, assign) NSUInteger countDown;
// 倒计时后是否自动关闭
@property (nonatomic, assign) BOOL autoCloseAfterCountDown;
// 支持的方向
@property (nonatomic, assign) PBOrientationSupported orientationSupported;
// 释放PBInterstitial前，必须将delegate设置为nil。
@property (nonatomic, assign) id <PBInterstitialDelegate> delegate;

// 弹出广告只有一个
+ (PBInterstitial *)sharedInterstitial;

/**
 *	@brief	加载弹出广告数据
 *
 *	@param 	pbRequest 	请求弹出广告时的参数
 */
- (void)loadInterstitial:(PBADRequest *)pbRequest;

/**
 *	@brief	显示弹出广告
 *
 *	@param 	scale 	显示比例
 *
 *	@return	是否能展现出来
 */
- (BOOL)showInterstitialWithScale:(CGFloat)scale;

/**
 *	@brief	显示弹出广告
 *
 *	@param 	rootView 	弹出广告的父视图
 *	@param 	scale 	显示比例
 *
 *	@return	是否能展现出来
 */
- (BOOL)showInterstitialOnRootView:(UIView *)rootView withScale:(CGFloat)scale;

/**
 *	@brief	关闭弹出广告
 */
- (void)closeInterstitial;

/**
 *	@brief	用弹出广告填充view
 *
 *	@param 	弹出广告的容器
 */
- (void)fillInterstitialInView:(UIView *)view;

/**
 *	@brief	取消填充
 */
- (void)cancelFillInterstitial;

@end


@protocol PBInterstitialDelegate <NSObject>

@optional

// 弹出广告加载完成
- (void)pbInterstitialDidLoadAd:(PBInterstitial *)pbInterstitial;

// 弹出广告加载错误
- (void)pbInterstitial:(PBInterstitial *)pbInterstitial
loadAdFailureWithError:(PBRequestError *)requestError;

// 弹出广告打开完成
- (void)pbInterstitialDidPresentScreen:(PBInterstitial *)pbInterstitial;

// 弹出广告将要关闭
- (void)pbInterstitialWillDismissScreen:(PBInterstitial *)pbInterstitial;

// 弹出广告关闭完成
- (void)pbInterstitialDidDismissScreen:(PBInterstitial *)pbInterstitial;

@end
