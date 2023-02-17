#include "firstwindow.h"
#include "../Controller/controller_databasemanager.h"
#include "../Model/model_database.h"



FirstWindow::FirstWindow(QObject *parent)
    : QObject{parent}
{
    //DataBase = new Model_database(this);
    //DataBase->connectToDataBase();
    Controller_DatabaseManager c_DB;
    //__model = new Controller_DatabaseManager;
    __engine = new QQmlApplicationEngine;
    __engine->rootContext()->setContextProperty("bd", &c_DB);
    const QUrl url(u"qrc:/View/FirstWindow/FirstWindow.qml"_qs);


    qmlRegisterType<Controller_DatabaseManager>("DatabaseManager", 0, 1, "Controller_DatabaseManager");
   // __engine->rootContext()->setContextProperty("DataBase", &DataBase);
   // __engine->rootContext()->setContextProperty("TableModel", __model);
    qDebug() << 11;
    __engine->load(url);

}

FirstWindow::~FirstWindow()
{
    delete __engine;
    delete __model;
}
