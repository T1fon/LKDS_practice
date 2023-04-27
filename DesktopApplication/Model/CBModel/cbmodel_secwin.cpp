#include "cbmodel_secwin.h"

CBModel_secwin::CBModel_secwin()
{
    __dispetcher = new Model_database;
    __q = new QSqlQuery;
    __regCB = new QList<QString>;

}

CBModel_secwin::~CBModel_secwin()
{
    delete __dispetcher;
    delete __q;
}
QString CBModel_secwin::getValue(int row){
    if(row >= rowCount()){

        return "Некорректная строчка";
    }
    return __CBMSW_names_variant->at(row).toString();
}
bool CBModel_secwin::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0 || (row + count - 1) > rowCount()){
        qDebug() << "FALSE";
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    __regCB->remove(row, count);
    __CBMSW_names_variant->remove(row, count);
    endRemoveRows();
    return true;
}
void CBModel_secwin::updateData(QString text)
{
    __dispetcher->connectToDataBase();
    __query = "SELECT * FROM Region WHERE NAME_REG LIKE '%" +text + "%'";
    __q = __dispetcher->queryToDB(__query);

    removeRows(0, __regCB->size());

    for (; __q->next();)
    {
        __regCB->push_back(__q->value("NAME_REG").toString());
    }

    insertRows(0,__regCB->size());
}
int CBModel_secwin::rowCount(const QModelIndex &parent) const
{
    return __regCB->size();
}

QVariant CBModel_secwin::data(const QModelIndex &index, int role) const
{
    int temp_row = index.row();

    if(role != Qt::DisplayRole || !index.isValid() || temp_row >= rowCount()){
        return QVariant();
    }

    return __CBMSW_names_variant->at(temp_row);
}

QHash<int, QByteArray> CBModel_secwin::roleNames()const
{
    return {{Qt::DisplayRole,"display"}};
}

bool CBModel_secwin::setData(const QModelIndex &index, const QVariant &value, int role)
{
    emit dataChanged(index, index, {role});
    __CBMSW_names_variant->push_back(value);
}

bool CBModel_secwin::insertRows(int row, int count, const QModelIndex &parent)
{
    int row_count = count;
    if (count == 0 || row > row_count)
        return false;

    beginInsertRows(parent, row, row + count - 1);
    qDebug() << "Count = " << count;
    for (int i = 0; i < count; i++)
    {
        setData(createIndex(i, 0),QVariant(__regCB->at(i)));
    }
    endInsertRows();
    return true;
}
