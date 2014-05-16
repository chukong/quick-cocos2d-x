#include "preferenceui.h"
#include "ui_preferenceui.h"

#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include "ProjectConfig/SimulatorConfig.h"

PreferenceUI::PreferenceUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceUI)
{
    ui->setupUi(this);

    ui->rootPath->setText(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
    ui->saveButton->setFocus();
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

    QDir dir = QDir(QCoreApplication::applicationDirPath());
    QFileDialog::Options dialogOptions = QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks;
#ifdef Q_OS_MAC
    // https://bugreports.qt-project.org/browse/QTBUG-2587
    #if (QT_VERSION <= QT_VERSION_CHECK(5, 2, 0))
        dialogOptions |= QFileDialog::DontUseNativeDialog;
    #endif

    if (SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().length() <= 0)
        dir.cdUp(), dir.cdUp();
    else
        dir = QDir(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
#endif

    QString dirPath = QFileDialog::getExistingDirectory(this, tr("quick-root"), dir.absolutePath(), dialogOptions);
    if (!dirPath.isEmpty())
        ui->rootPath->setText(dirPath);
}

void PreferenceUI::onSave()
{
    QDir dir(ui->rootPath->text());
    if (dir.exists())
    {
        Q_EMIT sigSaveQuickRootPath(dir.absolutePath());
        close();
    }
    else
    {
        QMessageBox::warning(this, "", tr("The root path is not exist.\nPlist choose the other"), QMessageBox::Ok);
    }
}
