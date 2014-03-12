#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SimulatorConfig.h"
#include "quickdemowebview.h"

#define RESTART_ARGS "restart_args"
#define APP_EXIT_CODE 'q'
#define ENV_KEY_QUICK_ROOT_PATH "QUICK_COCOS2DX_ROOT"

class QTextBrowser;
class MainMenu : public QObject
{
    Q_OBJECT

public:
    explicit MainMenu(QObject *parent = 0);
    ~MainMenu();
    static MainMenu *instance();

    void setProjectConfig(const ProjectConfig& config);
    ProjectConfig getProjectConfig();

    // for Lua
    static void registerAllCpp();
    static int openURL(lua_State *L);        /* path: 使用系统默认的方式打开 */
    static int openQuickDemoWithWebView(lua_State *L);
    static int newProject(lua_State *L);
    static int onOpenProject(lua_State *L);
    static int showLoginUI(lua_State *L);

    static void openURLHelper(const char *path);
    static void showLoginUIHelper();

public Q_SLOTS:
    void onOpenQuickDemoWebview();
    void onShowOpenCocoaChinaWebView();
    void onShowConsole();
    void onShowLoginUI();
    void restartWithProjectConfig(ProjectConfig &config);
    void onNewProject();

protected:
    void initMenu();

    // engine
    void restart();
    void applySettingAndRestart();
    void openlocalFolderOrFile(std::string filePath);

private Q_SLOTS:
    void on_actionRelaunch_triggered();
    void on_actionOpen_triggered();

    void onScreenSizeTriggered();
    void onLandscapeTriggered();
    void onScreenScaleTriggered();
    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionConfig_triggered();


private:
    QString         m_projectConfigFileName;
    ProjectConfig   m_projectConfig;
    QWidget         *m_renderWidget;

    QMenu           *m_viewMenu;
    QAction         *m_landscapeAction, *m_portraitAction;
    QTextBrowser    *m_textBrowser;
    QuickDemoWebView m_quickDemoWebview;
    QWebView         m_cocoaChinaWebview;
};

#endif // MAINWINDOW_H
