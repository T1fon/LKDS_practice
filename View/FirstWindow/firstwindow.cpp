#include "firstwindow.h"
//#include "../Controller/controller_databasemanager.h"
//#include "../Model/model_database.h"
#include "../Controller/controller_keytable.h"
#include "../SecondWindow/secondwindow.h"
#include "../../Controller/controller_databasemanager.h"
#include "../../Model/model_database.h"



FirstWindow::FirstWindow(QObject *parent)
    : QObject{parent}
{
    //DataBase = new Model_database(this);
    //DataBase->connectToDataBase();
    //__model = new Controller_DatabaseManager;
    __engine = new QQmlApplicationEngine;
    qmlRegisterType<Controller_DatabaseManager>("DatabaseManager", 1, 0, "Controller_DatabaseManager");
    qmlRegisterType<Controller_KeyTable>("KeyTable",1,0, "Controller_KeyTable");
    qmlRegisterType<Second_Window>("SecWin", 1, 0, "Second_Window");
    const QUrl url(u"qrc:/View/FirstWindow/FirstWindow.qml"_qs);

   // __engine->rootContext()->setContextProperty("DataBase", &DataBase);
   // __engine->rootContext()->setContextProperty("TableModel", __model);
    Controller_DatabaseManager c_DB;
    //__write_key_window = new FouthWindow(parent);

    //__model = new Controller_DatabaseManager;
    __engine = new QQmlApplicationEngine;
    //__engine->rootContext()->setContextProperty("bd", &c_DB);
   // __engine->rootContext()->setContextProperty("wkw", __write_key_window);
    const QUrl url(u"qrc:/View/FirstWindow/FirstWindow.qml"_qs);

    qmlRegisterType<Controller_DatabaseManager>("DatabaseManager", 0, 1, "Controller_DatabaseManager");
    qmlRegisterType<Fouth_Window>("WindowWriteKey", 1, 0, "Fouth_Window");
    qmlRegisterType<COMPortModel>("COMPortModel", 1, 0, "COM_Port_Model");
    qDebug() << 11;
    __engine->load(url);

}

FirstWindow::~FirstWindow()
{
    //delete __write_key_window;
    delete __engine;
    delete __model;
}
