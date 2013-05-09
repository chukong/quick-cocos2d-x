
#pragma once

#include "resource.h"

// C RunTime Header Files
#include "CCStdC.h"

#include <string>
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimulatorConfig.h"

using namespace std;
using namespace cocos2d;

class app
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
    static app *s_sharedInstance;
    static app *sharedInstance(void);
    static void purgeSharedInstance(void);

    app(void);

    AppDelegate *m_app;
    ProjectConfig m_project;

    HWND m_hwnd;
    BOOL m_exit;

    int run(void);
    void loadProjectConfig(void);
    void updateWindowTitle(void);
    void relaunch(void);

    // menu callback
    void onFileNewProject(void);
    void onFileOpenProject(void);
    void onFileCreateProjectShortcut(void);
    void onFileProjectConfig(void);
    void onFileRelaunch(void);
    void onFileExit(void);

    void onViewChangeFrameSize(int index);
    void onViewChangeDirection(int directionMode);
    void onViewChangeZoom(int scaleMode);

    void onHelpAbout(void);

    // windows callback
    static LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pProcessed);
    static INT_PTR CALLBACK AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    static INT CALLBACK OpenProjectCallback(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData);

    // helper
    const string getCommandLineArg(int index);
};
