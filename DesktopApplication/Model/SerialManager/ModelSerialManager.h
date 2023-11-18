#ifndef MODELSERIALWORKER_H
#define MODELSERIALWORKER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>
#include <QThread>


using namespace std;

typedef struct Settings{
    int bound_rate;
    QSerialPort::DataBits data_bits;
    QSerialPort::Direction direction;
    QSerialPort::FlowControl flow_control;
    QSerialPort::Parity parity;
    QSerialPort::PinoutSignal pinout_signal;
    QSerialPort::StopBits stop_bits;
} Settings;

class ModelSerialManager : public QObject
{
   Q_OBJECT
private:

    Settings __settings;
    QSerialPort *__serial_port = nullptr;
    QSerialPortInfo *__serial_port_info = nullptr;

//private slots:
  // void __portRead();
public:
    ModelSerialManager(Settings settings, QString port_name);

    void portWrite(QByteArray data);
    void moveToThreadSerialPort(QThread *&thread);
    void writeToPort(QByteArray data);
    bool open();
    void close();

    ~ModelSerialManager();
public slots:
    void process();
    void stop();
    void setSettingsPort(Settings settings);
    void readInPort();
signals:
    void finished();
    void errorPort(QString error);
    void printDataPort(QByteArray message);
};

#endif // MODELSERIALWORKER_H
