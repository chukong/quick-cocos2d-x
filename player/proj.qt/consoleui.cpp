#include "consoleui.h"
#include "ui_consoleui.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopServices>

ConsoleUI::ConsoleUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsoleUI)
{
    ui->setupUi(this);

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(onLogClear()));
    connect(ui->allwaysTop, SIGNAL(clicked(bool)), this, SLOT(onAllwaysTop(bool)));
    connect(ui->openLogButton, SIGNAL(clicked()), this, SLOT(onOpenLogFile()));
}

ConsoleUI::~ConsoleUI()
{
    m_logFile.close();
    delete ui;
}

ConsoleUI *ConsoleUI::instance()
{
    static ConsoleUI *consoleUI = NULL;
    if (!consoleUI) {
        consoleUI = new ConsoleUI();
    }
    return consoleUI;
}

void ConsoleUI::initWithLogFile(QString logPath)
{
    m_logFile.setFileName(logPath);
    m_textStream.setDevice(&m_logFile);
    if (!m_logFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QMessageBox::warning(this, tr("quick-x-cocos2d"), m_logFile.errorString() + "\n" + logPath, QMessageBox::Ok);
    }
    setWindowTitle(logPath);
}

void ConsoleUI::closeEvent(QCloseEvent *e)
{
    this->hide();
    e->ignore();
}

void ConsoleUI::dealWithMessageOutput(QtMsgType, const QString &msg)
{
    // log ui
    ui->textBrowser->append(msg);
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cursor);

    // log file
    if (m_logFile.isOpen()) {
        m_textStream << msg << "\n";
        m_textStream.flush();
    }
}

void ConsoleUI::onLogClear()
{
    ui->textBrowser->clear();
}

void ConsoleUI::onAllwaysTop(bool checked)
{
    // FIXME: http://stackoverflow.com/questions/19097323/setwindowflagsqtwindowstaysontophint-hides-qt-window
    QPoint pos = this->pos();
    if (checked) {
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    } else {
        setWindowFlags(windowFlags() ^ Qt::WindowStaysOnTopHint);
    }
    setVisible(true);
    activateWindow();
    raise();
    this->move(pos);
}

void ConsoleUI::onOpenLogFile()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_logFile.fileName()));
}
