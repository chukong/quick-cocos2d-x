
#include "ProjectConfigDialog.h"
#include <Windowsx.h>
#include <Shlobj.h>

ProjectConfigDialog *ProjectConfigDialog::s_sharedInstance = NULL;

bool ProjectConfigDialog::showModal(HWND hwnd, ProjectConfig *project, const char *dialogCaption, const char *buttonCaption)
{
    ProjectConfigDialog *dialog = new ProjectConfigDialog(hwnd);
    bool ret = dialog->showDialog(project, dialogCaption, buttonCaption);
    delete dialog;
    return ret;
}

bool ProjectConfigDialog::showDialog(ProjectConfig *project, const char *dialogCaption, const char *buttonCaption)
{
    m_project = *project;
    m_dialogCaption = string(dialogCaption ? dialogCaption : "Project Config");
    m_buttonCaption = string(buttonCaption ? buttonCaption : "Open Project");
    DialogBox(GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDD_PROJECT_CONFIG),
        m_hwnd,
        DialogCallback);
    if (m_dialogResult)
    {
        *project = m_project;
    }
    return m_dialogResult;
}

BOOL DirectoryExists(const char *path)
{
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL FileExists(const char *path)
{
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool ProjectConfigDialog::checkConfig(void)
{
    bool isOK = false;
    char buff[MAX_PATH + 1] = {0};

    do
    {
        // check project dir
        GetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, buff, MAX_PATH);
        if (!DirectoryExists(buff))
        {
            MessageBox(m_hwndDialog, L"Invalid Project Directory, please check it", L"Error", MB_OK);
            SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_PROJECT_DIR));
            break;
        }

        int len = strlen(buff);
        if (buff[len - 1] != '\\')
        {
            buff[len] = '\\';
            buff[len + 1] = '\0';
        }
        string projectDir(buff);

        // check script file
        GetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCRIPT_FILE, buff, MAX_PATH);
        string scriptFile(buff);
        string scriptPath((buff[1] == ':') ? buff : projectDir);
        if (buff[1] != ':')
        {
            scriptPath.append(buff[0] == '\\' ? buff + 1 : buff);
        }

        if (!FileExists(scriptPath.c_str()))
        {
            MessageBox(m_hwndDialog, L"Invalid Script File, please check it", L"Error", MB_OK);
            SetFocus(GetDlgItem(m_hwndDialog, IDC_EDIT_SCRIPT_FILE));
            break;
        }

        // check screen size
        HWND list = GetDlgItem(m_hwndDialog, IDC_COMBO_SCREEN_SIZE);
        int index = ComboBox_GetCurSel(list);
        ProjectConfigDefaults *defaults = ProjectConfigDefaults::sharedDefaults();

        int w, h;
        if (index < defaults->getScreenSizeCount())
        {
            const ScreenSizeDescription &size = defaults->getScreenSize(index);
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
        m_project.projectDir = projectDir.substr(0, projectDir.length() - 1);
        m_project.scriptFile = scriptFile;
        m_project.frameWidth = w;
        m_project.frameHeight = h;
        m_project.showConsole = IsDlgButtonChecked(m_hwndDialog, IDC_CHECK_SHOW_DEBUG_CONSOLE) == TRUE;
        isOK = true;
    } while (false);

    return isOK;
}

void ProjectConfigDialog::onInitDialog(HWND hwndDialog)
{
    ProjectConfigDefaults *defaults = ProjectConfigDefaults::sharedDefaults();
    m_hwndDialog = hwndDialog;
    HWND list = GetDlgItem(m_hwndDialog, IDC_COMBO_SCREEN_SIZE);

    SetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, m_project.projectDir.c_str());
    SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCRIPT_FILE, m_project.scriptFile.c_str());

    bool isLandscape = false;
    int currentSizeIndex = defaults->checkScreenSize(m_project.frameWidth, m_project.frameHeight);
    if (currentSizeIndex < 0)
    {
        currentSizeIndex = 0;
    }
    else
    {
        isLandscape = defaults->isLandscape(m_project.frameWidth, m_project.frameHeight);
    }

    for (int i = 0; i < defaults->getScreenSizeCount(); ++i)
    {
        const ScreenSizeDescription &size = defaults->getScreenSize(i);
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

    Button_SetCheck(GetDlgItem(m_hwndDialog, IDC_CHECK_SHOW_DEBUG_CONSOLE), m_project.showConsole);

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

int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED)
    {
        LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
        SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
    }
    return 0;
}

void ProjectConfigDialog::onSelectProjectDir(void)
{
    char buff[MAX_PATH + 1] = {0};
    WCHAR curr[MAX_PATH + 1] = {0};
    GetDlgItemText(m_hwndDialog, IDC_EDIT_PROJECT_DIR, curr, MAX_PATH);

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
        SetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, buff);
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
        string scriptFile(buff);
        GetDlgItemTextA(m_hwndDialog, IDC_EDIT_PROJECT_DIR, buff, MAX_PATH);
        string projectDir(buff);
        int projectDirLength = projectDir.length();
        if (_stricmp(scriptFile.substr(0, projectDirLength).c_str(), projectDir.c_str()) == 0)
        {
            scriptFile = scriptFile.substr(projectDirLength + 1);
        }
        SetDlgItemTextA(m_hwndDialog, IDC_EDIT_SCRIPT_FILE, scriptFile.c_str());
    }
}

void ProjectConfigDialog::onScreenSizeChanged(void)
{
    HWND list = GetDlgItem(m_hwndDialog, IDC_COMBO_SCREEN_SIZE);
    int index = ComboBox_GetCurSel(list);
    ProjectConfigDefaults *defaults = ProjectConfigDefaults::sharedDefaults();

    int w, h;
    if (index < defaults->getScreenSizeCount())
    {
        const ScreenSizeDescription &size = defaults->getScreenSize(index);
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

void ProjectConfigDialog::onOK(void)
{
    if (checkConfig())
    {
        m_dialogResult = true;
    }
}

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
