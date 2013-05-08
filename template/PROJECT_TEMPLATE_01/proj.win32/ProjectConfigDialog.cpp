
#include "ProjectConfigDialog.h"
#include <Windowsx.h>
#include <Shlobj.h>

ProjectConfigDialog *ProjectConfigDialog::s_sharedInstance = NULL;

bool ProjectConfigDialog::showModal(HWND hwnd, ProjectConfig *project, const string dialogCaption, const string buttonCaption)
{
    ProjectConfigDialog *dialog = new ProjectConfigDialog(hwnd);
    bool ret = dialog->showDialog(project, dialogCaption, buttonCaption);
    delete dialog;
    return ret;
}

bool ProjectConfigDialog::showDialog(ProjectConfig *project, const string dialogCaption, const string buttonCaption)
{
    m_project = *project;
    m_dialogCaption = dialogCaption.length() > 0 ? dialogCaption : string("Project Config");
    m_buttonCaption = buttonCaption.length() > 0 ? buttonCaption : string("Open Project");
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PROJECT_CONFIG), m_hwnd, DialogCallback);
    if (m_dialogResult)
    {
        *project = m_project;
    }
    return m_dialogResult;
}

bool ProjectConfigDialog::checkConfig(void)
{
    bool isOK = false;
    char buff[MAX_PATH + 1] = {0};

    do
    {
        // check project dir and script file
        GetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, buff, MAX_PATH);
        m_project.setProjectDir(buff);
        GetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCRIPT_FILE, buff, MAX_PATH);
        m_project.setScriptFile(buff);

        if (!DirectoryExists(m_project.getProjectDir().c_str()))
        {
            MessageBox(m_hwndDialog, L"Invalid Project Directory, please check it", L"Error", MB_OK);
            SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_PROJECT_DIR));
            break;
        }

        if (!FileExists(m_project.getScriptFilePath().c_str()))
        {
            MessageBox(m_hwndDialog, L"Invalid Script File, please check it", L"Error", MB_OK);
            SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_SCRIPT_FILE));
            break;
        }

        // check screen size
        HWND list = GetDlgItem(m_hwndDialog, IDC_COMBO_SCREEN_SIZE);
        int index = ComboBox_GetCurSel(list);
        SimulatorConfig *defaults = SimulatorConfig::sharedDefaults();

        int w, h;
        if (index < defaults->numScreenSize())
        {
            const SimulatorScreenSize &size = defaults->getScreenSize(index);
            w = size.width;
            h = size.height;

            if (IsDlgButtonChecked(m_hwndDialog, IDC_RADIO_LANDSCAPE) == BST_CHECKED)
            {
                int w2 = w;
                w = h;
                h = w2;
            }
        }
        else
        {
            GetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH, buff, MAX_PATH);
            w = atoi(buff);
            GetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT, buff, MAX_PATH);
            h = atoi(buff);

            if (w <= 0)
            {

                MessageBox(m_hwndDialog, L"Invalid Screen Width, please check it", L"Error", MB_OK);
                SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH));
                break;
            }
            else if (h <= 0)
            {
                MessageBox(m_hwndDialog, L"Invalid Screen Height, please check it", L"Error", MB_OK);
                SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT));
                break;
            }
        }

        // ok
        m_project.setFrameSize(CCSize(w, h));
        m_project.setShowConsole(IsDlgButtonChecked(m_hwndDialog, IDC_CHECK_SHOW_DEBUG_CONSOLE) == TRUE);
        isOK = true;
    } while (false);

    return isOK;
}

void ProjectConfigDialog::onInitDialog(HWND hwndDialog)
{
    SimulatorConfig *defaults = SimulatorConfig::sharedDefaults();
    m_hwndDialog = hwndDialog;
    HWND list = GetDlgItem(m_hwndDialog, IDC_COMBO_SCREEN_SIZE);

    updateProjectDir();
    updateScriptFile();
    updatePackagePath();

    BOOL isLandscape = FALSE;
    int currentSizeIndex = defaults->checkScreenSize(m_project.getFrameSize());
    if (currentSizeIndex < 0)
    {
        currentSizeIndex = 0;
    }
    else
    {
        isLandscape = m_project.isLandscapeFrame();
    }

    for (int i = 0; i < defaults->numScreenSize(); ++i)
    {
        const SimulatorScreenSize &size = defaults->getScreenSize(i);
        wstring title;
        title.assign(size.title.begin(), size.title.end());
        ComboBox_AddString(list, title.c_str());

        if (i == currentSizeIndex)
        {
            char buff[32];
            sprintf_s(buff, "%d", isLandscape ? size.height : size.width);
            SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH, buff);
            sprintf_s(buff, "%d", isLandscape ? size.width : size.height);
            SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT, buff);
        }
    }
    ComboBox_AddString(list, L"Custom Size");
    ComboBox_SetCurSel(list, currentSizeIndex);

    Edit_LimitText(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH), 4);
    Edit_LimitText(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT), 4);

    HWND direction = GetDlgItem(m_hwndDialog, IDC_RADIO_PORTRAIT);
    CheckRadioButton(m_hwndDialog, IDC_RADIO_PORTRAIT, IDC_RADIO_LANDSCAPE, isLandscape ? IDC_RADIO_LANDSCAPE : IDC_RADIO_PORTRAIT);

    Button_SetCheck(GetDlgItem(m_hwndDialog, IDC_CHECK_SHOW_DEBUG_CONSOLE), m_project.isShowConsole());

    // set dialog caption, button caption
    SetWindowTextA(m_hwndDialog, m_dialogCaption.c_str());
    SetDlgItemTextA(m_hwndDialog, IDOK, m_buttonCaption.c_str());
    
    // center a dialog box within its owner window
    RECT rc, rcOwner, rcDlg;
    GetWindowRect(m_hwnd, &rcOwner); 
    GetWindowRect(m_hwndDialog, &rcDlg); 
    CopyRect(&rc, &rcOwner); 

    OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top); 
    OffsetRect(&rc, -rc.left, -rc.top); 
    OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom); 

    SetWindowPos(m_hwndDialog,
                 HWND_TOP,
                 rcOwner.left + (rc.right / 2),
                 rcOwner.top + (rc.bottom / 2),
                 0, 0,          // Ignores size arguments. 
                 SWP_NOSIZE);
}

