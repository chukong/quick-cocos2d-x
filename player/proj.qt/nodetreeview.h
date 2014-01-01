#ifndef NODETREEVIEW_H
#define NODETREEVIEW_H

#include <QTreeView>

class NodeTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit NodeTreeView(QWidget *parent = 0);
};

#endif // NODETREEVIEW_H
