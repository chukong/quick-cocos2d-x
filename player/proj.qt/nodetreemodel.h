#ifndef NODETREEMODEL_H
#define NODETREEMODEL_H

#include <QStandardItemModel>
#include <cocos2d.h>

class NodeTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit NodeTreeModel(QObject *parent = 0);
    void setModelRootNode(cocos2d::CCNode *node);

protected:
    virtual void timerEvent(QTimerEvent */*event*/);
    void addNode(cocos2d::CCNode *node, QStandardItem *qnode);

private:
    int m_timer;
};

#endif // NODETREEMODEL_H
