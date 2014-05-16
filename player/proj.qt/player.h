#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ProjectConfig/SimulatorConfig.h"
#include "FastDelegate.h"
#include "msghandlerwapper.h"

#define RESTART_ARGS            "restart_args"
#define APP_EXIT_CODE           'q'
#define ENV_KEY_QUICK_ROOT_PATH "QUICK_COCOS2DX_ROOT"
#define kOpenRecentFiles        "recents"
#define kRecentItemTitle        "title"

class QTextBrowser;
class ConsoleUI;
class ProjectConfigUI;
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

    void initConsole();
    void setLogFileName(QString fileName);
    void initMainMenu();

    void makeMainWindow(QWidget *w, QMenuBar *bar);

    QMenuBar *getMenuBar();

    /**
     * @brief getCreateProjectCommand - [-f -p com.quick2dx.samples.hello -r landscape -o "/tmp/hello"]
     * @param projectPath
     * @param packageName
     * @param isPortrait
     * @return
     */
    QStringList getCreateProjectCommandArgs(QString projectPath, QString packageName, bool isPortrait);

    /**
     * @brief loadLuaBridgeModule
     * 加载 welcome/script/bridge.lua 文件
     * player 与 lua 交互的文件, 如 创建工程的参数, 样例数据等等
     */
    void loadLuaBridgeModule();

    void restoreSetting();
    void saveSetting();

    fastdelegate::FastDelegate0<void> enterBackgroundDelegate;
    fastdelegate::FastDelegate0<void> enterForegroundDelegate;
public Q_SLOTS:
    void onShowOpenCocoaChinaWebView();
    void onShowConsole();
    void onShowLoginUI();
    void restartWithProjectConfig(ProjectConfig &config);
    void onNewProject();
    void onOpenProject();
    void onOpenProjectWithArgs(QString data);
    void doOpenProject();
    void onCreateNewPlayer();
    void onCreateNewPlayerWithArgs(QString data);
    void onClose();
    void onShowWelcome();
    void onCreateSnapshot();
    void onCreateShortcut();
    void onWriteDebugLog(bool);
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
    // save ENV & restart play
    void onSaveQuickRootPath(QString absPath);
    QString getQuickRootPathFromSystem();
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

    bool eventFilter(QObject *, QEvent *);

    /**
     * @brief processKeyboardEvent - process the shortcut
     * @param e
     */
    void processKeyboardEvent(QKeyEvent *e);

    QKeySequence convertKeyEventToKeySequence(QKeyEvent *e);

private Q_SLOTS:
    void on_actionRelaunch_triggered();
    void on_actionOpen_triggered();

    void onScreenSizeTriggered();
    void onLandscapeTriggered();
    void onScreenScaleTriggered();
    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionConfig_triggered();

    void onLogin(QString userName, QString password);

    void sendMessageToLua(QString eventId, QString eventData);

private:
    QString         m_projectConfigFileName;
    ProjectConfig   m_projectConfig;

    QMenuBar        *m_mainMenu;
    QMenu           *m_screenMenu;
    QMenu           *m_openRecentMenu;
    QList<QAction*> m_recentFileActionList;
    QAction         *m_landscapeAction, *m_portraitAction;
    QAction         *m_writeDebugAction;

    ConsoleUI       *m_consoleUI;
    ProjectConfigUI *m_projectConfigUI;
    QMap<QKeySequence, QAction*> m_actionMap;
#ifdef Q_OS_WIN
    QWidget	        *m_mainWindow;
	QWidget			*m_container;
#endif

    QVariantMap     m_settings;
    QPoint          m_playerPosition;
};
Q_DECLARE_METATYPE(const char *);

#endif // MAINWINDOW_H
