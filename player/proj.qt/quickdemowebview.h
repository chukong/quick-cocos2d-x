#ifndef QUICKDEMOWEBVIEW_H
#define QUICKDEMOWEBVIEW_H

#include <QWebView>

class QuickDemoWebView : public QWebView
{
    Q_OBJECT
public:
    explicit QuickDemoWebView(QWidget *parent = 0);
    void setObject(QObject *obj);
    void load(const QString &filePath);
    void load(const QUrl &url);

public Q_SLOTS:
    void addJavaScriptObject();

private:
    QObject *m_object;  // weak ref
};

#endif // QUICKDEMOWEBVIEW_H
