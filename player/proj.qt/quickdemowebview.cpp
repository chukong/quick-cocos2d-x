#include "quickdemowebview.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVariantMap>
#include <QSignalMapper>

#define KeyDemoId   "id"
#define KeyDemoText "text"
static const QSize DemoMinSize(300, 100);

/*
 * show quick-cocos2d-x demos
 */
QuickDemoList::QuickDemoList(QWidget *parent)
    : QScrollArea(parent)
    , m_listWidget(0)
    , m_signalMapper(new QSignalMapper(this))
{
    initUI();
    connect(m_signalMapper, SIGNAL(mapped(QString)), this, SLOT(onOpenDemo(QString)));
}

void QuickDemoList::addDemos(QVariantList demoDataList)
{
    Q_FOREACH(QVariant data, demoDataList)
    {
        m_listWidget->layout()->addWidget(createOneDemoWidget(data.toMap()));
    }

    m_listWidget->adjustSize();
}

void QuickDemoList::onOpenDemo(QString demoId)
{
    Q_EMIT sigOpenDemo(demoId);
}

void QuickDemoList::initUI()
{
    setWindowTitle(tr("quick-cocos2d-x demo list"));
    setMinimumSize(DemoMinSize);

    QVBoxLayout *layout = new QVBoxLayout();

    m_listWidget =new QWidget();
    m_listWidget->setLayout(layout);

    setWidget(m_listWidget);
}

QWidget *QuickDemoList::createOneDemoWidget(QVariantMap data)
{
    QString infoText = data[KeyDemoText].toString();
    if (infoText.isEmpty())
        infoText = "<b>One Demo</b> <br/> <img src=\":/QuickIcon.png\"</img>";

    QLabel *info = new QLabel();
    info->setObjectName("demoInfoLabel");
    info->setText(infoText);

    QPushButton *openButton = new QPushButton(tr("Open"));
    openButton->setObjectName("openDemoBtn");
    connect(openButton, SIGNAL(clicked()), m_signalMapper, SLOT(map()));

    m_signalMapper->setMapping(openButton, data[KeyDemoId].toString());

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(info);
    layout->addWidget(openButton);
    layout->setAlignment(openButton, Qt::AlignBottom);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);

    return widget;
}
