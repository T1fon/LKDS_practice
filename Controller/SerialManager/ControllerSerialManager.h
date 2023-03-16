#ifndef CONTROLLERSERIALMANAGER_H
#define CONTROLLERSERIALMANAGER_H

#include "../../Model/SerialManager/ModelSerialManager.h"
#include <QThread>
#include <QDebug>

#define DEVICE_DESCRIPTION "USB-SERIAL CH340"
#define DEVICE_MANUFACTURER "wch.cn"

class ControllerSerialManager : public QObject
{
    Q_OBJECT
   // QML_ADDED_IN_MINOR_VERSION(1)
private:
    bool __connection_succeful = false;
    QThread *__serial_thread = nullptr;
    ModelSerialManager *__m_serial_manager = nullptr;

    QString __searchDevice();
public:
    ControllerSerialManager(Settings settings, QString port_name = "");
    void write(QByteArray data);
    bool isConnection();

    ~ControllerSerialManager();
private slots:
    void __read(QString message);
signals:
    void readyRead(QString message);
};

#endif // CONTROLLERSERIALMANAGER_H
