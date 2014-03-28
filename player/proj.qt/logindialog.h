/*
 * 登录ui
 * @author: jimi yin
 * @date  : 2014-03-11
 */
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

struct lua_State;
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);

    ~LoginDialog();
    void accept();

Q_SIGNALS:
    void sigLogin(QString userName, QString password);

private:
    void luaCallback();

private:
    Ui::LoginDialog *ui;
    lua_State *L;       // weak ref
};

#endif // LOGINDIALOG_H
