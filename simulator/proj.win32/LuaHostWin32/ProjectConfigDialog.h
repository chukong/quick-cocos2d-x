#pragma once

#include "resource.h"

// C RunTime Header Files
#include "CCStdC.h"

#include <string>
#include "SimulatorConfig.h"

class ProjectConfigDialog
{
public:
    static bool showModal(HWND hwnd, ProjectConfig *project, const char *dialogCaption = NULL, const char *buttonCaption = NULL);
    ~ProjectConfigDialog(void) {
        s_sharedInstance = NULL;
    }

private:
    ProjectConfigDialog(HWND hwnd)
    : m_dialogResult(false)
    , m_hwnd(hwnd)
    , m_hwndDialog(NULL)
    {
        assert(s_sharedInstance == NULL);
        s_sharedInstance = this;
    }
    static ProjectConfigDialog *sharedInstance(void) {
        return s_sharedInstance;
    }

    static ProjectConfigDialog *s_sharedInstance;
    ProjectConfig m_project;
    string m_dialogCaption;
    string m_buttonCaption;
    bool m_dialogResult;
    HWND m_hwnd;
    HWND m_hwndDialog;

    bool showDialog(ProjectConfig *project, const char *dialogCaption, const char *buttonCaption);
    bool checkConfig(void);

    void onInitDialog(HWND hwndDialog);
    void onSelectProjectDir(void);
    void onSelectScriptFile(void);
    void onScreenSizeChanged(void);
    void onScreenDirectionChanged(void);
	void onListSelectChanged(void);
	void onButtonAddSearchPathClicked(void);
	void onButtonRemoveSearchPathClicked(void);
    void onOK(void);

    // windows callback
    static INT_PTR CALLBACK DialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	// helper
	const string makeSearchPath(void);
	static BOOL DirectoryExists(const char *path);
	static BOOL FileExists(const char *path);
};
