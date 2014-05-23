//
//  PBMoreGame.h
//  PBADSDK
//
//  Created by CocoaChina_yangjh on 13-11-12.
//  Copyright (c) 2013年 CocoaChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "PBADRequest.h"
#import "PBRequestError.h"

typedef NS_ENUM(unsigned int, PBMoreGameStatus) {
    PBMoreGameStatus_Hide,
    PBMoreGameStatus_Showing,
    PBMoreGameStatus_Show,
    PBMoreGameStatus_Hiding,
};

@protocol PBMoreGameDelegate;

@interface PBMoreGame : NSObject

// 精品推荐当前状态
@property (nonatomic, readonly) PBMoreGameStatus status;
// 释放PBMoreGame前，必须将delegate设置为nil。
@property (nonatomic, assign) id <PBMoreGameDelegate> delegate;

// 精品推荐只有一个
+ (PBMoreGame *)sharedMoreGame;

/**
 *	@brief	加载精品推荐数据
 *
 *	@param 	pbRequest 	请求精品推荐时的参数
 */
- (void)loadMoreGame:(PBADRequest *)pbRequest;

/**
 *	@brief	显示精品推荐
 *
 *	@param 	scale 	显示比例
 */
- (void)showMoreGameWithScale:(CGFloat)scale;

/**
 *	@brief	显示精品推荐
 *
 *	@param 	rootView 	精品推荐的父视图
 *	@param 	scale 	显示比例
 */
- (void)showMoreGameOnRootView:(UIView *)rootView withScale:(CGFloat)scale;


/**
 *	@brief	关闭精品推荐
 */
- (void)closeMoreGame;

@end


@protocol PBMoreGameDelegate <NSObject>

@optional

// 精品推荐加载完成
- (void)pbMoreGameDidLoadAd:(PBMoreGame *)pbMoreGame;

// 精品推荐加载错误
- (void)pbMoreGame:(PBMoreGame *)pbMoreGame
loadAdFailureWithError:(PBRequestError *)requestError;

// 精品推荐打开完成
- (void)pbMoreGameDidPresentScreen:(PBMoreGame *)pbMoreGame;

// 精品推荐将要关闭
- (void)pbMoreGameWillDismissScreen:(PBMoreGame *)pbMoreGame;

// 精品推荐关闭完成
- (void)pbMoreGameDidDismissScreen:(PBMoreGame *)pbMoreGame;

@end
