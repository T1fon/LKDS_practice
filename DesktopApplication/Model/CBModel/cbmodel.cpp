    #include "cbmodel.h"
#include "../../View/FifthWindow/fifthwindow.h"

CBModel::CBModel()
{
    __tableCB = new QList<QString>;
    __textCB = new QList<QString>;
    __CBM_names_variant = new QVector<QVariant>;
    __dispetcher = new Model_database;
    __q = new QSqlQuery;

    //updateData(0);
}

CBModel::~CBModel()
{
    delete __tableCB;
    delete __textCB;
    delete __dispetcher;
    delete __q;
}
QString CBModel::getValue(int row){
    if(row >= rowCount()){

        return "Некорректная строчка";
    }
    return __CBM_names_variant->at(row).toString();
}
bool CBModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0 || (row + count - 1) > rowCount()){
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    __CBM_names_variant->remove(row, count);
    endRemoveRows();
    return true;
}
void CBModel::updateData(int numTable)
{
    __numTable = numTable;
    FifthWindow fw;

    removeRows(0, __CBM_names_variant->size());
    *__textCB = fw.getColumnName(numTable);
    for (int i = 0; i < __textCB->size(); i++)
    {
        __CBM_names_variant->push_back(QVariant(__textCB->at(i)));
    }
    insertRows(0,__CBM_names_variant->size());
}
int CBModel::rowCount(const QModelIndex &parent) const
{
    return __CBM_names_variant->size();
}

QVariant CBModel::data(const QModelIndex &index, int role) const
{
    int temp_row = index.row();

    if(role != Qt::DisplayRole || !index.isValid() || temp_row >= rowCount()){
        return QVariant();
    }

    return __CBM_names_variant->at(temp_row);
}

QHash<int, QByteArray> CBModel::roleNames()const
{
    return {{Qt::DisplayRole,"display"}};
}

bool CBModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   __CBM_names_variant->push_back(value);
    emit dataChanged(index, index, {role});
    return true;
}

bool CBModel::insertRows(int row, int count, const QModelIndex &parent)
{
    int row_count = count;
    if (count == 0)
        return false;

    beginInsertRows(parent, row, row + count - 1);
    for (int i = row; i < count; i++)
    {
        setData(createIndex(i, 0),QVariant(__textCB->at(i)));
    }
    endInsertRows();
    return true;
}

void CBModel::secWinData(QString value)
{
    __finalQuery = value;
    __dispetcher->connectToDataBase();
    if(__finalQuery == "")
    {
        __query = "SELECT * FROM Region;";
    }
    else
    {
        __query = "SELECT * FROM Region WHERE NAME_REG LIKE '%" + __finalQuery + "%'";
    }

    __q = __dispetcher->queryToDB(__query);

    removeRows(0, __CBM_names_variant->size());
    __textCB->clear();

    for (; __q->next();)
    {
        QString buf = "";
        buf = __q->value("NAME_REG").toString();
        __textCB->push_back(buf);

    }
    insertRows(0, __textCB->size());

}

void CBModel::clearQuery()
{
    __finalQuery.clear();
    removeRows(0, __CBM_names_variant->size());
    __CBM_names_variant->clear();
}

void CBModel::deleteQueryEl()
{
    __finalQuery.chop(1);
}

QString CBModel::getQuery()
{
    return __finalQuery;
}


