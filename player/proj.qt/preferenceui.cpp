#include "preferenceui.h"
#include "ui_preferenceui.h"

#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

PreferenceUI::PreferenceUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceUI)
{
    ui->setupUi(this);

    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(onSelectDir()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui->saveButton, SIGNAL(clicked()), SLOT(onSave()));
}

PreferenceUI::~PreferenceUI()
{
    delete ui;
}

void PreferenceUI::onSelectDir()
{
    ui->rootPath->setText( QFileDialog::getExistingDirectory() );
}

void PreferenceUI::onSave()
{
    QDir dir(ui->rootPath->text());
    if (dir.exists()) {
        QSettings settings;
        settings.setValue("QUICK_COCOS2DX_ROOT", dir.absolutePath());
        close();
    }
    else {
        QMessageBox::warning(this, "", tr("The root path is not exist.\nPlist choose the other"), QMessageBox::Ok);
    }
}
