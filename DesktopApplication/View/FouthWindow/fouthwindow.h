#ifndef FOUTHWINDOW_H
#define FOUTHWINDOW_H

#include "../../Controller/SerialManager/ControllerSerialManager.h"
#include "../../Controller/controller_keytable.h"
#include <qqml.h>

#define OPERATION_WRITE "1"
#define OPERATION_READ "2"
#define OPERATION_CHECK "3"
#define OPERATION_CLEAR "4"
#define OPERATION_SYMBOL "?"
#define ID_DEVELOPER 3
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
    bool __is_read_operation = false;
    bool __succeful_write_operation = false;
    int __COUNT_LOG_MESSAGE = 8;
    int __time = 0;

    int __current_key, __prefix, __count_key, __current_count_key;
    QList<int> __access_history;
    bool __overwriting = false;

public:
    Fouth_Window();
    ~Fouth_Window();


public slots:
    void acceptMessage(QString message);
    void setPortName(QString port_name);
    bool setKeyParametr(QString prefix, QString start_key, QString count_key, bool overwriting);
    QString getKeyParametr();
    int getCurrentKey();
    int getPrefix();

    void write(int prefix, int key, QString access_level);
    void read();
    void check();
    void clear();
    void slotClearLog();
    void backStep(Controller_KeyTable *key_table);
    void endWork();
signals:
    void returnMessage(QString message);
    void sendToQml(QString message);
    void signalClearLog();
    void succefulWrite(bool access_develoer, int last_access_key, bool back_step = false);
};

#endif // FOUTHWINDOW_H
