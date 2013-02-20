#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "LuaHostWin32.h"
#include "CCEGLView.h"
#include "SimpleAudioEngine.h"
#include <sstream>
#include <Commdlg.h>
#include <Shlobj.h>
#include "ProjectConfigDialog.h"

#define MAX_LOADSTRING 100

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    return LuaHostWin32::createAndRun();
}

LuaHostWin32 *LuaHostWin32::s_sharedInstance = NULL;

LuaHostWin32::LuaHostWin32(void)
: m_app(NULL)
, m_hwnd(NULL)
, m_consoleVisible(true)
, m_exit(true)
{
    CCAssert(s_sharedInstance == NULL, "Can't create more LuaHostWin32 instance");
    s_sharedInstance = this;

    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);
}

LuaHostWin32::~LuaHostWin32(void)
{
    s_sharedInstance = NULL;
}

int LuaHostWin32::createAndRun(void)
{
    LuaHostWin32 *host = new LuaHostWin32();
    host->init();
    return host->run();
}

bool LuaHostWin32::init(void)
{
    return true;
}

int LuaHostWin32::run(void)
{
    loadProjectConfig();

    AllocConsole();
    freopen("CONOUT$", "wt", stdout);
    freopen("CONOUT$", "wt", stderr);

    // disable close console
    HWND hwndConsole = GetConsoleWindow();
    if (hwndConsole != NULL)
    {
        HMENU hMenu = GetSystemMenu(hwndConsole, FALSE);
        if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }

    do
    {
        m_exit = true;

        if (m_project.showConsole)
        {
            ShowWindow(hwndConsole, SW_SHOW);
            BringWindowToTop(hwndConsole);
        }
        else
        {
            ShowWindow(hwndConsole, SW_HIDE);
        }

        // create the application instance
        m_app = new AppDelegate();
        m_app->setStartupScriptFilename(m_project.scriptFile);
        SetCurrentDirectoryA(m_project.projectDir.c_str());

        CCEGLView* eglView = CCEGLView::sharedOpenGLView();    
        eglView->setMenuResource(MAKEINTRESOURCE(IDC_LUAHOSTWIN32));
        eglView->setWndProc(WindowProc);
        eglView->setFrameSize(m_project.frameWidth, m_project.frameHeight);
        eglView->setFrameZoomFactor(m_project.frameScale);

        m_hwnd = eglView->getHWnd();
        BringWindowToTop(m_hwnd);

        if (m_project.windowLeft >= 0)
        {
            eglView->moveWindow(m_project.windowLeft, m_project.windowTop);
        }

        HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LUAHOSTWIN32));
        SendMessage(m_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
        SendMessage(hwndConsole, WM_SETICON, ICON_BIG, (LPARAM)icon);

        m_app->run();

        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
        CocosDenshion::SimpleAudioEngine::end();

        delete m_app;
        m_app = NULL;
    } while (!m_exit);

    FreeConsole();
    return 0;
}

void LuaHostWin32::loadProjectConfig(void)
{
    int index = 1;
    while (index < __argc)
    {
        const string arg = getCommandLineArg(index);
        if (arg.compare("-workdir") == 0)
        {
            index++;
            m_project.projectDir = getCommandLineArg(index);
        }
        else if (arg.compare("-file") == 0)
        {
            index++;
            m_project.scriptFile = getCommandLineArg(index);
        }
        else if (arg.compare("-size") == 0)
        {
            index++;
            const string size = getCommandLineArg(index);
            int pos = size.find('x');
            if (pos != size.npos && pos > 0)
            {
                string widthStr, heightStr;
                widthStr.assign(size, 0, pos);
                heightStr.assign(size, pos + 1, size.length() - pos);
                int frameWidth = atoi(widthStr.c_str());
                int frameHeight = atoi(heightStr.c_str());
                if (frameWidth < 320) frameWidth = 320;
                if (frameHeight < 320) frameHeight = 320;
                m_project.frameWidth = frameWidth;
                m_project.frameHeight = frameHeight;
            }
        }
        else if (arg.compare("-scale") == 0)
        {
            index++;
            const string scale = getCommandLineArg(index);
            float frameScale = atof(scale.c_str());
            if (frameScale > 0)
            {
                m_project.frameScale = frameScale;
            }
        }
        else if (arg.compare("-disable-console") == 0)
        {
            m_project.showConsole = false;
        }

        index++;
    }
}

void LuaHostWin32::updateWindowTitle(void)
{
}

void LuaHostWin32::relaunch(void)
{
    RECT rect;
    GetWindowRect(m_hwnd, &rect);
    m_project.windowLeft = rect.left;
    m_project.windowTop  = rect.top;
    m_exit = false;
    CCDirector::sharedDirector()->end();
}

// menu callback
void LuaHostWin32::onFileNewProject(void)
{
}

void LuaHostWin32::onFileOpenProject(void)
{
    if (ProjectConfigDialog::showModal(m_hwnd, &m_project))
    {
        relaunch();
    }
}

void LuaHostWin32::onFileCreateProjectShortcut(void)
{
}

