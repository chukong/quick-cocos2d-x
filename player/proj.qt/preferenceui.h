#ifndef PREFERENCEUI_H
#define PREFERENCEUI_H

#include <QDialog>

namespace Ui {
class PreferenceUI;
}

class PreferenceUI : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceUI(QWidget *parent = 0);
    ~PreferenceUI();

Q_SIGNALS:
    void sigSaveQuickRootPath(QString path);

private Q_SLOTS:
    void onSelectDir();
    void onSave();

private:
    Ui::PreferenceUI *ui;
};

#endif // PREFERENCEUI_H
