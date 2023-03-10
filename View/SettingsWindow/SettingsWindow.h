#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QObject>
#include <qqml.h>
#include <QSerialPortInfo>
#include <QDebug>

class SettingsWindow : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    QList<QSerialPortInfo> *__com_info = nullptr;
public:
    SettingsWindow();
    ~SettingsWindow();

public slots:
    QList<QString> getComPorts();
};

#endif // SETTINGSWINDOW_H
