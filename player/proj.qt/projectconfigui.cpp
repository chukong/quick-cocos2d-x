#include "projectconfigui.h"
#include "ui_projectconfigui.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>

ProjectConfigUI::ProjectConfigUI(ProjectConfig& projectConfig, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectConfigUI)
{
    ui->setupUi(this);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this );
    ui->screenWidth->setValidator(validator);
    ui->screenHeight->setValidator(validator);

    setDataForUI(projectConfig);
}

ProjectConfigUI::~ProjectConfigUI()
{
    delete ui;
}

void ProjectConfigUI::setDataForUI(ProjectConfig &projectConfig)
{
    m_projectConfig = projectConfig;

    clearUIDataAndSignal();
    ui->projectDir->setText(projectConfig.getProjectDir().data());
    ui->scriptFileName->setText(projectConfig.getScriptFile().data());
    ui->writablePath->setText(projectConfig.getWritablePath().data());

    int i = 0;
    int currentIndex = -1;
    for (; i < SimulatorConfig::sharedDefaults()->getScreenSizeCount(); i++)
    {
        const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        ui->screenSizeComboBox->addItem(screenSize.title.data());

        CCSize size = projectConfig.getFrameSize();
        if ((screenSize.width == size.width && screenSize.height == size.height)
            ||(screenSize.width == size.height && screenSize.height == size.width))
        {
            currentIndex = i;
        }
    }

    ui->screenSizeComboBox->addItem(tr("Customized Size"));
    ui->screenSizeComboBox->setCurrentIndex(currentIndex == -1 ? i : currentIndex);

    if (projectConfig.isLandscapeFrame())
        ui->landscapeCheckBox->setChecked(true);
    else
        ui->protratCheckBox->setChecked(true);

    ui->screenWidth->setText(QString::number(projectConfig.getFrameSize().width));
    ui->screenHeight->setText(QString::number(projectConfig.getFrameSize().height));

    ui->showDebugConsole->setChecked(projectConfig.isShowConsole());
    ui->loadPreFramework->setChecked(projectConfig.isLoadPrecompiledFramework());
    ui->logToFile->setChecked(projectConfig.isWriteDebugLogToFile());

    reconnectUISignal();
}

ProjectConfig ProjectConfigUI::getProjectConfig()
{
    return m_projectConfig;
}

void ProjectConfigUI::accept()
{
    QString errorString;
    if (!isAllDataOK(errorString))
    {
        QMessageBox::warning(0, "error", errorString);
    }
    else
    {
        QDialog::accept();
    }
}

void ProjectConfigUI::on_projectDirButton_clicked()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getProjectDir().length() > 0)
        dir = QString::fromLocal8Bit(m_projectConfig.getProjectDir().data());

    QFileDialog::Options dialogOptions = QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks;
#ifdef Q_OS_MAC
    // https://bugreports.qt-project.org/browse/QTBUG-2587
    #if (QT_VERSION <= QT_VERSION_CHECK(5, 2, 0))
        dialogOptions |= QFileDialog::DontUseNativeDialog;
    #endif
#endif
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir, dialogOptions);

    if (!dir.isEmpty())
    {
        m_projectConfig.setProjectDir(dir.toLocal8Bit().constData());
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_scriptFileNameButton_clicked()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getWritablePath().length() > 0)
        dir = QString::fromLocal8Bit(m_projectConfig.getWritablePath().data());

    QString luaFile = QFileDialog::getOpenFileName(this, tr("Open File")
                                       , dir
                                       , tr("Lua (*.lua)"));

    if (!luaFile.isEmpty())
    {
        m_projectConfig.setScriptFile(luaFile.toLocal8Bit().constData());
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_writeablePathButton_clicked()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getWritablePath().length() > 0)
        dir = QString::fromLocal8Bit(m_projectConfig.getWritablePath().data());

    QFileDialog::Options dialogOptions = QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks;
#ifdef Q_OS_MAC
    // https://bugreports.qt-project.org/browse/QTBUG-2587
    #if (QT_VERSION <= QT_VERSION_CHECK(5, 2, 0))
        dialogOptions |= QFileDialog::DontUseNativeDialog;
    #endif
