
#import "UmengShareSDK.h"
#import "UMSocial.h"
#import "CCLuaBridge.h"

static UmengShareSDK *gUmengShareInstance = nil;
static int functionId = 0;

@interface UmengShareSDK() {
    UIViewController *viewControl;
}

- (UIViewController*) getUIView;
+ (void) callListener:(NSString *)result;

@end

@implementation UmengShareSDK

- (void) setAppKey:(NSString*) appid {
    [UMSocialData setAppKey:appid];
}

- (void) setUIView:(UIViewController*) view {
    viewControl = view;
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
    UIImage *shareImage = [UIImage imageNamed:@"icon"];          //分享内嵌图片
    
    //如果得到分享完成回调，需要设置delegate为self
//    [UMSocialSnsService presentSnsIconSheetView:self appKey:UmengAppkey shareText:shareText shareImage:shareImage shareToSnsNames:nil delegate:self];
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

@end