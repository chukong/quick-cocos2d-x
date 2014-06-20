
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "app.h"
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include <Commdlg.h>
#include <Shlobj.h>
#include <winnls.h>
#include <shobjidl.h>
#include <objbase.h>
#include <objidl.h>
#include <shlguid.h>
#include <shellapi.h>

#include <vector>

#include "CCEGLView.h"
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#include "SimpleAudioEngine.h"
#include "ProjectConfigDialog.h"
#include "Registry.h"

static std::string makeTitleKeyForIndex(int index);
static std::string makeArgsKeyForIndex(int index);
static std::vector<std::string> splitString(std::string str,std::string pattern);

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
, m_writeDebugLogFile(NULL)
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);
}

int QuickXPlayer::run(void)
{
    const char *QUICK_COCOS2DX_ROOT = getenv("QUICK_COCOS2DX_ROOT");
    SimulatorConfig::sharedDefaults()->setQuickCocos2dxRootPath(QUICK_COCOS2DX_ROOT);

    loadProjectConfig();
    if (!m_project.getProjectDir().length())
    {
        m_project.resetToWelcome();
    }

    loadOpenRecents();

    HWND hwndConsole = NULL;
    if (m_project.isShowConsole())
    {
        AllocConsole();
        freopen("CONOUT$", "wt", stdout);
        freopen("CONOUT$", "wt", stderr);

        // disable close console
        hwndConsole = GetConsoleWindow();
        if (hwndConsole != NULL)
        {
            HMENU hMenu = GetSystemMenu(hwndConsole, FALSE);
            if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

            ShowWindow(hwndConsole, SW_SHOW);
            BringWindowToTop(hwndConsole);
        }
    }

    if (m_project.isWriteDebugLogToFile())
    {
        const string debugLogFilePath = m_project.getDebugLogFilePath();
        m_writeDebugLogFile = fopen(debugLogFilePath.c_str(), "w");
        if (!m_writeDebugLogFile)
        {
            CCLOG("Cannot create debug log file %s", debugLogFilePath.c_str());
        }
    }

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(QuickXPlayer::onWelcomeNewProject), "WELCOME_NEW_PROJECT", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(QuickXPlayer::onWelcomeOpen), "WELCOME_OPEN_PROJECT", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(QuickXPlayer::onWelcomeSamples), "WELCOME_SAMPLES", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(QuickXPlayer::onWelcomeGetStarted), "WELCOME_OPEN_DOCUMENTS", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(QuickXPlayer::onWelcomeGetCommunity), "WELCOME_OPEN_COMMUNITY", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(QuickXPlayer::onWelcomeOpenRecent), "WELCOME_OPEN_PROJECT_ARGS", NULL);

    do
    {
        m_exit = TRUE;

        // create the application instance
        m_app = new AppDelegate();
        m_app->setProjectConfig(m_project);

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

        if (hwndConsole)
        {
            SendMessage(hwndConsole, WM_SETICON, ICON_BIG, (LPARAM)icon);
        }

        // update menu
        updateOpenRecent();
        createRecentMenu();
        createViewMenu();
        updateMenu();

        // run game
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        const vector<string> arr = m_project.getPackagePathArray();
        for (vector<string>::const_iterator it = arr.begin(); it != arr.end(); ++it)
        {
            stack->addSearchPath(it->c_str());
        }

        m_app->setOpenRecents(getOpenRecentsForLua());
        m_app->run();

        // cleanup
        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
        CocosDenshion::SimpleAudioEngine::end();

        delete m_app;
        m_app = NULL;
    } while (!m_exit);

    FreeConsole();
    if (m_writeDebugLogFile) fclose(m_writeDebugLogFile);
    return 0;
}

void QuickXPlayer::loadProjectConfig(void)
{
    vector<string> args;
    for (int i = 0; i < __argc; ++i)
    {
        wstring ws(__wargv[i]);
        string s;
        s.assign(ws.begin(), ws.end());
        args.push_back(s);
    }
    m_project.parseCommandLine(args);
}

