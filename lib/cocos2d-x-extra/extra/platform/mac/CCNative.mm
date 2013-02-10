
#include "native/CCNative.h"
#import "platform/mac/CCNative_objc.h"
#import "platform/mac/openudid/OpenUDID_mac.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void CCNative::showActivityIndicator(CCActivityIndicatorViewStyle style)
{
    [[CCNative_objc sharedInstance] showActivityIndicator];
}

void CCNative::hideActivityIndicator(void)
{
    [[CCNative_objc sharedInstance] hideActivityIndicator];
}

#pragma mark -
#pragma mark alert view

void CCNative::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *cancelButtonTitle_ = cancelButtonTitle ? [NSString stringWithUTF8String:cancelButtonTitle] : nil;
    [[CCNative_objc sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int CCNative::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return [[CCNative_objc sharedInstance] addAlertButton:buttonTitle_];
}

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}
#endif

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
    [[CCNative_objc sharedInstance] showAlertViewWithDelegate:delegate];
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
    [[CCNative_objc sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

void CCNative::cancelAlert(void)
{
    [[CCNative_objc sharedInstance] cancelAlertView];
}


#pragma mark -
#pragma mark misc

void CCNative::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[NSWorkspace sharedWorkspace] openURL:nsurl];
}

const std::string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *defaultValue_ = [NSString stringWithUTF8String:defaultValue ? defaultValue : ""];
    NSString *input = [[CCNative_objc sharedInstance] getInputText:title_
                                                           message:message_
                                                      defaultValue:defaultValue_];
    return std::string([input cStringUsingEncoding:NSUTF8StringEncoding]);
}


#pragma mark -
#pragma mark OpenUDID

const std::string CCNative::getOpenUDID(void)
{
    return std::string([[OpenUDID_mac value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

NS_CC_EXTRA_END
