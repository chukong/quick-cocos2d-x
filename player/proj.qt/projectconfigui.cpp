#include "projectconfigui.h"
#include "ui_projectconfigui.h"

#include <QFileDialog>

ProjectConfigUI::ProjectConfigUI(ProjectConfig& projectConfig, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectConfigUI)
{
    ui->setupUi(this);
    setDataForUI(projectConfig);
}

ProjectConfigUI::~ProjectConfigUI()
{
    delete ui;
}

void ProjectConfigUI::setDataForUI(ProjectConfig &projectConfig)
{
    m_projectConfig = projectConfig;

    ui->projectDir->setText(projectConfig.getProjectDir().data());
    ui->scriptFileName->setText(projectConfig.getScriptFile().data());
    ui->writablePath->setText(projectConfig.getWritablePath().data());

    for (int i = 0; i < SimulatorConfig::sharedDefaults()->getScreenSizeCount(); i++) {
        const SimulatorScreenSize &screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        ui->screenSizeComboBox->addItem(screenSize.title.data());

        CCSize size = projectConfig.getFrameSize();
        if ((screenSize.width == size.width && screenSize.height == size.height)
            ||(screenSize.width == size.height && screenSize.height == size.width)) {
            ui->screenSizeComboBox->setCurrentIndex(i);
        }
    }

    if (projectConfig.isLandscapeFrame()) {
        ui->landscapeCheckBox->setChecked(true);
    } else {
        ui->protratCheckBox->setChecked(true);
    }
    ui->screenWidth->setText(QString::number(projectConfig.getFrameSize().width));
    ui->screenHeight->setText(QString::number(projectConfig.getFrameSize().height));

    ui->loadPreFramework->setChecked(projectConfig.isLoadPrecompiledFramework());
    ui->logToFile->setChecked(projectConfig.isWriteDebugLogToFile());
}

ProjectConfig ProjectConfigUI::getProjectConfig()
{
    return m_projectConfig;
}

void ProjectConfigUI::on_projectDirButton_clicked()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getProjectDir().length() > 0) {
        dir = QString::fromLocal8Bit(m_projectConfig.getProjectDir().data());
    }

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir
                                      , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        m_projectConfig.setProjectDir(dir.toLocal8Bit().constData());
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_scriptFileNameButton_clicked()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getWritablePath().length() > 0) {
        dir = QString::fromLocal8Bit(m_projectConfig.getWritablePath().data());
    }

    QString luaFile = QFileDialog::getOpenFileName(this, tr("Open File")
                                       , dir
                                       , tr("Lua (*.lua)"));

    if (!luaFile.isEmpty()) {
        m_projectConfig.setScriptFile(luaFile.toLocal8Bit().constData());
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_writeablePathButton_clicked()
{
    QString dir = qApp->applicationDirPath();
    if (m_projectConfig.getWritablePath().length() > 0) {
        dir = QString::fromLocal8Bit(m_projectConfig.getWritablePath().data());
    }

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir
                                      , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        m_projectConfig.setWritablePath(dir.toLocal8Bit().constData());
        setDataForUI(m_projectConfig);
    }
}

void ProjectConfigUI::on_screenSizeComboBox_activated(int index)
{
    const SimulatorScreenSize& screenSize = SimulatorConfig::sharedDefaults()->getScreenSize(index);
    m_projectConfig.setFrameSize(CCSize(screenSize.width, screenSize.height));
    if (ui->landscapeCheckBox->isChecked()) {
        m_projectConfig.changeFrameOrientationToLandscape();
    } else {
        m_projectConfig.changeFrameOrientationToPortait();
    }
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_protratCheckBox_clicked(bool checked)
{
    if (checked) {
        m_projectConfig.changeFrameOrientationToPortait();
    } else {
        m_projectConfig.changeFrameOrientationToLandscape();
    }
    ui->landscapeCheckBox->setChecked(false);
    setDataForUI(m_projectConfig);
}

void ProjectConfigUI::on_landscapeCheckBox_clicked(bool checked)
{
    if (checked) {
        m_projectConfig.changeFrameOrientationToLandscape();
    } else {
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
