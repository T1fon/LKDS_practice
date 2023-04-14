#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H


#include <QObject>
#include <QString>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QStringList>
#include <QAbstractTableModel>


class Second_Window : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:
     explicit Second_Window(QObject *parent = nullptr);
    ~Second_Window();

private:

};


#endif // SECONDWINDOW_H
