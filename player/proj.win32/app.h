
#pragma once

#include "resource.h"

// C RunTime Header Files
#include "CCStdC.h"

#include <string>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "ProjectConfig/SimulatorConfig.h"

using namespace std;
using namespace cocos2d;

class CC_DLL QuickXPlayer : public CCObject
{
public:
    static int createAndRun(void);

    AppDelegate *getApp(void) {
        return m_app;
    }

    HWND getWindowHandle(void) {
        return m_hwnd;
    }
    
private:
    static QuickXPlayer *s_sharedInstance;
    static QuickXPlayer *sharedInstance(void);
    static void purgeSharedInstance(void);

    QuickXPlayer(void);

    AppDelegate *m_app;
    ProjectConfig m_project;

    HWND m_hwnd;
    BOOL m_exit;
    FILE *m_writeDebugLogFile;

    int run(void);
    void loadProjectConfig(void);
    void loadOpenRecents(void);
    void createRecentMenu(void);
    void createViewMenu(void);
    void updateOpenRecent(void);
    void updateMenu(void);
    void updateWindowTitle(void);
    void saveRecents(void);
    void clearRecents(void);
    void relaunch(void);
    void relaunch(string &commandLine);
    CCLuaValueArray getOpenRecentsForLua(void);
    
    // debug log
    void writeDebugLog(const char *log);

    // welcome callback
    void onWelcomeNewProject(CCObject *object);
    void onWelcomeOpen(CCObject *object);
    void onWelcomeSamples(CCObject *object);
    void onWelcomeGetStarted(CCObject *object);
    void onWelcomeGetCommunity(CCObject *object);
    void onWelcomeOpenRecent(CCObject *object);

    // menu callback
    void onFileNewProject(void);
    void onFileOpenProject(void);
    void onFileAutoConnectDebugger(void);
    void onFileCreateProjectShortcut(void);
    void onFileProjectConfig(void);
    void onFileRelaunch(void);
    void onFileWelcome(void);
    void onFileExit(void);
    void onFileRecentClear(void);

    void onViewChangeFrameSize(int viewMenuID);
    void onViewChangeOrientation(int viewMenuID);
    void onViewChangeZoom(int scaleMode);

    void onOpenRecent(int recentId);

    void onHelpAbout(void);

    // windows callback
    static LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pProcessed);
    static INT_PTR CALLBACK AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    static INT CALLBACK OpenProjectCallback(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData);
};
