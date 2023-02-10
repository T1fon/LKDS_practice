#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include <qqml.h>

#include <QObject>

class SecondWindow : public QObject
{
    Q_OBJECT
public:
    explicit SecondWindow(QObject *parent = nullptr);

signals:

};

#endif // SECONDWINDOW_H
