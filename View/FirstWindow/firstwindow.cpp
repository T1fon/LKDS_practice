#include "firstwindow.h"

FirstWindow::FirstWindow(QObject *parent)
    : QObject{parent}
{
    __engine = new QQmlApplicationEngine;
    const QUrl url(u"qrc:/View/FirstWindow/FirstWindow.qml"_qs);
    __engine->load(url);
}

FirstWindow::~FirstWindow()
{
    delete __engine;
}
