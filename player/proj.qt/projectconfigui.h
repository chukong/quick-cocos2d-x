#ifndef PROJECTCONFIGUI_H
#define PROJECTCONFIGUI_H

#include <QDialog>
#include "ProjectConfig/SimulatorConfig.h"

namespace Ui {
class ProjectConfigUI;
}

class ProjectConfigUI : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectConfigUI(ProjectConfig& projectConfig, QWidget *parent = 0);
    ~ProjectConfigUI();

    void setDataForUI(ProjectConfig& projectConfig);

    ProjectConfig getProjectConfig();

    void accept();
private Q_SLOTS:
    void on_projectDirButton_clicked();

    void on_scriptFileNameButton_clicked();

    void on_writeablePathButton_clicked();

    void on_screenSizeComboBox_activated(int index);

    void on_protratCheckBox_clicked(bool checked);

    void on_landscapeCheckBox_clicked(bool checked);

    void on_loadPreFramework_clicked(bool checked);

    void on_logToFile_clicked(bool checked);

    void on_showDebugConsole_clicked(bool checked);

    void on_screenWidth_textChanged(const QString &arg1);

    void on_screenHeight_textChanged(const QString &arg1);

private:
    void clearUIDataAndSignal();
    void reconnectUISignal();
    bool isAllDataOK(QString &errorString);

private:
    Ui::ProjectConfigUI *ui;
    ProjectConfig m_projectConfig;
};

#endif // PROJECTCONFIGUI_H
