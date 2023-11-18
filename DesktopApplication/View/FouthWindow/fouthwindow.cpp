#include "fouthwindow.h"

const QMap<Fouth_Window::__access_level_t, QString> Fouth_Window::__access_level_name = {{__LEVEL_ENGINEER, "Engineer"},
                                                                     {__LEVEL_OPERATOR, "Operator"},
                                                                     {__LEVEL_ADMINISTRATOR, "Administrator"},
                                                                     {__LEVEL_DEVELOPER, "Developer"}};
const QMap<Fouth_Window::__access_level_t, QString> Fouth_Window::__access_level_color = {{__LEVEL_ENGINEER, "\"red\""},
                                                          {__LEVEL_OPERATOR, "\"green\""},
                                                          {__LEVEL_ADMINISTRATOR, "\"blue\""},
                                                          {__LEVEL_DEVELOPER, "\"#FAFF00\""}};

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

    connect(__controller_serial, SIGNAL(readyRead(QByteArray, int, int, int)), this, SLOT(acceptMessage(QByteArray,int,int,int)));
}
bool Fouth_Window::setKeyParametr(QString prefix, QString start_key, QString count_key, bool overwriting){
    if(prefix == "" || start_key == "" || count_key == ""){
        return false;
    }
    __current_key = start_key.toInt()+1;
    //qDebug() << __current_key << " " << start_key;
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
        __ptr_key_table = key_table;
        __back_step_process = true;
        this->clear();
    }
}
void Fouth_Window::write(int prefix, int key, QString access_level){
    if(__current_count_key <= 0){
        return;
    }

    __controller_serial->write(ControllerSerialManager::OPERATION_WRITE,prefix,key,access_level);
    __access_history.push_back(access_level.toInt());
    __time++;
    qDebug() << "Write";
}
void Fouth_Window::read(){
    __controller_serial->write(ControllerSerialManager::OPERATION_READ);
    __time++;
    qDebug() << "Read";
}
void Fouth_Window::check(){
    __controller_serial->write(ControllerSerialManager::OPERATION_CHECK);
    __time++;
    qDebug() << "Check";
}
void Fouth_Window::clear(){
    __controller_serial->write(ControllerSerialManager::OPERATION_CLEAR);
    __time++;
    qDebug() << "Clear";
}
void Fouth_Window::acceptMessage(QByteArray message, int lenght, int command, int answer)
{
    static QString temp_m = "<div>";
    static QString prev_temp_m = "";


    switch(command){
        case ControllerSerialManager::OPERATION_WRITE:
            if(answer == __STATUS_SUCCESS){
                temp_m += "<p>Operation write: Successful</p>";

                if(__access_history.back() == __LEVEL_DEVELOPER){
                    emit succefulWrite(true, __access_history.back(), false);
                }
                else{
                    __current_key++;
                    __current_count_key--;
                    emit succefulWrite(false, __access_history.back(), false);
                }
            }
            else{
                temp_m += "<p>Operation write: ACCESS DENIED!!!</p>";
            }
            break;
        case ControllerSerialManager::OPERATION_READ:
            if(answer == __STATUS_SUCCESS){
                temp_m += "<p>Result read:</p>";
                temp_m += QString("<p><font color=") + __access_level_color[(__access_level_t)message[ControllerSerialManager::FIELD_ANSWER+1]] + ">";
                temp_m += "Prefix: " + QString("").setNum((uint8_t)message[ControllerSerialManager::FIELD_ANSWER+2]) + " | ";
                temp_m += "Key: " + QString("").setNum( ((int)((uint8_t)message[ControllerSerialManager::FIELD_ANSWER+4]) << 8) |
                                                         (uint8_t)message[ControllerSerialManager::FIELD_ANSWER+3]) + " | ";
                temp_m += QString("Access mode: ") + __access_level_name[(__access_level_t)message[ControllerSerialManager::FIELD_ANSWER+1]];
                temp_m += "</font></p>";
            }
            else{
                temp_m += "<p>Operation read: ACCESS DENIED!!!</p>";
            }
            break;
        case ControllerSerialManager::OPERATION_CHECK:
            if(answer == 0x1){
                temp_m += "<p>Operation check: Successful</p>";
            }
            else{
                temp_m += "<p>Operation check: ACCESS DENIED!!!</p>";
            }
            break;
        case ControllerSerialManager::OPERATION_CLEAR:
            if(answer == __STATUS_SUCCESS){
                temp_m += "<p>Operation clear: Successful</p>";

                if(__back_step_process){
                    __back_step_process = false;
                    __current_key--;
                    __current_count_key++;
                    __ptr_key_table->deleteKey(QString().setNum(__current_key), QString().setNum(__prefix));

                    for(;__access_history.back() == __LEVEL_DEVELOPER; ){
                        qDebug() << __access_history.back();
                        emit succefulWrite(__access_history.back(), __access_history.back(), true);
                        __access_history.pop_back();
                    }
                    emit succefulWrite(__access_history.back(), __access_history.back(), true);
                    qDebug() << __access_history.back();
                    __access_history.pop_back();
                }
            }
            else{
                temp_m += "<p>Operation clear: fail</p>";
            }
            break;
        case ControllerSerialManager::OPERATION_GET_STATUS:
            if(answer == __STATUS_SUCCESS || answer == __STATUS_REQUEST){
                if(message[ControllerSerialManager::FIELD_ANSWER+4] & 0b10){
                    temp_m += "<p>Button PRESSED</p>";
                    emit pressButtomOnUZK();
                }
            }

            break;
    }
    if(answer != __STATUS_SUCCESS && answer != __STATUS_REQUEST){
        qDebug() << "ANSWER = " << (uint8_t)answer;
        switch ((uint8_t)answer) {
        case __STATUS_KEY_NOT_FOUND:
            emit createErrorDialog("УЗК","Отсутствует сервисный ключ");
            break;
        case __STATUS_ERROR_WRITE:
            emit createErrorDialog("УЗК","Ошибка записи / \nНевозможно записать сервисный ключ");
            break;
        case __STATUS_PACKAGE_ERROR:
            emit createErrorDialog("УЗК","Неверное содержимое пакета запроса");
            break;
        default:
            emit createErrorDialog("УЗК","Неизвестная ошибка возникла на УЗК");
            break;
        }
    }
    temp_m += "</div>";

    prev_temp_m += temp_m;
    if(__time == __COUNT_LOG_MESSAGE){
        emit signalClearLog();
        temp_m = prev_temp_m;
        prev_temp_m = "";
        __time = 0;
    }

    emit sendToQml(temp_m);

    temp_m = "<div>";


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
