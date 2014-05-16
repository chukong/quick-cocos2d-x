#include <QApplication>
#include <QProcess>
#include <QMenuBar>
#include <QSettings>
#include <QDebug>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "player.h"

int main(int argc, char *argv[])
{

    AppDelegate app(argc, argv);
    MsgHandlerWapper::instance();
    Player *player = Player::instance();
    player->initConsole();

    // set quick root path from env
    qApp->setOrganizationDomain("com.cocoachina.quick");
    qApp->setApplicationName("quick-cocos2d-x player");
    QString quickCocos2dxRoot = player->getQuickRootPathFromSystem();
    if (!quickCocos2dxRoot.isEmpty())
    {
        SimulatorConfig::sharedDefaults()->setQuickCocos2dxRootPath(quickCocos2dxRoot.toLocal8Bit().constData());
    }

    // recent files
    CCLuaValueArray recentArray;
    QSettings settings;
    QVariantList recents = settings.value(kOpenRecentFiles).toList();
    Q_FOREACH(QVariant recentItem, recents)
    {
        QVariantMap item = recentItem.toMap();
        QString title = item.value(kRecentItemTitle).toString();
        recentArray.push_back(CCLuaValue::stringValue(title.toUtf8().constData()));
    }
    app.setOpenRecents(recentArray);

    ProjectConfig projectConfig;
    // parse argv
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    projectConfig.parseCommandLine(args);
    projectConfig.dump();

    const string projectDir = projectConfig.getProjectDir();
    // show the welcome UI as default
    if (projectDir.length() <= 0)
    {
        projectConfig.resetToWelcome();
    }
    else
    {
        CCFileUtils::sharedFileUtils()->setSearchRootPath(projectDir.c_str());
    }

    CCFileUtils::sharedFileUtils()->setWritablePath(projectConfig.getWritableRealPath().data());
    CCFileUtils::sharedFileUtils()->setCachePath(projectConfig.getWritableRealPath().data());

    // load lua bridge module
    player->loadLuaBridgeModule();

    // console settings
    if (projectConfig.isWriteDebugLogToFile())
    {
        QString logFilePath(projectConfig.getWritableRealPath().data());
//        QString suffix = QDateTime::currentDateTime().toString("yyyy-MM-dd-") + QTime::currentTime().toString("HHmmss");
        QString logFileName = QString("%1/debug.log").arg(logFilePath);
        player->setLogFileName(logFileName);
    }

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

    player->initMainMenu();
    player->makeMainWindow(view->getGLWidget(), player->getMenuBar());
    player->enterBackgroundDelegate.bind(&app, &AppDelegate::applicationDidEnterBackground);
    player->enterForegroundDelegate.bind(&app, &AppDelegate::applicationWillEnterForeground);

#ifdef Q_OS_MAC

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    if (QT_VERSION < QT_VERSION_CHECK(5, 2, 0) && QSysInfo::macVersion() >= QSysInfo::MV_MAVERICKS)
#else
    if (QSysInfo::MacintoshVersion >= QSysInfo::MV_MOUNTAINLION)
#endif
    {
        // OS X 10.9 crash with Qt 5.1, so set the default font for quick-x-player
        QFont font("Courier", 13, QFont::Normal, false);
        qApp->setFont(font);
    }
#endif

    // menu
    player->setProjectConfig(projectConfig);

    player->restoreSetting();
    int ret = app.run();
    player->saveSetting();

    MsgHandlerWapper::instance()->cancelHandler();
    while (ret == APP_EXIT_CODE)
    {
        QProcess::startDetached(qApp->applicationFilePath()
                              , qApp->property(RESTART_ARGS).toStringList());
        return 0;
    }
    return ret;
}