#endif
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir, dialogOptions);

    if (!dir.isEmpty())
    {
        m_projectConfig.setWritablePath(dir.toLocal8Bit().constData());
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_screenSizeComboBox_activated(int index)
{
    if (index >= SimulatorConfig::sharedDefaults()->getScreenSizeCount())
    {
        m_projectConfig.setFrameSize(CCSize(ui->screenWidth->text().toInt(), ui->screenHeight->text().toInt()));
    }
    else
    {
        const SimulatorScreenSize& screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(index);
        m_projectConfig.setFrameSize(CCSize(screenSize.width, screenSize.height));
        if (ui->landscapeCheckBox->isChecked())
        {
            m_projectConfig.changeFrameOrientationToLandscape();
        }
        else
        {
            m_projectConfig.changeFrameOrientationToPortait();
        }
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_protratCheckBox_clicked(bool checked)
{
    if (checked)
    {
        m_projectConfig.changeFrameOrientationToPortait();
    }
    else
    {
        m_projectConfig.changeFrameOrientationToLandscape();
    }
    ui->landscapeCheckBox->setChecked(false);
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_landscapeCheckBox_clicked(bool checked)
{
    if (checked)
    {
        m_projectConfig.changeFrameOrientationToLandscape();
    }
    else
    {
        m_projectConfig.changeFrameOrientationToPortait();
    }
    ui->protratCheckBox->setChecked(false);
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_loadPreFramework_clicked(bool checked)
{
    m_projectConfig.setLoadPrecompiledFramework(checked);
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_logToFile_clicked(bool checked)
{
    m_projectConfig.setWriteDebugLogToFile(checked);
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_showDebugConsole_clicked(bool checked)
{
    m_projectConfig.setShowConsole(checked);
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_screenWidth_textChanged(const QString &arg1)
{
    m_projectConfig.setFrameSize(CCSize(arg1.toInt(), ui->screenHeight->text().toInt()));
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_screenHeight_textChanged(const QString &arg1)
{
    m_projectConfig.setFrameSize(CCSize(ui->screenWidth->text().toInt(), arg1.toInt()));
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::clearUIDataAndSignal()
{
    disconnect(ui->landscapeCheckBox, SIGNAL(clicked(bool)), this, SLOT(on_landscapeCheckBox_clicked(bool)));
    disconnect(ui->protratCheckBox, SIGNAL(clicked(bool)), this, SLOT(on_protratCheckBox_clicked(bool)));

    disconnect(ui->screenWidth, SIGNAL(textChanged(QString)), this, SLOT(on_screenWidth_textChanged(QString)));
    disconnect(ui->screenHeight, SIGNAL(textChanged(QString)), this, SLOT(on_screenHeight_textChanged(QString)));

    ui->landscapeCheckBox->setChecked(false);
    ui->protratCheckBox->setChecked(false);

    ui->screenSizeComboBox->clear();
}

void ProjectConfigUI::reconnectUISignal()
{
    connect(ui->landscapeCheckBox, SIGNAL(clicked(bool)), this, SLOT(on_landscapeCheckBox_clicked(bool)));
    connect(ui->protratCheckBox, SIGNAL(clicked(bool)), this, SLOT(on_protratCheckBox_clicked(bool)));

    connect(ui->screenWidth, SIGNAL(textChanged(QString)), this, SLOT(on_screenWidth_textChanged(QString)));
    connect(ui->screenHeight, SIGNAL(textChanged(QString)), this, SLOT(on_screenHeight_textChanged(QString)));
}

bool ProjectConfigUI::isAllDataOK(QString &errorString)
{
    //
    QDir projectDir(ui->projectDir->text());
    if (!projectDir.exists())
    {
        errorString += "Project Directory: \n" + projectDir.absolutePath() + " does not exists.\n\n";
    }

    QString writablePath = ui->writablePath->text();
    writablePath = writablePath.replace("$PROJDIR", ui->projectDir->text());
    QFileInfo writablePathInfo(writablePath);
    if (!writablePathInfo.exists())
    {
        errorString += "Writable Path: \n" + writablePathInfo.filePath() + " does not exists.\n\n";
    }
    else if(!writablePathInfo.isWritable())
    {
        errorString += "Writable Path: \n" + writablePathInfo.filePath() + " is not writable.\n\n";
    }

    QString scriptFileName = ui->scriptFileName->text();
    scriptFileName = scriptFileName.replace("$PROJDIR", ui->projectDir->text());
    QFileInfo scriptFileInfo(scriptFileName);
    if (!scriptFileInfo.exists())
    {
        errorString += "Lua file: \n" + scriptFileInfo.filePath() + " is not exists.\n\n";
    }

    return errorString.isEmpty();
}
