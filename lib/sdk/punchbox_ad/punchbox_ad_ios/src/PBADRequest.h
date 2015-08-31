//
//  PBADRequest.h
//  PBADSDK
//
//  Created by CocoaChina_yangjh on 13-11-4.
//  Copyright (c) 2013年 CocoaChina. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PBADRequest : NSObject

@property (nonatomic, retain) NSString *placementID;  // 广告位ID
@property (nonatomic, assign) NSUInteger requestInterval;  // 广告请求间隔，单位为秒。使用后台参数或系统默认时，设置为0。最小值30，只在Banner有效
@property (nonatomic, assign) NSUInteger displayTime;  // 广告展现时长，单位为秒。使用后台参数或系统默认时，设置为0。最小值30，只在Banner有效

+ (id)request;

+ (id)requestWithRequestInterval:(NSUInteger)requestInterval
                  andDisplayTime:(NSUInteger)displayTime;

@end
