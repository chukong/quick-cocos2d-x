#include <QApplication>
#include <QProcess>
#include <QMenuBar>
#include <QSettings>
#include <QDebug>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "player.h"

#ifdef USING_TRACKERBIRD
#if defined(Q_OS_WIN)
#include "Trackerbird.h"
#elif defined(Q_OS_MAC)
#include "TrackerbirdSDK.h"
#endif
#endif

static void trackerStart()
{
    #ifdef USING_TRACKERBIRD
#if defined(Q_OS_WIN)
    //Initialize the Trackerbird Configuration
    tbCreateConfig( L"http://18787.tbnet1.com",
                    L"2382168764",
                    L"2.2.3",
                    L"5AC234",
                    false);
    tbSetProductEdition( L"win-Beta");
    tbSetProductLanguage(L"zh");

    tbStart(TB_START_NO_SYN);

#elif defined(Q_OS_MAC)
    //Initialize the Trackerbird Configuration
    std::string url                 = std::string("http://18787.tbnet1.com");
    std::string productID           = std::string("2382168764");
    std::string productVersion      = std::string("2.2.3");
    std::string productBuildNumber  = std::string("5AC234");
    bool multiSessionEnabled        = false;
    std::string productEdition      = std::string("mac-Beta");
    std::string productLanguage     = std::string("zh");
    std::string filePath            = std::string();

    TrackerbirdSDK::TBConfig config = TrackerbirdSDK::TBConfig(url, productID, productVersion,
                                                               productBuildNumber, multiSessionEnabled,
                                                               productEdition, productLanguage, filePath);
    //Inform Trackerbird that a new runtime session has been started.
    TrackerbirdSDK::TBApp::start(config, NULL);
#endif
#endif // USING_TRACKERBIRD __END
}

static void trackerEnd()
{
#ifdef USING_TRACKERBIRD
#if defined(Q_OS_WIN)
    tbStop(TB_STOP_NO_SYN);
#elif defined(Q_OS_MAC)
    //Program closing - inform Trackerbird that this runtime session is closing down.
    TrackerbirdSDK::TBApp::stop(NULL);
#endif
#endif // USING_TRACKERBIRD __END
}

int main(int argc, char *argv[])
{
    //
    // save the argv first
    // crash sometimes on OSX
    //
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    trackerStart();
    AppDelegate app(argc, argv);
    MsgHandlerWapper::instance();
    Player *player = Player::instance();
    player->initConsole();


    // mac: ~/Library/Preferences/com.com-cocoachina-quick.quick-cocos2d-x player.plist
    // win: regedit
    qApp->setOrganizationDomain("com.cocoachina.quick");
    qApp->setApplicationName("quick-cocos2d-x player");

    // set quick root path from env
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
    projectConfig.resetToWelcome();

    if (settings.value(kAutoDebugger).toBool())
    {
        projectConfig.setDebuggerType(kCCLuaDebuggerLDT);
    }

    projectConfig.parseCommandLine(args);
    projectConfig.dump();

    const string projectDir = projectConfig.getProjectDir();
    CCFileUtils::sharedFileUtils()->setSearchRootPath(projectDir.c_str());
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
    player->setProjectConfig(projectConfig);
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

    player->restoreSetting();
    int ret = app.run();
    player->saveSetting();

    trackerEnd();

    MsgHandlerWapper::instance()->cancelHandler();
    if (ret == APP_EXIT_CODE)
    {
        QProcess::startDetached(qApp->applicationFilePath()
                              , qApp->property(RESTART_ARGS).toStringList());
        return 0;
    }
    return ret;
}
