#include "mainmenu.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextBrowser>
#include <QFile>
#include <QScrollBar>
#include <QMenuBar>
#include <QDebug>

#include "aboutui.h"
#include "projectconfigui.h"

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

MainMenu::MainMenu(QWidget *renderWidget, QObject *parent)
    : QObject(parent)
    , m_renderWidget(renderWidget)
{
    Q_ASSERT(renderWidget && "The render widget MUST not be null");

    m_textBrowser = new QTextBrowser(0);
    m_textBrowser->scrollBarWidgets(Qt::AlignBottom);
    QFont font("Helvetica");
    font.setStyleHint(QFont::Monospace);
    m_textBrowser->setFont(font);
    QTimer::singleShot(10, m_textBrowser, SLOT(show()));
    g_textBrowser = m_textBrowser;
    qInstallMessageHandler(myMessageOutput);

    QMenuBar *mainMenu = new QMenuBar(m_renderWidget);
    mainMenu->setNativeMenuBar(true);

    // file menu
    QMenu *fileMenu = mainMenu->addMenu(QObject::tr("&File"));
    fileMenu->addAction("&Open", this, SLOT(on_actionOpen_triggered()), QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addAction("&Relaunch", this, SLOT(on_actionRelaunch_triggered()), QKeySequence(Qt::Key_F5));
//    fileMenu->addAction("&Close",  qApp, SLOT(quit()), QKeySequence(QObject::tr("Ctrl+c")));

    // view menu
    m_viewMenu = mainMenu->addMenu(QObject::tr("&View"));

    // more menu
    QMenu *moreMenu = mainMenu->addMenu(QObject::tr("&More"));
    moreMenu->addAction("&AboutQt", this, SLOT(on_actionAboutQt_triggered()));
    moreMenu->addAction("&About", this, SLOT(on_actionAbout_triggered()));

    mainMenu->show();
}

MainMenu::~MainMenu()
{
    CC_SAFE_DELETE(m_textBrowser);
}

void MainMenu::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
    initUI();

    if (m_projectConfig.isWriteDebugLogToFile()) {
        QString logFileName = QString("%1/quick-x-%2.log")
                                        .arg(qApp->applicationDirPath())
                                        .arg(QTime::currentTime().toString().replace(":","-"));
        QFile *g_file = new QFile(logFileName, this);
        g_textStream = new QTextStream(g_file);

        if (g_file->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
            g_file->write(g_textBrowser->toPlainText().toLocal8Bit(), g_textBrowser->toPlainText().length());
            g_file->flush();
        } else {
            qDebug() << "Can not open file " << g_file->fileName() << g_file->errorString();
        }
    }
}

void MainMenu::initUI()
{
    m_renderWidget->setWindowTitle(QString("quick-x-player - %1x%2 - %3")
                   .arg(m_projectConfig.getFrameSize().width)
                   .arg(m_projectConfig.getFrameSize().height)
                   .arg(m_projectConfig.getFrameScale()));
    m_renderWidget->setAttribute(Qt::WA_DeleteOnClose);

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
    qDebug() << args;
    qApp->setProperty(RESTART_ARGS, args);
    this->restart();
}

CCSize MainMenu::getSuitableSize(const CCSize &portraitSize)
{
    CCSize size(portraitSize);
    if (m_landscapeAction->isChecked()) {
        size = CCSize(portraitSize.height, portraitSize.width);
    }
    return size;
}

void MainMenu::on_actionRelaunch_triggered()
{
    this->applySettingAndRestart();
}

void MainMenu::on_actionOpen_triggered()
{
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
