#ifndef CONTROLLER_KEYTABLE_H
#define CONTROLLER_KEYTABLE_H
#define PAGE_THIRD_WINDOW 2
#include <QObject>
#include <QObject>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QStringList>
#include <QAbstractTableModel>
#include "../Model/model_database.h"
#include <QMap>
#include <QVector>
#include "Controller/controller_databasemanager.h"
#include <QDate>

struct TableDisplayServiceKey
{
    QString IdNum;
    QString KodCust = "&";
    QString KodReg = "&";
    QString Date = "&";
    QString NumKey = "&";

};

class Controller_KeyTable : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)
    enum {
            ColumnIdNum = 0,
            ColumnKodCust,
            ColumnReg,
            ColumnDate,
            ColumnNumKey,
            CountofColumnsService
        };
public:
    Controller_KeyTable(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override ;
    int numKeyFofReg(QString __kodReg);

    QHash<int, QByteArray> roleNames() const override;

    //Qt::ItemFlags flags(const QModelIndex &index) const;
    /*bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override ;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())override;*/

    ~Controller_KeyTable();

public slots:
    void updateModel();
    void recieveRegion(QString codcust, QString city, QString reg);
    void addKey(QString numKey);
    QString printData();
    QString addCodCust();
    int getKey();
    QString getReg();

private:
    Model_database * __dispetcher;
    QStringList __columnNames;
    QSqlQuery *__q;
    QVector<TableDisplayServiceKey> *__serviceNames;
    int __rows = 0;
    int __page = PAGE_THIRD_WINDOW;
    QString __query;
    QString __codCust;
    TableDisplayServiceKey *__keyTable;
    int __rowsID = 0;
    int __numKey = 0;
    int __num = 0;
    QString __city = "";
    QString __kodReg = "";

signals:
};

#endif // CONTROLLER_KEYTABLE_H
