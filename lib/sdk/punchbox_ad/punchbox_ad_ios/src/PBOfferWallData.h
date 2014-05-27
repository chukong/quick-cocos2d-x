//
//  PBOfferWallData.h
//  PBADSDK
//
//  Created by CocoaChina_yangjh on 14-5-7.
//  Copyright (c) 2014年 CocoaChina. All rights reserved.
//

#import <Foundation/Foundation.h>

// 积分墙项
@interface PBOfferWallItem : NSObject
@property (nonatomic, readonly) NSString *coins;
@property (nonatomic, readonly) NSString *unit;
@property (nonatomic, readonly) NSString *iconUrl;
@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) NSString *content;
@end
// 积分墙任务项
@interface PBOfferWallTaskItem : NSObject
@property (nonatomic, readonly) NSString *coins;
@property (nonatomic, readonly) NSString *unit;
@property (nonatomic, readonly) NSString *taskUrl;
@property (nonatomic, readonly) unsigned int taskStatus; // 0：未领取；1：任务进行中；2：任务已完成
@property (nonatomic, readonly) NSString *taskName;
@property (nonatomic, readonly) NSString *taskContent;
@end
// 积分墙项详情
@interface PBOfferWallItemDetail : NSObject
@property (nonatomic, readonly) PBOfferWallItem *itemInfo;
@property (nonatomic, readonly) NSArray *taskList; // 列表中的元素为PBOfferWallTaskItem类型
@end


@protocol PBOfferWallDataDelegate;

@interface PBOfferWallData : NSObject

@property (nonatomic, assign) id <PBOfferWallDataDelegate> delegate;

+ (PBOfferWallData *)sharedInstance;

// 获取积分墙列表
- (void)getOfferWallList;

// 获取积分墙项详情
- (void)getOfferWallItemDetailOf:(PBOfferWallItem *)offerWallItem;

// 领取任务
- (void)clickOfferWallTaskItem:(PBOfferWallTaskItem *)taskItem;

@end


@protocol PBOfferWallDataDelegate <NSObject>

// 积分墙列表获取失败
- (void)pbOfferWallData:(PBOfferWallData *)offerWallData offerWallListError:(NSError *)error;

// 积分墙列表获取成功，offerWallList中的元素为PBOfferWallItem类型
- (void)pbOfferWallData:(PBOfferWallData *)offerWallData offerWallList:(NSArray *)offerWallList;

// 积分墙任务详情获取失败
- (void)pbOfferWallData:(PBOfferWallData *)offerWallData offerWallDetailError:(NSError *)error
                   with:(PBOfferWallItem *)offerWallItem;

// 积分墙任务详情获取成功
- (void)pbOfferWallData:(PBOfferWallData *)offerWallData
        offerWallDetail:(PBOfferWallItemDetail *)offerWallItemDetail;

@end
