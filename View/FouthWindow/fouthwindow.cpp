#include "fouthwindow.h"

Fouth_Window::Fouth_Window()
{
    __settings.bound_rate = QSerialPort::Baud9600;
    __settings.data_bits = QSerialPort::Data8;
    __settings.parity = QSerialPort::NoParity;
    __settings.direction = QSerialPort::AllDirections;
    __settings.flow_control = QSerialPort::NoFlowControl;
    __settings.stop_bits = QSerialPort::OneStop;

    __controller_serial = new ControllerSerialManager(__settings);

    connect(__controller_serial, SIGNAL(readyRead(QString)), this, SLOT(acceptMessage(QString)));
}
void Fouth_Window::write(QString prefix_and_key, QString access_level){
    QString message = OPERATION_WRITE + prefix_and_key + access_level + OPERATION_SYMBOL;
    __controller_serial->write(message.toLatin1());
    qDebug() << "Write";
}
void Fouth_Window::read(){
    __controller_serial->write(OPERATION_READ);
    qDebug() << "Read";
}
void Fouth_Window::check(){
    __controller_serial->write(OPERATION_CHECK);
    qDebug() << "Check";
}
void Fouth_Window::clear(){
    __controller_serial->write(OPERATION_CLEAR);
    qDebug() << "Clear";
}
void Fouth_Window::acceptMessage(QString message){
    qDebug() << message;
    emit sendToQml(message);
    //return message;
}
Fouth_Window::~Fouth_Window(){
    disconnect(__controller_serial, SIGNAL(readyRead(QString)), this, SLOT(acceptMessage(QString)));
    delete __controller_serial;
}
