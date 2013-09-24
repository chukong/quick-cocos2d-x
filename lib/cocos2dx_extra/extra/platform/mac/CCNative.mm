
#include "native/CCNative.h"
#include <sys/sysctl.h>
#import "platform/mac/CCNativeMac.h"
#import "platform/mac/openudid/OpenUDIDMac.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void CCNative::showActivityIndicator(void)
{
    [[CCNativeMac sharedInstance] showActivityIndicator];
}

void CCNative::hideActivityIndicator(void)
{
    [[CCNativeMac sharedInstance] hideActivityIndicator];
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
    [[CCNativeMac sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int CCNative::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return (int)[[CCNativeMac sharedInstance] addAlertButton:buttonTitle_];
}

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}
#endif

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
    [[CCNativeMac sharedInstance] showAlertViewWithDelegate:delegate];
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative::showAlertLua(LUA_FUNCTION listener)
{
    [[CCNativeMac sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

void CCNative::cancelAlert(void)
{
    [[CCNativeMac sharedInstance] cancelAlertView];
}


#pragma mark -
#pragma mark misc

void CCNative::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[NSWorkspace sharedWorkspace] openURL:nsurl];
}

const string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *defaultValue_ = [NSString stringWithUTF8String:defaultValue ? defaultValue : ""];
    NSString *input = [[CCNativeMac sharedInstance] getInputText:title_
                                                           message:message_
                                                      defaultValue:defaultValue_];
    return string([input cStringUsingEncoding:NSUTF8StringEncoding]);
}


#pragma mark -
#pragma mark OpenUDID

const string CCNative::getOpenUDID(void)
{
    return string([[OpenUDIDMac value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

const string CCNative::getDeviceName(void)
{
    size_t len = 0;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);
    if (len)
    {
        char* model = static_cast<char*>(malloc(len * sizeof(char)));
        sysctlbyname("hw.model", model, &len, NULL, 0);
        string modelStr(model);
        free(model);
        return modelStr;
    }

    CCLog("CCNative::getDeviceName() not support on this platform.");
    return string("");
}

void CCNative::vibrate()
{
    CCLog("CCNative::vibrate() not support on this platform.");
}

NS_CC_EXTRA_END
