#include "player.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextBrowser>
#include <QFile>
#include <QScrollBar>
#include <QMenuBar>
#include <QTimer>
#include <QApplication>
#include <QWebFrame>
#include <QDesktopServices>
#include <QProcess>
#include <QDebug>

// 3rd library
#include "cocos2d.h"
#include "CCLuaEngine.h"

// ui
#include "aboutui.h"
#include "projectconfigui.h"
#include "createprojectui.h"
#include "consoleui.h"
#include "logindialog.h"
#include "preferenceui.h"

#define kPortrait 1
#define kLandscape 2

struct ActionData
{
    QString         text;
    QKeySequence    keySequence;
    QVariant        userData;
};

Player::Player(QObject *parent)
    : QObject(parent)
    , m_renderWidget(0)
    , m_mainMenu(0)
#ifdef Q_OS_WIN
    , m_mainWindow(0)
#endif
{
    qRegisterMetaType<const char *>("const char *");
}

Player::~Player()
{
    CC_SAFE_DELETE(m_mainMenu);
}

Player *Player::instance()
{
    static Player *player = NULL;
    if (!player)
    {
        player = new Player;
    }
    return player;
}

void Player::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
    initScreenMenu();
}

ProjectConfig Player::getProjectConfig()
{
    return m_projectConfig;
}

int Player::openURL(lua_State *L)
{
    //从栈中读入实部，虚部
    const char *path = lua_tostring(L, 1);
    Player::instance()->onOpenURL(path);
    return 0;
}

int Player::openQuickDemoWithWebView(lua_State * /*L*/)
{
    Player::instance()->onOpenQuickDemoWebview();
    return 0;
}

int Player::newProject(lua_State * /*L*/)
{
    CreateProjectUI ui(0);
    if (ui.exec() == QDialog::Accepted) {
        ui.createNewProject();
    }
    return 0;
}

void Player::onOpenProject()
{
    ProjectConfig config = Player::instance()->getProjectConfig();
    ProjectConfigUI ui(config, 0);
    if (ui.exec() == QDialog::Accepted)
    {
        config = ui.getProjectConfig();
        Player::instance()->restartWithProjectConfig(config);
    }
}

int Player::openProject(lua_State * /*L*/)
{
    Player::instance()->onOpenProject();
    return 0;
}

int Player::showLoginUI(lua_State * /*L*/)
{
    Player::instance()->onShowLoginUI();
    return 0;
}

int Player::sendMessage(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc > 0)
    {
        //从栈中读入实部，虚部
        const char *funName = lua_tostring(L, 1);
        if (argc == 1)
        {
            QMetaObject::invokeMethod(Player::instance(), funName,
                                      Qt::QueuedConnection);
        }
        else if (argc == 2)
        {
            if (lua_isstring(L, 2))
            {
                const char *data = lua_tostring(L, 2);
                QMetaObject::invokeMethod(Player::instance(), funName,
                                          Qt::QueuedConnection,
                                          Q_ARG(const char *, data));
            }
            else
            {

            }
        }
        else
        {
            QMetaObject::invokeMethod(Player::instance(), funName, Qt::QueuedConnection);
        }
    }
    return 0;
}

void Player::onOpenURL(const char *path)
{
    QString tmpPath(path);
    if (tmpPath.startsWith("http://"))
        QDesktopServices::openUrl(QUrl(tmpPath));
    else
        QDesktopServices::openUrl(QUrl::fromLocalFile(tmpPath));
}

void Player::onRestartWithArgs(QStringList args)
{
    qApp->setProperty(RESTART_ARGS, args);
    qApp->exit(APP_EXIT_CODE);
}

void Player::openDemoWithArgs(QString cmds)
{
    QStringList args = cmds.split(",");
    Player::instance()->onRestartWithArgs(args);
}

