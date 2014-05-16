//
//  QQApi.h
//  QQApi
//
//  Created by Tencent on 5/1/12.
//  Copyright (c) 2012 Tencent. All rights reserved.
//

/** @file */

#import <Foundation/Foundation.h>
@class QQApiObject;
@class QQApiMessage;
@class QQApiAdItem;

typedef enum
{
    EQQAPISENDSUCESS = 0,
    EQQAPIQQNOTINSTALLED = 1,
    EQQAPIQQNOTSUPPORTAPI = 2,
    EQQAPIMESSAGETYPEINVALID = 3,
    EQQAPIMESSAGECONTENTNULL = 4,
    EQQAPIMESSAGECONTENTINVALID = 5,
    EQQAPIAPPNOTREGISTED = 6,
    EQQAPIAPPSHAREASYNC = 7,
    EQQAPISENDFAILD = -1,
    
    //qzone分享不支持text类型分享
    EQQAPIQZONENOTSUPPORTTEXT = 10000,
    //qzone分享不支持image类型分享
    EQQAPIQZONENOTSUPPORTIMAGE = 10001,
    
} QQApiSendResultCode;


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QQApi
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** \brief QQApi主要接口类。.
 
 可以通过其中的接口注册插件，发送、接收消息，打开QQ，测试QQ是否支持插件等
 */
@interface QQApi : NSObject

/**
 向QQ App发送消息
 @param message 待发送的消息对象
 
 @return 发送结果错误码
 */
+ (QQApiSendResultCode)sendMessage:(QQApiMessage *)message;

/**
 把URL反序列化成<code>QQApiMessage</code>对象，在AppDelegate的handleOpenURL中调用
 @return
     如果这是来自QQ的调用，一个QQApiMessage实例将被返回，否则返回nil。
 @note
     App应通过<code>QQApiMessage.type</code>来判断具体消息类型以作出进一步的处理。
 */
+ (QQApiMessage *)handleOpenURL:(NSURL *)url sourceApplication:(NSString *)source annotation:(id)annotation;

/**
 @see QQApi#handleOpenURL:sourceApplication:annotation:
 */
+ (QQApiMessage *)handleOpenURL:(NSURL *)url;

/**
 获取广告数据列表
 @return
     <code>QQApiAdItem</code>数组
 */
+ (NSArray*)getAdItemArray;



/**
 检测是否已安装QQ
 @return
     如果QQ已安装则返回TRUE，否则返回FALSE
 */
+ (BOOL)isQQInstalled;


//edit by peter
+(BOOL)appCanOpenURL:(NSDictionary *)params;
/**
 批量检测QQ号码是否在线
 */
+ (void)getQQUinOnlineStatues:(NSArray *)QQUins delegate:(id)target;

/**
 检测QQ是否支持API调用
 @return
     如果当前安装QQ版本支持API调用则返回TRUE，否则返回FALSE
 */
+ (BOOL)isQQSupportApi;

/**
 获取QQ下载地址
 
 如果App通过<code>QQApi#isQQInstalled</code>和<code>QQApi#isQQSupportApi</code>检测发现QQ没安装或当前版本QQ不支持API调用，可引导用户通过打开此链接下载最新版QQ。
 @return
     iPhoneQQ下载地址
 */
+ (NSString*)getQQInstallURL;

/**
 启动QQ
 @return
     成功返回TRUE，否则返回FALSE
 */
+ (BOOL)openQQApp;

+ (BOOL)isQQSupportApiForWallet;
+ (BOOL) checkQQApiURLMessage:(QQApiMessage *)message;
@end


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Message definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 消息类型定义
 */
enum
{
    // Message from QQ to Plugin app. Plugin app is required to display the data object attached in this message
	QQApiMessageTypeShowMessageFromQQRequest  = 0x01,///< QQ发给插件App的请求
    QQApiMessageTypeShowMessageFromQQResponse = 0x02,
    
    // Message from QQ to Plugin app. Plugin app is required to send data to QQ
	QQApiMessageTypeGetMessageFromQQRequest   = 0x03,
    QQApiMessageTypeGetMessageFromQQResponse  = 0x04,
    
    // Message from Plugin app to QQ. Plugin app is sharing data with QQ
    QQApiMessageTypeSendMessageToQQRequest    = 0x05,
    // Message from QQ to Plugin app.
    QQApiMessageTypeSendMessageToQQResponse   = 0x06,
    
