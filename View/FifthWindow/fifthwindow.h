#ifndef FIFTHWINDOW_H
#define FIFTHWINDOW_H

#include <QObject>
#include <qqml.h>
#include <QDebug>
#include <QString>
#include <QList>

#define FIRST_TABLE 0
#define SECOND_TABLE 1
#define THIRD_TABLE 3

class FifthWindow : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    FifthWindow();
    ~FifthWindow();

public slots:
    QList<QString> getColumnName(int value);
    QList<QString> getTableName();
};

#endif // FIFTHWINDOW_H
