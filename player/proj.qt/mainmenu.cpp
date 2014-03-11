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

MainMenu* MENU = NULL;
MainMenu::MainMenu(QObject *parent)
    : QObject(parent)
    , m_renderWidget(0)
    , m_textBrowser(0)
{
    QMenuBar *mainMenu = new QMenuBar(0);
    mainMenu->setNativeMenuBar(true);

    // file menu
    QMenu *fileMenu = mainMenu->addMenu(QObject::tr("&File"));
    fileMenu->addAction("&New Project", this, SLOT(onNewProject()), QKeySequence(Qt::CTRL + Qt::Key_N));
    fileMenu->addAction("&Open", this, SLOT(on_actionOpen_triggered()), QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addAction("&Relaunch", this, SLOT(on_actionRelaunch_triggered()), QKeySequence(Qt::Key_F5));
//    fileMenu->addAction("&Close",  qApp, SLOT(quit()), QKeySequence(QObject::tr("Ctrl+c")));

    // view menu
    m_viewMenu = mainMenu->addMenu(QObject::tr("&View"));

    // more menu
    QMenu *moreMenu = mainMenu->addMenu(QObject::tr("&More"));
    moreMenu->addAction("&AboutQt", this, SLOT(on_actionAboutQt_triggered()));
    moreMenu->addAction("&About", this, SLOT(on_actionAbout_triggered()));
    moreMenu->addAction("&Simples", this, SLOT(onOpenQuickDemoWebview()));
    moreMenu->addAction("open.cocoachina.com", this, SLOT(onShowOpenCocoaChinaWebView()));
    moreMenu->addAction("show console", this, SLOT(onShowConsole()));
    moreMenu->addAction("Login Test", this, SLOT(onShowLoginUI()));

    mainMenu->show();

    MENU = this;
}

MainMenu::~MainMenu()
{
    CC_SAFE_DELETE(m_textBrowser);
}

MainMenu *MainMenu::instance()
{
    return MENU;
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
    LoginDialog dialog;
    dialog.setLuaState(L);
    dialog.exec();
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
        QAction *action = m_viewMenu->addAction(QString::fromLocal8Bit(screenSize.title.data()));
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

    m_viewMenu->addSeparator();

    //
    actionGroup = new QActionGroup(this);

    m_landscapeAction = m_viewMenu->addAction(tr("Landscape"));
    m_landscapeAction->setData(kLandscape);
    m_landscapeAction->setCheckable(true);
    connect(m_landscapeAction, SIGNAL(triggered()), this, SLOT(onLandscapeTriggered()));

    m_portraitAction = m_viewMenu->addAction(tr("Portrait"));
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

    m_viewMenu->addSeparator();

    //
    actionGroup = new QActionGroup(this);
    QAction *screenScale100 = m_viewMenu->addAction(tr("100% scale"));
    screenScale100->setData(1.0f);
    screenScale100->setCheckable(true);
    connect(screenScale100, SIGNAL(triggered()), this, SLOT(onScreenScaleTriggered()));

    QAction *screenScale50 = m_viewMenu->addAction(tr("50% scale"));
    screenScale50->setData(0.5f);
    screenScale50->setCheckable(true);
    connect(screenScale50, SIGNAL(triggered()), this, SLOT(onScreenScaleTriggered()));

    actionGroup->addAction(screenScale100);
    actionGroup->addAction(screenScale50);
    if (m_projectConfig.getFrameScale() == 0.5f) {
        screenScale50->setChecked(true);
    } else if (m_projectConfig.getFrameScale() == 1.0f) {
        screenScale100->setChecked(true);
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
    QString filePaht(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
    filePaht.append("player/proj.qt/demo.html");
    m_quickDemoWebview.load(filePaht);
    m_quickDemoWebview.show();
}

void MainMenu::on_actionAbout_triggered()
{
    AboutUI aboutUI(m_renderWidget);
    aboutUI.exec();
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
    LoginDialog dialog;
    lua_State *L = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    dialog.setLuaState(L);
    dialog.exec();
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
