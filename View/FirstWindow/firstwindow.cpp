#include "firstwindow.h"
#include "../Controller/controller_databasemanager.h"
#include "../Model/model_database.h"


FirstWindow::FirstWindow(QObject *parent)
    : QObject{parent}
{
    Model_database DataBase;
    DataBase.connectToDataBase();

    __model = new Controller_DatabaseManager;
    __engine = new QQmlApplicationEngine;
    const QUrl url(u"qrc:/View/FirstWindow/FirstWindow.qml"_qs);
    qDebug() << 0;
   // __engine->rootContext()->setContextProperty("DataBase", &DataBase);
   // __engine->rootContext()->setContextProperty("TableModel", __model);
    qDebug() << 1;
    __engine->load(url);

}

FirstWindow::~FirstWindow()
{
    delete __engine;
    delete __model;
}
