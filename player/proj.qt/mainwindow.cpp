#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextBrowser>
#include <QFile>
#include <QScrollBar>
#include <QDebug>

#include "aboutui.h"
#include "projectconfigui.h"
#include "nodetreemodel.h"
#include "nodetreeview.h"
#include "mydatavisitor.h"

#define kPortrait 1
#define kLandscape 2

static QTextBrowser *g_textBrowser  = NULL;
static QTextStream  *g_textStream   = NULL;
void myMessageOutput(QtMsgType /*type*/, const QMessageLogContext &/*context*/, const QString &msg)
{
    if (g_textBrowser) {
        g_textBrowser->append(msg);
        QScrollBar *sb = g_textBrowser->verticalScrollBar();
        sb->setValue(sb->maximum());
    }

    if (g_textStream) {
        *g_textStream << msg << "\n";
        g_textStream->flush();
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_objectTreeView(NULL),
    m_objectTreeModel(NULL)
{
    QTextBrowser *textBrowser = new QTextBrowser(this);
    g_textBrowser = textBrowser;
    qInstallMessageHandler(myMessageOutput);

    ui->setupUi(this);

    ui->debugDockWidget->setWidget(textBrowser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRenderWidget(QWidget *w)
{
    ui->scrollArea->setWidget(w);
    ui->scrollArea->setWidgetResizable(true);
}

void MainWindow::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
    initUI();
    buildObjectTree();

    if (m_projectConfig.isWriteDebugLogToFile()) {
        QString logFileName = QString("%1/quick-x-%2.log")
                                        .arg(qApp->applicationDirPath())
                                        .arg(QTime::currentTime().toString().replace(":","-"));
        QFile *g_file = new QFile(logFileName, this);
        g_textStream = new QTextStream(g_file);
        ui->debugDockWidget->setWindowTitle(logFileName);

        if (g_file->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
            g_file->write(g_textBrowser->toPlainText().toLocal8Bit(), g_textBrowser->toPlainText().length());
            g_file->flush();
        } else {
            qDebug() << "Can not open file " << g_file->fileName() << g_file->errorString();
        }
    }
}


void MainWindow::showEvent(QShowEvent *)
{
    QDesktopWidget *w = qApp->desktop();
    QRect rect = w->screenGeometry();
    this->move((rect.width()-this->width())/2.0f, (rect.height()-this->height())/2.0f);
}

void MainWindow::initUI()
{
    setWindowTitle(QString("quick-x-player - %1x%2 - %3")
                   .arg(m_projectConfig.getFrameSize().width)
                   .arg(m_projectConfig.getFrameSize().height)
                   .arg(m_projectConfig.getFrameScale()));
    setAttribute(Qt::WA_DeleteOnClose);

    //
    QActionGroup *actionGroup = new QActionGroup(this);
    CCSize size = m_projectConfig.getFrameSize();
    for (int i = 0; i < SimulatorConfig::sharedDefaults()->getScreenSizeCount(); i++) {
        const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        QAction *action = ui->menuView->addAction(QString::fromLocal8Bit(screenSize.title.data()));
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

    ui->menuView->addSeparator();

    //
    actionGroup = new QActionGroup(this);

    QAction *landscapeAction = ui->menuView->addAction(tr("Landscape"));
    landscapeAction->setData(kLandscape);
    landscapeAction->setCheckable(true);
    connect(landscapeAction, SIGNAL(triggered()), this, SLOT(onLandscapeTriggered()));

    QAction *portraitAction = ui->menuView->addAction(tr("Portrait"));
    portraitAction->setData(kPortrait);
    portraitAction->setCheckable(true);
    connect(portraitAction, SIGNAL(triggered()), this, SLOT(onLandscapeTriggered()));

    actionGroup->addAction(landscapeAction);
    actionGroup->addAction(portraitAction);

    if (m_projectConfig.isLandscapeFrame()) {
        landscapeAction->setChecked(true);
    } else {
        portraitAction->setChecked(true);
    }

    ui->menuView->addSeparator();

    //
    actionGroup = new QActionGroup(this);
    QAction *screenScale100 = ui->menuView->addAction(tr("100% scale"));
    screenScale100->setData(1.0f);
    screenScale100->setCheckable(true);
    connect(screenScale100, SIGNAL(triggered()), this, SLOT(onScreenScaleTriggered()));

    QAction *screenScale50 = ui->menuView->addAction(tr("50% scale"));
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

void MainWindow::buildObjectTree()
{
    m_objectTreeModel = new NodeTreeModel(m_objectTreeView);

    m_objectTreeView = new NodeTreeView(this);
    m_objectTreeView->expandAll();
    m_objectTreeView->setModel(m_objectTreeModel);

    ui->objectDockWidget->setWidget(m_objectTreeView);
}

void MainWindow::restart()
{
    qApp->exit('q');
}

void MainWindow::applySettingAndRestart()
{
    QStringList args;
    if (m_projectConfig.getProjectDir().length() > 0)
        args << "-workdir" << m_projectConfig.getProjectDir().data();
    if (m_projectConfig.getScriptFile().length() > 0)
        args << "-file" << m_projectConfig.getScriptFile().data();
    if (m_projectConfig.getWritablePath().length() > 0)
        args << "-writable" << m_projectConfig.getWritablePath().data();

    CCSize frameSize = getSuitableSize(m_projectConfig.getFrameSize());
    args << "-size" << QString("%1x%2").arg(frameSize.width).arg(frameSize.height);
    args << "-scale" << QString::number(m_projectConfig.getFrameScale());

    if (m_projectConfig.isLoadPrecompiledFramework()) {
        args << "-load-framework";
    } else {
        args << "-disable-load-framework";
    }

    if (m_projectConfig.isWriteDebugLogToFile()) {
        args << "-write-debug-log";
    } else {
        args << "-disable-write-debug-log";
    }
//    QString cmd(m_config.makeCommandLine().data());
//    qDebug() << cmd.split(" ");
    qDebug() << args;
    qApp->setProperty(RESTART_ARGS, args);
    this->restart();
}

CCSize MainWindow::getSuitableSize(const CCSize &portraitSize)
{
    if (ui->actionLandscape->isChecked()) {
        return CCSize(portraitSize.height, portraitSize.width);
    }
    return portraitSize;
}

void MainWindow::on_actionRelaunch_triggered()
{
    this->applySettingAndRestart();
}

void MainWindow::on_actionOpen_triggered()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getProjectDir().length() > 0) {
        dir = QString::fromLocal8Bit(m_projectConfig.getProjectDir().data());
    }

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir
                                      , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        m_projectConfig.setProjectDir(dir.toLocal8Bit().constData());
        this->applySettingAndRestart();
    }
}

void MainWindow::onScreenSizeTriggered()
{
    QAction *action = (QAction*)sender();
    const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(action->data().toInt());
    m_projectConfig.setFrameSize(CCSize(screenSize.width,screenSize.height));

    applySettingAndRestart();
}

void MainWindow::onLandscapeTriggered()
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

void MainWindow::onScreenScaleTriggered()
{
    QAction *action = (QAction*)sender();
    float scale = action->data().toFloat();
    m_projectConfig.setFrameScale(scale);

    applySettingAndRestart();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutUI aboutUI(this);
    aboutUI.exec();
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionConfig_triggered()
{
    ProjectConfigUI ui(m_projectConfig, this);
    if (ui.exec() == QDialog::Accepted) {
        m_projectConfig = ui.getProjectConfig();
        applySettingAndRestart();
    }
}

void MainWindow::on_actionUpdateObject_triggered()
{
    if (m_objectTreeModel) {
        m_objectTreeModel->setModelRootNode(CCDirector::sharedDirector()->getRunningScene());

        MyDataVisitor visitor;
        CCDirector::sharedDirector()->getRunningScene()->acceptVisitor(visitor);
        qDebug() << visitor.getResult().data();
    }
}
