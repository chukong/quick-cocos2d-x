#ifndef CREATEPROJECTUI_H
#define CREATEPROJECTUI_H

#include <QDialog>

namespace Ui {
class CreateProjectUI;
}

class CreateProjectUI : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProjectUI(QWidget *parent = 0);
    ~CreateProjectUI();
    void createNewProject();

    void accept();
private Q_SLOTS:
    void onSelectFolder();
    void onOk();
    void updateProjectFolderLabel();

private:
    void initData();
    bool checkAllInfor();
private:
    Ui::CreateProjectUI *ui;
    int m_status;
    QString m_projectFolder;
};

#endif // CREATEPROJECTUI_H
