#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SimulatorConfig.h"
#include "quickdemowebview.h"
#include "FastDelegate.h"

#define RESTART_ARGS "restart_args"
#define APP_EXIT_CODE 'q'
#define ENV_KEY_QUICK_ROOT_PATH "QUICK_COCOS2DX_ROOT"

class QTextBrowser;
class Player : public QObject
{
    Q_OBJECT

public:    
    static Player *instance();
    ~Player();

    void setProjectConfig(const ProjectConfig& config);
    ProjectConfig getProjectConfig();

    // for Lua
    static void registerAllCpp();
    static int openURL(lua_State *L);        /* path: 使用系统默认的方式打开 */
    static int openQuickDemoWithWebView(lua_State *L);
    static int newProject(lua_State *L);
    static int openProject(lua_State *L);
    static int showLoginUI(lua_State *L);
    /**
     * @brief Interface for Lua
     *          ['messageName', '{}'] -> core.toolBar, json string
     * @param L
     * @return
     */
    static int sendMessage(lua_State *L);

    /**
     * @brief eventDispatch
     * @param messageName   : 'core.toolbar'
     * @param data          : '{}' json string
     */
    void eventDispatch(QString messageName, QString data);

    void initMainMenu();
    void makeMainWindow(QWindow *w, QMenuBar *bar);

    QMenuBar *getMenuBar();

    fastdelegate::FastDelegate0<void> enterBackgroundDelegate;
    fastdelegate::FastDelegate0<void> enterForegroundDelegate;
public Q_SLOTS:
    void onOpenQuickDemoWebview();
    void onShowOpenCocoaChinaWebView();
    void onShowConsole();
    void onShowLoginUI();
    void restartWithProjectConfig(ProjectConfig &config);
    void onNewProject();
    void onOpenProject();
    void onCreateNewPlayer();
    void onClose();
    void onShowWelcome();
    void onOpenDebugLog(bool);
    void onUploadToDevice();
    void onCreateLauncher();
    void onAutoConnectDebugger();
    void onBuildIOS();
    void onBuildAndroid();
    void onShowProjectSandBox();
    void onShowProjectFiles();
    void onShowPreferences();
    void onMainWidgetOnTop(bool checked);
    void onOpenURL(const char *path);
    void onRestartWithArgs(QStringList args);
    void openDemoWithArgs(QString cmds);
    void onSaveQuickRootPath(QString absPath);
    void onOpenRecentProject();
    void onClearRecentMenu();

    // device
    void onEnterBackground();
    void onEnterForeground();
    void onMemoryWarning();

protected:
    Player(QObject *parent = 0);

    void initScreenMenu();

    // engine
    void restart();
    void applySettingAndRestart();

    void checkQuickRootPath();
    void updateTitle();

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

    QMenuBar        *m_mainMenu;
    QMenu           *m_screenMenu;
    QMenu           *m_openRecentMenu;
    QList<QAction*> m_recentFileActionList;
    QAction         *m_landscapeAction, *m_portraitAction;

#ifdef Q_OS_WIN
    QMainWindow     *m_mainWindow;
#endif
};
Q_DECLARE_METATYPE(const char *);

#endif // MAINWINDOW_H
