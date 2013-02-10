
#include "native/CCNative.h"
#include "platform/win32/CCNative_win32.h"

NS_CC_EXTRA_BEGIN

void CCNative::showActivityIndicator(CCActivityIndicatorViewStyle style)
{
	CCNative_win32::sharedInstance()->showActivityIndicator();
}

void CCNative::hideActivityIndicator(void)
{
	CCNative_win32::sharedInstance()->hideActivityIndicator();
}


void CCNative::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
	CCNative_win32::sharedInstance()->createAlertView(title, message, cancelButtonTitle);
}

int CCNative::addAlertButton(const char* buttonTitle)
{
	return CCNative_win32::sharedInstance()->addAlertButton(buttonTitle);
}

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}
#endif

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
	CCNative_win32::sharedInstance()->showAlertViewWithDelegate(delegate);
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
	CCNative_win32::sharedInstance()->showAlertViewWithLuaListener(listener);
}
#endif

void CCNative::cancelAlert(void)
{
	CCNative_win32::sharedInstance()->cancelAlertView();
}

const std::string CCNative::getOpenUDID(void)
{
	return "";
}

void CCNative::openURL(const char* url)
{
    if (!url) return;
}

const std::string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
	return CCNative_win32::sharedInstance()->getInputText(title, message, defaultValue);
}


NS_CC_EXTRA_END
