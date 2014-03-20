#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "lua.hpp"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    L(0)
{
    ui->setupUi(this);
}

void LoginDialog::setLuaState(lua_State *state)
{
    L = state;
}

LoginDialog::~LoginDialog()
{
    delete ui;
    L = NULL;
}

void LoginDialog::accept()
{
    if (ui->userName->text().isEmpty() || ui->password->text().isEmpty())
    {
        QMessageBox::warning(this, this->windowTitle(),
                             tr("Please complete all infomation"),
                             QMessageBox::Ok);
    } else
    {
        if (this->luaCallback())
        {
            QDialog::accept();
        }
    }
}

bool LoginDialog::luaCallback()
{
    if (!L) return true;

    lua_getglobal(L, "PlayerLoginCallback");

    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1);
        return true;
    }

    lua_pushstring(L, ui->userName->text().toLocal8Bit().data());
    lua_pushstring(L, ui->password->text().toLocal8Bit().data());

    bool ret = true;
    if (!lua_pcall(L, 2, 2, 0))
    {
        // success
        ret = lua_toboolean(L, -2);
        const char *msg = lua_tostring(L, -1);
        lua_pop(L, 1);

        // error message
        if (!ret)
            QMessageBox::warning(this, this->windowTitle(), msg, QMessageBox::Ok);
    }
    else
    {
        // error
        const char *errMsg = lua_tostring(L, -1);
        lua_pop(L, 1);
        ret = true;

        QMessageBox::warning(this, this->windowTitle(), errMsg, QMessageBox::Ok);
    }

    return ret;
}
