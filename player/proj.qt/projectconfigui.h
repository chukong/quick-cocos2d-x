#ifndef PROJECTCONFIGUI_H
#define PROJECTCONFIGUI_H

#include <QDialog>
#include "SimulatorConfig.h"

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
private Q_SLOTS:
    void on_projectDirButton_clicked();

    void on_scriptFileNameButton_clicked();

    void on_writeablePathButton_clicked();

    void on_screenSizeComboBox_activated(int index);

    void on_protratCheckBox_clicked(bool checked);

    void on_landscapeCheckBox_clicked(bool checked);

    void on_loadPreFramework_clicked(bool checked);

    void on_logToFile_clicked(bool checked);

private:
    Ui::ProjectConfigUI *ui;
    ProjectConfig m_projectConfig;
};

#endif // PROJECTCONFIGUI_H
