///
/// \file QQApiInterfaceObject.h
/// \brief QQApiInterface所依赖的请求及应答消息对象封装帮助类
///
/// Created by Tencent on 12-5-15.
/// Copyright (c) 2012年 Tencent. All rights reserved.
///

#import "QQApi.h"

/**
 QQApi请求消息类型
 */
enum QQApiInterfaceReqType
{
    EGETMESSAGEFROMQQREQTYPE = 0,   ///< 手Q -> 第三方应用，请求第三方应用向手Q发送消息
    ESENDMESSAGETOQQREQTYPE = 1,    ///< 第三方应用 -> 手Q，第三方应用向手Q分享消息
    ESHOWMESSAGEFROMQQREQTYPE = 2   ///< 手Q -> 第三方应用，请求第三方应用展现消息中的数据
};

/**
 QQApi应答消息类型
 */
enum QQApiInterfaceRespType
{
    ESHOWMESSAGEFROMQQRESPTYPE = 0, ///< 第三方应用 -> 手Q，第三方应用应答消息展现结果
    EGETMESSAGEFROMQQRESPTYPE = 1,  ///< 第三方应用 -> 手Q，第三方应用回应发往手Q的消息
    ESENDMESSAGETOQQRESPTYPE = 2    ///< 手Q -> 第三方应用，手Q应答处理分享消息的结果
};

/**
 QQApi请求消息基类
 */
@interface QQBaseReq : NSObject

/** 请求消息类型，参见\ref QQApiInterfaceReqType */
@property (nonatomic, assign) int type;

@end

/**
 QQApi应答消息基类
 */
@interface QQBaseResp : NSObject

/** 请求处理结果 */
@property (nonatomic, copy) NSString* result;

/** 具体错误描述信息 */
@property (nonatomic, copy) NSString* errorDescription;

/** 应答消息类型，参见\ref QQApiInterfaceRespType */
@property (nonatomic, assign) int type;

/** 扩展信息 */
@property (nonatomic, assign) NSString* extendInfo;

@end

/**
 GetMessageFromQQReq请求帮助类
 */
@interface GetMessageFromQQReq : QQBaseReq

/**
 创建一个GetMessageFromQQReq请求实例
 */
+ (GetMessageFromQQReq *)req;

@end

/**
 GetMessageFromQQResp应答帮助类
 */
@interface GetMessageFromQQResp : QQBaseResp

/**
 创建一个GetMessageFromQQResp应答实例
 \param message 具体分享消息实例
 \return 新创建的GetMessageFromQQResp应答实例
 */
+ (GetMessageFromQQResp *)respWithContent:(QQApiObject *)message;

/** 具体分享消息 */
@property (nonatomic, retain) QQApiObject *message;

@end

/**
 SendMessageToQQReq请求帮助类
 */
@interface SendMessageToQQReq : QQBaseReq

/**
 创建一个SendMessageToQQReq请求实例
 \param message 具体分享消息实例
 \return 新创建的SendMessageToQQReq请求实例
 */
+ (SendMessageToQQReq *)reqWithContent:(QQApiObject *)message;

/** 具体分享消息 */
@property (nonatomic, retain) QQApiObject *message;

@end

/**
 SendMessageToQQResp应答帮助类
 */
@interface SendMessageToQQResp : QQBaseResp

/**
 创建一个SendMessageToQQResp应答实例
 \param result 请求处理结果
 \param errDesp 具体错误描述信息
 \param extendInfo 扩展信息
 \return 新创建的SendMessageToQQResp应答实例
 */
+(SendMessageToQQResp*) respWithResult:(NSString *)result errorDescription:(NSString *)errDesp extendInfo:(NSString*)extendInfo;

@end

/**
 ShowMessageFromQQReq请求帮助类
 */
@interface ShowMessageFromQQReq : QQBaseReq

/**
 创建一个ShowMessageFromQQReq请求实例
 \param message 具体待展现消息实例
 \return 新创建的ShowMessageFromQQReq请求实例
 */
+ (ShowMessageFromQQReq *)reqWithContent:(QQApiObject *)message;

/** 具体待展现消息 */
@property (nonatomic, retain) QQApiObject *message;

@end

/**
 ShowMessageFromQQResp应答帮助类
 */
@interface ShowMessageFromQQResp : QQBaseResp

/**
 创建一个ShowMessageFromQQResp应答实例
 \param result 展现消息结果
 \param errDesp 具体错误描述信息
 \return 新创建的ShowMessageFromQQResp应答实例
 */
+ (ShowMessageFromQQResp *)respWithResult:(NSString *)result errorDescription:(NSString *)errDesp;

@end

