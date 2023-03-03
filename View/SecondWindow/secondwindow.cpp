#include "secondwindow.h"
#include "../../Controller/controller_databasemanager.h"

SecondWindow::SecondWindow(QObject *parent)
    : QObject{parent}
{
    qmlRegisterType<Controller_DatabaseManager>("DatabaseManager", 0, 1, "Controller_DatabaseManager");
}