void Player::onSaveQuickRootPath(QString absPath)
{
    QSettings settings;
    settings.setValue(ENV_KEY_QUICK_ROOT_PATH, absPath);
    settings.sync();
}

void Player::registerAllCpp()
{
    lua_State *L = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    lua_register(L, "openURL", &Player::openURL);
    lua_register(L, "openQuickDemoWithWebView", &Player::openQuickDemoWithWebView);
    lua_register(L, "newProject", &Player::newProject);
    lua_register(L, "openProject", &Player::openProject);
    lua_register(L, "showLoginUI", &Player::showLoginUI);
    lua_register(L, "sendMessage", &Player::sendMessage);
}

void Player::initMainMenu()
{
#ifdef Q_OS_MAC
    m_mainMenu = new QMenuBar(0);
    m_mainMenu->setNativeMenuBar(true);
#else
    m_mainMenu = new QMenuBar(m_renderWidget);
#endif

    //
    // file menu
    //

    QMenu *fileMenu = m_mainMenu->addMenu(QObject::tr("&File"));
    fileMenu->addAction(QObject::tr("&New Project..."), this, SLOT(onNewProject()), QKeySequence(Qt::CTRL + Qt::Key_N));
    fileMenu->addAction(QObject::tr("New Player"), this, SLOT(onCreateNewPlayer()), QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_N));

    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("&Open"), this, SLOT(on_actionOpen_triggered()), QKeySequence(Qt::CTRL + Qt::Key_O));

    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("Welcome"), this, SLOT(onShowWelcome()));

    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("&Close"), this, SLOT(onClose()), QKeySequence(Qt::CTRL + Qt::Key_W));

    //
    // player menu
    //

    QMenu *playerMenu = m_mainMenu->addMenu(QObject::tr("Player"));
    playerMenu->addAction(QObject::tr("Write Debug Log to File"))->setCheckable(true);

    QAction *openDebugLogAction = playerMenu->addAction(QObject::tr("Open Debug Log"));
    openDebugLogAction->setCheckable(true);
    connect(openDebugLogAction, SIGNAL(triggered(bool)), SLOT(onOpenDebugLog(bool)));

    playerMenu->addAction(tr("Upload to Device..."), this, SLOT(onUploadToDevice()))->setEnabled(false);

    playerMenu->addAction(tr("Create Launcher"), this, SLOT(onCreateLauncher()))->setEnabled(false);

    playerMenu->addAction(tr("Auto Connect Debugger"), this, SLOT(onAutoConnectDebugger()))->setCheckable(true);

    playerMenu->addSeparator();
    QMenu *buildMenu = playerMenu->addMenu(tr("Build"));

    QAction *buildIOSMenu = buildMenu->addAction(tr("iOS..."), this, SLOT(onBuildIOS()), QKeySequence(Qt::CTRL + Qt::Key_B));
    buildIOSMenu->setEnabled(false);

    QAction *buildAndroidMenu = buildMenu->addAction(tr("Android..."), this, SLOT(onBuildAndroid()));
    buildAndroidMenu->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_B));
    buildAndroidMenu->setEnabled(false);

    playerMenu->addSeparator();
    QAction *relaunchAction = playerMenu->addAction(QObject::tr("&Relaunch"), this, SLOT(on_actionRelaunch_triggered()));
#ifdef Q_OS_MAC
    relaunchAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
#else   // windows, *nix and others
    relaunchAction->setShortcut(QKeySequence(Qt::Key_F5));
