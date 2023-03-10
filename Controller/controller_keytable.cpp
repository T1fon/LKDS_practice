#include "controller_keytable.h"

Controller_KeyTable::Controller_KeyTable(QObject *parent):QAbstractTableModel(parent)
{
    __columnNames <<tr("Cod_Cust") << tr("Id Num") << tr("Date") << tr("Num key");
    __q = new QSqlQuery;
    __serviceNames = new QVector<TableDisplayServiceKey>;
    this->updateModel();
}

int Controller_KeyTable::rowCount(const QModelIndex &) const
{
    return __rows;
}

int Controller_KeyTable::columnCount(const QModelIndex &) const
{

    return CountofColumnsService;
}

QVariant Controller_KeyTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount()){
        return QVariant();
    }
    qDebug() << __columnNames.at(section);
    return __columnNames.at(section);
}

QHash<int, QByteArray> Controller_KeyTable::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

QVariant Controller_KeyTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= rowCount() || col >= columnCount() || role !=  Qt::DisplayRole)
        return QVariant();
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

    //return QVariant();
}
void Controller_KeyTable::updateModel()
{
    TableDisplayServiceKey b;
    __rows = 0;
    bool flag = false;
    __query = "SELECT * FROM Service_key";
    flag = __q->exec(__query);
    if(!flag)
        qDebug() << "NO Flag";
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

Controller_KeyTable::~Controller_KeyTable()
{

}


