
#import "UmengShareSDK.h"
#import "UMSocial.h"
#import "UMSocialWechatHandler.h"
#import "UMSocialQQHandler.h"

#import "CCLuaBridge.h"

static UmengShareSDK *gUmengShareInstance = nil;
static int functionId = 0;

@interface UmengShareSDK() <UIApplicationDelegate, UMSocialUIDelegate> {
    UIViewController *viewControl;
    NSString *UmengAppKey;
    NSString *WXAppId;
    NSString *QQAppId;
    NSString *QQAppKey;
    NSString *webUrl;
    NSMutableArray *arraySns;
}

- (UIViewController*) getUIView;
- (int) getIndex:(NSString *)platform;
- (NSString *) getShareSns:(NSString*)platform;
+ (void) callListener:(NSString *)result;

@end

@implementation UmengShareSDK

- (id) init {
    if (self = [super init]) {
        arraySns = [[NSMutableArray alloc] init];
    }
    return (self);
}

- (void) dealloc {
    if (nil != arraySns) {
        [arraySns release];
    }
    
    [super dealloc];
}

- (void) setUIView:(UIViewController*) view {
    viewControl = view;
    
    #warning 替换为自己的appid
    UmengAppKey = @"5211818556240bc9ee01db2f";
    WXAppId = @"wxd9a39c7122aa6516";
    QQAppId = @"100424468";
    QQAppKey = @"c7394704798a158208a74ab60104f0ba";
    webUrl = @"http://quick.cocoachina.com/";
    
    //打开调试log的开关
    [UMSocialData openLog:YES];
    
    //如果你要支持不同的屏幕方向，需要这样设置，否则在iPhone只支持一个竖屏方向
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskAll];
    
    //设置友盟社会化组件appkey
    [UMSocialData setAppKey:UmengAppKey];
    
    //设置微信AppId，设置分享url，默认使用友盟的网址
    [UMSocialWechatHandler setWXAppId:WXAppId url:webUrl];
    
    //打开新浪微博的SSO开关
    [UMSocialConfig setSupportSinaSSO:YES];
    
    //设置分享到QQ空间的应用Id，和分享url 链接
    [UMSocialQQHandler setQQWithAppId:QQAppId appKey:QQAppKey url:webUrl];
    [UMSocialQQHandler setSupportQzoneSSO:YES];
}

- (UIViewController*) getUIView {
    return viewControl;
}

+ (UmengShareSDK*) getInstance {
    
    @synchronized(self) {
        if (nil == gUmengShareInstance) {
            gUmengShareInstance = [[UmengShareSDK alloc] init];
        }
    }
    
    return gUmengShareInstance;
}

- (int) getIndex:(NSString *)platform {
    int i;
    NSString* value;
    for (i = 0; i < arraySns.count; i++)
    {
        value = [arraySns objectAtIndex:i];
        if (NSOrderedSame == [value compare:platform]) {
            return i;
        }
    }
    return -1;
}

- (NSString *) getShareSns:(NSString*)platform {
    if (NSOrderedSame == [@"SINA" compare:platform]) {
        return UMShareToSina;
    } else if (NSOrderedSame == [@"QZONE" compare:platform]) {
        return UMShareToQzone;
    } else if (NSOrderedSame == [@"QQ" compare:platform]) {
        return UMShareToQQ;
    } else if (NSOrderedSame == [@"RENREN" compare:platform]) {
        return UMShareToRenren;
    } else if (NSOrderedSame == [@"WEIXIN" compare:platform]) {
        return UMShareToWechatSession;
    } else if (NSOrderedSame == [@"WEIXIN_CIRCLE" compare:platform]) {
        return UMShareToWechatTimeline;
    } else if (NSOrderedSame == [@"TENCENT" compare:platform]) {
        return UMShareToTencent;
    } else if (NSOrderedSame == [@"DOUBAN" compare:platform]) {
        return UMShareToDouban;
    } else if (NSOrderedSame == [@"SMS" compare:platform]) {
        return UMShareToSms;
    } else if (NSOrderedSame == [@"EMAIL" compare:platform]) {
        return UMShareToEmail;
    } else if (NSOrderedSame == [@"FACEBOOK" compare:platform]) {
        return UMShareToFacebook;
    } else if (NSOrderedSame == [@"TWITTER" compare:platform]) {
        return UMShareToTwitter;
    } else if (NSOrderedSame == [@"LAIWANG" compare:platform]) {
        return UMShareToLWSession;
    } else if (NSOrderedSame == [@"LAIWANG_DYNAMIC" compare:platform]) {
        return UMShareToLWTimeline;
    } else if (NSOrderedSame == [@"YIXIN" compare:platform]) {
        return UMShareToYXSession;
    } else if (NSOrderedSame == [@"YIXIN_CIRCLE" compare:platform]) {
        return UMShareToYXTimeline;
    } else if (NSOrderedSame == [@"INSTAGRAM" compare:platform]) {
        return UMShareToInstagram;
    } else if (NSOrderedSame == [@"GOOGLEPLUS" compare:platform]) {
        return nil;
    } else if (NSOrderedSame == [@"GENERIC" compare:platform]) {
        return nil;
    }
    return nil;
}

