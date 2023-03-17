#include "fouthwindow.h"

Fouth_Window::Fouth_Window()
{
    __settings.bound_rate = QSerialPort::Baud9600;
    __settings.data_bits = QSerialPort::Data8;
    __settings.parity = QSerialPort::NoParity;
    __settings.direction = QSerialPort::AllDirections;
    __settings.flow_control = QSerialPort::NoFlowControl;
    __settings.stop_bits = QSerialPort::OneStop;
    __port_name = __searchByPortSettings(DEFAULT_SAVE_PATH);
    __controller_serial = new ControllerSerialManager(__settings, __port_name);

    connect(__controller_serial, SIGNAL(readyRead(QString)), this, SLOT(acceptMessage(QString)));
}
QString Fouth_Window::__searchByPortSettings(QString path_to_settings_file){
    qDebug() << "Пробуем открыть файл";
    QFile file(path_to_settings_file);
    file.open(QFile::ReadOnly);
    if(!file.isOpen()){
        qDebug() << "Файл не открыт";
        return "";
    }

    QString device_name, manufacturer_name, temp;
    int device_id, manufacturer_id;
    QTextStream fin(&file);

    fin >> temp >> device_name;
    fin >> temp >> device_id;
    fin >> temp >> manufacturer_name;
    fin >> temp >> manufacturer_id;
    device_name.replace('_',' ');
    manufacturer_name.replace('_',' ');

    QList<QSerialPortInfo> port_info = QSerialPortInfo::availablePorts();
    for(int i = 0; i < port_info.size(); i++){
        if(port_info.at(i).description() == device_name &&
           port_info.at(i).productIdentifier() == device_id &&
           port_info.at(i).manufacturer() == manufacturer_name &&
           port_info.at(i).vendorIdentifier() == manufacturer_id){
            qDebug() << "Нашли";
            return port_info.at(i).portName();
        }
    }
    qDebug() << "Не нашли";
    qDebug() << device_name;
    qDebug() << device_id;
    qDebug() << manufacturer_name;
    qDebug() << manufacturer_id;
    return "";
}
void Fouth_Window::setPortName(QString port_name){
    __port_name = port_name;
    __controller_serial->startConnection(__port_name);
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
