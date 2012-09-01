
#include "stdafx.h"
#include "LuaHostWin32.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

#define MAX_LOADSTRING 100

USING_NS_CC;

const string getCommandLineArg(int index);
LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void restart(float width = 0, float height = 0);

HWND s_hWnd = NULL;
float s_startupWidth = 480;
float s_startupHeight = 320;
BOOL s_useConsole = FALSE;

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;

    // parse command line arguments
    int index = 1;
    while (index < __argc)
    {
        const string arg = getCommandLineArg(index);
        if (arg.compare("--size") == 0)
        {
            index++;
            const string size = getCommandLineArg(index);
            int pos = size.find('x');
            if (pos != size.npos && pos > 0)
            {
                string s_width, s_height;
                s_width.assign(size, 0, pos);
                s_height.assign(size, pos + 1, size.length() - pos);
                s_startupWidth = (float)atoi(s_width.c_str());
                s_startupHeight = (float)atoi(s_height.c_str());
                if (s_startupWidth < 480) s_startupWidth = 480;
                if (s_startupHeight < 320) s_startupHeight = 320;
            }
        }
        else if (arg.compare("--console") == 0)
        {
            s_useConsole = true;
        }
        else
        {
            app.setStartupScriptFilename(arg.c_str());
        }

        index++;
    }

    if (s_useConsole)
    {
        AllocConsole();
        // freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "wt", stdout);
        freopen("CONOUT$", "wt", stderr);

        // disable close console
        HWND hwnd = ::GetConsoleWindow();
        if (hwnd != NULL)
        {
            HMENU hMenu = ::GetSystemMenu(hwnd, FALSE);
            if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
        }
    }

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    
    eglView->setMenuResource(MAKEINTRESOURCE(IDC_LUAHOSTWIN32));
    eglView->setWndProc(WindowProc);
    eglView->setFrameSize(s_startupWidth, s_startupHeight);

    s_hWnd = eglView->getHWnd();

    int ret = CCApplication::sharedApplication()->run();

    if (s_useConsole)
    {
        FreeConsole();
    }

    return ret;
}

const string getCommandLineArg(int index)
{
    static string empty;
    if (index < 0 || index >= __argc) return empty;

    wstring ws(__wargv[index]);
    string s;
    s.assign(ws.begin(), ws.end());
    return s;
}

void restart(float width, float height)
{
    PostMessage(s_hWnd, WM_CLOSE, NULL, NULL);

    STARTUPINFO si;
    memset(&si, 0, sizeof(si));

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));

    char buff[MAX_PATH + 1];
    memset(buff, 0, sizeof(char) * (MAX_PATH + 1));

    const string path = getCommandLineArg(0);

    if (width > 0 && height > 0)
    {
        s_startupWidth = width;
        s_startupHeight = height;
    }
    sprintf_s(buff, MAX_PATH, "\"%s\" --size %dx%d", path.c_str(), (int)s_startupWidth, (int)s_startupHeight);

    if (s_useConsole)
    {
        strcat_s(buff, " --console");
    }

    //CCLOG("RESTART: %s", buff);

    WCHAR cmd[MAX_PATH + 1];
    memset(cmd, 0, sizeof(WCHAR) * (MAX_PATH + 1));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buff, strlen(buff), cmd, MAX_PATH);

    CreateProcess(NULL,
                  cmd,
                  NULL,
                  NULL,
                  FALSE,
                  NORMAL_PRIORITY_CLASS,
                  NULL,
                  NULL,
                  &si,
                  &pi);
}

LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
    int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ·ÖÎö²Ëµ¥Ñ¡Ôñ:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTBOX), s_hWnd, About);
			break;

        case ID_FILE_RESTART:
            restart();
            break;

        case ID_VIEW_IPHONE4:
            restart(960, 640);
            break;

        case ID_VIEW_IPAD:
            restart(1024, 768);
            break;

        case ID_VIEW_NEWIPAD:
            restart(2048, 1536);
            break;

        case ID_VIEW_ANDROID1:
            restart(854, 480);
            break;

        case ID_VIEW_ANDROID2:
            restart(800, 480);
            break;

        case ID_VIEW_ANDROID3:
            restart(1024, 600);
            break;

        case ID_VIEW_ANDROID4:
            restart(1280, 720);
            break;

        case ID_VIEW_ANDROID5:
            restart(1280, 800);
            break;

		case IDM_EXIT:
			DestroyWindow(s_hWnd);
			break;

        default:
            return 0;
		}
        break;

    case WM_KEYDOWN:
        if (wParam == VK_F5)
        {
            restart();
        }
        break;

    default:
        return 0;
	}

    *pProcessed = TRUE;
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
