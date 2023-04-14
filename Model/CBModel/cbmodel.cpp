#include "cbmodel.h"
#include "../View/FifthWindow/fifthwindow.h"

CBModel::CBModel()
{
    __tableCB = new QList<QString>;
    __textCB = new QList<QString>;
    __CBM_names_variant = new QVector<QVariant>;

    updateData(0);
}

CBModel::~CBModel()
{
    delete __tableCB;
    delete __textCB;
}

void CBModel::updateData(int numTable)
{
    emit beginResetModel();
    __numTable = numTable;
    FifthWindow fw;
   // *__tableCB= fw.getTableName();

    if(__numTable == FIRST_TABLE)
    {
        __textCB->clear();
        *__textCB = fw.getColumnName(FIRST_TABLE);
    }
    else if (__numTable == SECOND_TABLE)
    {
        __textCB->clear();
        *__textCB = fw.getColumnName(SECOND_TABLE);
    }
    else if (__numTable == THIRD_TABLE )
    {
        __textCB->clear();
        *__textCB = fw.getColumnName(THIRD_TABLE);
    }
    insertRows(0,rowCount());
    emit endResetModel();
}
int CBModel::rowCount(const QModelIndex &parent) const
{
    if(__numTable == FIRST_TABLE || __numTable == SECOND_TABLE)
        return 5;
    else if (__numTable == THIRD_TABLE)
        return 3;
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
    emit dataChanged(index, index, {role});
    __CBM_names_variant->push_back(value);
}

bool CBModel::insertRows(int row, int count, const QModelIndex &parent)
{
    int row_count = rowCount();
    if (count == 0 || row > row_count)
        return false;

    emit beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        setData(createIndex(i, 0),QVariant(__textCB->at(i)));
    }
    emit endInsertRows();
    return true;
}

bool CBModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int row_count = rowCount();
    if (count == 0 || (row + count - 1) > row_count)
        return false;
    emit beginRemoveRows(parent, row, row + count - 1);
    __textCB->remove(row, count);
    emit endRemoveRows();
    return true;
}