void ProjectConfigDialog::onSelectProjectDir(void)
{
    string dir = browseFolder(m_project.getProjectDir());
    if (dir.length() > 0)
    {
        m_project.setProjectDir(dir);
        updateProjectDir();
        updateScriptFile();
        updatePackagePath();
    }
}

void ProjectConfigDialog::onSelectScriptFile(void)
{
    char buff[MAX_PATH + 1] = {0};
    char projdir[MAX_PATH + 1] = {0};
    GetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, projdir, MAX_PATH);

    OPENFILENAMEA ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hwndDialog;
    ofn.lpstrFilter = "Lua Script File (*.lua)\0*.lua\0";
    ofn.lpstrTitle = "Select Script File";
    if (DirectoryExists(projdir))
    {
        ofn.lpstrInitialDir = projdir;
    }
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrFile = buff;
    ofn.nMaxFile = MAX_PATH;

    if (GetOpenFileNameA(&ofn))
    {
        m_project.setScriptFile(buff);
        updateScriptFile();
    }
}

void ProjectConfigDialog::onScreenSizeChanged(void)
{
    HWND list = GetDlgItem(m_hwndDialog, IDC_COMBO_SCREEN_SIZE);
    int index = ComboBox_GetCurSel(list);
    SimulatorConfig *defaults = SimulatorConfig::sharedDefaults();

    int w, h;
    if (index < defaults->numScreenSize())
    {
        const SimulatorScreenSize &size = defaults->getScreenSize(index);
        w = size.width;
        h = size.height;

        if (IsDlgButtonChecked(m_hwndDialog, IDC_RADIO_LANDSCAPE) == BST_CHECKED)
        {
            int w2 = w;
            w = h;
            h = w2;
        }
    }
    else
    {
        w = -1; h = -1;
    }

    if (w > 0)
    {
        char buff[32];
        sprintf_s(buff, "%d", w);
        SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH, buff);
        sprintf_s(buff, "%d", h);
        SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT, buff);

        Edit_Enable(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH), FALSE);
        Edit_Enable(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT), FALSE);
    }
    else
    {
        Edit_Enable(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH), TRUE);
        Edit_Enable(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT), TRUE);
        SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH));
    }
}

void ProjectConfigDialog::onScreenDirectionChanged(void)
{
    char buff[32] = {0};
    GetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH, buff, 30);
    int w = atoi(buff);
    GetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT, buff, 30);
    int h = atoi(buff);

    bool isLandscape = IsDlgButtonChecked(m_hwndDialog, IDC_RADIO_LANDSCAPE) == BST_CHECKED;
    if ((isLandscape && w < h) || (!isLandscape && w > h))
    {
        sprintf_s(buff, "%d", h);
        SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_WIDTH, buff);
        sprintf_s(buff, "%d", w);
        SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCREEN_HEIGHT, buff);
    }
}

void ProjectConfigDialog::onListSelectChanged(void)
{
    int index = ListBox_GetCurSel(GetDlgItem(m_hwndDialog, IDC_LIST_PACKAGE_SEARCH_PATHS));
    Button_Enable(GetDlgItem(m_hwndDialog, IDC_BUTTON_REMOVE_SEARCH_PATH), index != LB_ERR);
}

void ProjectConfigDialog::onButtonAddSearchPathClicked(void)
{
    string dir = browseFolder(m_project.getProjectDir());
    if (dir.length() > 0)
    {
        m_project.addPackagePath(dir);
        updatePackagePath();
    }
}

