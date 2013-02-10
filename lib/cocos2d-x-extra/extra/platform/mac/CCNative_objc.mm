
#import "platform/mac/CCNative_objc.h"

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
//    [self hideActivityIndicator];
    [self removeAlertView];
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    [super dealloc];
    s_sharedInstance = nil;
}


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator
{
//    if (activityIndicatorView_)
//    {
//        CCLOG("[CCNative_objc] ERR, showActivityIndicator() activity indicator already visible");
//        return;
//    }
//    
//    CCLOG("[CCNative_objc] showActivityIndicator()");
//    activityIndicatorView_ = [UIActivityIndicatorView  alloc];
//    [activityIndicatorView_ initWithActivityIndicatorStyle:style];
//    [activityIndicatorView_ autorelease];
//    [activityIndicatorView_ retain];
//    
//    NSInteger count = [UIApplication sharedApplication].windows.count;
//    UIWindow* topWindow = [[UIApplication sharedApplication].windows objectAtIndex:count - 1];
//    [topWindow addSubview: activityIndicatorView_];
//    activityIndicatorView_.center = topWindow.center;
//    [activityIndicatorView_ startAnimating];
}

- (void)hideActivityIndicator
{
//    if (!activityIndicatorView_)
//    {
//        CCLOG("[CCNative_objc] ERR, hideActivityIndicator() activity indicator not visible");
//        return;
//    }
//    
//    CCLOG("[CCNative_objc] hideActivityIndicator()");
//    [activityIndicatorView_ removeFromSuperview];
//    [activityIndicatorView_ release];
//    activityIndicatorView_ = nil;
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
    alertView_ = [NSAlert alertWithMessageText:title
                                 defaultButton:cancelButtonTitle
                               alternateButton:nil
                                   otherButton:nil
                     informativeTextWithFormat:@"%@", message];
    [alertView_ retain];
}

- (NSInteger)addAlertButton:(NSString *)buttonTitle
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, addAlertButton() alert view not exists");
        return 0;
    }

    CCLOG("[CCNative_objc] addAlertButton() buttonTitle: %s", utf8cstr(buttonTitle));
    [alertView_ addButtonWithTitle:buttonTitle];
    return [alertView_.buttons count] - 1;
}

- (void)showAlertViewWithDelegate:(CCAlertViewDelegate *)delegate
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, showAlertViewWithDelegate() alert view not exists");
        return;
    }

    CCLOG("[CCNative_objc] showAlertViewWithDelegate()");
    NSInteger buttonIndex = [alertView_ runModal];
    
    if (delegate)
    {
        delegate->alertViewClickedButtonAtIndex(buttonIndex);
    }
    [self removeAlertView];
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
}

- (void)cancelAlertView
{
    if (!alertView_)
    {
        CCLOG("[CCNative_objc] ERR, cancelAlertView() alert view not exists");
        return;
    }
    
    CCLOG("[CCNative_objc] cancelAlertView()");
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
    NSInteger buttonIndex = [alertView_ runModal];
    
    CCLuaValueDict event;
    event["action"] = CCLuaValue::stringValue("clicked");
    event["buttonIndex"] = CCLuaValue::intValue(buttonIndex + 1);
    
    CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
    stack->pushCCLuaValueDict(event);
    stack->executeFunctionByHandler(listener, 1);
    
    [self removeAlertView];
}

- (void)removeAlertViewLuaListener
{
}
#endif


#pragma mark -
#pragma mark misc

- (NSString*)getInputText:(NSString*)title message:(NSString*)message defaultValue:(NSString*)defaultValue
{
    NSAlert *alert = [NSAlert alertWithMessageText:title
                                     defaultButton:@"OK"
                                   alternateButton:@"Cancel"
                                       otherButton:nil
                         informativeTextWithFormat:@"%@", message];
    
    NSRect frame = NSMakeRect(0, 0, 320, 22);
    NSTextField *textField = [[NSTextField alloc] initWithFrame:frame];
    [textField setStringValue:defaultValue];
    [alert setAccessoryView:textField];
    NSInteger buttonIndex = [alert runModal];
    if (buttonIndex == 0)
    {
        return @"";
    }
    else
    {
        return [textField stringValue];
    }
}

@end
