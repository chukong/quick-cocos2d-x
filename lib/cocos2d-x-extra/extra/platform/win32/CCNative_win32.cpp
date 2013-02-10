
#include "platform/win32/CCNative_win32.h"
#include "platform/win32/CCNative_win32def.h"
#include "CCEGLView.h"

CCNative_win32* CCNative_win32::s_sharedInstance = NULL;

CCNative_win32* CCNative_win32::sharedInstance(void)
{
	if (!s_sharedInstance)
    {
		s_sharedInstance = new CCNative_win32();
    }
    return s_sharedInstance;
}

CCNative_win32::CCNative_win32(void)
{
}


void CCNative_win32::showActivityIndicator(void)
{
}

void CCNative_win32::hideActivityIndicator(void)
{
}


void CCNative_win32::createAlertView(const char* title, const char *message, const char* cancelButtonTitle)
{
	m_alertViewTitle = string(title ? title : "");
	m_alertViewMessage = string(message ? message : "");
}

int CCNative_win32::addAlertButton(const char* buttonTitle)
{
	return 0;
}

void CCNative_win32::showAlertViewWithDelegate(CCAlertViewDelegate *delegate)
{
	wstring title(m_alertViewTitle.begin(), m_alertViewTitle.end());
	wstring message(m_alertViewMessage.begin(), m_alertViewMessage.end());
	int button = MessageBox(NULL, message.c_str(), title.c_str(), MB_OKCANCEL);
	if (button == IDOK || button == IDYES)
	{
		delegate->alertViewClickedButtonAtIndex(0);
	}
	else
	{
		delegate->alertViewClickedButtonAtIndex(1);
	}
}

void CCNative_win32::removeAlertView(void)
{
}

void CCNative_win32::cancelAlertView(void)
{
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative_win32::showAlertViewWithLuaListener(LUA_FUNCTION listener)
{
	wstring title(m_alertViewTitle.begin(), m_alertViewTitle.end());
	wstring message(m_alertViewMessage.begin(), m_alertViewMessage.end());
	int button = MessageBox(NULL, message.c_str(), title.c_str(), MB_OKCANCEL);
    
    CCLuaValueDict event;
    event["action"] = CCLuaValue::stringValue("clicked");
	if (button == IDOK || button == IDYES)
	{
		event["buttonIndex"] = CCLuaValue::intValue(1);
	}
	else
	{
		event["buttonIndex"] = CCLuaValue::intValue(2);
	}

	CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
	stack->pushCCLuaValueDict(event);
    stack->executeFunctionByHandler(listener, 1);
}

void CCNative_win32::removeAlertViewLuaListener(void)
{
}
#endif

const string CCNative_win32::getInputText(const char* title, const char* message, const char* defaultValue)
{
	HWND handle = CCEGLView::sharedOpenGLView()->getHWnd();

	CCNativeWin32InputBoxStruct inputbox;
	inputbox.title = string(title ? title : "INPUT TEXT");
	inputbox.message = string(message ? message : "INPUT TEXT, PRESS ENTER");
	inputbox.value = string(defaultValue ? defaultValue : "");
	SendMessage(handle, WM_CUT, 998, (LPARAM)&inputbox);
	return inputbox.value;
}
