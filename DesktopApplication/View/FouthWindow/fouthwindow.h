#ifndef FOUTHWINDOW_H
#define FOUTHWINDOW_H

#include "../../Controller/SerialManager/ControllerSerialManager.h"
#include "../../Controller/controller_keytable.h"
#include <qqml.h>


#define OPERATION_SYMBOL "?"
//#define ID_DEVELOPER 3
#define DEFAULT_SAVE_PATH "./port_config.txt"

class Fouth_Window : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:

    enum __access_level_t{
        __LEVEL_ENGINEER = 0,
        __LEVEL_OPERATOR,
        __LEVEL_ADMINISTRATOR,
        __LEVEL_DEVELOPER
    };
    enum __answer_status_t{
        __STATUS_REQUEST = 0x0,
        __STATUS_SUCCESS = 0x1,
        __STATUS_KEY_NOT_FOUND = 0x81,
        __STATUS_ERROR_WRITE = 0x82,
        __STATUS_PACKAGE_ERROR = 0x83
    };

    static const QMap<__access_level_t, QString> __access_level_name;
    static const QMap<__access_level_t, QString> __access_level_color;

    Settings __settings;
    ControllerSerialManager *__controller_serial;
    QString __port_name = "";
    QString __searchByPortSettings(QString path_to_settings_file);
    const int __COUNT_LOG_MESSAGE = 8;
    int __time = 0;
    int __current_key, __prefix, __count_key, __current_count_key;
    QList<int> __access_history;
    bool __overwriting = false;
    bool __back_step_process = false;
    Controller_KeyTable *__ptr_key_table = nullptr;

public:
    Fouth_Window();
    ~Fouth_Window();


public slots:
    void acceptMessage(QByteArray message, int lenght, int command, int answer);
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
    void pressButtomOnUZK();
    void createErrorDialog(QString title, QString message);
};
#endif // FOUTHWINDOW_H
