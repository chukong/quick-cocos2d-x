#include <QApplication>
#include <QProcess>
#include <QMenuBar>
#include <QSettings>
#include <QDebug>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "player.h"
#include "consoleui.h"
#include "msghandlerwapper.h"

int main(int argc, char *argv[])
{

    AppDelegate app(argc, argv);
    MsgHandlerWapper::instance();
    ConsoleUI::instance();

    // set quick root path from env
    qApp->setOrganizationDomain("apps.qeeplay.com");
    qApp->setApplicationName("quick-x-player-qt");
    QSettings settings;
    QString quickCocos2dxRoot = settings.value(ENV_KEY_QUICK_ROOT_PATH).toString();
    if (!quickCocos2dxRoot.isEmpty())
    {
        SimulatorConfig::sharedDefaults()->setQuickCocos2dxRootPath(quickCocos2dxRoot.toLocal8Bit().constData());
    }

    ProjectConfig projectConfig;
    // parse argv
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    projectConfig.parseCommandLine(args);

    // show the welcome UI as default
    if (projectConfig.getProjectDir().length() <= 0)
    {
        projectConfig.resetToWelcome();
    }

    CCFileUtils::sharedFileUtils()->setWritablePath(projectConfig.getWritableRealPath().data());
    CCFileUtils::sharedFileUtils()->setCachePath(projectConfig.getWritableRealPath().data());

    // console settings
    if (projectConfig.isWriteDebugLogToFile())
    {
        QString logFilePath(projectConfig.getWritableRealPath().data());
        QString suffix = QDateTime::currentDateTime().toString("yyyy-MM-dd-") + QTime::currentTime().toString("HHmmss");
        QString logFileName = QString("%1/debug-%2.log")
                                        .arg(logFilePath)
                                        .arg(suffix);
        ConsoleUI::instance()->initWithLogFile(logFileName);
    }
    QObject::connect(MsgHandlerWapper::instance(), SIGNAL(message(QtMsgType,QString)),
                     ConsoleUI::instance(), SLOT(dealWithMessageOutput(QtMsgType,QString)));
    projectConfig.dump();

    app.setProjectConfig(projectConfig);
    QString searchPath(projectConfig.getProjectDir().data());
    if (searchPath.length() > 0)
    {
        cocos2d::CCFileUtils::sharedFileUtils()->addSearchPath(searchPath.append("/res/").toLocal8Bit().constData());
    }

    cocos2d::CCEGLView *view = cocos2d::CCEGLView::sharedOpenGLView();
    view->setFrameSize(projectConfig.getFrameSize().width, projectConfig.getFrameSize().height);
    float scale = projectConfig.getFrameScale();
    if (scale > 5.0f || scale < 0.1f)
        scale = 1.0f;
    view->setFrameZoomFactor(scale);

    if (projectConfig.getWindowOffset().x <= 1 && projectConfig.getWindowOffset().y <= 1)
    {
    }
    else
    {
        view->getGLWindow()->setPosition(projectConfig.getWindowOffset().x,
                                         projectConfig.getWindowOffset().y);
    }

    if (projectConfig.isShowConsole())
    {
        ConsoleUI::instance()->show();
    }
    Player *player = Player::instance();
    player->initMainMenu();
    player->makeMainWindow(view->getGLWindow(), player->getMenuBar());
    player->enterBackgroundDelegate.bind(&app, &AppDelegate::applicationDidEnterBackground);
    player->enterForegroundDelegate.bind(&app, &AppDelegate::applicationWillEnterForeground);

#ifdef Q_OS_MAC
    if (QT_VERSION < QT_VERSION_CHECK(5, 2, 0) && QSysInfo::macVersion() >= QSysInfo::MV_MAVERICKS)
    {
        // OS X 10.9 crash with Qt 5.1, so set the default font for quick-x-player
        QFont font("Courier", 13, QFont::Normal, false);
        qApp->setFont(font);
    }
#endif

    // menu
    player->setProjectConfig(projectConfig);

    int ret = app.run();

    MsgHandlerWapper::instance()->cancelHandler();
    while (ret == APP_EXIT_CODE)
    {
        QProcess::startDetached(qApp->applicationFilePath()
                              , qApp->property(RESTART_ARGS).toStringList());
        return 0;
    }
    return ret;
}

