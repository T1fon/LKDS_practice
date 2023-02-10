#include "controller_databasemanager.h"
#include"../Model/model_database.h"

Controller_DatabaseManager::Controller_DatabaseManager(QObject *parent)
    : QAbstractTableModel(parent)
{
    qDebug() << 00;
    __columnNames << tr("Cod_Cust") << tr("Name_Custom") << tr("INN") << tr("Reg") << tr("City");
    __dispetcher = new Model_database;
    __dispetcher->connectToDataBase();
    __q = new QSqlQuery;
    this->updateModel();
}
/////DODELAT C BD
int Controller_DatabaseManager::rowCount(const QModelIndex &) const
{
    return ;
}

int Controller_DatabaseManager::columnCount(const QModelIndex &) const
{
    return;
}
//////DODELAT C BD


QVariant Controller_DatabaseManager::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
            return QVariant();

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
            return QString("Multicast %1").arg(row + 1 /*, 2, QChar('0')*/);
        case ColumnNameCust:
            return QString("235.0.0.%1").arg(row + 1);
        case ColumnINN:
            return 1001 + row;
        case CountKodReg:
        case ColumnNameSity:
        }

        return QVariant();
}

int Controller_DatabaseManager::getId(int row)
{
     return this->data(this->index(row, 0), ColumnCodCust).toInt();
}

void Controller_DatabaseManager::updateModel()
{
    QString qq = "SELECT * FROM Custom";
    __q = __dispetcher->queryToDB(qq);
}

Controller_DatabaseManager::~Controller_DatabaseManager()
{
    delete __dispetcher;
}