#endif

    playerMenu->addSeparator();
    playerMenu->addAction(tr("Show Project Sandbox"), this, SLOT(onShowProjectSandBox()));

    playerMenu->addAction(tr("Show Porject Files"), this, SLOT(onShowProjectFiles()));

    //
    // screen menu
    //

    m_screenMenu = m_mainMenu->addMenu(QObject::tr("&Screen"));

    //
    // window
    //
    QMenu *windowMenu = m_mainMenu->addMenu(tr("Window"));
    {
        QAction *onTopAction = windowMenu->addAction(tr("Allways On Top"));
        onTopAction->setCheckable(true);
        connect(onTopAction, SIGNAL(triggered(bool)), this, SLOT(onMainWidgetOnTop(bool)));
    }

    //
    // more menu
    //

    QMenu *moreMenu = m_mainMenu->addMenu(QObject::tr("&More"));
    moreMenu->addAction("&AboutQt", this, SLOT(on_actionAboutQt_triggered()));
    moreMenu->addAction("&About", this, SLOT(on_actionAbout_triggered()));
    moreMenu->addAction("&Simples", this, SLOT(onOpenQuickDemoWebview()));
    moreMenu->addAction("open.cocoachina.com", this, SLOT(onShowOpenCocoaChinaWebView()));
    moreMenu->addAction("show console", this, SLOT(onShowConsole()));
    moreMenu->addAction("Login Test", this, SLOT(onShowLoginUI()));

    m_mainMenu->show();
    m_mainMenu->raise();

    //
    // Preferences
    //
    QAction *m_preference = moreMenu->addAction(tr("Preferences"));
    m_preference->setMenuRole(QAction::PreferencesRole);
    connect(m_preference, SIGNAL(triggered()), this, SLOT(onShowPreferences()));
}

void Player::makeMainWindow(QWindow *w, QMenuBar *bar)
{
#ifdef Q_OS_WIN
    if (bar && w)
    {
        bar->show();
        m_mainWindow = new QMainWindow();
        m_mainWindow->setAttribute(Qt::WA_DeleteOnClose);
        m_mainWindow->setMenuBar(bar);
        QSize size = w->size();// + QSize(0, bar->size().height());
        m_mainWindow->setCentralWidget(QWidget::createWindowContainer(w));
        m_mainWindow->setFixedSize(size);
        m_mainWindow->show();
    }
#endif
}

QMenuBar *Player::getMenuBar()
{
    return this->m_mainMenu;
}

void Player::initScreenMenu()
{
    //
    // create screen size
    //
    QActionGroup *actionGroup = new QActionGroup(this);
    CCSize size = m_projectConfig.getFrameSize();
    for (int i = 0; i < SimulatorConfig::sharedDefaults()->getScreenSizeCount(); i++)
    {
        const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        QAction *action = m_screenMenu->addAction(QString::fromLocal8Bit(screenSize.title.data()));
        action->setCheckable(true);
        action->setEnabled(true);
        action->setData(i);
        connect(action, SIGNAL(triggered()), this, SLOT(onScreenSizeTriggered()));
        actionGroup->addAction(action);

        if ((size.width == screenSize.width && size.height == screenSize.height) ||
            (size.width == screenSize.height && size.height == screenSize.width))
        {
            action->setChecked(true);
        }
    }

    m_screenMenu->addSeparator();

    //
    // Landscape or Portrait
    //
    actionGroup = new QActionGroup(this);

    m_landscapeAction = m_screenMenu->addAction(tr("Landscape"));
    m_landscapeAction->setData(kLandscape);
    m_landscapeAction->setCheckable(true);
    connect(m_landscapeAction, SIGNAL(triggered()), this, SLOT(onLandscapeTriggered()));

    m_portraitAction = m_screenMenu->addAction(tr("Portrait"));
    m_portraitAction->setData(kPortrait);
    m_portraitAction->setCheckable(true);
    connect(m_portraitAction, SIGNAL(triggered()), this, SLOT(onLandscapeTriggered()));

    actionGroup->addAction(m_landscapeAction);
    actionGroup->addAction(m_portraitAction);

    if (m_projectConfig.isLandscapeFrame())
        m_landscapeAction->setChecked(true);
    else
        m_portraitAction->setChecked(true);

    m_screenMenu->addSeparator();

    //
    // scale
    //
    actionGroup = new QActionGroup(this);
    QList<ActionData> screenScaleDataList;
    {
        ActionData actionData;
        actionData.text = tr("Actual (100%)");
        actionData.keySequence = QKeySequence(Qt::CTRL + Qt::Key_0);
        actionData.userData = 1.0f;
        screenScaleDataList << actionData;
    }
    {
        ActionData actionData;
        actionData.text = tr("Zoom Out (75%)");
        actionData.keySequence = QKeySequence(Qt::CTRL + Qt::Key_6);
        actionData.userData = 0.75f;
        screenScaleDataList << actionData;
    }
    {
        ActionData actionData;
        actionData.text = tr("Zoom Out (50%)");
        actionData.keySequence = QKeySequence(Qt::CTRL + Qt::Key_5);
        actionData.userData = 0.5f;
        screenScaleDataList << actionData;
    }
    {
        ActionData actionData;
        actionData.text = tr("Zoom Out (25%)");
        actionData.keySequence = QKeySequence(Qt::CTRL + Qt::Key_4);
        actionData.userData = 0.25f;
        screenScaleDataList << actionData;
    }
    Q_FOREACH(ActionData actionData, screenScaleDataList)
    {
        QAction *scaleAction = m_screenMenu->addAction(actionData.text);
        actionGroup->addAction(scaleAction);
        scaleAction->setCheckable(true);
        scaleAction->setShortcut(actionData.keySequence);
        scaleAction->setData(actionData.userData);
        connect(scaleAction, SIGNAL(triggered()), this, SLOT(onScreenScaleTriggered()));
        if (int(m_projectConfig.getFrameScale()*100) == int(actionData.userData.toFloat()*100)) {
            scaleAction->setChecked(true);
        }
    }
}

