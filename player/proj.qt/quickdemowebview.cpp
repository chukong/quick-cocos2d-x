#include "quickdemowebview.h"
#include <QWebFrame>
#include <QApplication>

QuickDemoWebView::QuickDemoWebView(QWidget *parent) :
    QWebView(parent),
    m_object(0)
{
    // web view
    setWindowTitle(tr("quick-x-cocos2d demo list"));
    settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()), this, SLOT(addJavaScriptObject()));
}

void QuickDemoWebView::setObject(QObject *obj)
{
    m_object = obj;
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
    if (m_object)
        page()->mainFrame()->addToJavaScriptWindowObject("quickx", m_object);
}
