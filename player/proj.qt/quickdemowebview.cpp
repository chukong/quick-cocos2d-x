#include "quickdemowebview.h"
#include <QWebFrame>
#include <QApplication>
#include <QtDebug>
#include "mainmenu.h"

QuickDemoWebView::QuickDemoWebView(QWidget *parent) :
    QWebView(parent)
{
    // web view
    setWindowTitle("Quick-x-cocos2d demo list");
    settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()), this, SLOT(addJavaScriptObject()));
}

void QuickDemoWebView::load(const QString& filePath)
{
    this->load(QUrl::fromLocalFile(filePath));
}

void QuickDemoWebView::load(const QUrl &url)
{
    page()->mainFrame()->load(url);
}

void QuickDemoWebView::addJavaScriptObject()
{
    page()->mainFrame()->addToJavaScriptWindowObject("quickx", &m_quickx);
}


QuickX::QuickX(QObject *parent)
    : QObject(parent)
{

}

void QuickX::openDemoWithArgs(QString cmds)
{
    QStringList args = cmds.split(",");
    qApp->setProperty(RESTART_ARGS, args);
    qApp->exit(APP_EXIT_CODE);
}
