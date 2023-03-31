#include "ModelSerialManager.h"
#include <QDebug>

ModelSerialManager::ModelSerialManager(Settings settings, QString port_name){
    setSettingsPort(settings);
    __serial_port = new QSerialPort(port_name);

    connect(__serial_port, SIGNAL(readyRead()), this, SLOT(readInPort()));
}

void ModelSerialManager::process(){
    open();
}
void ModelSerialManager::stop(){
    close();
}

void ModelSerialManager::readInPort(){
    QByteArray message = __serial_port->readAll();
    emit printDataPort(message);
}

void ModelSerialManager::setSettingsPort(Settings settings){
    __settings = settings;
}
bool ModelSerialManager::open(){
    __serial_port->setBaudRate(__settings.bound_rate);
    __serial_port->setDataBits(__settings.data_bits);
    __serial_port->setParity(__settings.parity);
    __serial_port->setStopBits(__settings.stop_bits);
    __serial_port->setFlowControl(__settings.flow_control);

    if(__serial_port->open(QIODevice::ReadWrite)){
        return true;
    }
    else{
        return false;
    }
}

void ModelSerialManager::close(){
    if(__serial_port->isOpen()){
        __serial_port->close();
        cout << "Connection closed" << endl;
    }
    //disconnect(__serial_port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    disconnect(__serial_port, SIGNAL(readyRead()), this, SLOT(readInPort()));
}
void ModelSerialManager::portWrite(QByteArray data){
    if(__serial_port->isOpen()){
        __serial_port->write(data);
    }
    else{
        qDebug() << "Open to error";
    }
}
void ModelSerialManager::__portRead(){
    QByteArray result;
    result = __serial_port->readAll();
    //qDebug() << result;
}
void ModelSerialManager::moveToThreadSerialPort(QThread *&thread){
    __serial_port->moveToThread(thread);
}

ModelSerialManager::~ModelSerialManager(){
    emit finished();
    delete __serial_port;
}
