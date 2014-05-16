
#import "UmengShareSDK.h"
#import "UMSocial.h"
#import "UMSocialWechatHandler.h"
#import "UMSocialQQHandler.h"

#import "CCLuaBridge.h"

static UmengShareSDK *gUmengShareInstance = nil;
static int functionId = 0;

@interface UmengShareSDK() <UIApplicationDelegate> {
    UIViewController *viewControl;
    NSString *UmengAppKey;
    NSString *WXAppId;
    NSString *QQAppId;
    NSString *QQAppKey;
    NSString *webUrl;
    NSArray *arraySns;
}

- (UIViewController*) getUIView;
+ (void) callListener:(NSString *)result;

@end

@implementation UmengShareSDK

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

    arraySns = [[NSArray alloc] initWithObjects:UMShareToSina, UMShareToTencent, UMShareToRenren, UMShareToQQ, UMShareToQzone, UMShareToWechatTimeline, UMShareToWechatSession, UMShareToDouban, nil];
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

+ (void) share:(NSDictionary*)options {
    NSString *shareText = [[options objectForKey:@"shareText"] copy];
    
    [UMSocialSnsService presentSnsIconSheetView:[UmengShareSDK getInstance]->viewControl
                                         appKey:[UmengShareSDK getInstance]->UmengAppKey
                                      shareText:shareText
                                     shareImage:nil
                                shareToSnsNames:nil
                                       delegate:nil];
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

@end