void QuickXPlayer::loadOpenRecents(void)
{
    CRegistry *reg = new CRegistry(HKEY_CURRENT_USER, "quick-x\\quick-x-player\\recents");
    string jsonString;
    reg->ReadStringValue(jsonString);
    delete reg;

    if (jsonString.length() == 0)
    {
        jsonString = "{}";
    }
    CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
    string code("_G[\"OPEN_RECENTS\"] = '");
    code.append(jsonString);
    code.append("'");
    stack->executeString(code.c_str());
}

void QuickXPlayer::createRecentMenu(void)
{
    HMENU menu = GetMenu(m_hwnd);
    HMENU fileMenu = GetSubMenu(menu, 0);
    HMENU recentMenu = GetSubMenu(fileMenu, 2);

    CRegistry *reg = new CRegistry(HKEY_CURRENT_USER, "quick-x\\quick-x-player\\recents");
    string countString;
    reg->ReadStringValue(countString);
    int menuCount = atoi(countString.c_str());

    for (int i = menuCount-1; i >= 0; --i)
    {
        string title;
        reg->ReadStringValue(title, makeTitleKeyForIndex(i).c_str());

        string args;
        reg->ReadStringValue(args, makeArgsKeyForIndex(i).c_str());

        wstring menuName;
        menuName.assign(title.begin(), title.end());

        MENUITEMINFO item;
        ZeroMemory(&item, sizeof(item));
        item.cbSize = sizeof(item);
        item.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STRING;
        item.fType = MFT_STRING;
        item.wID = ID_OPENRECENT_F + i;
        item.dwTypeData = (LPTSTR)menuName.c_str();
        item.cch = menuName.length();

        InsertMenuItem(recentMenu, 0, TRUE, &item);
    }
    delete reg;
}

void QuickXPlayer::createViewMenu(void)
{
    HMENU menu = GetMenu(m_hwnd);
    HMENU viewMenu = GetSubMenu(menu, 1);

    for (int i = SimulatorConfig::sharedDefaults()->getScreenSizeCount() - 1; i >= 0; --i)
    {
        SimulatorScreenSize size = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        wstring menuName;
        menuName.assign(size.title.begin(), size.title.end());

        MENUITEMINFO item;
        ZeroMemory(&item, sizeof(item));
        item.cbSize = sizeof(item);
        item.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STRING;
        item.fType = MFT_STRING;
        item.wID = ID_VIEW_SIZE + i;
        item.dwTypeData = (LPTSTR)menuName.c_str();
        item.cch = menuName.length();

        InsertMenuItem(viewMenu, 0, TRUE, &item);
    }
}

void QuickXPlayer::updateOpenRecent(void)
{
    stringstream buff;
    buff << SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath();
    buff << "player\\welcome\\";
    string welcomeTitle = buff.str();
    if (welcomeTitle == m_project.getProjectDir()) return;

    CRegistry *reg = new CRegistry(HKEY_CURRENT_USER, "quick-x\\quick-x-player\\recents");
    string countString;
    reg->ReadStringValue(countString);
    int menuCount = atoi(countString.c_str());

    std::vector<string> titleArray;
    std::vector<string> argsArray;

    string currProjectTitle = m_project.getProjectDir();
    for (int i = 0; i < menuCount; i++)
    {
        string title;
        reg->ReadStringValue(title, makeTitleKeyForIndex(i).c_str());

        string args;
        reg->ReadStringValue(args, makeArgsKeyForIndex(i).c_str());

        if ((title.length() >= 0) && (welcomeTitle != title) && (currProjectTitle != title) && (CCFileUtils::sharedFileUtils()->isDirectoryExist(title)))
        {
            titleArray.push_back(title);
            argsArray.push_back(args);
        }
    }

    titleArray.insert(titleArray.begin(), m_project.getProjectDir());
    argsArray.insert(argsArray.begin(), m_project.makeCommandLine());
    for (size_t i = 0; i < titleArray.size(); i++)
    {
        reg->WriteStringValue(titleArray.at(i).c_str(), makeTitleKeyForIndex(i).c_str());
        reg->WriteStringValue(argsArray.at(i).c_str(),  makeArgsKeyForIndex(i).c_str());
    }

    {
        stringstream buff;
        buff << titleArray.size();
        reg->WriteStringValue(buff.str().c_str());
    }

    delete reg;
}

