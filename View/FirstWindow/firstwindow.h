#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>

class FirstWindow : public QObject
{
    Q_OBJECT

public:
    explicit FirstWindow(QObject *parent = nullptr);
    ~FirstWindow();

private:
    QQmlApplicationEngine *__engine;
signals:

};

#endif // FIRSTWINDOW_H
