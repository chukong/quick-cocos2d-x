
#import "platform/ios/CCNative_objc.h"

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

@implementation CCNative_objc

static CCNative_objc *s_sharedInstance;

+ (CCNative_objc *)sharedInstance
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = [[CCNative_objc alloc] init];
    }
    return s_sharedInstance;
}

- (void)dealloc
{
    [self hideActivityIndicator];
    [self removeAlertView];
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    [super dealloc];
    s_sharedInstance = nil;
}


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator:(UIActivityIndicatorViewStyle)style
{
    if (activityIndicatorView_)
    {
        CCLOG("[CCNative_objc] ERR, showActivityIndicator() activity indicator already visible");
        return;
    }
    
    CCLOG("[CCNative_objc] showActivityIndicator()");
    activityIndicatorView_ = [UIActivityIndicatorView  alloc];
    [activityIndicatorView_ initWithActivityIndicatorStyle:style];
    [activityIndicatorView_ autorelease];
    [activityIndicatorView_ retain];
    
    NSInteger count = [UIApplication sharedApplication].windows.count;
    UIWindow* topWindow = [[UIApplication sharedApplication].windows objectAtIndex:count - 1];
    [topWindow addSubview: activityIndicatorView_];
    activityIndicatorView_.center = topWindow.center;
    [activityIndicatorView_ startAnimating];
}

- (void)hideActivityIndicator
{
    if (!activityIndicatorView_)
    {
        CCLOG("[CCNative_objc] ERR, hideActivityIndicator() activity indicator not visible");
        return;
    }
    
    CCLOG("[CCNative_objc] hideActivityIndicator()");
    [activityIndicatorView_ removeFromSuperview];
    [activityIndicatorView_ release];
    activityIndicatorView_ = nil;
}


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle
{
    if (alertView_)
    {
        CCLOG("[CCNative_objc] ERR, createAlertView() alert view already exists");
        return;
    }
    
    CCLOG("[CCNative_objc] createAlertView() title: %s, message: %s, cancelButtonTitle: %s",
          utf8cstr(title), utf8cstr(message), utf8cstr(cancelButtonTitle));
    alertView_ = [[UIAlertView alloc] initWithTitle:title
                                            message:message
                                           delegate:self
                                  cancelButtonTitle:cancelButtonTitle
                                  otherButtonTitles:nil];
}

- (NSInteger)addAlertButton:(NSString *)buttonTitle
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, addAlertButton() alert view not exists");
        return 0;
    }

    CCLOG("[CCNative_objc] addAlertButton() buttonTitle: %s", utf8cstr(buttonTitle));
    return [alertView_ addButtonWithTitle:buttonTitle];
}

- (void)showAlertViewWithDelegate:(CCAlertViewDelegate *)delegate
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, showAlertViewWithDelegate() alert view not exists");
        return;
    }

    CCLOG("[CCNative_objc] showAlertViewWithDelegate()");
    alertViewDelegates_ = delegate;
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    [alertView_ show];
}

- (void)removeAlertView
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, removeAlertView() alert view not exists");
        return;
    }
    
    CCLOG("[CCNative_objc] removeAlertView()");
    [alertView_ release];
    alertView_ = nil;
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    alertViewDelegates_ = nil;
}

- (void)cancelAlertView
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, cancelAlertView() alert view not exists");
        return;
    }
    
    CCLOG("[CCNative_objc] cancelAlertView()");
    [alertView_ dismissWithClickedButtonIndex:0 animated:YES];
    [self removeAlertView];
}

#if CC_LUA_ENGINE_ENABLED > 0
- (void)showAlertViewWithLuaListener:(LUA_FUNCTION)listener
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, showAlertViewWithLuaListener() alert view not exists");
        return;
    }
    
    CCLOG("[CCNative_objc] showAlertViewWithLuaListener()");
    alertViewLuaListener_ = listener;
    alertViewDelegates_ = nil;
    [alertView_ show];
}

- (void)removeAlertViewLuaListener
{
    if (alertViewLuaListener_)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(alertViewLuaListener_);
    }
}
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
- (void)showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, showAlertViewWithDelegate() alert view not exists");
        return;
    }
    
    CCLOG("[CCNative_objc] showAlertViewWithObjcDelegate()");
    [alertView_ setDelegate:delegate];
    [alertView_ show];
}
#endif

#pragma mark -
#pragma mark UIAlertView delegates

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertViewDelegates_)
    {
        alertViewDelegates_->alertViewClickedButtonAtIndex(buttonIndex);
    }
#if CC_LUA_ENGINE_ENABLED > 0
    if (alertViewLuaListener_)
    {
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
        CCLuaValueDict event;
        event["action"] = CCLuaValue::stringValue("clicked");
        event["buttonIndex"] = CCLuaValue::intValue(buttonIndex + 1);
        stack->pushCCLuaValueDict(event);
        stack->executeFunctionByHandler(alertViewLuaListener_, 1);
    }
#endif
    [self removeAlertView];
}

@end
