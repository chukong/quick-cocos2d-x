#include "nodetreemodel.h"
#include <cocos2d.h>

USING_NS_CC;
NodeTreeModel::NodeTreeModel(QObject *parent)
    : QStandardItemModel(parent)
    , m_timer(0)
{
//    m_timer = startTimer(1 * 1000);
}

void NodeTreeModel::setModelRootNode(CCNode *node)
{
    if (!node ) return ;

    clear();

    QStandardItem *rootNode = this->invisibleRootItem();
    addNode(node, rootNode);
}

void NodeTreeModel::timerEvent(QTimerEvent *)
{

}

void NodeTreeModel::addNode(CCNode *node, QStandardItem *qnode)
{
    qlonglong addr = (qlonglong)(node);
    QStandardItem *newItem = new QStandardItem(QString::number(addr));
    qnode->appendRow(newItem);

    for (unsigned int i = 0; i < node->getChildrenCount(); i++) {
        CCNode *childNode = (CCNode*)node->getChildren()->objectAtIndex(i);
        addNode(childNode, newItem);
    }
}
