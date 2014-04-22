#ifndef QUICKDEMOWEBVIEW_H
#define QUICKDEMOWEBVIEW_H

#include <QScrollArea>

class QSignalMapper;
class QuickDemoList : public QScrollArea
{
    Q_OBJECT
public:
    explicit QuickDemoList(QWidget *parent = 0);

    void addDemos(QVariantList demoDataList);

Q_SIGNALS:
    void sigOpenDemo(QString demoId);

protected Q_SLOTS:
    void onOpenDemo(QString demoId);

private:
    void initUI();
    QWidget *createOneDemoWidget(QVariantMap data);

private:
    QWidget         *m_listWidget;
    QSignalMapper   *m_signalMapper;
};


#endif // QUICKDEMOWEBVIEW_H