    // Message from Plugin app to QZone,
    QQApiMessageTypeSendMessageToQQQZoneRequest = 0x07,
    
	QQApiMessageTypeReserved   = 0xF0
};

typedef NSUInteger QQApiMessageType;

// QQApiMessage
/** @brief API MESSAGE对象.
 
 用于在QQ和插件间发送消息、数据等。
 */
@interface QQApiMessage : NSObject<NSCoding>
/**
 消息类型.
 @note 参见QQApi.h中的 QQApiMessageType 定义
 */
@property (nonatomic) QQApiMessageType type;
/**
 */
@property (nonatomic, retain)QQApiObject* object;

/**
 初始化函数
 */
- (id)initWithObject:(QQApiObject*)obj andType:(QQApiMessageType)type;
/**
 通过ApiObject获取QQApiMessage对象
 @note 通过此接口获取的对象类型为APP发送到QQ的请求
 */
+ (QQApiMessage*) messageWithObject:(QQApiObject*)obj;
/**
 通过ApiObject及MessageType获取QQApiMessage对象
 */
+ (QQApiMessage*) messageWithObject:(QQApiObject*)obj andType:(QQApiMessageType)type;
@end


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Payload object definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QQApiObject control flags
enum
{
    kQQAPICtrlFlagQZoneShareOnStart = 0x01,
    kQQAPICtrlFlagQZoneShareForbid = 0x02,
    kQQAPICtrlFlagShareWithoutReturn3rdApp = 0x04,
};

// QQApiObject
/** \brief 所有在QQ及插件间发送的数据对象的根类。
 */
@interface QQApiObject : NSObject
@property(nonatomic,retain) NSString* title; ///< 标题，最长128个字符
@property(nonatomic,retain) NSString* description; ///<简要描述，最长512个字符

@property (nonatomic, assign) uint64_t cflag;

@end

// QQApiResultObject
/** \brief 用于请求回应的数据类型。
 <h3>可能错误码及描述如下:</h3>
<TABLE>
 <TR><TD>error</TD><TD>errorDescription</TD><TD>注释</TD></TR>
 <TR><TD>0</TD><TD>nil</TD><TD>成功</TD></TR>
 <TR><TD>-1</TD><TD>param error</TD><TD>参数错误</TD></TR>
 <TR><TD>-2</TD><TD>group code is invalid</TD><TD>该群不在自己的群列表里面</TD></TR>
 <TR><TD>-3</TD><TD>upload photo failed</TD><TD>上传图片失败</TD></TR>
 <TR><TD>-4</TD><TD>user give up the current operation</TD><TD>用户放弃当前操作</TD></TR>
 <TR><TD>-5</TD><TD>client internal error</TD><TD>客户端内部处理错误</TD></TR>
</TABLE>
 */
@interface QQApiResultObject : QQApiObject
@property(nonatomic,retain) NSString* error; ///<错误
@property(nonatomic,retain) NSString* errorDescription; ///<错误描述
@property(nonatomic,retain) NSString* extendInfo; ///<扩展信息
@end

// QQApiTextObject
/** \brief 文本对象
 */
@interface QQApiTextObject : QQApiObject
@property(nonatomic,retain)NSString* text; ///<文本内容，必填，最长1536个字符

-(id)initWithText:(NSString*)text; ///<初始化方法
+(id)objectWithText:(NSString*)text;///<工厂方法，获取一个QQApiTextObject对象.
@end

// QQApiURLObject
typedef enum QQApiURLTargetType{
	QQApiURLTargetTypeNotSpecified = 0x00,
	QQApiURLTargetTypeAudio   = 0x01,
	QQApiURLTargetTypeVideo   = 0x02,
	QQApiURLTargetTypeNews    = 0x03
}QQApiURLTargetType;

/** @brief URL对象类型。
 
 包括URL地址，URL地址所指向的目标类型及预览图像。
 */
@interface QQApiURLObject : QQApiObject
/**
 URL地址所指向的目标类型.
 @note 参见QQApi.h 中的 QQApiURLTargetType 定义.
 */
@property(nonatomic)QQApiURLTargetType targetContentType; 

@property(nonatomic,retain)NSURL* url; ///<URL地址,必填，最长512个字符
@property(nonatomic,retain)NSData* previewImageData;///<预览图像数据，最大1M字节
@property(nonatomic,retain)NSURL *previewImageURL;    ///<预览图像URL **预览图像数据与预览图像URL可二选一
@property(nonatomic,retain)NSArray *imageDataArray;    ///多张本地图片数据,最大不能超过10M
@property(nonatomic,retain)NSArray *imageUrlArray;     ///多张url图片url列表，**预览图像数据列表与预览图像URL列表可二选一

