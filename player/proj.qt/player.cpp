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
#include <QSettings>
#include <QVBoxLayout>
#include <QDebug>

// 3rd library
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "json_lib.h"

// ui
#include "aboutui.h"
#include "projectconfigui.h"
#include "createprojectui.h"
#include "consoleui.h"
#include "logindialog.h"
#include "preferenceui.h"

#define kPortrait               1
#define kLandscape              2
#define kOpenRecentFiles        "recents"
#define kDefaultMaxRecents      "maxfiles"
#define kDefaultMaxRecentValue  5
#define kRecentItemTitle        "title"
#define kRecentItemArgs         "args"
#define MODULE_NAME_SEPARATOR   "."
#define MODULE_NAME_CORE        "core"

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
    , m_openRecentMenu(0)
#ifdef Q_OS_WIN
    , m_mainWindow(0)
	, m_container(0)
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

/**
 * @brief Player::onOpenProject
 * save the recent menu order and restart the player with args
 */
void Player::onOpenProject()
{
    ProjectConfig config = Player::instance()->getProjectConfig();
    ProjectConfigUI ui(config, 0);
    if (ui.exec() == QDialog::Accepted)
    {
        config = ui.getProjectConfig();

        // save recent menu order

        QSettings settings;
        QVariantList recents = settings.value(kOpenRecentFiles, QVariantList()).toList();
        int maxRecent = settings.value(kDefaultMaxRecents, kDefaultMaxRecentValue).toInt();
        QVariantMap newItem;
        newItem[kRecentItemTitle] = config.getProjectDir().data();
        QStringList args = QString::fromStdString(config.makeCommandLine()).split(" ");
        newItem[kRecentItemArgs]  = args;
        recents.insert(0, newItem);

        if (recents.size() > maxRecent)
        {
            recents.removeLast();
        }
        settings.setValue(kOpenRecentFiles, recents);

        // restart the player
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
        QString messageName(lua_tostring(L, 1));
        QStringList messageList = messageName.split(".");
        QString messageData;

        if (messageList.size() == 2)
        {
            messageData = lua_tostring(L, 2);
        }
        Player::instance()->eventDispatch(messageName, messageData);
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

void Player::onOpenRecentProject()
{
    QAction *action = dynamic_cast<QAction*> (sender());
    if (action)
    {
        int oldIndex = m_recentFileActionList.indexOf(action);
        m_recentFileActionList.move(oldIndex, 0);
        QStringList args = action->data().toStringList();
        std::vector<std::string> argsVector;
        Q_FOREACH(QString item, args)
        {
            argsVector.push_back(item.toStdString());
        }

        // update recents data
        QSettings settings;
        QVariantList recents = settings.value(kOpenRecentFiles, QVariantList()).toList();
        recents.move(oldIndex, 0);
        settings.setValue(kOpenRecentFiles, recents);

        m_projectConfig.parseCommandLine(argsVector);
        applySettingAndRestart();
    }
}

void Player::onClearRecentMenu()
{
    Q_FOREACH(QAction *action, m_recentFileActionList)
    {
        m_openRecentMenu->removeAction(action);
    }

    QSettings setting;
    setting.remove(kOpenRecentFiles);
}

void Player::onEnterBackground()
{
    enterBackgroundDelegate();
}

void Player::onEnterForeground()
{
    enterForegroundDelegate();
}

void Player::onMemoryWarning()
{

}

void Player::registerAllCpp()
{
    lua_State *L = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    lua_register(L, "openURL", &Player::openURL);
    lua_register(L, "openQuickDemoWithWebView", &Player::openQuickDemoWithWebView);
    lua_register(L, "newProject", &Player::newProject);
    lua_register(L, "openProject", &Player::openProject);
    lua_register(L, "showLoginUI", &Player::showLoginUI);
    lua_register(L, "QT_INTERFACE", &Player::sendMessage);
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
    fileMenu->addAction(QObject::tr("New Project..."), this, SLOT(onNewProject()), QKeySequence(Qt::CTRL + Qt::Key_N));
    fileMenu->addAction(QObject::tr("New Player"), this, SLOT(onCreateNewPlayer()), QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_N));

    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("Open"), this, SLOT(on_actionOpen_triggered()), QKeySequence(Qt::CTRL + Qt::Key_O));

    m_openRecentMenu = fileMenu->addMenu(tr("Open Recent"));
    QSettings setting;
    QVariantList recents = setting.value(kOpenRecentFiles).toList();
    Q_FOREACH(QVariant recentItem, recents)
    {
        QVariantMap item = recentItem.toMap();
        QString title = item.value(kRecentItemTitle).toString();
        QStringList args = item.value(kRecentItemArgs).toStringList();
        QAction *action = m_openRecentMenu->addAction(title);
        action->setData(args);
        m_recentFileActionList << action;
        connect(action, SIGNAL(triggered()), this, SLOT(onOpenRecentProject()));
    }

    m_openRecentMenu->addSeparator();
    m_openRecentMenu->addAction(tr("Clear"), this, SLOT(onClearRecentMenu()));

    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("Welcome"), this, SLOT(onShowWelcome()));

    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("Close"), this, SLOT(onClose()), QKeySequence(Qt::CTRL + Qt::Key_W));

    //
    // player menu
    //

    QMenu *playerMenu = m_mainMenu->addMenu(QObject::tr("&Player"));
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
    QAction *relaunchAction = playerMenu->addAction(QObject::tr("Relaunch"), this, SLOT(on_actionRelaunch_triggered()));
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
    QMenu *windowMenu = m_mainMenu->addMenu(tr("&Window"));
    {
        QAction *onTopAction = windowMenu->addAction(tr("Allways On Top"));
        onTopAction->setCheckable(true);
        connect(onTopAction, SIGNAL(triggered(bool)), this, SLOT(onMainWidgetOnTop(bool)));
    }

    //
    // device
    //
    QMenu *deviceMenu = m_mainMenu->addMenu(tr("&Device"));
    deviceMenu->addAction(tr("Enter Background"), this, SLOT(onEnterBackground()));
    deviceMenu->addAction(tr("Enter Foreground"), this, SLOT(onEnterForeground()));
    deviceMenu->addAction(tr("Memory Warning"), this, SLOT(onMemoryWarning()));


    //
    // more menu
    //

    QMenu *moreMenu = m_mainMenu->addMenu(QObject::tr("&More"));
    moreMenu->addAction(tr("AboutQt"), this, SLOT(on_actionAboutQt_triggered()));
    moreMenu->addAction(tr("About"), this, SLOT(on_actionAbout_triggered()));
    moreMenu->addAction(tr("Simples"), this, SLOT(onOpenQuickDemoWebview()));
    moreMenu->addAction(tr("open.cocoachina.com"), this, SLOT(onShowOpenCocoaChinaWebView()));
    moreMenu->addAction(tr("show console"), this, SLOT(onShowConsole()));
    moreMenu->addAction(tr("Login Test"), this, SLOT(onShowLoginUI()));

    m_mainMenu->show();
    m_mainMenu->raise();

    //
    // Preferences
    //
    QAction *m_preference = moreMenu->addAction(tr("&Preferences"));
    m_preference->setMenuRole(QAction::PreferencesRole);
    connect(m_preference, SIGNAL(triggered()), this, SLOT(onShowPreferences()));
}