+ (void) addPlatform:(NSDictionary*)options {
    NSString *strMedia = [options objectForKey:@"shareMedias"];
    NSArray* values = [strMedia componentsSeparatedByString:@","];
    int i, count;
    NSString* value;
    count = values.count;
    for (i = 0; i < count; i++)
    {
        value = values[i];
        if (-1 == [[UmengShareSDK getInstance] getIndex:value]) {
            [[UmengShareSDK getInstance]->arraySns addObject:[[UmengShareSDK getInstance] getShareSns:value]];
        }
    }
}

+ (void) removePlatform:(NSDictionary*)options {
    NSString *strMedia = [options objectForKey:@"shareMedias"];
    NSArray* values = [strMedia componentsSeparatedByString:@","];
    int i, count;
    NSString* value;
    count = values.count;
    for (i = 0; i < count; i++)
    {
        value = values[i];
        [[UmengShareSDK getInstance]->arraySns removeObject:[[UmengShareSDK getInstance] getShareSns:value]];
    }
}

+ (void) reorderPlatform:(NSDictionary*)options {
    NSString *strMedia = [options objectForKey:@"shareMedias"];
    NSArray* values = [strMedia componentsSeparatedByString:@","];
    int i, count, idx, orderN;
    NSString* value;
    NSString* snsName;
    count = values.count;
    orderN = 0;
    for (i = 0; i < count; i++)
    {
        value = values[i];
        snsName = [[UmengShareSDK getInstance] getShareSns:value];
        if (nil == snsName) {
            continue;
        }
        idx = [[UmengShareSDK getInstance] getIndex:snsName];
        if (- 1 == idx) {
            //not exits so add
            [[UmengShareSDK getInstance]->arraySns
                                    insertObject:snsName
                                        atIndex:i];
        } else {
            //exist so reorder
            [[UmengShareSDK getInstance]->arraySns exchangeObjectAtIndex:idx withObjectAtIndex:i];
        }
    }
}

+ (void) share:(NSDictionary*)options {
    NSString *shareText = [[options objectForKey:@"shareText"] copy];
    NSString *shareImage = [[options objectForKey:@"shareImage"] copy];
    UIImage *image = nil;
    if (nil != shareImage) {
        if(1 == [shareImage hasPrefix:@"http"]) {
            [[UMSocialData defaultData].urlResource setResourceType:UMSocialUrlResourceTypeImage url:shareImage];
        } else {
            image = [UIImage imageNamed:shareImage];
        }
    }
    
    NSArray* snsArr = nil;
    if ([UmengShareSDK getInstance]->arraySns.count > 0) {
        snsArr = [UmengShareSDK getInstance]->arraySns;
    }
    [UMSocialSnsService presentSnsIconSheetView:[UmengShareSDK getInstance]->viewControl
                                         appKey:[UmengShareSDK getInstance]->UmengAppKey
                                      shareText:shareText
                                     shareImage:image
                                shareToSnsNames:snsArr
                                       delegate:[UmengShareSDK getInstance]];
}

+ (void) addScriptListener:(NSDictionary*)options
{
    NSNumber *number = [options objectForKey:@"listener"];
    functionId = [number intValue];
}

+ (void) removeScriptListener
{
    cocos2d::CCLuaBridge::releaseLuaFunctionById(functionId);
}

+ (void) callListener:(NSString *)result
{
    cocos2d::CCLuaEngine *engine = dynamic_cast<cocos2d::CCLuaEngine *>(cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine());
    cocos2d::CCLuaStack *stack = engine->getLuaStack();
    cocos2d::CCLuaBridge::pushLuaFunctionById(functionId);
    stack->pushString([result UTF8String]);
    stack->executeFunction(1);
}

#pragma mark - UIApplicationDelegate
/**
 这里处理新浪微博SSO授权之后跳转回来，和微信分享完成之后跳转回来
 */
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    return  [UMSocialSnsService handleOpenURL:url wxApiDelegate:nil];
}

/**
 这里处理新浪微博SSO授权进入新浪微博客户端后进入后台，再返回原来应用
 */
- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [UMSocialSnsService  applicationDidBecomeActive];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    return  [UMSocialSnsService handleOpenURL:url wxApiDelegate:nil];
}

-(void)didFinishGetUMSocialDataInViewController:(UMSocialResponseEntity *)response
{
    NSMutableString* str = [[NSMutableString alloc] initWithCapacity:0];
    [str appendFormat:@"share|%d|%@", response.responseCode, [[response.data allKeys] objectAtIndex:0]];
    [UmengShareSDK callListener:str ];
    [str release];
}

@end