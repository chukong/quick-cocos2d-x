
#import "platform/mac/CCNativeMac.h"

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

@implementation CCNativeMac

static CCNativeMac *s_sharedInstance;

+ (CCNativeMac *)sharedInstance
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = [[CCNativeMac alloc] init];
    }
    return s_sharedInstance;
}


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator
{
    CCLog("CCNative::showActivityIndicator() not support on this platform.");
}

- (void)hideActivityIndicator
{
    CCLog("CCNative::hideActivityIndicator() not support on this platform.");
}


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle
{
    if (alertView_)
    {
        CCLOG("CCNative::createAlertView() - alert view already exists");
        return;
    }
    
    CCLOG("CCNative::createAlertView() - title: %s, message: %s, cancelButtonTitle: %s",
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
        CCLOG("CCNative::addAlertButton() - alert view not exists");
        return 0;
    }

    CCLOG("CCNative::addAlertButton() - buttonTitle: %s", utf8cstr(buttonTitle));
    [alertView_ addButtonWithTitle:buttonTitle];
    return [alertView_.buttons count] - 1;
}

- (void)showAlertViewWithDelegate:(CCAlertViewDelegate *)delegate
{
    if (!alertView_)
    {
        CCLOG("CCNative::showAlertViewWithDelegate() - alert view not exists");
        return;
    }

    CCLOG("CCNative::showAlertViewWithDelegate()");
    int buttonIndex = (int)[alertView_ runModal];
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
        CCLOG("CCNative::removeAlertView() - alert view not exists");
        return;
    }
    
    CCLOG("CCNative::removeAlertView()");
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
        CCLOG("CCNative::cancelAlertView() - alert view not exists");
        return;
    }
    
    CCLOG("CCNative::cancelAlertView()");
    [self removeAlertView];
}

#if CC_LUA_ENGINE_ENABLED > 0
- (void)showAlertViewWithLuaListener:(LUA_FUNCTION)listener
{
    if (!alertView_)
    {
        CCLOG("CCNative::showAlertViewWithLuaListener() - alert view not exists");
        return;
    }
    
    CCLOG("CCNative::showAlertViewWithLuaListener()");
    NSModalResponse buttonResponse = (int)[alertView_ runModal];
    int buttonIndex = 0;
    
    CCLOG("buttonResponse,%d",(int)buttonResponse);
    
    if (buttonResponse == NSAlertFirstButtonReturn)
    {
        buttonIndex = 0;
    }
    else if (buttonResponse == NSAlertSecondButtonReturn)
    {
        buttonIndex = 1;
    }
    else if (buttonResponse == NSAlertThirdButtonReturn)
    {
        buttonIndex = 2;
    }
    
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
