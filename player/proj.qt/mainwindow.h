#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SimulatorConfig.h"

#define RESTART_ARGS "restart_args"

class NodeTreeView;
class NodeTreeModel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setRenderWidget(QWidget *w);
    void setProjectConfig(const ProjectConfig& config);

protected:
    // ui
    void showEvent(QShowEvent *);
    void initUI();
    void buildObjectTree();

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

    void on_actionUpdateObject_triggered();

private:
    Ui::MainWindow *ui;
    QString m_projectConfigFileName;

    ProjectConfig m_projectConfig;
    NodeTreeView *m_objectTreeView;
    NodeTreeModel *m_objectTreeModel;

};

#endif // MAINWINDOW_H
