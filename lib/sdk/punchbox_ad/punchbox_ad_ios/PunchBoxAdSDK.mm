
#import "PunchBoxAdSDK.h"
#import "CCLuaBridge.h"
#import "PunchBoxAd.h"
#import "PBBannerView.h"
#import "PBInterstitial.h"
#import "PBMoreGame.h"
#import "PBOfferWall.h"
#import "PBADRequest.h"
#import "AppController.h"

static PunchBoxAdSDK *gPunchBoxAdSDKInstance = nil;
static NSString *appId = nil;
static int functionId = 0;

@interface PunchBoxAdSDK () <PBBannerViewDelegate,PBInterstitialDelegate,PBMoreGameDelegate,PBOfferWallDelegate>

+ (void) callListener:(NSString *)result;

@end

@implementation PunchBoxAdSDK


+ (PunchBoxAdSDK*) getInstance
{
    @synchronized(self) {
        if (gPunchBoxAdSDKInstance == nil) {
            gPunchBoxAdSDKInstance = [[PunchBoxAdSDK alloc] init];
        }
    }
    
    return gPunchBoxAdSDKInstance;
}

+ (void) start:(NSDictionary*)options
{
    appId = [options objectForKey:@"appId"];
}

+ (void) stop
{
    [PunchBoxAdSDK removeScriptListener];
}

+ (void) show:(NSDictionary*)options
{
    NSLog(@"entry show function");
    NSString *command = [[options objectForKeyedSubscript:@"command"] copy];
    NSString *position = [[options objectForKeyedSubscript:@"position"] copy];
    
    [PunchBoxAdSDK getInstance]->command = command;
    if (NSOrderedSame == [command compare:@"banner"]) {
        UIWindow *window = [PunchBoxAdSDK getMainWindow];
        CGRect windRect = [window bounds];
        CGRect frameBanner;
        if (NSOrderedSame == [position compare:@"bottom"]) {
            frameBanner = CGRectMake(0.0f, windRect.size.height - 50, 320.0f, 50.0f);
        } else {
            frameBanner = CGRectMake(0.0f, 0.0f, 320.0f, 50.0f);
        }
    
        PBBannerView *bannerView = [[PBBannerView alloc] initWithFrame:frameBanner];
        bannerView.delegate = [PunchBoxAdSDK getInstance];
        [bannerView loadRequest:[PBADRequest request]];
        [window addSubview:bannerView];

        [PunchBoxAdSDK getInstance]->viewAd = bannerView;
    } else if (NSOrderedSame == [command compare:@"interstitial"]) {
        [PBInterstitial sharedInterstitial].delegate = [PunchBoxAdSDK getInstance];
        [[PBInterstitial sharedInterstitial] showInterstitialWithScale:0.9f];
    } else if (NSOrderedSame == [command compare:@"moregame"]) {
        [PBMoreGame sharedMoreGame].delegate = [PunchBoxAdSDK getInstance];
        [[PBMoreGame sharedMoreGame] showMoreGameWithScale:0.9f];
    } else if (NSOrderedSame == [command compare:@"offerwall"]) {
        [PBOfferWall sharedOfferWall].delegate = [PunchBoxAdSDK getInstance];
        [[PBOfferWall sharedOfferWall] showOfferWallWithScale:0.9f];
    } else {
        NSLog(@"ad command wrong!");
    }
}