void Player::restart()
{
    qApp->exit(APP_EXIT_CODE);
}

void Player::applySettingAndRestart()
{
    QStringList args;

    QString cmd(m_projectConfig.makeCommandLine().data());
    args = cmd.split(" ");
    qDebug() << args;
    qApp->setProperty(RESTART_ARGS, args);
    this->restart();
}

void Player::on_actionRelaunch_triggered()
{
    this->applySettingAndRestart();
}

void Player::on_actionOpen_triggered()
{
    this->on_actionConfig_triggered();
    return ;

    // old
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getProjectDir().length() > 0)
        dir = QString::fromLocal8Bit(m_projectConfig.getProjectDir().data());

    QFileDialog::Options dialogOptions = QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks;
#ifdef Q_OS_MAC
    // https://bugreports.qt-project.org/browse/QTBUG-2587
    #if (QT_VERSION <= QT_VERSION_CHECK(5, 2, 0))
        dialogOptions |= QFileDialog::DontUseNativeDialog;
    #endif
#endif
    dir = QFileDialog::getExistingDirectory(m_renderWidget, tr("Open Directory"), dir, dialogOptions);

    if (!dir.isEmpty())
    {
        m_projectConfig.setProjectDir(dir.toLocal8Bit().constData());
        this->applySettingAndRestart();
    }
}

void Player::onScreenSizeTriggered()
{
    QAction *action = (QAction*)sender();
    const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(action->data().toInt());

    if (m_projectConfig.isLandscapeFrame())
        m_projectConfig.setFrameSize(CCSize(screenSize.height,screenSize.width));
    else
        m_projectConfig.setFrameSize(CCSize(screenSize.width,screenSize.height));

    applySettingAndRestart();
}

void Player::onLandscapeTriggered()
{
    QAction *action = (QAction*)sender();
    int type = action->data().toInt();
    if (type == kPortrait)
    {
        m_projectConfig.changeFrameOrientationToPortait();
    }
    else if (type == kLandscape)
    {
        m_projectConfig.changeFrameOrientationToLandscape();
    }

    applySettingAndRestart();
}

