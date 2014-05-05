#ifndef ABOUTUI_H
#define ABOUTUI_H

#include <QDialog>

namespace Ui {
class AboutUI;
}

class AboutUI : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutUI(QWidget *parent = 0);
    ~AboutUI();
    
private:
    Ui::AboutUI *ui;
};

#endif // ABOUTUI_H