+ (void) remove
{
    NSString *command = [PunchBoxAdSDK getInstance]->command;
    if (NSOrderedSame == [command compare:@"banner"]) {
        [[PunchBoxAdSDK getInstance]->viewAd removeFromSuperview];
        [[PunchBoxAdSDK getInstance]->viewAd release];
    } else if (NSOrderedSame == [command compare:@"interstitial"]) {
        [[PBInterstitial sharedInterstitial] closeInterstitial];
    } else if (NSOrderedSame == [command compare:@"moregame"]) {
        [[PBMoreGame sharedMoreGame] closeMoreGame];
    } else if (NSOrderedSame == [command compare:@"offerwall"]) {
        [[PBOfferWall sharedOfferWall] closeOfferWall];
    } else {
        NSLog(@"ad command wrong!");
    }
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

+ (UIWindow*)getMainWindow
{
    return [[[UIApplication sharedApplication] windows] firstObject];
}

+ (void) callListener:(NSString *)result
{
    NSLog(@"listener:%@", result);
    cocos2d::CCLuaEngine *engine = dynamic_cast<cocos2d::CCLuaEngine *>(cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine());
    cocos2d::CCLuaStack *stack = engine->getLuaStack();
    cocos2d::CCLuaBridge::pushLuaFunctionById(functionId);
    stack->pushString([result UTF8String]);
    stack->executeFunction(1);
}

#pragma mark - PbBannerViewDelegate

// 收到Banner广告
- (void)pbBannerViewDidReceiveAd:(PBBannerView *)pbBannerView
{
    [PunchBoxAdSDK callListener:@"received"];
}

// Banner广告数据错误
- (void)pbBannerView:(PBBannerView *)pbBannerView
      receiveAdError:(PBRequestError *)requestError
{
    [PunchBoxAdSDK callListener: [@"failed," stringByAppendingString:requestError.localizedDescription ]];
}

// 将要展示Banner广告
- (void)pbBannerViewWillPresentScreen:(PBBannerView *)pbBannerView
{
    [PunchBoxAdSDK callListener:@"will show"];
}

// 移除Banner广告
- (void)pbBannerViewDidDismissScreen:(PBBannerView *)pbBannerView
{
    [PunchBoxAdSDK callListener:@"removed"];
}

#pragma mark - PBInterstitialDelegate

// 弹出广告加载完成
- (void)pbInterstitialDidLoadAd:(PBInterstitial *)pbInterstitial
{
    [PunchBoxAdSDK callListener:@"load finish"];
}

// 弹出广告加载错误
- (void)pbInterstitial:(PBInterstitial *)pbInterstitial
loadAdFailureWithError:(PBRequestError *)requestError
{
    [PunchBoxAdSDK callListener:@"load fail,"];
}

// 弹出广告打开完成
- (void)pbInterstitialDidPresentScreen:(PBInterstitial *)pbInterstitial
{
    [PunchBoxAdSDK callListener:@"open"];
}

// 弹出广告将要关闭
- (void)pbInterstitialWillDismissScreen:(PBInterstitial *)pbInterstitial
{
    [PunchBoxAdSDK callListener:@"will close"];
}

// 弹出广告关闭完成
- (void)pbInterstitialDidDismissScreen:(PBInterstitial *)pbInterstitial
{
    [PunchBoxAdSDK callListener:@"closed"];
}

#pragma mark - PBMoregameDelegate

// 精品推荐加载完成
- (void)pbMoreGameDidLoadAd:(PBMoreGame *)pbMoreGame
{
    [PunchBoxAdSDK callListener:@"load finish"];
}

// 精品推荐加载错误
- (void)pbMoreGame:(PBMoreGame *)pbMoreGame
loadAdFailureWithError:(PBRequestError *)requestError
{
    [PunchBoxAdSDK callListener:[@"failed," stringByAppendingString:requestError.localizedDescription]];
}

// 精品推荐打开完成
- (void)pbMoreGameDidPresentScreen:(PBMoreGame *)pbMoreGame
{
    [PunchBoxAdSDK callListener:@"open"];
}

// 精品推荐将要关闭
- (void)pbMoreGameWillDismissScreen:(PBMoreGame *)pbMoreGame
{
    [PunchBoxAdSDK callListener:@"will close"];
}

// 精品推荐关闭完成
- (void)pbMoreGameDidDismissScreen:(PBMoreGame *)pbMoreGame
{
    [PunchBoxAdSDK callListener:@"closed"];
}

#pragma mark - PBOfferWallDelegate

// 积分墙加载完成
- (void)pbOfferWallDidLoadAd:(PBOfferWall *)pbOfferWall
{
    [PunchBoxAdSDK callListener:@"load finish"];
}

// 积分墙加载错误
- (void)pbOfferWall:(PBOfferWall *)pbOfferWall
loadAdFailureWithError:(PBRequestError *)requestError
{
    [PunchBoxAdSDK callListener:[@"failed," stringByAppendingString:requestError.localizedDescription]];
}

// 积分墙打开完成
- (void)pbOfferWallDidPresentScreen:(PBOfferWall *)pbOfferWall
{
    [PunchBoxAdSDK callListener:@"open"];
}

// 积分墙将要关闭
- (void)pbOfferWallWillDismissScreen:(PBOfferWall *)pbOfferWall
{
    [PunchBoxAdSDK callListener:@"will close"];
}

// 积分墙关闭完成
- (void)pbOfferWallDidDismissScreen:(PBOfferWall *)pbOfferWall
{
    [PunchBoxAdSDK callListener:@"closed"];
}

// 用户完成积分墙任务的回调，给用户充值
// taskCoins中的元素为NSDictionary类型
//     键值说明：taskContent  NSString   任务名称
//             coins  NSNumber  赚得金币数量x
- (void)pbOfferWall:(PBOfferWall *)pbOfferWall finishTaskRewardCoin:(NSArray *)taskCoins
{
    [PunchBoxAdSDK callListener:@"rewardcoin"];
}

@end
