#include "consoleui.h"
#include "ui_consoleui.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QProcess>

ConsoleUI::ConsoleUI(QWidget *parent) :
    QWidget(parent),
    ui(0),
    m_isRecording(true)
{
}

ConsoleUI::~ConsoleUI()
{
    m_logFile.close();
    m_buff.clear();
    if (ui)
        delete ui;
}

void ConsoleUI::initWithLogFile(QString logPath)
{
    m_logFile.setFileName(logPath);
    m_textStream.setDevice(&m_logFile);
    if (!m_logFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QMessageBox::warning(this, tr("quick-x-cocos2d"), m_logFile.errorString() + "\n" + logPath, QMessageBox::Ok);
    }
    if (m_buff.size() && m_isRecording)
    {
        m_textStream << m_buff << "\n";
        m_textStream.flush();
    }
    setWindowTitle(logPath);
}

void ConsoleUI::openLogFile()
{
    this->onOpenLogFile();
}

void ConsoleUI::setRecordDebugLog(bool recording)
{
    m_isRecording = recording;
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
        if (!m_logFile.fileName().isEmpty())
        {
            setWindowTitle(m_logFile.fileName());
        }
        connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(onLogClear()));
        connect(ui->allwaysTop, SIGNAL(clicked(bool)), this, SLOT(onAllwaysTop(bool)));
        connect(ui->openLogButton, SIGNAL(clicked()), this, SLOT(onOpenLogFile()));

        this->appendMsg(m_buff);
        m_buff.clear();
    }

    QWidget::showEvent(e);
}

void ConsoleUI::dealWithMessageOutput(QtMsgType, const QString &msg)
{
    // log ui
    // using buff to cache the output message
    //
    if (!ui)
    {
        m_buff += msg;
        m_buff += "\n";
        fflush(0);
    }
    else
    {
        if (m_buff.length() > 0)
        {
            ui->textBrowser->append(m_buff);
            m_buff.clear();
        }
        this->appendMsg(msg);
    }

    // log file
    if (m_logFile.isOpen() && m_isRecording)
    {
        m_textStream << msg << "\n";
        m_textStream.flush();
    }
}

void ConsoleUI::onLogClear()
{
    if (ui)
    {
        ui->textBrowser->clear();
    }
}

void ConsoleUI::onAllwaysTop(bool checked)
{
    Qt::WindowFlags flags = windowFlags();
    QPoint pos = this->pos();
    if (checked)
    {
        flags ^= Qt::WindowStaysOnBottomHint;
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        flags ^= Qt::WindowStaysOnTopHint;
        flags |= Qt::WindowStaysOnBottomHint;
    }
    setWindowFlags(flags);
    show();
    move(pos);
}

void ConsoleUI::onOpenLogFile()
{
    if (m_logFile.fileName().isEmpty())
    {
#ifdef Q_OS_MAC
        QDesktopServices::openUrl(QUrl::fromLocalFile("/Applications/Utilities/Console.app"));
#endif
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_logFile.fileName()));
    }
}

void ConsoleUI::appendMsg(const QString &msg)
{
    ui->textBrowser->append(msg);
    if (ui->scrollButton->isChecked())
    {
        QTextCursor cursor = ui->textBrowser->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textBrowser->setTextCursor(cursor);
    }
}
