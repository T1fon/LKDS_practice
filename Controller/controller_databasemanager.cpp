#include "controller_databasemanager.h"
#include"../Model/model_database.h"

Controller_DatabaseManager::Controller_DatabaseManager(QObject *parent)
    : QAbstractTableModel(parent)
{
    if (__page == PAGE_SECOND_WINDOW)
    {
        __columnNames << tr("Cod_Cust") << tr("Name_Custom") << tr("INN") << tr("Reg") << tr("City");
    }
    else if (__page == PAGE_THIRD_WINDOW)
    {
        __columnNames <<tr("Cod_Cust") << tr("Id Num") << tr("Date") << tr("Num key");
    }
    __dispetcher = new Model_database(this);
    __dispetcher->connectToDataBase();
    __q = new QSqlQuery;
    __rowNames = new QVector<TableDisplay>;
    this->updateModel();

}
int Controller_DatabaseManager::rowCount(const QModelIndex &) const
{
   // qDebug() << "ROWS " <<__rows;
    return __rows;
}

int Controller_DatabaseManager::columnCount(const QModelIndex &) const
{
    if (__page == PAGE_SECOND_WINDOW)
    {
    return CountofColumnsCustom;
    }
    else if (__page == PAGE_THIRD_WINDOW)
    {
        return CountofColumnsService;
    }
}


QVariant Controller_DatabaseManager::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount()){
        return QVariant();
    }
    qDebug() << __columnNames.at(section);
    return __columnNames.at(section);
}

QHash<int, QByteArray> Controller_DatabaseManager::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

QVariant Controller_DatabaseManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= rowCount() || col >= columnCount() || role !=  Qt::DisplayRole)
        return QVariant();
    if (__page == PAGE_SECOND_WINDOW)
    {
    switch (col)
        {
            case ColumnCodCust:
                return __rowNames->at(row).CodCust;
            case ColumnNameCust:
                return __rowNames->at(row).NameCust;
            case ColumnINN:
                return __rowNames->at(row).Inn;
            case CountKodReg:
                return __rowNames->at(row).KodReg;
            case ColumnNameSity:
                return __rowNames->at(row).NameSity;
        }
    }
    else if (__page == PAGE_THIRD_WINDOW)
    {
        switch (col)
        {
            case ColumnKodCust:
                return __serviceNames->at(row).KodCust;
            case ColumnIdNum:
                return __serviceNames->at(row).IdNum;
            case ColumnDate:
                return __serviceNames->at(row).Date;
            case ColumnNumKey:
                return __serviceNames->at(row).NumKey;
        }

    }

    //return QVariant();
}


void Controller_DatabaseManager::updateModel()
{
    TableDisplay a;
    TableDisplayServiceKey b;
    __rows = 0;
    bool flag = false;
    if (__page == PAGE_SECOND_WINDOW)
    {
         __query = "SELECT * FROM Custom";
    }
    else if (__page == PAGE_THIRD_WINDOW)
    {
         __query = "SELECT * FROM Custom";
    }
    flag = __q->exec(__query);
    if(!flag)
            qDebug() << "NO Flag";

    if (__page == PAGE_SECOND_WINDOW)
    {
        for (; __q->next();)
        {
            a.CodCust = __q->value("COD_CUST").toString();
            qDebug() << a.CodCust;
            a.NameCust = __q->value("NAME_CUSTOM").toString();
            qDebug() << a.NameCust;
            a.Inn = __q->value("INN").toString();
            qDebug() << a.Inn;
            a.KodReg = __q->value("KOD_REG").toString();
            qDebug() << a.KodReg;
            a.NameSity = __q->value("NAME_SITY").toString();
            qDebug() << a.NameSity;

         __rowNames->push_back(a);
         __rows++;
        }
    }
    else if (__page == PAGE_THIRD_WINDOW)
    {
        for (; __q->next();)
        {
            b.KodCust = __q->value("KOD_CUST").toString();
            b.IdNum = __q->value("ID_NUM").toString();
            b.Date = __q->value("DATE").toString();
            b.NumKey = __q->value("NUM_KEY").toString();

         __serviceNames->push_back(b);
         __rows++;
        }
    }

}

void Controller_DatabaseManager::changeToSecond()
{
    __page = PAGE_SECOND_WINDOW;
    emit sendToQml();

}
void Controller_DatabaseManager::changeToThird()
{
    __page = PAGE_THIRD_WINDOW;
}

Controller_DatabaseManager::~Controller_DatabaseManager()
{
    delete __dispetcher;
}
