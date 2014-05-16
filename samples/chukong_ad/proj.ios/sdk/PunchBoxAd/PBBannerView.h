//
//  PBBannerView.h
//  PBADSDK
//
//  Created by cassano on 13-10-14.
//  Copyright (c) 2013年 CocoaChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PBADRequest.h"
#import "PBRequestError.h"

@protocol PBBannerViewDelegate;

// iPhone 和 iPod Touch Banner广告大小。目前只有一种 320x50.
// iPad Banner广告大小。目前只有一种 728x90.
@interface PBBannerView : UIView

@property (nonatomic, assign) id <PBBannerViewDelegate> delegate;

/**
 *	@brief	加载Banner广告
 *
 *	@param 	pbRequest 	请求Banner广告时的参数
 */
- (void)loadRequest:(PBADRequest *)pbRequest;


@end


@protocol PBBannerViewDelegate <NSObject>

@optional

// 收到Banner广告
- (void)pbBannerViewDidReceiveAd:(PBBannerView *)pbBannerView;

// Banner广告数据错误
- (void)pbBannerView:(PBBannerView *)pbBannerView
      receiveAdError:(PBRequestError *)requestError;

// 将要展示Banner广告
- (void)pbBannerViewWillPresentScreen:(PBBannerView *)pbBannerView;

// 移除Banner广告
- (void)pbBannerViewDidDismissScreen:(PBBannerView *)pbBannerView;

@end
