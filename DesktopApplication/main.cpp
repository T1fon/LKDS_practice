#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "View/FirstWindow/firstwindow.h"
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /*QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/LKDS_practice/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);*/

    FirstWindow f;


    return app.exec();
}
