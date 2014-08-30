
#include "native/CCNative.h"
#include "platform/win32/CCNativeWin32.h"

NS_CC_EXTRA_BEGIN

void CCNative::showActivityIndicator(void)
{
	CCNativeWin32::sharedInstance()->showActivityIndicator();
}

void CCNative::hideActivityIndicator(void)
{
	CCNativeWin32::sharedInstance()->hideActivityIndicator();
}


void CCNative::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
	CCNativeWin32::sharedInstance()->createAlertView(title, message, cancelButtonTitle);
}

int CCNative::addAlertButton(const char* buttonTitle)
{
	return CCNativeWin32::sharedInstance()->addAlertButton(buttonTitle);
}

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}
#endif

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
	CCNativeWin32::sharedInstance()->showAlertViewWithDelegate(delegate);
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
	CCNativeWin32::sharedInstance()->showAlertViewWithLuaListener(listener);
}
#endif

void CCNative::cancelAlert(void)
{
	CCNativeWin32::sharedInstance()->cancelAlertView();
}

const std::string CCNative::getOpenUDID(void)
{
	return CCNativeWin32::sharedInstance()->getUDID();
}

void CCNative::openURL(const char* url)
{
    if (!url) return;
}

const std::string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
	return CCNativeWin32::sharedInstance()->getInputText(title, message, defaultValue);
}

const string CCNative::getDeviceName(void)
{
    return "Win32";
}

void CCNative::vibrate()
{
}


NS_CC_EXTRA_END
