
#include "native/CCNative.h"
#import <UIKit/UIKit.h>
#import "platform/ios/CCNativeIOS.h"
#import "platform/ios/openudid/OpenUDIDIOS.h"
#import "AudioToolbox/AudioServices.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void CCNative::showActivityIndicator(void)
{
    [[CCNativeIOS sharedInstance] showActivityIndicator:UIActivityIndicatorViewStyleWhiteLarge];
}

void CCNative::hideActivityIndicator(void)
{
    [[CCNativeIOS sharedInstance] hideActivityIndicator];
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
    [[CCNativeIOS sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int CCNative::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return [[CCNativeIOS sharedInstance] addAlertButton:buttonTitle_];
}

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
    [[CCNativeIOS sharedInstance] showAlertViewWithDelegate:delegate];
}

void CCNative::cancelAlert(void)
{
    [[CCNativeIOS sharedInstance] cancelAlertView];
}

void CCNative::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[UIApplication sharedApplication] openURL:nsurl];
}

const string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
    CCLOG("CCNative::getInputText() - not support this platform.");
    return string("");
}

#pragma mark -
#pragma mark OpenUDID

const string CCNative::getOpenUDID(void)
{
    return string([[OpenUDIDIOS value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

const string CCNative::getDeviceName(void)
{
    UIDevice *device = [UIDevice currentDevice];
    return [[device name] cStringUsingEncoding:NSUTF8StringEncoding];
}

void CCNative::vibrate()
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void CCNative::showAlertObjc(void *delegate)
{
    [[CCNativeIOS sharedInstance] showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate];
}
#endif

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}

void CCNative::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
    [[CCNativeIOS sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

NS_CC_EXTRA_END
