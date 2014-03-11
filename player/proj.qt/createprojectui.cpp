#include "createprojectui.h"
#include "ui_createprojectui.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include "SimulatorConfig.h"
#include <QtDebug>

CreateProjectUI::CreateProjectUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProjectUI)
{
    ui->setupUi(this);
    this->initData();
}

CreateProjectUI::~CreateProjectUI()
{
    delete ui;
}

void CreateProjectUI::onSelectFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Get project folder"),
                                                         QString(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data()));
    ui->projectPath->setText(folderPath);
}

void CreateProjectUI::onOk()
{
    this->accept();
}

void CreateProjectUI::initData()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onSelectFolder()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
}


void CreateProjectUI::createNewProject()
{
    QProcess createProject;
    QString shell(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
#if defined(_WINDOWS)
    shell.append("bin/create_project.bat");
#else
    shell.append("bin/create_project.sh");
#endif

    QStringList args;
    if (ui->portait->isChecked())
        args << "-o portrait";
    else
        args << "-o landscape";

    args << "-f";
    args << ui->packageName->text();
    createProject.start(shell, args);
    if (!createProject.waitForFinished()) {
        QMessageBox::warning(this, tr("quick-x-cocos2d"),
                                   tr("Create new project failed."),
                                   QMessageBox::Ok);
    }
    ui->cmdLog->setText( createProject.readAll() );
    QTextCursor c =  ui->cmdLog->textCursor();
    c.movePosition(QTextCursor::End);
    ui->cmdLog->setTextCursor(c);
}

void CreateProjectUI::accept()
{
    if (ui->projectPath->text().isEmpty() || ui->packageName->text().isEmpty()) {
        QMessageBox::warning(this, tr("quick-x-cocos2d"),
                             tr("Please complete all infomation"),
                             QMessageBox::Ok);
    } else {
        this->createNewProject();
//        QDialog::accept();
    }
}
