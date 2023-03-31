#ifndef CONTROLLERSERIALMANAGER_H
#define CONTROLLERSERIALMANAGER_H

#include "../../Model/SerialManager/ModelSerialManager.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QSerialPortInfo>
#include <QDebug>

#define DEFAULT_DEVICE_DESCRIPTION "USB-SERIAL CH340"
#define DEFAULT_DEVICE_MANUFACTURER "wch.cn"

class ControllerSerialManager : public QObject
{
    Q_OBJECT
private:
    bool __connection_succeful = false;
    QThread *__serial_thread = nullptr;
    ModelSerialManager *__m_serial_manager = nullptr;
    Settings __settings;
    bool __is_read_operation = false;
    QString __searchDevice();
public:
    ControllerSerialManager(Settings settings, QString port_name = "");
    void write(QByteArray data);
    bool isConnection();

    ~ControllerSerialManager();
private slots:
    void __read(QString message);
public slots:
    bool startConnection(QString port_name);
signals:
    void readyRead(QString message);
    void signalClear();
};

#endif // CONTROLLERSERIALMANAGER_H
