#include "createprojectui.h"
#include "ui_createprojectui.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QFileInfo>
#include "ProjectConfig/SimulatorConfig.h"
#include "player.h"

#define CreateProjectUIStatus_creating      1
#define CreateProjectUIStatus_showProject   2

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
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->stopAnimation();

    QFileDialog::Options dialogOptions = QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks;
#ifdef Q_OS_MAC
    // https://bugreports.qt-project.org/browse/QTBUG-2587
    #if (QT_VERSION <= QT_VERSION_CHECK(5, 2, 0))
        dialogOptions |= QFileDialog::DontUseNativeDialog;
    #endif
#endif
    QString folderPath = QFileDialog::getExistingDirectory(this
                                                           , tr("Get project folder")
                                                           , QString(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data())
                                                           , dialogOptions);
    if (!folderPath.isEmpty())
    {
        ui->projectPath->setText(folderPath);
    }

	pDirector->startAnimation();
}

void CreateProjectUI::onOk()
{
    this->accept();
}

void CreateProjectUI::initData()
{
    m_status = CreateProjectUIStatus_creating;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onSelectFolder()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->packageName, SIGNAL(textChanged(QString)), this, SLOT(updateProjectFolderLabel()));
    connect(ui->projectPath, SIGNAL(textChanged(QString)), this, SLOT(updateProjectFolderLabel()));
}

void CreateProjectUI::updateProjectFolderLabel()
{
    QString packageName = ui->packageName->text();
    QStringList nameList = packageName.split(".");
    m_projectFolder = ui->projectPath->text() + "/" + nameList.last();
    ui->projectFolder->setText(m_projectFolder);
}

void CreateProjectUI::createNewProject()
{
    QProcess createProject;
    QString shell(SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().data());
#if defined(Q_OS_WIN)
    shell.append("bin/create_project.bat");
#else
    shell.append("bin/create_project.sh");
#endif

    QStringList args = Player::instance()->getCreateProjectCommandArgs(m_projectFolder,
                                                                       ui->packageName->text(),
                                                                       ui->portait->isChecked());
    QString commandLine = shell + " " + args.join(" ");
    createProject.start(shell, args);

    if (!createProject.waitForFinished())
    {
        QMessageBox::warning(this, tr("quick-x-cocos2d"),
                                   tr("Create new project failed."),
                                   QMessageBox::Ok);
    }

    ui->cmdLog->setText( createProject.readAll() );
    ui->cmdLog->append(commandLine);
    QTextCursor c =  ui->cmdLog->textCursor();
    c.movePosition(QTextCursor::End);
    ui->cmdLog->setTextCursor(c);

    if (createProject.exitCode() == 0)
    {
        // change ui
        m_status = CreateProjectUIStatus_showProject;
        ui->cancel->setText(tr("Close"));
#ifdef Q_OS_MAC
        ui->ok->setText(tr("Finder"));
#else
        ui->ok->setText(tr("Show in Explorer"));
#endif
    }
}

bool CreateProjectUI::checkAllInfor()
{
    QString errString;
    bool isValid = true;
    QFileInfo location(ui->projectPath->text());
    if (!location.exists())
    {
        isValid = false;
        errString = QString("project location: [%1] is not exists.\n").arg(ui->projectPath->text());
    }
    else
    {
        if (!location.permission(QFile::WriteUser))
        {
            isValid = false;
            errString += QString("project location: [%1] cat not write.\n").arg(ui->projectPath->text());
        }
    }

    QStringList packageNameList = ui->packageName->text().split(".");
    if (packageNameList.size() < 2 || packageNameList.contains(""))
    {
        isValid = false;
        errString += QString("package name: [%1] is not valid.\n").arg(ui->packageName->text());
    }

    location.setFile(m_projectFolder);
    if (location.exists())
    {
        isValid  = false;
        errString += QString("project: [%1] is exists.\n").arg(m_projectFolder);
    }

    if (!isValid)
    {
        QMessageBox::warning(0, tr("quick-x-cocos2d"),
                             errString,
                             QMessageBox::Ok);
    }

    return isValid;
}

void CreateProjectUI::accept()
{

        if (m_status == CreateProjectUIStatus_creating)
        {
            if (checkAllInfor())
            {
                this->createNewProject();
            }
        }
        else if (m_status == CreateProjectUIStatus_showProject)
        {
            Player::instance()->onOpenURL(m_projectFolder.toLocal8Bit().constData());
        }

}
