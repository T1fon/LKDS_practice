#include "controller_databasemanager.h"
#include"../Model/model_database.h"
#include"../View/SecondWindow/secondwindow.h"

Controller_DatabaseManager::Controller_DatabaseManager(QObject *parent)
    : QAbstractTableModel(parent)
{
    __columnNames << tr("Код компании") << tr("Наименование") << tr("ИНН") << tr("Регион") << tr("Город");
    __dispetcher = new Model_database(this);
    __dispetcher->connectToDataBase();
    __q = new QSqlQuery;
    __rowNames = new QVector<TableDisplay>;
    __query = "SELECT * FROM Custom" ;
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
    qDebug() << "Query: " << __query;
    __q = __dispetcher->queryToDB(__query);

    for (; __q->next();)
    {
       // qDebug() << "PAGEDDD";
        __rows_to_add = __q->value("COD_CUST").toInt();
       // qDebug() << "ROWWWWW :" << __rows_to_add;
        a.CodCust = __q->value("COD_CUST").toString();
        //qDebug() << a.CodCust;
        a.NameCust = __q->value("NAME_CUSTOM").toString();
       // qDebug() << a.NameCust;
        a.Inn = __q->value("INN").toString();
       // qDebug() << a.Inn;
        a.KodReg = __q->value("KOD_REG").toString();
        //qDebug() << a.KodReg;
        a.NameSity = __q->value("NAME_SITY").toString();
        //qDebug() << a.NameSity;

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
     delete bufbuf;
}
bool Controller_DatabaseManager::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, count+row);


    endInsertRows();
    return true;
 }
bool Controller_DatabaseManager::removeRows(int row, int count, const QModelIndex &parent)
{

}
void Controller_DatabaseManager::setReg(QString value){
    __companyReg = value;
}

int Controller_DatabaseManager::recieveData(QString cust,QString inn,QString reg,QString city, bool flag)
{

    TableDisplay buf;
    __dispetcher->connectToDataBase();


    __query = "SELECT * FROM Region WHERE NAME_REG = '" + reg +"'";
    //qDebug() << __query;
    __q = __dispetcher->queryToDB(__query);
    __q->next();
    if (__q->value("KOD_REG").toString() == "")
    {
        return -1;
    }

    QString t = "";
    if (!flag)
        buf.CodCust = t.setNum(__rows_to_add +1);
    else
        buf.CodCust = __companyCodCust;
    buf.NameCust = cust;
    buf.Inn = inn;
    buf.KodReg = __q->value("KOD_REG").toString();
    buf.NameSity = city;
    qDebug() << flag;

    if (!flag)
    {
        __query = "INSERT INTO Custom (NAME_CUSTOM, INN, KOD_REG, NAME_SITY ) VALUES ( ' " + buf.NameCust + " ', '" + buf.Inn + "', '" + buf.KodReg + "' , '" + buf.NameSity + "')";
        //qDebug() << __query;
        __q = __dispetcher->queryToDB(__query);
        __rowNames->push_back(buf);
        insertRows(__rows, 1);
        __rows++;
    }
    else
    {
        //UPDATE Custom SET NAME_CUSTOM = 1, INN = 2, KOD_REG = 3, NAME_SITY = 4 WHERE COD_CUST = 71
        qDebug() << "NAMECUST:" << buf.NameCust << "INN" << buf.Inn << "KOD_REG" << buf.KodReg << "NAME_SITY" << buf.NameSity << "CODCUST" << __companyCodCust;
        __query = "UPDATE Custom SET NAME_CUSTOM = '" + buf.NameCust + "', INN = '" + buf.Inn + "', KOD_REG = '" + buf.KodReg + "', NAME_SITY ='" + buf.NameSity + "' WHERE COD_CUST = '" + __companyCodCust + "'";
        __q = __dispetcher->queryToDB(__query);

        beginResetModel();
        __rowNames->remove(__row);
        __rowNames->push_back(buf);
        endResetModel();
    }

}

void Controller_DatabaseManager::searchCompany(QString searchplace)
{
    __query = "SELECT * FROM Custom WHERE INN LIKE '%" + searchplace + "%' OR NAME_CUSTOM LIKE '%" +  searchplace + "%';";

    beginResetModel();
    __rowNames->clear();
    this->updateModel();
    endResetModel();
}

void Controller_DatabaseManager::refreshTable()
{
    __dispetcher->connectToDataBase();
     __query = "SELECT * FROM Custom";
    beginResetModel();
     __rowNames->clear();
     this->updateModel();
    endResetModel();
}

void Controller_DatabaseManager::chooseRegion(int row)
{
    __row = row;
    //qDebug() <<"ROW: " << row;
    TableDisplay bufer;
    bufer = __rowNames->at(row);
    qDebug() << "REG SECWIN" << bufer.KodReg;
    __companyCodCust = bufer.CodCust;
    __companyCity = bufer.NameSity;
    __companyReg = bufer.KodReg;
}

QString Controller_DatabaseManager::checkCodCust()
{
    return __companyCodCust;
}

QString Controller_DatabaseManager::checkCity()
{
    return __companyCity;
}
QString Controller_DatabaseManager::checkReg()
{
    return __companyReg;
}
QString Controller_DatabaseManager::checkReg1()
{
    return __companyReg1;
}
QString Controller_DatabaseManager::checkInn()
{
    return __companyInn;
}
QString Controller_DatabaseManager::checkName()
{
    return __companyName;
}

QString Controller_DatabaseManager::lastKey()
{
    __dispetcher->connectToDataBase();
    if (__companyCodCust != "")
        __query = "SELECT * FROM Service_key WHERE KOD_CUST = '" + __companyCodCust + "' ORDER BY ID_NUM DESC";
    else
        __query = "SELECT * FROM Service_key ORDER BY ID_NUM DESC";
    __q = __dispetcher->queryToDB(__query);
    qDebug() << __query;
    __q->next();
    __keyDate = __q->value("DATE").toString();
    __keyNum = __q->value("NUM_KEY").toString();
    qDebug() << "COD_CUST" << __companyCodCust << "DATE" << __keyDate << "NUM" << __keyNum;
    QString a = "COD CUST: " + __companyCodCust +  "\nDATE: " + __keyDate + "\nNUM: " + __keyNum;
    return a;

}

void Controller_DatabaseManager::redactProfile(int row)
{
    TableDisplay bufer;
    QString buf;
    bufer = __rowNames->at(row);
    qDebug() << "REG SECWIN" << bufer.KodReg;
    __companyCity = bufer.NameSity;
    __companyInn = bufer.Inn;
    __companyName = bufer.NameCust;
    __companyCodCust = bufer.CodCust;
    buf = bufer.KodReg;
    __dispetcher->connectToDataBase();
    __query = "SELECT * FROM REGION WHERE KOD_REG = " + buf;
    __q = __dispetcher->queryToDB(__query);
    __q->next();
    __companyReg1 = __q->value("NAME_REG").toString();

}

Controller_DatabaseManager::~Controller_DatabaseManager()
{
    delete __dispetcher;
}
