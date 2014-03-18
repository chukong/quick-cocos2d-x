#include "consoleui.h"
#include "ui_consoleui.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QProcess>

ConsoleUI::ConsoleUI(QWidget *parent) :
    QDialog(parent),
    ui(0)
{
}

ConsoleUI::~ConsoleUI()
{
    m_logFile.close();
    m_buff.clear();
    if (ui)
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

void ConsoleUI::openLogFile()
{
    this->onOpenLogFile();
}

void ConsoleUI::closeEvent(QCloseEvent *e)
{
    this->hide();
    e->ignore();
}

void ConsoleUI::showEvent(QShowEvent *e)
{
    if (!ui) {
        ui = new Ui::ConsoleUI;
        ui->setupUi(this);
        if (!m_logFile.fileName().isEmpty()) {
            setWindowTitle(m_logFile.fileName());
        }
        connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(onLogClear()));
        connect(ui->allwaysTop, SIGNAL(clicked(bool)), this, SLOT(onAllwaysTop(bool)));
        connect(ui->openLogButton, SIGNAL(clicked()), this, SLOT(onOpenLogFile()));

        this->appendMsg(m_buff);
        m_buff.clear();
    }
    QDialog::showEvent(e);
}

void ConsoleUI::dealWithMessageOutput(QtMsgType, const QString &msg)
{
    // log ui
    // using buff to cache the output message
    //
    if (!ui) {
        m_buff += msg;
        m_buff += "\n";
        fflush(0);
    } else {
        if (m_buff.length() > 0) {
            ui->textBrowser->append(m_buff);
            m_buff.clear();
        }
        this->appendMsg(msg);
    }

    // log file
    if (m_logFile.isOpen()) {
        m_textStream << msg << "\n";
        m_textStream.flush();
    }
}

void ConsoleUI::onLogClear()
{
    if (ui)
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
    if (m_logFile.fileName().isEmpty()) {
#ifdef Q_OS_MAC
        QDesktopServices::openUrl(QUrl::fromLocalFile("/Applications/Utilities/Console.app"));
#endif
    } else {
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_logFile.fileName()));
    }
}

void ConsoleUI::appendMsg(const QString &msg)
{
    ui->textBrowser->append(msg);
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cursor);
}
