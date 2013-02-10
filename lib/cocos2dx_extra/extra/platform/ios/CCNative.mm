
#include "native/CCNative.h"
#import <UIKit/UIKit.h>
#import "platform/ios/CCNative_objc.h"
#import "platform/ios/openudid/OpenUDID_objc.h"
#import "AudioToolbox/AudioServices.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void CCNative::showActivityIndicator(CCActivityIndicatorViewStyle style)
{
    [[CCNative_objc sharedInstance] showActivityIndicator:static_cast<UIActivityIndicatorViewStyle>(style)];
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

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
    [[CCNative_objc sharedInstance] showAlertViewWithDelegate:delegate];
}

void CCNative::cancelAlert(void)
{
    [[CCNative_objc sharedInstance] cancelAlertView];
}

void CCNative::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[UIApplication sharedApplication] openURL:nsurl];
}

#pragma mark -
#pragma mark OpenUDID

const std::string CCNative::getOpenUDID(void)
{
    return std::string([[OpenUDID_objc value] cStringUsingEncoding:NSUTF8StringEncoding]);
}


const char* CCNative::getDeviceName(void)
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
    [[CCNative_objc sharedInstance] showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate];
}
#endif

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}

void CCNative::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
    [[CCNative_objc sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

NS_CC_EXTRA_END
