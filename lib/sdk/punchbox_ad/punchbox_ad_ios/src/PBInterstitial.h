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

typedef NS_ENUM(unsigned int, PBInterstitialStatus) {
    PBInterstitialStatus_Hide,
    PBInterstitialStatus_Showing,
    PBInterstitialStatus_Show,
    PBInterstitialStatus_Hiding,
};

@protocol PBInterstitialDelegate;

@interface PBInterstitial : NSObject

// 关闭按钮显示前的倒计时时长（秒）
@property (nonatomic, assign) unsigned int countDown;
// 倒计时后是否自动关闭，默认为NO
@property (nonatomic, assign) BOOL autoCloseAfterCountDown;
// 是否显示关闭按钮，默认为YES
@property (nonatomic, assign) BOOL showCloseButton;
// 积分墙当前状态
@property (nonatomic, readonly) PBInterstitialStatus status;
// 弹出广告图片尺寸
@property (nonatomic, readonly) CGSize interstitialSize;
// PBInterstitial不再使用时，必须将delegate设置为nil。
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
 *	@brief	用弹出广告填充view
 *
 *	@param 	弹出广告的容器
 *
 *	@return	是否能展现出来
 */
- (BOOL)fillInterstitialInView:(UIView *)view;

/**
 *	@brief	关闭弹出广告
 */
- (void)closeInterstitial;

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

// 倒计时结束
- (void)pbInterstitialCountDownFinished:(PBInterstitial *)pbInterstitial;

// 弹出广告将要关闭
- (void)pbInterstitialWillDismissScreen:(PBInterstitial *)pbInterstitial;

// 弹出广告关闭完成
- (void)pbInterstitialDidDismissScreen:(PBInterstitial *)pbInterstitial;


@end
