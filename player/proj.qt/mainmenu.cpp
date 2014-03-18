#include "mainmenu.h"

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

#define kPortrait 1
#define kLandscape 2

struct ActionData
{
    QString         text;
    QKeySequence    keySequence;
    QVariant        userData;
};

MainMenu* MENU = NULL;
QMenuBar *xxBar = NULL;
MainMenu::MainMenu(QObject *parent)
    : QObject(parent)
    , m_renderWidget(0)
    , m_quickDemoWebview(0)
{
#ifdef Q_OS_MAC
    QMenuBar *mainMenu = new QMenuBar(0);
#else
    QMenuBar *mainMenu = new QMenuBar(m_renderWidget);
#endif
//    mainMenu->setNativeMenuBar(true);
    xxBar = mainMenu;

    // file menu
    QMenu *fileMenu = mainMenu->addMenu(QObject::tr("&File"));
    fileMenu->addAction(QObject::tr("&New Project..."), this, SLOT(onNewProject()), QKeySequence(Qt::CTRL + Qt::Key_N));
    fileMenu->addAction(QObject::tr("New Player"), this, SLOT(onCreateNewPlayer())
                        , QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_N));
    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("&Open"), this, SLOT(on_actionOpen_triggered()), QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("Welcome"), this, SLOT(onShowWelcome()));
    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("&Close"), this, SLOT(onClose()), QKeySequence(Qt::CTRL + Qt::Key_W));

    //
    // player menu
    //

    QMenu *playerMenu = mainMenu->addMenu(QObject::tr("Player"));
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

    m_screenMenu = mainMenu->addMenu(QObject::tr("&Screen"));

    //
    // more menu
    //

    QMenu *moreMenu = mainMenu->addMenu(QObject::tr("&More"));
    moreMenu->addAction("&AboutQt", this, SLOT(on_actionAboutQt_triggered()));
    moreMenu->addAction("&About", this, SLOT(on_actionAbout_triggered()));
    moreMenu->addAction("&Simples", this, SLOT(onOpenQuickDemoWebview()));
    moreMenu->addAction("open.cocoachina.com", this, SLOT(onShowOpenCocoaChinaWebView()));
    moreMenu->addAction("show console", this, SLOT(onShowConsole()));
    moreMenu->addAction("Login Test", this, SLOT(onShowLoginUI()));

    mainMenu->show();
    mainMenu->raise();

    MENU = this;
}

MainMenu::~MainMenu()
{
}

MainMenu *MainMenu::instance()
{
    return MENU;
}

QMenuBar *MainMenu::getMenuBar()
{
    return xxBar;
}

void MainMenu::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
    initMenu();
}

ProjectConfig MainMenu::getProjectConfig()
{
    return m_projectConfig;
}

int MainMenu::openURL(lua_State *L)
{
    //从栈中读入实部，虚部
    const char *path = lua_tostring(L, 1);
    openURLHelper(path);
    return 0;
}

int MainMenu::openQuickDemoWithWebView(lua_State * /*L*/)
{
    QuickDemoWebView *webview = new QuickDemoWebView();
    webview->setAttribute(Qt::WA_DeleteOnClose);
    QString filePaht(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
    filePaht.append("player/proj.qt/demo.html");
    webview->load(filePaht);
    webview->show();
    return 0;
}

int MainMenu::newProject(lua_State * /*L*/)
{
    CreateProjectUI ui(0);
    if (ui.exec() == QDialog::Accepted) {
        ui.createNewProject();
    }
    return 0;
}

int MainMenu::onOpenProject(lua_State * /*L*/)
{
    ProjectConfig config = MENU->getProjectConfig();
    ProjectConfigUI ui(config, 0);
    if (ui.exec() == QDialog::Accepted) {
        config = ui.getProjectConfig();
        MENU->restartWithProjectConfig(config);
    }
    return 0;
}

int MainMenu::showLoginUI(lua_State *L)
{
    MainMenu::showLoginUIHelper();
    return 0;
}

void MainMenu::openURLHelper(const char *path)
{
    QString tmpPath(path);
    if (tmpPath.startsWith("http://"))
        QDesktopServices::openUrl(QUrl(tmpPath));
    else
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainMenu::showLoginUIHelper()
{
    LoginDialog *dialog = new LoginDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    lua_State *L = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    dialog->setLuaState(L);
    dialog->show();
}

void MainMenu::registerAllCpp()
{
    lua_State *L = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    lua_register(L, "openURL", &MainMenu::openURL);
    lua_register(L, "openQuickDemoWithWebView", &MainMenu::openQuickDemoWithWebView);
    lua_register(L, "newProject", &MainMenu::newProject);
    lua_register(L, "openProject", &MainMenu::onOpenProject);
    lua_register(L, "showLoginUI", &MainMenu::showLoginUI);
}

void MainMenu::initMenu()
{
    //
    QActionGroup *actionGroup = new QActionGroup(this);
    CCSize size = m_projectConfig.getFrameSize();
    for (int i = 0; i < SimulatorConfig::sharedDefaults()->getScreenSizeCount(); i++) {
        const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        QAction *action = m_screenMenu->addAction(QString::fromLocal8Bit(screenSize.title.data()));
        action->setCheckable(true);
        action->setEnabled(true);
        action->setData(i);
        connect(action, SIGNAL(triggered()), this, SLOT(onScreenSizeTriggered()));
        actionGroup->addAction(action);

        if ((size.width == screenSize.width && size.height == screenSize.height) ||
            (size.width == screenSize.height && size.height == screenSize.width)) {
            action->setChecked(true);
        }
    }

    m_screenMenu->addSeparator();

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

    if (m_projectConfig.isLandscapeFrame()) {
        m_landscapeAction->setChecked(true);
    } else {
        m_portraitAction->setChecked(true);
    }

    m_screenMenu->addSeparator();

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

void MainMenu::restart()
{
    qApp->exit(APP_EXIT_CODE);
}

void MainMenu::applySettingAndRestart()
{
    QStringList args;

    QString cmd(m_projectConfig.makeCommandLine().data());
    args = cmd.split(" ");
    qApp->setProperty(RESTART_ARGS, args);
    this->restart();
}

void MainMenu::openlocalFolderOrFile(string filePath)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath.data()));
}

