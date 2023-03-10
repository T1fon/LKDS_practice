#include "ControllerSerialManager.h"

ControllerSerialManager::ControllerSerialManager(Settings settings, QString port_name)
{
    QString temp_port_name = "";
    if(port_name == ""){
        temp_port_name = __searchDevice();
    }
    else{
        temp_port_name = port_name;
    }

    if(temp_port_name == ""){
        throw invalid_argument("Port name not found");
    }

    __m_serial_manager = new ModelSerialManager(settings,temp_port_name);
    __serial_thread = new QThread(this);

    __m_serial_manager->moveToThread(__serial_thread);
    __m_serial_manager->moveToThreadSerialPort(__serial_thread);

    connect(__serial_thread, SIGNAL(started()), __m_serial_manager, SLOT(process()));
    connect(__m_serial_manager, SIGNAL(finished()), __serial_thread, SLOT(quit()));
    connect(__serial_thread, SIGNAL(finished()), __serial_thread, SLOT(quit()));
    connect( __m_serial_manager, SIGNAL(finished()),__m_serial_manager, SLOT(deleteLater()));
    connect( __serial_thread, SIGNAL(finished()),__serial_thread, SLOT(deleteLater()));

    connect(__m_serial_manager, SIGNAL(printDataPort(QString)), this, SLOT(__read(QString)));

    __serial_thread->start();
}
QString ControllerSerialManager::__searchDevice(){
    QList<QSerialPortInfo> a = QSerialPortInfo::availablePorts();
    for(int i = 0; i < a.size(); i++){
        if(a.at(i).description() == DEVICE_DESCRIPTION && a.at(i).manufacturer() == DEVICE_MANUFACTURER){
            return a.at(i).portName();
        }
    }
    return "";
}
void ControllerSerialManager::write(QByteArray data){
    __m_serial_manager->portWrite(data);
}
void ControllerSerialManager::__read(QString message){
    emit readyRead(message);
}
ControllerSerialManager::~ControllerSerialManager(){
    disconnect(__serial_thread, SIGNAL(started()), __m_serial_manager, SLOT(process()));
    disconnect(__m_serial_manager, SIGNAL(finished()), __serial_thread, SLOT(quit()));
    disconnect(__serial_thread, SIGNAL(finished()), __serial_thread, SLOT(quit()));
    disconnect( __m_serial_manager, SIGNAL(finished()),__m_serial_manager, SLOT(deleteLater()));
    disconnect( __serial_thread, SIGNAL(finished()),__serial_thread, SLOT(deleteLater()));

    disconnect(__m_serial_manager, SIGNAL(printDataPort(QString)), this, SLOT(__read(QString)));

    delete __m_serial_manager;
    delete __serial_thread;
}
