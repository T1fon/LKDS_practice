#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>
#include "../Controller/controller_databasemanager.h"

class FirstWindow : public QObject
{
    Q_OBJECT

public:
    explicit FirstWindow(QObject *parent = nullptr);
    ~FirstWindow();

private:
    QQmlApplicationEngine *__engine;
    Controller_DatabaseManager *__model;
signals:

};

#endif // FIRSTWINDOW_H
