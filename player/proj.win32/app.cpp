
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "app.h"
#include <Commdlg.h>
#include <Shlobj.h>
#include <winnls.h>
#include <shobjidl.h>
#include <objbase.h>
#include <objidl.h>
#include <shlguid.h>
#include <vector>
#include "CCEGLView.h"
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#include "SimpleAudioEngine.h"
#include "ProjectConfigDialog.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    return QuickXPlayer::createAndRun();
}

int QuickXPlayer::createAndRun(void)
{
    QuickXPlayer *host = QuickXPlayer::sharedInstance();
    int ret = host->run();
    QuickXPlayer::purgeSharedInstance();
    return ret;
}

QuickXPlayer *QuickXPlayer::s_sharedInstance = NULL;

QuickXPlayer *QuickXPlayer::sharedInstance(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new QuickXPlayer();
    }
    return s_sharedInstance;
}

void QuickXPlayer::purgeSharedInstance(void)
{
    if (s_sharedInstance)
    {
        delete s_sharedInstance;
        s_sharedInstance = NULL;
    }
}

QuickXPlayer::QuickXPlayer(void)
: m_app(NULL)
, m_hwnd(NULL)
, m_exit(TRUE)
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);
}

int QuickXPlayer::run(void)
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
        m_exit = TRUE;

        if (m_project.isShowConsole())
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
        m_app->setStartupScriptFilename(m_project.getScriptFileRealPath());

        // set environments
        SetCurrentDirectoryA(m_project.getProjectDir().c_str());
        CCFileUtils::sharedFileUtils()->setSearchRootPath(m_project.getProjectDir().c_str());
        CCFileUtils::sharedFileUtils()->setWritablePath(m_project.getWritableRealPath().c_str());

        // create opengl view
        CCEGLView* eglView = CCEGLView::sharedOpenGLView();
        eglView->setMenuResource(MAKEINTRESOURCE(IDC_LUAHOSTWIN32));
        eglView->setWndProc(WindowProc);
        eglView->setFrameSize(m_project.getFrameSize().width, m_project.getFrameSize().height);
        eglView->setFrameZoomFactor(m_project.getFrameScale());

        // make window actived
        m_hwnd = eglView->getHWnd();
        BringWindowToTop(m_hwnd);

        // restore window position
        const CCPoint windowOffset = m_project.getWindowOffset();
        if (windowOffset.x != 0 || windowOffset.y != 0)
        {
            eglView->moveWindow(windowOffset.x, windowOffset.y);
        }

        // set icon
        HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LUAHOSTWIN32));
        SendMessage(m_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
        SendMessage(hwndConsole, WM_SETICON, ICON_BIG, (LPARAM)icon);

        // run game
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        const vector<string> arr = m_project.getPackagePathArray();
        for (vector<string>::const_iterator it = arr.begin(); it != arr.end(); ++it)
        {
            stack->addSearchPath(it->c_str());
        }

        m_app->run();

        // cleanup
        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
        CocosDenshion::SimpleAudioEngine::end();

        delete m_app;
        m_app = NULL;
    } while (!m_exit);

    FreeConsole();
    return 0;
}

void QuickXPlayer::loadProjectConfig(void)
{
    int index = 1;
    while (index < __argc)
    {
        const string arg = getCommandLineArg(index);
        if (arg.compare("-workdir") == 0)
        {
            index++;
            m_project.setProjectDir(getCommandLineArg(index).c_str());
        }
        else if (arg.compare("-file") == 0)
        {
            index++;
            m_project.setScriptFile(getCommandLineArg(index).c_str());
        }
        else if (arg.compare("-writable") == 0)
        {
            index++;
            m_project.setWritablePath(getCommandLineArg(index).c_str());
        }
        else if (arg.compare("-package.path") == 0)
        {
            index++;
            m_project.setPackagePath(getCommandLineArg(index).c_str());
        }
        else if (arg.compare("-size") == 0)
        {
            index++;
            const string size = getCommandLineArg(index);
            int pos = size.find('x');
            if (pos != size.npos && pos > 0)
            {
                int frameWidth = atoi(size.substr(0, pos).c_str());
                int frameHeight = atoi(size.substr(pos + 1).c_str());
                if (frameWidth < 100) frameWidth = 100;
                if (frameHeight < 100) frameHeight = 100;
                m_project.setFrameSize(CCSize(frameWidth, frameHeight));
            }
        }
        else if (arg.compare("-scale") == 0)
        {
            index++;
            const string scale = getCommandLineArg(index);
            float frameScale = atof(scale.c_str());
            if (frameScale > 0)
            {
                m_project.setFrameScale(frameScale);
            }
        }
        else if (arg.compare("-disable-console") == 0)
        {
            m_project.setShowConsole(FALSE);
        }

        index++;
    }
}

void QuickXPlayer::updateWindowTitle(void)
{
}