void Player::makeMainWindow(QWindow *w, QMenuBar *bar)
{
#ifdef Q_OS_MAC
    Q_UNUSED(bar);
    w->show();

#else
	static bool bInited = false;
    if (bar && w && !bInited)
    {
		bInited = true;
        m_mainWindow = new QWidget();
        m_mainWindow->setAttribute(Qt::WA_DeleteOnClose);

		QSize glSize = w->size();
		m_container = QWidget::createWindowContainer(w);
		m_container->setMinimumSize(glSize);
		bar->setMaximumWidth(glSize.width());
		
		QVBoxLayout *layout = new QVBoxLayout();
		layout->setContentsMargins(0,0,0,0);
		layout->addWidget(bar);
		layout->addWidget(m_container);
		m_mainWindow->show();
		m_mainWindow->setLayout(layout);
    }

#endif

    checkQuickRootPath();
    updateTitle();
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

void Player::checkQuickRootPath()
{
    if (SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().length() <= 0)
    {
        onShowPreferences();
    }
}

void Player::updateTitle()
{
    QString title = QString("quick-x-player (%1%)").arg(m_projectConfig.getFrameScale()*100);
#ifdef Q_OS_MAC
    CCEGLView::sharedOpenGLView()->getGLWindow()->setTitle(title);
#else
    m_mainWindow->setWindowTitle(title);
#endif
}

void Player::eventDispatch(QString messageName, QString data)
{
    QStringList messageList = messageName.split(MODULE_NAME_SEPARATOR);
    // core message
    if (messageList.size() <= 2)
    {
        QString prefix = messageList.at(0);

        // core.openURL
        if (prefix == MODULE_NAME_CORE)
        {
            QString tmpMsgName = messageList.at(1);
            if (tmpMsgName == "openURL")
            {
                this->onOpenURL(data.toLocal8Bit().data());
            }
            else if (tmpMsgName == "openProject")
            {
                this->onOpenProject();
            }
            else if (tmpMsgName == "newProject")
            {
                this->onNewProject();
            }
            else if (tmpMsgName == "openDemo")
            {
                this->onOpenQuickDemoWebview();
            }
        }
    }
    // others
    else
    {

    }
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
		m_container->setFixedSize(CCEGLView::sharedOpenGLView()->getGLWindow()->size());
		m_mainWindow->setFixedSize(m_container->size());
    }
#endif

    updateTitle();
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
    onOpenProject();
}