void Player::onScreenScaleTriggered()
{
    QAction *action = (QAction*)sender();
    float scale = action->data().toFloat();
    m_projectConfig.setFrameScale(scale);

//    applySettingAndRestart();
    CCEGLView::sharedOpenGLView()->setFrameZoomFactor(scale);
#ifdef Q_OS_WIN
    if (m_mainWindow)
    {
        m_mainWindow->setFixedSize(CCEGLView::sharedOpenGLView()->getGLWindow()->size());
    }
#endif
}

void Player::onOpenQuickDemoWebview()
{
    QuickDemoWebView *webview = new QuickDemoWebView();
    webview->setAttribute(Qt::WA_DeleteOnClose);
    QString filePaht(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
    filePaht.append("player/proj.qt/demo.html");
    webview->setObject(this);
    webview->load(filePaht);
    webview->show();
}

void Player::on_actionAbout_triggered()
{
    AboutUI *aboutUI = new AboutUI(m_renderWidget);
    aboutUI->show();
}

void Player::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(0);
}

void Player::on_actionConfig_triggered()
{
    ProjectConfigUI ui(m_projectConfig, m_renderWidget);
    if (ui.exec() == QDialog::Accepted)
    {
        m_projectConfig = ui.getProjectConfig();
        applySettingAndRestart();
    }
}

void Player::onShowOpenCocoaChinaWebView()
{
    const char *url = "http://www.cocoachina.com/";
    url = "/Users/jryin/workspace/github/quick-cocos2d-x/lib/debug";
    onOpenURL(url);
}

void Player::onShowConsole()
{
    ConsoleUI::instance()->show();
}

void Player::onShowLoginUI()
{
    LoginDialog *dialog = new LoginDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    lua_State *L = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    dialog->setLuaState(L);
    dialog->show();
}

void Player::restartWithProjectConfig(ProjectConfig &config)
{
    m_projectConfig = config;
    applySettingAndRestart();
}

void Player::onNewProject()
{
    this->newProject(0);
}

void Player::onCreateNewPlayer()
{
    ProjectConfig newPlayerConfig = m_projectConfig;
    QWindow *window = CCEGLView::sharedOpenGLView()->getGLWindow();
    newPlayerConfig.resetToWelcome();
    newPlayerConfig.setWindowOffset(CCPoint(window->position().x()+50, window->position().y()+10));

    QString cmd(newPlayerConfig.makeCommandLine().data());
    QStringList args = cmd.split(" ");
    qDebug() << args;
    QProcess::startDetached(qApp->applicationFilePath(), args);
}

void Player::onClose()
{
    qApp->exit(0);
}

void Player::onShowWelcome()
{
    m_projectConfig.resetToWelcome();
    qApp->exit(APP_EXIT_CODE);
}

void Player::onOpenDebugLog(bool checked)
{
    if (checked)
        ConsoleUI::instance()->openLogFile();
}

void Player::onUploadToDevice()
{

}

void Player::onCreateLauncher()
{

}

void Player::onAutoConnectDebugger()
{

}

void Player::onBuildIOS()
{

}

void Player::onBuildAndroid()
{

}

void Player::onShowProjectSandBox()
{
    onOpenURL(m_projectConfig.getProjectDir().c_str());
}

void Player::onShowProjectFiles()
{
    onOpenURL(m_projectConfig.getProjectDir().c_str());
}

void Player::onShowPreferences()
{
    PreferenceUI *widget = new PreferenceUI();
    connect(widget, SIGNAL(sigSaveQuickRootPath(QString)), this, SLOT(onSaveQuickRootPath(QString)));
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->show();
}

void Player::onMainWidgetOnTop(bool checked)
{
    QWindow *window = CCEGLView::sharedOpenGLView()->getGLWindow();
    if (checked)
        window->setFlags(window->flags() | Qt::WindowStaysOnTopHint);
    else
        window->setFlags(window->flags() ^ Qt::WindowStaysOnTopHint);
}
