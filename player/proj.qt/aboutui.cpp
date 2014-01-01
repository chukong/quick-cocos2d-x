#include "aboutui.h"
#include "ui_aboutui.h"

AboutUI::AboutUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutUI)
{
    ui->setupUi(this);
    setWindowTitle(tr("About quick-x-player"));
}

AboutUI::~AboutUI()
{
    delete ui;
}
