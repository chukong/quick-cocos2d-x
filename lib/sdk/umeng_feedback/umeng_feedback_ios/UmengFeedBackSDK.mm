
#import "UmengFeedBackSDK.h"
#import "UMFeedback.h"
#import "CCLuaBridge.h"

static UmengFeedBackSDK* gUmengFeedBackInstance = nil;
static int functionId = 0;

@interface UmengFeedBackSDK () {
    UIViewController *viewControl;
}


+ (UmengFeedBackSDK*) getInstance;
- (void) umCheck:(NSNotification *)notification;

@end

@implementation UmengFeedBackSDK

+ (UmengFeedBackSDK*) getInstance {
    if (nil == gUmengFeedBackInstance) {
        gUmengFeedBackInstance = [[UmengFeedBackSDK alloc] init];
        
        [[NSNotificationCenter defaultCenter] addObserver:gUmengFeedBackInstance
                                                 selector:@selector(umCheck:)
                                                     name:UMFBCheckFinishedNotification
                                                   object:nil];
    }
    
    return gUmengFeedBackInstance;
}

+ (void) showFeedback:(NSDictionary*)option {
    NSString* appKey = [option objectForKey:@"appKey"];
    [UMFeedback showFeedback:[UmengFeedBackSDK getInstance]->viewControl
                  withAppkey:appKey];
}

+ (void) checkReplies:(NSDictionary*)option  {
    NSString* appKey = [option objectForKey:@"appKey"];
    [UMFeedback checkWithAppkey:appKey];
}

- (void) setView:(UIViewController*)view {
    viewControl = view;
}

- (void)umCheck:(NSNotification *)notification {
    int nRepliesCount = 0;
    NSLog(@"notification = %@", notification.userInfo);
    if (notification.userInfo) {
        NSArray * newReplies = [notification.userInfo objectForKey:@"newReplies"];
        nRepliesCount = [newReplies count];
    }
    
    NSString* result = [NSString stringWithFormat:@"replyCount|%d", nRepliesCount];
    [UmengFeedBackSDK callListener:result];


//    UIAlertView *alertView;
//    NSLog(@"notification = %@", notification.userInfo);
//    if (notification.userInfo) {
//        NSArray * newReplies = [notification.userInfo objectForKey:@"newReplies"];
//        NSLog(@"newReplies = %@", newReplies);
//        NSString *title = [NSString stringWithFormat:@"有%d条新回复", [newReplies count]];
//        NSMutableString *content = [NSMutableString string];
//        for (int i = 0; i < [newReplies count]; i++) {
//            NSString * dateTime = [[newReplies objectAtIndex:i] objectForKey:@"datetime"];
//            NSString *_content = [[newReplies objectAtIndex:i] objectForKey:@"content"];
//            [content appendString:[NSString stringWithFormat:@"%d .......%@.......\r\n", i+1,dateTime]];
//            [content appendString:_content];
//            [content appendString:@"\r\n\r\n"];
//        }
//        
//        alertView = [[UIAlertView alloc] initWithTitle:title message:content delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"查看", nil];
//        ((UILabel *) [[alertView subviews] objectAtIndex:1]).textAlignment = NSTextAlignmentLeft ;
//        
//    }else{
//        alertView = [[UIAlertView alloc] initWithTitle:@"没有新回复" message:nil delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
//    }
//    [alertView show];
}

+ (void) addScriptListener:(NSDictionary*)options
{
    NSNumber *number = [options objectForKey:@"listener"];
    functionId = [number intValue];
}

+ (void) removeScriptListener
{
    cocos2d::CCLuaBridge::releaseLuaFunctionById(functionId);
    functionId = 0;
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
