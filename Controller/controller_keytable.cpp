#include "controller_keytable.h"

Controller_KeyTable::Controller_KeyTable(QObject *parent):QAbstractTableModel(parent)
{
    __dispetcher = new Model_database;
    __dispetcher->connectToDataBase();
    __columnNames  << tr("Id Num")<< tr("Kod_Cust") << tr("Kod Reg") << tr("Date") << tr("Num key");
    __q = new QSqlQuery;
   // if (__codCust == "")
    //    __query = "SELECT * FROM Service_key";
    qDebug() <<"constQ" << __query;
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
        case ColumnIdNum:
            return __serviceNames->at(row).IdNum;
        case ColumnKodCust:
            return __serviceNames->at(row).KodCust;
        case ColumnReg:
            return __serviceNames->at(row).KodReg;
        case ColumnDate:
            return __serviceNames->at(row).Date;
        case ColumnNumKey:
            return __serviceNames->at(row).NumKey;
    }

    //return QVariant();
}
void Controller_KeyTable::updateModel()
{
   // qDebug() << "KEQTable Query:" << __query;
    TableDisplayServiceKey b;
    __rows = 0;
    bool flag =__dispetcher->isOpen();
   // qDebug() << flag;
    __dispetcher->connectToDataBase();
    __q = __dispetcher->queryToDB(__query);
    //qDebug() << __q;
    for (; __q->next();)
    {
        __rowsID = __q->value("ID_NUM").toInt();

        b.IdNum = __q->value("ID_NUM").toString();
         //qDebug()<< "ID" << __q->value("ID_NUM");

        b.KodCust = __q->value("KOD_CUST").toString();
        //qDebug() <<"KOD_CUST"<< __q->value("KOD_CUST");

        b.KodReg = __q->value("KOD_REG").toString();

        b.Date = __q->value("DATE").toString();
       // qDebug() << "Date" << __q->value("DATE");


        __numKey = __q->value("NUM_KEY").toInt();
        b.NumKey = __q->value("NUM_KEY").toString();
       // qDebug() << "Num" << __q->value("NUM_KEY");

     __serviceNames->push_back(b);
     __rows++;
    }
    qDebug() << "ROWS" << __rows;

}

void Controller_KeyTable::recieveRegion(QString codcust, QString city, QString reg)
{
    __dispetcher->connectToDataBase();
    __codCust = codcust;
    __city = city;
    __kodReg = reg;
    qDebug() << "RET TH" << __kodReg;
    if (__kodReg == "")
        __query = "SELECT * FROM Service_key";
    else
        __query = QString("SELECT * FROM Service_key WHERE KOD_REG ='") + __kodReg + QString("'");
    qDebug() << __query;
    emit beginResetModel();
    __serviceNames->clear();
    this->updateModel();
    emit endResetModel();
}
bool Controller_KeyTable::setData(const QModelIndex &index,const QVariant &value, int role)
 {
    if (__keyTable == nullptr)
    {
        __keyTable = new TableDisplayServiceKey;
    }
    int col = index.column();
    QString a = "";

    switch (col)
    {
    case ColumnIdNum:
        __keyTable->IdNum = a.setNum(__rowsID + 1);
    case ColumnKodCust:
        __keyTable->KodCust = value.toString();
    case ColumnReg:
        __keyTable->KodReg = value.toString();
    case ColumnDate:
        __keyTable->Date = value.toString();
    case ColumnNumKey:
        a = "";
        __keyTable->NumKey = a.setNum(__numKey);
    }

     if (index.isValid() && role == Qt::EditRole)
     {
        // __rowNames->replace();
        if((__keyTable->KodCust != "&") && (__keyTable->Date != "&") && (__keyTable->IdNum != "&")&& (__keyTable->KodReg != "&"))
        {
        emit dataChanged(index, index);
         __serviceNames->replace(index.row(), *__keyTable);
         return true;
        }
     }
     return false;
     delete __keyTable;
}
Qt::ItemFlags Controller_KeyTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool Controller_KeyTable::insertRows(int row, int count, const QModelIndex &parent)
{
    emit beginInsertRows(parent, row, count+row);
    qDebug() <<__query;
    emit endInsertRows();
    return true;
}
bool Controller_KeyTable::removeRows(int row, int count, const QModelIndex &parent)
{

}
void Controller_KeyTable::deleteKey(QString num_key, QString kod_reg){
    __query = QString("DELETE FROM Service_key WHERE NUM_KEY = ") + num_key + " AND KOD_REG = " + kod_reg + ";";
    qDebug() << __query;
    __dispetcher->connectToDataBase();
    __q = __dispetcher->queryToDB(__query);
    //__q->exec();
}
void Controller_KeyTable::addKey(QString key)
{
    int i = key.toInt();

   TableDisplayServiceKey buf;

   QString t = "";

   buf.KodCust =__codCust;
   qDebug() << "K" << __codCust;

   buf.IdNum = t.setNum(__rowsID + 1);
   qDebug() << "KOD"<<buf.KodCust;
   t = "";

   buf.KodReg = __kodReg;

   buf.Date = QDate::currentDate().toString("dd.MM.yyyy");
   __numKey = numKeyFofReg(__kodReg);
   qDebug() << "NUM KEY:" <<  __numKey << "ROWSID" << __rowsID;
   buf.NumKey = t.setNum(__numKey + 1);
   __numKey = i;
   __rowsID ++;


   __query = "INSERT INTO Service_key (KOD_CUST, KOD_REG, DATE, NUM_KEY) VALUES ( ' " + buf.KodCust + " ', '"+buf.KodReg + "', '" + buf.Date + "', '" + buf.NumKey + "')";
   __dispetcher->connectToDataBase();
   __q = __dispetcher->queryToDB(__query);
   __serviceNames->push_back(buf);
   insertRows(__rows, 1);
   __rows++;

}

QString Controller_KeyTable::printData()
{
   QString buf = "ГОРОД:" + __city + "    " + "Префикс:" + __kodReg;
   return buf;
}

QString Controller_KeyTable::addCodCust()
{
    return __codCust;
}

int Controller_KeyTable::numKeyFofReg(QString __kodReg)
{
    qDebug() << "srart";
    __query = "SELECT *FROM Service_key WHERE KOD_REG = " + __kodReg + " ORDER BY NUM_KEY DESC";
    __dispetcher->connectToDataBase();
    __q = __dispetcher->queryToDB(__query);
    __q->next();
    if (__q->value("NUM_KEY") == "")
        return 0;
    else
        return __q->value("NUM_KEY").toInt();
}

int Controller_KeyTable::getKey()
{
    return __numKey;
}
QString Controller_KeyTable::getReg()
{
    return __kodReg;
}

Controller_KeyTable::~Controller_KeyTable()
{
    delete __q;
    delete __serviceNames;
    delete __dispetcher;
}


