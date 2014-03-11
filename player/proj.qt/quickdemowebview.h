#ifndef QUICKDEMOWEBVIEW_H
#define QUICKDEMOWEBVIEW_H

#include <QWebView>

class QuickX : public QObject
{
    Q_OBJECT
public:
    QuickX(QObject *parent = 0);

public Q_SLOTS:
    void openDemoWithArgs(QString cmds);
};

class QuickDemoWebView : public QWebView
{
    Q_OBJECT
public:
    explicit QuickDemoWebView(QWidget *parent = 0);
    void load(const QString &filePath);
    void load(const QUrl &url);

public Q_SLOTS:
    void addJavaScriptObject();

private:
    QuickX m_quickx;
};

#endif // QUICKDEMOWEBVIEW_H