void LuaHostWin32::onFileProjectConfig(void)
{
    if (ProjectConfigDialog::showModal(m_hwnd, &m_project, "Change Project Config", "Relaunch"))
    {
        relaunch();
    }
}

void LuaHostWin32::onFileRelaunch(void)
{
    relaunch();
}

void LuaHostWin32::onFileExit(void)
{
    DestroyWindow(m_hwnd);
}

void LuaHostWin32::onViewChangeFrameSize(int index)
{
    int w, h;

    switch (index)
    {
        case ID_VIEW_640_960:
            w = 640; h = 960;
            break;

        case ID_VIEW_640_1136:
            w = 640; h = 1136;
            break;

        case ID_VIEW_768_1024:
            w = 768; h = 1024;
            break;

        case ID_VIEW_1536_2048:
            w = 1536; h = 2048;
            break;

        case ID_VIEW_480_800:
            w = 480; h = 800;
            break;

        case ID_VIEW_480_854:
            w = 480; h = 854;
            break;

        case ID_VIEW_600_1024:
            w = 600; h = 1024;
            break;

        case ID_VIEW_720_1280:
            w = 720; h = 1280;
            break;

        case ID_VIEW_800_1280:
            w = 800; h = 1280;
            break;

        case ID_VIEW_1080_1920:
            w = 1080; h = 1920;
            break;

        case ID_VIEW_320_480:
        default:
            w = 320; h = 480;
    }
    if (m_project.frameWidth > m_project.frameHeight)
    {
        int w2 = w;
        w = h;
        h = w2;
    }
    m_project.frameWidth = w;
    m_project.frameHeight = h;
    m_project.frameScale = 1.0f;
    relaunch();
}

void LuaHostWin32::onViewChangeDirection(int directionMode)
{
    if ((directionMode == ID_VIEW_PORTRAIT && m_project.frameWidth > m_project.frameHeight)
        || (directionMode == ID_VIEW_LANDSCAPE && m_project.frameHeight > m_project.frameWidth))
    {
        float height = m_project.frameWidth;
        m_project.frameWidth = m_project.frameHeight;
        m_project.frameHeight = height;
        relaunch();
    }
}

void LuaHostWin32::onViewChangeZoom(int scaleMode)
{
    float scale = 1.0f;
    if (scaleMode == ID_VIEW_ZOOM_OUT)
    {
        scale = 0.5f;
    }

    m_project.frameScale = scale;
    CCEGLView::sharedOpenGLView()->setFrameZoomFactor(scale);
    CCEGLView::sharedOpenGLView()->resize(m_project.frameWidth * scale, m_project.frameHeight * scale);
}

void LuaHostWin32::onHelpAbout(void)
{
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTBOX), m_hwnd, AboutDialogCallback);
}

// windows callback
LRESULT LuaHostWin32::WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
    int wmId, wmEvent;
    LuaHostWin32 *host = LuaHostWin32::sharedInstance();
    HWND hwnd = host->getHWnd();

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ·ÖÎö²Ëµ¥Ñ¡Ôñ:
		switch (wmId)
		{
        case ID_FILE_NEW_PROJECT:
            host->onFileNewProject();
            break;

        case ID_FILE_OPEN_PROJECT:
            host->onFileOpenProject();
            break;

        case ID_FILE_CREATE_PROJECT_SHORTCUT:
            host->onFileCreateProjectShortcut();

        case ID_FILE_PROJECT_CONFIG:
            host->onFileProjectConfig();
            break;

        case ID_FILE_RELAUNCH:
            host->onFileRelaunch();
            break;

        case ID_FILE_EXIT:
            host->onFileExit();
            break;

        case ID_VIEW_320_480:
        case ID_VIEW_640_960:
        case ID_VIEW_640_1136:
        case ID_VIEW_768_1024:
        case ID_VIEW_1536_2048:
        case ID_VIEW_480_800:
        case ID_VIEW_480_854:
        case ID_VIEW_600_1024:
        case ID_VIEW_720_1280:
        case ID_VIEW_800_1280:
        case ID_VIEW_1080_1920:
            host->onViewChangeFrameSize(wmId);
            break;

        case ID_VIEW_PORTRAIT:
        case ID_VIEW_LANDSCAPE:
            host->onViewChangeDirection(wmId);
            break;

        case ID_VIEW_RESET_ZOOM:
        case ID_VIEW_ZOOM_OUT:
            host->onViewChangeZoom(wmId);
            break;

        case ID_HELP_ABOUT:
            host->onHelpAbout();
            break;

        default:
            return 0;
		}
        break;

    case WM_KEYDOWN:
        if (wParam == VK_F5)
        {
            host->onFileRelaunch();
        }
        break;

    default:
        return 0;
	}

    *pProcessed = TRUE;
    return 0;
}

INT_PTR CALLBACK LuaHostWin32::AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

// helper

const string LuaHostWin32::getCommandLineArg(int index)
{
    static string empty;
    if (index < 0 || index >= __argc) return empty;

    wstring ws(__wargv[index]);
    string s;
    s.assign(ws.begin(), ws.end());
    return s;
}
