#include "thirdwindow.h"
#include "../Controller/controller_keytable.h"

ThirdWindow::ThirdWindow(QObject *parent)
    : QObject{parent}
{
    qmlRegisterType<Controller_KeyTable>("KeyTable",1,0, "Controller_KeyTable");
}
