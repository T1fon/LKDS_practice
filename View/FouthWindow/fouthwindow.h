#ifndef FOUTHWINDOW_H
#define FOUTHWINDOW_H

#include "../../Controller/SerialManager/ControllerSerialManager.h"
#include <qqml.h>

#define OPERATION_WRITE "1"
#define OPERATION_READ "2"
#define OPERATION_CHECK "3"
#define OPERATION_CLEAR "4"
#define OPERATION_SYMBOL "?"
#define DEFAULT_SAVE_PATH "./port_config.txt"

class Fouth_Window : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    Settings __settings;
    ControllerSerialManager *__controller_serial;
    QString __port_name = "";
    QString __searchByPortSettings(QString path_to_settings_file);
public:
    Fouth_Window();
    ~Fouth_Window();


public slots:
    void acceptMessage(QString message);
    void setPortName(QString port_name);

    void write(QString prefix_and_key, QString access_level);
    void read();
    void check();
    void clear();
signals:
    void returnMessage(QString message);
    void sendToQml(QString message);
};

#endif // FOUTHWINDOW_H
