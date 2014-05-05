#ifndef MSGHANDLERWAPPER_H
#define MSGHANDLERWAPPER_H

#include <QObject>

class MsgHandlerWapper:public QObject
{
    Q_OBJECT
public:
    static MsgHandlerWapper * instance();
    void cancelHandler();

Q_SIGNALS:
    void message(QtMsgType type, const QString &msg);

private:
    MsgHandlerWapper();
    static MsgHandlerWapper * m_instance;
};

#endif // MSGHANDLERWAPPER_H
