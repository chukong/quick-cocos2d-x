
#include "PunchBoxAdSDK.h"
#include "CCLuaBridge.h"

static PunchBoxAdSDK *gPunchBoxAdSDKInstance = nil;
static NSString *appId = nil;
static int functionId = 0;

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
    removeScriptListener();
}

+ (void) show:(NSDictionary*)options
{
    
}

+ (void) remove
{
    
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

@end
