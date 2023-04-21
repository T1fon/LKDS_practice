#ifndef CONTROLLER_DATABASEMANAGER_H
#define CONTROLLER_DATABASEMANAGER_H
#define PAGE_SECOND_WINDOW 1
#define PAGE_THIRD_WINDOW 2

#include <QObject>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QStringList>
#include <QAbstractTableModel>
#include "../Model/model_database.h"
#include <QMap>
#include <QVector>
#include <QSqlDatabase>
#include "controller_keytable.h"

#define DATABASE_NAME "LKDS_Base.db"
#define DATABASE_WAY "DataBase/LKDS_Base.db"

struct TableDisplay
{
    QString CodCust;
    QString NameCust = "&";
    QString Inn = "&";
    QString KodReg = "&";
    QString NameSity = "&";
};

class Controller_DatabaseManager : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:

    enum {
            ColumnCodCust = 0,
            ColumnNameCust,
            ColumnINN,
            CountKodReg,
            ColumnNameSity,
            CountofColumnsCustom
        };



    Controller_DatabaseManager(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    void header(int page);

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override ;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())override;

    QHash<int, QByteArray> roleNames() const override;
    ~Controller_DatabaseManager();


signals:


public slots:
    void updateModel();
    void recieveData(QString cust,QString inn,QString reg,QString city, bool flag);
    void searchCompany(QString seachplace);
    void refreshTable();
    void chooseRegion(int row);
    QString checkCodCust();
    QString checkCity();
    QString checkReg();
    void setReg(QString value);
    QString checkReg1();
    QString checkInn();
    QString checkName();
    QString lastKey();
    void redactProfile(int row);

private:
    QStringList __columnNames;
    QSqlQuery *__q;
    Model_database * __dispetcher;
    QVector<TableDisplay> *__rowNames;
    int __rows = 0;
    int __page = PAGE_SECOND_WINDOW;
    QString __query;
    int __rows_to_add = 0;
    int __row;
    QString __companyCodCust = "";
    QString __companyCity = "";
    QString __companyReg = "";
    QString __companyReg1 = "";
    QString __companyInn = "";
    QString __companyName = "";
    QString __keyDate = "";
    QString __keyNum = "";

    TableDisplay *bufbuf = nullptr;
};

#endif // CONTROLLER_DATABASEMANAGER_H
