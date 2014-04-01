/*
 * 浏览,记录log
 * @author: jimi yin
 * @date  : 2014-03-11
 */

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

namespace Ui {
class ConsoleUI;
}

class ConsoleUI : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleUI(QWidget *parent = 0);
    ~ConsoleUI();

    void initWithLogFile(QString logPath);
    void openLogFile();
    void setRecordDebugLog(bool);

public Q_SLOTS:
    void dealWithMessageOutput(QtMsgType /*type*/, const QString &msg);

protected:
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

private Q_SLOTS:
    void onLogClear();
    void onAllwaysTop(bool checked);
    void onOpenLogFile();
    void appendMsg(const QString &msg);

private:
    Ui::ConsoleUI *ui;

    QFile        m_logFile;
    QTextStream  m_textStream;
    QString      m_buff;
    bool         m_isRecording;
};

#endif // CONSOLEUI_H
