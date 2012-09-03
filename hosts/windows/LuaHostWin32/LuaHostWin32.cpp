
#include "stdafx.h"
#include "LuaHostWin32.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "platform\CCFileUtils.h"
#include <string>
#include <sstream>
#include <Commdlg.h>
#include <Shlobj.h>

#define MAX_LOADSTRING 100

using namespace std;
USING_NS_CC;

void parseCommandLineArgs(void);
const string getCommandLineArg(int index);
BOOL openProjectFolder(void);
void restartApplication(float width = 0, float height = 0);
LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

HWND s_hWnd = NULL;
BOOL s_useConsole = TRUE;
float s_startupWidth = 480;
float s_startupHeight = 320;
string s_resourcesDir("");
string s_projectFolder("");
string s_startupScriptFilename("main.lua");

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    parseCommandLineArgs();

    // create the application instance
    AppDelegate app;

    if (s_useConsole)
    {
        AllocConsole();
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

    if (s_projectFolder.length() == 0)
    {
        openProjectFolder();
        s_startupScriptFilename = string("main.lua");
    }

    if (s_projectFolder.length() > 0)
    {
        wstring ws(s_projectFolder.begin(), s_projectFolder.end());
        SetCurrentDirectory(ws.c_str());
    }

    if (s_resourcesDir.length() > 0)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory(s_resourcesDir.c_str());
    }
    app.setStartupScriptFilename(s_startupScriptFilename.c_str());

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

void parseCommandLineArgs(void)
{
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
                string widthStr, heightStr;
                widthStr.assign(size, 0, pos);
                heightStr.assign(size, pos + 1, size.length() - pos);
                s_startupWidth = (float)atoi(widthStr.c_str());
                s_startupHeight = (float)atoi(heightStr.c_str());
                if (s_startupWidth < 480) s_startupWidth = 480;
                if (s_startupHeight < 320) s_startupHeight = 320;
            }
        }
        else if (arg.compare("--disable-console") == 0)
        {
            s_useConsole = FALSE;
        }
        else if (arg.compare("--resdir") == 0)
        {
            index++;
            s_resourcesDir = getCommandLineArg(index);
        }
        else if (arg.compare("--workdir") == 0)
        {
            index++;
            s_projectFolder = getCommandLineArg(index);
        }
        else if (arg.compare("--file") == 0)
        {
            index++;
            s_startupScriptFilename = getCommandLineArg(index);
        }

        index++;
    }
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

BOOL openProjectFolder(void)
{
    TCHAR buff[MAX_PATH + 1];
    memset(buff, 0, sizeof(TCHAR) * (MAX_PATH + 1));

    BROWSEINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.hwndOwner = s_hWnd;
    bi.pszDisplayName = buff;
    bi.lpszTitle = L"Select application working dir";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    if (SHBrowseForFolder(&bi))
    {
        wstring ws(buff);
        s_projectFolder.assign(ws.begin(), ws.end());
        return TRUE;
    }

    return FALSE;
}

void restartApplication(float width, float height)
{
    PostMessage(s_hWnd, WM_CLOSE, NULL, NULL);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));

    ostringstream buff;
    buff << "\"";
    buff << getCommandLineArg(0);
    buff << "\"";

    if (width > 0 && height > 0)
    {
        s_startupWidth = width;
        s_startupHeight = height;
    }

    buff << " --size ";
    buff << s_startupWidth;
    buff << "x";
    buff << s_startupHeight;

    if (!s_useConsole)
    {
        buff << " --disable-console";
    }

    if (s_resourcesDir.length() > 0)
    {
        buff << " --dir ";
        buff << s_resourcesDir;
    }
    buff << " --file ";
    buff << s_startupScriptFilename;

    const string str = buff.str();

    CCLOG("cmd: %s", str.c_str());

    WCHAR cmd[MAX_PATH + 1];
    memset(cmd, 0, sizeof(WCHAR) * (MAX_PATH + 1));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), str.length(), cmd, MAX_PATH);

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

        case ID_FILE_OPEN:
        {
            if (openProjectFolder())
            {
                restartApplication();
            }
            //TCHAR buff[MAX_PATH + 1];
            //memset(buff, 0, sizeof(TCHAR) * (MAX_PATH + 1));

            //OPENFILENAME ofn;
            //memset(&ofn, 0, sizeof(ofn));
            //ofn.lStructSize = sizeof(ofn);
            //ofn.hwndOwner = s_hWnd;
            //ofn.lpstrFilter = L"*.lua";
            //ofn.lpstrTitle = L"Open script file";
            //ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
            //ofn.lpstrFile = buff;
            //ofn.nMaxFile = MAX_PATH;

            //if (GetOpenFileName(&ofn))
            //{
            //    wstring ws(buff);
            //    s_startupScriptFilename.assign(ws.begin(), ws.end());
            //    CCLOG("new startup script filename: %s", s_startupScriptFilename.c_str());
            //    restartApplication();
            //}
            //break;
        }

        case ID_FILE_RESTART:
            restartApplication();
            break;

        case ID_VIEW_IPHONE:
            restartApplication(480, 320);
            break;

        case ID_VIEW_IPHONE4:
            restartApplication(960, 640);
            break;

        case ID_VIEW_IPAD:
            restartApplication(1024, 768);
            break;

        case ID_VIEW_NEWIPAD:
            restartApplication(2048, 1536);
            break;

        case ID_VIEW_ANDROID1:
            restartApplication(854, 480);
            break;

        case ID_VIEW_ANDROID2:
            restartApplication(800, 480);
            break;

        case ID_VIEW_ANDROID3:
            restartApplication(1024, 600);
            break;

        case ID_VIEW_ANDROID4:
            restartApplication(1280, 720);
            break;

        case ID_VIEW_ANDROID5:
            restartApplication(1280, 800);
            break;

        case ID_VIEW_RESETZOOM:
            CCEGLView::sharedOpenGLView()->resize((int)s_startupWidth, (int)s_startupHeight);
            CCEGLView::sharedOpenGLView()->centerWindow();
            break;

        case ID_VIEW_ZOOMOUT:
            CCEGLView::sharedOpenGLView()->resize((int)s_startupWidth / 2, (int)s_startupHeight / 2);
            CCEGLView::sharedOpenGLView()->centerWindow();
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
            restartApplication();
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
