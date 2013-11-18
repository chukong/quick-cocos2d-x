/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include <string>

#include "platform/CCCommon.h"
#include "CCStdC.h"
#include "CCEGLView.h"

using namespace std;

NS_CC_BEGIN

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

void SendLogToWindow(const string& log)
{
	// Send data as a message
      COPYDATASTRUCT myCDS;
      myCDS.dwData = CCLOG_STRING;
      myCDS.cbData = (DWORD)log.length() + 1;
      myCDS.lpData = (PVOID)log.c_str();
      HWND hwnd = CCEGLView::sharedOpenGLView()->getHWnd();
      SendMessage(hwnd,
                  WM_COPYDATA,
                  (WPARAM)(HWND)hwnd,
                  (LPARAM)(LPVOID)&myCDS);
}

void CCLog(const char * pszFormat, ...)
{
    char szBuf[MAX_LEN];

    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
    va_end(ap);

	string msg(szBuf);
	wstring wmsg;
	wmsg.assign(msg.begin(), msg.end());

    OutputDebugStringW(wmsg.c_str());
    OutputDebugStringA("\n");
	puts(msg.c_str());

	SendLogToWindow(msg);
}

void CCLuaLog(const char *pszMsg)
{
	string msg(pszMsg ? pszMsg : "");
	if (msg.length() > MAX_LEN)
	{
		msg = msg.substr(0, MAX_LEN);
	}
	wstring wmsg;
	wmsg.assign(msg.begin(), msg.end());

    OutputDebugStringW(wmsg.c_str());
    OutputDebugStringA("\n");
	puts(msg.c_str());

	SendLogToWindow(msg);
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    MessageBoxA(NULL, pszMsg, pszTitle, MB_OK);
}

NS_CC_END
