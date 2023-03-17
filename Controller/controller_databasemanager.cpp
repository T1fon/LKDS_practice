#include "controller_databasemanager.h"
#include"../Model/model_database.h"
#include"../View/SecondWindow/secondwindow.h"

Controller_DatabaseManager::Controller_DatabaseManager(QObject *parent)
    : QAbstractTableModel(parent)
{
    __columnNames << tr("Cod_Cust") << tr("Name_Custom") << tr("INN") << tr("Reg") << tr("City");
    __dispetcher = new Model_database(this);
    __dispetcher->connectToDataBase();
    __q = new QSqlQuery;
    __rowNames = new QVector<TableDisplay>;
    this->updateModel();
    connect(this, SIGNAL(send(QString,QString,QString,QString)),this, SLOT(recieveData(QString,QString,QString,QString)));

}
int Controller_DatabaseManager::rowCount(const QModelIndex &) const
{
   // qDebug() << "ROWS " <<__rows;
    return __rows;
}

int Controller_DatabaseManager::columnCount(const QModelIndex &) const
{
    return CountofColumnsCustom;
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
    //return QVariant();
}


void Controller_DatabaseManager::updateModel()
{
    TableDisplay a;
    __rows = 0;
    __query = "SELECT * FROM Custom";
    __q = __dispetcher->queryToDB(__query);

    for (; __q->next();)
    {
        qDebug() << "PAGEDDD";
        __rows_to_add = __q->value("COD_CUST").toInt();
        qDebug() << "ROWWWWW :" << __rows_to_add;
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

Qt::ItemFlags Controller_DatabaseManager::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool Controller_DatabaseManager::setData(const QModelIndex &index,const QVariant &value, int role)
 {
    if (bufbuf == nullptr)
    {
        bufbuf = new TableDisplay;
    }
    int col = index.column();
    QString a = "";

    switch (col)
    {
    case ColumnCodCust:
        bufbuf->CodCust = a.setNum(__rows_to_add + 1);
    case ColumnNameCust:
        bufbuf->NameCust = value.toString();
    case ColumnINN:
        bufbuf->Inn = value.toString();
    case CountKodReg:
        bufbuf->KodReg = value.toString();
    case ColumnNameSity:
        bufbuf->NameSity = value.toString();
    }

     if (index.isValid() && role == Qt::EditRole)
     {
        // __rowNames->replace();
        if((bufbuf->NameCust != "&") && (bufbuf->Inn != "&") && (bufbuf->KodReg != "&") && (bufbuf->NameSity != "&"))
        {
        emit dataChanged(index, index);
         __rowNames->replace(index.row(), *bufbuf);
         return true;
        }
     }
     return false;
}
bool Controller_DatabaseManager::insertRows(int row, int count, const QModelIndex &parent)
{
    emit beginInsertRows(parent, row, count+row);


    emit endInsertRows();
    return true;
 }
bool Controller_DatabaseManager::removeRows(int row, int count, const QModelIndex &parent)
{

}

void Controller_DatabaseManager::recieveData(QString cust,QString inn,QString reg,QString city)
{

    qDebug() << 123456;
    TableDisplay buf;
    __dispetcher->connectToDataBase();

    if (__dispetcher->isOpen())
       qDebug() << "YES";
    else
       qDebug() << "NO";

    __query = "SELECT * FROM Region WHERE NAME_REG = '" + reg +"'";
    //qDebug() << __query;
    __q = __dispetcher->queryToDB(__query);
    __q->next();

    QString t = "";

    buf.CodCust = t.setNum(__rows_to_add +1);
    buf.NameCust = cust;
    buf.Inn = inn;
    buf.KodReg = __q->value("KOD_REG").toString();
    buf.NameSity = city;


    __query = "INSERT INTO Custom (NAME_CUSTOM, INN, KOD_REG, NAME_SITY ) VALUES ( ' " + buf.NameCust + " ', '" + buf.Inn + "', '" + buf.KodReg + "' , '" + buf.NameSity + "')";

    qDebug() << __query;
    __q = __dispetcher->queryToDB(__query);
    __rowNames->push_back(buf);
    insertRows(__rows, 1);
    __rows++;

}

Controller_DatabaseManager::~Controller_DatabaseManager()
{
    delete __dispetcher;
}
