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
bool Fouth_Window::setKeyParametr(QString prefix, QString start_key, QString count_key, bool overwriting){
    if(prefix == "" || start_key == "" || count_key == ""){
        return false;
    }
    __current_key = start_key.toInt()+1;
    __prefix = prefix.toInt();
    __count_key = count_key.toInt();
    __current_count_key = __count_key;
    __overwriting = overwriting;
    return true;
}
QString Fouth_Window::getKeyParametr(){
   // qDebug() << "count_key = " << __count_key;
    return "Префикс: " + QString().setNum(__prefix) + " | "
            + "Ключ: " + QString().setNum(__current_key) + " | "
            + "Осталось ключей: " + QString().setNum(__current_count_key);
}
int Fouth_Window::getCurrentKey(){
    return __current_key;
}
int Fouth_Window::getPrefix(){
    return __prefix;
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
void Fouth_Window::backStep(Controller_KeyTable *key_table){
    if(__current_count_key < __count_key && __count_key != 0){
        __current_key--;
        __current_count_key++;
        key_table->deleteKey(QString().setNum(__current_key), QString().setNum(__prefix));
        this->clear();

        for(;__access_history.back() == ID_DEVELOPER; ){
            qDebug() << __access_history.back();
            emit succefulWrite(__access_history.back(), __access_history.back(), true);
            __access_history.pop_back();
        }
        emit succefulWrite(__access_history.back(), __access_history.back(), true);
        qDebug() << __access_history.back();
        __access_history.pop_back();
    }
}
void Fouth_Window::write(int prefix, int key, QString access_level){
    __is_read_operation = false;
    if(__current_count_key <= 0){
        return;
    }
    QString message = OPERATION_WRITE +
                      QString().setNum(prefix) + OPERATION_SYMBOL +
                      QString().setNum(key) + OPERATION_SYMBOL +
                      access_level + OPERATION_SYMBOL;
    __controller_serial->write(message.toLatin1());
    __access_history.push_back(access_level.toInt());
    __time++;
    qDebug() << "Write";
}
void Fouth_Window::read(){
    __controller_serial->write(OPERATION_READ);
    __time++;
    __is_read_operation = true;
    qDebug() << "Read";
}
void Fouth_Window::check(){
    __controller_serial->write(OPERATION_CHECK);
    __time++;
    __is_read_operation = false;
    qDebug() << "Check";
}
void Fouth_Window::clear(){
    __controller_serial->write(OPERATION_CLEAR);
    __time++;
    __is_read_operation = false;
    qDebug() << "Clear";
}
void Fouth_Window::acceptMessage(QString message){

   // qDebug() << message;
    static QString temp_m = "<div>";
    static QString prev_temp_m = "";
    QString color = "";

    int color_position = 0;

    if(__is_read_operation){
        color_position = temp_m.indexOf("Access_mode");
        //qDebug() << temp_m << " " << color_position;
        if(temp_m.indexOf("Engineer") != -1){
            color = "\"red\"";
            //qDebug() << "color = " << color << " pos = " << temp_m.indexOf("Engineer");
            temp_m.insert(color_position,"<font color=" + color + ">");
        }
        else if(temp_m.indexOf("Operator") != -1){
            color = "\"green\"";
            //qDebug() << "color = " << color << " pos = " << temp_m.indexOf("Operator");
            temp_m.insert(color_position,"<font color=" + color + ">");
        }
        else if(temp_m.indexOf("Administrator") != -1){
            color = "\"blue\"";
            //qDebug() << "color = " << color << " pos = " << temp_m.indexOf("Administrator");
            temp_m.insert(color_position,"<font color=" + color + ">");
        }
        else if(temp_m.indexOf("Developer") != -1){
            color = "\"#FAFF00\"";
            //qDebug() << "color = " << color << " pos = " << temp_m.indexOf("Developer");
            temp_m.insert(color_position,"<font color=" + color + ">");
        }
    }

    for(int i = 0; i < message.size(); i++){
        if(message.at(i) == '\n'){
            //qDebug() << "\\n = " << i;
            if(__is_read_operation){
                temp_m += "</font>";
            }
            temp_m += "</div>";
            prev_temp_m += temp_m;
            prev_temp_m += "<div>";
            __succeful_write_operation = (temp_m.indexOf("write: Succeful", 0) != -1) ? true : false;
            if(__succeful_write_operation){
                if(__current_count_key > 0){

                    __succeful_write_operation = false;
                    if(__access_history.back() == ID_DEVELOPER){
                        emit succefulWrite(true, __access_history.back(), false);
                    }
                    else{
                        __current_key++;
                        __current_count_key--;
                        emit succefulWrite(false, __access_history.back(), false);
                    }
                }

            }


            if(__time == __COUNT_LOG_MESSAGE){
                emit signalClearLog();
                temp_m = prev_temp_m;
                prev_temp_m = "";
                __time = 0;
            }


            //qDebug() << "Write: " << __succeful_write_operation;
            emit sendToQml(temp_m);

            temp_m = "<div>";
        }
        else{

            temp_m += message.at(i);
        }
    }
}
void Fouth_Window::endWork(){
    __access_history.clear();
}
void Fouth_Window::slotClearLog(){
    emit signalClearLog();
}
Fouth_Window::~Fouth_Window(){
    disconnect(__controller_serial, SIGNAL(readyRead(QString)), this, SLOT(acceptMessage(QString)));
    delete __controller_serial;
}