void QuickXPlayer::relaunch(void)
{
    RECT rect;
    GetWindowRect(m_hwnd, &rect);
    m_project.setWindowOffset(CCPoint(rect.left, rect.top));
    m_exit = false;
    CCDirector::sharedDirector()->end();
}

// menu callback
void QuickXPlayer::onFileNewProject(void)
{
}

void QuickXPlayer::onFileOpenProject(void)
{
    if (ProjectConfigDialog::showModal(m_hwnd, &m_project))
    {
        relaunch();
    }
}

void QuickXPlayer::onFileCreateProjectShortcut(void)
{
    WCHAR shortcutPathBuff[MAX_PATH + 1] = {0};

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = m_hwnd;
    ofn.lpstrFilter = L"Shortcut (*.lnk)\0*.lnk\0";
    ofn.lpstrTitle  = L"Create Project Shortcut";
    ofn.Flags       = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
    ofn.lpstrFile   = shortcutPathBuff;
    ofn.nMaxFile    = MAX_PATH;

    if (!GetSaveFileName(&ofn)) return;

    // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
    // has already been called.
    IShellLink* psl;
    HRESULT hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);

    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf;

        // args
        string args("-workdir ");
        args.append(m_project.getProjectDir());

        args.append(" -file ");
        args.append(m_project.getScriptFile());

        args.append(" -writable ");
        args.append(m_project.getWritablePath());

        args.append(" -size ");
        const CCSize frameSize = m_project.getFrameSize();
        char buff[32] = {0};
        sprintf_s(buff, "%d", (int)frameSize.width);
        args.append(buff);
        args.append("x");
        sprintf_s(buff, "%d", (int)frameSize.height);
        args.append(buff);

        if (!m_project.isShowConsole())
        {
            args.append(" -disable-console");
        }

        // Set the path to the shortcut target and add the description.
        psl->SetPath(__wargv[0]);
        wstring wargs;
        wargs.assign(args.begin(), args.end());
        psl->SetArguments(wargs.c_str());
        psl->SetDescription(L"QuickXPlayer");

        // Query IShellLink for the IPersistFile interface, used for saving the
        // shortcut in persistent storage.
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hres))
        {
            // Save the link by calling IPersistFile::Save.
            size_t len = wcslen(shortcutPathBuff);
            if (_wcsicmp(shortcutPathBuff + len - 4, L".lnk") != 0)
            {
                wcscat_s(shortcutPathBuff, L".lnk");
            }
            hres = ppf->Save(shortcutPathBuff, TRUE);
            ppf->Release();
        }
        psl->Release();
    }
}

void QuickXPlayer::onFileProjectConfig(void)
{
    if (ProjectConfigDialog::showModal(m_hwnd, &m_project, "Change Project Config", "Relaunch"))
    {
        relaunch();
    }
}

void QuickXPlayer::onFileRelaunch(void)
{
    relaunch();
}

void QuickXPlayer::onFileExit(void)
{
    DestroyWindow(m_hwnd);
}

void QuickXPlayer::onViewChangeFrameSize(int index)
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
    if (m_project.isLandscapeFrame())
    {
        int w2 = w;
        w = h;
        h = w2;
    }
    m_project.setFrameSize(CCSize(w, h));
    m_project.setFrameScale(1.0f);
    relaunch();
}

void QuickXPlayer::onViewChangeDirection(int directionMode)
{
    BOOL isLandscape = m_project.isLandscapeFrame();
    if ((directionMode == ID_VIEW_PORTRAIT && isLandscape) || (directionMode == ID_VIEW_LANDSCAPE && !isLandscape))
    {
        CCSize frameSize = m_project.getFrameSize();
        frameSize.setSize(frameSize.height, frameSize.width);
        relaunch();
    }
}

void QuickXPlayer::onViewChangeZoom(int scaleMode)
{
    float scale = 1.0f;
    if (scaleMode == ID_VIEW_ZOOM_OUT)
    {
        scale = 0.5f;
    }

    m_project.setFrameScale(scale);
    CCEGLView::sharedOpenGLView()->setFrameZoomFactor(scale);
    CCEGLView::sharedOpenGLView()->resize(m_project.getFrameSize().width * scale,
        m_project.getFrameSize().height * scale);
}

void QuickXPlayer::onHelpAbout(void)
{
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTBOX), m_hwnd, AboutDialogCallback);
}

// windows callback
LRESULT QuickXPlayer::WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
    int wmId, wmEvent;
    QuickXPlayer *host = QuickXPlayer::sharedInstance();
    HWND hwnd = host->getWindowHandle();

    switch (message)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

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
            break;

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

INT_PTR CALLBACK QuickXPlayer::AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

const string QuickXPlayer::getCommandLineArg(int index)
{
    static string empty;
    if (index < 0 || index >= __argc) return empty;

    wstring ws(__wargv[index]);
    string s;
    s.assign(ws.begin(), ws.end());
    return s;
}
