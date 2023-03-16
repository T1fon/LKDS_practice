#include "COMPortModel.h"

COMPortModel::COMPortModel()
{
    __COM_names_variant = new QVector<QVariant>;
    __COM_info = new QList<QSerialPortInfo>;

   updateData();
}

COMPortModel::~COMPortModel()
{
    delete __COM_info;
    delete __COM_names_variant;
}

void COMPortModel::updateData(){
    *__COM_info = QSerialPortInfo::availablePorts();
    qDebug() << "DataUpdate";
    if(!removeRows(0,__COM_names_variant->size())){
        qDebug() << "Data no Add";
    }
    if(!insertRows(0,__COM_info->size())){
        qDebug() << "Data no remove";
    }
}

bool COMPortModel::setData(const QModelIndex &index, const QVariant &value, int role){
    emit dataChanged(index,index,{role});
    __COM_names_variant->push_back(value);
    return true;
}
bool COMPortModel::insertRows(int row, int count, const QModelIndex &parent){
    int row_count = rowCount();
    if(count == 0 || row > row_count){
        return false;
    }

    emit beginInsertRows(parent,row,row+count-1);
    for(int i = 0; i < count; i++){
        setData(createIndex(i,0),QVariant(__COM_info->at(i).portName()));
    }
    emit endInsertRows();
    return true;
}
bool COMPortModel::removeRows(int row, int count, const QModelIndex &parent){
    int row_count = rowCount();
    if(count == 0 || (row + count - 1) > row_count){
        return false;
    }

    emit beginRemoveRows(parent,row,row+count-1);
    __COM_names_variant->remove(row,count);
    emit endRemoveRows();
    return true;
}
int COMPortModel::rowCount(const QModelIndex &parent) const{
    return __COM_names_variant->size();
}
QVariant COMPortModel::data(const QModelIndex &index, int role)const{
    int temp_row = index.row();

    if(role != Qt::DisplayRole || !index.isValid() || temp_row >= rowCount()){
        return QVariant();
    }

    return __COM_names_variant->at(temp_row);
}
QHash<int, QByteArray> COMPortModel::roleNames()const{
    return {{Qt::DisplayRole,"display"}};
}

QString COMPortModel::getDeviceName(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString( __COM_info->at(index).description() );
}
QString COMPortModel::getPortName(const int &index){
    if(index >= rowCount()){
        return "";
    }
    return __COM_info->at(index).portName();
}
QString COMPortModel::getDeviceId(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString().setNum(__COM_info->at(index).productIdentifier());
}
QString COMPortModel::getManufacturerName(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString( __COM_info->at(index).manufacturer() );
}
QString COMPortModel::getManufacturerId(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString().setNum(__COM_info->at(index).vendorIdentifier() );
}