void Player::onShowOpenCocoaChinaWebView()
{
    const char *url = "http://www.cocoachina.com/";
    onOpenURL(url);
}

void Player::onShowConsole()
{
    ConsoleUI::instance()->show();

    static bool isFirstShow = true;
    if (isFirstShow)
    {
        isFirstShow = false;
        int y = qApp->desktop()->availableGeometry().height() - ConsoleUI::instance()->height();
        ConsoleUI::instance()->move(0, y);
    }
}

void Player::onShowLoginUI()
{
    LoginDialog *dialog = new LoginDialog();
    connect(dialog, SIGNAL(sigLogin(QString,QString)), this, SLOT(onLogin(QString,QString)));
    dialog->setAttribute(Qt::WA_DeleteOnClose);
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
#ifdef Q_OS_MAC
    Qt::WindowFlags flags = CCEGLView::sharedOpenGLView()->getGLWindow()->flags();
    QPoint pos = CCEGLView::sharedOpenGLView()->getGLWindow()->position();
    if (checked)
    {
        flags ^= Qt::WindowStaysOnBottomHint;
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        flags ^= Qt::WindowStaysOnTopHint;
        flags |= Qt::WindowStaysOnBottomHint;
    }
    CCEGLView::sharedOpenGLView()->getGLWindow()->setFlags(flags);
    CCEGLView::sharedOpenGLView()->getGLWindow()->show();
    CCEGLView::sharedOpenGLView()->getGLWindow()->setPosition(pos);
#else
	Qt::WindowFlags flags = m_mainWindow->windowFlags();
	QPoint pos = m_mainWindow->pos();
    if (checked)
    {
        flags ^= Qt::WindowStaysOnBottomHint;
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        flags ^= Qt::WindowStaysOnTopHint;
        flags |= Qt::WindowStaysOnBottomHint;
    }
	m_mainWindow->setWindowFlags(flags);
	m_mainWindow->show();
    m_mainWindow->move(pos);
#endif
}

void Player::onLogin(QString userName, QString password)
{
    CSJson::Value messageData;
    CSJson::FastWriter writer;
    messageData["user"] = userName.toLocal8Bit().data();
    messageData["pwd"]  = password.toLocal8Bit().data();
    std::string out = writer.write(messageData);

    cocos2d::CCLuaStack *luaStack = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack();
    luaStack->pushString("core.message");
    luaStack->pushString(out.data());
    luaStack->executeGlobalFunction("LUA_Interface", 2);
}
