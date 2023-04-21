#include "cbmodel.h"
#include "../../View/FifthWindow/fifthwindow.h"

CBModel::CBModel()
{
    __tableCB = new QList<QString>;
    __textCB = new QList<QString>;
    __CBM_names_variant = new QVector<QVariant>;

    //updateData(0);
}

CBModel::~CBModel()
{
    delete __tableCB;
    delete __textCB;
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
        qDebug() << "FALSE";
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    __textCB->remove(row, count);
    __CBM_names_variant->remove(row, count);
    endRemoveRows();
    return true;
}
void CBModel::updateData(int numTable)
{
    __numTable = numTable;
    FifthWindow fw;

    removeRows(0, __textCB->size());
    *__textCB = fw.getColumnName(numTable);
    insertRows(0,__textCB->size());
}
int CBModel::rowCount(const QModelIndex &parent) const
{
    return __textCB->size();
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
    int row_count = count;
    if (count == 0 || row > row_count)
        return false;

    beginInsertRows(parent, row, row + count - 1);
    qDebug() << "Count = " << count;
    for (int i = 0; i < count; i++)
    {
        setData(createIndex(i, 0),QVariant(__textCB->at(i)));
    }
    endInsertRows();
    return true;
}


