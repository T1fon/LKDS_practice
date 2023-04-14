#ifndef CONTROLLER_ALLBASE_H
#define CONTROLLER_ALLBASE_H

#include <QObject>
#include <QObject>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QStringList>
#include <QAbstractTableModel>
#include "../Model/model_database.h"
#include <QMap>
#include <QVector>
#include <QSqlDatabase>
#include <QFile>
#include <QTextStream>

#define DATABASE_NAME "LKDS_Base.db"
#define DATABASE_WAY "DataBase/LKDS_Base.db"
#define FIRST_TABLE 0
#define SECOND_TABLE 1
#define THIRD_TABLE 2

struct Custom
{
    QString CodCust = "&";
    QString NameCust = "&";
    QString Inn = "&";
    QString KodReg = "&";
    QString NameSity = "&";
};

struct ServiceKey
{
    QString IdNum;
    QString KodCust;
    QString KodReg;
    QString Date;
    QString NumKey;

};

struct Region
{
    QString KodReg = "&";
    QString NameReg = "&";
};

class controller_allBase : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)


public:

    enum {
            ColumnCodCust = 0,
            ColumnNameCust,
            ColumnINNCust,
            ColumnKodRegCust,
            ColumnNameSityCust,
            CountofColumnsCustom
        };
    enum {
            ColumnIdNumKey = 0,
            ColumnKodCustKey,
            ColumnRegKey,
            ColumnDateKey,
            ColumnNumKey,
            CountofColumnsService
        };
    enum{
            ColumnKodReg = 0,
            ColumnNameReg,
            CountofColumnsReg
    };


    explicit controller_allBase(QObject *parent = nullptr);
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
    ~controller_allBase();

private:

    int __numTable = 0;
    int __rows;
    QStringList __customNames, __keyNames, __regNames;
    QVector<Custom> *__customTable;
    QVector<ServiceKey> *__keyTable;
    QVector<Region> *__regTable;
    QSqlQuery *__q;
    Model_database * __dispetcher;
    QString __query;
    QVector<QMap<QString, QString>> *__filedate;

    Custom * __cust_display = nullptr;
    ServiceKey * __serv_display = nullptr;
    Region * __reg_display = nullptr;

    int __rows_cust = 0, __rows_reg = 0;
    int __numRow, __rowDelete;
    QString __companyCodCust = "", __companyCity = "", __companyInn = "", __companyName = "", __companyReg = "";
    QString __regKodReg = "", __regNameReg = "";
    bool __checkTouch = false;
    QString __secTabName = "CodCust";

public slots:
    void updateModel();
    int getTableNum();
    void setTableNum(int value);
    void addCustomData(QString cust,QString inn,QString reg,QString city, bool flag);
    void addRegData(QString kodreg, QString name, bool flag);
    void chooseRow(int row);
    void redactProfile(int row);
    void refreshTable();
    void deleteRow();
    QString checkCodCust();
    QString checkCity();
    QString checkReg();
    QString checkInn();
    QString checkName();
    QString checkRegKodReg();
    QString checkRegNameReg();
    int checkTable();
    bool checkTouchFlag();
    void pushDataToFile(QString path);
    void search(QString text);
    void setSecTabNum(int value);


signals:

};

#endif // CONTROLLER_ALLBASE_H