/**
 初始化方法
 */
-(id)initWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data targetContentType:(QQApiURLTargetType)targetContentType;
-(id)initWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL targetContentType:(QQApiURLTargetType)targetContentType;


-(id)initWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data imageDataArray:(NSArray*)imageDataArray targetContentType:(QQApiURLTargetType)targetContentType;
-(id)initWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL imageUrlArray:(NSArray*)imageUrlArray targetContentType:(QQApiURLTargetType)targetContentType;

/**
 工厂方法,获取一个QQApiURLObject对象
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data targetContentType:(QQApiURLTargetType)targetContentType;
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL targetContentType:(QQApiURLTargetType)targetContentType;

+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description imageDataArray:(NSArray*)imageDataArray targetContentType:(QQApiURLTargetType)targetContentType;
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description imageUrlArray:(NSArray*)imageUrlArray targetContentType:(QQApiURLTargetType)targetContentType;
@end

// QQApiExtendObject
/** @brief 扩展数据类型
 */
@interface QQApiExtendObject : QQApiObject
@property(nonatomic,retain) NSData* data;///<具体数据内容，必填，最大5M字节
@property(nonatomic,retain) NSData* previewImageData;///<预览图像，最大1M字节
@property(nonatomic,retain) NSArray *imageDataArray;    ///多张本地图片数据,最大不能超过10M

/**
 初始化方法
 @param data 数据内容
 @param previewImageData 用于预览的图片
 @param title 标题
 @param description 此对象，分享的描述
 */
- (id)initWithData:(NSData*)data previewImageData:(NSData*)previewImageData title:(NSString*)title description:(NSString*)description;


/**
 初始化方法
 @param data 数据内容
 @param title 标题
 @param description 此对象，分享的描述
 @param imageDataArray 发送的多张图片队列
 */
- (id)initWithData:(NSData *)data title:(NSString *)title description:(NSString *)description imageDataArray:(NSArray *)imageDataArray;

/**
 helper方法获取一个autorelease的<code>QQApiExtendObject</code>对象
 @param data 数据内容
 @param previewImageData 用于预览的图片
 @param title 标题
 @param description 此对象，分享的描述
 @return
     一个自动释放的<code>QQApiExtendObject</code>实例
 */
+ (id)objectWithData:(NSData*)data previewImageData:(NSData*)previewImageData title:(NSString*)title description:(NSString*)description;


/**
 helper方法获取一个autorelease的<code>QQApiExtendObject</code>对象
 @param data 数据内容
 @param previewImageData 用于预览的图片
 @param title 标题
 @param description 此对象，分享的描述
 @param imageDataArray 发送的多张图片队列
 @return
 一个自动释放的<code>QQApiExtendObject</code>实例
 */
+ (id)objectWithData:(NSData*)data previewImageData:(NSData*)previewImageData title:(NSString*)title description:(NSString*)description imageDataArray:(NSArray*)imageDataArray;


@end

// QQApiImageObject
/** @brief 图片对象
     用于分享图片内容的对象，是一个指定为图片类型的<code>QQApiExtendObject</code>
 */
@interface QQApiImageObject : QQApiExtendObject

@end

// QQApiAudioObject
/** @brief 音频URL对象
     用于分享目标内容为音频的URL的对象
 */
@interface QQApiAudioObject : QQApiURLObject

@property (nonatomic, retain) NSURL *flashURL;      ///<音频URL地址，最长512个字符

/**
 获取一个autorelease的<code>QQApiAudioObject</code>
 @param url 音频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param data 分享内容的预览图像
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data;

/**
 获取一个autorelease的<code>QQApiAudioObject</code>
 @param url 音频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param previewURL 分享内容的预览图像URL
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL;

/**
 获取一个autorelease的<code>QQApiAudioObject</code>
 @param url 音频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param data 分享内容的预览图像
 @param imageDataArray 分享内容的预览图像列表
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data imageDataArray:(NSArray*)imageDataArray;

/**
 获取一个autorelease的<code>QQApiAudioObject</code>
 @param url 音频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param previewURL 分享内容的预览图像URL
 @param imageUrlArray 分享内容的预览图像URL列表
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL imageUrlArray:(NSArray*)imageUrlArray;

@end

// QQApiVideoObject
/** @brief 视频URL对象
     用于分享目标内容为视频的URL的对象
 */
