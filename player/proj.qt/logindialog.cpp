#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::accept()
{
    if (ui->userName->text().isEmpty() || ui->password->text().isEmpty())
    {
        QMessageBox::warning(this, this->windowTitle(),
                             tr("Please complete all infomation"),
                             QMessageBox::Ok);
    }
    else
    {
        Q_EMIT sigLogin(ui->userName->text(), ui->password->text());
        QDialog::accept();
    }
}
