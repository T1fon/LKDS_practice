#include "ControllerSerialManager.h"

ControllerSerialManager::ControllerSerialManager(Settings settings, QString port_name)
{
    QString temp_port_name = "";
    __settings = settings;
    if(port_name == ""){
        temp_port_name = __searchDevice();
    }
    else{
        temp_port_name = port_name;
    }

    startConnection(temp_port_name);
}

bool ControllerSerialManager::startConnection(QString port_name){
    qDebug() << port_name;
    if(port_name == ""){
        __connection_succeful = false;
    }
    else{
        __connection_succeful = true;

        if(__m_serial_manager != nullptr){
            delete __m_serial_manager;
            delete __serial_thread;
        }
        __m_serial_manager = new ModelSerialManager(__settings,port_name);
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

    return __connection_succeful;
}
QString ControllerSerialManager::__searchDevice(){
    QList<QSerialPortInfo> a = QSerialPortInfo::availablePorts();
    for(int i = 0; i < a.size(); i++){
        if(a.at(i).description() == DEFAULT_DEVICE_DESCRIPTION && a.at(i).manufacturer() == DEFAULT_DEVICE_MANUFACTURER){
            return a.at(i).portName();
        }
    }
    return "";
}
bool ControllerSerialManager::isConnection(){
    return __connection_succeful;
}
void ControllerSerialManager::write(QByteArray data){

    if(__connection_succeful){
        //OPERATION_READ
        /*if(data == "2"){
            __is_read_operation = true;
        }
        else{
            __is_read_operation = false;
        }*/
        __m_serial_manager->portWrite(data);
    }
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