void QuickXPlayer::updateMenu(void)
{
    HMENU menu = GetMenu(m_hwnd);
    HMENU fileMenu = GetSubMenu(menu, 0);

    if (m_project.getDebuggerType() == kCCLuaDebuggerNone)
    {
        CheckMenuItem(fileMenu, ID_FILE_AUTO_CONNECT_DEBUGGER, MF_BYCOMMAND | MF_UNCHECKED);
    }
    else
    {
        CheckMenuItem(fileMenu, ID_FILE_AUTO_CONNECT_DEBUGGER, MF_BYCOMMAND | MF_CHECKED);
    }

    HMENU viewMenu = GetSubMenu(menu, 1);

    if (m_project.isLandscapeFrame())
    {
        CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_CHECKED);
    }
    else
    {
        CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_CHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_UNCHECKED);
    }

    if (m_project.getFrameScale() < 1.0f)
    {
        CheckMenuItem(viewMenu, ID_VIEW_RESET_ZOOM, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_ZOOM_OUT, MF_BYCOMMAND | MF_CHECKED);
    }
    else
    {
        CheckMenuItem(viewMenu, ID_VIEW_RESET_ZOOM, MF_BYCOMMAND | MF_CHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_ZOOM_OUT, MF_BYCOMMAND | MF_UNCHECKED);
    }

    int current = SimulatorConfig::sharedDefaults()->checkScreenSize(m_project.getFrameSize());
    for (int i = SimulatorConfig::sharedDefaults()->getScreenSizeCount() - 1; i >= 0; --i)
    {
        CheckMenuItem(viewMenu, i, MF_BYPOSITION | (i == current ? MF_CHECKED : MF_UNCHECKED));
    }
}

void QuickXPlayer::updateWindowTitle(void)
{
}

void QuickXPlayer::saveRecents(void)
{
    this->updateOpenRecent();
}

void QuickXPlayer::clearRecents(void)
{
    HMENU menu = GetMenu(m_hwnd);
    HMENU fileMenu = GetSubMenu(menu, 0);
    HMENU recentMenu = GetSubMenu(fileMenu, 2);

    CRegistry *reg = new CRegistry(HKEY_CURRENT_USER, "quick-x\\quick-x-player\\recents");
    string countString;
    reg->ReadStringValue(countString);
    int menuCount = atoi(countString.c_str());

    for (int i = 0; i < menuCount; i++)
    {
        RemoveMenu(recentMenu, 0, MF_BYPOSITION);
    }
    DrawMenuBar(m_hwnd);
    reg->WriteStringValue("0");
    delete reg;
}

