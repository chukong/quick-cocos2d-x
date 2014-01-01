#include <QApplication>
#include <QProcess>
#include <QDebug>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    AppDelegate app(argc, argv);
    MainWindow *m_window = new MainWindow();

    ProjectConfig projectConfig;
    // parse argv
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    projectConfig.parseCommandLine(args);

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


    // ui
    {
        m_window->setRenderWidget(CCEGLView::sharedOpenGLView()->getGLWidget());
        m_window->setProjectConfig(projectConfig);
        m_window->show();
    }

    int ret = app.run();

    while (ret == 'q') {
        QProcess::startDetached(qApp->applicationFilePath()
                              , qApp->property(RESTART_ARGS).toStringList());
        return 0;
    }
    return ret;
}

