
#include "platform/win32/CCNativeWin32.h"
#include "platform/win32/CCNativeWin32def.h"
#include "CCEGLView.h"

CCNativeWin32* CCNativeWin32::s_sharedInstance = NULL;

CCNativeWin32* CCNativeWin32::sharedInstance(void)
{
	if (!s_sharedInstance)
    {
		s_sharedInstance = new CCNativeWin32();
    }
    return s_sharedInstance;
}

CCNativeWin32::CCNativeWin32(void)
{
}


void CCNativeWin32::showActivityIndicator(void)
{
}

void CCNativeWin32::hideActivityIndicator(void)
{
}


void CCNativeWin32::createAlertView(const char* title, const char *message, const char* cancelButtonTitle)
{
	m_alertViewTitle = string(title ? title : "");
	m_alertViewMessage = string(message ? message : "");
}

int CCNativeWin32::addAlertButton(const char* buttonTitle)
{
	return 0;
}

void CCNativeWin32::showAlertViewWithDelegate(CCAlertViewDelegate *delegate)
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

void CCNativeWin32::removeAlertView(void)
{
}

void CCNativeWin32::cancelAlertView(void)
{
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNativeWin32::showAlertViewWithLuaListener(LUA_FUNCTION listener)
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

void CCNativeWin32::removeAlertViewLuaListener(void)
{
}
#endif

const string CCNativeWin32::getInputText(const char* title, const char* message, const char* defaultValue)
{
	HWND handle = CCEGLView::sharedOpenGLView()->getHWnd();

	CCNativeWin32InputBoxStruct inputbox;
	inputbox.title = string(title ? title : "INPUT TEXT");
	inputbox.message = string(message ? message : "INPUT TEXT, PRESS ENTER");
	inputbox.value = string(defaultValue ? defaultValue : "");
	SendMessage(handle, WM_CUT, 998, (LPARAM)&inputbox);
	return inputbox.value;
}
