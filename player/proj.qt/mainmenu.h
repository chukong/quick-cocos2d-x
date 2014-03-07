#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SimulatorConfig.h"

#define RESTART_ARGS "restart_args"
#define APP_EXIT_CODE 'q'
#define ENV_KEY_QUICK_ROOT_PATH "QUICK_COCOS2DX_ROOT"

class MainMenu : public QObject
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *renderWidget, QObject *parent = 0);
    ~MainMenu();

    void setProjectConfig(const ProjectConfig& config);

protected:
    void initUI();

    // engine
    void restart();
    void applySettingAndRestart();
    cocos2d::CCSize getSuitableSize(const cocos2d::CCSize &portraitSize);

private Q_SLOTS:
    void on_actionRelaunch_triggered();
    void on_actionOpen_triggered();

    void onScreenSizeTriggered();
    void onLandscapeTriggered();
    void onScreenScaleTriggered();

    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionConfig_triggered();

private:
    QString         m_projectConfigFileName;
    ProjectConfig   m_projectConfig;
    QWidget         *m_renderWidget;

    QMenu           *m_viewMenu;
    QAction         *m_landscapeAction, *m_portraitAction;
    QTextBrowser    *m_textBrowser;
};

#endif // MAINWINDOW_H