void QuickXPlayer::relaunch(string &commandLine)
{
    saveRecents();

    TCHAR moduleName[MAX_PATH];
    ZeroMemory(moduleName, sizeof(moduleName));
    GetModuleFileName(NULL, moduleName, MAX_PATH);

    wstring ws;
    ws.append(L"\"");
    ws.append(moduleName);
    ws.append(L"\" ");
    ws.append(commandLine.begin(), commandLine.end());

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    lstrcpyW(moduleName, ws.c_str());
    if (CreateProcess(NULL, moduleName, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
    {
        ExitProcess(0);
    }
}

void QuickXPlayer::relaunch(void)
{
    string commandLine = m_project.makeCommandLine(kProjectConfigAll);
    relaunch(commandLine);
}

CCLuaValueArray QuickXPlayer::getOpenRecentsForLua(void)
{
    CCLuaValueArray ret;
    
    CRegistry *reg = new CRegistry(HKEY_CURRENT_USER, "quick-x\\quick-x-player\\recents");
    string countString;
    reg->ReadStringValue(countString);
    int menuCount = atoi(countString.c_str());

    for (int i =0; i < menuCount; ++i)
    {
        string title;
        reg->ReadStringValue(title, makeTitleKeyForIndex(i).c_str());
        ret.push_back(CCLuaValue::stringValue(title));
    }
    delete reg;

    return ret;
}

void QuickXPlayer::writeDebugLog(const char *log)
{
    if (!m_writeDebugLogFile) return;

    fputs(log, m_writeDebugLogFile);
    fputc('\n', m_writeDebugLogFile);
    fflush(m_writeDebugLogFile);
}

// welcome callback
void QuickXPlayer::onWelcomeNewProject(CCObject *object)
{
    MessageBox(m_hwnd, L"Coming soon :-)", L"quick-x-player", MB_OK);
}

void QuickXPlayer::onWelcomeOpen(CCObject *object)
{
    onFileOpenProject();
}

void QuickXPlayer::onWelcomeSamples(CCObject *object)
{
    ShellExecuteA(NULL, "open", SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void QuickXPlayer::onWelcomeGetStarted(CCObject *object)
{
    ShellExecuteA(NULL, "open", "http://cn.cocos2d-x.org/tutorial/index?type=quick-cocos2d-x", NULL, NULL, SW_SHOWNORMAL);
}

void QuickXPlayer::onWelcomeGetCommunity(CCObject *object)
{
    ShellExecuteA(NULL, "open", "http://www.cocoachina.com/bbs/thread.php?fid=56", NULL, NULL, SW_SHOWNORMAL);
}

void QuickXPlayer::onWelcomeOpenRecent(CCObject *object)
{
    CCString *data = dynamic_cast<CCString*> (object);
    if (data)
    {
        m_project.parseCommandLine(splitString(string(data->getCString()), ","));
        string commandLine = m_project.makeCommandLine();
        relaunch(commandLine);
    }

    CCInteger *intData = dynamic_cast<CCInteger*> (object);
    if (intData)
    {
        onOpenRecent(ID_OPENRECENT_F + intData->getValue());
    }
}

// menu callback
void QuickXPlayer::onFileNewProject(void)
{
}

void QuickXPlayer::onFileOpenProject(void)
{
    ProjectConfig project;
    if (!m_project.isWelcome())
    {
        project = m_project;
    }
    if (ProjectConfigDialog::showModal(m_hwnd, &project))
    {
        m_project = project;
        relaunch();
    }
}

void QuickXPlayer::onFileAutoConnectDebugger(void)
{
    if (m_project.getDebuggerType() == kCCLuaDebuggerNone)
    {
        m_project.setDebuggerType(kCCLuaDebuggerLDT);
    }
    else
    {
        m_project.setDebuggerType(kCCLuaDebuggerNone);
    }
    updateMenu();
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
        string args = m_project.makeCommandLine();

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

void QuickXPlayer::onFileWelcome(void)
{
    m_project.resetToWelcome();
    relaunch();
}

void QuickXPlayer::onFileExit(void)
{
    DestroyWindow(m_hwnd);
}

void QuickXPlayer::onFileRecentClear(void)
{
    clearRecents();
}

void QuickXPlayer::onViewChangeFrameSize(int viewMenuID)
{
    int index = viewMenuID - ID_VIEW_SIZE;

    if (index >= 0 && index < SimulatorConfig::sharedDefaults()->getScreenSizeCount())
    {
        SimulatorScreenSize size = SimulatorConfig::sharedDefaults()->getScreenSize(index);
        bool isLandscape = m_project.isLandscapeFrame();
        m_project.setFrameSize(CCSize(size.width, size.height));
        if (isLandscape)
        {
            m_project.changeFrameOrientationToLandscape();
        }
        else
        {
            m_project.changeFrameOrientationToPortait();
        }
        m_project.setFrameScale(1.0f);
        relaunch();
    }
}

void QuickXPlayer::onViewChangeOrientation(int viewMenuID)
{
    bool isLandscape = m_project.isLandscapeFrame();
    bool isNeedRelaunch = false;
    if (viewMenuID == ID_VIEW_PORTRAIT && isLandscape)
    {
        m_project.changeFrameOrientationToPortait();
        isNeedRelaunch = true;
    }
    else if (viewMenuID == ID_VIEW_LANDSCAPE && !isLandscape)
    {
        m_project.changeFrameOrientationToLandscape();
        isNeedRelaunch = true;
    }

    if (isNeedRelaunch) relaunch();
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
    updateMenu();
}

void QuickXPlayer::onOpenRecent(int recentID)
{
    int index = recentID - ID_OPENRECENT_F;

    CRegistry *reg = new CRegistry(HKEY_CURRENT_USER, "quick-x\\quick-x-player\\recents");
    string countString;
    reg->ReadStringValue(countString);
    int menuCount = atoi(countString.c_str());

    for (int i = menuCount-1; i >= 0; --i)
    {
        if (index == i)
        {
            string title;
            reg->ReadStringValue(title, makeTitleKeyForIndex(i).c_str());

            string args;
            reg->ReadStringValue(args, makeArgsKeyForIndex(i).c_str());

            relaunch(args);
            break;
        }
    }
    delete reg;
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

        case ID_FILE_AUTO_CONNECT_DEBUGGER:
            host->onFileAutoConnectDebugger();
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

        case ID_FILE_WELCOME:
            host->onFileWelcome();
            break;

        case ID_OPENRECENT_CLEAR:
            host->onFileRecentClear();
            break;

        case ID_FILE_EXIT:
            host->onFileExit();
            break;

        case ID_VIEW_PORTRAIT:
        case ID_VIEW_LANDSCAPE:
            host->onViewChangeOrientation(wmId);
            break;

        case ID_VIEW_RESET_ZOOM:
        case ID_VIEW_ZOOM_OUT:
            host->onViewChangeZoom(wmId);
            break;

        case ID_HELP_ABOUT:
            host->onHelpAbout();
            break;

        default:
            if (wmId >= ID_VIEW_SIZE && wmId <= ID_VIEW_SIZE + SimulatorConfig::sharedDefaults()->getScreenSizeCount() - 1)
            {
                host->onViewChangeFrameSize(wmId);
                break;
            }
            else if (wmId >= ID_OPENRECENT_F && wmId < ID_OPENRECENT_CLEAR)
            {
                host->onOpenRecent(wmId);
                break;
            }

            return 0;
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_F5)
        {
            host->onFileRelaunch();
        }
        break;

    case WM_COPYDATA:
        {
            PCOPYDATASTRUCT pMyCDS = (PCOPYDATASTRUCT) lParam;
            if (pMyCDS->dwData == CCLOG_STRING)
            {
                const char *szBuf = (const char*)(pMyCDS->lpData);
                sharedInstance()->writeDebugLog(szBuf);
                break;
            }
        }

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


///// helper /////
static std::string makeTitleKeyForIndex(int index)
{
    stringstream buff;
    buff << "m" << index << "_title";
    return buff.str();
}

static std::string makeArgsKeyForIndex(int index)
{
    stringstream buff;
    buff << "m" << index << "_args";
    return buff.str();
}

static std::vector<std::string> splitString(std::string str, std::string pattern)
{
    std::string::size_type        pos;
    std::vector<std::string>    result;
    str += pattern;
    int size = str.size();

    for(int i = 0; i < size; i++)
    {
        pos = str.find(pattern,i);
        if(pos < size)
        {
            std::string s = str.substr(i, pos-i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}