void MainMenu::on_actionRelaunch_triggered()
{
    this->applySettingAndRestart();
}

void MainMenu::on_actionOpen_triggered()
{
    this->on_actionConfig_triggered();
    return ;

    // old
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getProjectDir().length() > 0) {
        dir = QString::fromLocal8Bit(m_projectConfig.getProjectDir().data());
    }

    dir = QFileDialog::getExistingDirectory(m_renderWidget, tr("Open Directory"), dir
                                      , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        m_projectConfig.setProjectDir(dir.toLocal8Bit().constData());
        this->applySettingAndRestart();
    }
}

void MainMenu::onScreenSizeTriggered()
{
    QAction *action = (QAction*)sender();
    const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(action->data().toInt());

    if (m_projectConfig.isLandscapeFrame())
        m_projectConfig.setFrameSize(CCSize(screenSize.height,screenSize.width));
    else
        m_projectConfig.setFrameSize(CCSize(screenSize.width,screenSize.height));

    applySettingAndRestart();
}

void MainMenu::onLandscapeTriggered()
{
    QAction *action = (QAction*)sender();
    int type = action->data().toInt();
    if (type == kPortrait) {
        m_projectConfig.changeFrameOrientationToPortait();
    } else if (type == kLandscape) {
        m_projectConfig.changeFrameOrientationToLandscape();
    }

    applySettingAndRestart();
}

void MainMenu::onScreenScaleTriggered()
{
    QAction *action = (QAction*)sender();
    float scale = action->data().toFloat();
    m_projectConfig.setFrameScale(scale);

//    applySettingAndRestart();
    CCEGLView::sharedOpenGLView()->setFrameZoomFactor(scale);
}

void MainMenu::onOpenQuickDemoWebview()
{
    if (!m_quickDemoWebview) {
        QString filePaht(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
        filePaht.append("player/proj.qt/demo.html");
        m_quickDemoWebview->load(filePaht);
        m_quickDemoWebview->show();
    }
}

void MainMenu::on_actionAbout_triggered()
{
    AboutUI *aboutUI = new AboutUI(m_renderWidget);
    aboutUI->show();
}

void MainMenu::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(0);
}

void MainMenu::on_actionConfig_triggered()
{
    ProjectConfigUI ui(m_projectConfig, m_renderWidget);
    if (ui.exec() == QDialog::Accepted) {
        m_projectConfig = ui.getProjectConfig();
        applySettingAndRestart();
    }
}

void MainMenu::onShowOpenCocoaChinaWebView()
{
    const char *url = "http://www.cocoachina.com/";
    url = "/Users/jryin/workspace/github/quick-cocos2d-x/lib/debug";
    openURLHelper(url);
}

void MainMenu::onShowConsole()
{
    ConsoleUI::instance()->show();
}

void MainMenu::onShowLoginUI()
{
    MainMenu::showLoginUIHelper();
}

void MainMenu::restartWithProjectConfig(ProjectConfig &config)
{
    m_projectConfig = config;
    applySettingAndRestart();
}

void MainMenu::onNewProject()
{
    this->newProject(0);
}

void MainMenu::onCreateNewPlayer()
{
    QProcess::startDetached(qApp->applicationFilePath());
}

void MainMenu::onClose()
{
    qApp->exit(0);
}

void MainMenu::onShowWelcome()
{
    m_projectConfig.resetToWelcome();
    qApp->exit(APP_EXIT_CODE);
}

void MainMenu::onOpenDebugLog(bool checked)
{
    if (checked)
        ConsoleUI::instance()->openLogFile();
}

void MainMenu::onUploadToDevice()
{

}

void MainMenu::onCreateLauncher()
{

}

void MainMenu::onAutoConnectDebugger()
{

}

void MainMenu::onShowProjectSandBox()
{
    openURLHelper(m_projectConfig.getProjectDir().c_str());
}

void MainMenu::onShowProjectFiles()
{
    openURLHelper(m_projectConfig.getProjectDir().c_str());
}
