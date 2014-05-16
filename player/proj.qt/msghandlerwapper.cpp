#include "msghandlerwapper.h"
#include <QApplication>
#include <QMutex>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
static void msgHandlerFunction(QtMsgType, const QMessageLogContext &, const QString &msg);
MsgHandlerWapper * MsgHandlerWapper::m_instance = 0;

MsgHandlerWapper * MsgHandlerWapper::instance()
{
    static QMutex mutex;
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        if (!m_instance)
            m_instance = new MsgHandlerWapper;
    }

    return m_instance;
}

void MsgHandlerWapper::cancelHandler()
{
    qInstallMessageHandler(0);
}

MsgHandlerWapper::MsgHandlerWapper()
    : QObject(qApp)
{
    qRegisterMetaType<QtMsgType>("QtMsgType");
    qInstallMessageHandler(msgHandlerFunction);
}

static void msgHandlerFunction(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    QMetaObject::invokeMethod(MsgHandlerWapper::instance(), "message"
                        , Q_ARG(QtMsgType, type)
                        , Q_ARG(QString, msg));
}
#else
static void msgHandlerFunction(QtMsgType type, const char *msg);
MsgHandlerWapper * MsgHandlerWapper::m_instance = 0;

MsgHandlerWapper * MsgHandlerWapper::instance()
{
    static QMutex mutex;
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        if (!m_instance)
            m_instance = new MsgHandlerWapper;
    }

    return m_instance;
}

void MsgHandlerWapper::cancelHandler()
{
    qInstallMsgHandler(0);
}

MsgHandlerWapper::MsgHandlerWapper()
    : QObject(qApp)
{
    qInstallMsgHandler(msgHandlerFunction);
}

static void msgHandlerFunction(QtMsgType type, const char *msg)
{
    QMetaObject::invokeMethod(MsgHandlerWapper::instance(), "message"
                        , Q_ARG(QtMsgType, type)
                        , Q_ARG(QString, msg));
}
#endif