void ProjectConfigDialog::onButtonRemoveSearchPathClicked(void)
{
    int index = ListBox_GetCurSel(GetDlgItem(m_hwndDialog, IDC_LIST_PACKAGE_SEARCH_PATHS));
    if (index != LB_ERR)
    {
        ListBox_DeleteString(GetDlgItem(m_hwndDialog, IDC_LIST_PACKAGE_SEARCH_PATHS), index);
        m_project.setPackagePath(makeSearchPath().c_str());
    }
}

void ProjectConfigDialog::onOK(void)
{
    if (checkConfig())
    {
        m_dialogResult = true;
    }
}


// callback

INT_PTR CALLBACK ProjectConfigDialog::DialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        sharedInstance()->onInitDialog(hDlg);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_SELECT_PROJECT_DIR:
            sharedInstance()->onSelectProjectDir();
            return (INT_PTR)TRUE;

        case IDC_BUTTON_SELECT_SCRIPT_FILE:
            sharedInstance()->onSelectScriptFile();
            return (INT_PTR)TRUE;

        case IDC_COMBO_SCREEN_SIZE:
            if (HIWORD(wParam) == CBN_SELENDOK)
            {
                sharedInstance()->onScreenSizeChanged();
                return (INT_PTR)TRUE;
            }
            break;

        case IDC_RADIO_PORTRAIT:
        case IDC_RADIO_LANDSCAPE:
            if (HIWORD(wParam) == BN_CLICKED || HIWORD(wParam) == BN_DBLCLK)
            {
                sharedInstance()->onScreenDirectionChanged();
                return (INT_PTR)TRUE;
            }
            break;

        case IDC_LIST_PACKAGE_SEARCH_PATHS:
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
                sharedInstance()->onListSelectChanged();
            }
            break;

        case IDC_BUTTON_ADD_SEARCH_PATH:
            sharedInstance()->onButtonAddSearchPathClicked();
            break;

        case IDC_BUTTON_REMOVE_SEARCH_PATH:
            sharedInstance()->onButtonRemoveSearchPathClicked();
            break;

        case IDOK:
            sharedInstance()->onOK();
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }

        break;
    }
    return (INT_PTR)FALSE;
}

int CALLBACK ProjectConfigDialog::BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED && lpData)
    {
        LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
        SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
    }
    return 0;
}


// update ui

void ProjectConfigDialog::updateProjectDir(void)
{
    SetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, m_project.getProjectDir().c_str());
}

void ProjectConfigDialog::updateScriptFile(void)
{
    SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCRIPT_FILE, m_project.getScriptFile().c_str());
}

void ProjectConfigDialog::updatePackagePath(void)
{
    HWND listbox = GetDlgItem(m_hwndDialog, IDC_LIST_PACKAGE_SEARCH_PATHS);
    ListBox_ResetContent(listbox);

    const vector<string> paths = m_project.getPackagePathArray();
    for (vector<string>::const_iterator it = paths.begin(); it != paths.end(); ++it)
    {
        wstring item;
        item.assign(it->begin(), it->end());
        ListBox_AddString(listbox, item.c_str());
    }
}

// helper

const string ProjectConfigDialog::makeSearchPath(void)
{
    HWND listbox = GetDlgItem(m_hwndDialog, IDC_LIST_PACKAGE_SEARCH_PATHS);
    int count = ListBox_GetCount(listbox);
    string path;
    for (int index = 0; index < count; ++index)
    {
        int buffsize = ListBox_GetTextLen(listbox, index);
        WCHAR *wbuff = new WCHAR[buffsize + 1];
        ListBox_GetText(listbox, index, wbuff);
        char *buff = new char[buffsize * 2 + 1];
        WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, buff, buffsize * 2, NULL, NULL);
        path.append(buff);
        if (index < count - 1) path.append(";");
        delete []buff;
        delete []wbuff;
    }
    return path;
}

const string ProjectConfigDialog::browseFolder(const string baseDir)
{
    char buff[MAX_PATH + 1] = {0};
    WCHAR curr[MAX_PATH + 1] = {0};

    if (baseDir.length() > 0)
    {
        MultiByteToWideChar(CP_UTF8, 0, baseDir.c_str(), baseDir.length(), curr, MAX_PATH);
    }
    else
    {
        GetCurrentDirectory(MAX_PATH + 1, curr);
    }

    BROWSEINFOA bi = {0};
    bi.hwndOwner = m_hwndDialog;
    bi.pszDisplayName = buff;
    bi.lpszTitle = "Select Project Directory";
    bi.lParam = reinterpret_cast<LPARAM>(curr);
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;

    PIDLIST_ABSOLUTE pid = SHBrowseForFolderA(&bi);
    if (pid)
    {
        SHGetPathFromIDListA(pid, buff);
        return string(buff);
    }
    else
    {
        return string("");
    }
}

BOOL ProjectConfigDialog::DirectoryExists(const string path)
{
    DWORD dwAttrib = GetFileAttributesA(path.c_str());
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL ProjectConfigDialog::FileExists(const string path)
{
    DWORD dwAttrib = GetFileAttributesA(path.c_str());
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
