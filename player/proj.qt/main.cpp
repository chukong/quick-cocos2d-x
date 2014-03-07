#include <QApplication>
#include <QProcess>
#include <QMenuBar>
#include <QDebug>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "mainmenu.h"

int main(int argc, char *argv[])
{
    AppDelegate app(argc, argv);
    MainMenu *mainMenu = new MainMenu(CCEGLView::sharedOpenGLView()->getGLWidget());

    // set quick root path from env
    QByteArray quickRootPath = qgetenv(ENV_KEY_QUICK_ROOT_PATH);
    if (!quickRootPath.isEmpty()) {
        SimulatorConfig::sharedDefaults()->setQuickCocos2dxRootPath(quickRootPath.constData());
    }

    ProjectConfig projectConfig;
    // parse argv
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    projectConfig.parseCommandLine(args);

    // show the welcome UI as default
    if (projectConfig.getProjectDir().length() <= 0) {
        projectConfig.resetToWelcome();
    }

    app.setProjectConfig(projectConfig);
    QString searchPath(projectConfig.getProjectDir().data());
    if (searchPath.length() > 0) {
        cocos2d::CCFileUtils::sharedFileUtils()->addSearchPath(searchPath.append("/res/").toLocal8Bit().constData());
    }

    cocos2d::CCEGLView *view = cocos2d::CCEGLView::sharedOpenGLView();
    view->setFrameSize(projectConfig.getFrameSize().width, projectConfig.getFrameSize().height);
    float scale = projectConfig.getFrameScale();
    if (scale > 5.0f || scale < 0.1f)
        scale = 1.0f;
    view->setFrameZoomFactor(scale);


    // crash with Qt 5.1, so set the default font for quick-x-player
    qApp->setFont(QFont("Helvetica [Cronyx]", 12));
//    qApp->setFont(QFont("arial", 12));

    // menu

    mainMenu->setProjectConfig(projectConfig);

    int ret = app.run();

    while (ret == APP_EXIT_CODE) {
        QProcess::startDetached(qApp->applicationFilePath()
                              , qApp->property(RESTART_ARGS).toStringList());
        return 0;
    }
    return ret;
}

