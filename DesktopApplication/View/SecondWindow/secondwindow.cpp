#include "secondwindow.h"
#include "../../Controller/controller_databasemanager.h"

Second_Window::Second_Window(QObject *parent)
    : QObject{parent}
{
    qmlRegisterType<Controller_DatabaseManager>("DatabaseManager", 1, 0, "Controller_DatabaseManager");
    qmlRegisterType<Second_Window>("SecWin", 1, 0, "Second_Window");
}

Second_Window::~Second_Window()
{

}
