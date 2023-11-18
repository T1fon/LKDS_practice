#include "ControllerSerialManager.h"


const uint8_t ControllerSerialManager::__calc_CRC_tab [256] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3};

ControllerSerialManager::ControllerSerialManager(Settings settings, QString port_name)
{
    QString temp_port_name = "";
    __buffer_message.clear();
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

        connect(__m_serial_manager, SIGNAL(printDataPort(QByteArray)), this, SLOT(__read(QByteArray)));

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
void ControllerSerialManager::write(operation_t operation, int prefix, int key, QString access_level){

    if(__connection_succeful){
        QByteArray data;
        uint8_t *temp_data = nullptr;

        if(operation ==  OPERATION_WRITE){
            temp_data = new uint8_t[0x11];
            temp_data[0] = __PREFIX;
            temp_data[FIELD_LENGHT] = 0x8;
            temp_data[FIELD_COMMAND] = OPERATION_WRITE;
            temp_data[FIELD_ANSWER] = 0x0;
            //data
            temp_data[FIELD_ANSWER+1] = access_level.toInt();
            temp_data[FIELD_ANSWER+2] = prefix;
            temp_data[FIELD_ANSWER+3] = key & 0b11111111;
            temp_data[FIELD_ANSWER+4] = (key >> 8) & 0b11111111;

            temp_data[FIELD_ANSWER+5] = __calcCRC(temp_data+1, temp_data[FIELD_LENGHT]-1);
            temp_data[FIELD_ANSWER+6] = __POSTFIX;
        }
        else{
            temp_data = new uint8_t[0x9];
            temp_data[0] = __PREFIX;
            temp_data[FIELD_LENGHT] = 0x4;
            temp_data[FIELD_COMMAND] = operation;
            temp_data[FIELD_ANSWER] = 0x0;
            temp_data[FIELD_ANSWER+1] = __calcCRC(temp_data+1,temp_data[FIELD_LENGHT]-1);
            temp_data[FIELD_ANSWER+2] = __POSTFIX;
            temp_data[FIELD_ANSWER+3] = 0b0;
            temp_data[FIELD_ANSWER+4] = 0b0;
        }

        data.append((char*)temp_data,temp_data[FIELD_LENGHT]+4);
        for(auto i = data.begin(); i != data.end(); i++){
            qDebug() << (int)(uint8_t)*i;
        }

        __m_serial_manager->portWrite(data);
        delete[] temp_data;
    }
}
void ControllerSerialManager::__read(QByteArray message){
    bool correct_message = true;
    int lenght,command,answer;
    size_t pos_pre_postfix;

    do{

        if(__buffer_message.size() == 0){
            pos_pre_postfix = message.indexOf(__PREFIX);
            if(pos_pre_postfix != -1){
                __buffer_message = message.remove(0, pos_pre_postfix);
            }
            else{
                qDebug() << "Prefix not found";
                return;
            }
        }
        pos_pre_postfix = __buffer_message.indexOf(__POSTFIX);
        if(pos_pre_postfix == -1){
            pos_pre_postfix = message.indexOf(__POSTFIX);
            if(pos_pre_postfix == -1){
                __buffer_message += message;
                qDebug() << "Postfix not found";
                return;
            }
            __buffer_message += QByteArray(message).remove(pos_pre_postfix+1, message.size());

        }
        message.remove(0,pos_pre_postfix+1);

        try{
            lenght = __buffer_message.at(FIELD_LENGHT);
            command = __buffer_message.at(FIELD_COMMAND);
            if(__buffer_message.size() < lenght){
                throw invalid_argument((QString("__buffer_message.size() < lenght: ") +QString().setNum(__buffer_message.size()) + " " + QString().setNum(lenght)).toStdString());
            }
            //message = "";
            answer = __buffer_message.at(FIELD_ANSWER);
            if((uint8_t)__buffer_message.at(lenght) != __calcCRC((uint8_t*)__buffer_message.data()+1,lenght-1)){

                correct_message = false;
            }
        }catch(exception &e){
            qDebug() << "Ошибка приёма сообщения с COM порта" << e.what();
            for(auto i = __buffer_message.begin(); i != __buffer_message.end(); i++){
                qDebug() << (int)(uint8_t)*i;
            }
            __buffer_message.clear();
            return;
        }

        if(!correct_message){
            qDebug() << "Ошибка приёма сообщения с COM порта, crc не совпадают";
            qDebug() << (int)(uint8_t)__buffer_message.at(lenght) << " " << (int)__calcCRC((uint8_t*)__buffer_message.data()+1,lenght-1) << " " <<__calcCRC((uint8_t*)__buffer_message.data()+1,lenght-1);
            __buffer_message.clear();
            return;
        }

        emit readyRead(__buffer_message, lenght,command,answer);
        __buffer_message.clear();
    }while(1);
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


uint8_t ControllerSerialManager::__calcCRC (uint8_t *data, uint16_t len)
{
  uint8_t crc=0;
  while (len--){
      crc = __calc_CRC_tab[crc ^ *data++];
  }

  return crc;
}

