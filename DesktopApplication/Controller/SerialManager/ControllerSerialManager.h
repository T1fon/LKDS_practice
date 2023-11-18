#ifndef CONTROLLERSERIALMANAGER_H
#define CONTROLLERSERIALMANAGER_H

#include "Model/SerialManager/ModelSerialManager.h"
//#include "../../Model/SerialManager/ModelSerialManager.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QSerialPortInfo>
#include <QDebug>
#include <QException>

#define DEFAULT_DEVICE_DESCRIPTION "USB-SERIAL CH340"
#define DEFAULT_DEVICE_MANUFACTURER "wch.cn"

class ControllerSerialManager : public QObject
{
    Q_OBJECT
private:
    static const uint8_t __calc_CRC_tab[256];

    static const uint8_t __PREFIX = 0x55;
    static const uint8_t __POSTFIX = 0xAA;

    bool __connection_succeful = false;
    QThread *__serial_thread = nullptr;
    ModelSerialManager *__m_serial_manager = nullptr;
    Settings __settings;
    bool __is_read_operation = false;
    QByteArray __buffer_message;

    QString __searchDevice();
    uint8_t __calcCRC (uint8_t *data, uint16_t len);
public:
    enum operation_t{
        OPERATION_WRITE = 1,
        OPERATION_READ,
        OPERATION_CHECK,
        OPERATION_CLEAR,
        OPERATION_GET_STATUS
    };

    static const uint8_t FIELD_LENGHT = 1;
    static const uint8_t FIELD_COMMAND = 2;
    static const uint8_t FIELD_ANSWER = 3;

    ControllerSerialManager(Settings settings, QString port_name = "");
    void write(operation_t operation, int prefix = -1, int key = -1, QString access_level="");
    bool isConnection();

    ~ControllerSerialManager();
private slots:
    void __read(QByteArray message);
public slots:
    bool startConnection(QString port_name);
signals:
    void readyRead(QByteArray message, int lenght, int command, int answer);
};
#endif // CONTROLLERSERIALMANAGER_H
