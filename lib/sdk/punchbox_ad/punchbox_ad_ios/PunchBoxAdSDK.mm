
#include "PunchBoxAdSDK.h"

#include "CCLuaBridge.h"
#include "CCLuaStack.h"

USING_NS_CC;

@implementation PunchBoxAdSDK

static PunchBoxAdSDK* s_instance = nil;

+ (PunchBoxAdSDK*) getInstance
{
    if (!s_instance) {
        s_instance = [[PunchBoxAdSDK alloc] init];
    }
    return s_instance;
}

+ (void) purgeInstance
{
    if (s_instance) {
        [s_instance dealloc];
        s_instance = nil;
    }
}

- (void) dealloc
{
    [self remove];
    [self removeScriptListener];
    [appId release];
    [super dealloc];
}

// public interface

+ (BOOL) start:(NSDictionary*)options
{
    NSString *appId = [options objectForKey:@"appId"];
    if (appId && [appId length]) {
        return [[PunchBoxAdSDK getInstance] start:appId];
    }
    return NO;
}

+ (void) stop
{
    [[PunchBoxAdSDK getInstance] stop];
}

+ (BOOL) show:(NSDictionary*)options
{
    NSString* adType = [options objectForKey:@"type"];
    NSString* adId = [options objectForKey:@"id"];
    NSString* adPosition = [options objectForKey:@"position"];
    
    if (!adType) return NO;
    
    if ([adType compare:@"banner" options:NSCaseInsensitiveSearch] == NSOrderedSame
        || [adType compare:@"interstitial" options:NSCaseInsensitiveSearch] == NSOrderedSame
        || [adType compare:@"moregame" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        return [[PunchBoxAdSDK getInstance] show:adType withId:adId andPosition:adPosition];
    }
    
    return NO;
}

+ (void) remove
{
    [[PunchBoxAdSDK getInstance] remove];
}

+ (BOOL) addScriptListener:(NSDictionary*)options
{
    NSNumber* listener = [options objectForKey:@"listener"];
    if (listener && [listener intValue]) {
        [[PunchBoxAdSDK getInstance] addScriptListener:[listener intValue]];
        return YES;
    }
    return NO;
    
}

+ (void) removeScriptListener
{
    [[PunchBoxAdSDK getInstance] removeScriptListener];
}


// internal interface

- (BOOL) start:(NSString*)appId_
{
    if (appId) {
        NSLog(@"[PunchBoxAdSDK] already start");
        return NO;
    }
    appId = [[NSString stringWithString:appId_] retain];
    [PunchBoxAd startSession:appId];
    NSLog(@"[PunchBoxAdSDK] start");
    return YES;
}

- (void) stop
{
    [self remove];
    [self removeScriptListener];
}

- (BOOL) show:(NSString*)adType withId:(NSString*)adId andPosition:(NSString*)adPosition
{
    if (adHandler) {
        NSLog(@"[PunchBoxAdSDK] One Ad already exists");
        return NO;
    }
    
    NSLog(@"[PunchBoxAdSDK] show, adType: %@, id: %@, position: %@", adType, adId, adPosition);
    adHandler = [[PunchBoxAdHandler alloc] initWithDelegate:self
                                                    andType:adType
                                                    andAdId:adId
                                                andPosition:adPosition];
    [adHandler show];
    return YES;
}

- (void) remove
{
    if (adHandler) {
        [adHandler remove];
        [adHandler release];
        adHandler = nil;
    }
}

- (void) addScriptListener:(int)listener_
{
    if (listener) {
        [self removeScriptListener];
    }
    listener = listener_;
}

- (void) removeScriptListener
{
    if (listener) {
        CCLuaBridge::releaseLuaFunctionById(listener);
        listener = 0;
    }
}


// PunchBoxAdDelegate

- (void) onReceiveAd
{
    CCLuaBridge::pushLuaFunctionById(listener);
    CCLuaStack *stack = CCLuaBridge::getStack();
    stack->pushString("received");
    stack->executeFunction(1);
}

- (void) onDismissScreen
{
    [self remove];
    CCLuaBridge::pushLuaFunctionById(listener);
    CCLuaStack *stack = CCLuaBridge::getStack();
    stack->pushString("dismiss");
    stack->executeFunction(1);
}

- (void) onFailedToReceiveAd:(PBRequestError*)requestError
{
    char buff[32];
    snprintf(buff, 32, "failed,%u", abs(requestError.code));
    [self remove];

    CCLuaBridge::pushLuaFunctionById(listener);
    CCLuaStack *stack = CCLuaBridge::getStack();
    stack->pushString(buff);
    stack->executeFunction(1);
}

- (void) onPresentScreen
{
    CCLuaBridge::pushLuaFunctionById(listener);
    CCLuaStack *stack = CCLuaBridge::getStack();
    stack->pushString("present");
    stack->executeFunction(1);
}

@end
