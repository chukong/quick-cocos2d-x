//
//  PBRequestError.h
//  PBADSDK
//
//  Created by CocoaChina_yangjh on 13-11-1.
//  Copyright (c) 2013年 CocoaChina. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, PBRequestErrorCode) {
    // 1000~1999 为服务器端错误
    PBRequestErrorCode_Success,
    PBRequestErrorCode_NoServices = 1000,    // 服务未开启
    PBRequestErrorCode_HttpMethodError,      // http方法错误
    PBRequestErrorCode_InvalidParameter,     // 参数错误
    PBRequestErrorCode_InvalidPostData,      // POST数据错误
    PBRequestErrorCode_EventSwitchClosed,    // 事件关闭
    PBRequestErrorCode_PunchBoxClosed = 1005,// PunchBox关闭
    PBRequestErrorCode_NoAdGroup,            // 无广告适合的广告组
    PBRequestErrorCode_NoAdIdea,             // 无广告创意可用
    PBRequestErrorCode_NoIdeaURL,            // 创意URL不存在
    PBRequestErrorCode_NoAdTemplate,         // 广告模板不存在
    PBRequestErrorCode_AppClosed = 1010,     // App关闭
    PBRequestErrorCode_VersionClosed,        // App版本关闭
    PBRequestErrorCode_UnsupportedAdType,    // 未支持的广告类型
    PBRequestErrorCode_FrequentRequest,      // 频繁的请求
    PBRequestErrorCode_RegionSwitchClosed,   // 地域开关关闭
    PBRequestErrorCode_Cheat = 1015,         // 作弊
    // 2000~2999为SDK错误码
    PBRequestErrorCode_NetError = 2001,      // 网络错误
    PBRequestErrorCode_NoData,               // 服务器返回内容为空
    PBRequestErrorCode_Unknown = 9999,       // 未知错误
};

@interface PBRequestError : NSError

@end
