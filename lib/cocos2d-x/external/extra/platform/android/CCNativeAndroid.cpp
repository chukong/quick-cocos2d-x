
#include "native/CCNative.h"

NS_CC_EXTRA_BEGIN

//  activity indicator

void CCNative::showActivityIndicator(void)
{
    CCLOG("CCNative::showActivityIndicator() - not support this platform.");
}

void CCNative::hideActivityIndicator(void)
{
    CCLOG("CCNative::hideActivityIndicator() - not support this platform.");
}


//  alert view

void CCNative::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
    CCLOG("CCNative::createAlert() - not support this platform.");
}

int CCNative::addAlertButton(const char* buttonTitle)
{
    CCLOG("CCNative::addAlertButton() - not support this platform.");
}

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    CCLOG("CCNative::addAlertButtonLua() - not support this platform.");
}
#endif

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
    CCLOG("CCNative::showAlert() - not support this platform.");
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative::showAlertLua(LUA_FUNCTION listener)
{
    CCLOG("CCNative::showAlertLua() - not support this platform.");
}
#endif

void CCNative::cancelAlert(void)
{
    CCLOG("CCNative::cancelAlert() - not support this platform.");
}


//  misc

void CCNative::openURL(const char* url)
{
    CCLOG("CCNative::openURL() - not support this platform.");
}

const string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
    CCLOG("CCNative::getInputText() - not support this platform.");
    return string("");
}


//  OpenUDID

const string CCNative::getOpenUDID(void)
{
    CCLOG("CCNative::getOpenUDID() - not support this platform.");
    return string("");
}

const string CCNative::getDeviceName(void)
{
    CCLOG("CCNative::getDeviceName() - not support this platform.");
    return string("");
}

void CCNative::vibrate()
{
    CCLog("CCNative::vibrate() not support on this platform.");
}

NS_CC_EXTRA_END