@interface QQApiVideoObject : QQApiURLObject

@property (nonatomic, retain) NSURL *flashURL;      ///<视频URL地址，最长512个字符

/**
 获取一个autorelease的<code>QQApiVideoObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param data 分享内容的预览图像
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data;

/**
 获取一个autorelease的<code>QQApiVideoObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param previewURL 分享内容的预览图像URL
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL;

/**
 获取一个autorelease的<code>QQApiVideoObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param data 分享内容的预览图像
 @param imageDataArray 分享内容的预览图像列表
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data imageDataArray:(NSArray*)imageDataArray;

/**
 获取一个autorelease的<code>QQApiVideoObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param previewURL 分享内容的预览图像URL
 @param previewURL 分享内容的预览图像URL列表
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL imageUrlArray:(NSArray*)imageUrlArray;

@end

// QQApiNewsObject
/** @brief 新闻URL对象
     用于分享目标内容为新闻的URL的对象
 */
@interface QQApiNewsObject : QQApiURLObject
/**
 获取一个autorelease的<code>QQApiNewsObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param data 分享内容的预览图像
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data;

/**
 获取一个autorelease的<code>QQApiNewsObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param previewURL 分享内容的预览图像URL
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL;

/**
 获取一个autorelease的<code>QQApiNewsObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param data 分享内容的预览图像
 @param imageDataArray 分享内容的预览图像列表
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageData:(NSData*)data imageDataArray:(NSArray*)imageDataArray;


/**
 获取一个autorelease的<code>QQApiNewsObject</code>
 @param url 视频内容的目标URL
 @param title 分享内容的标题
 @param description 分享内容的描述
 @param previewURL 分享内容的预览图像URL
 @param imageUrlArray 分享内容的预览图url列表
 @note 如果url为空，调用<code>QQApi#sendMessage:</code>时将返回FALSE
 */
+(id)objectWithURL:(NSURL*)url title:(NSString*)title description:(NSString*)description previewImageURL:(NSURL*)previewURL imageUrlArray:(NSArray*)imageUrlArray;

@end

// QQApiPayObject
/** \brief 支付对象
 */
@interface QQApiPayObject : QQApiObject
@property(nonatomic,retain)NSString* OrderNo; ///<支付订单号，必填

-(id)initWithOrderNo:(NSString*)OrderNo; ///<初始化方法
+(id)objectWithOrderNo:(NSString*)OrderNo;///<工厂方法，获取一个QQApiPayObject对象.
@end

// QQApiCommonContentObject;
/** @brief 通用模板类型对象
    用于分享一个固定显示模板的图文混排对象
    @note 图片列表和文本列表不能同时为空
*/
@interface QQApiCommonContentObject : QQApiObject
/**
 预定义的界面布局类型
 */
@property(nonatomic,assign) unsigned int layoutType;
@property(nonatomic,assign) NSData* previewImageData;///<预览图
@property(nonatomic,retain) NSArray* textArray;///<文本列表
@property(nonatomic,retain) NSArray* pictureDataArray;///<图片列表
+(id)objectWithLayoutType:(int)layoutType textArray:(NSArray*)textArray pictureArray:(NSArray*)pictureArray previewImageData:(NSData*)data;
/**
 将一个NSDictionary对象转化为QQApiCommomContentObject，如果无法转换，则返回空
 */
+(id)objectWithDictionary:(NSDictionary*)dic;
-(NSDictionary*)toDictionary;
@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ad item object definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief 广告数据对象
 */
@interface QQApiAdItem : NSObject
@property(nonatomic,retain) NSString* title; ///<名称
@property(nonatomic,retain) NSString* description;///<描述
@property(nonatomic,retain) NSData* imageData;///<广告图片
@property(nonatomic,retain) NSURL* target;///<广告目标链接
@end

// QQApiWPAObject
/** \brief 发起WPA对象
 */
@interface QQApiWPAObject : QQApiObject
@property(nonatomic,retain)NSString* uin; ///<想要对话的QQ号

-(id)initWithUin:(NSString*)uin; ///<初始化方法
+(id)objectWithUin:(NSString*)uin;///<工厂方法，获取一个QQApiWPAObject对象.
@end
