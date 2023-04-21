#include "SettingsWindow.h"

SettingsWindow::SettingsWindow()
{
    __com_info = new QList<QSerialPortInfo>;
}
QList<QString> SettingsWindow::getComPorts(){
    *__com_info = QSerialPortInfo::availablePorts();

    qDebug() << "Click\n";

    QList<QString> ports_name;
    for(int i = 0; i < __com_info->size(); i++){
        ports_name.push_back(__com_info->at(i).portName());
    }
    return ports_name;
}

SettingsWindow::~SettingsWindow()
{
    if(__com_info != nullptr){
        delete __com_info;
    }
}

