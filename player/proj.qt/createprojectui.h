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

private:
    void initData();

private:
    Ui::CreateProjectUI *ui;
};

#endif // CREATEPROJECTUI_H
