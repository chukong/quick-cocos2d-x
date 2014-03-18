/*
 * 浏览,记录log
 * @author: jimi yin
 * @date  : 2014-03-11
 */

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class ConsoleUI;
}

class ConsoleUI : public QDialog
{
    Q_OBJECT

public:
    explicit ConsoleUI(QWidget *parent = 0);
    ~ConsoleUI();

    static ConsoleUI *instance();
    void initWithLogFile(QString logPath);
    void openLogFile();

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
};

#endif // CONSOLEUI_H
